// serializedobject_h.cpp: serializedobject.h (GameDaemon PDB, 2019 + PDB).
#include "serializedobject.h"
#include "LiftStub.h"

#pragma comment(linker, "/INCLUDE:?TimerExpired@LtExpireSO@@MEAAXJ@Z")  // LIFT: dead-strip keep (no live caller yet)

// 0x4307b0
void __cdecl LtExpireSO::TimerExpired(long)
{
    _enable = false;
}
