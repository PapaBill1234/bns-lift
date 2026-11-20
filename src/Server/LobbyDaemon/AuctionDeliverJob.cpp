// AuctionDeliverJob.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "AuctionDeliverJob.h"
#include "LobbyJob.h"
#include "LiftStub.h"

// 0x12230
RefCntPoolObj::~RefCntPoolObj()
{
    LIFT_STUB(0x12230);
}

// 0x12270
LobbyJob::~LobbyJob()
{
    LIFT_STUB(0x12270);
}

// 0x122b0
bool LobbyJob::dispatch_work(int, void*)
{
    LIFT_STUB(0x122b0);
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
