// ObjectPool.obj (SmartCouponDaemon PDB). Source file: "..\LobbyDaemon\ObjectPool.cpp".
// LTCG put the one pool (EventNotiJob::_pool) into each body. This lift uses `this`.
// LIFT: SmartCouponDaemon build path of StlMemory.h (from the HR strings).
// ObjectPoolLobbyDaemon.cpp sets the LobbyDaemon path and file literal before it includes this file.
#ifndef LIFT_STLMEMORY_FILE
#define LIFT_STLMEMORY_FILE \
    L"e:\\dailybuild02\\smartcoupondaemon-common-0.0.348\\depot\\branch\\348nc\\program\\server\\bloodlib\\include\\StlMemory.h"
#endif
#ifndef LIFT_OBJPOOL_FILE
#define LIFT_OBJPOOL_FILE L"..\\LobbyDaemon\\ObjectPool.cpp"
#endif
#include "ObjectPool.h"

#include <windows.h>

#include "AlertSender.h"
#include "Daemon.h"
#include "Log.h"

static wchar_t const* const kObjPoolFile = LIFT_OBJPOOL_FILE;
static unsigned long long const kObjPoolGuard = 0xB10D1C2FB10D1C2FULL;

static wchar_t const* descOf(ObjPool const* pool)  // LIFT: inlined helper
{
    return pool->_desc != nullptr ? pool->_desc : L"null";
}

#ifndef LIFT_OBJPOOL_LOBBYDAEMON
// 0x14AA0 (folded empty function)
void SmartCouponObjPoolMemoryAllocator::Free(void*, wchar_t const*, int)
{
}

// 0x1180
ObjPool::ObjPool(unsigned long long id, int objsize, wchar_t const* desc)
    : _id(id), _objsize(objsize), _desc(desc), _alloc(nullptr), _vtbl(nullptr), _timeToWait(0), _total(0)
{
    _pool._head = nullptr;
    _pool._size = 0;
    _wait._head = nullptr;
    _wait._tail = nullptr;
    _wait._size = 0;
}

// 0x1210
ObjPool::~ObjPool()
{
}
#endif  // LIFT_OBJPOOL_LOBBYDAEMON

// 0x1250
bool ObjPool::Initialize(void* vtbl, int initialPoolCapacity, long timeToWait)
{
    if (_alloc != nullptr)
    {
        Log::Write(Log::LT_ERROR, kObjPoolFile, 156,
                   L"[objpool], initialize fail; already initialized,id:%d(%s), obj-size:%d", _id, descOf(this),
                   _objsize);
        return false;
    }
    if (GObjPoolMemAlloc == nullptr || vtbl == nullptr)
    {
        Log::Write(Log::LT_ERROR, kObjPoolFile, 161,
                   L"== CRASH == [objpool], initialize fail; invalid parameter,id:%d(%s), obj-size:%d", _id,
                   descOf(this), _objsize);
        AlertSender::Write(kObjPoolFile, 161,
                           L"== CRASH == [objpool], initialize fail; invalid parameter,id:%d(%s), obj-size:%d", _id,
                           descOf(this), _objsize);
        return false;
    }
    _alloc = GObjPoolMemAlloc;
    _vtbl = vtbl;
    _timeToWait = timeToWait;
    for (int i = 0; i < initialPoolCapacity; ++i)
    {
        Node* node = static_cast<Node*>(_alloc->Alloc(_objsize + 40, kObjPoolFile, 170));
        node->next = nullptr;
        node->file = nullptr;
        node->line = 0;
        node->when = 0;
        ++_total;
        _lock.Enter();
        node->next = _pool._head;
        ++_pool._size;
        _pool._head = node;
        _lock.Leave();
    }
    Log::Write(Log::LT_NOTICE, kObjPoolFile, 178,
               L"[objpool], initialized, initial-capacity:%d, id:%d(%s), obj-size:%d", initialPoolCapacity, _id,
               descOf(this), _objsize);
    return true;
}

// 0x1490
void ObjPool::Finalize()
{
    Log::Write(Log::LT_NOTICE, kObjPoolFile, 187,
               L"[objpool], finalized, total-count:%d, object-count:%d, id:%d(%s), obj-size:%d", _total,
               _pool._size, _id, descOf(this), _objsize);
    _lock.Enter();
    while (_pool._head != nullptr)
    {
        Node* node = _pool._head;
        --_pool._size;
        _pool._head = node->next;
        node->next = nullptr;
        _alloc->Free(node, kObjPoolFile, 195);
    }
    _lock.Leave();
    _total = 0;
}

// 0x1560
void* ObjPool::Checkout(wchar_t const* file, int line)
{
    _lock.Enter();
    Node* node = _pool._head;
    if (node != nullptr)
    {
        --_pool._size;
        _pool._head = node->next;
        node->next = nullptr;
    }
    _lock.Leave();
    if (node == nullptr)
    {
        node = static_cast<Node*>(_alloc->Alloc(_objsize + 40, kObjPoolFile, 222));
        InterlockedIncrement(reinterpret_cast<volatile long*>(&_total));
        node->next = nullptr;
        node->file = nullptr;
        node->line = 0;
        node->when = 0;
    }
    long long now = GetTickCount64() - Daemon::Instance->StartSystemTick64;
    node->line = line;
    node->file = file;
    node->when = now;
    unsigned char* object = reinterpret_cast<unsigned char*>(node + 1);
    *reinterpret_cast<unsigned long long*>(object + _objsize) = kObjPoolGuard;
    return object;
}

// 0x1640
void ObjPool::Checkin(void* mem, wchar_t const* file, int line)
{
    if (mem == nullptr)
    {
        Log::Write(Log::LT_ERROR, kObjPoolFile, 252,
                   L"[objpool], checkin failed; null memory, file:%s, liine:%d, id:%d(%s), obj-size:%d", file, line,
                   _id, descOf(this), _objsize);
        return;
    }
    Node* node = static_cast<Node*>(mem) - 1;
    if (*reinterpret_cast<unsigned long long*>(static_cast<unsigned char*>(mem) + _objsize) != kObjPoolGuard)
    {
        Log::Write(Log::LT_ERROR, kObjPoolFile, 273,
                   L"== CRASH == object memory overrun occurs, node:%p, checkout-file:%s, checkout-line:%d, "
                   L"checkout-time:%I64d, checkin-file:%s, checkin-line:%d, id:%d(%s), obj-size:%d",
                   node, node->file, node->line, node->when, file, line, _id, descOf(this), _objsize);
        AlertSender::Write(kObjPoolFile, 273,
                           L"== CRASH == object memory overrun occurs, node:%p, checkout-file:%s, checkout-line:%d, "
                           L"checkout-time:%I64d, checkin-file:%s, checkin-line:%d, id:%d(%s), obj-size:%d",
                           node, node->file, node->line, node->when, file, line, _id, descOf(this), _objsize);
    }
    _lock.Enter();
    if (node != nullptr)
    {
        node->next = _pool._head;
        ++_pool._size;
        _pool._head = node;
    }
    _lock.Leave();
}

// 0x1830
ObjPoolTimer::~ObjPoolTimer()
{
    if (_run)
    {
        _run = false;
        Daemon::Instance->RemoveTimer(this);
        Log::Write(Log::LT_DEBUG, kObjPoolFile, 372, L"[objpool], objpool timer stopped, uptime:%I64d",
                   GetTickCount64() - Daemon::Instance->StartSystemTick64);
    }
}

// 0x1D7A0 (folded: returns 0)
unsigned int ObjPoolTimer::TimerClass() const
{
    return 0;
}

// 0x1D7A0 (folded: returns 0)
unsigned long long ObjPoolTimer::TimerId() const
{
    return 0;
}

// 0x1900
bool ObjPoolTimer::HandleEvent(EventContext*, unsigned long)
{
    if (_run)
        Daemon::Instance->AddTimer(process(), this);
    return true;
}

// 0x1940
bool ObjPoolTimer::Start(long resolution)
{
    (void)resolution;  // LIFT: LTCG const 1000 in the body; 0x1940 does not read edx
    ObjPoolTimer* timer = GObjPoolTimer;
    if (timer->_run)
    {
        Log::Write(Log::LT_ERROR, kObjPoolFile, 379, L"== CRASH == [objpool], objpool timer already started");
        AlertSender::Write(kObjPoolFile, 379, L"== CRASH == [objpool], objpool timer already started");
        return false;
    }
    timer->_resolution = 1000;
    Daemon::Instance->AddTimer(1000, timer);
    timer->_run = true;
    Log::Write(Log::LT_DEBUG, kObjPoolFile, 389, L"[objpool], objpool timer start, resolution:%d", 1000);
    return true;
}

// 0x19F0
bool ObjPoolTimer::Add(ObjPool* listener)
{
    // LIFT: 0x19fa loads GObjPoolTimer; LTCG drops `this`.
    GObjPoolTimer->_listeners.push_back(listener);
    Log::Write(Log::LT_NOTICE, kObjPoolFile, 410, L"[objpool], objpool added to timer, id:%I64d", listener->_id);
    return true;
}

// 0x1AC0
long ObjPoolTimer::process()
{
    long resolution = _resolution;
    unsigned long long start = GetTickCount64() - Daemon::Instance->StartSystemTick64;
    int elapsed;
    for (;;)
    {
        // The per-pool work is empty in this exe. Only the loop is left.
        for (unsigned int i = 0; i < _listeners.size(); ++i)
        {
        }
        elapsed = static_cast<int>(GetTickCount64() - static_cast<unsigned int>(Daemon::Instance->StartSystemTick64) -
                                   start);
        if (elapsed < resolution)
            break;
        do
            resolution += _resolution;
        while (resolution <= elapsed);
    }
    return resolution - elapsed;
}
