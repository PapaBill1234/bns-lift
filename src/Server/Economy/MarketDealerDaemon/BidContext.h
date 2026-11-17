// BidContext.obj (MarketDealerDaemon PDB). Layout from include/pdb/MarketDealerDaemon/types.h.
#pragma once
#include <stddef.h>
#include <string.h>
#include "Dealings.h"

class BidContext : public DealingContext
{
public:
    // LIFT: inlined in SaleContext::AddBidContext (0x2be00).
    explicit BidContext(BidInfo const& bidInfo) { memcpy(&_bidInfo, &bidInfo, sizeof(_bidInfo)); }
    virtual ~BidContext() {}                // LIFT: folded into ~DynamicRefCntObj (0x6ef0)
    virtual int const GetDealingType();     // 0x6ee0
    bool SetNewBidPrice(long long newBidPrice);  // 0x6f20

    BidInfo _bidInfo;
};
static_assert(sizeof(BidContext) == 0xE0, "sizeof BidContext");
static_assert(offsetof(BidContext, _bidInfo) == 0x18, "BidContext::_bidInfo");
