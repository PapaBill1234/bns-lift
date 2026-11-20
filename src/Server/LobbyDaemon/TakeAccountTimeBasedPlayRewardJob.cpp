// TakeAccountTimeBasedPlayRewardJob.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "TakeAccountTimeBasedPlayRewardJob.h"
#include "LiftStub.h"

// 0x788a0
LobbyJobDef const* TakeAccountTimeBasedPlayRewardJob::GetDefinition() const
{
    LIFT_STUB(0x788a0);
}

// 0x788b0
void TakeAccountTimeBasedPlayRewardJob::deallocate_me(void*, wchar_t const*, int)
{
    LIFT_STUB(0x788b0);
}

// 0x78900
void* TakeAccountTimeBasedPlayRewardJob::_vtbl()
{
    LIFT_STUB(0x78900);
}

// 0x789d0
bool TakeAccountTimeBasedPlayRewardJob::work(int, void*)
{
    LIFT_STUB(0x789d0);
}

// 0x78a50
bool TakeAccountTimeBasedPlayRewardJob::init(TakeAccountTimeBasedPlayRewardReqParam*)
{
    LIFT_STUB(0x78a50);
}

// 0x78ec0
bool TakeAccountTimeBasedPlayRewardJob::takeAccountTimeBasedPlayRewardReq()
{
    LIFT_STUB(0x78ec0);
}

// 0x79220
bool TakeAccountTimeBasedPlayRewardJob::takeAccountTimeBasedPlayRewardResponse(void*)
{
    LIFT_STUB(0x79220);
}

// 0x79a00
bool TakeAccountTimeBasedPlayRewardJob::takeAccountTimeBasedPlayRewardExpire()
{
    LIFT_STUB(0x79a00);
}

// 0x79b30
void TakeAccountTimeBasedPlayRewardJob::sendOk(UserPromotionReward&, short)
{
    LIFT_STUB(0x79b30);
}

// 0x79eb0
void TakeAccountTimeBasedPlayRewardJob::sendFail(short, int)
{
    LIFT_STUB(0x79eb0);
}
