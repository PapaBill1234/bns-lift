// gamearenachannel_cpp_1.cpp: gamearenachannel.cpp part 1 (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "gamearenachannel.h"
#include "LiftStub.h"
#include "Session.h"
#include "AlertSender.h"
#include "Log.h"

// LIFT: per-exe path literal (lessons A6).
#define GAMEARENACHANNEL_FILE L"e:\\dailybuild02\\gamedaemon-common-0.0.348\\depot\\branch\\348nc\\program\\server\\gamedaemon\\GameArenaChannel.cpp"

// 0xbdb30
#pragma comment(linker, "/INCLUDE:?OnAccept@GameArenaSessionHandler@@UEBA_NPEBVSession@@@Z")  // LIFT: dead-strip keep (no live caller yet)
bool __cdecl GameArenaSessionHandler::OnAccept(::Session const * session) const
{
    Log::Write(Log::LT_DEBUG, GAMEARENACHANNEL_FILE, 48, L"[game-arena], accepted, session:0x%I64x", session->_id);
    return true;
}

// 0xbdb70
#pragma comment(linker, "/INCLUDE:?OnConnect@GameArenaSessionHandler@@UEBA_NPEBVSession@@_N@Z")  // LIFT: dead-strip keep (no live caller yet)
bool __cdecl GameArenaSessionHandler::OnConnect(::Session const *, bool) const
{
    Log::Write(Log::LT_ERROR, GAMEARENACHANNEL_FILE, 54,
               L"== CRASH == [game-arena], cannot connect game to arena (arena connect to game)");
    AlertSender::Write(GAMEARENACHANNEL_FILE, 54,
                       L"== CRASH == [game-arena], cannot connect game to arena (arena connect to game)");
    return false;
}

// 0xbdbb0
void __cdecl GameArenaSessionHandler::OnClose(::Session const *, bool) const
{
    LIFT_STUB(0xbdbb0);
}

// 0xbdcd0
bool __cdecl GameArenaSessionHandler::PacketHandler(::Session const *, ::Packet const *) const
{
    LIFT_STUB(0xbdcd0);
}

// 0xbe1b0
bool __cdecl HandleArenaGameGameHelloReq(::Session const *, ::Packet const *)
{
    LIFT_STUB(0xbe1b0);
}

// 0xbe4c0
bool __cdecl HandleArenaGameGameEnterArenaOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0xbe4c0);
}

// 0xbe990
bool __cdecl HandleArenaGameGameEnterArenaFail(::Session const *, ::Packet const *)
{
    LIFT_STUB(0xbe990);
}

// 0xbeb40
bool __cdecl HandleArenaGameGameLeaveArenaReq(::Session const *, ::Packet const *)
{
    LIFT_STUB(0xbeb40);
}

// 0xbf250
bool __cdecl HandleArenaGameGameLogoutOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0xbf250);
}

// 0xc0090
bool __cdecl HandleArenaGameGameForwardToCacheReq(::Session const *, ::Packet const *)
{
    LIFT_STUB(0xc0090);
}

// 0xc0240
bool __cdecl HandleArenaGameGameGuildMemberInfoReq(::Session const *, ::Packet const *)
{
    LIFT_STUB(0xc0240);
}

// 0xc03a0
bool __cdecl HandleArenaGameGameKickNotify(::Session const *, ::Packet const *)
{
    LIFT_STUB(0xc03a0);
}

// 0xc0450
bool __cdecl HandleArenaGameGameUpdateSeasonContentsGuildCombatRecordNotify(::Session const *, ::Packet const *)
{
    LIFT_STUB(0xc0450);
}

// 0xc0670
bool __cdecl HandleArenaGameGamePingReq(::Session const *, ::Packet const *)
{
    LIFT_STUB(0xc0670);
}

// 0xc07a0
bool __cdecl HandleArenaGameGameGamePlayRestrictLevelReq(::Session const *, ::Packet const *)
{
    LIFT_STUB(0xc07a0);
}

// 0xc0900
bool __cdecl HandleArenaGameGameGamePlayRestrictLevelForHealthySystemReq(::Session const *, ::Packet const *)
{
    LIFT_STUB(0xc0900);
}

// 0xc0a60
bool __cdecl HandleArenaLobbyGameHelloOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0xc0a60);
}

// 0xc0bd0
bool __cdecl HandleArenaLobbyGameHelloFail(::Session const *, ::Packet const *)
{
    LIFT_STUB(0xc0bd0);
}

// 0xc0ca0
bool __cdecl HandleArenaLobbyGameInitializeGuildInfoListOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0xc0ca0);
}

// 0xc0d20
bool __cdecl HandleArenaLobbyGameConfirmArenaOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0xc0d20);
}

// 0xc0ea0
bool __cdecl HandleArenaLobbyGameConfirmArenaFail(::Session const *, ::Packet const *)
{
    LIFT_STUB(0xc0ea0);
}

// 0xc0f60
bool __cdecl HandleArenaLobbyGameRelay(::Session const *, ::Packet const *)
{
    LIFT_STUB(0xc0f60);
}

// 0xc1360
bool __cdecl HandleArenaLobbyGameRelayFailNotify(::Session const *, ::Packet const *)
{
    LIFT_STUB(0xc1360);
}

// 0xc15b0
bool __cdecl HandleArenaLobbyGameInviteUnratedRoomOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0xc15b0);
}

// 0xc1790
bool __cdecl HandleArenaLobbyGameInviteUnratedRoomFail(::Session const *, ::Packet const *)
{
    LIFT_STUB(0xc1790);
}

// 0xc19d0
bool __cdecl HandleArenaLobbyGameInviteUnratedRoomNotify(::Session const *, ::Packet const *)
{
    LIFT_STUB(0xc19d0);
}

// 0xc1ed0
bool __cdecl HandleArenaLobbyGameCreateRoomFail(::Session const *, ::Packet const *)
{
    LIFT_STUB(0xc1ed0);
}

// 0xc2390
bool __cdecl HandleArenaLobbyGameCreateRoomNotify(::Session const *, ::Packet const *)
{
    LIFT_STUB(0xc2390);
}

// 0xc3470
bool __cdecl HandleArenaLobbyGameLastestArenaLobbyRoomInfoNotify(::Session const *, ::Packet const *)
{
    LIFT_STUB(0xc3470);
}

// 0xc3a90
bool __cdecl HandleArenaLobbyGameReserveReturnToArenaLobbyFail(::Session const *, ::Packet const *)
{
    LIFT_STUB(0xc3a90);
}

// 0xc3d20
bool __cdecl HandleArenaLobbyGameEnterRoomOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0xc3d20);
}

// 0xc4340
bool __cdecl HandleArenaLobbyGameEnterRoomFail(::Session const *, ::Packet const *)
{
    LIFT_STUB(0xc4340);
}

// 0xc4530
bool __cdecl HandleArenaLobbyGameEnterRoomNotify(::Session const *, ::Packet const *)
{
    LIFT_STUB(0xc4530);
}

// 0xc4b80
bool __cdecl HandleArenaLobbyGameReturnToRoomOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0xc4b80);
}

// 0xc4d30
bool __cdecl HandleArenaLobbyGameReturnToRoomFail(::Session const *, ::Packet const *)
{
    LIFT_STUB(0xc4d30);
}

// 0xc4fd0
bool __cdecl HandleArenaLobbyGameLeaveRoomOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0xc4fd0);
}

// 0xc5540
bool __cdecl HandleArenaLobbyGameLeaveRoomFail(::Session const *, ::Packet const *)
{
    LIFT_STUB(0xc5540);
}

// 0xc5870
bool __cdecl HandleArenaLobbyGameLeaveRoomNotify(::Session const *, ::Packet const *)
{
    LIFT_STUB(0xc5870);
}

// 0xc5e90
bool __cdecl HandleArenaLobbyGameSetRoomMatchOptionOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0xc5e90);
}

// 0xc6140
bool __cdecl HandleArenaLobbyGameSetRoomMatchOptionFail(::Session const *, ::Packet const *)
{
    LIFT_STUB(0xc6140);
}

// 0xc63d0
bool __cdecl HandleArenaLobbyGameSetRoomMatchOptionNotify(::Session const *, ::Packet const *)
{
    LIFT_STUB(0xc63d0);
}

// 0xc6a10
bool __cdecl HandleArenaLobbyGameDelegateTeamLeaderOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0xc6a10);
}

// 0xc6bf0
bool __cdecl HandleArenaLobbyGameDelegateTeamLeaderFail(::Session const *, ::Packet const *)
{
    LIFT_STUB(0xc6bf0);
}

// 0xc6e30
bool __cdecl HandleArenaLobbyGameDelegateTeamLeaderNotify(::Session const *, ::Packet const *)
{
    LIFT_STUB(0xc6e30);
}

// 0xc7340
bool __cdecl HandleArenaLobbyGameSetRoomPasswordOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0xc7340);
}

// 0xc7520
bool __cdecl HandleArenaLobbyGameSetRoomPasswordFail(::Session const *, ::Packet const *)
{
    LIFT_STUB(0xc7520);
}

// 0xc7730
bool __cdecl HandleArenaLobbyGameSetRoomPasswordNotify(::Session const *, ::Packet const *)
{
    LIFT_STUB(0xc7730);
}

// 0xc7c20
bool __cdecl HandleArenaLobbyGameJoinRoomOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0xc7c20);
}

// 0xc7e00
bool __cdecl HandleArenaLobbyGameJoinRoomFail(::Session const *, ::Packet const *)
{
    LIFT_STUB(0xc7e00);
}

// 0xc80b0
bool __cdecl HandleArenaLobbyGameBanishFromRoomOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0xc80b0);
}

// 0xc82d0
bool __cdecl HandleArenaLobbyGameBanishFromRoomFail(::Session const *, ::Packet const *)
{
    LIFT_STUB(0xc82d0);
}

// 0xc8560
bool __cdecl HandleArenaLobbyGameReadyToMatchOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0xc8560);
}

// 0xc8740
bool __cdecl HandleArenaLobbyGameReadyToMatchFail(::Session const *, ::Packet const *)
{
    LIFT_STUB(0xc8740);
}

// 0xc8a10
bool __cdecl HandleArenaLobbyGameReadyToMatchNotify(::Session const *, ::Packet const *)
{
    LIFT_STUB(0xc8a10);
}

// 0xc8f90
bool __cdecl HandleArenaLobbyGameUnReadyToMatchOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0xc8f90);
}

// 0xc9170
bool __cdecl HandleArenaLobbyGameUnReadyToMatchFail(::Session const *, ::Packet const *)
{
    LIFT_STUB(0xc9170);
}

// 0xc9390
bool __cdecl HandleArenaLobbyGameUnReadyToMatchNotify(::Session const *, ::Packet const *)
{
    LIFT_STUB(0xc9390);
}

// 0xc9910
bool __cdecl HandleArenaLobbyGameMatchRoomOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0xc9910);
}

// 0xc9af0
bool __cdecl HandleArenaLobbyGameMatchRoomFail(::Session const *, ::Packet const *)
{
    LIFT_STUB(0xc9af0);
}

// 0xc9e10
bool __cdecl HandleArenaLobbyGameSyncSeasonContentsInfoOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0xc9e10);
}

// 0xc9f10
bool __cdecl HandleArenaLobbyGameSyncSeasonContentsInfoFail(::Session const *, ::Packet const *)
{
    LIFT_STUB(0xc9f10);
}

// 0xca050
bool __cdecl HandleArenaLobbyGameMatchRoomFailAndUnReadListNotify(::Session const *, ::Packet const *)
{
    LIFT_STUB(0xca050);
}

// 0xca910
bool __cdecl HandleArenaLobbyGameStartMatchingNotify(::Session const *, ::Packet const *)
{
    LIFT_STUB(0xca910);
}

// 0xcadb0
bool __cdecl HandleArenaLobbyGameSkipMatchOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0xcadb0);
}

// 0xcaf90
bool __cdecl HandleArenaLobbyGameSkipMatchFail(::Session const *, ::Packet const *)
{
    LIFT_STUB(0xcaf90);
}

// 0xcb230
bool __cdecl HandleArenaLobbyGameSkipMatchNotify(::Session const *, ::Packet const *)
{
    LIFT_STUB(0xcb230);
}

// 0xcb6d0
bool __cdecl HandleArenaLobbyGameCancelMatchingOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0xcb6d0);
}

// 0xcb8b0
bool __cdecl HandleArenaLobbyGameCancelMatchingFail(::Session const *, ::Packet const *)
{
    LIFT_STUB(0xcb8b0);
}

// 0xcbad0
bool __cdecl HandleArenaLobbyGameCancelMatchingNotify(::Session const *, ::Packet const *)
{
    LIFT_STUB(0xcbad0);
}
