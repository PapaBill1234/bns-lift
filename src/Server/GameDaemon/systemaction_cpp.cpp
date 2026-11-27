// systemaction_cpp.cpp: systemaction.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "systemaction.h"
#include "action.h"
#include "bossnpc.h"
#include "controlledcreature.h"
#include "creature.h"
#include "pc.h"
#include "zone.h"
#include "LiftStub.h"

// 0x4b4600
wchar_t const * __cdecl GetEnterReasonString(::EnterReason)
{
    LIFT_STUB(0x4b4600);
}

// 0x4b46a0
wchar_t const * __cdecl GetLeaveReasonString(::LeaveReason)
{
    LIFT_STUB(0x4b46a0);
}

// 0x4b47e0
bool __cdecl PcSpawnAction::Initialize(::Zone *, ::Creature *, short, short, short, short, short, unsigned __int64, ::EnterReason, unsigned __int64, bool, bool, unsigned int)
{
    LIFT_STUB(0x4b47e0);
}

// 0x4b4a60
void __cdecl PcSpawnAction::AddNext(::PcSpawnAction *)
{
    LIFT_STUB(0x4b4a60);
}

// 0x4b4b00
void __cdecl PcSpawnAction::startAction(void)
{
    LIFT_STUB(0x4b4b00);
}

// 0x4b4db0
void __cdecl PcSpawnAction::intervalAction(long)
{
    LIFT_STUB(0x4b4db0);
}

// 0x4b4e50
void __cdecl PcSpawnAction::prepareSpawn(void)
{
    LIFT_STUB(0x4b4e50);
}

// 0x4b5160
bool __cdecl PcSpawnAction::spawn(::ControlledCreature *, ::vector16, ::GeoCell, short, unsigned __int64, bool)
{
    LIFT_STUB(0x4b5160);
}

// 0x4b5500
void __cdecl PcSpawnAction::SpawnCreature(::vector16, short)
{
    LIFT_STUB(0x4b5500);
}

// 0x4b5ab0
void __cdecl PcSpawnAction::finishAction(void)
{
    LIFT_STUB(0x4b5ab0);
}

// 0x4b6dd0
void __cdecl PcSpawnAction::cancelAction(::Action::CancelReason, wchar_t const *, int)
{
    LIFT_STUB(0x4b6dd0);
}

// 0x4b6e50
void __cdecl PcSpawnAction::failAction(::Action::FailReason)
{
    LIFT_STUB(0x4b6e50);
}

// 0x4b6ea0
void __cdecl PcSpawnAction::revive(void)
{
    LIFT_STUB(0x4b6ea0);
}

// 0x4b7630
bool __cdecl PcSpawnAction::checkSpawnPosition(void)
{
    LIFT_STUB(0x4b7630);
}

// 0x4b7930
::ActionPriorityClass __cdecl LeaveAction::getPriority(void) const
{
    LIFT_STUB(0x4b7930);
}

// 0x4b7970
__cdecl LeaveAction::LeaveAction(void)
{
    LIFT_STUB(0x4b7970);
}

// 0x4b7b10
void __cdecl LeaveAction::applyLeaveCost(void)
{
    LIFT_STUB(0x4b7b10);
}

// 0x4b8310
bool __cdecl LeaveAction::initialize(::Zone *, ::Creature *, ::LeaveType, unsigned int, short, unsigned __int64, short, ::LeaveReason, unsigned __int64, unsigned __int64, unsigned __int64, unsigned __int64, ::LeaveAction::PhaseZone *, unsigned __int64, unsigned __int64)
{
    LIFT_STUB(0x4b8310);
}

// 0x4b87d0
bool __cdecl LeaveAction::Initialize(::Zone *, ::Creature *, ::LeaveType, unsigned int, ::LeaveReason, unsigned __int64, unsigned __int64, unsigned __int64, unsigned __int64, unsigned __int64)
{
    LIFT_STUB(0x4b87d0);
}

// 0x4b8850
bool __cdecl LeaveAction::InitializeWithPcSpawn(::Zone *, ::Creature *, ::LeaveType, unsigned int, short, ::LeaveReason, unsigned __int64, unsigned __int64, unsigned __int64, unsigned __int64, ::LeaveAction::PhaseZone *, unsigned __int64)
{
    LIFT_STUB(0x4b8850);
}

// 0x4b88e0
bool __cdecl LeaveAction::InitializeWithArea(::Zone *, ::Creature *, ::LeaveType, unsigned int, unsigned __int64, ::LeaveReason, unsigned __int64, unsigned __int64, unsigned __int64, unsigned __int64, ::LeaveAction::PhaseZone *)
{
    LIFT_STUB(0x4b88e0);
}

// 0x4b8970
bool __cdecl LeaveAction::Initialize(::Zone *, ::Creature *, unsigned int, short)
{
    LIFT_STUB(0x4b8970);
}

// 0x4b8a90
bool __cdecl LeaveAction::Initialize(::Zone *, ::Creature *, short)
{
    LIFT_STUB(0x4b8a90);
}

// 0x4b8b00
bool __cdecl LeaveAction::InitializeWithEnterArenaLobby(::Zone *, ::Creature *, ::ArenaLobbyRoomInfo &)
{
    LIFT_STUB(0x4b8b00);
}

// 0x4b8be0
bool __cdecl LeaveAction::InitializeWithReturnToArenaDungeon(::Zone *, ::Creature *, ::ArenaLobbyRoomInfo &)
{
    LIFT_STUB(0x4b8be0);
}

// 0x4b8cc0
bool __cdecl LeaveAction::InitializeWithReturnToArenaLobby(::Zone *, ::Pc *, unsigned __int64)
{
    LIFT_STUB(0x4b8cc0);
}

// 0x4b8df0
bool __cdecl LeaveAction::Initialize(::Zone *, ::Creature *, ::LeaveType, unsigned int, short, ::vector16 &, ::LeaveReason, unsigned __int64, unsigned __int64, unsigned __int64, unsigned __int64)
{
    LIFT_STUB(0x4b8df0);
}

// 0x4b8e90
bool __cdecl LeaveAction::Initialize(::Zone *, ::Creature *, ::LeaveType, unsigned int, ::vector16, ::LeaveReason)
{
    LIFT_STUB(0x4b8e90);
}

// 0x4b8f20
bool __cdecl LeaveAction::Initialize(::Zone *, ::Creature *, ::LeaveType, unsigned int, unsigned __int64, ::LeaveReason)
{
    LIFT_STUB(0x4b8f20);
}

// 0x4b8f90
__cdecl LeaveAction::~LeaveAction(void)
{
    LIFT_STUB(0x4b8f90);
}

// 0x4b90d0
void __cdecl LeaveAction::AddNext(::LeaveAction *)
{
    LIFT_STUB(0x4b90d0);
}

// 0x4b9170
::LeaveAction * __cdecl LeaveAction::RemoveNext(void)
{
    LIFT_STUB(0x4b9170);
}

// 0x4b91c0
void __cdecl LeaveAction::Post(void)
{
    LIFT_STUB(0x4b91c0);
}

// 0x4b92e0
bool __cdecl LeaveAction::prepareAction(void)
{
    LIFT_STUB(0x4b92e0);
}

// 0x4b9710
void __cdecl LeaveAction::startAction(void)
{
    LIFT_STUB(0x4b9710);
}

// 0x4ba1a0
bool __cdecl LeaveAction::selectTransitZone(short, unsigned __int64 *, unsigned int *, unsigned __int64 *, unsigned __int64 *, unsigned __int64 *, unsigned __int64 *, short *, char)
{
    LIFT_STUB(0x4ba1a0);
}

// 0x4ba3f0
void __cdecl LeaveAction::intervalAction(long)
{
    LIFT_STUB(0x4ba3f0);
}

// 0x4ba420
void __cdecl LeaveAction::finishAction(void)
{
    LIFT_STUB(0x4ba420);
}

// 0x4baef0
void __cdecl LeaveAction::cancelAction(::Action::CancelReason, wchar_t const *, int)
{
    LIFT_STUB(0x4baef0);
}

// 0x4baf90
void __cdecl LeaveAction::failAction(::Action::FailReason)
{
    LIFT_STUB(0x4baf90);
}

// 0x4bb000
bool __cdecl LeaveAction::translatePosition(void)
{
    LIFT_STUB(0x4bb000);
}

// 0x4bb530
void __cdecl LeaveAction::sendFailPacket(::GameFailReason)
{
    LIFT_STUB(0x4bb530);
}

// 0x4bb5a0
void __cdecl LeaveAction::clearChannelChangeCooltime(void)
{
    LIFT_STUB(0x4bb5a0);
}

// 0x4bb5e0
void __cdecl DieAction::startAction(void)
{
    LIFT_STUB(0x4bb5e0);
}

// 0x4bb700
void __cdecl DieAction::finishAction(void)
{
    LIFT_STUB(0x4bb700);
}

// 0x4bb8b0
void __cdecl DieAction::cancelAction(::Action::CancelReason, wchar_t const *, int)
{
    LIFT_STUB(0x4bb8b0);
}

// 0x4bb950
void __cdecl DieAction::spawnAdditionalNpc(::BossNpc *)
{
    LIFT_STUB(0x4bb950);
}

// 0x4bbc60
void __cdecl DieAction::getAuthorizedMember(::BossNpc *, ::NpcSpawnParam &)
{
    LIFT_STUB(0x4bbc60);
}

// 0x4bbed0
void __cdecl ReviveAction::startAction(void)
{
    LIFT_STUB(0x4bbed0);
}

// 0x4bc0e0
void __cdecl ReviveAction::finishAction(void)
{
    LIFT_STUB(0x4bc0e0);
}

// 0x4bc160
void __cdecl ReviveAction::cancelAction(::Action::CancelReason, wchar_t const *, int)
{
    LIFT_STUB(0x4bc160);
}

// 0x4bc1f0
void __cdecl ReviveAction::failAction(::Action::FailReason)
{
    LIFT_STUB(0x4bc1f0);
}

// 0x4bc260
bool __cdecl RestorationAction::calcHelperTime(void)
{
    LIFT_STUB(0x4bc260);
}

// 0x4bc340
bool __cdecl RestorationAction::updateRemainTime(void)
{
    LIFT_STUB(0x4bc340);
}

// 0x4bc4a0
void __cdecl RestorationAction::finishHelperAction(void)
{
    LIFT_STUB(0x4bc4a0);
}

// 0x4bc560
bool __cdecl RestorationAction::LeaveHelper(::ControlledCreature *)
{
    LIFT_STUB(0x4bc560);
}

// 0x4bc600
bool __cdecl RestorationAction::prepareAction(void)
{
    LIFT_STUB(0x4bc600);
}

// 0x4bc6a0
void __cdecl RestorationAction::startAction(void)
{
    LIFT_STUB(0x4bc6a0);
}

// 0x4bcad0
void __cdecl RestorationAction::revive(void)
{
    LIFT_STUB(0x4bcad0);
}

// 0x4bd330
void __cdecl RestorationAction::die(unsigned __int64)
{
    LIFT_STUB(0x4bd330);
}

// 0x4bd3d0
void __cdecl RestorationAction::failAction(::Action::FailReason)
{
    LIFT_STUB(0x4bd3d0);
}

// 0x4bd400
void __cdecl RestorationAction::finishAction(void)
{
    LIFT_STUB(0x4bd400);
}

// 0x4bdd20
void __cdecl RestorationAction::cancelAction(::Action::CancelReason, wchar_t const *, int, unsigned __int64)
{
    LIFT_STUB(0x4bdd20);
}

// 0x4bde10
bool __cdecl RestorationAction::availableCancel(::CancelActionReason)
{
    LIFT_STUB(0x4bde10);
}

// 0x4bde20
void __cdecl HelpRestorationAction::startAction(void)
{
    LIFT_STUB(0x4bde20);
}

// 0x4be310
void __cdecl HelpRestorationAction::failAction(::Action::FailReason)
{
    LIFT_STUB(0x4be310);
}

// 0x4be370
void __cdecl HelpRestorationAction::finishAction(void)
{
    LIFT_STUB(0x4be370);
}

// 0x4be460
void __cdecl HelpRestorationAction::cancelAction(::Action::CancelReason, wchar_t const *, int)
{
    LIFT_STUB(0x4be460);
}
