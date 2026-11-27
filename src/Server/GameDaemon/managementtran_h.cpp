// managementtran_h.cpp: managementtran.h (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "managementtran.h"
#include "LiftStub.h"

// 0x156b20
::GameTranDef const * __cdecl DepositInGuildBankTran::GetDefinition(void) const
{
    return &DepositInGuildBankTran::_def;
}
#pragma comment(linker, "/INCLUDE:?GetDefinition@DepositInGuildBankTran@@UEBAPEBUGameTranDef@@XZ")  // LIFT: dead-strip keep (no live caller yet)
// LIFT: placeholder. The real _def needs the state tables of the class (a later card).
::GameTranDef DepositInGuildBankTran::_def;

// 0x156b30
::GameTranDef const * __cdecl WithdrawFromGuildBankTran::GetDefinition(void) const
{
    return &WithdrawFromGuildBankTran::_def;
}
#pragma comment(linker, "/INCLUDE:?GetDefinition@WithdrawFromGuildBankTran@@UEBAPEBUGameTranDef@@XZ")  // LIFT: dead-strip keep (no live caller yet)
// LIFT: placeholder. The real _def needs the state tables of the class (a later card).
::GameTranDef WithdrawFromGuildBankTran::_def;
