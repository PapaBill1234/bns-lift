// AuctionEscrow.obj (LobbyDaemon 2019 + PDB).
#pragma once
#include "LobbyDB.h"
#include "StsMsgGrade.h"
#include "StringUtil.h"

namespace StsMsgLib
{
struct _StsMsgInfoRequest : public _StsMsgInfo
{
    unsigned int nTxnId;
};

struct _StsMsgRequest : public _StsMsg
{
    virtual ECommand GetCommand() { return msgInfo.eCmd; }
    virtual unsigned int GetTransactionId() { return msgInfo.nTxnId; }
    virtual EMessageType GetMessageType() { return msgInfo.msgType; }
    _StsMsgInfoRequest msgInfo;
};
static_assert(sizeof(_StsMsgRequest) == 0x18, "sizeof _StsMsgRequest");

struct _StsMsgRequestGameAuctionDeliver : public _StsMsgRequest
{
    enum AuctionEventType
    {
        AUCTIONEVENTTYPE_INVALID = 0,
        AUCTIONEVENTTYPE_SUCCESS = 1,
        AUCTIONEVENTTYPE_EXPIRED = 2,
        AUCTIONEVENTTYPE_CANCELED = 3,
        AUCTIONEVENTTYPE_BIDFAIL = 4,
        AUCTIONEVENTTYPE_MAX = 5
    };

    enum AuctionUserType
    {
        AUCTIONUSERTYPE_INVALID = 0,
        AUCTIONUSERTYPE_SELLER = 1,
        AUCTIONUSERTYPE_BUYER = 2,
        AUCTIONUSERTYPE_MAX = 3
    };

    struct _AuctionMessage
    {
        AuctionEventType eAuctionEventType;
        AuctionUserType eAuctionUserType;
        GUID AuctionId;
        wchar_t GameItemKey[51];
        long long nQuantity;
        long long nSalePrice;
        long long nBidPrice;
        long long nCurrencyFee;
        long long nGameItemFee;
        long long tRegistered;
    };

    struct _DeliveryItem
    {
        wchar_t GameItemKey[51];
        long long nQuantity;
    };

    wchar_t RequestId[51];
    GUID UserId;
    short nWorldCode;
    long long nCharacterId;
    _AuctionMessage AuctionMessage;
    _DeliveryItem* pDeliveryItem;
    int nDeliveryItemCount;
};
static_assert(sizeof(_StsMsgRequestGameAuctionDeliver::_AuctionMessage) == 0xb0, "sizeof _AuctionMessage");
static_assert(sizeof(_StsMsgRequestGameAuctionDeliver::_DeliveryItem) == 0x70, "sizeof _DeliveryItem");
static_assert(sizeof(_StsMsgRequestGameAuctionDeliver) == 0x160, "sizeof _StsMsgRequestGameAuctionDeliver");
static_assert(offsetof(_StsMsgRequestGameAuctionDeliver, AuctionMessage) == 0xa0, "AuctionMessage offset");
static_assert(offsetof(_StsMsgRequestGameAuctionDeliver, nDeliveryItemCount) == 0x158, "nDeliveryItemCount offset");
}

struct LobbyDB::TryAuctionEscrowRollbackOutParam
{
    unsigned long long escrowId;
    id128 recipientAccountId;
    short recipientWid;
    unsigned long long recipientPcid;
    wchar_t recipientName[33];
    long long gameMoneyAmount;
    unsigned long long deliveryId;
};
static_assert(sizeof(LobbyDB::TryAuctionEscrowRollbackOutParam) == 0x80, "sizeof TryAuctionEscrowRollbackOutParam");
static_assert(offsetof(LobbyDB::TryAuctionEscrowRollbackOutParam, gameMoneyAmount) == 0x70, "gameMoneyAmount offset");

class AuctionEscrow
{
public:
    static bool GetDeliveryPostMessage(StsMsgLib::_StsMsgRequestGameAuctionDeliver* param, wchar_t* buf, int bufsizeInWords);  // 0x13630
    static bool GetRollbackEscrowPostMessage(LobbyDB::TryAuctionEscrowRollbackOutParam* param, wchar_t* buf, int bufsizeInWords);  // 0x14770
};

bool __printXml(wchar_t*&, wchar_t*, wchar_t const*, ...);  // 0x135e0
