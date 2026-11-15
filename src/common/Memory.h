// Memory.obj (CacheGate PDB).
#pragma once
#include "MemoryManager.h"

class Memory
{
public:
    enum MgrType
    {
        MMGR_DEFAULT = 0,
        MMGR_DEBUG = 1,
        MMGR_MAX = 2,
    };

    static MemoryManager const* CreateManager(MgrType type, void const* option, unsigned long long size,
                                              bool createAllocationHistory);

    // The PDB array has 24 bytes (3 entries). StlAllocator<T,2> uses entry 2.
    static MemoryManager const* _Manager[3];
};
