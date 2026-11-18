// Network.obj (CacheGate PDB). Layout from include/pdb/CacheGate/types.h.
#pragma once
#include <stddef.h>
#include <winsock2.h>
#include <mswsock.h>
#include "TimerQueue.h"

class ThreadManager;
class IoWorker;
class Port;
class IdleWatcher;
class SessionHandler;
class PacketBufferHandler;

// 0xCD70 EventId, 0xCD80 HandleEvent
class NetworkEndEvent : public DynamicEventObject
{
public:
    // PDB constructor, inlined in Network::Network (0xCDB0).
    NetworkEndEvent()
    {
        _tag = 1546;
        _ref = 1;
        _history = nullptr;
    }
    virtual unsigned int EventId() const;
    virtual bool HandleEvent(EventContext* context, unsigned long numOfBytes);
};
static_assert(sizeof(NetworkEndEvent) == 0x18, "sizeof NetworkEndEvent");

class Network
{
private:
    Network();  // 0xCDB0

public:
    static bool Initialize(void (*failedEventHandler)(EventObject*), unsigned int workerThreadCount);  // 0xCEA0
    static void Clear();                                                                              // 0xCFD0
    static bool OpenPort(unsigned int id, unsigned short portNumber, int initialMode, SessionHandler const* sessionHandler,
                         PacketBufferHandler const* bufferHandler, unsigned int maxSession, bool enableAccept,
                         bool enableRecv, bool nagle);                                                // 0xD2C0
    static bool OpenPort(unsigned int id);                                                            // 0x1AB20 (SmartCouponDaemon)
    // PDB static iocpHandle(), inlined. Some sites have no null test: the compiler removed it after an
    // earlier read of Instance.
    static void* iocpHandle() { return Instance ? Instance->iopcHandle() : nullptr; }
    static bool ClosePort(unsigned int id);                                                           // 0xD5A0
    static bool StopPort(unsigned int portId);                                                        // 0x28F10 (PostOfficeDaemon)
    static wchar_t const* GetAddressStringW(unsigned long address);                                   // 0xD6D0
    static void CloseSession(unsigned long long sessionId, bool force);                               // 0x209D0 (LobbyGate)
    // LIFT: LTCG removed portId (the only caller gives 1). LobbyGate 0x20860 reads _port[0].
    static bool SetMaxIdleTime(unsigned int portId, bool disconnect, long maxIdleTime);               // 0x20860 (LobbyGate)

protected:
    static void ReconnectSession(unsigned long long id);         // 0xD630
    static Network* initInstance(ThreadManager* threadManager);  // 0xD760
    // PDB name (with the typo). Inlined in Network::iocpHandle.
    void* iopcHandle() { return _iocpHandle; }

private:
    bool initWorkerThread(void (*failedEventHandler)(EventObject*), unsigned int workerThreadCount);  // 0xD8E0
    static bool initializeSocketInterface();                                                          // 0xDA30

public:
    unsigned int _workerThreadCount;
    IoWorker** _workerThreads;
    Port* _port[24];
    IdleWatcher* _idleWatcher;
    void* _iocpHandle;

    static ThreadManager* WorkerManager;
    static EventObject* EndEventObject;
    static bool _Run;

private:
    static Network* Instance;
    static LPFN_ACCEPTEX AcceptExFunc;
    static LPFN_GETACCEPTEXSOCKADDRS AcceptSockAddrsFunc;
    static LPFN_CONNECTEX ConnectExFunc;
    static LPFN_DISCONNECTEX DisconnectExFunc;

    friend class Daemon;
    friend class Connection;
    friend class PortListener;
    friend class Port;
    friend class Session;
    friend class Channel;
    friend class ReconnectTimer;
    friend class IdleStateTable;
    friend class DelayedRelease;  // LIFT: friend; PDB: Network::Instance is private. Release reads it (SmartCouponDaemon 0x22DA0, LobbyGate 0x283fb).
    friend class LobbyDSessionHandler;  // LIFT: friend; PDB: Network::Instance is private. PacketHandler reads it (LobbyGate 0x96f5, 0x97f8).
    friend class PostOfficeDaemon;  // LIFT: friend; PDB: Network::Instance is private. initNetwork and onStart read it (PostOfficeDaemon 0x13670, 0x13ca6).
};
static_assert(sizeof(Network) == 0xE0, "sizeof Network");
static_assert(offsetof(Network, _iocpHandle) == 0xD8, "Network::_iocpHandle");
