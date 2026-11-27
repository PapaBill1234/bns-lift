// brainmonstertalkable_cpp.cpp: brainmonstertalkable.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "brainmonstertalkable.h"
#include "brainbase.h"
#include "npc.h"
#include "LiftStub.h"

// 0x63120
static BrainBase::TransitionTable InitializeMonsterTalkableTransitionTable(void)
{
    LIFT_STUB(0x63120);
}

// 0x631e0
__cdecl BrainMonsterTalkable::BrainMonsterTalkable(::Npc &)
{
    LIFT_STUB(0x631e0);
}

// 0x633d0
__cdecl BrainMonsterTalkable::~BrainMonsterTalkable(void)
{
    LIFT_STUB(0x633d0);
}

// 0x63470
bool __cdecl BrainMonsterTalkable::Stop(void)
{
    LIFT_STUB(0x63470);
}
