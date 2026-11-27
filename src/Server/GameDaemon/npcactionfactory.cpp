// npcactionfactory.cpp: npcactionfactory.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "npcactionfactory.h"
#include "action.h"
#include "creature.h"
#include "npc.h"
#include "npcaction.h"
#include "LiftStub.h"

// 0x421d10
::Action * __cdecl NpcActionFactory::CreateIdleAction(::Npc &, long, unsigned char, ::NpcIdleAction::IdleType)
{
    LIFT_STUB(0x421d10);
}

// 0x421e00
::Action * __cdecl NpcActionFactory::CreateGroupMoveSyncAction(::Npc &, short)
{
    LIFT_STUB(0x421e00);
}

// 0x421ed0
::Action * __cdecl NpcActionFactory::CreateSocialAction(::Npc &, unsigned __int64, short)
{
    LIFT_STUB(0x421ed0);
}

// 0x421fe0
::Action * __cdecl NpcActionFactory::CreateHideAction(::Npc &, bool, unsigned __int64)
{
    LIFT_STUB(0x421fe0);
}

// 0x4220e0
::Action * __cdecl NpcActionFactory::CreateFallAction(::Npc &, ::GeoCell *)
{
    LIFT_STUB(0x4220e0);
}

// 0x4221b0
::Action * __cdecl NpcActionFactory::CreateKnockBackAction(::Npc &, __int64)
{
    LIFT_STUB(0x4221b0);
}

// 0x4222f0
::Action * __cdecl NpcActionFactory::CreateWarpAction(::Npc &, ::vector16 const &, short, ::WarpType, int, long, wchar_t const *)
{
    LIFT_STUB(0x4222f0);
}

// 0x422430
::Action * __cdecl NpcActionFactory::CreateMoveAction(::Npc &, ::NpcPredefinedMoveAction::NpcMoveSpeed, ::vector16 const &, bool, short, ::NpcPredefinedMoveAction::NpcMoveType)
{
    LIFT_STUB(0x422430);
}

// 0x4226e0
::Action * __cdecl NpcActionFactory::CreateSkillAction3(::Npc &, unsigned __int64, ::vector16 const &, ::Data::Skill3RecordActiveSkillPtr, char, unsigned __int64 *const, ::vector16 *const, unsigned __int64 *const)
{
    LIFT_STUB(0x4226e0);
}

// 0x422910
::Action * __cdecl NpcActionFactory::CreateSkillAction3(::Npc &, unsigned __int64, ::vector16 const &, ::Data::Skill3RecordActiveSkillPtr)
{
    LIFT_STUB(0x422910);
}

// 0x422b10
::Action * __cdecl NpcActionFactory::CreateChangeWeaponAndStance(::Npc &, ::Data::CombatSequenceActionChangeSet const &)
{
    LIFT_STUB(0x422b10);
}

// 0x422d40
::Action * __cdecl NpcActionFactory::CreateChangeWeaponAndStance(::Npc &, unsigned __int64, char, long)
{
    LIFT_STUB(0x422d40);
}

// 0x422e30
::Action * __cdecl NpcActionFactory::CreateChaseAction(::Npc &, ::Creature &, short, ::vector16 const &, bool, bool &)
{
    LIFT_STUB(0x422e30);
}

// 0x423010
::Action * __cdecl NpcActionFactory::CreatePathFindMoveAction(::Npc &, ::vector16 const &, ::MoveType, ::NpcPathFindMoveAction::NpcMoveSpeed, int, unsigned __int64)
{
    LIFT_STUB(0x423010);
}

// 0x423140
::Action * __cdecl NpcActionFactory::CreateFollowAction(::Npc &, ::vector16, __int64)
{
    LIFT_STUB(0x423140);
}

// 0x423260
::Action * __cdecl NpcActionFactory::CreateCombatMoveAction(::Npc &, unsigned __int64, ::NpcPredefinedMoveAction::NpcMoveSpeed, long, ::Data::CombatSequenceMoveType)
{
    LIFT_STUB(0x423260);
}

// 0x423460
::Action * __cdecl NpcActionFactory::CreateDetectCreatureAction(::Npc &, ::Data::CombatSequenceActionDetectCreature const &)
{
    LIFT_STUB(0x423460);
}
