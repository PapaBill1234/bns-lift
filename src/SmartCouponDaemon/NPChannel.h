// NPChannel.obj (..\Shared\NPChannel2.cpp), NPServiceChannel.obj and NPMessageHandler.obj (SmartCouponDaemon PDB).
// Layouts from include/pdb/SmartCouponDaemon/types.h.
#pragma once
#include <stddef.h>

struct HINSTANCE__;
#include <map>
#include <vector>
#include "SharedChannel.h"
#include "Channel.h"
#include "Lock.h"
#include "StlMemory.h"
#include "TimerQueue.h"

class NPChannel;
class NPPing;
class NPTransactionRegistry;
class NPTransaction;
class SessionHandler;
class Session;
class Packet;

class CouponJob;
union id128;

namespace StsMsgLib
{
// PDB enums (include/pdb/SmartCouponDaemon/types.h).
enum ECommand : int {
    COMMAND_INVALID = -1,
    COMMAND_NONE = 0x0,
    COMMAND_INITIAL_CONNECT = 0x3E9,
    COMMAND_PING = 0x3EA,
    COMMAND_COMMON_PRES_USER_INFO = 0x4B1,
    COMMAND_COMMON_PRES_WHISPER = 0x4B2,
    COMMAND_COMMON_GATE_CUSTOM_MESSAGE = 0x641,
    COMMAND_COMMON_WORLD_LIST_WORLDS = 0x6A5,
    COMMAND_COMMON_SECONDPWD_GET_STATUS = 0x6AF,
    COMMAND_COMMON_GRADE_LIST_GRADES = 0x6B9,
    COMMAND_COMMON_GRADE_GET_LEVEL = 0x6BA,
    COMMAND_COMMON_GRADE_LIST_LEVELS = 0x6BB,
    COMMAND_COMMON_GRADE_GET_BASE_GRADEID_ACTIVATION = 0x6BC,
    COMMAND_COMMON_GRADE_LIST_ALL_GRADES = 0x6BD,
    COMMAND_COMMON_SLOT_LIST_SLOTS = 0x5DD,
    COMMAND_COMMON_SLOT_GET_SLOT = 0x5DE,
    COMMAND_COMMON_GOODS_LIST_CATEGORY_IDS = 0x777,
    COMMAND_COMMON_GOODS_GET_GAME_GOODS_BY_CATEGORY_ID = 0x778,
    COMMAND_COMMON_GOODS_GET_REVISION = 0x779,
    COMMAND_COMMON_PURCHASE_PURCHASE = 0x781,
    COMMAND_COMMON_PROMOTIONSTAMP_LIST_CURRENT_PROMOTIONS = 0x673,
    COMMAND_COMMON_PROMOTIONSTAMP_GET_PROMOTION_POLICY = 0x674,
    COMMAND_COMMON_PROMOTIONSTAMP_GET_USER_PROMOTION_STATUS = 0x675,
    COMMAND_COMMON_PROMOTIONSTAMP_ATTEND_PROMOTION = 0x676,
    COMMAND_COMMON_PROMOTIONSTAMP_ATTEND_PROMOTION_SECURED = 0x677,
    COMMAND_COMMON_PROMOTIONSTAMP_REQUEST_REWARD_DELIVERY = 0x678,
    COMMAND_COMMON_PROMOTIONSTAMP_LIST_INVALID_REWARD_DELIVERIES = 0x679,
    COMMAND_SRV_AUTH_CONSUME_GAME_TOKEN = 0x835,
    COMMAND_SRV_AUTH_CREATE_ACCOUNT = 0x836,
    COMMAND_SRV_AUTH_GET_GAME_ACCOUNT_ID = 0x837,
    COMMAND_SRV_AUTH_LINK_GAME_ACCOUNT = 0x838,
    COMMAND_SRV_AUTH_LOGIN_WEB_START = 0x839,
    COMMAND_SRV_AUTH_IS_USER_NAME_CHANGEABLE_INCOMPLETE = 0x83A,
    COMMAND_SRV_AUTH_GET_USER_NAME_CHANGEABLE_INCOMPLETE = 0x83B,
    COMMAND_SRV_AUTH_CHANGE_MY_USER_NAME_INCOMPLETE = 0x83C,
    COMMAND_SRV_AUTH_GET_USER_INFO = 0x83D,
    COMMAND_SRV_GAMEACCOUNT_LIST_USER_LAST_PRESENCES = 0x8CB,
    COMMAND_SRV_PROFILE_GET_USER_PROFILE = 0x8D5,
    COMMAND_SRV_GAMETIME_GET_GAME_TIME = 0x8DF,
    COMMAND_SRV_GROUP_SET_GROUP_DATA = 0x8FD,
    COMMAND_SRV_GROUP_GET_GROUP_INFO = 0x8FE,
    COMMAND_SRV_GROUP_JOIN = 0x8FF,
    COMMAND_SRV_GROUP_INVITE = 0x900,
    COMMAND_SRV_GROUP_SET_ROLE = 0x901,
    COMMAND_SRV_GROUP_GROUP_INFO = 0x902,
    COMMAND_SRV_GROUP_SET_WATCH = 0x903,
    COMMAND_SRV_GROUP_USER_INFO = 0x904,
    COMMAND_SRV_GAMEGROUP_REQUEST_VALIDATE_GROUP = 0x957,
    COMMAND_SRV_GAMEGROUP_REQUEST_GET_CHANNEL_PROPERTY = 0x958,
    COMMAND_SRV_GAMEGROUP_REQUEST_GROUP_INFO = 0x959,
    COMMAND_SRV_CHANNEL_SET_PERMISSION_GROUP = 0x961,
    COMMAND_SRV_CHANNEL_UNSET_PERMISSION_GROUP = 0x962,
    COMMAND_SRV_CHANNEL_DELETE_GROUP_CHANNEL = 0x963,
    COMMAND_SRV_CHANNEL_KICK = 0x964,
    COMMAND_SRV_CHANNEL_SET_PERMISSION_MEMBER_CHANNELS = 0x965,
    COMMAND_SRV_CHANNEL_UNSET_PERMISSION_MEMBER_CHANNELS = 0x966,
    COMMAND_SRV_PRES_LOGIN = 0x899,
    COMMAND_SRV_PRES_LOGOUT = 0x89A,
    COMMAND_SRV_PRES_WHISPER = 0x89B,
    COMMAND_SRV_PRES_SET_USER_DATA = 0x89C,
    COMMAND_SRV_PRES_GET_USER_INFO = 0x89D,
    COMMAND_SRV_PRES_SET_WATCH = 0x89E,
    COMMAND_SRV_PRES_LOGOUT_USER = 0x89F,
    COMMAND_SRV_PRES_SET_APP_DATA = 0x8A0,
    COMMAND_SRV_PRES_MESSAGE = 0x8A1,
    COMMAND_SRV_PRES_KICK = 0x8A2,
    COMMAND_SRV_SLOT_CREATE_SLOTS = 0x9C5,
    COMMAND_SRV_SLOT_DELETE_SLOT = 0x9C6,
    COMMAND_SRV_SLOT_SET_DATA = 0x9C7,
    COMMAND_SRV_SLOT_RESET_DATA = 0x9C8,
    COMMAND_SRV_GATE_FIND = 0xA29,
    COMMAND_SRV_GATE_REGISTER_SERVICE = 0xA2A,
    COMMAND_SRV_GATE_UNREGISTER_SERVICE = 0xA2B,
    COMMAND_SRV_GATE_UPDATE_WORLD_PROPERTY = 0xA2C,
    COMMAND_SRV_GATE_GAMEACCOUNT_GET_ATTRIBUTES = 0xA2D,
    COMMAND_SRV_GATE_REGISTER_WAREHOUSE_SERVICE = 0xA2E,
    COMMAND_SRV_WORLD_GET_STATUS = 0xA8D,
    COMMAND_SRV_SECONDPWD_IS_VERIFIED = 0xA97,
    COMMAND_SRV_GRADE_ACTIVATE_GRADE = 0xAA1,
    COMMAND_SRV_GRADE_ADD_GRADE_SCORE = 0xAA2,
    COMMAND_SRV_GRADE_NOTIFY_GRADE_CHANGED = 0xAA3,
    COMMAND_SRV_GRADE_NOTIFY_SCORE_CHANGED = 0xAA4,
    COMMAND_SRV_FRIEND_SEND_MESSAGE = 0xABF,
    COMMAND_SRV_CONTENTBAN_LIST_USER_BANS = 0xADD,
    COMMAND_SRV_MTX_LIST_GOODS_INFOS = 0xAF1,
    COMMAND_SRV_MTX_GET_GOODS_INFO = 0xAF2,
    COMMAND_SRV_MTX_INVALID_GOODS_INVENTORY_INFO = 0xAF3,
    COMMAND_SRV_MTX_ELIMINATE_GOODS_INVENTORY = 0xAF7,
    COMMAND_SRV_GOODS_LIST_GOODS_INFOS = 0xAF8,
    COMMAND_SRV_WAREHOUSE_REQUEST_GOODS_INFO_CHANGED = 0xAFA,
    COMMAND_SRV_WAREHOUSE_REQUEST_GOODS_INVENTORY_CHANGED = 0xAFB,
    COMMAND_SRV_WAREHOUSE_GET_GOODS_COUNT = 0xAFC,
    COMMAND_SRV_WAREHOUSE_LIST = 0xAFD,
    COMMAND_SRV_WAREHOUSE_TAKE = 0xAFE,
    COMMAND_SRV_CHARGE_GET_INFO = 0xB55,
    COMMAND_SRV_CHARGE_START = 0xB56,
    COMMAND_SRV_CHARGE_STOP = 0xB57,
    COMMAND_SRV_CHARGE_REQUEST_STOP = 0xB58,
    COMMAND_SRV_CHARGE_ABANDON = 0xB59,
    COMMAND_SRV_CHARGE_NOTIFY_REMAIN_TIME = 0xB5A,
    COMMAND_SRV_CHARGE_NOTIFY_APPLY_NEW_CHARGE_ITEM = 0xB5B,
    COMMAND_SRV_PURCHASE_GET_PURCHASE = 0xB69,
    COMMAND_SRV_REFUND_REFUND_AGENCY_PURCHASE = 0xB4B,
    COMMAND_SRV_REWARDBROKER_EVENT_NOTI = 0xB23,
    COMMAND_SRV_REWARD_REQUEST_REWARD_FOR_EVENT = 0xB24,
    COMMAND_SRV_AUCTION_ESCROW = 0xB91,
    COMMAND_SRV_AUCTION_ROLLBACK_ESCROW = 0xB92,
    COMMAND_SRV_AUCTION_DELIVER = 0xB93,
    COMMAND_SRV_AUCTION_BID = 0xB94,
    COMMAND_SRV_VIRTUALCURRENCY_DEPOSIT = 0xBA5,
    COMMAND_SRV_RISKMGMT_INQUIRY = 0xA1F,
    COMMAND_COMMON_FOLLOW_FOLLOWED = 0xBB9,
    COMMAND_CLI_AUTH_LOGIN_START = 0xC1D,
    COMMAND_CLI_AUTH_LOGIN_KEY_DATA = 0xC1E,
    COMMAND_CLI_AUTH_LOGIN_FINISH = 0xC1F,
    COMMAND_CLI_AUTH_LOGOUT = 0xC21,
    COMMAND_CLI_AUTH_GAME_ACCOUNT_LIST = 0xC22,
    COMMAND_CLI_AUTH_REQUEST_GAME_TOKEN = 0xC23,
    COMMAND_CLI_AUTH_CHANGE_MY_PASSWORD = 0xC24,
    COMMAND_CLI_AUTH_RESET_PASSWORD = 0xC25,
    COMMAND_CLI_AUTH_REQUEST_TOKEN = 0xC26,
    COMMAND_CLI_AUTH_LOGIN_TOKEN_START = 0xC27,
    COMMAND_CLI_AUTH_TOKEN_KEY_DATA = 0xC28,
    COMMAND_CLI_AUTH_VERIFY_MOBI_OTP = 0xC29,
    COMMAND_CLI_AUTH_GET_MY_USER_INFO = 0xC2A,
    COMMAND_CLI_AUTH_GET_USERS_INFO = 0xC2B,
    COMMAND_CLI_AUTH_VERIFY_SECONDARY_AUTH = 0xC2C,
    COMMAND_CLI_AUTH_GET_SECURITY_CARD_CODE_INDEX = 0xC2D,
    COMMAND_CLI_AUTH_REGISTER_SECONDARY_PASSWORD = 0xC2E,
    COMMAND_CLI_PRES_LOGOUT_USER = 0xC81,
    COMMAND_COMMON_PRES_MESSAGE = 0xC82,
    COMMAND_CLI_GRADE_REWARD = 0xE89,
    COMMAND_CLI_SHOWCASE_LIST_CURRENT_GOODS_BY_CATEGORY_ID = 0xE9D,
    COMMAND_CLI_SHOWCASE_GET_USER_SALE_PRICE_BY_GOODS_ID = 0xE9E,
    COMMAND_CLI_SHOWCASE_LIST_GOODS_SALE_PRICE = 0xE9F,
    COMMAND_CLI_SHOWCASE_GET_GOODS_DISPLAY_REVISION = 0xEA0,
    COMMAND_CLI_SHOWCASE_LIST_DISPLAY_CATEGORY = 0xEA1,
    COMMAND_CLI_FRIEND_PROPOSE = 0xEA7,
    COMMAND_CLI_FRIEND_DENY_PROPOSAL = 0xEA8,
    COMMAND_CLI_FRIEND_ACCEPT_PROPOSAL = 0xEA9,
    COMMAND_CLI_FRIEND_PAGE_RECV_PROPOSALS = 0xEAA,
    COMMAND_CLI_FRIEND_REMOVE = 0xEAB,
    COMMAND_CLI_FRIEND_CHANGE_ALIAS = 0xEAC,
    COMMAND_CLI_FRIEND_GET_USERINFO = 0xEAD,
    COMMAND_CLI_FRIEND_GET_RELATIONS = 0xEAE,
    COMMAND_CLI_FRIEND_PAGE_FRIENDS = 0xEAF,
    COMMAND_CLI_FRIEND_PROPOSED = 0xEB0,
    COMMAND_CLI_FRIEND_PROPOSAL_ACCEPTED = 0xEB1,
    COMMAND_CLI_FRIEND_PROPOSAL_DENIED = 0xEB2,
    COMMAND_CLI_FRIEND_INFO = 0xEB3,
    COMMAND_CLI_FRIEND_MESSAGE = 0xEB4,
    COMMAND_CLI_FRIEND_USER_NAME_CHANGED = 0xEB5,
    COMMAND_CLI_FRIEND_REMOVED = 0xEB6,
    COMMAND_CLI_TENCENT_PURCHASE_TOKEN = 0xEBB,
    COMMAND_CLI_INGAMESHOP_PURCHASE = 0xF6F,
    COMMAND_CLI_INGAMESHOP_PAGE_PURCHASE_HISTORY = 0xF70,
    COMMAND_CLI_INGAMESHOP_GET_CATEGORIES = 0xF71,
    COMMAND_CLI_INGAMESHOP_GET_GOODS_BY_CATEGORYID = 0xF72,
    COMMAND_CLI_INGAMESHOP_GET_GOODS_BY_GOODSID = 0xF73,
    COMMAND_CLI_INGAMESHOP_GET_DISPLAY_REVISION = 0xF74,
    COMMAND_CLI_INGAMESHOP_GET_BALANCE = 0xF75,
    COMMAND_CLI_INGAMESHOP_LIST_GOODS_LIMITS = 0xF76,
    COMMAND_CLI_AUCTION_SELL = 0xF79,
    COMMAND_CLI_AUCTION_CANCEL_SALE = 0xF7A,
    COMMAND_CLI_AUCTION_BID = 0xF7B,
    COMMAND_CLI_AUCTION_PAGE_ITEMS = 0xF7C,
    COMMAND_CLI_AUCTION_PAGE_MY_SALES = 0xF7D,
    COMMAND_CLI_AUCTION_PAGE_MY_SALE_HISTORY = 0xF7E,
    COMMAND_CLI_AUCTION_PAGE_MY_BUY_HISTORY = 0xF7F,
    COMMAND_CLI_AUCTION_LIST_POLICIES = 0xF80,
    COMMAND_CLI_AUCTION_GET_STATISTICS = 0xF81,
    COMMAND_CLI_AUCTION_GET_BALANCE = 0xF82,
    COMMAND_CLI_AUCTION_NOTIFY_EVENT = 0xF83,
    COMMAND_CLI_SECONDPASSWORD_CREATE = 0xE7F,
    COMMAND_CLI_SECONDPASSWORD_CANCEL_DELETE = 0xE80,
    COMMAND_CLI_SECONDPASSWORD_CHANGE_MY_PASSWORD = 0xE81,
    COMMAND_CLI_SECONDPASSWORD_CHANGE_MY_ACTION_MASK = 0xE82,
    COMMAND_CLI_SECONDPASSWORD_ENABLE_MY_ACTION_MASK = 0xE83,
    COMMAND_CLI_SECONDPASSWORD_DISABLE_MY_ACTION_MASK = 0xE84,
    COMMAND_CLI_SECONDPASSWORD_VERIFY = 0xE85,
    COMMAND_CLI_VIRTUALCURRENCY_GET_BALANCE = 0xF8D,
    COMMAND_CLI_VIRTUALCURRENCY_NOTIFY_BALANCE_CHANGED = 0xF8E,
    COMMAND_CLI_INGAMESHOP_WISH_WISH = 0xF97,
    COMMAND_CLI_INGAMESHOP_WISH_ACCEPT = 0xF98,
    COMMAND_CLI_INGAMESHOP_WISH_REJECT = 0xF99,
    COMMAND_CLI_INGAMESHOP_WISH_PAGE_WISHES = 0xF9A,
    COMMAND_CLI_INGAMESHOP_WISH_PAGE_RECEIVED_WISHES = 0xF9B,
    COMMAND_CLI_INGAMESHOP_WISH_GET_WISH_COUNT_AT_TODAY = 0xF9C,
    COMMAND_CLI_INGAMESHOP_WISH_IS_OPTOUT_USER = 0xF9D,
    COMMAND_CLI_INGAMESHOP_WISH_CHANGE_OPTOUT = 0xF9E,
    COMMAND_CLI_PROMOTIONSTAMP_GOODS_CATEGORYID_LIST = 0xE49,
    COMMAND_CLI_PROMOTIONSTAMP_GOODS_BY_CATEGORYID = 0xE4A,
    COMMAND_CLI_PROMOTIONSTAMP_GOODS_BY_GOODSID = 0xE4B,
    COMMAND_CLI_PROMOTIONSTAMP_GOODS_REVISION = 0xE4C,
    COMMAND_CLI_COUPON_REGISTER_USER_COUPON = 0xF5B,
    COMMAND_CLI_COUPON_GET_USER_COUPON_COUNT = 0xF5C,
    COMMAND_CLI_COUPON_PAGE_USER_COUPONS = 0xF5D,
    COMMAND_CLI_COUPON_USE_GOODS_COUPON = 0xF5E,
    COMMAND_CLI_PG_DR_DIRECT_PURCHASE = 0xF65,
    COMMAND_CLI_PG_CHECK_DR_BILLING_INFO = 0xF66,
    COMMAND_CLI_PG_CHECK_CURRENCY_LOCKING = 0xF67,
    COMMAND_CLI_PG_PAGE_PAYMENT_ORDER = 0xF68,
    COMMAND_CLI_GOODS_PAGE_SEARCH_GOODS = 0xF47,
    COMMAND_CLI_GOODS_LIST_GAME_GOODS = 0xF48,
    COMMAND_CLI_GOODS_CHECK_NEW_GOODS = 0xF49,
    COMMAND_CLI_GOODS_GET_SALE_GOODS = 0xF4A,
    COMMAND_CLI_SLOT_SET_DATA = 0xDAD,
    COMMAND_CLI_REPORT_ADD_REPORT = 0xF29,
    COMMAND_CLI_CHANNEL_CREATE = 0xD49,
    COMMAND_CLI_CHANNEL_JOIN = 0xD4A,
    COMMAND_CLI_CHANNEL_LEAVE = 0xD4B,
    COMMAND_CLI_CHANNEL_LOGOUT = 0xD4C,
    COMMAND_CLI_CHANNEL_TALK = 0xD4D,
    COMMAND_CLI_CHANNEL_NOTIFY_TALK = 0xD4E,
    COMMAND_CLI_CHANNEL_NOTIFY_USER_INFO = 0xD4F,
    COMMAND_CLI_CHANNEL_NOTIFY_CHANNEL_INFO = 0xD50,
    COMMAND_CLI_CHANNEL_JOIN_GROUP_CHANNEL = 0xD51,
    COMMAND_CLI_CHANNEL_PAGE_MEMBERS = 0xD52,
    COMMAND_CLI_CHANNEL_SET_PERMISSION = 0xD53,
    COMMAND_CLI_CHANNEL_UNSET_PERMISSION = 0xD54,
    COMMAND_CLI_CHANNEL_ACTIVATE_VOICE = 0xD55,
    COMMAND_CLI_CHANNEL_DEACTIVATE_VOICE = 0xD56,
    COMMAND_CLI_CHANNEL_SET_USER_DATA = 0xD57,
    COMMAND_CLI_CHANNEL_START_VOICE = 0xD58,
    COMMAND_CLI_CHANNEL_END_VOICE = 0xD59,
};

enum EMessageType : int {
    MESSAGE_TYPE_NONE = 0x0,
    MESSAGE_TYPE_REQUEST = 0x1,
    MESSAGE_TYPE_RESPONSE = 0x2,
    MESSAGE_TYPE_NOTIFY = 0x3,
    MESSAGES = 0x4,
};

enum EStsMsgError : int {
    STS_MSG_ERROR_NONE = 0x0,
    STS_MSG_ERROR_SUCCESS = 0x1,
    STS_MSG_ERROR_FAIL = 0x2,
    STS_MSG_ERROR_WRONG_GAME_CODE = 0x3,
    STS_MSG_ERROR_WRONG_PARAMETERS = 0x4,
    STS_MSG_ERROR_BUFFER_SIZE_IS_NOT_ENOUGH = 0x5,
    STS_MSG_ERROR_WRONG_MESSAGE_BODY = 0x6,
    STS_MSG_ERROR_ALLOC_FAILED = 0x7,
    STS_MSG_ERROR_WRONG_KEY_DATA = 0x8,
    STS_MSG_ERROR_WRONG_COMMAND = 0x9,
    STS_MSG_ERROR_ENCRYPT_FAILED = 0xA,
    STS_MSG_ERROR_DECRYPT_FAILED = 0xB,
    STS_MSG_ERRORS = 0xC,
};

struct _StsMsg
{
    virtual ECommand GetCommand() = 0;            // slot 0
    virtual unsigned int GetTransactionId() = 0;  // slot 1
    virtual EMessageType GetMessageType() = 0;    // slot 2
};
static_assert(sizeof(_StsMsg) == 0x8, "sizeof StsMsgLib::_StsMsg");

struct _StsMsgBuffer
{
    unsigned char* pData;
    unsigned int nLen;
};

// The interface that StsMsgSrv64.dll gives (CreateStsMsg).
class IStsMsg
{
public:
    virtual int Initialize(int programId, char const* gameCode) = 0;            // slot 0
    virtual EStsMsgError Build(_StsMsg* msg, _StsMsgBuffer* buffer) = 0;        // slot 1
    virtual void WriteReceiveData(unsigned char* data, unsigned int len) = 0;   // slot 2
    virtual EStsMsgError Parse(_StsMsg** msg, void* cmdDispatcher) = 0;         // slot 3
    virtual void ReleaseStsMsg(_StsMsg* msg) = 0;                               // slot 4
    virtual int SetCryptFilterWhenUsingExternalAuth() = 0;                      // slot 5 ❓ signature
};

struct _StsMsgInfo
{
    ECommand eCmd;
    EMessageType msgType;
};
static_assert(sizeof(_StsMsgInfo) == 0x8, "sizeof StsMsgLib::_StsMsgInfo");

struct _StsMsgInfoRequest : public _StsMsgInfo
{
    unsigned int nTxnId;
};

struct _StsMsgRequest : public _StsMsg
{
    virtual ECommand GetCommand();            // 0x4440
    virtual unsigned int GetTransactionId();  // 0x4450
    virtual EMessageType GetMessageType();    // 0x4460

    _StsMsgInfoRequest msgInfo;
};
static_assert(sizeof(_StsMsgRequest) == 0x18, "sizeof StsMsgLib::_StsMsgRequest");
static_assert(offsetof(_StsMsgRequest, msgInfo.nTxnId) == 0x10, "_StsMsgRequest nTxnId");

struct _StsMsgRequestPing : public _StsMsgRequest
{
};

struct _StsMsgRequestInitialConnect : public _StsMsgRequest
{
    char* pszIpAddress;
};

struct _StsMsgRequestRewardBrokerEventNoti : public _StsMsgRequest
{
    void* pUserId;
    int nNotiType;
    int nEventId;
    long long nRequestKey;
    wchar_t* pwszRequestDesc;
};
static_assert(offsetof(_StsMsgRequestRewardBrokerEventNoti, nRequestKey) == 0x28, "nRequestKey");

struct _StsMsgRequestRewardRequestRewardForEvent : public _StsMsgRequest
{
    void* pUserId;
    char* pszEventId;
    short nRequestFromCode;
    char* pszRequestKey;
};

// PDB type StsMsgLib::_StsMsgInfoResponse::_StsMsgBanInfo.
struct _StsMsgBanInfo
{
    unsigned int nBanId;
    long long tEffectiveFrom;
    long long tEffectiveTo;
    long long tUserUnbanFrom;
    int nBanReasonCode;
};
static_assert(sizeof(_StsMsgBanInfo) == 0x28, "sizeof StsMsgLib::_StsMsgBanInfo");

struct _StsMsgErrInfo
{
    char const* pszErr;
    unsigned int nStatusCode;
    wchar_t const* pwszReason;
    int nErrorCode;
    _StsMsgBanInfo banInfo;
};
static_assert(sizeof(_StsMsgErrInfo) == 0x48, "sizeof StsMsgLib::_StsMsgErrInfo");

struct _StsMsgInfoResponse : public _StsMsgInfo
{
    unsigned int nTxnId;
    bool bComplete;
    _StsMsgErrInfo errInfo;
};
static_assert(sizeof(_StsMsgInfoResponse) == 0x58, "sizeof StsMsgLib::_StsMsgInfoResponse");

struct _StsMsgResponse : public _StsMsg
{
    _StsMsgInfoResponse msgInfo;
};
static_assert(sizeof(_StsMsgResponse) == 0x60, "sizeof StsMsgLib::_StsMsgResponse");
static_assert(offsetof(_StsMsgResponse, msgInfo.bComplete) == 0x14, "bComplete");
static_assert(offsetof(_StsMsgResponse, msgInfo.errInfo.nStatusCode) == 0x20, "nStatusCode");
static_assert(offsetof(_StsMsgResponse, msgInfo.errInfo.pwszReason) == 0x28, "pwszReason");
static_assert(offsetof(_StsMsgResponse, msgInfo.errInfo.nErrorCode) == 0x30, "nErrorCode");

struct _StsMsgResponseRewardBrokerEventNoti : public _StsMsgResponse
{
    wchar_t* pwszAcceptTid;
};
static_assert(sizeof(_StsMsgResponseRewardBrokerEventNoti) == 0x68, "sizeof _StsMsgResponseRewardBrokerEventNoti");
}  // namespace StsMsgLib

bool STSMSGLIB_CHECK_DLL_VERSION(HINSTANCE__* module);  // 0x4350

class NPMessageHandler
{
public:
    virtual bool OnConnect(NPChannel*, bool) const = 0;                               // slot 0
    virtual bool OnClose(NPChannel*, bool) const = 0;                                 // slot 1
    virtual bool HandleMessage(NPChannel*, StsMsgLib::_StsMsg*, void*) const = 0;     // slot 2
};
static_assert(sizeof(NPMessageHandler) == 0x8, "sizeof NPMessageHandler");

class NPSessionHandler : public SessionHandler
{
public:
    virtual bool OnAccept(Session const* session) const;                          // 0x4A60
    virtual bool OnConnect(Session const* session, bool firstConnected) const;    // 0x4AD0
    virtual void OnClose(Session const* session, bool tryReconnect) const;        // 0x4BC0
    virtual bool PacketHandler(Session const* session, Packet const* packet) const;  // 0x4CC0

    mutable CriticalSection _connlock;
};
static_assert(sizeof(NPSessionHandler) == 48, "sizeof NPSessionHandler");

class NPPing : public Timer
{
public:
    // LIFT: Inlined in NPChannel::Initialize (0x5120).
    explicit NPPing(NPChannel* owner) : _owner(owner), _run(false)
    {
        StartTick = 0;
        InLtq = false;
        prev = nullptr;
        next = nullptr;
        SlotIndex = -1;
    }
    virtual unsigned int TimerClass() const;                        // 0x4470
    virtual unsigned long long TimerId() const;                     // 0x4480
    virtual bool HandleEvent(EventContext* ctx, unsigned long);     // 0x4490

    static unsigned int _class;        // rva 0x84AC0
    static unsigned long long _id;     // rva 0x84AC8
    static long _interval;             // rva 0x84AC4

    NPChannel* _owner;
    bool _run;
};
static_assert(sizeof(NPPing) == 72, "sizeof NPPing");

class NPTransactionRegistry
{
public:
    struct Item
    {
        StsMsgLib::ECommand cmd;
        void* context;
    };
    typedef void (*CmdDispatcher)(unsigned int, StsMsgLib::ECommand*);  // ❓ typedef name

    explicit NPTransactionRegistry(CmdDispatcher cmdDispatcher);  // 0x4500
    bool Find(unsigned int id, Item* item);                         // 0x4580
    bool Register(StsMsgLib::ECommand cmd, void* context, unsigned int* id);  // 0x4690
    void* Release(unsigned int id);                                 // 0x47D0
    // ❓ The PDB type is std::vector<Timer*,StlAllocator<Timer*,2>>* (COMDAT folding). The code stores void*.
    void ReleaseAll(std::vector<void*, StlAllocator<void*, 2> >* e);  // 0x48B0

    CmdDispatcher _cmdDispatcher;
    unsigned int volatile _seed;
    std::map<unsigned int, Item*, std::less<unsigned int>, StlAllocator<std::pair<unsigned int const, Item*>, 2> > _dict;
    CriticalSection _lock;
};
static_assert(sizeof(NPTransactionRegistry) == 0x58, "sizeof NPTransactionRegistry");

class NPTransaction
{
public:
    virtual ~NPTransaction() {}
    virtual int GetKind() const = 0;
    virtual void Expire() = 0;
};

class NPJobTransaction : public NPTransaction
{
public:
    NPJobTransaction() : _jobid(0), _state(-1), _task(0) {}  // LIFT: inlined in SendRequestEventNoti (0xFF10)
    virtual ~NPJobTransaction() {}
    virtual int GetKind() const { return 1; }  // 0x231F0
    virtual void Expire();                     // 0xFE70

    unsigned long long _jobid;
    int _state;
    int _task;
};
static_assert(sizeof(NPJobTransaction) == 24, "sizeof NPJobTransaction");

class NPChannel : public SharedChannel
{
public:
    NPChannel() : _sts(nullptr), _handler(nullptr), _tranRegistry(nullptr), _ping(nullptr) {}  // LIFT: inlined
    virtual ~NPChannel();  // 0x5000
    virtual bool Connect(unsigned long long id, unsigned int portId, unsigned long ip, unsigned short portNo,
                         long timeout, bool reconnect);  // 0x5300

    static bool Setup(int programId, wchar_t const* gameCode);  // 0x4D40
    static void Cleanup();                                      // 0x4F50

    bool Initialize(NPMessageHandler* handler, NPTransactionRegistry::CmdDispatcher cmdDispatcher);  // 0x5120
    bool SendMsg(StsMsgLib::_StsMsg* msg, bool response, void* context);  // 0x53D0
    bool handlePacket(Packet const* packet);                                // 0x57D0
    bool onConnect(Session const* session, bool firstConnected);           // 0x5AD0
    bool sendInitialConnectMessage(Session const* session);                // 0x5C40
    static bool checkLibError(StsMsgLib::EStsMsgError err);                // 0x5D50

    static NPSessionHandler* _sessionHandler;
    static HINSTANCE__* _module;
    static int _programId;
    static wchar_t _gameCode[9];
    static StsMsgLib::IStsMsg* (*_stsCreate)();
    static void (*_stsCleanUp)(StsMsgLib::IStsMsg*);
    static bool _recvCompletionLog;

    StsMsgLib::IStsMsg* _sts;
    NPMessageHandler* _handler;
    NPTransactionRegistry* _tranRegistry;
    NPPing* _ping;
};
static_assert(sizeof(NPChannel) == 0x40, "sizeof NPChannel");

class NPServiceChannel : public NPChannel
{
public:
    NPServiceChannel() {}            // LIFT: inlined in NPServiceChannelManager::Initialize (0x10340)
    virtual ~NPServiceChannel() {}   // 0xFD50 (scalar deleting destructor only)

    bool SendRequestEventNoti(CouponJob* job, id128 const* gameAccountId, int couponEventId,
                              long long publicationId);  // 0xFF10
};
static_assert(sizeof(NPServiceChannel) == 0x40, "sizeof NPServiceChannel");

typedef bool (*NPServiceMessageHandler)(NPChannel*, StsMsgLib::_StsMsg*, NPTransaction*);  // PDB S_UDT (0x4B4E)

class NPMsgHandleEvent : public DynamicEventObject
{
public:
    // LIFT: Inlined in NPServiceChannelManager::HandleMessage (0x10700).
    NPMsgHandleEvent(NPChannel* channel, StsMsgLib::_StsMsg* msg, NPTransaction* tran, NPServiceMessageHandler handler)
        : _channel(channel), _msg(msg), _tran(tran), _handler(handler)
    {
    }
    virtual ~NPMsgHandleEvent();                                   // 0x10230
    virtual unsigned int EventId() const { return 0; }             // ❓ value
    virtual bool HandleEvent(EventContext* ctx, unsigned long);    // 0x102C0

    NPChannel* _channel;
    StsMsgLib::_StsMsg* _msg;
    NPTransaction* _tran;
    NPServiceMessageHandler _handler;
};
static_assert(sizeof(NPMsgHandleEvent) == 56, "sizeof NPMsgHandleEvent");

class NPServiceChannelManager : public NPMessageHandler
{
public:
    // LIFT: Inlined in SmartCouponDaemon::initialize (0x150E0).
    NPServiceChannelManager() : _init(false), _npServChannel(nullptr) {}
    virtual bool OnConnect(NPChannel*, bool) const;                                  // 0x104A0
    virtual bool OnClose(NPChannel*, bool) const;                                    // 0x10560
    virtual bool HandleMessage(NPChannel*, StsMsgLib::_StsMsg*, void*) const;        // 0x10700

    bool Initialize(unsigned int portId, unsigned long ip, unsigned short portNo, long timeout);  // 0x10340

    bool _init;
    NPServiceChannel* _npServChannel;
};
static_assert(sizeof(NPServiceChannelManager) == 0x18, "sizeof NPServiceChannelManager");

void NPServiceChannelCmdDispatcher(unsigned int id, StsMsgLib::ECommand* eCmd);           // 0xFD80
bool NPHandlerEventNoti(NPChannel* channel, StsMsgLib::_StsMsg* msg, NPTransaction* tran);  // 0xFBC0
