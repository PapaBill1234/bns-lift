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
        PacketBuffer* pktbuf = PacketBufferAllocator::_Local->allocate();
        if (ListHead != nullptr)
            ListTail->Next = pktbuf;
        else
            ListHead = pktbuf;
        ListTail = pktbuf;
        if (CurHeader == nullptr)
            CurHeader = reinterpret_cast<Header*>(&pktbuf->Buffer[8]);

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
