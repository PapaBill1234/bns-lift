// logarchivesession.cpp: logarchivesession.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "logarchivesession.h"
#include "LiftStub.h"

// 0x6b9d00
__cdecl LogArchiveSession::~LogArchiveSession(void)
{
    LIFT_STUB(0x6b9d00);
}

// 0x6b9d60
bool __cdecl LogArchiveSession::Connect(unsigned long, unsigned short)
{
    LIFT_STUB(0x6b9d60);
}

// 0x6b9fd0
bool __cdecl LogArchiveSession::Send(::Packet const *)
{
    LIFT_STUB(0x6b9fd0);
}

// 0x6ba1f0
bool __cdecl LogArchiveSession::Recv(::Packet *)
{
    LIFT_STUB(0x6ba1f0);
}

// 0x6ba300
int __cdecl LogArchiveSession::recv(char *, int, int)
{
    LIFT_STUB(0x6ba300);
}

// 0x6ba510
void __cdecl LogArchiveSession::Close(void)
{
    LIFT_STUB(0x6ba510);
}
