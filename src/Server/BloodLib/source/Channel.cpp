// Channel.obj (CacheGate PDB).
#include "Channel.h"
#include <windows.h>
#include "AlertSender.h"
#include "Connection.h"
#include "CrashHandler.h"
#include "Daemon.h"
#include "DelayedRelease.h"
#include "IoWorkerThread.h"
#include "Log.h"
#include "Memory.h"
#include "MemoryManager.h"
#include "Network.h"
#include "Port.h"
#include "Session.h"
#include <stdarg.h>

static wchar_t const CHANNEL_FILE[] = L"source\\Channel.cpp";
// The file name of the inlined helper from BloodLib/include/Channel.h.
// LIFT: each exe has its own build path. A wrapper .cpp (ChannelLobbyGate.cpp, ...) defines LIFT_CHANNEL_H_FILE
// before it includes this file. The default is CacheGate.
#ifndef LIFT_CHANNEL_H_FILE
#define LIFT_CHANNEL_H_FILE \
    L"E:\\DailyBuild02\\CacheGate-Common-0.0.348\\depot\\Branch\\348NC\\Program\\Server\\BloodLib\\include\\Channel.h"
#endif
static wchar_t const CHANNEL_HEADER_FILE[] = LIFT_CHANNEL_H_FILE;
static wchar_t const LOBBYGATE_CHANNEL_HEADER_FILE[] = LIFT_CHANNEL_H_FILE;

// Inlined crash macro.
#define CHANNEL_ASSERT_CRASH(line)                                                  \
    do                                                                              \
    {                                                                               \
        Log::Write(Log::LT_ERROR, CHANNEL_FILE, line, L"== CRASH == ASSERT CRASH"); \
        AlertSender::Write(CHANNEL_FILE, line, L"== CRASH == ASSERT CRASH");       \
        CrashHandler::MakeCrash("source\\Channel.cpp", line, L"");                  \
    } while (0)

// 0x103C0
Channel::~Channel()
{
    Session* session = _session;
    if (session != nullptr)
    {
        _session = nullptr;
        Channel* channel = session->_channel;
        if (channel != nullptr)
        {
            session->_channel = nullptr;
            channel->removeReferenceCount(CHANNEL_FILE, 98);
        }
        session->removeReferenceCount(CHANNEL_FILE, 100);
    }
}

// 0x10450
bool Channel::MakeSession(unsigned int portId, unsigned long ip, unsigned short portNo, long timeout, bool reconnect)
{
    // LIFT: LTCG folded portId 2. CacheGate 0x104c3 and LobbyGate 0x21373 read Network+0x18 (_port[1]).
    if (_session != nullptr)
        CHANNEL_ASSERT_CRASH(30);

    Port* port = Network::Instance->_port[portId - 1];
    if (port == nullptr)
    {
        Log::Write(Log::LT_ERROR, CHANNEL_FILE, 36, L"[channel], cannot find port, port:%d", portId);
        return false;
    }

    // LIFT: LTCG folded the nagle argument. Session::Connect (0xE570) reads port->_nagle.
    if (port->MakeNewSession(ip, portNo, this, timeout, port->_nagle, reconnect, &_session))
        return true;

    Log::Write(Log::LT_ERROR, CHANNEL_FILE, 44, L"[channel], cannot make session, port:%d, ip:%s, portno:%d", portId,
               Network::GetAddressStringW(ip), static_cast<int>(portNo));
    return false;
}

// 0x10560
void Channel::SetSession(Session const* session)
{
    if (session == nullptr || _session != nullptr)
        CHANNEL_ASSERT_CRASH(53);

    Session* newSession = const_cast<Session*>(session);
    newSession->addReferenceCount(CHANNEL_FILE, 55);
    _session = newSession;
    newSession->SetChannel(this);
}

// 0x10620
void Channel::RemoveSession(Session const* session, bool forceNow)
{
    if (session != nullptr && session != _session)
    {
        Log::Write(Log::LT_ERROR, CHANNEL_FILE, 68, L"Channel(%p, %I64X), session(%p, %I64X), removing session(%p, %I64X)",
                   this, GetId(), session, session->_id, _session, _session != nullptr ? _session->_id : 0ULL);
    }

    if (forceNow || !_useDelayedRemove)
    {
        Session* current = _session;
        if (current != nullptr)
        {
            _session = nullptr;
            Channel* channel = current->_channel;
            if (channel != nullptr)
            {
                current->_channel = nullptr;
                channel->removeReferenceCount(CHANNEL_FILE, 98);
            }
            current->removeReferenceCount(CHANNEL_FILE, 100);
        }
    }
    else if (_session != nullptr)
    {
        Daemon* daemon = Daemon::Instance;
        _waitForRelease = true;
        _session->_waitForRelease = true;
        // LIFT: LTCG folded the callback (removeSession) and ref3 (nullptr) into DelayedRelease::Add.
        daemon->GlobalDelayedRelease->Add(GetTickCount64() - Daemon::Instance->StartSystemTick64, &Channel::removeSession,
                                          this, _session, nullptr);
    }
}

// 0x10770
void Channel::removeSession(RefCntObject* ref1, RefCntObject* ref2, RefCntObject* ref3)
{
    Channel* channel = static_cast<Channel*>(ref1);
    Session* session = channel->_session;
    if (session != nullptr)
    {
        channel->_session = nullptr;
        Channel* sessionChannel = session->_channel;
        if (sessionChannel != nullptr)
        {
            session->_channel = nullptr;
            sessionChannel->removeReferenceCount(CHANNEL_FILE, 98);
        }
        session->removeReferenceCount(CHANNEL_FILE, 100);
    }
}

// 0x107D0
Session const* Channel::GetSession() const
{
    Session* session = _session;
    if (session == nullptr || _waitForRelease)
        return nullptr;
    session->addReferenceCount(CHANNEL_FILE, 112);
    return session;
}

// 0x10810
void Channel::Close()
{
    Session* session = const_cast<Session*>(GetSession());
    if (session != nullptr)
    {
        RemoveSession(nullptr, false);
        session->_lock.Enter();
        bool closed = session->close(false);
        session->_lock.Leave();
        if (closed)
            session->_port->RemoveSession(session);
        session->removeReferenceCount(CHANNEL_HEADER_FILE, 52);
    }
}

// 0x108A0
DaemonChannel::~DaemonChannel()
{
}

// 0x108B0
bool DaemonChannel::OnAccept(Session const* session) const
{
    bool result = const_cast<DaemonChannel*>(this)->onAccept(session);
    if (result)
    {
        _InterlockedIncrement(&ConnectedSessionCount);
        return true;
    }
    return result;
}

// 0x108E0
bool DaemonChannel::OnConnect(Session const* session, bool firstConnected) const
{
    bool result = const_cast<DaemonChannel*>(this)->onConnect(session, firstConnected);
    if (result)
    {
        _InterlockedIncrement(&ConnectedSessionCount);
        return true;
    }
    return result;
}

// 0x10910
void DaemonChannel::OnClose(Session const* session, bool tryReconnect) const
{
    bool closeAll = _InterlockedDecrement(&ConnectedSessionCount) <= 0;
    const_cast<DaemonChannel*>(this)->onClose(session, tryReconnect, closeAll);
}

// 0x10950
ClientSideDaemonChannel::~ClientSideDaemonChannel()
{
    if (session != nullptr)
    {
        for (int i = 0; i < SessionSize; ++i)
        {
            if (session[i] != nullptr)
            {
                session[i]->removeReferenceCount(CHANNEL_FILE, 282);
                session[i] = nullptr;
            }
        }
        Memory::_Manager[2]->Free(session, CHANNEL_FILE, 286);
        session = nullptr;
    }
}

// 0x10AD0
Session* ClientSideDaemonChannel::getSession()
{
    if (session == nullptr)
        return nullptr;

    Session* found = session[IoWorker::WorkerId];
    bool usable = false;
    if (found != nullptr)
    {
        found->_lock.Enter();
        usable = found->_state == Session::CONNECTED && found->_connection->_socket != INVALID_SOCKET;
        found->_lock.Leave();
    }
    if (!usable)
    {
        if (session[0] == nullptr)
            return nullptr;
        found = session[0];
    }
    found->addReferenceCount(CHANNEL_FILE, 380);
    return found;
}

// 0x10B90
void ClientSideDaemonChannel::releaseSession(Session* releasedSession)
{
    if (releasedSession != nullptr)
        releasedSession->removeReferenceCount(CHANNEL_FILE, 388);
}

// 0x216C0 (LobbyGate)
bool Channel::Send(char const* format, ...)
{
    Session* session = const_cast<Session*>(GetSession());
    if (session == nullptr)
        return false;
    va_list args;
    va_start(args, format);
    session->SendV(format, args);
    va_end(args);
    session->removeReferenceCount(LOBBYGATE_CHANNEL_HEADER_FILE, 52);
    return true;
}

// 0x21720 (LobbyGate)
// LIFT: noinline. The orig calls it out of line (POD 0x2c160).
__declspec(noinline) bool Channel::Send(Packet const* packet)
{
    Session* session = const_cast<Session*>(GetSession());
    if (session == nullptr)
        return false;
    // Inlined Session::Send(Packet const*) (0x18F00 LobbyGate).
    session->Send(packet);
    session->removeReferenceCount(LOBBYGATE_CHANNEL_HEADER_FILE, 52);
    return true;
}
