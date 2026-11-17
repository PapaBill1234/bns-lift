// Dealings.h (MarketDealerDaemon PDB). No code in the PDB. Layouts from include/pdb/MarketDealerDaemon/types.h.
// ❓ The PDB gives no header for these types. DealingInfo, BidInfo, PurchaseInfo and DealingContext are here.
#pragma once
#include <stddef.h>
#include "RefCntObject.h"
#include "Participant.h"

class DealingInfo
{
public:
    long long _dealingId;
    long long _pawnId;
    Participant _trader;
    long long _dealingPrice;
};
static_assert(sizeof(DealingInfo) == 0xC0, "sizeof DealingInfo");
static_assert(offsetof(DealingInfo, _trader) == 0x10, "DealingInfo::_trader");
static_assert(offsetof(DealingInfo, _dealingPrice) == 0xB8, "DealingInfo::_dealingPrice");

class BidInfo
{
public:
    enum BidStatus
    {
        BIDSTATUS_INVALID_STATUS = 0,
        BIDSTATUS_RESERVING = 1,
        BIDSTATUS_BIDDING = 2,
        BIDSTATUS_BID_WINNER = 3,
        BIDSTATUS_BID_LOSER = 4,
        BIDSTATUS_RESERVATION_CANCELLATION = 5,
        BIDSTATUS_BID_ABANDONMENT = 6,
        BIDSTATUS_MAX = 7,
    };
    enum Column
    {
        COLUMN_BID_ID = 0,
        COLUMN_PAWN_ID = 1,
        COLUMN_BIDDER_WID = 2,
        COLUMN_BIDDER_PCID = 3,
        COLUMN_BIDDER_ACCOUNT_ID = 4,
        COLUMN_BIDDER_WORLD_NAME = 5,
        COLUMN_BIDDER_NAME = 6,
        COLUMN_BID_PRICE = 7,
        COLUMN_BID_STATUS = 8,
        MAX_COLUMN_COUNT = 9,
    };

    DealingInfo _dealingInfo;
    char _bidStatus;
};
static_assert(sizeof(BidInfo) == 0xC8, "sizeof BidInfo");
static_assert(offsetof(BidInfo, _bidStatus) == 0xC0, "BidInfo::_bidStatus");

class PurchaseInfo
{
public:
    enum Column
    {
        COLUMN_PURCHASE_ID = 0,
        COLUMN_PAWN_ID = 1,
        COLUMN_PURCHASER_WID = 2,
        COLUMN_PURCHASER_PCID = 3,
        COLUMN_PURCHASER_ACCOUNT_ID = 4,
        COLUMN_PURCHASER_WORLD_NAME = 5,
        COLUMN_PURCHASER_NAME = 6,
        COLUMN_PURCHASE_PRICE = 7,
        COLUMN_PURCHASE_STATUS = 8,
        MAX_COLUMN_COUNT = 9,
    };
    enum PurchaseStatus
    {
        PURCHASESTATUS_INVALID_STATUS = 0,
        PURCHASESTATUS_RESERVING = 1,
        PURCHASESTATUS_BUYOUT = 2,
        PURCHASESTATUS_RESERVATION_CANCELLATION = 3,
        PURCHASESTATUS_MAX = 4,
    };

    DealingInfo _dealingInfo;
    char _purchaseStatus;
};
static_assert(sizeof(PurchaseInfo) == 0xC8, "sizeof PurchaseInfo");
static_assert(offsetof(PurchaseInfo, _purchaseStatus) == 0xC0, "PurchaseInfo::_purchaseStatus");

class DealingContext : public DynamicRefCntObj
{
public:
    enum DealingType
    {
        DEALINGTYPE_BID = 0,
        DEALINGTYPE_PURCHASE = 1,
    };

    virtual int const GetDealingType() = 0;  // slot 4
    virtual ~DealingContext() {}             // LIFT: folded into ~DynamicRefCntObj (0x6ef0)
};
static_assert(sizeof(DealingContext) == 0x18, "sizeof DealingContext");
