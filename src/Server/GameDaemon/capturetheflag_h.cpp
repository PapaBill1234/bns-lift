// capturetheflag_h.cpp: capturetheflag.h (GameDaemon PDB, 2019 + PDB).
#include "capturetheflag.h"
#include "LiftStub.h"

#pragma comment(linker, "/INCLUDE:?Context1@CaptureTheFlag@@UEAA_JXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?Context2@CaptureTheFlag@@UEAA_JXZ")  // LIFT: dead-strip keep (no live caller yet)

// 0x180ed0
__int64 __cdecl CaptureTheFlag::Context1(void)
{
    return _flagCount;
}

// 0x180ee0
__int64 __cdecl CaptureTheFlag::Context2(void)
{
    return _lastFlagSpawnedTime;
}
