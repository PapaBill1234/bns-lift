// brainboss.h: brainboss.cpp, brainboss.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"
#include "brainconst.h"

class BrainBoss
{
protected:
    virtual unsigned __int64 __cdecl GetLastTargetId(void) const;  // 0x79c60
    virtual ::BrainState * __cdecl GetState(::BrainConst::State);  // 0x79c70
    __cdecl BrainBoss(::Npc &);  // 0x7c740
    virtual bool __cdecl Stop(void);  // 0x7c9e0
public:
    virtual void __cdecl InitSpecialState(void);  // 0x7c9f0
    void __cdecl GatherSpecialTargets(char, char, bool, bool, char, bool, char);  // 0x7ca30
private:
    void __cdecl getNearSpecialTargets(::Creature **const, char, char);  // 0x7cdc0
    void __cdecl getFarSpecialTargets(::Creature **const, char, char);  // 0x7cf80
    void __cdecl getMinHateSpecialTargets(::Creature **const, char, char);  // 0x7d140
    bool __cdecl checkPCHateListEmptied(void);  // 0x7d2e0
    void __cdecl fireEventHateListEmptied(void);  // 0x7d350
public:
    virtual bool __cdecl ResetHateByTargetId(unsigned __int64, wchar_t const *);  // 0x7d4c0
    virtual bool __cdecl ResetHateByIndex(int, wchar_t const *);  // 0x7d530
private:
    bool __cdecl checkSpecialTargetCond(::Creature *, bool, bool, char, bool, char);  // 0x7d570
};

