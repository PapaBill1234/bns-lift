// AuctionBidJob.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "AuctionBidJob.h"
#include "LiftStub.h"

// 0x110d0
LobbyJobDef const* AuctionBidJob::GetDefinition() const
{
    LIFT_STUB(0x110d0);
}

// 0x110e0
void AuctionBidJob::deallocate_me(void*, wchar_t const*, int)
{
    LIFT_STUB(0x110e0);
}

// 0x11130
void* AuctionBidJob::_vtbl()
{
    LIFT_STUB(0x11130);
}

// 0x11210
bool AuctionBidJob::work(int, void*)
{
    LIFT_STUB(0x11210);
}

// 0x11290
bool AuctionBidJob::init(Game_AuctionBidReqParam*)
{
    LIFT_STUB(0x11290);
}

// 0x11750
bool AuctionBidJob::auctionBidReq()
{
    LIFT_STUB(0x11750);
}

// 0x11aa0
bool AuctionBidJob::auctionBidResponse(void*)
{
    LIFT_STUB(0x11aa0);
}

// 0x12130
bool AuctionBidJob::auctionBidExpire()
{
    LIFT_STUB(0x12130);
}
