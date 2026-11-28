// brainmonstertalkable.h: brainmonstertalkable.cpp, brainmonstertalkable.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the class has no data members declared. The PDB layout is read through BrainMonsterTalkableView.
#pragma once
#include "GameDaemonFwd.h"
#include "brainconst.h"
#include <stddef.h>

class BrainMonsterTalkable
{
protected:
    virtual ::BrainState * __cdecl GetState(::BrainConst::State);  // 0x630e0
    __cdecl BrainMonsterTalkable(::Npc &);  // 0x631e0
    virtual __cdecl ~BrainMonsterTalkable(void);  // 0x633d0
    virtual bool __cdecl Stop(void);  // 0x63470
};

// LIFT: partial view of the PDB class BrainMonsterTalkable (size 0x490). The bodies read it with reinterpret_cast.
// The state members are byte views at their PDB offsets. Only GetState reads them.
struct BrainMonsterTalkableView
{
    char lift_pad_0[0x428];  // PDB fields +0 to +0x427 (vfptr, BrainBase, _actSeq, _combatSeq, _hateList)
    char _spawn[0x8];  // +1064 (0x428) PDB type SpawnState
    char _talk[0x20];  // +1072 (0x430) PDB type TalkState
    char _combat[0x18];  // +1104 (0x450) PDB type CombatSeqState
    char _act[0x10];  // +1128 (0x468) PDB type ActSeqState
    char _return[0x18];  // +1144 (0x478) PDB type ReturnState
};
static_assert(offsetof(BrainMonsterTalkableView, _spawn) == 0x428, "BrainMonsterTalkable::_spawn");
static_assert(offsetof(BrainMonsterTalkableView, _talk) == 0x430, "BrainMonsterTalkable::_talk");
static_assert(offsetof(BrainMonsterTalkableView, _combat) == 0x450, "BrainMonsterTalkable::_combat");
static_assert(offsetof(BrainMonsterTalkableView, _act) == 0x468, "BrainMonsterTalkable::_act");
static_assert(offsetof(BrainMonsterTalkableView, _return) == 0x478, "BrainMonsterTalkable::_return");
