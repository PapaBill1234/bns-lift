// jackpotbossmanager.h: jackpotbossmanager.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class JackpotBossManager
{
public:
    bool __cdecl Initialize(::Zone *, __int64);  // 0x137410
    void __cdecl OnBossSpawned(::Npc *);  // 0x1374e0
    void __cdecl AcquireFactionScoreForDebug(char, int);  // 0x1375a0
    void __cdecl TransferFactionScore(unsigned __int64, char, int &);  // 0x137680
private:
    void __cdecl despawnBossNpc(unsigned __int64, bool, bool);  // 0x137820
    void __cdecl spawnBossNpc(unsigned __int64, long);  // 0x1378c0
    void __cdecl onChangedFactionScore(void);  // 0x1379a0
};

