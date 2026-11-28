// battleroyalfield_h.cpp: battleroyalfield.h (GameDaemon PDB, 2019 + PDB).
#include "battleroyalfield.h"
#include "LiftStub.h"

#pragma comment(linker, "/INCLUDE:?GetTypeName@BattleRoyalField@@UEAAPEB_WXZ")  // LIFT: dead-strip keep (no live caller yet)

// 0x35f60
wchar_t const * __cdecl BattleRoyalField::GetTypeName(void)
{
    return L"BattleRoyalField";
}
