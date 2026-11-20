// LogoutInGameWorldJob.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "LogoutInGameWorldJob.h"
#include "LiftStub.h"

// 0x5aa80
LobbyJobDef const* LogoutInGameWorldJob::GetDefinition() const
{
    LIFT_STUB(0x5aa80);
}

// 0x5aa90
void LogoutInGameWorldJob::deallocate_me(void*, wchar_t const*, int)
{
    LIFT_STUB(0x5aa90);
}

// 0x5aae0
void* LogoutInGameWorldJob::_vtbl()
{
    LIFT_STUB(0x5aae0);
}

// 0x5ab90
bool LogoutInGameWorldJob::Initialize(short)
{
    LIFT_STUB(0x5ab90);
}

// 0x5ac80
bool LogoutInGameWorldJob::work(int, void*)
{
    LIFT_STUB(0x5ac80);
}

// 0x5acc0
bool LogoutInGameWorldJob::init()
{
    LIFT_STUB(0x5acc0);
}

// 0x5af30
bool LogoutInGameWorldJob::logout()
{
    LIFT_STUB(0x5af30);
}
