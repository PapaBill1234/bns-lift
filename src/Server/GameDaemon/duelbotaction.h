// duelbotaction.h: duelbotaction.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class DuelBotMoveAction
{
public:
    __cdecl DuelBotMoveAction(void);  // 0xa2970
    bool __cdecl Initialize(::Zone *, unsigned __int64, short, short, char, short, short);  // 0xa29b0
    virtual bool __cdecl IsAvailableAction(void);  // 0xa2aa0
private:
    virtual void __cdecl startAction(void);  // 0xa2ad0
    virtual void __cdecl intervalAction(long);  // 0xa2c40
    virtual void __cdecl finishAction(void);  // 0xa2e60
    bool __cdecl move(::vector16 const &, long);  // 0xa2ea0
    long __cdecl getTimerDuration(void) const;  // 0xa3070
};

class DuelBotSummonedMoveAction
{
public:
    bool __cdecl Initialize(::Zone *, unsigned __int64, short, short, short);  // 0xa3150
private:
    virtual void __cdecl startAction(void);  // 0xa31d0
    virtual void __cdecl intervalAction(long);  // 0xa32f0
    bool __cdecl move(::vector16 const &, long);  // 0xa3510
    long __cdecl getTimerDuration(void) const;  // 0xa36e0
};

