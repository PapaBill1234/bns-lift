// action.h: action.cpp, action.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class Action
{
public:
    enum CancelReason {};
    enum FailReason {};
public:
    virtual void __cdecl SetSlotId(char);  // 0x1d190
    virtual char __cdecl GetSlotId(void) const;  // 0x1d1a0
private:
    virtual void __cdecl cancelAction(::Action::CancelReason, wchar_t const *, int, unsigned __int64);  // 0x1d1b0
public:
    ::Creature * __cdecl GetCaster(void) const;  // 0x96ed0
    __cdecl Action(::ActionClass);  // 0x467730
    virtual __cdecl ~Action(void);  // 0x4677a0
    void __cdecl Initialize(::Zone *, ::Creature *);  // 0x4677c0
    void __cdecl Initialize(::Zone *, unsigned __int64);  // 0x467880
private:
    virtual void __cdecl TimerExpired(unsigned int, long);  // 0x467910
public:
    virtual void __cdecl startAction(void);  // 0x468070
    virtual void __cdecl changePriority(void);  // 0x4680a0
    void __cdecl CancelAction(::Action::CancelReason, unsigned __int64, wchar_t const *, int);  // 0x4680d0
protected:
    virtual bool __cdecl availableCancel(::CancelActionReason);  // 0x468190
public:
    virtual void __cdecl RequestCancel(::CancelActionReason, unsigned __int64);  // 0x4681a0
    void __cdecl ClearParent(void);  // 0x468280
protected:
    void __cdecl actionFinished(void);  // 0x47bf80
};

class ActionFactory
{
public:
    __cdecl ~ActionFactory(void);  // 0x468410
    bool __cdecl Init(void);  // 0x468470
    ::Action * __cdecl CreateAction(::ActionClass) const;  // 0x468580
};

class ActionQueue
{
public:
    virtual __cdecl ~ActionQueue(void);  // 0x453520
protected:
    char __cdecl generateInstanceId(char);  // 0x453530
};

class DuelBotActionQueue
{
public:
    virtual ::Action * __cdecl GetOperation(bool);  // 0x453590
    virtual void __cdecl RequestActionCancel(::CancelActionReason, unsigned __int64);  // 0x469f00
    __cdecl DuelBotActionQueue(::DuelBot *);  // 0x46c1c0
    virtual __cdecl ~DuelBotActionQueue(void);  // 0x46c2a0
    virtual void __cdecl PushAction(::Action *);  // 0x46c400
    virtual void __cdecl ActionChangedPriority(::Action *);  // 0x46c490
    virtual void __cdecl ActionFinished(::Action *);  // 0x46c510
    virtual void __cdecl ValidateAction(void);  // 0x46c530
    virtual void __cdecl CancelAction(::Action *, bool, unsigned __int64, wchar_t const *, int);  // 0x46c5a0
    virtual bool __cdecl CancelOperation(::ActionClass, wchar_t const *, int);  // 0x46c5c0
    virtual void __cdecl CancelSkillCast(void);  // 0x46c600
    virtual void __cdecl ReturnSimSkill(unsigned __int64, bool);  // 0x46c640
    bool __cdecl RequestSkillTrigger(__int64, int);  // 0x46c6c0
    bool __cdecl SucceedTargetInfo(__int64, int, unsigned __int64 &, ::vector16 &, unsigned __int64 *const, char &);  // 0x46c760
private:
    void __cdecl insertSlot(::Action *);  // 0x46c840
    void __cdecl deleteSlot(::Action *, bool, wchar_t const *, int);  // 0x46ca10
    bool __cdecl moveToSimOperation(void);  // 0x46cea0
    bool __cdecl getPriority(::Action const *, ::Action const *) const;  // 0x46cfa0
public:
    virtual void __cdecl IntervalAction(::Action *, long);  // 0x46d330
};

class DuelBotSummonedActionQueue
{
private:
    bool __cdecl getPriority(::Action const *const, ::Action const *const, bool) const;  // 0x4535b0
public:
    virtual __cdecl ~DuelBotSummonedActionQueue(void);  // 0x46d110
    virtual void __cdecl PushAction(::Action *);  // 0x46d190
    virtual void __cdecl ActionChangedPriority(::Action *);  // 0x46d290
    virtual void __cdecl ActionFinished(::Action *);  // 0x46d310
    virtual void __cdecl ValidateAction(void);  // 0x46d340
    virtual void __cdecl CancelAction(::Action *, bool, unsigned __int64, wchar_t const *, int);  // 0x46d390
    virtual void __cdecl CancelSkillCast(void);  // 0x46d3b0
    virtual void __cdecl ReturnSimSkill(unsigned __int64, bool);  // 0x46d3f0
    virtual bool __cdecl CancelOperation(::ActionClass, wchar_t const *, int);  // 0x46d440
    virtual ::Action * __cdecl GetOperation(bool);  // 0x46d480
    virtual ::Action * __cdecl GetMovement(void);  // 0x46d500
private:
    void __cdecl insertSlot(::Action *);  // 0x46d570
    bool __cdecl moveToSimOperation(void);  // 0x46d750
    void __cdecl deleteSlot(::Action *const, bool, wchar_t const *, int);  // 0x46d840
};

class NoAction
{
public:
    virtual void __cdecl intervalAction(long);  // 0x468350
};

class NoMoveAction
{
public:
    virtual void __cdecl intervalAction(long);  // 0x4683d0
};

class NoOpAction
{
public:
    virtual void __cdecl intervalAction(long);  // 0x468390
};

class NpcActionQueue
{
public:
    enum ActionExpiredReason {};
public:
    virtual void __cdecl PushAction(::Action *);  // 0x46ae30
    virtual void __cdecl ActionChangedPriority(::Action *);  // 0x46b040
    virtual void __cdecl ActionFinished(::Action *);  // 0x46b0a0
    virtual void __cdecl ValidateAction(void);  // 0x46b0d0
    virtual void __cdecl CancelAction(::Action *, bool, unsigned __int64, wchar_t const *, int);  // 0x46b120
    virtual void __cdecl CancelSkillCast(void);  // 0x46b150
    virtual void __cdecl ReturnSimSkill(unsigned __int64, bool);  // 0x46b190
    virtual bool __cdecl CancelOperation(::ActionClass, wchar_t const *, int);  // 0x46b1d0
    virtual void __cdecl RequestActionCancel(::CancelActionReason, unsigned __int64);  // 0x46b210
    virtual ::Action * __cdecl GetOperation(bool);  // 0x46b220
    virtual ::Action * __cdecl GetMovement(void);  // 0x46b2a0
private:
    void __cdecl insertSlot(::Action *);  // 0x46b310
    void __cdecl deleteSlot(::Action *, ::NpcActionQueue::ActionExpiredReason, wchar_t const *, int);  // 0x46b5d0
    void __cdecl transferEvent(::Action *, ::NpcActionQueue::ActionExpiredReason);  // 0x46b770
    bool __cdecl moveToSimOperation(void);  // 0x46b7f0
};

class PcActionQueue
{
public:
    virtual ::Action * __cdecl GetOperation(bool);  // 0x453580
    __cdecl PcActionQueue(::Pc *);  // 0x469920
    virtual __cdecl ~PcActionQueue(void);  // 0x469a20
    virtual void __cdecl PushAction(::Action *);  // 0x469b80
    virtual void __cdecl ActionChangedPriority(::Action *);  // 0x469c60
    virtual void __cdecl ActionFinished(::Action *);  // 0x469c70
    virtual void __cdecl ValidateAction(void);  // 0x469ca0
    void __cdecl ClearSimOperations(void);  // 0x469d50
    virtual void __cdecl CancelAction(::Action *, bool, unsigned __int64, wchar_t const *, int);  // 0x469dd0
    virtual bool __cdecl CancelOperation(::ActionClass, wchar_t const *, int);  // 0x469e00
    virtual void __cdecl CancelSkillCast(void);  // 0x469e40
    virtual void __cdecl ReturnSimSkill(unsigned __int64, bool);  // 0x469e80
    bool __cdecl RequestSkillTrigger(__int64, int);  // 0x469f10
    bool __cdecl SucceedTargetInfo(__int64, int, unsigned __int64 &, ::vector16 &, unsigned __int64 *const, char &);  // 0x469fb0
private:
    void __cdecl insertSlot(::Action *);  // 0x46a090
    void __cdecl deleteSlot(::Action *, bool, wchar_t const *, int, unsigned __int64);  // 0x46a380
    void __cdecl shiftSlot(::Action *);  // 0x46a9b0
    bool __cdecl moveToSimOperation(bool);  // 0x46aa40
    char __cdecl getSimOpSlotId(void);  // 0x46abd0
    bool __cdecl getPriority(::Action const *, ::Action const *) const;  // 0x46ac60
    bool __cdecl isEgoSkillAction(::Action *) const;  // 0x46ad30
};

class SummonedActionQueue
{
public:
    virtual __cdecl ~SummonedActionQueue(void);  // 0x46b970
    virtual void __cdecl PushAction(::Action *);  // 0x46b9f0
    virtual void __cdecl ActionChangedPriority(::Action *);  // 0x46baf0
    virtual void __cdecl ActionFinished(::Action *);  // 0x46bb70
    virtual void __cdecl ValidateAction(void);  // 0x46bb90
    void __cdecl ClearSimOperation(void);  // 0x46bbe0
    virtual void __cdecl CancelAction(::Action *, bool, unsigned __int64, wchar_t const *, int);  // 0x46bc10
    virtual void __cdecl CancelSkillCast(void);  // 0x46bc30
    virtual bool __cdecl CancelOperation(::ActionClass, wchar_t const *, int);  // 0x46bc70
    virtual ::Action * __cdecl GetOperation(bool);  // 0x46bcb0
    virtual ::Action * __cdecl GetMovement(void);  // 0x46bd30
private:
    void __cdecl insertSlot(::Action *);  // 0x46bda0
    bool __cdecl moveToSimOperation(void);  // 0x46bf80
    void __cdecl deleteSlot(::Action *const, bool, wchar_t const *, int);  // 0x46c070
};

