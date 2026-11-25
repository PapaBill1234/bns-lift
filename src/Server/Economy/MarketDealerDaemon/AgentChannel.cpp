// AgentChannel.obj (MarketDealerDaemon PDB). Source: .scratch/hr/AgentChannel.c
// 0x37b0 is a COMDAT copy of CriticalSection::~CriticalSection (src/common/Lock.h).
#include <winsock2.h>
#include <windows.h>
#include "AgentChannel.h"
#include "AlertSender.h"
#include "Log.h"
#include "Network.h"
#include "Packet.h"
#include "MarketDealerDaemon.h"
#include "Session.h"
#include "ThreadFreePacketPump.h"

namespace
{
wchar_t const* const AGENT_CHANNEL_FILE = L"AgentChannel.cpp";  // LIFT: No PDB symbol. The binary uses the literal.
static wchar_t const* const MODULE_NAME = L"agent channel";  // PDB MODULE_NAME
}

// 0x37c0
bool AgentChannelManager::initChannelManager()
{
    if (_marketAgentChannel == nullptr)
        return true;
    Log::Write(Log::LT_ERROR, AGENT_CHANNEL_FILE, 47,
               L"== CRASH == [%s], %s; agent channel manager is already initialized, marketAgentChannel:0x%p",
               MODULE_NAME, L"AgentChannelManager::initChannelManager", _marketAgentChannel);
    AlertSender::Write(AGENT_CHANNEL_FILE, 47,
                       L"== CRASH == [%s], %s; agent channel manager is already initialized, marketAgentChannel:0x%p",
                       MODULE_NAME, L"AgentChannelManager::initChannelManager", _marketAgentChannel);
    return false;
}

// 0x3860
AgentChannel* AgentChannelManager::GetMarketAgentChannel()
{
    AgentChannel* result = nullptr;
    _lock.Enter();
    if (_marketAgentChannel != nullptr)
    {
        _marketAgentChannel->addReferenceCount(false, AGENT_CHANNEL_FILE, 65);
        result = _marketAgentChannel;
    }
    _lock.Leave();
    return result;
}

// 0x38b0
bool AgentChannelManager::SetMarketAgentChannel(AgentChannel* const marketAgentChannel)
{
    if (marketAgentChannel == nullptr)
    {
        Log::Write(Log::LT_ERROR, AGENT_CHANNEL_FILE, 76, L"== CRASH == [%s], %s; invalid parameter, marketAgentChannel:0x%p",
                   MODULE_NAME, L"AgentChannelManager::SetMarketAgentChannel", static_cast<void*>(nullptr));
        AlertSender::Write(AGENT_CHANNEL_FILE, 76, L"== CRASH == [%s], %s; invalid parameter, marketAgentChannel:0x%p",
                           MODULE_NAME, L"AgentChannelManager::SetMarketAgentChannel", static_cast<void*>(nullptr));
        return false;
    }
    _lock.Enter();
    if (_marketAgentChannel != nullptr)
    {
        _lock.Leave();
        // BUG: 0x38b0 reads _marketAgentChannel after the lock is released.
        Log::Write(Log::LT_ERROR, AGENT_CHANNEL_FILE, 84,
                   L"[%s], %s; market agent channel is already set, old-marketAgentChannel:0x%p, old-agentWid:%u, "
                   L"new-marketAgentChannel:0x%p, new-agentWid:%u",
                   MODULE_NAME, L"AgentChannelManager::SetMarketAgentChannel", _marketAgentChannel,
                   static_cast<unsigned int>(_marketAgentChannel->_agentWid), marketAgentChannel,
                   static_cast<unsigned int>(marketAgentChannel->_agentWid));
        return false;
    }
    marketAgentChannel->addReferenceCount(false, AGENT_CHANNEL_FILE, 88);
    _marketAgentChannel = marketAgentChannel;
    _lock.Leave();
    return true;
}

// 0x39e0
void AgentChannelManager::RemoveMarketAgentChannel()
{
    _lock.Enter();
    if (_marketAgentChannel != nullptr)
    {
        _marketAgentChannel->removeReferenceCount(AGENT_CHANNEL_FILE, 99);
        _marketAgentChannel = nullptr;
    }
    _lock.Leave();
}

// 0x3a30
bool AgentSessionHandler::OnAccept(Session const* session) const
{
    unsigned long long const sessionId = session->_id;
    Log::Write(Log::LT_NOTICE, AGENT_CHANNEL_FILE, 112,
               L"[%s], %s; accepted agent session, sessionId:0x%I64X, portId:%u, sessionIndex:%u", MODULE_NAME,
               L"AgentSessionHandler::OnAccept", sessionId, static_cast<unsigned int>(sessionId >> 32),
               static_cast<unsigned int>(sessionId));
    return true;
}

// 0x3a90
bool AgentSessionHandler::OnConnect(Session const* session, bool firstConnected) const
{
    unsigned long long const sessionId = session->_id;
    Log::Write(Log::LT_ERROR, AGENT_CHANNEL_FILE, 118,
               L"[%s], %s; cannot use AgentSessionHandler::OnConnect handler, sessionId:0x%I64X, portId:%u, sessionIndex:%u",
               MODULE_NAME, L"AgentSessionHandler::OnConnect", sessionId,
               static_cast<unsigned int>(sessionId >> 32), static_cast<unsigned int>(sessionId));
    return false;
}

// 0x3af0
void AgentSessionHandler::OnClose(Session const* session, bool tryReconnect) const
{
    AgentChannel* const channel = static_cast<AgentChannel*>(session->GetChannel());
    if (channel == nullptr)
    {
        unsigned long long const sessionId = session->_id;
        Log::Write(Log::LT_NOTICE, AGENT_CHANNEL_FILE, 143,
                   L"[%s], %s; closed connection with unknown agent session, sessionId:0x%I64X, portId:%u, sessionIndex:%u",
                   MODULE_NAME, L"AgentSessionHandler::OnClose", sessionId,
                   static_cast<unsigned int>(sessionId >> 32), static_cast<unsigned int>(sessionId));
        return;
    }

    unsigned short const agentWid = channel->_agentWid;
    bool const isMarketAgent = channel->_connectionType == AgentChannel::CONNECTION_MARKET_AGENT;
    if (isMarketAgent)
        MarketDealerDaemon::_instance->_agentChannelManager->RemoveMarketAgentChannel();  // inlined at 0x3af0
    channel->RemoveSession(session, false);
    channel->removeReferenceCount(AGENT_CHANNEL_FILE, 133);

    unsigned long long const sessionId = session->_id;
    if (isMarketAgent)
        Log::Write(Log::LT_NOTICE, AGENT_CHANNEL_FILE, 136,
                   L"[%s], %s; closed connection with market agent session, agentWid:%u, sessionId:0x%I64X, portId:%u, sessionIndex:%u",
                   MODULE_NAME, L"AgentSessionHandler::OnClose", static_cast<unsigned int>(agentWid), sessionId,
                   static_cast<unsigned int>(sessionId >> 32), static_cast<unsigned int>(sessionId));
    else
        Log::Write(Log::LT_NOTICE, AGENT_CHANNEL_FILE, 139,
                   L"[%s], %s; closed connection with client agent session, agentWid:%u, sessionId:0x%I64X, portId:%u, sessionIndex:%u",
                   MODULE_NAME, L"AgentSessionHandler::OnClose", static_cast<unsigned int>(agentWid), sessionId,
                   static_cast<unsigned int>(sessionId >> 32), static_cast<unsigned int>(sessionId));
}

// 0x3cd0
bool AgentSessionHandler::PacketHandler(Session const* session, Packet const* packet) const
{
    unsigned long long const sessionId = session->_id;
    if (packet->CurHeader + 1 == nullptr)
    {
        Log::Write(Log::LT_ERROR, AGENT_CHANNEL_FILE, 151,
                   L"[%s], %s; invalid packet; packet command is null, cmd:0x%p, sessionId:0x%I64X, portId:%u, sessionIndex:%u",
                   MODULE_NAME, L"AgentSessionHandler::PacketHandler", static_cast<void*>(nullptr), sessionId,
                   static_cast<unsigned int>(sessionId >> 32), static_cast<unsigned int>(sessionId));
        return false;
    }

    short const cmd = (packet->CurHeader + 1)->size;
    AgentChannel* const channel = static_cast<AgentChannel*>(session->GetChannel());
    if (channel == nullptr)
    {
        // Only the hello request is allowed before the session has a channel.
        if (cmd == 1 && MarketDealerPacketServerSideHandlerList[1] != nullptr)
            return MarketDealerPacketServerSideHandlerList[1](session, packet);
        Log::Write(Log::LT_ERROR, AGENT_CHANNEL_FILE, 170,
                   L"[%s], %s; invalid packet command of not authorized session, command:%d, sessionId:0x%I64X, portId:%u, sessionIndex:%u",
                   MODULE_NAME, L"AgentSessionHandler::PacketHandler", static_cast<int>(cmd), sessionId,
                   static_cast<unsigned int>(sessionId >> 32), static_cast<unsigned int>(sessionId));
        return false;
    }

    bool result = false;
    if (channel->_connectionType == AgentChannel::CONNECTION_MARKET_AGENT)
    {
        if (cmd > 0 && cmd < 76)
        {
            if (MarketDealerPacketServerSideHandlerList[cmd] != nullptr)
                result = TFPP_PumpPacket(MarketDealerDaemon::MARKETEVENT_PACKET_PUMP_EVENT, Network::iocpHandle(), session,
                                         packet, cmd, 0, MarketDealerPacketServerSideHandlerList,
                                         MarketDealerPacketServerSideFragmentHandlerList);
            else
                Log::Write(Log::LT_ERROR, AGENT_CHANNEL_FILE, 188,
                           L"[%s], %s; invalid packet command of marketdealer, command:%d, agentWid:%u, connectionType:%d, "
                           L"sessionId:0x%I64X, portId:%u, sessionIndex:%u",
                           MODULE_NAME, L"AgentSessionHandler::PacketHandler", static_cast<int>(cmd),
                           static_cast<unsigned int>(channel->_agentWid), 1, sessionId,
                           static_cast<unsigned int>(sessionId >> 32), static_cast<unsigned int>(sessionId));
        }
        else if (cmd > 3072 && cmd < 3077)
        {
            if (MarketAgentPacketClientSideHandlerList[cmd - 3072] != nullptr)
                result = TFPP_PumpPacket(MarketDealerDaemon::MARKETEVENT_PACKET_PUMP_EVENT, Network::iocpHandle(), session,
                                         packet, cmd, 3072, MarketAgentPacketClientSideHandlerList,
                                         MarketAgentPacketClientSideFragmentHandlerList);
            else
                Log::Write(Log::LT_ERROR, AGENT_CHANNEL_FILE, 201,
                           L"[%s], %s; invalid packet command of marketagent, command:%d, agentWid:%u, connectionType:%d, "
                           L"sessionId:0x%I64X, portId:%u, sessionIndex:%u",
                           MODULE_NAME, L"AgentSessionHandler::PacketHandler", static_cast<int>(cmd),
                           static_cast<unsigned int>(channel->_agentWid), 1, sessionId,
                           static_cast<unsigned int>(sessionId >> 32), static_cast<unsigned int>(sessionId));
        }
        else
        {
            Log::Write(Log::LT_ERROR, AGENT_CHANNEL_FILE, 206,
                       L"[%s], %s; invalid packet command of session, command:%d, agentWid:%u, connectionType:%d, "
                       L"sessionId:0x%I64X, portId:%u, sessionIndex:%u",
                       MODULE_NAME, L"AgentSessionHandler::PacketHandler", static_cast<int>(cmd),
                       static_cast<unsigned int>(channel->_agentWid), 1, sessionId,
                       static_cast<unsigned int>(sessionId >> 32), static_cast<unsigned int>(sessionId));
        }
    }
    else if (cmd > 0 && cmd < 76 && MarketDealerPacketServerSideHandlerList[cmd] != nullptr)
    {
        result = TFPP_PumpPacket(MarketDealerDaemon::MARKETEVENT_PACKET_PUMP_EVENT, Network::iocpHandle(), session, packet,
                                 cmd, 0, MarketDealerPacketServerSideHandlerList,
                                 MarketDealerPacketServerSideFragmentHandlerList);
    }
    else
    {
        Log::Write(Log::LT_ERROR, AGENT_CHANNEL_FILE, 219,
                   L"[%s], %s; invalid packet command of clientagent, command:%d, agentWid:%u, connectionType:%d, "
                   L"sessionId:0x%I64X, portId:%u, sessionIndex:%u",
                   MODULE_NAME, L"AgentSessionHandler::PacketHandler", static_cast<int>(cmd),
                   static_cast<unsigned int>(channel->_agentWid), static_cast<int>(channel->_connectionType), sessionId,
                   static_cast<unsigned int>(sessionId >> 32), static_cast<unsigned int>(sessionId));
    }
    channel->removeReferenceCount(AGENT_CHANNEL_FILE, 223);
    return result;
}
