// arenalobbycommon.h: arenalobbycommon.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class ArenaLobbyRoomUtil
{
public:
    static bool __cdecl FetchArenaLobbyRoomInfo(::FragmentPacketConcatenater *, char, ::ArenaLobbyRoomInfo &);  // 0x45ae0
    static bool __cdecl FetchTeamList(::FragmentPacketConcatenater *, ::ArenaLobbyRoomInfo &);  // 0x45c40
    static bool __cdecl FetchDungeonTeamMemberList(::Packet const *, ::RepeatPacketDecomposer &, ::ArenaLobbyRoomInfo &);  // 0x46230
    static bool __cdecl FetchArenaLobbyRoomInfo2(::FragmentPacketConcatenater *, char, ::ArenaLobbyRoomInfo &);  // 0x46760
    static bool __cdecl FetchTeamList2(::FragmentPacketConcatenater *, ::ArenaLobbyRoomInfo &);  // 0x468b0
    static int __cdecl FetchSpectateGameList(::Packet const *, ::RepeatPacketDecomposer &, ::ArenaSpectateGameList *, int);  // 0x46f10
    static void __cdecl BuildSpectateGameListPacket(::Packet &, ::RepeatPacketComposer &, ::ArenaSpectateGameList const *, int);  // 0x47180
    static void __cdecl BuildBroadcastPacket(::FragmentPacket &, ::ArenaLobbyRoomInfo const &, unsigned int, unsigned __int64, int);  // 0x47300
    static void __cdecl BuildTeamListPacketForClient(::FragmentPacket &, ::ArenaLobbyRoomInfo const &, int);  // 0x47500
    static void __cdecl BuildTeamListPacketForArenaLobby(::FragmentPacket &, ::ArenaLobbyRoomInfo const &);  // 0x479d0
    static void __cdecl BuildTeamList2PacketForClient(::FragmentPacket &, ::ArenaLobbyRoomInfo const &);  // 0x47ed0
    static void __cdecl BuildCreateRoomReqPacket(::Packet &, unsigned __int64, char, char, char, char, ::Pc **, int, unsigned __int64);  // 0x48340
    static bool __cdecl FetchSelectedMapList(unsigned __int64, char, ::FragmentPacketConcatenater *, short &, short *const);  // 0x48fa0
    static void __cdecl BuildSelectedMapListPacket(::FragmentPacket &, short, short const *const);  // 0x49100
    static void __cdecl BuildArenaLobbyRoomInfo(::FragmentPacket &, __int64, ::ArenaLobbyRoomInfo const &);  // 0x49200
    static char __cdecl ConvertGameGameModeToArenaLobbyGameMode(char, char);  // 0x49280
    static char __cdecl ConvertArenaDungeonGameModeToDifficultyType(char);  // 0x49310
    static bool __cdecl IsDungeonGameMode(char);  // 0x49390
    static bool __cdecl IsPartyBattleFieldGameMode(char);  // 0x493a0
    static bool __cdecl IsPublicRaidGameMode(char);  // 0x493b0
    static int __cdecl GetMaxTeamMemberCount(char, char);  // 0x493d0
    static int __cdecl GetMinRatingScore(char);  // 0x49520
    static int __cdecl GetMaxRatingScore(char);  // 0x49710
    static bool __cdecl IsPreserveSessionInArenaEnable(char, char);  // 0x49900
private:
    static char __cdecl convertArenaLobbyGameModeToArenaDungeonGameMode(char);  // 0x499b0
};

class ArenaLobbySend
{
public:
    static void __cdecl HelloGame(::Session const *, short);  // 0x45180
    static void __cdecl HelloArena(::Session const *);  // 0x453d0
};

