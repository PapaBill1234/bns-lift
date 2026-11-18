// WorldChannel.obj (PostOfficeDaemon PDB). Source: .scratch/hr/WorldChannel.c
// 0x1f4c0 is the std::map ctor (STL).
#include <winsock2.h>
#include <windows.h>
#include <string.h>
#include "WorldChannel.h"
#include "AlertSender.h"
#include "Log.h"
#include "Network.h"
#include "Packet.h"
#include "PacketBuffer.h"
#include "PostOfficeDaemon.h"
#include "RelayContext.h"
#include "Session.h"
#include "ThreadFreePacketPump.h"

extern Daemon::PacketHandler PostOfficeServicePacketServerSideHandlerList[13];
extern Daemon::PacketHandler PostOfficeServicePacketServerSideFragmentHandlerList[13];

namespace
{
wchar_t const* const WORLD_CHANNEL_FILE = L"WorldChannel.cpp";  // LIFT: No PDB symbol. The binary uses the literal.
static wchar_t const* const MODULE_NAME = L"world channel";  // PDB MODULE_NAME
wchar_t const* const SESSION_FILE = L"source\\Session.cpp";
wchar_t const* const CHANNEL_H_FILE =
    L"E:\\DailyBuild02\\PostOfficeDaemon-Common-0.0.348\\depot\\Branch\\348NC\\Program\\Server\\BloodLib\\include\\Channel.h";  // LIFT: No PDB symbol. The binary uses the literal.
}

// The original writes each "== CRASH ==" text to Log (LT_ERROR) and to AlertSender.
#define WORLD_CHANNEL_CRASH(line, fmt, ...)                                       \
    do                                                                            \
    {                                                                             \
        Log::Write(Log::LT_ERROR, WORLD_CHANNEL_FILE, line, fmt, __VA_ARGS__);    \
        AlertSender::Write(WORLD_CHANNEL_FILE, line, fmt, __VA_ARGS__);           \
    } while (0)

// LIFT: folded with ~AgentChannel (0x1f620)
WorldChannel::~WorldChannel()
{
}

// LIFT: folded with AgentChannel::GetId (0x1a6e0)
unsigned long long WorldChannel::GetId()
{
    return _wid;
}

// 0x1e490
unsigned short WorldChannel::GetWid(Session const* session)
{
    if (session == nullptr)
    {
        WORLD_CHANNEL_CRASH(32, L"== CRASH == [%s], %s; invalid parameter, session:0x%p", MODULE_NAME,
                            L"WorldChannel::GetWid", static_cast<void const*>(nullptr));
        return 0;
    }
    unsigned short wid = 0;
    WorldChannel* const channel = static_cast<WorldChannel*>(session->GetChannel());
    if (channel != nullptr)
    {
        wid = channel->_wid;
        channel->removeReferenceCount(SESSION_FILE, 1059);  // inlined Session code
    }
    return wid;
}

// 0x1e570
bool WorldChannel::SendRelayResponse(RelayContext const* const relayContext)
{
    if (relayContext == nullptr)
    {
        WORLD_CHANNEL_CRASH(50, L"== CRASH == [%s], %s; invalid parameter, relayContext:0x%p", MODULE_NAME,
                            L"WorldChannel::SendRelayResponse", static_cast<void*>(nullptr));
        return false;
    }

    Packet packet;
    memset(static_cast<void*>(&packet), 0, sizeof(packet));
    packet.Allocate();
    if (!relayContext->ComposeResponsePacket(packet))
    {
        return false;
    }

    Session* const session = const_cast<Session*>(GetSession());
    if (session != nullptr)
    {
        packet.ListHead->encrypt(session->_currentCrypt, session->_security3rd);
        PacketBuffer const* buffer = packet.ListHead;
        session->_lock.Enter();
        session->send(&buffer, 1);  // LIFT: inlined send
        session->_lock.Leave();
        session->removeReferenceCount(CHANNEL_H_FILE, 52);
    }
    return true;
}

// 0x1e720
bool WorldChannelManager::initChannelManager()
{
    if (_lockList != nullptr || _containerList != nullptr)
    {
        WORLD_CHANNEL_CRASH(101,
                            L"== CRASH == [%s], %s; world channel manager is already initialized, lockList:0x%p, containerList:0x%p",
                            MODULE_NAME, L"WorldChannelManager::initChannelManager", _lockList, _containerList);
        return false;
    }
    _lockList = liftArrayNew(CriticalSection, _bucketCount, WORLD_CHANNEL_FILE, 105);
    _containerList = liftArrayNew(Container, _bucketCount, WORLD_CHANNEL_FILE, 106);
    return true;
}

// 0x1e8b0
WorldChannel* WorldChannelManager::GetWorldChannel(unsigned short wid)
{
    if (wid == 0)
    {
        WORLD_CHANNEL_CRASH(114, L"== CRASH == [%s], %s; invalid parameter, wid:%u", MODULE_NAME,
                            L"WorldChannelManager::GetWorldChannel", 0u);
        return nullptr;
    }
    if (_lockList == nullptr || _containerList == nullptr)
    {
        WORLD_CHANNEL_CRASH(118,
                            L"== CRASH == [%s], %s; invalid world channel manager, lockList:0x%p, containerList:0x%p",
                            MODULE_NAME, L"WorldChannelManager::GetWorldChannel", _lockList, _containerList);
        return nullptr;
    }

    int const index = wid % _bucketCount;
    WorldChannel* worldChannel = nullptr;
    _lockList[index].Enter();
    Container::iterator it = _containerList[index].find(wid);
    if (it != _containerList[index].end())
    {
        worldChannel = it->second;
        if (worldChannel == nullptr)
        {
            _lockList[index].Leave();
            WORLD_CHANNEL_CRASH(131, L"== CRASH == [%s], %s; world channel is null, wid:%u, worldChannel:0x%p",
                                MODULE_NAME, L"WorldChannelManager::GetWorldChannel", static_cast<unsigned int>(wid),
                                static_cast<void*>(nullptr));
            return nullptr;
        }
        worldChannel->addReferenceCount(WORLD_CHANNEL_FILE, 134);
    }
    _lockList[index].Leave();
    return worldChannel;
}

// 0x1eb20
bool WorldChannelManager::AddWorldChannel(WorldChannel* const worldChannel)
{
    if (worldChannel == nullptr)
    {
        WORLD_CHANNEL_CRASH(144, L"== CRASH == [%s], %s; invalid parameter, worldChannel:0x%p", MODULE_NAME,
                            L"WorldChannelManager::AddWorldChannel", static_cast<void*>(nullptr));
        return false;
    }
    if (_lockList == nullptr || _containerList == nullptr)
    {
        WORLD_CHANNEL_CRASH(148,
                            L"== CRASH == [%s], %s; invalid world channel manager, lockList:0x%p, containerList:0x%p",
                            MODULE_NAME, L"WorldChannelManager::AddWorldChannel", _lockList, _containerList);
        return false;
    }
    unsigned short const wid = worldChannel->_wid;
    if (wid == 0)
    {
        Log::Write(Log::LT_ERROR, WORLD_CHANNEL_FILE, 154, L"[%s], %s; invalid world Id, wid:%u", MODULE_NAME,
                   L"WorldChannelManager::AddWorldChannel", 0u);
        return false;
    }

    int const index = wid % _bucketCount;
    _lockList[index].Enter();
    if (!_containerList[index].insert(std::pair<unsigned short, WorldChannel*>(wid, worldChannel)).second)
    {
        _lockList[index].Leave();
        Log::Write(Log::LT_ERROR, WORLD_CHANNEL_FILE, 165, L"[%s], %s; failed to add world channel, wid:%u",
                   MODULE_NAME, L"WorldChannelManager::AddWorldChannel", static_cast<unsigned int>(wid));
        return false;
    }
    worldChannel->addReferenceCount(WORLD_CHANNEL_FILE, 169);
    InterlockedIncrement(&_worldCount);
    _lockList[index].Leave();
    return true;
}

// 0x1ed90
bool WorldChannelManager::RemoveWorldChannel(unsigned short wid)
{
    if (wid == 0)
    {
        WORLD_CHANNEL_CRASH(181, L"== CRASH == [%s], %s; invalid parameter, wid:%u", MODULE_NAME,
                            L"WorldChannelManager::RemoveWorldChannel", 0u);
        return false;
    }
    if (_lockList == nullptr || _containerList == nullptr)
    {
        WORLD_CHANNEL_CRASH(185,
                            L"== CRASH == [%s], %s; invalid world channel manager, lockList:0x%p, containerList:0x%p",
                            MODULE_NAME, L"WorldChannelManager::RemoveWorldChannel", _lockList, _containerList);
        return false;
    }

    int const index = wid % _bucketCount;
    _lockList[index].Enter();
    Container::iterator it = _containerList[index].find(wid);
    if (it == _containerList[index].end())
    {
        _lockList[index].Leave();
        Log::Write(Log::LT_ERROR, WORLD_CHANNEL_FILE, 195, L"[%s], %s; no such world channel, wid:%u",
                   MODULE_NAME, L"WorldChannelManager::RemoveWorldChannel", static_cast<unsigned int>(wid));
        return false;
    }
    WorldChannel* const worldChannel = it->second;
    if (worldChannel == nullptr)
    {
        _lockList[index].Leave();
        WORLD_CHANNEL_CRASH(202, L"== CRASH == [%s], %s; world channel is null, wid:%u, worldChannel:0x%p",
                            MODULE_NAME, L"WorldChannelManager::RemoveWorldChannel", static_cast<unsigned int>(wid),
                            static_cast<void*>(nullptr));
        return false;
    }
    _containerList[index].erase(it);
    worldChannel->removeReferenceCount(WORLD_CHANNEL_FILE, 207);
    InterlockedDecrement(&_worldCount);
    _lockList[index].Leave();
    return true;
}

// LIFT: no out-of-line copy found
WorldSessionHandler::~WorldSessionHandler()
{
}

// 0x1f060
bool WorldSessionHandler::OnAccept(Session const* session) const
{
    unsigned long long const sessionId = session->_id;
    Log::Write(Log::LT_NOTICE, WORLD_CHANNEL_FILE, 224,
               L"[%s], %s; accepted world session, sessionId:0x%I64X, portId:%u, sessionIndex:%u", MODULE_NAME,
               L"WorldSessionHandler::OnAccept", sessionId, static_cast<unsigned int>(sessionId >> 32),
               static_cast<unsigned int>(sessionId));
    return true;
}

// 0x1f0c0
bool WorldSessionHandler::OnConnect(Session const* session, bool firstConnected) const
{
    unsigned long long const sessionId = session->_id;
    Log::Write(Log::LT_ERROR, WORLD_CHANNEL_FILE, 230,
               L"[%s], %s; cannot use WorldSessionHandler::OnConnect handler, sessionId:0x%I64X, portId:%u, sessionIndex:%u",
               MODULE_NAME, L"WorldSessionHandler::OnConnect", sessionId,
               static_cast<unsigned int>(sessionId >> 32), static_cast<unsigned int>(sessionId));
    return false;
}

// 0x1f120
void WorldSessionHandler::OnClose(Session const* session, bool tryReconnect) const
{
    unsigned long long const sessionId = session->_id;
    WorldChannel* const channel = static_cast<WorldChannel*>(session->GetChannel());
    if (channel == nullptr)
    {
        Log::Write(Log::LT_NOTICE, WORLD_CHANNEL_FILE, 247,
                   L"[%s], %s; closed connection with unknown world session, sessionId:0x%I64X, portId:%u, sessionIndex:%u",
                   MODULE_NAME, L"WorldSessionHandler::OnClose", sessionId,
                   static_cast<unsigned int>(sessionId >> 32), static_cast<unsigned int>(sessionId));
        return;
    }

    unsigned short const wid = channel->_wid;
    PostOfficeDaemon::_instance->_worldChannelManager->RemoveWorldChannel(wid);
    channel->RemoveSession(session, false);
    channel->removeReferenceCount(WORLD_CHANNEL_FILE, 242);
    Log::Write(Log::LT_NOTICE, WORLD_CHANNEL_FILE, 244,
               L"[%s], %s; closed connection with world session, wid:%u, sessionId:0x%I64X, portId:%u, sessionIndex:%u",
               MODULE_NAME, L"WorldSessionHandler::OnClose", static_cast<unsigned int>(wid), sessionId,
               static_cast<unsigned int>(sessionId >> 32), static_cast<unsigned int>(sessionId));
}

// 0x1f270
bool WorldSessionHandler::PacketHandler(Session const* session, Packet const* packet) const
{
    unsigned long long const sessionId = session->_id;
    if (packet->CurHeader == nullptr)
    {
        Log::Write(Log::LT_ERROR, WORLD_CHANNEL_FILE, 255,
                   L"[%s], %s; invalid packet; command is null, cmd:0x%p, sessionId:0x%I64X, portId:%u, sessionIndex:%u",
                   MODULE_NAME, L"WorldSessionHandler::PacketHandler", static_cast<void*>(nullptr), sessionId,
                   static_cast<unsigned int>(sessionId >> 32), static_cast<unsigned int>(sessionId));
        return false;
    }

    short const cmd = reinterpret_cast<Packet::Header const*>(packet->CurHeader)[1].size;
    WorldChannel* const channel = static_cast<WorldChannel*>(session->GetChannel());
    if (channel == nullptr)
    {
        // Only the hello request is allowed before the session has a channel.
        if (cmd == 1 && PostOfficeServicePacketServerSideHandlerList[1] != nullptr)
            return PostOfficeServicePacketServerSideHandlerList[1](session, packet);
        Log::Write(Log::LT_ERROR, WORLD_CHANNEL_FILE, 272,
                   L"[%s], %s; invalid packet command of not authorized world session, command:%d, sessionId:0x%I64X, portId:%u, sessionIndex:%u",
                   MODULE_NAME, L"WorldSessionHandler::PacketHandler", static_cast<int>(cmd), sessionId,
                   static_cast<unsigned int>(sessionId >> 32), static_cast<unsigned int>(sessionId));
        return false;
    }

    bool result = false;
    if (cmd > 0 && cmd < 13 && PostOfficeServicePacketServerSideHandlerList[cmd] != nullptr)
    {
        // LIFT: LTCG folded the event id and the offset. The values come from the LobbyGate call.
        result = TFPP_PumpPacket(128, Network::iocpHandle(), session, packet, cmd, 0,
                                 PostOfficeServicePacketServerSideHandlerList,
                                 PostOfficeServicePacketServerSideFragmentHandlerList);
    }
    else
    {
        Log::Write(Log::LT_ERROR, WORLD_CHANNEL_FILE, 284,
                   L"[%s], %s; invalid packet command of world session, command:%d, wid:%u, sessionId:0x%I64X, portId:%u, sessionIndex:%u",
                   MODULE_NAME, L"WorldSessionHandler::PacketHandler", static_cast<int>(cmd),
                   static_cast<unsigned int>(channel->_wid), sessionId, static_cast<unsigned int>(sessionId >> 32),
                   static_cast<unsigned int>(sessionId));
    }
    channel->removeReferenceCount(WORLD_CHANNEL_FILE, 287);
    return result;
}
