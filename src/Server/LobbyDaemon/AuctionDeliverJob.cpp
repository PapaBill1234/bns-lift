// AuctionDeliverJob.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include <new>
#include "AuctionDeliverJob.h"
#include "LobbyJob.h"
#include "LiftStub.h"
#include "ObjectPoolLobbyDaemon.h"

// .data 0x203a70, dynamic init 0x11d990, atexit dtor 0x11e8c0.
// The exe .data holds id 1, objsize 0xd8, desc L"AuctionDeliverJob".
ObjPool AuctionDeliverJob::_pool(1, sizeof(AuctionDeliverJob), L"AuctionDeliverJob");

// LIFT: no RVA. LTCG inlined it into LobbyDaemon::initialize (0x9b300). The original constructs a job on the stack
// and returns its vfptr. It does not run the destructor.
void* AuctionDeliverJob::_vtbl()
{
    char buf[sizeof(AuctionDeliverJob)];
    AuctionDeliverJob* job = ::new (buf) AuctionDeliverJob();
    return *reinterpret_cast<void**>(job);
}

// 0x12230
RefCntPoolObj::~RefCntPoolObj()
{
}

// 0x12270
LobbyJob::~LobbyJob()
{
    // The CriticalSection dtor of _lock and the RefCntPoolObj dtor run here.
}

// 0x122b0
bool LobbyJob::dispatch_work(int task, void* param)
{
    return work(task, param);
}

// 0x12300
LobbyJobDef const* AuctionDeliverJob::GetDefinition() const
{
    LIFT_STUB(0x12300);
}

// 0x12310
void AuctionDeliverJob::deallocate_me(void*, wchar_t const*, int)
{
    LIFT_STUB(0x12310);
}

// 0x12360
AuctionDeliverJob::AuctionDeliverJob()
{
    LIFT_STUB(0x12360);
}

// 0x123f0
AuctionDeliverJob::~AuctionDeliverJob()
{
    LIFT_STUB(0x123f0);
}

// 0x12460
bool AuctionDeliverJob::work(int, void*)
{
    LIFT_STUB(0x12460);
}

// 0x124f0
bool AuctionDeliverJob::init(void*)
{
    LIFT_STUB(0x124f0);
}

// 0x12f30
bool AuctionDeliverJob::registerPostOk(void*)
{
    LIFT_STUB(0x12f30);
}

// 0x13230
bool AuctionDeliverJob::registerPostFail(void*)
{
    LIFT_STUB(0x13230);
}

// 0x13520
bool AuctionDeliverJob::registerPostTimeout()
{
    LIFT_STUB(0x13520);
}
