// LobbyToken.obj (LobbyDaemon PDB, 2019 + PDB).
#include "LobbyToken.h"
#include "CliSession.h"
#include "LiftStub.h"

// LIFT: keep until the caller is lifted (0x96750).
#pragma comment(linker, "/INCLUDE:??0LobbyToken@@QEAA@PEAVCliSession@@@Z")

// 0x96750
LobbyToken::LobbyToken(CliSession* clisession) : _tokenkey(0), _clisession(clisession), _expire(0)
{
    if (clisession != nullptr)
        clisession->addReferenceCount(L"LobbyToken.cpp", 27);
}

// LIFT: the original emits this body as part of the deleting destructor (0x967d0).
LobbyToken::~LobbyToken()
{
    CliSession* clisession = _clisession;
    if (clisession != nullptr)
        clisession->removeReferenceCount(L"LobbyToken.cpp", 33);
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
