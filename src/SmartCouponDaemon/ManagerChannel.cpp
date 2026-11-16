// ManagerChannel.obj (SmartCouponDaemon PDB).
#include "ManagerChannel.h"

#include <winsock2.h>
#include <windows.h>

#include "AlertSender.h"
#include "Connection.h"
#include "Log.h"
#include "Packet.h"
#include "PacketBuffer.h"
#include "Session.h"
#include "SmartCouponDaemon.h"

static wchar_t const MANAGERCHANNEL_FILE[] = L"ManagerChannel.cpp";

// ❓ Packet has no constructor. The original sets these fields inline.
static void zeroPacket(Packet* packet)
{
    packet->Splitter = nullptr;
    packet->IsFragmentPacket = false;
    packet->FragmentPacketCmd = 0;
    packet->CurHeader = nullptr;
    packet->ListHead = nullptr;
    packet->ListTail = nullptr;
}

// ❓ Inlined connected check (Session lock, state and socket).
static bool isConnected(Session* session)
{
    session->_lock.Enter();
    bool connected = session->_state == Session::CONNECTED && session->_connection->_socket != INVALID_SOCKET;
    session->_lock.Leave();
    return connected;
}

// 0xe7a0
bool ManagerSessionHandler::OnAccept(Session const* session) const
{
    unsigned long long id = session->_id;
    Log::Write(Log::LT_NOTICE, MANAGERCHANNEL_FILE, 28,
               L"[ManagerSessionHandler], accepted manager session, sessionId:0x%I64X, portId:%u, sessionIndex:%u", id,
               static_cast<unsigned int>(id >> 32), static_cast<unsigned int>(id));
    return true;
}

// 0xe7f0
bool ManagerSessionHandler::OnConnect(Session const* session, bool firstConnected) const
{
    unsigned long long id = session->_id;
    Log::Write(Log::LT_ERROR, MANAGERCHANNEL_FILE, 34,
               L"[ManagerSessionHandler], cannot use ManagerSessionHandler::OnConnect handler, sessionId:0x%I64X, portId:%u, "
               L"sessionIndex:%u",
               id, static_cast<unsigned int>(id >> 32), static_cast<unsigned int>(id));
    return false;
}

// 0xe830
void ManagerSessionHandler::OnClose(Session const* session, bool tryReconnect) const
{
    Channel* channel = session->GetChannel();
    unsigned long long id = session->_id;
    if (channel != nullptr)
    {
        SmartCouponDaemon::_instance->_managerChannelLock.Enter();
        SmartCouponDaemon::_instance->_managerChannel = nullptr;
        SmartCouponDaemon::_instance->_managerChannelLock.Leave();
        unsigned long long wid = channel->GetId();
        channel->RemoveSession(session, false);
        channel->removeReferenceCount(MANAGERCHANNEL_FILE, 48);
        Log::Write(Log::LT_NOTICE, MANAGERCHANNEL_FILE, 50,
                   L"[ManagerSessionHandler], closed connection with manager session, wid:%I64d, sessionId:0x%I64X, "
                   L"portId:%u, sessionIndex:%u",
                   wid, id, static_cast<unsigned int>(id >> 32), static_cast<unsigned int>(id));
    }
    else
    {
        Log::Write(Log::LT_NOTICE, MANAGERCHANNEL_FILE, 53,
                   L"[ManagerSessionHandler], closed connection with unknown manager session, sessionId:0x%I64X, "
                   L"portId:%u, sessionIndex:%u",
                   id, static_cast<unsigned int>(id >> 32), static_cast<unsigned int>(id));
    }
}

// 0xe980
bool ManagerSessionHandler::PacketHandler(Session const* session, Packet const* packet) const
{
    if (session == nullptr || packet == nullptr)
    {
        Log::Write(Log::LT_ERROR, MANAGERCHANNEL_FILE, 62,
                   L"== CRASH == [ManagerSessionHandler], handle packet failed; invalid parameter");
        AlertSender::Write(MANAGERCHANNEL_FILE, 62,
                           L"== CRASH == [ManagerSessionHandler], handle packet failed; invalid parameter");
        return false;
    }

    unsigned long long id = session->_id;
    if (packet->CurHeader == reinterpret_cast<Packet::Header*>(-2))
    {
        Log::Write(Log::LT_ERROR, MANAGERCHANNEL_FILE, 69,
                   L"[ManagerSessionHandler], invalid packet; command is null, cmd:0x%p, sessionId:0x%I64X, portId:%u, "
                   L"sessionIndex:%u",
                   static_cast<void*>(nullptr), id, static_cast<unsigned int>(id >> 32), static_cast<unsigned int>(id));
        return false;
    }
    short cmd = (packet->CurHeader + 1)->size;

    Channel* channel = session->GetChannel();
    if (channel != nullptr)
    {
        bool result = false;
        if (cmd >= 1 && cmd < 10 && SmartCouponManagerPacketSmartCouponSideHandlerList[cmd] != nullptr)
        {
            result = SmartCouponManagerPacketSmartCouponSideHandlerList[cmd](session, packet);
        }
        else
        {
            Log::Write(Log::LT_ERROR, MANAGERCHANNEL_FILE, 96,
                       L"[ManagerSessionHandler], invalid manager packet command, command:%d, managerWid:%u, "
                       L"sessionId:0x%I64X, portId:%u, sessionIndex:%u",
                       cmd, static_cast<unsigned int>(channel->GetId()), id, static_cast<unsigned int>(id >> 32),
                       static_cast<unsigned int>(id));
        }
        channel->removeReferenceCount(MANAGERCHANNEL_FILE, 101);
        return result;
    }

    if (cmd == 1 && SmartCouponManagerPacketSmartCouponSideHandlerList[1] != nullptr)
        return SmartCouponManagerPacketSmartCouponSideHandlerList[1](session, packet);

    Log::Write(Log::LT_ERROR, MANAGERCHANNEL_FILE, 84,
               L"[ManagerSessionHandler], invalid packet command of not authorized session, command:%d, "
               L"sessionId:0x%I64X, portId:%u, sessionIndex:%u",
               cmd, id, static_cast<unsigned int>(id >> 32), static_cast<unsigned int>(id));
    return false;
}

// 0xeb80
void ManagerChannel::SendRetryCouponPublicationOk(Session* session, long long tid, long long acceptTid)
{
    if (session == nullptr || !isConnected(session))
    {
        Log::Write(Log::LT_ERROR, MANAGERCHANNEL_FILE, 120,
                   L"[manager-ch], 0x%.16I64X, %I64d, send retry coupon publication ok; invalid session; send fail",
                   session != nullptr ? session->_id : 0ULL, GetId(), -2);
        return;
    }

    Packet p;
    zeroPacket(&p);
    p.Allocate();
    if (p.Compose("hqq", 5, tid, acceptTid) != 0)
    {
        PacketBuffer const* buffer = p.ListHead;
        p.ListHead->encrypt(session->_currentCrypt, session->_security3rd);
        session->_lock.Enter();
        session->send(&buffer, 1);  // ❓ inlined send
        session->_lock.Leave();
    }
    else
    {
        Log::Write(Log::LT_ERROR, MANAGERCHANNEL_FILE, 113,
                   L"[manager-ch], 0x%.16I64X, %I64d, send retry coupon publication ok; compose packet fail; compose fail",
                   session->_id, GetId());
    }
    p.Clear();
}

// 0xed20
void ManagerChannel::SendRetryCouponPublicationFail(Session* session, long long tid, short failReason)
{
    if (session == nullptr || !isConnected(session))
    {
        Log::Write(Log::LT_ERROR, MANAGERCHANNEL_FILE, 141,
                   L"[manager-ch], 0x%.16I64X, %I64d, send retry coupon publication fail; invalid session; send fail",
                   session != nullptr ? session->_id : 0ULL, GetId(), -2);
        return;
    }

    Packet p;
    zeroPacket(&p);
    p.Allocate();
    if (p.Compose("hqE", 6, tid, failReason) != 0)
    {
        PacketBuffer const* buffer = p.ListHead;
        p.ListHead->encrypt(session->_currentCrypt, session->_security3rd);
        session->_lock.Enter();
        session->send(&buffer, 1);  // ❓ inlined send
        session->_lock.Leave();
    }
    else
    {
        Log::Write(Log::LT_ERROR, MANAGERCHANNEL_FILE, 134,
                   L"[manager-ch], 0x%.16I64X, %I64d, send retry coupon publication fail; compose packet fail; compose "
                   L"fail",
                   session->_id, GetId());
    }
    p.Clear();
}
