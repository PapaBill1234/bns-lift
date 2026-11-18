// MemoryManager.obj (CacheGate PDB).
#include "MemoryManager.h"
#include "Log.h"
#include "AlertSender.h"

// The path is per exe project. MemoryManager<Exe>.cpp wrappers set it (lesson 30).
#ifndef LIFT_MEMORYMANAGER_H_FILE
#define LIFT_MEMORYMANAGER_H_FILE \
    L"E:\\DailyBuild02\\CacheGate-Common-0.0.348\\depot\\Branch\\348NC\\Program\\Server\\BloodLib\\include\\MemoryManager.h"
#endif
#define LIFT_DO_NOT_USE L"== CRASH == [memory], do not use this function"

// 0x590a0 (.rdata). HeapMemoryManager::Initialize compares the option with 2.
void const* const HeapMemoryManager::LFH = reinterpret_cast<void const*>(2);

// 0x19df0
bool StaticPageMemoryManager::Initialize(void const* option, unsigned long long size)
{
    Log::Write(Log::LT_ERROR, LIFT_MEMORYMANAGER_H_FILE, 112, LIFT_DO_NOT_USE);
    AlertSender::Write(LIFT_MEMORYMANAGER_H_FILE, 112, LIFT_DO_NOT_USE);
    return false;
}

// 0x19e30
void StaticPageMemoryManager::Clear()
{
    Log::Write(Log::LT_ERROR, LIFT_MEMORYMANAGER_H_FILE, 113, LIFT_DO_NOT_USE);
    AlertSender::Write(LIFT_MEMORYMANAGER_H_FILE, 113, LIFT_DO_NOT_USE);
}

// 0x19e70
void* StaticPageMemoryManager::AllocZero(unsigned long long size, wchar_t const* file, int line) const
{
    Log::Write(Log::LT_ERROR, LIFT_MEMORYMANAGER_H_FILE, 117, LIFT_DO_NOT_USE);
    AlertSender::Write(LIFT_MEMORYMANAGER_H_FILE, 117, LIFT_DO_NOT_USE);
    return nullptr;
}

// 0x19eb0
void* StaticPageMemoryManager::Realloc(void* ptr, unsigned long long size, wchar_t const* file, int line) const
{
    Log::Write(Log::LT_ERROR, LIFT_MEMORYMANAGER_H_FILE, 118, LIFT_DO_NOT_USE);
    AlertSender::Write(LIFT_MEMORYMANAGER_H_FILE, 118, LIFT_DO_NOT_USE);
    return nullptr;
}

// 0x19ef0
void* StaticPageMemoryManager::ReallocZero(void* ptr, unsigned long long size, unsigned long long oldSize,
                                           wchar_t const* file, int line) const
{
    Log::Write(Log::LT_ERROR, LIFT_MEMORYMANAGER_H_FILE, 119, LIFT_DO_NOT_USE);
    AlertSender::Write(LIFT_MEMORYMANAGER_H_FILE, 119, LIFT_DO_NOT_USE);
    return nullptr;
}

// 0x19f30
bool HeapMemoryManager::Initialize(void const* option, unsigned long long size)
{
    if (option == LFH)
    {
        unsigned long value = 2;
        return HeapSetInformation(_heap, HeapCompatibilityInformation, &value, sizeof(value)) != FALSE;
    }
    return true;
}

// 0x19f70
void* HeapMemoryManager::Alloc(unsigned long long size, wchar_t const* file, int line) const
{
    return HeapAlloc(_heap, 0, size);
}

// 0x19f80
void* HeapMemoryManager::AllocZero(unsigned long long size, wchar_t const* file, int line) const
{
    return HeapAlloc(_heap, HEAP_ZERO_MEMORY, size);
}

// 0x19fa0
void* HeapMemoryManager::Realloc(void* ptr, unsigned long long size, wchar_t const* file, int line) const
{
    if (ptr == nullptr)
        return HeapAlloc(_heap, 0, size);
    return HeapReAlloc(_heap, 0, ptr, size);
}

// 0x19fc0
void* HeapMemoryManager::ReallocZero(void* ptr, unsigned long long size, unsigned long long oldSize,
                                     wchar_t const* file, int line) const
{
    if (ptr == nullptr)
        return HeapAlloc(_heap, HEAP_ZERO_MEMORY, size);
    return HeapReAlloc(_heap, HEAP_ZERO_MEMORY, ptr, size);
}

// 0x19ff0
void HeapMemoryManager::Free(void* ptr, wchar_t const* file, int line) const
{
    HeapFree(_heap, 0, ptr);
}

// 0x1a000
PagePoolMemoryManager::~PagePoolMemoryManager()
{
}

// 0x1a010
bool PagePoolMemoryManager::Initialize(unsigned long long size)
{
    if (_allocSize != 0)
    {
        Log::Write(Log::LT_ERROR, L"source\\MemoryManager.cpp", 266,
                   L"== CRASH == [memory], Page Pool Memory Manager already initialized");
        AlertSender::Write(L"source\\MemoryManager.cpp", 266,
                           L"== CRASH == [memory], Page Pool Memory Manager already initialized");
        return false;
    }
    if (size < 1024 || size > _granularity)
    {
        Log::Write(Log::LT_ERROR, L"source\\MemoryManager.cpp", 271,
                   L"== CRASH == [memory], Page Pool Memory Manager initialization failed, size: %d", size);
        AlertSender::Write(L"source\\MemoryManager.cpp", 271,
                           L"== CRASH == [memory], Page Pool Memory Manager initialization failed, size: %d", size);
        return false;
    }
    // The size must be a power of two (from 1024 to the granularity).
    for (unsigned long long check = 1024; check < _granularity && check != size; check *= 2)
    {
        if (check > size)
        {
            Log::Write(Log::LT_ERROR, L"source\\MemoryManager.cpp", 279,
                       L"== CRASH == [memory], Page Pool Memory Manager allocation size is invalid, size: %d", size);
            AlertSender::Write(L"source\\MemoryManager.cpp", 279,
                               L"== CRASH == [memory], Page Pool Memory Manager allocation size is invalid, size: %d",
                               size);
            return false;
        }
    }
    _allocSize = size;
    return true;
}

// 0x1a100
void* PagePoolMemoryManager::Alloc()
{
    _lock.Enter();
    if (_block >= _blockEnd)
    {
        _block = static_cast<unsigned char*>(VirtualAlloc(nullptr, _granularity, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE));
        _blockEnd = _block + _granularity;
    }
    unsigned char* block = _block;
    _block = block + _allocSize;
    _lock.Leave();
    return block;
}

// 0x1a190
StaticPageMemoryManager::~StaticPageMemoryManager()
{
}

// 0x1a1a0
// LTCG gave a copy with size 2048 and allocated 584. This is the generic form.
bool StaticPageMemoryManager::Initialize(void* page, unsigned long long size, unsigned long long allocated,
                                         MemoryManager const* additional)
{
    if (page == nullptr)
    {
        Log::Write(Log::LT_ERROR, L"source\\MemoryManager.cpp", 334,
                   L"== CRASH == [memory], static page memory manager initialization failed, page: %p, size: %d, "
                   L"allocated: %d",
                   page, size, allocated);
        AlertSender::Write(L"source\\MemoryManager.cpp", 334,
                           L"== CRASH == [memory], static page memory manager initialization failed, page: %p, "
                           L"size: %d, allocated: %d",
                           page, size, allocated);
        return false;
    }
    _start = static_cast<unsigned char*>(page);
    _additional = additional;
    _end = _start + size;
    _current = _start + ((allocated + 15) & ~15ULL);
    return true;
}

// 0x1a240
void* StaticPageMemoryManager::allocate(unsigned long long size, wchar_t const* file, int line)
{
    if (_current == nullptr)
    {
        Log::Write(Log::LT_ERROR, L"source\\MemoryManager.cpp", 352, L"[memory], static page memory not initialized");
        return nullptr;
    }
    unsigned long long freeSize = _end - _current;
    unsigned long long allocSize = (size + 15) & ~15ULL;
    if (freeSize >= allocSize)
    {
        _current += allocSize;
        return _current - allocSize;
    }
    if (_additional != nullptr)
        return _additional->Alloc(allocSize, file, line);
    Log::Write(Log::LT_ERROR, L"source\\MemoryManager.cpp", 362,
               L"[memory], static page memory full, free size: %d, size: %d", freeSize, allocSize);
    return nullptr;
}

// 0x1a2e0
void* StaticPageMemoryManager::Alloc(unsigned long long size, wchar_t const* file, int line) const
{
    return const_cast<StaticPageMemoryManager*>(this)->allocate(size, file, line);
}

// 0x1a2f0
// BUG: 0x1a2f0 _additional is not checked for null.
void StaticPageMemoryManager::Free(void* ptr, wchar_t const* file, int line) const
{
    if (ptr < _start || ptr >= _end)
        _additional->Free(ptr, file, line);
}
