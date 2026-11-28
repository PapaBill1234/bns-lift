// geoworld_cpp.cpp: geoworld.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "geoworld.h"
#include "Memory.h"
#include "LiftStub.h"
#include <string.h>

#define GEOWORLD_FILE L"e:\\dailybuild02\\gamedaemon-common-0.0.348\\depot\\branch\\348nc\\program\\server\\gamedaemon\\GeoWorld.cpp"

#pragma comment(linker, "/INCLUDE:??0GeoCube@@IEAA@XZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:??1GeoCube@@IEAA@XZ")  // LIFT: dead-strip keep (no live caller yet)

// 0xd97e0
__cdecl RecordMaps::RecordMaps(void)
{
    LIFT_STUB(0xd97e0);
}

// 0xd9df0
__cdecl RecordMaps::~RecordMaps(void)
{
    LIFT_STUB(0xd9df0);
}

// 0xda0b0
__cdecl GeoWorld::~GeoWorld(void)
{
    LIFT_STUB(0xda0b0);
}

// 0xda250
bool __cdecl GeoWorld::Initialize(::GeoData const *)
{
    LIFT_STUB(0xda250);
}

// 0xda560
bool __cdecl GeoWorld::InitializeZone(void)
{
    LIFT_STUB(0xda560);
}

// 0xda9e0
::GeoZone const * __cdecl GeoWorld::GetGeoZone(unsigned int) const
{
    LIFT_STUB(0xda9e0);
}

// 0xdaa60
int __cdecl GeoWorld::EnumGeoZone(char, ::GeoZone **, int) const
{
    LIFT_STUB(0xdaa60);
}

// 0xdab60
::GeoTerrain const * __cdecl GeoWorld::getTerrain(unsigned int) const
{
    LIFT_STUB(0xdab60);
}

// 0xdabe0
::GeoRegion const * __cdecl GeoWorld::getRegion(unsigned int) const
{
    LIFT_STUB(0xdabe0);
}

// 0xdac60
bool __cdecl GeoTerrain::FindCell(short, short, short, short, ::GeoCell &, int &) const
{
    LIFT_STUB(0xdac60);
}

// 0xdb0d0
__cdecl GeoCube::GeoCube(void)
{
    index = 0;
    nearbyCount = 0;
    memset(nearby, 0, sizeof(nearby));
    memset(&visibleEnvObjs, 0, sizeof(visibleEnvObjs));
    memset(&checkEnvObjs, 0, sizeof(checkEnvObjs));
    memset(&gatherSources, 0, sizeof(gatherSources));
}

// 0xdb110
void __cdecl GeoCube::Initialize(int, int, int)
{
    LIFT_STUB(0xdb110);
}

// 0xdb290
__cdecl GeoCube::~GeoCube(void)
{
    if (visibleEnvObjs.list != nullptr)
        Memory::_Manager[1]->Free(visibleEnvObjs.list, GEOWORLD_FILE, 1546);
    if (checkEnvObjs.list != nullptr)
        Memory::_Manager[1]->Free(checkEnvObjs.list, GEOWORLD_FILE, 1549);
}

// 0xdb2f0
void __cdecl GeoCube::SetObjList(::ObjIndexList *, void *)
{
    LIFT_STUB(0xdb2f0);
}

// 0xdb3c0
void __cdecl GeoCube::SetObjList(::ObjIndex16List *, void *)
{
    LIFT_STUB(0xdb3c0);
}

// 0xdb490
__cdecl GeoZone::GeoZone(void)
{
    LIFT_STUB(0xdb490);
}

// 0xdb5d0
__cdecl GeoZone::~GeoZone(void)
{
    LIFT_STUB(0xdb5d0);
}

// 0xdbbb0
bool __cdecl GeoZone::InitializeByRecordMap(::Data::ZoneRecordPtr &, ::GeoTerrain const *, ::GeoRegion const *, ::RecordMaps *)
{
    LIFT_STUB(0xdbbb0);
}

// 0xdc030
bool __cdecl GeoZone::buildPathwayRecordIndexByRecordMap(::RecordIndexMapContainer< ::Data::ZonePathwayRecordPtr> const *const)
{
    LIFT_STUB(0xdc030);
}

// 0xdc4e0
::Data::ZonePathwayRecordPtr __cdecl GeoZone::GetPathway(unsigned int, short) const
{
    LIFT_STUB(0xdc4e0);
}

// 0xdc690
bool __cdecl GeoZone::buildEnvRecordIndexByRecordMap(::RecordIndexMapContainer< ::Data::ZoneEnv2SpawnRecordPtr> const *const)
{
    LIFT_STUB(0xdc690);
}

// 0xdca70
bool __cdecl GeoZone::buildEventStage(void)
{
    LIFT_STUB(0xdca70);
}

// 0xdcef0
void __cdecl GeoZone::getCubeIndexes(::vector16 &, ::vector16 &, unsigned short *const, int &)
{
    LIFT_STUB(0xdcef0);
}

// 0xdd220
bool __cdecl GeoZone::validatePosition(::dr_vector16 const &)
{
    LIFT_STUB(0xdd220);
}

// 0xdd300
bool __cdecl GeoZone::validateArea(::Data::ZoneAreaRecordPtr const *)
{
    LIFT_STUB(0xdd300);
}

// 0xdd620
bool __cdecl GeoZone::validateZoneNpcSpawnEvent(void)
{
    LIFT_STUB(0xdd620);
}

// 0xdd6e0
bool __cdecl GeoZone::validateZoneEvent(void)
{
    LIFT_STUB(0xdd6e0);
}

// 0xdd860
bool __cdecl GeoZone::ConstructCube(int, int)
{
    LIFT_STUB(0xdd860);
}

// 0xdeeb0
bool __cdecl GeoZone::FindCell(short, short, short, short, ::GeoCell &) const
{
    LIFT_STUB(0xdeeb0);
}

// 0xdf030
bool __cdecl GeoZone::GetPcSpawn(short, short &, short &, short &, short &) const
{
    LIFT_STUB(0xdf030);
}

// 0xdf0e0
unsigned __int64 __cdecl GeoZone::GetRespawn(char) const
{
    LIFT_STUB(0xdf0e0);
}

// 0xdf130
bool __cdecl GeoZone::FindRespawn(char, ::Data::ZoneRespawnRecordPtr *) const
{
    LIFT_STUB(0xdf130);
}

// 0xdf1c0
bool __cdecl GeoZone::FindArea(unsigned int, ::box16 &) const
{
    LIFT_STUB(0xdf1c0);
}

// 0xdf240
bool __cdecl GeoZone::setRespawnPoint(void)
{
    LIFT_STUB(0xdf240);
}

// 0xdf400
bool __cdecl GeoZone::setBaseCampPoint(void)
{
    LIFT_STUB(0xdf400);
}

// 0xdf5c0
void __cdecl GeoZone::setIsBroadcastNpcSquadExist(void)
{
    LIFT_STUB(0xdf5c0);
}

// 0xdf680
bool __cdecl GeoZone::IsFactionBattleFieldDungeon(void) const
{
    LIFT_STUB(0xdf680);
}

// 0xdf6d0
bool __cdecl GeoZone::IsTeamPartyZone(void) const
{
    LIFT_STUB(0xdf6d0);
}

// 0x105e20 RecordIndexMapContainer<Data::ZonePcSpawnRecordPtr>::RecordIndexMapContainer<Data::ZonePcSpawnRecordPtr>: LIFT: no body in wave 0 (member of a class template).

// 0x105fc0 RecordIndexMapContainer<Data::ZoneNpcRandomSpawnRecordPtr>::~RecordIndexMapContainer<Data::ZoneNpcRandomSpawnRecordPtr>: LIFT: no body in wave 0 (member of a class template).

// 0x1060a0 RecordIndexMapContainer<Data::ZoneNpcSquadRecordPtr>::RecordIndexMapContainer<Data::ZoneNpcSquadRecordPtr>: LIFT: no body in wave 0 (member of a class template).

// 0x106240 RecordIndexMapContainer<Data::ZoneConvoyRecordPtr>::RecordIndexMapContainer<Data::ZoneConvoyRecordPtr>: LIFT: no body in wave 0 (member of a class template).

// 0x1063e0 RecordIndexMapContainer<Data::ZoneNpcSpawnRecordPtr>::RecordIndexMapContainer<Data::ZoneNpcSpawnRecordPtr>: LIFT: no body in wave 0 (member of a class template).

// 0x106580 RecordIndexMapContainer<Data::ZoneAreaRecordPtr>::RecordIndexMapContainer<Data::ZoneAreaRecordPtr>: LIFT: no body in wave 0 (member of a class template).

// 0x106720 RecordIndexMapContainer<Data::ZoneRespawnRecordPtr>::RecordIndexMapContainer<Data::ZoneRespawnRecordPtr>: LIFT: no body in wave 0 (member of a class template).

// 0x1068c0 RecordIndexMapContainer<Data::ZonePathwayRecordPtr>::RecordIndexMapContainer<Data::ZonePathwayRecordPtr>: LIFT: no body in wave 0 (member of a class template).

// 0x106a60 RecordIndexMapContainer<Data::ZoneGatherSourceRecordPtr>::RecordIndexMapContainer<Data::ZoneGatherSourceRecordPtr>: LIFT: no body in wave 0 (member of a class template).

// 0x106c00 RecordIndexMapContainer<Data::ZoneEnv2SpawnRecordPtr>::RecordIndexMapContainer<Data::ZoneEnv2SpawnRecordPtr>: LIFT: no body in wave 0 (member of a class template).

// 0x106da0 RecordIndexMapContainer<Data::ZoneCampfireRecordPtr>::RecordIndexMapContainer<Data::ZoneCampfireRecordPtr>: LIFT: no body in wave 0 (member of a class template).

// 0x106f40 RecordIndexMapContainer<Data::ZoneEventRecordPtr>::RecordIndexMapContainer<Data::ZoneEventRecordPtr>: LIFT: no body in wave 0 (member of a class template).

// 0x1070d0 RecordIndexMapContainer<Data::ZoneNpcSpawnEventRecordPtr>::RecordIndexMapContainer<Data::ZoneNpcSpawnEventRecordPtr>: LIFT: no body in wave 0 (member of a class template).

// 0x107260 RecordIndexMapContainer<Data::ZoneAreaGroupRecordPtr>::RecordIndexMapContainer<Data::ZoneAreaGroupRecordPtr>: LIFT: no body in wave 0 (member of a class template).

// 0x107400 RecordIndexMapContainer<Data::ZoneNpcRandomSpawnRecordPtr>::RecordIndexMapContainer<Data::ZoneNpcRandomSpawnRecordPtr>: LIFT: no body in wave 0 (member of a class template).

// 0x1075a0 buildRecordIndexByRecordMap<Data::ZoneNpcSquadRecordPtr>: LIFT: no body in wave 0 (function template).

// 0x107780 buildRecordIndexByRecordMap<Data::ZoneGatherSourceRecordPtr>: LIFT: no body in wave 0 (function template).

// 0x107960 buildRecordIndexByRecordMap<Data::ZoneNpcRandomSpawnRecordPtr>: LIFT: no body in wave 0 (function template).

// 0x107b40 buildRecordIndexByRecordMap<Data::ZoneCampfireRecordPtr>: LIFT: no body in wave 0 (function template).

// 0x107d10 buildRecordIndexByRecordMap<Data::ZoneEventRecordPtr>: LIFT: no body in wave 0 (function template).

// 0x107ee0 buildRecordIndexByRecordMap<Data::ZoneNpcSpawnEventRecordPtr>: LIFT: no body in wave 0 (function template).

// 0x1080b0 buildRecordIndexByRecordMap<Data::ZoneAreaGroupRecordPtr>: LIFT: no body in wave 0 (function template).
