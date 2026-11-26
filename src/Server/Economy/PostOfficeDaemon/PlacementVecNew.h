#pragma once
// LIFT: the original Memory.h (line 181) gives its own placement array new and delete. The PostOfficeDaemon PDB puts
// the one body of operator delete[](void*, void*) (0xb040) in RelayTimeContext.obj. Include this file before all
// other headers in each module that uses liftArrayNew. It stops <new> from giving its empty inline forms.
#define __PLACEMENT_VEC_NEW_INLINE
#include <stddef.h>

inline void* __cdecl operator new[](size_t, void* buf) throw()
{
    return buf;
}

// Defined in RelayTimeContext.cpp (0xb040).
void __cdecl operator delete[](void*, void*);
