// ManageChannel.obj (LobbyDaemon PDB, 2019 + PDB).
// LIFT: gap-19 lifts the manage session handler and the ManageChannel senders.
#include <winsock2.h>
#include <windows.h>
#include "ManageChannel.h"
#include "LobbyManagePacketHandler.h"
#include "AlertSender.h"
#include "Daemon.h"
#include "LobbyDaemon.h"
#include "Log.h"
#include "Packet.h"
#include "PacketUtil.h"
#include "Session.h"

namespace
{
// LIFT: No PDB symbol. The binary uses the literal as the file string of the log calls (first use at 0x5b140).
wchar_t const* const MANAGE_CHANNEL_FILE = L"ManageChannel.cpp";
// LIFT: No PDB symbol. The binary uses the literal as the file string of the Session reference count call (line 1059; used in
// ManageSessionHandler::PacketHandler 0x5b2a0).
wchar_t const* const SESSION_FILE = L"source\\Session.cpp";
}

// 0x5b140
bool ManageSessionHandler::OnAccept(Session const* session) const
{
    unsigned long long id = session != nullptr ? session->_id : 0;
    Log::Write(Log::LT_NOTICE, MANAGE_CHANNEL_FILE, 21, L"[manage], accepted manager session, session-id:0x%I64X", id);
    return true;
}

// 0x5b180
bool ManageSessionHandler::OnConnect(Session const* session, bool) const
{
    unsigned long long id = session != nullptr ? session->_id : 0;
    Log::Write(Log::LT_ERROR, MANAGE_CHANNEL_FILE, 27, L"[manage], connect forbidden, session-id:0x%I64X", id);
    return false;
}

// 0x5b1c0
void ManageSessionHandler::OnClose(Session const* session, bool) const
{
    ManageChannel* channel = static_cast<ManageChannel*>(session->GetChannel());
    if (channel != nullptr)
    {
        int manageWid = channel->GetManageWid();
        channel->RemoveSession(session, false);
        Log::Write(Log::LT_ERROR, MANAGE_CHANNEL_FILE, 40, L"[manage], closed, mgt-wid:%d, session-id:0x%I64X", manageWid,
                   session->_id);
        channel->removeReferenceCount(MANAGE_CHANNEL_FILE, 42);
    }
    else
    {
        Log::Write(Log::LT_ERROR, MANAGE_CHANNEL_FILE, 45, L"[manage], not authed session closed, session-id:0x%I64X",
                   session->_id);
    }
}

// 0x5b2a0
bool ManageSessionHandler::PacketHandler(Session const* session, Packet const* packet) const
{
    if (session == nullptr || packet == nullptr)
    {
        Log::Write(Log::LT_ERROR, MANAGE_CHANNEL_FILE, 57, L"== CRASH == [manage], handle packet failed; invalid parameter");
        AlertSender::Write(MANAGE_CHANNEL_FILE, 57, L"== CRASH == [manage], handle packet failed; invalid parameter");
        return false;
    }

    Packet::Header const* header = packet->CurHeader;
    unsigned short bodySize = static_cast<unsigned short>(header->size - 2);
    if (bodySize < 2u)
    {
        Log::Write(Log::LT_ERROR, MANAGE_CHANNEL_FILE, 63,
                   L"[manage], handle packet failed; invalid packet size, size:%d, session-id:0x%I64X",
                   static_cast<int>(bodySize), session->_id);
        return false;
    }

    short cmd = header[1].size;
    if (static_cast<unsigned short>(cmd - 1) > 15u)
    {
        Log::Write(Log::LT_ERROR, MANAGE_CHANNEL_FILE, 71,
                   L"[manage], handle packet failed; packet command out of range, cmd:%d, session-id:0x%I64X",
                   static_cast<int>(cmd), session->_id);
        return false;
    }

    LobbyManagePacketHandlerDef const* def = &LobbyManagePacketLobbySideHandlerList[cmd];
    if (def->handler == nullptr)
    {
        Log::Write(Log::LT_ERROR, MANAGE_CHANNEL_FILE, 78,
                   L"[manage], handle packet failed; handler not exists, cmd:%d, session-id:0x%I64X",
                   static_cast<int>(cmd), session->_id);
        return false;
    }

    bool result = false;
    ManageChannel* channel = static_cast<ManageChannel*>(session->GetChannel());
    if (!def->auth)
    {
        Log::Write(Log::LT_DEBUG, MANAGE_CHANNEL_FILE, 87, L"[manage], handle begin, cmd:%d, session-id:0x%I64X",
                   static_cast<int>(cmd), session->_id);
        result = reinterpret_cast<Daemon::PacketHandler>(def->handler)(session, packet);
        Log::Write(Log::LT_DEBUG, MANAGE_CHANNEL_FILE, 89, L"[manage], handle end, cmd:%d, session-id:0x%I64X",
                   static_cast<int>(cmd), session->_id);
    }
    else
    {
        if (channel == nullptr)
        {
            Log::Write(Log::LT_ERROR, MANAGE_CHANNEL_FILE, 115,
                       L"[manage], handle packet fail; unknown handler type, cmd:%d, session-id:0x%I64X",
                       static_cast<int>(cmd), session->_id);
            return false;
        }
        if (def->fragment)
        {
            bool completed = false;
            ConcatenatePacket(session, packet, completed);
            if (completed)
            {
                PacketConcatenater* concatenater = session->_concatenater;
                Log::Write(Log::LT_DEBUG, MANAGE_CHANNEL_FILE, 100,
                           L"[manage], handle begin, cmd:%d, session-id:0x%I64X, mgt-wid:%d", static_cast<int>(cmd),
                           session->_id, static_cast<int>(channel->GetManageWid()));
                reinterpret_cast<bool (*)(Session const*, PacketConcatenater*)>(def->handler)(session, concatenater);
                Log::Write(Log::LT_DEBUG, MANAGE_CHANNEL_FILE, 102,
                           L"[manage], handle end, cmd:%d, session-id:0x%I64X, mgt-wid:%d", static_cast<int>(cmd),
                           session->_id, static_cast<int>(channel->GetManageWid()));
                concatenater->Clear();
            }
        }
        else
        {
            Log::Write(Log::LT_DEBUG, MANAGE_CHANNEL_FILE, 108,
                       L"[manage], handle begin, cmd:%d, session-id:0x%I64X, mgt-wid:%d", static_cast<int>(cmd),
                       session->_id, static_cast<int>(channel->GetManageWid()));
            reinterpret_cast<Daemon::PacketHandler>(def->handler)(session, packet);
            Log::Write(Log::LT_DEBUG, MANAGE_CHANNEL_FILE, 110,
                       L"[manage], handle end, cmd:%d, session-id:0x%I64X, mgt-wid:%d", static_cast<int>(cmd),
                       session->_id, static_cast<int>(channel->GetManageWid()));
        }
        result = true;
    }
    if (channel != nullptr)
        channel->removeReferenceCount(SESSION_FILE, 1059);
    return result;
}

// LIFT: the senders below share one shape. The original inlines the Packet ctor and Session::Send(Packet const*).
#define MANAGE_PACKET_INIT(p)       \
    Packet p;                       \
    p.CurHeader = nullptr;          \
    p.Splitter = nullptr;           \
    p.ListHead = nullptr;           \
    p.ListTail = nullptr;           \
    p.IsFragmentPacket = false;     \
    p.FragmentPacketCmd = 0;        \
    p.Allocate()

// 0x5b630
void ManageChannel::SendKickOk(Session const* s, unsigned long long tid)
{
    if (s != nullptr)
    {
        MANAGE_PACKET_INIT(p);
        if (0 != p.Compose("hq", 6, tid))
            s->Send(&p);
        else
            Log::Write(Log::LT_ERROR, MANAGE_CHANNEL_FILE, 133,
                       L"[manage], send kick ok fail; compose packet fail; compose fail, tid:0x%I64X, session-id:0x%I64X", tid,
                       s->_id);
    }
}

// 0x5b760
void ManageChannel::SendKickFail(Session const* s, unsigned long long tid, short reason)
{
    if (s != nullptr)
    {
        MANAGE_PACKET_INIT(p);
        if (0 != p.Compose("hqE", 7, tid, static_cast<int>(reason)))
            s->Send(&p);
        else
            Log::Write(Log::LT_ERROR, MANAGE_CHANNEL_FILE, 148,
                       L"[manage], send kick fail fail; compose packet fail; compose fail, tid:0x%I64X, reason:%d, session-id:0x%I64X",
                       tid, static_cast<int>(reason), s->_id);
    }
}

// 0x5b8a0
void ManageChannel::SendCleanupGameAccountIdIndexOk(Session const* s, unsigned long long tid)
{
    if (s != nullptr)
    {
        MANAGE_PACKET_INIT(p);
        if (0 != p.Compose("hq", 9, tid))
            s->Send(&p);
        else
            Log::Write(Log::LT_ERROR, MANAGE_CHANNEL_FILE, 163,
                       L"[manage], send cleanup game-account-id index ok fail; compose fail, tid:0x%I64X, session-id:0x%I64X", tid,
                       s->_id);
    }
}

// 0x5b9d0
void ManageChannel::SendCleanupGameAccountIdIndexFail(Session const* s, unsigned long long tid, short reason)
{
    if (s != nullptr)
    {
        MANAGE_PACKET_INIT(p);
        if (0 != p.Compose("hqE", 10, tid, static_cast<int>(reason)))
            s->Send(&p);
        else
            Log::Write(Log::LT_ERROR, MANAGE_CHANNEL_FILE, 178,
                       L"[manage], send game-account-id index fail fail; compose fail, tid:0x%I64X, reason:%d, session-id:0x%I64X",
                       tid, static_cast<int>(reason), s->_id);
    }
}

// 0x5bb10
void ManageChannel::SendCleanupPcidIndexOk(Session const* s, unsigned long long tid)
{
    if (s != nullptr)
    {
        MANAGE_PACKET_INIT(p);
        if (0 != p.Compose("hq", 12, tid))
            s->Send(&p);
        else
            Log::Write(Log::LT_ERROR, MANAGE_CHANNEL_FILE, 193,
                       L"[manage], send cleanup pc-id index ok fail; compose fail, tid:0x%I64X, session-id:0x%I64X", tid, s->_id);
    }
}

// 0x5bc40
void ManageChannel::SendCleanupPcidIndexFail(Session const* s, unsigned long long tid, short reason)
{
    if (s != nullptr)
    {
        MANAGE_PACKET_INIT(p);
        if (0 != p.Compose("hqE", 13, tid, static_cast<int>(reason)))
            s->Send(&p);
        else
            Log::Write(Log::LT_ERROR, MANAGE_CHANNEL_FILE, 208,
                       L"[manage], send cleanup pc-id index fail fail; compose fail, tid:0x%I64X, reason:%d, session-id:0x%I64X",
                       tid, static_cast<int>(reason), s->_id);
    }
}

// 0x5bd80
void ManageChannel::SendRetryMileageDepositOk(Session const* s, unsigned long long tid)
{
    if (s != nullptr)
    {
        MANAGE_PACKET_INIT(p);
        if (0 != p.Compose("hq", 15, tid))
            s->Send(&p);
        else
            Log::Write(Log::LT_ERROR, MANAGE_CHANNEL_FILE, 224,
                       L"[manage], send retry mileage deposit ok fail; compose fail, tid:0x%I64X, session-id:0x%I64X", tid, s->_id);
    }
}

// 0x5beb0
void ManageChannel::SendRetryMileageDepositFail(Session const* s, unsigned long long tid, short reason)
{
    if (s != nullptr)
    {
        MANAGE_PACKET_INIT(p);
        if (0 != p.Compose("hqE", 16, tid, static_cast<int>(reason)))
            s->Send(&p);
        else
            // LIFT: the original log text says "ok" on the fail path (0x5beb0). Kept as is.
            Log::Write(Log::LT_ERROR, MANAGE_CHANNEL_FILE, 241,
                       L"[manage], send retry mileage deposit ok fail; compose fail, tid:0x%I64X, reason:%d, session-id:0x%I64X",
                       tid, static_cast<int>(reason), s->_id);
    }
}

#undef MANAGE_PACKET_INIT
