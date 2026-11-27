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

class GeoRegion
{
public:
    char __cdecl GetEnv(int, int, int) const;  // 0x8c440
};

class GeoTerrain
{
public:
    bool __cdecl FindCell(short, short, short, short, ::GeoCell &, int &) const;  // 0xdac60
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
};

class RecordMaps
{
public:
    __cdecl RecordMaps(void);  // 0xd97e0
    __cdecl ~RecordMaps(void);  // 0xd9df0
};

