// npcsquad.cpp: npcsquad.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "npcsquad.h"
#include "creature.h"
#include "npc.h"
#include "zone.h"
#include "LiftStub.h"

// 0x42d000
__cdecl NpcSquad::NpcSquad(::Zone *, ::Data::ZoneNpcSquadRecordPtr)
{
    LIFT_STUB(0x42d000);
}

// 0x42d0a0
void __cdecl NpcSquad::EventOccured(::ScriptEvent const *)
{
    LIFT_STUB(0x42d0a0);
}

// 0x42d140
bool __cdecl NpcSquad::Add(::Npc *)
{
    LIFT_STUB(0x42d140);
}

// 0x42d310
void __cdecl NpcSquad::AddHate(::Npc *, ::Creature *, char)
{
    LIFT_STUB(0x42d310);
}

// 0x42d520
void __cdecl NpcSquad::GroupMoveThink(::NpcSquad::GroupMoveEvent, ::Npc *)
{
    LIFT_STUB(0x42d520);
}

// 0x42d7c0
unsigned __int64 __cdecl NpcSquad::GetNearMembersTargetId(::Npc &)
{
    LIFT_STUB(0x42d7c0);
}

// 0x42da10
void __cdecl NpcSquad::ResetCombat(void)
{
    LIFT_STUB(0x42da10);
}

// 0x42db10
bool __cdecl NpcSquad::CheckLeaderlessParty(::Data::ZoneNpcSpawnRecordPtr const &)
{
    LIFT_STUB(0x42db10);
}
