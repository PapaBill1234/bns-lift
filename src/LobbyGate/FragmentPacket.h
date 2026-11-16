// FragmentPacket.obj (LobbyGate PDB). Layouts from include/pdb/LobbyGate/types.h.
#pragma once
#include <stddef.h>
#include "Packet.h"
#include "PacketUtil.h"

class FragmentPacketSplitter : public PacketSplitter
{
public:
    // ❓ The constructor is inlined (FragmentPacket 0x2420).
    FragmentPacketSplitter() : Command(0), TotalSize(nullptr), CurSize(nullptr) {}

    // The PDB parameters are Packet::Header const* prevHeader, Packet::Header* newHeader.
    virtual bool AddBuffer(void* prevHeader, void* newHeader);  // 0x2280
    // The PDB parameter is Packet::Header const* lastHeader.
    virtual bool Finalize(void* lastHeader);                    // 0x23a0
    virtual void Clear();                                       // 0x2410

    short Command;
    int* TotalSize;
    int* CurSize;
};
static_assert(sizeof(FragmentPacketSplitter) == 0x20, "sizeof FragmentPacketSplitter");
static_assert(offsetof(FragmentPacketSplitter, Command) == 0x8, "FragmentPacketSplitter::Command");
static_assert(offsetof(FragmentPacketSplitter, TotalSize) == 0x10, "FragmentPacketSplitter::TotalSize");
static_assert(offsetof(FragmentPacketSplitter, CurSize) == 0x18, "FragmentPacketSplitter::CurSize");

class FragmentPacket
{
public:
    FragmentPacket(short command, char const* format);  // 0x2420
    ~FragmentPacket();                                  // 0x24e0

    void StartRepeat();                                 // 0x37f0
    void IncRepeatCount();                              // 0x3840
    int FreeSize() const;                               // 0x38a0 ❓ return type
    unsigned short Compose(int n, ...);                 // 0x38c0 ❓ return type

    int count;
    Packet packet;
    FragmentPacketSplitter splitter;
    RepeatPacketComposer composer;
};
static_assert(sizeof(FragmentPacket) == 0xF8, "sizeof FragmentPacket");
static_assert(offsetof(FragmentPacket, packet) == 0x8, "FragmentPacket::packet");
static_assert(offsetof(FragmentPacket, splitter) == 0x30, "FragmentPacket::splitter");
static_assert(offsetof(FragmentPacket, composer) == 0x50, "FragmentPacket::composer");

class FragmentPacketConcatenater : public PacketConcatenateBuffer
{
public:
    // ❓ The constructor is inlined (Clone 0x2870, __pump_fragment_packet 0x1bc0).
    FragmentPacketConcatenater()
    {
        buffer = nullptr;
        size = 0;
        gbuffer = nullptr;
        gbufsize = 0;
        decomposer.format = nullptr;
        decomposer.len = 0;
        decomposer.index = 0;
        decomposer.offset = 0;
        decomposer.top = -1;
        Command = 0;
        TotalSize = 0;
        relayPacket.Splitter = nullptr;
        relayPacket.IsFragmentPacket = false;
        relayPacket.FragmentPacketCmd = 0;
        relayPacket.CurHeader = nullptr;
        relayPacket.ListHead = nullptr;
        relayPacket.ListTail = nullptr;
    }
    virtual ~FragmentPacketConcatenater();                       // 0x2510
    virtual void Clear();                                        // 0x2590
    virtual short check(char const* buffer, short size);         // 0x2810
    virtual unsigned long long AllocSize() const;                // 0x2860
    virtual PacketConcatenater* Clone(void* buffer) const;       // 0x2870
    virtual void Destroy(void* buffer);                          // 0x2920

    bool Add(Packet const* packet, bool* completed, bool added); // 0x25d0
    bool Copy(FragmentPacketConcatenater* fpc);                  // 0x2770

    short Command;
    int TotalSize;
    Packet relayPacket;
};
static_assert(sizeof(FragmentPacketConcatenater) == 0x90, "sizeof FragmentPacketConcatenater");
static_assert(offsetof(FragmentPacketConcatenater, Command) == 0x60, "FragmentPacketConcatenater::Command");
static_assert(offsetof(FragmentPacketConcatenater, TotalSize) == 0x64, "FragmentPacketConcatenater::TotalSize");
static_assert(offsetof(FragmentPacketConcatenater, relayPacket) == 0x68, "FragmentPacketConcatenater::relayPacket");

struct FragmentPacketWrap
{
    FragmentPacket* _child;
    FragmentPacketWrap* _NEXT;
};
static_assert(sizeof(FragmentPacketWrap) == 0x10, "sizeof FragmentPacketWrap");
