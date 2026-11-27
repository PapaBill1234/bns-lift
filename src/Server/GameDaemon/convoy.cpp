// convoy.cpp: convoy.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "convoy.h"
#include "creature.h"
#include "gameobject.h"
#include "npc.h"
#include "pc.h"
#include "zone.h"
#include "LiftStub.h"

// 0x40bbd0
__cdecl Convoy::Convoy(::Zone *, ::Data::ZoneConvoyRecordPtr)
{
    LIFT_STUB(0x40bbd0);
}

// 0x40bd80
void __cdecl Convoy::EventOccured(::ScriptEvent const *)
{
    LIFT_STUB(0x40bd80);
}

// 0x40bdd0
void __cdecl Convoy::OnTimer(::Zone *)
{
    LIFT_STUB(0x40bdd0);
}

// 0x40bfa0
::GameFailReason __cdecl Convoy::CanStart(::Pc *, unsigned char, ::Npc **const)
{
    LIFT_STUB(0x40bfa0);
}

// 0x40c170
bool __cdecl Convoy::Start(::Pc *, ::Npc **const)
{
    LIFT_STUB(0x40c170);
}

// 0x40c630
bool __cdecl Convoy::AddPc(::Pc *)
{
    LIFT_STUB(0x40c630);
}

// 0x40c710
bool __cdecl Convoy::RemovePc(::Pc *)
{
    LIFT_STUB(0x40c710);
}

// 0x40c780
void __cdecl Convoy::checkArrived(::GameObject *, ::GameObject *)
{
    LIFT_STUB(0x40c780);
}

// 0x40cdf0
void __cdecl Convoy::OnAttacked(::Pc *, ::Creature *)
{
    LIFT_STUB(0x40cdf0);
}

// 0x40ceb0
void __cdecl Convoy::checkNpcKilled(::GameObject *)
{
    LIFT_STUB(0x40ceb0);
}

// 0x40d010
void __cdecl Convoy::OnFailed(::Pc *, ::GameFailReason)
{
    LIFT_STUB(0x40d010);
}

// 0x40d0b0
void __cdecl Convoy::failed(::Pc *, ::GameFailReason)
{
    LIFT_STUB(0x40d0b0);
}

// 0x40d240
void __cdecl Convoy::OnDisposeQuest(::Pc *, unsigned __int64)
{
    LIFT_STUB(0x40d240);
}

// 0x40d320
void __cdecl Convoy::failedAll(void)
{
    LIFT_STUB(0x40d320);
}

// 0x40d780
void __cdecl Convoy::resetAll(void)
{
    LIFT_STUB(0x40d780);
}
