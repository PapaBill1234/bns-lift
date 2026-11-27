// script.h: script.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class ScriptPlayer
{
public:
    static bool __cdecl Play(::Data::ObjectScript const *, ::ScriptEvent const *, ::dr_tref const *);  // 0x463f90
    static bool __cdecl CheckFilterSet(::Data::FilterRecord **const, int, ::ScriptEvent const *);  // 0x464090
private:
    static bool __cdecl doReactionSet(::Data::ReactionSet const *, ::ScriptEvent const *);  // 0x4641b0
    static bool __cdecl processDecisionContents(::Data::DecisionContents *, ::ScriptEvent const *, bool);  // 0x464300
public:
    static bool __cdecl GetParam(::ScriptParam &, ::DrScriptObj const &, ::ScriptEvent const *, char);  // 0x464400
    static bool __cdecl GetParam(::ScriptParam *const, ::DrScriptObj const *const, int, ::ScriptEvent const *);  // 0x4646e0
private:
    static bool __cdecl getPcPartySub(int, ::ScriptParam &, ::ScriptEvent const *);  // 0x464a20
    static bool __cdecl getPcTeamSub(int, ::ScriptParam &, ::ScriptEvent const *);  // 0x464b70
    static bool __cdecl getZoneRegSub(int, ::ScriptParam &, ::ScriptEvent const *);  // 0x464cc0
    static bool __cdecl getNpcPartySub(int, ::ScriptParam &, ::ScriptEvent const *);  // 0x464ee0
    static bool __cdecl getObjectSub(int, ::ScriptParam &, ::ScriptEvent const *);  // 0x465130
    static bool __cdecl getObjectIdSub(int, ::ScriptParam &, ::ScriptEvent const *);  // 0x465700
};

