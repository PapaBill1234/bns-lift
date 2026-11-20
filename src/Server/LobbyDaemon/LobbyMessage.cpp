// LobbyMessage.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "LobbyMessage.h"
#include "LiftStub.h"

// 0x2f9d0
LobbyMessage::~LobbyMessage()
{
    LIFT_STUB(0x2f9d0);
}

// 0x2f9e0
void LobbyMessage::Dispatch(LobbyMessageAcceptor*)
{
    LIFT_STUB(0x2f9e0);
}

// 0x2fa90
void CliSessionStopPcCafeChargeMessage::Dispatch(PcCafeMileage*)
{
    LIFT_STUB(0x2fa90);
}

// 0x2fad0
void CliSessionStartPcCafeChargeMessage::Dispatch(PcCafeMileage*)
{
    LIFT_STUB(0x2fad0);
}

// 0x2fb10
void CliSessionGradeChangedMessage::Dispatch(MembershipMileage*)
{
    LIFT_STUB(0x2fb10);
}

// 0x2fb60
void CliSessionMileageInterimDepositMessage::Dispatch(PcCafeMileage*)
{
    LIFT_STUB(0x2fb60);
}
