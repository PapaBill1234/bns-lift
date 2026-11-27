// contribution.h: contribution.cpp, contribution.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class ContributionPouch
{
private:
    void __cdecl writeGameLog(::Pc *, ::NpcDeadBody *, unsigned __int64, short);  // 0x985e0
public:
    __cdecl ContributionPouch(void);  // 0x4554a0
};

class FactionContribution
{
public:
    virtual void __cdecl IncreaseContribution(::Npc *, ::GameObject *, __int64);  // 0x98ba0
    virtual void __cdecl DecreaseContribution(::Npc *, __int64, __int64);  // 0x98ca0
private:
    void __cdecl updateTopContribution(::Npc *, __int64);  // 0x98cf0
public:
    virtual __int64 __cdecl TopContributionGroupId(void);  // 0x98dd0
    virtual __int64 __cdecl TotalDamage(void);  // 0x98e00
    virtual void __cdecl Reset(void);  // 0x98e40
};

class GuildContribution
{
public:
    virtual void __cdecl IncreaseContribution(::Npc *, ::GameObject *, __int64);  // 0x98e60
private:
    void __cdecl updateTopContribution(::Npc *, __int64, __int64);  // 0x98f10
public:
    virtual void __cdecl DecreaseContribution(::Npc *, __int64, __int64);  // 0x99320
    virtual __int64 __cdecl TopContributionGroupId(void);  // 0x994e0
    virtual __int64 __cdecl TotalDamage(void);  // 0x99500
    virtual void __cdecl Reset(void);  // 0x99520
};

class NpcContribution
{
public:
    virtual void __cdecl Reset(void);  // 0x8c2a0
    virtual void __cdecl IncreaseContribution(::Npc *, ::GameObject *, __int64);  // 0x98b30
};

class PcContribution
{
public:
    void __cdecl Reset(::Pc *, __int64);  // 0x984d0
    __cdecl PcContribution(void);  // 0x455480
};

