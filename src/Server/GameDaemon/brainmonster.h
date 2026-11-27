// brainmonster.h: brainmonster.cpp, brainmonster.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"
#include "brainconst.h"

class BrainMonster
{
protected:
    virtual unsigned __int64 __cdecl GetLastTargetId(void) const;  // 0x402d60
    virtual ::BrainState * __cdecl GetState(::BrainConst::State);  // 0x402d70
    __cdecl BrainMonster(::Npc &);  // 0x4032c0
    virtual bool __cdecl Stop(void);  // 0x4034b0
};

