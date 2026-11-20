// SecondPasswordGetStatusJob.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "SecondPasswordGetStatusJob.h"
#include "LiftStub.h"

// 0x71550
LobbyJobDef const* SecondPasswordGetStatusJob::GetDefinition() const
{
    LIFT_STUB(0x71550);
}

// 0x71560
void SecondPasswordGetStatusJob::deallocate_me(void*, wchar_t const*, int)
{
    LIFT_STUB(0x71560);
}

// 0x715b0
void* SecondPasswordGetStatusJob::_vtbl()
{
    LIFT_STUB(0x715b0);
}

// 0x71680
bool SecondPasswordGetStatusJob::work(int, void*)
{
    LIFT_STUB(0x71680);
}

// 0x71700
bool SecondPasswordGetStatusJob::init(void*)
{
    LIFT_STUB(0x71700);
}

// 0x71a60
bool SecondPasswordGetStatusJob::requestGetStatus()
{
    LIFT_STUB(0x71a60);
}

// 0x71ce0
bool SecondPasswordGetStatusJob::responseGetStatus(void*)
{
    LIFT_STUB(0x71ce0);
}

// 0x72010
bool SecondPasswordGetStatusJob::expireGetStatus()
{
    LIFT_STUB(0x72010);
}
