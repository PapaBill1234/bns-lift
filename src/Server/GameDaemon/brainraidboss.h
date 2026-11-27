// brainraidboss.h: brainraidboss.cpp, brainraidboss.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"
#include "brainconst.h"

class BrainRaidBoss
{
protected:
    virtual unsigned __int64 __cdecl GetLastTargetId(void) const;  // 0x634a0
    virtual ::BrainState * __cdecl GetState(::BrainConst::State);  // 0x634b0
    __cdecl BrainRaidBoss(::Npc &);  // 0x634f0
public:
    virtual void __cdecl InitSpecialState(void);  // 0x63700
    void __cdecl GatherSpecialTargets(char, char, bool, bool, char, bool, char);  // 0x63730
private:
    void __cdecl getNearSpecialTargets(::Creature **const, char, char);  // 0x63ac0
    void __cdecl getFarSpecialTargets(::Creature **const, char, char);  // 0x63c80
    void __cdecl getMinHateSpecialTargets(::Creature **const, char, char);  // 0x63e40
};

