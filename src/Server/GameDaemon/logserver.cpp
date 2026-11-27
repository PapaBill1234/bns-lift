// logserver.cpp: logserver.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "logserver.h"
#include "LiftStub.h"

// 0x6ba5a0
__cdecl LogServer::~LogServer(void)
{
    LIFT_STUB(0x6ba5a0);
}

// 0x6ba6b0
bool __cdecl LogServer::Initialize(bool, unsigned __int64)
{
    LIFT_STUB(0x6ba6b0);
}

// 0x6ba780
bool __cdecl LogServer::Connect(unsigned long, unsigned short)
{
    LIFT_STUB(0x6ba780);
}

// 0x6ba7a0
void __cdecl LogServer::Close(void)
{
    LIFT_STUB(0x6ba7a0);
}

// 0x6ba870
void __cdecl LogServer::ClearLogData(void)
{
    LIFT_STUB(0x6ba870);
}

// 0x6ba900
bool __cdecl LogServer::AsyncSend(void)
{
    LIFT_STUB(0x6ba900);
}

// 0x6bab30
bool __cdecl LogServer::SendComplete(void)
{
    LIFT_STUB(0x6bab30);
}

// 0x6bad70
bool __cdecl LogServer::RecvComplete(void)
{
    LIFT_STUB(0x6bad70);
}

// 0x6baf30
bool __cdecl LogServer::waitComplete(void)
{
    LIFT_STUB(0x6baf30);
}

// 0x6bb020
bool __cdecl LogServer::AsyncRecv(void)
{
    LIFT_STUB(0x6bb020);
}

// 0x6bb0a0
bool __cdecl LogServer::HandlePacket(::Packet const *)
{
    LIFT_STUB(0x6bb0a0);
}
