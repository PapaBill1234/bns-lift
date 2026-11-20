// ListLobbyServiceItemJob.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "ListLobbyServiceItemJob.h"
#include "LiftStub.h"

// 0x55b20
LobbyJobDef const* ListLobbyServiceItemJob::GetDefinition() const
{
    LIFT_STUB(0x55b20);
}

// 0x55b30
void ListLobbyServiceItemJob::deallocate_me(void*, wchar_t const*, int)
{
    LIFT_STUB(0x55b30);
}

// 0x55b80
void* ListLobbyServiceItemJob::_vtbl()
{
    LIFT_STUB(0x55b80);
}

// 0x55c00
ListLobbyServiceItemJob::ListLobbyServiceItemJob(CliSession*, LobbyGateChannel*, char, unsigned long long)
{
    LIFT_STUB(0x55c00);
}

// 0x55cb0
ListLobbyServiceItemJob::~ListLobbyServiceItemJob()
{
    LIFT_STUB(0x55cb0);
}

// 0x55d20
bool ListLobbyServiceItemJob::work(int, void*)
{
    LIFT_STUB(0x55d20);
}

// 0x55dc0
bool ListLobbyServiceItemJob::init()
{
    LIFT_STUB(0x55dc0);
}

// 0x560f0
bool ListLobbyServiceItemJob::listLobbyServiceItemReq()
{
    LIFT_STUB(0x560f0);
}

// 0x56280
bool ListLobbyServiceItemJob::listLobbyServiceItemOk(void*)
{
    LIFT_STUB(0x56280);
}

// 0x56490
bool ListLobbyServiceItemJob::listLobbyServiceItemFail(void*)
{
    LIFT_STUB(0x56490);
}

// 0x56670
bool ListLobbyServiceItemJob::listLobbyServiceItemTimeout()
{
    LIFT_STUB(0x56670);
}
