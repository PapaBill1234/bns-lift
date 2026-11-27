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

// LIFT: GameDaemon only (card lift-gamedaemon-0c). Types of the declarations in Packet.
class PacketComposer;
class PacketDecomposer;
class RepeatPacketComposer;
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
    // The original stores are in this order (LobbyDaemon 0x67b0: +0x10, +0x0, +0x18, +0x20, +0x8, +0xc; 136 of the
    // 143 former manual zeroing blocks).
    explicit Packet(PacketSplitter* splitter = nullptr)
    {
        CurHeader = nullptr;
        Splitter = splitter;
        ListHead = nullptr;
        ListTail = nullptr;
        IsFragmentPacket = false;
        FragmentPacketCmd = 0;
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
    // LIFT: GameDaemon only (card lift-gamedaemon-0c). Declarations for the wave-0 stubs in
    // src/Server/GameDaemon. They add no code to the other exes.
public:
    void __cdecl IncRepeatCount(::RepeatPacketComposer *);  // GameDaemon 0xac70
    bool __cdecl Reserve(::PacketComposer const *, ::Packet::VarData *);  // GameDaemon 0x6910a0
    void __cdecl GrowAdd(void const *, short);  // GameDaemon 0x6912c0
    void __cdecl Restore(short);  // GameDaemon 0x6915e0
    unsigned short __cdecl DecomposeV(::PacketDecomposer *, int, char *) const;  // GameDaemon 0x691ef0
    void __cdecl setRecvBuffer(char const *);  // GameDaemon 0x692220
};
static_assert(sizeof(Packet::VarData) == 0x10, "sizeof Packet::VarData");
static_assert(sizeof(Packet) == 0x28, "sizeof Packet");
static_assert(offsetof(Packet, Splitter) == 0x0, "Packet::Splitter");
static_assert(offsetof(Packet, IsFragmentPacket) == 0x8, "Packet::IsFragmentPacket");
static_assert(offsetof(Packet, FragmentPacketCmd) == 0xC, "Packet::FragmentPacketCmd");
static_assert(offsetof(Packet, CurHeader) == 0x10, "Packet::CurHeader");
static_assert(offsetof(Packet, ListHead) == 0x18, "Packet::ListHead");
static_assert(offsetof(Packet, ListTail) == 0x20, "Packet::ListTail");
