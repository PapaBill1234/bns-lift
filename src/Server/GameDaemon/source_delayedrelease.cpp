// source_delayedrelease.cpp: delayedrelease.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "delayedrelease_gd.h"
#include "leadtheballmanager.h"
#include "LiftStub.h"

// 0x6a11d0 DelayedRelease::DelayedRelease: LIFT: no body in wave 0 (shared class DelayedRelease has another form or the change needs codegen (W1, pattern 35)).

// 0x6a16d0
bool __cdecl DelayedDelete::Add(__int64, bool (__cdecl *)(void *), void (__cdecl *)(void *), void *)
{
    LIFT_STUB(0x6a16d0);
}

// 0x6a17c0
void __cdecl DelayedDelete::Delete(__int64, int, bool, bool)
{
    LIFT_STUB(0x6a17c0);
}

// 0x6a1960
void __cdecl DelayedDelete::Cleanup(void)
{
    LIFT_STUB(0x6a1960);
}

// 0x6a19d0
void __cdecl DelayedDelete::deleteNode(::DelayedDelete::Node *)
{
    LIFT_STUB(0x6a19d0);
}

// 0x6a1a50
bool __cdecl DeleteEvent::HandleEvent(::EventContext *, unsigned long)
{
    LIFT_STUB(0x6a1a50);
}
