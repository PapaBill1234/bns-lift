// SaleContext.obj (MarketDealerDaemon PDB). Layouts from include/pdb/MarketDealerDaemon/types.h.
#pragma once
#include <stddef.h>
#include <map>
#include "RefCntObject.h"
#include "Lock.h"
#include "StlMemory.h"
#include "Participant.h"
#include "Dealings.h"
#include "MarketDealerDefine.h"

class BidContext;
class PurchaseContext;

class SaleInfo
{
public:
    enum Column
    {
        COLUMN_SALE_ID = 0,
        COLUMN_PAWN_ID = 1,
        COLUMN_SALE_TYPE = 2,
        COLUMN_SELLER_WID = 3,
        COLUMN_SELLER_PCID = 4,
        COLUMN_SELLER_ACCOUNT_ID = 5,
        COLUMN_SELLER_WORLD_NAME = 6,
        COLUMN_SELLER_NAME = 7,
        COLUMN_SALE_PRICE = 8,
        COLUMN_UNIT_PRICE = 9,
        COLUMN_BID_UNIT_PRICE = 10,
        COLUMN_TOP_BID_ID = 11,
        COLUMN_TOP_BIDDER_PAWN_ID = 12,
        COLUMN_TOP_BIDDER_WID = 13,
        COLUMN_TOP_BIDDER_PCID = 14,
        COLUMN_TOP_BIDDER_NAME = 15,
        COLUMN_TOP_BID_PRICE = 16,
        COLUMN_SALE_STATUS = 17,
        COLUMN_SALE_EXPIRATION_TIME = 18,
        MAX_COLUMN_COUNT = 19,
    };
    enum SaleStatus
    {
        SALESTATUS_INVALID_STATUS = 0,
        SALESTATUS_RESERVING = 1,
        SALESTATUS_SELLING = 2,
        SALESTATUS_SALE_TIMEOUT = 3,
        SALESTATUS_SOLDOUT = 4,
        SALESTATUS_RESERVATION_CANCELLATION = 5,
        SALESTATUS_SALE_ABANDONMENT = 6,
        SALESTATUS_SUSPENSION_OF_SALE = 7,
        SALESTATUS_MAX = 8,
    };

    SaleInfo();  // 0x2adb0

    long long _saleId;
    long long _pawnId;
    char _saleType;
    Participant _seller;
    long long _salePrice;
    long long _unitPrice;
    long long _bidUnitPrice;
    long long _topBidId;
    long long _topBidderPawnId;
    Participant _topBidder;
    long long _topBidPrice;
    char _saleStatus;
    long long _saleExpirationTime;
};
static_assert(sizeof(SaleInfo) == 0x1A8, "sizeof SaleInfo");
static_assert(offsetof(SaleInfo, _seller) == 0x18, "SaleInfo::_seller");
static_assert(offsetof(SaleInfo, _topBidder) == 0xE8, "SaleInfo::_topBidder");
static_assert(offsetof(SaleInfo, _saleExpirationTime) == 0x1A0, "SaleInfo::_saleExpirationTime");

class SaleItemInfo
{
public:
    enum Column
    {
        COLUMN_ITEM_COMMON_CATEGORY = 0,
        COLUMN_ITEM_FIRST_CATEGORY = 1,
        COLUMN_ITEM_SECOND_CATEGORY = 2,
        COLUMN_ITEM_THIRD_CATEGORY = 3,
        COLUMN_ITEM_TYPE = 4,
        COLUMN_ITEM_INSTANCE_ID = 5,
        COLUMN_ITEM_DATA_ID = 6,
        COLUMN_ITEM_LEVEL = 7,
        COLUMN_ITEM_EXP = 8,
        COLUMN_ITEM_AMOUNT = 9,
        COLUMN_ITEM_GRADE = 10,
        COLUMN_ITEM_EQUIP_LEVEL = 11,
        COLUMN_ITEM_XML_DATA = 12,
        MAX_COLUMN_COUNT = 13,
    };
    enum Param
    {
        PARAM_ITEM_COMMON_CATEGORY = 0,
        PARAM_ITEM_FIRST_CATEGORY = 1,
        PARAM_ITEM_SECOND_CATEGORY = 2,
        PARAM_ITEM_THIRD_CATEGORY = 3,
        PARAM_ITEM_TYPE = 4,
        PARAM_ITEM_INSTANCE_ID = 5,
        PARAM_ITEM_DATA_ID = 6,
        PARAM_ITEM_LEVEL = 7,
        PARAM_ITEM_EXP = 8,
        PARAM_ITEM_AMOUNT = 9,
        PARAM_ITEM_GRADE = 10,
        PARAM_ITEM_EQUIP_LEVEL = 11,
        PARAM_ITEM_XML_DATA = 12,
        MAX_PARAM_COUNT = 13,
    };

    MarketDealerFailReason CheckItemDataValidity() const;  // 0x2af30

    char _itemCommonCategory;
    char _itemFirstCategory;
    char _itemSecondCategory;
    char _itemThirdCategory;
    char _itemType;
    long long _itemInstanceId;
    int _itemDataId;
    short _itemLevel;
    int _itemExp;
    int _itemAmount;
    char _itemGrade;
    char _itemEquipLevel;
    wchar_t _itemXmlData[1025];
};
static_assert(sizeof(SaleItemInfo) == 0x828, "sizeof SaleItemInfo");
static_assert(offsetof(SaleItemInfo, _itemInstanceId) == 0x8, "SaleItemInfo::_itemInstanceId");
static_assert(offsetof(SaleItemInfo, _itemExp) == 0x18, "SaleItemInfo::_itemExp");
static_assert(offsetof(SaleItemInfo, _itemXmlData) == 0x22, "SaleItemInfo::_itemXmlData");

class SaleContext : public DynamicRefCntObj
{
public:
    // LIFT: no typedef name in the PDB. Member type: std::map<__int64,DealingContext *,...,StlAllocator<...,2>>.
    typedef std::map<long long, DealingContext*, std::less<long long>,
                     StlAllocator<std::pair<long long const, DealingContext*>, 2> > DealingList;

    explicit SaleContext(SaleInfo const& saleInfo);                             // 0x2b080
    SaleContext(SaleInfo const& saleInfo, SaleItemInfo const& saleItemInfo);    // 0x2b260
    virtual ~SaleContext();                                                     // 0x2b3b0

    static bool DetermineUnitPrice(long long salePrice, int itemAmount, long long& unitPrice);  // 0x2b880
    static bool DetermineBidUnitPrice(long long salePrice, long long& bidUnitPrice);           // 0x2b950
    bool SetTopBidInfo(BidInfo const& newTopBidInfo);                            // 0x2ba20
    BidContext* GetBidContext(long long bidderPcId);                             // 0x2bb50. Adds a reference.
    bool IsBidding(long long bidderPcId) const;                                  // 0x2bcf0
    bool AddBidContext(BidInfo const& bidInfo);                                  // 0x2be00
    bool RemoveBidContext(long long bidderPcId);                                 // 0x2bf30
    PurchaseContext* GetPurchaseContext(long long purchaserPcId);                // 0x2c120. Adds a reference.
    bool IsPurchasing(long long purchaserPcId) const;                            // 0x2c2c0
    bool AddPurchaseContext(PurchaseInfo const& purchaseInfo);                   // 0x2c3d0
    bool RemovePurchaseContext(long long purchaserPcId);                         // 0x2c500

    CriticalSection _lock;
    SaleInfo _saleInfo;
    SaleItemInfo _saleItemInfo;
    DealingList _bidList;
    int _bidCount;
    DealingList _purchaseList;
};
static_assert(sizeof(SaleContext) == 0xA58, "sizeof SaleContext");
static_assert(offsetof(SaleContext, _lock) == 0x18, "SaleContext::_lock");
static_assert(offsetof(SaleContext, _saleInfo) == 0x40, "SaleContext::_saleInfo");
static_assert(offsetof(SaleContext, _saleItemInfo) == 0x1E8, "SaleContext::_saleItemInfo");
static_assert(offsetof(SaleContext, _bidList) == 0xA10, "SaleContext::_bidList");
static_assert(offsetof(SaleContext, _bidCount) == 0xA30, "SaleContext::_bidCount");
static_assert(offsetof(SaleContext, _purchaseList) == 0xA38, "SaleContext::_purchaseList");

class SaleContextManager
{
public:
    // LIFT: no typedef name in the PDB. Member type: std::map<__int64,SaleContext *,...,StlAllocator<...,2>>.
    typedef std::map<long long, SaleContext*, std::less<long long>,
                     StlAllocator<std::pair<long long const, SaleContext*>, 2> > Container;

    bool InitContextManager();                          // 0x2c6f0
    SaleContext* GetContext(long long saleId) const;    // 0x2c880. Adds a reference.
    bool AddContext(SaleContext* const saleContext);    // 0x2caf0
    bool RemoveContext(long long saleId);               // 0x2cd50

    int const _bucketCount;
    CriticalSection* _lockList;
    Container* _containerList;
    long volatile _contextCount;  // The PDB type is int. The code uses Interlocked calls on it.

    // LIFT: inlined in the MarketDealerDaemon code (later card).
    explicit SaleContextManager(int bucketCount)
        : _bucketCount(bucketCount), _lockList(nullptr), _containerList(nullptr), _contextCount(0)
    {
    }
};
static_assert(sizeof(SaleContextManager) == 0x20, "sizeof SaleContextManager");
static_assert(offsetof(SaleContextManager, _containerList) == 0x10, "SaleContextManager::_containerList");
static_assert(offsetof(SaleContextManager, _contextCount) == 0x18, "SaleContextManager::_contextCount");
