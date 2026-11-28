// brainmonstertalkable_h.cpp: brainmonstertalkable.h (GameDaemon PDB, 2019 + PDB).
#include "brainmonstertalkable.h"
#include "brainconst.h"
#include "LiftStub.h"

// 0x630e0
#pragma comment(linker, "/INCLUDE:?GetState@BrainMonsterTalkable@@MEAAPEAVBrainState@@W4State@BrainConst@@@Z")  // LIFT: dead-strip keep (no live caller yet)
// LIFT: the state members are byte views (see brainmonstertalkable.h). The casts give the member addresses.
::BrainState * __cdecl BrainMonsterTalkable::GetState(::BrainConst::State state)
{
    ::BrainMonsterTalkableView *const self = reinterpret_cast< ::BrainMonsterTalkableView *>(this);
    switch (state)
    {
    case ::BrainConst::STATE_SPAWN:
        return reinterpret_cast< ::BrainState *>(&self->_spawn);
    case ::BrainConst::STATE_ACT_SEQ:
        return reinterpret_cast< ::BrainState *>(&self->_act);
    case ::BrainConst::STATE_TALK:
        return reinterpret_cast< ::BrainState *>(&self->_talk);
    case ::BrainConst::STATE_COMBAT_SEQ:
        return reinterpret_cast< ::BrainState *>(&self->_combat);
    case ::BrainConst::STATE_RETURN:
        return reinterpret_cast< ::BrainState *>(&self->_return);
    default:
        return NULL;
    }
}
