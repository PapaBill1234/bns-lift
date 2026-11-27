// npchannel2.cpp: npchannel2.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "npchannel2.h"
#include "LiftStub.h"

// 0x1b880
bool __cdecl NPChannel::Setup(int, wchar_t const *, wchar_t *, unsigned int, unsigned __int64, long)
{
    LIFT_STUB(0x1b880);
}

// 0x1c2e0
bool __cdecl NPChannel::handlePacket(::Packet const *)
{
    LIFT_STUB(0x1c2e0);
}

// 0x1c5e0
bool __cdecl NPChannel::onConnect(::Session const *, bool)
{
    LIFT_STUB(0x1c5e0);
}

// 0x1c750
bool __cdecl NPChannel::sendInitialConnectMessage(::Session const *)
{
    LIFT_STUB(0x1c750);
}

// 0x1c860
bool __cdecl NPChannel::checkLibError(::StsMsgLib::EStsMsgError)
{
    LIFT_STUB(0x1c860);
}
