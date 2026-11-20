// LeaveGameWorldJob.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "LeaveGameWorldJob.h"
#include "LiftStub.h"

// 0x877b0
LobbyJobDef const* LeaveGameWorldJob::GetDefinition() const
{
    LIFT_STUB(0x877b0);
}

// 0x877c0
void LeaveGameWorldJob::deallocate_me(void*, wchar_t const*, int)
{
    LIFT_STUB(0x877c0);
}

// 0x87810
void* LeaveGameWorldJob::_vtbl()
{
    LIFT_STUB(0x87810);
}

// 0x878e0
bool LeaveGameWorldJob::Initialize(GamedChannel*, unsigned long long, unsigned long long)
{
    LIFT_STUB(0x878e0);
}

// 0x87a00
bool LeaveGameWorldJob::work(int, void*)
{
    LIFT_STUB(0x87a00);
}

// 0x87a40
bool LeaveGameWorldJob::init()
{
    LIFT_STUB(0x87a40);
}

// 0x87e90
bool LeaveGameWorldJob::leaveGameWorld()
{
    LIFT_STUB(0x87e90);
}
