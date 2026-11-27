// user_h.cpp: user.h (GameDaemon PDB, 2019 + PDB). Lifted: GetId (card lift-gamedaemon-gap-006-e6).
#include "user.h"
#include "LiftStub.h"

// LIFT: keep the lifted virtual until the callers are lifted (the vftable and the callers are stubs;
// /OPT:REF drops it). Card lift-gamedaemon-gap-006-e6.
#pragma comment(linker, "/INCLUDE:?GetId@User@@UEAA_KXZ")  // LIFT: dead-strip keep (no live caller yet)

// 0x3502e0
unsigned __int64 __cdecl User::GetId(void)
{
    return PcDbId;
}
