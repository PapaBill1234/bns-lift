// zonenpcspawnevent.h: zonenpcspawnevent.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class ZoneNpcSpawnEvent
{
public:
    enum SpawnEvent {};
protected:
    void __cdecl spawnNpc(::Zone *, unsigned __int64);  // 0x25ecf0
};

class ZoneNpcSpawnEventManager
{
public:
    bool __cdecl Init(::Zone *);  // 0x25f3c0
private:
    ::ZoneNpcSpawnEvent * __cdecl createEvent(::Data::ZoneNpcSpawnEventRecordPtr const &);  // 0x25f4a0
    void __cdecl clear(void);  // 0x25f680
};

class ZoneNpcSpawnNpcKilledEvent1
{
public:
    virtual void __cdecl HandleNpcSpawnEvent(::Zone *, unsigned __int64);  // 0x25f050
};

class ZoneNpcSpawnNpcKilledEvent2
{
public:
    virtual void __cdecl HandleNpcSpawnEvent(::Zone *, unsigned __int64);  // 0x25f110
    virtual void __cdecl ResetContext(::Zone *);  // 0x25f250
};

class ZoneNpcSpawnNpcKilledEvent3
{
public:
    virtual void __cdecl HandleNpcSpawnEvent(::Zone *, unsigned __int64);  // 0x25f2a0
    virtual void __cdecl ResetContext(::Zone *);  // 0x25f390
};

class ZoneNpcSpawnWeeklyEvent
{
public:
    virtual void __cdecl HandleNpcSpawnEvent(::Zone *, unsigned __int64);  // 0x25ed80
};

