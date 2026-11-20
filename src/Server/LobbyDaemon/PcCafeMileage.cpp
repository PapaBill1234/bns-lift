// PcCafeMileage.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "PcCafeMileage.h"
#include "LiftStub.h"

// 0x633b0
void PcCafeMileage::Accept(LobbyMessage*)
{
    LIFT_STUB(0x633b0);
}

// 0x63400
bool PcCafeMileage::Start(CliSession*, long long)
{
    LIFT_STUB(0x63400);
}

// 0x636b0
bool PcCafeMileage::Stop(CliSession*, long long, long long*)
{
    LIFT_STUB(0x636b0);
}
