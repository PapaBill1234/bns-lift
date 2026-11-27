// defmemory.h: defmemory.cpp, defmemory.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
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

class DrHeapMemory
{
public:
    virtual __cdecl ~DrHeapMemory(void);  // 0x6ed5e0
    virtual void * __cdecl Alloc(unsigned __int64, wchar_t const *, int);  // 0x6ed600
    __cdecl DrHeapMemory(void);  // 0x6ed620
};

class DrMemoryManager
{
public:
    enum Section {};
public:
    static bool __cdecl SetupMemory(::DrMemoryManager::Section, ::DrMemory *);  // 0x6ed5c0
    static ::DrMemory * __cdecl Memory(::DrMemoryManager::Section);  // 0x6ed6a0
};

