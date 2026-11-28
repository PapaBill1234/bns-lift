// lobbydaemonchannel_cpp.cpp: lobbydaemonchannel.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "lobbydaemonchannel.h"
#include "user.h"
#include "LiftStub.h"

#pragma comment(linker, "/INCLUDE:?HandleLobbyGame_UpdateAccountContentQuotaOk@@YA_NPEBVSession@@PEBVPacket@@@Z")  // LIFT: dead-strip keep (no live caller yet)

// 0x13e280
bool __cdecl LobbyDaemonSessionHandler::OnAccept(::Session const *) const
{
    LIFT_STUB(0x13e280);
}

// 0x13e2c0
bool __cdecl LobbyDaemonSessionHandler::OnConnect(::Session const *, bool) const
{
    LIFT_STUB(0x13e2c0);
}

// 0x13e4f0
void __cdecl LobbyDaemonSessionHandler::OnClose(::Session const *, bool) const
{
    LIFT_STUB(0x13e4f0);
}

// 0x13e6d0
bool __cdecl LobbyDaemonSessionHandler::PacketHandler(::Session const *, ::Packet const *) const
{
    LIFT_STUB(0x13e6d0);
}

// 0x13e730
void __cdecl LobbyDaemonChannel::Initialize(short)
{
    LIFT_STUB(0x13e730);
}

// 0x13e870
bool __cdecl LobbyDaemonChannel::SendHello(void)
{
    LIFT_STUB(0x13e870);
}

// 0x13e9e0
bool __cdecl LobbyDaemonChannel::ProcHello(bool, ::Packet const *)
{
    LIFT_STUB(0x13e9e0);
}

// 0x13ec00
bool __cdecl HandleLobbyGame_HelloOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x13ec00);
}

// 0x13ed30
bool __cdecl HandleLobbyGame_HelloFail(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x13ed30);
}

// 0x13ee50
bool __cdecl HandleLobbyGame_NPPresenceKickNotify(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x13ee50);
}

// 0x13efc0
bool __cdecl HandleLobbyGame_EnterWorldOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x13efc0);
}

// 0x13fe30
bool __cdecl HandleLobbyGame_EnterWorldFail(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x13fe30);
}

// 0x13ff90
bool __cdecl HandleLobbyGame_LeaveWorldOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x13ff90);
}

// 0x1400f0
bool __cdecl HandleLobbyGame_LeaveWorldFail(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x1400f0);
}

// 0x140250
bool __cdecl HandleLobbyGame_CloseSessionNotify(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x140250);
}

// 0x1402a0
bool __cdecl HandleLobbyGame_KickReq(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x1402a0);
}

// 0x140610
bool __cdecl HandleLobbyGame_StopPlayNotify(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x140610);
}

// 0x140730
bool __cdecl HandleLobbyGame_CreateCharacterReq(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x140730);
}

// 0x141130
bool __cdecl HandleLobbyGame_DeleteCharacterReq(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x141130);
}

// 0x141460
bool __cdecl HandleLobbyGame_RestoreCharacterReq(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x141460);
}

// 0x1417c0
bool __cdecl HandleLobbyGame_DeleteCharacterCompleteNotify(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x1417c0);
}

// 0x141880
bool __cdecl HandleLobbyGame_StartChargeOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x141880);
}

// 0x141ab0
bool __cdecl HandleLobbyGame_StartChargeFail(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x141ab0);
}

// 0x141c40
bool __cdecl HandleLobbyGame_StopChargeOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x141c40);
}

// 0x141ce0
bool __cdecl HandleLobbyGame_StopChargeFail(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x141ce0);
}

// 0x141e70
bool __cdecl HandleLobbyGame_ApplyNewChargeItemNotify(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x141e70);
}

// 0x142070
bool __cdecl HandleLobbyGame_UpdateChargeRemainTimeNotify(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x142070);
}

// 0x142190
bool __cdecl HandleLobbyGame_UpdateCharacterDataOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x142190);
}

// 0x142200
bool __cdecl HandleLobbyGame_UpdateCharacterDataFail(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x142200);
}

// 0x142360
bool __cdecl HandleLobbyGame_UpdateAccountDataOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x142360);
}

// 0x1423e0
bool __cdecl HandleLobbyGame_UpdateAccountDataFail(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x1423e0);
}

// 0x142540
bool __cdecl HandleLobbyGame_TryRegisterGuildOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x142540);
}

// 0x142720
bool __cdecl HandleLobbyGame_TryRegisterGuildFail(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x142720);
}

// 0x142920
bool __cdecl HandleLobbyGame_TryRenameGuildOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x142920);
}

// 0x142b60
bool __cdecl HandleLobbyGame_TryRenameGuildFail(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x142b60);
}

// 0x142da0
bool __cdecl HandleLobbyGame_AccountInventoryNotify(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x142da0);
}

// 0x143270
bool __cdecl HandleLobbyGame_ChangeCharacterAppearanceReq(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x143270);
}

// 0x143cc0
bool __cdecl HandleLobbyGame_ChangeCharacterSexReq(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x143cc0);
}

// 0x1447b0
bool __cdecl HandleLobbyGame_ChangeCharacterRaceReq(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x1447b0);
}

// 0x1452e0
bool __cdecl HandleLobbyGame_RenameCharacterReq(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x1452e0);
}

// 0x145690
bool __cdecl HandleLobbyGame_ExtendJumpingCharacterCreationQuotaWithAccountInventoryItemOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x145690);
}

// 0x145860
bool __cdecl HandleLobbyGame_ExtendJumpingCharacterCreationQuotaWithAccountInventoryItemFail(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x145860);
}

// 0x145a20
bool __cdecl HandleLobbyGame_UpgradeJumpingCharacterStateWithCreationQuotaOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x145a20);
}

// 0x145c00
bool __cdecl HandleLobbyGame_UpgradeJumpingCharacterStateWithCreationQuotaFail(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x145c00);
}

// 0x145dc0
bool __cdecl HandleLobbyGame_UpdateJumpingCharacterStateOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x145dc0);
}

// 0x145f80
bool __cdecl HandleLobbyGame_UpdateJumpingCharacterStateFail(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x145f80);
}

// 0x146150
bool __cdecl HandleLobbyGame_SecondPasswordGetStatusOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x146150);
}

// 0x146740
bool __cdecl HandleLobbyGame_SecondPasswordGetStatusFail(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x146740);
}

// 0x146cd0
bool __cdecl HandleLobbyGame_SecondPasswordIsVerifiedOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x146cd0);
}

// 0x147240
bool __cdecl HandleLobbyGame_SecondPasswordIsVerifiedFail(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x147240);
}

// 0x1477d0
bool __cdecl HandleLobbyGame_AuctionEscrowReq(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x1477d0);
}

// 0x147e30
bool __cdecl HandleLobbyGame_AuctionBidOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x147e30);
}

// 0x148100
bool __cdecl HandleLobbyGame_AuctionBidFail(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x148100);
}

// 0x148510
bool __cdecl HandleLobbyGame_ActivateGradeOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x148510);
}

// 0x148680
bool __cdecl HandleLobbyGame_ActivateGradeFail(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x148680);
}

// 0x148820
bool __cdecl HandleLobbyGame_DepositGameMileageOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x148820);
}

// 0x149480
bool __cdecl HandleLobbyGame_DepositGameMileageFail(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x149480);
}

// 0x149ec0
bool __cdecl HandleLobbyGame_TakeAccountTimeBasedPlayRewardOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x149ec0);
}

// 0x14a390
bool __cdecl HandleLobbyGame_TakeAccountTimeBasedPlayRewardFail(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x14a390);
}

// 0x14a630
bool __cdecl HandleLobbyGame_GetGradeListOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x14a630);
}

// 0x14aa80
bool __cdecl HandleLobbyGame_GetGradeListFail(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x14aa80);
}

// 0x14ac80
bool __cdecl HandleLobbyGame_ChangedGradeNotify(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x14ac80);
}

// 0x14ae80
bool __cdecl HandleLobbyGame_ChangedGradeLevelNotify(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x14ae80);
}

// 0x14b060
bool __cdecl HandleLobbyGame_UpdateAccountExpFail(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x14b060);
}

// 0x14b0e0
bool __cdecl HandleLobbyGame_UpdateAccountContentQuotaOk(::Session const *, ::Packet const *packet)
{
    short c;
    __int64 gameTid;
    unsigned __int64 pcdbid;
    packet->Decompose("hqq", &c, &gameTid, &pcdbid);
    return true;
}

// 0x14b120
bool __cdecl HandleLobbyGame_UpdateAccountContentQuotaFail(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x14b120);
}

// 0x14b1a0
bool __cdecl HandleLobbyGame_UpdateAccountRecycleTimeFail(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x14b1a0);
}

// 0x14b220
bool __cdecl LobbyDaemonChannelManager::Initialize(short, short *const)
{
    LIFT_STUB(0x14b220);
}

// 0x14b5c0
void __cdecl LobbyDaemonChannelManager::Destroy(void)
{
    LIFT_STUB(0x14b5c0);
}

// 0x14b730
::LobbyDaemonChannel * __cdecl LobbyDaemonChannelManager::acquire(unsigned int)
{
    LIFT_STUB(0x14b730);
}

// 0x14b850
bool __cdecl LobbyDaemonChannelManager::Send(short, char const *, ...)
{
    LIFT_STUB(0x14b850);
}

// 0x14b940
bool __cdecl LobbyDaemonChannelManager::Send(short, ::Packet const *)
{
    LIFT_STUB(0x14b940);
}

// 0x14ba30
bool __cdecl LobbyDaemonChannelManager::SendCreateCharacterOk(short, __int64, ::FsdShowcaseRecord const &)
{
    LIFT_STUB(0x14ba30);
}

// 0x14bbb0
bool __cdecl LobbyDaemonChannelManager::SendChangeCharacterAppearanceOk(short, __int64, ::FsdShowcaseRecord const &)
{
    LIFT_STUB(0x14bbb0);
}

// 0x14bd20
bool __cdecl LobbyDaemonChannelManager::SendChangeCharacterSexOk(short, __int64, ::FsdShowcaseRecord const &)
{
    LIFT_STUB(0x14bd20);
}

// 0x14be90
bool __cdecl LobbyDaemonChannelManager::SendChangeCharacterRaceOk(short, __int64, ::FsdShowcaseRecord const &)
{
    LIFT_STUB(0x14be90);
}

// 0x14c000
bool __cdecl LobbyDaemonChannelManager::SendUpdateCharacterDataReq(short, __int64, unsigned __int64, __int64, ::FsdShowcaseRecord const &)
{
    LIFT_STUB(0x14c000);
}

// 0x14c190
bool __cdecl LobbyDaemonChannelManager::SendUpdateAccountDataReq(short, __int64, unsigned __int64, __int64, int, __int64, ::TimeBasedPlayInfoList &, ::AccountExpInfo const *, ::std::vector< ::AccountContentQuota, ::StlAllocator< ::AccountContentQuota, 2> > *, ::std::vector< ::AccountRecycleTime, ::StlAllocator< ::AccountRecycleTime, 2> > *)
{
    LIFT_STUB(0x14c190);
}

// 0x14c6b0
bool __cdecl LobbyDaemonChannelManager::SendUpdateAccountExpReq(short, __int64, unsigned __int64, __int64, ::AccountExpInfo const &)
{
    LIFT_STUB(0x14c6b0);
}

// 0x14c880
bool __cdecl LobbyDaemonChannelManager::SendUpdateAccountContentQuotaReq(short, __int64, unsigned __int64, __int64, ::AccountContentQuota const &)
{
    LIFT_STUB(0x14c880);
}

// 0x14cb20
bool __cdecl LobbyDaemonChannelManager::SendUpdateAccountRecycleTimeReq(short, __int64, unsigned __int64, __int64, ::AccountRecycleTime const &)
{
    LIFT_STUB(0x14cb20);
}

// 0x14cda0
bool __cdecl LobbyDaemonChannelManager::SendTryRegisterGuildName(short, unsigned __int64, char, wchar_t const *)
{
    LIFT_STUB(0x14cda0);
}

// 0x14cf20
bool __cdecl LobbyDaemonChannelManager::SendFinishRegisterGuild(short, unsigned __int64, unsigned __int64)
{
    LIFT_STUB(0x14cf20);
}

// 0x14d090
bool __cdecl LobbyDaemonChannelManager::SendCancelRegisterGuild(short, unsigned __int64, unsigned __int64)
{
    LIFT_STUB(0x14d090);
}

// 0x14d200
bool __cdecl LobbyDaemonChannelManager::SendTryRenameGuild(short, unsigned __int64, unsigned __int64, char, wchar_t const *)
{
    LIFT_STUB(0x14d200);
}

// 0x14d3d0
bool __cdecl LobbyDaemonChannelManager::SendFinishRenameGuildNotify(short, unsigned __int64, unsigned __int64, unsigned __int64)
{
    LIFT_STUB(0x14d3d0);
}

// 0x14d560
bool __cdecl LobbyDaemonChannelManager::SendCancelRenameGuildNotify(short, unsigned __int64)
{
    LIFT_STUB(0x14d560);
}

// 0x14d6a0
bool __cdecl LobbyDaemonChannelManager::SendDeleteGuildNotify(short, unsigned __int64, unsigned __int64)
{
    LIFT_STUB(0x14d6a0);
}

// 0x14d810
bool __cdecl LobbyDaemonChannelManager::SendSetAppDataNotify(short, unsigned __int64, short, ::KeyValueRecord const *const)
{
    LIFT_STUB(0x14d810);
}

// 0x14dab0
bool __cdecl LobbyDaemonChannelManager::SendFriendMessage(short, unsigned __int64, wchar_t const *, short, ::KeyValueRecord const *const)
{
    LIFT_STUB(0x14dab0);
}

// 0x14dd30
bool __cdecl LobbyDaemonChannelManager::SendActivateGrade(short, unsigned __int64, char, int)
{
    LIFT_STUB(0x14dd30);
}

// 0x14de60
bool __cdecl LobbyDaemonChannelManager::SendDepositGameMileage(short, ::MileageDepositContext const *, bool)
{
    LIFT_STUB(0x14de60);
}

// 0x14e210
bool __cdecl LobbyDaemonChannelManager::SendAuctionBid(short, unsigned __int64, ::id128 &, short, __int64)
{
    LIFT_STUB(0x14e210);
}

// 0x14e400
bool __cdecl LobbyDaemonChannelManager::SendServiceOpen(short, short)
{
    LIFT_STUB(0x14e400);
}

// 0x14e530
bool __cdecl LobbyDaemonChannelManager::SendBoastEventInWorld(short, short, wchar_t const *, short, __int64, __int64)
{
    LIFT_STUB(0x14e530);
}

// 0x14e8b0
bool __cdecl LobbyDaemonChannelManager::SendBoastEventInWorld(short, short, wchar_t const *, short)
{
    LIFT_STUB(0x14e8b0);
}

// 0x14ea00
bool __cdecl LobbyDaemonChannelManager::SendUpdateJumpingCharacterState(short, __int64, unsigned __int64, __int64)
{
    LIFT_STUB(0x14ea00);
}

// 0x14eb20
bool __cdecl LobbyDaemonChannelManager::SendSecondPasswordGetStatus(short, unsigned __int64, unsigned __int64, char)
{
    LIFT_STUB(0x14eb20);
}

// 0x14ec60
bool __cdecl LobbyDaemonChannelManager::SendSecondPasswordIsVerified(short, unsigned __int64, unsigned __int64, char, char)
{
    LIFT_STUB(0x14ec60);
}
