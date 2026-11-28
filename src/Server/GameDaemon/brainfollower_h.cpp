// brainfollower_h.cpp: brainfollower.h (GameDaemon PDB, 2019 + PDB).
#include "brainfollower.h"
#include "brainconst.h"
#include "LiftStub.h"

#pragma comment(linker, "/INCLUDE:?GetLastTargetId@BrainFollower@@MEBA_KXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetState@BrainFollower@@MEAAPEAVBrainState@@W4State@BrainConst@@@Z")  // LIFT: dead-strip keep (no live caller yet)

// Partial PDB offsets of BrainFollower. The state members are subobjects that derive from BrainState at +0.
enum
{
    BrainFollower_spawn = 1064,       // SpawnState _spawn
    BrainFollower_act = 1072,         // ActSeqState _act
    BrainFollower_follow = 1088,      // FollowState _follow
    BrainFollower_combat = 1128,      // CombatSeqState _combat
    BrainFollower_CombatSeqState_lastTargetId = 16  // CombatSeqState::_lastTargetId
};

// 0x402db0
unsigned __int64 __cdecl BrainFollower::GetLastTargetId(void) const
{
    return *reinterpret_cast<const unsigned __int64 *>(reinterpret_cast<const char *>(this) + BrainFollower_combat + BrainFollower_CombatSeqState_lastTargetId);
}

// 0x402dc0
::BrainState * __cdecl BrainFollower::GetState(::BrainConst::State state)
{
    char *base = reinterpret_cast<char *>(this);
    switch (state)
    {
    case BrainConst::STATE_SPAWN:
        return reinterpret_cast< ::BrainState *>(base + BrainFollower_spawn);
    case BrainConst::STATE_ACT_SEQ:
        return reinterpret_cast< ::BrainState *>(base + BrainFollower_act);
    case BrainConst::STATE_FOLLOW:
        return reinterpret_cast< ::BrainState *>(base + BrainFollower_follow);
    case BrainConst::STATE_COMBAT_SEQ:
        return reinterpret_cast< ::BrainState *>(base + BrainFollower_combat);
    default:
        return nullptr;
    }
}
