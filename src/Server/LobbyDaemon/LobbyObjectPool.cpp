// ObjectPool.obj (LobbyDaemon PDB). Source file "ObjectPool.cpp" (log strings).
// ObjectPool.cpp in this directory is the SmartCouponDaemon form. It is not in lift_lobbydaemon, because the
// LobbyDaemon form uses LobbyObjPoolMemAllocator and other log paths.
// LIFT: This file has only the functions that the lifted LobbyDaemon packet handlers, the job pools (gap-26, gap-25)
// and the live startup path (LobbyDaemon::onStart, gap-04) need.
// Not done here: Initialize (0x62610), Finalize (0x62800), ~ObjPoolTimer (0x62b70), HandleEvent (0x62c40), Add (0x62d30),
// process (0x62e00).

#include "ObjectPool.h"

#include <windows.h>

#include "AlertSender.h"
#include "Daemon.h"
#include "Log.h"

// LIFT: the LobbyDaemon build has no out-of-line ObjPool ctor. The dynamic initializers of the job pools
// (0x11d850-0x11e660) set only the locks and _wait; the other members are static data (id 1, objsize, desc).
// This out-of-line form gives the same values. ❓
ObjPool::ObjPool(unsigned long long id, int objsize, wchar_t const* desc)
    : _id(id), _objsize(objsize), _desc(desc), _alloc(nullptr), _vtbl(nullptr), _timeToWait(0), _total(0)
{
    _pool._head = nullptr;
    _pool._size = 0;
    _wait._head = nullptr;
    _wait._tail = nullptr;
    _wait._size = 0;
}

// LIFT: inlined in the dynamic atexit destructors of the job pools (0x11e7c0-0x11f2c0). The lock members delete
// their critical sections.
ObjPool::~ObjPool()
{
}

// 0x628c0
void* ObjPool::Checkout(wchar_t const* file, int line)
{
    EnterCriticalSection(&_lock.CS);
    Node* node = _pool._head;
    if (node != nullptr)
    {
        --_pool._size;
        _pool._head = node->next;
        node->next = nullptr;
    }
    LeaveCriticalSection(&_lock.CS);
    if (node == nullptr)
    {
        node = static_cast<Node*>(_alloc->Alloc(_objsize + 40, L"ObjectPool.cpp", 222));
        InterlockedIncrement(reinterpret_cast<volatile long*>(&_total));
        node->next = nullptr;
        node->file = nullptr;
        node->line = 0;
        node->when = 0;
    }
    long long now = GetTickCount64() - Daemon::Instance->StartSystemTick64;
    node->file = file;
    node->line = line;
    node->when = now;
    unsigned char* object = reinterpret_cast<unsigned char*>(node + 1);
    *reinterpret_cast<unsigned long long*>(object + _objsize) = 0xB10D1C2FB10D1C2FULL;
    return object;
}

// 0x629a0
void ObjPool::Checkin(void* mem, wchar_t const* file, int line)
{
    if (mem == nullptr)
    {
        Log::Write(Log::LT_ERROR, L"ObjectPool.cpp", 252,
                   L"[objpool], checkin failed; null memory, file:%s, liine:%d, id:%d(%s), obj-size:%d", file, line, _id,
                   _desc != nullptr ? _desc : L"null", _objsize);
        return;
    }
    Node* const node = static_cast<Node*>(mem) - 1;
    if (*reinterpret_cast<unsigned long long*>(static_cast<unsigned char*>(mem) + _objsize) != 0xB10D1C2FB10D1C2FULL)
    {
        Log::Write(Log::LT_ERROR, L"ObjectPool.cpp", 273,
                   L"== CRASH == object memory overrun occurs, node:%p, checkout-file:%s, checkout-line:%d, "
                   L"checkout-time:%I64d, checkin-file:%s, checkin-line:%d, id:%d(%s), obj-size:%d",
                   node, node->file, node->line, node->when, file, line, _id, _desc != nullptr ? _desc : L"null",
                   _objsize);
        AlertSender::Write(L"ObjectPool.cpp", 273,
                           L"== CRASH == object memory overrun occurs, node:%p, checkout-file:%s, checkout-line:%d, "
                           L"checkout-time:%I64d, checkin-file:%s, checkin-line:%d, id:%d(%s), obj-size:%d",
                           node, node->file, node->line, node->when, file, line, _id,
                           _desc != nullptr ? _desc : L"null", _objsize);
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

// 0x62c80
bool ObjPoolTimer::Start(long resolution)
{
    (void)resolution;  // LIFT: LTCG put the const 1000 in the body; 0x62c80 does not read edx
    ObjPoolTimer* timer = GObjPoolTimer;
    if (timer->_run)
    {
        Log::Write(Log::LT_ERROR, L"ObjectPool.cpp", 379, L"== CRASH == [objpool], objpool timer already started");
        AlertSender::Write(L"ObjectPool.cpp", 379, L"== CRASH == [objpool], objpool timer already started");
        return false;
    }
    timer->_resolution = 1000;
    Daemon::Instance->AddTimer(1000, timer);
    timer->_run = true;
    Log::Write(Log::LT_DEBUG, L"ObjectPool.cpp", 389, L"[objpool], objpool timer start, resolution:%d", 1000);
    return true;
}
