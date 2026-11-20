// RecoverPcJob.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "RecoverPcJob.h"
#include "LiftStub.h"

// 0x64e50
LobbyJobDef const* RecoverPcJob::GetDefinition() const
{
    LIFT_STUB(0x64e50);
}

// 0x64e60
void RecoverPcJob::deallocate_me(void*, wchar_t const*, int)
{
    LIFT_STUB(0x64e60);
}

// 0x64eb0
void* RecoverPcJob::_vtbl()
{
    LIFT_STUB(0x64eb0);
}

// 0x64f30
RecoverPcJob::RecoverPcJob(CliSession*)
{
    LIFT_STUB(0x64f30);
}

// 0x64fa0
RecoverPcJob::~RecoverPcJob()
{
    LIFT_STUB(0x64fa0);
}

// 0x65040
bool RecoverPcJob::Initialize(LobbyGateChannel*, id128 const&)
{
    LIFT_STUB(0x65040);
}

// 0x65260
bool RecoverPcJob::work(int, void*)
{
    LIFT_STUB(0x65260);
}

// 0x652f0
bool RecoverPcJob::init()
{
    LIFT_STUB(0x652f0);
}

// 0x65b40
bool RecoverPcJob::restoreGameWorldPcReq()
{
    LIFT_STUB(0x65b40);
}

// 0x65d30
bool RecoverPcJob::restoreGameWorldPcOk()
{
    LIFT_STUB(0x65d30);
}

// 0x66070
bool RecoverPcJob::restoreGameWorldPcFail(short*)
{
    LIFT_STUB(0x66070);
}

// 0x664f0
bool RecoverPcJob::restoreGameWorldPcExpired()
{
    LIFT_STUB(0x664f0);
}

// 0x66600
bool RecoverPcJob::__restoreStuckPc(Character*, short&)
{
    LIFT_STUB(0x66600);
}
