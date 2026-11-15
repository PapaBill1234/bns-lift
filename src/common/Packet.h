// Packet.obj (SmartCouponDaemon PDB). Layouts from include/pdb/CacheGate/types.h and the SmartCouponDaemon PDB.
#pragma once
#include <stddef.h>

class PacketBuffer;

class PacketSplitter
{
public:
    virtual bool AddBuffer(void* prev, void* cur) = 0;  // slot 0
    virtual bool Finalize(void* header) = 0;            // slot 1
    virtual void Clear() = 0;                           // slot 2
};
static_assert(sizeof(PacketSplitter) == 0x8, "sizeof PacketSplitter");

class Packet
{
public:
    struct Header
    {
        short size;
    };

    ~Packet();
    void Clear();
    char const* Allocate();
    unsigned short Compose(char const* format, ...);
    void AddSize(short size);
    unsigned short Decompose(char const* format, ...) const;

    PacketSplitter* Splitter;
    bool IsFragmentPacket;
    int FragmentPacketCmd;
    Header* CurHeader;
    PacketBuffer* ListHead;
    PacketBuffer* ListTail;
};
static_assert(sizeof(Packet) == 0x28, "sizeof Packet");
static_assert(offsetof(Packet, Splitter) == 0x0, "Packet::Splitter");
static_assert(offsetof(Packet, IsFragmentPacket) == 0x8, "Packet::IsFragmentPacket");
static_assert(offsetof(Packet, FragmentPacketCmd) == 0xC, "Packet::FragmentPacketCmd");
static_assert(offsetof(Packet, CurHeader) == 0x10, "Packet::CurHeader");
static_assert(offsetof(Packet, ListHead) == 0x18, "Packet::ListHead");
static_assert(offsetof(Packet, ListTail) == 0x20, "Packet::ListTail");
