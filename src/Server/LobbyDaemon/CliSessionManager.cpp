// CliSessionManager.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "CliSessionManager.h"
#include "InitCliSessionWnpTokenJob.h"
#include "LiftStub.h"

// 0x3c080
LobbyJobDef const* InitCliSessionWnpTokenJob::GetDefinition() const
{
    LIFT_STUB(0x3c080);
}

// 0x3c090
void InitCliSessionWnpTokenJob::deallocate_me(void*, wchar_t const*, int)
{
    LIFT_STUB(0x3c090);
}

// 0x3cbd0
void CliSessionManager::OnCloseLobbyGateChannel(short)
{
    LIFT_STUB(0x3cbd0);
}

// 0x3cdd0
void CliSessionManager::OnCloseGamedChannel(short)
{
    LIFT_STUB(0x3cdd0);
}
