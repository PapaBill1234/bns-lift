// fragmentpacket_gd.h: fragmentpacket.cpp, fragmentpacket.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class SimplePacketSplitter
{
protected:
    virtual bool __cdecl AddBuffer(::Packet::Header const *, ::Packet::Header *);  // 0xdf700
};

