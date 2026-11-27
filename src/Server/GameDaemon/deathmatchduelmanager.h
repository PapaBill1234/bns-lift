// deathmatchduelmanager.h: deathmatchduelmanager.cpp, deathmatchduelmanager.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class DeathMatchDuelManager
{
private:
    virtual bool __cdecl verifyDuelType(void) const;  // 0x4c180
    virtual ::DuelRule *const __cdecl instantiateDuelRule(void);  // 0x4c190
    virtual ::DuelTeam *const __cdecl instantiateDuelTeam(int);  // 0x4c1e0
    virtual void __cdecl readyByForce(void);  // 0x9afc0
};

class DeathMatchDuleRule
{
public:
    virtual ::DuelRoundResult const __cdecl CalcRoundResult(::Zone *const);  // 0x9ad00
};

