// JobContext.obj (MarketDealerDaemon PDB).
// Card lift-marketdealerdaemon-5 adds the classes that MarketDB part 2 uses (layout from the PDB).
// The bodies (JobContext.cpp) come in a later card. Only the members that MarketDB calls are declared.
#pragma once

#include <stddef.h>
#include "Participant.h"
#include "MarketStatement.h"
#include "Dealings.h"
#include "SaleContext.h"

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
    virtual ~RetrieveSaleListJob();
    virtual bool verifyParameter(short& result) const;
    virtual bool handleJob(short& result);
    bool addMySaleInfo(MySaleInfo const& mySaleInfo);  // 0x93c0 ❓ const& or const*

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
    virtual ~RetrieveBidListJob();
    virtual bool verifyParameter(short& result) const;
    virtual bool handleJob(short& result);
    bool addMyBidInfo(MyBidInfo const& myBidInfo);  // 0xa5a0 ❓ const& or const*

    unsigned long long _tid;
    short _wid;
    long long _bidderPcId;
    MyBidInfo* _myBidList;
    int _maxListCount;
    int _currListCount;
};

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
    virtual bool verifyParameter(short& result) const;
    virtual bool handleJob(short& result);

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
    virtual bool verifyParameter(short& result) const;
    virtual bool handleJob(short& result);

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
    virtual bool verifyParameter(short& result) const;
    virtual bool handleJob(short& result);

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
    virtual bool verifyParameter(short& result) const;
    virtual bool handleJob(short& result);

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
    virtual bool verifyParameter(short& result) const;
    virtual bool handleJob(short& result);

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
    virtual bool verifyParameter(short& result) const;
    virtual bool handleJob(short& result);

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
    virtual bool verifyParameter(short& result) const;
    virtual bool handleJob(short& result);

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
    virtual bool verifyParameter(short& result) const;
    virtual bool handleJob(short& result);

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
    virtual bool verifyParameter(short& result) const;
    virtual bool handleJob(short& result);

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
    virtual bool verifyParameter(short& result) const;
    virtual bool handleJob(short& result);

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
    virtual bool verifyParameter(short& result) const;
    virtual bool handleJob(short& result);

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
    virtual bool verifyParameter(short& result) const;
    virtual bool handleJob(short& result);

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
    virtual bool verifyParameter(short& result) const;
    virtual bool handleJob(short& result);

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
