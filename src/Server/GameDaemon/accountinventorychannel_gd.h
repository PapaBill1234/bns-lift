// accountinventorychannel_gd.h: accountinventorychannel.cpp, accountinventorychannel.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"
#include "../BloodLib/include/Lock.h"

class AccountInventoryChannel
{
public:
    void __cdecl Initialize(short);  // 0x29a30
    bool __cdecl SendHello(void);  // 0x29b60
    virtual unsigned __int64 __cdecl GetId(void);  // 0x180c10
};

class AccountInventoryChannelManager
{
public:
    static short __cdecl translateErrorReasonToGame(short);  // 0x29840
    bool __cdecl Initialize(short, short *const);  // 0x31d30
    void __cdecl Destroy(void);  // 0x320f0
private:
    ::AccountInventoryChannel * __cdecl acquire(unsigned int);  // 0x32260
public:
    bool __cdecl Send(short, char const *, ...);  // 0x32330
    bool __cdecl Send(short, ::Packet const *);  // 0x32450
    bool __cdecl SendFinishWarehouseItemAcquisitionReq(short, unsigned __int64, __int64, __int64, ::id128 const &, __int64, char);  // 0x325a0
    bool __cdecl SendTryInstantPaymentReq(short, unsigned __int64, ::id128 const &, short, __int64, wchar_t const *, int, char const *, short, short, ::InstantPaymentGoodsInfoParam::GoodsInfo *const);  // 0x32610
    bool __cdecl SendFinishInstantPaymentReq(short, unsigned __int64, ::id128 const &, __int64, __int64, bool);  // 0x328b0
    bool __cdecl SendBoardGachaDrawByInstantPaymentReq(short, unsigned __int64, ::id128 const &, __int64, wchar_t const *, __int64, short, int, ::InstantPaymentGoodsInfoParam &);  // 0x32ac0
    __cdecl ~AccountInventoryChannelManager(void);  // 0x18d060

    // PDB layout (GameDaemon), size 0x98.
private:
    CriticalSection _lock;
    short _worldIdCount;
    short _worldIds[50];
    ::AccountInventoryChannel** _channels;
};
static_assert(sizeof(AccountInventoryChannelManager) == 0x98, "sizeof AccountInventoryChannelManager");

class AccountInventorySessionHandler
{
public:
    virtual bool __cdecl OnAccept(::Session const *) const;  // 0x29390
    virtual bool __cdecl OnConnect(::Session const *, bool) const;  // 0x293d0
    virtual void __cdecl OnClose(::Session const *, bool) const;  // 0x29600
    virtual bool __cdecl PacketHandler(::Session const *, ::Packet const *) const;  // 0x297e0
};

bool __cdecl HandleAccountInventoryGame_HelloOk(::Session const *, ::Packet const *);  // 0x29cf0
bool __cdecl HandleAccountInventoryGame_HelloFail(::Session const *, ::Packet const *);  // 0x29e50
bool __cdecl HandleAccountInventoryGame_GetGoodsCountOk(::Session const *, ::Packet const *);  // 0x29f50
bool __cdecl HandleAccountInventoryGame_GetGoodsCountFail(::Session const *, ::Packet const *);  // 0x2a0e0
bool __cdecl HandleAccountInventoryGame_ListGoodsOk(::Session const *, ::Packet const *);  // 0x2a270
bool __cdecl HandleAccountInventoryGame_ListGoodsFail(::Session const *, ::Packet const *);  // 0x2a560
bool __cdecl HandleAccountInventoryGame_TakeGoodsOk(::Session const *, ::Packet const *);  // 0x2a6f0
bool __cdecl HandleAccountInventoryGame_TakeGoodsFail(::Session const *, ::Packet const *);  // 0x2a9e0
bool __cdecl HandleAccountInventoryGame_RetrieveWarehouseLobbyServiceItemListOk(::Session const *, ::Packet const *);  // 0x2ab70
bool __cdecl HandleAccountInventoryGame_RetrieveWarehouseLobbyServiceItemListFail(::Session const *, ::Packet const *);  // 0x2ae60
bool __cdecl HandleAccountInventoryGame_RetrieveWarehouseItemListOk(::Session const *, ::Packet const *);  // 0x2aff0
bool __cdecl HandleAccountInventoryGame_RetrieveWarehouseItemListFail(::Session const *, ::Packet const *);  // 0x2b2e0
bool __cdecl HandleAccountInventoryGame_RetrieveUncompletedItemAcquisitionListOk(::Session const *, ::Packet const *);  // 0x2b470
bool __cdecl HandleAccountInventoryGame_RetrieveUncompletedItemAcquisitionListFail(::Session const *, ::Packet const *);  // 0x2b760
bool __cdecl HandleAccountInventoryGame_TryWarehouseItemAcquisitionOk(::Session const *, ::Packet const *);  // 0x2b8f0
bool __cdecl HandleAccountInventoryGame_TryWarehouseItemAcquisitionFail(::Session const *, ::Packet const *);  // 0x2bad0
bool __cdecl HandleAccountInventoryGame_FinishWarehouseItemAcquisitionOk(::Session const *, ::Packet const *);  // 0x2bc60
bool __cdecl HandleAccountInventoryGame_FinishWarehouseItemAcquisitionFail(::Session const *, ::Packet const *);  // 0x2be50
bool __cdecl HandleAccountInventoryGame_FinishMultipleWarehouseItemAcquisitionOk(::Session const *, ::Packet const *);  // 0x2bf00
bool __cdecl HandleAccountInventoryGame_FinishMultipleWarehouseItemAcquisitionFail(::Session const *, ::Packet const *);  // 0x2c1e0
bool __cdecl HandleAccountInventoryGame_RetrieveSingleWarehouseItemOk(::Session const *, ::Packet const *);  // 0x2c360
bool __cdecl HandleAccountInventoryGame_RetrieveSingleWarehouseItemFail(::Session const *, ::Packet const *);  // 0x2c590
bool __cdecl HandleAccountInventoryGame_TryWarehouseItemConsumptionOk(::Session const *, ::Packet const *);  // 0x2c730
bool __cdecl HandleAccountInventoryGame_TryWarehouseItemConsumptionFail(::Session const *, ::Packet const *);  // 0x2c860
bool __cdecl HandleAccountInventoryGame_FinishWarehouseItemConsumptionOk(::Session const *, ::Packet const *);  // 0x2ca80
bool __cdecl HandleAccountInventoryGame_FinishWarehouseItemConsumptionFail(::Session const *, ::Packet const *);  // 0x2cb90
bool __cdecl HandleAccountInventoryGame_TryInstantPaymentOk(::Session const *, ::Packet const *);  // 0x2cdb0
bool __cdecl HandleAccountInventoryGame_TryInstantPaymentFail(::Session const *, ::Packet const *);  // 0x2d410
bool __cdecl HandleAccountInventoryGame_FinishInstantPaymentOk(::Session const *, ::Packet const *);  // 0x2d5a0
bool __cdecl HandleAccountInventoryGame_FinishInstantPaymentFail(::Session const *, ::Packet const *);  // 0x2d8d0
bool __cdecl HandleAccountInventoryGame_RefundInstantPaymentOk(::Session const *, ::Packet const *);  // 0x2da60
bool __cdecl HandleAccountInventoryGame_RefundInstantPaymentFail(::Session const *, ::Packet const *);  // 0x2dae0
bool __cdecl HandleAccountInventoryGame_BoardGachaRetrieveSeasonScheduleFail(::Session const *, ::Packet const *);  // 0x2db50
bool __cdecl HandleAccountInventoryGame_BoardGachaSeasonScheduleNotify(::Session const *, ::Packet const *);  // 0x2dba0
bool __cdecl HandleAccountInventoryGame_BoardGachaEndNotify(::Session const *, ::Packet const *);  // 0x2de50
bool __cdecl HandleAccountInventoryGame_BoardGachaBoardStartNotify(::Session const *, ::Packet const *);  // 0x2dfb0
bool __cdecl HandleAccountInventoryGame_BoardGachaBoardEndNotify(::Session const *, ::Packet const *);  // 0x2e240
bool __cdecl HandleAccountInventoryGame_BoardGachaBoardParticipationInfoNotify(::Session const *, ::Packet const *);  // 0x2e4f0
bool __cdecl HandleAccountInventoryGame_BoardGachaResultNotify(::Session const *, ::Packet const *);  // 0x2e7a0
bool __cdecl HandleAccountInventoryGame_BoardGachaRetrieveParticipationCountPerSeasonOk(::Session const *, ::Packet const *);  // 0x2f4e0
bool __cdecl HandleAccountInventoryGame_BoardGachaRetrieveParticipationCountPerSeasonFail(::Session const *, ::Packet const *);  // 0x2f6a0
bool __cdecl HandleAccountInventoryGame_BoardGachaRetrieveBoardParticipationInfoPerPcOk(::Session const *, ::Packet const *);  // 0x2f860
bool __cdecl HandleAccountInventoryGame_BoardGachaRetrieveBoardParticipationInfoPerPcFail(::Session const *, ::Packet const *);  // 0x2fc90
bool __cdecl HandleAccountInventoryGame_BoardGachaTryDrawByItemOk(::Session const *, ::Packet const *);  // 0x2fe40
bool __cdecl HandleAccountInventoryGame_BoardGachaTryDrawByItemFail(::Session const *, ::Packet const *);  // 0x30020
bool __cdecl HandleAccountInventoryGame_BoardGachaFinishDrawByItemOk(::Session const *, ::Packet const *);  // 0x301b0
bool __cdecl HandleAccountInventoryGame_BoardGachaFinishDrawByItemFail(::Session const *, ::Packet const *);  // 0x30400
bool __cdecl HandleAccountInventoryGame_BoardGachaFinishDrawByItemRecoveryOk(::Session const *, ::Packet const *);  // 0x30590
bool __cdecl HandleAccountInventoryGame_BoardGachaFinishDrawByItemRecoveryFail(::Session const *, ::Packet const *);  // 0x30a40
bool __cdecl HandleAccountInventoryGame_BoardGachaCancelDrawByItemOk(::Session const *, ::Packet const *);  // 0x30ac0
bool __cdecl HandleAccountInventoryGame_BoardGachaCancelDrawByItemFail(::Session const *, ::Packet const *);  // 0x30b30
bool __cdecl HandleAccountInventoryGame_BoardGachaDrawByInstantPaymentOk(::Session const *, ::Packet const *);  // 0x30ba0
bool __cdecl HandleAccountInventoryGame_BoardGachaDrawByInstantPaymentFail(::Session const *, ::Packet const *);  // 0x30de0
bool __cdecl HandleAccountInventoryGame_BoardGachaRetrieveParticipationRewardStateOk(::Session const *, ::Packet const *);  // 0x30fa0
bool __cdecl HandleAccountInventoryGame_BoardGachaRetrieveParticipationRewardStateFail(::Session const *, ::Packet const *);  // 0x312c0
bool __cdecl HandleAccountInventoryGame_BoardGachaTakeParticipationRewardOk(::Session const *, ::Packet const *);  // 0x31480
bool __cdecl HandleAccountInventoryGame_BoardGachaTakeParticipationRewardFail(::Session const *, ::Packet const *);  // 0x31690
bool __cdecl HandleAccountInventoryGame_DeliverSystemPostNotify(::Session const *, ::Packet const *);  // 0x31850
