// BindCharacterSlotJob.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "BindCharacterSlotJob.h"
#include "LiftStub.h"

// 0x16e90
LobbyJobDef const* BindCharacterSlotJob::GetDefinition() const
{
    LIFT_STUB(0x16e90);
}

// 0x16ea0
void BindCharacterSlotJob::deallocate_me(void*, wchar_t const*, int)
{
    LIFT_STUB(0x16ea0);
}

// 0x16ef0
void* BindCharacterSlotJob::_vtbl()
{
    LIFT_STUB(0x16ef0);
}

// 0x16fc0
bool BindCharacterSlotJob::work(int, void*)
{
    LIFT_STUB(0x16fc0);
}

// 0x17050
bool BindCharacterSlotJob::init(void*)
{
    LIFT_STUB(0x17050);
}

// 0x17840
bool BindCharacterSlotJob::reqGetSlot()
{
    LIFT_STUB(0x17840);
}

// 0x179e0
bool BindCharacterSlotJob::responseGetSlot(void*)
{
    LIFT_STUB(0x179e0);
}

// 0x17ff0
bool BindCharacterSlotJob::expireGetSlot()
{
    LIFT_STUB(0x17ff0);
}

// 0x18100
bool BindCharacterSlotJob::bindCharacterSlot()
{
    LIFT_STUB(0x18100);
}
