// logagent.cpp: logagent.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "logagent.h"
#include "LiftStub.h"

#pragma comment(linker, "/INCLUDE:??1LogAgent@@UEAA@XZ")  // LIFT: dead-strip keep (no live caller yet)

// 0x6bb190
// LIFT: the body closes the socket. That is the inlined base destructor ~LogArchiveSession (Close, line 249).
__cdecl LogAgent::~LogAgent(void)
{
}

// 0x6bb200
bool __cdecl LogAgent::HandlePacket(::Packet const *)
{
    LIFT_STUB(0x6bb200);
}
