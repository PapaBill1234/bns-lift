// include_packet.cpp: packet.h (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "GameDaemonFwd.h"
#include "../BloodLib/include/Packet.h"
#include "../BloodLib/include/PacketUtil.h"
#include "LiftStub.h"

// 0xac70
// LIFT: round 2 review reject (P2_cc: build jns, original js). A later card lifts it.
void __cdecl Packet::IncRepeatCount(::RepeatPacketComposer *rpc)
{
    LIFT_STUB(0xac70);
}

// 0xe3c0 Packet::GetFreeBody: LIFT: no body in wave 0 (shared class Packet has another form or the change needs codegen (W1, pattern 35)).
