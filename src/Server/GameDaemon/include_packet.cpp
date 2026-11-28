// include_packet.cpp: packet.h (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "GameDaemonFwd.h"
#include "../BloodLib/include/Packet.h"
#include "../BloodLib/include/PacketUtil.h"
#include "LiftStub.h"

#pragma comment(linker, "/INCLUDE:?IncRepeatCount@Packet@@QEAAXPEAVRepeatPacketComposer@@@Z")  // LIFT: dead-strip keep (no live caller yet)

// 0xac70
// LIFT: the HR body works on the composer in rcx (start[top], subTop, counts[top]). It is the code of
// RepeatPacketComposer::IncRepeatCount (inline in PacketUtil.h), folded under the Packet name.
void __cdecl Packet::IncRepeatCount(::RepeatPacketComposer *rpc)
{
    rpc->IncRepeatCount();
}

// 0xe3c0 Packet::GetFreeBody: LIFT: no body in wave 0 (shared class Packet has another form or the change needs codegen (W1, pattern 35)).
