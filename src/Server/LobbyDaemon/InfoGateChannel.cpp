// InfoGateChannel.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "InfoGateChannel.h"
#include "LiftStub.h"

// 0x2e6d0
void InfoGateChannel::SendAuthTokenOk(unsigned long long, unsigned long long, id128 const&)
{
    LIFT_STUB(0x2e6d0);
}

// 0x2e870
void InfoGateChannel::SendAuthTokenFail(unsigned long long, unsigned long long, short)
{
    LIFT_STUB(0x2e870);
}

// 0x2e980
void InfoGateChannel::SendGetWorldInfoListFail(short)
{
    LIFT_STUB(0x2e980);
}

// 0x2ea70
InfoGateChannelManager::~InfoGateChannelManager()
{
    LIFT_STUB(0x2ea70);
}

// 0x2eb50
bool InfoGateChannelManager::Add(InfoGateChannel*)
{
    LIFT_STUB(0x2eb50);
}

// 0x2ec10
void InfoGateChannelManager::Remove(short)
{
    LIFT_STUB(0x2ec10);
}

// 0x2ed20
InfoGateChannel* InfoGateChannelManager::Acquire(short)
{
    LIFT_STUB(0x2ed20);
}

// 0x2edf0
void InfoGateChannelManager::BroadcastBoastEventInWorldNotify(short, wchar_t const*, short)
{
    LIFT_STUB(0x2edf0);
}

// 0x2ef40
bool InfoGateChannelManager::Broadcast(Packet const*)
{
    LIFT_STUB(0x2ef40);
}

// 0x2f040
bool InfoGateChannelManager::OnAccept(Session const*) const
{
    LIFT_STUB(0x2f040);
}

// 0x2f0b0
bool InfoGateChannelManager::OnConnect(Session const*, bool) const
{
    LIFT_STUB(0x2f0b0);
}

// 0x2f170
void InfoGateChannelManager::OnClose(Session const*, bool) const
{
    LIFT_STUB(0x2f170);
}

// 0x2f300
bool InfoGateChannelManager::PacketHandler(Session const*, Packet const*) const
{
    LIFT_STUB(0x2f300);
}
