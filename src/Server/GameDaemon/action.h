// action.h: action.cpp, action.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"
#include "zoneserializedobject.h"

// LIFT: card lift-gamedaemon-e19 adds the PDB base and data members (size 0x98) and the PDB virtual slot order.
// A virtual function with no lifted body yet is a pure placeholder, so the slots keep the PDB order.
class Action : public ::ZoneSerializedObject
{
public:
    enum CancelReason {};
    enum FailReason {};
public:
    __cdecl Action(::ActionClass);  // 0x467730
    virtual __cdecl ~Action(void);  // 0x4677a0
    void __cdecl Initialize(::Zone *, ::Creature *);  // 0x4677c0
    void __cdecl Initialize(::Zone *, unsigned __int64);  // 0x467880
    ::Creature * __cdecl GetCaster(void) const;  // 0x96ed0
protected:
    // LIFT: PDB slot 8 is ZoneSerializedObject::ProcessUnexpired(int). The base header does not declare it yet.
    virtual void __cdecl lift_slot8_ProcessUnexpired(void) = 0;
public:
    virtual bool __cdecl IsAvailableAction(void) = 0;  // PDB slot 9. LIFT: pure placeholder (body not lifted)
    virtual ::ActionPriorityClass __cdecl getPriority(void) const = 0;  // PDB slot 10
    virtual bool __cdecl prepareAction(void) = 0;  // PDB slot 11. LIFT: pure placeholder (body not lifted)
    virtual void __cdecl startAction(void);  // 0x468070, PDB slot 12
    virtual void __cdecl intervalAction(long) = 0;  // PDB slot 13. LIFT: pure placeholder (body not lifted)
    virtual void __cdecl changePriority(void);  // 0x4680a0, PDB slot 14
    void __cdecl CancelAction(::Action::CancelReason, unsigned __int64, wchar_t const *, int);  // 0x4680d0
    virtual void __cdecl RequestCancel(::CancelActionReason, unsigned __int64);  // 0x4681a0, PDB slot 15
    void __cdecl ClearParent(void);  // 0x468280
    virtual bool __cdecl IsSimultaneous(void) const = 0;  // PDB slot 16. LIFT: pure placeholder (body not lifted)
    virtual unsigned int __cdecl GetSimultaneousGroup(void) const = 0;  // PDB slot 17. LIFT: pure placeholder (body not lifted)
    virtual void __cdecl SetSlotId(char);  // 0x1d190, PDB slot 18
    virtual char __cdecl GetSlotId(void) const;  // 0x1d1a0, PDB slot 19
    virtual unsigned int __cdecl GetFlowType(void) const = 0;  // PDB slot 20. LIFT: pure placeholder (body not lifted)
protected:
    void __cdecl actionFinished(void);  // 0x47bf80
    virtual bool __cdecl availableCancel(::CancelActionReason);  // 0x468190, PDB slot 21
private:
    virtual void __cdecl TimerExpired(unsigned int, long);  // 0x467910
    // MSVC orders same-name virtual overloads in reverse declaration order: the 4-argument form is slot 22.
    virtual void __cdecl cancelAction(::Action::CancelReason, wchar_t const *, int) = 0;  // PDB slot 23. LIFT: pure placeholder (body not lifted)
    virtual void __cdecl cancelAction(::Action::CancelReason, wchar_t const *, int, unsigned __int64);  // 0x1d1b0, PDB slot 22
    virtual void __cdecl failAction(::Action::FailReason) = 0;  // PDB slot 24
private:
    unsigned __int64 _parentId;  // +0x80
    unsigned __int64 _zoneId;  // +0x88
    char _slotId;  // +0x90
    char _instanceId;  // +0x91
    unsigned short _actionClass;  // +0x92
    unsigned char _flags;  // +0x94
    bool _doneAddChild;  // +0x95

    friend struct ActionLayoutCheck;
};

struct ActionLayoutCheck
{
    static_assert(offsetof(Action, _parentId) == 0x80, "Action::_parentId");
    static_assert(offsetof(Action, _slotId) == 0x90, "Action::_slotId");
    static_assert(offsetof(Action, _doneAddChild) == 0x95, "Action::_doneAddChild");
    static_assert(sizeof(Action) == 0x98, "sizeof Action");
};

class ActionFactory
{
public:
    __cdecl ~ActionFactory(void);  // 0x468410
    bool __cdecl Init(void);  // 0x468470
    ::Action * __cdecl CreateAction(::ActionClass) const;  // 0x468580
};

// LIFT: card lift-gamedaemon-e19 adds the PDB vftable order and the data member (size 0x10).
class ActionQueue
{
public:
    virtual void __cdecl PushAction(::Action *) = 0;  // slot 0
    virtual void __cdecl IntervalAction(::Action *, long) = 0;  // slot 1
    virtual void __cdecl ValidateAction(void) = 0;  // slot 2
    virtual void __cdecl CancelAction(::Action *, bool, unsigned __int64, wchar_t const *, int) = 0;  // slot 3
    virtual bool __cdecl CancelOperation(::ActionClass, wchar_t const *, int) = 0;  // slot 4
    virtual void __cdecl ActionStarted(::Action *) = 0;  // slot 5
    virtual void __cdecl ActionFinished(::Action *) = 0;  // slot 6
    virtual void __cdecl ActionChangedPriority(::Action *) = 0;  // slot 7
    virtual void __cdecl CancelSkillCast(void) = 0;  // slot 8
    virtual void __cdecl ReturnSimSkill(unsigned __int64, bool) = 0;  // slot 9
    virtual void __cdecl RequestActionCancel(::CancelActionReason, unsigned __int64) = 0;  // slot 10
    virtual ::Action * __cdecl GetOperation(bool) = 0;  // slot 11
    virtual ::Action * __cdecl GetMovement(void) = 0;  // slot 12
    virtual __cdecl ~ActionQueue(void);  // 0x453520, slot 13
protected:
    static int const MAX_INSTANCE_ID = 100;
    static int const SIMULTANEOUS_MASK = 0x80;
    char __cdecl generateInstanceId(char);  // 0x453530
private:
    char instanceId;  // +8
};

// LIFT: card lift-gamedaemon-e19 adds the PDB base and data members (size 0x70).
class DuelBotActionQueue : public ::ActionQueue
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
private:
    ::Action *_movement;  // +0x10
    ::Action *_operation;  // +0x18
    ::DuelBot *_caster;  // +0x20
    ::Action *_simOperations[8];  // +0x28
    int _simOpCount;  // +0x68

    friend struct DuelBotActionQueueLayoutCheck;
};

struct DuelBotActionQueueLayoutCheck
{
    static_assert(offsetof(DuelBotActionQueue, _operation) == 0x18, "DuelBotActionQueue::_operation");
    static_assert(offsetof(DuelBotActionQueue, _simOpCount) == 0x68, "DuelBotActionQueue::_simOpCount");
    static_assert(sizeof(DuelBotActionQueue) == 0x70, "sizeof DuelBotActionQueue");
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

// LIFT: card lift-gamedaemon-e19 adds the PDB base and data members (size 0xB8).
class PcActionQueue : public ::ActionQueue
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
private:
    ::Action *movement;  // +0x10
    ::Action *operation;  // +0x18
    ::Action *egoOperation;  // +0x20
    ::Pc *caster;  // +0x28
    ::Action *simOperations[16];  // +0x30
    int simOpCount;  // +0xB0

    friend struct PcActionQueueLayoutCheck;
};

struct PcActionQueueLayoutCheck
{
    static_assert(offsetof(PcActionQueue, egoOperation) == 0x20, "PcActionQueue::egoOperation");
    static_assert(offsetof(PcActionQueue, simOpCount) == 0xB0, "PcActionQueue::simOpCount");
    static_assert(sizeof(PcActionQueue) == 0xB8, "sizeof PcActionQueue");
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

