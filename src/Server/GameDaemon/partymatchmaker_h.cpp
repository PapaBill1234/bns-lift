// partymatchmaker_h.cpp: partymatchmaker.h (GameDaemon PDB, 2019 + PDB).
#include "partymatchmaker.h"
#include "LiftStub.h"

#pragma comment(linker, "/INCLUDE:?Name@PartyMatchMaker@@UEAAPEB_WXZ")  // LIFT: dead-strip keep (no live caller yet)

// 0x180b90
wchar_t const * __cdecl PartyMatchMaker::Name(void)
{
    return L"PartyMatchMaker";
}
