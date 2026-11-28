// accountinventorychannel_cpp.cpp: accountinventorychannel.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "accountinventorychannel_gd.h"
#include "LiftStub.h"
#include "AlertSender.h"
#include "Log.h"

// LIFT: per-exe path literal (lessons A6).
#define ACCOUNTINVENTORYCHANNEL_FILE L"e:\\dailybuild02\\gamedaemon-common-0.0.348\\depot\\branch\\348nc\\program\\server\\gamedaemon\\AccountInventoryChannel.cpp"

// 0x29390
#pragma comment(linker, "/INCLUDE:?OnAccept@AccountInventorySessionHandler@@UEBA_NPEBVSession@@@Z")  // LIFT: dead-strip keep (no live caller yet)
bool __cdecl AccountInventorySessionHandler::OnAccept(::Session const *) const
{
    Log::Write(Log::LT_ERROR, ACCOUNTINVENTORYCHANNEL_FILE, 35,
               L"== CRASH == [game-accountI], cannot accept from accountI (game connect to accountI)");
    AlertSender::Write(ACCOUNTINVENTORYCHANNEL_FILE, 35,
                       L"== CRASH == [game-accountI], cannot accept from accountI (game connect to accountI)");
    return false;
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
#pragma comment(linker, "/INCLUDE:?HandleAccountInventoryGame_RefundInstantPaymentOk@@YA_NPEBVSession@@PEBVPacket@@@Z")  // LIFT: dead-strip keep (no live caller yet)
bool __cdecl HandleAccountInventoryGame_RefundInstantPaymentOk(::Session const *, ::Packet const *packet)
{
    short c;
    __int64 gameTid;
    __int64 purchaseId;
    __int64 refundReceptionId;
    packet->Decompose("hqqq", &c, &gameTid, &purchaseId, &refundReceptionId);
    Log::Write(Log::LT_DEBUG, ACCOUNTINVENTORYCHANNEL_FILE, 1236,
               L"[game-accountI] HandleAccountInventoryGame_RefundInstantPaymentOk, tid:%#I64x, purchaseId:%I64d, refundReceptionId:%I64d",
               gameTid, purchaseId, refundReceptionId);
    return true;
}

// 0x2dae0
#pragma comment(linker, "/INCLUDE:?HandleAccountInventoryGame_RefundInstantPaymentFail@@YA_NPEBVSession@@PEBVPacket@@@Z")  // LIFT: dead-strip keep (no live caller yet)
bool __cdecl HandleAccountInventoryGame_RefundInstantPaymentFail(::Session const *, ::Packet const *packet)
{
    short c;
    __int64 gameTid;
    short errorReason;
    packet->Decompose("hqE", &c, &gameTid, &errorReason);
    Log::Write(Log::LT_DEBUG, ACCOUNTINVENTORYCHANNEL_FILE, 1247,
               L"[game-accountI] HandleAccountInventoryGame_RefundInstantPaymentFail, tid:%#I64x, errorCode:%d",
               gameTid, static_cast<int>(errorReason));
    return true;
}

// 0x2db50
#pragma comment(linker, "/INCLUDE:?HandleAccountInventoryGame_BoardGachaRetrieveSeasonScheduleFail@@YA_NPEBVSession@@PEBVPacket@@@Z")  // LIFT: dead-strip keep (no live caller yet)
bool __cdecl HandleAccountInventoryGame_BoardGachaRetrieveSeasonScheduleFail(::Session const *, ::Packet const *packet)
{
    short c;
    short errorReason;
    packet->Decompose("hE", &c, &errorReason);
    Log::Write(Log::LT_DEBUG, ACCOUNTINVENTORYCHANNEL_FILE, 1258,
               L"[game-accountI] HandleAccountInventoryGame_BoardGachaRetrieveSeasonScheduleFail, errorCode:%d",
               static_cast<int>(errorReason));
    return true;
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
#pragma comment(linker, "/INCLUDE:?HandleAccountInventoryGame_BoardGachaFinishDrawByItemRecoveryFail@@YA_NPEBVSession@@PEBVPacket@@@Z")  // LIFT: dead-strip keep (no live caller yet)
bool __cdecl HandleAccountInventoryGame_BoardGachaFinishDrawByItemRecoveryFail(::Session const *, ::Packet const *packet)
{
    short c;
    __int64 gameTid;
    __int64 pcdbid;
    short errorReason;
    // BUG: the format "hqE" has no field for pcdbid. Decompose writes errorReason into pcdbid, and the log shows stack values.
    packet->Decompose("hqE", &c, &gameTid, &pcdbid, &errorReason);
    Log::Write(Log::LT_DEBUG, ACCOUNTINVENTORYCHANNEL_FILE, 2026,
               L"[game-accountI] #BoardGachaFinishDrawByItemRecoveryFail, tid:%#I64x, pcdbid:%#I64x, errorCode:%d",
               gameTid, pcdbid, static_cast<int>(errorReason));
    return true;
}

// 0x30ac0
#pragma comment(linker, "/INCLUDE:?HandleAccountInventoryGame_BoardGachaCancelDrawByItemOk@@YA_NPEBVSession@@PEBVPacket@@@Z")  // LIFT: dead-strip keep (no live caller yet)
bool __cdecl HandleAccountInventoryGame_BoardGachaCancelDrawByItemOk(::Session const *, ::Packet const *packet)
{
    short c;
    __int64 gameTid;
    __int64 pcdbid;
    packet->Decompose("hqq", &c, &gameTid, &pcdbid);
    Log::Write(Log::LT_DEBUG, ACCOUNTINVENTORYCHANNEL_FILE, 2041,
               L"[game-accountI] #BoardGachaCancelDrawByItemOk, tid:%#I64x, pcdbid:%#I64x",
               gameTid, pcdbid);
    return true;
}

// 0x30b30
#pragma comment(linker, "/INCLUDE:?HandleAccountInventoryGame_BoardGachaCancelDrawByItemFail@@YA_NPEBVSession@@PEBVPacket@@@Z")  // LIFT: dead-strip keep (no live caller yet)
bool __cdecl HandleAccountInventoryGame_BoardGachaCancelDrawByItemFail(::Session const *, ::Packet const *packet)
{
    short c;
    __int64 gameTid;
    __int64 pcdbid;
    short errorReason;
    packet->Decompose("hqqE", &c, &gameTid, &pcdbid, &errorReason);
    Log::Write(Log::LT_DEBUG, ACCOUNTINVENTORYCHANNEL_FILE, 2055,
               L"[game-accountI] #BoardGachaCancelDrawByItemFail, tid:%#I64x, errorCode:%d",
               gameTid, static_cast<int>(errorReason));
    return true;
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
