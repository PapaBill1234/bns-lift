// npcparty_h.cpp: npcparty.h (GameDaemon PDB, 2019 + PDB).
#include "npcparty.h"
#include "zone.h"
#include "LiftStub.h"

#pragma comment(linker, "/INCLUDE:?TimerExpired@NpcPartyTimer@@EEAAXIJ@Z")  // LIFT: dead-strip keep (no live caller yet)

// 0x34f2c0
__cdecl NpcPartyTimer::NpcPartyTimer(::Zone *, ::NpcParty *)
{
    LIFT_STUB(0x34f2c0);
}

// 0x34f360
void __cdecl NpcPartyTimer::TimerExpired(unsigned int, long)
{
    _handler->OnTimer(GetZone());
}
