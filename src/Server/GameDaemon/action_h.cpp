// action_h.cpp: action.h (GameDaemon PDB, 2019 + PDB).
#include "action.h"
#include "creature.h"
#include "LiftStub.h"

#pragma comment(linker, "/INCLUDE:?SetSlotId@Action@@UEAAXD@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetSlotId@Action@@UEBADXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?cancelAction@Action@@EEAAXW4CancelReason@1@PEB_WH_K@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:??1ActionQueue@@UEAA@XZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?generateInstanceId@ActionQueue@@IEAADD@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetOperation@PcActionQueue@@UEAAPEAVAction@@_N@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetOperation@DuelBotActionQueue@@UEAAPEAVAction@@_N@Z")  // LIFT: dead-strip keep (no live caller yet)

// 0x1d190
void __cdecl Action::SetSlotId(char slotId)
{
    _slotId = slotId;
}

// 0x1d1a0
char __cdecl Action::GetSlotId(void) const
{
    return _slotId;
}

// 0x1d1b0
void __cdecl Action::cancelAction(::Action::CancelReason reason, wchar_t const *file, int line, unsigned __int64 /*cancellerId*/)
{
    cancelAction(reason, file, line);
}

// 0x96ed0
// LIFT: stub kept. The body reads RelationalRefCntObject::_childRole (+0x20). The ZoneSerializedObject header
// keeps the RelationalRefCntObject members in its LiftBytes base, so the member has no name yet.
::Creature * __cdecl Action::GetCaster(void) const
{
    LIFT_STUB(0x96ed0);
}

// 0x453520
__cdecl ActionQueue::~ActionQueue(void)
{
}

// 0x453530
char __cdecl ActionQueue::generateInstanceId(char slotId)
{
    if (slotId >= 0)
        return slotId | SIMULTANEOUS_MASK;

    char id = instanceId;
    instanceId = (instanceId + 1) % MAX_INSTANCE_ID;
    return id;
}

// 0x453580
::Action * __cdecl PcActionQueue::GetOperation(bool isEgoOperation)
{
    if (isEgoOperation)
        return egoOperation;
    return operation;
}

// 0x453590
::Action * __cdecl DuelBotActionQueue::GetOperation(bool isEgoOperation)
{
    if (isEgoOperation)
        return nullptr;
    return _operation;
}

// 0x4535b0
// LIFT: stub kept. The body makes virtual calls on DuelBotSummonedActionQueue and reads a word at +146.
// The class has no PDB base or members in the source yet.
bool __cdecl DuelBotSummonedActionQueue::getPriority(::Action const *const, ::Action const *const, bool) const
{
    LIFT_STUB(0x4535b0);
}
