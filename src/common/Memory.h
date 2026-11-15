// Memory.obj (CacheGate PDB).
#pragma once
#include <stddef.h>
#include "MemoryManager.h"

class Memory
{
public:
    enum MgrType
    {
        MMGR_DEFAULT = 0,
        MMGR_DEBUG = 1,
        MMGR_MAX = 2,
    };

    static MemoryManager const* CreateManager(MgrType type, void const* option, unsigned long long size,
                                              bool createAllocationHistory);

    // The PDB array has 24 bytes (3 entries). StlAllocator<T,2> uses entry 2.
    static MemoryManager const* _Manager[3];
};

class GrowingBuffer
{
public:
    // ❓ Inlined in RawPacketBufferHandler::Clone (0x216F0). The arguments are a guess from the stores.
    GrowingBuffer(int sec, unsigned long long initSize)
        : _sec(sec), _initSize(initSize), _size(0), _count(0), _buffer(nullptr)
    {
    }
    virtual ~GrowingBuffer();  // slot 0

private:
    void grow(unsigned long long size);

public:
    int _sec;
    unsigned long long _initSize;
    unsigned long long _size;
    unsigned long long _count;
    unsigned char* _buffer;

    friend class RawPacketBufferHandler;  // ❓ ToPacket (0x21860) calls the inlined grow path.
};
static_assert(sizeof(GrowingBuffer) == 0x30, "sizeof GrowingBuffer");
static_assert(offsetof(GrowingBuffer, _sec) == 0x8, "GrowingBuffer::_sec");
static_assert(offsetof(GrowingBuffer, _initSize) == 0x10, "GrowingBuffer::_initSize");
static_assert(offsetof(GrowingBuffer, _size) == 0x18, "GrowingBuffer::_size");
static_assert(offsetof(GrowingBuffer, _count) == 0x20, "GrowingBuffer::_count");
static_assert(offsetof(GrowingBuffer, _buffer) == 0x28, "GrowingBuffer::_buffer");
