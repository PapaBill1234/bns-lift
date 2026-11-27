// defmemory_cpp.cpp: defmemory.cpp (GameDaemon PDB, 2019 + PDB).
#include "defmemory.h"
#include "LiftStub.h"

#pragma comment(linker, "/INCLUDE:?SetupMemory@DrMemoryManager@@SA_NW4Section@1@PEAVDrMemory@@@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:??0DrHeapMemory@@QEAA@XZ")  // LIFT: dead-strip keep (no live caller yet)

::DrMemory * DrMemoryManager::memory[DrMemoryManager::SECTION_MAX];

// 0x6ed5c0
bool __cdecl DrMemoryManager::SetupMemory(::DrMemoryManager::Section section, ::DrMemory * memory)
{
    if (section < 0 || section >= SECTION_MAX)
        return false;

    DrMemoryManager::memory[section] = memory;
    return true;
}

// 0x6ed620
__cdecl DrHeapMemory::DrHeapMemory(void)
    : heap(nullptr)
{
    heap = ::HeapCreate(0, 0, 0);
}

// 0x6ed5e0
__cdecl DrHeapMemory::~DrHeapMemory(void)
{
    ::HeapDestroy(heap);
}

// 0x6ed600
void * __cdecl DrHeapMemory::Alloc(unsigned __int64 size, wchar_t const * file, int line)
{
    return ::HeapAlloc(heap, HEAP_GENERATE_EXCEPTIONS, size);
}

// 0x6b7dc0 (folded with HeapMemoryManager::Realloc). LIFT: the vtable of the ctor needs it.
void * __cdecl DrHeapMemory::Realloc(void * ptr, unsigned __int64 size, wchar_t const * file, int line)
{
    // LIFT: same source form as HeapMemoryManager::Realloc (BloodLib). The linker folds the 2 bodies (ICF) only when the code is the same.
    if (ptr == nullptr)
        return ::HeapAlloc(heap, 0, size);
    return ::HeapReAlloc(heap, 0, ptr, size);
}

// 0x6b7e10 (folded with HeapMemoryManager::Free). LIFT: the vtable of the ctor needs it.
void __cdecl DrHeapMemory::Free(void * ptr, wchar_t const * file, int line)
{
    ::HeapFree(heap, 0, ptr);
}

// 0x6ed6a0
::DrMemory * __cdecl DrMemoryManager::Memory(::DrMemoryManager::Section)
{
    LIFT_STUB(0x6ed6a0);
}
