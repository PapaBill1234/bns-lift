// script.cpp: script.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "script.h"
#include "scripttable.h"
#include "LiftStub.h"

// 0x463f90
bool __cdecl ScriptPlayer::Play(::Data::ObjectScript const *, ::ScriptEvent const *, ::dr_tref const *)
{
    LIFT_STUB(0x463f90);
}

// 0x464090
bool __cdecl ScriptPlayer::CheckFilterSet(::Data::FilterRecord **const, int, ::ScriptEvent const *)
{
    LIFT_STUB(0x464090);
}

// 0x4641b0
bool __cdecl ScriptPlayer::doReactionSet(::Data::ReactionSet const *, ::ScriptEvent const *)
{
    LIFT_STUB(0x4641b0);
}

// 0x464300
bool __cdecl ScriptPlayer::processDecisionContents(::Data::DecisionContents *, ::ScriptEvent const *, bool)
{
    LIFT_STUB(0x464300);
}

// 0x464400
bool __cdecl ScriptPlayer::GetParam(::ScriptParam &, ::DrScriptObj const &, ::ScriptEvent const *, char)
{
    LIFT_STUB(0x464400);
}

// 0x4646e0
bool __cdecl ScriptPlayer::GetParam(::ScriptParam *const, ::DrScriptObj const *const, int, ::ScriptEvent const *)
{
    LIFT_STUB(0x4646e0);
}

// 0x464a20
bool __cdecl ScriptPlayer::getPcPartySub(int, ::ScriptParam &, ::ScriptEvent const *)
{
    LIFT_STUB(0x464a20);
}

// 0x464b70
bool __cdecl ScriptPlayer::getPcTeamSub(int, ::ScriptParam &, ::ScriptEvent const *)
{
    LIFT_STUB(0x464b70);
}

// 0x464cc0
bool __cdecl ScriptPlayer::getZoneRegSub(int, ::ScriptParam &, ::ScriptEvent const *)
{
    LIFT_STUB(0x464cc0);
}

// 0x464ee0
bool __cdecl ScriptPlayer::getNpcPartySub(int, ::ScriptParam &, ::ScriptEvent const *)
{
    LIFT_STUB(0x464ee0);
}

// 0x465130
bool __cdecl ScriptPlayer::getObjectSub(int, ::ScriptParam &, ::ScriptEvent const *)
{
    LIFT_STUB(0x465130);
}

// 0x465700
bool __cdecl ScriptPlayer::getObjectIdSub(int, ::ScriptParam &, ::ScriptEvent const *)
{
    LIFT_STUB(0x465700);
}
