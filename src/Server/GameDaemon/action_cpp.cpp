// action_cpp.cpp: action.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "action.h"
#include "creature.h"
#include "duelbot.h"
#include "pc.h"
#include "zone.h"
#include "LiftStub.h"

// 0x467730
__cdecl Action::Action(::ActionClass)
{
    LIFT_STUB(0x467730);
}

// 0x4677a0
__cdecl Action::~Action(void)
{
    LIFT_STUB(0x4677a0);
}

// 0x4677c0
void __cdecl Action::Initialize(::Zone *, ::Creature *)
{
    LIFT_STUB(0x4677c0);
}

// 0x467880
void __cdecl Action::Initialize(::Zone *, unsigned __int64)
{
    LIFT_STUB(0x467880);
}

// 0x467910
void __cdecl Action::TimerExpired(unsigned int, long)
{
    LIFT_STUB(0x467910);
}

// 0x468070
void __cdecl Action::startAction(void)
{
    LIFT_STUB(0x468070);
}

// 0x4680a0
void __cdecl Action::changePriority(void)
{
    LIFT_STUB(0x4680a0);
}

// 0x4680d0
void __cdecl Action::CancelAction(::Action::CancelReason, unsigned __int64, wchar_t const *, int)
{
    LIFT_STUB(0x4680d0);
}

// 0x468190
#pragma comment(linker, "/INCLUDE:?availableCancel@Action@@MEAA_NW4CancelActionReason@@@Z")  // LIFT: dead-strip keep (no live caller yet)
bool __cdecl Action::availableCancel(::CancelActionReason reason)
{
    switch (reason)
    {
    case CANCELACTIONREASON_USER_REQUEST:
    case CANCELACTIONREASON_MOVE:
    case CANCELACTIONREASON_OVERRIDE_SKILL:
    case CANCELACTIONREASON_ATTACKED:
        return true;
    }
    return false;
}

// 0x4681a0
void __cdecl Action::RequestCancel(::CancelActionReason, unsigned __int64)
{
    LIFT_STUB(0x4681a0);
}

// 0x468280
void __cdecl Action::ClearParent(void)
{
    LIFT_STUB(0x468280);
}

// 0x468350
void __cdecl NoAction::intervalAction(long)
{
    LIFT_STUB(0x468350);
}

// 0x468390
void __cdecl NoOpAction::intervalAction(long)
{
    LIFT_STUB(0x468390);
}

// 0x4683d0
void __cdecl NoMoveAction::intervalAction(long)
{
    LIFT_STUB(0x4683d0);
}

// 0x468410
__cdecl ActionFactory::~ActionFactory(void)
{
    LIFT_STUB(0x468410);
}

// 0x468470
bool __cdecl ActionFactory::Init(void)
{
    LIFT_STUB(0x468470);
}

// 0x468580
::Action * __cdecl ActionFactory::CreateAction(::ActionClass) const
{
    LIFT_STUB(0x468580);
}

// 0x469920
__cdecl PcActionQueue::PcActionQueue(::Pc *)
{
    LIFT_STUB(0x469920);
}

// 0x469a20
__cdecl PcActionQueue::~PcActionQueue(void)
{
    LIFT_STUB(0x469a20);
}

// 0x469b80
void __cdecl PcActionQueue::PushAction(::Action *)
{
    LIFT_STUB(0x469b80);
}

// 0x469c60
void __cdecl PcActionQueue::ActionChangedPriority(::Action *)
{
    LIFT_STUB(0x469c60);
}

// 0x469c70
void __cdecl PcActionQueue::ActionFinished(::Action *)
{
    LIFT_STUB(0x469c70);
}

// 0x469ca0
void __cdecl PcActionQueue::ValidateAction(void)
{
    LIFT_STUB(0x469ca0);
}

// 0x469d50
void __cdecl PcActionQueue::ClearSimOperations(void)
{
    LIFT_STUB(0x469d50);
}

// 0x469dd0
void __cdecl PcActionQueue::CancelAction(::Action *, bool, unsigned __int64, wchar_t const *, int)
{
    LIFT_STUB(0x469dd0);
}

// 0x469e00
bool __cdecl PcActionQueue::CancelOperation(::ActionClass, wchar_t const *, int)
{
    LIFT_STUB(0x469e00);
}

// 0x469e40
void __cdecl PcActionQueue::CancelSkillCast(void)
{
    LIFT_STUB(0x469e40);
}

// 0x469e80
void __cdecl PcActionQueue::ReturnSimSkill(unsigned __int64, bool)
{
    LIFT_STUB(0x469e80);
}

// 0x469f00
#pragma comment(linker, "/INCLUDE:?RequestActionCancel@DuelBotActionQueue@@UEAAXW4CancelActionReason@@_K@Z")  // LIFT: dead-strip keep (no live caller yet)
void __cdecl DuelBotActionQueue::RequestActionCancel(::CancelActionReason reason, unsigned __int64 cancellerId)
{
    _operation->RequestCancel(reason, cancellerId);
}

// 0x469f10
bool __cdecl PcActionQueue::RequestSkillTrigger(__int64, int)
{
    LIFT_STUB(0x469f10);
}

// 0x469fb0
bool __cdecl PcActionQueue::SucceedTargetInfo(__int64, int, unsigned __int64 &, ::vector16 &, unsigned __int64 *const, char &)
{
    LIFT_STUB(0x469fb0);
}

// 0x46a090
void __cdecl PcActionQueue::insertSlot(::Action *)
{
    LIFT_STUB(0x46a090);
}

// 0x46a380
void __cdecl PcActionQueue::deleteSlot(::Action *, bool, wchar_t const *, int, unsigned __int64)
{
    LIFT_STUB(0x46a380);
}

// 0x46a9b0
void __cdecl PcActionQueue::shiftSlot(::Action *)
{
    LIFT_STUB(0x46a9b0);
}

// 0x46aa40
bool __cdecl PcActionQueue::moveToSimOperation(bool)
{
    LIFT_STUB(0x46aa40);
}

// 0x46abd0
char __cdecl PcActionQueue::getSimOpSlotId(void)
{
    LIFT_STUB(0x46abd0);
}

// 0x46ac60
bool __cdecl PcActionQueue::getPriority(::Action const *, ::Action const *) const
{
    LIFT_STUB(0x46ac60);
}

// 0x46ad30
bool __cdecl PcActionQueue::isEgoSkillAction(::Action *) const
{
    LIFT_STUB(0x46ad30);
}

// 0x46ae30
void __cdecl NpcActionQueue::PushAction(::Action *)
{
    LIFT_STUB(0x46ae30);
}

// 0x46b040
void __cdecl NpcActionQueue::ActionChangedPriority(::Action *)
{
    LIFT_STUB(0x46b040);
}

// 0x46b0a0
void __cdecl NpcActionQueue::ActionFinished(::Action *)
{
    LIFT_STUB(0x46b0a0);
}

// 0x46b0d0
void __cdecl NpcActionQueue::ValidateAction(void)
{
    LIFT_STUB(0x46b0d0);
}

// 0x46b120
void __cdecl NpcActionQueue::CancelAction(::Action *, bool, unsigned __int64, wchar_t const *, int)
{
    LIFT_STUB(0x46b120);
}

// 0x46b150
void __cdecl NpcActionQueue::CancelSkillCast(void)
{
    LIFT_STUB(0x46b150);
}

// 0x46b190
void __cdecl NpcActionQueue::ReturnSimSkill(unsigned __int64, bool)
{
    LIFT_STUB(0x46b190);
}

// 0x46b1d0
bool __cdecl NpcActionQueue::CancelOperation(::ActionClass, wchar_t const *, int)
{
    LIFT_STUB(0x46b1d0);
}

// 0x46b210
void __cdecl NpcActionQueue::RequestActionCancel(::CancelActionReason, unsigned __int64)
{
    LIFT_STUB(0x46b210);
}

// 0x46b220
::Action * __cdecl NpcActionQueue::GetOperation(bool)
{
    LIFT_STUB(0x46b220);
}

// 0x46b2a0
::Action * __cdecl NpcActionQueue::GetMovement(void)
{
    LIFT_STUB(0x46b2a0);
}

// 0x46b310
void __cdecl NpcActionQueue::insertSlot(::Action *)
{
    LIFT_STUB(0x46b310);
}

// 0x46b5d0
void __cdecl NpcActionQueue::deleteSlot(::Action *, ::NpcActionQueue::ActionExpiredReason, wchar_t const *, int)
{
    LIFT_STUB(0x46b5d0);
}

// 0x46b770
void __cdecl NpcActionQueue::transferEvent(::Action *, ::NpcActionQueue::ActionExpiredReason)
{
    LIFT_STUB(0x46b770);
}

// 0x46b7f0
bool __cdecl NpcActionQueue::moveToSimOperation(void)
{
    LIFT_STUB(0x46b7f0);
}

// 0x46b970
__cdecl SummonedActionQueue::~SummonedActionQueue(void)
{
    LIFT_STUB(0x46b970);
}

// 0x46b9f0
void __cdecl SummonedActionQueue::PushAction(::Action *)
{
    LIFT_STUB(0x46b9f0);
}

// 0x46baf0
void __cdecl SummonedActionQueue::ActionChangedPriority(::Action *)
{
    LIFT_STUB(0x46baf0);
}

// 0x46bb70
void __cdecl SummonedActionQueue::ActionFinished(::Action *)
{
    LIFT_STUB(0x46bb70);
}

// 0x46bb90
void __cdecl SummonedActionQueue::ValidateAction(void)
{
    LIFT_STUB(0x46bb90);
}

// 0x46bbe0
void __cdecl SummonedActionQueue::ClearSimOperation(void)
{
    LIFT_STUB(0x46bbe0);
}

// 0x46bc10
void __cdecl SummonedActionQueue::CancelAction(::Action *, bool, unsigned __int64, wchar_t const *, int)
{
    LIFT_STUB(0x46bc10);
}

// 0x46bc30
void __cdecl SummonedActionQueue::CancelSkillCast(void)
{
    LIFT_STUB(0x46bc30);
}

// 0x46bc70
bool __cdecl SummonedActionQueue::CancelOperation(::ActionClass, wchar_t const *, int)
{
    LIFT_STUB(0x46bc70);
}

// 0x46bcb0
::Action * __cdecl SummonedActionQueue::GetOperation(bool)
{
    LIFT_STUB(0x46bcb0);
}

// 0x46bd30
::Action * __cdecl SummonedActionQueue::GetMovement(void)
{
    LIFT_STUB(0x46bd30);
}

// 0x46bda0
void __cdecl SummonedActionQueue::insertSlot(::Action *)
{
    LIFT_STUB(0x46bda0);
}

// 0x46bf80
bool __cdecl SummonedActionQueue::moveToSimOperation(void)
{
    LIFT_STUB(0x46bf80);
}

// 0x46c070
void __cdecl SummonedActionQueue::deleteSlot(::Action *const, bool, wchar_t const *, int)
{
    LIFT_STUB(0x46c070);
}

// 0x46c1c0
__cdecl DuelBotActionQueue::DuelBotActionQueue(::DuelBot *)
{
    LIFT_STUB(0x46c1c0);
}

// 0x46c2a0
__cdecl DuelBotActionQueue::~DuelBotActionQueue(void)
{
    LIFT_STUB(0x46c2a0);
}

// 0x46c400
void __cdecl DuelBotActionQueue::PushAction(::Action *)
{
    LIFT_STUB(0x46c400);
}

// 0x46c490
void __cdecl DuelBotActionQueue::ActionChangedPriority(::Action *)
{
    LIFT_STUB(0x46c490);
}

// 0x46c510
void __cdecl DuelBotActionQueue::ActionFinished(::Action *)
{
    LIFT_STUB(0x46c510);
}

// 0x46c530
void __cdecl DuelBotActionQueue::ValidateAction(void)
{
    LIFT_STUB(0x46c530);
}

// 0x46c5a0
void __cdecl DuelBotActionQueue::CancelAction(::Action *, bool, unsigned __int64, wchar_t const *, int)
{
    LIFT_STUB(0x46c5a0);
}

// 0x46c5c0
bool __cdecl DuelBotActionQueue::CancelOperation(::ActionClass, wchar_t const *, int)
{
    LIFT_STUB(0x46c5c0);
}

// 0x46c600
void __cdecl DuelBotActionQueue::CancelSkillCast(void)
{
    LIFT_STUB(0x46c600);
}

// 0x46c640
void __cdecl DuelBotActionQueue::ReturnSimSkill(unsigned __int64, bool)
{
    LIFT_STUB(0x46c640);
}

// 0x46c6c0
bool __cdecl DuelBotActionQueue::RequestSkillTrigger(__int64, int)
{
    LIFT_STUB(0x46c6c0);
}

// 0x46c760
bool __cdecl DuelBotActionQueue::SucceedTargetInfo(__int64, int, unsigned __int64 &, ::vector16 &, unsigned __int64 *const, char &)
{
    LIFT_STUB(0x46c760);
}

// 0x46c840
void __cdecl DuelBotActionQueue::insertSlot(::Action *)
{
    LIFT_STUB(0x46c840);
}

// 0x46ca10
void __cdecl DuelBotActionQueue::deleteSlot(::Action *, bool, wchar_t const *, int)
{
    LIFT_STUB(0x46ca10);
}

// 0x46cea0
bool __cdecl DuelBotActionQueue::moveToSimOperation(void)
{
    LIFT_STUB(0x46cea0);
}

// 0x46cfa0
bool __cdecl DuelBotActionQueue::getPriority(::Action const *, ::Action const *) const
{
    LIFT_STUB(0x46cfa0);
}

// 0x46d110
__cdecl DuelBotSummonedActionQueue::~DuelBotSummonedActionQueue(void)
{
    LIFT_STUB(0x46d110);
}

// 0x46d190
void __cdecl DuelBotSummonedActionQueue::PushAction(::Action *)
{
    LIFT_STUB(0x46d190);
}

// 0x46d290
void __cdecl DuelBotSummonedActionQueue::ActionChangedPriority(::Action *)
{
    LIFT_STUB(0x46d290);
}

// 0x46d310
void __cdecl DuelBotSummonedActionQueue::ActionFinished(::Action *)
{
    LIFT_STUB(0x46d310);
}

// 0x46d330
#pragma comment(linker, "/INCLUDE:?IntervalAction@DuelBotActionQueue@@UEAAXPEAVAction@@J@Z")  // LIFT: dead-strip keep (no live caller yet)
void __cdecl DuelBotActionQueue::IntervalAction(::Action *action, long elapsed)
{
    action->intervalAction(elapsed);
}

// 0x46d340
void __cdecl DuelBotSummonedActionQueue::ValidateAction(void)
{
    LIFT_STUB(0x46d340);
}

// 0x46d390
void __cdecl DuelBotSummonedActionQueue::CancelAction(::Action *, bool, unsigned __int64, wchar_t const *, int)
{
    LIFT_STUB(0x46d390);
}

// 0x46d3b0
void __cdecl DuelBotSummonedActionQueue::CancelSkillCast(void)
{
    LIFT_STUB(0x46d3b0);
}

// 0x46d3f0
void __cdecl DuelBotSummonedActionQueue::ReturnSimSkill(unsigned __int64, bool)
{
    LIFT_STUB(0x46d3f0);
}

// 0x46d440
bool __cdecl DuelBotSummonedActionQueue::CancelOperation(::ActionClass, wchar_t const *, int)
{
    LIFT_STUB(0x46d440);
}

// 0x46d480
::Action * __cdecl DuelBotSummonedActionQueue::GetOperation(bool)
{
    LIFT_STUB(0x46d480);
}

// 0x46d500
::Action * __cdecl DuelBotSummonedActionQueue::GetMovement(void)
{
    LIFT_STUB(0x46d500);
}

// 0x46d570
void __cdecl DuelBotSummonedActionQueue::insertSlot(::Action *)
{
    LIFT_STUB(0x46d570);
}

// 0x46d750
bool __cdecl DuelBotSummonedActionQueue::moveToSimOperation(void)
{
    LIFT_STUB(0x46d750);
}

// 0x46d840
void __cdecl DuelBotSummonedActionQueue::deleteSlot(::Action *const, bool, wchar_t const *, int)
{
    LIFT_STUB(0x46d840);
}

// 0x47bf80
void __cdecl Action::actionFinished(void)
{
    LIFT_STUB(0x47bf80);
}
