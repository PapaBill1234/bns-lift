// LobbyToken.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "LobbyToken.h"
#include "LiftStub.h"

// 0x96750
LobbyToken::LobbyToken(CliSession*)
{
    LIFT_STUB(0x96750);
}

// 0x96830
bool LobbyToken::Verify(int, unsigned long long, unsigned long long, unsigned long) const
{
    LIFT_STUB(0x96830);
}

// 0x96b00
void LobbyToken::Expire()
{
    LIFT_STUB(0x96b00);
}

// 0x96c30
LobbyTokenDesk::LobbyTokenDesk(long, unsigned long long (__cdecl*)(void))
{
    LIFT_STUB(0x96c30);
}

// 0x96d70
LobbyTokenDesk::~LobbyTokenDesk()
{
    LIFT_STUB(0x96d70);
}

// 0x96e20
bool LobbyTokenDesk::Issue(LobbyToken*)
{
    LIFT_STUB(0x96e20);
}

// 0x96fb0
LobbyToken* LobbyTokenDesk::Verify(int, unsigned long long, unsigned long long, unsigned long, bool&)
{
    LIFT_STUB(0x96fb0);
}

// 0x97240
bool LobbyTokenDesk::Tick(long long)
{
    LIFT_STUB(0x97240);
}
