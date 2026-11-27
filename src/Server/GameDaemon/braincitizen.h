// braincitizen.h: braincitizen.cpp, braincitizen.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"
#include "brainconst.h"

class BrainCitizen
{
protected:
    virtual ::BrainState * __cdecl GetState(::BrainConst::State);  // 0x402a80
    __cdecl BrainCitizen(::Npc &);  // 0x402ab0
    virtual __cdecl ~BrainCitizen(void);  // 0x402ba0
    virtual bool __cdecl Stop(void);  // 0x402c30
};

