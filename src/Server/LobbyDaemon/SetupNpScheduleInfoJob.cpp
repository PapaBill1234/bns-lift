// SetupNpScheduleInfoJob.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "SetupNpScheduleInfoJob.h"
#include "LiftStub.h"

// 0x72cf0
LobbyJobDef const* SetupNpScheduleInfoJob::GetDefinition() const
{
    LIFT_STUB(0x72cf0);
}

// 0x72d00
void SetupNpScheduleInfoJob::deallocate_me(void*, wchar_t const*, int)
{
    LIFT_STUB(0x72d00);
}

// 0x72d90
SetupNpScheduleInfoJob::SetupNpScheduleInfoJob()
{
    LIFT_STUB(0x72d90);
}

// 0x72e40
SetupNpScheduleInfoJob::~SetupNpScheduleInfoJob()
{
    LIFT_STUB(0x72e40);
}

// 0x72eb0
bool SetupNpScheduleInfoJob::work(int, void*)
{
    LIFT_STUB(0x72eb0);
}

// 0x72ff0
bool SetupNpScheduleInfoJob::tryListCurrentPromotions(void*)
{
    LIFT_STUB(0x72ff0);
}

// 0x73160
bool SetupNpScheduleInfoJob::listCurrentPromotionsAck(void*)
{
    LIFT_STUB(0x73160);
}

// 0x733e0
bool SetupNpScheduleInfoJob::tryGetPromotionPolicy(void*)
{
    LIFT_STUB(0x733e0);
}

// 0x73630
bool SetupNpScheduleInfoJob::getPromotionPolicyAck(void*)
{
    LIFT_STUB(0x73630);
}
