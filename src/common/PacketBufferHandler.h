// PacketBufferHandler.obj (SmartCouponDaemon PDB).
#pragma once
#include <stddef.h>
#include "Memory.h"

class Session;

class PacketBufferHandler
{
public:
    virtual unsigned long long AllocSize() const = 0;                       // slot 0
    virtual PacketBufferHandler* Clone(void* buffer) const = 0;             // slot 1
    virtual void Destroy(void* buffer) = 0;                                 // slot 2
    virtual void Initialize() = 0;                                          // slot 3
    virtual int MinimalPacketSize() = 0;                                    // slot 4
    virtual int ToPacket(Session const* session, char const* buffer, int bufferSize, int freeSize,
                         char const** packet) = 0;                          // slot 5
    virtual int ToBuffer(Session const* session, char* buffer, int bufferSize, char const* packet,
                         char const** sendBuffer) = 0;                      // slot 6
};
static_assert(sizeof(PacketBufferHandler) == 0x8, "sizeof PacketBufferHandler");

class TrustedPacketBufferHandler : public PacketBufferHandler
{
public:
    virtual unsigned long long AllocSize() const;
    virtual PacketBufferHandler* Clone(void* buffer) const;
    virtual void Destroy(void* buffer);
    virtual void Initialize();
    virtual int MinimalPacketSize();
    virtual int ToPacket(Session const* session, char const* buffer, int bufferSize, int freeSize,
                         char const** packet);
    virtual int ToBuffer(Session const* session, char* buffer, int bufferSize, char const* packet,
                         char const** sendBuffer);
};
static_assert(sizeof(TrustedPacketBufferHandler) == 0x8, "sizeof TrustedPacketBufferHandler");

class RawPacketBufferHandler : public PacketBufferHandler
{
public:
    RawPacketBufferHandler() : Buffer(2, 512) {}  // LIFT: inlined in Clone (0x216F0)
    virtual unsigned long long AllocSize() const;
    virtual PacketBufferHandler* Clone(void* buffer) const;
    virtual void Destroy(void* buffer);
    virtual void Initialize();
    virtual int MinimalPacketSize();
    virtual int ToPacket(Session const* session, char const* buffer, int bufferSize, int freeSize,
                         char const** packet);
    virtual int ToBuffer(Session const* session, char* buffer, int bufferSize, char const* packet,
                         char const** sendBuffer);

    GrowingBuffer Buffer;
};
static_assert(sizeof(RawPacketBufferHandler) == 0x38, "sizeof RawPacketBufferHandler");
static_assert(offsetof(RawPacketBufferHandler, Buffer) == 0x8, "RawPacketBufferHandler::Buffer");

// LobbyGate PDB.
class ClientPacketBufferHandler : public PacketBufferHandler
{
public:
    virtual unsigned long long AllocSize() const;
    virtual PacketBufferHandler* Clone(void* buffer) const;
    virtual void Destroy(void* buffer);
    virtual void Initialize();
    virtual int MinimalPacketSize();
    virtual int ToPacket(Session const* session, char const* buffer, int bufferSize, int freeSize,
                         char const** packet);
    virtual int ToBuffer(Session const* session, char* buffer, int bufferSize, char const* packet,
                         char const** sendBuffer);
};
static_assert(sizeof(ClientPacketBufferHandler) == 0x8, "sizeof ClientPacketBufferHandler");

// PostOfficeDaemon PDB.
class TextStreamPacketBufferHandler : public PacketBufferHandler
{
public:
    // LIFT: Inlined in Clone (0x2C3F0). Clone does not set delimiter; Initialize sets it.
    TextStreamPacketBufferHandler() : Buffer(2, 512) {}
    virtual unsigned long long AllocSize() const;
    virtual PacketBufferHandler* Clone(void* buffer) const;
    virtual void Destroy(void* buffer);
    virtual void Initialize();
    virtual int MinimalPacketSize();
    virtual int ToPacket(Session const* session, char const* buffer, int bufferSize, int freeSize,
                         char const** packet);
    virtual int ToBuffer(Session const* session, char* buffer, int bufferSize, char const* packet,
                         char const** sendBuffer);

    wchar_t delimiter[4];
    GrowingBuffer Buffer;
};
static_assert(sizeof(TextStreamPacketBufferHandler) == 0x40, "sizeof TextStreamPacketBufferHandler");
static_assert(offsetof(TextStreamPacketBufferHandler, delimiter) == 0x8, "TextStreamPacketBufferHandler::delimiter");
static_assert(offsetof(TextStreamPacketBufferHandler, Buffer) == 0x10, "TextStreamPacketBufferHandler::Buffer");
