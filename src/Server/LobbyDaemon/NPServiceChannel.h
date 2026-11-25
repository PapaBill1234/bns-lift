// NPServiceChannel.obj (LobbyDaemon PDB, 2019 + PDB). Class layouts from the PDB.
#pragma once
#include <stddef.h>
#include <string.h>

class LobbyJob;
class NPChannel;
class NPTransaction;
union id128;

// LIFT: NPChannel is the real class of NPChannelBase.h (SendMsg 0x3ac0 is defined in NPChannel2.cpp). No local copy: one definition only.
#include "NPChannelBase.h"

// LIFT: PDB StsMsgLib request types that LobbyDaemon builds. Layouts from tools/pdbcls.py LobbyDaemon. The base
// _StsMsgRequest comes from NPChannelBase.h.
namespace StsMsgLib
{
struct _StsMsgRequestAuthChangeMyUserNameIncomplete : public _StsMsgRequest
{
    id128 const* pUserId;
    wchar_t const* pwszUserNameOld;
    wchar_t const* pwszUserNameNew;
    bool bSkipCheckPassword;
    wchar_t const* pwszPasswordHash;
};
static_assert(sizeof(_StsMsgRequestAuthChangeMyUserNameIncomplete) == 0x40, "sizeof _StsMsgRequestAuthChangeMyUserNameIncomplete");
static_assert(offsetof(_StsMsgRequestAuthChangeMyUserNameIncomplete, pUserId) == 0x18, "_StsMsgRequestAuthChangeMyUserNameIncomplete::pUserId");
static_assert(offsetof(_StsMsgRequestAuthChangeMyUserNameIncomplete, bSkipCheckPassword) == 0x30, "_StsMsgRequestAuthChangeMyUserNameIncomplete::bSkipCheckPassword");
static_assert(offsetof(_StsMsgRequestAuthChangeMyUserNameIncomplete, pwszPasswordHash) == 0x38, "_StsMsgRequestAuthChangeMyUserNameIncomplete::pwszPasswordHash");

struct _StsMsgRequestFriendSendMessage : public _StsMsgRequest
{
    struct Contents
    {
        struct Field
        {
            char* pszKey;
            wchar_t* pwszValue;
        };
        // LIFT: PDB inline constructor. HandleLobbyGame_FriendMessageNotify (0x90f70) shows the zeroing.
        Contents() : pFields(nullptr), nFieldCount(0) {}
        Field* pFields;
        int nFieldCount;
    };
    id128 const* pUserId;
    id128* pAppIds;
    int nAppIdCount;
    wchar_t const* pwszScope;
    id128* pScopeId;
    wchar_t const* pwszMessageName;
    Contents contents;
};
static_assert(sizeof(_StsMsgRequestFriendSendMessage) == 0x58, "sizeof _StsMsgRequestFriendSendMessage");
static_assert(offsetof(_StsMsgRequestFriendSendMessage, pAppIds) == 0x20, "_StsMsgRequestFriendSendMessage::pAppIds");
static_assert(offsetof(_StsMsgRequestFriendSendMessage, nAppIdCount) == 0x28, "_StsMsgRequestFriendSendMessage::nAppIdCount");
static_assert(offsetof(_StsMsgRequestFriendSendMessage, pwszScope) == 0x30, "_StsMsgRequestFriendSendMessage::pwszScope");
static_assert(offsetof(_StsMsgRequestFriendSendMessage, pwszMessageName) == 0x40, "_StsMsgRequestFriendSendMessage::pwszMessageName");
static_assert(offsetof(_StsMsgRequestFriendSendMessage, contents) == 0x48, "_StsMsgRequestFriendSendMessage::contents");
}  // namespace StsMsgLib

// PDB StsMsgLib::_StsMsgResponseChargeRequestStop. CliSession::completeRequestChargeStop (0x35eb0) builds it inline.
namespace StsMsgLib
{
struct _StsMsgResponseChargeRequestStop : public _StsMsgResponse
{
};
static_assert(sizeof(_StsMsgResponseChargeRequestStop) == 0x60, "sizeof _StsMsgResponseChargeRequestStop");
}  // namespace StsMsgLib

// LIFT: inlined ctor _StsMsgResponse(ECommand, unsigned int) (PDB, no own body).
inline void npInitResponse(StsMsgLib::_StsMsgResponse& msg, StsMsgLib::ECommand cmd, unsigned int txnId)
{
    msg.msgInfo.msgType = StsMsgLib::MESSAGE_TYPE_RESPONSE;
    msg.msgInfo.bComplete = false;
    msg.msgInfo.errInfo.pszErr = nullptr;
    msg.msgInfo.errInfo.nStatusCode = 0;
    msg.msgInfo.errInfo.pwszReason = nullptr;
    msg.msgInfo.errInfo.nErrorCode = 0;
    msg.msgInfo.errInfo.banInfo.nBanId = 0;
    memset(&msg.msgInfo.errInfo.banInfo.tEffectiveFrom, 0, 28);  // tEffectiveFrom .. nBanReasonCode
    msg.msgInfo.eCmd = cmd;
    msg.msgInfo.nTxnId = txnId;
}

// PDB NPGameServiceChannel (sizeof 0x40, NPChannel base, no own members).
class NPGameServiceChannel : public NPChannel
{
public:
    bool SendRequestConsumeGameToken(NPTransaction*, id128 const&, id128 const&, unsigned long);  // 0xd0220
    bool SendRequestAuthChangeMyUserNameIncomplete(NPTransaction*, id128 const&, wchar_t const*, wchar_t const*, wchar_t const*);  // 0xd0370
    bool SendRequestSlotListSlots(NPTransaction*, id128 const&, wchar_t const*);  // PDB inline (no body in the binary)
    bool SendRequestSlotGetSlot(NPTransaction*, id128 const&, id128 const&);  // 0xd03d0
    bool SendRequestSlotCreateActivitySlots(NPTransaction*, id128 const&, wchar_t const*, unsigned long long, int, wchar_t const*);  // 0xd0450
    bool SendRequestSlotSetActivitySlotData(NPTransaction*, id128 const&, id128 const&, unsigned long long);  // 0xd0560
    bool SendRequestPresenceLogin(NPTransaction*, wchar_t const*, wchar_t const*, wchar_t const*, id128 const&, unsigned long);  // 0xd0650
    bool SendRequestPresenceLogout(id128 const&);  // 0xd0800
    bool SendRequestPresenceKick(NPTransaction*, id128 const&, id128 const&, bool);  // 0xd09b0
    bool SendRequestFriendSendMessage(NPTransaction*, id128 const&, id128*, int, wchar_t const*, id128*, wchar_t const*, StsMsgLib::_StsMsgRequestFriendSendMessage::Contents const&);  // 0xd0a00
    bool SendResponseGateLogoutUser(unsigned int, int);  // 0xd0e20
    bool SendRequestChargeGetInfo(NPTransaction*, id128 const&, unsigned long);  // 0xd0e90
    bool SendRequestChargeStart(NPTransaction*, id128 const&, unsigned long, short, unsigned int);  // 0xd0fc0
    bool SendRequestChargeStop(NPTransaction*, id128 const&, unsigned long, wchar_t const*);  // 0xd1110
    bool SendRequestChargeAbandon(NPTransaction*, id128 const&, wchar_t const*);  // 0xd1230
    bool SendResponseChargeRequestStopFail(unsigned int, wchar_t const*, int);  // 0xd1310
    bool SendRequestListUserLastPresences(NPTransaction*, id128 const&);  // 0xd1390
    bool SendRequestGradeListAllGrades(NPTransaction*, id128 const&);  // 0xd1410
    bool SendRequestGradeActivateGrade(NPTransaction*, id128 const&, int, int);  // 0xd1510
    bool SendResponseGameAuctionEscrowOk(unsigned int, unsigned long long);  // 0xd1610
    bool SendResponseGameAuctionEscrowFail(unsigned int, wchar_t const*, int, unsigned long long);  // 0xd1710
    bool SendResponseGameAuctionRollbackEscrowOk(unsigned int);  // 0xd17f0
    bool SendResponseGameAuctionRollbackEscrowFail(unsigned int, wchar_t const*, int);  // 0xd1860
    bool SendResponseGameAuctionDeliveryOk(unsigned int, unsigned long long);  // 0xd18e0
    bool SendResponseGameAuctionDeliveryFail(unsigned int, wchar_t const*, int, unsigned long long);  // 0xd19e0
    bool SendRequestListUserBans(NPTransaction*, id128 const&);  // 0xd1af0
    bool SendRequestRMSInquiry(NPTransaction*, id128 const&, char*, unsigned long);  // 0xd1be0
    bool SendRequestProfileGetUserProfile(NPTransaction*, id128 const&);  // 0xd1ce0
    bool SendRequestGameTimeGetGameTime(NPTransaction*, id128 const&);  // 0xd1d60
    bool SendRequestPromotionStampListCurrentPromotions(NPTransaction*, wchar_t const*);  // 0xd1de0
    bool SendRequestPromotionStampGetPromotionPolicy(NPTransaction*, int);  // 0xd1f00
    bool SendRequestPromotionStampGetUserPromotionStatus(NPTransaction*, id128 const&, int, short, wchar_t const*);  // 0xd1f90
    bool SendRequestPromotionStampAttendPromotionSecured(NPTransaction*, id128 const&, int, short, wchar_t const*, short, long long);  // 0xd20d0
    // PDB inline methods (no RVA). DepositMileageJob.cpp defines the bodies. They are inlined in DepositMileageJob::depositReq
    // (0x4a3e0) and DepositMileageJob::depositAck (0x4aa40).
    inline bool SendRequestPresenceMessage(NPTransaction*, id128 const&, id128 const&, wchar_t const*, wchar_t const*);
    inline bool SendRequestVirtualCurrencyDeposit(NPTransaction*, id128 const&, short, long long, char*, int, long long, bool, int, char*, unsigned long, wchar_t*);
};

// PDB NPLobbyJobTransaction (sizeof 0x18, NPTransaction base). Same form as SmartCouponDaemon NPJobTransaction.
class NPLobbyJobTransaction : public NPTransaction
{
public:
    // LIFT: the constructor is not in the PDB. Expire resets the members to this state.
    NPLobbyJobTransaction() : _jobid(0), _state(-1), _task(0) {}
    virtual ~NPLobbyJobTransaction() {}  // scalar deleting destructor 0xd2240 (folded with NPTransaction)
    // LIFT: the original global operator delete(void*) (0x32b50) is empty. The callers do "delete p;" and then
    // Memory::_Manager[2]->Free(p, ...). This empty class operator delete keeps that shape (see CliSession.h).
    static void operator delete(void*) {}
    virtual int GetKind() const { return 1; }  // 0xe3ec0 (folded)
    virtual void Expire();  // 0xd2250
    NPTransaction* Set(LobbyJob*, int);  // 0xd22c0
    unsigned long long GetJobId() const { return _jobid; }  // PDB inline
    int GetJobState() const { return _state; }  // PDB inline

    unsigned long long _jobid;
    int _state;
    int _task;
};
static_assert(sizeof(NPLobbyJobTransaction) == 0x18, "sizeof NPLobbyJobTransaction");
static_assert(offsetof(NPLobbyJobTransaction, _jobid) == 0x08, "NPLobbyJobTransaction::_jobid");
static_assert(offsetof(NPLobbyJobTransaction, _task) == 0x14, "NPLobbyJobTransaction::_task");

// PDB NPServiceChannelManager (sizeof 0x18, NPMessageHandler base).
class NPServiceChannelManager : public NPMessageHandler
{
public:
    // LIFT: the PDB ctor has no out-of-line body. It is inline in LobbyDaemon::startNPChannel (0x9f010).
    NPServiceChannelManager() : _init(false), _gameServChannel(nullptr) {}
    bool Initialize(unsigned int, unsigned long, unsigned short, long);  // 0xcfba0
    virtual bool OnConnect(NPChannel*, bool) const;  // 0xcfdb0
    virtual bool OnClose(NPChannel*, bool) const;  // 0xcff70
    virtual bool HandleMessage(NPChannel*, StsMsgLib::_StsMsg*, void*) const;  // 0xd0100

    bool _init;
    NPGameServiceChannel* _gameServChannel;
};
static_assert(offsetof(NPServiceChannelManager, _init) == 0x8, "NPServiceChannelManager::_init");
static_assert(offsetof(NPServiceChannelManager, _gameServChannel) == 0x10, "NPServiceChannelManager::_gameServChannel");
static_assert(sizeof(NPServiceChannelManager) == 0x18, "sizeof NPServiceChannelManager");
static_assert(sizeof(NPGameServiceChannel) == 0x40, "sizeof NPGameServiceChannel");
