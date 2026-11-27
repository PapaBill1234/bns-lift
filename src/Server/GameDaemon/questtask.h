// questtask.h: questtask.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"
#include "inventory.h"

class ChallengeListAcquireQuestTask
{
public:
    static char __cdecl GetChallengeType(char, __int64, ::Pc *);  // 0x58bc00
    bool __cdecl Initialize(::Zone *, ::Creature *, char, unsigned short);  // 0x58bde0
private:
    virtual void __cdecl start(void);  // 0x58bed0
};

class ChallengeListTakeRewardTask
{
public:
    bool __cdecl Initialize(::Zone *, ::Creature *, char);  // 0x58c320
    static char __cdecl GetChallengeCompletionCount(::Pc *, char);  // 0x58c410
private:
    virtual void __cdecl start(void);  // 0x58c570
};

class DungeonProgressToStepNTask
{
public:
    __cdecl DungeonProgressToStepNTask(void);  // 0x58b6b0
    bool __cdecl Initialize(::Zone *, ::Creature *, short, unsigned short, char, __int64, int, ::Inventory::DisposeOrderWithPos const *const);  // 0x58b760
private:
    virtual void __cdecl start(void);  // 0x58b850
};

class MissionStepRollbackTask
{
private:
    virtual void __cdecl start(void);  // 0x58ae50
};

class MissionStepTimeExpiredTask
{
private:
    virtual void __cdecl start(void);  // 0x58b080
};

class ProgressMissionAllTask
{
public:
    __cdecl ProgressMissionAllTask(void);  // 0x58acb0
private:
    virtual void __cdecl start(void);  // 0x58ad40
};

class ProgressMissionBaseTask
{
public:
    __cdecl ProgressMissionBaseTask(void);  // 0x58a100
    bool __cdecl Initialize(::Zone *, ::Creature *);  // 0x58a160
protected:
    ::GameFailReason __cdecl progressMission(bool, unsigned short, char, char, char, __int64, short, ::QuestRequiredItems const *);  // 0x58a1b0
};

class ProgressMissionByAcquireSummonedTask
{
public:
    bool __cdecl Initialize(::Zone *const, ::Pc *const, short, char, char, unsigned __int64, wchar_t const *const);  // 0x58b130
private:
    virtual void __cdecl start(void);  // 0x58b4b0
};

class ProgressMissionTask
{
public:
    bool __cdecl Initialize(::Zone *, ::Creature *, unsigned short, char, char, char, __int64, short, ::QuestRequiredItems const *);  // 0x58ab00
private:
    virtual void __cdecl start(void);  // 0x58ac20
};

class ProgressSkipMissionStepTask
{
private:
    virtual void __cdecl start(void);  // 0x58baf0
};

class QuestAcquireTask
{
public:
    __cdecl QuestAcquireTask(void);  // 0x5896f0
private:
    virtual void __cdecl start(void);  // 0x589790
};

class QuestCompleteListTask
{
private:
    virtual void __cdecl start(void);  // 0x589570
};

class QuestDisposeTask
{
public:
    __cdecl QuestDisposeTask(void);  // 0x589590
private:
    virtual void __cdecl start(void);  // 0x589640
};

class QuestListTask
{
private:
    virtual void __cdecl start(void);  // 0x589330
};

class ResetQuestCompletionTimeTask
{
public:
    __cdecl ResetQuestCompletionTimeTask(void);  // 0x58b950
private:
    virtual void __cdecl start(void);  // 0x58ba00
};

class TendencyQuestPackTask
{
public:
    __cdecl TendencyQuestPackTask(void);  // 0x58d420
    bool __cdecl Initialize(::Zone *, ::Creature *, unsigned __int64, __int64, __int64, char, char);  // 0x58d490
private:
    virtual void __cdecl start(void);  // 0x58d570
};

::GameFailReason __cdecl initCaseEvent(::QuestCase const &, ::ScriptEvent &, ::CaseContext const &);  // 0x588810
