// GetLobbyServiceItemJob.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "GetLobbyServiceItemJob.h"
#include "LiftStub.h"

// 0x52060
LobbyJobDef const* GetLobbyServiceItemJob::GetDefinition() const
{
    LIFT_STUB(0x52060);
}

// 0x52070
void GetLobbyServiceItemJob::deallocate_me(void*, wchar_t const*, int)
{
    LIFT_STUB(0x52070);
}

// 0x520c0
void* GetLobbyServiceItemJob::_vtbl()
{
    LIFT_STUB(0x520c0);
}

// 0x52140
GetLobbyServiceItemJob::GetLobbyServiceItemJob(CliSession*, LobbyGateChannel*, unsigned long long)
{
    LIFT_STUB(0x52140);
}

// 0x521e0
GetLobbyServiceItemJob::~GetLobbyServiceItemJob()
{
    LIFT_STUB(0x521e0);
}

// 0x52250
bool GetLobbyServiceItemJob::work(int, void*)
{
    LIFT_STUB(0x52250);
}

// 0x522f0
bool GetLobbyServiceItemJob::init()
{
    LIFT_STUB(0x522f0);
}

// 0x52620
bool GetLobbyServiceItemJob::getLobbyServiceItemReq()
{
    LIFT_STUB(0x52620);
}

// 0x527b0
bool GetLobbyServiceItemJob::getLobbyServiceItemOk(void*)
{
    LIFT_STUB(0x527b0);
}

// 0x529d0
bool GetLobbyServiceItemJob::getLobbyServiceItemFail(void*)
{
    LIFT_STUB(0x529d0);
}

// 0x52be0
bool GetLobbyServiceItemJob::getLobbyServiceItemTimeout()
{
    LIFT_STUB(0x52be0);
}
