// npcparty.h: npcparty.cpp, npcparty.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have only part of their members yet. Later waves add the full PDB layouts.
#pragma once
#include "GameDaemonFwd.h"
#include "zoneserializedobject.h"

class NpcParty
{
public:
    // LIFT: PDB slots 0, 1, 4 and 5 are not lifted yet. Pure placeholders keep the PDB slot order.
    virtual void __cdecl EventOccured(::ScriptEvent const *) = 0;  // PDB slot 0
    virtual void __cdecl OnTimer(::Zone *) = 0;  // PDB slot 1
    virtual bool __cdecl Add(::Npc *);  // 0x428c70, PDB slot 2
    virtual bool __cdecl Remove(::Npc *);  // 0x428cd0, PDB slot 3
    virtual void __cdecl AddHate(::Npc *, ::Creature *, char) = 0;  // PDB slot 4
    virtual bool __cdecl CheckLeaderlessParty(::Data::ZoneNpcSpawnRecordPtr const &) = 0;  // PDB slot 5
protected:
    virtual __cdecl ~NpcParty(void);  // 0x428bc0, PDB slot 6
    bool __cdecl initializeTimer(void);  // 0x428c00
public:
    void __cdecl SetVar(int, __int64);  // 0x428d10
protected:  // LIFT: NpcSquad (derived) reads NpcParty::_npc, _maxNpc and _leaderIdx.
    int _type;  // +8 (PDB: NpcParty::Type) LIFT: the enum NpcParty::Type is not declared yet
    ::Zone *_zone;  // +16
    ::NpcPartyTimer *_timer;  // +24
    unsigned __int64 const *_spawnKey;  // +32
    ::Npc **_npc;  // +40
    int _maxNpc;  // +48
    int _leaderIdx;  // +52
    __int64 _var[4];  // +56
};

class NpcPartyTimer : public ::ZoneSerializedObject
{
public:
    __cdecl NpcPartyTimer(::Zone *, ::NpcParty *);  // 0x34f2c0
private:
    virtual void __cdecl TimerExpired(unsigned int, long);  // 0x34f360
public:
    void __cdecl SetTimer(long);  // 0x428d50
private:
    ::NpcParty *_handler;  // +128
};
