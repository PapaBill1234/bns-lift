// LobbyJob.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "LobbyJob.h"
#include "LiftStub.h"

// 0xc1670
LobbyJobTaskEvent::~LobbyJobTaskEvent()
{
    LIFT_STUB(0xc1670);
}

// 0xc1710
bool LobbyJob::transit(int)
{
    LIFT_STUB(0xc1710);
}

// 0xc1a60
LobbyJobManager::~LobbyJobManager()
{
    LIFT_STUB(0xc1a60);
}

// 0xc1b40
bool LobbyJobManager::Initialize(int)
{
    LIFT_STUB(0xc1b40);
}

// 0xc1c90
bool LobbyJobManager::Register(LobbyJob*)
{
    LIFT_STUB(0xc1c90);
}

// 0xc1d20
void LobbyJobManager::Clear()
{
    LIFT_STUB(0xc1d20);
}

// 0xc1ed0
bool LobbyJobManager::Start(LobbyJob*, int, void*)
{
    LIFT_STUB(0xc1ed0);
}

// 0xc1f30
bool LobbyJobManager::Postpone(LobbyJob*, int, LobbyJobTaskParam*)
{
    LIFT_STUB(0xc1f30);
}

// 0xc2020
void LobbyJobManager::Execute(LobbyJob*, int, void*)
{
    LIFT_STUB(0xc2020);
}

// 0xc20a0
bool LobbyJobManager::ExecuteW(unsigned long long, int, void*)
{
    LIFT_STUB(0xc20a0);
}

// 0xc2140
bool LobbyJobManager::ResumeW(unsigned long long, int, int, void*)
{
    LIFT_STUB(0xc2140);
}

// 0xc21f0
bool LobbyJobManager::add(LobbyJob*)
{
    LIFT_STUB(0xc21f0);
}

// 0xc22d0
void LobbyJobManager::remove(unsigned long long)
{
    LIFT_STUB(0xc22d0);
}

// 0xc23d0
LobbyJob* LobbyJobManager::find(unsigned long long)
{
    LIFT_STUB(0xc23d0);
}

// 0xc24c0
bool LobbyJobTaskEvent::HandleEvent(EventContext*, unsigned long)
{
    LIFT_STUB(0xc24c0);
}
