// npcsquad.h: npcsquad.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class NpcSquad
{
public:
    enum GroupMoveEvent {};
public:
    __cdecl NpcSquad(::Zone *, ::Data::ZoneNpcSquadRecordPtr);  // 0x42d000
private:
    virtual void __cdecl EventOccured(::ScriptEvent const *);  // 0x42d0a0
public:
    virtual bool __cdecl Add(::Npc *);  // 0x42d140
    virtual void __cdecl AddHate(::Npc *, ::Creature *, char);  // 0x42d310
    void __cdecl GroupMoveThink(::NpcSquad::GroupMoveEvent, ::Npc *);  // 0x42d520
    unsigned __int64 __cdecl GetNearMembersTargetId(::Npc &);  // 0x42d7c0
    void __cdecl ResetCombat(void);  // 0x42da10
    virtual bool __cdecl CheckLeaderlessParty(::Data::ZoneNpcSpawnRecordPtr const &);  // 0x42db10
};

