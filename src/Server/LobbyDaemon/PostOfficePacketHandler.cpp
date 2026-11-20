// PostOfficePacketHandler.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "PostOfficePacketHandler.h"
#include "LiftStub.h"

// 0x646f0
bool HandlePostOfficeHelloOk(Session const*, Packet const*)
{
    LIFT_STUB(0x646f0);
}

// 0x64740
bool HandlePostOfficeHelloFail(Session const*, Packet const*)
{
    LIFT_STUB(0x64740);
}

// 0x647f0
bool HandlePostOfficeRegisterPostOk(Session const*, Packet const*)
{
    LIFT_STUB(0x647f0);
}

// 0x64a20
bool HandlePostOfficeRegisterPostFail(Session const*, Packet const*)
{
    LIFT_STUB(0x64a20);
}
