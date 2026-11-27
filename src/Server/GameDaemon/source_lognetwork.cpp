// source_lognetwork.cpp: lognetwork.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "lognetwork.h"
#include "LiftStub.h"

// 0x6a07c0
::LogNetwork * __cdecl LogNetwork::Instance(void)
{
    LIFT_STUB(0x6a07c0);
}

// 0x6a0870
void __cdecl LogNetwork::Stop(void)
{
    LIFT_STUB(0x6a0870);
}

// 0x6a09d0
bool __cdecl LogNetwork::AddSession(::Session const *)
{
    LIFT_STUB(0x6a09d0);
}

// 0x6a0c90
void __cdecl LogNetwork::RemoveSession(::Session const *)
{
    LIFT_STUB(0x6a0c90);
}

// 0x6a0e30
void __cdecl LogNetwork::write(::LogBuffer const *)
{
    LIFT_STUB(0x6a0e30);
}
