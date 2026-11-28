// defmemory_h.cpp: defmemory.h (GameDaemon PDB, 2019 + PDB).
#include "defmemory.h"

// LIFT: DrBaseStaticMemory::Instance is kept by DrMemoryManager::Memory. DrBaseDynamicMemory::Instance has no lifted caller.
#pragma comment(linker, "/INCLUDE:?Instance@DrBaseDynamicMemory@@SAPEAV1@XZ")  // LIFT: dead-strip keep (no live caller yet)

// 0x6ecf90
::DrBaseStaticMemory * __cdecl DrBaseStaticMemory::Instance(void)
{
    static DrBaseStaticMemory instance;
    return &instance;
}

// 0x6ecff0
::DrBaseDynamicMemory * __cdecl DrBaseDynamicMemory::Instance(void)
{
    static DrBaseDynamicMemory instance;
    return &instance;
}
