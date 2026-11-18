// Network.obj (CacheGate PDB).
#include "Network.h"
#include <new>
#include <string.h>
#include <intrin.h>
#include <windows.h>
#include "AlertSender.h"
#include "CrashHandler.h"
#include "CryptoKey.h"
#include "Daemon.h"
#include "IdleWatcher.h"
#include "IoWorkerThread.h"
#include "Log.h"
#include "Memory.h"
#include "MemoryManager.h"
#include "PacketBuffer.h"
#include "Port.h"
#include "SysInfo.h"
#include "Thread.h"

static wchar_t const NETWORK_FILE[] = L"source\\Network.cpp";

// Inlined crash macro.
#define NETWORK_ASSERT_CRASH(line)                                                  \
    do                                                                              \
    {                                                                               \
        Log::Write(Log::LT_ERROR, NETWORK_FILE, line, L"== CRASH == ASSERT CRASH"); \
        AlertSender::Write(NETWORK_FILE, line, L"== CRASH == ASSERT CRASH");       \
        CrashHandler::MakeCrash("source\\Network.cpp", line, L"");                  \
    } while (0)

int PacketCrypt::_MaxSize = 0;

// 0x327E0 (PacketCrypt module). Inlined in Network::Initialize (LobbyGate 0x20192-0x201aa).
PacketCrypt::ErrCode PacketCrypt::Setup(int maxSize)
{
    if (_MaxSize > 0)
        return ALREADY_INITIALIZED;
    _MaxSize = maxSize;
    CryptoKey::Initialize();  // LobbyGate 0x201a5. The original ignores the result.
    return SPCE_NO_ERROR;
}

// 0xCD60 EventObject::~EventObject / DynamicEventObject::~DynamicEventObject (folded):
// compiler-generated. See TimerQueue.h.

// 0x2350 (CacheGate PDB; folded with DynamicRefCntObj::deallocate_me). LobbyGate 0x1330.
void DynamicEventObject::deallocate_me(void* ptr, wchar_t const* file, int line)
{
    this->~DynamicEventObject();
    Memory::_Manager[2]->Free(ptr, file, line);
}

// LIFT: name; CacheGate .rdata 0x4e408 = {10000, 10000, 16, 16}, indexed by initialMode at 0xd40b-0xd412.
static unsigned int const s_defaultMaxSession[4] = {10000, 10000, 16, 16};

// GetAddressStringW (LobbyGate 0x20b20) uses TLS slot 0 +0x40 char[32] (strcpy_s size 0x20, 0x20b5e) and +0x60 wchar_t[32] (cch 0x1F, 0x20b7d).
// PDB (CacheGate Network.obj): S_LTHREAD32 __ip_addr_string_w__ at .tls+0x60. The char name is not in the PDB symbols. ❓
static __declspec(thread) char __ip_addr_string_a__[32];
static __declspec(thread) wchar_t __ip_addr_string_w__[32];

ThreadManager* Network::WorkerManager;
EventObject* Network::EndEventObject;
bool Network::_Run;
Network* Network::Instance;
LPFN_ACCEPTEX Network::AcceptExFunc;
LPFN_GETACCEPTEXSOCKADDRS Network::AcceptSockAddrsFunc;
LPFN_CONNECTEX Network::ConnectExFunc;
LPFN_DISCONNECTEX Network::DisconnectExFunc;

// 0xCD70
unsigned int NetworkEndEvent::EventId() const
{
    return 1;
}

// 0xCD80
bool NetworkEndEvent::HandleEvent(EventContext* context, unsigned long numOfBytes)
{
    return true;
}

// 0xCDB0
Network::Network()
{
    if (Instance != nullptr)
        NETWORK_ASSERT_CRASH(52);
    Instance = this;
    WorkerManager = nullptr;
    void* memory = Memory::_Manager[2]->Alloc(sizeof(NetworkEndEvent), NETWORK_FILE, 56);
    EndEventObject = memory != nullptr ? new (memory) NetworkEndEvent() : nullptr;
    _workerThreadCount = 0;
    _workerThreads = nullptr;
    _iocpHandle = nullptr;
    _idleWatcher = nullptr;
    memset(_port, 0, sizeof(_port));
}

// 0xCEA0
bool Network::Initialize(void (*failedEventHandler)(EventObject*), unsigned int workerThreadCount)
{
    if (Instance == nullptr)
        NETWORK_ASSERT_CRASH(80);
    initializeSocketInterface();
    _Run = true;
    Instance->_iocpHandle = CreateIoCompletionPort(INVALID_HANDLE_VALUE, nullptr, 0, 0);
    if (Instance->_iocpHandle == nullptr || Instance->_iocpHandle == INVALID_HANDLE_VALUE)
    {
        Log::Write(NETWORK_FILE, 89, GetLastError(), L"CreateIoCompletionPort");
        return false;
    }
    if (!Instance->initWorkerThread(failedEventHandler, workerThreadCount))
    {
        Log::Write(Log::LT_ERROR, NETWORK_FILE, 96, L"Worker Thread Initialize Error");
        return false;
    }
    // LIFT: Setup is inlined. It sets _MaxSize to 4000 only when _MaxSize <= 0 (LobbyGate 0x20192-0x2019b).
    PacketCrypt::ErrCode result = PacketCrypt::Setup(4000);
    if (result != PacketCrypt::SPCE_NO_ERROR)
    {
        Log::Write(Log::LT_ERROR, NETWORK_FILE, 103, L"Crypt Module initialized failed(%d)", result);
        return false;
    }
    return true;
}

// 0xCFD0
void Network::Clear()
{
    _Run = false;
    if (Instance->_idleWatcher != nullptr)
    {
        Daemon::Instance->threadManager->StopThread(Instance->_idleWatcher->_id, 2000, true, true);
        if (Instance->_idleWatcher != nullptr)
            Instance->_idleWatcher->~IdleWatcher();
        BASE_MEMORY_MANAGER.Free(Instance->_idleWatcher, NETWORK_FILE, 117);
        Instance->_idleWatcher = nullptr;
    }
    if (Instance->_iocpHandle != nullptr)
    {
        for (unsigned int i = 0; i < Instance->_workerThreadCount; ++i)
        {
            if (Instance->_workerThreads[i] != nullptr)
                WorkerManager->StopThread(Instance->_workerThreads[i]->_id, 0, false, false);
        }
        for (unsigned int i = 0; i < Instance->_workerThreadCount; ++i)
        {
            if (Instance->_workerThreads[i] != nullptr)
            {
                WorkerManager->StopThread(Instance->_workerThreads[i]->_id, 2000, true, true);
                if (Instance->_workerThreads[i] != nullptr)
                    Instance->_workerThreads[i]->~IoWorker();
                BASE_MEMORY_MANAGER.Free(Instance->_workerThreads[i], NETWORK_FILE, 141);
                Instance->_workerThreads[i] = nullptr;
            }
        }
    }
    // BUG: 0xCFD0 the _workerThreads array (AllocZero line 377) is never freed.
    for (int i = 0; i < 24; ++i)
    {
        if (Instance->_port[i] != nullptr)
        {
            Instance->_port[i]->_enableAccept = false;
            Instance->_port[i]->Clear();
            if (Instance->_port[i] != nullptr)
                Instance->_port[i]->~Port();
            BASE_MEMORY_MANAGER.Free(Instance->_port[i], NETWORK_FILE, 152);
            Instance->_port[i] = nullptr;
        }
    }
    _InterlockedDecrement(&s_initializedCount);  // LIFT: inlined PacketCrypt clean-up (LobbyGate 0x204cb, 0x94108)
    if (Instance->_iocpHandle != nullptr)
        CloseHandle(Instance->_iocpHandle);
    // BUG: 0xCFD0 Instance and EndEventObject are not released and WSACleanup is not called.
}

// 0xD2C0
// LIFT: SmartCouponDaemon 0x1A8B0 is this overload with LTCG-folded constants (initialMode 2, enableAccept false,
// enableRecv true, nagle false). The SCD callers pass these values. A separate 5-arg overload did not pair with the orig.
bool Network::OpenPort(unsigned int id, unsigned short portNumber, int initialMode, SessionHandler const* sessionHandler,
                       PacketBufferHandler const* bufferHandler, unsigned int maxSession, bool enableAccept,
                       bool enableRecv, bool nagle)
{
    // LIFT: LTCG folded the bool params (LobbyGate 0x20500, call 0x20708). All callers give constants.
    // LobbyGate and CacheGate use enableAccept == true and enableRecv == true. PostOfficeDaemon keeps enableAccept and nagle (0x28AB0).
    if (id == 0)
        NETWORK_ASSERT_CRASH(170);
    // LIFT: LTCG keeps only the purposes that the callers of each exe use: CacheGate {1, 2}, LobbyGate {0, 2},
    // PostOfficeDaemon {2, 3} (0x28AB0). s_defaultMaxSession has 4 entries, so the source range is 0..3.
    if (initialMode < 0 || initialMode > 3)  // ❓ exact source form of the check
        NETWORK_ASSERT_CRASH(175);
    if (Instance->_port[id - 1] != nullptr)
        NETWORK_ASSERT_CRASH(177);

    if (maxSession == 0)
    {
        if (initialMode == 2 || initialMode == 3)  // PostOfficeDaemon 0x28B6D
        {
            maxSession = 2 * Instance->_workerThreadCount + 1;
            if (s_defaultMaxSession[initialMode] > maxSession)
                maxSession = s_defaultMaxSession[initialMode];
        }
        else
        {
            maxSession = s_defaultMaxSession[initialMode];
        }
    }

    void* memory = BASE_MEMORY_MANAGER.Alloc(sizeof(Port), NETWORK_FILE, 184);
    Port* port = memory != nullptr ? new (memory) Port() : nullptr;
    if (!port->Initialize(id, portNumber, maxSession, initialMode, enableRecv, nagle, Instance->_iocpHandle,
                          sessionHandler, bufferHandler))
    {
        if (port != nullptr)
            port->~Port();
        BASE_MEMORY_MANAGER.Free(port, NETWORK_FILE, 188);
        return false;
    }
    if (port->_portNumber != 0)
    {
        if (!port->StartAccept())
        {
            port->clearPool();  // LIFT: inlined StartAccept failed; only this path calls clearPool (LobbyGate 0x20753-0x207a1)
            port->~Port();
            BASE_MEMORY_MANAGER.Free(port, NETWORK_FILE, 194);
            return false;
        }
    }
    // PostOfficeDaemon 0x28C6A: StartAccept runs for each listen port. A port with enableAccept == false
    // gets accept later through OpenPort(id).
    port->_enableRecv = enableRecv;
    if (!enableAccept)
        port->_enableAccept = false;
    Instance->_port[id - 1] = port;
    return true;
}

// 0x1AB20 (SmartCouponDaemon)
bool Network::OpenPort(unsigned int id)
{
    if (id - 1 > 23 || Instance->_port[id - 1] == nullptr)
        NETWORK_ASSERT_CRASH(209);
    Port* port = Instance->_port[id - 1];
    if (port->_portNumber != 0)
    {
        if (port->_listener == nullptr)
        {
            Log::Write(Log::LT_ERROR, L"source\\Port.cpp", 330, L"Initialize first!");
            port->clearPool();
            return false;
        }
        port->_enableAccept = true;
    }
    port->_enableRecv = true;
    return true;
}

// 0xD5A0
bool Network::ClosePort(unsigned int id)
{
    if (id - 1 > 23 || Instance->_port[id - 1] == nullptr)
        NETWORK_ASSERT_CRASH(215);
    Instance->_port[id - 1]->_enableAccept = false;
    return true;
}

// 0x28F10 (PostOfficeDaemon)
bool Network::StopPort(unsigned int portId)
{
    if (portId - 1 > 23 || Instance->_port[portId - 1] == nullptr)
        NETWORK_ASSERT_CRASH(222);
    Instance->_port[portId - 1]->_enableAccept = false;
    Instance->_port[portId - 1]->_enableRecv = false;
    return true;
}

// 0xD630
void Network::ReconnectSession(unsigned long long id)
{
    unsigned int portId = static_cast<unsigned int>(id >> 32);
    if (portId - 1 > 23 || Instance->_port[portId - 1] == nullptr)
        NETWORK_ASSERT_CRASH(266);
    Instance->_port[portId - 1]->ReconnectSession(id);
}

// 0x20860 (LobbyGate)
bool Network::SetMaxIdleTime(unsigned int portId, bool disconnect, long maxIdleTime)
{
    (void)portId;  // LIFT: LTCG removed it. LobbyGate 0x20860 reads _port[0].
    if (Instance->_port[0] == nullptr)
        NETWORK_ASSERT_CRASH(229);
    if (Instance->_idleWatcher == nullptr)
    {
        void* memory = BASE_MEMORY_MANAGER.Alloc(sizeof(IdleWatcher), NETWORK_FILE, 233);
        IdleWatcher* watcher = memory != nullptr ? new (memory) IdleWatcher() : nullptr;
        Instance->_idleWatcher = watcher;
        Daemon::Instance->threadManager->StartThread(watcher, nullptr);
    }
    Port* port = Instance->_port[0];
    IdleWatcher* watcher = Instance->_idleWatcher;
    if (port->_idleStateTable != nullptr)
        return false;
    IdleStateTable* table = IdleStateTable::Create(port, static_cast<int>(port->_maxSession), maxIdleTime, disconnect);
    port->_idleStateTable = table;
    if (table == nullptr)
        return false;
    watcher->_table[port->_id] = table;
    return true;
}

// 0x209D0 (LobbyGate)
void Network::CloseSession(unsigned long long sessionId, bool force)
{
    unsigned int index = static_cast<unsigned int>(sessionId >> 32) - 1;
    if (index > 23 || Instance->_port[index] == nullptr)
        NETWORK_ASSERT_CRASH(250);
    Instance->_port[index]->CloseSession(sessionId, force);
}

// 0xD6D0
wchar_t const* Network::GetAddressStringW(unsigned long address)
{
    wchar_t* addressW = __ip_addr_string_w__;
    char* addressA = __ip_addr_string_a__;
    addressW[0] = L'\0';
    addressA[0] = '\0';
    in_addr addr;
    addr.s_addr = address;
    char const* text = inet_ntoa(addr);
    if (text != nullptr)
        strcpy_s(addressA, 32, text);
    if (addressA != nullptr)
    {
        addressW[31] = L'\0';
        MultiByteToWideChar(CP_ACP, 0, addressA, -1, addressW, 31);
    }
    return addressW;
}

// 0xD760
Network* Network::initInstance(ThreadManager* threadManager)
{
    if (Instance != nullptr)
        NETWORK_ASSERT_CRASH(338);
    void* memory = BASE_MEMORY_MANAGER.Alloc(sizeof(Network), NETWORK_FILE, 340);
    Network* network = memory != nullptr ? new (memory) Network() : nullptr;
    WorkerManager = threadManager;
    if (network == nullptr)
        NETWORK_ASSERT_CRASH(342);
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        Log::Write(NETWORK_FILE, 346, WSAGetLastError(), L"WSAStartup");
        return nullptr;  // BUG: 0xD760 network is not freed and Instance still points to it.
    }
    return network;
}

// 0xD8E0
bool Network::initWorkerThread(void (*failedEventHandler)(EventObject*), unsigned int workerThreadCount)
{
    if (workerThreadCount == 0)
        workerThreadCount = 2 * SysInfo::ProcessorCount();
    _workerThreads = static_cast<IoWorker**>(
        BASE_MEMORY_MANAGER.AllocZero(sizeof(IoWorker*) * workerThreadCount, NETWORK_FILE, 377));
    for (unsigned int i = 0; i < workerThreadCount; ++i)
    {
        void* memory = BASE_MEMORY_MANAGER.Alloc(sizeof(IoWorker), NETWORK_FILE, 380);
        IoWorker* worker = memory != nullptr ? new (memory) IoWorker() : nullptr;
        if (worker != nullptr)
        {
            _workerThreads[i] = worker;
            worker->Initialize(i + 1, this, failedEventHandler);
            WorkerManager->StartThread(worker, nullptr);  // LobbyGate 0x20e30 gives threadId = nullptr
        }
    }
    _workerThreadCount = workerThreadCount;
    Sleep(1000);
    return true;
}

// 0xDA30
bool Network::initializeSocketInterface()
{
    unsigned long bytes = 0;
    SOCKET sock = WSASocketW(AF_INET, SOCK_STREAM, IPPROTO_TCP, nullptr, 0, WSA_FLAG_OVERLAPPED);
    if (sock == INVALID_SOCKET)
    {
        Log::Write(NETWORK_FILE, 402, WSAGetLastError(), L"WSASocket()");
        return false;
    }
    if (AcceptExFunc == nullptr)
    {
        GUID guidAcceptEx = WSAID_ACCEPTEX;
        if (WSAIoctl(sock, SIO_GET_EXTENSION_FUNCTION_POINTER, &guidAcceptEx, sizeof(guidAcceptEx), &AcceptExFunc,
                     sizeof(AcceptExFunc), &bytes, nullptr, nullptr) == SOCKET_ERROR)
        {
            Log::Write(NETWORK_FILE, 413, WSAGetLastError(), L"WSAIoctl()");
            closesocket(sock);
            return false;
        }
    }
    if (AcceptSockAddrsFunc == nullptr)
    {
        GUID guidGetAcceptExSockAddrs = WSAID_GETACCEPTEXSOCKADDRS;
        if (WSAIoctl(sock, SIO_GET_EXTENSION_FUNCTION_POINTER, &guidGetAcceptExSockAddrs,
                     sizeof(guidGetAcceptExSockAddrs), &AcceptSockAddrsFunc, sizeof(AcceptSockAddrsFunc), &bytes,
                     nullptr, nullptr) == SOCKET_ERROR)
        {
            Log::Write(NETWORK_FILE, 426, WSAGetLastError(), L"WSAIoctl()");
            closesocket(sock);
            return false;
        }
    }
    if (ConnectExFunc == nullptr)
    {
        GUID guidConnectEx = WSAID_CONNECTEX;
        if (WSAIoctl(sock, SIO_GET_EXTENSION_FUNCTION_POINTER, &guidConnectEx, sizeof(guidConnectEx), &ConnectExFunc,
                     sizeof(ConnectExFunc), &bytes, nullptr, nullptr) == SOCKET_ERROR)
        {
            Log::Write(NETWORK_FILE, 439, WSAGetLastError(), L"WSAIoctl()");
            closesocket(sock);
            return false;
        }
    }
    if (DisconnectExFunc == nullptr)
    {
        GUID guidDiconnectEx = WSAID_DISCONNECTEX;
        if (WSAIoctl(sock, SIO_GET_EXTENSION_FUNCTION_POINTER, &guidDiconnectEx, sizeof(guidDiconnectEx),
                     &DisconnectExFunc, sizeof(DisconnectExFunc), &bytes, nullptr, nullptr) == SOCKET_ERROR)
        {
            Log::Write(NETWORK_FILE, 452, WSAGetLastError(), L"WSAIoctl()");
            closesocket(sock);
            return false;
        }
    }
    closesocket(sock);
    return true;
}
