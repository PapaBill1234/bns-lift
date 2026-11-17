// CacheDChannel.obj (CacheGate PDB).
#include "CacheDChannel.h"

#include <winsock2.h>
#include <windows.h>
#include <wchar.h>

#include "CacheD.h"
#include "CacheGate.h"
#include "CacheGateSessionHandler.h"
#include "Connection.h"
#include "Log.h"
#include "Network.h"
#include "Packet.h"
#include "PipeConsole.h"
#include "Session.h"
#include "CacheGatePacketCommand.h"

static wchar_t const CACHED_CHANNEL_FILE[] = L"CacheDChannel.cpp";
// The inlined Session::GetChannel / ReleaseChannel use the Session.cpp path.
static wchar_t const SESSION_FILE[] = L"source\\Session.cpp";

// 0x3c70
CacheDChannel::~CacheDChannel()
{
}

// 0x3c80
bool CacheDChannel::onConnect(Session const* session, bool firstConnected)
{
    bool result = true;
    if (firstConnected)
        Log::Write(Log::LT_DEBUG, CACHED_CHANNEL_FILE, 64, L"Session(%I64X), Cached channel connected", session->_id);
    else
        Log::Write(Log::LT_DEBUG, CACHED_CHANNEL_FILE, 66, L"Session(%I64X), Cached channel reconnected", session->_id);

    // Inlined Session::GetChannel.
    CacheD* cached = nullptr;
    if (session->_channel != nullptr && !session->_waitForRelease)
    {
        session->_channel->addReferenceCount(SESSION_FILE, 1051);
        cached = static_cast<CacheD*>(session->_channel);
    }
    if (cached != nullptr)
    {
        int ret = cached->Verify(session);
        if (ret == 0)
        {
            session->Send("hhhh", CacheGate_HelloCmd, 4, 10, cached->_id);
            Log::Write(Log::LT_DEBUG, CACHED_CHANNEL_FILE, 80, L"[cg], cached connect, hello send, wid:%d, ip:%s",
                       static_cast<int>(cached->_id), Network::GetAddressStringW(session->_connection->_ip));
        }
        else
        {
            Log::Write(Log::LT_DEBUG, CACHED_CHANNEL_FILE, 83, L"[cg], cached register fail, ret-code:%d, wid:%d, ip:%s", ret,
                       static_cast<int>(cached->_id), Network::GetAddressStringW(session->_connection->_ip));
            result = false;
        }

        if (CacheGate::_instance != nullptr && CacheGate::_instance->pipeConsole != nullptr)
            CacheGate::_instance->pipeConsole->SetInvalidInfo(cached->_daemonInvalidInfoKey, false);

        // Inlined Session::ReleaseChannel.
        cached->removeReferenceCount(SESSION_FILE, 1059);
        return result;
    }
    else
    {
        Log::Write(Log::LT_DEBUG, CACHED_CHANNEL_FILE, 70, L"[cg], cached channel bind fail");
        return false;
    }
}

// 0x3e40
void CacheDChannel::onClose(Session const* session, bool tryReconnect, bool closeAll)
{
    // Inlined Session::GetChannel.
    CacheD* cached = nullptr;
    if (session->_channel != nullptr && !session->_waitForRelease)
    {
        session->_channel->addReferenceCount(SESSION_FILE, 1051);
        cached = static_cast<CacheD*>(session->_channel);
    }
    if (cached == nullptr)
    {
        Log::Write(Log::LT_DEBUG, CACHED_CHANNEL_FILE, 98, L"Session(%I64X), Cached channel closed, GetChannel fail",
                   session->_id);
        return;
    }

    // Inlined PipeConsole::SetInvalidInfo(cached->_daemonInvalidInfoKey, true).
    if (CacheGate::_instance != nullptr && CacheGate::_instance->pipeConsole != nullptr)
    {
        PipeConsole* console = CacheGate::_instance->pipeConsole;
        console->_lock.Enter();
        PipeConsole::ItemNode* node = console->_invalid._head._next;
        while (node != &console->_invalid._tail)
        {
            if (wcscmp(node->_key, cached->_daemonInvalidInfoKey) == 0)
                break;
            node = node->_next;
        }
        if (node == &console->_invalid._tail || node == nullptr)
            PipeConsole::addNode(console->_invalid, cached->_daemonInvalidInfoKey, L"");  // LIFT: LTCG folded valueString. addNode (0x15ED0) does not read r8 and copies L"" (0x3B700).
        console->_lock.Leave();
    }

    if (cached->_status == 1)
    {
        cached->_lock.Enter();
        cached->_status = 0;
        cached->_lock.Leave();
    }

    if (tryReconnect)
    {
        Log::Write(Log::LT_DEBUG, CACHED_CHANNEL_FILE, 107, L"Session(%I64X), Cached channel(%I64X) trying to reconnect",
                   session->_id, cached->GetId());
    }
    else
    {
        Log::Write(Log::LT_DEBUG, CACHED_CHANNEL_FILE, 110, L"Session(%I64X), Cached channel(%I64X) closed", session->_id,
                   cached->GetId());
        if (closeAll)
            Log::Write(Log::LT_DEBUG, CACHED_CHANNEL_FILE, 113, L"Session(%I64X), Cached channel(%I64X) closed(All)",
                       session->_id, cached->GetId());
    }

    // Inlined Session::ReleaseChannel.
    cached->removeReferenceCount(SESSION_FILE, 1059);
}

// 0x40b0
bool ClientSideDaemonChannel::onAccept(Session const* session)
{
    return false;
}

// 0x4150 (COMDAT folded with CacheGateSessionHandler::PacketHandler)
bool CacheDChannel::PacketHandler(Session const* session, Packet const* packet) const
{
    Daemon::PacketHandler handler =
        CacheGatePacketServerSideHandlerList[static_cast<unsigned short>(packet->CurHeader[1].size)];
    if (handler == nullptr)
        return false;
    return handler(session, packet);
}
