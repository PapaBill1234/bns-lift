// braincitizen_h.cpp: braincitizen.h (GameDaemon PDB, 2019 + PDB).
#include "braincitizen.h"
#include "brainconst.h"
#include "LiftStub.h"

#pragma comment(linker, "/INCLUDE:?GetState@BrainCitizen@@MEAAPEAVBrainState@@W4State@BrainConst@@@Z")  // LIFT: dead-strip keep (no live caller yet)

namespace
{
// LIFT: view of the PDB class BrainCitizen. The skeleton class has no members yet.
struct BrainCitizenView
{
    char lift_pad_0[0x110];
    char _spawn[0x118 - 0x110];  // +272 (0x110) SpawnState
    char _talk[0x138 - 0x118];   // +280 (0x118) TalkState
    char _act[8];                // +312 (0x138) ActSeqState
};
}

// 0x402a80
::BrainState * __cdecl BrainCitizen::GetState(::BrainConst::State state)
{
    BrainCitizenView *self = reinterpret_cast<BrainCitizenView *>(this);
    switch (state)
    {
    case ::BrainConst::STATE_SPAWN:
        return reinterpret_cast<::BrainState *>(&self->_spawn);
    case ::BrainConst::STATE_ACT_SEQ:
        return reinterpret_cast<::BrainState *>(&self->_act);
    case ::BrainConst::STATE_TALK:
        return reinterpret_cast<::BrainState *>(&self->_talk);
    default:
        return nullptr;
    }
}
