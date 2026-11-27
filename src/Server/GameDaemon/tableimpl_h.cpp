// tableimpl_h.cpp: tableimpl.h (GameDaemon PDB, 2019 + PDB).
#include "tableimpl.h"
#include "LiftStub.h"

// LIFT: keep the lifted virtual function until the callers are lifted (the vftable and the callers are stubs;
// /OPT:REF drops it). Card lift-gamedaemon-gap-005-e5.
#pragma comment(linker, "/INCLUDE:?UseLegacyElHeader@DrDataTableImpl@@UEAAX_N@Z")  // LIFT: dead-strip keep (no live caller yet)

// 0x6fd290
void __cdecl DrDataTableImpl::UseLegacyElHeader(bool useLegacyElHeader)
{
    _useLegacyElHeader = useLegacyElHeader;
}
