// instantpaymenttran.h: instantpaymenttran.cpp, instantpaymenttran.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: some classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"
#include "gametran.h"

// PDB: InstantPaymentJob, size 0x158. The vtable order is the PDB slot order.
class InstantPaymentJob
{
public:
    enum INSTANT_PAYMENT_JOB_TYPE {};
    virtual __cdecl ~InstantPaymentJob(void) {}  // slot 0
    virtual INSTANT_PAYMENT_JOB_TYPE __cdecl GetType(void) = 0;  // slot 1
    virtual bool __cdecl init(int, void *);  // 0x132850, slot 2
    bool __cdecl tryInstantPaymentReq(void *);  // 0x1334b0
    bool __cdecl tryInstantPaymentOk(void *);  // 0x132930
    bool __cdecl tryInstantPaymentFail(short);  // 0x133070
    virtual bool __cdecl finishInstantPaymentReq(void *);  // 0x133920, slot 3
    virtual bool __cdecl finishInstantPaymentOk(void *);  // 0x133de0, slot 4
    virtual bool __cdecl finishInstantPaymentFail(short);  // 0x134240, slot 5
    virtual bool __cdecl finishAbort(void *);  // 0x134390, slot 6
    virtual bool __cdecl procBeforePurchase(int, void *);  // 0x1328f0, slot 7
    virtual bool __cdecl apply(int, void *);  // 0x132910, slot 8
    virtual bool __cdecl procAfterPurchase(int, void *) = 0;  // LIFT: PDB slot 9; body not declared yet
protected:
    virtual bool __cdecl tryAbortImpl(short);  // 0x133900, slot 10
    virtual bool __cdecl tryInstantPaymentFailImpl(void) = 0;  // slot 11
    virtual bool __cdecl tryInstantPaymentOkImpl(void *) = 0;  // slot 12
    virtual int __cdecl DataId(void);  // 0x1107d0, slot 13
    virtual int __cdecl DataId(short) = 0;  // slot 14
    virtual void __cdecl setExtraParam(void *) = 0;  // slot 15
    virtual void __cdecl postFailProc(void) = 0;  // slot 16
    virtual void __cdecl sendFailPacket(short) = 0;  // slot 17
private:
    short __cdecl getGameFailReason(void);  // 0x1343b0
protected:
    ::InstantPaymentTran *_tran;  // +0x8
    ::InstantPaymentGoodsInfoParam _goodsInfo;  // +0x10
    __int64 _resultServiceId;  // +0x118
    __int64 _resultPurchaseId;  // +0x120
    unsigned int _resultServiceTypes[10];  // +0x128
    short _resultServiceTypeCount;  // +0x150
    short _instantPaymentFailReason;  // +0x152
};

// PDB: InstantPaymentTryBuyCollectionItemsParam, size 0x110.
struct InstantPaymentTryBuyCollectionItemsParam
{
public:
    struct BuyItem
    {
        unsigned int chargeItem;  // +0x0
        unsigned __int64 closetGroupKey;  // +0x8
        unsigned __int64 collectionItemKey;  // +0x10
    };
    short buyItemCount;  // +0x0
    BuyItem buyItem[10];  // +0x8
    unsigned __int64 reserved[3];  // +0xf8  LIFT: PDB type ReservedPosForInstantPayment (0x18 bytes); its layout is not lifted yet
    __cdecl InstantPaymentTryBuyCollectionItemsParam(void);  // 0x110700
};

class InstantPaymentBuyCollectionItemsSubJob : public InstantPaymentJob
{
protected:
    virtual void __cdecl setExtraParam(void *);  // 0x135e20
    virtual void __cdecl sendFailPacket(short);  // 0x135e80
public:
    virtual int __cdecl DataId(short);  // 0x135f00
protected:
    virtual bool __cdecl tryInstantPaymentOkImpl(void *);  // 0x135f10
    virtual bool __cdecl tryInstantPaymentFailImpl(void);  // 0x136510
public:
    __cdecl InstantPaymentBuyCollectionItemsSubJob(::InstantPaymentTran *);  // 0x350300
private:
    ::InstantPaymentTryBuyCollectionItemsParam _buyParam;  // +0x158
};

class InstantPaymentDrawSlateNewStoneSubJob
{
// LIFT: no members and no base yet: the InstantPaymentJob layout is not lifted, so _cashId (PDB offset 360) cannot be placed.
protected:
    virtual bool __cdecl tryInstantPaymentOkImpl(void *);  // 0x136950
    virtual void __cdecl sendFailPacket(short);  // 0x137390
    virtual int __cdecl DataId(short);  // 0x1ee480
};

class InstantPaymentRandomStoreDrawSubJob
{
public:
    virtual int __cdecl DataId(short);  // 0x1344e0
protected:
    virtual void __cdecl sendFailPacket(short);  // 0x134590
    virtual bool __cdecl tryInstantPaymentOkImpl(void *);  // 0x134620
};

class InstantPaymentRandomStoreExpandSubJob
{
public:
    virtual int __cdecl DataId(short);  // 0x134b30
protected:
    virtual void __cdecl sendFailPacket(short);  // 0x134c00
    virtual bool __cdecl tryInstantPaymentOkImpl(void *);  // 0x134ca0
};

// PDB: InstantPaymentTran, size 0x60.
class InstantPaymentTran : public UserTran
{
public:
    virtual ::GameTranDef const * __cdecl GetDefinition(void) const;  // 0x1107c0
    static ::GameTranDef _def;  // LIFT: PDB data InstantPaymentTran::_def
    virtual __cdecl ~InstantPaymentTran(void);  // 0x132640
private:
    virtual bool __cdecl work(int, void *);  // 0x1326b0
    ::InstantPaymentJob *_job;  // +0x58
};

// PDB: InstantPaymentTransformItemSubJob, size 0x258.
class InstantPaymentTransformItemSubJob : public InstantPaymentJob
{
protected:
    virtual void __cdecl setExtraParam(void *);  // 0x1351e0
    virtual void __cdecl sendFailPacket(short);  // 0x135260
    virtual bool __cdecl tryInstantPaymentOkImpl(void *);  // 0x1352a0
    virtual bool __cdecl tryInstantPaymentFailImpl(void);  // 0x135970
public:
    virtual int __cdecl DataId(short);  // 0x6eb460
private:
    __int64 _recipeId;  // +0x158
    int _goodsItemDataId;  // +0x160
    ::InstantPaymentTransformInfoParam _transformParam;  // +0x168
};

