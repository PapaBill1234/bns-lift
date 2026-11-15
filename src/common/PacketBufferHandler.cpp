// PacketBufferHandler.obj (SmartCouponDaemon PDB).
#include "PacketBufferHandler.h"
#include <string.h>
#include <new>
#include "Session.h"
#include "Log.h"
#include "AlertSender.h"

#define PBH_FILE L"source\\PacketBufferHandler.cpp"

// 0x4EA80 (SmartCouponDaemon) folded with Blowfish::BlockSize
unsigned long long TrustedPacketBufferHandler::AllocSize() const
{
    return 8;
}

// 0x21580 (SmartCouponDaemon)
PacketBufferHandler* TrustedPacketBufferHandler::Clone(void* buffer) const
{
    if (buffer != nullptr)
        return new (buffer) TrustedPacketBufferHandler();
    void* mem = Memory::_Manager[2]->Alloc(8, PBH_FILE, 41);
    if (mem == nullptr)
        return nullptr;
    return new (mem) TrustedPacketBufferHandler();
}

// 0x215D0 (SmartCouponDaemon)
void TrustedPacketBufferHandler::Destroy(void* buffer)
{
    if (buffer == nullptr)
        Memory::_Manager[2]->Free(this, PBH_FILE, 46);
}

// 0x14AA0 (SmartCouponDaemon) folded with Console::Flush
void TrustedPacketBufferHandler::Initialize()
{
}

// 0x41CC0 (SmartCouponDaemon) folded with PortListener::EventId
int TrustedPacketBufferHandler::MinimalPacketSize()
{
    return 2;
}

// 0x21600 (SmartCouponDaemon)
int TrustedPacketBufferHandler::ToPacket(Session const* session, char const* buffer, int bufferSize, int freeSize,
                                         char const** packet)
{
    if (bufferSize < 2)
        return 0;
    short size = *reinterpret_cast<short const*>(buffer);
    if (size < 2 || size > 4000)
    {
        Log::Write(Log::LT_ERROR, PBH_FILE, 63,
                   L"== CRASH == [session], TrustedPacketBufferHandler; invalid packet size, id:%I64X, header->size:%d",
                   session->_id, static_cast<int>(size));
        AlertSender::Write(PBH_FILE, 63,
                           L"== CRASH == [session], TrustedPacketBufferHandler; invalid packet size, id:%I64X, header->size:%d",
                           session->_id, static_cast<int>(*reinterpret_cast<short const*>(buffer)));
        return -1;
    }
    if (bufferSize < size)
        return 0;
    if (packet != nullptr)
        *packet = buffer;
    return *reinterpret_cast<short const*>(buffer);
}

// 0x216C0 (SmartCouponDaemon)
int TrustedPacketBufferHandler::ToBuffer(Session const* session, char* buffer, int bufferSize, char const* packet,
                                         char const** sendBuffer)
{
    if (sendBuffer != nullptr)
        *sendBuffer = packet;
    return *reinterpret_cast<short const*>(packet);
}

// 0x216E0 (SmartCouponDaemon)
unsigned long long RawPacketBufferHandler::AllocSize() const
{
    return 56;
}

// 0x216F0 (SmartCouponDaemon)
PacketBufferHandler* RawPacketBufferHandler::Clone(void* buffer) const
{
    if (buffer != nullptr)
        return new (buffer) RawPacketBufferHandler();
    void* mem = Memory::_Manager[2]->Alloc(56, PBH_FILE, 362);
    if (mem == nullptr)
        return nullptr;
    return new (mem) RawPacketBufferHandler();
}

// 0x217A0 (SmartCouponDaemon)
void RawPacketBufferHandler::Destroy(void* buffer)
{
    if (buffer != nullptr)
    {
        this->~RawPacketBufferHandler();
        return;
    }
    if (this != nullptr)
        this->~RawPacketBufferHandler();
    Memory::_Manager[2]->Free(this, PBH_FILE, 367);
}

// 0x14AA0 (SmartCouponDaemon) folded with Console::Flush
void RawPacketBufferHandler::Initialize()
{
}

// 0x1D7A0 (SmartCouponDaemon) folded with Rsa::KeySize
int RawPacketBufferHandler::MinimalPacketSize()
{
    return 0;
}

// 0x21860 (SmartCouponDaemon)
int RawPacketBufferHandler::ToPacket(Session const* session, char const* buffer, int bufferSize, int freeSize,
                                     char const** packet)
{
    // Inlined GrowingBuffer writes.
    Buffer._count = 0;
    short size = static_cast<short>(bufferSize + 2);
    unsigned long long copySize = static_cast<unsigned long long>(static_cast<long long>(size));
    if (Buffer._size - Buffer._count < copySize + 2)
        Buffer.grow(copySize + 2);
    if (Buffer._size - Buffer._count < 2)
        Buffer.grow(2);
    *reinterpret_cast<short*>(&Buffer._buffer[Buffer._count]) = size;
    Buffer._count += 2;
    if (copySize != 0)
    {
        if (Buffer._size - Buffer._count < copySize)
            Buffer.grow(copySize);
        // BUG: 0x21860 copies bufferSize + 2 bytes, 2 bytes more than the received data.
        memcpy(&Buffer._buffer[Buffer._count], buffer, copySize);
        Buffer._count += copySize;
    }
    if (packet != nullptr)
        *packet = reinterpret_cast<char const*>(Buffer._buffer);
    return size - 2;
}

// 0x21940 (SmartCouponDaemon)
int RawPacketBufferHandler::ToBuffer(Session const* session, char* buffer, int bufferSize, char const* packet,
                                     char const** sendBuffer)
{
    if (sendBuffer != nullptr)
        *sendBuffer = packet + 2;
    return *reinterpret_cast<short const*>(packet) - 2;
}
