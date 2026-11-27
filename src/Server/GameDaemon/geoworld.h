// geoworld.h: geoworld.cpp, geoworld.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class GeoCube
{
protected:
    __cdecl GeoCube(void);  // 0xdb0d0
    void __cdecl Initialize(int, int, int);  // 0xdb110
    __cdecl ~GeoCube(void);  // 0xdb290
    static void __cdecl SetObjList(::ObjIndexList *, void *);  // 0xdb2f0
    static void __cdecl SetObjList(::ObjIndex16List *, void *);  // 0xdb3c0
};

struct geo_vector16
{
    short x;  // +0
    short y;  // +2
    short z;  // +4
};

struct geo_box16
{
    ::geo_vector16 l;  // +0
    ::geo_vector16 u;  // +6
};

struct GeoRegionSector
{
    int envIndex;  // +0
};

union RegionSectorPtr
{
    ::GeoRegionSector *ptr;  // +0
    __int64 offset;  // +0
};

union EnvPtr
{
    char *ptr;  // +0
    __int64 offset;  // +0
};

struct GeoDataRegion
{
    __int64 _size;  // +0
    int id;  // +8
    short sectorcx;  // +12
    short sectorcy;  // +14
    short sector_xmin;  // +16
    short sector_xmax;  // +18
    short sector_ymin;  // +20
    short sector_ymax;  // +22
    ::RegionSectorPtr sectors;  // +24
    ::EnvPtr envs;  // +32
    short origincx;  // +40
    short origincy;  // +42
};

struct GeoDataTerrain
{
    __int64 _size;  // +0
    int id;  // +8
    ::geo_box16 boundary;  // +12
    // LIFT: PDB members from sector_xmin (+24) to volumeCellOffsets (+104) are not declared yet. Size 0x70.
    char lift_pad_18[0x70 - 0x18];
};

class GeoRegion
{
public:
    char __cdecl GetEnv(int, int, int) const;  // 0x8c440
private:
    ::GeoRegionSector const *GET_SECTOR(int cx, int cy) const
    {
        return &region->sectors.ptr[(cx - region->origincx) / 8 * region->sectorcy + (cy - region->origincy) / 8];
    }
    ::GeoDataRegion *region;  // +0
};

class GeoTerrain
{
public:
    bool __cdecl FindCell(short, short, short, short, ::GeoCell &, int &) const;  // 0xdac60
    int X_TO_CELL_X(short x) const { return (x - terrain->boundary.l.x) / 8; }
    int Y_TO_CELL_Y(short y) const { return (y - terrain->boundary.l.y) / 8; }
private:
    ::GeoDataTerrain const *terrain;  // +0
};

class GeoWorld
{
public:
    __cdecl ~GeoWorld(void);  // 0xda0b0
    bool __cdecl Initialize(::GeoData const *);  // 0xda250
    bool __cdecl InitializeZone(void);  // 0xda560
    ::GeoZone const * __cdecl GetGeoZone(unsigned int) const;  // 0xda9e0
    int __cdecl EnumGeoZone(char, ::GeoZone **, int) const;  // 0xdaa60
private:
    ::GeoTerrain const * __cdecl getTerrain(unsigned int) const;  // 0xdab60
    ::GeoRegion const * __cdecl getRegion(unsigned int) const;  // 0xdabe0
};

class GeoZone
{
public:
    bool __cdecl FindCell(short, short, short, ::GeoCell &) const;  // 0x1d1c0
    unsigned int __cdecl CubeIndex(short, short, short) const;  // 0x8c4a0
    __cdecl GeoZone(void);  // 0xdb490
    __cdecl ~GeoZone(void);  // 0xdb5d0
    bool __cdecl InitializeByRecordMap(::Data::ZoneRecordPtr &, ::GeoTerrain const *, ::GeoRegion const *, ::RecordMaps *);  // 0xdbbb0
private:
    bool __cdecl buildPathwayRecordIndexByRecordMap(::RecordIndexMapContainer< ::Data::ZonePathwayRecordPtr> const *const);  // 0xdc030
public:
    ::Data::ZonePathwayRecordPtr __cdecl GetPathway(unsigned int, short) const;  // 0xdc4e0
private:
    bool __cdecl buildEnvRecordIndexByRecordMap(::RecordIndexMapContainer< ::Data::ZoneEnv2SpawnRecordPtr> const *const);  // 0xdc690
    bool __cdecl buildEventStage(void);  // 0xdca70
    void __cdecl getCubeIndexes(::vector16 &, ::vector16 &, unsigned short *const, int &);  // 0xdcef0
    bool __cdecl validatePosition(::dr_vector16 const &);  // 0xdd220
    bool __cdecl validateArea(::Data::ZoneAreaRecordPtr const *);  // 0xdd300
    bool __cdecl validateZoneNpcSpawnEvent(void);  // 0xdd620
    bool __cdecl validateZoneEvent(void);  // 0xdd6e0
public:
    bool __cdecl ConstructCube(int, int);  // 0xdd860
    bool __cdecl FindCell(short, short, short, short, ::GeoCell &) const;  // 0xdeeb0
    bool __cdecl GetPcSpawn(short, short &, short &, short &, short &) const;  // 0xdf030
    unsigned __int64 __cdecl GetRespawn(char) const;  // 0xdf0e0
    bool __cdecl FindRespawn(char, ::Data::ZoneRespawnRecordPtr *) const;  // 0xdf130
    bool __cdecl FindArea(unsigned int, ::box16 &) const;  // 0xdf1c0
private:
    bool __cdecl setRespawnPoint(void);  // 0xdf240
    bool __cdecl setBaseCampPoint(void);  // 0xdf400
    void __cdecl setIsBroadcastNpcSquadExist(void);  // 0xdf5c0
public:
    bool __cdecl IsFactionBattleFieldDungeon(void) const;  // 0xdf680
    bool __cdecl IsTeamPartyZone(void) const;  // 0xdf6d0
    int X_TO_CELL_X(short x) const { return terrain->X_TO_CELL_X(x); }
    int Y_TO_CELL_Y(short y) const { return terrain->Y_TO_CELL_Y(y); }
private:
    // LIFT: PDB members from zoneData (+0) to _eventStageCount (+424) are not declared yet.
    char lift_pad_0[0x1b0];
    ::GeoTerrain const *terrain;  // +432
    ::GeoRegion const *region;  // +440
};

class RecordMaps
{
public:
    __cdecl RecordMaps(void);  // 0xd97e0
    __cdecl ~RecordMaps(void);  // 0xd9df0
};

