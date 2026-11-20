// LobbyPerfMonitor.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "LobbyPerfMonitor.h"
#include "LiftStub.h"

// 0x59ce0
SystemPerfMonitor::~SystemPerfMonitor()
{
    LIFT_STUB(0x59ce0);
}

// 0x59d60
bool SystemPerfMonitor::Initialize()
{
    LIFT_STUB(0x59d60);
}

// 0x59e30
bool SystemPerfMonitor::Start()
{
    LIFT_STUB(0x59e30);
}

// 0x59ee0
bool SystemPerfMonitor::HandleEvent(EventContext*, unsigned long)
{
    LIFT_STUB(0x59ee0);
}

// 0x59f40
void SystemPerfMonitor::update()
{
    LIFT_STUB(0x59f40);
}
