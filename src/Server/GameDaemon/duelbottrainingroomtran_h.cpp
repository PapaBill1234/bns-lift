// duelbottrainingroomtran_h.cpp: duelbottrainingroomtran.h (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "duelbottrainingroomtran.h"
#include "LiftStub.h"

// 0xaca50
::GameTranDef const * __cdecl DuelBotTrainingRoomResultTran::GetDefinition(void) const
{
    return &DuelBotTrainingRoomResultTran::_def;
}
#pragma comment(linker, "/INCLUDE:?GetDefinition@DuelBotTrainingRoomResultTran@@UEBAPEBUGameTranDef@@XZ")  // LIFT: dead-strip keep (no live caller yet)
// LIFT: placeholder. The real _def needs the state tables of the class (a later card).
::GameTranDef DuelBotTrainingRoomResultTran::_def;

// 0xaca60
::GameTranDef const * __cdecl DuelBotTrainingRoomRewardTran::GetDefinition(void) const
{
    return &DuelBotTrainingRoomRewardTran::_def;
}
#pragma comment(linker, "/INCLUDE:?GetDefinition@DuelBotTrainingRoomRewardTran@@UEBAPEBUGameTranDef@@XZ")  // LIFT: dead-strip keep (no live caller yet)
// LIFT: placeholder. The real _def needs the state tables of the class (a later card).
::GameTranDef DuelBotTrainingRoomRewardTran::_def;
