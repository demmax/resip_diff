#ifndef SilentlyAbandonServerTransaction_Include_Guard
#define SilentlyAbandonServerTransaction_Include_Guard

#include "resip/stack/TransactionMessage.hxx"

#include "rutil/Data.hxx"
#include "rutil/resipfaststreams.hxx"

namespace resip
{
class SilentlyAbandonServerTransaction : public TransactionMessage
{
   public:
      SilentlyAbandonServerTransaction(const Data& tid) :
         mTid(tid)
      {}
      virtual ~SilentlyAbandonServerTransaction() {}

/////////////////// Must implement unless abstract ///

      virtual const Data& getTransactionId() const {return mTid;}
      virtual bool isClientTransaction() const {return false;}
      virtual EncodeStream& encode(EncodeStream& strm) const
      {
         return strm << "SilentlyAbandonServerTransaction: " << mTid;
      }
      virtual EncodeStream& encodeBrief(EncodeStream& strm) const
      {
         return strm << "SilentlyAbandonServerTransaction: " << mTid;
      }

/////////////////// May override ///

      virtual Message* clone() const
      {
         return new SilentlyAbandonServerTransaction(*this);
      }

   protected:
      const resip::Data mTid;

}; // class SilentlyAbandonServerTransaction

} // namespace resip

#endif // include guard
