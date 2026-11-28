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

#pragma comment(linker, "/INCLUDE:?DecomposeV@PacketConcatenateBuffer@@QEAA_NHPEAD@Z")  // LIFT: dead-strip keep (no live caller yet)

static wchar_t const PACKETUTIL_FILE[] = L"source\\PacketUtil.cpp";

// 0x693240
bool __cdecl PacketConcatenateBuffer::DecomposeV(int n, char *args)
{
    if (buffer == nullptr || static_cast<int>(decomposer.offset) >= size)
    {
        Log::Write(Log::LT_ERROR, PACKETUTIL_FILE, 375, L"== CRASH == ASSERT CRASH");
        AlertSender::Write(PACKETUTIL_FILE, 375, L"== CRASH == ASSERT CRASH");
        CrashHandler::MakeCrash("source\\PacketUtil.cpp", 375, L"");
    }
    unsigned int offset = decomposer.offset;
    unsigned short used = PacketBuffer::Decompose(&buffer[offset], size - offset, decomposer.CurrentFormat(),
                                                  static_cast<unsigned long long>(n), args);
    decomposer.index += n;
    decomposer.offset += used;
    return true;
}

// 0x693310 PacketConcatenateBuffer::copy: LIFT: no body in wave 0 (shared class PacketConcatenateBuffer has another form or the change needs codegen (W1, pattern 35)).
