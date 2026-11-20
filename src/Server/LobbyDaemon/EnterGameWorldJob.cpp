// EnterGameWorldJob.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "EnterGameWorldJob.h"
#include "LiftStub.h"

// 0x84e00
LobbyJobDef const* EnterGameWorldJob::GetDefinition() const
{
    LIFT_STUB(0x84e00);
}

// 0x84e10
void EnterGameWorldJob::deallocate_me(void*, wchar_t const*, int)
{
    LIFT_STUB(0x84e10);
}

// 0x84e60
void* EnterGameWorldJob::_vtbl()
{
    LIFT_STUB(0x84e60);
}

// 0x84f30
bool EnterGameWorldJob::Initialize(GamedChannel*, unsigned long long, unsigned long long)
{
    LIFT_STUB(0x84f30);
}

// 0x85080
bool EnterGameWorldJob::work(int, void*)
{
    LIFT_STUB(0x85080);
}

// 0x850c0
bool EnterGameWorldJob::init()
{
    LIFT_STUB(0x850c0);
}

// 0x85240
bool EnterGameWorldJob::enterGameWorld()
{
    LIFT_STUB(0x85240);
}
