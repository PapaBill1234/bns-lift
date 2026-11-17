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
    // ❓ Inlined in SmartCouponDaemon::initialize (0x150E0).
    SmartCouponObjPoolMemoryAllocator(unsigned long long systemAllocationGranularity, unsigned long long alignment)
        : _systemAllocationGranularity(systemAllocationGranularity), _alignment(alignment), _mem(nullptr), _end(nullptr)
    {
    }
    virtual void* Alloc(unsigned long long size, wchar_t const* file, int line);  // 0x14AB0
    virtual void Free(void* ptr, wchar_t const* file, int line);                  // ❓ address

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
    struct Node  // ❓ layout from ObjPool::Checkout (0x1560)
    {
        Node* next;
        wchar_t const* file;
        int line;
        long long time;
    };
    static_assert(sizeof(Node) == 0x20, "sizeof ObjPool::Node");

    struct Stack  // ❓ PDB type 0x1ED7, layout from ObjPool::Initialize (0x1250)
    {
        Node* _top;
        int _count;
    };
    static_assert(sizeof(Stack) == 0x10, "sizeof ObjPool::Stack");

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
    alignas(8) unsigned char _wait[0x18];  // ❓ PDB type 0x1ED8: ObjPool::Queue (not used in this exe)
    CriticalSection _waitlock;
};
static_assert(sizeof(ObjPool) == 0xB0, "sizeof ObjPool");

class ObjPoolTimer : public Timer
{
public:
    // ❓ Inlined in SmartCouponDaemon::initialize (0x150E0).
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
