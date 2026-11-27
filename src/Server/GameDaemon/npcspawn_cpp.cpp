// npcspawn_cpp.cpp: npcspawn.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "npcspawn.h"
#include "npc.h"
#include "npctask.h"
#include "LiftStub.h"

#pragma comment(linker, "/INCLUDE:?GetNpc@NpcSpawn@@QEAAPEAVNpc@@_K@Z")  // LIFT: dead-strip keep (no live caller yet)
// LIFT: GetNpc inlines getNpcPos, so the out-of-line body has no live caller.
#pragma comment(linker, "/INCLUDE:?getNpcPos@NpcSpawn@@AEAAH_K@Z")  // LIFT: dead-strip keep (no live caller yet)

namespace
{
// LIFT: views of PDB classes that have no layout in the skeleton yet. Offsets are from the PDB.

// LIFT: view of Data::ZoneRecord (key at +0x8).
struct ZoneRecordKeyView
{
    char lift_pad_0[0x8];
    int key;  // +8 (0x8). LIFT: PDB type Data::ZoneRecord::Key (id)
};

// LIFT: view of GeoZone::IndexInfo.
struct GeoZoneIndexInfoView
{
    int *indexes;    // +0 (0x0)
    int indexCount;  // +8 (0x8)
    int count;       // +12 (0xC)
};

// LIFT: view of GeoZone (zoneData._record at +0, _npcSpawnIndexInfo at +0x70).
struct GeoZoneSpawnView
{
    ZoneRecordKeyView const *zoneData_record;  // +0 (0x0). LIFT: GeoZone::zoneData._record
    char lift_pad_0[0x70 - 0x8];
    GeoZoneIndexInfoView _npcSpawnIndexInfo;   // +112 (0x70)
};

// LIFT: view of Zone (GeoZoneData at +0x3F60).
struct ZoneSpawnView
{
    char lift_pad_0[0x3F60];
    GeoZoneSpawnView const *GeoZoneData;  // +16224 (0x3F60)
};

// LIFT: view of NpcSpawn (PDB size 0x80).
struct NpcSpawnView
{
    ZoneSpawnView *_zone;  // +0 (0x0)
    void const *_records;  // +8 (0x8). LIFT: PDB type Data::ZoneNpcSpawnRecordPtr const *
    ::Npc **_npc;          // +16 (0x10)
};
}  // namespace

// 0x428dd0
__cdecl NpcSpawn::~NpcSpawn(void)
{
    LIFT_STUB(0x428dd0);
}

// 0x429080
bool __cdecl NpcSpawn::Initialize(void)
{
    LIFT_STUB(0x429080);
}

// 0x429730
::Npc * __cdecl NpcSpawn::GetNpc(unsigned __int64 npcSpawnKey)
{
    int pos = getNpcPos(npcSpawnKey);
    if (pos < 0)
        return nullptr;
    return reinterpret_cast<NpcSpawnView *>(this)->_npc[pos];
}

// 0x429780
int __cdecl NpcSpawn::getNpcPos(unsigned __int64 npcSpawnKey)
{
    NpcSpawnView const *self = reinterpret_cast<NpcSpawnView const *>(this);
    if (npcSpawnKey == 0)
        return -1;
    GeoZoneSpawnView const *geoZone = self->_zone->GeoZoneData;
    if (self->_npc == nullptr)
        return -1;
    // LIFT: the low 32 bits of the key are the zone id, the next 16 bits are the spawn index.
    if (geoZone->zoneData_record->key != static_cast<int>(npcSpawnKey))
        return -1;
    short index = static_cast<short>(npcSpawnKey >> 32);
    if (index == 0)
        return -1;
    if (geoZone->_npcSpawnIndexInfo.indexCount <= index)
        return -1;
    return geoZone->_npcSpawnIndexInfo.indexes[index];
}

// 0x4297c0
::NpcSpawn::SpawnResult __cdecl NpcSpawn::Spawn(unsigned __int64, ::NpcSpawnParam const *)
{
    LIFT_STUB(0x4297c0);
}

// 0x429b80
::NpcSpawn::SpawnResult __cdecl NpcSpawn::Spawn(unsigned __int64, ::vector16, short, ::NpcSpawnParam const *)
{
    LIFT_STUB(0x429b80);
}

// 0x429f60
::NpcSpawn::SpawnResult __cdecl NpcSpawn::Spawn(::Data::ZoneNpcSpawnRecordPtr const &, ::NpcSpawnParam const *)
{
    LIFT_STUB(0x429f60);
}

// 0x42a360
::NpcSpawn::SpawnResult __cdecl NpcSpawn::RandomSpawn(int, ::NpcSpawnParam const *)
{
    LIFT_STUB(0x42a360);
}

// 0x42a6e0
bool __cdecl NpcSpawn::SpawnDebugNpc(unsigned __int64, ::vector16, short, ::NpcSpawnParam const *)
{
    LIFT_STUB(0x42a6e0);
}

// 0x42ab80
void __cdecl NpcSpawn::SpawnAll(bool, long, ::ExceptSpawnIdRange *)
{
    LIFT_STUB(0x42ab80);
}

// 0x42b290
void __cdecl NpcSpawn::Despawn(::Npc *, bool, bool)
{
    LIFT_STUB(0x42b290);
}

// 0x42b830
void __cdecl NpcSpawn::Despawn(unsigned __int64, bool, bool)
{
    LIFT_STUB(0x42b830);
}

// 0x42b9f0
void __cdecl NpcSpawn::DespawnRandomSpawnNpc(int, bool, bool)
{
    LIFT_STUB(0x42b9f0);
}

// 0x42bb50
void __cdecl NpcSpawn::DespawnAll(bool, bool)
{
    LIFT_STUB(0x42bb50);
}

// 0x42bc20
void __cdecl NpcSpawn::Cleanup(void)
{
    LIFT_STUB(0x42bc20);
}

// 0x42beb0
::NpcSpawnTask * __cdecl NpcSpawn::spawn(int, ::Data::NpcRecordPtr, ::Data::ZoneNpcSpawnRecordPtr, ::NpcSpawnParam const &, short, short, short, short, short)
{
    LIFT_STUB(0x42beb0);
}

// 0x42c160
::NpcSpawnTask * __cdecl NpcSpawn::spawn(int, ::Data::NpcRecordPtr, ::Data::ZoneNpcRandomSpawnRecordPtr, ::NpcSpawnParam const &, short, short, short, short, short)
{
    LIFT_STUB(0x42c160);
}

// 0x42c420
::Npc * __cdecl NpcSpawn::CreateNpc(unsigned __int64, ::NpcSpawnTask *, int, ::NpcSpawnParam const &)
{
    LIFT_STUB(0x42c420);
}

// 0x42ca20
void __cdecl NpcSpawn::CancelSpawn(::NpcSpawnTask *, int)
{
    LIFT_STUB(0x42ca20);
}

// 0x42cba0
void __cdecl NpcSpawn::forceDespawn(::Npc *, bool)
{
    LIFT_STUB(0x42cba0);
}

// 0x42cf10
bool __cdecl NpcSpawn::resizeDebugNpc(int)
{
    LIFT_STUB(0x42cf10);
}
