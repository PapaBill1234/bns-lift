// LobbyStats.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "LobbyStats.h"
#include "LiftStub.h"

// 0x5a0b0
bool LobbyStats::Initialize(wchar_t const*, wchar_t const*, wchar_t const*, long)
{
    LIFT_STUB(0x5a0b0);
}

// 0x5a1d0
bool LobbyStats::HandleEvent(EventContext*, unsigned long)
{
    LIFT_STUB(0x5a1d0);
}

// 0x5a210
bool LobbyStats::update()
{
    LIFT_STUB(0x5a210);
}
