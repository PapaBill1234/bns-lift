// accountinventorychannel_cpp.cpp: accountinventorychannel.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "accountinventorychannel_gd.h"
#include "LiftStub.h"

// 0x29390
bool __cdecl AccountInventorySessionHandler::OnAccept(::Session const *) const
{
    LIFT_STUB(0x29390);
}

// 0x293d0
bool __cdecl AccountInventorySessionHandler::OnConnect(::Session const *, bool) const
{
    LIFT_STUB(0x293d0);
}

// 0x29600
void __cdecl AccountInventorySessionHandler::OnClose(::Session const *, bool) const
{
    LIFT_STUB(0x29600);
}

// 0x297e0
bool __cdecl AccountInventorySessionHandler::PacketHandler(::Session const *, ::Packet const *) const
{
    LIFT_STUB(0x297e0);
}

// 0x29840
short __cdecl AccountInventoryChannelManager::translateErrorReasonToGame(short)
{
    LIFT_STUB(0x29840);
}

// 0x29a30
void __cdecl AccountInventoryChannel::Initialize(short)
{
    LIFT_STUB(0x29a30);
}

// 0x29b60
bool __cdecl AccountInventoryChannel::SendHello(void)
{
    LIFT_STUB(0x29b60);
}

// 0x29cf0
bool __cdecl HandleAccountInventoryGame_HelloOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x29cf0);
}

// 0x29e50
bool __cdecl HandleAccountInventoryGame_HelloFail(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x29e50);
}

// 0x29f50
bool __cdecl HandleAccountInventoryGame_GetGoodsCountOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x29f50);
}

// 0x2a0e0
bool __cdecl HandleAccountInventoryGame_GetGoodsCountFail(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x2a0e0);
}

// 0x2a270
bool __cdecl HandleAccountInventoryGame_ListGoodsOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x2a270);
}

// 0x2a560
bool __cdecl HandleAccountInventoryGame_ListGoodsFail(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x2a560);
}

// 0x2a6f0
bool __cdecl HandleAccountInventoryGame_TakeGoodsOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x2a6f0);
}

// 0x2a9e0
bool __cdecl HandleAccountInventoryGame_TakeGoodsFail(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x2a9e0);
}

// 0x2ab70
bool __cdecl HandleAccountInventoryGame_RetrieveWarehouseLobbyServiceItemListOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x2ab70);
}

// 0x2ae60
bool __cdecl HandleAccountInventoryGame_RetrieveWarehouseLobbyServiceItemListFail(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x2ae60);
}

// 0x2aff0
bool __cdecl HandleAccountInventoryGame_RetrieveWarehouseItemListOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x2aff0);
}

// 0x2b2e0
bool __cdecl HandleAccountInventoryGame_RetrieveWarehouseItemListFail(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x2b2e0);
}

// 0x2b470
bool __cdecl HandleAccountInventoryGame_RetrieveUncompletedItemAcquisitionListOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x2b470);
}

// 0x2b760
bool __cdecl HandleAccountInventoryGame_RetrieveUncompletedItemAcquisitionListFail(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x2b760);
}

// 0x2b8f0
bool __cdecl HandleAccountInventoryGame_TryWarehouseItemAcquisitionOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x2b8f0);
}

// 0x2bad0
bool __cdecl HandleAccountInventoryGame_TryWarehouseItemAcquisitionFail(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x2bad0);
}

// 0x2bc60
bool __cdecl HandleAccountInventoryGame_FinishWarehouseItemAcquisitionOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x2bc60);
}

// 0x2be50
bool __cdecl HandleAccountInventoryGame_FinishWarehouseItemAcquisitionFail(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x2be50);
}

// 0x2bf00
bool __cdecl HandleAccountInventoryGame_FinishMultipleWarehouseItemAcquisitionOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x2bf00);
}

// 0x2c1e0
bool __cdecl HandleAccountInventoryGame_FinishMultipleWarehouseItemAcquisitionFail(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x2c1e0);
}

// 0x2c360
bool __cdecl HandleAccountInventoryGame_RetrieveSingleWarehouseItemOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x2c360);
}

// 0x2c590
bool __cdecl HandleAccountInventoryGame_RetrieveSingleWarehouseItemFail(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x2c590);
}

// 0x2c730
bool __cdecl HandleAccountInventoryGame_TryWarehouseItemConsumptionOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x2c730);
}

// 0x2c860
bool __cdecl HandleAccountInventoryGame_TryWarehouseItemConsumptionFail(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x2c860);
}

// 0x2ca80
bool __cdecl HandleAccountInventoryGame_FinishWarehouseItemConsumptionOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x2ca80);
}

// 0x2cb90
bool __cdecl HandleAccountInventoryGame_FinishWarehouseItemConsumptionFail(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x2cb90);
}

// 0x2cdb0
bool __cdecl HandleAccountInventoryGame_TryInstantPaymentOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x2cdb0);
}

// 0x2d410
bool __cdecl HandleAccountInventoryGame_TryInstantPaymentFail(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x2d410);
}

// 0x2d5a0
bool __cdecl HandleAccountInventoryGame_FinishInstantPaymentOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x2d5a0);
}

// 0x2d8d0
bool __cdecl HandleAccountInventoryGame_FinishInstantPaymentFail(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x2d8d0);
}

// 0x2da60
bool __cdecl HandleAccountInventoryGame_RefundInstantPaymentOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x2da60);
}

// 0x2dae0
bool __cdecl HandleAccountInventoryGame_RefundInstantPaymentFail(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x2dae0);
}

// 0x2db50
bool __cdecl HandleAccountInventoryGame_BoardGachaRetrieveSeasonScheduleFail(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x2db50);
}

// 0x2dba0
bool __cdecl HandleAccountInventoryGame_BoardGachaSeasonScheduleNotify(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x2dba0);
}

// 0x2de50
bool __cdecl HandleAccountInventoryGame_BoardGachaEndNotify(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x2de50);
}

// 0x2dfb0
bool __cdecl HandleAccountInventoryGame_BoardGachaBoardStartNotify(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x2dfb0);
}

// 0x2e240
bool __cdecl HandleAccountInventoryGame_BoardGachaBoardEndNotify(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x2e240);
}

// 0x2e4f0
bool __cdecl HandleAccountInventoryGame_BoardGachaBoardParticipationInfoNotify(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x2e4f0);
}

// 0x2e7a0
bool __cdecl HandleAccountInventoryGame_BoardGachaResultNotify(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x2e7a0);
}

// 0x2f4e0
bool __cdecl HandleAccountInventoryGame_BoardGachaRetrieveParticipationCountPerSeasonOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x2f4e0);
}

// 0x2f6a0
bool __cdecl HandleAccountInventoryGame_BoardGachaRetrieveParticipationCountPerSeasonFail(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x2f6a0);
}

// 0x2f860
bool __cdecl HandleAccountInventoryGame_BoardGachaRetrieveBoardParticipationInfoPerPcOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x2f860);
}

// 0x2fc90
bool __cdecl HandleAccountInventoryGame_BoardGachaRetrieveBoardParticipationInfoPerPcFail(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x2fc90);
}

// 0x2fe40
bool __cdecl HandleAccountInventoryGame_BoardGachaTryDrawByItemOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x2fe40);
}

// 0x30020
bool __cdecl HandleAccountInventoryGame_BoardGachaTryDrawByItemFail(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x30020);
}

// 0x301b0
bool __cdecl HandleAccountInventoryGame_BoardGachaFinishDrawByItemOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x301b0);
}

// 0x30400
bool __cdecl HandleAccountInventoryGame_BoardGachaFinishDrawByItemFail(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x30400);
}

// 0x30590
bool __cdecl HandleAccountInventoryGame_BoardGachaFinishDrawByItemRecoveryOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x30590);
}

// 0x30a40
bool __cdecl HandleAccountInventoryGame_BoardGachaFinishDrawByItemRecoveryFail(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x30a40);
}

// 0x30ac0
bool __cdecl HandleAccountInventoryGame_BoardGachaCancelDrawByItemOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x30ac0);
}

// 0x30b30
bool __cdecl HandleAccountInventoryGame_BoardGachaCancelDrawByItemFail(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x30b30);
}

// 0x30ba0
bool __cdecl HandleAccountInventoryGame_BoardGachaDrawByInstantPaymentOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x30ba0);
}

// 0x30de0
bool __cdecl HandleAccountInventoryGame_BoardGachaDrawByInstantPaymentFail(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x30de0);
}

// 0x30fa0
bool __cdecl HandleAccountInventoryGame_BoardGachaRetrieveParticipationRewardStateOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x30fa0);
}

// 0x312c0
bool __cdecl HandleAccountInventoryGame_BoardGachaRetrieveParticipationRewardStateFail(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x312c0);
}

// 0x31480
bool __cdecl HandleAccountInventoryGame_BoardGachaTakeParticipationRewardOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x31480);
}

// 0x31690
bool __cdecl HandleAccountInventoryGame_BoardGachaTakeParticipationRewardFail(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x31690);
}

// 0x31850
bool __cdecl HandleAccountInventoryGame_DeliverSystemPostNotify(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x31850);
}

// 0x31d30
bool __cdecl AccountInventoryChannelManager::Initialize(short, short *const)
{
    LIFT_STUB(0x31d30);
}

// 0x320f0
void __cdecl AccountInventoryChannelManager::Destroy(void)
{
    LIFT_STUB(0x320f0);
}

// 0x32260
::AccountInventoryChannel * __cdecl AccountInventoryChannelManager::acquire(unsigned int)
{
    LIFT_STUB(0x32260);
}

// 0x32330
bool __cdecl AccountInventoryChannelManager::Send(short, char const *, ...)
{
    LIFT_STUB(0x32330);
}

// 0x32450
bool __cdecl AccountInventoryChannelManager::Send(short, ::Packet const *)
{
    LIFT_STUB(0x32450);
}

// 0x325a0
bool __cdecl AccountInventoryChannelManager::SendFinishWarehouseItemAcquisitionReq(short, unsigned __int64, __int64, __int64, ::id128 const &, __int64, char)
{
    LIFT_STUB(0x325a0);
}

// 0x32610
bool __cdecl AccountInventoryChannelManager::SendTryInstantPaymentReq(short, unsigned __int64, ::id128 const &, short, __int64, wchar_t const *, int, char const *, short, short, ::InstantPaymentGoodsInfoParam::GoodsInfo *const)
{
    LIFT_STUB(0x32610);
}

// 0x328b0
bool __cdecl AccountInventoryChannelManager::SendFinishInstantPaymentReq(short, unsigned __int64, ::id128 const &, __int64, __int64, bool)
{
    LIFT_STUB(0x328b0);
}

// 0x32ac0
bool __cdecl AccountInventoryChannelManager::SendBoardGachaDrawByInstantPaymentReq(short, unsigned __int64, ::id128 const &, __int64, wchar_t const *, __int64, short, int, ::InstantPaymentGoodsInfoParam &)
{
    LIFT_STUB(0x32ac0);
}
