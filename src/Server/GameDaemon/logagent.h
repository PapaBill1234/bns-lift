// logagent.h: logagent.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class LogAgent
{
public:
    virtual __cdecl ~LogAgent(void);  // 0x6bb190
    virtual bool __cdecl HandlePacket(::Packet const *);  // 0x6bb200
};

