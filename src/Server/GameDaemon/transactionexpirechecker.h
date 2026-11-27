// transactionexpirechecker.h: transactionexpirechecker.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class TransactionExpireChecker
{
public:
    class ExpireToken {};
    class ExpireTokenManager;
public:
    bool __cdecl Initialize(long);  // 0x2251c0
    bool __cdecl Set(::TransactionExpireChecker::ExpireToken *);  // 0x225310
};

class GameTranExpireToken
{
public:
    virtual void __cdecl Expire(void);  // 0x225aa0
    ::TransactionExpireChecker::ExpireToken * __cdecl Set(::GameTran *, int);  // 0x225ae0
private:
    char lift_pad_8[0x30];  // ❓ no PDB name: base TransactionExpireChecker::ExpireToken (+8 to +0x37) is not declared yet
    unsigned __int64 _tid;  // +56 (0x38)
    int _state;             // +64 (0x40)
    int _op;                // +68 (0x44)
};

class TransactionExpireChecker::ExpireTokenManager
{
public:
    virtual __cdecl ~ExpireTokenManager(void);  // 0x225460
    bool __cdecl remove(::TransactionExpireChecker::ExpireToken *);  // 0x2254c0
    void __cdecl expireAll(void);  // 0x225540
    virtual bool __cdecl HandleEvent(::EventContext *, unsigned long);  // 0x225800
private:
    void __cdecl timerExpired(void);  // 0x225810
};

