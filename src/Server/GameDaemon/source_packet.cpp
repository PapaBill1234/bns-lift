// source_packet.cpp: packet.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "GameDaemonFwd.h"
#include "../BloodLib/include/Packet.h"
#include "../BloodLib/include/AlertSender.h"
#include "../BloodLib/include/CrashHandler.h"
#include "../BloodLib/include/Log.h"
#include "LiftStub.h"

// 0x6909a0 Packet::Compose: LIFT: no body in wave 0 (shared class Packet has another form or the change needs codegen (W1, pattern 35)).

// 0x6910a0
bool __cdecl Packet::Reserve(::PacketComposer const *, ::Packet::VarData *)
{
    LIFT_STUB(0x6910a0);
}

#pragma comment(linker, "/INCLUDE:?GrowAdd@Packet@@QEAAXPEBXF@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?Restore@Packet@@QEAAXF@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?setRecvBuffer@Packet@@QEAAXPEBD@Z")  // LIFT: dead-strip keep (no live caller yet)

static wchar_t const PACKET_FILE[] = L"source\\Packet.cpp";

// Inlined crash macro (same form as BloodLib Packet.cpp).
#define PACKET_ASSERT_CRASH(line)                                                  \
    do                                                                             \
    {                                                                              \
        Log::Write(Log::LT_ERROR, PACKET_FILE, line, L"== CRASH == ASSERT CRASH"); \
        AlertSender::Write(PACKET_FILE, line, L"== CRASH == ASSERT CRASH");       \
        CrashHandler::MakeCrash("source\\Packet.cpp", line, L"");                  \
    } while (0)

// 0x6912c0
void __cdecl Packet::GrowAdd(void const *data, short size)
{
    if (size < 0 || (CurHeader != nullptr ? static_cast<unsigned short>(4000 - CurHeader->size) : 0) < size)
        PACKET_ASSERT_CRASH(297);
    if ((CurHeader != nullptr ? static_cast<unsigned short>(4000 - CurHeader->size) : 0) < size)
        Allocate();
    Add(data, size);
}

// 0x691450 Packet::AddSize: LIFT: no body in wave 0 (shared class Packet has another form or the change needs codegen (W1, pattern 35)).

// 0x6915e0
void __cdecl Packet::Restore(short)
{
    // LIFT: the HR body subtracts the constant 19 and ignores the argument (LTCG constant propagation of the only caller).
    if (CurHeader == nullptr || CurHeader->size - 2 < 19)
        PACKET_ASSERT_CRASH(350);
    CurHeader->size -= 19;
}

// 0x691ef0
unsigned short __cdecl Packet::DecomposeV(::PacketDecomposer *, int, char *) const
{
    LIFT_STUB(0x691ef0);
}

// 0x692220
void __cdecl Packet::setRecvBuffer(char const *buffer)
{
    if (buffer == nullptr)
        PACKET_ASSERT_CRASH(626);
    Clear();
    CurHeader = const_cast<Header *>(reinterpret_cast<Header const *>(buffer));
}
