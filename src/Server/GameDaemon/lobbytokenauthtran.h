// lobbytokenauthtran.h: lobbytokenauthtran.cpp, lobbytokenauthtran.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

struct EnterWorldOkParam
{
public:
    __cdecl EnterWorldOkParam(void);  // 0x13e020
    __cdecl ~EnterWorldOkParam(void);  // 0x13fd20
};

class LobbyTokenAuthTran
{
public:
    virtual ::GameTranDef const * __cdecl GetDefinition(void) const;  // 0x13e270
    __cdecl LobbyTokenAuthTran(::Session *);  // 0x14edb0
    virtual __cdecl ~LobbyTokenAuthTran(void);  // 0x14eff0
private:
    virtual bool __cdecl work(int, void *);  // 0x14f3f0
    bool __cdecl init(int, void *);  // 0x14fc30
    bool __cdecl tryEnterWorld(void);  // 0x14fd00
    bool __cdecl enterWorldOk(void *);  // 0x14fea0
    bool __cdecl enterWorldFail(short);  // 0x1504d0
    bool __cdecl preLoadSeasonContentsCombatRecordOk(void *);  // 0x150610
    bool __cdecl preLoadSeasonContentsCombatRecordFail(short);  // 0x150950
    bool __cdecl initializeCharacterReq(void);  // 0x150a50
    bool __cdecl initializeCharacterFail(short);  // 0x151310
    bool __cdecl loadSeasonContentsRankingLogListFail(short);  // 0x151460
    bool __cdecl retryTakeRankingRewardOk(void *);  // 0x151570
    bool __cdecl retryTakeRankingRewardFail(short);  // 0x151680
    bool __cdecl retryTakeAchievementRewardOk(void *);  // 0x151780
    bool __cdecl retryTakeAchievementRewardFail(short);  // 0x151890
    bool __cdecl retryTakeDuelBotTrainingRoomRewardOk(void *);  // 0x151990
    bool __cdecl retryTakeDuelBotTrainingRoomRewardFail(short);  // 0x151ab0
    bool __cdecl recoverUncompletedCraftReq(void);  // 0x151bb0
    bool __cdecl recoverUncompletedCraftOk(void *);  // 0x151c40
    bool __cdecl recoverUncompletedCraftFail(short);  // 0x151d50
    bool __cdecl recoverUncompletedRenameGuildReq(void);  // 0x151e30
    bool __cdecl recoverUncompletedRenameGuildOk(void *);  // 0x151ec0
    bool __cdecl recoverUncompletedRenameGuildFail(short);  // 0x151fc0
    bool __cdecl recoverUncompletedWeaponAppearanceChangeOk(void *);  // 0x1520a0
    bool __cdecl recoverUncompletedWeaponAppearanceChangeFail(short);  // 0x1521a0
    void __cdecl finishedToRecoverUncompletedWeaponAppearanceChange(void);  // 0x1522a0
    bool __cdecl diagnoseOuterWorldReq(void);  // 0x1523a0
    bool __cdecl retrieveMarketReservationListOk(void *);  // 0x152530
    bool __cdecl retrieveMarketReservationListFail(short);  // 0x152a20
    bool __cdecl retrieveAccInvenUncompleteListOk(void *);  // 0x152ac0
    bool __cdecl retrieveAccInvenUncompleteListFail(short);  // 0x152f40
    bool __cdecl diagnoseInWorldReq(void);  // 0x153020
    bool __cdecl restorePawnOk(void *);  // 0x153470
    bool __cdecl restorePawnFail(short);  // 0x153530
    bool __cdecl loadUncompletedWarehouseItemAcquisitionOk(void *);  // 0x1535b0
    bool __cdecl loadUncompletedWarehouseItemAcquisitionFail(short);  // 0x1542b0
    bool __cdecl applyResultToOuterWorldReq(void);  // 0x154330
    bool __cdecl cancelMarketReservationListOk(void *);  // 0x154c60
    bool __cdecl cancelMarketReservationListFail(short);  // 0x154db0
    bool __cdecl finishTakeMultipleItemOk(void *);  // 0x154e50
    bool __cdecl finishTakeMultipleItemFail(short);  // 0x155240
    bool __cdecl tryStartCharge(void);  // 0x155310
    bool __cdecl tryLoadCharacter(void);  // 0x1554f0
    bool __cdecl loadCharacterOk(void *);  // 0x155610
    bool __cdecl loadCharacterFail(short);  // 0x156360
    bool __cdecl startChargeOk(void *);  // 0x1564a0
    bool __cdecl startChargeFail(short);  // 0x156810
    bool __cdecl successLobbyTokenAuth(void);  // 0x156a40
};

