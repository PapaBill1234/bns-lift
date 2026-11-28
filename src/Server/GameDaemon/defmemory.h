// defmemory.h: defmemory.cpp, defmemory.h (GameDaemon PDB, 2019 + PDB).
#pragma once
#include "GameDaemonFwd.h"
#include <new>

// PDB layout (size 0x10): base DrMemory, heap at +8.
class DrHeapMemory : public DrMemory
{
public:
    // LIFT: noinline (lessons A4). Both Instance bodies (0x6ecf90, 0x6ecff0) call the ctor out of line in the original.
    __declspec(noinline) __cdecl DrHeapMemory(void);  // 0x6ed620
    virtual __cdecl ~DrHeapMemory(void);  // 0x6ed5e0
    virtual void * __cdecl Alloc(unsigned __int64 size, wchar_t const * file, int line);  // 0x6ed600
    virtual void * __cdecl Realloc(void * ptr, unsigned __int64 size, wchar_t const * file, int line);  // 0x6b7dc0
    virtual void __cdecl Free(void * ptr, wchar_t const * file, int line);  // 0x6b7e10
protected:
    void * heap;
};

// PDB layout (size 0x10): base DrHeapMemory, no own members.
class DrBaseDynamicMemory : public DrHeapMemory
{
public:
    static ::DrBaseDynamicMemory * __cdecl Instance(void);  // 0x6ecff0
};

// PDB layout (size 0x10): base DrHeapMemory, no own members.
class DrBaseStaticMemory : public DrHeapMemory
{
public:
    static ::DrBaseStaticMemory * __cdecl Instance(void);  // 0x6ecf90
};

// LIFT: per-exe path literal of the 2019 build (lessons A6).
#define DR_DEFMEMORY_FILE L"e:\\dailybuild02\\platformbinary-common-0.0.346\\depot\\branch\\346nc\\program\\library\\datareader\\src\\DefMemory.h"

// PDB layout (size 0x8): base DrMemory, static memory[2].
class DrMemoryManager : public DrMemory
{
public:
    enum Section
    {
        SECTION_STATIC = 0,
        SECTION_DYNAMIC = 1,
        SECTION_MAX = 2,
    };
public:
    static bool __cdecl SetupMemory(::DrMemoryManager::Section section, ::DrMemory * memory);  // 0x6ed5c0
    static ::DrMemory * __cdecl Memory(::DrMemoryManager::Section section);  // 0x6ed6a0
private:
    static ::DrMemory * memory[SECTION_MAX];
};

// LIFT: inline array helper of DefMemory.h (line 193 of the 2019 build). The PDB has no name for it (inlined), so DrNewArray is a lift name.
template <class T>
inline T * DrNewArray(int count)
{
    T * p = static_cast<T *>(DrMemoryManager::Memory(DrMemoryManager::SECTION_STATIC)->Alloc(sizeof(T) * count, DR_DEFMEMORY_FILE, 193));
    for (int i = 0; i < count; ++i)
        ::new (static_cast<void *>(&p[i])) T();
    return p;
}

