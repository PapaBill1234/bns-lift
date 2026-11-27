// brainfollower.h: brainfollower.cpp, brainfollower.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"
#include "brainconst.h"

class BrainFollower
{
protected:
    virtual unsigned __int64 __cdecl GetLastTargetId(void) const;  // 0x402db0
    virtual ::BrainState * __cdecl GetState(::BrainConst::State);  // 0x402dc0
    __cdecl BrainFollower(::Npc &);  // 0x403010
    virtual bool __cdecl Stop(void);  // 0x403220
};

