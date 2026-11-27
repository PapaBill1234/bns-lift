// npservicetran_h.cpp: npservicetran.h (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "npservicetran.h"
#include "LiftStub.h"

// 0x121950
::GameTranDef const * __cdecl NPRegisterServiceTran::GetDefinition(void) const
{
    return &NPRegisterServiceTran::_def;
}
#pragma comment(linker, "/INCLUDE:?GetDefinition@NPRegisterServiceTran@@UEBAPEBUGameTranDef@@XZ")  // LIFT: dead-strip keep (no live caller yet)
// LIFT: placeholder. The real _def needs the state tables of the class (a later card).
::GameTranDef NPRegisterServiceTran::_def;

// 0x121960
::GameTranDef const * __cdecl NPValidateGroupTran::GetDefinition(void) const
{
    return &NPValidateGroupTran::_def;
}
#pragma comment(linker, "/INCLUDE:?GetDefinition@NPValidateGroupTran@@UEBAPEBUGameTranDef@@XZ")  // LIFT: dead-strip keep (no live caller yet)
// LIFT: placeholder. The real _def needs the state tables of the class (a later card).
::GameTranDef NPValidateGroupTran::_def;

// 0x121970
::GameTranDef const * __cdecl NPGetChannelPropertyTran::GetDefinition(void) const
{
    return &NPGetChannelPropertyTran::_def;
}
#pragma comment(linker, "/INCLUDE:?GetDefinition@NPGetChannelPropertyTran@@UEBAPEBUGameTranDef@@XZ")  // LIFT: dead-strip keep (no live caller yet)
// LIFT: placeholder. The real _def needs the state tables of the class (a later card).
::GameTranDef NPGetChannelPropertyTran::_def;

// 0x121980
::GameTranDef const * __cdecl NPGroupInfoTran::GetDefinition(void) const
{
    return &NPGroupInfoTran::_def;
}
#pragma comment(linker, "/INCLUDE:?GetDefinition@NPGroupInfoTran@@UEBAPEBUGameTranDef@@XZ")  // LIFT: dead-strip keep (no live caller yet)
// LIFT: placeholder. The real _def needs the state tables of the class (a later card).
::GameTranDef NPGroupInfoTran::_def;
