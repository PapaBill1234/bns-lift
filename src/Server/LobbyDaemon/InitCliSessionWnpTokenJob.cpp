// InitCliSessionWnpTokenJob.obj (LobbyDaemon PDB, 2019 + PDB). Lifted from the pseudocode with PDB types.
#include <new>
#include "InitCliSessionWnpTokenJob.h"
#include "LiftStub.h"

namespace
{
LobbyJobStateDef const StateDef[] = {{0, L"INIT"}, {1, L"FIN"}};  // 0x12da30
}

LobbyJobDef InitCliSessionWnpTokenJob::_def = {1, StateDef, 1, L"InitCliSessionWnpTokenJob"};  // 0x2017b0
// LIFT: InitCliSessionWnpTokenJob::_pool (0x2055f0) has no definition. The LobbyDaemon ObjectPool module is not in
// lift_lobbydaemon (see CliSession.cpp).

// 0x98120
// The original constructs a job on the stack (null owner) and returns its vfptr. It does not run the destructor.
void* InitCliSessionWnpTokenJob::_vtbl()
{
    char buf[sizeof(InitCliSessionWnpTokenJob)];
    InitCliSessionWnpTokenJob* job = ::new (buf) InitCliSessionWnpTokenJob(nullptr);
    return *reinterpret_cast<void**>(job);
}

// 0x981a0
bool InitCliSessionWnpTokenJob::work(int task, void* param)
{
    return _state == INIT && task == 7 && init(task, param);
}

// 0x981c0
// LIFT: Not done. The body builds an AnonymousLobbyGatePresence. Its constructor (0x3a3f0) is still a stub.
bool InitCliSessionWnpTokenJob::init(int, void*)
{
    LIFT_STUB(0x981c0);
}
