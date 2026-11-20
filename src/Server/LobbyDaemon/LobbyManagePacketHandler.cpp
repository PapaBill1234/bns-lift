// LobbyManagePacketHandler.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "LobbyManagePacketHandler.h"
#include "ManageChannel.h"
#include "LiftStub.h"

// 0x58770
unsigned long long ManageChannel::GetId()
{
    LIFT_STUB(0x58770);
}

// 0x587d0
bool HandleLobbyManage_HelloReq(Session const*, Packet const*)
{
    LIFT_STUB(0x587d0);
}

// 0x589b0
bool HandleLobbyManage_AnnounceNotify(Session const*, Packet const*)
{
    LIFT_STUB(0x589b0);
}

// 0x58b00
bool HandleLobbyManage_KickReq(Session const*, Packet const*)
{
    LIFT_STUB(0x58b00);
}

// 0x590a0
bool HandleLobbyManage_CleanupGameAccountIdIndexReq(Session const*, Packet const*)
{
    LIFT_STUB(0x590a0);
}

// 0x59470
bool HandleLobbyManage_CleanupPcidIndexReq(Session const*, Packet const*)
{
    LIFT_STUB(0x59470);
}

// 0x59820
bool HandleLobbyManage_RetryMileageDepositReq(Session const*, Packet const*)
{
    LIFT_STUB(0x59820);
}
