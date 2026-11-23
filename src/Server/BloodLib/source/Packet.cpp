// Packet.obj (SmartCouponDaemon PDB).
#include "Packet.h"
#include <stdarg.h>
#include "AlertSender.h"
#include "CrashHandler.h"
#include "Log.h"
#include "PacketBuffer.h"
#include "PacketUtil.h"
#include <string.h>

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

// 0x21EB0 (PostOfficeDaemon)
unsigned short Packet::ComposeText(char const* format, ...)
{
    va_list args;
    va_start(args, format);
    if (format == nullptr || CurHeader == nullptr)
        PACKET_ASSERT_CRASH(213);
    unsigned short size = PacketBuffer::ComposeText(reinterpret_cast<char*>(CurHeader) + CurHeader->size,
                                                    4000 - CurHeader->size, format,
                                                    static_cast<unsigned long long>(-1), args);
    AddSize(size);
    va_end(args);
    return size;
}

// 0x22220 (PostOfficeDaemon)
unsigned short Packet::DecomposeText(char const* format, ...) const
{
    va_list args;
    va_start(args, format);
    if (format == nullptr || CurHeader == nullptr)
        PACKET_ASSERT_CRASH(612);
    // LIFT: the count value is a guess. PDB: DecomposeText has 5 arguments. 0x22293-0x222a0 passes only
    // buffer, format and args. DecomposeText (0x2FAB0) reads the length from the buffer, not count.
    unsigned short size = PacketBuffer::DecomposeText(reinterpret_cast<char const*>(CurHeader + 1),
                                                      CurHeader->size - 2, format,
                                                      static_cast<unsigned long long>(-1), args);
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
// LIFT: noinline. The orig calls it out of line (POD 0x220d0).
__declspec(noinline) unsigned short Packet::Decompose(char const* format, ...) const
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

// 0x220D0 (PostOfficeDaemon)
// LIFT: noinline. The orig calls it out of line from the CacheEconomyPacketHandler handlers.
__declspec(noinline) unsigned short Packet::Decompose(int offset, int n, char const* format, ...) const
{
    va_list args;
    va_start(args, format);
    if (format == nullptr || CurHeader == nullptr || offset >= CurHeader->size - 2)
        PACKET_ASSERT_CRASH(472);
    unsigned short size = PacketBuffer::Decompose(reinterpret_cast<char const*>(CurHeader + 1) + offset,
                                                  CurHeader->size - offset - 2, format,
                                                  static_cast<unsigned long long>(n), args);
    va_end(args);
    return size;
}

// 0x168D0 (LobbyGate)
char const* Packet::Allocate(PacketComposer* pcr)
{
    if (pcr == nullptr)
        PACKET_ASSERT_CRASH(70);
    char const* oldFreeBody = GetFreeBody();
    char const* body = Allocate();
    if (body != nullptr)
        pcr->Allocated(this, oldFreeBody);
    return body;
}

// 0xde140 (LobbyDaemon)
unsigned short Packet::Compose(PacketComposer* pcr, int n, ...)
{
    va_list args;
    va_start(args, n);
    if (IsFragmentPacket)
        return ComposeV(pcr, n, args);
    if (pcr == nullptr || CurHeader == nullptr)
        PACKET_ASSERT_CRASH(140);
    int count = n >= 0 ? n : pcr->len - pcr->index;
    unsigned short size = PacketBuffer::Compose(reinterpret_cast<char*>(CurHeader) + CurHeader->size,
                                                4000 - CurHeader->size, pcr->CurrentFormat(),
                                                static_cast<unsigned long long>(count), args);
    pcr->Forward(n);
    AddSize(size);
    return size;
}

// 0x16A50 (LobbyGate)
unsigned short Packet::ComposeV(PacketComposer* pcr, int n, char* args)
{
    if (IsFragmentPacket)
    {
        if (pcr == nullptr || CurHeader == nullptr || n <= 0)
            PACKET_ASSERT_CRASH(159);
        unsigned short total = 0;
        int i = 0;
        do
        {
            char* prevArgs = args;
            unsigned short need = PacketBuffer::CheckCompose(reinterpret_cast<char*>(CurHeader) + CurHeader->size,
                                                             4000 - CurHeader->size, pcr->CurrentFormat(), &args);
            if (need == 5000)
            {
                if (prevArgs != args)
                    PACKET_ASSERT_CRASH(171);
                Allocate(pcr);
                continue;
            }
            if (need != 0)
            {
                if (prevArgs == args)
                    PACKET_ASSERT_CRASH(177);
                short size = PacketBuffer::Compose(reinterpret_cast<char*>(CurHeader) + CurHeader->size,
                                                   4000 - CurHeader->size, pcr->CurrentFormat(), 1, prevArgs);
                if (need != static_cast<unsigned short>(size))
                    PACKET_ASSERT_CRASH(181);
                pcr->Forward(1);
                AddSize(size);
                total += size;
            }
            else
            {
                Log::Write(Log::LT_ERROR, PACKET_FILE, 191, L"== CRASH == [packet], %s, Failed to CheckCompose(), cmd:%d",
                           L"Packet::ComposeV", FragmentPacketCmd);
                AlertSender::Write(PACKET_FILE, 191, L"== CRASH == [packet], %s, Failed to CheckCompose(), cmd:%d",
                                   L"Packet::ComposeV", FragmentPacketCmd);
            }
            ++i;
        } while (i < n);
        return total;
    }

    if (pcr == nullptr || CurHeader == nullptr)
        PACKET_ASSERT_CRASH(201);
    int count = n >= 0 ? n : pcr->len - pcr->index;
    unsigned short size = PacketBuffer::Compose(reinterpret_cast<char*>(CurHeader) + CurHeader->size,
                                                4000 - CurHeader->size, pcr->CurrentFormat(),
                                                static_cast<unsigned long long>(count), args);
    // BUG: 0x16A50 Forward gets n, not count. When n < 0 the index moves back.
    pcr->Forward(n);
    AddSize(size);
    return size;
}

// 0x16DF0 (LobbyGate)
void Packet::Add(void const* data, short size)
{
    if (size < 0 || (CurHeader != nullptr ? static_cast<unsigned short>(4000 - CurHeader->size) : 0) < size)
        PACKET_ASSERT_CRASH(287);
    if (size > 0)
    {
        memcpy(reinterpret_cast<char*>(CurHeader) + CurHeader->size, data, size);
        CurHeader->size += size;
    }
}

// 0x16F60 (LobbyGate)
void Packet::Copy(Packet const* packet)
{
    if (packet == nullptr)
        PACKET_ASSERT_CRASH(370);
    if (packet->CurHeader == nullptr)
        PACKET_ASSERT_CRASH(371);
    Clear();
    PacketBuffer* src = packet->ListHead;
    if (src == nullptr)
    {
        Allocate();
        memcpy(CurHeader, packet->CurHeader, packet->CurHeader->size);
        return;
    }
    do
    {
        // LIFT: 0x1707B and 0x170B2 (LobbyGate) the original has two allocate calls. It tests CurHeader first.
        if (CurHeader == nullptr)
        {
            PacketBuffer* pktbuf = PacketBufferAllocator::_Local->allocate();
            if (ListHead != nullptr)
                ListTail->Next = pktbuf;
            else
                ListHead = pktbuf;
            ListTail = pktbuf;
            CurHeader = reinterpret_cast<Header*>(&pktbuf->Buffer[8]);
        }
        else
        {
            PacketBuffer* pktbuf = PacketBufferAllocator::_Local->allocate();
            if (ListHead != nullptr)
                ListTail->Next = pktbuf;
            else
                ListHead = pktbuf;
            ListTail = pktbuf;
        }

        PacketBuffer* dst = ListTail;
        char const* srcBuf;
        char* dstBuf;
        unsigned short size;
        if (dst->sendBuffer != nullptr)
        {
            srcBuf = src->sendBuffer != nullptr ? src->sendBuffer : &src->Buffer[8];
            dstBuf = dst->sendBuffer != nullptr ? const_cast<char*>(dst->sendBuffer) : &dst->Buffer[8];
            size = src->sendBuffer != nullptr ? static_cast<unsigned short>(src->sendSize)
                                              : *reinterpret_cast<unsigned short*>(&src->Buffer[8]);
            dst->sendBuffer = dstBuf;
            dst->sendSize = size;
        }
        else
        {
            size = *reinterpret_cast<unsigned short*>(&src->Buffer[8]);
            srcBuf = &src->Buffer[8];
            dstBuf = &dst->Buffer[8];
        }
        memcpy(dstBuf, srcBuf, size);
        src = src->Next;
    } while (src != nullptr);
}

// 0x17170 (LobbyGate)
void Packet::Encrypt(PacketCrypt* crypt)
{
    if (crypt != nullptr && ListHead != nullptr)
        ListHead->encrypt(crypt, nullptr);
}

// 0x17240 (LobbyGate)
void Packet::Finalize(PacketCrypt* crypt)
{
    if (Splitter != nullptr)
        Splitter->Finalize(CurHeader);
    if (ListHead != nullptr && crypt != nullptr)
        ListHead->encrypt(crypt, nullptr);
}

// 0x7300 (CacheGate)
void Packet::Concatenate(Packet const* packet, PacketConcatenateHandler const* concatHandler)
{
    if (packet == nullptr)
        PACKET_ASSERT_CRASH(414);
    if (packet->CurHeader == nullptr)
        PACKET_ASSERT_CRASH(415);
    PacketBuffer* src = packet->ListHead;
    if (src == nullptr)
    {
        Concatenate(reinterpret_cast<char const*>(packet->CurHeader), packet->CurHeader->size, concatHandler);
        return;
    }
    do
    {
        PacketBuffer* pktbuf = PacketBufferAllocator::_Local->allocate();
        if (ListHead != nullptr)
            ListTail->Next = pktbuf;
        else
            ListHead = pktbuf;
        Header* header = reinterpret_cast<Header*>(&pktbuf->Buffer[8]);
        ListTail = pktbuf;
        memcpy(&pktbuf->Buffer[8], &src->Buffer[8], *reinterpret_cast<unsigned short*>(&src->Buffer[8]));
        src = src->Next;
        if (CurHeader == nullptr)
            CurHeader = header;
    } while (src != nullptr);
}

// 0x7470 (CacheGate)
void Packet::Concatenate(char const* buffer, unsigned short size, PacketConcatenateHandler const* concatHandler)
{
    if (buffer == nullptr)
        PACKET_ASSERT_CRASH(440);
    if (size > 4000)
        PACKET_ASSERT_CRASH(441);
    PacketBuffer* pktbuf = PacketBufferAllocator::_Local->allocate();
    if (ListHead != nullptr)
        ListTail->Next = pktbuf;
    else
        ListHead = pktbuf;
    Header* header = reinterpret_cast<Header*>(&pktbuf->Buffer[8]);
    ListTail = pktbuf;
    memcpy(&pktbuf->Buffer[8], buffer, static_cast<short>(size));
    if (CurHeader == nullptr)
        CurHeader = header;
}

// 0x75B0 (CacheGate)
unsigned short Packet::Decompose(PacketDecomposer* pdr, int n, ...) const
{
    va_list args;
    va_start(args, n);
    if (pdr == nullptr)
    {
        Log::Write(Log::LT_ERROR, PACKET_FILE, 501, L"== CRASH == [packet], invalid pdr");
        AlertSender::Write(PACKET_FILE, 501, L"== CRASH == [packet], invalid pdr");
        return 0;
    }
    if (CurHeader == nullptr)
    {
        Log::Write(Log::LT_ERROR, PACKET_FILE, 506, L"== CRASH == [packet], invalid CurHeader");
        AlertSender::Write(PACKET_FILE, 506, L"== CRASH == [packet], invalid CurHeader");
        return 0;
    }
    int offset = static_cast<int>(pdr->offset);
    if (offset >= CurHeader->size - 2)
    {
        Log::Write(Log::LT_ERROR, PACKET_FILE, 514, L"[packet], pdr->offset %d >= CurHeader->size %d - HEADER_SIZE %d",
                   offset, CurHeader->size, 2);
        return 0;
    }
    int count = n >= 0 ? n : pdr->len - pdr->index;
    unsigned short result = PacketBuffer::Decompose(reinterpret_cast<char const*>(CurHeader + 1) + pdr->offset,
                                                    CurHeader->size - pdr->offset - 2, pdr->CurrentFormat(),
                                                    static_cast<unsigned long long>(count), args);
    // BUG: 0x75B0 index moves by n, not count. When n < 0 the index moves back.
    pdr->index += n;
    pdr->offset += result;
    va_end(args);
    return result;
}

// 0xde970 (LobbyDaemon)
unsigned short Packet::Decompose(PacketDecomposer* pdr, VarStr* str) const
{
    if (CurHeader == nullptr || str == nullptr || pdr == nullptr)
        PACKET_ASSERT_CRASH(565);
    if (*pdr->CurrentFormat() != 's')
        PACKET_ASSERT_CRASH(566);
    unsigned int offset = pdr->offset;
    unsigned long long limit = static_cast<unsigned long long>(CurHeader->size - 2);
    if (limit < static_cast<unsigned long long>(offset) + 2)
        return 0;
    short length = *reinterpret_cast<short const*>(reinterpret_cast<char const*>(CurHeader + 1) + offset);
    // LIFT: the original keeps the byte size (2 * length) in a 16-bit value. A value with bit 15 set is refused.
    short byteSize = static_cast<short>(length * 2);
    if (byteSize < 0 || limit < static_cast<unsigned long long>(byteSize) + offset + 2)
        return 0;
    ++pdr->index;
    str->len = reinterpret_cast<short*>(const_cast<char*>(reinterpret_cast<char const*>(CurHeader + 1)) + offset);
    str->str = reinterpret_cast<wchar_t*>(const_cast<char*>(reinterpret_cast<char const*>(CurHeader + 2)) + offset);
    pdr->offset = offset + byteSize + 2;
    return static_cast<unsigned short>(byteSize + 2);
}

// 0xdeab0 (LobbyDaemon)
unsigned short Packet::Decompose(PacketDecomposer* pdr, VarData* data) const
{
    if (CurHeader == nullptr || data == nullptr || pdr == nullptr)
        PACKET_ASSERT_CRASH(589);
    if (*pdr->CurrentFormat() != 'b')
        PACKET_ASSERT_CRASH(590);
    unsigned int offset = pdr->offset;
    unsigned long long limit = static_cast<unsigned long long>(CurHeader->size - 2);
    if (limit < static_cast<unsigned long long>(offset) + 2)
        return 0;
    short length = *reinterpret_cast<short const*>(reinterpret_cast<char const*>(CurHeader + 1) + offset);
    if (length < 0 || limit < static_cast<unsigned long long>(length) + offset + 2)
        return 0;
    ++pdr->index;
    data->size = reinterpret_cast<short*>(const_cast<char*>(reinterpret_cast<char const*>(CurHeader + 1)) + offset);
    data->buffer = const_cast<char*>(reinterpret_cast<char const*>(CurHeader + 2)) + offset;
    pdr->offset = offset + length + 2;
    return static_cast<unsigned short>(length + 2);
}
