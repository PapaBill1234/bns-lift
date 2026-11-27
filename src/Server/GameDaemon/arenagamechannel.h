// arenagamechannel.h: arenagamechannel.cpp, arenagamechannel.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class ArenaGameChannel
{
public:
    __cdecl ArenaGameChannel(::DaemonInfo const &);  // 0x36160
    bool __cdecl SendPing(void);  // 0x362e0
    void __cdecl CheckPing(void);  // 0x363a0
};

class ArenaGameManager
{
public:
    bool __cdecl Connect(::DaemonInfo const &);  // 0x42ca0
    bool __cdecl Disconnect(::DaemonInfo const &);  // 0x42e70
    bool __cdecl Send(unsigned int, char const *, ...);  // 0x42f40
    bool __cdecl Send(unsigned int, ::Packet const *);  // 0x43030
    static void __cdecl SendLogoutOk(::Session const *, unsigned __int64, unsigned __int64, char, ::Pc *);  // 0x43120
    bool __cdecl SendLogoutOk(short, unsigned __int64, unsigned __int64, char, ::Pc *);  // 0x43490
    bool __cdecl SendLeaveArenaReq(unsigned __int64, short, unsigned __int64, unsigned __int64, __int64, __int64, __int64, int, __int64, int, int, __int64, int, int, int, __int64, __int64, int, ::GradeLevelInfo &, ::GradeInfo *const, short);  // 0x43b60
    bool __cdecl SendLeaveArenaReq(short, unsigned __int64, unsigned __int64, unsigned __int64, __int64, __int64, __int64, int, __int64, int, int, __int64, int, int, int, __int64, __int64, int, ::GradeLevelInfo &, ::GradeInfo *const, short);  // 0x43e90
    bool __cdecl SendKickNotify(short, unsigned __int64, short);  // 0x441d0
    bool __cdecl SendUpdateSeasonContentsGuildCombatRecordNotify(short, unsigned __int64, char, char, int, __int64, char);  // 0x442a0
    bool __cdecl SendDepositGameMileageReq(short, ::MileageDepositContext const *, bool);  // 0x44370
    bool __cdecl SendCalcTimeBasedPlayInfoNotify(short, unsigned __int64);  // 0x446a0
    bool __cdecl SendUpdateChallengePartyMemberZoneInfoNotify(short, __int64, unsigned __int64, int);  // 0x447b0
    bool __cdecl SendUpdateAccountExpToLobbyNotify(short, unsigned __int64, ::AccountExpInfo const &);  // 0x44930
    bool __cdecl SendUpdateAccountContentQuotaToLobbyNotify(short, unsigned __int64, ::AccountContentQuota const &);  // 0x44a60
    bool __cdecl SendUpdateAccountRecycleTimeToLobbyNotify(short, unsigned __int64, ::AccountRecycleTime const &);  // 0x44c70
    void __cdecl CheckPing(void);  // 0x44e70
private:
    ::ArenaGameChannel * __cdecl acquire(unsigned int);  // 0x44fb0
public:
    void __cdecl Destroy(void);  // 0x45040
};

class ArenaGameSessionHandler
{
public:
    virtual bool __cdecl OnAccept(::Session const *) const;  // 0x36480
    virtual bool __cdecl OnConnect(::Session const *, bool) const;  // 0x364c0
    virtual void __cdecl OnClose(::Session const *, bool) const;  // 0x366d0
    virtual bool __cdecl PacketHandler(::Session const *, ::Packet const *) const;  // 0x368a0
};

class ArenaSideArenaLobbyChannel
{
public:
    virtual __cdecl ~ArenaSideArenaLobbyChannel(void);  // 0x3cc70
    bool __cdecl InitSession(void);  // 0x3cc80
    bool __cdecl SendCreateRoom(::Pc **, int, unsigned __int64, char, char, char, unsigned __int64);  // 0x3cd10
    bool __cdecl SendPublishRecruitArenaDungeonMember(unsigned __int64, unsigned __int64, unsigned __int64, unsigned __int64, unsigned __int64, char, short);  // 0x3cea0
    bool __cdecl SendCancelRecruitArenaDungeonMember(unsigned __int64, unsigned __int64, unsigned __int64, unsigned __int64, unsigned __int64, char, short, char);  // 0x3d080
    bool __cdecl SendPing(void);  // 0x3d2c0
    void __cdecl CheckPing(void);  // 0x3d380
protected:
    virtual ::Session * __cdecl getSession(void);  // 0x3d440
    virtual bool __cdecl onConnect(::Session const *, bool);  // 0x3d4f0
    virtual void __cdecl onClose(::Session const *, bool, bool);  // 0x3d5a0
    virtual bool __cdecl PacketHandler(::Session const *, ::Packet const *) const;  // 0x3d670
};

bool __cdecl HandleArenaGameArenaHelloOk(::Session const *, ::Packet const *);  // 0x36c40
bool __cdecl HandleArenaGameArenaHelloFail(::Session const *, ::Packet const *);  // 0x37030
bool __cdecl HandleArenaGameArenaEnterArenaReq(::Session const *, ::Packet const *);  // 0x37090
bool __cdecl HandleArenaGameArenaLeaveArenaOk(::Session const *, ::Packet const *);  // 0x38740
bool __cdecl HandleArenaGameArenaLeaveArenaFail(::Session const *, ::Packet const *);  // 0x38820
bool __cdecl HandleArenaGameArenaLogoutReq(::Session const *, ::Packet const *);  // 0x38a50
bool __cdecl HandleArenaGameArenaGuildMemberInfoOk(::Session const *, ::Packet const *);  // 0x38f10
bool __cdecl HandleArenaGameArenaRenameGuildNotify(::Session const *, ::Packet const *);  // 0x39320
bool __cdecl HandleArenaGameArenaRenameGuildByManagementDNotify(::Session const *, ::Packet const *);  // 0x39480
bool __cdecl HandleArenaGameArenaPingOk(::Session const *, ::Packet const *);  // 0x395e0
bool __cdecl HandleArenaGameArenaGamePlayRestrictLevelOk(::Session const *, ::Packet const *);  // 0x396e0
bool __cdecl HandleArenaGameArenaGamePlayRestrictLevelForHealthySystemOk(::Session const *, ::Packet const *);  // 0x399c0
bool __cdecl HandleArenaGameGameGradeListReq(::Session const *, ::Packet const *);  // 0x39c60
bool __cdecl HandleArenaGameArenaGradeListOk(::Session const *, ::Packet const *);  // 0x39da0
bool __cdecl HandleArenaGameArenaGradeListFail(::Session const *, ::Packet const *);  // 0x3a1c0
bool __cdecl HandleArenaGameArenaChangedGradeNotify(::Session const *, ::Packet const *);  // 0x3a3d0
bool __cdecl HandleArenaGameArenaChangedGradeLevelNotify(::Session const *, ::Packet const *);  // 0x3a5c0
bool __cdecl HandleArenaGameArenaUpdateArenaSessionTimerReq(::Session const *, ::Packet const *);  // 0x3a790
bool __cdecl HandleArenaGameGameUpdateArenaSessionTimerOk(::Session const *, ::Packet const *);  // 0x3a9a0
bool __cdecl HandleArenaGameGameDepositGameMileageReq(::Session const *, ::Packet const *);  // 0x3adb0
bool __cdecl HandleArenaGameArenaDepositGameMileageOk(::Session const *, ::Packet const *);  // 0x3afc0
bool __cdecl HandleArenaGameArenaDepositGameMileageFail(::Session const *, ::Packet const *);  // 0x3b8a0
bool __cdecl HandleArenaGameArenaChangedGuildBuffNotify(::Session const *, ::Packet const *);  // 0x3c000
bool __cdecl HandleArenaGameGameCalcTimeBasedPlayInfoNotify(::Session const *, ::Packet const *);  // 0x3c390
bool __cdecl HandleArenaGameGameUpdateChallengePartyMemberZoneInfoNotify(::Session const *, ::Packet const *);  // 0x3c480
bool __cdecl HandleArenaGameGameUpdateAccountExpToLobbyNotify(::Session const *, ::Packet const *);  // 0x3c5a0
bool __cdecl HandleArenaGameGameUpdateAccountContentQuotaToLobbyNotify(::Session const *, ::Packet const *);  // 0x3c6b0
bool __cdecl HandleArenaGameGameUpdateAccountRecycleTimeToLobbyNotify(::Session const *, ::Packet const *);  // 0x3c980
bool __cdecl HandleArenaLobbyArenaHelloOk(::Session const *, ::Packet const *);  // 0x3d740
bool __cdecl HandleArenaLobbyArenaHelloFail(::Session const *, ::Packet const *);  // 0x3d850
bool __cdecl HandleArenaLobbyArenaConnectGameNotify(::Session const *, ::Packet const *);  // 0x3d8c0
bool __cdecl HandleArenaLobbyArenaDisconnectGameNotify(::Session const *, ::Packet const *);  // 0x3d9b0
bool __cdecl HandleArenaLobbyArenaRelayFailNotify(::Session const *, ::Packet const *);  // 0x3da90
bool __cdecl HandleArenaLobbyArenaCreateRoomFail(::Session const *, ::Packet const *);  // 0x3db00
bool __cdecl HandleArenaLobbyArenaCreateRoomNotify(::Session const *, ::Packet const *);  // 0x3df70
bool __cdecl HandleArenaLobbyArenaReserveArenaReq(::Session const *, ::Packet const *);  // 0x3e910
bool __cdecl HandleArenaLobbyArenaReserveReturnToArenaReq(::Session const *, ::Packet const *);  // 0x3f1e0
bool __cdecl HandleArenaLobbyArenaReserveSpectatorToArenaReq(::Session const *, ::Packet const *);  // 0x3fb60
bool __cdecl HandleArenaLobbyArenaRemoveArenaLobbyMemberOk(::Session const *, ::Packet const *);  // 0x40330
bool __cdecl HandleArenaLobbyArenaRemoveArenaLobbyMemberFail(::Session const *, ::Packet const *);  // 0x40430
bool __cdecl HandleArenaLobbyArenaPublishRecruitArenaDungeonMemberOk(::Session const *, ::Packet const *);  // 0x40530
bool __cdecl HandleArenaLobbyArenaPublishRecruitArenaDungeonMemberFail(::Session const *, ::Packet const *);  // 0x40920
bool __cdecl HandleArenaLobbyArenaCancelRecruitArenaDungeonMemberOk(::Session const *, ::Packet const *);  // 0x40ba0
bool __cdecl HandleArenaLobbyArenaCancelRecruitArenaDungeonMemberFail(::Session const *, ::Packet const *);  // 0x41120
bool __cdecl HandleArenaLobbyArenaReserveRecruitMemberToArenaReq(::Session const *, ::Packet const *);  // 0x413f0
bool __cdecl HandleArenaLobbyArenaPingOk(::Session const *, ::Packet const *);  // 0x42c00
