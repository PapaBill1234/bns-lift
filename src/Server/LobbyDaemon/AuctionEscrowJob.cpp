// AuctionEscrowJob.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "AuctionEscrowJob.h"
#include "LiftStub.h"
#include "ObjectPoolLobbyDaemon.h"

// .data 0x203b20, dynamic init 0x11d9e0, atexit dtor 0x11e900.
// The exe .data holds id 1, objsize 0x80, desc L"AuctionEscrowJob".
ObjPool AuctionEscrowJob::_pool(1, sizeof(AuctionEscrowJob), L"AuctionEscrowJob");

// 0x14cb0
LobbyJobDef const* AuctionEscrowJob::GetDefinition() const
{
    LIFT_STUB(0x14cb0);
}

// 0x14cc0
void AuctionEscrowJob::deallocate_me(void*, wchar_t const*, int)
{
    LIFT_STUB(0x14cc0);
}

// 0x14d10
void* AuctionEscrowJob::_vtbl()
{
    LIFT_STUB(0x14d10);
}

// 0x14db0
AuctionEscrowJob::~AuctionEscrowJob()
{
    LIFT_STUB(0x14db0);
}

// 0x14e20
bool AuctionEscrowJob::work(int, void*)
{
    LIFT_STUB(0x14e20);
}

// 0x14ea0
bool AuctionEscrowJob::escrow(void*)
{
    LIFT_STUB(0x14ea0);
}

// 0x15860
bool AuctionEscrowJob::escrowOk()
{
    LIFT_STUB(0x15860);
}

// 0x15a60
bool AuctionEscrowJob::escrowFail(void*)
{
    LIFT_STUB(0x15a60);
}

// 0x15e80
bool AuctionEscrowJob::escrowExpire()
{
    LIFT_STUB(0x15e80);
}
