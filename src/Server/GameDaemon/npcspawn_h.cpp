// npcspawn_h.cpp: npcspawn.h (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "npcspawn.h"
#include "LiftStub.h"

// 0x1edf00
wchar_t const * __cdecl NpcSpawnInfo::GetAlias(void)
{
    LIFT_STUB(0x1edf00);
}

// 0x34f070
int __cdecl NpcSpawnInfo::GetActDetect(int)
{
    LIFT_STUB(0x34f070);
}

// 0x34f0b0
unsigned __int64 __cdecl NpcSpawnInfo::GetActSocial(int)
{
    LIFT_STUB(0x34f0b0);
}

// 0x34f0f0
::Data::ZoneAreaRecord::Key __cdecl NpcSpawn::PickAreaIdForNpcRandomSpawn(int)
{
    LIFT_STUB(0x34f0f0);
}
