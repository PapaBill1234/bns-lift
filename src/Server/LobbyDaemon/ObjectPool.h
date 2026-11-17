// ObjectPool.obj (SmartCouponDaemon PDB). Layouts from include/pdb/SmartCouponDaemon/types.h.
// The source file is "..\LobbyDaemon\ObjectPool.cpp" (log strings).
#pragma once
#include <stddef.h>
#include <vector>
#include "Lock.h"
#include "TimerQueue.h"

class ObjPoolMemoryAllocator
{
public:
    virtual void* Alloc(unsigned long long size, wchar_t const* file, int line) = 0;  // slot 0
    virtual void Free(void* ptr, wchar_t const* file, int line) = 0;                  // slot 1
};
static_assert(sizeof(ObjPoolMemoryAllocator) == 0x8, "sizeof ObjPoolMemoryAllocator");

class SmartCouponObjPoolMemoryAllocator : public ObjPoolMemoryAllocator
{
public:
    // LIFT: Inlined in SmartCouponDaemon::initialize (0x150E0).
    SmartCouponObjPoolMemoryAllocator(unsigned long long systemAllocationGranularity, unsigned long long alignment)
        : _systemAllocationGranularity(systemAllocationGranularity), _alignment(alignment), _mem(nullptr), _end(nullptr)
    {
    }
    virtual void* Alloc(unsigned long long size, wchar_t const* file, int line);  // 0x14AB0
    virtual void Free(void* ptr, wchar_t const* file, int line);                  // 0x14AA0 (retn 0)

    CriticalSection _lock;
    unsigned long long const _systemAllocationGranularity;
    unsigned long long const _alignment;
    unsigned char* _mem;
    unsigned char* _end;
};
static_assert(sizeof(SmartCouponObjPoolMemoryAllocator) == 0x50, "sizeof SmartCouponObjPoolMemoryAllocator");

class ObjPool
{
public:
    // Header in front of each object. The object follows at +0x20, then an 8-byte guard.
    struct Node  // PDB type 0x1F00, field list 0x1EFF
    {
        Node* next;
        wchar_t const* file;
        int line;
        long long when;
    };
    static_assert(sizeof(Node) == 0x20, "sizeof ObjPool::Node");

    struct Stack  // PDB type 0x1EFA, field list 0x1EF9
    {
        Node* _head;
        int _size;
    };
    static_assert(sizeof(Stack) == 0x10, "sizeof ObjPool::Stack");

    struct Queue  // PDB type 0x1EEF, field list 0x1EEE. This exe does not use it.
    {
        Node* _head;
        Node* _tail;
        int _size;
    };
    static_assert(sizeof(Queue) == 0x18, "sizeof ObjPool::Queue");

    ObjPool(unsigned long long id, int objsize, wchar_t const* desc);  // 0x1180
    virtual ~ObjPool();                                                 // 0x1210

    bool Initialize(void* vtbl, int initialPoolCapacity, long timeToWait);  // 0x1250
    void Finalize();                                                       // 0x1490
    void* Checkout(wchar_t const* file, int line);                         // 0x1560
    void Checkin(void* mem, wchar_t const* file, int line);                // 0x1640

    unsigned long long _id;
    int _objsize;
    wchar_t const* _desc;
    ObjPoolMemoryAllocator* _alloc;
    void* _vtbl;
    long _timeToWait;
    int _total;
    Stack _pool;
    CriticalSection _lock;
    Queue _wait;
    CriticalSection _waitlock;
};
static_assert(sizeof(ObjPool) == 0xB0, "sizeof ObjPool");
static_assert(offsetof(ObjPool, _pool) == 56, "ObjPool::_pool");
static_assert(offsetof(ObjPool, _wait) == 112, "ObjPool::_wait");
static_assert(offsetof(ObjPool, _waitlock) == 136, "ObjPool::_waitlock");

class ObjPoolTimer : public Timer
{
public:
    // LIFT: Inlined in SmartCouponDaemon::initialize (0x150E0).
    ObjPoolTimer() : _run(false), _resolution(0) {}
    virtual ~ObjPoolTimer();
    virtual unsigned int TimerClass() const;
    virtual unsigned long long TimerId() const;
    virtual bool HandleEvent(EventContext* ctx, unsigned long);

    bool Add(ObjPool* listener);         // 0x19F0
    static bool Start(long resolution);  // 0x1940

private:
    long process();  // 0x1AC0

public:

    bool _run;
    std::vector<ObjPool*, StlAllocator<ObjPool*, 2> > _listeners;
    long _resolution;
};
static_assert(sizeof(ObjPoolTimer) == 0x68, "sizeof ObjPoolTimer");

extern SmartCouponObjPoolMemoryAllocator* GObjPoolMemAlloc;  // rva 0x84B18
extern ObjPoolTimer* GObjPoolTimer;                           // rva 0x84B20
