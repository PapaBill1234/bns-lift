// ManageChannel.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "ManageChannel.h"
#include "LiftStub.h"

// 0x5b140
bool ManageSessionHandler::OnAccept(Session const*) const
{
    LIFT_STUB(0x5b140);
}

// 0x5b180
bool ManageSessionHandler::OnConnect(Session const*, bool) const
{
    LIFT_STUB(0x5b180);
}

// 0x5b1c0
void ManageSessionHandler::OnClose(Session const*, bool) const
{
    LIFT_STUB(0x5b1c0);
}

// 0x5b2a0
bool ManageSessionHandler::PacketHandler(Session const*, Packet const*) const
{
    LIFT_STUB(0x5b2a0);
}

// 0x5b630
void ManageChannel::SendKickOk(Session const*, unsigned long long)
{
    LIFT_STUB(0x5b630);
}

// 0x5b760
void ManageChannel::SendKickFail(Session const*, unsigned long long, short)
{
    LIFT_STUB(0x5b760);
}

// 0x5b8a0
void ManageChannel::SendCleanupGameAccountIdIndexOk(Session const*, unsigned long long)
{
    LIFT_STUB(0x5b8a0);
}

// 0x5b9d0
void ManageChannel::SendCleanupGameAccountIdIndexFail(Session const*, unsigned long long, short)
{
    LIFT_STUB(0x5b9d0);
}

// 0x5bb10
void ManageChannel::SendCleanupPcidIndexOk(Session const*, unsigned long long)
{
    LIFT_STUB(0x5bb10);
}

// 0x5bc40
void ManageChannel::SendCleanupPcidIndexFail(Session const*, unsigned long long, short)
{
    LIFT_STUB(0x5bc40);
}

// 0x5bd80
void ManageChannel::SendRetryMileageDepositOk(Session const*, unsigned long long)
{
    LIFT_STUB(0x5bd80);
}

// 0x5beb0
void ManageChannel::SendRetryMileageDepositFail(Session const*, unsigned long long, short)
{
    LIFT_STUB(0x5beb0);
}
