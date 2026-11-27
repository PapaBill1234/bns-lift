// gamearenachannel.h: gamearenachannel.cpp, gamearenachannel.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class GameArenaLobbyManager
{
public:
    __cdecl GameArenaLobbyManager(void);  // 0xd3000
    bool __cdecl Initialize(short, short *const);  // 0xd3080
    void __cdecl Destroy(void);  // 0xd3460
    void __cdecl CheckPing(void);  // 0xd35d0
    void __cdecl ResetIsInitializeGuildInfo(void);  // 0xd3720
    void __cdecl SetConnectedWorld(short, bool);  // 0xd37b0
    bool __cdecl IsCloseAllConnection(void);  // 0xd3890
private:
    ::GameSideArenaLobbyChannel * __cdecl acquire(unsigned int);  // 0xd3960
    ::GameSideArenaLobbyChannel * __cdecl acquireFirstSession(void);  // 0xd3a30
public:
    bool __cdecl Send(short, char const *, ...);  // 0xd3ab0
    bool __cdecl Send(short, ::Packet const *);  // 0xd3ba0
    bool __cdecl SendFirstSession(::Packet const *);  // 0xd3c90
    bool __cdecl SendCreateRoom(short, ::Pc **, int, unsigned __int64, char, char, unsigned __int64, char);  // 0xd3d80
    bool __cdecl SendReserveReturnToArenaLobby(::Pc *, unsigned __int64, unsigned __int64, unsigned int, short);  // 0xd3eb0
    bool __cdecl SendRelayPacket(short, ::DaemonId, wchar_t const *, wchar_t const *, __int64, ::Packet const *);  // 0xd3fa0
    bool __cdecl SendInitializeGuildInfoList(void);  // 0xd4240
    bool __cdecl SendInitializeGuildInfoListNolock(void);  // 0xd4350
    bool __cdecl SendUpdateGuildInfo(unsigned __int64, char, int, int, __int64);  // 0xd44c0
    bool __cdecl SendSyncSeasonContentsInfoReq(::Pc const *, unsigned __int64, short, ::SeasonContentsSyncData *const);  // 0xd47a0
};

class GameArenaManager
{
public:
    __cdecl ~GameArenaManager(void);  // 0xd0b80
    bool __cdecl Send(unsigned int, unsigned int, ::Packet const *);  // 0xd0c00
    bool __cdecl Broadcast(::Packet const *);  // 0xd0d00
    bool __cdecl SendLogoutReq(unsigned int, unsigned __int64, unsigned int, unsigned __int64, short);  // 0xd0ef0
    bool __cdecl SendLogoutReq(unsigned int, unsigned int, unsigned __int64, unsigned __int64, short);  // 0xd1000
    bool __cdecl BroadcastLogin(unsigned __int64);  // 0xd1110
    bool __cdecl BroadcastRenameGuild(unsigned __int64, wchar_t const *);  // 0xd11e0
    bool __cdecl BroadcastRenameGuildByManagement(unsigned __int64, wchar_t const *);  // 0xd1310
    bool __cdecl SendDepositGameMileageOk(unsigned int, unsigned int, unsigned __int64, char, unsigned __int64, unsigned __int64, unsigned __int64, ::id128, __int64, short, __int64, int);  // 0xd1410
    bool __cdecl SendDepositGameMileageFail(unsigned int, unsigned int, unsigned __int64, char, unsigned __int64, unsigned __int64, unsigned __int64, ::id128, short, int);  // 0xd1580
private:
    ::GameArenaChannel * __cdecl acquire(unsigned int, unsigned int);  // 0xd16d0
public:
    bool __cdecl ReserveConfirm(::GameArenaChannel *);  // 0xd17c0
    void __cdecl ClearReserved(short);  // 0xd18b0
    void __cdecl ConfirmOk(unsigned int, __int64, unsigned int);  // 0xd1a90
    void __cdecl ConfirmFail(__int64, unsigned int);  // 0xd2080
    bool __cdecl Remove(::GameArenaChannel *);  // 0xd21e0
    void __cdecl Destroy(void);  // 0xd2320
    void __cdecl CheckPing(__int64);  // 0xd2460
};

class GameArenaSessionHandler
{
public:
    virtual bool __cdecl OnAccept(::Session const *) const;  // 0xbdb30
    virtual bool __cdecl OnConnect(::Session const *, bool) const;  // 0xbdb70
    virtual void __cdecl OnClose(::Session const *, bool) const;  // 0xbdbb0
    virtual bool __cdecl PacketHandler(::Session const *, ::Packet const *) const;  // 0xbdcd0
};

class GameSideArenaLobbyChannel
{
public:
    void __cdecl Initialize(short);  // 0xd2d10
    bool __cdecl SendPing(void);  // 0xd2e50
    void __cdecl CheckPing(void);  // 0xd2f20
    virtual unsigned __int64 __cdecl GetId(void);  // 0x1105d0
};

class GameSideArenaLobbySessionHandler
{
public:
    virtual bool __cdecl OnAccept(::Session const *) const;  // 0xd26d0
    virtual bool __cdecl OnConnect(::Session const *, bool) const;  // 0xd2710
    virtual void __cdecl OnClose(::Session const *, bool) const;  // 0xd2960
    virtual bool __cdecl PacketHandler(::Session const *, ::Packet const *) const;  // 0xd2be0
};

bool __cdecl HandleArenaGameGameHelloReq(::Session const *, ::Packet const *);  // 0xbe1b0
bool __cdecl HandleArenaGameGameEnterArenaOk(::Session const *, ::Packet const *);  // 0xbe4c0
bool __cdecl HandleArenaGameGameEnterArenaFail(::Session const *, ::Packet const *);  // 0xbe990
bool __cdecl HandleArenaGameGameLeaveArenaReq(::Session const *, ::Packet const *);  // 0xbeb40
bool __cdecl HandleArenaGameGameLogoutOk(::Session const *, ::Packet const *);  // 0xbf250
bool __cdecl HandleArenaGameGameForwardToCacheReq(::Session const *, ::Packet const *);  // 0xc0090
bool __cdecl HandleArenaGameGameGuildMemberInfoReq(::Session const *, ::Packet const *);  // 0xc0240
bool __cdecl HandleArenaGameGameKickNotify(::Session const *, ::Packet const *);  // 0xc03a0
bool __cdecl HandleArenaGameGameUpdateSeasonContentsGuildCombatRecordNotify(::Session const *, ::Packet const *);  // 0xc0450
bool __cdecl HandleArenaGameGamePingReq(::Session const *, ::Packet const *);  // 0xc0670
bool __cdecl HandleArenaGameGameGamePlayRestrictLevelReq(::Session const *, ::Packet const *);  // 0xc07a0
bool __cdecl HandleArenaGameGameGamePlayRestrictLevelForHealthySystemReq(::Session const *, ::Packet const *);  // 0xc0900
bool __cdecl HandleArenaLobbyGameHelloOk(::Session const *, ::Packet const *);  // 0xc0a60
bool __cdecl HandleArenaLobbyGameHelloFail(::Session const *, ::Packet const *);  // 0xc0bd0
bool __cdecl HandleArenaLobbyGameInitializeGuildInfoListOk(::Session const *, ::Packet const *);  // 0xc0ca0
bool __cdecl HandleArenaLobbyGameConfirmArenaOk(::Session const *, ::Packet const *);  // 0xc0d20
bool __cdecl HandleArenaLobbyGameConfirmArenaFail(::Session const *, ::Packet const *);  // 0xc0ea0
bool __cdecl HandleArenaLobbyGameRelay(::Session const *, ::Packet const *);  // 0xc0f60
bool __cdecl HandleArenaLobbyGameRelayFailNotify(::Session const *, ::Packet const *);  // 0xc1360
bool __cdecl HandleArenaLobbyGameInviteUnratedRoomOk(::Session const *, ::Packet const *);  // 0xc15b0
bool __cdecl HandleArenaLobbyGameInviteUnratedRoomFail(::Session const *, ::Packet const *);  // 0xc1790
bool __cdecl HandleArenaLobbyGameInviteUnratedRoomNotify(::Session const *, ::Packet const *);  // 0xc19d0
bool __cdecl HandleArenaLobbyGameCreateRoomFail(::Session const *, ::Packet const *);  // 0xc1ed0
bool __cdecl HandleArenaLobbyGameCreateRoomNotify(::Session const *, ::Packet const *);  // 0xc2390
bool __cdecl HandleArenaLobbyGameLastestArenaLobbyRoomInfoNotify(::Session const *, ::Packet const *);  // 0xc3470
bool __cdecl HandleArenaLobbyGameReserveReturnToArenaLobbyFail(::Session const *, ::Packet const *);  // 0xc3a90
bool __cdecl HandleArenaLobbyGameEnterRoomOk(::Session const *, ::Packet const *);  // 0xc3d20
bool __cdecl HandleArenaLobbyGameEnterRoomFail(::Session const *, ::Packet const *);  // 0xc4340
bool __cdecl HandleArenaLobbyGameEnterRoomNotify(::Session const *, ::Packet const *);  // 0xc4530
bool __cdecl HandleArenaLobbyGameReturnToRoomOk(::Session const *, ::Packet const *);  // 0xc4b80
bool __cdecl HandleArenaLobbyGameReturnToRoomFail(::Session const *, ::Packet const *);  // 0xc4d30
bool __cdecl HandleArenaLobbyGameLeaveRoomOk(::Session const *, ::Packet const *);  // 0xc4fd0
bool __cdecl HandleArenaLobbyGameLeaveRoomFail(::Session const *, ::Packet const *);  // 0xc5540
bool __cdecl HandleArenaLobbyGameLeaveRoomNotify(::Session const *, ::Packet const *);  // 0xc5870
bool __cdecl HandleArenaLobbyGameSetRoomMatchOptionOk(::Session const *, ::Packet const *);  // 0xc5e90
bool __cdecl HandleArenaLobbyGameSetRoomMatchOptionFail(::Session const *, ::Packet const *);  // 0xc6140
bool __cdecl HandleArenaLobbyGameSetRoomMatchOptionNotify(::Session const *, ::Packet const *);  // 0xc63d0
bool __cdecl HandleArenaLobbyGameDelegateTeamLeaderOk(::Session const *, ::Packet const *);  // 0xc6a10
bool __cdecl HandleArenaLobbyGameDelegateTeamLeaderFail(::Session const *, ::Packet const *);  // 0xc6bf0
bool __cdecl HandleArenaLobbyGameDelegateTeamLeaderNotify(::Session const *, ::Packet const *);  // 0xc6e30
bool __cdecl HandleArenaLobbyGameSetRoomPasswordOk(::Session const *, ::Packet const *);  // 0xc7340
bool __cdecl HandleArenaLobbyGameSetRoomPasswordFail(::Session const *, ::Packet const *);  // 0xc7520
bool __cdecl HandleArenaLobbyGameSetRoomPasswordNotify(::Session const *, ::Packet const *);  // 0xc7730
bool __cdecl HandleArenaLobbyGameJoinRoomOk(::Session const *, ::Packet const *);  // 0xc7c20
bool __cdecl HandleArenaLobbyGameJoinRoomFail(::Session const *, ::Packet const *);  // 0xc7e00
bool __cdecl HandleArenaLobbyGameBanishFromRoomOk(::Session const *, ::Packet const *);  // 0xc80b0
bool __cdecl HandleArenaLobbyGameBanishFromRoomFail(::Session const *, ::Packet const *);  // 0xc82d0
bool __cdecl HandleArenaLobbyGameReadyToMatchOk(::Session const *, ::Packet const *);  // 0xc8560
bool __cdecl HandleArenaLobbyGameReadyToMatchFail(::Session const *, ::Packet const *);  // 0xc8740
bool __cdecl HandleArenaLobbyGameReadyToMatchNotify(::Session const *, ::Packet const *);  // 0xc8a10
bool __cdecl HandleArenaLobbyGameUnReadyToMatchOk(::Session const *, ::Packet const *);  // 0xc8f90
bool __cdecl HandleArenaLobbyGameUnReadyToMatchFail(::Session const *, ::Packet const *);  // 0xc9170
bool __cdecl HandleArenaLobbyGameUnReadyToMatchNotify(::Session const *, ::Packet const *);  // 0xc9390
bool __cdecl HandleArenaLobbyGameMatchRoomOk(::Session const *, ::Packet const *);  // 0xc9910
bool __cdecl HandleArenaLobbyGameMatchRoomFail(::Session const *, ::Packet const *);  // 0xc9af0
bool __cdecl HandleArenaLobbyGameSyncSeasonContentsInfoOk(::Session const *, ::Packet const *);  // 0xc9e10
bool __cdecl HandleArenaLobbyGameSyncSeasonContentsInfoFail(::Session const *, ::Packet const *);  // 0xc9f10
bool __cdecl HandleArenaLobbyGameMatchRoomFailAndUnReadListNotify(::Session const *, ::Packet const *);  // 0xca050
bool __cdecl HandleArenaLobbyGameStartMatchingNotify(::Session const *, ::Packet const *);  // 0xca910
bool __cdecl HandleArenaLobbyGameSkipMatchOk(::Session const *, ::Packet const *);  // 0xcadb0
bool __cdecl HandleArenaLobbyGameSkipMatchFail(::Session const *, ::Packet const *);  // 0xcaf90
bool __cdecl HandleArenaLobbyGameSkipMatchNotify(::Session const *, ::Packet const *);  // 0xcb230
bool __cdecl HandleArenaLobbyGameCancelMatchingOk(::Session const *, ::Packet const *);  // 0xcb6d0
bool __cdecl HandleArenaLobbyGameCancelMatchingFail(::Session const *, ::Packet const *);  // 0xcb8b0
bool __cdecl HandleArenaLobbyGameCancelMatchingNotify(::Session const *, ::Packet const *);  // 0xcbad0
bool __cdecl HandleArenaLobbyGameCancelMatchOk(::Session const *, ::Packet const *);  // 0xcbfb0
bool __cdecl HandleArenaLobbyGameCancelMatchFail(::Session const *, ::Packet const *);  // 0xcc190
bool __cdecl HandleArenaLobbyGameReadyToGoToArenaOk(::Session const *, ::Packet const *);  // 0xcc3b0
bool __cdecl HandleArenaLobbyGameReadyToGoToArenaFail(::Session const *, ::Packet const *);  // 0xcc590
bool __cdecl HandleArenaLobbyGameReadyToGoToArenaNotify(::Session const *, ::Packet const *);  // 0xcc7b0
bool __cdecl HandleArenaLobbyGameDecideToGoToArenaOk(::Session const *, ::Packet const *);  // 0xccd30
bool __cdecl HandleArenaLobbyGameDecideToGoToArenaFail(::Session const *, ::Packet const *);  // 0xccf10
bool __cdecl HandleArenaLobbyGameDecideToGoToArenaNotify(::Session const *, ::Packet const *);  // 0xcd150
bool __cdecl HandleArenaLobbyGameStartWaitingNotify(::Session const *, ::Packet const *);  // 0xcd6d0
bool __cdecl HandleArenaLobbyGameRetrieveWaitingNumberOk(::Session const *, ::Packet const *);  // 0xcdcd0
bool __cdecl HandleArenaLobbyGameRetrieveWaitingNumberFail(::Session const *, ::Packet const *);  // 0xcdee0
bool __cdecl HandleArenaLobbyGameCancelWaitingOk(::Session const *, ::Packet const *);  // 0xce130
bool __cdecl HandleArenaLobbyGameCancelWaitingFail(::Session const *, ::Packet const *);  // 0xce320
bool __cdecl HandleArenaLobbyGameReserveArenaNotify(::Session const *, ::Packet const *);  // 0xce570
bool __cdecl HandleArenaLobbyGameChattingServerAuthenticateUserReq(::Session const *, ::Packet const *);  // 0xcece0
bool __cdecl HandleArenaLobbyGamePingOk(::Session const *, ::Packet const *);  // 0xcefd0
bool __cdecl HandleArenaLobbyGameSpectateGameOk(::Session const *, ::Packet const *);  // 0xcf100
bool __cdecl HandleArenaLobbyGameSpectateGameFail(::Session const *, ::Packet const *);  // 0xcf7a0
bool __cdecl HandleArenaLobbyGameListSpectateGameOk(::Session const *, ::Packet const *);  // 0xcfac0
bool __cdecl HandleArenaLobbyGameListSpectateGameFail(::Session const *, ::Packet const *);  // 0xcff80
bool __cdecl HandleArenaLobbyGameMoveToArenaOk(::Session const *, ::Packet const *);  // 0xd01e0
bool __cdecl HandleArenaLobbyGameMoveToArenaFail(::Session const *, ::Packet const *);  // 0xd0410
bool __cdecl HandleArenaLobbyGameFindArenaSessionOk(::Session const *, ::Packet const *);  // 0xd06d0
bool __cdecl HandleArenaLobbyGameFindArenaSessionFail(::Session const *, ::Packet const *);  // 0xd0970
