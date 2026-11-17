// FragmentPacket.obj (CacheGate, LobbyGate and PostOfficeDaemon PDBs).
// SendFragmentPacketConcatenater: CacheGate RVAs. The other functions: LobbyGate RVAs.
// PostOfficeDaemon has the same logic and the same log line numbers at 0x1000-0x17b0.
#include "PacketUtil.h"

#include <stdarg.h>
#include <new>

#include "AlertSender.h"
#include "CrashHandler.h"
#include "FragmentPacket.h"
#include "Log.h"
#include "Packet.h"

// ❓ CacheGate and PostOfficeDaemon use "..\..\Packet\FragmentPacket.cpp".
// LobbyGate uses "..\Packet\FragmentPacket.cpp". This shared file uses the first path.
static wchar_t const FRAGMENT_PACKET_FILE[] = L"..\\..\\Packet\\FragmentPacket.cpp";
static wchar_t const* const kFile = FRAGMENT_PACKET_FILE;  // ❓ local name

// 0x11c0
SendFragmentPacketConcatenater::~SendFragmentPacketConcatenater()
{
    _packet.Clear();
}

// 0x1200
void SendFragmentPacketConcatenater::Clear()
{
    _packet.Clear();
}

// 0x1210
unsigned long long SendFragmentPacketConcatenater::AllocSize() const
{
    return sizeof(SendFragmentPacketConcatenater);
}

// 0x1220
PacketConcatenater* SendFragmentPacketConcatenater::Clone(void* buffer) const
{
    if (buffer == nullptr)
    {
        Log::Write(Log::LT_ERROR, FRAGMENT_PACKET_FILE, 389,
                   L"== CRASH == [network], SendFragmentPacketConcatenater Clone() failed");
        AlertSender::Write(FRAGMENT_PACKET_FILE, 389,
                           L"== CRASH == [network], SendFragmentPacketConcatenater Clone() failed");
        return nullptr;
    }
    return new (buffer) SendFragmentPacketConcatenater();
}

// 0x1290
void SendFragmentPacketConcatenater::Destroy(void* buffer)
{
    // The original calls the virtual destructor of this object (flag 0). It does not use buffer.
    this->~SendFragmentPacketConcatenater();
}

// 0x2280
bool FragmentPacketSplitter::AddBuffer(void* prev, void* cur)
{
    Packet::Header const* prevHeader = static_cast<Packet::Header const*>(prev);
    Packet::Header* newHeader = static_cast<Packet::Header*>(cur);

    if (Command == 0)
    {
        Log::Write(Log::LT_ERROR, kFile, 57, L"== CRASH == [fragment-packet-splitter], add buffer; command is null");
        AlertSender::Write(kFile, 57, L"== CRASH == [fragment-packet-splitter], add buffer; command is null");
        return false;
    }
    if (newHeader == nullptr)
    {
        Log::Write(Log::LT_ERROR, kFile, 63, L"== CRASH == [fragment-packet-splitter], add buffer; newHeader is null");
        AlertSender::Write(kFile, 63, L"== CRASH == [fragment-packet-splitter], add buffer; newHeader is null");
        return false;
    }

    CurSize = reinterpret_cast<int*>(reinterpret_cast<char*>(newHeader) + newHeader->size + 2);
    *reinterpret_cast<short*>(reinterpret_cast<char*>(newHeader) + newHeader->size) = Command;
    *CurSize = -1;
    newHeader->size += 6;

    if (TotalSize == nullptr)
    {
        TotalSize = CurSize;
        *CurSize = 0;
        return true;
    }
    if (prevHeader == nullptr)
    {
        Log::Write(Log::LT_ERROR, kFile, 81, L"== CRASH == [fragment-packet-splitter], add buffer; prev header is null");
        AlertSender::Write(kFile, 81, L"== CRASH == [fragment-packet-splitter], add buffer; prev header is null");
        return false;
    }
    *TotalSize += prevHeader->size - 8;
    return true;
}

// 0x23a0
bool FragmentPacketSplitter::Finalize(void* last)
{
    Packet::Header const* lastHeader = static_cast<Packet::Header const*>(last);
    if (Command != 0 && TotalSize != nullptr)
    {
        *TotalSize += lastHeader->size - 8;
        if (CurSize != TotalSize)
            *CurSize = 0;
        TotalSize = nullptr;
        return true;
    }
    Log::Write(Log::LT_ERROR, kFile, 95, L"== CRASH == [fragment-packet-splitter], finalize; command or total size is 0");
    AlertSender::Write(kFile, 95, L"== CRASH == [fragment-packet-splitter], finalize; command or total size is 0");
    return false;
}

// 0x2410
void FragmentPacketSplitter::Clear()
{
    TotalSize = nullptr;
    CurSize = nullptr;
}

// 0x2420
FragmentPacket::FragmentPacket(short command, char const* format)
{
    packet.CurHeader = nullptr;
    packet.Splitter = nullptr;
    packet.ListHead = nullptr;
    packet.ListTail = nullptr;
    packet.IsFragmentPacket = false;
    packet.FragmentPacketCmd = 0;
    // LIFT: RepeatPacketComposer has no constructor in common; the inline one sets these fields.
    composer.format = nullptr;
    composer.len = 0;
    composer.index = 0;
    composer.top = -1;
    composer.subTop = -1;
    count = 0;
    splitter.Command = command;
    if (format != nullptr)
        composer.SetFormat(format, 2);
    packet.IsFragmentPacket = true;
    packet.Splitter = &splitter;
    packet.FragmentPacketCmd = command;
}

// 0x24e0
FragmentPacket::~FragmentPacket()
{
    packet.Clear();
}

// 0x37f0 (Client.obj copy)
void FragmentPacket::StartRepeat()
{
    if (packet.CurHeader == nullptr || static_cast<unsigned short>(4000 - packet.CurHeader->size) < 2u)
        packet.Allocate(&composer);
    composer.PushRepeatCount(&packet);
}

// 0x3840 (Client.obj copy)
void FragmentPacket::IncRepeatCount()
{
    if (composer.subTop < 0)
        composer.index = composer.start[composer.top] + 1;
    else
        composer.sub[composer.subTop].index = composer.start[composer.top] + 1;
    ++*composer.counts[composer.top];
}

// 0x38a0 (Client.obj copy)
unsigned short FragmentPacket::FreeSize() const
{
    if (packet.CurHeader != nullptr)
        return static_cast<unsigned short>(4000 - packet.CurHeader->size);
    return 0;
}

// 0x38c0 (Client.obj copy)
unsigned short FragmentPacket::Compose(int n, ...)
{
    va_list args;
    va_start(args, n);
    if (packet.CurHeader == nullptr)
        packet.Allocate(&composer);
    unsigned short result = packet.ComposeV(&composer, n, args);
    va_end(args);
    return result;
}

// 0x2510
FragmentPacketConcatenater::~FragmentPacketConcatenater()
{
    relayPacket.Clear();
    // The second relayPacket.Clear() is the inlined Packet destructor.
}

// 0x2590
void FragmentPacketConcatenater::Clear()
{
    buffer = nullptr;
    size = 0;
    decomposer.Reset();
    Command = 0;
    TotalSize = 0;
    relayPacket.Clear();
}

// 0x25d0
bool FragmentPacketConcatenater::Add(Packet const* packet, bool* completed, bool added)
{
    (void)added;
    *completed = false;
    int total = *reinterpret_cast<int const*>(reinterpret_cast<char const*>(packet->CurHeader) + 4);

    if (total == 0)
    {
        if (!PacketConcatenateBuffer::Add(reinterpret_cast<char const*>(packet->CurHeader) + 2,
                                          packet->CurHeader->size - 2))
        {
            Log::Write(Log::LT_ERROR, kFile, 185, L"FragmentPacketConcatenater::Add() failed, END_DATA");
            return false;
        }
        if (size != TotalSize)
        {
            Log::Write(Log::LT_ERROR, kFile, 189, L"FragmentPacketConcatenater::Add() failed, Size != total");
            return false;
        }
        *completed = true;
        return true;
    }
    if (total == -1)
    {
        if (size == 0)
        {
            Log::Write(Log::LT_ERROR, kFile, 197, L"FragmentPacketConcatenater::Add() failed, Size = 0");
            return false;
        }
        if (!PacketConcatenateBuffer::Add(reinterpret_cast<char const*>(packet->CurHeader) + 2,
                                          packet->CurHeader->size - 2))
        {
            Log::Write(Log::LT_ERROR, kFile, 201, L"FragmentPacketConcatenater::Add() failed, MORE_DATA");
            return false;
        }
        return true;
    }
    if (total <= 0)
    {
        Log::Write(Log::LT_ERROR, kFile, 223, L"FragmentPacketConcatenater::Add() failed, total < 0");
        return false;
    }
    if (static_cast<unsigned short>(packet->CurHeader->size - 2) - 6 != total || size != 0)
    {
        if (!PacketConcatenateBuffer::Add(reinterpret_cast<char const*>(packet->CurHeader) + 2,
                                          packet->CurHeader->size - 2))
        {
            Log::Write(Log::LT_ERROR, kFile, 217, L"FragmentPacketConcatenater::Add() failed, FIRST");
            return false;
        }
        return true;
    }

    char const* body = reinterpret_cast<char const*>(packet->CurHeader) + 2;
    short bodySize = packet->CurHeader->size - 2;
    short offset = check(body, bodySize);
    if (offset >= 0)
    {
        buffer = body + offset;
        size = bodySize - offset;
        *completed = true;
        return true;
    }
    Log::Write(Log::LT_ERROR, kFile, 209, L"FragmentPacketConcatenater::Add() failed, add failed");
    return false;
}

// 0x2770
bool FragmentPacketConcatenater::Copy(FragmentPacketConcatenater* fpc)
{
    if (fpc == nullptr)
    {
        Log::Write(Log::LT_ERROR, kFile, 232, L"== CRASH == ASSERT CRASH");
        AlertSender::Write(kFile, 232, L"== CRASH == ASSERT CRASH");
        CrashHandler::MakeCrash("..\\..\\Packet\\FragmentPacket.cpp", 232, L"");  // ❓ format is an empty global string
    }
    bool result = PacketConcatenateBuffer::copy(fpc);
    if (result)
    {
        Command = fpc->Command;
        TotalSize = fpc->TotalSize;
        return true;
    }
    return result;
}

// 0x2810
short FragmentPacketConcatenater::check(char const* buffer, short size)
{
    if (Command == 0)
    {
        Command = *reinterpret_cast<short const*>(buffer);
        TotalSize = *reinterpret_cast<int const*>(buffer + 2);
    }
    short bodySize;
    if (Command == *reinterpret_cast<short const*>(buffer) && (bodySize = size - 6) >= 0 &&
        TotalSize >= this->size + bodySize)
        return 6;
    return -1;
}

// 0x2860
unsigned long long FragmentPacketConcatenater::AllocSize() const
{
    return 144;
}

// 0x2870
PacketConcatenater* FragmentPacketConcatenater::Clone(void* buffer) const
{
    if (buffer != nullptr)
        return ::new (buffer) FragmentPacketConcatenater();
    Log::Write(Log::LT_ERROR, kFile, 273, L"== CRASH == [network], FragmentPacketConcatenater Clone() failed");
    AlertSender::Write(kFile, 273, L"== CRASH == [network], FragmentPacketConcatenater Clone() failed");
    return nullptr;
}

// 0x2920
void FragmentPacketConcatenater::Destroy(void* buffer)
{
    (void)buffer;
    this->~FragmentPacketConcatenater();
}
