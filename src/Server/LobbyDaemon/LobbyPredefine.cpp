// LobbyPredefine.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "LobbyPredefine.h"
#include "LiftStub.h"

// 0x96480
char GetLobbyGateKickReason(int)
{
    LIFT_STUB(0x96480);
}

// 0x96500
char GetGameWorldKickReason(int)
{
    LIFT_STUB(0x96500);
}

// 0x96580
bool GetId128FromGuidString(wchar_t const*, id128*)
{
    LIFT_STUB(0x96580);
}

// 0x966a0
bool CreateNewId128(id128*)
{
    LIFT_STUB(0x966a0);
}
