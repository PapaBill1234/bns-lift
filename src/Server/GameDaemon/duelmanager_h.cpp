// duelmanager_h.cpp: duelmanager.h (GameDaemon PDB, 2019 + PDB).
// LIFT: per-exe StlMemory.h path (A6). The inlined std::list head node allocation uses the GameDaemon build path.
#define LIFT_STLMEMORY_FILE \
    L"e:\\dailybuild02\\gamedaemon-common-0.0.348\\depot\\branch\\348nc\\program\\server\\bloodlib\\include\\StlMemory.h"
#include "duelmanager.h"
#include "Memory.h"
#include "pc.h"
#include "LiftStub.h"

// 0x27bb0
__cdecl DuelTeam::DuelTeam(int const, int const teamIndex)
    : _teamIndex(teamIndex)
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
#pragma comment(linker, "/INCLUDE:?isSaveGameResult@DuelManager@@AEBA_NXZ")  // LIFT: dead-strip keep (no live caller yet)
bool __cdecl DuelManager::isSaveGameResult(void) const
{
    ::DuelManagerView const *const self = reinterpret_cast< ::DuelManagerView const *>(this);
    return !self->_data->is_unrated_match && self->_calcRatingScore;
}
