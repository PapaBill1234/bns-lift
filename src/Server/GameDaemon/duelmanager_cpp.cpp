// duelmanager_cpp.cpp: duelmanager.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "duelmanager.h"
#include "controlledcreature.h"
#include "pc.h"
#include "zone.h"
#include "LiftStub.h"

#define DUELMANAGER_FILE L"e:\\dailybuild02\\gamedaemon-common-0.0.348\\depot\\branch\\348nc\\program\\server\\gamedaemon\\DuelManager.cpp"

namespace
{
// LIFT: view of Pc (PDB: GameObject::Id at +0x28, Creature Prop.State.dead at +0x24A, Pc::_pcDbId at +0x4E10).
struct DuelPcView
{
    char lift_pad_0[0x28];
    unsigned __int64 Id;          // +40 (0x28)
    char lift_pad_1[0x24A - 0x30];
    char dead;                    // +586 (0x24A) Prop.State.dead
    char lift_pad_2[0x4E10 - 0x24B];
    unsigned __int64 _pcDbId;     // +19984 (0x4E10)
};

// LIFT: view of the PDB class DuelMember (size 0x28, vfptr at +0). The skeleton class has no members yet.
struct DuelMemberView
{
    void *lift_vfptr;             // +0 (0x0)
    int _teamIndex;               // +8 (0x8)
    int _memberIndex;             // +12 (0xC)
    DuelPcView *_pc;              // +16 (0x10)
    int _arenaPosition;           // +24 (0x18) DuelMember::ArenaPosition
    bool _roundReady;             // +28 (0x1C)
    bool _roundEntrance;          // +29 (0x1D)
    bool _isDeported;             // +30 (0x1E)
    long long _attackDamage;      // +32 (0x20)
};

// LIFT: view of the PDB class DuelTeam (size 0x48, vfptr at +0). The skeleton class has no members yet.
struct DuelTeamView
{
    // LIFT: view of the node of std::list<DuelMember *, StlAllocator<DuelMember *, 2> > (VS2010 _List_nod::_Node).
    // The lift toolchain has no <list> header.
    struct MemberNode
    {
        MemberNode *_Next;        // +0
        MemberNode *_Prev;        // +8
        DuelMemberView *_Myval;   // +16
    };
    // LIFT: view of the PDB member _members (std::list, size 0x18).
    struct DuelMembers
    {
        void *lift_alval;         // +0 StlAllocator (padded)
        MemberNode *_Myhead;      // +8
        unsigned long long _Mysize;  // +16
    };
    void *lift_vfptr;             // +0 (0x0)
    int _teamIndex;               // +8 (0x8)
    DuelMembers _members;         // +16 (0x10)
    long long _reserveKey;        // +40 (0x28)
    int _maxMemberCount;          // +48 (0x30)
    int _ratingScore;             // +52 (0x34)
    int _maxRatingScore;          // +56 (0x38)
    int _totalRatingScore;        // +60 (0x3C)
    long long _teamAttackDamage;  // +64 (0x40)
};

// LIFT: view of the PDB class DuelManager (size 0xD4B0, vfptr at +0). The skeleton class has no members yet.
struct DuelManagerView
{
    void *lift_vfptr;             // +0 (0x0)
    void *_data;                  // +8 (0x8) Data::DuelRecordPtr
    ::Zone *_zone;                // +16 (0x10)
    ::DuelRule *_rule;            // +24 (0x18)
    int _memberRule;              // +32 (0x20)
    DuelTeamView *_teams[2];      // +40 (0x28)
    char lift_pad_0[0xD382 - 0x38];
    char _lastAttackTeam;         // +54146 (0xD382)
};

const int ARENAPOSITION_WAITING = 1;  // LIFT: PDB enumerator DuelMember::ARENAPOSITION_WAITING = 1
const short DUEL_READY_FAIL_ALREADY_READIED = 2;  // LIFT: value 2 (pseudocode); ❓ PDB enumerator name of the fail reason
}

// 0xb1750
#pragma comment(linker, "/INCLUDE:?ReadyRound@DuelMember@@UEAA_NAEAF@Z")  // LIFT: dead-strip keep (no live caller yet)
bool __cdecl DuelMember::ReadyRound(short & failReason)
{
    DuelMemberView *self = reinterpret_cast<DuelMemberView *>(this);
    if (self->_roundReady)
    {
        Log::Write(Log::LT_ERROR, DUELMANAGER_FILE, 44, L"[duel], DuelMember::ReadyRound; already readied, pcId:0x%I64X, pcDbId:0x%I64X",
                   self->_pc->Id, self->_pc->_pcDbId);
        failReason = DUEL_READY_FAIL_ALREADY_READIED;
        return false;
    }
    self->_roundReady = true;
    return true;
}

// 0xb17c0
#pragma comment(linker, "/INCLUDE:?ResetRound@DuelMember@@UEAAXXZ")  // LIFT: dead-strip keep (no live caller yet)
void __cdecl DuelMember::ResetRound(void)
{
    DuelMemberView *self = reinterpret_cast<DuelMemberView *>(this);
    self->_arenaPosition = ARENAPOSITION_WAITING;
    self->_roundReady = false;
    self->_roundEntrance = false;
    self->_isDeported = false;
    self->_attackDamage = 0;
}

// 0xb17e0
bool __cdecl DuelTeam::IsTeamMember(::Pc const *const) const
{
    LIFT_STUB(0xb17e0);
}

// 0xb1860
#pragma comment(linker, "/INCLUDE:?IsTeamMemberAllDead@DuelTeam@@QEBA_NXZ")  // LIFT: dead-strip keep (no live caller yet)
bool __cdecl DuelTeam::IsTeamMemberAllDead(void) const
{
    DuelTeamView const *self = reinterpret_cast<DuelTeamView const *>(this);
    DuelTeamView::MemberNode const *head = self->_members._Myhead;
    for (DuelTeamView::MemberNode const *it = head->_Next; it != head; it = it->_Next)
    {
        DuelMemberView const *member = it->_Myval;
        // LIFT: DuelMember::IsRoundEntrance and Pc dead check are inlined in the original.
        if (member->_roundEntrance && member->_pc->dead == 0)
            return false;
    }
    return true;
}

// 0xb1890
::DuelMember *const __cdecl DuelTeam::GetDuelMember(::Pc const *const)
{
    LIFT_STUB(0xb1890);
}

// 0xb1920
bool __cdecl DuelTeam::Join(int, ::Pc *const)
{
    LIFT_STUB(0xb1920);
}

// 0xb1b20
bool __cdecl DuelTeam::Leave(::Pc *const)
{
    LIFT_STUB(0xb1b20);
}

// 0xb1cf0
#pragma comment(linker, "/INCLUDE:?ResetRound@DuelTeam@@UEAAXXZ")  // LIFT: dead-strip keep (no live caller yet)
void __cdecl DuelTeam::ResetRound(void)
{
    reinterpret_cast<DuelTeamView *>(this)->_teamAttackDamage = 0;
}

// 0xb1d00
__cdecl DuelManager::DuelManager(void)
{
    LIFT_STUB(0xb1d00);
}

// 0xb1e00
__cdecl DuelManager::~DuelManager(void)
{
    LIFT_STUB(0xb1e00);
}

// 0xb1ed0
bool __cdecl DuelManager::Initialize(::Zone *const, ::Data::DuelRecordPtr const &)
{
    LIFT_STUB(0xb1ed0);
}

// 0xb2250
void __cdecl DuelManager::FetchMembers(::FragmentPacket &)
{
    LIFT_STUB(0xb2250);
}

// 0xb2430
void __cdecl DuelManager::SetRoomInfo(::ArenaLobbyRoomInfo const &)
{
    LIFT_STUB(0xb2430);
}

// 0xb2590
::DuelMember *const __cdecl DuelManager::GetDuelMember(::Pc const *const)
{
    LIFT_STUB(0xb2590);
}

// 0xb2620
::DuelMember const *const __cdecl DuelManager::GetDuelMember(::Pc const *const) const
{
    LIFT_STUB(0xb2620);
}

// 0xb26b0
::DuelMember *const __cdecl DuelManager::GetDuelMember(unsigned __int64)
{
    LIFT_STUB(0xb26b0);
}

// 0xb2770
bool __cdecl DuelManager::IsDuelMember(::Pc const *const) const
{
    LIFT_STUB(0xb2770);
}

// 0xb2810
bool __cdecl DuelManager::Enter(::Pc *const)
{
    LIFT_STUB(0xb2810);
}

// 0xb3310
bool __cdecl DuelManager::Leave(::Pc *const)
{
    LIFT_STUB(0xb3310);
}

// 0xb3bd0
void __cdecl DuelManager::EnterByRevive(::ControlledCreature *const)
{
    LIFT_STUB(0xb3bd0);
}

// 0xb3f40
bool __cdecl DuelManager::Ready(unsigned __int64, short &)
{
    LIFT_STUB(0xb3f40);
}

// 0xb4230
bool __cdecl DuelManager::ReadyAll(short &)
{
    LIFT_STUB(0xb4230);
}

// 0xb4560
void __cdecl DuelManager::NotifyDuelDeath(unsigned __int64, ::Pc const *const)
{
    LIFT_STUB(0xb4560);
}

// 0xb4660
void __cdecl DuelManager::OnTimer(void)
{
    LIFT_STUB(0xb4660);
}

// 0xb48a0
void __cdecl DuelManager::OnDead(::Pc *const)
{
    LIFT_STUB(0xb48a0);
}

// 0xb4a80
bool __cdecl DuelManager::OnDamaged(::Pc *const, ::ControlledCreature *const, __int64)
{
    LIFT_STUB(0xb4a80);
}

// 0xb4b70
void __cdecl DuelManager::OnSkillChanged(::Pc *const)
{
    LIFT_STUB(0xb4b70);
}

// 0xb4c50
void __cdecl DuelManager::clearDuelMemberState(::Pc *const, bool)
{
    LIFT_STUB(0xb4c50);
}

// 0xb4e40
void __cdecl DuelManager::spawnDuelMember(::Pc *const, ::Data::ZonePcSpawnRecordPtr, bool)
{
    LIFT_STUB(0xb4e40);
}

// 0xb5020
int const __cdecl DuelManager::GetDuelTypeCodeForLog(void) const
{
    LIFT_STUB(0xb5020);
}

// 0xb5080
bool __cdecl DuelManager::verifyRoomInfo(void) const
{
    LIFT_STUB(0xb5080);
}

// 0xb5170
void __cdecl DuelManager::addDuelTimer(long)
{
    LIFT_STUB(0xb5170);
}

// 0xb52d0
bool __cdecl DuelManager::isAllRoundEntrance(void) const
{
    LIFT_STUB(0xb52d0);
}

// 0xb5350
bool __cdecl DuelManager::setTeamRatingScore(void)
{
    LIFT_STUB(0xb5350);
}

// 0xb56d0
void __cdecl DuelManager::startCountdown(void)
{
    LIFT_STUB(0xb56d0);
}

// 0xb57c0
void __cdecl DuelManager::startGame(void)
{
    LIFT_STUB(0xb57c0);
}

// 0xb6ec0
void __cdecl DuelManager::prepareRound(void)
{
    LIFT_STUB(0xb6ec0);
}

// 0xb6fb0
void __cdecl DuelManager::checkRound(void)
{
    LIFT_STUB(0xb6fb0);
}

// 0xb7130
void __cdecl DuelManager::startRound(void)
{
    LIFT_STUB(0xb7130);
}

// 0xb7aa0
void __cdecl DuelManager::finishRound(void)
{
    LIFT_STUB(0xb7aa0);
}

// 0xb7c40
#pragma comment(linker, "/INCLUDE:?finishGame@DuelManager@@AEAAXXZ")  // LIFT: dead-strip keep (no live caller yet)
void __cdecl DuelManager::finishGame(void)
{
    DuelManagerView *self = reinterpret_cast<DuelManagerView *>(this);
    // LIFT: DuelTeam::IsTeamEmpty is inlined in the original.
    if (self->_teams[0]->_members.empty())
        finishGame(static_cast< ::DuelGameResult>(4));  // LIFT: DUELGAMERESULT_BETA_WIN = 4 (PDB)
    else if (self->_teams[1]->_members.empty())
        finishGame(static_cast< ::DuelGameResult>(3));  // LIFT: DUELGAMERESULT_ALPHA_WIN = 3 (PDB)
    else
        finishGame(self->_rule->CalcGameResult());
}

// 0xb7ca0
void __cdecl DuelManager::finishGame(::DuelGameResult)
{
    LIFT_STUB(0xb7ca0);
}

// 0xb8260
void __cdecl DuelManager::standbyNextRound(void)
{
    LIFT_STUB(0xb8260);
}

// 0xb8360
void __cdecl DuelManager::enterToArena(void)
{
    LIFT_STUB(0xb8360);
}

// 0xb8400
void __cdecl DuelManager::leaveFromArena(void)
{
    LIFT_STUB(0xb8400);
}

// 0xb84d0
#pragma comment(linker, "/INCLUDE:?resetRound@DuelManager@@MEAAXXZ")  // LIFT: dead-strip keep (no live caller yet)
void __cdecl DuelManager::resetRound(void)
{
    reinterpret_cast<DuelManagerView *>(this)->_lastAttackTeam = -1;
}

// 0xb84e0
::Data::ZonePcSpawnRecordPtr const __cdecl DuelManager::getRoundStartPcSpawn(int, int) const
{
    // LIFT: Not done. It needs the Data::DuelRecord layout (round start spawn ids) and the DataManager zone-pc-spawn table lookup.
    LIFT_STUB(0xb84e0);
}

// 0xb8560
void __cdecl DuelManager::recordGameResult(::Pc *const, int, ::DuelManager::DuelScoreResult)
{
    LIFT_STUB(0xb8560);
}

// 0xb8660
void __cdecl DuelManager::recordGameResult(::DuelGameResult)
{
    LIFT_STUB(0xb8660);
}

// 0xb92a0
void __cdecl DuelManager::calcDuelRating(::Pc *const, ::DuelManager::DuelScoreResult, int, int, int, int)
{
    LIFT_STUB(0xb92a0);
}

// 0xb9a10
int const __cdecl DuelManager::calcRateDiffByELO(::DuelManager::DuelScoreResult, int, int, int, int) const
{
    LIFT_STUB(0xb9a10);
}

// 0xb9c00
int const __cdecl DuelManager::calcRateDiffByELORenewal(::DuelManager::DuelScoreResult, int, int, int, int, int) const
{
    LIFT_STUB(0xb9c00);
}

// 0xb9d70
void __cdecl DuelManager::calcBaseExpPoint(::Pc *const, char, ::DuelManager::DuelScoreResult, ::ResultReward &) const
{
    LIFT_STUB(0xb9d70);
}

// 0xb9f50
void __cdecl DuelManager::calcBonusExpPoint(::Pc *const, ::DuelManager::DuelScoreResult, int, ::ResultReward &, int &) const
{
    LIFT_STUB(0xb9f50);
}

// 0xba6d0
bool const __cdecl DuelManager::isBeginner(::Pc *const, char, int &) const
{
    LIFT_STUB(0xba6d0);
}

// 0xba850
bool __cdecl DuelManager::startDuelResultTran(::Pc *, ::DuelManager::DuelScoreResult, int, ::DuelResultTranResultNotifyInfo const &)
{
    LIFT_STUB(0xba850);
}

// 0xbad50
bool __cdecl DuelRule::IsGameDone(void) const
{
    // LIFT: Not done. It needs the Data::DuelRecord fields (max round, win count) that the pseudocode shows only as raw DrEl offsets.
    LIFT_STUB(0xbad50);
}

// 0xbada0
::DuelGameResult const __cdecl DuelRule::CalcGameResult(void) const
{
    LIFT_STUB(0xbada0);
}

// 0xbae10
bool __cdecl DuelRule::CanResurrect(::Pc const *const) const
{
    LIFT_STUB(0xbae10);
}
