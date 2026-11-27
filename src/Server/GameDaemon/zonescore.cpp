// zonescore.cpp: zonescore.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "zonescore.h"
#include "LiftStub.h"

// 0x25f710
void __cdecl ZoneScore::AddScore(char, short)
{
    LIFT_STUB(0x25f710);
}

// 0x25f7a0
bool __cdecl ZoneScore::FetchPartyBattleScore(::FragmentPacket &, char)
{
    LIFT_STUB(0x25f7a0);
}

// 0x25f870
bool __cdecl ZoneScore::FetchScoreTypeHistory(::FragmentPacket &)
{
    LIFT_STUB(0x25f870);
}
