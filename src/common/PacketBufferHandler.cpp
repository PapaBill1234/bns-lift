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

// 0x5C580 (LobbyGate) folded with Blowfish::BlockSize
unsigned long long ClientPacketBufferHandler::AllocSize() const
{
    return 8;
}

// 0x21920 (LobbyGate)
PacketBufferHandler* ClientPacketBufferHandler::Clone(void* buffer) const
{
    if (buffer != nullptr)
        return new (buffer) ClientPacketBufferHandler();
    void* mem = Memory::_Manager[2]->Alloc(8, PBH_FILE, 98);
    if (mem == nullptr)
        return nullptr;
    return new (mem) ClientPacketBufferHandler();
}

// 0x21970 (LobbyGate)
void ClientPacketBufferHandler::Destroy(void* buffer)
{
    if (buffer == nullptr)
        Memory::_Manager[2]->Free(this, PBH_FILE, 103);
}

// (LobbyGate) folded with Console::Flush ❓ no own address
void ClientPacketBufferHandler::Initialize()
{
}

// 0x21830 (LobbyGate) folded with LobbyGateReloadInvalidRestoreTimer::TimerId
int ClientPacketBufferHandler::MinimalPacketSize()
{
    return 2;
}

// 0x219A0 (LobbyGate)
int ClientPacketBufferHandler::ToPacket(Session const* session, char const* buffer, int bufferSize, int freeSize,
                                        char const** packet)
{
    // The handler changes the crypt members through the const session.
    Session* mutableSession = const_cast<Session*>(session);
    unsigned short header = *reinterpret_cast<unsigned short const*>(buffer);
    PacketCrypt::Algorithm algorithm = static_cast<PacketCrypt::Algorithm>(header >> 14);
    unsigned int size;
    if ((header >> 14) != 0)
        size = 4 * (header & 0xFFF);
    else
        size = header & 0x3FFF;
    int packetSize = 0;
    if (size > 0xFFFF)
        return -1;
    if (bufferSize < static_cast<int>(size + 2))
        return 0;

    PacketCrypt* currentCrypt = session->_currentCrypt;
    if (currentCrypt != nullptr)
    {
        int cryptMode = session->_cryptMode;
        bool with3rdParty = false;
        if (cryptMode != 5)
        {
            Log::Write(Log::LT_ERROR, PBH_FILE, 165, L"Session(%I64X), Seesion decrypt failed;invalid module, mode:%d",
                       session->_id, cryptMode);
            return -1;
        }
        short code = static_cast<short>(header >> 12);
        if (code != 8 && code != 9 && code != 10 && code != 11)
        {
            Log::Write(Log::LT_ERROR, PBH_FILE, 173,
                       L"Session(%I64X), Seesion decrypt failed;invalid enc-code, enc-code:%d", session->_id,
                       static_cast<unsigned int>(header) >> 12);
            return -1;
        }
        packetSize = bufferSize;
        int err = currentCrypt->Decrypt(reinterpret_cast<unsigned char*>(const_cast<char*>(buffer)), bufferSize,
                                        &packetSize, &with3rdParty);
        if (err != PacketCrypt::SPCE_NO_ERROR)
        {
            Log::Write(Log::LT_ERROR, PBH_FILE, 180, L"Session(%I64X), Session decrypt failed, error-code:%d",
                       session->_id, err);
            return -1;
        }
        Security3rdParty* security3rd = session->_security3rd;
        if (security3rd != nullptr)
        {
            int size3rd = reinterpret_cast<short const*>(buffer)[1] - 2;
            int err3rd = security3rd->Decrypt(reinterpret_cast<unsigned char*>(const_cast<char*>(buffer)) + 4,
                                              &size3rd, with3rdParty);
            if (err3rd != 0)  // Security3rdParty::S3ERR_SUCCESS
            {
                Log::Write(Log::LT_ERROR, PBH_FILE, 198,
                           L"Session(%I64X), Session 3rd party decrypt failed, error-code: %d", session->_id, err3rd);
                return -1;
            }
        }
    }
    else
    {
        if (algorithm == PacketCrypt::ALGORITHM_DEFAULT)
        {
            Log::Write(Log::LT_ERROR, PBH_FILE, 139,
                       L"Session(%I64X), Handshake decrypt failed, code 'plain' not acceptable", session->_id);
            return -1;
        }
        if (session->_cryptMode == 2)
        {
            PacketCrypt* crypt =
                static_cast<PacketCrypt*>(session->allocateCrypt(PacketCrypt::HANDSHAKE_CRYPT, algorithm));
            mutableSession->_handshakeCrypt = crypt;
            mutableSession->_currentCrypt = crypt;
        }
        PacketCrypt* crypt = session->_currentCrypt;
        if (crypt == nullptr)
        {
            Log::Write(Log::LT_ERROR, PBH_FILE, 149, L"Session(%I64X), Handshake decrypt failed;cannot create crypt",
                       session->_id);
            return -1;
        }
        packetSize = bufferSize;
        int err = crypt->Decrypt(reinterpret_cast<unsigned char*>(const_cast<char*>(buffer)), bufferSize, &packetSize,
                                 nullptr);
        if (err != PacketCrypt::SPCE_NO_ERROR)
        {
            Log::Write(Log::LT_ERROR, PBH_FILE, 156, L"Session(%I64X), Handshake decrypt failed, error-code:%d",
                       session->_id, err);
            return -1;
        }
    }
    if (packet != nullptr)
        *packet = buffer + 2;
    short headerSize = reinterpret_cast<short const*>(buffer)[1];
    if (headerSize >= 2 && packetSize >= headerSize)
        return packetSize;
    Log::Write(Log::LT_ERROR, PBH_FILE, 213,
               L"[session], ClientPacketBufferHandler; invalid packet size, id:%I64X, header->size:%d, packet-size:%d",
               session->_id, static_cast<int>(headerSize), packetSize);
    return -1;
}

// 0x21CB0 (LobbyGate)
int ClientPacketBufferHandler::ToBuffer(Session const* session, char* buffer, int bufferSize, char const* packet,
                                        char const** sendBuffer)
{
    if (sendBuffer != nullptr)
        *sendBuffer = packet;
    return 4 * (*reinterpret_cast<unsigned short const*>(packet) & 0xFFF) + 2;
}
