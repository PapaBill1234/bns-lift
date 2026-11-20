// CreateInitialUserNameJob.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "CreateInitialUserNameJob.h"
#include "LiftStub.h"

// 0x2fc20
LobbyJobDef const* CreateInitialUserNameJob::GetDefinition() const
{
    LIFT_STUB(0x2fc20);
}

// 0x2fc30
void CreateInitialUserNameJob::deallocate_me(void*, wchar_t const*, int)
{
    LIFT_STUB(0x2fc30);
}

// 0x2fc80
void* CreateInitialUserNameJob::_vtbl()
{
    LIFT_STUB(0x2fc80);
}

// 0x2fd20
CreateInitialUserNameJob::~CreateInitialUserNameJob()
{
    LIFT_STUB(0x2fd20);
}

// 0x2fda0
bool CreateInitialUserNameJob::work(int, void*)
{
    LIFT_STUB(0x2fda0);
}

// 0x2fe20
bool CreateInitialUserNameJob::init(void*)
{
    LIFT_STUB(0x2fe20);
}

// 0x30660
bool CreateInitialUserNameJob::changeUserNameReq()
{
    LIFT_STUB(0x30660);
}

// 0x30980
bool CreateInitialUserNameJob::changeUserNameAck(void*)
{
    LIFT_STUB(0x30980);
}

// 0x30d90
bool CreateInitialUserNameJob::changeUserNameExpire()
{
    LIFT_STUB(0x30d90);
}
