// seasoncontentstran_h.cpp: seasoncontentstran.h (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "seasoncontentstran.h"
#include "LiftStub.h"

// 0x180c70
::GameTranDef const * __cdecl PartyBattleResultTran::GetDefinition(void) const
{
    return &PartyBattleResultTran::_def;
}
#pragma comment(linker, "/INCLUDE:?GetDefinition@PartyBattleResultTran@@UEBAPEBUGameTranDef@@XZ")  // LIFT: dead-strip keep (no live caller yet)
// LIFT: placeholder. The real _def needs the state tables of the class (a later card).
::GameTranDef PartyBattleResultTran::_def;

// 0x180c80
::GameTranDef const * __cdecl DuelResultTran::GetDefinition(void) const
{
    return &DuelResultTran::_def;
}
#pragma comment(linker, "/INCLUDE:?GetDefinition@DuelResultTran@@UEBAPEBUGameTranDef@@XZ")  // LIFT: dead-strip keep (no live caller yet)
// LIFT: placeholder. The real _def needs the state tables of the class (a later card).
::GameTranDef DuelResultTran::_def;

// 0x180c90
::GameTranDef const * __cdecl TimeAttackRecordResultTran::GetDefinition(void) const
{
    return &TimeAttackRecordResultTran::_def;
}
#pragma comment(linker, "/INCLUDE:?GetDefinition@TimeAttackRecordResultTran@@UEBAPEBUGameTranDef@@XZ")  // LIFT: dead-strip keep (no live caller yet)
// LIFT: placeholder. The real _def needs the state tables of the class (a later card).
::GameTranDef TimeAttackRecordResultTran::_def;
