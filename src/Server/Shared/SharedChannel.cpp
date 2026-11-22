// SharedChannel.obj (SmartCouponDaemon PDB).
#include "SharedChannel.h"
#include "Session.h"
#include "Connection.h"
#include "Memory.h"
#include "MemoryManager.h"
#include "Log.h"
#include "AlertSender.h"
#include <new>

#include <stdarg.h>

static wchar_t const* const SHARED_CHANNEL_FILE = L"..\\Shared\\SharedChannel.cpp";
// LIFT: A6. Each exe has its own build path in the header literals. The default is SmartCouponDaemon.
#if defined(LIFT_EXE_LD)
static wchar_t const* const CHANNEL_H_FILE =
    L"E:\\DailyBuild02\\LobbyDaemon-Common-0.0.348\\depot\\Branch\\348NC\\Program\\Server\\BloodLib\\include\\Channel.h";
#define LIFT_SHARED_CHANNEL_H_FILE \
    L"e:\\dailybuild02\\lobbydaemon-common-0.0.348\\depot\\branch\\348nc\\program\\server\\shared\\SharedChannel.h"
#else
static wchar_t const* const CHANNEL_H_FILE =
    L"E:\\DailyBuild02\\SmartCouponDaemon-Common-0.0.348\\depot\\Branch\\348NC\\Program\\Server\\BloodLib\\include\\Channel.h";
#define LIFT_SHARED_CHANNEL_H_FILE \
    L"e:\\dailybuild02\\smartcoupondaemon-common-0.0.348\\depot\\branch\\348nc\\program\\server\\shared\\SharedChannel.h"
#endif

// 0x4270. The original body is inline in SharedChannel.h.
SharedChannel::~SharedChannel()
{
    if (_rawChannel != nullptr)
    {
        _rawChannel->RemoveSession(nullptr, false);  // slot 5 at 0x42a1
        _rawChannel->removeReferenceCount(LIFT_SHARED_CHANNEL_H_FILE, 36);
        _rawChannel = nullptr;
    }
}

// 0x6390
unsigned long long SharedChannel::RawChannel::GetId()
{
    return _id;
}

// 0x63d0
bool SharedChannel::Connect(unsigned long long id, unsigned int portId, unsigned long ip, unsigned short portNo,
                            long timeout, bool reconnect)
{
    if (_rawChannel != nullptr)
    {
        Log::Write(Log::LT_ERROR, SHARED_CHANNEL_FILE, 16, L"== CRASH == [shared-channel], connect fail; channel already exists");
        AlertSender::Write(SHARED_CHANNEL_FILE, 16, L"== CRASH == [shared-channel], connect fail; channel already exists");
        return false;
    }

    void* buffer = Memory::_Manager[2]->Alloc(sizeof(RawChannel), SHARED_CHANNEL_FILE, 20);
    _rawChannel = buffer != nullptr ? new (buffer) RawChannel(id, this) : nullptr;
    // BUG: 0x6400 no check for a null _rawChannel before MakeSession.
    if (!_rawChannel->MakeSession(portId, ip, portNo, timeout, reconnect))
    {
        Log::Write(Log::LT_ERROR, SHARED_CHANNEL_FILE, 22, L"[shared-channel], connect fail; make session fail");
        return false;
    }
    Log::Write(Log::LT_DEBUG, SHARED_CHANNEL_FILE, 26, L"[shared-channel], try connect ok");
    return true;
}

// 0x6510
bool SharedChannel::Accept(unsigned long long id, Session const* session)
{
    if (id == 0 || session == nullptr)
    {
        Log::Write(Log::LT_ERROR, SHARED_CHANNEL_FILE, 34, L"== CRASH == [shared-channel], accept fail; invalid parameter");
        AlertSender::Write(SHARED_CHANNEL_FILE, 34, L"== CRASH == [shared-channel], accept fail; invalid parameter");
        return false;
    }
    if (_rawChannel != nullptr)
    {
        Log::Write(Log::LT_ERROR, SHARED_CHANNEL_FILE, 40,
                   L"== CRASH == [shared-channel], accept fail; channel already exists, id:0xI64d, new:0xI64d",
                   _rawChannel->GetId(), id);
        AlertSender::Write(SHARED_CHANNEL_FILE, 40,
                           L"== CRASH == [shared-channel], accept fail; channel already exists, id:0xI64d, new:0xI64d",
                           _rawChannel->GetId(), id);
        return false;
    }

    void* buffer = Memory::_Manager[2]->Alloc(sizeof(RawChannel), SHARED_CHANNEL_FILE, 44);
    _rawChannel = buffer != nullptr ? new (buffer) RawChannel(id, this) : nullptr;
    // BUG: 0x6610 calls SetSession on a null _rawChannel when the alloc fails.
    _rawChannel->SetSession(session);
    return true;
}

// 0x6690
void SharedChannel::Close()
{
    if (_rawChannel == nullptr)
        return;
    Session* session = const_cast<Session*>(_rawChannel->GetSession());
    if (session != nullptr)
    {
        session->Close(false);
        session->removeReferenceCount(CHANNEL_H_FILE, 52);
    }
}

// 0x6720
void SharedChannel::StopReconnect()
{
    if (_rawChannel == nullptr)
        return;
    Session const* session = _rawChannel->GetSession();
    if (session != nullptr)
    {
        session->StopReconnect();
        const_cast<Session*>(session)->removeReferenceCount(CHANNEL_H_FILE, 52);
    }
}

// 0x67b0
bool SharedChannel::IsConnected()
{
    if (_rawChannel == nullptr)
        return false;
    Session* session = const_cast<Session*>(_rawChannel->GetSession());
    if (session == nullptr)
        return false;  // LIFT: 0x67d4 jumps with rax = 0, so al = 0 at 0x683a
    session->_lock.Enter();
    bool connected = session->_state == Session::CONNECTED && session->_connection->_socket != INVALID_SOCKET;
    session->_lock.Leave();
    session->removeReferenceCount(CHANNEL_H_FILE, 52);
    return connected;
}

// The functions below are from the LobbyDaemon PDB (2019 + PDB). SmartCouponDaemon does not call them.

// 0x4b70 (LobbyDaemon)
bool SharedChannel::Send(char const* format, ...)
{
    va_list args;
    va_start(args, format);
    return sendV(format, args);
}

// 0x4ba0 (LobbyDaemon)
// LIFT: noinline. The orig GamedChannel Send* functions call it out of line (A4).
__declspec(noinline) bool SharedChannel::Send(Packet const* packet)
{
    if (_rawChannel == nullptr)
        return false;
    Session* session = const_cast<Session*>(_rawChannel->GetSession());
    if (session == nullptr)
        return false;
    session->_lock.Enter();
    bool connected = session->_state == Session::CONNECTED && session->_connection->_socket != INVALID_SOCKET;
    session->_lock.Leave();
    // BUG: 0x4c0b returns without removeReferenceCount. The session reference leaks when it is not connected.
    if (!connected)
        return false;
    session->Send(packet);
    session->removeReferenceCount(CHANNEL_H_FILE, 52);
    return true;
}

// 0x4c50 (LobbyDaemon)
bool SharedChannel::sendV(char const* format, char* args)
{
    if (_rawChannel == nullptr)
        return false;
    Session* session = const_cast<Session*>(_rawChannel->GetSession());
    if (session == nullptr)
        return false;
    session->_lock.Enter();
    bool connected = session->_state == Session::CONNECTED && session->_connection->_socket != INVALID_SOCKET;
    session->_lock.Leave();
    // BUG: 0x4cbb returns without removeReferenceCount. The session reference leaks when it is not connected.
    if (!connected)
        return false;
    session->SendV(format, args);
    session->removeReferenceCount(CHANNEL_H_FILE, 52);
    return true;
}

// 0x4d20 (LobbyDaemon)
SharedChannelList::~SharedChannelList()
{
    Memory::_Manager[2]->Free(_channels, SHARED_CHANNEL_FILE, 190);
    _channels = nullptr;
    _idmin = 0;
    _idsize = 0;
    _size = 0;
}

// 0x4d60 (LobbyDaemon)
bool SharedChannelList::Initialize(unsigned long long idmin, unsigned long long idmax)
{
    if (idmax == 0 || idmin > idmax)
    {
        Log::Write(Log::LT_ERROR, SHARED_CHANNEL_FILE, 170,
                   L"== CRASH == [shared-channel-list], initialize fail; invalid parameter");
        AlertSender::Write(SHARED_CHANNEL_FILE, 170,
                           L"== CRASH == [shared-channel-list], initialize fail; invalid parameter");
        return false;
    }
    if (_channels != nullptr)
    {
        Log::Write(Log::LT_ERROR, SHARED_CHANNEL_FILE, 176,
                   L"== CRASH == [shared-channel-list], initialize fail; already initialized");
        AlertSender::Write(SHARED_CHANNEL_FILE, 176,
                           L"== CRASH == [shared-channel-list], initialize fail; already initialized");
        return false;
    }
    _idmin = idmin;
    _idsize = static_cast<int>(idmax - idmin + 1);
    _channels = static_cast<SharedChannel**>(
        Memory::_Manager[2]->AllocZero(sizeof(SharedChannel*) * _idsize, SHARED_CHANNEL_FILE, 182));
    _size = 0;
    return true;
}

// 0x4e20 (LobbyDaemon)
bool SharedChannelList::Set(SharedChannel* channel)
{
    if (channel == nullptr)
    {
        Log::Write(Log::LT_ERROR, SHARED_CHANNEL_FILE, 209, L"== CRASH == [shared-channel-list], add fail; null channel");
        AlertSender::Write(SHARED_CHANNEL_FILE, 209, L"== CRASH == [shared-channel-list], add fail; null channel");
        return false;
    }
    // LIFT: 0x4e6e. The orig gets the id from the inlined channel getter (null _rawChannel gives 0).
    int index = static_cast<int>(channel->_rawChannel != nullptr ? channel->_rawChannel->GetId() : 0) -
                static_cast<int>(_idmin);
    if (index < 0 || index >= _idsize)
    {
        Log::Write(Log::LT_ERROR, SHARED_CHANNEL_FILE, 215, L"[shared-channel-list], add fail; id out of range, id:%I64d",
                   channel->_rawChannel != nullptr ? channel->_rawChannel->GetId() : 0ULL);
        return false;
    }
    if (_channels[index] != nullptr)
    {
        Log::Write(Log::LT_ERROR, SHARED_CHANNEL_FILE, 220, L"[shared-channel-list], add fail; already exists, id:%I64d",
                   channel->_rawChannel != nullptr ? channel->_rawChannel->GetId() : 0ULL);
        return false;
    }
    _channels[index] = channel;
    ++_size;
    return true;
}
