// clientsessionhandler.cpp: clientsessionhandler.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "clientsessionhandler.h"
#include "user.h"
#include "LiftStub.h"

// 0x7d6b0
void __cdecl ClientSessionHandler::OnCreated(::Session const *) const
{
    LIFT_STUB(0x7d6b0);
}

// 0x7d730
void __cdecl ClientSessionHandler::OnDestroyed(::Session const *) const
{
    LIFT_STUB(0x7d730);
}

// 0x7d7b0
bool __cdecl ClientSessionHandler::OnAccept(::Session const *) const
{
    LIFT_STUB(0x7d7b0);
}

// 0x7d810
bool __cdecl ClientSessionHandler::OnConnect(::Session const *, bool) const
{
    LIFT_STUB(0x7d810);
}

// 0x7d850
void __cdecl ClientSessionHandler::OnClose(::Session const *, bool) const
{
    LIFT_STUB(0x7d850);
}

// 0x7da70
bool __cdecl ClientSessionHandler::PacketHandler(::Session const *, ::Packet const *) const
{
    LIFT_STUB(0x7da70);
}

// 0x7e310
void __cdecl ClientSessionHandler::sendRightFailPacket(::Session const *, short) const
{
    LIFT_STUB(0x7e310);
}

// 0x7e530
unsigned short __cdecl ClientSessionHandler::getDataSize(short, char const *, unsigned __int64)
{
    LIFT_STUB(0x7e530);
}

// 0x7e6d0
void __cdecl ClientSessionHandler::logMaxRecvDisconnect(__int64, ::User *, __int64, __int64) const
{
    LIFT_STUB(0x7e6d0);
}
