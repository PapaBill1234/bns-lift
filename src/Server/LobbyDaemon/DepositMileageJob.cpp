// DepositMileageJob.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "DepositMileageJob.h"
#include "LiftStub.h"

// 0x49b40
LobbyJobDef const* DepositMileageJob::GetDefinition() const
{
    LIFT_STUB(0x49b40);
}

// 0x49b50
void DepositMileageJob::deallocate_me(void*, wchar_t const*, int)
{
    LIFT_STUB(0x49b50);
}

// 0x49c90
DepositMileageJob::~DepositMileageJob()
{
    LIFT_STUB(0x49c90);
}

// 0x49d20
bool DepositMileageJob::work(int, void*)
{
    LIFT_STUB(0x49d20);
}

// 0x49da0
bool DepositMileageJob::init(void*)
{
    LIFT_STUB(0x49da0);
}

// 0x4a3e0
bool DepositMileageJob::depositReq()
{
    LIFT_STUB(0x4a3e0);
}

// 0x4aa40
bool DepositMileageJob::depositAck(void*)
{
    LIFT_STUB(0x4aa40);
}

// 0x4aee0
bool DepositMileageJob::depositExpire()
{
    LIFT_STUB(0x4aee0);
}
