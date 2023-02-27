#ifndef SetTransactionMessageFilter_Include_Guard
#define SetTransactionMessageFilter_Include_Guard

#include "resip/stack/TransactionMessage.hxx"

#include "rutil/Data.hxx"
#include "rutil/resipfaststreams.hxx"

namespace resip
{

class SipMessage;
class TransactionController;
class TransactionState;

class SetTransactionMessageFilter: public TransactionMessage
{
   public:
      SetTransactionMessageFilter(const Data& tid) :
         mTid(tid)
      {}
      virtual ~SetTransactionMessageFilter() {}

/////////////////// Must implement unless abstract ///

      virtual const Data& getTransactionId() const {return mTid;}
      virtual bool isClientTransaction() const {return false;}
      virtual EncodeStream& encode(EncodeStream& strm) const
      {
         return strm << "SetTransactionMessageFilter: " << mTid;
      }
      virtual EncodeStream& encodeBrief(EncodeStream& strm) const
      {
         return strm << "SetTransactionMessageFilter: " << mTid;
      }

      // must return true to proceed with message
      virtual bool filterMessage(TransactionController& controller, TransactionState& state, SipMessage* msg) = 0;

/////////////////// May override ///


   protected:
      const resip::Data mTid;

}; // class SetTransactionMessageFilter

} // namespace resip

#endif // include guard
