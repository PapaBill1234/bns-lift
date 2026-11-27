// transactionexpirechecker.cpp: transactionexpirechecker.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "transactionexpirechecker.h"
#include "gametran.h"
#include "LiftStub.h"

// 0x2251c0
bool __cdecl TransactionExpireChecker::Initialize(long)
{
    LIFT_STUB(0x2251c0);
}

// 0x225310
bool __cdecl TransactionExpireChecker::Set(::TransactionExpireChecker::ExpireToken *)
{
    LIFT_STUB(0x225310);
}

// 0x225460
__cdecl TransactionExpireChecker::ExpireTokenManager::~ExpireTokenManager(void)
{
    LIFT_STUB(0x225460);
}

// 0x2254c0
bool __cdecl TransactionExpireChecker::ExpireTokenManager::remove(::TransactionExpireChecker::ExpireToken *)
{
    LIFT_STUB(0x2254c0);
}

// 0x225540
void __cdecl TransactionExpireChecker::ExpireTokenManager::expireAll(void)
{
    LIFT_STUB(0x225540);
}

// 0x225800
bool __cdecl TransactionExpireChecker::ExpireTokenManager::HandleEvent(::EventContext *, unsigned long)
{
    LIFT_STUB(0x225800);
}

// 0x225810
void __cdecl TransactionExpireChecker::ExpireTokenManager::timerExpired(void)
{
    LIFT_STUB(0x225810);
}

// 0x225aa0
void __cdecl GameTranExpireToken::Expire(void)
{
    LIFT_STUB(0x225aa0);
}

// 0x225ae0
::TransactionExpireChecker::ExpireToken * __cdecl GameTranExpireToken::Set(::GameTran *, int)
{
    LIFT_STUB(0x225ae0);
}
