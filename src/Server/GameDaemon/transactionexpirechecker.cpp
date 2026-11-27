// transactionexpirechecker.cpp: transactionexpirechecker.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "transactionexpirechecker.h"
#include "gametran.h"
#include "LiftStub.h"

#pragma comment(linker, "/INCLUDE:?Set@GameTranExpireToken@@QEAAPEAVExpireToken@TransactionExpireChecker@@PEAVGameTran@@H@Z")  // LIFT: dead-strip keep (no live caller yet)

#define TRANSACTIONEXPIRECHECKER_FILE L"e:\\dailybuild02\\gamedaemon-common-0.0.348\\depot\\branch\\348nc\\program\\server\\gamedaemon\\TransactionExpireChecker.cpp"

// LIFT: view of the PDB class GameTran (size 0x50). Only the fields that the lifted bodies read are declared.
struct GameTranView
{
    char lift_pad_0[0x18];  // ❓ no PDB name: base and vfptr (+0 to +0x17) are not declared yet
    unsigned __int64 _id;   // +24 (0x18)
    int _state;             // +32 (0x20)
    int _lastState;         // +36 (0x24)
};

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
::TransactionExpireChecker::ExpireToken * __cdecl GameTranExpireToken::Set(::GameTran *tran, int op)
{
    if (tran == nullptr)
    {
        Log::Write(Log::LT_ERROR, TRANSACTIONEXPIRECHECKER_FILE, 235, L"== CRASH == [expire-token], set context fail; invalid parameter");
        AlertSender::Write(TRANSACTIONEXPIRECHECKER_FILE, 235, L"== CRASH == [expire-token], set context fail; invalid parameter");
        return nullptr;
    }

    ::GameTranView const *view = reinterpret_cast< ::GameTranView const *>(tran);
    _tid = view->_id;      // PDB: GameTran::GetId()
    _op = op;
    _state = view->_state; // PDB: GameTran::GetState()
    // LIFT: 0x225ae0 the base TransactionExpireChecker::ExpireToken is at +0 in the PDB; the skeleton class has no base yet.
    return reinterpret_cast< ::TransactionExpireChecker::ExpireToken *>(this);
}
