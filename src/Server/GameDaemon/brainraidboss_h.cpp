// brainraidboss_h.cpp: brainraidboss.h (GameDaemon PDB, 2019 + PDB).
#include "brainraidboss.h"
#include "brainconst.h"
#include "LiftStub.h"

#pragma comment(linker, "/INCLUDE:?GetLastTargetId@BrainRaidBoss@@MEBA_KXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetState@BrainRaidBoss@@MEAAPEAVBrainState@@W4State@BrainConst@@@Z")  // LIFT: dead-strip keep (no live caller yet)

// 0x634a0
unsigned __int64 __cdecl BrainRaidBoss::GetLastTargetId(void) const
{
    // PDB: CombatSeqState::GetLastTargetId (inline).
    return _combat._lastTargetId;
}

// 0x634b0
::BrainState * __cdecl BrainRaidBoss::GetState(::BrainConst::State state)
{
    // LIFT: the state members are views. Each PDB state class has BrainState as its base at +0.
    switch (state)
    {
    case ::BrainConst::STATE_SPAWN:
        return reinterpret_cast< ::BrainState *>(&_spawn);
    case ::BrainConst::STATE_ACT_SEQ:
        return reinterpret_cast< ::BrainState *>(&_act);
    case ::BrainConst::STATE_COMBAT_SEQ:
        return reinterpret_cast< ::BrainState *>(&_combat);
    case ::BrainConst::STATE_RETURN:
        return reinterpret_cast< ::BrainState *>(&_return);
    default:
        return nullptr;
    }
}
