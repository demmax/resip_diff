#ifndef CancelClientNonInviteTransaction_Include_Guard
#define CancelClientNonInviteTransaction_Include_Guard

#include "resip/stack/TransactionMessage.hxx"

#include "rutil/Data.hxx"

namespace resip
{
class CancelClientNonInviteTransaction : public TransactionMessage
{
   public:
      explicit CancelClientNonInviteTransaction(const resip::Data& tid) :
         mTid(tid)
      {}
      virtual ~CancelClientNonInviteTransaction(){}

/////////////////// Must implement unless abstract ///

      virtual const Data& getTransactionId() const {return mTid;}
      virtual bool isClientTransaction() const {return true;}
      virtual EncodeStream& encode(EncodeStream& strm) const
      {
         return strm << "CancelClientNonInviteTransaction: " << mTid;
      }
      virtual EncodeStream& encodeBrief(EncodeStream& strm) const
      {
         return strm << "CancelClientNonInviteTransaction: " << mTid;
      }

/////////////////// May override ///

      virtual Message* clone() const
      {
         return new CancelClientNonInviteTransaction(*this);
      }

   protected:
      const resip::Data mTid;

}; // class CancelClientNonInviteTransaction

} // namespace resip

#endif // include guard
