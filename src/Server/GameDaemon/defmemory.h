// defmemory.h: defmemory.cpp, defmemory.h (GameDaemon PDB, 2019 + PDB).
// LIFT: DrBaseDynamicMemory and DrBaseStaticMemory have no members yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class DrBaseDynamicMemory
{
public:
    static ::DrBaseDynamicMemory * __cdecl Instance(void);  // 0x6ecff0
};

class DrBaseStaticMemory
{
public:
    static ::DrBaseStaticMemory * __cdecl Instance(void);  // 0x6ecf90
};

// PDB layout (size 0x10): base DrMemory, heap at +8.
class DrHeapMemory : public DrMemory
{
public:
    __cdecl DrHeapMemory(void);  // 0x6ed620
    virtual __cdecl ~DrHeapMemory(void);  // 0x6ed5e0
    virtual void * __cdecl Alloc(unsigned __int64 size, wchar_t const * file, int line);  // 0x6ed600
    virtual void * __cdecl Realloc(void * ptr, unsigned __int64 size, wchar_t const * file, int line);  // 0x6b7dc0
    virtual void __cdecl Free(void * ptr, wchar_t const * file, int line);  // 0x6b7e10
protected:
    void * heap;
};

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

