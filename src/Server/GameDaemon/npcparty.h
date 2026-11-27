// npcparty.h: npcparty.cpp, npcparty.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class NpcParty
{
protected:
    virtual __cdecl ~NpcParty(void);  // 0x428bc0
    bool __cdecl initializeTimer(void);  // 0x428c00
public:
    virtual bool __cdecl Add(::Npc *);  // 0x428c70
    virtual bool __cdecl Remove(::Npc *);  // 0x428cd0
    void __cdecl SetVar(int, __int64);  // 0x428d10
};

class NpcPartyTimer
{
public:
    __cdecl NpcPartyTimer(::Zone *, ::NpcParty *);  // 0x34f2c0
private:
    virtual void __cdecl TimerExpired(unsigned int, long);  // 0x34f360
public:
    void __cdecl SetTimer(long);  // 0x428d50
};

