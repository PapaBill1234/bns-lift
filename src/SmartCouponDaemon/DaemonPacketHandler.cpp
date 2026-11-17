// DaemonPacketHandler.obj (SmartCouponDaemon PDB). Source: .scratch/hr/DaemonPacketHandler.c
#include "DaemonChannel.h"

#include <winsock2.h>
#include <windows.h>
#include <new>

#include "AlertSender.h"
#include "Connection.h"
#include "CouponGameEventConfig.h"
#include "GameEventWorker.h"
#include "Log.h"
#include "Memory.h"
#include "MemoryManager.h"
#include "Network.h"
#include "Packet.h"
#include "Session.h"
#include "SmartCouponDB.h"
#include "SmartCouponDaemon.h"

static wchar_t const DAEMONPACKETHANDLER_FILE[] = L"DaemonPacketHandler.cpp";
static wchar_t const SESSION_SOURCE_FILE[] = L"source\\Session.cpp";
static wchar_t const CHANNEL_H_FILE[] =
    L"E:\\DailyBuild02\\SmartCouponDaemon-Common-0.0.348\\depot\\Branch\\348NC\\Program\\Server\\BloodLib\\include\\Channel.h";

static short const SMARTCOUPON_PACKET_VERSION = 1;  // ❓ name

// ❓ The guid prints as DWORD, WORD, WORD and 8 bytes.
#define GUID_ARGS(g)                                                                                               \
    *reinterpret_cast<unsigned int const*>(&(g).guid[0]), *reinterpret_cast<unsigned short const*>(&(g).guid[4]), \
        *reinterpret_cast<unsigned short const*>(&(g).guid[6]), (g).guid[8], (g).guid[9], (g).guid[10],            \
        (g).guid[11], (g).guid[12], (g).guid[13], (g).guid[14], (g).guid[15]

// 0x7d30
unsigned long long DChannel::GetId()
{
    return static_cast<unsigned int>(((_daemonId._wid + (_daemonId._type << 16)) << 8) + _daemonId._reserved);
}

// 0x7d50
DChannel::~DChannel()
{
}

// 0x7d80
unsigned int GameEventLogEvent::EventId() const
{
    return 128;
}

// 0x7dc0
bool HandleSmartCoupon_HelloReq(Session const* session, Packet const* packet)
{
    short cmd = 0;
    short packetVersion = 0;
    int daemonType = 0;  // ❓ PDB type SmartCouponDaemonType
    short worldId = 0;
    unsigned short internalPort = 0;

    Channel* channel = session->GetChannel();
    if (channel != nullptr)
    {
        // BUG: 0x7DC0 the channel reference from GetChannel is not released.
        Log::Write(Log::LT_ERROR, DAEMONPACKETHANDLER_FILE, 36, L"already authed session, session:0x%.16I64X",
                   session->_id);
        return false;
    }

    if (packet->Decompose("hhQhh", &cmd, &packetVersion, &daemonType, &worldId, &internalPort) == 0)
    {
        Log::Write(Log::LT_ERROR, DAEMONPACKETHANDLER_FILE, 41, L"failed to decompose packet");
        session->Send("hh", 3, 2);
        return false;
    }

    if (packetVersion != SMARTCOUPON_PACKET_VERSION)
    {
        Log::Write(Log::LT_ERROR, DAEMONPACKETHANDLER_FILE, 48,
                   L"invalid packet version, world-id:%d, packet-version:%d, client version:%d", worldId,
                   SMARTCOUPON_PACKET_VERSION, packetVersion);
        session->Send("hh", 3, 9);
        return false;
    }

    if (!SmartCouponDaemon::_instance->_serviceAvailable)
    {
        Log::Write(Log::LT_ERROR, DAEMONPACKETHANDLER_FILE, 55,
                   L"service not available, packet-version:%d, daemon-type:%s(%d), world-id:%d, internal-port:%d",
                   SMARTCOUPON_PACKET_VERSION, SmartCouponDaemonTypeDesc[daemonType], daemonType, worldId,
                   internalPort);
        session->Send("hh", 3, 8);
        return false;
    }

    Log::Write(Log::LT_DEBUG, DAEMONPACKETHANDLER_FILE, 60,
               L"decomposed packet, packet-version:%d, daemon-type:%s(%d), world-id:%d, internal-port:%d",
               SMARTCOUPON_PACKET_VERSION, SmartCouponDaemonTypeDesc[daemonType], daemonType, worldId, internalPort);

    GameEventDaemonId daemonId;
    daemonId._type = static_cast<unsigned char>(daemonType);
    daemonId._wid = worldId;
    daemonId._reserved = 0;
    DChannel* daemon = SmartCouponDaemon::_instance->_daemonChannelMgr->FindDaemon(&daemonId);
    if (daemon == nullptr)
    {
        Log::Write(Log::LT_ERROR, DAEMONPACKETHANDLER_FILE, 65, L"register world fail, not capable world, world-id:%d",
                   worldId);
        session->Send("hh", 3, 2);
        return false;
    }

    unsigned long ip = session->_connection->_ip;
    if (daemon->_addr != ip)
    {
        wchar_t acc[16];
        wchar_t exp[16];
        wcscpy_s(acc, 15, Network::GetAddressStringW(ip));
        wcscpy_s(exp, 15, Network::GetAddressStringW(daemon->_addr));
        Log::Write(Log::LT_ERROR, DAEMONPACKETHANDLER_FILE, 74,
                   L"register world fail, ip validation fail, world-id:%d, ip:%s, required-ip:%s ", worldId, acc, exp);
        session->Send("hh", 3, 11);
        daemon->removeReferenceCount(DAEMONPACKETHANDLER_FILE, 76);
        return false;
    }

    Session const* oldSession = daemon->GetSession();
    if (oldSession != nullptr)
    {
        Log::Write(Log::LT_ERROR, DAEMONPACKETHANDLER_FILE, 89,
                   L"register world fail, session already exists, old-session:0x%016I64X", oldSession->_id);
        void* mem = Memory::_Manager[2]->Alloc(sizeof(DChannel), DAEMONPACKETHANDLER_FILE, 92);
        DChannel* newDaemon = nullptr;
        if (mem != nullptr)
        {
            GameEventDaemonId newId;
            newId._type = daemon->_daemonId._type;
            newId._wid = daemon->_daemonId._wid;
            newId._reserved = 0;
            newDaemon = new (mem) DChannel(newId, daemon->_addr, daemon->_port);
        }
        // BUG: 0x81BD the old daemon is passed to ReplaceDaemon, not newDaemon.
        if (!SmartCouponDaemon::_instance->_daemonChannelMgr->ReplaceDaemon(daemon))
        {
            Log::Write(Log::LT_ERROR, DAEMONPACKETHANDLER_FILE, 95,
                       L"== CRASH == replace world channel fail, worldId:%d", daemon->_daemonId._wid);
            AlertSender::Write(DAEMONPACKETHANDLER_FILE, 95, L"== CRASH == replace world channel fail, worldId:%d",
                               daemon->_daemonId._wid);
        }
        daemon->Close();
        Log::Write(Log::LT_DEBUG, DAEMONPACKETHANDLER_FILE, 100, L"close old session, old-session:0x%016I64X",
                   oldSession->_id);
        session->Send("hh", 3, 13);
        // BUG: 0x7DC0 no null check of newDaemon when the alloc fails.
        newDaemon->removeReferenceCount(DAEMONPACKETHANDLER_FILE, 104);
        const_cast<Session*>(oldSession)->removeReferenceCount(CHANNEL_H_FILE, 52);
        daemon->removeReferenceCount(DAEMONPACKETHANDLER_FILE, 106);
        return false;
    }

    daemon->SetSession(session);
    session->Send("h", 2);
    int wid = daemon->_daemonId._wid;
    Log::Write(Log::LT_NOTICE, DAEMONPACKETHANDLER_FILE, 113, L"hello success, daemon-type:%s(%d), wid:%d, ip:%s",
               SmartCouponDaemonTypeDesc[daemonType], daemonType, wid, Network::GetAddressStringW(daemon->_addr));
    daemon->removeReferenceCount(DAEMONPACKETHANDLER_FILE, 115);
    return true;
}

// 0x8360
bool HandleSmartCoupon_GameEventByCharacterReq(Session const* session, Packet const* packet)
{
    DChannel* channel = static_cast<DChannel*>(session->GetChannel());
    if (channel == nullptr)
    {
        Log::Write(Log::LT_ERROR, DAEMONPACKETHANDLER_FILE, 123,
                   L"[packet], 0x%.16I64X, %I64d, not authed session, session:0x%.16I64X", session->_id, 0LL,
                   session->_id);
        return false;
    }

    short cmd = 0;
    unsigned long long tid = 0;
    void* mem = Memory::_Manager[2]->Alloc(sizeof(GameEventLogEvent), DAEMONPACKETHANDLER_FILE, 134);
    GameEventLogEvent* event = mem != nullptr ? new (mem) GameEventLogEvent() : nullptr;
    // BUG: 0x8360 no null check of the alloc result.
    event->_eventTargetType = 2;

    short failReason;
    if (packet->Decompose("hqiohq", &cmd, &tid, &event->_gameEventId, &event->_gameAccountId, &event->_wid,
                          &event->_pcdbid) == 0)
    {
        Log::Write(Log::LT_ERROR, DAEMONPACKETHANDLER_FILE, 140, L"[packet], 0x%.16I64X, %I64d, failed to decompose packet",
                   session->_id, channel->GetId());
        failReason = 2;
    }
    else if ((event->_gameAccountId.id[0] == 0 && event->_gameAccountId.id[1] == 0) || event->_wid <= 0 ||
             event->_wid != static_cast<short>(channel->_daemonId._wid) || event->_pcdbid <= 0 ||
             event->_gameEventId <= 0)
    {
        Log::Write(Log::LT_ERROR, DAEMONPACKETHANDLER_FILE, 155,
                   L"[packet], 0x%.16I64X, %I64d, invalid parameter, cmd:%d, wid:%d, channel-tid:0x%.16I64X, "
                   L"account-id:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X, pcdbid:0x%I64X, game-event-id:%d",
                   session->_id, channel->GetId(), cmd, channel->_daemonId._wid, tid,
                   GUID_ARGS(event->_gameAccountId), event->_pcdbid, event->_gameEventId);
        failReason = 7;
    }
    else
    {
        GameEventConfig::GameEventInfo* info =
            SmartCouponDaemon::_instance->_gameEventConfig->FindGameEventInfo(event->_gameEventId);
        if (info == nullptr)
        {
            Log::Write(Log::LT_ERROR, DAEMONPACKETHANDLER_FILE, 164,
                       L"[packet], 0x%.16I64X, %I64d, invalid game event id, cmd:%d, wid:%d, channel-tid:0x%.16I64X, "
                       L"account-id:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X, pcdbid:0x%I64X, game-event-id:%d",
                       session->_id, channel->GetId(), cmd, channel->_daemonId._wid, tid,
                       GUID_ARGS(event->_gameAccountId), event->_pcdbid, event->_gameEventId);
            failReason = 7;
        }
        else if (info->daemonType != channel->_daemonId._type)
        {
            Log::Write(Log::LT_ERROR, DAEMONPACKETHANDLER_FILE, 170,
                       L"[packet], 0x%.16I64X, %I64d, invalid daemon type, cmd:%d, wid:%d, channel-tid:0x%.16I64X, "
                       L"account-id:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X, pcdbid:0x%I64X, game-event-id:%d, "
                       L"config-type:%d, channel-type:%d",
                       session->_id, channel->GetId(), cmd, channel->_daemonId._wid, tid,
                       GUID_ARGS(event->_gameAccountId), event->_pcdbid, event->_gameEventId,
                       static_cast<int>(info->daemonType), static_cast<int>(channel->_daemonId._type));
            failReason = 7;
        }
        else
        {
            Log::Write(Log::LT_DEBUG, DAEMONPACKETHANDLER_FILE, 175,
                       L"[packet], 0x%.16I64X, %I64d, decomposed packet, cmd:%d, wid:%d, channel-tid:0x%.16I64X, "
                       L"account-id:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X, pcdbid:0x%I64X, game-event-id:%d",
                       session->_id, channel->GetId(), cmd, channel->_daemonId._wid, tid,
                       GUID_ARGS(event->_gameAccountId), event->_pcdbid, event->_gameEventId);
            int dbRetValue = 0;
            if (!SmartCouponDB::RegisterGameEventLog(&dbRetValue, &event->_gameAccountId, event->_wid, event->_pcdbid,
                                                     event->_gameEventId, &event->_gameEventLogId))
            {
                Log::Write(Log::LT_ERROR, DAEMONPACKETHANDLER_FILE, 183,
                           L"[packet], 0x%.16I64X, %I64d, failed to register game event log in db, cmd:%d, wid:%d, "
                           L"channel-tid:0x%.16I64X, account-id:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X, "
                           L"pcdbid:0x%I64X, game-event-id:%d, dbRetValue:%d",
                           session->_id, channel->GetId(), cmd, channel->_daemonId._wid, tid,
                           GUID_ARGS(event->_gameAccountId), event->_pcdbid, event->_gameEventId, dbRetValue);
                failReason = 6;
            }
            else
            {
                Packet p;
                p.Allocate();
                p.Compose("hqq", 5, tid, event->_gameEventLogId);
                session->Send(&p);  // inlined encrypt and send (0xFA40)
                Log::Write(Log::LT_DEBUG, DAEMONPACKETHANDLER_FILE, 202,
                           L"[packet], 0x%.16I64X, %I64d, register game event log, success, cmd:%d, wid:%d, "
                           L"channel-tid:0x%.16I64X, account-id:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X, "
                           L"pcdbid:0x%I64X, game-event-id:%d, log-id:%I64d",
                           session->_id, channel->GetId(), cmd, channel->_daemonId._wid, tid,
                           GUID_ARGS(event->_gameAccountId), event->_pcdbid, event->_gameEventId,
                           event->_gameEventLogId);
                p.Clear();
                if (GameEventManager::Instance != nullptr && GameEventManager::Instance->_gameEventHandle != nullptr)
                {
                    PostQueuedCompletionStatus(GameEventManager::Instance->_gameEventHandle, 0,
                                               reinterpret_cast<ULONG_PTR>(event), nullptr);
                    channel->removeReferenceCount(SESSION_SOURCE_FILE, 1059);
                    return true;
                }
                // BUG: 0x8360 the event and the channel reference leak here.
                // BUG: 0x8360 the format has no session and id fields, so the args shift by two.
                Log::Write(Log::LT_ERROR, DAEMONPACKETHANDLER_FILE, 210,
                           L"game-event-by-char, game event handle is null, cmd:%d, wid:%d, channel-tid:0x%.16I64X, "
                           L"account-id:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X, pcdbid:0x%I64X, game-event-id:%d",
                           static_cast<int>(cmd), static_cast<int>(channel->_daemonId._wid), tid,
                           GUID_ARGS(event->_gameAccountId), event->_pcdbid, event->_gameEventId);
                return true;
            }
        }
    }

    // BUG: 0x8360 the event leaks on each failure path.
    session->Send("hqE", 6, tid, static_cast<int>(failReason));
    Log::Write(Log::LT_ERROR, DAEMONPACKETHANDLER_FILE, 221,
               L"[packet], 0x%.16I64X, %I64d, sent game-event-by-char failure ack, cmd:%d, wid:%d, channel-tid:0x%.16I64X, "
               L"account-id:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X, pcdbid:0x%I64X, game-event-id:%d, "
               L"failReason:%d",
               session->_id, channel->GetId(), cmd, channel->_daemonId._wid, tid, GUID_ARGS(event->_gameAccountId),
               event->_pcdbid, event->_gameEventId, static_cast<int>(failReason));
    channel->removeReferenceCount(SESSION_SOURCE_FILE, 1059);
    return true;
}

// 0x8e80
bool HandleSmartCoupon_GameEventByAccountReq(Session const* session, Packet const* packet)
{
    DChannel* channel = static_cast<DChannel*>(session->GetChannel());
    if (channel == nullptr)
    {
        Log::Write(Log::LT_ERROR, DAEMONPACKETHANDLER_FILE, 231,
                   L"[packet], 0x%.16I64X, %I64d, not authed session, session:0x%.16I64X", session->_id, 0LL,
                   session->_id);
        return false;
    }

    short cmd = 0;
    unsigned long long tid = 0;
    void* mem = Memory::_Manager[2]->Alloc(sizeof(GameEventLogEvent), DAEMONPACKETHANDLER_FILE, 242);
    GameEventLogEvent* event = mem != nullptr ? new (mem) GameEventLogEvent() : nullptr;
    // BUG: 0x8E80 no null check of the alloc result.
    event->_eventTargetType = 1;

    short failReason;
    if (packet->Decompose("hqio", &cmd, &tid, &event->_gameEventId, &event->_gameAccountId) == 0)
    {
        Log::Write(Log::LT_ERROR, DAEMONPACKETHANDLER_FILE, 248, L"[packet], 0x%.16I64X, %I64d, failed to decompose packet",
                   session->_id, channel->GetId());
        failReason = 2;
    }
    else if ((event->_gameAccountId.id[0] == 0 && event->_gameAccountId.id[1] == 0) || event->_gameEventId <= 0)
    {
        Log::Write(Log::LT_ERROR, DAEMONPACKETHANDLER_FILE, 262,
                   L"[packet], 0x%.16I64X, %I64d, invalid parameter, cmd:%d, wid:%d, channel-tid:0x%.16I64X, "
                   L"account-id:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X, game-event-id:%d",
                   session->_id, channel->GetId(), cmd, channel->_daemonId._wid, tid,
                   GUID_ARGS(event->_gameAccountId), event->_gameEventId);
        failReason = 7;
    }
    else
    {
        GameEventConfig::GameEventInfo* info =
            SmartCouponDaemon::_instance->_gameEventConfig->FindGameEventInfo(event->_gameEventId);
        if (info == nullptr)
        {
            Log::Write(Log::LT_ERROR, DAEMONPACKETHANDLER_FILE, 271,
                       L"[packet], 0x%.16I64X, %I64d, invalid game event id, cmd:%d, wid:%d, channel-tid:0x%.16I64X, "
                       L"account-id:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X, game-event-id:%d",
                       session->_id, channel->GetId(), cmd, channel->_daemonId._wid, tid,
                       GUID_ARGS(event->_gameAccountId), event->_gameEventId);
            failReason = 7;
        }
        else if (info->daemonType != channel->_daemonId._type)
        {
            Log::Write(Log::LT_ERROR, DAEMONPACKETHANDLER_FILE, 277,
                       L"[packet], 0x%.16I64X, %I64d, invalid daemon type, cmd:%d, wid:%d, channel-tid:0x%.16I64X, "
                       L"account-id:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X, game-event-id:%d, config-type:%d, "
                       L"channel-type:%d",
                       session->_id, channel->GetId(), cmd, channel->_daemonId._wid, tid,
                       GUID_ARGS(event->_gameAccountId), event->_gameEventId, static_cast<int>(info->daemonType),
                       static_cast<int>(channel->_daemonId._type));
            failReason = 7;
        }
        else
        {
            Log::Write(Log::LT_DEBUG, DAEMONPACKETHANDLER_FILE, 282,
                       L"[packet], 0x%.16I64X, %I64d, decomposed packet, cmd:%d, wid:%d, channel-tid:0x%.16I64X, "
                       L"account-id:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X, game-event-id:%d",
                       session->_id, channel->GetId(), cmd, channel->_daemonId._wid, tid,
                       GUID_ARGS(event->_gameAccountId), event->_gameEventId);
            int dbRetValue = 0;
            if (!SmartCouponDB::RegisterGameEventLog(&dbRetValue, &event->_gameAccountId, event->_wid, event->_pcdbid,
                                                     event->_gameEventId, &event->_gameEventLogId))
            {
                Log::Write(Log::LT_ERROR, DAEMONPACKETHANDLER_FILE, 289,
                           L"[packet], 0x%.16I64X, %I64d, failed to register game event log in db, cmd:%d, wid:%d, "
                           L"channel-tid:0x%.16I64X, account-id:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X, "
                           L"game-event-id:%d, dbRetValue:%d",
                           session->_id, channel->GetId(), cmd, channel->_daemonId._wid, tid,
                           GUID_ARGS(event->_gameAccountId), event->_gameEventId, dbRetValue);
                failReason = 6;
            }
            else
            {
                Packet p;
                p.Allocate();
                p.Compose("hqq", 8, tid, event->_gameEventLogId);
                session->Send(&p);  // inlined encrypt and send (0xFA40)
                Log::Write(Log::LT_DEBUG, DAEMONPACKETHANDLER_FILE, 308,
                           L"[packet], 0x%.16I64X, %I64d, register game event log, success, cmd:%d, wid:%d, "
                           L"channel-tid:0x%.16I64X, account-id:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X, "
                           L"game-event-id:%d, log-id:%I64d",
                           session->_id, channel->GetId(), cmd, channel->_daemonId._wid, tid,
                           GUID_ARGS(event->_gameAccountId), event->_gameEventId, event->_gameEventLogId);
                p.Clear();
                if (GameEventManager::Instance != nullptr && GameEventManager::Instance->_gameEventHandle != nullptr)
                {
                    PostQueuedCompletionStatus(GameEventManager::Instance->_gameEventHandle, 0,
                                               reinterpret_cast<ULONG_PTR>(event), nullptr);
                    channel->removeReferenceCount(SESSION_SOURCE_FILE, 1059);
                    return true;
                }
                // BUG: 0x8E80 the event and the channel reference leak here.
                // BUG: 0x8E80 the log text says game-event-by-char.
                Log::Write(Log::LT_ERROR, DAEMONPACKETHANDLER_FILE, 316,
                           L"game-event-by-char, game event handle is null, cmd:%d, wid:%d, channel-tid:0x%.16I64X, "
                           L"account-id:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X, game-event-id:%d",
                           static_cast<int>(cmd), static_cast<int>(channel->_daemonId._wid), tid,
                           GUID_ARGS(event->_gameAccountId), event->_gameEventId);
                return true;
            }
        }
    }

    // BUG: 0x8E80 the event leaks on each failure path.
    session->Send("hqE", 9, tid, static_cast<int>(failReason));
    Log::Write(Log::LT_ERROR, DAEMONPACKETHANDLER_FILE, 327,
               L"[packet], 0x%.16I64X, %I64d, sent game-event-by-acc failure ack, cmd:%d, wid:%d, channel-tid:0x%.16I64X, "
               L"account-id:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X, game-event-id:%d, failReason:%d",
               session->_id, channel->GetId(), cmd, channel->_daemonId._wid, tid, GUID_ARGS(event->_gameAccountId),
               event->_gameEventId, static_cast<int>(failReason));
    channel->removeReferenceCount(SESSION_SOURCE_FILE, 1059);
    return true;
}
