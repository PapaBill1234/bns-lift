// session_gd.h: session.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class ReconnectTimer
{
protected:
    virtual bool __cdecl HandleEvent(::EventContext *, unsigned long);  // 0x699dd0
};

