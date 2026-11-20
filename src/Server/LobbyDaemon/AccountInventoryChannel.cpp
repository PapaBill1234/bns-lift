// AccountInventoryChannel.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "AccountInventoryChannel.h"
#include "LiftStub.h"

// 0x6500
bool AccountInventoryChannel::Connect(unsigned long long, unsigned int, unsigned long, unsigned short, long, bool)
{
    LIFT_STUB(0x6500);
}

// 0x66b0
bool AccountInventoryChannel::SendHelloReq(short, short, short)
{
    LIFT_STUB(0x66b0);
}

// 0x67b0
bool AccountInventoryChannel::SendLoginNotify(id128 const&)
{
    LIFT_STUB(0x67b0);
}

// 0x68a0
bool AccountInventoryChannel::SendLogoutNotify(id128 const&)
{
    LIFT_STUB(0x68a0);
}

// 0x8020
bool AccountInventorySessionHandler::OnAccept(Session const*) const
{
    LIFT_STUB(0x8020);
}

// 0x8080
bool AccountInventorySessionHandler::OnConnect(Session const*, bool) const
{
    LIFT_STUB(0x8080);
}

// 0x81b0
void AccountInventorySessionHandler::OnClose(Session const*, bool) const
{
    LIFT_STUB(0x81b0);
}

// 0x82f0
bool AccountInventorySessionHandler::PacketHandler(Session const*, Packet const*) const
{
    LIFT_STUB(0x82f0);
}
