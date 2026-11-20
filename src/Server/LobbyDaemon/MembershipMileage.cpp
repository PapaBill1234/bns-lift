// MembershipMileage.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "MembershipMileage.h"
#include "LiftStub.h"

// 0x5bff0
void MembershipMileage::Accept(LobbyMessage*)
{
    LIFT_STUB(0x5bff0);
}

// 0x5c040
bool MembershipMileage::Initialize(MileageConfig const&, long long)
{
    LIFT_STUB(0x5c040);
}

// 0x5c300
bool MembershipMileage::Start(CliSession*, long long)
{
    LIFT_STUB(0x5c300);
}

// 0x5c6c0
bool MembershipMileage::Stop(CliSession*, long long, long long*)
{
    LIFT_STUB(0x5c6c0);
}
