// CreateCharacterJob.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "CreateCharacterJob.h"
#include "LiftStub.h"

// 0x41840
LobbyJobDef const* CreateCharacterJob::GetDefinition() const
{
    LIFT_STUB(0x41840);
}

// 0x41850
void CreateCharacterJob::deallocate_me(void*, wchar_t const*, int)
{
    LIFT_STUB(0x41850);
}

// 0x418a0
CreateCharacterJob::CreateCharacterJob(CliSession*)
{
    LIFT_STUB(0x418a0);
}

// 0x41940
CreateCharacterJob::~CreateCharacterJob()
{
    LIFT_STUB(0x41940);
}

// 0x41a30
bool CreateCharacterJob::work(int, void*)
{
    LIFT_STUB(0x41a30);
}

// 0x41b10
bool CreateCharacterJob::init(int, void*)
{
    LIFT_STUB(0x41b10);
}

// 0x43260
bool CreateCharacterJob::reqGetSlot()
{
    LIFT_STUB(0x43260);
}

// 0x433f0
bool CreateCharacterJob::responseGetSlot(void*)
{
    LIFT_STUB(0x433f0);
}

// 0x43a80
bool CreateCharacterJob::expireGetSlot()
{
    LIFT_STUB(0x43a80);
}

// 0x43b90
bool CreateCharacterJob::tryCreateCharacter()
{
    LIFT_STUB(0x43b90);
}

// 0x44270
bool CreateCharacterJob::createCharacterOk(void*)
{
    LIFT_STUB(0x44270);
}

// 0x44900
bool CreateCharacterJob::createCharacterFail(short)
{
    LIFT_STUB(0x44900);
}

// 0x44d40
bool CreateCharacterJob::createCharacterExpire()
{
    LIFT_STUB(0x44d40);
}
