// AgentChannel.obj (PostOfficeDaemon PDB). Source: .scratch/hr/AgentChannel.c
// 0x36b0 is a COMDAT copy of CriticalSection::~CriticalSection (src/common/Lock.h).
// 0x1a6e0 AgentChannel::GetId and 0x1f620 ~AgentChannel are in the AgentPacketHandler module (COMDAT). They are here.
#include <winsock2.h>
#include <windows.h>
#include "AgentChannel.h"
#include "AlertSender.h"
#include "Log.h"
#include "Network.h"
#include "Packet.h"
#include "PostOfficeDaemon.h"
#include "Session.h"
#include "ThreadFreePacketPump.h"

extern Daemon::PacketHandler PostOfficePacketServerSideHandlerList[7];
extern Daemon::PacketHandler PostOfficePacketServerSideFragmentHandlerList[7];

namespace
{
wchar_t const* const AGENT_CHANNEL_FILE = L"AgentChannel.cpp";  // LIFT: No PDB symbol. The binary uses the literal.
wchar_t const* const SESSION_FILE = L"source\\Session.cpp";
static wchar_t const* const MODULE_NAME = L"agent channel";  // PDB MODULE_NAME
}

// 0x1f620
AgentChannel::~AgentChannel()
{
}

// 0x1a6e0
unsigned long long AgentChannel::GetId()
{
    return _agentWid;
}

// 0x36c0
bool AgentChannelManager::initChannelManager()
{
    if (_postAgentChannel == nullptr)
        return true;
    Log::Write(Log::LT_ERROR, AGENT_CHANNEL_FILE, 46,
               L"== CRASH == [%s], %s; agent channel manager is already initialized, postAgentChannel:0x%p",
               MODULE_NAME, L"AgentChannelManager::initChannelManager", _postAgentChannel);
    AlertSender::Write(AGENT_CHANNEL_FILE, 46,
                       L"== CRASH == [%s], %s; agent channel manager is already initialized, postAgentChannel:0x%p",
                       MODULE_NAME, L"AgentChannelManager::initChannelManager", _postAgentChannel);
    return false;
}

// LIFT: no out-of-line copy found
AgentSessionHandler::~AgentSessionHandler()
{
}

// 0x3760
bool AgentSessionHandler::OnAccept(Session const* session) const
{
    unsigned long long const sessionId = session->_id;
    Log::Write(Log::LT_NOTICE, AGENT_CHANNEL_FILE, 112,
               L"[%s], %s; accepted agent session, sessionId:0x%I64X, portId:%u, sessionIndex:%u", MODULE_NAME,
               L"AgentSessionHandler::OnAccept", sessionId, static_cast<unsigned int>(sessionId >> 32),
               static_cast<unsigned int>(sessionId));
    return true;
}

// 0x37c0
bool AgentSessionHandler::OnConnect(Session const* session, bool firstConnected) const
{
    unsigned long long const sessionId = session->_id;
    Log::Write(Log::LT_ERROR, AGENT_CHANNEL_FILE, 118,
               L"[%s], %s; cannot use AgentSessionHandler::OnConnect handler, sessionId:0x%I64X, portId:%u, sessionIndex:%u",
               MODULE_NAME, L"AgentSessionHandler::OnConnect", sessionId,
               static_cast<unsigned int>(sessionId >> 32), static_cast<unsigned int>(sessionId));
    return false;
}

// 0x3820
void AgentSessionHandler::OnClose(Session const* session, bool tryReconnect) const
{
    unsigned long long const sessionId = session->_id;
    AgentChannel* const channel = static_cast<AgentChannel*>(session->GetChannel());
    if (channel == nullptr)
    {
        Log::Write(Log::LT_NOTICE, AGENT_CHANNEL_FILE, 143,
                   L"[%s], %s; closed connection with unknown agent session, sessionId:0x%I64X, portId:%u, sessionIndex:%u",
                   MODULE_NAME, L"AgentSessionHandler::OnClose", sessionId,
                   static_cast<unsigned int>(sessionId >> 32), static_cast<unsigned int>(sessionId));
        return;
    }

    unsigned short const agentWid = channel->_agentWid;
    bool const isPostAgent = channel->_connectionType == 1;
    if (isPostAgent)
    {
        // LIFT: inlined AgentChannelManager release (log line 98). The name is not in the PDB.
        AgentChannelManager* const manager = PostOfficeDaemon::_instance->_agentChannelManager;
        manager->_lock.Enter();
        if (manager->_postAgentChannel != nullptr)
        {
            manager->_postAgentChannel->removeReferenceCount(AGENT_CHANNEL_FILE, 98);
            manager->_postAgentChannel = nullptr;
        }
        manager->_lock.Leave();
    }
    channel->RemoveSession(session, false);
    channel->removeReferenceCount(AGENT_CHANNEL_FILE, 133);

    if (isPostAgent)
        Log::Write(Log::LT_NOTICE, AGENT_CHANNEL_FILE, 136,
                   L"[%s], %s; closed connection with post agent session, agentWid:%u, sessionId:0x%I64X, portId:%u, sessionIndex:%u",
                   MODULE_NAME, L"AgentSessionHandler::OnClose", static_cast<unsigned int>(agentWid), sessionId,
                   static_cast<unsigned int>(sessionId >> 32), static_cast<unsigned int>(sessionId));
    else
        Log::Write(Log::LT_NOTICE, AGENT_CHANNEL_FILE, 139,
                   L"[%s], %s; closed connection with client agent session, agentWid:%u, sessionId:0x%I64X, portId:%u, sessionIndex:%u",
                   MODULE_NAME, L"AgentSessionHandler::OnClose", static_cast<unsigned int>(agentWid), sessionId,
                   static_cast<unsigned int>(sessionId >> 32), static_cast<unsigned int>(sessionId));
}

// 0x3a00
bool AgentSessionHandler::PacketHandler(Session const* session, Packet const* packet) const
{
    void* iocpHandle = nullptr;
    short const* const pCmd = &packet->CurHeader[1].size;
    if (pCmd == nullptr)
    {
        Log::Write(Log::LT_ERROR, AGENT_CHANNEL_FILE, 151,
                   L"[%s], %s; invalid packet; command is null, cmd:0x%p, sessionId:0x%I64X, portId:%u, sessionIndex:%u",
                   MODULE_NAME, L"AgentSessionHandler::PacketHandler", static_cast<void*>(nullptr), session->_id,
                   static_cast<unsigned int>(session->_id >> 32), static_cast<unsigned int>(session->_id));
        return false;
    }

    // LIFT: Inlined Session::GetChannel with the add-ref (Session.cpp line 1051).
    AgentChannel* channel = nullptr;
    if (session->_channel != nullptr && !session->_waitForRelease)
    {
        session->_channel->addReferenceCount(SESSION_FILE, 1051);
        channel = static_cast<AgentChannel*>(session->_channel);
    }
    bool result = false;
    if (channel == nullptr)
    {
        // Only the hello request is allowed before the session has a channel.
        if (*pCmd == 1 && PostOfficePacketServerSideHandlerList[1] != nullptr)
        {
            result = PostOfficePacketServerSideHandlerList[1](session, packet);
        }
        else
        {
            Log::Write(Log::LT_ERROR, AGENT_CHANNEL_FILE, 168,
                       L"[%s], %s; invalid packet command of not authorized session, command:%d, sessionId:0x%I64X, portId:%u, sessionIndex:%u",
                       MODULE_NAME, L"AgentSessionHandler::PacketHandler", static_cast<int>(*pCmd), session->_id,
                       static_cast<unsigned int>(session->_id >> 32), static_cast<unsigned int>(session->_id));
        }
    }
    else
    {
        if (*pCmd > 0 && *pCmd < 7 && PostOfficePacketServerSideHandlerList[*pCmd] != nullptr)
        {
            // LIFT: LTCG folded the event id and the offset. The values come from the LobbyGate call.
            iocpHandle = Network::iocpHandle();
            result = TFPP_PumpPacket(PostOfficeDaemon::POSTEVENT_PACKET_PUMP_EVENT, iocpHandle, session, packet, *pCmd, 0,
                                     PostOfficePacketServerSideHandlerList, PostOfficePacketServerSideFragmentHandlerList);
        }
        else
        {
            Log::Write(Log::LT_ERROR, AGENT_CHANNEL_FILE, 181,
                       L"[%s], %s; invalid clientagent packet command, command:%d, agentWid:%u, connectionType:%d, sessionId:0x%I64X, portId:%u, sessionIndex:%u",
                       MODULE_NAME, L"AgentSessionHandler::PacketHandler", static_cast<int>(*pCmd),
                       static_cast<unsigned int>(channel->_agentWid), static_cast<int>(channel->_connectionType), session->_id,
                       static_cast<unsigned int>(session->_id >> 32), static_cast<unsigned int>(session->_id));
        }
        channel->removeReferenceCount(AGENT_CHANNEL_FILE, 184);
    }
    return result;
}
