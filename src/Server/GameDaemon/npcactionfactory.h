// npcactionfactory.h: npcactionfactory.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"
#include "npcaction.h"

class NpcActionFactory
{
public:
    static ::Action * __cdecl CreateIdleAction(::Npc &, long, unsigned char, ::NpcIdleAction::IdleType);  // 0x421d10
    static ::Action * __cdecl CreateGroupMoveSyncAction(::Npc &, short);  // 0x421e00
    static ::Action * __cdecl CreateSocialAction(::Npc &, unsigned __int64, short);  // 0x421ed0
    static ::Action * __cdecl CreateHideAction(::Npc &, bool, unsigned __int64);  // 0x421fe0
    static ::Action * __cdecl CreateFallAction(::Npc &, ::GeoCell *);  // 0x4220e0
    static ::Action * __cdecl CreateKnockBackAction(::Npc &, __int64);  // 0x4221b0
    static ::Action * __cdecl CreateWarpAction(::Npc &, ::vector16 const &, short, ::WarpType, int, long, wchar_t const *);  // 0x4222f0
    static ::Action * __cdecl CreateMoveAction(::Npc &, ::NpcPredefinedMoveAction::NpcMoveSpeed, ::vector16 const &, bool, short, ::NpcPredefinedMoveAction::NpcMoveType);  // 0x422430
    static ::Action * __cdecl CreateSkillAction3(::Npc &, unsigned __int64, ::vector16 const &, ::Data::Skill3RecordActiveSkillPtr, char, unsigned __int64 *const, ::vector16 *const, unsigned __int64 *const);  // 0x4226e0
    static ::Action * __cdecl CreateSkillAction3(::Npc &, unsigned __int64, ::vector16 const &, ::Data::Skill3RecordActiveSkillPtr);  // 0x422910
    static ::Action * __cdecl CreateChangeWeaponAndStance(::Npc &, ::Data::CombatSequenceActionChangeSet const &);  // 0x422b10
    static ::Action * __cdecl CreateChangeWeaponAndStance(::Npc &, unsigned __int64, char, long);  // 0x422d40
    static ::Action * __cdecl CreateChaseAction(::Npc &, ::Creature &, short, ::vector16 const &, bool, bool &);  // 0x422e30
    static ::Action * __cdecl CreatePathFindMoveAction(::Npc &, ::vector16 const &, ::MoveType, ::NpcPathFindMoveAction::NpcMoveSpeed, int, unsigned __int64);  // 0x423010
    static ::Action * __cdecl CreateFollowAction(::Npc &, ::vector16, __int64);  // 0x423140
    static ::Action * __cdecl CreateCombatMoveAction(::Npc &, unsigned __int64, ::NpcPredefinedMoveAction::NpcMoveSpeed, long, ::Data::CombatSequenceMoveType);  // 0x423260
    static ::Action * __cdecl CreateDetectCreatureAction(::Npc &, ::Data::CombatSequenceActionDetectCreature const &);  // 0x423460
};

