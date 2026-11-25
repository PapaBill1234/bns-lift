// NPServiceChannel.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "NPServiceChannel.h"
#include "LiftStub.h"
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
bool NPGameServiceChannel::SendRequestAuthChangeMyUserNameIncomplete(NPTransaction*, id128 const&, wchar_t const*, wchar_t const*, wchar_t const*)
{
    LIFT_STUB(0xd0370);
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
