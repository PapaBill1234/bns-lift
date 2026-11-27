// changeweaponappearancetran_h.cpp: changeweaponappearancetran.h (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "changeweaponappearancetran.h"
#include "LiftStub.h"

// 0x714c0
::GameTranDef const * __cdecl ChangeWeaponAppearanceTran::GetDefinition(void) const
{
    return &ChangeWeaponAppearanceTran::_def;
}
#pragma comment(linker, "/INCLUDE:?GetDefinition@ChangeWeaponAppearanceTran@@UEBAPEBUGameTranDef@@XZ")  // LIFT: dead-strip keep (no live caller yet)
// LIFT: placeholder. The real _def needs the state tables of the class (a later card).
::GameTranDef ChangeWeaponAppearanceTran::_def;
