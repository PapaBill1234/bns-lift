// geomovechecker.cpp: geomovechecker.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "geomovechecker.h"
#include "zone.h"
#include "LiftStub.h"

// 0xd6520
int __cdecl LineIterator::X_TO_UX(int)
{
    LIFT_STUB(0xd6520);
}

// 0xd6570
int __cdecl LineIterator::Y_TO_UY(int)
{
    LIFT_STUB(0xd6570);
}

// 0xd65c0
bool __cdecl LineIterator::Initialize(::Zone const *, ::vector16, ::vector16)
{
    LIFT_STUB(0xd65c0);
}

// 0xd6980
bool __cdecl LineIterator::Next(int *, int *)
{
    LIFT_STUB(0xd6980);
}

// 0xd6ae0
bool __cdecl LineOfSightIterator::Initialize(::Zone const *, ::vector16, ::vector16)
{
    LIFT_STUB(0xd6ae0);
}

// 0xd6dd0
bool __cdecl LineOfSightIterator::Next(int *, int *, int *)
{
    LIFT_STUB(0xd6dd0);
}

// 0xd70e0
bool __cdecl GeoMoveChecker::Push(::Zone const *, ::vector16, ::vector16, short, short, ::vector16 *, ::GeoCell *, bool *, ::GeoMoveChecker::PushType)
{
    LIFT_STUB(0xd70e0);
}

// 0xd7ce0
bool __cdecl GeoMoveChecker::pushAdjacent(::Zone const *, ::GeoCell *, int, int, int, short, short, ::GeoCell *, bool &)
{
    LIFT_STUB(0xd7ce0);
}

// 0xd7ee0
bool __cdecl GeoMoveChecker::CheckLineOfSight(::Zone const *, ::vector16 &, ::vector16 &, short, ::GeoMoveChecker::CheckLineType)
{
    LIFT_STUB(0xd7ee0);
}
