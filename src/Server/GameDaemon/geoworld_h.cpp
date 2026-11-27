// geoworld_h.cpp: geoworld.h (GameDaemon PDB, 2019 + PDB).
#include "geoworld.h"
#include "LiftStub.h"

#pragma comment(linker, "/INCLUDE:?FindCell@GeoZone@@QEBA_NFFFAEAUGeoCell@@@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetEnv@GeoRegion@@QEBADHHH@Z")  // LIFT: dead-strip keep (no live caller yet)

// 0x1d1c0
bool __cdecl GeoZone::FindCell(short x, short y, short z, ::GeoCell &cell) const
{
    return FindCell(X_TO_CELL_X(x), Y_TO_CELL_Y(y), z, z + 8, cell);
}

// 0x8c440
char __cdecl GeoRegion::GetEnv(int envOffset, int cx, int cy) const
{
    ::GeoRegionSector const *sector = GET_SECTOR(cx, cy);
    if (sector->envIndex < 0)
        return 0;
    return (region->envs.ptr + sector->envIndex)[envOffset];
}

// 0x8c4a0
unsigned int __cdecl GeoZone::CubeIndex(short, short, short) const
{
    LIFT_STUB(0x8c4a0);
}
