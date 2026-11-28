// logagentpackethandler.h: logagentpackethandler.cpp (GameDaemon PDB, 2019 + PDB).
#pragma once
#include "GameDaemonFwd.h"

// PDB: LogAgentPacketHandler (GameDaemon), size 0x8 (vfptr only).
class LogAgentPacketHandler
{
public:
    virtual ~LogAgentPacketHandler() {}  // LIFT: PDB slot 0; the body only sets the vfptr
    bool __cdecl HandleLogdAckPacket(::LogAgent *, ::Packet const *);  // 0x6d94e0
};
static_assert(sizeof(LogAgentPacketHandler) == 0x8, "sizeof LogAgentPacketHandler");
