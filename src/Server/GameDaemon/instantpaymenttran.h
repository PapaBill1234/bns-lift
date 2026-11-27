// instantpaymenttran.h: instantpaymenttran.cpp, instantpaymenttran.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class InstantPaymentBuyCollectionItemsSubJob
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
};

class InstantPaymentDrawSlateNewStoneSubJob
{
public:
    char _pad0[0x164];  // LIFT: the base layout is not lifted yet; the vptr (4 bytes) and this pad put _cashId at 0x168 as in the PDB
    int _cashId;
protected:
    virtual bool __cdecl tryInstantPaymentOkImpl(void *);  // 0x136950
    virtual void __cdecl sendFailPacket(short);  // 0x137390
    virtual int __cdecl DataId(short);  // 0x1ee480
};

class InstantPaymentJob
{
protected:
    virtual int __cdecl DataId(void);  // 0x1107d0
    virtual int __cdecl DataId(short) = 0;  // LIFT: PDB vtable slot 14
public:
    virtual bool __cdecl init(int, void *);  // 0x132850
    virtual bool __cdecl procBeforePurchase(int, void *);  // 0x1328f0
    virtual bool __cdecl apply(int, void *);  // 0x132910
    bool __cdecl tryInstantPaymentOk(void *);  // 0x132930
    bool __cdecl tryInstantPaymentFail(short);  // 0x133070
    bool __cdecl tryInstantPaymentReq(void *);  // 0x1334b0
protected:
    virtual bool __cdecl tryAbortImpl(short);  // 0x133900
public:
    virtual bool __cdecl finishInstantPaymentReq(void *);  // 0x133920
    virtual bool __cdecl finishInstantPaymentOk(void *);  // 0x133de0
    virtual bool __cdecl finishInstantPaymentFail(short);  // 0x134240
    virtual bool __cdecl finishAbort(void *);  // 0x134390
private:
    short __cdecl getGameFailReason(void);  // 0x1343b0
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

class InstantPaymentTran
{
public:
    virtual ::GameTranDef const * __cdecl GetDefinition(void) const;  // 0x1107c0
    static ::GameTranDef _def;  // LIFT: PDB data InstantPaymentTran::_def
    virtual __cdecl ~InstantPaymentTran(void);  // 0x132640
private:
    virtual bool __cdecl work(int, void *);  // 0x1326b0
};

class InstantPaymentTransformItemSubJob
{
protected:
    virtual void __cdecl setExtraParam(void *);  // 0x1351e0
    virtual void __cdecl sendFailPacket(short);  // 0x135260
    virtual bool __cdecl tryInstantPaymentOkImpl(void *);  // 0x1352a0
    virtual bool __cdecl tryInstantPaymentFailImpl(void);  // 0x135970
public:
    virtual int __cdecl DataId(short);  // 0x6eb460
};

struct InstantPaymentTryBuyCollectionItemsParam
{
public:
    __cdecl InstantPaymentTryBuyCollectionItemsParam(void);  // 0x110700
};

