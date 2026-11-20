// InitCliSessionWlobbyTokenJob.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "InitCliSessionWlobbyTokenJob.h"
#include "LiftStub.h"

// 0x54830
LobbyJobDef const* InitCliSessionWlobbyTokenJob::GetDefinition() const
{
    LIFT_STUB(0x54830);
}

// 0x54840
void InitCliSessionWlobbyTokenJob::deallocate_me(void*, wchar_t const*, int)
{
    LIFT_STUB(0x54840);
}

// 0x54890
void* InitCliSessionWlobbyTokenJob::_vtbl()
{
    LIFT_STUB(0x54890);
}

// 0x54960
bool InitCliSessionWlobbyTokenJob::Initialize(LobbyGateChannel*, unsigned long long)
{
    LIFT_STUB(0x54960);
}

// 0x54aa0
bool InitCliSessionWlobbyTokenJob::work(int, void*)
{
    LIFT_STUB(0x54aa0);
}

// 0x54ae0
bool InitCliSessionWlobbyTokenJob::init()
{
    LIFT_STUB(0x54ae0);
}

// 0x54c40
bool InitCliSessionWlobbyTokenJob::initOk()
{
    LIFT_STUB(0x54c40);
}
