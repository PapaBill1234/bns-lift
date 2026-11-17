// ManagerChannel.obj (MarketDealerDaemon PDB). Source: .scratch/hr/ManagerChannel.c
#include <winsock2.h>
#include <windows.h>
#include "ManagerChannel.h"
#include "Log.h"
#include "Network.h"
#include "Packet.h"
#include "MarketDealerDaemon.h"
#include "Session.h"
#include "ThreadFreePacketPump.h"

namespace
{
wchar_t const* const MANAGER_CHANNEL_FILE = L"ManagerChannel.cpp";  // LIFT: No PDB symbol. The binary uses the literal.
static wchar_t const* const MODULE_NAME = L"manager channel";  // PDB MODULE_NAME
}

// 0x1a4c0
bool ManagerSessionHandler::OnAccept(Session const* session) const
{
    unsigned long long const sessionId = session->_id;
    Log::Write(Log::LT_NOTICE, MANAGER_CHANNEL_FILE, 32,
               L"[%s], %s; accepted manager session, sessionId:0x%I64X, portId:%u, sessionIndex:%u", MODULE_NAME,
               L"ManagerSessionHandler::OnAccept", sessionId, static_cast<unsigned int>(sessionId >> 32),
               static_cast<unsigned int>(sessionId));
    return true;
}

// 0x1a520
bool ManagerSessionHandler::OnConnect(Session const* session, bool firstConnected) const
{
    unsigned long long const sessionId = session->_id;
    Log::Write(Log::LT_ERROR, MANAGER_CHANNEL_FILE, 38,
               L"[%s], %s; cannot use ManagerSessionHandler::OnConnect handler, sessionId:0x%I64X, portId:%u, sessionIndex:%u",
               MODULE_NAME, L"ManagerSessionHandler::OnConnect", sessionId,
               static_cast<unsigned int>(sessionId >> 32), static_cast<unsigned int>(sessionId));
    return false;
}

// 0x1a580
void ManagerSessionHandler::OnClose(Session const* session, bool tryReconnect) const
{
    ManagerChannel* const channel = static_cast<ManagerChannel*>(session->GetChannel());
    if (channel == nullptr)
    {
        unsigned long long const sessionId = session->_id;
        Log::Write(Log::LT_NOTICE, MANAGER_CHANNEL_FILE, 54,
                   L"[%s], %s; closed connection with unknown manager session, sessionId:0x%I64X, portId:%u, sessionIndex:%u",
                   MODULE_NAME, L"ManagerSessionHandler::OnClose", sessionId,
                   static_cast<unsigned int>(sessionId >> 32), static_cast<unsigned int>(sessionId));
        return;
    }

    unsigned short const managerWid = channel->_managerWid;
    channel->RemoveSession(session, false);
    channel->removeReferenceCount(MANAGER_CHANNEL_FILE, 49);
    unsigned long long const sessionId = session->_id;
    Log::Write(Log::LT_NOTICE, MANAGER_CHANNEL_FILE, 51,
               L"[%s], %s; closed connection with manager session, wid:%u, sessionId:0x%I64X, portId:%u, sessionIndex:%u",
               MODULE_NAME, L"ManagerSessionHandler::OnClose", static_cast<unsigned int>(managerWid), sessionId,
               static_cast<unsigned int>(sessionId >> 32), static_cast<unsigned int>(sessionId));
}

// 0x1a6c0
bool ManagerSessionHandler::PacketHandler(Session const* session, Packet const* packet) const
{
    unsigned long long const sessionId = session->_id;
    if (packet->CurHeader + 1 == nullptr)
    {
        Log::Write(Log::LT_ERROR, MANAGER_CHANNEL_FILE, 62,
                   L"[%s], %s; invalid packet; command is null, cmd:0x%p, sessionId:0x%I64X, portId:%u, sessionIndex:%u",
                   MODULE_NAME, L"ManagerSessionHandler::PacketHandler", static_cast<void*>(nullptr), sessionId,
                   static_cast<unsigned int>(sessionId >> 32), static_cast<unsigned int>(sessionId));
        return false;
    }

    short const cmd = (packet->CurHeader + 1)->size;
    ManagerChannel* const channel = static_cast<ManagerChannel*>(session->GetChannel());
    if (channel == nullptr)
    {
        // Only the hello request is allowed before the session has a channel.
        if (cmd == 1 && MarketManagerPacketServerSideHandlerList[1] != nullptr)
            return MarketManagerPacketServerSideHandlerList[1](session, packet);
        Log::Write(Log::LT_ERROR, MANAGER_CHANNEL_FILE, 79,
                   L"[%s], %s; invalid packet command of not authorized session, command:%d, sessionId:0x%I64X, portId:%u, sessionIndex:%u",
                   MODULE_NAME, L"ManagerSessionHandler::PacketHandler", static_cast<int>(cmd), sessionId,
                   static_cast<unsigned int>(sessionId >> 32), static_cast<unsigned int>(sessionId));
        return false;
    }

    bool result = false;
    if (cmd > 0 && cmd < 16 && MarketManagerPacketServerSideHandlerList[cmd] != nullptr)
    {
        result = TFPP_PumpPacket(MarketDealerDaemon::MARKETEVENT_PACKET_PUMP_EVENT, Network::iocpHandle(), session, packet,
                                 cmd, 0, MarketManagerPacketServerSideHandlerList,
                                 MarketManagerPacketServerSideFragmentHandlerList);
    }
    else
    {
        Log::Write(Log::LT_ERROR, MANAGER_CHANNEL_FILE, 91,
                   L"[%s], %s; invalid manager packet command, command:%d, managerWid:%u, sessionId:0x%I64X, portId:%u, sessionIndex:%u",
                   MODULE_NAME, L"ManagerSessionHandler::PacketHandler", static_cast<int>(cmd),
                   static_cast<unsigned int>(channel->_managerWid), sessionId,
                   static_cast<unsigned int>(sessionId >> 32), static_cast<unsigned int>(sessionId));
    }
    channel->removeReferenceCount(MANAGER_CHANNEL_FILE, 94);
    return result;
}
