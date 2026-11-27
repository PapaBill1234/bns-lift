// geopathfinder.h: geopathfinder.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class GeoMath
{
public:
    static void __cdecl Initialize(void);  // 0xd88b0
    static int __cdecl GetDistance(int, int);  // 0xd8950
};

class GeoPathFinder
{
public:
    enum BlockedReason {};
private:
    bool __cdecl findPath(::vector16, ::vector16, short, short, ::vector16 *const, int &);  // 0xd89f0
    ::_Node * __cdecl getNewNode(void);  // 0xd9030
    int __cdecl getNeighborNode(::_Node, ::_Node *, short, short);  // 0xd90d0
    void __cdecl getResultPath(::vector16 *const, int &, ::_Node);  // 0xd9250
    bool __cdecl findStraightPath(::vector16, ::vector16, short, short, ::vector16 *const, int, int &, ::GeoPathFinder::BlockedReason &);  // 0xd9350
};

class GeoPathFinderCloseSet
{
public:
    bool __cdecl Add(::_Node *);  // 0xd8780
};

class GeoPathFinderOpenSet
{
public:
    ::_Node * __cdecl DeleteMin(void);  // 0xd8830
};

class LOSIterator
{
public:
    bool __cdecl GetNext(int *, int *, int *);  // 0xd8510
};

