// npcspawn.h: npcspawn.cpp, npcspawn.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class NpcSpawn
{
public:
    enum SpawnResult {};
public:
    ::Data::ZoneAreaRecord::Key __cdecl PickAreaIdForNpcRandomSpawn(int);  // 0x34f0f0
    __cdecl ~NpcSpawn(void);  // 0x428dd0
    bool __cdecl Initialize(void);  // 0x429080
    ::Npc * __cdecl GetNpc(unsigned __int64);  // 0x429730
private:
    int __cdecl getNpcPos(unsigned __int64);  // 0x429780
public:
    ::NpcSpawn::SpawnResult __cdecl Spawn(unsigned __int64, ::NpcSpawnParam const *);  // 0x4297c0
    ::NpcSpawn::SpawnResult __cdecl Spawn(unsigned __int64, ::vector16, short, ::NpcSpawnParam const *);  // 0x429b80
    ::NpcSpawn::SpawnResult __cdecl Spawn(::Data::ZoneNpcSpawnRecordPtr const &, ::NpcSpawnParam const *);  // 0x429f60
    ::NpcSpawn::SpawnResult __cdecl RandomSpawn(int, ::NpcSpawnParam const *);  // 0x42a360
    bool __cdecl SpawnDebugNpc(unsigned __int64, ::vector16, short, ::NpcSpawnParam const *);  // 0x42a6e0
    void __cdecl SpawnAll(bool, long, ::ExceptSpawnIdRange *);  // 0x42ab80
    void __cdecl Despawn(::Npc *, bool, bool);  // 0x42b290
    void __cdecl Despawn(unsigned __int64, bool, bool);  // 0x42b830
    void __cdecl DespawnRandomSpawnNpc(int, bool, bool);  // 0x42b9f0
    void __cdecl DespawnAll(bool, bool);  // 0x42bb50
    void __cdecl Cleanup(void);  // 0x42bc20
private:
    ::NpcSpawnTask * __cdecl spawn(int, ::Data::NpcRecordPtr, ::Data::ZoneNpcSpawnRecordPtr, ::NpcSpawnParam const &, short, short, short, short, short);  // 0x42beb0
    ::NpcSpawnTask * __cdecl spawn(int, ::Data::NpcRecordPtr, ::Data::ZoneNpcRandomSpawnRecordPtr, ::NpcSpawnParam const &, short, short, short, short, short);  // 0x42c160
public:
    ::Npc * __cdecl CreateNpc(unsigned __int64, ::NpcSpawnTask *, int, ::NpcSpawnParam const &);  // 0x42c420
    void __cdecl CancelSpawn(::NpcSpawnTask *, int);  // 0x42ca20
private:
    void __cdecl forceDespawn(::Npc *, bool);  // 0x42cba0
    bool __cdecl resizeDebugNpc(int);  // 0x42cf10
};

class NpcSpawnInfo
{
public:
    wchar_t const * __cdecl GetAlias(void);  // 0x1edf00
    int __cdecl GetActDetect(int);  // 0x34f070
    unsigned __int64 __cdecl GetActSocial(int);  // 0x34f0b0
};

