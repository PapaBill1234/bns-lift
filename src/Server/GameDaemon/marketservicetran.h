// marketservicetran.h: marketservicetran.cpp, marketservicetran.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class RegisterBidTran
{
public:
    virtual ::GameTranDef const * __cdecl GetDefinition(void) const;  // 0x15af10
private:
    virtual bool __cdecl work(int, void *);  // 0x165250
    bool __cdecl init(int, void *);  // 0x165370
    bool __cdecl reserveReq(void);  // 0x165480
    bool __cdecl reserveOk(void *);  // 0x1657a0
    bool __cdecl registerPawnOk(void *);  // 0x165ad0
    bool __cdecl registerPawnFail(short);  // 0x166070
    bool __cdecl registerBidOk(void *);  // 0x1663a0
    bool __cdecl registerBidFail(short);  // 0x1664d0
    bool __cdecl cancelPawnOk(void *);  // 0x1666b0
    bool __cdecl cancelPawnFail(short);  // 0x1669e0
    bool __cdecl abort(short);  // 0x166a60
    short __cdecl getGameFailReason(short);  // 0x166ae0
};

class RegisterPurchaseTran
{
public:
    virtual ::GameTranDef const * __cdecl GetDefinition(void) const;  // 0x15af00
private:
    virtual bool __cdecl work(int, void *);  // 0x1638d0
    bool __cdecl init(int, void *);  // 0x1639f0
    bool __cdecl reserveReq(void);  // 0x163b00
    bool __cdecl reserveOk(void *);  // 0x163e20
    bool __cdecl registerPawnOk(void *);  // 0x164150
    bool __cdecl registerPawnFail(short);  // 0x1646f0
    bool __cdecl registerPurchaseOk(void *);  // 0x164a20
    bool __cdecl registerPurchaseFail(short);  // 0x164b50
    bool __cdecl cancelPawnOk(void *);  // 0x164d30
    bool __cdecl cancelPawnFail(short);  // 0x165060
    bool __cdecl abort(short);  // 0x1650e0
    short __cdecl getGameFailReason(short);  // 0x165160
};

class UpdateBidTran
{
public:
    virtual ::GameTranDef const * __cdecl GetDefinition(void) const;  // 0x15af20
private:
    virtual bool __cdecl work(int, void *);  // 0x166bb0
    bool __cdecl init(int, void *);  // 0x166d00
    bool __cdecl addPawnMoneyReq(void);  // 0x166e10
    bool __cdecl addPawnMoneyOk(void);  // 0x167100
    bool __cdecl addPawnMoneyFail(short);  // 0x167500
    bool __cdecl updateBidPriceOk(void);  // 0x1677f0
    bool __cdecl updateBidPriceFail(short);  // 0x167910
    bool __cdecl subtractPawnMoneyOk(void);  // 0x167b00
    bool __cdecl abort(short);  // 0x167df0
};

