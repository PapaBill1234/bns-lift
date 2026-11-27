// gametran_h.cpp: gametran.h (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "gametran.h"
#include "user.h"
#include "LiftStub.h"

// 0x27e10
__cdecl GameTran::~GameTran(void)
{
    LIFT_STUB(0x27e10);
}

// 0x27e50
bool __cdecl GameTran::run(int, void *)
{
    LIFT_STUB(0x27e50);
}

// 0x27e60
__cdecl UserTran::UserTran(::User *)
{
    LIFT_STUB(0x27e60);
}

// 0x27ef0
__cdecl UserTran::~UserTran(void)
{
    LIFT_STUB(0x27ef0);
}

// 0x1105e0
__cdecl SessionTran::SessionTran(::Session *)
{
    LIFT_STUB(0x1105e0);
}

// 0x110670
__cdecl SessionTran::~SessionTran(void)
{
    LIFT_STUB(0x110670);
}
