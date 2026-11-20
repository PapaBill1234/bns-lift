// GiveupWaitGameWorldJob.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "GiveupWaitGameWorldJob.h"
#include "LiftStub.h"

// 0x52cf0
LobbyJobDef const* GiveupWaitGameWorldJob::GetDefinition() const
{
    LIFT_STUB(0x52cf0);
}

// 0x52d00
void GiveupWaitGameWorldJob::deallocate_me(void*, wchar_t const*, int)
{
    LIFT_STUB(0x52d00);
}

// 0x52d50
void* GiveupWaitGameWorldJob::_vtbl()
{
    LIFT_STUB(0x52d50);
}

// 0x52e20
bool GiveupWaitGameWorldJob::Initialize(LobbyGateChannel*)
{
    LIFT_STUB(0x52e20);
}

// 0x52f30
bool GiveupWaitGameWorldJob::work(int, void*)
{
    LIFT_STUB(0x52f30);
}

// 0x52f70
bool GiveupWaitGameWorldJob::init()
{
    LIFT_STUB(0x52f70);
}

// 0x530d0
bool GiveupWaitGameWorldJob::giveupWait()
{
    LIFT_STUB(0x530d0);
}
