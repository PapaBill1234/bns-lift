// arenalobbycommon.cpp: arenalobbycommon.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "arenalobbycommon.h"
#include "pc.h"
#include "LiftStub.h"

// 0x45180
void __cdecl ArenaLobbySend::HelloGame(::Session const *, short)
{
    LIFT_STUB(0x45180);
}

// 0x453d0
void __cdecl ArenaLobbySend::HelloArena(::Session const *)
{
    LIFT_STUB(0x453d0);
}

// 0x45ae0
bool __cdecl ArenaLobbyRoomUtil::FetchArenaLobbyRoomInfo(::FragmentPacketConcatenater *, char, ::ArenaLobbyRoomInfo &)
{
    LIFT_STUB(0x45ae0);
}

// 0x45c40
bool __cdecl ArenaLobbyRoomUtil::FetchTeamList(::FragmentPacketConcatenater *, ::ArenaLobbyRoomInfo &)
{
    LIFT_STUB(0x45c40);
}

// 0x46230
bool __cdecl ArenaLobbyRoomUtil::FetchDungeonTeamMemberList(::Packet const *, ::RepeatPacketDecomposer &, ::ArenaLobbyRoomInfo &)
{
    LIFT_STUB(0x46230);
}

// 0x46760
bool __cdecl ArenaLobbyRoomUtil::FetchArenaLobbyRoomInfo2(::FragmentPacketConcatenater *, char, ::ArenaLobbyRoomInfo &)
{
    LIFT_STUB(0x46760);
}

// 0x468b0
bool __cdecl ArenaLobbyRoomUtil::FetchTeamList2(::FragmentPacketConcatenater *, ::ArenaLobbyRoomInfo &)
{
    LIFT_STUB(0x468b0);
}

// 0x46f10
int __cdecl ArenaLobbyRoomUtil::FetchSpectateGameList(::Packet const *, ::RepeatPacketDecomposer &, ::ArenaSpectateGameList *, int)
{
    LIFT_STUB(0x46f10);
}

// 0x47180
void __cdecl ArenaLobbyRoomUtil::BuildSpectateGameListPacket(::Packet &, ::RepeatPacketComposer &, ::ArenaSpectateGameList const *, int)
{
    LIFT_STUB(0x47180);
}

// 0x47300
void __cdecl ArenaLobbyRoomUtil::BuildBroadcastPacket(::FragmentPacket &, ::ArenaLobbyRoomInfo const &, unsigned int, unsigned __int64, int)
{
    LIFT_STUB(0x47300);
}

// 0x47500
void __cdecl ArenaLobbyRoomUtil::BuildTeamListPacketForClient(::FragmentPacket &, ::ArenaLobbyRoomInfo const &, int)
{
    LIFT_STUB(0x47500);
}

// 0x479d0
void __cdecl ArenaLobbyRoomUtil::BuildTeamListPacketForArenaLobby(::FragmentPacket &, ::ArenaLobbyRoomInfo const &)
{
    LIFT_STUB(0x479d0);
}

// 0x47ed0
void __cdecl ArenaLobbyRoomUtil::BuildTeamList2PacketForClient(::FragmentPacket &, ::ArenaLobbyRoomInfo const &)
{
    LIFT_STUB(0x47ed0);
}

// 0x48340
void __cdecl ArenaLobbyRoomUtil::BuildCreateRoomReqPacket(::Packet &, unsigned __int64, char, char, char, char, ::Pc **, int, unsigned __int64)
{
    LIFT_STUB(0x48340);
}

// 0x48fa0
bool __cdecl ArenaLobbyRoomUtil::FetchSelectedMapList(unsigned __int64, char, ::FragmentPacketConcatenater *, short &, short *const)
{
    LIFT_STUB(0x48fa0);
}

// 0x49100
void __cdecl ArenaLobbyRoomUtil::BuildSelectedMapListPacket(::FragmentPacket &, short, short const *const)
{
    LIFT_STUB(0x49100);
}

// 0x49200
void __cdecl ArenaLobbyRoomUtil::BuildArenaLobbyRoomInfo(::FragmentPacket &, __int64, ::ArenaLobbyRoomInfo const &)
{
    LIFT_STUB(0x49200);
}

// 0x49280
char __cdecl ArenaLobbyRoomUtil::ConvertGameGameModeToArenaLobbyGameMode(char, char)
{
    LIFT_STUB(0x49280);
}

// 0x49310
char __cdecl ArenaLobbyRoomUtil::ConvertArenaDungeonGameModeToDifficultyType(char)
{
    LIFT_STUB(0x49310);
}

// 0x49390
bool __cdecl ArenaLobbyRoomUtil::IsDungeonGameMode(char)
{
    LIFT_STUB(0x49390);
}

// 0x493a0
bool __cdecl ArenaLobbyRoomUtil::IsPartyBattleFieldGameMode(char)
{
    LIFT_STUB(0x493a0);
}

// 0x493b0
bool __cdecl ArenaLobbyRoomUtil::IsPublicRaidGameMode(char)
{
    LIFT_STUB(0x493b0);
}

// 0x493d0
int __cdecl ArenaLobbyRoomUtil::GetMaxTeamMemberCount(char, char)
{
    LIFT_STUB(0x493d0);
}

// 0x49520
int __cdecl ArenaLobbyRoomUtil::GetMinRatingScore(char)
{
    LIFT_STUB(0x49520);
}

// 0x49710
int __cdecl ArenaLobbyRoomUtil::GetMaxRatingScore(char)
{
    LIFT_STUB(0x49710);
}

// 0x49900
bool __cdecl ArenaLobbyRoomUtil::IsPreserveSessionInArenaEnable(char, char)
{
    LIFT_STUB(0x49900);
}

// 0x499b0
char __cdecl ArenaLobbyRoomUtil::convertArenaLobbyGameModeToArenaDungeonGameMode(char)
{
    LIFT_STUB(0x499b0);
}
