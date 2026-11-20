// ChangeUserNameJob.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "ChangeUserNameJob.h"
#include "LiftStub.h"

// 0x26990
LobbyJobDef const* ChangeUserNameJob::GetDefinition() const
{
    LIFT_STUB(0x26990);
}

// 0x269a0
void ChangeUserNameJob::deallocate_me(void*, wchar_t const*, int)
{
    LIFT_STUB(0x269a0);
}

// 0x269f0
void* ChangeUserNameJob::_vtbl()
{
    LIFT_STUB(0x269f0);
}

// 0x26a70
ChangeUserNameJob::ChangeUserNameJob(CliSession*)
{
    LIFT_STUB(0x26a70);
}

// 0x26ae0
ChangeUserNameJob::~ChangeUserNameJob()
{
    LIFT_STUB(0x26ae0);
}

// 0x26b50
bool ChangeUserNameJob::work(int, void*)
{
    LIFT_STUB(0x26b50);
}

// 0x26c80
bool ChangeUserNameJob::init(void*)
{
    LIFT_STUB(0x26c80);
}

// 0x275f0
bool ChangeUserNameJob::checkAccountInventoryItem()
{
    LIFT_STUB(0x275f0);
}

// 0x27790
bool ChangeUserNameJob::checkAccountInventoryItemOk(void*)
{
    LIFT_STUB(0x27790);
}

// 0x27bc0
bool ChangeUserNameJob::checkAccountInventoryItemFail(void*)
{
    LIFT_STUB(0x27bc0);
}

// 0x27e50
bool ChangeUserNameJob::checkAccountInventoryItemTimeout()
{
    LIFT_STUB(0x27e50);
}

// 0x27f70
bool ChangeUserNameJob::changeUserName()
{
    LIFT_STUB(0x27f70);
}

// 0x28580
bool ChangeUserNameJob::changeUserNameResponse(void*)
{
    LIFT_STUB(0x28580);
}

// 0x28a80
bool ChangeUserNameJob::changeUserNameExpire()
{
    LIFT_STUB(0x28a80);
}

// 0x28bd0
bool ChangeUserNameJob::consumeLobbyServiceItem()
{
    LIFT_STUB(0x28bd0);
}

// 0x28dc0
bool ChangeUserNameJob::consumeLobbyServiceItemOk(void*)
{
    LIFT_STUB(0x28dc0);
}

// 0x28ed0
bool ChangeUserNameJob::consumeLobbyServiceItemFail(void*)
{
    LIFT_STUB(0x28ed0);
}

// 0x291f0
bool ChangeUserNameJob::consumeLobbyServiceItemTimeout()
{
    LIFT_STUB(0x291f0);
}

// 0x29350
bool ChangeUserNameJob::finLobbyService()
{
    LIFT_STUB(0x29350);
}

// 0x29630
void ChangeUserNameJob::releaseService()
{
    LIFT_STUB(0x29630);
}
