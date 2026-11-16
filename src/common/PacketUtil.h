// PacketUtil.obj (LobbyGate PDB): PacketFormatIterator, RepeatPacketComposer, RepeatPacketDecomposer,
// PacketConcatenater, PacketConcatenateBuffer. Layouts from include/pdb/LobbyGate/types.h.
#pragma once
#include <stddef.h>

class Packet;

class PacketFormatIterator
{
public:
    virtual void Reset() { index = 0; }  // slot 0 ❓ no out-of-line copy in LobbyGate.exe
    virtual void SetFormat(char const* format, int start);  // slot 1
    virtual void Forward(int index);                        // slot 2
    virtual void Rewind(int index);                         // slot 3
    virtual void Allocated(Packet*, char const*) {}         // slot 4 ❓ empty, folds with Console::Flush
    virtual char const* CurrentFormat() const;              // slot 5
    virtual int GetIndex() const;                           // slot 6
    virtual void skipRepeatFormat();                        // slot 7

    char const* format;
    int len;
    int index;
};
static_assert(sizeof(PacketFormatIterator) == 0x18, "sizeof PacketFormatIterator");
static_assert(offsetof(PacketFormatIterator, format) == 0x8, "PacketFormatIterator::format");
static_assert(offsetof(PacketFormatIterator, len) == 0x10, "PacketFormatIterator::len");
static_assert(offsetof(PacketFormatIterator, index) == 0x14, "PacketFormatIterator::index");

class PacketComposer : public PacketFormatIterator
{
};
static_assert(sizeof(PacketComposer) == 0x18, "sizeof PacketComposer");

class RepeatPacketComposer : public PacketComposer
{
public:
    struct SubPacketInfo
    {
        unsigned char* size;
        char const* startPos;
        char const* format;
        int index;
    };

    virtual void Reset();
    virtual void Forward(int index);
    virtual void Rewind(int index);
    virtual void Allocated(Packet* packet, char const* oldFreeBody);
    virtual char const* CurrentFormat() const;
    virtual void skipRepeatFormat();

    void PushRepeatCount(Packet* packet);
    void PopRepeatCount();

    short* counts[3];
    int start[3];
    int top;
    SubPacketInfo sub[3];
    int subTop;
};
static_assert(sizeof(RepeatPacketComposer::SubPacketInfo) == 0x20, "sizeof RepeatPacketComposer::SubPacketInfo");
static_assert(sizeof(RepeatPacketComposer) == 0xA8, "sizeof RepeatPacketComposer");
static_assert(offsetof(RepeatPacketComposer, counts) == 0x18, "RepeatPacketComposer::counts");
static_assert(offsetof(RepeatPacketComposer, start) == 0x30, "RepeatPacketComposer::start");
static_assert(offsetof(RepeatPacketComposer, top) == 0x3C, "RepeatPacketComposer::top");
static_assert(offsetof(RepeatPacketComposer, sub) == 0x40, "RepeatPacketComposer::sub");
static_assert(offsetof(RepeatPacketComposer, subTop) == 0xA0, "RepeatPacketComposer::subTop");

class PacketConcatenater
{
public:
    virtual void Clear() = 0;                                    // slot 0
    virtual unsigned long long AllocSize() const = 0;            // slot 1
    virtual PacketConcatenater* Clone(void* buffer) const = 0;   // slot 2
    virtual void Destroy(void* buffer) = 0;                      // slot 3
};
static_assert(sizeof(PacketConcatenater) == 0x8, "sizeof PacketConcatenater");

class PacketDecomposer : public PacketFormatIterator
{
public:
    virtual void Reset()  // ❓ no out-of-line copy in LobbyGate.exe
    {
        index = 0;
        offset = 0;
    }

    unsigned int offset;
};
static_assert(sizeof(PacketDecomposer) == 0x20, "sizeof PacketDecomposer");
static_assert(offsetof(PacketDecomposer, offset) == 0x18, "PacketDecomposer::offset");

class RepeatPacketDecomposer : public PacketDecomposer
{
public:
    virtual void Reset();

    int PopRepeatCount();
    int PushRepeatCount(char const* buffer, int size);

    short counts[3];
    int start[3];
    int top;
};
static_assert(sizeof(RepeatPacketDecomposer) == 0x38, "sizeof RepeatPacketDecomposer");
static_assert(offsetof(RepeatPacketDecomposer, counts) == 0x20, "RepeatPacketDecomposer::counts");
static_assert(offsetof(RepeatPacketDecomposer, start) == 0x28, "RepeatPacketDecomposer::start");
static_assert(offsetof(RepeatPacketDecomposer, top) == 0x34, "RepeatPacketDecomposer::top");

class PacketConcatenateBuffer : public PacketConcatenater
{
public:
    struct VarData
    {
        short* size;
        char* buffer;
    };

    virtual ~PacketConcatenateBuffer();                        // slot 4
    virtual short check(char const* buffer, short size) = 0;   // slot 5
    virtual bool copy(PacketConcatenateBuffer* pcb);           // slot 6
    virtual void Clear();

    bool Add(char const* buffer, short size);
    bool Decompose(int n, ...);
    int Decompose(VarData* data);

    char const* buffer;
    int size;
    char* gbuffer;
    int gbufsize;
    RepeatPacketDecomposer decomposer;
};
static_assert(sizeof(PacketConcatenateBuffer::VarData) == 0x10, "sizeof PacketConcatenateBuffer::VarData");
static_assert(sizeof(PacketConcatenateBuffer) == 0x60, "sizeof PacketConcatenateBuffer");
static_assert(offsetof(PacketConcatenateBuffer, buffer) == 0x8, "PacketConcatenateBuffer::buffer");
static_assert(offsetof(PacketConcatenateBuffer, size) == 0x10, "PacketConcatenateBuffer::size");
static_assert(offsetof(PacketConcatenateBuffer, gbuffer) == 0x18, "PacketConcatenateBuffer::gbuffer");
static_assert(offsetof(PacketConcatenateBuffer, gbufsize) == 0x20, "PacketConcatenateBuffer::gbufsize");
static_assert(offsetof(PacketConcatenateBuffer, decomposer) == 0x28, "PacketConcatenateBuffer::decomposer");
