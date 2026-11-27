// logserversessionhandler.h: logserversessionhandler.cpp, logserversessionhandler.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class LogServerSessionHandler
{
public:
    virtual __cdecl ~LogServerSessionHandler(void);  // 0x6ba560
    bool __cdecl HandleVersionNotifyPacket(::LogServer *, ::Packet const *);  // 0x6d9010
    bool __cdecl HandleInitAckPacket(::LogServer *, ::Packet const *);  // 0x6d91f0
    bool __cdecl HandlePingAckPacket(::LogServer *, ::Packet const *);  // 0x6d9370
    bool __cdecl HandleControlRequeryNotifyPacket(::LogServer *, ::Packet const *);  // 0x6d93f0
};

