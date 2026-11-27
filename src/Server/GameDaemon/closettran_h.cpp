// closettran_h.cpp: closettran.h (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "closettran.h"
#include "LiftStub.h"

// 0x80070
::GameTranDef const * __cdecl PutItemIntoClosetTran::GetDefinition(void) const
{
    return &PutItemIntoClosetTran::_def;
}
#pragma comment(linker, "/INCLUDE:?GetDefinition@PutItemIntoClosetTran@@UEBAPEBUGameTranDef@@XZ")  // LIFT: dead-strip keep (no live caller yet)
// LIFT: placeholder. The real _def needs the state tables of the class (a later card).
::GameTranDef PutItemIntoClosetTran::_def;

// 0x80080
::GameTranDef const * __cdecl TakeItemFromClosetTran::GetDefinition(void) const
{
    return &TakeItemFromClosetTran::_def;
}
#pragma comment(linker, "/INCLUDE:?GetDefinition@TakeItemFromClosetTran@@UEBAPEBUGameTranDef@@XZ")  // LIFT: dead-strip keep (no live caller yet)
// LIFT: placeholder. The real _def needs the state tables of the class (a later card).
::GameTranDef TakeItemFromClosetTran::_def;
