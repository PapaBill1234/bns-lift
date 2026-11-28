// brainmonster_h.cpp: brainmonster.h (GameDaemon PDB, 2019 + PDB).
#include "brainmonster.h"
#include "brainconst.h"
#include "LiftStub.h"

#pragma comment(linker, "/INCLUDE:?GetLastTargetId@BrainMonster@@MEBA_KXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetState@BrainMonster@@MEAAPEAVBrainState@@W4State@BrainConst@@@Z")  // LIFT: dead-strip keep (no live caller yet)

// Partial PDB offsets of BrainMonster. The state members are subobjects that derive from BrainState at +0.
enum
{
    BrainMonster_spawn = 1064,        // SpawnState _spawn
    BrainMonster_act = 1072,          // ActSeqState _act
    BrainMonster_combat = 1088,       // CombatSeqState _combat
    BrainMonster_return = 1112,       // ReturnState _return
    BrainMonster_CombatSeqState_lastTargetId = 16  // CombatSeqState::_lastTargetId
};

// 0x402d60
unsigned __int64 __cdecl BrainMonster::GetLastTargetId(void) const
{
    return *reinterpret_cast<const unsigned __int64 *>(reinterpret_cast<const char *>(this) + BrainMonster_combat + BrainMonster_CombatSeqState_lastTargetId);
}

// 0x402d70
::BrainState * __cdecl BrainMonster::GetState(::BrainConst::State state)
{
    char *base = reinterpret_cast<char *>(this);
    switch (state)
    {
    case BrainConst::STATE_SPAWN:
        return reinterpret_cast< ::BrainState *>(base + BrainMonster_spawn);
    case BrainConst::STATE_ACT_SEQ:
        return reinterpret_cast< ::BrainState *>(base + BrainMonster_act);
    case BrainConst::STATE_COMBAT_SEQ:
        return reinterpret_cast< ::BrainState *>(base + BrainMonster_combat);
    case BrainConst::STATE_RETURN:
        return reinterpret_cast< ::BrainState *>(base + BrainMonster_return);
    default:
        return nullptr;
    }
}
