#if !defined(RESIP_PARAMETERTYPEENUMS_HXX)
#define RESIP_PARAMETERTYPEENUMS_HXX 

#include "rutil/Data.hxx"

#define defineParam(_enum, _name, _type, _rfc) _enum
#define UNUSED_defineParam(_enum, _name, _type, _rfc) SAVE##_enum, _enum = UNKNOWN, RESET##enum = SAVE##_enum-1

namespace resip
{

class Parameter;
class ParseBuffer;

class ParameterTypes
{
  
   public:
      // !dlb! until automated, must ensure that this set is consistent with
      // gperf in ParameterTypes.cxx, ParameterTypes.hxx, Parameters.gperf
      // NOTE: !!Parameters.gperf must have lowercase parameters!!
      // Also needs to be in ParserCategory.hxx/cxx
      // PLEASE compile and run testParserCategories after changing this file.
      enum Type
      {
         UNKNOWN = -1,
         defineParam(data, "data", ExistsParameter, "RFC 3840"),
         defineParam(control, "control", ExistsParameter, "RFC 3840"),
         defineParam(mobility, "mobility", QuotedDataParameter, "RFC 3840"), // mobile|fixed
         defineParam(description, "description", QuotedDataParameter, "RFC 3840"), // <> quoted
         defineParam(events, "events", QuotedDataParameter, "RFC 3840"), // list
         defineParam(priority, "priority", QuotedDataParameter, "RFC 3840"), // non-urgent|normal|urgent|emergency
         defineParam(methods, "methods", QuotedDataParameter, "RFC 3840"), // list
         defineParam(schemes, "schemes", QuotedDataParameter, "RFC 3840"), // list
         defineParam(application, "application", ExistsParameter, "RFC 3840"),
         defineParam(video, "video", ExistsParameter, "RFC 3840"),
         defineParam(language, "language", QuotedDataParameter, "RFC 3840"), // list
         defineParam(type, "type", QuotedDataParameter, "RFC 3840"), // list
         defineParam(isFocus, "isfocus", ExistsParameter, "RFC 3840"),
         defineParam(actor, "actor", QuotedDataParameter, "RFC 3840"), // principal|msg-taker|attendant|information
         defineParam(text, "text", ExistsOrDataParameter, "RFC 3840"), // using ExistsOrDataParameter so this parameter is compatible with both RFC3840 and RFC3326
         defineParam(extensions, "extensions", QuotedDataParameter, "RFC 3840"), //list

         defineParam(Instance, "+sip.instance", QuotedDataParameter, "gruu"),  // <> quoted
         defineParam(regid, "reg-id", UInt32Parameter, "outbound"),  
         defineParam(ob,"ob",ExistsParameter,"outbound-05"),

         defineParam(pubGruu, "pub-gruu", QuotedDataParameter, "gruu"),
         defineParam(tempGruu, "temp-gruu", QuotedDataParameter, "gruu"),
         defineParam(gr, "gr", ExistsOrDataParameter, "gruu"),

         defineParam(accessType, "access-type", DataParameter, "RFC 2046"),
         defineParam(algorithm, "algorithm", DataParameter, "RFC ????"),
         defineParam(boundary, "boundary", DataParameter, "RFC 2046"),
         defineParam(branch, "branch", BranchParameter, "RFC ????"),
         defineParam(charset, "charset", DataParameter, "RFC 2045"),
         defineParam(cnonce, "cnonce", QuotedDataParameter, "RFC ????"),
         defineParam(comp, "comp", DataParameter, "RFC ????"),
         defineParam(dAlg, "d-alg", DataParameter, "RFC 3329"),
         defineParam(dQop, "d-qop", DataParameter, "RFC ????"),
         defineParam(dVer, "d-ver", QuotedDataParameter, "RFC ????"),
         defineParam(directory, "directory", DataParameter, "RFC 2046"),
         defineParam(domain, "domain", QuotedDataParameter, "RFC ????"),
         defineParam(duration, "duration", UInt32Parameter, "RFC ????"),
         defineParam(expiration, "expiration", QuotedDataParameter, "RFC 2046"),
         defineParam(expires, "expires", UInt32Parameter, "RFC ????"),
         defineParam(filename, "filename", DataParameter, "RFC ????"),
         defineParam(fromTag, "from-tag", DataParameter, "RFC ????"),
         defineParam(handling, "handling", DataParameter, "RFC ????"),
         defineParam(id, "id", DataParameter, "RFC ????"),
         defineParam(lr, "lr", ExistsParameter, "RFC ????"),
         defineParam(maddr, "maddr", DataParameter, "RFC ????"),
         defineParam(method, "method", DataParameter, "RFC ????"),
         defineParam(micalg, "micalg", DataParameter, "RFC 1847"),
         defineParam(mode, "mode", DataParameter, "RFC 2046"),
         defineParam(name, "name", DataParameter, "RFC 2046"),
         defineParam(nc, "nc", DataParameter, "RFC ????"),
         defineParam(nonce, "nonce", QuotedDataParameter, "RFC ????"),
         defineParam(opaque, "opaque", QuotedDataParameter, "RFC ????"),
         defineParam(permission, "permission", DataParameter, "RFC 2046"),
         defineParam(protocol, "protocol", QuotedDataParameter, "RFC 1847"),
         defineParam(purpose, "purpose", DataParameter, "RFC ????"),
         defineParam(q, "q", QValueParameter, "RFC 3261"),

         defineParam(realm, "realm", QuotedDataParameter, "RFC ????"),
         defineParam(reason, "reason", DataParameter, "RFC ????"),
         defineParam(received, "received", DataParameter, "RFC ????"),
         defineParam(response, "response", QuotedDataParameter, "RFC ????"),
         defineParam(retryAfter, "retry-after", UInt32Parameter, "RFC ????"),
         defineParam(rinstance, "rinstance", DataParameter, ""),
         defineParam(rport, "rport", RportParameter, "RFC ????"),
         defineParam(server, "server", DataParameter, "RFC 2046"),
         defineParam(site, "site", DataParameter, "RFC 2046"),
         defineParam(size, "size", DataParameter, "RFC 2046"),
         defineParam(smimeType, "smime-type", DataParameter, "RFC 2633"),
         defineParam(stale, "stale", DataParameter, "RFC ????"),
         defineParam(tag, "tag", DataParameter, "RFC ????"),
         defineParam(toTag, "to-tag", DataParameter, "RFC ????"),
         defineParam(transport, "transport", DataParameter, "RFC ????"),
         defineParam(ttl, "ttl", UInt32Parameter, "RFC ????"),
         defineParam(uri, "uri", QuotedDataParameter, "RFC ????"),
         defineParam(user, "user", DataParameter, "RFC ????"),
         defineParam(extension, "ext", DataParameter, "RFC ????"),
         defineParam(username, "username", DataParameter, "RFC ????"),
         defineParam(earlyOnly, "early-only", ExistsParameter, "RFC 3891"),
         defineParam(refresher, "refresher", DataParameter, "RFC 4028"),

         defineParam(profileType, "profile-type", DataParameter, "draft-ietf-sipping-config-framework"),
         defineParam(vendor, "vendor", QuotedDataParameter, "draft-ietf-sipping-config-framework"),
         defineParam(model, "model", QuotedDataParameter, "draft-ietf-sipping-config-framework"),
         defineParam(version, "version", QuotedDataParameter, "draft-ietf-sipping-config-framework"),
         defineParam(effectiveBy, "effective-by", UInt32Parameter, "draft-ietf-sipping-config-framework"),
         defineParam(document, "document", DataParameter, "draft-ietf-sipping-config-framework"),
         defineParam(appId, "app-id", DataParameter, "draft-ietf-sipping-config-framework"),
         defineParam(networkUser, "network-user", DataParameter, "draft-ietf-sipping-config-framework"),

         defineParam(url, "url", QuotedDataParameter, "draft-ietf-sip-content-indirect-mech-05"),


         defineParam(sigcompId, "sigcomp-id", QuotedDataParameter, "draft-ietf-rohc-sigcomp-sip"),
         defineParam(qop, "qop", DataParameter, "RFC 3261"),
         defineParam(qopOptions, "qop", DataParameter, "RFC 3261"),
         defineParam(addTransport, "addTransport", ExistsParameter, ""),
		  //alexkr
		  defineParam(orbit, "orbit", DataParameter, "Polycom parking orbit implementation"),
		  defineParam(joined, "joined", ExistsParameter, "MCU joined notification"),
		  defineParam(left, "left", ExistsParameter, "MCU left notification"),
		  defineParam(cterm, "cterm", DataParameter, "MCU termination policy"),
		  defineParam(ctype, "ctype", DataParameter, "MCU termination type"),
		  defineParam(hadd, "hadd", DataParameter, "MCU host address add"),
		  defineParam(hdel, "hdel", DataParameter, "MCU host address delete"),
		  

         MAX_PARAMETER
      };

      // convert to enum from two pointers into the HFV raw buffer
      static Type getType(const char* start, unsigned int length);

      typedef Parameter* (*Factory)(ParameterTypes::Type, ParseBuffer&, const char*);

      static Factory ParameterFactories[MAX_PARAMETER];
      static Data ParameterNames[MAX_PARAMETER];
};
 
}

#undef defineParam
#undef UNUSED_defineParam

#endif

/* ====================================================================
 * The Vovida Software License, Version 1.0 
 * 
 * Copyright (c) 2000 Vovida Networks, Inc.  All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 
 * 3. The names "VOCAL", "Vovida Open Communication Application Library",
 *    and "Vovida Open Communication Application Library (VOCAL)" must
 *    not be used to endorse or promote products derived from this
 *    software without prior written permission. For written
 *    permission, please contact vocal@vovida.org.
 *
 * 4. Products derived from this software may not be called "VOCAL", nor
 *    may "VOCAL" appear in their name, without prior written
 *    permission of Vovida Networks, Inc.
 * 
 * THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESSED OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, TITLE AND
 * NON-INFRINGEMENT ARE DISCLAIMED.  IN NO EVENT SHALL VOVIDA
 * NETWORKS, INC. OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT DAMAGES
 * IN EXCESS OF $1,000, NOR FOR ANY INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
 * USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
 * DAMAGE.
 * 
 * ====================================================================
 * 
 * This software consists of voluntary contributions made by Vovida
 * Networks, Inc. and many individuals on behalf of Vovida Networks,
 * Inc.  For more information on Vovida Networks, Inc., please see
 * <http://www.vovida.org/>.
 *
 */
