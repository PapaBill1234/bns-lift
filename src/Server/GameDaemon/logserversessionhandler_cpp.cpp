// logserversessionhandler_cpp.cpp: logserversessionhandler.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "logserversessionhandler.h"
#include "logserver.h"
#include "LiftStub.h"

// 0x6d9010
bool __cdecl LogServerSessionHandler::HandleVersionNotifyPacket(::LogServer *, ::Packet const *)
{
    LIFT_STUB(0x6d9010);
}

// 0x6d91f0
bool __cdecl LogServerSessionHandler::HandleInitAckPacket(::LogServer *, ::Packet const *)
{
    LIFT_STUB(0x6d91f0);
}

// 0x6d9370
bool __cdecl LogServerSessionHandler::HandlePingAckPacket(::LogServer *, ::Packet const *)
{
    LIFT_STUB(0x6d9370);
}

// 0x6d93f0
bool __cdecl LogServerSessionHandler::HandleControlRequeryNotifyPacket(::LogServer *, ::Packet const *)
{
    LIFT_STUB(0x6d93f0);
}
