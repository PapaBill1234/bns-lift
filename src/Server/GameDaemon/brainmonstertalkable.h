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
private:
    // LIFT: PDB layout of BrainMonsterTalkable (size 0x490). The base BrainBase and the state classes are not
    // declared yet. The state members are byte views at their PDB offsets. Only GetState reads them.
    char lift_pad_8[0x420];  // ❓ BrainBase (after the vfptr), _actSeq, _combatSeq, _hateList (+0x8 to +0x427)
    char _spawn[0x8];  // +1064 (0x428) PDB type SpawnState
    char _talk[0x20];  // +1072 (0x430) PDB type TalkState
    char _combat[0x18];  // +1104 (0x450) PDB type CombatSeqState
    char _act[0x10];  // +1128 (0x468) PDB type ActSeqState
    char _return[0x18];  // +1144 (0x478) PDB type ReturnState
};
static_assert(sizeof(BrainMonsterTalkable) == 0x490, "BrainMonsterTalkable size");

