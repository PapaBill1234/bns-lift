// Port.obj (CacheGate PDB).
#include "Port.h"
#include <winsock2.h>
#include <windows.h>
#include <intrin.h>
#include <new>
#include "AlertSender.h"
#include "Channel.h"
#include "Connection.h"
#include "CrashHandler.h"
#include "Daemon.h"
#include "Listener.h"
#include "Log.h"
#include "Memory.h"
#include "PacketBufferHandler.h"
#include "Session.h"
#include "SysInfo.h"

static wchar_t const PORT_FILE[] = L"source\\Port.cpp";

// Inlined crash macro.
#define PORT_ASSERT_CRASH(line)                                                  \
    do                                                                           \
    {                                                                            \
        Log::Write(Log::LT_ERROR, PORT_FILE, line, L"== CRASH == ASSERT CRASH"); \
        AlertSender::Write(PORT_FILE, line, L"== CRASH == ASSERT CRASH");       \
        CrashHandler::MakeCrash("source\\Port.cpp", line, L"");                  \
    } while (0)

long long SessionPool::Allocated = 0;
long long SessionPool::Using = 0;

// 0x184E0
SessionPool::SessionPool(unsigned int portId)
    : _portId(portId), _valid(false), _useUnusedSessionReadOnly(false), _head(nullptr), _tail(nullptr),
      _allocator(SysInfo::MemnoryAllocationGranularity())
{
    _tag = 2058;
    _allocator.Initialize(0x2000);
}

// 0x18600 (0x185E0 vector deleting destructor)
SessionPool::~SessionPool()
{
    if (_valid)
    {
        Log::Write(Log::LT_ERROR, PORT_FILE, 43, L"== CRASH == [port], not cleared, id: %d", _portId);
        AlertSender::Write(PORT_FILE, 43, L"== CRASH == [port], not cleared, id: %d", _portId);
        _lock.Enter();
        _valid = false;
        _lock.Leave();
    }
}

// 0x186F0
bool SessionPool::Initialize(int maxSession, int prepareRatio, bool useUnusedSessionReadOnly)
{
    if (_valid)
    {
        Log::Write(Log::LT_ERROR, PORT_FILE, 54, L"== CRASH == [port], session pool is already initialized, id: %d",
                   _portId);
        AlertSender::Write(PORT_FILE, 54, L"== CRASH == [port], session pool is already initialized, id: %d", _portId);
        return false;
    }
    // LIFT: LTCG folded useUnusedSessionReadOnly to false (the binary stores 0).
    _useUnusedSessionReadOnly = useUnusedSessionReadOnly;
    int count = prepareRatio * maxSession / 100;
    for (int i = 0; i < count; ++i)
    {
        void* memory = _allocator.Alloc();
        Session* session = memory != nullptr ? new (memory) Session() : nullptr;
        addToPool(session);
        _InterlockedIncrement64(&Allocated);
    }
    _valid = true;
    return true;
}

// 0x18820
Session* SessionPool::MakeSession(PacketBufferHandler const* bufferHandler)
{
    Session* session = nullptr;
    {
        EnterCriticalSection(&_lock.CS);
        if (!_valid)
        {
            LeaveCriticalSection(&_lock.CS);
            Log::Write(Log::LT_ERROR, PORT_FILE, 89, L"[port], cannot make session, id: %d", _portId);
            return nullptr;
        }
        if (_useUnusedSessionReadOnly && !_sessionQueue.empty())
        {
            session = _sessionQueue.front();
            _sessionQueue.pop_front();
            DWORD oldProtect = 0;
            VirtualProtect(session, _allocator._allocSize, PAGE_READWRITE, &oldProtect);
        }
        else if (!_useUnusedSessionReadOnly && _head != nullptr)
        {
            session = _head;
            _head = session->_next;
            if (_head == nullptr)
                _tail = nullptr;
        }
        else
        {
            void* memory = _allocator.Alloc();
            session = memory != nullptr ? new (memory) Session() : nullptr;
            _InterlockedIncrement64(&Allocated);
        }
        LeaveCriticalSection(&_lock.CS);
    }
    if (session == nullptr)
    {
        Log::Write(Log::LT_ERROR, PORT_FILE, 133, L"[port], cannot make session, id: %d", _portId);
        return nullptr;
    }
    _InterlockedIncrement64(&Using);
    // BUG: 0x18820 a new session runs Session::Session() and then this constructor (no destructor between).
    new (session) Session(_portId, bufferHandler);
    addReferenceCount(PORT_FILE, 140);
    return session;
}

// 0x18A30
void SessionPool::RemoveSession(Session* session)
{
    if (session == nullptr)
    {
        Log::Write(Log::LT_ERROR, PORT_FILE, 149, L"== CRASH == [port], invalid session in removing, id: %d", _portId);
        AlertSender::Write(PORT_FILE, 149, L"== CRASH == [port], invalid session in removing, id: %d", _portId);
        return;
    }
    _InterlockedDecrement64(&Using);
    session->~Session();
    addToPool(session);
    removeReferenceCount(PORT_FILE, 156);
}

// 0x18AD0
void SessionPool::addToPool(Session* session)
{
    _lock.Enter();
    if (_useUnusedSessionReadOnly)
    {
        DWORD oldProtect = 0;
        VirtualProtect(session, _allocator._allocSize, PAGE_READONLY, &oldProtect);
        _sessionQueue.push_back(session);
    }
    else
    {
        if (_tail != nullptr)
            _tail->_next = session;
        else
            _head = session;
        _tail = session;
    }
    _lock.Leave();
}

// 0x18B70
bool Port::Initialize(unsigned int id, unsigned short portNumber, unsigned int maxSession, int initialMode,
                      bool enableRecv, bool nagle, void* iocpHandle, SessionHandler const* sessionHandler,
                      PacketBufferHandler const* bufferHandler)
{
    (void)enableRecv;  // LIFT: LTCG folded enableRecv. Initialize does not read it. OpenPort sets _enableRecv (LobbyGate 0x207a7).
    int prepareRatio = 100;
    if (_listener != nullptr || sessionHandler == nullptr)
        PORT_ASSERT_CRASH(216);
    _id = id;
    _portNumber = portNumber;
    _nagle = nagle;  // LobbyGate stores 0 (folded). PostOfficeDaemon gives nagle = 1 for the management port (0x13B59).
    _maxSession = maxSession;
    _sessionHandler = sessionHandler;
    _bufferHandler = bufferHandler->Clone(nullptr);
    switch (initialMode)
    {
    case 0:
        _initialMode = 2;
        break;
    case 1:
        _initialMode = 1;
        break;
    case 2:
    case 3:
        _initialMode = 1;
        prepareRatio = 0;
        break;
    default:
        PORT_ASSERT_CRASH(239);
        break;
    }
    void* memory = BASE_MEMORY_MANAGER.Alloc(sizeof(SessionPool), PORT_FILE, 243);
    _pool = memory != nullptr ? new (memory) SessionPool(_id) : nullptr;
    _pool->Initialize(_maxSession, prepareRatio, false);
    _unusedSessionIndex = 1;
    _sessionList = static_cast<Session**>(
        BASE_MEMORY_MANAGER.AllocZero(sizeof(Session*) * _maxSession, PORT_FILE, 248));
    _iocpHandle = iocpHandle;
    if (portNumber == 0)
        return true;
    void* listenerMemory = Memory::_Manager[2]->Alloc(sizeof(PortListener), PORT_FILE, 255);
    _listener = listenerMemory != nullptr ? new (listenerMemory) PortListener() : nullptr;
    if (_listener->Initialize(this, iocpHandle, portNumber))
        return true;
    Clear();
    clearPool();
    return false;
}

// 0x18DF0
void Port::Clear()
{
    _enableAccept = false;
    PortListener* listener = _listener;
    if (listener != nullptr)
    {
        // LIFT: 0x18df0 the original inlines PortListener::Clear here. Ours is noinline (PortListener::Initialize
        // calls it), so this is a copy of its body.
        SOCKET listenSocket = static_cast<SOCKET>(_InterlockedExchange64(
            reinterpret_cast<volatile long long*>(&listener->_socket), static_cast<long long>(INVALID_SOCKET)));
        if (listenSocket != INVALID_SOCKET)
        {
            closesocket(listenSocket);
            listener->_portInstance = nullptr;
            listener->removeReferenceCount(L"source\\Listener.cpp", 113);
        }
        _listener->removeReferenceCount(PORT_FILE, 280);
        _listener = nullptr;
    }
    if (_sessionList != nullptr)
    {
        for (unsigned int i = 0; i < _maxSession; ++i)
        {
            if (_sessionList[i] != nullptr)
                RemoveSession(_sessionList[i]);
        }
        BASE_MEMORY_MANAGER.Free(_sessionList, PORT_FILE, 295);
        _sessionList = nullptr;
    }
    _sessionHandler = nullptr;
    if (_bufferHandler != nullptr)
    {
        const_cast<PacketBufferHandler*>(_bufferHandler)->Destroy(nullptr);
        _bufferHandler = nullptr;
    }
    _id = 0;
    _iocpHandle = nullptr;
    _portNumber = 0;
    _enableAccept = false;
    _enableRecv = false;
    _nagle = false;
    _initialMode = 0;
    _maxSession = 0;
    _unusedSessionIndex = 0;
    _sessionCount = 0;
    SessionPool* pool = _pool;  // 0x18df0: the original reads _pool one time for the lock.
    if (pool != nullptr)
    {
        pool->_lock.Enter();
        pool->_valid = false;
        pool->_lock.Leave();
        _pool->removeReferenceCount(PORT_FILE, 319);
        _pool = nullptr;
    }
}

// LIFT: Inlined in Network::OpenPort (0xD2C0).
bool Port::StartAccept()
{
    if (_listener == nullptr)
    {
        Log::Write(Log::LT_ERROR, PORT_FILE, 330, L"Initialize first!");
        return false;
    }
    _enableAccept = true;
    return true;
}

// 0x18F40
Session* Port::MakeNewSession(unsigned long long* socket, unsigned long ip, unsigned short portNumber, int option)
{
    unsigned long long id = 0;
    Session* session = makeSession(id);
    if (session == nullptr)
        return nullptr;
    session->addReferenceCount(PORT_FILE, 387);
    if (!session->Accept(this, id, socket, ip, portNumber, option))
    {
        session->removeReferenceCount(PORT_FILE, 390);
        RemoveSession(session);
        return nullptr;
    }
    return session;
}

// 0x19010
bool Port::MakeNewSession(unsigned long ip, unsigned short portNumber, Channel* channel, long timeout, bool nagle,
                          bool reconnect, Session** session)
{
    unsigned long long id = 0;
    Session* newSession = makeSession(id);
    if (newSession == nullptr)
        return false;
    // BUG: 0x19010 if session is null, the new session stays in the session list (leak).
    if (session == nullptr)
        return false;
    newSession->addReferenceCount(PORT_FILE, 416);
    if (channel != nullptr)
        newSession->SetChannel(channel);
    *session = newSession;
    if (newSession->Connect(this, id, ip, portNumber, timeout, nagle, reconnect))
        return true;
    Channel* oldChannel = newSession->_channel;
    if (oldChannel != nullptr)
    {
        newSession->_channel = nullptr;
        oldChannel->removeReferenceCount(PORT_FILE, 427);
    }
    *session = nullptr;
    newSession->removeReferenceCount(PORT_FILE, 430);
    RemoveSession(newSession);
    return false;
}

// 0x19120
bool Port::RemoveSession(Session* session)
{
    if (session == nullptr)
        PORT_ASSERT_CRASH(450);
    unsigned int index = static_cast<unsigned int>(session->_id);
    if (index >= _maxSession)
        PORT_ASSERT_CRASH(453);
    Session* removed = nullptr;
    _sessionLock.Enter();
    if (_sessionList[index] == session)
    {
        removed = session;
        _sessionList[index] = nullptr;
        --_sessionCount;
        removed->removeReferenceCount(PORT_FILE, 462);
    }
    _sessionLock.Leave();
    if (removed == nullptr)
        return false;
    if (Daemon::Instance->allowClientSessionLifeCycleInLogs || _id != 1)
        Log::Write(Log::LT_DEBUG, PORT_FILE, 480, L"[session], removed, port-id:%u, session-id:%I64x, session:%p", _id,
                   static_cast<unsigned long long>(index) | (static_cast<unsigned long long>(_id) << 32), session);
    return true;
}

// 0x192A0
void Port::ReconnectSession(unsigned long long id)
{
    if (static_cast<unsigned int>(id >> 32) != _id)
        PORT_ASSERT_CRASH(552);
    if (static_cast<unsigned int>(id) >= _maxSession)
        PORT_ASSERT_CRASH(553);
    Session* session = nullptr;
    _sessionLock.Enter();
    {
        Session* found = _sessionList[static_cast<unsigned int>(id)];
        if (found != nullptr && found->_id == id && found->_option == 2 &&
            (found->_state != Session::CONNECTED || found->_connection->_socket == INVALID_SOCKET))
        {
            session = found;
            session->addReferenceCount(PORT_FILE, 561);
        }
    }
    _sessionLock.Leave();
    if (session == nullptr)
        return;
    bool reconnected;
    session->_lock.Enter();
    reconnected = session->reconnect();
    session->_lock.Leave();
    if (reconnected)
    {
        session->removeReferenceCount(PORT_FILE, 580);
    }
    else
    {
        RemoveSession(session);
        session->removeReferenceCount(PORT_FILE, 576);
    }
}

// 0x25F20 (LobbyGate)
void Port::CloseSession(unsigned long long sessionId, bool force)
{
    if (static_cast<unsigned int>(sessionId >> 32) != _id)
        PORT_ASSERT_CRASH(523);
    if (static_cast<unsigned int>(sessionId) >= _maxSession)
        PORT_ASSERT_CRASH(524);
    _sessionLock.Enter();
    Session* session = _sessionList[static_cast<unsigned int>(sessionId)];
    if (session != nullptr && session->_id == sessionId)
        session->addReferenceCount(PORT_FILE, 531);
    else
        session = nullptr;
    _sessionLock.Leave();
    if (session == nullptr)
        return;
    session->_lock.Enter();
    bool closed = session->close(force);
    session->_lock.Leave();
    if (closed)
        session->_port->RemoveSession(session);
    session->removeReferenceCount(PORT_FILE, 543);
}

// 0x26220 (LobbyGate)
long long Port::GetSessionLastRecvTime(unsigned long long sessionId)
{
    long long lastRecvTime = 0;
    if (static_cast<unsigned int>(sessionId >> 32) != _id)
        PORT_ASSERT_CRASH(590);
    if (static_cast<unsigned int>(sessionId) >= _maxSession)
        PORT_ASSERT_CRASH(591);
    _sessionLock.Enter();
    Session* session = _sessionList[static_cast<unsigned int>(sessionId)];
    if (session != nullptr)
        lastRecvTime = session->_lastRecvTime;
    _sessionLock.Leave();
    return lastRecvTime;
}

// 0x19420
Session* Port::makeSession(unsigned long long& id)
{
    if (_sessionCount >= _maxSession)
    {
        Log::Write(Log::LT_ERROR, PORT_FILE, 613, L"Session List if full, %d", _maxSession);
        return nullptr;
    }
    Session* session = _pool->MakeSession(_bufferHandler);
    if (session == nullptr)
        return nullptr;
    id = 0;
    _sessionLock.Enter();
    {
        int maxSession = static_cast<int>(_maxSession);
        for (int i = 0; i < maxSession; ++i)
        {
            if (_unusedSessionIndex != 0 && _sessionList[_unusedSessionIndex] == nullptr)
            {
                _sessionList[_unusedSessionIndex] = session;
                ++_sessionCount;
                id = static_cast<unsigned long long>(_unusedSessionIndex) | (static_cast<unsigned long long>(_id) << 32);
                _unusedSessionIndex = (_unusedSessionIndex + 1) % _maxSession;
                break;
            }
            _unusedSessionIndex = (_unusedSessionIndex + 1) % static_cast<unsigned int>(maxSession);
        }
    }
    _sessionLock.Leave();
    if (id == 0)
    {
        session->removeReferenceCount(PORT_FILE, 650);
        Log::Write(Log::LT_ERROR, PORT_FILE, 651, L"[port], Cannot find empty slot in session list, id: %d", _id);
        return nullptr;
    }
    if (Daemon::Instance->allowClientSessionLifeCycleInLogs || _id != 1)
        Log::Write(Log::LT_DEBUG, PORT_FILE, 660, L"[session], created, port-id:%u, session-id:%I64x, session:%p", _id, id,
                   session);
    return session;
}

// 0x195A0
void Port::clearPool()
{
    SessionPool* pool = _pool;  // 0x195a0: the original reads _pool one time for the lock.
    if (pool != nullptr)
    {
        pool->_lock.Enter();
        pool->_valid = false;
        pool->_lock.Leave();
        _pool->removeReferenceCount(PORT_FILE, 672);
        _pool = nullptr;
    }
}
