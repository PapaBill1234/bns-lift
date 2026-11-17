// BidContext.obj (MarketDealerDaemon PDB).
// No code: ~DynamicRefCntObj 0x6ed0 and the scalar deleting destructor 0x6ef0 (common, folded).
#include "BidContext.h"
#include "Log.h"
#include "AlertSender.h"

#define BID_CONTEXT_FILE L"BidContext.cpp"
static wchar_t const* const MODULE_NAME = L"bid context";  // PDB MODULE_NAME

// 0x6ee0 (ICF fold: returns 0)
int const BidContext::GetDealingType()
{
    return DEALINGTYPE_BID;
}

// 0x6f20
bool BidContext::SetNewBidPrice(long long newBidPrice)
{
    if (newBidPrice <= 0 || newBidPrice <= _bidInfo._dealingInfo._dealingPrice)
    {
        Log::Write(Log::LT_ERROR, BID_CONTEXT_FILE, 27,
                   L"== CRASH == [%s], %s; invalid parameter, newBidPrice:%I64d, currentBidPrice:%I64d", MODULE_NAME,
                   L"BidContext::SetNewBidPrice", newBidPrice, _bidInfo._dealingInfo._dealingPrice);
        AlertSender::Write(BID_CONTEXT_FILE, 27,
                           L"== CRASH == [%s], %s; invalid parameter, newBidPrice:%I64d, currentBidPrice:%I64d",
                           MODULE_NAME, L"BidContext::SetNewBidPrice", newBidPrice, _bidInfo._dealingInfo._dealingPrice);
        return false;
    }
    _bidInfo._dealingInfo._dealingPrice = newBidPrice;
    return true;
}
