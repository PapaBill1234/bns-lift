// bannedwordfiltermemorymanager.h: bannedwordfiltermemorymanager.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class BannedWordFilterDynamicMemoryManager
{
public:
    virtual void * __cdecl Alloc(unsigned __int64, wchar_t const *, int);  // 0x33a160
    virtual void * __cdecl Realloc(void *, unsigned __int64, wchar_t const *, int);  // 0x33a170
    virtual void __cdecl Free(void *, wchar_t const *, int);  // 0x616fa0
};

