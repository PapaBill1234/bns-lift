// Packet.obj (SmartCouponDaemon PDB).
#include "Packet.h"
#include <stdarg.h>
#include "AlertSender.h"
#include "CrashHandler.h"
#include "Log.h"
#include "PacketBuffer.h"

static wchar_t const PACKET_FILE[] = L"source\\Packet.cpp";

// Inlined crash macro.
#define PACKET_ASSERT_CRASH(line)                                                  \
    do                                                                             \
    {                                                                              \
        Log::Write(Log::LT_ERROR, PACKET_FILE, line, L"== CRASH == ASSERT CRASH"); \
        AlertSender::Write(PACKET_FILE, line, L"== CRASH == ASSERT CRASH");       \
        CrashHandler::MakeCrash("source\\Packet.cpp", line, L"");                  \
    } while (0)

// 0x1B450 (SmartCouponDaemon)
Packet::~Packet()
{
    Clear();
}

// 0x1B460 (SmartCouponDaemon)
void Packet::Clear()
{
    for (PacketBuffer* pktbuf = ListHead; pktbuf != nullptr; pktbuf = ListHead)
    {
        ListHead = pktbuf->Next;
        pktbuf->removeReferenceCount(PACKET_FILE, 40);
    }
    ListTail = nullptr;
    ListHead = nullptr;
    CurHeader = nullptr;
    if (Splitter != nullptr)
        Splitter->Clear();
}

// 0x1B600 (SmartCouponDaemon)
char const* Packet::Allocate()
{
    Header* prevHeader = CurHeader;
    PacketBuffer* pktbuf = PacketBufferAllocator::_Local->allocate();
    if (ListHead != nullptr)
        ListTail->Next = pktbuf;
    else
        ListHead = pktbuf;
    ListTail = pktbuf;
    CurHeader = reinterpret_cast<Header*>(&pktbuf->Buffer[8]);
    CurHeader->size = 2;
    if (Splitter != nullptr && !Splitter->AddBuffer(prevHeader, CurHeader))
        return nullptr;
    return reinterpret_cast<char const*>(CurHeader) + CurHeader->size;
}

// 0x1B6A0 (SmartCouponDaemon)
unsigned short Packet::Compose(char const* format, ...)
{
    va_list args;
    va_start(args, format);
    if (format == nullptr || CurHeader == nullptr)
        PACKET_ASSERT_CRASH(113);
    unsigned short size = PacketBuffer::Compose(reinterpret_cast<char*>(CurHeader) + CurHeader->size,
                                                4000 - CurHeader->size, format,
                                                static_cast<unsigned long long>(-1), args);
    AddSize(size);
    va_end(args);
    return size;
}

// 0x1B750 (SmartCouponDaemon)
void Packet::AddSize(short size)
{
    if (CurHeader == nullptr || static_cast<unsigned short>(4000 - CurHeader->size) < size)
        PACKET_ASSERT_CRASH(307);
    CurHeader->size += size;
}

// 0x1B7F0 (SmartCouponDaemon)
unsigned short Packet::Decompose(char const* format, ...) const
{
    va_list args;
    va_start(args, format);
    if (format == nullptr || CurHeader == nullptr)
        PACKET_ASSERT_CRASH(486);
    unsigned short size = PacketBuffer::Decompose(reinterpret_cast<char const*>(CurHeader + 1),
                                                  CurHeader->size - 2, format,
                                                  static_cast<unsigned long long>(-1), args);
    va_end(args);
    return size;
}
