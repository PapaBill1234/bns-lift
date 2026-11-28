// tagmatchduelmanager_h.cpp: tagmatchduelmanager.h (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "tagmatchduelmanager.h"
#include "duelmanager.h"
#include "pc.h"
#include "LiftStub.h"

#pragma comment(linker, "/INCLUDE:?verifyDuelType@TagMatchDuelManager@@EEBA_NXZ")  // LIFT: dead-strip keep (no live caller yet)

// Partial PDB offsets. DuelManager::_data (Data::DuelRecordPtr) is at +8 and holds one DrEl pointer.
// Data::DuelRecord::duel_type is at +32.
enum
{
    TagMatchDuelManager_data = 8,
    TagMatchDuelRecord_duel_type = 32
};

// 0x4c290
::DuelMember *const __cdecl TagMatchDuelTeam::instantiateDuelMember(int, int, ::Pc *const)
{
    LIFT_STUB(0x4c290);
}

// 0x4c390
bool __cdecl TagMatchDuelManager::verifyDuelType(void) const
{
    const char *record = *reinterpret_cast<const char *const *>(reinterpret_cast<const char *>(this) + TagMatchDuelManager_data);
    return record[TagMatchDuelRecord_duel_type] == 2;
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
