// accountinventorytran_h.cpp: accountinventorytran.h (GameDaemon PDB, 2019 + PDB). The GetDefinition getters are lifted.
// LIFT: the _def data is not lifted yet. The empty GameTranDef of the header stands in for the PDB data.
#include "accountinventorytran.h"
#include "LiftStub.h"

#pragma comment(linker, "/INCLUDE:?GetDefinition@AccountInventoryGetGoodsCountTran@@UEBAPEBUGameTranDef@@XZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetDefinition@AccountInventoryListGoodsTran@@UEBAPEBUGameTranDef@@XZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetDefinition@AccountInventoryTakeGoodsTran@@UEBAPEBUGameTranDef@@XZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetDefinition@AccountInventoryRetrieveWarehouseLobbyServiceItemListTran@@UEBAPEBUGameTranDef@@XZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetDefinition@AccountInventoryRetrieveWarehouseItemListTran@@UEBAPEBUGameTranDef@@XZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetDefinition@AccountInventoryTakeWarehouseItemTran@@UEBAPEBUGameTranDef@@XZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetDefinition@AccountInventoryJumpingCharacter2TicketTran@@UEBAPEBUGameTranDef@@XZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetDefinition@AccountInventoryBoardGachaParticipationCountPerSeasonTran@@UEBAPEBUGameTranDef@@XZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetDefinition@AccountInventoryBoardGachaParticipationInfoPerPcTran@@UEBAPEBUGameTranDef@@XZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetDefinition@AccountInventoryBoardGachaDrawByItemTran@@UEBAPEBUGameTranDef@@XZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetDefinition@AccountInventoryBoardGachaDrawByInstantPaymentTran@@UEBAPEBUGameTranDef@@XZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetDefinition@AccountInventoryBoardGachaParticipationRewardStateTran@@UEBAPEBUGameTranDef@@XZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetDefinition@AccountInventoryBoardGachaTakeParticipationRewardTran@@UEBAPEBUGameTranDef@@XZ")  // LIFT: dead-strip keep (no live caller yet)

// 0x1c30b0
::GameTranDef const * __cdecl AccountInventoryGetGoodsCountTran::GetDefinition(void) const
{
    return &_def;
}

// 0x1c30c0
::GameTranDef const * __cdecl AccountInventoryListGoodsTran::GetDefinition(void) const
{
    return &_def;
}

// 0x1c30d0
::GameTranDef const * __cdecl AccountInventoryTakeGoodsTran::GetDefinition(void) const
{
    return &_def;
}

// 0x1c30e0
::GameTranDef const * __cdecl AccountInventoryRetrieveWarehouseLobbyServiceItemListTran::GetDefinition(void) const
{
    return &_def;
}

// 0x1c30f0
::GameTranDef const * __cdecl AccountInventoryRetrieveWarehouseItemListTran::GetDefinition(void) const
{
    return &_def;
}

// 0x1c3100
::GameTranDef const * __cdecl AccountInventoryTakeWarehouseItemTran::GetDefinition(void) const
{
    return &_def;
}

// 0x1c3110
::GameTranDef const * __cdecl AccountInventoryJumpingCharacter2TicketTran::GetDefinition(void) const
{
    return &_def;
}

// 0x1c3120
::GameTranDef const * __cdecl AccountInventoryBoardGachaParticipationCountPerSeasonTran::GetDefinition(void) const
{
    return &_def;
}

// 0x1c3130
::GameTranDef const * __cdecl AccountInventoryBoardGachaParticipationInfoPerPcTran::GetDefinition(void) const
{
    return &_def;
}

// 0x1c3140
::GameTranDef const * __cdecl AccountInventoryBoardGachaDrawByItemTran::GetDefinition(void) const
{
    return &_def;
}

// 0x1c3150
::GameTranDef const * __cdecl AccountInventoryBoardGachaDrawByInstantPaymentTran::GetDefinition(void) const
{
    return &_def;
}

// 0x1c3160
::GameTranDef const * __cdecl AccountInventoryBoardGachaParticipationRewardStateTran::GetDefinition(void) const
{
    return &_def;
}

// 0x1c3170
::GameTranDef const * __cdecl AccountInventoryBoardGachaTakeParticipationRewardTran::GetDefinition(void) const
{
    return &_def;
}

::GameTranDef AccountInventoryGetGoodsCountTran::_def;
::GameTranDef AccountInventoryListGoodsTran::_def;
::GameTranDef AccountInventoryTakeGoodsTran::_def;
::GameTranDef AccountInventoryRetrieveWarehouseLobbyServiceItemListTran::_def;
::GameTranDef AccountInventoryRetrieveWarehouseItemListTran::_def;
::GameTranDef AccountInventoryTakeWarehouseItemTran::_def;
::GameTranDef AccountInventoryJumpingCharacter2TicketTran::_def;
::GameTranDef AccountInventoryBoardGachaParticipationCountPerSeasonTran::_def;
::GameTranDef AccountInventoryBoardGachaParticipationInfoPerPcTran::_def;
::GameTranDef AccountInventoryBoardGachaDrawByItemTran::_def;
::GameTranDef AccountInventoryBoardGachaDrawByInstantPaymentTran::_def;
::GameTranDef AccountInventoryBoardGachaParticipationRewardStateTran::_def;
::GameTranDef AccountInventoryBoardGachaTakeParticipationRewardTran::_def;
