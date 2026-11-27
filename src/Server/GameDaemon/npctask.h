// npctask.h: npctask.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class NpcDespawnTask
{
public:
    bool __cdecl Initialize(::Zone *, ::Npc *, bool, bool, unsigned __int64, long);  // 0x4574d0
private:
    virtual void __cdecl TimerExpired(unsigned int, long);  // 0x4575d0
};

class NpcPlaySocialTask
{
public:
    bool __cdecl Initialize(::Zone *, ::Npc *, unsigned int, unsigned __int64, long, bool);  // 0x457a00
private:
    virtual void __cdecl TimerExpired(unsigned int, long);  // 0x457b70
};

class NpcSpawnTask
{
public:
    __cdecl NpcSpawnTask(void);  // 0x456560
    bool __cdecl Initialize(::Zone &, ::Data::NpcRecordPtr, ::Data::ZoneNpcSpawnRecordPtr, int, short, short, short, short, short, ::NpcSpawnParam const &, ::EnterReason);  // 0x4565e0
    bool __cdecl Initialize(::Zone &, ::Data::NpcRecordPtr, ::Data::ZoneNpcRandomSpawnRecordPtr, int, int, short, short, short, short, short, ::NpcSpawnParam const &, ::EnterReason);  // 0x456860
private:
    virtual void __cdecl TimerExpired(unsigned int, long);  // 0x456ae0
    bool __cdecl spawn(unsigned __int64);  // 0x456ea0
};

class ResumeRaidBossDeadTask
{
public:
    bool __cdecl Initialize(::Zone *, ::Npc *, unsigned __int64, __int64);  // 0x4576b0
private:
    virtual void __cdecl TimerExpired(unsigned int, long);  // 0x457790
};

