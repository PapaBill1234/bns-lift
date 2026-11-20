// LobbyInfoGatePacketHandler.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "LobbyInfoGatePacketHandler.h"
#include "LiftStub.h"

// 0x56d40
bool HandleLobbyInfoGate_HelloReq(Session const*, Packet const*)
{
    LIFT_STUB(0x56d40);
}

// 0x57350
bool HandleLobbyInfoGate_AuthTokenReq(SharedChannel*, Packet const*)
{
    LIFT_STUB(0x57350);
}

// 0x57880
bool HandleLobbyInfoGate_GetWorldInfoListReq(SharedChannel*, Packet const*)
{
    LIFT_STUB(0x57880);
}
