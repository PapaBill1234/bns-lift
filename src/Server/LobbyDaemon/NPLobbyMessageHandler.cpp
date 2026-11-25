// NPLobbyMessageHandler.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "NPLobbyMessageHandler.h"
#include "LiftStub.h"

// 0xcb710
bool (*DispatchNPLobbyMessageHandler(int))(NPChannel*, StsMsgLib::_StsMsg*, NPTransaction*)
{
    LIFT_STUB(0xcb710);
}
