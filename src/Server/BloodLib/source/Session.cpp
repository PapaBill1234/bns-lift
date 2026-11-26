// Session.obj (CacheGate PDB). Pseudocode: .scratch/hr/Session.c.
#include <winsock2.h>
#include <windows.h>
#include <string.h>
#include <new>
#include "Session.h"
#include "Connection.h"
#include "SessionBuffer.h"
#include "Port.h"
#include "Network.h"
#include "Daemon.h"
#include "Channel.h"
#include "IdleWatcher.h"
#include "Log.h"
#include "AlertSender.h"
#include "CrashHandler.h"
#include "Packet.h"
#include "PacketUtil.h"
#include "PacketBufferHandler.h"
#include "Memory.h"

#define SESSION_FILE L"source\\Session.cpp"

#define SESSION_ASSERT_CRASH(wfile, cfile, line)                               \
    do                                                                         \
    {                                                                          \
        Log::Write(Log::LT_ERROR, wfile, line, L"== CRASH == ASSERT CRASH");   \
        AlertSender::Write(wfile, line, L"== CRASH == ASSERT CRASH");          \
        CrashHandler::MakeCrash(cfile, line, L"");                             \
    } while (0)

// 0xDE80
unsigned int Timer::EventId() const
{
    return 5;
}

// 0xDE90 (from the scalar deleting destructor)
Timer::~Timer()
{
    SlotIndex = -1;
    prev = nullptr;
    next = nullptr;
}

// LobbyGate ReconnectTimer vtable 0x80760 slot 8 = 0x126f0 (retn 0). The body is empty.
void Timer::preprocessExpireEvent()
{
}

// The PDB has the class name only. Size 0x40 (Memory::_Manager[2]->Alloc(64) in Connect).
class ReconnectTimer : public Timer
{
public:
    // LIFT: Inlined in Session::Connect (0xE570).
    explicit ReconnectTimer(unsigned long long sessionId) : _sessionId(sessionId)
    {
        _tag = 66058;
        StartTick = 0;
        next = nullptr;
        prev = nullptr;
        SlotIndex = -1;
        InLtq = false;
    }
    virtual ~ReconnectTimer();
    virtual unsigned int TimerClass() const;
    virtual unsigned long long TimerId() const;
    virtual bool HandleEvent(EventContext* context, unsigned long numOfBytes);

    unsigned long long _sessionId;
};
static_assert(sizeof(ReconnectTimer) == 0x40, "sizeof ReconnectTimer");

// 0xFF90 (from the scalar deleting destructor)
ReconnectTimer::~ReconnectTimer()
{
    _sessionId = 0;
}

// LobbyGate ReconnectTimer vtable 0x80760 slot 6 = 0x27fc0 (xor eax, eax; retn).
unsigned int ReconnectTimer::TimerClass() const
{
    return 0;
}

// 0xFFD0 (folded with LogMedia::GetLastFileName)
unsigned long long ReconnectTimer::TimerId() const
{
    return 0;
}

// 0xFFE0
bool ReconnectTimer::HandleEvent(EventContext* context, unsigned long numOfBytes)
{
    Network::ReconnectSession(_sessionId);
    return true;
}

// 0xDED0
unsigned int Session::EventId() const
{
    return 3;  // EVID_IO_CONNECT (bytes b8 03 00 00 00 c3)
}

// 0xDEE0
Session::Session()
{
    _tag = 1802;
    clear();
    _InterlockedDecrement(&_ref);
}

// 0xDF80
Session::Session(unsigned int portId, PacketBufferHandler const* bufferHandler)
{
    void* buffer = nullptr;
    _tag = 1802;
    clear();
    // LTCG folded size and used into StaticPageMemoryManager::Initialize (LobbyGate 0x26c90):
    // size 0x800 (0x26c99) and used 0x248 (crash log 0x26cbe).
    // LIFT: Instance() (PDB name) and not &_Instance: LTCG IPA keeps the address as an argument (r8 at 0xdf80).
    _allocator.Initialize(this, 2048, 0x248, BaseMemoryManager::Instance());
    if (bufferHandler != nullptr)
    {
        if (bufferHandler->AllocSize() != 0)
            buffer = _allocator.Alloc(bufferHandler->AllocSize(), SESSION_FILE, 69);
        _bufferHandler = bufferHandler->Clone(buffer);
        _minPacketSize = _bufferHandler->MinimalPacketSize();
    }
    _createdPort = portId;
}

// 0xE0A0
Session::~Session()
{
    if (_port != nullptr && _port->_sessionHandler != nullptr)  // LobbyGate 0x175d1 tests _port, 0x175da tests _sessionHandler
        _port->_sessionHandler->OnDestroyed(this);
    if (_connection != nullptr)
    {
        if (_connection->_socket != INVALID_SOCKET)
        {
            closesocket(_connection->_socket);
            _connection->_socket = INVALID_SOCKET;
        }
        _connection = nullptr;
    }
    if (_channel != nullptr)
    {
        _channel->removeReferenceCount(SESSION_FILE, 111);
        _channel = nullptr;
    }
    _extraData = nullptr;
    _recvBuffer = nullptr;
    if (_sendBuffer != nullptr)
    {
        _sendBuffer->Clear();
        _sendBuffer = nullptr;
    }
    _connectContext = nullptr;
    if (_bufferHandler != nullptr)
    {
        unsigned char* p = reinterpret_cast<unsigned char*>(_bufferHandler);
        _bufferHandler->Destroy(p >= _allocator._start && p < _allocator._end ? p : nullptr);
        _bufferHandler = nullptr;
    }
    if (_concatenater != nullptr)
    {
        unsigned char* p = reinterpret_cast<unsigned char*>(_concatenater);
        _concatenater->Destroy(p >= _allocator._start && p < _allocator._end ? p : nullptr);
        _concatenater = nullptr;
    }
    if (_reconnectTimer != nullptr)
    {
        _reconnectTimer->removeReferenceCount(SESSION_FILE, 182);
        _reconnectTimer = nullptr;
    }
    _currentCrypt = nullptr;
#if defined(LIFT_EXE_LG)
    // LIFT: per-exe form, LG 0x175a0 has the body of deallocateCrypt (0x194c0) in place, twice (compare chain).
#define LIFT_DEALLOC_CRYPT(member)                                                                                   \
    if (member != nullptr)                                                                                           \
    {                                                                                                                \
        PacketCrypt* crypt = member;                                                                                 \
        int type = crypt->GetType();                                                                                 \
        int rest1;                                                                                                   \
        int rest2;                                                                                                   \
        if (type == 0 || ((rest1 = type - 1) != 0 && ((rest2 = rest1 - 1) == 0 || static_cast<unsigned int>(rest2 - 1) <= 1))) \
            crypt->~PacketCrypt();                                                                                   \
        _allocator.Free(crypt, SESSION_FILE, 1331);                                                                  \
        member = nullptr;                                                                                            \
    }
    LIFT_DEALLOC_CRYPT(_handshakeCrypt)
    LIFT_DEALLOC_CRYPT(_sessionCrypt)
#undef LIFT_DEALLOC_CRYPT
#else
    if (_handshakeCrypt != nullptr)
    {
        deallocateCrypt(_handshakeCrypt);
        _handshakeCrypt = nullptr;
    }
    if (_sessionCrypt != nullptr)
    {
        deallocateCrypt(_sessionCrypt);
        _sessionCrypt = nullptr;
    }
#endif
    _security3rd = nullptr;
    _id = 0;
    _port = nullptr;
    _option = 0;
    _connectCount = 0;
}

// 0xE2E0
bool Session::initialize(Port* port, unsigned long long id, int option)
{
    unsigned char* page = reinterpret_cast<unsigned char*>(this);

    Connection* connection = new (page + 392) Connection();
    _connection = connection;

    SessionRecvBuffer* recvBuffer = new (page + 4096) SessionRecvBuffer;
    memset(&recvBuffer->_context, 0, sizeof(recvBuffer->_context));
    recvBuffer->_context._id = EVID_IO_RECV;
    recvBuffer->_context._session = this;
    recvBuffer->_recvdSize = 0;
    _recvBuffer = recvBuffer;

    SessionSendBuffer* sendBuffer = new (page + 416) SessionSendBuffer;
    memset(&sendBuffer->_context, 0, sizeof(sendBuffer->_context));
    sendBuffer->_context._id = EVID_IO_SEND;
    sendBuffer->_context._session = this;
    memset(sendBuffer->_bufferList, 0, sizeof(sendBuffer->_bufferList));
    sendBuffer->_bufferHandler = _bufferHandler;
    sendBuffer->_curSendingList = nullptr;
    sendBuffer->_maxBufferCount = 0;
    _sendBuffer = sendBuffer;

    // LIFT: SessionSendBuffer::Initialize does not read the second argument; it overwrites r8 (LobbyGate 0x2489a).
    if (_connection == nullptr || _recvBuffer == nullptr || _sendBuffer == nullptr
        || !_sendBuffer->Initialize(page + 2048, id))
        return false;

    _id = id;
    _port = port;
    _lastRecvTime = GetTickCount64() - Daemon::Instance->StartSystemTick64;
    _idleStatePos = 0;
    _cryptMode = option;
    _currentCrypt = nullptr;
    _handshakeCrypt = nullptr;
    _sessionCrypt = nullptr;
    _security3rd = nullptr;
    if (_bufferHandler != nullptr)
        _bufferHandler->Initialize();
    _recvPending = false;
    _sendPending = false;
    _connectPending = false;
    _waitForRelease = false;
    return true;
}

// 0xE4B0
void Session::clear()
{
    _connection = nullptr;
    _sendBuffer = nullptr;
    _state = CLOSED;
    _option = 0;
    _recvPending = false;
    _sendPending = false;
    _connectPending = false;
    _next = nullptr;
    _id = 0;
    _createdPort = 0;
    _connectCount = 0;
    _minPacketSize = 0;
    _idleStatePos = 0;
    _port = nullptr;
    _channel = nullptr;
    _extraData = nullptr;
    _waitForRelease = false;
    _connectContext = nullptr;
    _recvBuffer = nullptr;
    _bufferHandler = nullptr;
    _concatenater = nullptr;
    _reconnectTimer = nullptr;
    _cryptMode = 0;
    _currentCrypt = nullptr;
    _handshakeCrypt = nullptr;
    _sessionCrypt = nullptr;
    _security3rd = nullptr;
    _lastRecvTime = GetTickCount64() - Daemon::Instance->StartSystemTick64;
}

// 0xE570
bool Session::Connect(Port* port, unsigned long long id, unsigned long ip, unsigned short portNumber, long timeout,
                      bool nagle, bool reconnect)
{
    if (!initialize(port, id, 1))
        return false;
    _port->_sessionHandler->OnCreated(this);  // LobbyGate 0x17a70: the original reads the member
    _state = CONNECTING;
    _connectCount = 0;
    _option = 2;

    void* timerMemory = Memory::_Manager[2]->Alloc(sizeof(ReconnectTimer), SESSION_FILE, 363);
    _reconnectTimer = timerMemory != nullptr ? new (timerMemory) ReconnectTimer(id) : nullptr;

    _connectContext = reinterpret_cast<AsyncConnectContext*>(this + 1);
    if (_connectContext == nullptr)  // 0xe5f1: the original tests this + 1 for null
        return false;
    memset(_connectContext, 0, sizeof(AsyncConnectContext));
    _connectContext->_id = EVID_IO_CONNECT;
    _connectContext->_session = this;
    _connectContext->_socket = INVALID_SOCKET;
    _connectContext->_firstConnect = true;
    _connectContext->_timeout = 0;
    _connectContext->_tryReconnectCount = 0;
    // LIFT: LobbyGate 0x17bbc (PDB lines 379-380): the original zeroes the address again and fills it through one
    // pointer. htons comes before the sin_addr store.
    sockaddr_in* remoteAddr = &_connectContext->_remoteAddr;
    memset(remoteAddr, 0, sizeof(sockaddr_in));
    remoteAddr->sin_family = AF_INET;
    remoteAddr->sin_port = htons(portNumber);
    remoteAddr->sin_addr.s_addr = ip;
    // LTCG folded the timeout constant in each exe. CacheGate callers give 0. LobbyGate 0x17bed (PDB line 384)
    // stores GetTickCount64() - StartSystemTick64 + 5000 (the caller gives 5000). The signed local keeps the
    // original "sub; lea +5000" form. One unsigned expression gives "5000 - StartSystemTick64" first.
    if (timeout > 0)
    {
        long long now = GetTickCount64() - Daemon::Instance->StartSystemTick64;
        _connectContext->_timeout = now + timeout;
    }
    _connectPending = true;

    if (!_connection->AsyncConnect(_connectContext, port->_nagle))
    {
        _state = CLOSED;
        _connectPending = false;
        Log::Write(Log::LT_ERROR, SESSION_FILE, 395,
                   L"[session], Connection::AsyncConnect failed, id:%I64x, this:%p, error:%d", id, this,
                   WSAGetLastError());
        return false;
    }
    Log::Write(Log::LT_DEBUG, SESSION_FILE, 431, L"[session], connect to, port id: %u, id:%I64x, this:%p, ip:%s, port:%d",
               port->_id, _id, this, Network::GetAddressStringW(ip), portNumber);
    return true;
}

// 0xE7C0
bool Session::Accept(Port* port, unsigned long long id, unsigned long long* socket, unsigned long ip,
                     unsigned short portNumber, int option)
{
    if (!initialize(port, id, option))
        return false;
    _port->_sessionHandler->OnCreated(this);  // orig reads the member (CG 0xe7c0)
    if (!_connection->Accept(this, *socket, ip, portNumber))
    {
        Log::Write(Log::LT_ERROR, SESSION_FILE, 448, L"[session], Connection::Accept failed, id:%I64x, this:%p, error:%d",
                   _id, this, WSAGetLastError());
        return false;
    }
    *socket = INVALID_SOCKET;
    _state = CONNECTED;
    if (!port->_sessionHandler->OnAccept(this))
    {
        if (_connection->_socket != INVALID_SOCKET)
        {
            closesocket(_connection->_socket);
            _connection->_socket = INVALID_SOCKET;
        }
        _state = CLOSED;
        Log::Write(Log::LT_ERROR, SESSION_FILE, 460, L"[session], OnAccept failed, id:%I64x, this:%p", _id, this);
        return false;
    }
    if (port->_idleStateTable != nullptr)
    {
        _lastRecvTime = GetTickCount64() - Daemon::Instance->StartSystemTick64;
        _idleStatePos = port->_idleStateTable->SetBusyWithPos(id).pos;  // inlined (CG 0xe7c0)
    }
    if (!Daemon::Instance->allowClientIPAddressInLogs && port->_id == 1)
        ip = 0;
    if (Daemon::Instance->allowClientSessionLifeCycleInLogs || port->_id != 1)
        Log::Write(Log::LT_DEBUG, SESSION_FILE, 480,
                   L"[session], accepted from, port id: %u, session id:%I64x, this:%p, ip:%s, port:%d, socket:%p",
                   port->_id, _id, this, Network::GetAddressStringW(ip), portNumber,
                   reinterpret_cast<void*>(_connection->_socket));  // LobbyGate 0x17ee8: _connection(+0x40)->_socket(+8)
    return true;
}

// 0xEA40
bool Session::tryReconnect(long timeout)
{
    AsyncConnectContext* context = _connectContext;
    Log::Write(Log::LT_DEBUG, SESSION_FILE, 528,
               L"[session], trying to reconnect after %d msec, id:%I64x, this:%p, addr:(%s:%d)", timeout, _id, this,
               Network::GetAddressStringW(context->_remoteAddr.sin_addr.s_addr), ntohs(context->_remoteAddr.sin_port));
    if (!Network::_Run)
    {
        Log::Write(Log::LT_ERROR, SESSION_FILE, 532,
                   L"[session], network module is terminated; cancel reconnect, id:%I64x, this:%p", _id, this);
        return false;
    }
    if (_option != 2 || _reconnectTimer == nullptr)
    {
        Log::Write(Log::LT_ERROR, SESSION_FILE, 538,
                   L"[session], cannot reconnect session; option is not set or no timer, id:%I64x, this:%p", _id,
                   this);
        return false;
    }
    if (_state != CLOSED)
    {
        Log::Write(Log::LT_ERROR, SESSION_FILE, 544,
                   L"[session], connect is alive; cannot reconnect, id:%I64x, this:%p, state:%d", _id, this, _state);
        return false;
    }
    if (context->_timeout > 0)
    {
        long long remain = context->_timeout - (GetTickCount64() - Daemon::Instance->StartSystemTick64);
        if (remain <= 0)
        {
            Log::Write(Log::LT_DEBUG, SESSION_FILE, 550, L"[session], connect timeout, id:%I64x, this:%p", _id, this);
            return false;
        }
    }
    _state = POSTPONE_CONNECTING;
    if (_connectCount == 0)
        return reconnect();
    if (Daemon::Instance->AddTimer(timeout, reinterpret_cast<Timer*>(_reconnectTimer)))
        return true;
    Log::Write(Log::LT_ERROR, SESSION_FILE, 561,
               L"[session], reconnect failed; add to global timer error, id:%I64x, this:%p", _id, this);
    return false;
}

// 0xEC40
bool Session::reconnect()
{
    if (!Network::_Run)
    {
        Log::Write(Log::LT_ERROR, SESSION_FILE, 583,
                   L"[session], network module is terminated; cancel reconnect, id:%I64x, this:%p", _id, this);
        return false;
    }
    if (_state != POSTPONE_CONNECTING)
    {
        Log::Write(Log::LT_ERROR, SESSION_FILE, 589, L"[session], invalid state; cancel reconnect, id:%I64x, this:%p, state:%d",
                   _id, this, _state);
        return false;
    }
    AsyncConnectContext* context = _connectContext;
    if (++context->_tryReconnectCount > 5)
    {
        closesocket(context->_socket);
        context->_socket = INVALID_SOCKET;
        context->_tryReconnectCount = 0;
    }
    _state = CONNECTING;
    _connectPending = true;
    context->_firstConnect = false;
    if (_connection->AsyncConnect(context, _port->_nagle))
        return true;
    Log::Write(Log::LT_DEBUG, SESSION_FILE, 609,
               L"[session], trying to reconnect after %d msec, id:%I64x, this:%p, addr:(%s:%d)", 5000, _id, this,
               Network::GetAddressStringW(context->_remoteAddr.sin_addr.s_addr), ntohs(context->_remoteAddr.sin_port));
    _state = POSTPONE_CONNECTING;
    _connectPending = false;
    if (Daemon::Instance->AddTimer(5000, reinterpret_cast<Timer*>(_reconnectTimer)))
        return true;
    Log::Write(Log::LT_ERROR, SESSION_FILE, 615,
               L"[session], reconnect failed; add to global timer error, id:%I64x, this:%p, error:%d", _id, this,
               WSAGetLastError());
    return false;
}

// 0xEE30
void Session::Close(bool graceful)
{
    EnterCriticalSection(&_lock.CS);
    bool removed = close(graceful);
    LeaveCriticalSection(&_lock.CS);
    if (removed)
        _port->RemoveSession(this);
}

// 0xEE90
bool Session::close(bool force)
{
    if (_state == FORCE_CLOSING || force)
    {
        _state = FORCE_CLOSING;
    }
    else
    {
        _state = CLOSING;
        if (_sendPending)
        {
            Log::Write(Log::LT_DEBUG, SESSION_FILE, 654, L"[session], something remain to send, id:%I64x, this:%p",
                       _id, this);
            goto check_state;
        }
    }
    if (_connection->_socket != INVALID_SOCKET)
    {
        closesocket(_connection->_socket);
        _connection->_socket = INVALID_SOCKET;
    }

check_state:
    // BUG: 0xEE90 _state is CLOSING or FORCE_CLOSING here, so the POSTPONE_CONNECTING branch never runs.
    if (_state == POSTPONE_CONNECTING)
    {
        if (_reconnectTimer != nullptr)
        {
            bool result = Daemon::Instance->RemoveTimer(reinterpret_cast<Timer*>(_reconnectTimer));
            Log::Write(Log::LT_DEBUG, SESSION_FILE, 671,
                       L"[session], close called; stop reconnect, id:%I64x, this:%p, state:%d, result:%s", _id, this,
                       _state, result ? L"true" : L"false");
            return result;
        }
        goto keep_session;
    }
    if (_state == CLOSED || _recvPending || _sendPending || _connectPending || _connection->_socket != INVALID_SOCKET)
        goto keep_session;

    _recvBuffer->_recvdSize = 0;
    _sendBuffer->Clear();
    _state = CLOSED;
    // LIFT: LTCG folded the tryReconnect argument. The callee does not read edx and uses 5000 (LobbyGate 0x180f4).
    if (_option == 2 && tryReconnect(5000))
        goto keep_session;
    if (Daemon::Instance->allowClientSessionLifeCycleInLogs || static_cast<unsigned int>(_id >> 32) != 1)
        Log::Write(Log::LT_DEBUG, SESSION_FILE, 707, L"[session], close called; remove session, id:%I64x, this:%p, state:%d",
                   _id, this, _state);
    return true;

keep_session:
    Log::Write(Log::LT_DEBUG, SESSION_FILE, 714,
               L"[session], close called; don't remove session, id:%I64x, this:%p, state:%d", _id, this, _state);
    return false;
}

// 0xF090
// LIFT: noinline. The original HandleEvent calls this function in all 4 exes. VS2010 /LTCG inlines it without the attribute.
__declspec(noinline) bool Session::Recv()
{
    EnterCriticalSection(&_lock.CS);
    bool result = recv();
    LeaveCriticalSection(&_lock.CS);
    return result;
}

// 0xF0D0
bool Session::recv()
{
    if (_state != CONNECTED || _connection->_socket == INVALID_SOCKET || _recvBuffer == nullptr)
    {
        Log::Write(Log::LT_DEBUG, SESSION_FILE, 732, L"[session], recv error, not connected, id:%I64x, this:%p, state:%d",
                   _id, this, _state);
        return false;
    }
    // CG 0xf0d0: the context pointer first; the store through it makes the compiler read _recvBuffer again.
    AsyncRecvContext* context = &_recvBuffer->_context;
    context->_wsaBuffer.len = 4008 - _recvBuffer->_recvdSize;
    context->_wsaBuffer.buf = &_recvBuffer->_buffer[_recvBuffer->_recvdSize];
    // LIFT: AsyncRecv does not read the second argument; it sets r8 to 0 (LobbyGate 0x27264). r8 holds the recv buffer.
    // CG 0xf0d0 puts the failure block first.
    if (!_connection->AsyncRecv(context, reinterpret_cast<unsigned int*>(_recvBuffer)))
    {
        Log::Write(Log::LT_ERROR, SESSION_FILE, 743,
                   L"[session], recv error; Connection::AsyncRecv failed, id:%I64x, this:%p, error:%d", _id, this,
                   WSAGetLastError());
        return false;
    }
    _recvPending = true;
    return true;
}

// 0xF1C0
bool Session::HandleEvent(EventContext* context, unsigned long numOfBytes)
{
    unsigned __int64 id;    // LIFT: 0xf1c0 shared Log::Write tail arguments
    int error;
    wchar_t const* format;
    int line;
    switch (context->_id)
    {
    case EVID_IO_CONNECT:
    {
        // 0xf1c0 hr line 1074: the original reads _connectContext. That form lowered the score (98.5 -> 97.4). ❓
        AsyncConnectContext* connectContext = static_cast<AsyncConnectContext*>(context);
        bool firstConnect = connectContext->_firstConnect;
        if (!_connection->CompleteAsyncConnect(connectContext))
        {
            Log::Write(Log::LT_ERROR, SESSION_FILE, 824, L"[session], CompleteAsyncConnect failed, id:%I64x, this:%p, error:%d",
                       _id, this, WSAGetLastError());
            return false;
        }
        EnterCriticalSection(&_lock.CS);
        _state = CONNECTED;
        connectContext->_timeout = 0;
        ++_connectCount;
        LeaveCriticalSection(&_lock.CS);
        if (!_port->_sessionHandler->OnConnect(this, firstConnect))
        {
            _port->_sessionHandler->OnClose(this, _option == 2);
            Log::Write(Log::LT_ERROR, SESSION_FILE, 838, L"[session], OnConnect failed, id:%I64x, this:%p", _id, this);
            return false;
        }
        EnterCriticalSection(&_lock.CS);
        bool result = recv();
        if (result)
            _connectPending = false;
        LeaveCriticalSection(&_lock.CS);
        if (result)
            return true;
        int error = WSAGetLastError();
        _port->_sessionHandler->OnClose(this, _option == 2);
        Log::Write(Log::LT_ERROR, SESSION_FILE, 854, L"[session], first recv error, id:%I64x, this:%p, error:%d", _id,
                   this, error);
        return false;
    }
    case EVID_IO_RECV:
    {
        if (numOfBytes == 0)
        {
            Log::Write(Log::LT_ERROR, SESSION_FILE, 780, L"[session], recv zero; socket has closed, id:%I64x, this:%p",
                       _id, this);
            return false;
        }
        unsigned int total = numOfBytes + _recvBuffer->_recvdSize;
        if (total > 4008 || (_recvBuffer->_recvdSize = total) == 0)  // ❓ the original also tests the new size for 0
        {
            Log::Write(Log::LT_ERROR, SESSION_FILE, 785, L"[session], invalid received size, id:%I64x, this:%p, bytes:%d",
                       _id, this, numOfBytes);
            return false;
        }
        if (!handlePacket())
        {
            Log::Write(Log::LT_DEBUG, SESSION_FILE, 791, L"[session], handle packet failed, id:%I64x, this:%p", _id,
                       this);
            return false;
        }
        if (!Recv())
        {
            // LIFT: 0xf1c0 the original shares one Log::Write tail for lines 796 and 814 (merged tail).
            id = _id;
            error = WSAGetLastError();
            format = L"[session], next recv error, id:%I64x, this:%p, error:%d";
            line = 796;
            goto logDebugError;
        }
        if (_port->_idleStateTable != nullptr)
        {
            _lastRecvTime = GetTickCount64() - Daemon::Instance->StartSystemTick64;
            IdleStateTable* table = _port->_idleStateTable;
            int index = static_cast<int>(_idleStatePos >> 32);
            short slot = static_cast<short>(_idleStatePos >> 16);
            unsigned char slotByte = static_cast<unsigned char>(_idleStatePos >> 16);
            table->_table[index] &= ~IdleStateTable::STATE_MASK[slot];
            table->_table[index] |= 1 << (2 * (3 - slotByte));
        }
        return true;
    }
    case EVID_IO_SEND:
    {
        EnterCriticalSection(&_lock.CS);
        bool result = sendNext(numOfBytes);
        LeaveCriticalSection(&_lock.CS);
        if (result)
            return true;
        id = _id;
        error = WSAGetLastError();
        format = L"[session], next send error, id:%I64x, this:%p, error:%d";
        line = 814;
        goto logDebugError;
    }
    default:
        Log::Write(Log::LT_ERROR, SESSION_FILE, 862, L"== CRASH == [session], invalid event, id:%I64x, this:%p, context:%d",
                   _id, this, context->_id);
        AlertSender::Write(SESSION_FILE, 862, L"== CRASH == [session], invalid event, id:%I64x, this:%p, context:%d",
                           _id, this, context->_id);
        return true;
    }
logDebugError:
    Log::Write(Log::LT_DEBUG, SESSION_FILE, line, format, id, this, error);
    return false;
}

// 0xF5D0
void Session::HandleFailedEvent(EventContext* context, unsigned long numOfBytes)
{
    // LIFT: each case has its own close and Leave (PDB lines 906-910, 913-918, 921-925 of CacheGate 0xf5d0).
    // The compiler merges the 3 tails into one.
    bool removed;
    switch (context->_id)
    {
    case EVID_IO_RECV:
    {
        IdleStateTable* table = _port->_idleStateTable;
        if (table != nullptr)
        {
            table->SetNotAvailable(_id);  // inlined (CG 0xf5d0)
        }
        _port->_sessionHandler->OnClose(this, _option == 2);
        EnterCriticalSection(&_lock.CS);
        _recvPending = false;
        removed = close(false);
        LeaveCriticalSection(&_lock.CS);
        break;
    }
    case EVID_IO_SEND:
        EnterCriticalSection(&_lock.CS);
        _sendPending = false;
        _sendBuffer->Clear();
        removed = close(false);
        LeaveCriticalSection(&_lock.CS);
        break;
    case EVID_IO_CONNECT:
        EnterCriticalSection(&_lock.CS);
        _connectPending = false;
        removed = close(false);
        LeaveCriticalSection(&_lock.CS);
        break;
    default:
        Log::Write(Log::LT_ERROR, SESSION_FILE, 928, L"== CRASH == [session], invalid event, id:%I64x, this:%p, context:%d",
                   _id, this, context->_id);
        AlertSender::Write(SESSION_FILE, 928, L"== CRASH == [session], invalid event, id:%I64x, this:%p, context:%d",
                           _id, this, context->_id);
        return;
    }
    if (removed)
        _port->RemoveSession(this);
}

// 0xF750
bool Session::handlePacket()
{
    // ~Packet() calls Clear() on each return (0xF750 has one unwind state).
    // 0xF750 sets Splitter and IsFragmentPacket, then zeroes 28 bytes from FragmentPacketCmd (inline).
    Packet packet = {nullptr, false};
    unsigned int offset = 0;
    while (_minPacketSize <= _recvBuffer->_recvdSize - offset)
    {
        char const* pkt = nullptr;
        // LobbyGate 0x18cc4: the 5th argument is 0xFA8 - _recvdSize (free space), not 0xFA8 - offset.
        int size = _bufferHandler->ToPacket(this, &_recvBuffer->_buffer[offset], _recvBuffer->_recvdSize - offset,
                                            4008 - _recvBuffer->_recvdSize, &pkt);
        if (size < 0)
            return false;
        if (size == 0)
            break;
        if (pkt == nullptr)
            SESSION_ASSERT_CRASH(L"source\\Packet.cpp", "source\\Packet.cpp", 626);
        packet.Clear();
        packet.CurHeader = reinterpret_cast<Packet::Header*>(const_cast<char*>(pkt));
        if (_port->_enableRecv && !_port->_sessionHandler->PacketHandler(this, &packet))
        {
            Log::Write(Log::LT_ERROR, SESSION_FILE, 984,
                       L"[session], packet handler failed, id:%I64x, this:%p, port-running:%s", _id, this,
                       _port->_enableRecv ? L"true" : L"false");
            return false;
        }
        offset += size;
    }
    SessionRecvBuffer* recvBuffer = _recvBuffer;
    unsigned int recvdSize = recvBuffer->_recvdSize;
    // 0xF750: the original puts the good path first and the error block last.
    if (offset <= recvdSize)
    {
        if (offset < recvdSize)
            memmove(recvBuffer->_buffer, &recvBuffer->_buffer[offset], recvdSize - offset);
        recvBuffer->_recvdSize -= offset;
        return true;
    }
    Log::Write(Log::LT_ERROR, SESSION_FILE, 998, L"[session], clear recv buffer error, id:%I64x, this:%p", _id, this);
    return false;
}

// 0xF960
bool Session::SetChannel(Channel* channel)
{
    if (_channel != nullptr)
        return false;
    channel->addReferenceCount(false, SESSION_FILE, 0x403);
    _channel = channel;
    return true;
}

// 0x1D330 (SmartCouponDaemon). The callers inline it.
Channel* Session::GetChannel() const
{
    if (_channel == nullptr || _waitForRelease)
        return nullptr;
    _channel->addReferenceCount(false, SESSION_FILE, 1051);
    return _channel;
}

// 0xF9B0
void Session::StopReconnect() const
{
    Session* self = const_cast<Session*>(this);
    EnterCriticalSection(&self->_lock.CS);
    if (self->_option == 2)
    {
        self->_option = 1;
        if (self->_reconnectTimer != nullptr)
            Daemon::Instance->RemoveTimer(reinterpret_cast<Timer*>(self->_reconnectTimer));
    }
    LeaveCriticalSection(&self->_lock.CS);
}

// 0xFA10
void Session::Send(char const* format, ...) const
{
    va_list args;
    va_start(args, format);
    SendV(format, args);
    va_end(args);
}

// 0xFA40
// LIFT: per-exe form, CG 0xfa40 and LG 0x18f00 call it out of line (noinline). SCD and POD inline it (no function).
#if defined(LIFT_EXE_CG) || defined(LIFT_EXE_LG)
__declspec(noinline)
#endif
void Session::Send(Packet const* packet) const
{
    Session* self = const_cast<Session*>(this);
    packet->ListHead->encrypt(_currentCrypt, _security3rd);
    PacketBuffer const* list[1];
    list[0] = packet->ListHead;
    EnterCriticalSection(&self->_lock.CS);
    send(list, 1);
    LeaveCriticalSection(&self->_lock.CS);
}

// 0xFAA0
void Session::SendV(char const* format, char* args) const
{
    Session* self = const_cast<Session*>(this);
    if (format == nullptr)
        SESSION_ASSERT_CRASH(SESSION_FILE, "source\\Session.cpp", 1153);
    Packet packet = {nullptr, false};
    PacketBuffer* buffer = PacketBufferAllocator::_Local->allocate();
    packet.ListTail = buffer;
    packet.ListHead = buffer;
    packet.CurHeader = reinterpret_cast<Packet::Header*>(&buffer->Buffer[8]);
    packet.CurHeader->size = 2;
    int size = static_cast<short>(
        PacketBuffer::Compose(reinterpret_cast<char*>(packet.CurHeader) + packet.CurHeader->size,
                              4000 - packet.CurHeader->size, format, static_cast<unsigned long long>(-1), args));
    if (static_cast<unsigned short>(4000 - packet.CurHeader->size) < size)
        SESSION_ASSERT_CRASH(L"source\\Packet.cpp", "source\\Packet.cpp", 307);
    packet.CurHeader->size += static_cast<short>(size);
    buffer->encrypt(_currentCrypt, _security3rd);
    PacketBuffer const* list[1];
    list[0] = buffer;
    EnterCriticalSection(&self->_lock.CS);
    send(list, 1);
    LeaveCriticalSection(&self->_lock.CS);
}

// 0xFC40
PacketConcatenater* Session::SetPacketConcatenater(PacketConcatenater const* concatenater) const
{
    Session* self = const_cast<Session*>(this);
    if (concatenater == nullptr)
    {
        Log::Write(Log::LT_ERROR, SESSION_FILE, 1209,
                   L"== CRASH == [session], packet concatenater parameter is NULL, id:%I64x, this:%p", _id, this);
        AlertSender::Write(SESSION_FILE, 1209,
                           L"== CRASH == [session], packet concatenater parameter is NULL, id:%I64x, this:%p", _id,
                           this);
        return nullptr;
    }
    if (_concatenater != nullptr)
    {
        Log::Write(Log::LT_ERROR, SESSION_FILE, 1215,
                   L"== CRASH == [session], packet concatenater is already set, id:%I64x, this:%p", _id, this);
        AlertSender::Write(SESSION_FILE, 1215,
                           L"== CRASH == [session], packet concatenater is already set, id:%I64x, this:%p", _id, this);
        return nullptr;
    }
    void* buffer = nullptr;
    if (concatenater->AllocSize() != 0)
        buffer = self->_allocator.Alloc(concatenater->AllocSize(), SESSION_FILE, 1222);
    self->_concatenater = concatenater->Clone(buffer);
    return self->_concatenater;
}

// 0xFD80
void Session::deallocate_me(void* ptr, wchar_t const* file, int line)
{
    if (_createdPort - 1 <= 23)
    {
        Port* port = Network::Instance->_port[_createdPort - 1];
        if (port != nullptr)
            port->_pool->RemoveSession(this);
    }
}

// 0xFDC0
bool Session::sendNext(unsigned long sentSize)
{
    if ((_state != CONNECTED && _state != CLOSING) || _connection->_socket == INVALID_SOCKET)
        return false;
    AsyncSendContext* context = _sendBuffer->RemoveSentBuffer(sentSize);
    if (context == nullptr)
    {
        if (_state != CLOSING)
        {
            _sendPending = false;
            return true;
        }
        return false;
    }
    SOCKET socket = _connection->_socket;
    if (socket == INVALID_SOCKET)
        return false;
    DWORD sent = 0;
    SendBufferList* list = context->_bufferList;
    if (WSASend(socket, static_cast<WSABUF*>(list->_wsaBuffer), list->_count, &sent, 0, context, nullptr)
        == SOCKET_ERROR)
    {
        int error = WSAGetLastError();
        if (error != WSA_IO_PENDING)
        {
            Log::Write(L"source\\Connection.cpp", 225, error, L"WSASend()");
            return false;
        }
    }
    _sendPending = true;
    return true;
}

// 0xFE90
// LIFT: noinline. LG 0x19360 calls it out of line in ClientManager::broadcast. VS2010 /LTCG inlined it there. CG, SCD, POD: no change.
__declspec(noinline) bool Session::send(PacketBuffer const** const pbufferList, int count) const
{
    Session* self = const_cast<Session*>(this);
    if (_state != CONNECTED || _connection->_socket == INVALID_SOCKET)
    {
        Log::Write(Log::LT_ERROR, SESSION_FILE, 1290,
                   L"[session], cannot send packet; not connected, id:%I64x, this:%p, state:%d, socket:%I32x", _id,
                   this, _state, static_cast<unsigned int>(_connection->_socket));
        return false;
    }
    AsyncSendContext* context = _sendBuffer->Add(pbufferList, count);
    if (context != nullptr)
    {
        if (!_connection->AsyncSend(context))
        {
            Log::Write(Log::LT_ERROR, SESSION_FILE, 1300,
                       L"[session], cannot send packet; async send failed, id:%I64x, this:%p, state:%d, socket:%I32x, "
                       L"error:%d",
                       _id, this, _state, static_cast<unsigned int>(_connection->_socket), WSAGetLastError());
            return false;
        }
        self->_sendPending = true;
    }
    return true;
}

// PDB Thread_LastCryptError (LobbyGate Session.obj, TLS 0x9a010).
__declspec(thread) PacketCrypt::ErrCode Thread_LastCryptError;

// PacketCrypt::InstanceSize (0x4CC60) and PacketCrypt::Create (0x4CCE0): src/Security/source/BloodPacketCrypt/PacketCrypt.cpp.

// 0x19460 (LobbyGate)
// LIFT: noinline. The orig calls it out of line at all call sites (LG 0x19460: not inlined).
// LIFT: inline_depth(0). LG 0x19460 calls PacketCrypt::InstanceSize (0x4cc60) out of line (lessons A20).
#pragma inline_depth(0)
__declspec(noinline) void* Session::allocateCrypt(PacketCrypt::Type type, PacketCrypt::Algorithm algorithm) const
{
    // LIFT: LTCG removed the algorithm param from InstanceSize and Create. Create gets (type, buffer, size)
    // (LobbyGate 0x1946d, tail jump 0x194ac).
    Session* self = const_cast<Session*>(this);
    int size = PacketCrypt::InstanceSize(type, algorithm);
    if (size <= 0)
        return nullptr;
    unsigned char* buffer = static_cast<unsigned char*>(self->_allocator.Alloc(size, SESSION_FILE, 1320));
    return PacketCrypt::Create(type, algorithm, buffer, size);
}
#pragma inline_depth()

// 0x194C0 (LobbyGate). The CacheGate ~Session (0xE0A0) inlines it.
// LIFT: per-exe form, only LG 0x194c0 has the function (noinline). CG, SCD and POD inline it in ~Session.
#if defined(LIFT_EXE_LG)
__declspec(noinline)
#endif
void Session::deallocateCrypt(void* crypt) const
{
    Session* self = const_cast<Session*>(this);
    PacketCrypt* packetCrypt = static_cast<PacketCrypt*>(crypt);
    if (crypt == nullptr)  // LobbyGate 0x194c0 tests crypt in the function
        return;
    // LIFT: the orig test is a compare chain (LobbyGate 0x194c0: v == 0, v - 1, v - 2, v - 3 <= 1; no constants 2, 3, 4).
    int type = packetCrypt->GetType();
    int rest1;
    int rest2;
    if (type == 0 || ((rest1 = type - 1) != 0 && ((rest2 = rest1 - 1) == 0 || static_cast<unsigned int>(rest2 - 1) <= 1)))
        packetCrypt->~PacketCrypt();  // vtable slot 7 (deleting destructor) with flag 0 = no free (LobbyGate 0x194f9)
    self->_allocator.Free(crypt, SESSION_FILE, 1331);
}

// 0x19530 (LobbyGate)
bool Session::SetHandshakeParameter(unsigned char const* param, int paramSize, unsigned char* replyParam,
                                    int* replyParamSize) const
{
    Session* self = const_cast<Session*>(this);
    if (_cryptMode != 2)
    {
        Log::Write(Log::LT_ERROR, SESSION_FILE, 1341, L"[session], invalid crypt mode, id:%I64x, this:%p, mode:%d", _id,
                   this, _cryptMode);
        return false;
    }
    PacketCrypt* currentCrypt = _currentCrypt;
    if (currentCrypt == nullptr || _handshakeCrypt == nullptr || _sessionCrypt != nullptr)
    {
        Log::Write(Log::LT_ERROR, SESSION_FILE, 1346, L"[session], invalid crypt step, id:%I64x, this:%p", _id, this);
        return false;
    }
    PacketCrypt::ErrCode errCode = currentCrypt->SetKey(param, paramSize);
    Thread_LastCryptError = errCode;
    if (errCode != PacketCrypt::SPCE_NO_ERROR)
    {
        Log::Write(Log::LT_ERROR, SESSION_FILE, 1363,
                   L"[session], cannot set handshake key, id:%I64x, this:%p, error-code:%d", _id, this, errCode);
        return false;
    }
    unsigned char keybuf[64];
    int keybufCnt = 64;
    errCode = currentCrypt->GenerateKey(keybuf, &keybufCnt, replyParam, replyParamSize);
    Thread_LastCryptError = errCode;
    if (errCode != PacketCrypt::SPCE_NO_ERROR)
    {
        Log::Write(Log::LT_ERROR, SESSION_FILE, 1373,
                   L"[session], cannot generate session key, id:%I64x, this:%p, error-code:%d", _id, this, errCode);
        return false;
    }
    // LIFT: LTCG removed the algorithm param of allocateCrypt (LobbyGate 0x1946d).
    self->_sessionCrypt = static_cast<PacketCrypt*>(allocateCrypt(PacketCrypt::SESSION_CRYPT, PacketCrypt::ALGORITHM_DEFAULT));
    if (_sessionCrypt == nullptr)
    {
        // BUG: 0x196da the format has "this:%p", but the call does not give it.
        Log::Write(Log::LT_ERROR, SESSION_FILE, 1381, L"[session], cannot create session crypt, id:%I64x, this:%p", _id);
        return false;
    }
    errCode = _sessionCrypt->SetKey(keybuf, keybufCnt);
    Thread_LastCryptError = errCode;
    if (errCode == PacketCrypt::SPCE_NO_ERROR)
    {
        self->_cryptMode = 3;
        return true;
    }
    Log::Write(Log::LT_ERROR, SESSION_FILE, 1387,
               L"[session], cannot set session key, id:%I64x, this:%p, error-code:%d", _id, this, errCode);
    deallocateCrypt(_sessionCrypt);
    self->_sessionCrypt = nullptr;
    return false;
}

// 0x19790 (LobbyGate)
bool Session::FailHandshake() const
{
    Session* self = const_cast<Session*>(this);
    if (_cryptMode != 2 && _cryptMode != 3)
        return false;
    self->_cryptMode = 4;
    if (_handshakeCrypt != nullptr)
        _handshakeCrypt->SetEncryptParam(PacketCrypt::PARAM_HANDSHAKE_FAIL);
    return true;
}

// 0x197E0 (LobbyGate). deallocateCrypt is inlined.
// LIFT: noinline only in LG: the LG original keeps a call.
#if defined(LIFT_EXE_LG)
__declspec(noinline)
#endif
void Session::completeHandshake()
{
    PacketCrypt* handshakeCrypt = _handshakeCrypt;
    _cryptMode = 5;
    if (handshakeCrypt != nullptr)
    {
#if defined(LIFT_EXE_LG)
        // LIFT: LG 0x197e0 has the body of deallocateCrypt (0x194c0) in place, with no null test.
        int type = handshakeCrypt->GetType();
        int rest1;
        int rest2;
        if (type == 0 || ((rest1 = type - 1) != 0 && ((rest2 = rest1 - 1) == 0 || static_cast<unsigned int>(rest2 - 1) <= 1)))
            handshakeCrypt->~PacketCrypt();
        _allocator.Free(handshakeCrypt, SESSION_FILE, 1331);
#else
        deallocateCrypt(handshakeCrypt);
#endif
        _handshakeCrypt = nullptr;
    }
    _currentCrypt = _sessionCrypt;
}
