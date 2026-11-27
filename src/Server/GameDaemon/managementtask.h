// managementtask.h: managementtask.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class ManagementTask
{
protected:
    static bool __cdecl validateTarget(wchar_t const *, ::Zone *, ::Creature *, wchar_t const *);  // 0x159400
};

class SendHomeManagementTask
{
public:
    __cdecl SendHomeManagementTask(void);  // 0x1594f0
private:
    virtual void __cdecl start(void);  // 0x159570
};

