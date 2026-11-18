// PacketUtil.obj (LobbyGate PDB).
#include "PacketUtil.h"
#include <stdarg.h>
#include <string.h>
#include "AlertSender.h"
#include "CrashHandler.h"
#include "Log.h"
#include "Memory.h"
#include "MemoryManager.h"
#include "Packet.h"
#include "PacketBuffer.h"

static wchar_t const PACKETUTIL_FILE[] = L"source\\PacketUtil.cpp";
// LIFT: each exe has its own build path for include\PacketUtil.h. A wrapper .cpp (PacketUtilLobbyGate.cpp,
// PacketUtilPostOfficeDaemon.cpp) can define LIFT_PACKETUTIL_H_PATH before it includes this file. The default is CacheGate.
#ifndef LIFT_PACKETUTIL_H_PATH
#define LIFT_PACKETUTIL_H_PATH \
    "e:\\dailybuild02\\cachegate-common-0.0.348\\depot\\branch\\348nc\\program\\server\\bloodlib\\include\\PacketUtil.h"
#endif
#define LIFT_WIDEN2(x) L##x
#define LIFT_WIDEN(x) LIFT_WIDEN2(x)
static wchar_t const PACKETUTIL_H_FILE[] = LIFT_WIDEN(LIFT_PACKETUTIL_H_PATH);

// Inlined crash macro.
#define PACKETUTIL_ASSERT_CRASH(line)                                                  \
    do                                                                                 \
    {                                                                                  \
        Log::Write(Log::LT_ERROR, PACKETUTIL_FILE, line, L"== CRASH == ASSERT CRASH"); \
        AlertSender::Write(PACKETUTIL_FILE, line, L"== CRASH == ASSERT CRASH");       \
        CrashHandler::MakeCrash("source\\PacketUtil.cpp", line, L"");                  \
    } while (0)

#define PACKETUTIL_H_ASSERT_CRASH(line)                                                  \
    do                                                                                   \
    {                                                                                    \
        Log::Write(Log::LT_ERROR, PACKETUTIL_H_FILE, line, L"== CRASH == ASSERT CRASH"); \
        AlertSender::Write(PACKETUTIL_H_FILE, line, L"== CRASH == ASSERT CRASH");       \
        CrashHandler::MakeCrash(LIFT_PACKETUTIL_H_PATH, line, L"");                                              \
    } while (0)

// ---- PacketFormatIterator (PacketUtil.h inline bodies) ----

// 0x20F0
void PacketFormatIterator::SetFormat(char const* format, int start)
{
    if (format == nullptr || start < 0)
        PACKETUTIL_H_ASSERT_CRASH(52);
    this->format = format;
    index = start;
    len = static_cast<int>(strlen(format));
    if (start >= len)
        PACKETUTIL_H_ASSERT_CRASH(56);
}

// 0x21E0
void PacketFormatIterator::Forward(int index)
{
    this->index += index;
}

// 0x21F0
void PacketFormatIterator::Rewind(int index)
{
    this->index -= index;
}

// 0x2200
char const* PacketFormatIterator::CurrentFormat() const
{
    return &format[index];
}

// 0x2210
int PacketFormatIterator::GetIndex() const
{
    return index;
}

// 0x1B010
void PacketFormatIterator::skipRepeatFormat()
{
    int depth = 1;
    if (format[index - 1] != 'C')
        PACKETUTIL_ASSERT_CRASH(24);
    while (format[index] != '\0')
    {
        char c = format[index];
        if (c == 'C')
            ++depth;
        else if (c == ';')
            --depth;
        ++index;
        if (depth <= 0)
            return;
    }
    PACKETUTIL_ASSERT_CRASH(28);
}

// ---- RepeatPacketComposer ----

// 0x2220
void RepeatPacketComposer::Reset()
{
    index = 0;
    top = -1;
    subTop = -1;
}

// 0x2240
void RepeatPacketComposer::Forward(int index)
{
    if (subTop < 0)
        this->index += index;
    else
        sub[subTop].index += index;
}

// 0x2260
void RepeatPacketComposer::Rewind(int index)
{
    if (subTop < 0)
        this->index -= index;
    else
        sub[subTop].index -= index;
}

// 0x1B110
void RepeatPacketComposer::PushRepeatCount(Packet* packet)
{
    int depth = ++top;
    if (packet == nullptr)
    {
        Log::Write(Log::LT_ERROR, PACKETUTIL_FILE, 49, L"[packet], packet is null pointer");
        PACKETUTIL_ASSERT_CRASH(50);
        return;
    }
    unsigned short freeSize = packet->CurHeader != nullptr
                                  ? static_cast<unsigned short>(4000 - packet->CurHeader->size)
                                  : 0;
    if (freeSize < 2)
    {
        Log::Write(Log::LT_ERROR, PACKETUTIL_FILE, 54,
                   L"[packet], not enough free size in packet, free size:%d, format:%s", freeSize, format);
        PACKETUTIL_ASSERT_CRASH(55);
        return;
    }
    if (depth >= 3)
    {
        Log::Write(Log::LT_ERROR, PACKETUTIL_FILE, 59,
                   L"[packet], too many nested Repeat Format, current depth:%d, format:%s", depth, format);
        return;
    }
    if (subTop >= 0)
    {
        if (sub[subTop].format[sub[subTop].index] != 'C')
        {
            Log::Write(Log::LT_ERROR, PACKETUTIL_FILE, 69,
                       L"[packet], invalid PushRepeatCount call when inner format is not 'C', format:%s, index:%d, innerFormat:%s, innerIndex:%d",
                       format, index, sub[subTop].format, sub[subTop].index);
            PACKETUTIL_ASSERT_CRASH(70);
            return;
        }
    }
    else if (format[index] != 'C')
    {
        Log::Write(Log::LT_ERROR, PACKETUTIL_FILE, 63,
                   L"[packet], invalid PushRepeatCount call when format is not 'C', format:%s, index:%d", format, index);
        PACKETUTIL_ASSERT_CRASH(64);
        return;
    }
    counts[depth] = reinterpret_cast<short*>(reinterpret_cast<char*>(packet->CurHeader) + packet->CurHeader->size);
    if (subTop < 0)
    {
        start[top] = index++;
    }
    else
    {
        start[top] = sub[subTop].index;
        ++sub[subTop].index;
    }
    *counts[top] = 0;
    packet->AddSize(2);
}

// 0x1B3E0
void RepeatPacketComposer::PopRepeatCount()
{
    if (top < 0)
    {
        Log::Write(Log::LT_ERROR, PACKETUTIL_FILE, 89, L"[packet], invalid pop opertion , top:%d", top);
        PACKETUTIL_ASSERT_CRASH(90);
        return;
    }
    if (subTop >= 0)
    {
        if (sub[subTop].format[start[top]] != 'C')
        {
            // BUG: 0x1B3E0 the arguments are in the wrong order for the format (top before subformat).
            Log::Write(Log::LT_ERROR, PACKETUTIL_FILE, 99,
                       L"[packet], invalid pop repeat operation when sub format's start[top] is not 'C', format:%s, subformat:%s, top:%d, start[top]:%d",
                       format, top, sub[subTop].format, start[top]);
            PACKETUTIL_ASSERT_CRASH(100);
            return;
        }
    }
    else if (format[start[top]] != 'C')
    {
        Log::Write(Log::LT_ERROR, PACKETUTIL_FILE, 94,
                   L"[packet], invalid pop repeat operation when format's start[top] is not 'C', format:%s, top:%d, start[top]:%d",
                   format, top, start[top]);
        PACKETUTIL_ASSERT_CRASH(95);
        return;
    }
    counts[top] = nullptr;
    --top;
    skipRepeatFormat();
}

// 0x1B5B0
char const* RepeatPacketComposer::CurrentFormat() const
{
    if (subTop < 0)
        return &format[index];
    if (sub[subTop].format == nullptr)
        PACKETUTIL_ASSERT_CRASH(144);
    return &sub[subTop].format[sub[subTop].index];
}

// 0x1B650
void RepeatPacketComposer::Allocated(Packet* packet, char const* oldFreeBody)
{
    for (int i = 0; i <= subTop; ++i)
    {
        *sub[i].size += static_cast<unsigned char>(oldFreeBody - sub[i].startPos);
        sub[i].startPos = packet->GetFreeBody();
    }
}

// 0x1B6E0
void RepeatPacketComposer::skipRepeatFormat()
{
    int depth = 1;
    char const* fmt;
    int idx;
    if (subTop < 0)
    {
        fmt = format;
        idx = index;
    }
    else
    {
        fmt = sub[subTop].format;
        idx = sub[subTop].index;
    }
    if (fmt[idx - 1] != 'C')
        PACKETUTIL_ASSERT_CRASH(215);
    do
    {
        char c = fmt[idx];
        if (c == '\0')
        {
            PACKETUTIL_ASSERT_CRASH(219);
            return;
        }
        if (c == 'C')
            ++depth;
        else if (c == ';')
            --depth;
        ++idx;
    } while (depth > 0);
    if (subTop < 0)
        index = idx;
    else
        sub[subTop].index = idx;
}

// ---- RepeatPacketDecomposer ----

// 0x1B000
void RepeatPacketDecomposer::Reset()
{
    top = -1;
    index = 0;
    offset = 0;
}

// 0x1B820
int RepeatPacketDecomposer::PopRepeatCount()
{
    if (top < 0 || format[start[top]] != 'C')
        PACKETUTIL_ASSERT_CRASH(248);
    skipRepeatFormat();
    return static_cast<unsigned short>(counts[top--]);
}

// 0x1B8B0
int RepeatPacketDecomposer::PushRepeatCount(char const* buffer, int size)
{
    ++top;
    if (static_cast<unsigned int>(size) < 2)
    {
        Log::Write(Log::LT_ERROR, PACKETUTIL_FILE, 264, L"[packet], invalid buffer size, size:%d", size);
        return -1;
    }
    if (format[index] != 'C')
    {
        Log::Write(Log::LT_ERROR, PACKETUTIL_FILE, 271,
                   L"== CRASH == [packet], invalid format index, index:%d, char:%d", index, format[index]);
        // BUG: 0x1B8B0 the alert has format specifiers but no arguments.
        AlertSender::Write(PACKETUTIL_FILE, 271, L"== CRASH == [packet], invalid format index, index:%d, char:%d");
        return -1;
    }
    if (top >= 3)
        PACKETUTIL_ASSERT_CRASH(275);
    if (buffer == nullptr)
        PACKETUTIL_ASSERT_CRASH(276);
    counts[top] = *reinterpret_cast<short const*>(buffer);
    start[top] = index++;
    offset += 2;
    return static_cast<unsigned short>(counts[top]);
}

// ---- PacketConcatenateBuffer ----

// 0x1BA90
PacketConcatenateBuffer::~PacketConcatenateBuffer()
{
    if (gbuffer != nullptr)
    {
        Memory::_Manager[2]->Free(gbuffer, PACKETUTIL_FILE, 302);
        gbuffer = nullptr;
    }
}

// 0x1BAE0
void PacketConcatenateBuffer::Clear()
{
    buffer = nullptr;
    size = 0;
    decomposer.Reset();
}

// 0x1BB00
bool PacketConcatenateBuffer::Add(char const* buffer, short size)
{
    if (gbuffer == nullptr)
    {
        gbufsize = 4000;
        gbuffer = static_cast<char*>(Memory::_Manager[2]->Alloc(4000, PACKETUTIL_FILE, 331));
    }
    if (this->buffer != gbuffer)
    {
        this->buffer = gbuffer;
        this->size = 0;
    }
    short skip = check(buffer, size);
    if (skip < 0)
        return false;
    int need = size - skip;
    if (gbufsize - this->size < need)
    {
        do
            gbufsize *= 2;
        while (gbufsize - this->size < need);
        gbuffer = static_cast<char*>(Memory::_Manager[2]->Realloc(gbuffer, gbufsize, PACKETUTIL_FILE, 346));
        this->buffer = gbuffer;
    }
    memcpy(&gbuffer[this->size], &buffer[skip], need);
    this->size += size - skip;
    return true;
}

// 0x1BC10
bool PacketConcatenateBuffer::Decompose(int n, ...)
{
    va_list args;
    va_start(args, n);
    if (buffer == nullptr || static_cast<int>(decomposer.offset) >= size)
        PACKETUTIL_ASSERT_CRASH(360);
    unsigned int offset = decomposer.offset;
    unsigned short used = PacketBuffer::Decompose(&buffer[offset], size - offset, decomposer.CurrentFormat(),
                                                  static_cast<unsigned long long>(n), args);
    decomposer.index += n;
    decomposer.offset += used;
    va_end(args);
    return true;
}

// 0x1BCE0
int PacketConcatenateBuffer::Decompose(VarData* data)
{
    if (buffer == nullptr || data == nullptr)
        PACKETUTIL_ASSERT_CRASH(411);
    if (*decomposer.CurrentFormat() != 'b')
        PACKETUTIL_ASSERT_CRASH(412);
    unsigned long long total = static_cast<unsigned long long>(size);
    if (total < decomposer.offset + 2ull)
        return 0;
    short len = *reinterpret_cast<short const*>(&buffer[decomposer.offset]);
    if (len < 0)
        return 0;
    if (total < static_cast<unsigned long long>(static_cast<long long>(static_cast<int>(decomposer.offset)) + len + 2))
        return 0;
    ++decomposer.index;
    char* p = const_cast<char*>(&buffer[decomposer.offset]);
    data->size = reinterpret_cast<short*>(p);
    data->buffer = p + 2;
    decomposer.offset += len + 2;
    return len + 2;
}

// 0x1BE20
bool PacketConcatenateBuffer::copy(PacketConcatenateBuffer* pcb)
{
    if (pcb == nullptr)
        PACKETUTIL_ASSERT_CRASH(434);
    if (pcb->buffer == nullptr)
        PACKETUTIL_ASSERT_CRASH(435);
    if (gbuffer != nullptr)
        PACKETUTIL_ASSERT_CRASH(436);
    gbufsize = pcb->size;
    gbuffer = static_cast<char*>(Memory::_Manager[2]->Alloc(pcb->size, PACKETUTIL_FILE, 439));
    memcpy(gbuffer, pcb->buffer, pcb->size);
    buffer = gbuffer;
    size = pcb->size;
    return true;
}
