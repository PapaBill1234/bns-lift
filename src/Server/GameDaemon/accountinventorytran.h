// accountinventorytran.h: accountinventorytran.cpp, accountinventorytran.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class AccountInventoryBoardGachaDrawByInstantPaymentTran
{
public:
    virtual ::GameTranDef const * __cdecl GetDefinition(void) const;  // 0x1c3150
    static ::GameTranDef _def;
private:
    virtual bool __cdecl work(int, void *);  // 0x1cede0
    bool __cdecl init(int, void *);  // 0x1cee80
    bool __cdecl tryReq(void);  // 0x1cefb0
    bool __cdecl recvOk(void *);  // 0x1cf170
    bool __cdecl recvFail(short);  // 0x1cf350
    void __cdecl failProcess(short);  // 0x1cf3d0
};

class AccountInventoryBoardGachaDrawByItemTran
{
public:
    virtual ::GameTranDef const * __cdecl GetDefinition(void) const;  // 0x1c3140
    static ::GameTranDef _def;
    __cdecl AccountInventoryBoardGachaDrawByItemTran(::User *);  // 0x1cc240
    virtual __cdecl ~AccountInventoryBoardGachaDrawByItemTran(void);  // 0x1cc340
private:
    virtual bool __cdecl work(int, void *);  // 0x1cc3b0
    bool __cdecl init(int, void *);  // 0x1cc580
    bool __cdecl checkCostItemValidation(void);  // 0x1cc850
    bool __cdecl checkCondition(void *);  // 0x1ccce0
    bool __cdecl tryDrawTicketReq(void);  // 0x1cd0f0
    bool __cdecl tryDrawTicketOk(void *);  // 0x1cd260
    bool __cdecl tryConsumeItemReq(void);  // 0x1cd660
    bool __cdecl tryConsumeItemOk(void *);  // 0x1cd870
    bool __cdecl tryConsumeItemFail(short);  // 0x1cdbd0
    bool __cdecl finishDrawTicketReq(void);  // 0x1cdd30
    bool __cdecl finishDrawTicketOk(void *);  // 0x1cdeb0
    bool __cdecl abort(void *);  // 0x1ce0e0
    bool __cdecl recvFailFromAccountInventory(short);  // 0x1ce1f0
    bool __cdecl expire(short);  // 0x1ce360
    void __cdecl failProcess(short);  // 0x1ce460
    void __cdecl finProcess(void);  // 0x1ce660
    void __cdecl writeGameLogBoardGachaJoinItemItem(::Pc *, unsigned __int64);  // 0x1ce8e0
public:
    static void __cdecl WriteGameLogBoardGachaJoin(::Pc *, unsigned __int64, __int64, ::BoardGachaDrawByItemFinishDrawOkParam *);  // 0x1ceb00
};

class AccountInventoryBoardGachaParticipationCountPerSeasonTran
{
public:
    virtual ::GameTranDef const * __cdecl GetDefinition(void) const;  // 0x1c3120
    static ::GameTranDef _def;
private:
    virtual bool __cdecl work(int, void *);  // 0x1cb6f0
    bool __cdecl init(int, void *);  // 0x1cb790
    bool __cdecl tryGetInfo(void);  // 0x1cb850
    bool __cdecl getInfoOk(void *);  // 0x1cb910
    bool __cdecl getInfoFail(short);  // 0x1cba30
    void __cdecl failProcess(short);  // 0x1cbab0
};

class AccountInventoryBoardGachaParticipationInfoPerPcTran
{
public:
    virtual ::GameTranDef const * __cdecl GetDefinition(void) const;  // 0x1c3130
    static ::GameTranDef _def;
private:
    virtual bool __cdecl work(int, void *);  // 0x1cbc00
    bool __cdecl init(int, void *);  // 0x1cbca0
    bool __cdecl tryGetInfo(void);  // 0x1cbd60
    bool __cdecl getInfoOk(void *);  // 0x1cbe20
    bool __cdecl getInfoFail(short);  // 0x1cc0d0
    void __cdecl failProcess(short);  // 0x1cc150
};

class AccountInventoryBoardGachaParticipationRewardStateTran
{
public:
    virtual ::GameTranDef const * __cdecl GetDefinition(void) const;  // 0x1c3160
    static ::GameTranDef _def;
private:
    virtual bool __cdecl work(int, void *);  // 0x1cf540
    bool __cdecl init(int, void *);  // 0x1cf5e0
    bool __cdecl tryGetInfo(void);  // 0x1cf6a0
    bool __cdecl getInfoOk(void *);  // 0x1cf760
    bool __cdecl getInfoFail(short);  // 0x1cfb50
    void __cdecl failProcess(short);  // 0x1cfbd0
};

class AccountInventoryBoardGachaTakeParticipationRewardTran
{
public:
    virtual ::GameTranDef const * __cdecl GetDefinition(void) const;  // 0x1c3170
    static ::GameTranDef _def;
private:
    virtual bool __cdecl work(int, void *);  // 0x1cfd40
    bool __cdecl init(int, void *);  // 0x1cfde0
    bool __cdecl tryReq(void);  // 0x1cfec0
    bool __cdecl recvOk(void *);  // 0x1cff90
    bool __cdecl recvFail(short);  // 0x1d00f0
    void __cdecl failProcess(short);  // 0x1d0170
    void __cdecl writeGameLogReceiveBoardGachaReward(::Pc *, unsigned __int64, ::BoardGachaTakeParticipationRewardOkParam *);  // 0x1d0280
};

class AccountInventoryGetGoodsCountTran
{
public:
    virtual ::GameTranDef const * __cdecl GetDefinition(void) const;  // 0x1c30b0
    static ::GameTranDef _def;
private:
    virtual bool __cdecl work(int, void *);  // 0x1c31e0
    bool __cdecl init(int, void *);  // 0x1c3270
    bool __cdecl tryGetGoodsCount(void);  // 0x1c3330
    bool __cdecl getGoodsCountOk(void *);  // 0x1c3450
    bool __cdecl getGoodsCountFail(short);  // 0x1c3520
    bool __cdecl getGoodsCountExpire(void);  // 0x1c35f0
};

class AccountInventoryJumpingCharacter2TicketTran
{
public:
    virtual ::GameTranDef const * __cdecl GetDefinition(void) const;  // 0x1c3110
    static ::GameTranDef _def;
    __cdecl AccountInventoryJumpingCharacter2TicketTran(::User *);  // 0x1c83c0
    virtual __cdecl ~AccountInventoryJumpingCharacter2TicketTran(void);  // 0x1c8480
private:
    virtual bool __cdecl work(int, void *);  // 0x1c8520
    bool __cdecl init(int, void *);  // 0x1c8800
    bool __cdecl checkItemConsumptionReq(void);  // 0x1c8c90
    bool __cdecl checkItemConsumptionOk(void *);  // 0x1c8df0
    bool __cdecl checkCondition(void *);  // 0x1c9250
    bool __cdecl tryItemConsumptionReq(void);  // 0x1c9840
    bool __cdecl tryItemConsumptionOk(void *);  // 0x1c99c0
    bool __cdecl tryTakeRewardReq(void);  // 0x1c9cd0
    bool __cdecl tryTakeRewardOk(void *);  // 0x1c9e90
    bool __cdecl updateJumpingCharacterStateReq(void *);  // 0x1ca220
    bool __cdecl updateJumpingCharacterStateOk(void *);  // 0x1ca400
    bool __cdecl finishItemConsumptionReq(void);  // 0x1ca740
    bool __cdecl finishItemConsumptionOk(void *);  // 0x1ca8b0
    bool __cdecl finishTakeRewardOk(void *);  // 0x1caac0
    bool __cdecl abort(void *);  // 0x1caeb0
    bool __cdecl recvFail(short, short);  // 0x1cafd0
    bool __cdecl expire(short);  // 0x1cb140
    void __cdecl failProcess(short, __int64);  // 0x1cb240
    void __cdecl finProcess(void);  // 0x1cb450
};

class AccountInventoryListGoodsTran
{
public:
    virtual ::GameTranDef const * __cdecl GetDefinition(void) const;  // 0x1c30c0
    static ::GameTranDef _def;
private:
    virtual bool __cdecl work(int, void *);  // 0x1c36d0
    bool __cdecl init(int, void *);  // 0x1c3760
    bool __cdecl tryListGoods(void);  // 0x1c3830
    bool __cdecl listGoodsOk(void *);  // 0x1c3940
    bool __cdecl listGoodsFail(short);  // 0x1c4100
    bool __cdecl listGoodsExpire(void);  // 0x1c41d0
};

class AccountInventoryRetrieveWarehouseItemListTran
{
public:
    virtual ::GameTranDef const * __cdecl GetDefinition(void) const;  // 0x1c30f0
    static ::GameTranDef _def;
private:
    virtual bool __cdecl work(int, void *);  // 0x1c5920
    bool __cdecl init(int, void *);  // 0x1c59b0
    bool __cdecl tryRetrieveWarehouseItemList(void);  // 0x1c5aa0
    bool __cdecl retrieveWarehouseItemListOk(void *);  // 0x1c5be0
    bool __cdecl retrieveWarehouseItemListFail(short);  // 0x1c6610
    bool __cdecl retrieveWarehouseItemListExpire(void);  // 0x1c66f0
};

class AccountInventoryRetrieveWarehouseLobbyServiceItemListTran
{
public:
    virtual ::GameTranDef const * __cdecl GetDefinition(void) const;  // 0x1c30e0
    static ::GameTranDef _def;
private:
    virtual bool __cdecl work(int, void *);  // 0x1c5070
    bool __cdecl init(int, void *);  // 0x1c5100
    bool __cdecl tryRetrieveWarehouseLobbyServiceItemList(void);  // 0x1c51f0
    bool __cdecl retrieveWarehouseLobbyServiceItemListOk(void *);  // 0x1c5320
    bool __cdecl retrieveWarehouseLobbyServiceItemListFail(short);  // 0x1c5750
    bool __cdecl retrieveWarehouseLobbyServiceItemListExpire(void);  // 0x1c5830
};

class AccountInventoryTakeGoodsTran
{
public:
    virtual ::GameTranDef const * __cdecl GetDefinition(void) const;  // 0x1c30d0
    static ::GameTranDef _def;
private:
    virtual bool __cdecl work(int, void *);  // 0x1c42b0
    bool __cdecl init(int, void *);  // 0x1c4340
    bool __cdecl tryTakeGoods(void);  // 0x1c4420
    bool __cdecl takeGoodsOk(void *);  // 0x1c4540
    bool __cdecl takeGoodsFail(short);  // 0x1c4e90
    bool __cdecl takeGoodsExpire(void);  // 0x1c4f80
};

class AccountInventoryTakeWarehouseItemTran
{
public:
    virtual ::GameTranDef const * __cdecl GetDefinition(void) const;  // 0x1c3100
    static ::GameTranDef _def;
private:
    virtual bool __cdecl work(int, void *);  // 0x1c67e0
    bool __cdecl init(int, void *);  // 0x1c68c0
    bool __cdecl tryItemAcquisitionReq(void *);  // 0x1c69f0
    bool __cdecl tryItemAcquisitionOk(void *);  // 0x1c6f30
    bool __cdecl tryItemAcquisitionFail(short);  // 0x1c73e0
    bool __cdecl tryItemAcquisitionExpire(void);  // 0x1c7750
    bool __cdecl tryWarehouseItemAcquisitionOk(void *);  // 0x1c7a50
    bool __cdecl tryWarehouseItemAcquisitionFail(short);  // 0x1c80a0
};

