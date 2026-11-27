// actsequence.cpp: actsequence.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "actsequence.h"
#include "action.h"
#include "npc.h"
#include "LiftStub.h"

// 0x3fbe20
bool __cdecl ActSequence::Set(::Npc &, unsigned __int64)
{
    LIFT_STUB(0x3fbe20);
}

// 0x3fbf80
::Action * __cdecl ActSequence::GetNextAction(::Npc &)
{
    LIFT_STUB(0x3fbf80);
}

// 0x3fc190
::Action * __cdecl ActSequence::getNextMovearound(::Npc &, ::ActActionSeq const &, unsigned __int64, char, char)
{
    LIFT_STUB(0x3fc190);
}

// 0x3fc280
::Action * __cdecl ActSequence::getNextPathway(::Npc &, ::ActActionSeq const &, unsigned __int64)
{
    LIFT_STUB(0x3fc280);
}

// 0x3fc410
bool __cdecl ActSequence::canRandomSocial(::Npc &, ::ActRandomSocial const &)
{
    LIFT_STUB(0x3fc410);
}

// 0x3fc4d0
::Action * __cdecl ActSequence::createPauseAction(::Npc &, ::ActActionSeq const *)
{
    LIFT_STUB(0x3fc4d0);
}

// 0x3fc550
::Action * __cdecl ActSequence::createRandomSocialAction(::Npc &, ::ActRandomSocial const &)
{
    LIFT_STUB(0x3fc550);
}

// 0x3fc780
::ActActionSeq const * __cdecl ActSequence::getLoopNext(::Npc &)
{
    LIFT_STUB(0x3fc780);
}

// 0x3fc9b0
::ActActionSeq const * __cdecl ActSequence::pushLoop(::Npc &, ::ActActionSeq const *)
{
    LIFT_STUB(0x3fc9b0);
}

// 0x3fca30
::ActActionSeq const * __cdecl ActSequence::processSelect(::Npc &, ::ActActionSeq const *)
{
    LIFT_STUB(0x3fca30);
}

// 0x3fcae0
void __cdecl ActSequence::changeDetect(::Npc &, ::ActActionSeq const &) const
{
    LIFT_STUB(0x3fcae0);
}

// 0x3fcbd0
::Action * __cdecl ActSequence::createAction(::Npc &, ::ActActionSeq const *)
{
    LIFT_STUB(0x3fcbd0);
}

// 0x3fd0b0
::Action * __cdecl ActSequence::createSocialAction(::Npc &, unsigned __int64, ::DrScriptObj)
{
    LIFT_STUB(0x3fd0b0);
}

// 0x3fd290
::Action * __cdecl ActSequence::createStayAction(::Npc &, long, ::DrScriptObj)
{
    LIFT_STUB(0x3fd290);
}

// 0x3fd480
::Action * __cdecl ActSequence::createMovearoundAction(::Npc &, unsigned __int64)
{
    LIFT_STUB(0x3fd480);
}

// 0x3fd910
::Action * __cdecl ActSequence::createMovearoundAction(::Npc &, unsigned __int64, char, char)
{
    LIFT_STUB(0x3fd910);
}

// 0x3fd980
bool __cdecl ActSequence::advancePathway(::Npc &, unsigned __int64, bool &, short &, bool)
{
    LIFT_STUB(0x3fd980);
}

// 0x3fdac0
::Action * __cdecl ActSequence::createPathwayAction(::Npc &, unsigned __int64)
{
    LIFT_STUB(0x3fdac0);
}

// 0x3fdc80
::Action * __cdecl ActSequence::RestoreState(::Npc &)
{
    LIFT_STUB(0x3fdc80);
}
