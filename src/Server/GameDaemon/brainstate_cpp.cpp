// brainstate_cpp.cpp: brainstate.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "brainstate.h"
#include "action.h"
#include "brainbase.h"
#include "creature.h"
#include "npc.h"
#include "zone.h"
#include "LiftStub.h"

// 0x4034c0
::Action * __cdecl SpawnState::createSpawnSkill(::Npc &)
{
    LIFT_STUB(0x4034c0);
}

// 0x403590
::Action * __cdecl SpawnState::createSpawnIdle(::Npc &)
{
    LIFT_STUB(0x403590);
}

// 0x403630
::Action * __cdecl SpawnState::enter(::BrainBase &)
{
    LIFT_STUB(0x403630);
}

// 0x4037e0
::Action * __cdecl SpawnState::process(::BrainBase &, ::NpcActionQueue::ActionExpiredReason)
{
    LIFT_STUB(0x4037e0);
}

// 0x403850
void __cdecl SpawnState::leave(::BrainBase &)
{
    LIFT_STUB(0x403850);
}

// 0x4039a0
::Action * __cdecl ActSeqState::enter(::BrainBase &)
{
    LIFT_STUB(0x4039a0);
}

// 0x403c60
::Action * __cdecl ActSeqState::process(::BrainBase &, ::NpcActionQueue::ActionExpiredReason)
{
    LIFT_STUB(0x403c60);
}

// 0x403d60
void __cdecl ActSeqState::leave(::BrainBase &)
{
    LIFT_STUB(0x403d60);
}

// 0x403dc0
void __cdecl FollowState::SetMaster(::Npc &, unsigned __int64, ::Data::ActSequenceDetectType, int, int)
{
    LIFT_STUB(0x403dc0);
}

// 0x403e70
void __cdecl FollowState::ChangeMaster(::Npc &, unsigned __int64)
{
    LIFT_STUB(0x403e70);
}

// 0x403f10
::Action * __cdecl FollowState::enter(::BrainBase &)
{
    LIFT_STUB(0x403f10);
}

// 0x403f30
::Action * __cdecl FollowState::process(::BrainBase &, ::NpcActionQueue::ActionExpiredReason)
{
    LIFT_STUB(0x403f30);
}

// 0x404200
bool __cdecl FollowState::GetNextPosition(::Npc &, ::vector16 &, ::Creature *)
{
    LIFT_STUB(0x404200);
}

// 0x404390
void __cdecl FollowState::ClearTicket(::Zone *, ::Creature *)
{
    LIFT_STUB(0x404390);
}

// 0x404430
void __cdecl FollowState::leave(::BrainBase &)
{
    LIFT_STUB(0x404430);
}

// 0x4044b0
::Action * __cdecl CombatSeqState::enter(::BrainBase &)
{
    LIFT_STUB(0x4044b0);
}

// 0x4044e0
::Action * __cdecl CombatSeqState::process(::BrainBase &, ::NpcActionQueue::ActionExpiredReason)
{
    LIFT_STUB(0x4044e0);
}

// 0x404920
void __cdecl CombatSeqState::leave(::BrainBase &)
{
    LIFT_STUB(0x404920);
}

// 0x404a00
bool __cdecl TalkState::resizePcList(void)
{
    LIFT_STUB(0x404a00);
}

// 0x404ab0
::Action * __cdecl TalkState::enter(::BrainBase &)
{
    LIFT_STUB(0x404ab0);
}

// 0x404bd0
::Action * __cdecl TalkState::process(::BrainBase &, ::NpcActionQueue::ActionExpiredReason)
{
    LIFT_STUB(0x404bd0);
}

// 0x404c20
void __cdecl TalkState::leave(::BrainBase &)
{
    LIFT_STUB(0x404c20);
}

// 0x404d30
void __cdecl TalkState::ClearPcList(wchar_t const *)
{
    LIFT_STUB(0x404d30);
}

// 0x404e40
::Action * __cdecl ReturnState::enter(::BrainBase &)
{
    LIFT_STUB(0x404e40);
}

// 0x405020
::Action * __cdecl ReturnState::process(::BrainBase &, ::NpcActionQueue::ActionExpiredReason)
{
    LIFT_STUB(0x405020);
}

// 0x4050b0
void __cdecl ReturnState::leave(::BrainBase &)
{
    LIFT_STUB(0x4050b0);
}

// 0x405220
::Action * __cdecl ReturnState::createReturnLongWarp(::Npc &)
{
    LIFT_STUB(0x405220);
}

// 0x4052e0
void __cdecl ReturnState::removeDebuff(::Npc &)
{
    LIFT_STUB(0x4052e0);
}
