// NPServiceChannel.obj (LobbyDaemon PDB, 2019 + PDB).
#include <winsock2.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <new>
#include "NPServiceChannel.h"
#include "AlertSender.h"
#include "BnsCommonConfigDefinition.h"
#if defined(__clang__)
#include "crt_cpp_overload.h"  // The Wine headers do not have swprintf_s<N>. VS2010 has it.
#endif
#include "LiftStub.h"
#include "LobbyConfig.h"
#include "StringUtil.h"
#include "LobbyDaemon.h"
#include "LobbyJob.h"
#include "Memory.h"
#include "MemoryManager.h"
#include "Log.h"
#include "LobbyEvent.h"
#include "Network.h"
#include "NPLobbyMessageHandler.h"
#include "PipeConsole.h"
#include "StringUtil.h"

using namespace StsMsgLib;

// LIFT: Name of the narrow buffer used in Network.cpp (0x5c87). The original reads it at TLS +0xFA80.
extern __declspec(thread) char __ip_addr_string_a__[32];

namespace
{
wchar_t const NPSERVICECHANNEL_FILE[] = L"NPServiceChannel.cpp";

// LIFT: the request fields are _GUID* (PDB). The callers give id128 const&.
inline _GUID* npGuid(id128 const& id)
{
    return reinterpret_cast<_GUID*>(const_cast<id128*>(&id));
}

// LIFT: inlined address text (the same steps as Network::GetAddressStringW 0xd6d0, narrow only).
inline void npAddressStringA(unsigned long address, char (&out)[32])
{
    char* buffer = __ip_addr_string_a__;
    buffer[0] = 0;
    in_addr addr;
    addr.s_addr = address;
    char const* text = inet_ntoa(addr);
    if (text != nullptr)
        strcpy_s(buffer, 32, text);
    strcpy_s(out, 32, buffer);
}

// LIFT: inlined ctor _StsMsgResponse(ECommand, unsigned int) (PDB, no own body).
inline void npInitResponse(_StsMsgResponse& msg, ECommand cmd, unsigned int txnId)
{
    msg.msgInfo.msgType = MESSAGE_TYPE_RESPONSE;
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

inline void npInitRequest(_StsMsgRequest& msg, ECommand cmd)
{
    msg.msgInfo.eCmd = cmd;
    msg.msgInfo.msgType = MESSAGE_TYPE_REQUEST;
    msg.msgInfo.nTxnId = 0;
}

// LIFT: (wcslen + 1) * 2 <= 18 bytes: the code fits AppGroupCode[9].
inline bool npAppGroupCodeFits()
{
    return (wcslen(BnsCommonConfig::Config->_npGameCode) + 1) * sizeof(wchar_t) <= 9 * sizeof(wchar_t);
}
}  // namespace

// PDB StsMsgLib message types (LobbyDaemon types). All derive from the NPChannelBase.h bases.
namespace StsMsgLib
{
struct _StsMsgRequestConsumeGameToken : public _StsMsgRequest
{
    _GUID* pUserId;
    _GUID* pGameToken;
    char const* pszClientNetAddress;
};
static_assert(sizeof(_StsMsgRequestConsumeGameToken) == 0x30, "sizeof _StsMsgRequestConsumeGameToken");

struct _StsMsgRequestSlotGetSlot : public _StsMsgRequest
{
    _GUID* pUserId;
    _GUID* pSlotId;
};
static_assert(sizeof(_StsMsgRequestSlotGetSlot) == 0x28, "sizeof _StsMsgRequestSlotGetSlot");

struct _StsMsgRequestSlotCreateSlots : public _StsMsgRequest
{
    struct _SlotData
    {
        long long serviceId;
    };
    _GUID* pUserId;
    wchar_t const* pwszSlotType;
    _SlotData slotData;
    wchar_t* pwszSlotData;
    unsigned int nCount;
    wchar_t const* pwszTransactionKey;
};
static_assert(sizeof(_StsMsgRequestSlotCreateSlots) == 0x48, "sizeof _StsMsgRequestSlotCreateSlots");
static_assert(offsetof(_StsMsgRequestSlotCreateSlots, nCount) == 0x38, "_StsMsgRequestSlotCreateSlots::nCount");

struct _StsMsgRequestSlotSetData : public _StsMsgRequest
{
    _GUID* pUserId;
    _GUID* pSlotId;
    _StsMsgRequestSlotCreateSlots::_SlotData slotData;
    wchar_t* pwszSlotData;
};
static_assert(sizeof(_StsMsgRequestSlotSetData) == 0x38, "sizeof _StsMsgRequestSlotSetData");

struct _StsMsgRequestPresenceLogIn : public _StsMsgRequest
{
    char* pszLoginName;
    wchar_t const* pwszUserName;
    _GUID* pGameAccountId;
    wchar_t const* pwszAlias;
    char* pszClientNetAddress;
};
static_assert(sizeof(_StsMsgRequestPresenceLogIn) == 0x40, "sizeof _StsMsgRequestPresenceLogIn");

struct _StsMsgRequestPresenceLogOut : public _StsMsgRequest
{
    _GUID* pUserId;
};
static_assert(sizeof(_StsMsgRequestPresenceLogOut) == 0x20, "sizeof _StsMsgRequestPresenceLogOut");

struct _StsMsgRequestPresenceKick : public _StsMsgRequest
{
    _GUID* pUserId;
    _GUID* pAppId;
    bool bForce;
};
static_assert(sizeof(_StsMsgRequestPresenceKick) == 0x30, "sizeof _StsMsgRequestPresenceKick");

struct _StsMsgRequestChargeGetInfo : public _StsMsgRequest
{
    _GUID* pUserId;
    char* pszClientNetAddress;
};
static_assert(sizeof(_StsMsgRequestChargeGetInfo) == 0x28, "sizeof _StsMsgRequestChargeGetInfo");

struct _StsMsgRequestChargeStart : public _StsMsgRequest
{
    _GUID* pUserId;
    char* pszClientNetAddress;
    unsigned int nWorldCode;
    unsigned int nClientInstanceCount;
};
static_assert(sizeof(_StsMsgRequestChargeStart) == 0x30, "sizeof _StsMsgRequestChargeStart");

struct _StsMsgRequestChargeStop : public _StsMsgRequest
{
    _GUID* pUserId;
    char* pszClientNetAddress;
    wchar_t ChargeKey[65];
};
static_assert(sizeof(_StsMsgRequestChargeStop) == 0xB0, "sizeof _StsMsgRequestChargeStop");

struct _StsMsgRequestChargeAbandon : public _StsMsgRequest
{
    _GUID* pUserId;
    wchar_t ChargeKey[65];
};
static_assert(sizeof(_StsMsgRequestChargeAbandon) == 0xA8, "sizeof _StsMsgRequestChargeAbandon");

struct _StsMsgRequestGameAccountListUserLastPresences : public _StsMsgRequest
{
    _GUID* pUserId;
};
static_assert(sizeof(_StsMsgRequestGameAccountListUserLastPresences) == 0x20, "sizeof _StsMsgRequestGameAccountListUserLastPresences");

struct _StsMsgRequestGradeListAllGrades : public _StsMsgRequest
{
    _GUID* pUserId;
    int nDailyRewardInfo;
    wchar_t AppGroupCode[9];
};
static_assert(sizeof(_StsMsgRequestGradeListAllGrades) == 0x38, "sizeof _StsMsgRequestGradeListAllGrades");
static_assert(offsetof(_StsMsgRequestGradeListAllGrades, AppGroupCode) == 0x24, "_StsMsgRequestGradeListAllGrades::AppGroupCode");

struct _StsMsgRequestGradeActivateGrade : public _StsMsgRequest
{
    _GUID* pUserId;
    int nGradeId;
    int nGameGradeKey;
    wchar_t AppGroupCode[9];
};
static_assert(sizeof(_StsMsgRequestGradeActivateGrade) == 0x40, "sizeof _StsMsgRequestGradeActivateGrade");
static_assert(offsetof(_StsMsgRequestGradeActivateGrade, AppGroupCode) == 0x28, "_StsMsgRequestGradeActivateGrade::AppGroupCode");

struct _StsMsgRequestListUserBans : public _StsMsgRequest
{
    _GUID* pUserId;
    wchar_t AppGroupCode[9];
};
static_assert(sizeof(_StsMsgRequestListUserBans) == 0x38, "sizeof _StsMsgRequestListUserBans");

struct _StsMsgRequestRiskMgmtInquiry : public _StsMsgRequest
{
    _GUID* pUserId;
    char* pszEvent;
    char* pszLocation;
};
static_assert(sizeof(_StsMsgRequestRiskMgmtInquiry) == 0x30, "sizeof _StsMsgRequestRiskMgmtInquiry");

struct _StsMsgRequestProfileGetUserProfile : public _StsMsgRequest
{
    _GUID* pUserId;
};
static_assert(sizeof(_StsMsgRequestProfileGetUserProfile) == 0x20, "sizeof _StsMsgRequestProfileGetUserProfile");

struct _StsMsgRequestGameTimeGetGameTime : public _StsMsgRequest
{
    _GUID* pGameAccountId;
};
static_assert(sizeof(_StsMsgRequestGameTimeGetGameTime) == 0x20, "sizeof _StsMsgRequestGameTimeGetGameTime");

struct _StsMsgRequestPromotionStampListCurrentPromotions : public _StsMsgRequest
{
    char const* pszAppGroupCode;
    short nExcludeSuspended;
};
static_assert(sizeof(_StsMsgRequestPromotionStampListCurrentPromotions) == 0x28, "sizeof _StsMsgRequestPromotionStampListCurrentPromotions");

struct _StsMsgRequestPromotionStampGetPromotionPolicy : public _StsMsgRequest
{
    int nPromotionId;
    short nReplyType;
    short nPromotionLanguageCode;
};
static_assert(sizeof(_StsMsgRequestPromotionStampGetPromotionPolicy) == 0x20, "sizeof _StsMsgRequestPromotionStampGetPromotionPolicy");

struct _StsMsgRequestPromotionStampGetUserPromotionStatus : public _StsMsgRequest
{
    int nPromotionId;
    short nBoardType;
    _GUID* pUserId;
    char const* pszAppGroupCode;
};
static_assert(sizeof(_StsMsgRequestPromotionStampGetUserPromotionStatus) == 0x30, "sizeof _StsMsgRequestPromotionStampGetUserPromotionStatus");

struct _StsMsgRequestPromotionStampAttendPromotionSecured : public _StsMsgRequest
{
    int nPromotionId;
    short nBoardType;
    _GUID* pUserId;
    char const* pszAppGroupCode;
    int nAccumulatedPoint;
    long long tAttended;
};
static_assert(sizeof(_StsMsgRequestPromotionStampAttendPromotionSecured) == 0x40, "sizeof _StsMsgRequestPromotionStampAttendPromotionSecured");
static_assert(offsetof(_StsMsgRequestPromotionStampAttendPromotionSecured, tAttended) == 0x38, "tAttended");

struct _StsMsgRequestRegisterService : public _StsMsgRequest
{
    char const* pszProtocolName;
    char const* pszWorldCode;
    char const* pszGroupOwner;
};
static_assert(sizeof(_StsMsgRequestRegisterService) == 0x30, "sizeof _StsMsgRequestRegisterService");

struct _StsMsgResponseLogOutUser : public _StsMsgResponse
{
    enum EError
    {
        ERR_SUCCESS = 0,
        ERR_USER_NOT_ONLINE = 1,
        ERR_BAD_SERVER_DATA = 2,
    };
    EError eError;
};
static_assert(sizeof(_StsMsgResponseLogOutUser) == 0x68, "sizeof _StsMsgResponseLogOutUser");

struct _StsMsgResponseChargeRequestStop : public _StsMsgResponse
{
};
static_assert(sizeof(_StsMsgResponseChargeRequestStop) == 0x60, "sizeof _StsMsgResponseChargeRequestStop");

struct _StsMsgResponseGameAuctionEscrow : public _StsMsgResponse
{
    wchar_t const* pwszEscrowId;
};
static_assert(sizeof(_StsMsgResponseGameAuctionEscrow) == 0x68, "sizeof _StsMsgResponseGameAuctionEscrow");

struct _StsMsgResponseGameAuctionRollbackEscrow : public _StsMsgResponse
{
};
static_assert(sizeof(_StsMsgResponseGameAuctionRollbackEscrow) == 0x60, "sizeof _StsMsgResponseGameAuctionRollbackEscrow");

struct _StsMsgResponseGameAuctionDeliver : public _StsMsgResponse
{
    wchar_t const* pwszDeliveryId;
};
static_assert(sizeof(_StsMsgResponseGameAuctionDeliver) == 0x68, "sizeof _StsMsgResponseGameAuctionDeliver");

// PDB: the 3 overrides are in NPServiceChannel.obj. They fold with the _StsMsgRequest bodies (0xcfa80, 0x2bc0, 0x2bd0).
ECommand _StsMsgResponse::GetCommand() { return msgInfo.eCmd; }
unsigned int _StsMsgResponse::GetTransactionId() { return msgInfo.nTxnId; }
EMessageType _StsMsgResponse::GetMessageType() { return msgInfo.msgType; }
}  // namespace StsMsgLib

// 0xcfac0
void NPGameServiceChannelCmdDispatcher(unsigned int nTxnId, ECommand& eCmd)
{
    NPGameServiceChannel* gameServChannel = LobbyDaemon::_instance->_npServchmgr->_gameServChannel;
    if (gameServChannel == nullptr)
    {
        Log::Write(Log::LT_ERROR, NPSERVICECHANNEL_FILE, 38,
                   L"[np], [np-game-service-channel], dispatch command fail; no channel exists, txn-id:%u", nTxnId);
        return;
    }
    NPTransactionRegistry* tranRegistry = gameServChannel->_tranRegistry;
    if (tranRegistry == nullptr)
    {
        Log::Write(Log::LT_ERROR, NPSERVICECHANNEL_FILE, 44,
                   L"== CRASH == [np], [np-gameservch-tran-reg], not ready to dispatch command");
        AlertSender::Write(NPSERVICECHANNEL_FILE, 44,
                           L"== CRASH == [np], [np-gameservch-tran-reg], not ready to dispatch command");
        return;
    }
    NPTransactionRegistry::Item item;
    if (!tranRegistry->Find(nTxnId, &item))
        Log::Write(Log::LT_ERROR, NPSERVICECHANNEL_FILE, 50,
                   L"[np], [np-gameservch-tran-reg], dispatch command fail; not found, txn-id:%u", nTxnId);
    else
        eCmd = item.cmd;
}

// 0xcfba0
// LIFT: the PDB has no register for portId and timeout. LTCG put the constants of the caller
// LobbyDaemon::startNPChannel (0x9f010: port id 2, timeout 5) into the body. The source keeps the parameters.
bool NPServiceChannelManager::Initialize(unsigned int portId, unsigned long ip, unsigned short portNo, long timeout)
{
    if (_init)
    {
        Log::Write(Log::LT_ERROR, NPSERVICECHANNEL_FILE, 80, L"[np-servch-mgr], initialize fail; already initailized");
        return false;
    }
    // LIFT: inlined PipeConsole::SetInvalidInfo(L"NP game-service disconnected", true), as in the original.
    PipeConsole* const pipeConsole = LobbyDaemon::_instance->pipeConsole;
    if (pipeConsole != nullptr)
    {
        pipeConsole->_lock.Enter();
        PipeConsole::ItemNode* node = pipeConsole->_invalid._head._next;
        while (node != &pipeConsole->_invalid._tail)
        {
            if (wcscmp(node->_key, L"NP game-service disconnected") == 0)
                break;
            node = node->_next;
        }
        if (node == &pipeConsole->_invalid._tail || node == nullptr)
            PipeConsole::addNode(pipeConsole->_invalid, L"NP game-service disconnected", L"");
        pipeConsole->_lock.Leave();
    }
    void* mem = Memory::_Manager[2]->Alloc(sizeof(NPGameServiceChannel), NPSERVICECHANNEL_FILE, 86);
    _gameServChannel = mem ? new (mem) NPGameServiceChannel() : nullptr;
    if (!_gameServChannel->Initialize(this, NPGameServiceChannelCmdDispatcher))
    {
        Log::Write(Log::LT_ERROR, NPSERVICECHANNEL_FILE, 89,
                   L"[np-servch-mgr], initialize fail; init game-service channel fail");
        return false;
    }
    if (!_gameServChannel->Connect(0, portId, ip, portNo, timeout, true))
    {
        Log::Write(Log::LT_ERROR, NPSERVICECHANNEL_FILE, 94,
                   L"[np-servch-mgr], initialize fail; connect game service channel fail");
        return false;
    }
    _init = true;
    Log::Write(Log::LT_DEBUG, NPSERVICECHANNEL_FILE, 100,
               L"[np-servch-mgr], initialize ok, port-id:%d, ip:%s, port:%d, timeout:%d(sec)", portId,
               Network::GetAddressStringW(ip), portNo, timeout);
    return true;
}

// 0xcfdb0
bool NPServiceChannelManager::OnConnect(NPChannel* channel, bool firstConnected) const
{
    unsigned long long id =
        (channel != nullptr && channel->_rawChannel != nullptr) ? channel->_rawChannel->GetId() : 0;
    Log::Write(Log::LT_NOTICE, NPSERVICECHANNEL_FILE, 116, L"[np], game-serivce channel connected, channel-id:%I64d", id);
    if (firstConnected)
    {
        void* event = LobbyDaemon::_instance->_npInitialConnectEvent.Event;
        if (event == nullptr || !SetEvent(event))
        {
            Log::Write(Log::LT_ERROR, NPSERVICECHANNEL_FILE, 120, L"[np], set lobby-np initial connect event fail");
            return false;
        }
    }
    if (LobbyDaemon::_instance->_config->_enableAuctionEscrowService)
    {
        _StsMsgRequestRegisterService msg;
        npInitRequest(msg, COMMAND_SRV_GATE_REGISTER_SERVICE);
        msg.pszProtocolName = "Srv2GameAuction";
        msg.pszWorldCode = nullptr;
        msg.pszGroupOwner = nullptr;
        if (!channel->SendMsg(&msg, true, nullptr))
        {
            Log::Write(Log::LT_ERROR, NPSERVICECHANNEL_FILE, 129, L"[np], send register Srv2Auction service fail");
            return false;
        }
    }
    // LIFT: inlined PipeConsole::SetInvalidInfo(L"NP game-service disconnected", false), as in the original.
    PipeConsole* const pipeConsole = LobbyDaemon::_instance->pipeConsole;
    if (pipeConsole != nullptr)
    {
        pipeConsole->_lock.Enter();
        PipeConsole::ItemNode* node = pipeConsole->_invalid._head._next;
        while (node != &pipeConsole->_invalid._tail)
        {
            if (wcscmp(node->_key, L"NP game-service disconnected") == 0)
                break;
            node = node->_next;
        }
        if (node != &pipeConsole->_invalid._tail && node != nullptr)
        {
            node->_next->_prev = node->_prev;
            node->_prev->_next = node->_next;
            Memory::_Manager[2]->Free(node, L"source\\PipeConsole.cpp", 837);
        }
        pipeConsole->_lock.Leave();
    }
    return true;
}

// 0xcff70
bool NPServiceChannelManager::OnClose(NPChannel* channel, bool) const
{
    unsigned long long id =
        (channel != nullptr && channel->_rawChannel != nullptr) ? channel->_rawChannel->GetId() : 0;
    Log::Write(Log::LT_ERROR, NPSERVICECHANNEL_FILE, 141, L"[np], game-service channel closed, channel-id:%I64d", id);
    if (channel->_tranRegistry != nullptr)
    {
        std::vector<void*, StlAllocator<void*, 2> > tranlist;
        channel->_tranRegistry->ReleaseAll(tranlist);
        for (auto it = tranlist.begin(); it != tranlist.end(); ++it)
        {
            NPTransaction* tran = static_cast<NPTransaction*>(*it);
            if (tran != nullptr)
            {
                tran->Expire();
                tran->~NPTransaction();
                Memory::_Manager[2]->Free(tran, NPSERVICECHANNEL_FILE, 152);
            }
        }
    }
    // LIFT: inlined PipeConsole::SetInvalidInfo(L"NP game-service disconnected", true), as in the original.
    PipeConsole* const pipeConsole = LobbyDaemon::_instance->pipeConsole;
    if (pipeConsole != nullptr)
    {
        pipeConsole->_lock.Enter();
        PipeConsole::ItemNode* node = pipeConsole->_invalid._head._next;
        while (node != &pipeConsole->_invalid._tail)
        {
            if (wcscmp(node->_key, L"NP game-service disconnected") == 0)
                break;
            node = node->_next;
        }
        if (node == &pipeConsole->_invalid._tail || node == nullptr)
            PipeConsole::addNode(pipeConsole->_invalid, L"NP game-service disconnected", L"");
        pipeConsole->_lock.Leave();
    }
    return true;
}

// 0xd0100
bool NPServiceChannelManager::HandleMessage(NPChannel* channel, _StsMsg* msg, void* context) const
{
    if (channel == nullptr || msg == nullptr)
        return false;
    bool (*handler)(NPChannel*, _StsMsg*, NPTransaction*) = DispatchNPLobbyMessageHandler(msg->GetCommand());
    if (handler == nullptr)
    {
        channel->_sts->ReleaseStsMsg(msg);
        return false;
    }
    void* mem = Memory::_Manager[2]->Alloc(sizeof(NPLobbyMessageHandleEvent), NPSERVICECHANNEL_FILE, 173);
    NPLobbyMessageHandleEvent* event =
        mem ? new (mem) NPLobbyMessageHandleEvent(channel, msg, static_cast<NPTransaction*>(context), handler) : nullptr;
    PostQueuedCompletionStatus(Network::iocpHandle(), 0, reinterpret_cast<ULONG_PTR>(event), nullptr);
    return true;
}

// 0xd0220
bool NPGameServiceChannel::SendRequestConsumeGameToken(NPTransaction* t, id128 const& portalAccountId,
                                                       id128 const& gameToken, unsigned long clientNetAddr)
{
    if (t == nullptr)
    {
        Log::Write(Log::LT_ERROR, NPSERVICECHANNEL_FILE, 192,
                   L"== CRASH == [np], send request consume game token fail; null transaction");
        AlertSender::Write(NPSERVICECHANNEL_FILE, 192,
                           L"== CRASH == [np], send request consume game token fail; null transaction");
        return false;
    }
    char clientNetAddrA[32] = {0};
    npAddressStringA(clientNetAddr, clientNetAddrA);
    _StsMsgRequestConsumeGameToken msg;
    npInitRequest(msg, COMMAND_SRV_AUTH_CONSUME_GAME_TOKEN);
    msg.pUserId = npGuid(portalAccountId);
    msg.pGameToken = npGuid(gameToken);
    msg.pszClientNetAddress = clientNetAddrA;
    return SendMsg(&msg, true, t);
}

// 0xd0370
// LIFT: LTCG folds the constant password hash L"dummy" (the only caller passes it) into the body. The PDB signature
// keeps the parameter. The body uses the constant, as the binary does.
bool NPGameServiceChannel::SendRequestAuthChangeMyUserNameIncomplete(NPTransaction* t, id128 const& portalAccountId, wchar_t const* userNameOld, wchar_t const* userNameNew, wchar_t const* passwordHash)
{
    (void)passwordHash;
    StsMsgLib::_StsMsgRequestAuthChangeMyUserNameIncomplete msg;
    msg.msgInfo.eCmd = StsMsgLib::COMMAND_SRV_AUTH_CHANGE_MY_USER_NAME_INCOMPLETE;
    msg.msgInfo.msgType = StsMsgLib::MESSAGE_TYPE_REQUEST;
    msg.msgInfo.nTxnId = 0;
    msg.pUserId = &portalAccountId;
    msg.pwszUserNameOld = userNameOld;
    msg.pwszUserNameNew = userNameNew;
    msg.bSkipCheckPassword = true;
    msg.pwszPasswordHash = L"dummy";
    return SendMsg(&msg, true, t);
}

namespace StsMsgLib
{
// PDB StsMsgLib::_StsMsgRequestSlotListSlots (sizeof 0x28).
struct _StsMsgRequestSlotListSlots : public _StsMsgRequest
{
    void* pUserId;  // PDB _GUID*
    wchar_t* pwszSlotType;
};
static_assert(sizeof(_StsMsgRequestSlotListSlots) == 0x28, "sizeof StsMsgLib::_StsMsgRequestSlotListSlots");
static_assert(offsetof(_StsMsgRequestSlotListSlots, pUserId) == 0x18, "_StsMsgRequestSlotListSlots::pUserId");
static_assert(offsetof(_StsMsgRequestSlotListSlots, pwszSlotType) == 0x20, "_StsMsgRequestSlotListSlots::pwszSlotType");
}  // namespace StsMsgLib

// PDB inline: the binary has no body. StartCliSessionWnpTokenJob::listSlotsReq (0xd47e0) has it inline.
// LIFT: defined here, not in the header. LTCG inlines it into its only caller.
bool NPGameServiceChannel::SendRequestSlotListSlots(NPTransaction* t, id128 const& userId, wchar_t const* slotType)
{
    if (t == nullptr)
    {
        Log::Write(Log::LT_ERROR, L"NPServiceChannel.cpp", 246,
                   L"== CRASH == [np], send request slot list slots fail; null transaction");
        AlertSender::Write(L"NPServiceChannel.cpp", 246,
                           L"== CRASH == [np], send request slot list slots fail; null transaction");
        return false;
    }
    StsMsgLib::_StsMsgRequestSlotListSlots msg;
    msg.msgInfo.eCmd = StsMsgLib::COMMAND_COMMON_SLOT_LIST_SLOTS;
    msg.msgInfo.msgType = StsMsgLib::MESSAGE_TYPE_REQUEST;
    msg.msgInfo.nTxnId = 0;
    msg.pUserId = const_cast<id128*>(&userId);
    msg.pwszSlotType = const_cast<wchar_t*>(slotType);
    return SendMsg(&msg, true, t);
}

// 0xd03d0
bool NPGameServiceChannel::SendRequestSlotGetSlot(NPTransaction* t, id128 const& portalAccountId, id128 const& slotId)
{
    if (t == nullptr)
    {
        Log::Write(Log::LT_ERROR, NPSERVICECHANNEL_FILE, 232,
                   L"== CRASH == [np], send request slot get slot fail; null transaction");
        AlertSender::Write(NPSERVICECHANNEL_FILE, 232,
                           L"== CRASH == [np], send request slot get slot fail; null transaction");
        return false;
    }
    _StsMsgRequestSlotGetSlot msg;
    npInitRequest(msg, COMMAND_COMMON_SLOT_GET_SLOT);
    msg.pUserId = npGuid(portalAccountId);
    msg.pSlotId = npGuid(slotId);
    return SendMsg(&msg, true, t);
}

// 0xd0450
// LIFT: LTCG removed the unused slotType and count arguments. The original sends L"activity" and 1.
bool NPGameServiceChannel::SendRequestSlotCreateActivitySlots(NPTransaction* t, id128 const& portalAccountId,
                                                              wchar_t const*, unsigned long long activityStatus, int,
                                                              wchar_t const* transactionKey)
{
    if (t == nullptr)
    {
        Log::Write(Log::LT_ERROR, NPSERVICECHANNEL_FILE, 277,
                   L"== CRASH == [np], send request slot create slots fail; null transaction");
        AlertSender::Write(NPSERVICECHANNEL_FILE, 277,
                           L"== CRASH == [np], send request slot create slots fail; null transaction");
        return false;
    }
    wchar_t slotData[33];
    swprintf_s(slotData, L"0x%.16I64X", activityStatus);
    _StsMsgRequestSlotCreateSlots msg;
    npInitRequest(msg, COMMAND_SRV_SLOT_CREATE_SLOTS);
    msg.pUserId = npGuid(portalAccountId);
    msg.pwszSlotType = L"activity";
    msg.slotData.serviceId = 0;
    msg.pwszSlotData = slotData;
    msg.nCount = 1;
    msg.pwszTransactionKey = transactionKey;
    return SendMsg(&msg, true, t);
}

// 0xd0560
bool NPGameServiceChannel::SendRequestSlotSetActivitySlotData(NPTransaction* t, id128 const& portalAccountId,
                                                              id128 const& slotId, unsigned long long activityStatus)
{
    if (t == nullptr)
    {
        Log::Write(Log::LT_ERROR, NPSERVICECHANNEL_FILE, 297,
                   L"== CRASH == [np], send request slot set data fail; null transaction");
        AlertSender::Write(NPSERVICECHANNEL_FILE, 297,
                           L"== CRASH == [np], send request slot set data fail; null transaction");
        return false;
    }
    wchar_t slotData[33];
    swprintf_s(slotData, L"0x%.16I64X", activityStatus);
    _StsMsgRequestSlotSetData msg;
    npInitRequest(msg, COMMAND_SRV_SLOT_SET_DATA);
    msg.pUserId = npGuid(portalAccountId);
    msg.pSlotId = npGuid(slotId);
    msg.slotData.serviceId = 0;
    msg.pwszSlotData = slotData;
    return SendMsg(&msg, true, t);
}

// 0xd0650
// LIFT: LTCG removed the unused gameAlias argument. The original sends an empty alias.
bool NPGameServiceChannel::SendRequestPresenceLogin(NPTransaction* t, wchar_t const* loginName, wchar_t const* userName,
                                                    wchar_t const*, id128 const& gameAccountId,
                                                    unsigned long clientIpaddr)
{
    if (t == nullptr)
    {
        Log::Write(Log::LT_ERROR, NPSERVICECHANNEL_FILE, 315,
                   L"== CRASH == [np], send request presence login fail; null transaction");
        AlertSender::Write(NPSERVICECHANNEL_FILE, 315,
                           L"== CRASH == [np], send request presence login fail; null transaction");
        return false;
    }
    char clientNetAddrA[32] = {0};
    char loginNameA[65] = {0};
    WideCharToMultiByte(CP_ACP, 0, loginName, -1, loginNameA, 64, nullptr, nullptr);
    npAddressStringA(clientIpaddr, clientNetAddrA);
    _StsMsgRequestPresenceLogIn msg;
    npInitRequest(msg, COMMAND_SRV_PRES_LOGIN);
    msg.pszLoginName = loginNameA;
    msg.pwszUserName = userName;
    msg.pGameAccountId = npGuid(gameAccountId);
    msg.pwszAlias = L"";
    msg.pszClientNetAddress = clientNetAddrA;
    return SendMsg(&msg, true, t);
}

// 0xd0800
bool NPGameServiceChannel::SendRequestPresenceLogout(id128 const& portalAccountId)
{
    _StsMsgRequestPresenceLogOut msg;
    npInitRequest(msg, COMMAND_SRV_PRES_LOGOUT);
    msg.pUserId = npGuid(portalAccountId);
    bool sent = SendMsg(&msg, true, nullptr);
    if (sent)
    {
        Log::Write(Log::LT_DEBUG, NPSERVICECHANNEL_FILE, 361,
                   L"[np], presence logout sent, user-id:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X, txn-id:%u",
                   portalAccountId.guid.id1, portalAccountId.guid.id2, portalAccountId.guid.id3,
                   portalAccountId.guid.id4[0], portalAccountId.guid.id4[1], portalAccountId.guid.id4[2],
                   portalAccountId.guid.id4[3], portalAccountId.guid.id4[4], portalAccountId.guid.id4[5],
                   portalAccountId.guid.id4[6], portalAccountId.guid.id4[7], msg.msgInfo.nTxnId);
    }
    else
    {
        Log::Write(Log::LT_ERROR, NPSERVICECHANNEL_FILE, 363,
                   L"[np], presence logout send fail, user-id:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X",
                   portalAccountId.guid.id1, portalAccountId.guid.id2, portalAccountId.guid.id3,
                   portalAccountId.guid.id4[0], portalAccountId.guid.id4[1], portalAccountId.guid.id4[2],
                   portalAccountId.guid.id4[3], portalAccountId.guid.id4[4], portalAccountId.guid.id4[5],
                   portalAccountId.guid.id4[6], portalAccountId.guid.id4[7]);
    }
    return sent;
}

// 0xd09b0
// LIFT: LTCG removed the unused t argument. The original sends with no transaction.
bool NPGameServiceChannel::SendRequestPresenceKick(NPTransaction*, id128 const& portalAccountId,
                                                   id128 const& targetAppId, bool force)
{
    _StsMsgRequestPresenceKick msg;
    npInitRequest(msg, COMMAND_SRV_PRES_KICK);
    msg.pUserId = npGuid(portalAccountId);
    msg.pAppId = npGuid(targetAppId);
    msg.bForce = force;
    return SendMsg(&msg, true, nullptr);
}

// 0xd0a00
// LIFT: the only caller (RenameCharacterJob::sendFriendMessageToNP 0x6bc50) passes a null transaction, the scope
// L"all" and a null scope id. LTCG folds these constants into the body. The body uses the parameters.
bool NPGameServiceChannel::SendRequestFriendSendMessage(NPTransaction* t, id128 const& portalAccountId, id128* destAppIdList, int destAppIdCount, wchar_t const* scope, id128* scopeId, wchar_t const* messageName, StsMsgLib::_StsMsgRequestFriendSendMessage::Contents const& contents)
{
    StsMsgLib::_StsMsgRequestFriendSendMessage msg;
    msg.msgInfo.eCmd = StsMsgLib::COMMAND_SRV_FRIEND_SEND_MESSAGE;
    msg.msgInfo.msgType = StsMsgLib::MESSAGE_TYPE_REQUEST;
    msg.msgInfo.nTxnId = 0;
    msg.pAppIds = nullptr;
    msg.nAppIdCount = 0;
    msg.pwszScope = nullptr;
    msg.pScopeId = nullptr;
    msg.pwszMessageName = nullptr;
    msg.contents.pFields = nullptr;
    msg.contents.nFieldCount = 0;
    msg.pUserId = &portalAccountId;
    if (destAppIdList != nullptr && destAppIdCount > 0)
    {
        msg.pAppIds = static_cast<id128*>(Memory::_Manager[2]->AllocZero(sizeof(id128) * destAppIdCount, L"NPServiceChannel.cpp", 405));
        msg.nAppIdCount = destAppIdCount;
        for (int i = 0; i < destAppIdCount; ++i)
            msg.pAppIds[i].guid = destAppIdList[i].guid;
    }
    msg.pwszScope = scope;
    msg.pScopeId = scopeId;
    msg.pwszMessageName = messageName;
    msg.contents = contents;
    bool const result = SendMsg(&msg, true, t);
    if (msg.pAppIds != nullptr)
        Memory::_Manager[2]->Free(msg.pAppIds, L"NPServiceChannel.cpp", 418);
    return result;
}

// 0xd0e20
bool NPGameServiceChannel::SendResponseGateLogoutUser(unsigned int txnid, int errcode)
{
    _StsMsgResponseLogOutUser msg;
    npInitResponse(msg, COMMAND_SRV_PRES_LOGOUT_USER, txnid);
    msg.eError = static_cast<_StsMsgResponseLogOutUser::EError>(errcode);
    return SendMsg(&msg, false, nullptr);
}

// 0xd0e90
bool NPGameServiceChannel::SendRequestChargeGetInfo(NPTransaction* t, id128 const& portalAccountId,
                                                    unsigned long clientNetAddr)
{
    if (t == nullptr)
    {
        Log::Write(Log::LT_ERROR, NPSERVICECHANNEL_FILE, 435,
                   L"== CRASH == [np], send request charge get info fail; null transaction");
        AlertSender::Write(NPSERVICECHANNEL_FILE, 435,
                           L"== CRASH == [np], send request charge get info fail; null transaction");
        return false;
    }
    char clientNetAddrA[32] = {0};
    npAddressStringA(clientNetAddr, clientNetAddrA);
    _StsMsgRequestChargeGetInfo msg;
    npInitRequest(msg, COMMAND_SRV_CHARGE_GET_INFO);
    msg.pUserId = npGuid(portalAccountId);
    msg.pszClientNetAddress = clientNetAddrA;
    return SendMsg(&msg, true, t);
}

// 0xd0fc0
// LIFT: LTCG removed the unused clientInstanceCount argument. The original sends 1.
bool NPGameServiceChannel::SendRequestChargeStart(NPTransaction* t, id128 const& portalAccountId,
                                                  unsigned long clientNetAddr, short wid, unsigned int)
{
    if (t == nullptr)
    {
        Log::Write(Log::LT_ERROR, NPSERVICECHANNEL_FILE, 453,
                   L"== CRASH == [np], send request charge start fail; null transaction");
        AlertSender::Write(NPSERVICECHANNEL_FILE, 453,
                           L"== CRASH == [np], send request charge start fail; null transaction");
        return false;
    }
    char clientNetAddrA[32] = {0};
    npAddressStringA(clientNetAddr, clientNetAddrA);
    _StsMsgRequestChargeStart msg;
    npInitRequest(msg, COMMAND_SRV_CHARGE_START);
    msg.pUserId = npGuid(portalAccountId);
    msg.pszClientNetAddress = clientNetAddrA;
    msg.nWorldCode = wid;
    msg.nClientInstanceCount = 1;
    return SendMsg(&msg, true, t);
}

// 0xd1110
bool NPGameServiceChannel::SendRequestChargeStop(NPTransaction* t, id128 const& portalAccountId,
                                                 unsigned long clientNetAddr, wchar_t const* chargeKey)
{
    char clientNetAddrA[32] = {0};
    npAddressStringA(clientNetAddr, clientNetAddrA);
    _StsMsgRequestChargeStop msg;
    npInitRequest(msg, COMMAND_SRV_CHARGE_STOP);
    msg.pUserId = npGuid(portalAccountId);
    msg.pszClientNetAddress = clientNetAddrA;
    msg.ChargeKey[0] = 0;
    wcscpy_s(msg.ChargeKey, 65, chargeKey);
    return SendMsg(&msg, true, t);
}

// 0xd1230
bool NPGameServiceChannel::SendRequestChargeAbandon(NPTransaction* t, id128 const& portalAccountId,
                                                    wchar_t const* chargeKey)
{
    if (t == nullptr)
    {
        Log::Write(Log::LT_ERROR, NPSERVICECHANNEL_FILE, 485,
                   L"== CRASH == [np], send request charge abandon fail; null transaction");
        AlertSender::Write(NPSERVICECHANNEL_FILE, 485,
                           L"== CRASH == [np], send request charge abandon fail; null transaction");
        return false;
    }
    _StsMsgRequestChargeAbandon msg;
    npInitRequest(msg, COMMAND_SRV_CHARGE_ABANDON);
    msg.pUserId = npGuid(portalAccountId);
    msg.ChargeKey[0] = 0;
    wcscpy_s(msg.ChargeKey, 65, chargeKey);
    return SendMsg(&msg, true, t);
}

// 0xd1310
bool NPGameServiceChannel::SendResponseChargeRequestStopFail(unsigned int txnid, wchar_t const* reason, int netError)
{
    _StsMsgResponseChargeRequestStop msg;
    npInitResponse(msg, COMMAND_SRV_CHARGE_REQUEST_STOP, txnid);
    msg.msgInfo.errInfo.nStatusCode = 400;
    msg.msgInfo.errInfo.pwszReason = reason != nullptr ? reason : nullptr;
    msg.msgInfo.errInfo.nErrorCode = netError;
    return SendMsg(&msg, false, nullptr);
}

// 0xd1390
bool NPGameServiceChannel::SendRequestListUserLastPresences(NPTransaction* t, id128 const& portalAccountId)
{
    if (t == nullptr)
    {
        Log::Write(Log::LT_ERROR, NPSERVICECHANNEL_FILE, 540,
                   L"== CRASH == [np], send request list user last presences fail; null transaction");
        AlertSender::Write(NPSERVICECHANNEL_FILE, 540,
                           L"== CRASH == [np], send request list user last presences fail; null transaction");
        return false;
    }
    _StsMsgRequestGameAccountListUserLastPresences msg;
    npInitRequest(msg, COMMAND_SRV_GAMEACCOUNT_LIST_USER_LAST_PRESENCES);
    msg.pUserId = npGuid(portalAccountId);
    return SendMsg(&msg, true, t);
}

// 0xd1410
bool NPGameServiceChannel::SendRequestGradeListAllGrades(NPTransaction* t, id128 const& portalAccountId)
{
    _StsMsgRequestGradeListAllGrades msg;
    npInitRequest(msg, COMMAND_COMMON_GRADE_LIST_ALL_GRADES);
    msg.pUserId = npGuid(portalAccountId);
    msg.nDailyRewardInfo = 0;
    msg.AppGroupCode[0] = 0;
    if (!npAppGroupCodeFits())
    {
        Log::Write(Log::LT_ERROR, NPSERVICECHANNEL_FILE, 567,
                   L"== CRASH == [np], send request grade list all grades; insufficient app-group-code buffer");
        AlertSender::Write(NPSERVICECHANNEL_FILE, 567,
                           L"== CRASH == [np], send request grade list all grades; insufficient app-group-code buffer");
        return false;
    }
    wcscpy_s(msg.AppGroupCode, 9, BnsCommonConfig::Config->_npGameCode);
    return SendMsg(&msg, true, t);
}

// 0xd1510
bool NPGameServiceChannel::SendRequestGradeActivateGrade(NPTransaction* t, id128 const& portalAccountId, int gradeId,
                                                         int gameGradeKey)
{
    _StsMsgRequestGradeActivateGrade msg;
    npInitRequest(msg, COMMAND_SRV_GRADE_ACTIVATE_GRADE);
    msg.pUserId = npGuid(portalAccountId);
    msg.nGradeId = 0;
    msg.nGameGradeKey = 0;
    msg.AppGroupCode[0] = 0;
    if (gameGradeKey > 0)
    {
        msg.nGameGradeKey = gameGradeKey;
        if (!npAppGroupCodeFits())
        {
            Log::Write(Log::LT_ERROR, NPSERVICECHANNEL_FILE, 606,
                       L"== CRASH == [np], send request activate grades; insufficient app-group-code buffer");
            AlertSender::Write(NPSERVICECHANNEL_FILE, 606,
                               L"== CRASH == [np], send request activate grades; insufficient app-group-code buffer");
            return false;
        }
        wcscpy_s(msg.AppGroupCode, 9, BnsCommonConfig::Config->_npGameCode);
    }
    else
    {
        msg.nGradeId = gradeId;
    }
    return SendMsg(&msg, true, t);
}

// 0xd1610
bool NPGameServiceChannel::SendResponseGameAuctionEscrowOk(unsigned int txnid, unsigned long long escrowId)
{
    wchar_t escrowIdStr[51] = {0};
    _StsMsgResponseGameAuctionEscrow msg;
    npInitResponse(msg, COMMAND_SRV_AUCTION_ESCROW, txnid);
    _ui64tow_s(escrowId, escrowIdStr, 51, 10);
    msg.pwszEscrowId = escrowIdStr;
    return SendMsg(&msg, false, nullptr);
}

// 0xd1710
// LIFT: the original clears escrowIdStr but does not use it on the fail path.
bool NPGameServiceChannel::SendResponseGameAuctionEscrowFail(unsigned int txnid, wchar_t const* reason, int netError,
                                                             unsigned long long)
{
    wchar_t escrowIdStr[51] = {0};
    (void)escrowIdStr;
    _StsMsgResponseGameAuctionEscrow msg;
    npInitResponse(msg, COMMAND_SRV_AUCTION_ESCROW, txnid);
    msg.pwszEscrowId = nullptr;
    msg.msgInfo.errInfo.nStatusCode = 400;
    msg.msgInfo.errInfo.pwszReason = reason != nullptr ? reason : nullptr;
    msg.msgInfo.errInfo.nErrorCode = netError;
    return SendMsg(&msg, false, nullptr);
}

// 0xd17f0
bool NPGameServiceChannel::SendResponseGameAuctionRollbackEscrowOk(unsigned int txnid)
{
    _StsMsgResponseGameAuctionRollbackEscrow msg;
    npInitResponse(msg, COMMAND_SRV_AUCTION_ROLLBACK_ESCROW, txnid);
    return SendMsg(&msg, false, nullptr);
}

// 0xd1860
bool NPGameServiceChannel::SendResponseGameAuctionRollbackEscrowFail(unsigned int txnid, wchar_t const* reason,
                                                                     int netError)
{
    _StsMsgResponseGameAuctionRollbackEscrow msg;
    npInitResponse(msg, COMMAND_SRV_AUCTION_ROLLBACK_ESCROW, txnid);
    msg.msgInfo.errInfo.nStatusCode = 400;
    msg.msgInfo.errInfo.pwszReason = reason != nullptr ? reason : nullptr;
    msg.msgInfo.errInfo.nErrorCode = netError;
    return SendMsg(&msg, false, nullptr);
}

// 0xd18e0
bool NPGameServiceChannel::SendResponseGameAuctionDeliveryOk(unsigned int txnid, unsigned long long postId)
{
    wchar_t deliveryId[51] = {0};
    _StsMsgResponseGameAuctionDeliver msg;
    npInitResponse(msg, COMMAND_SRV_AUCTION_DELIVER, txnid);
    _ui64tow_s(postId, deliveryId, 51, 10);
    msg.pwszDeliveryId = deliveryId;
    return SendMsg(&msg, false, nullptr);
}

// 0xd19e0
bool NPGameServiceChannel::SendResponseGameAuctionDeliveryFail(unsigned int txnid, wchar_t const* reason, int netError,
                                                               unsigned long long postId)
{
    wchar_t deliveryId[51] = {0};
    _StsMsgResponseGameAuctionDeliver msg;
    npInitResponse(msg, COMMAND_SRV_AUCTION_DELIVER, txnid);
    msg.pwszDeliveryId = nullptr;
    msg.msgInfo.errInfo.nStatusCode = 400;
    msg.msgInfo.errInfo.pwszReason = reason != nullptr ? reason : nullptr;
    msg.msgInfo.errInfo.nErrorCode = netError;
    if (postId != 0)
    {
        _ui64tow_s(postId, deliveryId, 51, 10);
        msg.pwszDeliveryId = deliveryId;
    }
    return SendMsg(&msg, false, nullptr);
}

// 0xd1af0
bool NPGameServiceChannel::SendRequestListUserBans(NPTransaction* t, id128 const& portalAccountId)
{
    _StsMsgRequestListUserBans msg;
    npInitRequest(msg, COMMAND_SRV_CONTENTBAN_LIST_USER_BANS);
    msg.pUserId = npGuid(portalAccountId);
    msg.AppGroupCode[0] = 0;
    if (!npAppGroupCodeFits())
    {
        Log::Write(Log::LT_ERROR, NPSERVICECHANNEL_FILE, 731,
                   L"== CRASH == [np], send request list-user-bans fail; insufficient app-group-code buffer");
        AlertSender::Write(NPSERVICECHANNEL_FILE, 731,
                           L"== CRASH == [np], send request list-user-bans fail; insufficient app-group-code buffer");
        return false;
    }
    wcscpy_s(msg.AppGroupCode, 9, BnsCommonConfig::Config->_npGameCode);
    return SendMsg(&msg, true, t);
}

// 0xd1be0
// LIFT: LTCG removed the unused requestEvent argument. The original sends "bns:trade".
bool NPGameServiceChannel::SendRequestRMSInquiry(NPTransaction* t, id128 const& portalAccountId, char*,
                                                 unsigned long clientNetAddress)
{
    _StsMsgRequestRiskMgmtInquiry msg;
    npInitRequest(msg, COMMAND_SRV_RISKMGMT_INQUIRY);
    msg.pUserId = npGuid(portalAccountId);
    msg.pszEvent = "bns:trade";
    msg.pszLocation = nullptr;
    char clientNetAddrA[32];
    if (clientNetAddress != 0)
    {
        memset(clientNetAddrA, 0, sizeof(clientNetAddrA));
        npAddressStringA(clientNetAddress, clientNetAddrA);
        msg.pszLocation = clientNetAddrA;
    }
    return SendMsg(&msg, true, t);
}

// 0xd1ce0
bool NPGameServiceChannel::SendRequestProfileGetUserProfile(NPTransaction* t, id128 const& userId)
{
    if (t == nullptr)
    {
        Log::Write(Log::LT_ERROR, NPSERVICECHANNEL_FILE, 785,
                   L"== CRASH == [np], send request profile get user profile fail; null transaction");
        AlertSender::Write(NPSERVICECHANNEL_FILE, 785,
                           L"== CRASH == [np], send request profile get user profile fail; null transaction");
        return false;
    }
    _StsMsgRequestProfileGetUserProfile msg;
    npInitRequest(msg, COMMAND_SRV_PROFILE_GET_USER_PROFILE);
    msg.pUserId = npGuid(userId);
    return SendMsg(&msg, true, t);
}

// 0xd1d60
bool NPGameServiceChannel::SendRequestGameTimeGetGameTime(NPTransaction* t, id128 const& gameAccountId)
{
    if (t == nullptr)
    {
        Log::Write(Log::LT_ERROR, NPSERVICECHANNEL_FILE, 798,
                   L"== CRASH == [np], send request gametime get game time fail; null transaction");
        AlertSender::Write(NPSERVICECHANNEL_FILE, 798,
                           L"== CRASH == [np], send request gametime get game time fail; null transaction");
        return false;
    }
    _StsMsgRequestGameTimeGetGameTime msg;
    npInitRequest(msg, COMMAND_SRV_GAMETIME_GET_GAME_TIME);
    msg.pGameAccountId = npGuid(gameAccountId);
    return SendMsg(&msg, true, t);
}

// 0xd1de0
bool NPGameServiceChannel::SendRequestPromotionStampListCurrentPromotions(NPTransaction* t,
                                                                          wchar_t const* appGroupCode)
{
    if (t == nullptr)
    {
        Log::Write(Log::LT_ERROR, NPSERVICECHANNEL_FILE, 811,
                   L"== CRASH == [np], send request promotion stamp - list current promotions fail; null transaction");
        AlertSender::Write(
            NPSERVICECHANNEL_FILE, 811,
            L"== CRASH == [np], send request promotion stamp - list current promotions fail; null transaction");
        return false;
    }
    char appGroupCodeA[33] = {0};
    WideCharToMultiByte(CP_ACP, 0, appGroupCode, -1, appGroupCodeA, 32, nullptr, nullptr);
    _StsMsgRequestPromotionStampListCurrentPromotions msg;
    npInitRequest(msg, COMMAND_COMMON_PROMOTIONSTAMP_LIST_CURRENT_PROMOTIONS);
    msg.pszAppGroupCode = appGroupCodeA;
    msg.nExcludeSuspended = 1;
    return SendMsg(&msg, true, t);
}

// 0xd1f00
bool NPGameServiceChannel::SendRequestPromotionStampGetPromotionPolicy(NPTransaction* t, int promotionId)
{
    if (t == nullptr)
    {
        Log::Write(Log::LT_ERROR, NPSERVICECHANNEL_FILE, 828,
                   L"== CRASH == [np], send request promotion stamp - get promotion policy fail; null transaction");
        AlertSender::Write(
            NPSERVICECHANNEL_FILE, 828,
            L"== CRASH == [np], send request promotion stamp - get promotion policy fail; null transaction");
        return false;
    }
    _StsMsgRequestPromotionStampGetPromotionPolicy msg;
    npInitRequest(msg, COMMAND_COMMON_PROMOTIONSTAMP_GET_PROMOTION_POLICY);
    msg.nPromotionId = promotionId;
    msg.nReplyType = 1;
    msg.nPromotionLanguageCode = 0;
    return SendMsg(&msg, true, t);
}

// 0xd1f90
bool NPGameServiceChannel::SendRequestPromotionStampGetUserPromotionStatus(NPTransaction* t, id128 const& userId,
                                                                           int promotionId, short boardType,
                                                                           wchar_t const* appGroupCode)
{
    if (t == nullptr)
    {
        Log::Write(Log::LT_ERROR, NPSERVICECHANNEL_FILE, 842,
                   L"== CRASH == [np], send request promotion stamp - get user promotion status fail; null transaction");
        AlertSender::Write(
            NPSERVICECHANNEL_FILE, 842,
            L"== CRASH == [np], send request promotion stamp - get user promotion status fail; null transaction");
        return false;
    }
    char appGroupCodeA[33] = {0};
    WideCharToMultiByte(CP_ACP, 0, appGroupCode, -1, appGroupCodeA, 32, nullptr, nullptr);
    _StsMsgRequestPromotionStampGetUserPromotionStatus msg;
    npInitRequest(msg, COMMAND_COMMON_PROMOTIONSTAMP_GET_USER_PROMOTION_STATUS);
    msg.nPromotionId = promotionId;
    msg.nBoardType = boardType;
    msg.pUserId = npGuid(userId);
    msg.pszAppGroupCode = appGroupCodeA;
    return SendMsg(&msg, true, t);
}

// 0xd20d0
bool NPGameServiceChannel::SendRequestPromotionStampAttendPromotionSecured(NPTransaction* t, id128 const& userId,
                                                                           int promotionId, short boardType,
                                                                           wchar_t const* appGroupCode,
                                                                           short accumulatedPoint, long long attended)
{
    if (t == nullptr)
    {
        Log::Write(Log::LT_ERROR, NPSERVICECHANNEL_FILE, 861,
                   L"== CRASH == [np], send request promotion stamp - attend promotion secured fail; null transaction");
        AlertSender::Write(
            NPSERVICECHANNEL_FILE, 861,
            L"== CRASH == [np], send request promotion stamp - attend promotion secured fail; null transaction");
        return false;
    }
    char appGroupCodeA[33] = {0};
    WideCharToMultiByte(CP_ACP, 0, appGroupCode, -1, appGroupCodeA, 32, nullptr, nullptr);
    _StsMsgRequestPromotionStampAttendPromotionSecured msg;
    npInitRequest(msg, COMMAND_COMMON_PROMOTIONSTAMP_ATTEND_PROMOTION_SECURED);
    msg.nPromotionId = promotionId;
    msg.nBoardType = boardType;
    msg.pUserId = npGuid(userId);
    msg.pszAppGroupCode = appGroupCodeA;
    msg.nAccumulatedPoint = accumulatedPoint;
    msg.tAttended = attended;
    return SendMsg(&msg, true, t);
}

// 0xd2250
void NPLobbyJobTransaction::Expire()
{
    if (!LobbyDaemon::_instance->_jobMgr->ResumeW(_jobid, _state, _task, nullptr))
        Log::Write(Log::LT_ERROR, NPSERVICECHANNEL_FILE, 909,
                   L"[np], expire np lobby-job transaction fail; execute job fail, tid:0x%I64X, state:%d, task:%d",
                   _jobid, _state, _task);
}

// 0xd22c0
NPTransaction* NPLobbyJobTransaction::Set(LobbyJob* job, int task)
{
    if (job == nullptr)
    {
        Log::Write(Log::LT_ERROR, NPSERVICECHANNEL_FILE, 915, L"[np], set np lobby-job transaction fail; invalid parameter");
        return nullptr;
    }
    _jobid = job->_id;
    _state = job->_state;
    _task = task;
    return this;
}
