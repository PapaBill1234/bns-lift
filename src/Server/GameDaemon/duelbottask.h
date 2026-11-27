// duelbottask.h: duelbottask.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class DuelBotSetBrainTask
{
public:
    __cdecl DuelBotSetBrainTask(void);  // 0xac130
    bool __cdecl Initialize(::Zone *, __int64, __int64, short);  // 0xac1a0
private:
    virtual void __cdecl TimerExpired(unsigned int, long);  // 0xac270
};

class DuelBotSpawnTask
{
public:
    __cdecl DuelBotSpawnTask(void);  // 0xab600
    bool __cdecl Initialize(::Zone *, ::Data::DuelBotRecordPtr const &, int, long, short, short, short, short, short, ::EnterReason);  // 0xab690
private:
    virtual void __cdecl TimerExpired(unsigned int, long);  // 0xab810
    bool __cdecl spawn(unsigned __int64);  // 0xab9c0
};

class DuelBotSummonedSpawnTask
{
public:
    __cdecl DuelBotSummonedSpawnTask(void);  // 0xac2f0
    bool __cdecl Initialize(::Zone *, ::DuelBot *, short, short, short, short, short, ::EnterReason, unsigned __int64);  // 0xac370
private:
    virtual void __cdecl start(void);  // 0xac4b0
    bool __cdecl enter(void);  // 0xac4f0
    bool __cdecl spawn(void);  // 0xac8d0
};

