/*
Copyright (c) 2007, Adobe Systems, Incorporated
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are
met:

* Redistributions of source code must retain the above copyright
  notice, this list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright
  notice, this list of conditions and the following disclaimer in the
  documentation and/or other materials provided with the distribution.

* Neither the name of Adobe Systems, Network Resonance nor the names of its
  contributors may be used to endorse or promote products derived from
  this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/



static char *RCSSTRING __UNUSED__="$Id: stun_server_ctx.c,v 1.2 2008/04/28 18:21:30 ekr Exp $";

#include <string.h>
#include <assert.h>

#include "nr_api.h"
#include "stun.h"

static int nr_stun_server_destroy_client(nr_stun_server_client *clnt);
static int nr_stun_server_send_response(nr_stun_server_ctx *ctx, nr_socket *sock, nr_transport_addr *peer_addr, nr_stun_message *res, nr_stun_server_client *clnt);
static int nr_stun_server_process_request_auth_checks(nr_stun_server_ctx *ctx, nr_stun_message *req, int auth_rule, nr_stun_message *res);


int nr_stun_server_ctx_create(char *label, nr_socket *sock, nr_stun_server_ctx **ctxp)
  {
    int r,_status;
    nr_stun_server_ctx *ctx=0;

    if ((r=nr_stun_startup()))
      ABORT(r);

    if(!(ctx=RCALLOC(sizeof(nr_stun_server_ctx))))
      ABORT(R_NO_MEMORY);

    if(!(ctx->label=r_strdup(label)))
      ABORT(R_NO_MEMORY);
    ctx->sock=sock;
    nr_socket_getaddr(sock,&ctx->my_addr);

    STAILQ_INIT(&ctx->clients);
    
    *ctxp=ctx;

    _status=0;
  abort:
    return(_status);
  }

int nr_stun_server_ctx_destroy(nr_stun_server_ctx **ctxp)
  {
    nr_stun_server_ctx *ctx;
    nr_stun_server_client *clnt1,*clnt2;

    if(!ctxp || !*ctxp)
      return(0);
    
    ctx=*ctxp;
   
    STAILQ_FOREACH_SAFE(clnt1, &ctx->clients, entry, clnt2) {
        nr_stun_server_destroy_client(clnt1);
    }

    RFREE(ctx->label);
    RFREE(ctx);
    
    return(0);
  }

int nr_stun_server_add_client(nr_stun_server_ctx *ctx, char *client_label, char *user, Data *pass, int (*stun_server_cb)(void *cb_arg, nr_stun_server_ctx *ctx,nr_socket *sock, nr_stun_server_request *req, int *error), void *cb_arg)
  {
    int r,_status;

    nr_stun_server_client *clnt=0;

    if(!(clnt=RCALLOC(sizeof(nr_stun_server_client))))
      ABORT(R_NO_MEMORY);
    
    if(!(clnt->label=r_strdup(client_label)))
      ABORT(R_NO_MEMORY);

    if(!(clnt->username=r_strdup(user)))
      ABORT(R_NO_MEMORY);

    if(r=r_data_copy(&clnt->password,pass))
      ABORT(r);

    clnt->stun_server_cb=stun_server_cb;
    clnt->cb_arg=cb_arg;

    STAILQ_INSERT_TAIL(&ctx->clients,clnt,entry);
    
    _status=0;
  abort:
    if(_status){
      nr_stun_server_destroy_client(clnt);
    }
    return(_status);
  }

int nr_stun_server_get_password(void *arg, nr_stun_message *msg, Data **password)
  {
    int _status;
    nr_stun_server_ctx *ctx = (nr_stun_server_ctx*)arg;
    nr_stun_server_client *clnt = 0;
    nr_stun_message_attribute *username_attribute;

    if ((nr_stun_get_message_client(ctx, msg, &clnt))) {
        if (! nr_stun_message_has_attribute(msg, NR_STUN_ATTR_USERNAME, &username_attribute)) {
           r_log(NR_LOG_STUN,LOG_NOTICE,"STUN-SERVER(%s): Missing Username",ctx->label);
           ABORT(R_NOT_FOUND);
        }

        r_log(NR_LOG_STUN,LOG_NOTICE,"STUN-SERVER(%s): Unable to find password for unknown user: %s",ctx->label,username_attribute->u.username);
        ABORT(R_NOT_FOUND);
    }

    *password = &clnt->password;

    _status=0;
  abort:
    return(_status);
  }

int nr_stun_server_process_request_auth_checks(nr_stun_server_ctx *ctx, nr_stun_message *req, int auth_rule, nr_stun_message *res)
  {
    int r,_status;

    if (nr_stun_message_has_attribute(req, NR_STUN_ATTR_MESSAGE_INTEGRITY, 0)
     || !(auth_rule & NR_STUN_AUTH_RULE_OPTIONAL)) {
        /* favor long term credentials over short term, if both are supported */

        if (auth_rule & NR_STUN_AUTH_RULE_LONG_TERM) {
            if ((r=nr_stun_receive_request_long_term_auth(req, ctx, res)))
                ABORT(r);
        }
        else if (auth_rule & NR_STUN_AUTH_RULE_SHORT_TERM) {
            if ((r=nr_stun_receive_request_or_indication_short_term_auth(req, res)))
                ABORT(r);
        }
    }

    _status=0;
  abort:
    return(_status);
  }

int nr_stun_server_process_request(nr_stun_server_ctx *ctx, nr_socket *sock, char *msg, int len, nr_transport_addr *peer_addr, int auth_rule)
  {
    int r,_status;
    char string[256];
    nr_stun_message *req = 0;
    nr_stun_message *res = 0;
    nr_stun_server_client *clnt;
    nr_stun_server_request info;
    int error;

    r_log(NR_LOG_STUN,LOG_DEBUG,"STUN-SERVER(%s): Received(my_addr=%s,peer_addr=%s)",ctx->label,ctx->my_addr.as_string,peer_addr->as_string);
   
    snprintf(string, sizeof(string)-1, "STUN-SERVER(%s): Received ", ctx->label);
    r_dump(NR_LOG_STUN, LOG_DEBUG, string, (char*)msg, len);

    memset(&info,0,sizeof(info));

    if ((r=nr_stun_message_create2(&req, (UCHAR*)msg, len)))
        ABORT(r);

    if ((r=nr_stun_message_create(&res)))
        ABORT(r);

    if ((r=nr_stun_decode_message(req, nr_stun_server_get_password, ctx))) {
        /* draft-ietf-behave-rfc3489bis-07.txt S 7.3 says "If any errors are
         * detected, the message is silently discarded."  */
#ifndef USE_STUN_PEDANTIC
        /* ... but that seems like a bad idea, at least return a 400 so
         * that the server isn't a black hole to the client */
        nr_stun_form_error_response(req, res, 400, "Bad Request");
        ABORT(R_ALREADY);
#endif /* USE_STUN_PEDANTIC */
        ABORT(R_REJECTED);
    }

    if ((r=nr_stun_receive_message(0, req))) {
        /* draft-ietf-behave-rfc3489bis-07.txt S 7.3 says "If any errors are
         * detected, the message is silently discarded."  */
#ifndef USE_STUN_PEDANTIC
        /* ... but that seems like a bad idea, at least return a 400 so
         * that the server isn't a black hole to the client */
        nr_stun_form_error_response(req, res, 400, "Bad Request");
        ABORT(R_ALREADY);
#endif /* USE_STUN_PEDANTIC */
        ABORT(R_REJECTED);
    }

    if (NR_STUN_GET_TYPE_CLASS(req->header.type) != NR_CLASS_REQUEST
     && NR_STUN_GET_TYPE_CLASS(req->header.type) != NR_CLASS_INDICATION) {
         r_log(NR_LOG_STUN,LOG_NOTICE,"STUN-SERVER(%s): Illegal message type: %04x",ctx->label,req->header.type);
        /* draft-ietf-behave-rfc3489bis-07.txt S 7.3 says "If any errors are
         * detected, the message is silently discarded."  */
#ifndef USE_STUN_PEDANTIC
        /* ... but that seems like a bad idea, at least return a 400 so
         * that the server isn't a black hole to the client */
        nr_stun_form_error_response(req, res, 400, "Bad Request");
        ABORT(R_ALREADY);
#endif /* USE_STUN_PEDANTIC */
        ABORT(R_REJECTED);
    }

    /* "The STUN agent then does any checks that are required by a
     * authentication mechanism that the usage has specified" */
    if ((r=nr_stun_server_process_request_auth_checks(ctx, req, auth_rule, res)))
        ABORT(r);

    if (NR_STUN_GET_TYPE_CLASS(req->header.type) == NR_CLASS_INDICATION) {
        if ((r=nr_stun_process_indication(req)))
            ABORT(r);
    }
    else {
        if ((r=nr_stun_process_request(req, res)))
            ABORT(r);
    }

    assert(res->header.type == 0);

    clnt = 0;
    if (NR_STUN_GET_TYPE_CLASS(req->header.type) == NR_CLASS_REQUEST) {
        if ((nr_stun_get_message_client(ctx, req, &clnt))) {
            if ((r=nr_stun_form_success_response(req, peer_addr, 0, res)))
                ABORT(r);
        }
        else {
            if ((r=nr_stun_form_success_response(req, peer_addr, &clnt->password, res)))
                ABORT(r);
        }
    }

    if(clnt && clnt->stun_server_cb){
        r_log(NR_LOG_STUN,LOG_DEBUG,"Entering STUN server callback");

        /* Set up the info */
        if(r=nr_transport_addr_copy(&info.src_addr,peer_addr))
            ABORT(r);

        info.request = req;
        info.response = res;

        error = 0;
        if (clnt->stun_server_cb(clnt->cb_arg,ctx,sock,&info,&error)) {
            if (error == 0)
                error = 500;

            nr_stun_form_error_response(req, res, error, "ICE Failure");
            ABORT(R_ALREADY);
        }
    }

    _status=0;
  abort:
    if (NR_STUN_GET_TYPE_CLASS(req->header.type) == NR_CLASS_INDICATION)
        goto skip_response;

    /* Now respond */

    if (_status != 0 && ! nr_stun_message_has_attribute(res, NR_STUN_ATTR_ERROR_CODE, 0))
         nr_stun_form_error_response(req, res, 500, "Failed to specify error");

    if ((r=nr_stun_server_send_response(ctx, sock, peer_addr, res, clnt))) {
        r_log(NR_LOG_STUN,LOG_WARNING,"STUN-SERVER(label=%s): Failed sending response (my_addr=%s,peer_addr=%s)",ctx->label,ctx->my_addr.as_string,peer_addr->as_string);
        _status = R_FAILED;
    }

#ifdef SANITY_CHECKS
    if (_status == R_ALREADY) {
        assert(NR_STUN_GET_TYPE_CLASS(res->header.type) == NR_CLASS_ERROR_RESPONSE);
        assert(nr_stun_message_has_attribute(res, NR_STUN_ATTR_ERROR_CODE, 0));
    }
    else {
        assert(NR_STUN_GET_TYPE_CLASS(res->header.type) == NR_CLASS_RESPONSE);
        assert(!nr_stun_message_has_attribute(res, NR_STUN_ATTR_ERROR_CODE, 0));
    }
#endif /* SANITY_CHECKS */

    if (0) {
  skip_response:
        _status = 0;
    }

    nr_stun_message_destroy(&res);
    nr_stun_message_destroy(&req);

    return(_status);
  }

static int nr_stun_server_send_response(nr_stun_server_ctx *ctx, nr_socket *sock, nr_transport_addr *peer_addr, nr_stun_message *res, nr_stun_server_client *clnt)
  {
    int r,_status;
    Data *hmacPassword;
    char string[256];

    r_log(NR_LOG_STUN,LOG_DEBUG,"STUN-SERVER(label=%s): Sending(my_addr=%s,peer_addr=%s)",ctx->label,ctx->my_addr.as_string,peer_addr->as_string);

    if (clnt) {
        hmacPassword = &clnt->password;
    }
    else {
        hmacPassword = 0;
    }

    if ((r=nr_stun_encode_message(res))) {
        /* should never happen */
        r_log(NR_LOG_STUN,LOG_ERR,"STUN-SERVER(label=%s): Unable to encode message", ctx->label);
    }
    else {
        snprintf(string, sizeof(string)-1, "STUN(%s): Sending to %s ", ctx->label, peer_addr->as_string);
        r_dump(NR_LOG_STUN, LOG_DEBUG, string, (char*)res->buffer, res->length);

        if(r=nr_socket_sendto(sock?sock:ctx->sock,res->buffer,res->length,0,peer_addr))
          ABORT(r);
    }

    _status=0;
  abort:
    return(_status);
  }

static int nr_stun_server_destroy_client(nr_stun_server_client *clnt)
  {
    RFREE(clnt->label);
    RFREE(clnt->username);
    r_data_zfree(&clnt->password);

    RFREE(clnt);
    return(0);
  }

int nr_stun_get_message_client(nr_stun_server_ctx *ctx, nr_stun_message *req, nr_stun_server_client **out)
  {
    int _status;
    nr_stun_message_attribute *attr;
    nr_stun_server_client *clnt=0;

    if (! nr_stun_message_has_attribute(req, NR_STUN_ATTR_USERNAME, &attr)) {
       r_log(NR_LOG_STUN,LOG_NOTICE,"STUN-SERVER(%s): Missing Username",ctx->label);
       ABORT(R_NOT_FOUND);
    }

    STAILQ_FOREACH(clnt, &ctx->clients, entry) {
        if (!strcmp(clnt->username, attr->u.username))
            break;
    }
    if (!clnt) {
        r_log(NR_LOG_STUN,LOG_NOTICE,"STUN-SERVER(%s): Request from unknown user: %s",ctx->label,attr->u.username);
        ABORT(R_NOT_FOUND);
    }

    *out = clnt;

    _status=0;
  abort:
    return(_status);
  }

