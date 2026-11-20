// PcCafe.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "PcCafe.h"
#include "LiftStub.h"

// 0x62e90
TencentNetBar* TencentNetBar::CreateFromExternalAuthData(char const*, CliSession const*)
{
    LIFT_STUB(0x62e90);
}

// 0x63350
void TencentNetBar::onSet(CliSession*)
{
    LIFT_STUB(0x63350);
}
