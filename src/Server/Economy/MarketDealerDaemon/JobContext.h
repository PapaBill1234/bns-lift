// JobContext.obj (MarketDealerDaemon PDB).
// Card lift-marketdealerdaemon-5 adds the classes that MarketDB part 2 uses (layout from the PDB).
// The bodies (JobContext.cpp) come in a later card. Only the members that MarketDB calls are declared.
#pragma once

#include <stddef.h>
#include <string.h>
#include "Participant.h"
#include "MarketStatement.h"
#include "Dealings.h"
#include "SaleContext.h"

class Packet;
class Session;
class FragmentPacket;
class RepeatPacketComposer;
class PacketConcatenateBuffer;

class JobContext
{
public:
    virtual ~JobContext();
    virtual bool verifyParameter(short& result) const = 0;
    virtual bool handleJob(short& result) = 0;
};

class MySaleInfo
{
public:
    enum Column : int
    {
        COLUMN_SALE_ID = 0x0,
        COLUMN_SALE_TYPE = 0x1,
        COLUMN_SALE_PRICE = 0x2,
        COLUMN_UNIT_PRICE = 0x3,
        COLUMN_TOP_BID_PRICE = 0x4,
        COLUMN_SALE_EXPIRATION_TIME = 0x5,
        MAX_COLUMN_COUNT = 0x6,
    };
    // LIFT: inlined in the array new of RetrieveSaleListJob (0x8890). It sets all SaleItemInfo fields to zero.
    MySaleInfo() { ZeroSaleItemInfo(_saleItemInfo); }
    static void ZeroSaleItemInfo(SaleItemInfo& info)  // LIFT: no PDB name (inlined zero of SaleItemInfo, 0x8890)
    {
        info._itemCommonCategory = 0;
        info._itemFirstCategory = 0;
        info._itemSecondCategory = 0;
        info._itemThirdCategory = 0;
        info._itemType = 0;
        info._itemInstanceId = 0;
        info._itemDataId = 0;
        info._itemLevel = 0;
        info._itemExp = 0;
        info._itemAmount = 0;
        info._itemGrade = 0;
        info._itemEquipLevel = 0;
        memset(info._itemXmlData, 0, sizeof(info._itemXmlData));
    }

    SaleInfo _saleInfo;
    SaleItemInfo _saleItemInfo;
};

class MyBidInfo
{
public:
    enum Column : int
    {
        COLUMN_BID_ID = 0x0,
        COLUMN_SALE_ID = 0x1,
        COLUMN_BID_PRICE = 0x2,
        COLUMN_SELLER_WID = 0x3,
        COLUMN_SELLER_NAME = 0x4,
        COLUMN_BID_UNIT_PRICE = 0x5,
        COLUMN_TOP_BID_PRICE = 0x6,
        COLUMN_SALE_EXPIRATION_TIME = 0x7,
        MAX_COLUMN_COUNT = 0x8,
    };
    // LIFT: inlined in the array new of RetrieveBidListJob (0x9d10).
    MyBidInfo() : _bidId(0), _bidPrice(0) { MySaleInfo::ZeroSaleItemInfo(_saleItemInfo); }

    long long _bidId;
    long long _bidPrice;
    SaleInfo _saleInfo;
    SaleItemInfo _saleItemInfo;
};

class MyReservationInfo
{
public:
    enum Column : int
    {
        COLUMN_SERVICE_TYPE = 0x0,
        COLUMN_SALE_ID = 0x1,
        COLUMN_SERVICE_ID = 0x2,
        MAX_COLUMN_COUNT = 0x3,
    };
    char _serviceType;
    long long _saleId;
    long long _serviceId;
};

class RetrieveSaleListJob : public JobContext
{
public:
    enum Param : int
    {
        PARAM_RETURN_VALUE = 0x0,
        PARAM_SELLER_PCID = 0x1,
        PARAM_SEARCH_COUNT = 0x2,
        PARAM_SEARCH_TYPE = 0x3,
        PARAM_ORDER_TYPE = 0x4,
        PARAM_SEARCH_KEY = 0x5,
        MAX_PARAM_COUNT = 0x6,
    };
    explicit RetrieveSaleListJob(int searchCount);                      // 0x8890
    virtual ~RetrieveSaleListJob();                                     // 0x8a10
    virtual bool verifyParameter(short& failReason) const;              // 0x91e0
    virtual bool handleJob(short& failReason);                          // 0x92e0
    bool Initialize(Packet const*& packet);                             // 0x8a80
    bool ReplySuccess(Session const*& session) const;                   // 0x8c60
    void ReplyFailure(Session const*& session, short const& failReason) const;  // 0x9060
    bool addMySaleInfo(MySaleInfo const& mySaleInfo);  // 0x93c0 ❓ const& or const*
    bool composeResponsePacket(FragmentPacket& packet) const;           // 0x9540 ❓ & or *
    bool composeResponsePacketReversely(FragmentPacket& packet) const;  // 0x9930 ❓ & or *

    unsigned long long _tid;
    short _wid;
    long long _sellerPcId;
    char _searchType;
    char _orderType;
    long long _searchKey;
    char _pageNo;
    int _searchCount;
    MySaleInfo* _mySaleList;
    int _maxListCount;
    int _currListCount;
};

class RetrieveBidListJob : public JobContext
{
public:
    enum Param : int
    {
        PARAM_RETURN_VALUE = 0x0,
        PARAM_BIDDER_PCID = 0x1,
        MAX_PARAM_COUNT = 0x2,
    };
    explicit RetrieveBidListJob(int concurrentBidCount);                // 0x9d10
    virtual ~RetrieveBidListJob();                                      // 0x9e90
    virtual bool verifyParameter(short& failReason) const;              // 0xa470
    virtual bool handleJob(short& failReason);                          // 0xa4f0
    bool Initialize(Packet const*& packet);                             // 0x9f00
    bool ReplySuccess(Session const*& session) const;                   // 0xa060
    void ReplyFailure(Session const*& session, short const& failReason) const;  // 0xa340
    bool addMyBidInfo(MyBidInfo const& myBidInfo);  // 0xa5a0 ❓ const& or const*
    bool composeResponsePacket(FragmentPacket& packet) const;           // 0xa6e0 ❓ & or *

    unsigned long long _tid;
    short _wid;
    long long _bidderPcId;
    MyBidInfo* _myBidList;
    int _maxListCount;
    int _currListCount;
};

class MyBidRankStatusInfo
{
public:
    // LIFT: inlined in the array new of RetrieveBidRankStatusJob::Initialize (0xab50).
    MyBidRankStatusInfo() : _saleId(0), _bidRankStatus(0) {}

    long long _saleId;
    char _bidRankStatus;
};
static_assert(sizeof(MyBidRankStatusInfo) == 0x10, "sizeof MyBidRankStatusInfo");
static_assert(offsetof(MyBidRankStatusInfo, _bidRankStatus) == 0x8, "MyBidRankStatusInfo::_bidRankStatus");

class RetrieveBidRankStatusJob : public JobContext
{
public:
    enum Param : int
    {
        PARAM_BIDDER_PCID = 0x0,
        MAX_PARAM_COUNT = 0x1,
    };
    // LIFT: The constructor is inlined at the call site (AgentPacketHandler.obj, later card). ❓ Field values.
    RetrieveBidRankStatusJob() : _tid(0), _wid(0), _bidderPcId(0), _myBidRankStatusList(nullptr), _currListCount(0) {}
    virtual ~RetrieveBidRankStatusJob();                                // 0xaae0
    virtual bool verifyParameter(short& failReason) const;              // 0xb3f0
    virtual bool handleJob(short& failReason);                          // 0xb4f0
    bool Initialize(Packet const*& packet);                             // 0xab50
    bool ReplySuccess(Session const*& session) const;                   // 0xaf90
    void ReplyFailure(Session const*& session, short const& failReason) const;  // 0xb2c0
    bool composeResponsePacket(RepeatPacketComposer& rpc, Packet& packet) const;  // 0xb590 ❓ & or *

    unsigned long long _tid;
    short _wid;
    long long _bidderPcId;
    MyBidRankStatusInfo* _myBidRankStatusList;
    int _currListCount;
};
static_assert(sizeof(RetrieveBidRankStatusJob) == 0x30, "sizeof RetrieveBidRankStatusJob");
static_assert(offsetof(RetrieveBidRankStatusJob, _myBidRankStatusList) == 0x20,
              "RetrieveBidRankStatusJob::_myBidRankStatusList");
static_assert(offsetof(RetrieveBidRankStatusJob, _currListCount) == 0x28, "RetrieveBidRankStatusJob::_currListCount");

class RetrieveReservationListJob : public JobContext
{
public:
    class MyReservationContext;
    enum Param : int
    {
        PARAM_RETURN_VALUE = 0x0,
        PARAM_PCID = 0x1,
        MAX_PARAM_COUNT = 0x2,
    };
    class MyReservationContext
    {
    public:
        MyReservationInfo _myReservationInfo;
        RetrieveReservationListJob::MyReservationContext* _prev;
        RetrieveReservationListJob::MyReservationContext* _next;
    };
    virtual ~RetrieveReservationListJob();
    virtual bool verifyParameter(short& result) const;
    virtual bool handleJob(short& result);
    bool addMyReservationInfo(MyReservationInfo const& myReservationInfo);  // 0x17b00 ❓ const& or const*

    unsigned long long _tid;
    short _wid;
    long long _pcId;
    RetrieveReservationListJob::MyReservationContext* const _header;
    int _contextCount;
};

class ReserveSaleJob : public JobContext
{
public:
    enum Param : int
    {
        PARAM_RETURN_VALUE = 0x0,
        PARAM_CONCURRENT_SALE_COUNT = 0x1,
        PARAM_ACCUMULATED_SALE_COUNT = 0x2,
        PARAM_RULE_RESET_TIME = 0x3,
        PARAM_SALE_TYPE = 0x4,
        PARAM_SELLER_WID = 0x5,
        PARAM_SELLER_PCID = 0x6,
        PARAM_SELLER_ACCOUNT_ID = 0x7,
        PARAM_SELLER_WORLD_NAME = 0x8,
        PARAM_SELLER_NAME = 0x9,
        PARAM_SALE_PRICE = 0xA,
        PARAM_UNIT_PRICE = 0xB,
        PARAM_BID_UNIT_PRICE = 0xC,
        PARAM_SALE_ID = 0xD,
        MAX_PARAM_COUNT = 0xE,
    };
    virtual ~ReserveSaleJob();
    virtual bool verifyParameter(short& failReason) const;              // 0xbc10
    virtual bool handleJob(short& failReason);                          // 0xbe20
    bool Initialize(Packet const*& packet);                             // 0xb6d0
    void ReplySuccess(Session const*& session) const;                   // 0xb9c0
    void ReplyFailure(Session const*& session, short const& failReason) const;  // 0xbae0

    unsigned long long _tid;
    SaleInfo _saleInfo;
    int _concurrentSaleCount;
    int _accumulatedSaleCount;
    int _ruleResetTime;
};

class CancelSaleReservationJob : public JobContext
{
public:
    enum Param : int
    {
        PARAM_RETURN_VALUE = 0x0,
        PARAM_SALE_ID = 0x1,
        PARAM_SELLER_PCID = 0x2,
        MAX_PARAM_COUNT = 0x3,
    };
    virtual ~CancelSaleReservationJob();
    virtual bool verifyParameter(short& failReason) const;              // 0xc3d0
    virtual bool handleJob(short& failReason);                          // 0xc450
    bool Initialize(Packet const*& packet);                             // 0xc160
    void ReplySuccess(Session const*& session) const;                   // 0xc2c0

    unsigned long long _tid;
    long long _saleId;
    long long _sellerPcId;
};

class RegisterSaleJob : public JobContext
{
public:
    enum Param : int
    {
        PARAM_RETURN_VALUE = 0x0,
        PARAM_SALE_ID = 0x1,
        PARAM_SELLER_PCID = 0x2,
        PARAM_PAWN_ID = 0x3,
        PARAM_UNIT_PRICE = 0x4,
        PARAM_SALE_DURATION = 0x5,
        PARAM_SALE_EXPIRATION_TIME = 0x6,
        MAX_PARAM_COUNT = 0x7,
    };
    virtual ~RegisterSaleJob();
    virtual bool verifyParameter(short& failReason) const;              // 0xcd60
    virtual bool handleJob(short& failReason);                          // 0xd170
    bool Initialize(PacketConcatenateBuffer*& fpc);                     // 0xc8a0
    void ReplySuccess(Session const*& session) const;                   // 0xcc50

    unsigned long long _tid;
    long long _saleId;
    long long _sellerPcId;
    long long _pawnId;
    int _saleDuration;
    SaleItemInfo _saleItemInfo;
    long long _unitPrice;
    long long _saleExpirationTime;
};

class UpdateSalePriceJob : public JobContext
{
public:
    enum Param : int
    {
        PARAM_RETURN_VALUE = 0x0,
        PARAM_SALE_ID = 0x1,
        PARAM_SALE_TYPE = 0x2,
        PARAM_SELLER_PCID = 0x3,
        PARAM_NEW_SALE_PRICE = 0x4,
        PARAM_NEW_UNIT_PRICE = 0x5,
        PARAM_NEW_BID_UNIT_PRICE = 0x6,
        MAX_PARAM_COUNT = 0x7,
    };
    virtual ~UpdateSalePriceJob();
    virtual bool verifyParameter(short& failReason) const;              // 0xdaa0
    virtual bool handleJob(short& failReason);                          // 0xdb30
    bool Initialize(Packet const*& packet);                             // 0xd700
    void ReplySuccess(Session const*& session) const;                   // 0xd870
    void ReplyFailure(Session const*& session, short const& failReason) const;  // 0xd980

    unsigned long long _tid;
    long long _saleId;
    long long _sellerPcId;
    long long _newSalePrice;
    long long _newUnitPrice;
    long long _newBidUnitPrice;
    char _saleType;
};

class AbandonSaleJob : public JobContext
{
public:
    enum Param : int
    {
        PARAM_RETURN_VALUE = 0x0,
        PARAM_SALE_ID = 0x1,
        PARAM_SALE_TYPE = 0x2,
        PARAM_SELLER_PCID = 0x3,
        PARAM_DELIVERY_ID = 0x4,
        PARAM_STATEMENT_TITLE = 0x5,
        PARAM_STATEMENT_BODY = 0x6,
        MAX_PARAM_COUNT = 0x7,
    };
    virtual ~AbandonSaleJob();
    virtual bool verifyParameter(short& failReason) const;              // 0xe440
    virtual bool handleJob(short& failReason);                          // 0xe4c0
    bool Initialize(Packet const*& packet);                             // 0xe1d0
    void ReplySuccess(Session const*& session) const;                   // 0xe330

    unsigned long long _tid;
    long long _saleId;
    long long _sellerPcId;
    char _saleType;
    long long _deliveryId;
    MarketStatement _marketStatement;
};

class ReserveBidJob : public JobContext
{
public:
    enum Param : int
    {
        PARAM_RETURN_VALUE = 0x0,
        PARAM_CONCURRENT_BID_COUNT = 0x1,
        PARAM_SALE_ID = 0x2,
        PARAM_BIDDER_WID = 0x3,
        PARAM_BIDDER_PCID = 0x4,
        PARAM_BIDDER_ACCOUNT_ID = 0x5,
        PARAM_BIDDER_WORLD_NAME = 0x6,
        PARAM_BIDDER_NAME = 0x7,
        PARAM_BID_PRICE = 0x8,
        PARAM_BID_ID = 0x9,
        MAX_PARAM_COUNT = 0xA,
    };
    virtual ~ReserveBidJob();
    virtual bool verifyParameter(short& failReason) const;              // 0xf1b0
    virtual bool handleJob(short& failReason);                          // 0xf3b0
    bool Initialize(Packet const*& packet);                             // 0xecb0
    void ReplySuccess(Session const*& session) const;                   // 0xef60
    void ReplyFailure(Session const*& session, short const& failReason) const;  // 0xf080

    unsigned long long _tid;
    long long _saleId;
    BidInfo _bidInfo;
    int _concurrentBidCount;
};

class CancelBidReservationJob : public JobContext
{
public:
    enum Param : int
    {
        PARAM_RETURN_VALUE = 0x0,
        PARAM_BID_ID = 0x1,
        PARAM_BIDDER_PCID = 0x2,
        MAX_PARAM_COUNT = 0x3,
    };
    virtual ~CancelBidReservationJob();
    virtual bool verifyParameter(short& failReason) const;              // 0xfe80
    virtual bool handleJob(short& failReason);                          // 0xff10
    bool Initialize(Packet const*& packet);                             // 0xfae0
    void ReplySuccess(Session const*& session) const;                   // 0xfc50
    void ReplyFailure(Session const*& session, short const& failReason) const;  // 0xfd60

    unsigned long long _tid;
    long long _saleId;
    long long _bidId;
    long long _bidderPcId;
};

class RegisterBidJob : public JobContext
{
public:
    enum Param : int
    {
        PARAM_RETURN_VALUE = 0x0,
        PARAM_SALE_ID = 0x1,
        PARAM_BID_ID = 0x2,
        PARAM_BIDDER_PCID = 0x3,
        PARAM_PAWN_ID = 0x4,
        PARAM_BID_PRICE = 0x5,
        PARAM_NEW_UNIT_PRICE = 0x6,
        MAX_PARAM_COUNT = 0x7,
    };
    virtual ~RegisterBidJob();
    virtual bool verifyParameter(short& failReason) const;              // 0x10930
    virtual bool handleJob(short& failReason);                          // 0x109d0
    bool Initialize(Packet const*& packet);                             // 0x10540
    void ReplySuccess(Session const*& session) const;                   // 0x106e0
    void ReplyFailure(Session const*& session, short const& failReason) const;  // 0x10800

    unsigned long long _tid;
    long long _saleId;
    long long _bidId;
    long long _bidderPcId;
    long long _pawnId;
    long long _bidPrice;
    long long _newUnitPrice;
};

class UpdateBidPriceJob : public JobContext
{
public:
    enum Param : int
    {
        PARAM_RETURN_VALUE = 0x0,
        PARAM_SALE_ID = 0x1,
        PARAM_BID_ID = 0x2,
        PARAM_BIDDER_PCID = 0x3,
        PARAM_NEW_BID_PRICE = 0x4,
        PARAM_NEW_UNIT_PRICE = 0x5,
        MAX_PARAM_COUNT = 0x6,
    };
    virtual ~UpdateBidPriceJob();
    virtual bool verifyParameter(short& failReason) const;              // 0x11770
    virtual bool handleJob(short& failReason);                          // 0x11820
    bool Initialize(Packet const*& packet);                             // 0x11360
    void ReplySuccess(Session const*& session) const;                   // 0x11510
    void ReplyFailure(Session const*& session, short const& failReason) const;  // 0x11630

    unsigned long long _tid;
    long long _saleId;
    long long _bidId;
    long long _bidderPcId;
    long long _maxDealingPrice;
    long long _extraBidPrice;
    long long _newBidPrice;
    long long _newUnitPrice;
};

class AbandonBidJob : public JobContext
{
public:
    enum Param : int
    {
        PARAM_RETURN_VALUE = 0x0,
        PARAM_SALE_ID = 0x1,
        PARAM_BID_ID = 0x2,
        PARAM_BIDDER_PCID = 0x3,
        PARAM_DELIVERY_ID = 0x4,
        PARAM_MARKETSTATEMENT_TITLE = 0x5,
        PARAM_MARKETSTATEMENT_BODY = 0x6,
        MAX_PARAM_COUNT = 0x7,
    };
    virtual ~AbandonBidJob();
    virtual bool verifyParameter(short& failReason) const;              // 0x12780
    virtual bool handleJob(short& failReason);                          // 0x12810
    bool Initialize(Packet const*& packet);                             // 0x123e0
    void ReplySuccess(Session const*& session) const;                   // 0x12550
    void ReplyFailure(Session const*& session, short const& failReason) const;  // 0x12660

    unsigned long long _tid;
    long long _saleId;
    long long _bidId;
    long long _bidderPcId;
    long long _deliveryId;
    MarketStatement _marketStatement;
};

class ReservePurchaseJob : public JobContext
{
public:
    enum Param : int
    {
        PARAM_RETURN_VALUE = 0x0,
        PARAM_SALE_ID = 0x1,
        PARAM_PURCHASER_WID = 0x2,
        PARAM_PURCHASER_PCID = 0x3,
        PARAM_PURCHASER_ACCOUNT_ID = 0x4,
        PARAM_PURCHASER_WORLD_NAME = 0x5,
        PARAM_PURCHASER_NAME = 0x6,
        PARAM_PURCHASE_PRICE = 0x7,
        PARAM_PURCHASE_ID = 0x8,
        MAX_PARAM_COUNT = 0x9,
    };
    virtual ~ReservePurchaseJob();
    virtual bool verifyParameter(short& failReason) const;              // 0x136f0
    virtual bool handleJob(short& failReason);                          // 0x138f0
    bool Initialize(Packet const*& packet);                             // 0x131f0
    void ReplySuccess(Session const*& session) const;                   // 0x134a0
    void ReplyFailure(Session const*& session, short const& failReason) const;  // 0x135c0

    unsigned long long _tid;
    long long _saleId;
    PurchaseInfo _purchaseInfo;
};

class CancelPurchaseReservationJob : public JobContext
{
public:
    enum Param : int
    {
        PARAM_RETURN_VALUE = 0x0,
        PARAM_PURCHASE_ID = 0x1,
        PARAM_PURCHASER_PCID = 0x2,
        MAX_PARAM_COUNT = 0x3,
    };
    virtual ~CancelPurchaseReservationJob();
    virtual bool verifyParameter(short& failReason) const;              // 0x14310
    virtual bool handleJob(short& failReason);                          // 0x143a0
    bool Initialize(Packet const*& packet);                             // 0x13f70
    void ReplySuccess(Session const*& session) const;                   // 0x140e0
    void ReplyFailure(Session const*& session, short const& failReason) const;  // 0x141f0

    unsigned long long _tid;
    long long _saleId;
    long long _purchaseId;
    long long _purchaserPcId;
};

class RegisterPurchaseJob : public JobContext
{
public:
    enum Param : int
    {
        PARAM_RETURN_VALUE = 0x0,
        PARAM_SALE_ID = 0x1,
        PARAM_PURCHASE_ID = 0x2,
        PARAM_PURCHASER_PCID = 0x3,
        PARAM_PAWN_ID = 0x4,
        PARAM_PURCHASE_PRICE = 0x5,
        PARAM_RULE_RESET_TIME = 0x6,
        PARAM_MONEY_DELIVERY_ID = 0x7,
        PARAM_MONEY_MARKETSTATEMENT_TITLE = 0x8,
        PARAM_MONEY_MARKETSTATEMENT_BODY = 0x9,
        PARAM_RESULT_MONEY_AMOUNT = 0xA,
        PARAM_ITEM_DELIVERY_ID = 0xB,
        PARAM_ITEM_MARKETSTATEMENT_TITLE = 0xC,
        PARAM_ITEM_MARKETSTATEMENT_BODY = 0xD,
        MAX_PARAM_COUNT = 0xE,
    };
    virtual ~RegisterPurchaseJob();
    virtual bool verifyParameter(short& failReason) const;              // 0x14dc0
    virtual bool handleJob(short& failReason);                          // 0x14e60
    bool Initialize(Packet const*& packet);                             // 0x149d0
    void ReplySuccess(Session const*& session) const;                   // 0x14b70
    void ReplyFailure(Session const*& session, short const& failReason) const;  // 0x14c90

    unsigned long long _tid;
    long long _saleId;
    long long _purchaseId;
    long long _purchaserPcId;
    long long _pawnId;
    long long _purchasePrice;
    int _ruleResetTime;
    long long _moneyDeliveryId;
    MarketStatement _moneyMarketStatement;
    long long _resultMoneyAmount;
    long long _itemDeliveryId;
    MarketStatement _itemMarketStatement;
};

// Card lift-marketdealerdaemon-6: delivery status jobs (layout only). The JobContext module is a later card.
#define LIFT_DELIVERY_STATUS_JOB(Name)                         \
    class Name : public JobContext                             \
    {                                                          \
    public:                                                    \
        enum Param : int                                       \
        {                                                      \
            PARAM_RETURN_VALUE = 0x0,                          \
            PARAM_DELIVERY_ID = 0x1,                           \
            MAX_PARAM_COUNT = 0x2,                             \
        };                                                     \
        virtual ~Name();                                       \
        virtual bool verifyParameter(short& result) const;     \
        virtual bool handleJob(short& result);                 \
                                                               \
        unsigned long long _tid;                               \
        long long _deliveryId;                                 \
    };                                                         \
    static_assert(sizeof(Name) == 0x18, "sizeof " #Name);      \
    static_assert(offsetof(Name, _deliveryId) == 0x10, #Name "::_deliveryId")

// LIFT: The macro is not in the PDB. The five classes have the same layout in the PDB types.
LIFT_DELIVERY_STATUS_JOB(UpdateStatusToReportSuccessJob);
LIFT_DELIVERY_STATUS_JOB(UpdateStatusToPawnRemovalSuccessJob);
LIFT_DELIVERY_STATUS_JOB(UpdateStatusToPawnRemovalFailureJob);
LIFT_DELIVERY_STATUS_JOB(UpdateStatusToPostRegistrationFailureJob);
LIFT_DELIVERY_STATUS_JOB(UpdateStatusToRetryReadyJob);
#undef LIFT_DELIVERY_STATUS_JOB

class UpdateStatusToPostRegistrationSuccessJob : public JobContext
{
public:
    enum Param : int
    {
        PARAM_RETURN_VALUE = 0x0,
        PARAM_DELIVERY_ID = 0x1,
        PARAM_RECEIPT_ID = 0x2,
        MAX_PARAM_COUNT = 0x3,
    };
    virtual ~UpdateStatusToPostRegistrationSuccessJob();
    virtual bool verifyParameter(short& result) const;
    virtual bool handleJob(short& result);

    unsigned long long _tid;
    long long _deliveryId;
    long long _receiptId;
};
static_assert(sizeof(UpdateStatusToPostRegistrationSuccessJob) == 0x20, "sizeof UpdateStatusToPostRegistrationSuccessJob");
static_assert(offsetof(UpdateStatusToPostRegistrationSuccessJob, _receiptId) == 0x18,
              "UpdateStatusToPostRegistrationSuccessJob::_receiptId");
