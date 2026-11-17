// Network.obj (CacheGate PDB).
#include "Network.h"
#include <new>
#include <string.h>
#include <intrin.h>
#include <windows.h>
#include "AlertSender.h"
#include "CrashHandler.h"
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

// File static s_initializedCount (PDB: CryptoKey.obj, CacheGate rva 0x5A508). PacketCrypt::Setup increments it.
// Network::Clear decrements it (an inlined PacketCrypt clean-up).
extern long volatile s_initializedCount;
long volatile s_initializedCount = 0;  // The PacketCrypt module is not lifted. The definition is here.

int PacketCrypt::_MaxSize = 0;

// 0x327E0 (PacketCrypt module). Not in the CacheGate hr export.
PacketCrypt::ErrCode PacketCrypt::Setup(int maxSize)
{
    // TODO(lift-cg-5) the PacketCrypt module is not lifted.
    _MaxSize = maxSize;
    _InterlockedIncrement(&s_initializedCount);
    return SPCE_NO_ERROR;
}

// 0xCD60 (folded with DynamicEventObject::~DynamicEventObject)
EventObject::~EventObject()
{
}

// 0xCD60 (folded with EventObject::~EventObject)
DynamicEventObject::~DynamicEventObject()
{
}

// ❓ Not in the CacheGate hr export. Same body as DynamicRefCntObj::deallocate_me (0x2350).
void DynamicEventObject::deallocate_me(void* ptr, wchar_t const* file, int line)
{
    this->~DynamicEventObject();
    Memory::_Manager[2]->Free(ptr, file, line);
}

// ❓ IDA dword_14004E408: default maxSession for each initialMode (0..3).
static unsigned int const s_defaultMaxSession[4] = {10000, 10000, 16, 16};

// ❓ TLS buffers of GetAddressStringW (TLS +64 and TLS +96).
static __declspec(thread) char s_addressStringA[32];
static __declspec(thread) wchar_t s_addressStringW[32];

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
    // ❓ LTCG removed the argument. PacketCrypt::Setup sets _MaxSize to 4000.
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
        BaseMemoryManager::_Instance.Free(Instance->_idleWatcher, NETWORK_FILE, 117);
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
                BaseMemoryManager::_Instance.Free(Instance->_workerThreads[i], NETWORK_FILE, 141);
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
            BaseMemoryManager::_Instance.Free(Instance->_port[i], NETWORK_FILE, 152);
            Instance->_port[i] = nullptr;
        }
    }
    _InterlockedDecrement(&s_initializedCount);  // LIFT: inlined PacketCrypt clean-up
    if (Instance->_iocpHandle != nullptr)
        CloseHandle(Instance->_iocpHandle);
    // BUG: 0xCFD0 Instance and EndEventObject are not released and WSACleanup is not called.
}

// 0xD2C0
bool Network::OpenPort(unsigned int id, unsigned short portNumber, int initialMode, SessionHandler const* sessionHandler,
                       PacketBufferHandler const* bufferHandler, unsigned int maxSession, bool enableAccept,
                       bool enableRecv, bool nagle)
{
    // ❓ LTCG removed the bool params (all callers give constants). The code uses enableAccept == true,
    // enableRecv == true. Port::Initialize gets enableRecv and nagle as constants.
    if (id == 0)
        NETWORK_ASSERT_CRASH(170);
    if (initialMode != 1 && initialMode != 2)
        NETWORK_ASSERT_CRASH(175);
    if (Instance->_port[id - 1] != nullptr)
        NETWORK_ASSERT_CRASH(177);

    if (maxSession == 0)
    {
        if (initialMode == 2)
        {
            maxSession = 2 * Instance->_workerThreadCount + 1;
            if (maxSession < 16)
                maxSession = 16;
        }
        else
        {
            maxSession = s_defaultMaxSession[initialMode];
        }
    }

    void* memory = BaseMemoryManager::_Instance.Alloc(sizeof(Port), NETWORK_FILE, 184);
    Port* port = memory != nullptr ? new (memory) Port() : nullptr;
    if (!port->Initialize(id, portNumber, maxSession, initialMode, enableRecv, nagle, Instance->_iocpHandle,
                          sessionHandler, bufferHandler))
    {
        if (port != nullptr)
            port->~Port();
        BaseMemoryManager::_Instance.Free(port, NETWORK_FILE, 188);
        return false;
    }
    if (enableAccept && port->_portNumber != 0)
    {
        if (!port->StartAccept())
        {
            port->clearPool();  // ❓ the binary calls clearPool on this path only
            port->~Port();
            BaseMemoryManager::_Instance.Free(port, NETWORK_FILE, 194);
            return false;
        }
    }
    if (enableRecv)
        port->_enableRecv = true;
    Instance->_port[id - 1] = port;
    return true;
}

// 0x1A8B0 (SmartCouponDaemon)
bool Network::OpenPort(unsigned int portId, unsigned short portNo, SessionHandler const* sessionHandler,
                       PacketBufferHandler const* bufferHandler, unsigned int maxSession)
{
    if (portId == 0)
        NETWORK_ASSERT_CRASH(170);
    if (Instance->_port[portId - 1] != nullptr)
        NETWORK_ASSERT_CRASH(177);

    if (maxSession == 0)
    {
        maxSession = 2 * Instance->_workerThreadCount + 1;
        if (maxSession < 16)
            maxSession = 16;
    }

    void* memory = BaseMemoryManager::_Instance.Alloc(sizeof(Port), NETWORK_FILE, 184);
    Port* port = memory != nullptr ? new (memory) Port() : nullptr;
    // LIFT: LTCG folded Port::Initialize (0x28E10): initialMode 2, enableRecv true, nagle false.
    if (!port->Initialize(portId, portNo, maxSession, 2, true, false, Instance->_iocpHandle, sessionHandler,
                          bufferHandler))
    {
        if (port != nullptr)
            port->~Port();
        BaseMemoryManager::_Instance.Free(port, NETWORK_FILE, 188);
        return false;
    }
    if (port->_portNumber != 0)
    {
        if (!port->StartAccept())
        {
            port->clearPool();
            port->~Port();
            BaseMemoryManager::_Instance.Free(port, NETWORK_FILE, 194);
            return false;
        }
    }
    // 0x1AAE7: one word store. Accept stays off (OpenPort(id) 0x1AB20 sets it later), recv is on.
    port->_enableAccept = false;
    port->_enableRecv = true;
    Instance->_port[portId - 1] = port;
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
    (void)portId;  // ❓ LTCG removed it. The code reads _port[0].
    if (Instance->_port[0] == nullptr)
        NETWORK_ASSERT_CRASH(229);
    if (Instance->_idleWatcher == nullptr)
    {
        void* memory = BaseMemoryManager::_Instance.Alloc(sizeof(IdleWatcher), NETWORK_FILE, 233);
        IdleWatcher* watcher = memory != nullptr ? new (memory) IdleWatcher() : nullptr;
        Instance->_idleWatcher = watcher;
        Daemon::Instance->threadManager->StartThread(watcher, nullptr);
    }
    Port* port = Instance->_port[0];
    if (port->_idleStateTable != nullptr)
        return false;
    IdleStateTable* table = IdleStateTable::Create(port, static_cast<int>(port->_maxSession), maxIdleTime, disconnect);
    port->_idleStateTable = table;
    if (table == nullptr)
        return false;
    Instance->_idleWatcher->_table[port->_id] = table;
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
    wchar_t* addressW = s_addressStringW;
    char* addressA = s_addressStringA;
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
    void* memory = BaseMemoryManager::_Instance.Alloc(sizeof(Network), NETWORK_FILE, 340);
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
        workerThreadCount = 2 * SysInfo::_ProcessorCount;
    _workerThreads = static_cast<IoWorker**>(
        BaseMemoryManager::_Instance.AllocZero(sizeof(IoWorker*) * workerThreadCount, NETWORK_FILE, 377));
    for (unsigned int i = 0; i < workerThreadCount; ++i)
    {
        void* memory = BaseMemoryManager::_Instance.Alloc(sizeof(IoWorker), NETWORK_FILE, 380);
        IoWorker* worker = memory != nullptr ? new (memory) IoWorker() : nullptr;
        if (worker != nullptr)
        {
            _workerThreads[i] = worker;
            worker->Initialize(i + 1, this, failedEventHandler);
            WorkerManager->StartThread(worker, nullptr);  // ❓ threadId arg is not set in the binary (r8 is free)
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
    int line = 0;
    if (AcceptExFunc == nullptr)
    {
        GUID guidAcceptEx = WSAID_ACCEPTEX;
        if (WSAIoctl(sock, SIO_GET_EXTENSION_FUNCTION_POINTER, &guidAcceptEx, sizeof(guidAcceptEx), &AcceptExFunc,
                     sizeof(AcceptExFunc), &bytes, nullptr, nullptr) == SOCKET_ERROR)
        {
            line = 413;
            goto failed;
        }
    }
    if (AcceptSockAddrsFunc == nullptr)
    {
        GUID guidGetAcceptExSockAddrs = WSAID_GETACCEPTEXSOCKADDRS;
        if (WSAIoctl(sock, SIO_GET_EXTENSION_FUNCTION_POINTER, &guidGetAcceptExSockAddrs,
                     sizeof(guidGetAcceptExSockAddrs), &AcceptSockAddrsFunc, sizeof(AcceptSockAddrsFunc), &bytes,
                     nullptr, nullptr) == SOCKET_ERROR)
        {
            line = 426;
            goto failed;
        }
    }
    if (ConnectExFunc == nullptr)
    {
        GUID guidConnectEx = WSAID_CONNECTEX;
        if (WSAIoctl(sock, SIO_GET_EXTENSION_FUNCTION_POINTER, &guidConnectEx, sizeof(guidConnectEx), &ConnectExFunc,
                     sizeof(ConnectExFunc), &bytes, nullptr, nullptr) == SOCKET_ERROR)
        {
            line = 439;
            goto failed;
        }
    }
    if (DisconnectExFunc == nullptr)
    {
        GUID guidDiconnectEx = WSAID_DISCONNECTEX;
        if (WSAIoctl(sock, SIO_GET_EXTENSION_FUNCTION_POINTER, &guidDiconnectEx, sizeof(guidDiconnectEx),
                     &DisconnectExFunc, sizeof(DisconnectExFunc), &bytes, nullptr, nullptr) == SOCKET_ERROR)
        {
            line = 452;
            goto failed;
        }
    }
    closesocket(sock);
    return true;

failed:
    Log::Write(NETWORK_FILE, line, WSAGetLastError(), L"WSAIoctl()");
    closesocket(sock);
    return false;
}
