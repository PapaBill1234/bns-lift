// duelbottrainingroom.h: duelbottrainingroom.cpp, duelbottrainingroom.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class DuelBotTrainingRoom
{
public:
    virtual wchar_t const * __cdecl GetTypeName(void);  // 0x97770
    virtual bool __cdecl Init(::Zone *, bool);  // 0xaca70
    void __cdecl Start(::Pc *);  // 0xacaf0
    bool __cdecl SpawnDuelBot(::Zone *, int, short);  // 0xacb70
    virtual void __cdecl OnEntered(::Zone *, ::Creature *, ::EnterReason);  // 0xacf70
    virtual void __cdecl OnLeaved(::Zone *, ::Creature *, ::LeaveReason);  // 0xad140
    virtual void __cdecl OnKill(::Zone *, ::GameObject *, ::Creature *);  // 0xad320
    virtual void __cdecl OnZoneAttractionTimer(::Zone *);  // 0xad400
    virtual void __cdecl OnCombatStart(::Zone *, ::Creature *, ::Creature *);  // 0xad5a0
    virtual void __cdecl ReviveByAttractionRule(::Pc *);  // 0xad690
    virtual void __cdecl LeaveAttractionZone(::Pc *);  // 0xad6e0
private:
    ::Pc * __cdecl getPlayer(::Zone *);  // 0xad7b0
    void __cdecl initPlayerState(::Pc *);  // 0xad810
    void __cdecl finish(::Zone *, ::DuelBotTrainingRoomEvent);  // 0xadbf0
    bool __cdecl spawnDuelBot(::Zone *, unsigned __int64, long);  // 0xae060
};

class DuelBotTrainingRoomGameLog
{
public:
    static void __cdecl WriteDuelBotTrainingRoomStart(::Pc *, char, __int64, ::dr_vector16);  // 0xae210
    static void __cdecl WriteDuelBotTrainingRoomEnd(::Pc *, ::GameLogDuelBotTrainingRoomStateCode, char, char, char, __int64, __int64);  // 0xae4b0
};

