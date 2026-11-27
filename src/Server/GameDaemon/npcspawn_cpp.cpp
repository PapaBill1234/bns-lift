// npcspawn_cpp.cpp: npcspawn.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "npcspawn.h"
#include "npc.h"
#include "npctask.h"
#include "LiftStub.h"

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
::Npc * __cdecl NpcSpawn::GetNpc(unsigned __int64)
{
    LIFT_STUB(0x429730);
}

// 0x429780
int __cdecl NpcSpawn::getNpcPos(unsigned __int64)
{
    LIFT_STUB(0x429780);
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
