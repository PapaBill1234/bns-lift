// marketservicetran_h.cpp: marketservicetran.h (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "marketservicetran.h"
#include "LiftStub.h"

// 0x15af00
::GameTranDef const * __cdecl RegisterPurchaseTran::GetDefinition(void) const
{
    return &RegisterPurchaseTran::_def;
}
#pragma comment(linker, "/INCLUDE:?GetDefinition@RegisterPurchaseTran@@UEBAPEBUGameTranDef@@XZ")  // LIFT: dead-strip keep (no live caller yet)
// LIFT: placeholder. The real _def needs the state tables of the class (a later card).
::GameTranDef RegisterPurchaseTran::_def;

// 0x15af10
::GameTranDef const * __cdecl RegisterBidTran::GetDefinition(void) const
{
    return &RegisterBidTran::_def;
}
#pragma comment(linker, "/INCLUDE:?GetDefinition@RegisterBidTran@@UEBAPEBUGameTranDef@@XZ")  // LIFT: dead-strip keep (no live caller yet)
// LIFT: placeholder. The real _def needs the state tables of the class (a later card).
::GameTranDef RegisterBidTran::_def;

// 0x15af20
::GameTranDef const * __cdecl UpdateBidTran::GetDefinition(void) const
{
    return &UpdateBidTran::_def;
}
#pragma comment(linker, "/INCLUDE:?GetDefinition@UpdateBidTran@@UEBAPEBUGameTranDef@@XZ")  // LIFT: dead-strip keep (no live caller yet)
// LIFT: placeholder. The real _def needs the state tables of the class (a later card).
::GameTranDef UpdateBidTran::_def;
