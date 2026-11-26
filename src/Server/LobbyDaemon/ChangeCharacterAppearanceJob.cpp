// ChangeCharacterAppearanceJob.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include <new>
#include "ChangeCharacterAppearanceJob.h"
#include "LiftStub.h"
#include "ObjectPoolLobbyDaemon.h"

// .data 0x203de0, dynamic init 0x11db20, atexit dtor 0x11ea00.
// The exe .data holds id 1, objsize 0xb0, desc L"ChangeCharacterAppearanceJob".
ObjPool ChangeCharacterAppearanceJob::_pool(1, sizeof(ChangeCharacterAppearanceJob), L"ChangeCharacterAppearanceJob");

// LIFT: no RVA. LTCG inlined it into LobbyDaemon::initialize (0x9b300). The original constructs a job on the stack
// and returns its vfptr. It does not run the destructor.
void* ChangeCharacterAppearanceJob::_vtbl()
{
    char buf[sizeof(ChangeCharacterAppearanceJob)];
    ChangeCharacterAppearanceJob* job = ::new (buf) ChangeCharacterAppearanceJob(nullptr);
    return *reinterpret_cast<void**>(job);
}

// 0x1ab60
LobbyJobDef const* ChangeCharacterAppearanceJob::GetDefinition() const
{
    LIFT_STUB(0x1ab60);
}

// 0x1ab70
void ChangeCharacterAppearanceJob::deallocate_me(void*, wchar_t const*, int)
{
    LIFT_STUB(0x1ab70);
}

// 0x1abc0
ChangeCharacterAppearanceJob::ChangeCharacterAppearanceJob(CliSession* owner) : CliSessionJob(owner)  // LIFT: base init only (fix7 layout)
{
    LIFT_STUB(0x1abc0);
}

// 0x1ac50
ChangeCharacterAppearanceJob::~ChangeCharacterAppearanceJob()
{
    LIFT_STUB(0x1ac50);
}

// 0x1ad00
bool ChangeCharacterAppearanceJob::work(int, void*)
{
    LIFT_STUB(0x1ad00);
}

// 0x1aea0
bool ChangeCharacterAppearanceJob::init(void*)
{
    LIFT_STUB(0x1aea0);
}

// 0x1bae0
bool ChangeCharacterAppearanceJob::checkAccountInventoryItem()
{
    LIFT_STUB(0x1bae0);
}

// 0x1bc90
bool ChangeCharacterAppearanceJob::checkAccountInventoryItemOk(void*)
{
    LIFT_STUB(0x1bc90);
}

// 0x1c100
bool ChangeCharacterAppearanceJob::checkAccountInventoryItemFail(void*)
{
    LIFT_STUB(0x1c100);
}

// 0x1c370
bool ChangeCharacterAppearanceJob::checkAccountInventoryItemTimeout()
{
    LIFT_STUB(0x1c370);
}

// 0x1c490
bool ChangeCharacterAppearanceJob::registerServiceEntry()
{
    LIFT_STUB(0x1c490);
}

// 0x1cad0
bool ChangeCharacterAppearanceJob::tryConsumeAccountInventoryItem()
{
    LIFT_STUB(0x1cad0);
}

// 0x1cc90
bool ChangeCharacterAppearanceJob::tryConsumeAccountInventoryItemOk(void*)
{
    LIFT_STUB(0x1cc90);
}

// 0x1cf70
bool ChangeCharacterAppearanceJob::tryConsumeAccountInventoryItemFail(void*)
{
    LIFT_STUB(0x1cf70);
}

// 0x1d1d0
bool ChangeCharacterAppearanceJob::tryConsumeAccountInventoryItemTimeout()
{
    LIFT_STUB(0x1d1d0);
}

// 0x1d300
bool ChangeCharacterAppearanceJob::changeCharacterAppearance()
{
    LIFT_STUB(0x1d300);
}

// 0x1d540
bool ChangeCharacterAppearanceJob::changeCharacterAppearanceOk(void*)
{
    LIFT_STUB(0x1d540);
}

// 0x1dad0
bool ChangeCharacterAppearanceJob::changeCharacterAppearanceFail(void*)
{
    LIFT_STUB(0x1dad0);
}

// 0x1dd30
bool ChangeCharacterAppearanceJob::changeCharacterAppearanceTimeout()
{
    LIFT_STUB(0x1dd30);
}

// 0x1de60
bool ChangeCharacterAppearanceJob::finConsumeAccountInventoryItem()
{
    LIFT_STUB(0x1de60);
}

// 0x1e020
bool ChangeCharacterAppearanceJob::finConsumeAccountInventoryItemOk(void*)
{
    LIFT_STUB(0x1e020);
}

// 0x1e2f0
bool ChangeCharacterAppearanceJob::finConsumeAccountInventoryItemFail(void*)
{
    LIFT_STUB(0x1e2f0);
}

// 0x1e550
bool ChangeCharacterAppearanceJob::finConsumeAccountInventoryItemTimeout()
{
    LIFT_STUB(0x1e550);
}

// 0x1e680
bool ChangeCharacterAppearanceJob::finServiceEntry()
{
    LIFT_STUB(0x1e680);
}

// 0x229a0
bool ChangeCharacterAppearanceJob::releasePcServiceStatus()
{
    LIFT_STUB(0x229a0);
}
