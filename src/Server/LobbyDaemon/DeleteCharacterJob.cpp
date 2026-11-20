// DeleteCharacterJob.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "DeleteCharacterJob.h"
#include "LiftStub.h"

// 0x45040
LobbyJobDef const* DeleteCharacterJob::GetDefinition() const
{
    LIFT_STUB(0x45040);
}

// 0x45050
void DeleteCharacterJob::deallocate_me(void*, wchar_t const*, int)
{
    LIFT_STUB(0x45050);
}

// 0x450a0
void* DeleteCharacterJob::_vtbl()
{
    LIFT_STUB(0x450a0);
}

// 0x45120
DeleteCharacterJob::DeleteCharacterJob(CliSession*)
{
    LIFT_STUB(0x45120);
}

// 0x451a0
DeleteCharacterJob::~DeleteCharacterJob()
{
    LIFT_STUB(0x451a0);
}

// 0x45240
bool DeleteCharacterJob::work(int, void*)
{
    LIFT_STUB(0x45240);
}

// 0x453a0
bool DeleteCharacterJob::init(int, void*)
{
    LIFT_STUB(0x453a0);
}

// 0x46440
bool DeleteCharacterJob::checkSecondPasswordStatus()
{
    LIFT_STUB(0x46440);
}

// 0x46760
bool DeleteCharacterJob::checkSecondPasswordStatusResponse(void*)
{
    LIFT_STUB(0x46760);
}

// 0x46d20
bool DeleteCharacterJob::checkSecondPasswordStatusExpire()
{
    LIFT_STUB(0x46d20);
}

// 0x46ed0
bool DeleteCharacterJob::checkSecondPasswordVerified()
{
    LIFT_STUB(0x46ed0);
}

// 0x47200
bool DeleteCharacterJob::checkSecondPasswordVerifiedResponse(void*)
{
    LIFT_STUB(0x47200);
}

// 0x47560
bool DeleteCharacterJob::checkSecondPasswordVerifiedExpire()
{
    LIFT_STUB(0x47560);
}

// 0x47710
bool DeleteCharacterJob::getCharacterGoodsReq()
{
    LIFT_STUB(0x47710);
}

// 0x47ac0
bool DeleteCharacterJob::getCharacterGoodsCountOk(void*)
{
    LIFT_STUB(0x47ac0);
}

// 0x47d80
bool DeleteCharacterJob::getCharacterGoodsCountFail(void*)
{
    LIFT_STUB(0x47d80);
}

// 0x47fa0
bool DeleteCharacterJob::getCharacterGoodsCountExpire()
{
    LIFT_STUB(0x47fa0);
}

// 0x482b0
bool DeleteCharacterJob::deleteReq()
{
    LIFT_STUB(0x482b0);
}

// 0x48890
bool DeleteCharacterJob::deleteOk(DeleteCharacterOkParam*)
{
    LIFT_STUB(0x48890);
}

// 0x48a10
bool DeleteCharacterJob::deleteFail(void*)
{
    LIFT_STUB(0x48a10);
}

// 0x49090
bool DeleteCharacterJob::deleteExpire()
{
    LIFT_STUB(0x49090);
}

// 0x493a0
bool DeleteCharacterJob::directDelete()
{
    LIFT_STUB(0x493a0);
}

// 0x49770
bool DeleteCharacterJob::scheduleDelete()
{
    LIFT_STUB(0x49770);
}
