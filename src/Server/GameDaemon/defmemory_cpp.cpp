// defmemory_cpp.cpp: defmemory.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "defmemory.h"
#include "LiftStub.h"

// 0x6ed5c0
bool __cdecl DrMemoryManager::SetupMemory(::DrMemoryManager::Section, ::DrMemory *)
{
    LIFT_STUB(0x6ed5c0);
}

// 0x6ed5e0
__cdecl DrHeapMemory::~DrHeapMemory(void)
{
    LIFT_STUB(0x6ed5e0);
}

// 0x6ed600
void * __cdecl DrHeapMemory::Alloc(unsigned __int64, wchar_t const *, int)
{
    LIFT_STUB(0x6ed600);
}

// 0x6ed620
__cdecl DrHeapMemory::DrHeapMemory(void)
{
    LIFT_STUB(0x6ed620);
}

// 0x6ed6a0
::DrMemory * __cdecl DrMemoryManager::Memory(::DrMemoryManager::Section)
{
    LIFT_STUB(0x6ed6a0);
}
