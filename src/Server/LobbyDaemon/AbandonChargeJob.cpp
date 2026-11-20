// AbandonChargeJob.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "AbandonChargeJob.h"
#include "LiftStub.h"

// 0x4f70
LobbyJobDef const* AbandonChargeJob::GetDefinition() const
{
    LIFT_STUB(0x4f70);
}

// 0x4f80
void AbandonChargeJob::deallocate_me(void*, wchar_t const*, int)
{
    LIFT_STUB(0x4f80);
}

// 0x5020
void* AbandonChargeJob::_vtbl()
{
    LIFT_STUB(0x5020);
}

// 0x50d0
bool AbandonChargeJob::Initialize(unsigned long long, wchar_t const*)
{
    LIFT_STUB(0x50d0);
}

// 0x5220
bool AbandonChargeJob::work(int, void*)
{
    LIFT_STUB(0x5220);
}

// 0x52a0
bool AbandonChargeJob::init()
{
    LIFT_STUB(0x52a0);
}

// 0x54a0
bool AbandonChargeJob::requestChargeAbandon()
{
    LIFT_STUB(0x54a0);
}

// 0x5690
bool AbandonChargeJob::responseChargeAbandon(void*)
{
    LIFT_STUB(0x5690);
}

// 0x5b10
bool AbandonChargeJob::expireChargeAbandon()
{
    LIFT_STUB(0x5b10);
}
