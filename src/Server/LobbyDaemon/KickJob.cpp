// KickJob.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "KickJob.h"
#include "LiftStub.h"

// 0x861a0
LobbyJobDef const* KickJob::GetDefinition() const
{
    LIFT_STUB(0x861a0);
}

// 0x861b0
void KickJob::deallocate_me(void*, wchar_t const*, int)
{
    LIFT_STUB(0x861b0);
}

// 0x86200
void* KickJob::_vtbl()
{
    LIFT_STUB(0x86200);
}

// 0x862f0
KickJob::~KickJob()
{
    LIFT_STUB(0x862f0);
}

// 0x86380
bool KickJob::work(int, void*)
{
    LIFT_STUB(0x86380);
}

// 0x86460
bool KickJob::init(int, void*)
{
    LIFT_STUB(0x86460);
}

// 0x865e0
bool KickJob::kick()
{
    LIFT_STUB(0x865e0);
}

// 0x87010
bool KickJob::worldKickReq()
{
    LIFT_STUB(0x87010);
}

// 0x872e0
bool KickJob::worldKickOk()
{
    LIFT_STUB(0x872e0);
}

// 0x87420
bool KickJob::worldKickFail(short)
{
    LIFT_STUB(0x87420);
}

// 0x87580
bool KickJob::worldKickExpire()
{
    LIFT_STUB(0x87580);
}

// 0x876c0
void NPDemander::Response(int)
{
    LIFT_STUB(0x876c0);
}

// 0x87750
void ManageDemander::Response(int)
{
    LIFT_STUB(0x87750);
}
