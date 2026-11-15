// Memory.obj (CacheGate PDB).
#include "Memory.h"
#include <new>

MemoryManager const* Memory::_Manager[3] = {};

// 0xdd10
// LTCG removed type, size and createAllocationHistory. The binary gets only the
// option in rcx and gives size 0. The PDB signature is kept here.
// BUG: 0xdd10 the result of Alloc is not checked for null before the Initialize call.
MemoryManager const* Memory::CreateManager(MgrType type, void const* option, unsigned long long size,
                                           bool createAllocationHistory)
{
    void* memory = BaseMemoryManager::_Instance.Alloc(sizeof(HeapMemoryManager), L"source\\Memory.cpp", 22);
    MemoryManager* manager = memory != nullptr ? new (memory) HeapMemoryManager() : nullptr;
    manager->Initialize(option, size);
    return manager;
}
