// defmemory_h.cpp: defmemory.h (GameDaemon PDB, 2019 + PDB).
#include "defmemory.h"

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
