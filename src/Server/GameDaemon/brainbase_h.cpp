// brainbase_h.cpp: brainbase.h (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "brainbase.h"
#include "LiftStub.h"

// 0x34f040
#pragma comment(linker, "/INCLUDE:?IsPeace@BrainBase@@QEBA_NXZ")  // LIFT: dead-strip keep (no live caller yet)
bool __cdecl BrainBase::IsPeace(void) const
{
    ::BrainBaseMemberView const *self = reinterpret_cast< ::BrainBaseMemberView const *>(this);
    // LIFT: inline state read of the brain stack (an invalid _top gives STATE_INVALID).
    ::BrainConst::State state = ::BrainConst::STATE_INVALID;
    if (self->_top >= 0 && self->_top < 16)
        state = self->_stack[self->_top];
    if (state == ::BrainConst::STATE_COMBAT_SEQ || state == ::BrainConst::STATE_RETURN)
        return false;
    return true;
}
