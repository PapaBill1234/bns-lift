// CacheGateChannel.obj (PostOfficeDaemon PDB). Source: .scratch/hr/CacheGateChannel.c
// 0x6fb0 FragmentPacket::Compose is in src/common/FragmentPacket.cpp (same code).
#include <winsock2.h>
#include <windows.h>
#include <string.h>
#include "CacheGateChannel.h"
#include "AlertSender.h"
#include "CachedWatchdog.h"
#include "FragmentPacket.h"
#include "Log.h"
#include "Network.h"
#include "Packet.h"
#include "PipeConsole.h"
#include "PostOfficeDaemon.h"
#include "RelayContext.h"
#include "Session.h"
#include "ThreadFreePacketPump.h"
#include "CacheGatePacketCommand.h"

extern Daemon::PacketHandler CacheGatePacketClientSideHandlerList[10];
extern Daemon::PacketHandler CacheGatePacketClientSideFragmentHandlerList[10];

namespace
{
wchar_t const* const CACHEGATE_CHANNEL_FILE = L"CacheGateChannel.cpp";  // LIFT: No PDB symbol. The binary uses the literal.
wchar_t const* const CHANNEL_HEADER_FILE =                               // LIFT: No PDB symbol. The binary uses the literal.
    L"E:\\DailyBuild02\\PostOfficeDaemon-Common-0.0.348\\depot\\Branch\\348NC\\Program\\Server\\BloodLib\\include\\Channel.h";
static wchar_t const* const MODULE_NAME = L"cachegate channel";  // PDB MODULE_NAME
wchar_t const* const DISCONNECTED_CACHEGATE = L"disconnected cachegate";  // LIFT: No PDB symbol. The binary uses the literal.
}

// 0x12c30 (scalar deleting dtor; the dtor body is empty)
CacheGateChannel::~CacheGateChannel()
{
}

// 0x5d860 (folded by ICF with PingGenerator::TimerId: xor eax, eax)
unsigned long long CacheGateChannel::GetId()
{
    return 0;
}

// 0x12c20 (folded by ICF with ~AgentSessionHandler; the body is empty)
CacheGateSessionHandler::~CacheGateSessionHandler()
{
}

// Inlined (log line 36)
void CacheGateChannel::SetServiceState(ServiceState const newState)
{
    InterlockedExchange(reinterpret_cast<long volatile*>(&_serviceState), newState);
    Log::Write(Log::LT_NOTICE, CACHEGATE_CHANNEL_FILE, 36, L"[%s], %s; current cachegate service state:%s",
               MODULE_NAME, L"CacheGateChannel::SetServiceState",
               newState == SERVICE_STATE_AVAILABLE ? L"available" : L"unavailable");  // inlined: 0x7bf7 state 0 -> L"unavailable", 0x7ed9 state 1 -> L"available"
}

// 0x75a0
bool CacheGateChannel::composeRelayHeader(Packet& packet, RelayHeader const& relayHeader)
{
    bool const result = packet.Compose("hhhqhq", 4, relayHeader._fromWid, relayHeader._toWid, relayHeader._relayTid,
                                       relayHeader._hint, relayHeader._reserved) != 0;
    if (result)
        Log::Write(Log::LT_DEBUG, CACHEGATE_CHANNEL_FILE, 115,
                   L"[%s], %s; composed relay header, fromWid:%u, toWid:%u, relayTid:0x%I64X, hint:%u, reserved:%I64u",
                   MODULE_NAME, L"CacheGateChannel::composeRelayHeader", relayHeader._fromWid, relayHeader._toWid,
                   relayHeader._relayTid, relayHeader._hint, relayHeader._reserved);
    else
        Log::Write(Log::LT_ERROR, CACHEGATE_CHANNEL_FILE, 112,
                   L"[%s], %s; failed to compose relay header, fromWid:%u, toWid:%u, relayTid:0x%I64X, hint:%u, reserved:%I64u",
                   MODULE_NAME, L"CacheGateChannel::composeRelayHeader", relayHeader._fromWid, relayHeader._toWid,
                   relayHeader._relayTid, relayHeader._hint, relayHeader._reserved);
    return result;
}

// 0x7670
__declspec(noinline) bool CacheGateChannel::composeRelayHeader(FragmentPacket& packet, RelayHeader const& relayHeader)
{
    bool const result = packet.Compose(5, relayHeader._fromWid, relayHeader._toWid, relayHeader._relayTid,
                                       relayHeader._hint, relayHeader._reserved) != 0;
    if (result)
        Log::Write(Log::LT_DEBUG, CACHEGATE_CHANNEL_FILE, 126,
                   L"[%s], %s; composed relay header, fromWid:%u, toWid:%u, relayTid:0x%I64X, hint:%u, reserved:%I64u",
                   MODULE_NAME, L"CacheGateChannel::composeRelayHeader", relayHeader._fromWid, relayHeader._toWid,
                   relayHeader._relayTid, relayHeader._hint, relayHeader._reserved);
    else
        Log::Write(Log::LT_ERROR, CACHEGATE_CHANNEL_FILE, 123,
                   L"[%s], %s; failed to compose relay header, fromWid:%u, toWid:%u, relayTid:0x%I64X, hint:%u, reserved:%I64u",
                   MODULE_NAME, L"CacheGateChannel::composeRelayHeader", relayHeader._fromWid, relayHeader._toWid,
                   relayHeader._relayTid, relayHeader._hint, relayHeader._reserved);
    return result;
}

// 0x7410
__declspec(noinline) bool CacheGateChannel::combineFragmentRelayFormat(char* const relayFormat, unsigned long long const bufferSize,
                                                   char const* const economyFormat)
{
    if (relayFormat == nullptr || economyFormat == nullptr)  // LIFT: 0x7422 tests only relayFormat; LTCG made economyFormat the constant 0x14007acd0
    {
        Log::Write(Log::LT_ERROR, CACHEGATE_CHANNEL_FILE, 91,
                   L"== CRASH == [%s], %s; invalid parameter, relayFormat:0x%p, bufferSize:%d, economyFormat:0x%p",
                   MODULE_NAME, L"CacheGateChannel::combineFragmentRelayFormat", relayFormat, bufferSize, economyFormat);
        AlertSender::Write(CACHEGATE_CHANNEL_FILE, 91,
                           L"== CRASH == [%s], %s; invalid parameter, relayFormat:0x%p, bufferSize:%d, economyFormat:0x%p",
                           MODULE_NAME, L"CacheGateChannel::combineFragmentRelayFormat", relayFormat, bufferSize, economyFormat);
        return false;
    }

    unsigned long long const formatLength = strlen(relayFormat) + strlen(economyFormat);
    if (formatLength >= bufferSize)
    {
        Log::Write(Log::LT_ERROR, CACHEGATE_CHANNEL_FILE, 97, L"[%s], %s; format length overflow, formatLength:%d",
                   MODULE_NAME, L"CacheGateChannel::combineFragmentRelayFormat", formatLength);
        return false;
    }

    if (strncat_s(relayFormat, bufferSize, economyFormat, strlen(economyFormat)) != 0)
    {
        Log::Write(Log::LT_ERROR, CACHEGATE_CHANNEL_FILE, 102, L"[%s], %s; failed to append economy packet format",
                   MODULE_NAME, L"CacheGateChannel::combineFragmentRelayFormat");
        return false;
    }
    return true;
}

// 0x7000
bool CacheGateChannel::SendRelayRequest(RelayContext const* const relayContext)
{
    if (relayContext == nullptr)
    {
        Log::Write(Log::LT_ERROR, CACHEGATE_CHANNEL_FILE, 42, L"== CRASH == [%s], %s; invalid parameter, relayContext:0x%p",
                   MODULE_NAME, L"CacheGateChannel::SendRelayRequest", static_cast<RelayContext*>(nullptr));
        AlertSender::Write(CACHEGATE_CHANNEL_FILE, 42, L"== CRASH == [%s], %s; invalid parameter, relayContext:0x%p",
                           MODULE_NAME, L"CacheGateChannel::SendRelayRequest",
                           static_cast<RelayContext*>(nullptr));
        return false;
    }

    Packet packet = {};  // LIFT: inlined constructor
    packet.Allocate();
    if (composeRelayHeader(packet, relayContext->MakeRelayHeader()) && relayContext->ComposeRequestPacket(packet))
    {
        Session const* const session = GetSession();
        if (session != nullptr)
        {
            session->Send(&packet);
            const_cast<Session*>(session)->removeReferenceCount(CHANNEL_HEADER_FILE, 52);
        }
        packet.Clear();
        return true;
    }
    packet.Clear();
    return false;
}

// 0x71e0
bool CacheGateChannel::SendFragmentRelayRequest(RelayContext const* const relayContext, char const* const economyFormat)
{
    if (relayContext == nullptr)
    {
        Log::Write(Log::LT_ERROR, CACHEGATE_CHANNEL_FILE, 63,
                   L"== CRASH == [%s], %s; invalid parameter, relayContext:0x%p, economyFormat:0x%p",
                   MODULE_NAME, L"CacheGateChannel::SendFragmentRelayRequest",
                   static_cast<RelayContext*>(nullptr), economyFormat);
        AlertSender::Write(CACHEGATE_CHANNEL_FILE, 63,
                           L"== CRASH == [%s], %s; invalid parameter, relayContext:0x%p, economyFormat:0x%p",
                           MODULE_NAME, L"CacheGateChannel::SendFragmentRelayRequest",
                           static_cast<RelayContext*>(nullptr), economyFormat);
        return false;
    }

    char relayFormat[256] = "hihhqhq";
    if (!combineFragmentRelayFormat(relayFormat, sizeof(relayFormat), economyFormat))
        return false;

    FragmentPacket packet(9, relayFormat);
    if (!composeRelayHeader(packet, relayContext->MakeRelayHeader()) || !relayContext->ComposeRequestPacket(packet))
    {
        packet.packet.Clear();
        return false;
    }

    if (packet.packet.Splitter != nullptr)
        packet.packet.Splitter->Finalize(packet.packet.CurHeader);
    // BUG: 0x71e0 the session reference from GetSession is not released.
    if (GetSession() != nullptr)
        Send(&packet.packet);
    packet.packet.Clear();
    return true;
}

// 0x7740
bool CacheGateChannelManager::initChannelManager()
{
    if (_cachegateChannel == nullptr)
        return true;
    Log::Write(Log::LT_ERROR, CACHEGATE_CHANNEL_FILE, 155,
               L"== CRASH == [%s], %s; cachegate channel manager is already initialized, cachegateChannel:0x%p",
               L"cachegate channel", L"CacheGateChannelManager::initChannelManager", _cachegateChannel);
    AlertSender::Write(CACHEGATE_CHANNEL_FILE, 155,
                       L"== CRASH == [%s], %s; cachegate channel manager is already initialized, cachegateChannel:0x%p",
                       L"cachegate channel", L"CacheGateChannelManager::initChannelManager", _cachegateChannel);
    return false;
}

// 0x77e0
bool CacheGateChannelManager::SetCacheGateChannel(CacheGateChannel* const cachegateChannel)
{
    if (cachegateChannel == nullptr)
    {
        Log::Write(Log::LT_ERROR, CACHEGATE_CHANNEL_FILE, 179,
                   L"== CRASH == [%s], %s; invalid parameter, cachegateChannel:0x%p", L"cachegate channel",
                   L"CacheGateChannelManager::SetCacheGateChannel", static_cast<CacheGateChannel*>(nullptr));
        AlertSender::Write(CACHEGATE_CHANNEL_FILE, 179, L"== CRASH == [%s], %s; invalid parameter, cachegateChannel:0x%p",
                           L"cachegate channel", L"CacheGateChannelManager::SetCacheGateChannel",
                           static_cast<CacheGateChannel*>(nullptr));
        return false;
    }

    _lock.Enter();
    if (_cachegateChannel != nullptr)
    {
        _lock.Leave();
        Log::Write(Log::LT_ERROR, CACHEGATE_CHANNEL_FILE, 186,
                   L"[%s], %s; cachegate channel is already set, cachegateChannel:0x%p", L"cachegate channel",
                   L"CacheGateChannelManager::SetCacheGateChannel", _cachegateChannel);
        return false;
    }
    cachegateChannel->addReferenceCount(CACHEGATE_CHANNEL_FILE, 190);
    _cachegateChannel = cachegateChannel;
    _lock.Leave();
    return true;
}

// 0x7900
bool CacheGateSessionHandler::OnAccept(Session const* session) const
{
    unsigned long long const sessionId = session->_id;
    Log::Write(Log::LT_ERROR, CACHEGATE_CHANNEL_FILE, 235,
               L"[%s], %s; cannot use CacheGateSessionHandler::OnAccept handler, sessionId:0x%I64X, portId:%u, sessionIndex:%u",
               L"cachegate channel", L"CacheGateSessionHandler::OnAccept", sessionId,
               static_cast<unsigned int>(sessionId >> 32), static_cast<unsigned int>(sessionId));
    return false;
}

// 0x7960
bool CacheGateSessionHandler::OnConnect(Session const* session, bool firstConnected) const
{
    unsigned long long const sessionId = session->_id;
    if (firstConnected)
        Log::Write(Log::LT_NOTICE, CACHEGATE_CHANNEL_FILE, 242,
                   L"[%s], %s; connected to cachegate, sessionId:0x%I64X, portId:%u, sessionIndex:%u",
                   L"cachegate channel", L"CacheGateSessionHandler::OnConnect", sessionId,
                   static_cast<unsigned int>(sessionId >> 32), static_cast<unsigned int>(sessionId));
    else
        Log::Write(Log::LT_NOTICE, CACHEGATE_CHANNEL_FILE, 244,
                   L"[%s], %s; reconnected to cachegate, sessionId:0x%I64X, portId:%u, sessionIndex:%u",
                   L"cachegate channel", L"CacheGateSessionHandler::OnConnect", sessionId,
                   static_cast<unsigned int>(sessionId >> 32), static_cast<unsigned int>(sessionId));

    Channel* const channel = session->GetChannel();
    if (channel == nullptr)
    {
        Log::Write(Log::LT_ERROR, CACHEGATE_CHANNEL_FILE, 249,
                   L"[%s], %s; cachegate channel is null, cachegateChannel:0x%p, sessionId:0x%I64X, portId:%u, sessionIndex:%u",
                   L"cachegate channel", L"CacheGateSessionHandler::OnConnect", static_cast<Channel*>(nullptr),
                   sessionId, static_cast<unsigned int>(sessionId >> 32), static_cast<unsigned int>(sessionId));
        return false;
    }
    channel->removeReferenceCount(CACHEGATE_CHANNEL_FILE, 252);

    PostOfficeDaemon* const daemon = PostOfficeDaemon::_instance;
    if (daemon->pipeConsole != nullptr)
        daemon->pipeConsole->SetInvalidInfo(DISCONNECTED_CACHEGATE, false);

    // 0x7a75-0x7a95: Send("hhhh" 0x74388, 1, 4, 0xA, word [daemon+0x750]).
    session->Send("hhhh", CacheGate_HelloCmd, 4, 10, daemon->_serviceWid);
    Log::Write(Log::LT_NOTICE, CACHEGATE_CHANNEL_FILE, 261,
               L"[%s], %s; sent hello request to cachegate, cachegate-packet-version:%d, economy-common-packet-version:%d, postofficeServiceWid:%u",
               L"cachegate channel", L"CacheGateSessionHandler::OnConnect", 4, 10, daemon->_serviceWid);
    return true;
}

// 0x7b50
void CacheGateSessionHandler::OnClose(Session const* session, bool tryReconnect) const
{
    unsigned long long const sessionId = session->_id;
    Log::Write(Log::LT_NOTICE, CACHEGATE_CHANNEL_FILE, 268,
               L"[%s], %s; closed connection with cachegate, sessionId:0x%I64X, portId:%u, sessionIndex:%u",
               L"cachegate channel", L"CacheGateSessionHandler::OnClose", sessionId,
               static_cast<unsigned int>(sessionId >> 32), static_cast<unsigned int>(sessionId));

    PostOfficeDaemon* const daemon = PostOfficeDaemon::_instance;
    Channel* const channel = session->GetChannel();
    if (channel != nullptr)
    {
        static_cast<CacheGateChannel*>(channel)->SetServiceState(CacheGateChannel::SERVICE_STATE_UNAVAILABLE);
        if (!tryReconnect)
        {
            // LIFT: inlined CacheGateChannelManager release (log line 202). The name is not in the PDB.
            CacheGateChannelManager* const manager = daemon->_cachegateChannelManager;
            manager->_lock.Enter();
            if (manager->_cachegateChannel != nullptr)
            {
                manager->_cachegateChannel->removeReferenceCount(CACHEGATE_CHANNEL_FILE, 202);
                manager->_cachegateChannel = nullptr;
            }
            manager->_lock.Leave();
            channel->RemoveSession(session, false);
        }
        channel->removeReferenceCount(CACHEGATE_CHANNEL_FILE, 277);
    }

    daemon->_cachedWatchdogManager->SetAllServiceState(CachedWatchdog::SERVICE_STATE_UNAVAILABLE);  // 0x7cae; LTCG folded the value into 0x4a50 (r12d = 0 at 0x4a78)

    if (tryReconnect)
        Log::Write(Log::LT_DEBUG, CACHEGATE_CHANNEL_FILE, 284,
                   L"[%s], %s; reconnecting to cachegate, sessionId:0x%I64X, portId:%u, sessionIndex:%u",
                   L"cachegate channel", L"CacheGateSessionHandler::OnClose", sessionId,
                   static_cast<unsigned int>(sessionId >> 32), static_cast<unsigned int>(sessionId));

    // LIFT: inlined search and addNode; same logic as SetInvalidInfo(key, true).
    if (daemon->pipeConsole != nullptr)
        daemon->pipeConsole->SetInvalidInfo(DISCONNECTED_CACHEGATE, true);
}

// 0x7d90
bool CacheGateSessionHandler::PacketHandler(Session const* session, Packet const* packet) const
{
    void* iocpHandle = nullptr;
    short const* const pCmd = &packet->CurHeader[1].size;
    if (pCmd == nullptr)
    {
        Log::Write(Log::LT_ERROR, CACHEGATE_CHANNEL_FILE, 295,
                   L"[%s], %s; invalid packet; command is null, cmd:0x%p, sessionId:0x%I64X, portId:%u, sessionIndex:%u",
                   MODULE_NAME, L"CacheGateSessionHandler::PacketHandler", static_cast<void*>(nullptr), session->_id,
                   static_cast<unsigned int>(session->_id >> 32), static_cast<unsigned int>(session->_id));
        return false;
    }

    if (*pCmd <= 0 || *pCmd >= 10 || CacheGatePacketClientSideHandlerList[*pCmd] == nullptr)
    {
        Log::Write(Log::LT_ERROR, CACHEGATE_CHANNEL_FILE, 305,
                   L"[%s], %s; invalid cachegate packet command, command:%d, sessionId:0x%I64X, portId:%u, sessionIndex:%u",
                   MODULE_NAME, L"CacheGateSessionHandler::PacketHandler", static_cast<int>(*pCmd), session->_id,
                   static_cast<unsigned int>(session->_id >> 32), static_cast<unsigned int>(session->_id));
        return false;
    }

    // LIFT: LTCG folded the event id and the offset. The values come from the LobbyGate call.
    iocpHandle = Network::iocpHandle();
    return TFPP_PumpPacket(PostOfficeDaemon::POSTEVENT_PACKET_PUMP_EVENT, iocpHandle, session, packet, *pCmd, 0,
                           CacheGatePacketClientSideHandlerList, CacheGatePacketClientSideFragmentHandlerList);
}
