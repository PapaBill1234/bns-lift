// defmemory_h.cpp: defmemory.h (GameDaemon PDB, 2019 + PDB).
#include "defmemory.h"

// LIFT: DrBaseStaticMemory::Instance is kept by DrMemoryManager::Memory. DrBaseDynamicMemory::Instance has no lifted caller.
#pragma comment(linker, "/INCLUDE:?Instance@DrBaseDynamicMemory@@SAPEAV1@XZ")  // LIFT: dead-strip keep (no live caller yet)

// LIFT: empty PDB dtors. Defined in this file, apart from ~DrHeapMemory (defmemory_cpp.cpp), so the
// deleting dtor calls ~DrHeapMemory out of line (0x6eb430) and does not fold with 0x6ed660.
__cdecl DrBaseStaticMemory::~DrBaseStaticMemory(void)
{
}

__cdecl DrBaseDynamicMemory::~DrBaseDynamicMemory(void)
{
}

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
