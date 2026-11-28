// fragmentpacket_h.cpp: fragmentpacket.h (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "fragmentpacket_gd.h"
#include "../Packet/FragmentPacket.h"
#include "LiftStub.h"

// 0xb370 FragmentPacket::FreeSize: LIFT: no body in wave 0 (shared class FragmentPacket has another form or the change needs codegen (W1, pattern 35)).

#pragma comment(linker, "/INCLUDE:?FreeBody@FragmentPacket@@QEAAPEBDXZ")  // LIFT: dead-strip keep (no live caller yet)

// 0x10d40
char const * __cdecl FragmentPacket::FreeBody(void)
{
    return packet.GetFreeBody();
}

// 0x271c0
void __cdecl FragmentPacket::StartInnerPacket(char const *)
{
    LIFT_STUB(0x271c0);
}
