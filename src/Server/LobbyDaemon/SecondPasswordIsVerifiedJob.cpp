// SecondPasswordIsVerifiedJob.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "SecondPasswordIsVerifiedJob.h"
#include "LiftStub.h"

// 0x72110
LobbyJobDef const* SecondPasswordIsVerifiedJob::GetDefinition() const
{
    LIFT_STUB(0x72110);
}

// 0x72120
void SecondPasswordIsVerifiedJob::deallocate_me(void*, wchar_t const*, int)
{
    LIFT_STUB(0x72120);
}

// 0x72170
void* SecondPasswordIsVerifiedJob::_vtbl()
{
    LIFT_STUB(0x72170);
}

// 0x72240
bool SecondPasswordIsVerifiedJob::work(int, void*)
{
    LIFT_STUB(0x72240);
}

// 0x722c0
bool SecondPasswordIsVerifiedJob::init(void*)
{
    LIFT_STUB(0x722c0);
}

// 0x72640
bool SecondPasswordIsVerifiedJob::requestIsVerified()
{
    LIFT_STUB(0x72640);
}

// 0x728d0
bool SecondPasswordIsVerifiedJob::responseIsVerified(void*)
{
    LIFT_STUB(0x728d0);
}

// 0x72bf0
bool SecondPasswordIsVerifiedJob::expireIsVerified()
{
    LIFT_STUB(0x72bf0);
}
