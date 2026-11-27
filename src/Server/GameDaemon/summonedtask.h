// summonedtask.h: summonedtask.cpp, summonedtask.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"
#include "inventory.h"

class ChangeSummonedNameTask
{
public:
    bool __cdecl Initialize(::Zone *const, ::Pc *const, wchar_t const *const, int, ::Inventory::DisposeOrderWithPos const *const);  // 0x1c2240
private:
    virtual void __cdecl start(void);  // 0x1c2620
public:
    __cdecl ChangeSummonedNameTask(void);  // 0x36dde0
};

class ChangeSummonedTask
{
public:
    bool __cdecl Initialize(::Zone *const, ::Pc *const, unsigned __int64, char const *const, int);  // 0x1c0fd0
private:
    virtual void __cdecl start(void);  // 0x1c1150
public:
    __cdecl ChangeSummonedTask(void);  // 0x36dd60
};

class SummonedSpawnTask
{
public:
    __cdecl SummonedSpawnTask(void);  // 0x1c0290
    bool __cdecl Initialize(::Zone *, ::Pc *, short, short, short, short, short, ::EnterReason, unsigned __int64);  // 0x1c0310
private:
    virtual void __cdecl start(void);  // 0x1c0450
    bool __cdecl enter(void);  // 0x1c0490
    bool __cdecl spawn(void);  // 0x1c0e40
};

