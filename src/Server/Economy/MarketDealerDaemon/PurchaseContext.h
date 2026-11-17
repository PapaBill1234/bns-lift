// PurchaseContext.obj (MarketDealerDaemon PDB). Layout from include/pdb/MarketDealerDaemon/types.h.
#pragma once
#include <stddef.h>
#include <string.h>
#include "Dealings.h"

class PurchaseContext : public DealingContext
{
public:
    // LIFT: inlined in SaleContext::AddPurchaseContext (0x2c3d0).
    explicit PurchaseContext(PurchaseInfo const& purchaseInfo) { memcpy(&_purchaseInfo, &purchaseInfo, sizeof(_purchaseInfo)); }
    virtual ~PurchaseContext() {}           // LIFT: folded into ~DynamicRefCntObj (0x6ef0)
    virtual int const GetDealingType();     // 0x63c60 (ICF fold: returns 1)

    PurchaseInfo _purchaseInfo;
};
static_assert(sizeof(PurchaseContext) == 0xE0, "sizeof PurchaseContext");
static_assert(offsetof(PurchaseContext, _purchaseInfo) == 0x18, "PurchaseContext::_purchaseInfo");
