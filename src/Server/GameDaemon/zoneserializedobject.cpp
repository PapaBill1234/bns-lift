// zoneserializedobject.cpp: zoneserializedobject.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "zoneserializedobject.h"
#include "zone.h"
#include "LiftStub.h"

// 0x25fa00
__cdecl ZoneSerializedObject::ZoneSerializedObject(void)
{
    LIFT_STUB(0x25fa00);
}

// 0x25fab0
__cdecl ZoneSerializedObject::~ZoneSerializedObject(void)
{
    LIFT_STUB(0x25fab0);
}

// 0x25fb40
void __cdecl ZoneSerializedObject::SetZone(::Zone *)
{
    LIFT_STUB(0x25fb40);
}

// LIFT: keep the lifted virtual until the callers are lifted (the vftable and the callers are stubs;
// /OPT:REF drops it). Card lift-gamedaemon-gap-006-e6.
#pragma comment(linker, "/INCLUDE:?TimerExpired@ZoneSerializedObject@@MEAAXJ@Z")  // LIFT: dead-strip keep (no live caller yet)

// 0x25fbf0
void __cdecl ZoneSerializedObject::TimerExpired(long elapsed)
{
    TimerExpired(1u, elapsed);  // DEFAULT_TIMER_ID
}

// 0x25fc00
void __cdecl ZoneSerializedObject::DetachParent(void)
{
    LIFT_STUB(0x25fc00);
}
