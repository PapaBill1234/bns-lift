// ManagerPacketHandler.obj (SmartCouponDaemon PDB).
#include "ManagerChannel.h"

#include <winsock2.h>
#include <windows.h>
#include <new>

#include "AlertSender.h"
#include "GameEventWorker.h"
#include "Log.h"
#include "Memory.h"
#include "MemoryManager.h"
#include "Packet.h"
#include "Session.h"
#include "SmartCouponDB.h"
#include "SmartCouponDaemon.h"
#include "SmartCouponManagerPacketCommand.h"

static wchar_t const MANAGERPACKETHANDLER_FILE[] = L"ManagerPacketHandler.cpp";
static wchar_t const SESSION_SOURCE_FILE[] = L"source\\Session.cpp";

static int const SMARTCOUPONMANAGER_PACKET_VERSION = 2;  // LIFT: No PDB symbol. The binary uses the literal.

// LIFT: lift macro, not in any PDB. The 11 id128::guid arguments of the "%08X-%04X-%04X-..." format.
#define GUID_ARGS(g)                                                                                               \
    (g).guid.id1, (g).guid.id2, (g).guid.id3, (g).guid.id4[0], (g).guid.id4[1], (g).guid.id4[2], (g).guid.id4[3], \
        (g).guid.id4[4], (g).guid.id4[5], (g).guid.id4[6], (g).guid.id4[7]

// 0xeec0
unsigned long long ManagerChannel::GetId()
{
    return _managerWid;
}

// 0xef00
unsigned int RetryCouponPublicationEvent::EventId() const
{
    return 130;
}

// 0xef40
bool HandleSmartCouponManager_HelloReq(Session const* session, Packet const* packet)
{
    short cmd = 0;
    short version = 0;
    unsigned short managerWid = 0;
    if (session == nullptr || packet == nullptr)
    {
        unsigned long long id = session != nullptr ? session->_id : 0;
        Log::Write(Log::LT_ERROR, MANAGERPACKETHANDLER_FILE, 37,
                   L"== CRASH == [mgr-ch], 0x%.16I64X, %I64d, invalid session or packet in helloreq", id, 0LL);
        AlertSender::Write(MANAGERPACKETHANDLER_FILE, 37,
                           L"== CRASH == [mgr-ch], 0x%.16I64X, %I64d, invalid session or packet in helloreq", id, 0LL);
        return false;
    }

    Channel* channel = session->GetChannel();
    short failReason = 0;
    if (channel != nullptr && channel->GetId() != 0)
    {
        Log::Write(Log::LT_ERROR, MANAGERPACKETHANDLER_FILE, 44, L"[mgr-ch], 0x%.16I64X, %I64d, already hello req",
                   session->_id, channel->GetId());
        failReason = 8;
    }
    else
    {
        if (packet->Decompose("hhh", &cmd, &version, &managerWid) == 0)
        {
            Log::Write(Log::LT_ERROR, MANAGERPACKETHANDLER_FILE, 53,
                       L"[mgr-ch], 0x%.16I64X, %I64d, failed to decompose packet, hello req", session->_id,
                       channel != nullptr ? channel->GetId() : 0ULL);
            failReason = 2;
        }
        else
        {
            Log::Write(Log::LT_DEBUG, MANAGERPACKETHANDLER_FILE, 59,
                       L"[mgr-ch], 0x%.16I64X, %I64d, decomposed packet, hello req, smartcouponmanger-packet-version:%d, "
                       L"managerWid:%u",
                       session->_id, channel != nullptr ? channel->GetId() : 0ULL, version, managerWid);
            if (version != SMARTCOUPONMANAGER_PACKET_VERSION)
            {
                Log::Write(Log::LT_ERROR, MANAGERPACKETHANDLER_FILE, 64,
                           L"[mgr-ch], 0x%.16I64X, %I64d, invalid packet version, hello req, my "
                           L"smartcouponmanger-packet-version:%d, client version:%d",
                           session->_id, channel != nullptr ? channel->GetId() : 0ULL, SMARTCOUPONMANAGER_PACKET_VERSION,
                           version);
                failReason = 9;
            }
            else
            {
                // BUG: 0xEF40 no null check of the alloc result.
                void* mem = Memory::_Manager[1]->Alloc(sizeof(ManagerChannel), MANAGERPACKETHANDLER_FILE, 69);
                ManagerChannel* managerChannel = new (mem) ManagerChannel(managerWid);
                managerChannel->SetSession(session);
                SmartCouponDaemon::SetManagerChannel(managerChannel);
                managerChannel->removeReferenceCount(MANAGERPACKETHANDLER_FILE, 75);
                session->Send("h", SmartCouponManager_HelloOkCmd);
                Log::Write(Log::LT_NOTICE, MANAGERPACKETHANDLER_FILE, 78,
                           L"[mgr-ch], 0x%.16I64X, %I64d, sent hello success ack, managerWid:%u", session->_id,
                           managerChannel->GetId(), managerWid);
                // BUG: 0xEF40 channel leaks a reference when it is not null and its id is 0.
                return true;
            }
        }
    }

    session->Send("hh", SmartCouponManager_HelloFailCmd, failReason);
    Log::Write(Log::LT_NOTICE, MANAGERPACKETHANDLER_FILE, 84,
               L"[mgr-ch], 0x%.16I64X, %I64d, sent hello failure ack, managerWid:%u, failReason:%d", session->_id,
               channel != nullptr ? channel->GetId() : 0ULL, managerWid, failReason);
    if (channel != nullptr)
        channel->removeReferenceCount(MANAGERPACKETHANDLER_FILE, 87);
    return false;
}

// 0xf2f0
bool HandleSmartCouponManager_RetryCouponPublicationReq(Session const* session, Packet const* packet)
{
    Channel* channel = session->GetChannel();
    if (channel == nullptr)
    {
        Log::Write(Log::LT_ERROR, MANAGERPACKETHANDLER_FILE, 96,
                   L"[mgr-ch], 0x%.16I64X, %I64d, not authed session, session:0x%.16I64X", session->_id, 0ULL,
                   session->_id);
        return false;
    }

    short cmd = 0;
    // BUG: 0xF2F0 no null check of the alloc result.
    void* mem = Memory::_Manager[1]->Alloc(sizeof(RetryCouponPublicationEvent), MANAGERPACKETHANDLER_FILE, 106);
    RetryCouponPublicationEvent* event = new (mem) RetryCouponPublicationEvent();
    short failReason = 0;
    if (packet->Decompose("hqoq", &cmd, &event->_tid, &event->_gameAccountId, &event->_publicationId) == 0)
    {
        Log::Write(Log::LT_ERROR, MANAGERPACKETHANDLER_FILE, 112,
                   L"[mgr-ch], 0x%.16I64X, %I64d, failed to decompose packet", session->_id, channel->GetId());
        failReason = 2;
    }
    else if (event->_tid > 0 && (event->_gameAccountId.id[0] != ID128_GUID_ZERO.id[0] || event->_gameAccountId.id[1] != ID128_GUID_ZERO.id[1]) &&
             event->_publicationId > 0)
    {
        if (GameEventManager::Instance != nullptr && GameEventManager::Instance->_gameEventHandle != nullptr)
        {
            PostQueuedCompletionStatus(GameEventManager::Instance->_gameEventHandle, 0,
                                       reinterpret_cast<ULONG_PTR>(event), nullptr);
            channel->removeReferenceCount(SESSION_SOURCE_FILE, 1059);
            return true;
        }
        Log::Write(Log::LT_ERROR, MANAGERPACKETHANDLER_FILE, 128,
                   L"[mgr-ch], 0x%.16I64X, %I64d, game event handle is null, cmd:%d, tid:0x%.16I64X, "
                   L"account-id:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X, publication-id:0x%I64X",
                   session->_id, channel->GetId(), cmd, event->_tid, GUID_ARGS(event->_gameAccountId),
                   event->_publicationId);
        failReason = 2;
    }
    else
    {
        Log::Write(Log::LT_ERROR, MANAGERPACKETHANDLER_FILE, 119,
                   L"[mgr-ch], 0x%.16I64X, %I64d, invalid parameter, cmd:%d, tid:0x%.16I64X, "
                   L"account-id:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X, publication-id:0x%I64X",
                   session->_id, channel->GetId(), cmd, event->_tid, GUID_ARGS(event->_gameAccountId),
                   event->_publicationId);
        failReason = 7;
    }

    session->Send("hqE", SmartCouponManager_RetryCouponPublicationFailCmd, event->_tid, failReason);
    Log::Write(Log::LT_ERROR, MANAGERPACKETHANDLER_FILE, 140,
               L"[mgr-ch], 0x%.16I64X, %I64d, retry coupon publication failure ack, cmd:%d, tid:0x%.16I64X, "
               L"account-id:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X, publication-id:0x%I64X, failReason:%d",
               session->_id, channel->GetId(), cmd, event->_tid, GUID_ARGS(event->_gameAccountId),
               event->_publicationId, failReason);
    channel->removeReferenceCount(SESSION_SOURCE_FILE, 1059);
    // BUG: 0xF2F0 the event leaks on the failure path.
    return true;
}

// 0xf7f0
bool HandleSmartCouponManager_LoadRetryReadyGameEventLogListReq(Session const* session, Packet const* packet)
{
    Channel* channel = session->GetChannel();
    if (channel == nullptr)
    {
        Log::Write(Log::LT_ERROR, MANAGERPACKETHANDLER_FILE, 150,
                   L"[mgr-ch], 0x%.16I64X, %I64d, not authed session, session:0x%.16I64X", session->_id, 0ULL,
                   session->_id);
        return false;
    }

    RetrieveEventLogContext context(128);
    short cmd = 0;
    long long tid = 0;
    short failReason = 0;
    if (packet->Decompose("hq", &cmd, &tid) == 0)
    {
        Log::Write(Log::LT_ERROR, MANAGERPACKETHANDLER_FILE, 167,
                   L"[mgr-ch], 0x%.16I64X, %I64d, failed to decompose packet", session->_id, channel->GetId());
        failReason = 2;
    }
    else if (tid <= 0)
    {
        Log::Write(Log::LT_ERROR, MANAGERPACKETHANDLER_FILE, 174,
                   L"[mgr-ch], 0x%.16I64X, %I64d, invalid parameter, cmd:%d, tid:0x%.16I64X", session->_id,
                   channel->GetId(), cmd, tid);
        failReason = 7;
    }
    else
    {
        Log::Write(Log::LT_DEBUG, MANAGERPACKETHANDLER_FILE, 179,
                   L"load-retryready-game-event-log-list");
        int dbRetValue = 0;
        if (!SmartCouponDB::LoadRetryReadyGameEventLogList(&dbRetValue, &context))
        {
            Log::Write(Log::LT_ERROR, MANAGERPACKETHANDLER_FILE, 184,
                       L"[mgr-ch], 0x%.16I64X, %I64d, failed to LoadRetryReadyGameEventLogList, cmd:%d, "
                       L"tid:0x%.16I64X, dbRetValue:%d",
                       session->_id, channel->GetId(), cmd, tid, dbRetValue);
            failReason = 4;
        }
        else if (context._count > 0 && !GameEventManager::PostGameEventLogList(&context))
        {
            Log::Write(Log::LT_ERROR, MANAGERPACKETHANDLER_FILE, 194,
                       L"[mgr-ch], 0x%.16I64X, %I64d, load-retryready-game-event-log-list, game event handle is null, "
                       L"cmd:%d, tid:0x%.16I64X, ",
                       session->_id, channel->GetId(), cmd, tid);
            failReason = 2;
        }
        else
        {
            session->Send("hq", SmartCouponManager_LoadRetryReadyGameEventLogListOkCmd, tid);
            Log::Write(Log::LT_DEBUG, MANAGERPACKETHANDLER_FILE, 201,
                       L"[mgr-ch], 0x%.16I64X, %I64d, load-retryready-game-event-log-list success ack, cmd:%d, "
                       L"tid:0x%.16I64X, count:%d",
                       session->_id, channel->GetId(), cmd, tid, context._count);
            channel->removeReferenceCount(SESSION_SOURCE_FILE, 1059);
            return true;
        }
    }

    session->Send("hqE", SmartCouponManager_LoadRetryReadyGameEventLogListFailCmd, tid, failReason);
    Log::Write(Log::LT_ERROR, MANAGERPACKETHANDLER_FILE, 208,
               L"[mgr-ch], 0x%.16I64X, %I64d, load-retryready-game-event-log-list failure ack, cmd:%d, tid:0x%.16I64X, "
               L"failReason:%d",
               session->_id, channel->GetId(), cmd, tid, failReason);
    channel->removeReferenceCount(SESSION_SOURCE_FILE, 1059);
    return true;
}
