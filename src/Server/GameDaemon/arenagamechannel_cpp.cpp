// arenagamechannel_cpp.cpp: arenagamechannel.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "arenagamechannel.h"
#include "pc.h"
#include "LiftStub.h"
#include "AlertSender.h"
#include "Log.h"

// LIFT: per-exe path literal (lessons A6).
#define ARENAGAMECHANNEL_FILE L"e:\\dailybuild02\\gamedaemon-common-0.0.348\\depot\\branch\\348nc\\program\\server\\gamedaemon\\ArenaGameChannel.cpp"

// 0x36160
__cdecl ArenaGameChannel::ArenaGameChannel(::DaemonInfo const &)
{
    LIFT_STUB(0x36160);
}

// 0x362e0
bool __cdecl ArenaGameChannel::SendPing(void)
{
    LIFT_STUB(0x362e0);
}

// 0x363a0
void __cdecl ArenaGameChannel::CheckPing(void)
{
    LIFT_STUB(0x363a0);
}

// 0x36480
#pragma comment(linker, "/INCLUDE:?OnAccept@ArenaGameSessionHandler@@UEBA_NPEBVSession@@@Z")  // LIFT: dead-strip keep (no live caller yet)
bool __cdecl ArenaGameSessionHandler::OnAccept(::Session const *) const
{
    Log::Write(Log::LT_ERROR, ARENAGAMECHANNEL_FILE, 114,
               L"== CRASH == [arena-game], cannot accept from game (arena connect to game)");
    AlertSender::Write(ARENAGAMECHANNEL_FILE, 114,
                       L"== CRASH == [arena-game], cannot accept from game (arena connect to game)");
    return false;
}

// 0x364c0
bool __cdecl ArenaGameSessionHandler::OnConnect(::Session const *, bool) const
{
    LIFT_STUB(0x364c0);
}

// 0x366d0
void __cdecl ArenaGameSessionHandler::OnClose(::Session const *, bool) const
{
    LIFT_STUB(0x366d0);
}

// 0x368a0
bool __cdecl ArenaGameSessionHandler::PacketHandler(::Session const *, ::Packet const *) const
{
    LIFT_STUB(0x368a0);
}

// 0x36c40
bool __cdecl HandleArenaGameArenaHelloOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x36c40);
}

// 0x37030
#pragma comment(linker, "/INCLUDE:?HandleArenaGameArenaHelloFail@@YA_NPEBVSession@@PEBVPacket@@@Z")  // LIFT: dead-strip keep (no live caller yet)
bool __cdecl HandleArenaGameArenaHelloFail(::Session const *session, ::Packet const *packet)
{
    short cmd;  // LIFT: the original does not set cmd and reason before Decompose (0x37030).
    short reason;
    packet->Decompose("hh", &cmd, &reason);
    Log::Write(Log::LT_ERROR, ARENAGAMECHANNEL_FILE, 378, L"[arena-game], hello failed, session-id:0x%I64x, reason:%d",
               session->_id, static_cast<int>(reason));
    return false;
}

// 0x37090
bool __cdecl HandleArenaGameArenaEnterArenaReq(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x37090);
}

// 0x38740
bool __cdecl HandleArenaGameArenaLeaveArenaOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x38740);
}

// 0x38820
bool __cdecl HandleArenaGameArenaLeaveArenaFail(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x38820);
}

// 0x38a50
bool __cdecl HandleArenaGameArenaLogoutReq(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x38a50);
}

// 0x38f10
bool __cdecl HandleArenaGameArenaGuildMemberInfoOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x38f10);
}

// 0x39320
bool __cdecl HandleArenaGameArenaRenameGuildNotify(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x39320);
}

// 0x39480
bool __cdecl HandleArenaGameArenaRenameGuildByManagementDNotify(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x39480);
}

// 0x395e0
bool __cdecl HandleArenaGameArenaPingOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x395e0);
}

// 0x396e0
bool __cdecl HandleArenaGameArenaGamePlayRestrictLevelOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x396e0);
}

// 0x399c0
bool __cdecl HandleArenaGameArenaGamePlayRestrictLevelForHealthySystemOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x399c0);
}

// 0x39c60
bool __cdecl HandleArenaGameGameGradeListReq(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x39c60);
}

// 0x39da0
bool __cdecl HandleArenaGameArenaGradeListOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x39da0);
}

// 0x3a1c0
bool __cdecl HandleArenaGameArenaGradeListFail(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x3a1c0);
}

// 0x3a3d0
bool __cdecl HandleArenaGameArenaChangedGradeNotify(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x3a3d0);
}

// 0x3a5c0
bool __cdecl HandleArenaGameArenaChangedGradeLevelNotify(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x3a5c0);
}

// 0x3a790
bool __cdecl HandleArenaGameArenaUpdateArenaSessionTimerReq(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x3a790);
}

// 0x3a9a0
bool __cdecl HandleArenaGameGameUpdateArenaSessionTimerOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x3a9a0);
}

// 0x3adb0
bool __cdecl HandleArenaGameGameDepositGameMileageReq(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x3adb0);
}

// 0x3afc0
bool __cdecl HandleArenaGameArenaDepositGameMileageOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x3afc0);
}

// 0x3b8a0
bool __cdecl HandleArenaGameArenaDepositGameMileageFail(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x3b8a0);
}

// 0x3c000
bool __cdecl HandleArenaGameArenaChangedGuildBuffNotify(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x3c000);
}

// 0x3c390
bool __cdecl HandleArenaGameGameCalcTimeBasedPlayInfoNotify(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x3c390);
}

// 0x3c480
bool __cdecl HandleArenaGameGameUpdateChallengePartyMemberZoneInfoNotify(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x3c480);
}

// 0x3c5a0
bool __cdecl HandleArenaGameGameUpdateAccountExpToLobbyNotify(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x3c5a0);
}

// 0x3c6b0
bool __cdecl HandleArenaGameGameUpdateAccountContentQuotaToLobbyNotify(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x3c6b0);
}

// 0x3c980
bool __cdecl HandleArenaGameGameUpdateAccountRecycleTimeToLobbyNotify(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x3c980);
}

// 0x3cc70
__cdecl ArenaSideArenaLobbyChannel::~ArenaSideArenaLobbyChannel(void)
{
    LIFT_STUB(0x3cc70);
}

// 0x3cc80
bool __cdecl ArenaSideArenaLobbyChannel::InitSession(void)
{
    LIFT_STUB(0x3cc80);
}

// 0x3cd10
bool __cdecl ArenaSideArenaLobbyChannel::SendCreateRoom(::Pc **, int, unsigned __int64, char, char, char, unsigned __int64)
{
    LIFT_STUB(0x3cd10);
}

// 0x3cea0
bool __cdecl ArenaSideArenaLobbyChannel::SendPublishRecruitArenaDungeonMember(unsigned __int64, unsigned __int64, unsigned __int64, unsigned __int64, unsigned __int64, char, short)
{
    LIFT_STUB(0x3cea0);
}

// 0x3d080
bool __cdecl ArenaSideArenaLobbyChannel::SendCancelRecruitArenaDungeonMember(unsigned __int64, unsigned __int64, unsigned __int64, unsigned __int64, unsigned __int64, char, short, char)
{
    LIFT_STUB(0x3d080);
}

// 0x3d2c0
bool __cdecl ArenaSideArenaLobbyChannel::SendPing(void)
{
    LIFT_STUB(0x3d2c0);
}

// 0x3d380
void __cdecl ArenaSideArenaLobbyChannel::CheckPing(void)
{
    LIFT_STUB(0x3d380);
}

// 0x3d440
::Session * __cdecl ArenaSideArenaLobbyChannel::getSession(void)
{
    LIFT_STUB(0x3d440);
}

// 0x3d4f0
bool __cdecl ArenaSideArenaLobbyChannel::onConnect(::Session const *, bool)
{
    LIFT_STUB(0x3d4f0);
}

// 0x3d5a0
void __cdecl ArenaSideArenaLobbyChannel::onClose(::Session const *, bool, bool)
{
    LIFT_STUB(0x3d5a0);
}

// 0x3d670
bool __cdecl ArenaSideArenaLobbyChannel::PacketHandler(::Session const *, ::Packet const *) const
{
    LIFT_STUB(0x3d670);
}

// 0x3d740
bool __cdecl HandleArenaLobbyArenaHelloOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x3d740);
}

// 0x3d850
#pragma comment(linker, "/INCLUDE:?HandleArenaLobbyArenaHelloFail@@YA_NPEBVSession@@PEBVPacket@@@Z")  // LIFT: dead-strip keep (no live caller yet)
bool __cdecl HandleArenaLobbyArenaHelloFail(::Session const *session, ::Packet const *packet)
{
    short cmd = 0;
    short reason = 0;
    packet->Decompose("hh", &cmd, &reason);
    Log::Write(Log::LT_ERROR, ARENAGAMECHANNEL_FILE, 2274, L"[arena-lobby], hello arena failed, session-id:0x%I64x, reason:%d",
               session->_id, static_cast<int>(reason));
    return false;
}

// 0x3d8c0
bool __cdecl HandleArenaLobbyArenaConnectGameNotify(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x3d8c0);
}

// 0x3d9b0
bool __cdecl HandleArenaLobbyArenaDisconnectGameNotify(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x3d9b0);
}

// 0x3da90
// ❓ Not done: the format string "hiQciQcssqhqE" has 13 fields, but the pseudocode shows only two targets (see handoff).
bool __cdecl HandleArenaLobbyArenaRelayFailNotify(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x3da90);
}

// 0x3db00
bool __cdecl HandleArenaLobbyArenaCreateRoomFail(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x3db00);
}

// 0x3df70
bool __cdecl HandleArenaLobbyArenaCreateRoomNotify(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x3df70);
}

// 0x3e910
bool __cdecl HandleArenaLobbyArenaReserveArenaReq(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x3e910);
}

// 0x3f1e0
bool __cdecl HandleArenaLobbyArenaReserveReturnToArenaReq(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x3f1e0);
}

// 0x3fb60
bool __cdecl HandleArenaLobbyArenaReserveSpectatorToArenaReq(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x3fb60);
}

// 0x40330
bool __cdecl HandleArenaLobbyArenaRemoveArenaLobbyMemberOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x40330);
}

// 0x40430
bool __cdecl HandleArenaLobbyArenaRemoveArenaLobbyMemberFail(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x40430);
}

// 0x40530
bool __cdecl HandleArenaLobbyArenaPublishRecruitArenaDungeonMemberOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x40530);
}

// 0x40920
bool __cdecl HandleArenaLobbyArenaPublishRecruitArenaDungeonMemberFail(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x40920);
}

// 0x40ba0
bool __cdecl HandleArenaLobbyArenaCancelRecruitArenaDungeonMemberOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x40ba0);
}

// 0x41120
bool __cdecl HandleArenaLobbyArenaCancelRecruitArenaDungeonMemberFail(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x41120);
}

// 0x413f0
bool __cdecl HandleArenaLobbyArenaReserveRecruitMemberToArenaReq(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x413f0);
}

// 0x42c00
bool __cdecl HandleArenaLobbyArenaPingOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x42c00);
}

// 0x42ca0
bool __cdecl ArenaGameManager::Connect(::DaemonInfo const &)
{
    LIFT_STUB(0x42ca0);
}

// 0x42e70
bool __cdecl ArenaGameManager::Disconnect(::DaemonInfo const &)
{
    LIFT_STUB(0x42e70);
}

// 0x42f40
bool __cdecl ArenaGameManager::Send(unsigned int, char const *, ...)
{
    LIFT_STUB(0x42f40);
}

// 0x43030
bool __cdecl ArenaGameManager::Send(unsigned int, ::Packet const *)
{
    LIFT_STUB(0x43030);
}

// 0x43120
void __cdecl ArenaGameManager::SendLogoutOk(::Session const *, unsigned __int64, unsigned __int64, char, ::Pc *)
{
    LIFT_STUB(0x43120);
}

// 0x43490
bool __cdecl ArenaGameManager::SendLogoutOk(short, unsigned __int64, unsigned __int64, char, ::Pc *)
{
    LIFT_STUB(0x43490);
}

// 0x43b60
bool __cdecl ArenaGameManager::SendLeaveArenaReq(unsigned __int64, short, unsigned __int64, unsigned __int64, __int64, __int64, __int64, int, __int64, int, int, __int64, int, int, int, __int64, __int64, int, ::GradeLevelInfo &, ::GradeInfo *const, short)
{
    LIFT_STUB(0x43b60);
}

// 0x43e90
bool __cdecl ArenaGameManager::SendLeaveArenaReq(short, unsigned __int64, unsigned __int64, unsigned __int64, __int64, __int64, __int64, int, __int64, int, int, __int64, int, int, int, __int64, __int64, int, ::GradeLevelInfo &, ::GradeInfo *const, short)
{
    LIFT_STUB(0x43e90);
}

// 0x441d0
bool __cdecl ArenaGameManager::SendKickNotify(short, unsigned __int64, short)
{
    LIFT_STUB(0x441d0);
}

// 0x442a0
bool __cdecl ArenaGameManager::SendUpdateSeasonContentsGuildCombatRecordNotify(short, unsigned __int64, char, char, int, __int64, char)
{
    LIFT_STUB(0x442a0);
}

// 0x44370
bool __cdecl ArenaGameManager::SendDepositGameMileageReq(short, ::MileageDepositContext const *, bool)
{
    LIFT_STUB(0x44370);
}

// 0x446a0
bool __cdecl ArenaGameManager::SendCalcTimeBasedPlayInfoNotify(short, unsigned __int64)
{
    LIFT_STUB(0x446a0);
}

// 0x447b0
bool __cdecl ArenaGameManager::SendUpdateChallengePartyMemberZoneInfoNotify(short, __int64, unsigned __int64, int)
{
    LIFT_STUB(0x447b0);
}

// 0x44930
bool __cdecl ArenaGameManager::SendUpdateAccountExpToLobbyNotify(short, unsigned __int64, ::AccountExpInfo const &)
{
    LIFT_STUB(0x44930);
}

// 0x44a60
bool __cdecl ArenaGameManager::SendUpdateAccountContentQuotaToLobbyNotify(short, unsigned __int64, ::AccountContentQuota const &)
{
    LIFT_STUB(0x44a60);
}

// 0x44c70
bool __cdecl ArenaGameManager::SendUpdateAccountRecycleTimeToLobbyNotify(short, unsigned __int64, ::AccountRecycleTime const &)
{
    LIFT_STUB(0x44c70);
}

// 0x44e70
void __cdecl ArenaGameManager::CheckPing(void)
{
    LIFT_STUB(0x44e70);
}

// 0x44fb0
::ArenaGameChannel * __cdecl ArenaGameManager::acquire(unsigned int)
{
    LIFT_STUB(0x44fb0);
}

// 0x45040
void __cdecl ArenaGameManager::Destroy(void)
{
    LIFT_STUB(0x45040);
}
