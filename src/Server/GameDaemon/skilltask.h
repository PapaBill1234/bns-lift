// skilltask.h: skilltask.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class ChangeSkillPageTask
{
private:
    virtual void __cdecl start(void);  // 0x595ca0
};

class ExpandSkillPageTask
{
private:
    virtual void __cdecl start(void);  // 0x596730
};

class RenameSkillPageTask
{
private:
    virtual void __cdecl start(void);  // 0x596430
};

class SetMasteryStatPointTask
{
public:
    bool __cdecl Initialize(::Zone *, ::Creature *, short, short, char *const, char);  // 0x5960c0
private:
    virtual void __cdecl start(void);  // 0x596200
};

class SkillListTask
{
private:
    virtual void __cdecl start(void);  // 0x5956b0
};

class SkillPageTotalTask
{
private:
    virtual void __cdecl start(void);  // 0x596a90
};

class TrainTraitTask
{
public:
    __cdecl TrainTraitTask(void);  // 0x5956e0
private:
    virtual void __cdecl TimerExpired(unsigned int, long);  // 0x595770
    virtual void __cdecl start(void);  // 0x5957b0
};

