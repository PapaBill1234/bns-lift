// partybattlemanager_cpp.cpp: partybattlemanager.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "partybattlemanager.h"
#include "creature.h"
#include "fielditem.h"
#include "gameobject.h"
#include "npc.h"
#include "pc.h"
#include "zone.h"
#include "zonescore.h"
#include "Memory.h"
#include "MemoryManager.h"
#include "LiftStub.h"

#pragma comment(linker, "/INCLUDE:??0PartyBattleSide@@QEAA@XZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:??1PartyBattleSide@@QEAA@XZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?IncreaseDeathCount@PartyBattleSide@@QEAAX_K@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?IncreaseOccupationCount@PartyBattleSide@@QEAAX_K@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?IncreaseManipulationCount@PartyBattleSide@@QEAAX_K@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetFirstMemberId@PartyBattleSide@@QEAA_KXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?CheckToFinishGame@PartyBattleManager@@UEAA_NXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?CanTakeAchievementReward@PartyBattleManager@@UEAA_NXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?isSaveGameResult@PartyBattleManager@@MEAA_NXZ")  // LIFT: dead-strip keep (no live caller yet)

// LIFT: PartyBattleManager has no member list yet. The lifted bodies read its members through PartyBattleManagerView.
#define PBM_VIEW ((PartyBattleManagerView *)this)
// LIFT: _member is PartyBattleSideMember * in the PDB. The lifted bodies read it through PartyBattleSideMemberView.
#define PBS_MEMBER ((PartyBattleSideMemberView *)_member)

// 0x181370
__cdecl PartyBattleSide::PartyBattleSide(void)
    : _combatSide(0)
    , _worldId(0)
    , _memberCapacity(0)
    , _member(nullptr)
    , _memberCount(0)
    , _ratingScore(0)
    , _totalRatingScore(0)
    , _maxRatingScore(0)
    , _guildId(0)
    , _goalInCount(0)
    , _consecutiveGoalInCount(0)
{
}

// 0x1813a0
__cdecl PartyBattleSide::~PartyBattleSide(void)
{
    if (_member != nullptr)
    {
        Memory::_Manager[2]->Free(_member, L"e:\\dailybuild02\\gamedaemon-common-0.0.348\\depot\\branch\\348nc\\program\\server\\gamedaemon\\PartyBattleManager.cpp", 49);
        _member = nullptr;
    }
}

// 0x1813e0
bool __cdecl PartyBattleSide::OnEntered(::PartyBattleManager *, ::Pc *)
{
    LIFT_STUB(0x1813e0);
}

// 0x181740
bool __cdecl PartyBattleSide::OnLeaved(::PartyBattleManager *, ::Pc *, char)
{
    LIFT_STUB(0x181740);
}

// 0x1819d0
void __cdecl PartyBattleSide::OnFinished(::Zone *, ::PartyBattleManager *)
{
    LIFT_STUB(0x1819d0);
}

// 0x181aa0
void __cdecl PartyBattleSide::IncreaseDeathCount(unsigned __int64 victimId)
{
    if (victimId == 0)
        return;
    for (short i = 0; i < _memberCount; ++i)
    {
        if (PBS_MEMBER[i]._pcId == victimId)
        {
            ++PBS_MEMBER[i].deathCount;
            PBS_MEMBER[i].straightKillCount = 0;
            return;
        }
    }
}

// 0x181b20
void __cdecl PartyBattleSide::IncreaseOccupationCount(unsigned __int64 pcId)
{
    if (pcId == 0)
        return;
    for (short i = 0; i < _memberCount; ++i)
    {
        if (PBS_MEMBER[i]._pcId == pcId)
        {
            ++PBS_MEMBER[i].occupationCount;
            return;
        }
    }
}

// 0x181b80
void __cdecl PartyBattleSide::IncreaseManipulationCount(unsigned __int64 pcId)
{
    if (pcId == 0)
        return;
    for (short i = 0; i < _memberCount; ++i)
    {
        if (PBS_MEMBER[i]._pcId == pcId)
        {
            ++PBS_MEMBER[i].manipulationCount;
            return;
        }
    }
}

// 0x181be0
void __cdecl PartyBattleSide::InvokeEffectToAllMember(::Zone *, unsigned __int64 *const, char)
{
    LIFT_STUB(0x181be0);
}

// 0x181de0
void __cdecl PartyBattleSide::SendGoalInAchievement(::Zone *, ::PartyBattleManager *)
{
    LIFT_STUB(0x181de0);
}

// 0x181f10
void __cdecl PartyBattleSide::SendGoalInCountInfoAllMember(::Zone *, short, short, short, short)
{
    LIFT_STUB(0x181f10);
}

// 0x182060
bool __cdecl PartyBattleSide::SetMembers(char, ::ArenaLobbyTeamMemberInfo *const, short, bool)
{
    LIFT_STUB(0x182060);
}

// 0x182200
unsigned __int64 __cdecl PartyBattleSide::GetFirstMemberId(void)
{
    for (short i = 0; i < _memberCount; ++i)
    {
        if (PBS_MEMBER[i].state != 0)
            return PBS_MEMBER[i]._pcId;
    }
    return 0;
}

// 0x182250
void __cdecl PartyBattleSide::SetMemberScore(::Zone *, ::PartyBattleManager *)
{
    LIFT_STUB(0x182250);
}

// 0x1824d0
void __cdecl PartyBattleSide::SendMemberRecord(::Zone *, ::PartyBattleManager *)
{
    LIFT_STUB(0x1824d0);
}

// 0x182670
bool __cdecl PartyBattleSide::ReturnToArenaLobbyRequest(::Zone *, ::Pc *, bool, unsigned __int64, char, char)
{
    LIFT_STUB(0x182670);
}

// 0x182d30
void __cdecl PartyBattleSide::spawnAllMember(::Zone *, ::Data::ZonePcSpawnRecordPtr const &)
{
    LIFT_STUB(0x182d30);
}

// 0x182e30
void __cdecl PartyBattleSide::spawnMember(::Pc *, ::Data::ZonePcSpawnRecordPtr const &)
{
    LIFT_STUB(0x182e30);
}

// 0x183120
bool __cdecl PartyBattleSide::invokeEffect(::Zone *, unsigned __int64, ::Data::EffectRecordPtr const &)
{
    LIFT_STUB(0x183120);
}

// 0x1831d0
void __cdecl PartyBattleSide::resetAllMemberSpecialSkillGauge(::Zone *)
{
    LIFT_STUB(0x1831d0);
}

// 0x1832b0
bool __cdecl PartyBattleManager::Init(::Zone *, unsigned __int64)
{
    LIFT_STUB(0x1832b0);
}

// 0x183430
void __cdecl PartyBattleManager::SetRoomInfo(::Zone *, ::ArenaLobbyRoomInfo const &, bool)
{
    LIFT_STUB(0x183430);
}

// 0x183630
bool __cdecl PartyBattleManager::EnterByRevive(::Pc *)
{
    LIFT_STUB(0x183630);
}

// 0x183830
bool __cdecl PartyBattleManager::Enter(::Pc *)
{
    LIFT_STUB(0x183830);
}

// 0x1839d0
bool __cdecl PartyBattleManager::Leave(::Pc *)
{
    LIFT_STUB(0x1839d0);
}

// 0x183b90
bool __cdecl PartyBattleManager::Ready(::Pc *)
{
    LIFT_STUB(0x183b90);
}

// 0x183c40
bool __cdecl PartyBattleManager::Start(::Pc *, bool)
{
    LIFT_STUB(0x183c40);
}

// 0x183e40
void __cdecl PartyBattleManager::Vote(bool, bool, ::PartyBattleResult, char)
{
    LIFT_STUB(0x183e40);
}

// 0x184220
void __cdecl PartyBattleManager::Finish(void)
{
    LIFT_STUB(0x184220);
}

// 0x184310
bool __cdecl PartyBattleManager::CheckToFinishGame(void)
{
    ::Zone *zone = PBM_VIEW->_zone;
    if (zone == nullptr)
        return false;
    // LIFT: Zone::GetZoneScore (0x258710) is inline here: a null score gives 0. Score types 4 and 5 are the two sides.
    ::ZoneScore *score = ((ZoneView *)zone)->_score;
    int betaScore = 0;
    int alphaScore;
    if (score != nullptr)
        alphaScore = score->Score(4);
    else
        alphaScore = 0;
    if (PBM_VIEW->_data->goal_score <= alphaScore)
        return true;
    score = ((ZoneView *)zone)->_score;
    if (score != nullptr)
        betaScore = score->Score(5);
    return PBM_VIEW->_data->goal_score <= betaScore;
}

// 0x184370
bool __cdecl PartyBattleManager::CanResurrect(::Pc *)
{
    LIFT_STUB(0x184370);
}

// 0x1843d0
bool __cdecl PartyBattleManager::CanTakeAchievementReward(void)
{
    return PBM_VIEW->_step != 4;  // ❓ step 4: PartyBattleStep value without a checked PDB enumerator name
}

// 0x1843e0
bool __cdecl PartyBattleManager::GetNearRespawnArea(::Pc *, unsigned int &, unsigned __int64 &)
{
    LIFT_STUB(0x1843e0);
}

// 0x1844f0
void __cdecl PartyBattleManager::DisposeFieldItem(::Pc *, ::FieldItem *)
{
    LIFT_STUB(0x1844f0);
}

// 0x184510
void __cdecl PartyBattleManager::OnDamaged(unsigned __int64, ::Creature *, __int64)
{
    LIFT_STUB(0x184510);
}

// 0x1845f0
void __cdecl PartyBattleManager::IncreaseKillCount(::Pc *)
{
    LIFT_STUB(0x1845f0);
}

// 0x1846a0
void __cdecl PartyBattleManager::IncreaseDeathCount(::Pc *)
{
    LIFT_STUB(0x1846a0);
}

// 0x1846f0
void __cdecl PartyBattleManager::IncreaseOccupationCount(::Pc *)
{
    LIFT_STUB(0x1846f0);
}

// 0x184740
void __cdecl PartyBattleManager::IncreaseManipulationCount(::Pc *)
{
    LIFT_STUB(0x184740);
}

// 0x184790
void __cdecl PartyBattleManager::AddAttackDamage(::Pc *, __int64)
{
    LIFT_STUB(0x184790);
}

// 0x184830
void __cdecl PartyBattleManager::AddReceivedDamage(::Pc *, __int64)
{
    LIFT_STUB(0x184830);
}

// 0x1848d0
void __cdecl PartyBattleManager::SetMemberScore(::Pc *, ::PartyBattleResult, int, int, __int64, ::PartyBattleSideMember const &)
{
    LIFT_STUB(0x1848d0);
}

// 0x184980
void __cdecl PartyBattleManager::FetchMembers(::FragmentPacket &)
{
    LIFT_STUB(0x184980);
}

// 0x184b30
void __cdecl PartyBattleManager::SendMemberRecord(::Pc *)
{
    LIFT_STUB(0x184b30);
}

// 0x184d50
::PartyBattleSide * __cdecl PartyBattleManager::GetPartyBattleSideByPcDbId(unsigned __int64)
{
    LIFT_STUB(0x184d50);
}

// 0x184df0
::PartyBattleManager * __cdecl PartyBattleManager::CreatePartyBattleManager(::Zone *, unsigned __int64)
{
    LIFT_STUB(0x184df0);
}

// 0x184f90
::PartyBattleResult __cdecl PartyBattleManager::getResult(bool)
{
    LIFT_STUB(0x184f90);
}

// 0x185110
bool __cdecl PartyBattleManager::enterMember(::Pc *)
{
    LIFT_STUB(0x185110);
}

// 0x185240
void __cdecl PartyBattleManager::ResetPcState(::Pc *)
{
    LIFT_STUB(0x185240);
}

// 0x1852d0
void __cdecl PartyBattleManager::SetVoteMember(void)
{
    LIFT_STUB(0x1852d0);
}

// 0x185360
bool __cdecl PartyBattleManager::VoteEnable(::Pc *, unsigned __int64)
{
    LIFT_STUB(0x185360);
}

// 0x1853f0
char __cdecl PartyBattleManager::VoteCast(::Pc *, unsigned __int64, unsigned __int64)
{
    LIFT_STUB(0x1853f0);
}

// 0x185590
void __cdecl PartyBattleManager::initEnv(void)
{
    LIFT_STUB(0x185590);
}

// 0x1856c0
bool __cdecl PartyBattleManager::doEnvOperation(void)
{
    LIFT_STUB(0x1856c0);
}

// 0x1858d0
::Pc * __cdecl PartyBattleManager::getAttackerPc(::GameObject *)
{
    LIFT_STUB(0x1858d0);
}

// 0x185910
bool const __cdecl PartyBattleManager::isBeginner(::Pc *const) const
{
    LIFT_STUB(0x185910);
}

// 0x185ad0
char __cdecl PartyBattleManager::getIndividualScoreResult(char, ::PartyBattleResult)
{
    LIFT_STUB(0x185ad0);
}

// 0x185b70
bool __cdecl PartyBattleManager::isSaveGameResult(void)
{
    // ❓ detail rules 3 to 5 do not save the result (PDB enumerator names not checked).
    return (unsigned int)(PBM_VIEW->_detailRule - 3) > 2 && PBM_VIEW->_isGiveReward;
}

// 0x185b90
void __cdecl PartyBattleManager::RecordGameResult(::Pc *, ::PartyBattleResult, int, int, __int64, ::PartyBattleSideMember const &)
{
    LIFT_STUB(0x185b90);
}

// 0x185ce0
void __cdecl PartyBattleManager::getTeamRatingScore(char, int &, int &, int &) const
{
    LIFT_STUB(0x185ce0);
}

// 0x185d90
void __cdecl PartyBattleManager::setTeamRatingScore(void)
{
    LIFT_STUB(0x185d90);
}

// 0x186110
bool __cdecl PartyBattleManager::checkFinishByRule(::PartyBattleStep)
{
    LIFT_STUB(0x186110);
}

// 0x1862a0
bool __cdecl PartyBattleManager::startPartyBattleResultTran(::Pc *, ::PartyBattleManager::PartyBattleScoreResult, int, ::PartyBattleResultTranResultNotifyInfo const &)
{
    LIFT_STUB(0x1862a0);
}

// 0x1867f0
bool __cdecl PartyBattleManager::RestoreDisconnectPartyBattleResultTran(::Pc *, int, int)
{
    LIFT_STUB(0x1867f0);
}

// 0x186d30
void __cdecl PartyBattleManager::DelegateNewEmcee(void)
{
    LIFT_STUB(0x186d30);
}

// 0x186dc0
int __cdecl PartyBattleManager::calcGuildRatingScore(char, __int64, ::PartyBattleManager::PartyBattleScoreResult, int, int)
{
    LIFT_STUB(0x186dc0);
}

// 0x186f60
int __cdecl PartyBattleManager::calcRatingScore(::Pc *const, char, ::PartyBattleResult, ::PartyBattleManager::PartyBattleScoreResult, int, int, int, int, int, int, __int64, ::PartyBattleSideMember const &)
{
    LIFT_STUB(0x186f60);
}

// 0x1879c0
int __cdecl PartyBattleManager::calcGuildRatingScoreDiffByELO(::PartyBattleManager::PartyBattleScoreResult, int, int) const
{
    LIFT_STUB(0x1879c0);
}

// 0x187bb0
int __cdecl PartyBattleManager::calcRatingScoreDiffByELO(::PartyBattleManager::PartyBattleScoreResult, int, int, int, int) const
{
    LIFT_STUB(0x187bb0);
}

// 0x187df0
int __cdecl PartyBattleManager::calcRatingScoreDiffByELORenewal(::PartyBattleManager::PartyBattleScoreResult, int, int, int, int, int) const
{
    LIFT_STUB(0x187df0);
}

// 0x187f60
void __cdecl PartyBattleManager::calcBaseExpPoint(::Pc *const, char, char, ::PartyBattleManager::PartyBattleScoreResult, int, int, int, int, ::ResultReward &)
{
    LIFT_STUB(0x187f60);
}

// 0x1884c0
void __cdecl PartyBattleManager::calcBonusExpPoint(::Pc *const, char, ::PartyBattleManager::PartyBattleScoreResult, int, ::ResultReward &)
{
    LIFT_STUB(0x1884c0);
}

// 0x188b20
short __cdecl PartyBattleManager::calcBonusZoneScore(char, short, short)
{
    LIFT_STUB(0x188b20);
}

// 0x188c10
void __cdecl PartyBattleManager::addZoneScoreOnDead(char, char)
{
    LIFT_STUB(0x188c10);
}

// 0x188d20
void __cdecl PartyBattleGameLog::WritePartyBattleTeamStart(::Zone *, ::PartyBattleManager *, char, int, ::PartyBattleSideMember *const, short)
{
    LIFT_STUB(0x188d20);
}

// 0x1890f0
void __cdecl PartyBattleGameLog::getTimeStr(wchar_t *, unsigned __int64, __int64)
{
    LIFT_STUB(0x1890f0);
}

// 0x189190
void __cdecl PartyBattleGameLog::WritePartyBattleTeamEnd(::Zone *, ::PartyBattleManager *, char, int, ::PartyBattleSideMember *const, short, __int64, ::PartyBattleResult, short, short)
{
    LIFT_STUB(0x189190);
}

// 0x1895b0
void __cdecl PartyBattleGameLog::WritePartyBattlePcStart(::Zone *, ::PartyBattleManager *, unsigned __int64, char, int)
{
    LIFT_STUB(0x1895b0);
}

// 0x1898b0
void __cdecl PartyBattleGameLog::WritePartyBattleResult(::Zone *, ::PartyBattleManager *, ::Pc *, char, int, int, int, __int64, ::PartyBattleResult, int, __int64, __int64, char)
{
    LIFT_STUB(0x1898b0);
}

// 0x189be0
void __cdecl PartyBattleGameLog::WritePartyBattleDisconnected(::PartyBattleManager *, ::Pc *, char)
{
    LIFT_STUB(0x189be0);
}

// 0x189e60
void __cdecl PartyBattleGameLog::WritePartyBattleRejoin(::PartyBattleManager *, ::Pc *)
{
    LIFT_STUB(0x189e60);
}

// 0x18a0b0
void __cdecl PartyBattleGameLog::WritePartyBattleMvpVote(::PartyBattleManager *, ::Pc *, unsigned __int64)
{
    LIFT_STUB(0x18a0b0);
}

// 0x18a4d0
void __cdecl PartyBattleGameLog::WriteOccupyControlPoint(::Zone *, ::PartyBattleManager *, ::Pc *, unsigned __int64, wchar_t *, short, char, char)
{
    LIFT_STUB(0x18a4d0);
}

// 0x18a840
void __cdecl PartyBattleGameLog::WriteCreateBall(::Npc *, char)
{
    LIFT_STUB(0x18a840);
}

// 0x18a9b0
void __cdecl PartyBattleGameLog::WriteGoalIn(::Zone *, ::PartyBattleManager *, unsigned __int64, __int64, __int64, __int64, __int64)
{
    LIFT_STUB(0x18a9b0);
}

// 0x18ac30
::Pc * __cdecl PartyBattleGameLog::getFirstPartyMember(::Zone *, ::PartyBattleManager *, ::PartyBattleSideMember *const, short)
{
    LIFT_STUB(0x18ac30);
}

// 0x18ace0
char __cdecl PartyBattleGameLog::getLogResultCode(::PartyBattleResult, unsigned __int64, char)
{
    LIFT_STUB(0x18ace0);
}
