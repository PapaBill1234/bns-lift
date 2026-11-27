// managementtran.h: managementtran.cpp, managementtran.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class DepositInGuildBankTran
{
public:
    virtual ::GameTranDef const * __cdecl GetDefinition(void) const;  // 0x156b20
private:
    virtual bool __cdecl work(int, void *);  // 0x1598c0
    bool __cdecl init(int, void *);  // 0x159940
    bool __cdecl tryDepositGuildBank(void);  // 0x159ab0
    bool __cdecl depositGuildBankOk(void);  // 0x159e90
    bool __cdecl depositGuildBankFail(short);  // 0x15a290
};

class WithdrawFromGuildBankTran
{
public:
    virtual ::GameTranDef const * __cdecl GetDefinition(void) const;  // 0x156b30
private:
    virtual bool __cdecl work(int, void *);  // 0x15a410
    bool __cdecl init(int, void *);  // 0x15a490
    bool __cdecl tryWithdrawGuildBank(void);  // 0x15a600
    bool __cdecl withdrawGuildBankOk(void);  // 0x15a9b0
    bool __cdecl withdrawGuildBankFail(short);  // 0x15adc0
};

