// brainstate_h.cpp: brainstate.h (GameDaemon PDB, 2019 + PDB).
#include "brainstate.h"
#include "LiftStub.h"

#pragma comment(linker, "/INCLUDE:??1ActSeqState@@UEAA@XZ")  // LIFT: dead-strip keep (no live caller yet)

// 0x633b0
// The body only resets the vftable to BrainState (base dtor inlined). The
// binary folds it with SpawnState::~SpawnState.
__cdecl ActSeqState::~ActSeqState(void)
{
}
