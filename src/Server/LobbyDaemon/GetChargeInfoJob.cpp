// GetChargeInfoJob.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "GetChargeInfoJob.h"
#include "LiftStub.h"

// 0x50550
LobbyJobDef const* GetChargeInfoJob::GetDefinition() const
{
    LIFT_STUB(0x50550);
}

// 0x50560
void GetChargeInfoJob::deallocate_me(void*, wchar_t const*, int)
{
    LIFT_STUB(0x50560);
}

// 0x505b0
void* GetChargeInfoJob::_vtbl()
{
    LIFT_STUB(0x505b0);
}

// 0x50630
GetChargeInfoJob::GetChargeInfoJob(CliSession*, LobbyGateChannel*)
{
    LIFT_STUB(0x50630);
}

// 0x506e0
bool GetChargeInfoJob::work(int, void*)
{
    LIFT_STUB(0x506e0);
}

// 0x50760
bool GetChargeInfoJob::init()
{
    LIFT_STUB(0x50760);
}

// 0x50970
bool GetChargeInfoJob::requestChargeGetInfo()
{
    LIFT_STUB(0x50970);
}

// 0x50c30
bool GetChargeInfoJob::responseChargeGetInfo(void*)
{
    LIFT_STUB(0x50c30);
}

// 0x51360
bool GetChargeInfoJob::expireChargeGetInfo()
{
    LIFT_STUB(0x51360);
}
