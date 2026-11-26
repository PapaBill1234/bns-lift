// AuctionRollbackEscrowJob.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include <new>
#include "AuctionRollbackEscrowJob.h"
#include "LiftStub.h"
#include "ObjectPoolLobbyDaemon.h"

// .data 0x203bd0, dynamic init 0x11da30, atexit dtor 0x11e940.
// The exe .data holds id 1, objsize 0x78, desc L"AuctionRollbackEscrowJob".
ObjPool AuctionRollbackEscrowJob::_pool(1, sizeof(AuctionRollbackEscrowJob), L"AuctionRollbackEscrowJob");

// LIFT: no RVA. LTCG inlined it into LobbyDaemon::initialize (0x9b300). The original constructs a job on the stack
// and returns its vfptr. It does not run the destructor.
void* AuctionRollbackEscrowJob::_vtbl()
{
    char buf[sizeof(AuctionRollbackEscrowJob)];
    AuctionRollbackEscrowJob* job = ::new (buf) AuctionRollbackEscrowJob();
    return *reinterpret_cast<void**>(job);
}

// 0x15fa0
LobbyJobDef const* AuctionRollbackEscrowJob::GetDefinition() const
{
    LIFT_STUB(0x15fa0);
}

// 0x15fb0
void AuctionRollbackEscrowJob::deallocate_me(void*, wchar_t const*, int)
{
    LIFT_STUB(0x15fb0);
}

// 0x16000
AuctionRollbackEscrowJob::AuctionRollbackEscrowJob()
{
    LIFT_STUB(0x16000);
}

// 0x16090
AuctionRollbackEscrowJob::~AuctionRollbackEscrowJob()
{
    LIFT_STUB(0x16090);
}

// 0x16100
bool AuctionRollbackEscrowJob::work(int, void*)
{
    LIFT_STUB(0x16100);
}

// 0x16190
bool AuctionRollbackEscrowJob::rollbackEscrow(void*)
{
    LIFT_STUB(0x16190);
}

// 0x167c0
bool AuctionRollbackEscrowJob::registerPostOk(void*)
{
    LIFT_STUB(0x167c0);
}

// 0x16a80
bool AuctionRollbackEscrowJob::registerPostFail(void*)
{
    LIFT_STUB(0x16a80);
}

// 0x16d70
bool AuctionRollbackEscrowJob::registerPostExpire()
{
    LIFT_STUB(0x16d70);
}
