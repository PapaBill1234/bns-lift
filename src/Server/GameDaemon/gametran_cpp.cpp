// gametran_cpp.cpp: gametran.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "gametran.h"
#include "transactionexpirechecker.h"
#include "LiftStub.h"

// 0xd5950
bool __cdecl GameTran::transit(int)
{
    LIFT_STUB(0xd5950);
}

// 0xd5b60
::GameTran::Result __cdecl GameTran::execute(int, void *)
{
    LIFT_STUB(0xd5b60);
}

// 0xd5c20
::GameTran::Result __cdecl GameTran::resume(int, int, void *)
{
    LIFT_STUB(0xd5c20);
}

// 0xd5cf0
__cdecl GameTranManager::~GameTranManager(void)
{
    LIFT_STUB(0xd5cf0);
}

// 0xd5dd0
bool __cdecl GameTranManager::Initialize(unsigned __int64 (__cdecl *)(void))
{
    LIFT_STUB(0xd5dd0);
}

// 0xd5ea0
bool __cdecl GameTranManager::SetExpireChecker(long)
{
    LIFT_STUB(0xd5ea0);
}

// 0xd5f50
bool __cdecl GameTranManager::Start(::GameTran *, int, void *)
{
    LIFT_STUB(0xd5f50);
}

// 0xd5ff0
void __cdecl GameTranManager::Execute(::GameTran *, int, void *)
{
    LIFT_STUB(0xd5ff0);
}

// 0xd6070
bool __cdecl GameTranManager::ExecuteW(unsigned __int64, int, void *)
{
    LIFT_STUB(0xd6070);
}

// 0xd6100
bool __cdecl GameTranManager::ResumeW(unsigned __int64, int, int, void *)
{
    LIFT_STUB(0xd6100);
}

// 0xd61a0
bool __cdecl GameTranManager::SetExpireToken(::TransactionExpireChecker::ExpireToken *)
{
    LIFT_STUB(0xd61a0);
}

// 0xd6240
bool __cdecl GameTranManager::add(::GameTran *)
{
    LIFT_STUB(0xd6240);
}

// 0xd63a0
void __cdecl GameTranManager::remove(unsigned __int64)
{
    LIFT_STUB(0xd63a0);
}

// 0xd6460
::GameTran * __cdecl GameTranManager::find(unsigned __int64)
{
    LIFT_STUB(0xd6460);
}
