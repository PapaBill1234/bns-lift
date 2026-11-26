// Packet.obj (SmartCouponDaemon PDB). Layouts from include/pdb/CacheGate/types.h and the SmartCouponDaemon PDB.
#pragma once
#include <stddef.h>

class PacketBuffer;
class PacketComposer;
class PacketCrypt;
class PacketConcatenateHandler;
class PacketDecomposer;

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

    struct VarData
    {
        short* size;
        char* buffer;
    };

    struct VarStr
    {
        short* len;
        wchar_t* str;
    };

    // PDB: public ctor Packet::Packet(PacketSplitter*), inlined at each use (the originals zero the 6 fields before
    // Packet::Allocate). LIFT: without it `Packet p;` leaves Splitter and ListHead uninitialized and Allocate reads them.
    explicit Packet(PacketSplitter* splitter = nullptr)
        : Splitter(splitter), IsFragmentPacket(false), FragmentPacketCmd(0), CurHeader(nullptr), ListHead(nullptr), ListTail(nullptr)
    {
    }
    ~Packet();
    void Clear();
    char const* Allocate();
    unsigned short Compose(char const* format, ...);
    void AddSize(short size);
    unsigned short Decompose(char const* format, ...) const;
    unsigned short Decompose(unsigned int offset, int n, char const* format, ...) const; // 0x220D0 (PostOfficeDaemon)
    unsigned short ComposeText(char const* format, ...);         // 0x21EB0 (PostOfficeDaemon)
    unsigned short DecomposeText(char const* format, ...) const; // 0x22220 (PostOfficeDaemon)
    char const* Allocate(PacketComposer* pcr);
    unsigned short Compose(PacketComposer* pcr, int n, ...);  // 0xde140 (LobbyDaemon)
    unsigned short ComposeV(PacketComposer* pcr, int n, char* args);
    void Add(void const* data, short size);
    void Copy(Packet const* packet);
    void Encrypt(PacketCrypt* crypt);
    void Finalize(PacketCrypt* crypt);
    void Concatenate(Packet const* packet, PacketConcatenateHandler const* concatHandler);           // 0x7300 (CacheGate)
    void Concatenate(char const* buffer, short size, PacketConcatenateHandler const* concatHandler);           // 0x7470 (CacheGate), PDB size is short
    unsigned short Decompose(PacketDecomposer* pdr, int n, ...) const;                                // 0x75B0 (CacheGate)
    unsigned short Decompose(PacketDecomposer* pdr, VarStr* str) const;                               // 0xde970 (LobbyDaemon)
    unsigned short Decompose(PacketDecomposer* pdr, VarData* data) const;                             // 0xdeab0 (LobbyDaemon)
    unsigned short FreeSize();                                                                        // 0x29D0 (LobbyDaemon)

    // 0x14280 (inline)
    char const* GetFreeBody() const
    {
        return CurHeader != nullptr ? reinterpret_cast<char const*>(CurHeader) + CurHeader->size : nullptr;
    }

    PacketSplitter* Splitter;
    bool IsFragmentPacket;
    int FragmentPacketCmd;
    Header* CurHeader;
    PacketBuffer* ListHead;
    PacketBuffer* ListTail;
};
static_assert(sizeof(Packet::VarData) == 0x10, "sizeof Packet::VarData");
static_assert(sizeof(Packet) == 0x28, "sizeof Packet");
static_assert(offsetof(Packet, Splitter) == 0x0, "Packet::Splitter");
static_assert(offsetof(Packet, IsFragmentPacket) == 0x8, "Packet::IsFragmentPacket");
static_assert(offsetof(Packet, FragmentPacketCmd) == 0xC, "Packet::FragmentPacketCmd");
static_assert(offsetof(Packet, CurHeader) == 0x10, "Packet::CurHeader");
static_assert(offsetof(Packet, ListHead) == 0x18, "Packet::ListHead");
static_assert(offsetof(Packet, ListTail) == 0x20, "Packet::ListTail");
