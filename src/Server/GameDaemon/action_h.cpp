// action_h.cpp: action.h (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "action.h"
#include "creature.h"
#include "LiftStub.h"

// 0x1d190
void __cdecl Action::SetSlotId(char)
{
    LIFT_STUB(0x1d190);
}

// 0x1d1a0
char __cdecl Action::GetSlotId(void) const
{
    LIFT_STUB(0x1d1a0);
}

// 0x1d1b0
void __cdecl Action::cancelAction(::Action::CancelReason, wchar_t const *, int, unsigned __int64)
{
    LIFT_STUB(0x1d1b0);
}

// 0x96ed0
::Creature * __cdecl Action::GetCaster(void) const
{
    LIFT_STUB(0x96ed0);
}

// 0x453520
__cdecl ActionQueue::~ActionQueue(void)
{
    LIFT_STUB(0x453520);
}

// 0x453530
char __cdecl ActionQueue::generateInstanceId(char)
{
    LIFT_STUB(0x453530);
}

// 0x453580
::Action * __cdecl PcActionQueue::GetOperation(bool)
{
    LIFT_STUB(0x453580);
}

// 0x453590
::Action * __cdecl DuelBotActionQueue::GetOperation(bool)
{
    LIFT_STUB(0x453590);
}

// 0x4535b0
bool __cdecl DuelBotSummonedActionQueue::getPriority(::Action const *const, ::Action const *const, bool) const
{
    LIFT_STUB(0x4535b0);
}
