// zoneevent.h: zoneevent.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class InOutDetector
{
public:
    __cdecl InOutDetector(void);  // 0x25cef0
    __cdecl ~InOutDetector(void);  // 0x25cf60
private:
    void __cdecl stop(::Zone *, ::Data::ScriptStopDetectReasonType);  // 0x25cfd0
    void __cdecl clear(void);  // 0x25d210
public:
    bool __cdecl Start(::Zone *, unsigned __int64, ::Data::ScriptDetectRefTypeType, unsigned __int64, unsigned __int64, short, long, short, unsigned __int64, unsigned __int64, unsigned __int64, unsigned __int64);  // 0x25d290
    bool __cdecl Detect(::Zone *);  // 0x25da80
private:
    bool __cdecl checkCreature(::Creature *, __int64 &);  // 0x25dc60
    bool __cdecl gather(::Zone *, ::Pointer2< ::Creature>);  // 0x25dd40
    void __cdecl invokeEventIn(::Zone *, ::Pointer2< ::Creature>, ::Creature *);  // 0x25e3c0
    void __cdecl invokeEventOut(::Zone *, ::Pointer2< ::Creature>, ::Creature *);  // 0x25e600
};

class ZoneCreatureDetector
{
public:
    __cdecl ZoneCreatureDetector(::Zone *);  // 0x25e840
    bool __cdecl OnDetect(void);  // 0x25e920
    bool __cdecl Start(char, unsigned __int64, ::Data::ScriptDetectRefTypeType, unsigned __int64, unsigned __int64, short, long, short, unsigned __int64, unsigned __int64, unsigned __int64, unsigned __int64);  // 0x25ea20
    bool __cdecl Stop(char);  // 0x25ec30
};

class ZoneEvent
{
public:
    bool __cdecl ProcessFactionKillEvent(void);  // 0x25cab0
    bool __cdecl ProcessKillNpcEvent(unsigned __int64);  // 0x25cc70
private:
    bool __cdecl setEventStep(char);  // 0x25ce70
};

