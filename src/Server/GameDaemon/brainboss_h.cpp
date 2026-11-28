// brainboss_h.cpp: brainboss.h (GameDaemon PDB, 2019 + PDB).
#include "brainboss.h"
#include "brainconst.h"
#include "LiftStub.h"

#pragma comment(linker, "/INCLUDE:?GetLastTargetId@BrainBoss@@MEBA_KXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetState@BrainBoss@@MEAAPEAVBrainState@@W4State@BrainConst@@@Z")  // LIFT: dead-strip keep (no live caller yet)

// Partial PDB offsets of BrainBoss. The state members are subobjects that derive from BrainState at +0.
enum
{
    BrainBoss_spawn = 1168,           // SpawnState _spawn
    BrainBoss_act = 1176,             // ActSeqState _act
    BrainBoss_combat = 1192,          // CombatSeqState _combat
    BrainBoss_return = 1216,          // ReturnState _return
    CombatSeqState_lastTargetId = 16  // CombatSeqState::_lastTargetId
};

// 0x79c60
unsigned __int64 __cdecl BrainBoss::GetLastTargetId(void) const
{
    return *reinterpret_cast<const unsigned __int64 *>(reinterpret_cast<const char *>(this) + BrainBoss_combat + CombatSeqState_lastTargetId);
}

// 0x79c70
::BrainState * __cdecl BrainBoss::GetState(::BrainConst::State state)
{
    char *base = reinterpret_cast<char *>(this);
    switch (state)
    {
    case BrainConst::STATE_SPAWN:
        return reinterpret_cast< ::BrainState *>(base + BrainBoss_spawn);
    case BrainConst::STATE_ACT_SEQ:
        return reinterpret_cast< ::BrainState *>(base + BrainBoss_act);
    case BrainConst::STATE_COMBAT_SEQ:
        return reinterpret_cast< ::BrainState *>(base + BrainBoss_combat);
    case BrainConst::STATE_RETURN:
        return reinterpret_cast< ::BrainState *>(base + BrainBoss_return);
    default:
        return nullptr;
    }
}
