// actsequence.h: actsequence.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class ActSequence
{
public:
    bool __cdecl Set(::Npc &, unsigned __int64);  // 0x3fbe20
    ::Action * __cdecl GetNextAction(::Npc &);  // 0x3fbf80
protected:
    ::Action * __cdecl getNextMovearound(::Npc &, ::ActActionSeq const &, unsigned __int64, char, char);  // 0x3fc190
    ::Action * __cdecl getNextPathway(::Npc &, ::ActActionSeq const &, unsigned __int64);  // 0x3fc280
    bool __cdecl canRandomSocial(::Npc &, ::ActRandomSocial const &);  // 0x3fc410
    ::Action * __cdecl createPauseAction(::Npc &, ::ActActionSeq const *);  // 0x3fc4d0
    ::Action * __cdecl createRandomSocialAction(::Npc &, ::ActRandomSocial const &);  // 0x3fc550
    ::ActActionSeq const * __cdecl getLoopNext(::Npc &);  // 0x3fc780
    ::ActActionSeq const * __cdecl pushLoop(::Npc &, ::ActActionSeq const *);  // 0x3fc9b0
    ::ActActionSeq const * __cdecl processSelect(::Npc &, ::ActActionSeq const *);  // 0x3fca30
    void __cdecl changeDetect(::Npc &, ::ActActionSeq const &) const;  // 0x3fcae0
    ::Action * __cdecl createAction(::Npc &, ::ActActionSeq const *);  // 0x3fcbd0
    ::Action * __cdecl createSocialAction(::Npc &, unsigned __int64, ::DrScriptObj);  // 0x3fd0b0
    ::Action * __cdecl createStayAction(::Npc &, long, ::DrScriptObj);  // 0x3fd290
    ::Action * __cdecl createMovearoundAction(::Npc &, unsigned __int64);  // 0x3fd480
    ::Action * __cdecl createMovearoundAction(::Npc &, unsigned __int64, char, char);  // 0x3fd910
    bool __cdecl advancePathway(::Npc &, unsigned __int64, bool &, short &, bool);  // 0x3fd980
    ::Action * __cdecl createPathwayAction(::Npc &, unsigned __int64);  // 0x3fdac0
public:
    ::Action * __cdecl RestoreState(::Npc &);  // 0x3fdc80
};

