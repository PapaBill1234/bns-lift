// source_packetutil.cpp: packetutil.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "GameDaemonFwd.h"
#include "../BloodLib/include/PacketUtil.h"
#include "../BloodLib/include/AlertSender.h"
#include "../BloodLib/include/CrashHandler.h"
#include "../BloodLib/include/Log.h"
#include "../BloodLib/include/PacketBuffer.h"
#include "LiftStub.h"

// 0x6922a0 PacketFormatIterator::skipRepeatFormat: LIFT: no body in wave 0 (shared class PacketFormatIterator has another form or the change needs codegen (W1, pattern 35)).

// 0x692840
void __cdecl RepeatPacketComposer::PushInnerPacket(::Packet *, char const *)
{
    LIFT_STUB(0x692840);
}

// 0x692960
void __cdecl RepeatPacketComposer::PopInnerPacket(::Packet *)
{
    LIFT_STUB(0x692960);
}

// 0x692bb0 RepeatPacketComposer::skipRepeatFormat: LIFT: no body in wave 0 (shared class RepeatPacketComposer has another form or the change needs codegen (W1, pattern 35)).

// 0x692cf0 RepeatPacketDecomposer::PushRepeatCount: LIFT: no body in wave 0 (shared class RepeatPacketDecomposer has another form or the change needs codegen (W1, pattern 35)).

// 0x692e10 RepeatPacketDecomposer::PushRepeatCount: LIFT: no body in wave 0 (shared class RepeatPacketDecomposer has another form or the change needs codegen (W1, pattern 35)).

// 0x693240
// LIFT: round 2 review reject (P2_cc: build jae, original jbe; P3_imm: original has 4 times 0x8). A later card lifts it.
bool __cdecl PacketConcatenateBuffer::DecomposeV(int n, char *args)
{
    LIFT_STUB(0x693240);
}

// 0x693310 PacketConcatenateBuffer::copy: LIFT: no body in wave 0 (shared class PacketConcatenateBuffer has another form or the change needs codegen (W1, pattern 35)).
