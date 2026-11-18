// Memory.obj (CacheGate PDB).
#include "Memory.h"
#include <new>
#include "AlertSender.h"
#include "CrashHandler.h"
#include "Log.h"

MemoryManager const* Memory::_Manager[3] = {};

// 0xdd10
// LTCG removed type, size and createAllocationHistory. The binary gets only the
// option in rcx and gives size 0. The PDB signature is kept here.
// BUG: 0xdd10 the result of Alloc is not checked for null before the Initialize call.
// LIFT: noinline. initMemorySection is forceinline and the orig calls CreateManager out of line (CacheGate 0xdd10).
__declspec(noinline) MemoryManager const* Memory::CreateManager(MgrType type, void const* option, unsigned long long size,
                                           bool createAllocationHistory)
{
    void* memory = BASE_MEMORY_MANAGER.Alloc(sizeof(HeapMemoryManager), L"source\\Memory.cpp", 22);
    MemoryManager* manager = memory != nullptr ? new (memory) HeapMemoryManager() : nullptr;
    manager->Initialize(option, size);
    return manager;
}

// 0x19550 (SmartCouponDaemon) scalar deleting destructor
GrowingBuffer::~GrowingBuffer()
{
    if (_buffer != nullptr)
    {
        Memory::_Manager[_sec]->Free(_buffer, L"source\\Memory.cpp", 109);
        _buffer = nullptr;
    }
}

// 0x29750 (PostOfficeDaemon)
// LIFT: noinline. The orig calls it out of line (POD 0x29750).
__declspec(noinline) void GrowingBuffer::Add(unsigned long long size)
{
    if (_size - _count < size)
    {
        Log::Write(Log::LT_ERROR, L"source\\Memory.cpp", 122, L"== CRASH == ASSERT CRASH");
        AlertSender::Write(L"source\\Memory.cpp", 122, L"== CRASH == ASSERT CRASH");
        CrashHandler::MakeCrash("source\\Memory.cpp", 122, L"");
    }
    _count += size;
}

// 0x195A0 (SmartCouponDaemon)
// LIFT: noinline. The orig calls it out of line (POD 0x297e0).
__declspec(noinline) void GrowingBuffer::grow(unsigned long long size)
{
    _size *= 2;
    if (_size == 0)
        _size = _initSize;
    while (_size - _count < size)
        _size *= 2;
    _buffer = static_cast<unsigned char*>(Memory::_Manager[_sec]->Realloc(_buffer, _size, L"source\\Memory.cpp", 147));
}
