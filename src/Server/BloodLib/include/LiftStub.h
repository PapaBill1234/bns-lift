// LIFT: Build helper, no PDB module. It marks a function that has no lifted body yet.
// A stub must not report success. LIFT_STUB stops the process: it breaks into a debugger and then aborts.
// LIFT: VS2010 stdlib.h does not declare abort noreturn. __assume(0) marks the end as unreachable,
// so that a stub with a return type compiles without error C4716.
// Find all stubs with: grep -rn "LIFT_STUB(" src
// The argument is the RVA of the function in LobbyDaemon.exe (2019 + PDB).
#pragma once
#include <intrin.h>
#include <stdlib.h>

#define LIFT_STUB(rva)     \
    do                     \
    {                      \
        (void)(rva);       \
        __debugbreak();    \
        ::abort();         \
        __assume(0);       \
    } while (0)
