// brainbase_cpp.cpp: brainbase.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "brainbase.h"
#include "action.h"
#include "brainconst.h"
#include "creature.h"
#include "npc.h"
#include "LiftStub.h"

#define BRAINBASE_FILE L"e:\\dailybuild02\\gamedaemon-common-0.0.348\\depot\\branch\\348nc\\program\\server\\gamedaemon\\BrainBase.cpp"

namespace
{
// LIFT: view of the PDB record Data::NpcRecord (alias at +0x10). The skeleton has no record members yet.
struct BrainNpcRecordView
{
    char lift_pad_0[0x10];
    wchar_t const *alias;         // +16 (0x10)
};

// LIFT: view of Npc (PDB: GameObject::Id at +0x28, Npc::_data (Data::NpcRecordPtr) at +0xC50).
struct BrainNpcView
{
    char lift_pad_0[0x28];
    unsigned __int64 Id;          // +40 (0x28)
    char lift_pad_1[0xC50 - 0x30];
    BrainNpcRecordView *_data;    // +3152 (0xC50)
};
}

// 0x3feee0
__cdecl BrainBase::BrainBase(::Npc &, ::BrainBase::TransitionTable &, ::Data::NpcBrainType, char)
{
    LIFT_STUB(0x3feee0);
}

// 0x3fefc0
#pragma comment(linker, "/INCLUDE:??1BrainBase@@MEAA@XZ")  // LIFT: dead-strip keep (no live caller yet)
__cdecl BrainBase::~BrainBase(void)
{
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
#pragma comment(linker, "/INCLUDE:?ResetAllHates@BrainBase@@QEAAXPEB_W@Z")  // LIFT: dead-strip keep (no live caller yet)
void __cdecl BrainBase::ResetAllHates(wchar_t const * reason)
{
    ::BrainBaseMemberView *self = reinterpret_cast< ::BrainBaseMemberView *>(this);
    for (int i = 0; i < self->_hateMax; ++i)
        ResetHateByIndex(i, reason);
    self->_curTargetIndex = -1;
    self->_hateTourValue = 0;
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
#pragma comment(linker, "/INCLUDE:?pushState@BrainBase@@AEAAXW4State@BrainConst@@@Z")  // LIFT: dead-strip keep (no live caller yet)
void __cdecl BrainBase::pushState(::BrainConst::State state)
{
    ::BrainBaseMemberView *self = reinterpret_cast< ::BrainBaseMemberView *>(this);
    if (++self->_top >= 16)
    {
        BrainNpcView *npc = reinterpret_cast<BrainNpcView *>(self->_npc);
        Log::Write(Log::LT_ERROR, BRAINBASE_FILE, 1910, L"[brain], invalid brain stack; brain stack overflow, npc-id:0x%I64x, npc-alias:%s",
                   npc->Id, npc->_data->alias);
        self->_top = 0;
        self->_stack[0] = ::BrainConst::STATE_SPAWN;
    }
    self->_stack[self->_top] = state;
}

// 0x4029a0
#pragma comment(linker, "/INCLUDE:?popState@BrainBase@@AEAA?AW4State@BrainConst@@W423@@Z")  // LIFT: dead-strip keep (no live caller yet)
::BrainConst::State __cdecl BrainBase::popState(::BrainConst::State def)
{
    ::BrainBaseMemberView *self = reinterpret_cast< ::BrainBaseMemberView *>(this);
    if (--self->_top < 0)
    {
        BrainNpcView *npc = reinterpret_cast<BrainNpcView *>(self->_npc);
        Log::Write(Log::LT_ERROR, BRAINBASE_FILE, 1922, L"[brain], invalid brain stack; brain stack underflow, npc-id:0x%I64x, npc-alias:%s",
                   npc->Id, npc->_data->alias);
        self->_top = 0;
        self->_stack[0] = def;
    }
    return self->_stack[self->_top];
}

// 0x402a20
bool __cdecl BrainBase::CancelActionByCombatSeqTransit(void)
{
    LIFT_STUB(0x402a20);
}
