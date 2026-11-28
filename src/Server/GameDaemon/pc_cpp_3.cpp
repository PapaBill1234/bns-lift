// pc_cpp_3.cpp: pc.cpp part 3 (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "pc.h"
#include "creature.h"
#include "npcdeadbody.h"
#include "raiddungeon.h"
#include "task.h"
#include "transactionexpirechecker.h"
#include "zone.h"
#include "zoneserializedobject.h"
#include "Daemon.h"
#include "Log.h"
#include "LiftStub.h"

#pragma comment(linker, "/INCLUDE:?isActivatedGrade@Pc@@AEBA_NH@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetRewardContribution@Pc@@QEAA_J_K_J@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?AvailableTurnBack@Pc@@QEAA_NXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?BeginArenaLobbyReservation@Pc@@QEAA_N_KD@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?RollbackArenaLobbyReservation@Pc@@QEAAXXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?LeaveArenaLobbyOk@Pc@@QEAA_NXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?ReturnToGameByEnterFail@Pc@@QEAAXXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetArenaSessionState@Pc@@QEBA?AW4ArenaSession@1@XZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?IsInArenaOrArenaLobby@Pc@@QEBA_NXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?checkTeamGuildBattleFieldWithTarget@Pc@@QEAA_NPEAVCreature@@@Z")  // LIFT: dead-strip keep (no live caller yet)

#define PC_CPP_FILE L"e:\\dailybuild02\\gamedaemon-common-0.0.348\\depot\\branch\\348nc\\program\\server\\gamedaemon\\Pc.cpp"

namespace
{
// LIFT: views of PDB classes whose members the skeleton does not declare. Offsets are from the PDB.

// LIFT: view of GradeInfo (size 0x20). gameGradeKey +0, activation +8.
struct GradeInfoView
{
    int gameGradeKey;      // +0x0
    int gradeId;           // +0x4
    char activation;       // +0x8
    char lift_pad_0[0x20 - 0x9];
};

// LIFT: view of PcContribution (size 0x28).
struct PcContributionView
{
    unsigned __int64 _npcId;       // +0x0
    __int64 _combatStartTime;      // +0x8
    char _contributionType;        // +0x10
    char lift_pad_0[7];
    __int64 _damage[2];            // +0x18
};

// LIFT: view of Zone. GeoZoneData at +0x3F60, _guildBattleFieldMgr at +0x43A0.
struct ZoneView
{
    char lift_pad_0[0x3F60];
    void const *GeoZoneData;            // +0x3F60
    char lift_pad_1[0x43A0 - 0x3F68];
    void *_guildBattleFieldMgr;         // +0x43A0
};

// LIFT: view of Creature (Id +0x28, Prop.State.guild_id +0x150, zone +0x8B8).
struct CreatureView
{
    char lift_pad_0[0x28];
    unsigned __int64 Id;                // +0x28
    char lift_pad_1[0x150 - 0x30];
    __int64 guild_id;                   // +0x150. Prop (+0x30) .State (+0xD8) .guild_id (+0x48)
    char lift_pad_2[0x8B8 - 0x158];
    ZoneView *zone;                     // +0x8B8
};

// LIFT: view of Pc. The skeleton class declares only part of its PDB members.
struct PcView
{
    char lift_pad_0[0x28];
    unsigned __int64 Id;                // +0x28
    char lift_pad_1[0x150 - 0x30];
    __int64 guild_id;                   // +0x150
    char lift_pad_2[0x8B8 - 0x158];
    ZoneView *zone;                     // +0x8B8
    char lift_pad_3[0x3050 - 0x8C0];
    short _gradeCount;                  // +0x3050
    char lift_pad_4[0x3058 - 0x3052];
    GradeInfoView _gradeList[32];       // +0x3058
    char lift_pad_5[0x4E10 - (0x3058 + 32 * 0x20)];
    unsigned __int64 _pcDbId;           // +0x4E10
    char lift_pad_6[0x4E98 - 0x4E18];
    __int64 _enterPortalFailStamp;      // +0x4E98
    char lift_pad_7[0x8EC0 - 0x4EA0];
    CRITICAL_SECTION _arenaLock;        // +0x8EC0. LIFT: PDB type CriticalSection (CS at +0, size 0x28)
    int _arenaSession;                  // +0x8EE8. LIFT: PDB type Pc::ArenaSession
    char lift_pad_8[4];
    unsigned __int64 _arenaLobbyEnterParam_roomId;          // +0x8EF0
    unsigned __int64 _arenaLobbyEnterParam_pcArenaLobbyId;  // +0x8EF8
    unsigned __int64 _arenaLobbyEnterParam_portalKey;       // +0x8F00
    char _arenaLobbyEnterParam_attraction;                  // +0x8F08
    char lift_pad_9[0x8F28 - 0x8F09];
    char _reserveArenaParam[0x50];      // +0x8F28. LIFT: PDB type ReserveArenaParam
    char lift_pad_10[0x9055 - 0x8F78];
    char _arenaGameGameMode;            // +0x9055
    char lift_pad_11[0x9068 - 0x9056];
    PcContributionView _contributionList[2];  // +0x9068
    char _contributionCount;            // +0x90B8
};

// LIFT: values of Pc::ArenaSession.
enum
{
    LIFT_ARENA_SESSION_IN_WORLD = 1,
    LIFT_ARENA_SESSION_MOVE_TO_ARENA_LOBBY = 2,
    LIFT_ARENA_SESSION_IN_ARENA_LOBBY = 3,
    LIFT_ARENA_SESSION_RETURN_TO_GAME = 4,
};
}  // namespace

// 0x5f70b0
void __cdecl Pc::ActivateGradeBenefit(int)
{
    LIFT_STUB(0x5f70b0);
}

// 0x5f7390
void __cdecl Pc::ActivateGradeEffectBenefits(void)
{
    LIFT_STUB(0x5f7390);
}

// 0x5f7580
void __cdecl Pc::DeactivateAllGradeBenefits(bool)
{
    LIFT_STUB(0x5f7580);
}

// 0x5f7610
void __cdecl Pc::DeactivateGradeBenefit(int, bool &)
{
    LIFT_STUB(0x5f7610);
}

// 0x5f7860
void __cdecl Pc::onGradeTimerExpired(void)
{
    LIFT_STUB(0x5f7860);
}

// 0x5f7a90
bool __cdecl Pc::IsAvailableGradeAchievement(short, short)
{
    LIFT_STUB(0x5f7a90);
}

// 0x5f7b90
bool __cdecl Pc::IsAllowedContent(char)
{
    LIFT_STUB(0x5f7b90);
}

// 0x5f7d50
bool __cdecl Pc::isActivatedGrade(int gradeKey) const
{
    PcView const *self = reinterpret_cast<PcView const *>(this);
    for (short i = 0; i < self->_gradeCount; ++i)
    {
        if (self->_gradeList[i].activation != 0 && gradeKey == self->_gradeList[i].gameGradeKey)
            return true;
    }
    return false;
}

// 0x5f7d90
void __cdecl Pc::invokeGradeEffect(int)
{
    LIFT_STUB(0x5f7d90);
}

// 0x5f7f00
void __cdecl Pc::deactivateGradeVitalityBonus(void)
{
    LIFT_STUB(0x5f7f00);
}

// 0x5f8180
void __cdecl Pc::checkAndDeactivateGradeAchievementBenefit(void)
{
    LIFT_STUB(0x5f8180);
}

// 0x5f8350
void __cdecl Pc::IncreaseContribution(unsigned __int64, __int64, char, __int64)
{
    LIFT_STUB(0x5f8350);
}

// 0x5f8400
void __cdecl Pc::insertContribution(unsigned __int64, __int64, char, __int64)
{
    LIFT_STUB(0x5f8400);
}

// 0x5f8590
__int64 __cdecl Pc::GetRewardContribution(unsigned __int64 npcId, __int64 combatStartTime)
{
    PcView *self = reinterpret_cast<PcView *>(this);
    char contributionCount = self->_contributionCount;
    char i = 0;
    if (contributionCount <= 0)
        return 0;
    while (self->_contributionList[i]._npcId != npcId || self->_contributionList[i]._combatStartTime != combatStartTime)
    {
        if (++i >= contributionCount)
            return 0;
    }
    return self->_contributionList[i]._damage[1];
}

// 0x5f85e0
__int64 __cdecl Pc::RegisterContributionPouch(::NpcDeadBody &, __int64, __int64, __int64)
{
    LIFT_STUB(0x5f85e0);
}

// 0x5f8800
void __cdecl Pc::insertContributionPouch(::NpcDeadBody &, __int64, __int64)
{
    LIFT_STUB(0x5f8800);
}

// 0x5f8bc0
::GameFailReason __cdecl Pc::TakeContributionReward(::NpcDeadBody &)
{
    LIFT_STUB(0x5f8bc0);
}

// 0x5f8e60
int __cdecl Pc::TakeContributionFactionScore(::NpcDeadBody &, int, __int64)
{
    LIFT_STUB(0x5f8e60);
}

// 0x5f8f50
bool __cdecl Pc::SetExceptLootCaseBitMap(unsigned __int64, int, char)
{
    LIFT_STUB(0x5f8f50);
}

// 0x5f8fb0
void __cdecl Pc::sendContributionPouchList(unsigned __int64)
{
    LIFT_STUB(0x5f8fb0);
}

// 0x5f9220
void __cdecl Pc::ResetAllGroupContribution(void)
{
    LIFT_STUB(0x5f9220);
}

// 0x5f9360
void __cdecl Pc::ResetContribution(char, __int64)
{
    LIFT_STUB(0x5f9360);
}

// 0x5f95b0
void __cdecl Pc::SetMaxLevel(void)
{
    LIFT_STUB(0x5f95b0);
}

// 0x5f9860
bool __cdecl Pc::CheckRechargeVitality(void)
{
    LIFT_STUB(0x5f9860);
}

// 0x5f99a0
bool __cdecl Pc::RechargeVitality(::ChangedProperty *)
{
    LIFT_STUB(0x5f99a0);
}

// 0x5f9e00
void __cdecl Pc::CutOffVitality(::ChangedProperty *)
{
    LIFT_STUB(0x5f9e00);
}

// 0x5fa120
void __cdecl Pc::SendEnterPortalFail(::GameFailReason)
{
    LIFT_STUB(0x5fa120);
}

// 0x5fa2a0
bool __cdecl Pc::AvailableTurnBack(void)
{
    PcView *self = reinterpret_cast<PcView *>(this);
    if (self->_enterPortalFailStamp == 0)
    {
        // LIFT: the format string is in .rdata (Hex-Rays shows zone._extraPrivateProp[3532]). "hi" = short, int. ❓
        Send("hi", 297, 1186);
        Log::Write(Log::LT_DEBUG, PC_CPP_FILE, 13848, L"[turn back portal], fail to turn back for not portal fail, pc:%I64x",
                   self->Id);
        return false;
    }
    if ((__int64)(GetTickCount64() - Daemon::Instance->StartSystemTick64 - self->_enterPortalFailStamp) > 30000)
    {
        Send("hi", 297, 1185);
        Log::Write(Log::LT_DEBUG, PC_CPP_FILE, 13857, L"[turn back portal], fail to turn back for too late, pc:%I64x",
                   self->Id);
        return false;
    }
    return true;
}

// 0x5fa360
bool __cdecl Pc::executeZSO(::Zone *)
{
    LIFT_STUB(0x5fa360);
}

// 0x5fa5b0
void __cdecl Pc::destroyZSO(::Pc::ExpireReason, wchar_t const *)
{
    LIFT_STUB(0x5fa5b0);
}

// 0x5fa710
bool __cdecl Pc::postZSO(::ZoneSerializedObject *, ::Pc::ZSOType, bool)
{
    LIFT_STUB(0x5fa710);
}

// 0x5fa8b0
bool __cdecl Pc::HandleChallengePartyId(__int64, ::ChangedProperty *)
{
    LIFT_STUB(0x5fa8b0);
}

// 0x5fa9b0
bool __cdecl Pc::HandleChallengePartyOutTime(__int64, ::ChangedProperty *)
{
    LIFT_STUB(0x5fa9b0);
}

// 0x5faab0
__int64 __cdecl Pc::GetGuildRegistrationTime(void)
{
    LIFT_STUB(0x5faab0);
}

// 0x5fab60
void __cdecl Pc::UpdateGeoZoneToGuild(::EnterReason)
{
    LIFT_STUB(0x5fab60);
}

// 0x5faca0
bool __cdecl Pc::PostSetGuildIdTask(unsigned __int64, wchar_t const *)
{
    LIFT_STUB(0x5faca0);
}

// 0x5fb150
bool __cdecl Pc::PostCompleteChallengeList(unsigned __int64, char, char, char, char, wchar_t const *)
{
    LIFT_STUB(0x5fb150);
}

// 0x5fb1f0
void __cdecl Pc::SendGetGradeListFailToArena(short)
{
    LIFT_STUB(0x5fb1f0);
}

// 0x5fb3a0
void __cdecl Pc::SendGradeList(void)
{
    LIFT_STUB(0x5fb3a0);
}

// 0x5fb630
void __cdecl Pc::SendGradeListToArena(int, ::GradeLevelInfo &, ::GradeInfo *const, short)
{
    LIFT_STUB(0x5fb630);
}

// 0x5fb940
void __cdecl Pc::SendGradeToArena(int, ::GradeInfo &, char)
{
    LIFT_STUB(0x5fb940);
}

// 0x5fbb50
void __cdecl Pc::SendGradeLevelToArena(int, ::GradeLevelInfo &)
{
    LIFT_STUB(0x5fbb50);
}

// 0x5fbd40
void __cdecl Pc::SendGuildInfoToArena(::Session const *)
{
    LIFT_STUB(0x5fbd40);
}

// 0x5fc020
void __cdecl Pc::SendGamePlayRestrictLevelToArena(::Session const *)
{
    LIFT_STUB(0x5fc020);
}

// 0x5fc1a0
void __cdecl Pc::SendGamePlayRestrictLevelForHealthySystemToArena(::Session const *)
{
    LIFT_STUB(0x5fc1a0);
}

// 0x5fc300
void __cdecl Pc::SendChangedGuildBuff(::SeasonContentsResultInfoOfGuild const *)
{
    LIFT_STUB(0x5fc300);
}

// 0x5fc650
short __cdecl Pc::CheckArenaPortalUsable(::Data::ArenaPortalRecordPtr)
{
    LIFT_STUB(0x5fc650);
}

// 0x5fc9f0
bool __cdecl Pc::BeginArenaLobbyReservation(unsigned __int64 arenaPortalKey, char arenaAttraction)
{
    PcView *self = reinterpret_cast<PcView *>(this);
    bool result = true;
    EnterCriticalSection(&self->_arenaLock);
    if (self->_arenaSession == LIFT_ARENA_SESSION_IN_WORLD)
    {
        self->_arenaSession = LIFT_ARENA_SESSION_MOVE_TO_ARENA_LOBBY;
        self->_arenaLobbyEnterParam_portalKey = arenaPortalKey;
        self->_arenaLobbyEnterParam_pcArenaLobbyId = 0;
        self->_arenaLobbyEnterParam_roomId = 0;
        self->_arenaLobbyEnterParam_attraction = arenaAttraction;
    }
    else
    {
        result = false;
    }
    LeaveCriticalSection(&self->_arenaLock);
    return result;
}

// 0x5fca90
void __cdecl Pc::RollbackArenaLobbyReservation(void)
{
    PcView *self = reinterpret_cast<PcView *>(this);
    EnterCriticalSection(&self->_arenaLock);
    if (self->_arenaSession == LIFT_ARENA_SESSION_MOVE_TO_ARENA_LOBBY)
        self->_arenaSession = LIFT_ARENA_SESSION_IN_WORLD;
    LeaveCriticalSection(&self->_arenaLock);
}

// 0x5fcae0
bool __cdecl Pc::CreateArenaLobbyRoomNotify(::ArenaLobbyEnterParam const &, bool, char)
{
    LIFT_STUB(0x5fcae0);
}

// 0x5fcc00
void __cdecl Pc::SendReserveArenaLobbyFail(short)
{
    LIFT_STUB(0x5fcc00);
}

// 0x5fcd70
void __cdecl Pc::SendFriendNotiLocation(::Pc::FriendNotiLocationType)
{
    LIFT_STUB(0x5fcd70);
}

// 0x5fcfe0
short __cdecl Pc::SendEnterArenaLobby(char const *, short)
{
    LIFT_STUB(0x5fcfe0);
}

// 0x5fd820
void __cdecl Pc::SendLeaveArenaLobbyByDisconnect(void)
{
    LIFT_STUB(0x5fd820);
}

// 0x5fd930
short __cdecl Pc::SendLeaveArenaLobbyByUserRequest(void)
{
    LIFT_STUB(0x5fd930);
}

// 0x5fda50
bool __cdecl Pc::SendLeaveArenaLobbyByAASFatiqueRule(void)
{
    LIFT_STUB(0x5fda50);
}

// 0x5fdb60
bool __cdecl Pc::EnterArenaLobbyOk(char)
{
    LIFT_STUB(0x5fdb60);
}

// 0x5fdc40
bool __cdecl Pc::LeaveArenaLobbyOk(void)
{
    PcView *self = reinterpret_cast<PcView *>(this);
    bool result = true;
    EnterCriticalSection(&self->_arenaLock);
    if (self->_arenaSession == LIFT_ARENA_SESSION_IN_ARENA_LOBBY)
    {
        self->_arenaSession = LIFT_ARENA_SESSION_RETURN_TO_GAME;
        self->_arenaLobbyEnterParam_portalKey = 0;
        self->_arenaLobbyEnterParam_roomId = 0;
        self->_arenaGameGameMode = 0;
    }
    else
    {
        result = false;
    }
    LeaveCriticalSection(&self->_arenaLock);
    return result;
}

// 0x5fdcc0
short __cdecl Pc::SendExitFromArenaLobbyRoom(void)
{
    LIFT_STUB(0x5fdcc0);
}

// 0x5fddc0
short __cdecl Pc::SendSetArenaLobbyRoomMatchOption(char, char, char, char, short, short const *const)
{
    LIFT_STUB(0x5fddc0);
}

// 0x5fe780
short __cdecl Pc::SendDelegateArenaLobbyRoomLeader(short, unsigned __int64)
{
    LIFT_STUB(0x5fe780);
}

// 0x5fe880
short __cdecl Pc::SendSetArenaLobbyRoomPassword(short)
{
    LIFT_STUB(0x5fe880);
}

// 0x5fe970
short __cdecl Pc::SendJoinArenaLobbyRoom(__int64, wchar_t const *, short, char, char)
{
    LIFT_STUB(0x5fe970);
}

// 0x5fead0
short __cdecl Pc::SendBanishFromArenaLobby(short, unsigned __int64)
{
    LIFT_STUB(0x5fead0);
}

// 0x5febd0
bool __cdecl Pc::ReturnToGame(void)
{
    LIFT_STUB(0x5febd0);
}

// 0x5fec90
short __cdecl Pc::SendReadyToMatchArenaLobbyRoom(void)
{
    LIFT_STUB(0x5fec90);
}

// 0x5fed90
short __cdecl Pc::SendUnReadyToMatchArenaLobbyRoom(void)
{
    LIFT_STUB(0x5fed90);
}

// 0x5fee70
short __cdecl Pc::SendArenaLobbyMatchReq(char)
{
    LIFT_STUB(0x5fee70);
}

// 0x5ff000
short __cdecl Pc::SendSkipArenaLobbyMatchReq(void)
{
    LIFT_STUB(0x5ff000);
}

// 0x5ff0e0
short __cdecl Pc::SendCancelArenaLobbyMatchingReq(char)
{
    LIFT_STUB(0x5ff0e0);
}

// 0x5ff1d0
short __cdecl Pc::SendCancelArenaLobbyMatchReq(void)
{
    LIFT_STUB(0x5ff1d0);
}

// 0x5ff2b0
short __cdecl Pc::SendDecideToGoToArena(::Data::ArenaMatchingRuleDetailType)
{
    LIFT_STUB(0x5ff2b0);
}

// 0x5ff3a0
bool __cdecl Pc::ReserveArena(::ReserveArenaParam const &)
{
    LIFT_STUB(0x5ff3a0);
}

// 0x5ff580
void __cdecl Pc::RetrieveArenaLobbyWaitingNumber(void)
{
    LIFT_STUB(0x5ff580);
}

// 0x5ff6f0
void __cdecl Pc::RetrieveArenaLobbyWaitingNumberComplete(unsigned __int64, int)
{
    LIFT_STUB(0x5ff6f0);
}

// 0x5ff7f0
short __cdecl Pc::CancelArenaLobbyWaiting(void)
{
    LIFT_STUB(0x5ff7f0);
}

// 0x5ff8e0
void __cdecl Pc::CancelArenaLobbyWaitingComplete(unsigned __int64)
{
    LIFT_STUB(0x5ff8e0);
}

// 0x5ff990
bool __cdecl Pc::SendEnterArena(char const *, int)
{
    LIFT_STUB(0x5ff990);
}

// 0x6004f0
void __cdecl Pc::InitArenaGradeParam(void)
{
    LIFT_STUB(0x6004f0);
}

// 0x6006f0
bool __cdecl Pc::SetArenaGradeParam(::ArenaGradeParam &)
{
    LIFT_STUB(0x6006f0);
}

// 0x600850
bool __cdecl Pc::GetArenaGradeParam(::ArenaGradeParam &)
{
    LIFT_STUB(0x600850);
}

// 0x6009b0
bool __cdecl Pc::SendLogoutReqToArena(::TransactionExpireChecker::ExpireToken *, short)
{
    LIFT_STUB(0x6009b0);
}

// 0x600a80
bool __cdecl Pc::SendLogoutReqToArena(unsigned __int64, short)
{
    LIFT_STUB(0x600a80);
}

// 0x600b30
void __cdecl Pc::LogoutOkFromArena(void)
{
    LIFT_STUB(0x600b30);
}

// 0x600b90
void __cdecl Pc::UpdateReturnPos(::Pc::UpdateReturnPosType)
{
    LIFT_STUB(0x600b90);
}

// 0x600ce0
void __cdecl Pc::ArenaLobbyClosed(short)
{
    LIFT_STUB(0x600ce0);
}

// 0x600e20
void __cdecl Pc::ReturnToGameByEnterFail(void)
{
    PcView *self = reinterpret_cast<PcView *>(this);
    EnterCriticalSection(&self->_arenaLock);
    self->_arenaSession = LIFT_ARENA_SESSION_RETURN_TO_GAME;
    memset(self->_reserveArenaParam, 0, sizeof(self->_reserveArenaParam));
    self->_arenaLobbyEnterParam_roomId = 0;
    self->_arenaLobbyEnterParam_pcArenaLobbyId = 0;
    self->_arenaLobbyEnterParam_portalKey = 0;
    *reinterpret_cast<unsigned __int64 *>(&self->_arenaLobbyEnterParam_attraction) = 0;
    LeaveCriticalSection(&self->_arenaLock);
    Send("hQ", 620, 3);
}

// 0x600eb0
short __cdecl Pc::SendMoveToArena(int, bool, char)
{
    LIFT_STUB(0x600eb0);
}

// 0x600fe0
::Pc::ArenaSession __cdecl Pc::GetArenaSessionState(void) const
{
    PcView const *self = reinterpret_cast<PcView const *>(this);
    CRITICAL_SECTION *lock = const_cast<CRITICAL_SECTION *>(&self->_arenaLock);
    EnterCriticalSection(lock);
    ::Pc::ArenaSession state = static_cast< ::Pc::ArenaSession>(self->_arenaSession);
    LeaveCriticalSection(lock);
    return state;
}

// 0x601020
bool __cdecl Pc::IsInArenaOrArenaLobby(void) const
{
    PcView const *self = reinterpret_cast<PcView const *>(this);
    CRITICAL_SECTION *lock = const_cast<CRITICAL_SECTION *>(&self->_arenaLock);
    EnterCriticalSection(lock);
    unsigned int arenaSession = static_cast<unsigned int>(self->_arenaSession);
    bool result = arenaSession >= LIFT_ARENA_SESSION_MOVE_TO_ARENA_LOBBY &&
                  (arenaSession <= LIFT_ARENA_SESSION_IN_ARENA_LOBBY || (arenaSession - 5) <= 1);
    LeaveCriticalSection(lock);
    return result;
}

// 0x601080
char __cdecl Pc::GetArenaLobbySessionForClient(void)
{
    LIFT_STUB(0x601080);
}

// 0x601100
wchar_t const * __cdecl Pc::GetArenaSessionString(void) const
{
    LIFT_STUB(0x601100);
}

// 0x601200
bool __cdecl Pc::FetchShowcaseData(::FsdShowcaseRecord *)
{
    LIFT_STUB(0x601200);
}

// 0x601600
void __cdecl Pc::resetExhaustionTimer(bool)
{
    LIFT_STUB(0x601600);
}

// 0x601b00
void __cdecl Pc::exhaustionExceptRule(bool)
{
    LIFT_STUB(0x601b00);
}

// 0x601c00
void __cdecl Pc::onExhaustionTimer(void)
{
    LIFT_STUB(0x601c00);
}

// 0x601da0
void __cdecl Pc::onAutoRespawnTimer(void)
{
    LIFT_STUB(0x601da0);
}

// 0x601e50
bool __cdecl Pc::UseHyperEnergy(int)
{
    LIFT_STUB(0x601e50);
}

// 0x601f10
int __cdecl Pc::getMaxHyperEnergyPoint(void)
{
    LIFT_STUB(0x601f10);
}

// 0x602090
void __cdecl Pc::calcHyperEnergyPoint(void)
{
    LIFT_STUB(0x602090);
}

// 0x602150
bool __cdecl Pc::changeMoveState(::CreatureMoveState, short, wchar_t *)
{
    LIFT_STUB(0x602150);
}

// 0x602810
void __cdecl Pc::StopTrialPlay(void)
{
    LIFT_STUB(0x602810);
}

// 0x602910
bool __cdecl Pc::IsBoundRaidDungeon(unsigned __int64)
{
    LIFT_STUB(0x602910);
}

// 0x602990
int __cdecl Pc::GetAllBoundRaidDungeon(::Pointer2< ::RaidDungeon> *const)
{
    LIFT_STUB(0x602990);
}

// 0x602b80
void __cdecl Pc::LogoutBoundRaidDungeon(void)
{
    LIFT_STUB(0x602b80);
}

// 0x602c50
bool __cdecl Pc::SetOccupyingRaidDungeon(unsigned __int64)
{
    LIFT_STUB(0x602c50);
}

// 0x602e30
bool __cdecl Pc::InitializeRaidDungeonInfo(bool)
{
    LIFT_STUB(0x602e30);
}

// 0x603290
::GameFailReason __cdecl Pc::isEnterableRaidDungeon(short, unsigned __int64 &, char)
{
    LIFT_STUB(0x603290);
}

// 0x604020
void __cdecl Pc::writeLogMoveHacking(void)
{
    LIFT_STUB(0x604020);
}

// 0x6041c0
void __cdecl Pc::checkToEnterZoneCount(void)
{
    LIFT_STUB(0x6041c0);
}

// 0x6042c0
void __cdecl Pc::CheckToInvalidPartyPacket(void)
{
    LIFT_STUB(0x6042c0);
}

// 0x604350
bool __cdecl Pc::checkTeamFactionBattleFieldWithTarget(::Creature *)
{
    LIFT_STUB(0x604350);
}

// 0x604430
bool __cdecl Pc::checkTeamGuildBattleFieldWithTarget(::Creature *target)
{
    PcView *self = reinterpret_cast<PcView *>(this);
    CreatureView *targetView = reinterpret_cast<CreatureView *>(target);
    ZoneView *zone = self->zone;
    bool result = true;
    if (zone != nullptr && zone->GeoZoneData != nullptr && zone == targetView->zone && zone->_guildBattleFieldMgr != nullptr)
    {
        Log::Write(Log::LT_DEBUG, PC_CPP_FILE, 17893,
                   L"[pc], checkTeamGuildBattleFieldWithTarget, pc:0x%I64x, pcdbid:0x%I64x, target:0x%I64x", self->Id,
                   self->_pcDbId, targetView->Id);
        if (self->guild_id != targetView->guild_id)
            return false;
    }
    return result;
}

// 0x6044d0
char __cdecl Pc::CheckTeamAttractionCondition(unsigned int)
{
    LIFT_STUB(0x6044d0);
}
