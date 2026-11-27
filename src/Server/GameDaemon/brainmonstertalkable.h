// brainmonstertalkable.h: brainmonstertalkable.cpp, brainmonstertalkable.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"
#include "brainconst.h"

class BrainMonsterTalkable
{
protected:
    virtual ::BrainState * __cdecl GetState(::BrainConst::State);  // 0x630e0
    __cdecl BrainMonsterTalkable(::Npc &);  // 0x631e0
    virtual __cdecl ~BrainMonsterTalkable(void);  // 0x633d0
    virtual bool __cdecl Stop(void);  // 0x63470
};

