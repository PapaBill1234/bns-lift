// StartChargeJob.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "StartChargeJob.h"
#include "LiftStub.h"

// 0x75570
LobbyJobDef const* StartChargeJob::GetDefinition() const
{
    LIFT_STUB(0x75570);
}

// 0x75580
void StartChargeJob::deallocate_me(void*, wchar_t const*, int)
{
    LIFT_STUB(0x75580);
}

// 0x755d0
void* StartChargeJob::_vtbl()
{
    LIFT_STUB(0x755d0);
}

// 0x756a0
bool StartChargeJob::Initialize(GamedChannel*, unsigned long long, unsigned long long)
{
    LIFT_STUB(0x756a0);
}

// 0x757b0
bool StartChargeJob::work(int, void*)
{
    LIFT_STUB(0x757b0);
}

// 0x75830
bool StartChargeJob::init()
{
    LIFT_STUB(0x75830);
}

// 0x75a60
bool StartChargeJob::requestStartCharge()
{
    LIFT_STUB(0x75a60);
}

// 0x75c10
bool StartChargeJob::responseStartCharge(void*)
{
    LIFT_STUB(0x75c10);
}

// 0x76150
bool StartChargeJob::expireStartCharge()
{
    LIFT_STUB(0x76150);
}
