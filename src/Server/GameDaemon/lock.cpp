// lock.cpp: lock.h (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "lock_gd.h"
#include "accountinventorychannel_gd.h"
#include "LiftStub.h"

// 0x1cbc0 AutoCS::~AutoCS: LIFT: no body in wave 0 (shared class AutoCS has another form or the change needs codegen (W1, pattern 35)).

// 0x1cbd0 AutoCS::Enter: LIFT: no body in wave 0 (shared class AutoCS has another form or the change needs codegen (W1, pattern 35)).

// 0x1cc50 AutoCS::Leave: LIFT: no body in wave 0 (shared class AutoCS has another form or the change needs codegen (W1, pattern 35)).

// 0x18d060
__cdecl AccountInventoryChannelManager::~AccountInventoryChannelManager(void)
{
    LIFT_STUB(0x18d060);
}

// 0x1dc200
__cdecl AutoSRW::~AutoSRW(void)
{
    LIFT_STUB(0x1dc200);
}
