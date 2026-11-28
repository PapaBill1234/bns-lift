// npcsquad.cpp: npcsquad.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "npcsquad.h"
#include "creature.h"
#include "npc.h"
#include "zone.h"
#include "LiftStub.h"
#include <string.h>

// 0x42d000
__cdecl NpcSquad::NpcSquad(::Zone *, ::Data::ZoneNpcSquadRecordPtr)
{
    LIFT_STUB(0x42d000);
}

// LIFT: view of the PDB ScriptEvent (size 0x98). The skeleton ScriptEvent has no members yet.
struct ScriptEventView
{
    char objectType;          // +0x0
    char type;                // +0x1
    bool broadcasted;         // +0x2
    ::Zone *zone;             // +0x8
    ::GameObject *subject;    // +0x10
    char param[0x98 - 0x18];  // +0x18 (PDB: ScriptParam param[8])
};
static_assert(sizeof(ScriptEventView) == 0x98, "ScriptEvent size (PDB)");

// 0x42d0a0
#pragma comment(linker, "/INCLUDE:?EventOccured@NpcSquad@@EEAAXPEBVScriptEvent@@@Z")  // LIFT: dead-strip keep (no live caller yet)
void __cdecl NpcSquad::EventOccured(::ScriptEvent const *e)
{
    if (e == nullptr)
        return;
    if (_leaderIdx < 0 || _leaderIdx >= _maxNpc)
        return;
    ::Npc *leader = NpcParty::_npc[_leaderIdx];
    if (leader == nullptr)
        return;
    ScriptEventView broadcastedEvent;
    memcpy(&broadcastedEvent, e, sizeof(broadcastedEvent));
    broadcastedEvent.broadcasted = true;
    leader->Think(reinterpret_cast<const ::ScriptEvent *>(&broadcastedEvent));
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
