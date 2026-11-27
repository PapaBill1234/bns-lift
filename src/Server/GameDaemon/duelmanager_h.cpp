// duelmanager_h.cpp: duelmanager.h (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "duelmanager.h"
#include "pc.h"
#include "LiftStub.h"

// 0x27bb0
__cdecl DuelTeam::DuelTeam(int, int)
{
    LIFT_STUB(0x27bb0);
}

// 0x27c30
__cdecl DuelTeam::~DuelTeam(void)
{
    LIFT_STUB(0x27c30);
}

// 0x27d60
::DuelMember *const __cdecl DuelTeam::instantiateDuelMember(int, int, ::Pc *const)
{
    LIFT_STUB(0x27d60);
}

// 0x97070
bool __cdecl DuelManager::isSaveGameResult(void) const
{
    LIFT_STUB(0x97070);
}
