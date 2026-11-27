// bannedwordfiltermemorymanager.cpp: bannedwordfiltermemorymanager.h (GameDaemon PDB, 2019 + PDB).
#include "bannedwordfiltermemorymanager.h"
#include "Memory.h"
#include "MemoryManager.h"
#include "LiftStub.h"

#pragma comment(linker, "/INCLUDE:?Alloc@BannedWordFilterDynamicMemoryManager@@UEAAPEAX_KPEB_WH@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?Realloc@BannedWordFilterDynamicMemoryManager@@UEAAPEAXPEAX_KPEB_WH@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?Free@BannedWordFilterDynamicMemoryManager@@UEAAXPEAXPEB_WH@Z")  // LIFT: dead-strip keep (no live caller yet)

// 0x33a160
void * __cdecl BannedWordFilterDynamicMemoryManager::Alloc(unsigned __int64 size, wchar_t const *file, int line)
{
    return Memory::_Manager[2]->Alloc(size, file, line);
}

// 0x33a170
void * __cdecl BannedWordFilterDynamicMemoryManager::Realloc(void *ptr, unsigned __int64 size, wchar_t const *file, int line)
{
    return Memory::_Manager[2]->Realloc(ptr, size, file, line);
}

// 0x616fa0
void __cdecl BannedWordFilterDynamicMemoryManager::Free(void *ptr, wchar_t const *file, int line)
{
    Memory::_Manager[2]->Free(ptr, file, line);
}
