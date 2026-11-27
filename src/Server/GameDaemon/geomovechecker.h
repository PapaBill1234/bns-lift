// geomovechecker.h: geomovechecker.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class GeoMoveChecker
{
public:
    enum CheckLineType {};
    enum PushType {};
public:
    static bool __cdecl Push(::Zone const *, ::vector16, ::vector16, short, short, ::vector16 *, ::GeoCell *, bool *, ::GeoMoveChecker::PushType);  // 0xd70e0
private:
    static bool __cdecl pushAdjacent(::Zone const *, ::GeoCell *, int, int, int, short, short, ::GeoCell *, bool &);  // 0xd7ce0
public:
    static bool __cdecl CheckLineOfSight(::Zone const *, ::vector16 &, ::vector16 &, short, ::GeoMoveChecker::CheckLineType);  // 0xd7ee0
};

class LineIterator
{
public:
    int __cdecl X_TO_UX(int);  // 0xd6520
    int __cdecl Y_TO_UY(int);  // 0xd6570
    bool __cdecl Initialize(::Zone const *, ::vector16, ::vector16);  // 0xd65c0
    bool __cdecl Next(int *, int *);  // 0xd6980
};

class LineOfSightIterator
{
public:
    bool __cdecl Initialize(::Zone const *, ::vector16, ::vector16);  // 0xd6ae0
    bool __cdecl Next(int *, int *, int *);  // 0xd6dd0
};

