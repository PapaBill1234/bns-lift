// EndWaitGameWorldJob.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "EndWaitGameWorldJob.h"
#include "LiftStub.h"

// 0x4afe0
LobbyJobDef const* EndWaitGameWorldJob::GetDefinition() const
{
    LIFT_STUB(0x4afe0);
}

// 0x4aff0
void EndWaitGameWorldJob::deallocate_me(void*, wchar_t const*, int)
{
    LIFT_STUB(0x4aff0);
}

// 0x4b040
void* EndWaitGameWorldJob::_vtbl()
{
    LIFT_STUB(0x4b040);
}

// 0x4b110
bool EndWaitGameWorldJob::work(int, void*)
{
    LIFT_STUB(0x4b110);
}

// 0x4b150
bool EndWaitGameWorldJob::init(int, void*)
{
    LIFT_STUB(0x4b150);
}

// 0x4b460
bool EndWaitGameWorldJob::endWait()
{
    LIFT_STUB(0x4b460);
}
