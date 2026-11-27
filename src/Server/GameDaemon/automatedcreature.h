// automatedcreature.h: automatedcreature.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class AutomatedCreature
{
public:
    virtual void __cdecl LeaveZone(::LeaveReason);  // 0x9b960
    virtual __cdecl ~AutomatedCreature(void);  // 0x3fee10
    virtual void __cdecl EnterZone(::EnterReason, bool, unsigned int);  // 0x3fee20
};

