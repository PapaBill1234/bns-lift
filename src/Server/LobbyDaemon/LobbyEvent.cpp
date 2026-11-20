// LobbyEvent.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "LobbyEvent.h"
#include "LiftStub.h"

// 0xbb7f0
SharedChannelPacketHandleEvent::SharedChannelPacketHandleEvent(SharedChannel*, Packet*, bool (__cdecl*)(SharedChannel*, Packet const*))
{
    LIFT_STUB(0xbb7f0);
}

// 0xbb880
SharedChannelPacketHandleEvent::~SharedChannelPacketHandleEvent()
{
    LIFT_STUB(0xbb880);
}

// 0xbb900
bool SharedChannelPacketHandleEvent::HandleEvent(EventContext*, unsigned long)
{
    LIFT_STUB(0xbb900);
}

// 0xbb950
SharedChannelFragmentPacketHandleEvent::SharedChannelFragmentPacketHandleEvent(SharedChannel*, FragmentPacketConcatenater*, bool (__cdecl*)(SharedChannel*, FragmentPacketConcatenater*))
{
    LIFT_STUB(0xbb950);
}

// 0xbb9e0
SharedChannelFragmentPacketHandleEvent::~SharedChannelFragmentPacketHandleEvent()
{
    LIFT_STUB(0xbb9e0);
}

// 0xbba60
bool SharedChannelFragmentPacketHandleEvent::HandleEvent(EventContext*, unsigned long)
{
    LIFT_STUB(0xbba60);
}

// 0xbbad0
NPLobbyMessageHandleEvent::~NPLobbyMessageHandleEvent()
{
    LIFT_STUB(0xbbad0);
}

// 0xbbb60
bool NPLobbyMessageHandleEvent::HandleEvent(EventContext*, unsigned long)
{
    LIFT_STUB(0xbbb60);
}

// 0xbbbe0
PacketHandleEvent::~PacketHandleEvent()
{
    LIFT_STUB(0xbbbe0);
}

// 0xbbc60
bool PacketHandleEvent::HandleEvent(EventContext*, unsigned long)
{
    LIFT_STUB(0xbbc60);
}

// 0xbbcf0
bool StopPlayTimerEvent::HandleEvent(EventContext*, unsigned long)
{
    LIFT_STUB(0xbbcf0);
}
