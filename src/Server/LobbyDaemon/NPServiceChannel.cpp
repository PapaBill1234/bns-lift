// NPServiceChannel.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "NPServiceChannel.h"
#include "AlertSender.h"
#include "LiftStub.h"
#include "Memory.h"
#include "MemoryManager.h"
#include "StringUtil.h"
#include "LobbyDaemon.h"
#include "LobbyJob.h"
#include "Log.h"

// 0xcfba0
bool NPServiceChannelManager::Initialize(unsigned int, unsigned long, unsigned short, long)
{
    LIFT_STUB(0xcfba0);
}

// 0xcfdb0
bool NPServiceChannelManager::OnConnect(NPChannel*, bool) const
{
    LIFT_STUB(0xcfdb0);
}

// 0xcff70
bool NPServiceChannelManager::OnClose(NPChannel*, bool) const
{
    LIFT_STUB(0xcff70);
}

// 0xd0220
bool NPGameServiceChannel::SendRequestConsumeGameToken(NPTransaction*, id128 const&, id128 const&, unsigned long)
{
    LIFT_STUB(0xd0220);
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
bool NPGameServiceChannel::SendRequestSlotGetSlot(NPTransaction*, id128 const&, id128 const&)
{
    LIFT_STUB(0xd03d0);
}

// 0xd0450
bool NPGameServiceChannel::SendRequestSlotCreateActivitySlots(NPTransaction*, id128 const&, wchar_t const*, unsigned long long, int, wchar_t const*)
{
    LIFT_STUB(0xd0450);
}

// 0xd0560
bool NPGameServiceChannel::SendRequestSlotSetActivitySlotData(NPTransaction*, id128 const&, id128 const&, unsigned long long)
{
    LIFT_STUB(0xd0560);
}

// 0xd0650
bool NPGameServiceChannel::SendRequestPresenceLogin(NPTransaction*, wchar_t const*, wchar_t const*, wchar_t const*, id128 const&, unsigned long)
{
    LIFT_STUB(0xd0650);
}

// 0xd0800
bool NPGameServiceChannel::SendRequestPresenceLogout(id128 const&)
{
    LIFT_STUB(0xd0800);
}

// 0xd09b0
bool NPGameServiceChannel::SendRequestPresenceKick(NPTransaction*, id128 const&, id128 const&, bool)
{
    LIFT_STUB(0xd09b0);
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
bool NPGameServiceChannel::SendResponseGateLogoutUser(unsigned int, int)
{
    LIFT_STUB(0xd0e20);
}

// 0xd0e90
bool NPGameServiceChannel::SendRequestChargeGetInfo(NPTransaction*, id128 const&, unsigned long)
{
    LIFT_STUB(0xd0e90);
}

// 0xd0fc0
bool NPGameServiceChannel::SendRequestChargeStart(NPTransaction*, id128 const&, unsigned long, short, unsigned int)
{
    LIFT_STUB(0xd0fc0);
}

// 0xd1110
bool NPGameServiceChannel::SendRequestChargeStop(NPTransaction*, id128 const&, unsigned long, wchar_t const*)
{
    LIFT_STUB(0xd1110);
}

// 0xd1230
bool NPGameServiceChannel::SendRequestChargeAbandon(NPTransaction*, id128 const&, wchar_t const*)
{
    LIFT_STUB(0xd1230);
}

// 0xd1310
bool NPGameServiceChannel::SendResponseChargeRequestStopFail(unsigned int, wchar_t const*, int)
{
    LIFT_STUB(0xd1310);
}

// 0xd1390
bool NPGameServiceChannel::SendRequestListUserLastPresences(NPTransaction*, id128 const&)
{
    LIFT_STUB(0xd1390);
}

// 0xd1410
bool NPGameServiceChannel::SendRequestGradeListAllGrades(NPTransaction*, id128 const&)
{
    LIFT_STUB(0xd1410);
}

// 0xd1510
bool NPGameServiceChannel::SendRequestGradeActivateGrade(NPTransaction*, id128 const&, int, int)
{
    LIFT_STUB(0xd1510);
}

// 0xd1610
bool NPGameServiceChannel::SendResponseGameAuctionEscrowOk(unsigned int, unsigned long long)
{
    LIFT_STUB(0xd1610);
}

// 0xd1710
bool NPGameServiceChannel::SendResponseGameAuctionEscrowFail(unsigned int, wchar_t const*, int, unsigned long long)
{
    LIFT_STUB(0xd1710);
}

// 0xd17f0
bool NPGameServiceChannel::SendResponseGameAuctionRollbackEscrowOk(unsigned int)
{
    LIFT_STUB(0xd17f0);
}

// 0xd1860
bool NPGameServiceChannel::SendResponseGameAuctionRollbackEscrowFail(unsigned int, wchar_t const*, int)
{
    LIFT_STUB(0xd1860);
}

// 0xd18e0
bool NPGameServiceChannel::SendResponseGameAuctionDeliveryOk(unsigned int, unsigned long long)
{
    LIFT_STUB(0xd18e0);
}

// 0xd19e0
bool NPGameServiceChannel::SendResponseGameAuctionDeliveryFail(unsigned int, wchar_t const*, int, unsigned long long)
{
    LIFT_STUB(0xd19e0);
}

// 0xd1af0
bool NPGameServiceChannel::SendRequestListUserBans(NPTransaction*, id128 const&)
{
    LIFT_STUB(0xd1af0);
}

// 0xd1be0
bool NPGameServiceChannel::SendRequestRMSInquiry(NPTransaction*, id128 const&, char*, unsigned long)
{
    LIFT_STUB(0xd1be0);
}

// 0xd1ce0
bool NPGameServiceChannel::SendRequestProfileGetUserProfile(NPTransaction*, id128 const&)
{
    LIFT_STUB(0xd1ce0);
}

// 0xd1d60
bool NPGameServiceChannel::SendRequestGameTimeGetGameTime(NPTransaction*, id128 const&)
{
    LIFT_STUB(0xd1d60);
}

// 0xd1de0
bool NPGameServiceChannel::SendRequestPromotionStampListCurrentPromotions(NPTransaction*, wchar_t const*)
{
    LIFT_STUB(0xd1de0);
}

// 0xd1f00
bool NPGameServiceChannel::SendRequestPromotionStampGetPromotionPolicy(NPTransaction*, int)
{
    LIFT_STUB(0xd1f00);
}

// 0xd1f90
bool NPGameServiceChannel::SendRequestPromotionStampGetUserPromotionStatus(NPTransaction*, id128 const&, int, short, wchar_t const*)
{
    LIFT_STUB(0xd1f90);
}

// 0xd20d0
bool NPGameServiceChannel::SendRequestPromotionStampAttendPromotionSecured(NPTransaction*, id128 const&, int, short, wchar_t const*, short, long long)
{
    LIFT_STUB(0xd20d0);
}

// 0xd2250
void NPLobbyJobTransaction::Expire()
{
    if (!LobbyDaemon::_instance->_jobMgr->ResumeW(_jobid, _state, _task, nullptr))
        Log::Write(Log::LT_ERROR, L"NPServiceChannel.cpp", 909,
                   L"[np], expire np lobby-job transaction fail; execute job fail, tid:0x%I64X, state:%d, task:%d",
                   _jobid, _state, _task);
}

// 0xd22c0
NPTransaction* NPLobbyJobTransaction::Set(LobbyJob* job, int task)
{
    if (job == nullptr)
    {
        Log::Write(Log::LT_ERROR, L"NPServiceChannel.cpp", 915, L"[np], set np lobby-job transaction fail; invalid parameter");
        return nullptr;
    }
    _jobid = job->_id;
    _state = job->_state;
    _task = task;
    return this;
}
