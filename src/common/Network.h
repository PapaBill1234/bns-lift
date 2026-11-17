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
    static bool OpenPort(unsigned int portId, unsigned short portNo, SessionHandler const* sessionHandler,
                         PacketBufferHandler const* bufferHandler, unsigned int maxSession);          // 0x1A8B0 (SmartCouponDaemon)
    static bool OpenPort(unsigned int id);                                                            // 0x1AB20 (SmartCouponDaemon)
    // ❓ Not in the PDB. Inlined read of Instance->_iocpHandle.
    static void* iocpHandle() { return Instance->_iocpHandle; }
    // ❓ Not in the PDB. Inlined read of (Instance ? Instance->_iocpHandle : nullptr).
    static void* iocpHandleOrNull() { return Instance ? Instance->_iocpHandle : nullptr; }
    static bool ClosePort(unsigned int id);                                                           // 0xD5A0
    static bool StopPort(unsigned int portId);                                                        // 0x28F10 (PostOfficeDaemon)
    static wchar_t const* GetAddressStringW(unsigned long address);                                   // 0xD6D0
    static void CloseSession(unsigned long long sessionId, bool force);                               // 0x209D0 (LobbyGate)
    // ❓ LTCG removed portId (the only caller gives 1). The code uses _port[0].
    static bool SetMaxIdleTime(unsigned int portId, bool disconnect, long maxIdleTime);               // 0x20860 (LobbyGate)

protected:
    static void ReconnectSession(unsigned long long id);         // 0xD630
    static Network* initInstance(ThreadManager* threadManager);  // 0xD760

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
    friend class DelayedRelease;  // ❓ access for DelayedRelease::Release (0x22DA0)
    friend class LobbyDSessionHandler;  // ❓ access for LobbyDSessionHandler::PacketHandler (LobbyGate 0x9660)
    friend class PostOfficeDaemon;  // ❓ initNetwork and onStart (PostOfficeDaemon 0x135e0, 0x13ca0) read Instance
};
static_assert(sizeof(Network) == 0xE0, "sizeof Network");
static_assert(offsetof(Network, _iocpHandle) == 0xD8, "Network::_iocpHandle");
