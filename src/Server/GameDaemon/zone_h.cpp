// zone_h.cpp: zone.h (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "zone.h"
#include "creature.h"
#include "LiftStub.h"

// 0x35f70
::Pointer2< ::Creature> __cdecl Zone::GetCreaturePtr(unsigned __int64)
{
    LIFT_STUB(0x35f70);
}

// 0x35fa0
void __cdecl Zone::ReleaseCreature(::Creature *)
{
    LIFT_STUB(0x35fa0);
}

// 0x180e80
::Creature * __cdecl Zone::AcquireCreature(unsigned __int64)
{
    LIFT_STUB(0x180e80);
}

// 0x1ee760
::Pointer2< ::Creature> __cdecl Zone::GetMobileCreaturePtr(unsigned __int64)
{
    LIFT_STUB(0x1ee760);
}

// 0x1ee7a0
int __cdecl Zone::getBroadcastCubeIndex(int, int, int) const
{
    LIFT_STUB(0x1ee7a0);
}

// 0x350390
void __cdecl Zone::SetTransitableByNpcPortal(bool)
{
    LIFT_STUB(0x350390);
}
