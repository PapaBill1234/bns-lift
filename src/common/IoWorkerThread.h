// IoWorkerThread.obj (CacheGate PDB). Layout from include/pdb/CacheGate/types.h.
#pragma once
#include <stddef.h>
#include "Thread.h"

class Network;
class EventObject;
struct ZSTD_CCtx_s;

// zstd is not vendored yet.
struct ZSTD_customMem
{
    void* (*customAlloc)(void* opaque, size_t size);
    void (*customFree)(void* opaque, void* address);
    void* opaque;
};
extern "C" ZSTD_CCtx_s* ZSTD_createCCtx_advanced(ZSTD_customMem customMem);  // TODO(lift-zstd)

class IoWorker : public Thread
{
public:
    // ❓ Inlined in Network::initWorkerThread (0xD8E0). It sets _maxFrozenSeconds to 60 and the TLS ZstdCCtx to null.
    IoWorker() : _workerId(0), _networkInstance(nullptr), _failedEventHandler(nullptr)
    {
        _maxFrozenSeconds = 60;
        ZstdCCtx = nullptr;
    }
    virtual ~IoWorker();                 // 0x199F0
    virtual void yield();                // 0x19AA0
    virtual wchar_t const* Name();       // 0x199E0
    virtual void run();                  // 0x19AC0

    bool Initialize(int workerId, Network* networkInstance, void (*failedEventHandler)(EventObject*));  // 0x19A00

protected:
    virtual void stop();                 // 0x19DD0

public:
    // TLS +16 and TLS +48 in .tls.
    static __declspec(thread) int WorkerId;
    static __declspec(thread) ZSTD_CCtx_s* ZstdCCtx;

    int _workerId;
    Network* _networkInstance;
    void (*_failedEventHandler)(EventObject*);
};
static_assert(sizeof(IoWorker) == 0x48, "sizeof IoWorker");
static_assert(offsetof(IoWorker, _workerId) == 0x30, "IoWorker::_workerId");
static_assert(offsetof(IoWorker, _failedEventHandler) == 0x40, "IoWorker::_failedEventHandler");
