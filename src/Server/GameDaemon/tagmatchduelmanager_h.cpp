// tagmatchduelmanager_h.cpp: tagmatchduelmanager.h (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "tagmatchduelmanager.h"
#include "duelmanager.h"
#include "pc.h"
#include "LiftStub.h"

// 0x4c290
::DuelMember *const __cdecl TagMatchDuelTeam::instantiateDuelMember(int, int, ::Pc *const)
{
    LIFT_STUB(0x4c290);
}

// 0x4c390
bool __cdecl TagMatchDuelManager::verifyDuelType(void) const
{
    LIFT_STUB(0x4c390);
}

// 0x4c3a0
::DuelRule *const __cdecl TagMatchDuelManager::instantiateDuelRule(void)
{
    LIFT_STUB(0x4c3a0);
}

// 0x4c400
::DuelTeam *const __cdecl TagMatchDuelManager::instantiateDuelTeam(int)
{
    LIFT_STUB(0x4c400);
}
