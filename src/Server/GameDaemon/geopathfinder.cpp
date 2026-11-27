// geopathfinder.cpp: geopathfinder.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "geopathfinder.h"
#include "LiftStub.h"

// 0xd8510
bool __cdecl LOSIterator::GetNext(int *, int *, int *)
{
    LIFT_STUB(0xd8510);
}

// 0xd8780
bool __cdecl GeoPathFinderCloseSet::Add(::_Node *)
{
    LIFT_STUB(0xd8780);
}

// 0xd8830
::_Node * __cdecl GeoPathFinderOpenSet::DeleteMin(void)
{
    LIFT_STUB(0xd8830);
}

// 0xd88b0
void __cdecl GeoMath::Initialize(void)
{
    LIFT_STUB(0xd88b0);
}

// 0xd8950
int __cdecl GeoMath::GetDistance(int, int)
{
    LIFT_STUB(0xd8950);
}

// 0xd89f0
bool __cdecl GeoPathFinder::findPath(::vector16, ::vector16, short, short, ::vector16 *const, int &)
{
    LIFT_STUB(0xd89f0);
}

// 0xd9030
::_Node * __cdecl GeoPathFinder::getNewNode(void)
{
    LIFT_STUB(0xd9030);
}

// 0xd90d0
int __cdecl GeoPathFinder::getNeighborNode(::_Node, ::_Node *, short, short)
{
    LIFT_STUB(0xd90d0);
}

// 0xd9250
void __cdecl GeoPathFinder::getResultPath(::vector16 *const, int &, ::_Node)
{
    LIFT_STUB(0xd9250);
}

// 0xd9350
bool __cdecl GeoPathFinder::findStraightPath(::vector16, ::vector16, short, short, ::vector16 *const, int, int &, ::GeoPathFinder::BlockedReason &)
{
    LIFT_STUB(0xd9350);
}
