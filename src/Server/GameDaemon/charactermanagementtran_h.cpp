// charactermanagementtran_h.cpp: charactermanagementtran.h (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "charactermanagementtran.h"
#include "LiftStub.h"

// 0x72590
::GameTranDef const * __cdecl CreateCharacterTran::GetDefinition(void) const
{
    return &CreateCharacterTran::_def;
}
#pragma comment(linker, "/INCLUDE:?GetDefinition@CreateCharacterTran@@UEBAPEBUGameTranDef@@XZ")  // LIFT: dead-strip keep (no live caller yet)
// LIFT: placeholder. The real _def needs the state tables of the class (a later card).
::GameTranDef CreateCharacterTran::_def;

// 0x725a0
::GameTranDef const * __cdecl ChangeCharacterAppearanceTran::GetDefinition(void) const
{
    return &ChangeCharacterAppearanceTran::_def;
}
#pragma comment(linker, "/INCLUDE:?GetDefinition@ChangeCharacterAppearanceTran@@UEBAPEBUGameTranDef@@XZ")  // LIFT: dead-strip keep (no live caller yet)
// LIFT: placeholder. The real _def needs the state tables of the class (a later card).
::GameTranDef ChangeCharacterAppearanceTran::_def;

// 0x725b0
::GameTranDef const * __cdecl ChangeCharacterSexTran::GetDefinition(void) const
{
    return &ChangeCharacterSexTran::_def;
}
#pragma comment(linker, "/INCLUDE:?GetDefinition@ChangeCharacterSexTran@@UEBAPEBUGameTranDef@@XZ")  // LIFT: dead-strip keep (no live caller yet)
// LIFT: placeholder. The real _def needs the state tables of the class (a later card).
::GameTranDef ChangeCharacterSexTran::_def;

// 0x725c0
::GameTranDef const * __cdecl ChangeCharacterRaceTran::GetDefinition(void) const
{
    return &ChangeCharacterRaceTran::_def;
}
#pragma comment(linker, "/INCLUDE:?GetDefinition@ChangeCharacterRaceTran@@UEBAPEBUGameTranDef@@XZ")  // LIFT: dead-strip keep (no live caller yet)
// LIFT: placeholder. The real _def needs the state tables of the class (a later card).
::GameTranDef ChangeCharacterRaceTran::_def;

// 0x725d0
::GameTranDef const * __cdecl RenameCharacterTran::GetDefinition(void) const
{
    return &RenameCharacterTran::_def;
}
#pragma comment(linker, "/INCLUDE:?GetDefinition@RenameCharacterTran@@UEBAPEBUGameTranDef@@XZ")  // LIFT: dead-strip keep (no live caller yet)
// LIFT: placeholder. The real _def needs the state tables of the class (a later card).
::GameTranDef RenameCharacterTran::_def;

// 0x725e0
::GameTranDef const * __cdecl DeleteCharacterTran::GetDefinition(void) const
{
    return &DeleteCharacterTran::_def;
}
#pragma comment(linker, "/INCLUDE:?GetDefinition@DeleteCharacterTran@@UEBAPEBUGameTranDef@@XZ")  // LIFT: dead-strip keep (no live caller yet)
// LIFT: placeholder. The real _def needs the state tables of the class (a later card).
::GameTranDef DeleteCharacterTran::_def;

// 0x725f0
::GameTranDef const * __cdecl RestoreCharacterTran::GetDefinition(void) const
{
    return &RestoreCharacterTran::_def;
}
#pragma comment(linker, "/INCLUDE:?GetDefinition@RestoreCharacterTran@@UEBAPEBUGameTranDef@@XZ")  // LIFT: dead-strip keep (no live caller yet)
// LIFT: placeholder. The real _def needs the state tables of the class (a later card).
::GameTranDef RestoreCharacterTran::_def;
