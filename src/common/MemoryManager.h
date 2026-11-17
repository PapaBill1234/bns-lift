// MemoryManager.obj (CacheGate PDB). Layouts from include/pdb/CacheGate/types.h.
#pragma once
#include "Lock.h"

class MemoryManager
{
public:
    virtual ~MemoryManager() {}                                                     // slot 0
protected:
    virtual bool Initialize(void const* option, unsigned long long size) = 0;      // slot 1
public:
    virtual void Clear() = 0;                                                       // slot 2
    virtual void* Alloc(unsigned long long size, wchar_t const* file, int line) const = 0;  // slot 3
    virtual void* AllocZero(unsigned long long size, wchar_t const* file, int line) const = 0;  // slot 4
    virtual void* Realloc(void* ptr, unsigned long long size, wchar_t const* file, int line) const = 0;  // slot 5
    virtual void* ReallocZero(void* ptr, unsigned long long size, unsigned long long oldSize,
                              wchar_t const* file, int line) const = 0;            // slot 6
    virtual void Free(void* ptr, wchar_t const* file, int line) const = 0;          // slot 7
    virtual void DumpLeak(wchar_t const* path) const {}                             // slot 8

    friend class Memory;
};
static_assert(sizeof(MemoryManager) == 0x8, "sizeof MemoryManager");

class HeapMemoryManager : public MemoryManager
{
public:
    HeapMemoryManager() : _heap(HeapCreate(0, 0, 0)) {}
    virtual ~HeapMemoryManager() { HeapDestroy(_heap); }
protected:
    virtual bool Initialize(void const* option, unsigned long long size);
public:
    virtual void Clear() {}
    virtual void* Alloc(unsigned long long size, wchar_t const* file, int line) const;
    virtual void* AllocZero(unsigned long long size, wchar_t const* file, int line) const;
    virtual void* Realloc(void* ptr, unsigned long long size, wchar_t const* file, int line) const;
    virtual void* ReallocZero(void* ptr, unsigned long long size, unsigned long long oldSize,
                              wchar_t const* file, int line) const;
    virtual void Free(void* ptr, wchar_t const* file, int line) const;

    static void const* const LFH;

    void* _heap;
};
static_assert(sizeof(HeapMemoryManager) == 0x10, "sizeof HeapMemoryManager");

class BaseMemoryManager : public HeapMemoryManager
{
public:
    static BaseMemoryManager _Instance;
};
static_assert(sizeof(BaseMemoryManager) == 0x10, "sizeof BaseMemoryManager");

class StaticPageMemoryManager : public MemoryManager
{
public:
    StaticPageMemoryManager() : _start(nullptr), _end(nullptr), _current(nullptr), _additional(nullptr) {}
    virtual ~StaticPageMemoryManager();
    virtual bool Initialize(void const* option, unsigned long long size);
    virtual void Clear();
    virtual void* Alloc(unsigned long long size, wchar_t const* file, int line) const;
    virtual void* AllocZero(unsigned long long size, wchar_t const* file, int line) const;
    virtual void* Realloc(void* ptr, unsigned long long size, wchar_t const* file, int line) const;
    virtual void* ReallocZero(void* ptr, unsigned long long size, unsigned long long oldSize,
                              wchar_t const* file, int line) const;
    virtual void Free(void* ptr, wchar_t const* file, int line) const;

    bool Initialize(void* page, unsigned long long size, unsigned long long allocated,
                    MemoryManager const* additional);

private:
    void* allocate(unsigned long long size, wchar_t const* file, int line);

    unsigned char* _start;
    unsigned char* _end;
    unsigned char* _current;
    MemoryManager const* _additional;

    friend class Session;  // LIFT: access helper. No PDB in the set has friend records. Session::~Session (0x1BA50) reads _start and _end (PDB: private).
};
static_assert(sizeof(StaticPageMemoryManager) == 0x28, "sizeof StaticPageMemoryManager");

class PagePoolMemoryManager
{
public:
    PagePoolMemoryManager(unsigned long long granularity)  // LIFT: inlined constructor (0x135D0)
        : _allocSize(0), _granularity(granularity), _block(nullptr), _blockEnd(nullptr) {}
    ~PagePoolMemoryManager();
    bool Initialize(unsigned long long size);
    void* Alloc();

    unsigned long long _allocSize;
    unsigned long long _granularity;
    unsigned char* _block;
    unsigned char* _blockEnd;
    CriticalSection _lock;
};
static_assert(sizeof(PagePoolMemoryManager) == 0x48, "sizeof PagePoolMemoryManager");
static_assert(offsetof(PagePoolMemoryManager, _lock) == 0x20, "PagePoolMemoryManager::_lock");
