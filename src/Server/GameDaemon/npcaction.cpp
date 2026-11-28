// npcaction.cpp: npcaction.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "npcaction.h"
#include "action.h"
#include "creature.h"
#include "npc.h"
#include "zone.h"
#include "LiftStub.h"

// 0x41bbe0
static unsigned char GetBlockState(Creature*)
{
    LIFT_STUB(0x41bbe0);
}

// 0x41bc20
bool __cdecl NpcIdleAction::Initialize(::Zone *, ::Npc *, ::NpcIdleAction::IdleType, long, unsigned char)
{
    LIFT_STUB(0x41bc20);
}

// 0x41bd70
bool __cdecl NpcIdleAction::IsAvailableAction(void)
{
    LIFT_STUB(0x41bd70);
}

// 0x41bdd0
void __cdecl NpcIdleAction::startAction(void)
{
    LIFT_STUB(0x41bdd0);
}

// 0x41be30
void __cdecl NpcIdleAction::intervalAction(long)
{
    LIFT_STUB(0x41be30);
}

// 0x41bee0
bool __cdecl NpcGroupMoveSyncAction::Initialize(::Zone *, ::Npc *, short)
{
    LIFT_STUB(0x41bee0);
}

// 0x41bfe0
void __cdecl NpcGroupMoveSyncAction::startAction(void)
{
    LIFT_STUB(0x41bfe0);
}

// 0x41c0a0
void __cdecl NpcGroupMoveSyncAction::intervalAction(long)
{
    LIFT_STUB(0x41c0a0);
}

// 0x41c130
bool __cdecl NpcSocialAction::Initialize(::Zone *, ::Npc *, unsigned int, short, long)
{
    LIFT_STUB(0x41c130);
}

// 0x41c270
void __cdecl NpcSocialAction::startAction(void)
{
    LIFT_STUB(0x41c270);
}

// 0x41c3b0
void __cdecl NpcSocialAction::intervalAction(long)
{
    LIFT_STUB(0x41c3b0);
}

// 0x41c460
void __cdecl NpcSocialAction::cancelAction(::Action::CancelReason, wchar_t const *, int)
{
    LIFT_STUB(0x41c460);
}

// 0x41c4f0
bool __cdecl NpcHideAction::Initialize(::Zone *, ::Npc *, bool, unsigned __int64)
{
    LIFT_STUB(0x41c4f0);
}

// 0x41c600
void __cdecl NpcHideAction::startAction(void)
{
    LIFT_STUB(0x41c600);
}

// 0x41c810
void __cdecl NpcHideAction::intervalAction(long)
{
    LIFT_STUB(0x41c810);
}

// 0x41c840
void __cdecl NpcHideAction::cancelAction(::Action::CancelReason, wchar_t const *, int)
{
    LIFT_STUB(0x41c840);
}

// 0x41c8d0
bool __cdecl NpcKnockBackAction::Initialize(::Zone *, ::Npc *, __int64)
{
    LIFT_STUB(0x41c8d0);
}

// 0x41c9d0
void __cdecl NpcKnockBackAction::startAction(void)
{
    LIFT_STUB(0x41c9d0);
}

// 0x41ca20
void __cdecl NpcKnockBackAction::finishAction(void)
{
    LIFT_STUB(0x41ca20);
}

// 0x41ca40
void __cdecl NpcKnockBackAction::cancelAction(::Action::CancelReason, wchar_t const *, int)
{
    LIFT_STUB(0x41ca40);
}

// 0x41ca80
#pragma comment(linker, "/INCLUDE:?NpcMoveTypeName@NpcPredefinedMoveAction@@SAPEA_WW4NpcMoveType@1@@Z")  // LIFT: dead-strip keep (no live caller yet)
wchar_t * __cdecl NpcPredefinedMoveAction::NpcMoveTypeName(::NpcPredefinedMoveAction::NpcMoveType npcMoveType)
{
    switch (npcMoveType)
    {
    case NPC_MOVE_TYPE_MOVEAROUND:
        return L"movearound";
    case NPC_MOVE_TYPE_PATHWAY_WALK:
        return L"pathway walk";
    case NPC_MOVE_TYPE_PATHWAY_RUN:
        return L"pathway run";
    case NPC_MOVE_TYPE_PATHWAY_SPRINT:
        return L"pathway sprint";
    }
    return L"unknown";
}

// 0x41cac0
bool __cdecl NpcPredefinedMoveAction::SetDestination(::vector16 const *, int, ::NpcPredefinedMoveAction::NpcMoveSpeed, bool, short)
{
    LIFT_STUB(0x41cac0);
}

// 0x41cc00
bool __cdecl NpcPredefinedMoveAction::IsAvailableAction(void)
{
    LIFT_STUB(0x41cc00);
}

// 0x41cc40
void __cdecl NpcPredefinedMoveAction::startAction(void)
{
    LIFT_STUB(0x41cc40);
}

// 0x41cd90
void __cdecl NpcPredefinedMoveAction::intervalAction(long)
{
    LIFT_STUB(0x41cd90);
}

// 0x41d150
bool __cdecl NpcPredefinedMoveAction::move(::vector16 const &, long, bool)
{
    LIFT_STUB(0x41d150);
}

// 0x41d450
bool __cdecl NpcPredefinedMoveAction::createPath(void)
{
    LIFT_STUB(0x41d450);
}

// 0x41d730
short __cdecl NpcPredefinedMoveAction::getSpeed(::NpcPredefinedMoveAction::NpcMoveSpeed) const
{
    LIFT_STUB(0x41d730);
}

// 0x41d7e0
short __cdecl NpcPredefinedMoveAction::getYaw(::vector16 const &, ::vector16 const &) const
{
    LIFT_STUB(0x41d7e0);
}

// 0x41d850
::MoveType __cdecl NpcPredefinedMoveAction::getMoveType(::NpcPredefinedMoveAction::NpcMoveSpeed) const
{
    LIFT_STUB(0x41d850);
}

// 0x41d8f0
long __cdecl NpcPredefinedMoveAction::getTimerDuration(void) const
{
    LIFT_STUB(0x41d8f0);
}

// 0x41db30
bool __cdecl NpcFallAction::Initialize(::Zone *, ::Npc *, ::GeoCell *)
{
    LIFT_STUB(0x41db30);
}

// 0x41dc30
bool __cdecl NpcFallAction::IsAvailableAction(void)
{
    LIFT_STUB(0x41dc30);
}

// 0x41dc60
void __cdecl NpcFallAction::startAction(void)
{
    LIFT_STUB(0x41dc60);
}

// 0x41de00
void __cdecl NpcFallAction::intervalAction(long)
{
    LIFT_STUB(0x41de00);
}

// 0x41e370
void __cdecl NpcFallAction::finishAction(void)
{
    LIFT_STUB(0x41e370);
}

// 0x41e420
void __cdecl NpcFallAction::cancelAction(::Action::CancelReason, wchar_t const *, int)
{
    LIFT_STUB(0x41e420);
}

// 0x41e510
__cdecl NpcPathFindMoveAction::NpcPathFindMoveAction(::ActionClass)
{
    LIFT_STUB(0x41e510);
}

// 0x41e580
bool __cdecl NpcPathFindMoveAction::Initialize(::Npc &, ::vector16 const &, ::MoveType, ::NpcPathFindMoveAction::NpcMoveSpeed, short, unsigned __int64, bool *const)
{
    LIFT_STUB(0x41e580);
}

// 0x41e670
bool __cdecl NpcPathFindMoveAction::IsStraightWalkable(::Zone *, ::vector16 const &, ::vector16 const &)
{
    LIFT_STUB(0x41e670);
}

// 0x41e730
bool __cdecl NpcPathFindMoveAction::isSameCell(::vector16 const &, ::vector16 const &)
{
    LIFT_STUB(0x41e730);
}

// 0x41e8d0
bool __cdecl NpcPathFindMoveAction::needResearch(void) const
{
    LIFT_STUB(0x41e8d0);
}

// 0x41e9d0
bool __cdecl NpcPathFindMoveAction::searchPath(::vector16 const &, long)
{
    LIFT_STUB(0x41e9d0);
}

// 0x41ed70
void __cdecl NpcPathFindMoveAction::startAction(void)
{
    LIFT_STUB(0x41ed70);
}

// 0x41ee80
void __cdecl NpcPathFindMoveAction::intervalAction(long)
{
    LIFT_STUB(0x41ee80);
}

// 0x41ef80
bool __cdecl NpcPathFindMoveAction::pathfindMove(::vector16 const &, long)
{
    LIFT_STUB(0x41ef80);
}

// 0x41f370
bool __cdecl NpcPathFindMoveAction::arrived(::vector16 const &, ::vector16 const &)
{
    LIFT_STUB(0x41f370);
}

// 0x41f390
bool __cdecl NpcPathFindMoveAction::move(::vector16 const &, long)
{
    LIFT_STUB(0x41f390);
}

// 0x41f800
short __cdecl NpcPathFindMoveAction::getSpeed(::NpcPathFindMoveAction::NpcMoveSpeed) const
{
    LIFT_STUB(0x41f800);
}

// 0x41f8b0
bool __cdecl NpcChaseMoveAction::Initialize(::Npc &, ::Creature &, short, ::MoveType, ::NpcPathFindMoveAction::NpcMoveSpeed, ::vector16 const &, bool, bool *const)
{
    LIFT_STUB(0x41f8b0);
}

// 0x41f980
::vector16 __cdecl NpcChaseMoveAction::getDestinationPos(::Creature *, ::Creature *, bool *const)
{
    LIFT_STUB(0x41f980);
}

// 0x4201a0
bool __cdecl NpcChaseMoveAction::updateDestination(::vector16 &, long)
{
    LIFT_STUB(0x4201a0);
}

// 0x420520
::NpcChaseMoveAction::DistanceCheckResult __cdecl NpcChaseMoveAction::CheckTargetDistance(::vector16 const &, ::vector16 const &, ::vector16 const &, ::Data::NpcRecordPtr)
{
    LIFT_STUB(0x420520);
}

// 0x420620
bool __cdecl NpcChaseMoveAction::arrived(::vector16 const &, ::vector16 const &)
{
    LIFT_STUB(0x420620);
}

// 0x420e20
bool __cdecl NpcFollowMoveAction::updateDestination(::vector16 &, long)
{
    LIFT_STUB(0x420e20);
}

// 0x420f40
bool __cdecl NpcFollowMoveAction::arrived(::vector16 const &, ::vector16 const &)
{
    LIFT_STUB(0x420f40);
}

// 0x420f60
void __cdecl NpcChangeWeaponAndStanceAction::startAction(void)
{
    LIFT_STUB(0x420f60);
}

// 0x421190
void __cdecl NpcChangeWeaponAndStanceAction::cancelAction(::Action::CancelReason, wchar_t const *, int)
{
    LIFT_STUB(0x421190);
}

// 0x421210
void __cdecl NpcChangeWeaponAndStanceAction::failAction(::Action::FailReason)
{
    LIFT_STUB(0x421210);
}

// 0x4212a0
void __cdecl NpcWarpAction::startAction(void)
{
    LIFT_STUB(0x4212a0);
}

// 0x4217a0
bool __cdecl NpcDetectCreatureAction::Initialize(::Zone *, ::Npc *, short, short)
{
    LIFT_STUB(0x4217a0);
}

// 0x4218b0
void __cdecl NpcDetectCreatureAction::startAction(void)
{
    LIFT_STUB(0x4218b0);
}

// 0x421cb0
void __cdecl NpcDetectCreatureAction::failAction(::Action::FailReason)
{
    LIFT_STUB(0x421cb0);
}
