// deathmatchduelmanager_h.cpp: deathmatchduelmanager.h (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "deathmatchduelmanager.h"
#include "duelmanager.h"
#include "LiftStub.h"

#pragma comment(linker, "/INCLUDE:?verifyDuelType@DeathMatchDuelManager@@EEBA_NXZ")  // LIFT: dead-strip keep (no live caller yet)

// Partial PDB offsets. DuelManager::_data (Data::DuelRecordPtr) is at +8 and holds one DrEl pointer.
// Data::DuelRecord::duel_type is at +32.
enum
{
    DuelManager_data = 8,
    DuelRecord_duel_type = 32
};

// 0x4c180
bool __cdecl DeathMatchDuelManager::verifyDuelType(void) const
{
    const char *record = *reinterpret_cast<const char *const *>(reinterpret_cast<const char *>(this) + DuelManager_data);
    return record[DuelRecord_duel_type] == 1;
}

// 0x4c190
::DuelRule *const __cdecl DeathMatchDuelManager::instantiateDuelRule(void)
{
    LIFT_STUB(0x4c190);
}

// 0x4c1e0
::DuelTeam *const __cdecl DeathMatchDuelManager::instantiateDuelTeam(int)
{
    LIFT_STUB(0x4c1e0);
}
