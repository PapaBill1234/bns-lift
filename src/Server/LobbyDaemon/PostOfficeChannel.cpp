// PostOfficeChannel.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "PostOfficeChannel.h"
#include "LiftStub.h"

// 0x639f0
bool PostOfficeChannel::Connect(unsigned long long, unsigned int, unsigned long, unsigned short, long, bool)
{
    LIFT_STUB(0x639f0);
}

// 0x63ba0
bool PostOfficeChannel::SendHelloReq()
{
    LIFT_STUB(0x63ba0);
}

// 0x64170
bool PostOfficeSessionHandler::OnAccept(Session const*) const
{
    LIFT_STUB(0x64170);
}

// 0x641d0
bool PostOfficeSessionHandler::OnConnect(Session const*, bool) const
{
    LIFT_STUB(0x641d0);
}

// 0x642e0
void PostOfficeSessionHandler::OnClose(Session const*, bool) const
{
    LIFT_STUB(0x642e0);
}

// 0x64420
bool PostOfficeSessionHandler::PacketHandler(Session const*, Packet const*) const
{
    LIFT_STUB(0x64420);
}
