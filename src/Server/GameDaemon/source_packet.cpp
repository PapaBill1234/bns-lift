// source_packet.cpp: packet.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "GameDaemonFwd.h"
#include "../BloodLib/include/Packet.h"
#include "LiftStub.h"

// 0x6909a0 Packet::Compose: LIFT: no body in wave 0 (shared class Packet has another form or the change needs codegen (W1, pattern 35)).

// 0x6910a0
bool __cdecl Packet::Reserve(::PacketComposer const *, ::Packet::VarData *)
{
    LIFT_STUB(0x6910a0);
}

// 0x6912c0
void __cdecl Packet::GrowAdd(void const *, short)
{
    LIFT_STUB(0x6912c0);
}

// 0x691450 Packet::AddSize: LIFT: no body in wave 0 (shared class Packet has another form or the change needs codegen (W1, pattern 35)).

// 0x6915e0
void __cdecl Packet::Restore(short)
{
    LIFT_STUB(0x6915e0);
}

// 0x691ef0
unsigned short __cdecl Packet::DecomposeV(::PacketDecomposer *, int, char *) const
{
    LIFT_STUB(0x691ef0);
}

// 0x692220
void __cdecl Packet::setRecvBuffer(char const *)
{
    LIFT_STUB(0x692220);
}
