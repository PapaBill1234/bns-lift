// brainbase_cpp.cpp: brainbase.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "brainbase.h"
#include "action.h"
#include "brainconst.h"
#include "creature.h"
#include "npc.h"
#include "LiftStub.h"

// 0x3feee0
__cdecl BrainBase::BrainBase(::Npc &, ::BrainBase::TransitionTable &, ::Data::NpcBrainType, char)
{
    LIFT_STUB(0x3feee0);
}

// 0x3fefc0
__cdecl BrainBase::~BrainBase(void)
{
    LIFT_STUB(0x3fefc0);
}

// 0x3fefd0
bool __cdecl BrainBase::Start(::BrainConst::State)
{
    LIFT_STUB(0x3fefd0);
}

// 0x3ff0f0
bool __cdecl BrainBase::Stop(void)
{
    LIFT_STUB(0x3ff0f0);
}

// 0x3ff1a0
void __cdecl BrainBase::actionFinished(::Action *, ::NpcActionQueue::ActionExpiredReason)
{
    LIFT_STUB(0x3ff1a0);
}

// 0x3ff320
bool __cdecl BrainBase::EventOccured(::BrainConst::Event, bool)
{
    LIFT_STUB(0x3ff320);
}

// 0x3ff790
bool __cdecl BrainBase::isValidTargetBySquadRule(::Creature *, ::vector16 const &)
{
    LIFT_STUB(0x3ff790);
}

// 0x3ff890
int __cdecl BrainBase::getTargetBySquadTargetRule(::Pointer2< ::Creature> *, ::vector16 const &)
{
    LIFT_STUB(0x3ff890);
}

// 0x3ffd80
int __cdecl BrainBase::GetTarget(::Pointer2< ::Creature> *, int &, bool)
{
    LIFT_STUB(0x3ffd80);
}

// 0x400080
bool __cdecl BrainBase::IsValidTarget(::Npc &, ::Creature &)
{
    LIFT_STUB(0x400080);
}

// 0x400110
void __cdecl BrainBase::GetTargetIds(unsigned __int64 *, unsigned __int64 *, int *)
{
    LIFT_STUB(0x400110);
}

// 0x400220
void __cdecl BrainBase::GetTargetIdsExceptCond(unsigned __int64 *, unsigned __int64 *, char, int *)
{
    LIFT_STUB(0x400220);
}

// 0x4003f0
int __cdecl BrainBase::AddHate(::Creature *, __int64, bool)
{
    LIFT_STUB(0x4003f0);
}

// 0x400560
int __cdecl BrainBase::AddHate(unsigned __int64, __int64, bool)
{
    LIFT_STUB(0x400560);
}

// 0x4005f0
bool __cdecl BrainBase::UpdateHateTime(unsigned __int64)
{
    LIFT_STUB(0x4005f0);
}

// 0x400660
bool __cdecl BrainBase::ResetHateByTargetId(unsigned __int64, wchar_t const *)
{
    LIFT_STUB(0x400660);
}

// 0x4006b0
bool __cdecl BrainBase::ResetHateByIndex(int, wchar_t const *)
{
    LIFT_STUB(0x4006b0);
}

// 0x400d10
void __cdecl BrainBase::ResetAllHates(wchar_t const *)
{
    LIFT_STUB(0x400d10);
}

// 0x400d80
void __cdecl BrainBase::SetProvocativeTarget(unsigned __int64)
{
    LIFT_STUB(0x400d80);
}

// 0x401000
void __cdecl BrainBase::SetMinHate(unsigned __int64)
{
    LIFT_STUB(0x401000);
}

// 0x4011d0
void __cdecl BrainBase::SetMaxHate(unsigned __int64)
{
    LIFT_STUB(0x4011d0);
}

// 0x401390
__int64 __cdecl BrainBase::GetHateById(unsigned __int64) const
{
    LIFT_STUB(0x401390);
}

// 0x401410
__int64 __cdecl BrainBase::GetHateByIndex(int) const
{
    LIFT_STUB(0x401410);
}

// 0x401480
int __cdecl BrainBase::getTargetByHateRule(::Pointer2< ::Creature> *, int &)
{
    LIFT_STUB(0x401480);
}

// 0x401750
::Creature * __cdecl BrainBase::isValidHate(int, int &)
{
    LIFT_STUB(0x401750);
}

// 0x401a20
void __cdecl BrainBase::changeTargetProp(unsigned __int64)
{
    LIFT_STUB(0x401a20);
}

// 0x401aa0
int __cdecl BrainBase::findHateful(unsigned __int64, bool, __int64)
{
    LIFT_STUB(0x401aa0);
}

// 0x401cc0
::BrainBase * __cdecl BrainBase::getReferenceHateBrain(void) const
{
    LIFT_STUB(0x401cc0);
}

// 0x401da0
void __cdecl BrainBase::CopyHateList(::BrainBase *)
{
    LIFT_STUB(0x401da0);
}

// 0x401fa0
void __cdecl BrainBase::SetReferenceHateTargetId(unsigned __int64)
{
    LIFT_STUB(0x401fa0);
}

// 0x402040
unsigned __int64 __cdecl BrainBase::GetTopHateTargetId(bool)
{
    LIFT_STUB(0x402040);
}

// 0x402160
unsigned __int64 __cdecl BrainBase::GetMinHateTargetId(bool)
{
    LIFT_STUB(0x402160);
}

// 0x402280
void __cdecl BrainBase::SetForcedCombatMode(bool, unsigned __int64)
{
    LIFT_STUB(0x402280);
}

// 0x402320
int __cdecl BrainBase::GetLastTarget(::Pointer2< ::Creature> *)
{
    LIFT_STUB(0x402320);
}

// 0x402420
unsigned __int64 __cdecl BrainBase::GetNearestTargetId(bool)
{
    LIFT_STUB(0x402420);
}

// 0x4025a0
unsigned __int64 __cdecl BrainBase::GetNearestTargetPcInDetectRange(void)
{
    LIFT_STUB(0x4025a0);
}

// 0x402710
unsigned __int64 __cdecl BrainBase::GetFarthestTargetId(bool)
{
    LIFT_STUB(0x402710);
}

// 0x402880
void __cdecl BrainBase::traceHate(wchar_t *, ...)
{
    LIFT_STUB(0x402880);
}

// 0x402910
void __cdecl BrainBase::pushState(::BrainConst::State)
{
    LIFT_STUB(0x402910);
}

// 0x4029a0
::BrainConst::State __cdecl BrainBase::popState(::BrainConst::State)
{
    LIFT_STUB(0x4029a0);
}

// 0x402a20
bool __cdecl BrainBase::CancelActionByCombatSeqTransit(void)
{
    LIFT_STUB(0x402a20);
}
