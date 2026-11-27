// duelbotchallengeattractionstate_cpp.cpp: duelbotchallengeattractionstate.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "duelbotchallengeattractionstate.h"
#include "creature.h"
#include "gameobject.h"
#include "pc.h"
#include "zone.h"
#include "LiftStub.h"

// 0xa3910
__cdecl DuelBotChallengeAttractionState::DuelBotChallengeAttractionState(void)
{
    LIFT_STUB(0xa3910);
}

// 0xa3a00
bool __cdecl DuelBotChallengeAttractionState::Init(::Zone *, bool)
{
    LIFT_STUB(0xa3a00);
}

// 0xa3b10
bool __cdecl DuelBotChallengeAttractionState::shuffleFloors(void)
{
    LIFT_STUB(0xa3b10);
}

// 0xa3cb0
bool __cdecl DuelBotChallengeAttractionState::shuffleStrategicTools(void)
{
    LIFT_STUB(0xa3cb0);
}

// 0xa3d50
void __cdecl DuelBotChallengeAttractionState::Start(::Pc *)
{
    LIFT_STUB(0xa3d50);
}

// 0xa3ec0
void __cdecl DuelBotChallengeAttractionState::OnEntered(::Zone *, ::Creature *, ::EnterReason)
{
    LIFT_STUB(0xa3ec0);
}

// 0xa41b0
void __cdecl DuelBotChallengeAttractionState::OnLeaved(::Zone *, ::Creature *, ::LeaveReason)
{
    LIFT_STUB(0xa41b0);
}

// 0xa4370
void __cdecl DuelBotChallengeAttractionState::OnKill(::Zone *, ::GameObject *, ::Creature *)
{
    LIFT_STUB(0xa4370);
}

// 0xa4480
void __cdecl DuelBotChallengeAttractionState::OnZoneAttractionTimer(::Zone *)
{
    LIFT_STUB(0xa4480);
}

// 0xa4620
void __cdecl DuelBotChallengeAttractionState::OnCombatStart(::Zone *, ::Creature *, ::Creature *)
{
    LIFT_STUB(0xa4620);
}

// 0xa48b0
bool __cdecl DuelBotChallengeAttractionState::PickStrategicTool(::Pc *, char)
{
    LIFT_STUB(0xa48b0);
}

// 0xa49e0
bool __cdecl DuelBotChallengeAttractionState::UseStrategicTool(::Pc *, unsigned __int64)
{
    LIFT_STUB(0xa49e0);
}

// 0xa4bc0
void __cdecl DuelBotChallengeAttractionState::TakeAttractionReward(::Pc *)
{
    LIFT_STUB(0xa4bc0);
}

// 0xa4d80
void __cdecl DuelBotChallengeAttractionState::ReviveByAttractionRule(::Pc *)
{
    LIFT_STUB(0xa4d80);
}

// 0xa4dd0
void __cdecl DuelBotChallengeAttractionState::LeaveAttractionZone(::Pc *)
{
    LIFT_STUB(0xa4dd0);
}

// 0xa4eb0
void __cdecl DuelBotChallengeAttractionState::FetchInZoneAttractionState(::FragmentPacket &)
{
    LIFT_STUB(0xa4eb0);
}

// 0xa4f60
void __cdecl DuelBotChallengeAttractionState::onDuelBotKilled(::Zone *)
{
    LIFT_STUB(0xa4f60);
}

// 0xa51e0
int __cdecl DuelBotChallengeAttractionState::getStartFloor(int)
{
    LIFT_STUB(0xa51e0);
}

// 0xa5260
::Pc * __cdecl DuelBotChallengeAttractionState::getPlayer(::Zone *)
{
    LIFT_STUB(0xa5260);
}

// 0xa52c0
void __cdecl DuelBotChallengeAttractionState::initPlayerState(::Pc *)
{
    LIFT_STUB(0xa52c0);
}

// 0xa56a0
void __cdecl DuelBotChallengeAttractionState::finish(::Zone *, ::DuelBotChallengeEvent, int)
{
    LIFT_STUB(0xa56a0);
}

// 0xa5a10
void __cdecl DuelBotChallengeAttractionState::finishBySystemError(::Zone *)
{
    LIFT_STUB(0xa5a10);
}

// 0xa5bb0
void __cdecl DuelBotChallengeAttractionState::giveRewardForSystemError(::Pc *)
{
    LIFT_STUB(0xa5bb0);
}

// 0xa5e20
void __cdecl DuelBotChallengeAttractionState::onFloorChanged(::Zone *)
{
    LIFT_STUB(0xa5e20);
}

// 0xa5ef0
unsigned __int64 __cdecl DuelBotChallengeAttractionState::getNextDuelBotId(void)
{
    LIFT_STUB(0xa5ef0);
}

// 0xa6050
void __cdecl DuelBotChallengeAttractionState::spawnDuelBot(::Zone *, unsigned __int64, long)
{
    LIFT_STUB(0xa6050);
}

// 0xa6250
void __cdecl DuelBotChallengeAttractionState::combatDuelBot(::Zone *, unsigned __int64)
{
    LIFT_STUB(0xa6250);
}

// 0xa6400
void __cdecl DuelBotChallengeGameLog::WriteDuelBotChallengeStageStart(::Pc *, ::GameLogDuelBotChallengeStageStartCode, wchar_t *, __int64, unsigned __int64 *const, __int64, char, bool, __int64, __int64, ::Data::DuelBotChallengeRecordPtr &, ::dr_vector16, __int64)
{
    LIFT_STUB(0xa6400);
}

// 0xa68c0
void __cdecl DuelBotChallengeGameLog::WriteDuelBotChallengeStageEnd(::Pc *, ::GameLogDuelBotChallengeStateCode, wchar_t *, __int64, unsigned __int64 *const, __int64, char, bool, __int64, __int64, __int64, __int64, __int64, ::Data::DuelBotChallengeRecordPtr &, __int64)
{
    LIFT_STUB(0xa68c0);
}

// 0xa6df0
void __cdecl DuelBotChallengeGameLog::WriteDuelBotChallengeReward(::Pc *, ::GameLogDuelBotChallengeStateCode, wchar_t *, __int64, __int64, __int64, __int64, __int64)
{
    LIFT_STUB(0xa6df0);
}

// 0xa7100
void __cdecl DuelBotChallengeGameLog::WriteDuelBotChallengeRewardItem(::Pc *, ::GameLogDuelBotChallengeStateCode, wchar_t *, ::AttractionRewardItem)
{
    LIFT_STUB(0xa7100);
}

// 0xa72c0
void __cdecl DuelBotChallengeGameLog::WriteDuelBotChallengeScoreChange(::Pc *, ::GameLogDuelBotChallengeStateCode, wchar_t *, __int64, __int64, __int64, __int64, __int64, __int64, int, __int64, __int64)
{
    LIFT_STUB(0xa72c0);
}

// 0xa7610
unsigned __int64 * __cdecl DuelBotChallengeGameLog::getEffectKey(::Data::DuelBotChallengeRecordPtr &, short)
{
    LIFT_STUB(0xa7610);
}

// 0xae770
__int64 __cdecl DuelBotChallengeGameLog::getPcAttackPower(::Pc *)
{
    LIFT_STUB(0xae770);
}
