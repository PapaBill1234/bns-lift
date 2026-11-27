// droppedpouch.h: droppedpouch.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class DroppedPouch
{
public:
    __cdecl DroppedPouch(unsigned __int64);  // 0x9b080
    virtual __cdecl ~DroppedPouch(void);  // 0x9b190
    bool __cdecl InitializeFromBattleRoyalField(::vector16, ::Zone *, short, unsigned __int64, long);  // 0x9b230
private:
    void __cdecl makeItemPouch(void);  // 0x9b310
public:
    virtual void __cdecl OnTimer(::Zone *, unsigned short);  // 0x9b400
    bool __cdecl UpdateItemPouch(void);  // 0x9b430
private:
    void __cdecl hide(void);  // 0x9b490
    void __cdecl decompose(void);  // 0x9b510
};

class DroppedPouchIdManager
{
protected:
    virtual bool __cdecl IsExist(unsigned __int64);  // 0x9b060
};

class DroppedPouchList
{
public:
    __cdecl ~DroppedPouchList(void);  // 0x9b5a0
    bool __cdecl Initialize(::Zone *, int);  // 0x9b660
    ::DroppedPouch * __cdecl Create(void);  // 0x9b710
    bool __cdecl Remove(unsigned __int64);  // 0x9b870
};

