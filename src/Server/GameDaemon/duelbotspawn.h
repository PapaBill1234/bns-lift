// duelbotspawn.h: duelbotspawn.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class DuelBotSpawn
{
public:
    bool __cdecl Init(void);  // 0xaa700
    bool __cdecl Spawn(unsigned __int64, ::vector16 &, long);  // 0xaa790
    void __cdecl Despawn(::DuelBot *, bool, bool);  // 0xaab60
    void __cdecl Despawn(char, bool, bool);  // 0xaad70
    void __cdecl DespawnAll(bool);  // 0xaae70
    void __cdecl Cleanup(void);  // 0xab050
    ::DuelBot * __cdecl CreateDuelBot(unsigned __int64, ::DuelBotSpawnTask *, int);  // 0xab0e0
    void __cdecl CancelSpawn(::DuelBotSpawnTask *, int);  // 0xab3e0
private:
    void __cdecl forceDespawn(::DuelBot *, bool);  // 0xab460
private:
    ::Zone *_zone;  // +0
    ::DuelBot **_duelBot;  // +8
    ::DuelBotSpawnTask **_spawnTask;  // +16
    int _maxDuelBot;  // +24
    char _targetJob;  // +28
};

