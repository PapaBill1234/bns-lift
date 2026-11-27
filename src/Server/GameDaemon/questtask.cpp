// questtask.cpp: questtask.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "questtask.h"
#include "creature.h"
#include "inventory.h"
#include "pc.h"
#include "zone.h"
#include "LiftStub.h"

// 0x588810
::GameFailReason __cdecl initCaseEvent(::QuestCase const &, ::ScriptEvent &, ::CaseContext const &)
{
    LIFT_STUB(0x588810);
}

// 0x589330
void __cdecl QuestListTask::start(void)
{
    LIFT_STUB(0x589330);
}

// 0x589570
void __cdecl QuestCompleteListTask::start(void)
{
    LIFT_STUB(0x589570);
}

// 0x589590
__cdecl QuestDisposeTask::QuestDisposeTask(void)
{
    LIFT_STUB(0x589590);
}

// 0x589640
void __cdecl QuestDisposeTask::start(void)
{
    LIFT_STUB(0x589640);
}

// 0x5896f0
__cdecl QuestAcquireTask::QuestAcquireTask(void)
{
    LIFT_STUB(0x5896f0);
}

// 0x589790
void __cdecl QuestAcquireTask::start(void)
{
    LIFT_STUB(0x589790);
}

// 0x58a100
__cdecl ProgressMissionBaseTask::ProgressMissionBaseTask(void)
{
    LIFT_STUB(0x58a100);
}

// 0x58a160
bool __cdecl ProgressMissionBaseTask::Initialize(::Zone *, ::Creature *)
{
    LIFT_STUB(0x58a160);
}

// 0x58a1b0
::GameFailReason __cdecl ProgressMissionBaseTask::progressMission(bool, unsigned short, char, char, char, __int64, short, ::QuestRequiredItems const *)
{
    LIFT_STUB(0x58a1b0);
}

// 0x58ab00
bool __cdecl ProgressMissionTask::Initialize(::Zone *, ::Creature *, unsigned short, char, char, char, __int64, short, ::QuestRequiredItems const *)
{
    LIFT_STUB(0x58ab00);
}

// 0x58ac20
void __cdecl ProgressMissionTask::start(void)
{
    LIFT_STUB(0x58ac20);
}

// 0x58acb0
__cdecl ProgressMissionAllTask::ProgressMissionAllTask(void)
{
    LIFT_STUB(0x58acb0);
}

// 0x58ad40
void __cdecl ProgressMissionAllTask::start(void)
{
    LIFT_STUB(0x58ad40);
}

// 0x58ae50
void __cdecl MissionStepRollbackTask::start(void)
{
    LIFT_STUB(0x58ae50);
}

// 0x58b080
void __cdecl MissionStepTimeExpiredTask::start(void)
{
    LIFT_STUB(0x58b080);
}

// 0x58b130
bool __cdecl ProgressMissionByAcquireSummonedTask::Initialize(::Zone *const, ::Pc *const, short, char, char, unsigned __int64, wchar_t const *const)
{
    LIFT_STUB(0x58b130);
}

// 0x58b4b0
void __cdecl ProgressMissionByAcquireSummonedTask::start(void)
{
    LIFT_STUB(0x58b4b0);
}

// 0x58b6b0
__cdecl DungeonProgressToStepNTask::DungeonProgressToStepNTask(void)
{
    LIFT_STUB(0x58b6b0);
}

// 0x58b760
bool __cdecl DungeonProgressToStepNTask::Initialize(::Zone *, ::Creature *, short, unsigned short, char, __int64, int, ::Inventory::DisposeOrderWithPos const *const)
{
    LIFT_STUB(0x58b760);
}

// 0x58b850
void __cdecl DungeonProgressToStepNTask::start(void)
{
    LIFT_STUB(0x58b850);
}

// 0x58b950
__cdecl ResetQuestCompletionTimeTask::ResetQuestCompletionTimeTask(void)
{
    LIFT_STUB(0x58b950);
}

// 0x58ba00
void __cdecl ResetQuestCompletionTimeTask::start(void)
{
    LIFT_STUB(0x58ba00);
}

// 0x58baf0
void __cdecl ProgressSkipMissionStepTask::start(void)
{
    LIFT_STUB(0x58baf0);
}

// 0x58bc00
char __cdecl ChallengeListAcquireQuestTask::GetChallengeType(char, __int64, ::Pc *)
{
    LIFT_STUB(0x58bc00);
}

// 0x58bde0
bool __cdecl ChallengeListAcquireQuestTask::Initialize(::Zone *, ::Creature *, char, unsigned short)
{
    LIFT_STUB(0x58bde0);
}

// 0x58bed0
void __cdecl ChallengeListAcquireQuestTask::start(void)
{
    LIFT_STUB(0x58bed0);
}

// 0x58c320
bool __cdecl ChallengeListTakeRewardTask::Initialize(::Zone *, ::Creature *, char)
{
    LIFT_STUB(0x58c320);
}

// 0x58c410
char __cdecl ChallengeListTakeRewardTask::GetChallengeCompletionCount(::Pc *, char)
{
    LIFT_STUB(0x58c410);
}

// 0x58c570
void __cdecl ChallengeListTakeRewardTask::start(void)
{
    LIFT_STUB(0x58c570);
}

// 0x58d420
__cdecl TendencyQuestPackTask::TendencyQuestPackTask(void)
{
    LIFT_STUB(0x58d420);
}

// 0x58d490
bool __cdecl TendencyQuestPackTask::Initialize(::Zone *, ::Creature *, unsigned __int64, __int64, __int64, char, char)
{
    LIFT_STUB(0x58d490);
}

// 0x58d570
void __cdecl TendencyQuestPackTask::start(void)
{
    LIFT_STUB(0x58d570);
}
