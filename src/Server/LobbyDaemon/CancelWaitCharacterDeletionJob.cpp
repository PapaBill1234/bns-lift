// CancelWaitCharacterDeletionJob.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "CancelWaitCharacterDeletionJob.h"
#include "LiftStub.h"

// 0x18890
LobbyJobDef const* CancelWaitCharacterDeletionJob::GetDefinition() const
{
    LIFT_STUB(0x18890);
}

// 0x188a0
void CancelWaitCharacterDeletionJob::deallocate_me(void*, wchar_t const*, int)
{
    LIFT_STUB(0x188a0);
}

// 0x188f0
void* CancelWaitCharacterDeletionJob::_vtbl()
{
    LIFT_STUB(0x188f0);
}

// 0x18970
CancelWaitCharacterDeletionJob::CancelWaitCharacterDeletionJob(CliSession*)
{
    LIFT_STUB(0x18970);
}

// 0x189e0
CancelWaitCharacterDeletionJob::~CancelWaitCharacterDeletionJob()
{
    LIFT_STUB(0x189e0);
}

// 0x18a80
bool CancelWaitCharacterDeletionJob::work(int, void*)
{
    LIFT_STUB(0x18a80);
}

// 0x18b40
bool CancelWaitCharacterDeletionJob::init(CancelWaitCharacterDeletionReqParam*)
{
    LIFT_STUB(0x18b40);
}

// 0x196f0
bool CancelWaitCharacterDeletionJob::restore()
{
    LIFT_STUB(0x196f0);
}

// 0x19ad0
bool CancelWaitCharacterDeletionJob::restoreCharacterReq()
{
    LIFT_STUB(0x19ad0);
}

// 0x19f30
bool CancelWaitCharacterDeletionJob::restoreCharacterOk()
{
    LIFT_STUB(0x19f30);
}

// 0x1a3b0
bool CancelWaitCharacterDeletionJob::restoreCharacterFail(short*)
{
    LIFT_STUB(0x1a3b0);
}

// 0x1a860
bool CancelWaitCharacterDeletionJob::restoreCharacterExpire()
{
    LIFT_STUB(0x1a860);
}
