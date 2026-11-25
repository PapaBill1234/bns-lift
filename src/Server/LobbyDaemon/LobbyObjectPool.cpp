// ObjectPool.obj (LobbyDaemon PDB). Source file "ObjectPool.cpp" (log strings).
// ObjectPool.cpp in this directory is the SmartCouponDaemon form. It is not in lift_lobbydaemon, because the
// LobbyDaemon form uses LobbyObjPoolMemAllocator and other log paths.
// LIFT: This file has only the functions that the lifted LobbyDaemon packet handlers need (gap-26).
// Not done here: Initialize (0x62610), Finalize (0x62800), Checkin (0x629a0), ObjPoolTimer (0x62b50-0x62e00).

#include "ObjectPool.h"

#include <windows.h>

#include "Daemon.h"

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
