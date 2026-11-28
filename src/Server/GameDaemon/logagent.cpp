// logagent.cpp: logagent.cpp (GameDaemon PDB, 2019 + PDB).
#include "logagent.h"
#include "logagentpackethandler.h"
#include "../BloodLib/include/Log.h"
#include "../BloodLib/include/AlertSender.h"
#include "../BloodLib/include/Packet.h"
#include "LiftStub.h"

#pragma comment(linker, "/INCLUDE:??1LogAgent@@UEAA@XZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?HandlePacket@LogAgent@@UEAA_NPEBVPacket@@@Z")  // LIFT: dead-strip keep (no live caller yet)

static wchar_t const LOG_AGENT_FILE[] = L"source\\LogAgent.cpp";

// 0x6bb190
// LIFT: the body closes the socket. That is the inlined base destructor ~LogArchiveSession (Close, line 249).
__cdecl LogAgent::~LogAgent(void)
{
}

// 0x6bb200
bool __cdecl LogAgent::HandlePacket(::Packet const *packet)
{
    // LIFT: _handler (LogAgentPacketHandler) is at +0x18.
    LogAgentPacketHandler *handler =
        reinterpret_cast<LogAgentPacketHandler *>(reinterpret_cast<char *>(this) + 0x18);
    // LIFT: the command id is the byte after the 2 byte packet size.
    unsigned char command = reinterpret_cast<unsigned char const *>(packet->CurHeader)[2];
    int line;
    if (command > 2)
    {
        // ❓ HR hides the format string (pipe.chReply[3524]). The text is assumed.
        Log::Write(Log::LT_ERROR, LOG_AGENT_FILE, 26, L"invalid packet command %d", (int)(char)command);
        line = 26;
    }
    else
    {
        if (command == 1)
            return handler->HandleLogdAckPacket(this, packet);
        Log::Write(Log::LT_ERROR, LOG_AGENT_FILE, 34, L"invalid packet command %d", (int)(char)command);
        line = 34;
    }
    AlertSender::Write(LOG_AGENT_FILE, line, L"invalid packet command %d", (unsigned int)(char)command);
    return false;
}
