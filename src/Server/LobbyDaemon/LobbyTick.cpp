// LobbyTick.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "LobbyTick.h"
#include "LiftStub.h"

// 0x5a610
LobbyTick::~LobbyTick()
{
    LIFT_STUB(0x5a610);
}

// 0x5a7f0
bool LobbyTick::HandleEvent(EventContext*, unsigned long)
{
    LIFT_STUB(0x5a7f0);
}

// 0x5a830
void LobbyTick::process()
{
    LIFT_STUB(0x5a830);
}

// 0x5a9b0
LobbyTickEvent::~LobbyTickEvent()
{
    LIFT_STUB(0x5a9b0);
}

// 0x5aa20
bool LobbyTickEvent::HandleEvent(EventContext*, unsigned long)
{
    LIFT_STUB(0x5aa20);
}
