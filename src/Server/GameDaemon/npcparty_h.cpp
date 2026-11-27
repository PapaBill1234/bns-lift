// npcparty_h.cpp: npcparty.h (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "npcparty.h"
#include "zone.h"
#include "LiftStub.h"

// 0x34f2c0
__cdecl NpcPartyTimer::NpcPartyTimer(::Zone *, ::NpcParty *)
{
    LIFT_STUB(0x34f2c0);
}

// 0x34f360
void __cdecl NpcPartyTimer::TimerExpired(unsigned int, long)
{
    LIFT_STUB(0x34f360);
}
