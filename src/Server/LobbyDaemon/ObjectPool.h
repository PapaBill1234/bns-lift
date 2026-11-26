// ObjectPool.obj (SmartCouponDaemon PDB). Layouts from include/pdb/SmartCouponDaemon/types.h.
// The source file is "..\LobbyDaemon\ObjectPool.cpp" (log strings).
// LIFT: ObjectPoolLobbyDaemon.h defines LIFT_OBJPOOL_LOBBYDAEMON. Then this header gives the
// LobbyDaemon form: the ObjPool ctor, the dtor and the Stack/Queue ctors are inline (no PDB
// symbol), and GObjPoolMemAlloc has the type LobbyObjPoolMemAllocator*.
#pragma once
#include <stddef.h>
#include <vector>
#include "Lock.h"
#include "SysInfo.h"
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

#ifdef LIFT_OBJPOOL_LOBBYDAEMON
// LobbyDaemon PDB. Layout: include/pdb/LobbyDaemon/types.h (sizeof 0x50).
// LIFT: moved here from LobbyDaemon.h, so that ObjectPool.cpp sees the complete type.
class LobbyObjPoolMemAllocator : public ObjPoolMemoryAllocator
{
public:
    // LIFT: Inlined in LobbyDaemon::initialize (0x9b300).
    LobbyObjPoolMemAllocator()
        : _systemAllocationGranularity(SysInfo::MemnoryAllocationGranularity()), _alignment(16), _mem(nullptr),
          _end(nullptr)
    {
    }
    virtual void* Alloc(unsigned long long, wchar_t const*, int);  // 0x99260
    // LIFT: Free has no LD RVA in the index (❓ folded with an empty function). It does nothing.
    virtual void Free(void*, wchar_t const*, int) {}

    CriticalSection _lock;
    unsigned long long const _systemAllocationGranularity;
    unsigned long long const _alignment;
    unsigned char* _mem;
    unsigned char* _end;
};
static_assert(sizeof(LobbyObjPoolMemAllocator) == 0x50, "sizeof LobbyObjPoolMemAllocator");
#endif

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
#ifdef LIFT_OBJPOOL_LOBBYDAEMON
        Stack() : _head(nullptr), _size(0) {}  // LIFT: LobbyDaemon PDB ObjPool::Stack::Stack (inline)
#endif
        Node* _head;
        int _size;
    };
    static_assert(sizeof(Stack) == 0x10, "sizeof ObjPool::Stack");

    struct Queue  // PDB type 0x1EEF, field list 0x1EEE. This exe does not use it.
    {
#ifdef LIFT_OBJPOOL_LOBBYDAEMON
        Queue() : _head(nullptr), _tail(nullptr), _size(0) {}  // LIFT: LobbyDaemon PDB ObjPool::Queue::Queue (inline)
#endif
        Node* _head;
        Node* _tail;
        int _size;
    };
    static_assert(sizeof(Queue) == 0x18, "sizeof ObjPool::Queue");

#ifdef LIFT_OBJPOOL_LOBBYDAEMON
    // LIFT: LobbyDaemon has no out-of-line ctor or dtor. The _pool dynamic initializers only
    // run the CriticalSection ctors; the other members are static .data.
    ObjPool(unsigned long long id, int objsize, wchar_t const* desc)
        : _id(id), _objsize(objsize), _desc(desc), _alloc(nullptr), _vtbl(nullptr), _timeToWait(0), _total(0)
    {
    }
    virtual ~ObjPool() {}
#else
    ObjPool(unsigned long long id, int objsize, wchar_t const* desc);  // 0x1180
    virtual ~ObjPool();                                                 // 0x1210
#endif

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

#ifdef LIFT_OBJPOOL_LOBBYDAEMON
extern LobbyObjPoolMemAllocator* GObjPoolMemAlloc;  // LobbyDaemon rva 0x2095D8
extern ObjPoolTimer* GObjPoolTimer;                  // LobbyDaemon rva 0x2095E0
#else
extern SmartCouponObjPoolMemoryAllocator* GObjPoolMemAlloc;  // rva 0x84B18
extern ObjPoolTimer* GObjPoolTimer;                           // rva 0x84B20
#endif
