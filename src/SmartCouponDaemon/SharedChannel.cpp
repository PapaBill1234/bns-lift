// SharedChannel.obj (SmartCouponDaemon PDB).
#include "SharedChannel.h"
#include "Session.h"
#include "Connection.h"
#include "Memory.h"
#include "MemoryManager.h"
#include "Log.h"
#include "AlertSender.h"
#include <new>

static wchar_t const* const SHARED_CHANNEL_FILE = L"..\\Shared\\SharedChannel.cpp";
static wchar_t const* const CHANNEL_H_FILE =
    L"E:\\DailyBuild02\\SmartCouponDaemon-Common-0.0.348\\depot\\Branch\\348NC\\Program\\Server\\BloodLib\\include\\Channel.h";

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
        return false;  // ❓ Hex-Rays gives the low byte of the null pointer (0).
    session->_lock.Enter();
    bool connected = session->_state == Session::CONNECTED && session->_connection->_socket != INVALID_SOCKET;
    session->_lock.Leave();
    session->removeReferenceCount(CHANNEL_H_FILE, 52);
    return connected;
}
