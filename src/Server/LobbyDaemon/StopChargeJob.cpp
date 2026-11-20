// StopChargeJob.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "StopChargeJob.h"
#include "LiftStub.h"

// 0x77c90
LobbyJobDef const* StopChargeJob::GetDefinition() const
{
    LIFT_STUB(0x77c90);
}

// 0x77ca0
void StopChargeJob::deallocate_me(void*, wchar_t const*, int)
{
    LIFT_STUB(0x77ca0);
}

// 0x77cf0
void* StopChargeJob::_vtbl()
{
    LIFT_STUB(0x77cf0);
}

// 0x77dc0
bool StopChargeJob::Initialize(GamedChannel*, unsigned long long, unsigned long long, wchar_t*)
{
    LIFT_STUB(0x77dc0);
}

// 0x77f50
bool StopChargeJob::work(int, void*)
{
    LIFT_STUB(0x77f50);
}

// 0x77fd0
bool StopChargeJob::init()
{
    LIFT_STUB(0x77fd0);
}

// 0x78290
bool StopChargeJob::requestChargeStop()
{
    LIFT_STUB(0x78290);
}

// 0x78430
bool StopChargeJob::responseChargeStop(void*)
{
    LIFT_STUB(0x78430);
}

// 0x78790
bool StopChargeJob::expireChargeStop()
{
    LIFT_STUB(0x78790);
}
