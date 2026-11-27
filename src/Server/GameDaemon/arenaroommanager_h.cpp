// arenaroommanager_h.cpp: arenaroommanager.h (GameDaemon PDB, 2019 + PDB).
#include "arenaroommanager.h"
#include <intrin.h>
#include "LiftStub.h"

#pragma comment(linker, "/INCLUDE:?GetArenaPortalPublicRaidModeType@ArenaRoom@@UEBADXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?SetPublicRaidReservePcCount@ArenaPublicRaidRoom@@UEAAXH@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?IsSetPublicRaidReservePcCount@ArenaPublicRaidRoom@@UEAA_NXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetPublicRaidKey@ArenaPublicRaidRoom@@UEAA_KXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetArenaPortalPublicRaidModeType@ArenaPublicRaidRoom@@UEBADXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetArenaAttraction@ArenaDungeonRoom@@UEAADXZ")  // LIFT: dead-strip keep (no live caller yet)

// 0x27b20
char __cdecl ArenaRoom::GetArenaPortalPublicRaidModeType(void) const
{
    // ❓ PDB enumerator name not looked up. 6 is the value of the original.
    return 6;
}

// 0x27b30
void __cdecl ArenaPublicRaidRoom::SetPublicRaidReservePcCount(int count)
{
    _InterlockedCompareExchange(&_reservePcCount, count, 0);
}

// 0x27b40
bool __cdecl ArenaPublicRaidRoom::IsSetPublicRaidReservePcCount(void)
{
    return _InterlockedCompareExchange(&_reservePcCount, 0, 0) != 0;
}

// 0x27b50
int __cdecl ArenaPublicRaidRoom::GetPublicRaidReservePcCount(void)
{
    LIFT_STUB(0x27b50);
}

// 0x27b80
unsigned __int64 __cdecl ArenaPublicRaidRoom::GetPublicRaidKey(void)
{
    if (_interDungeonList._record != nullptr)  // LIFT: form (je to repz ret)
        return _interDungeonList._record->public_raid;
    return 0;
}

// 0x27ba0
char __cdecl ArenaPublicRaidRoom::GetArenaPortalPublicRaidModeType(void) const
{
    return _arenaPortalPublicRaidModeType;
}

// 0x66a1a0
char __cdecl ArenaDungeonRoom::GetArenaAttraction(void)
{
    // ❓ PDB enumerator name not looked up. 2 is the value of the original.
    return 2;
}
