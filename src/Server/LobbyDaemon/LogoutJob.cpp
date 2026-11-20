// LogoutJob.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "LogoutJob.h"
#include "LiftStub.h"

// 0x97a10
LobbyJobDef const* LogoutJob::GetDefinition() const
{
    LIFT_STUB(0x97a10);
}

// 0x97a20
void LogoutJob::deallocate_me(void*, wchar_t const*, int)
{
    LIFT_STUB(0x97a20);
}

// 0x97a70
void* LogoutJob::_vtbl()
{
    LIFT_STUB(0x97a70);
}

// 0x97af0
LogoutJob::LogoutJob(CliSession*, LobbyGateChannel*, bool)
{
    LIFT_STUB(0x97af0);
}

// 0x97bb0
bool LogoutJob::work(int, void*)
{
    LIFT_STUB(0x97bb0);
}

// 0x97bf0
bool LogoutJob::init(int, void*)
{
    LIFT_STUB(0x97bf0);
}

// 0x97d30
bool LogoutJob::logout()
{
    LIFT_STUB(0x97d30);
}
