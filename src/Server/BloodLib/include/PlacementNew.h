#pragma once

#include <stddef.h>

// Memory.h:173 (CacheGate 0x1000). Include this before the CRT placement operators.
#define __PLACEMENT_NEW_INLINE
inline void* __cdecl operator new(size_t, void* where) throw() { return where; }
void __cdecl operator delete(void*, void*) throw();
