// logagent.h: logagent.cpp (GameDaemon PDB, 2019 + PDB).
#pragma once
#include "GameDaemonFwd.h"
#include "logarchivesession.h"
#include "logagentpackethandler.h"

// PDB: LogAgent (GameDaemon), size 0x20. Base LogArchiveSession +0.
class LogAgent : public LogArchiveSession
{
public:
    virtual __cdecl ~LogAgent(void);  // 0x6bb190
    virtual bool __cdecl HandlePacket(::Packet const *);  // 0x6bb200

private:
    LogAgentPacketHandler _handler;  // +0x18
};
static_assert(sizeof(LogAgent) == 0x20, "sizeof LogAgent");
