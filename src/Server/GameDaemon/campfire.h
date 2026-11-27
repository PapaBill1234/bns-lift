// campfire.h: campfire.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class Campfire
{
private:
    __cdecl Campfire(unsigned __int64);  // 0x64030
public:
    bool __cdecl Initialize(unsigned int, unsigned __int64, ::vector16, ::Zone *, ::CampfireType);  // 0x64160
    long __cdecl GetRemainDuration(void) const;  // 0x64350
    virtual void __cdecl OnTimer(::Zone *, unsigned short);  // 0x643b0
private:
    void __cdecl remove(void);  // 0x643d0
};

class CampfireIdManager
{
protected:
    virtual bool __cdecl IsExist(unsigned __int64);  // 0x63fe0
};

class CampfireList
{
public:
    __cdecl ~CampfireList(void);  // 0x64550
    bool __cdecl Initialize(::Zone *, int);  // 0x646e0
    ::Campfire * __cdecl CreateCampfire(void);  // 0x647d0
    bool __cdecl Remove(unsigned __int64);  // 0x64880
};

