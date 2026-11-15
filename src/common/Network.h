// Network (CacheGate PDB). Layout from include/pdb/CacheGate/types.h.
// Declarations only. The bodies are in a later card.
#pragma once
#include <stddef.h>

class ThreadManager;
class IoWorker;
class Port;
class IdleWatcher;

class Network
{
protected:
    static Network* initInstance(ThreadManager* threadManager);  // 0xd760 TODO(lift-network)

public:
    static wchar_t const* GetAddressStringW(unsigned long address);  // 0xd6d0 TODO(lift-network)

    unsigned int _workerThreadCount;
    IoWorker** _workerThreads;
    Port* _port[24];
    IdleWatcher* _idleWatcher;
    void* _iocpHandle;

private:
    static Network* Instance;  // 0x84B40 (SmartCouponDaemon) TODO(lift-network)

    friend class Daemon;
    friend class DelayedRelease;  // ❓ access for DelayedRelease::Release (0x22DA0)
};
static_assert(sizeof(Network) == 0xE0, "sizeof Network");
static_assert(offsetof(Network, _iocpHandle) == 0xD8, "Network::_iocpHandle");
