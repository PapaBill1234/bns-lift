// ActivateGradeJob.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "ActivateGradeJob.h"
#include "LiftStub.h"

// 0xbac0
LobbyJobDef const* ActivateGradeJob::GetDefinition() const
{
    LIFT_STUB(0xbac0);
}

// 0xbad0
void ActivateGradeJob::deallocate_me(void*, wchar_t const*, int)
{
    LIFT_STUB(0xbad0);
}

// 0xbb20
void* ActivateGradeJob::_vtbl()
{
    LIFT_STUB(0xbb20);
}

// 0xbba0
ActivateGradeJob::ActivateGradeJob(CliSession*)
{
    LIFT_STUB(0xbba0);
}

// 0xbc00
ActivateGradeJob::~ActivateGradeJob()
{
    LIFT_STUB(0xbc00);
}

// 0xbc70
bool ActivateGradeJob::work(int, void*)
{
    LIFT_STUB(0xbc70);
}

// 0xbd00
bool ActivateGradeJob::initFromLobbyGate(LobbyGate_ActivateGradeReqParam*)
{
    LIFT_STUB(0xbd00);
}

// 0xc1a0
bool ActivateGradeJob::initFromGame(Game_ActivateGradeReqParam*)
{
    LIFT_STUB(0xc1a0);
}

// 0xc670
bool ActivateGradeJob::activateGradeReq()
{
    LIFT_STUB(0xc670);
}

// 0xca10
bool ActivateGradeJob::activateGradeResponse(void*)
{
    LIFT_STUB(0xca10);
}

// 0xcf50
bool ActivateGradeJob::activateGradeExpire()
{
    LIFT_STUB(0xcf50);
}

// 0xd0a0
void ActivateGradeJob::sendFail(int)
{
    LIFT_STUB(0xd0a0);
}
