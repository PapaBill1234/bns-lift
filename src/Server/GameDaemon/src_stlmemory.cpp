// src_stlmemory.cpp: stlmemory.h (GameDaemon PDB, 2019 + PDB).
// LIFT: the bodies are in stlmemory.h. This file instantiates the members of this card until a lifted caller uses them.
#include "drstlmemory.h"
#include <string>

#pragma comment(linker, "/INCLUDE:?allocate@?$DrStlAllocator@_W$00@@QEAAPEA_W_K@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?deallocate@?$DrStlAllocator@V?$basic_string@_WU?$char_traits@_W@std@@V?$DrStlAllocator@_W$00@@@std@@$00@@QEAAXPEAV?$basic_string@_WU?$char_traits@_W@std@@V?$DrStlAllocator@_W$00@@@std@@_K@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?deallocate@?$DrStlAllocator@PEAUDrEl@@$0A@@@QEAAXPEAPEAUDrEl@@_K@Z")  // LIFT: dead-strip keep (no live caller yet)

// 0x6ee800 DrStlAllocator<wchar_t,1>::allocate
template wchar_t * DrStlAllocator<wchar_t, 1>::allocate(unsigned __int64);

// 0x6f35d0 DrStlAllocator<std::basic_string<wchar_t,std::char_traits<wchar_t>,DrStlAllocator<wchar_t,1> >,1>::deallocate
template void DrStlAllocator< ::std::basic_string<wchar_t, ::std::char_traits<wchar_t>, DrStlAllocator<wchar_t, 1> >, 1>::deallocate(::std::basic_string<wchar_t, ::std::char_traits<wchar_t>, DrStlAllocator<wchar_t, 1> > *, unsigned __int64);

// 0x6fd420 DrStlAllocator<DrEl * __ptr64,0>::deallocate
template void DrStlAllocator< ::DrEl *, 0>::deallocate(::DrEl **, unsigned __int64);
