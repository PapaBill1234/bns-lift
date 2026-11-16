// SessionBuffer.obj (CacheGate PDB). Layouts from include/pdb/CacheGate/types.h.
#pragma once
#include <winsock2.h>
#include <stddef.h>
#include "Connection.h"

class PacketBuffer;
class PacketBufferHandler;
class Session;

struct SendBufferList
{
    bool _external;
    unsigned int _size;
    unsigned int _count;
    void* _wsaBuffer;  // WSABUF[_size]
    PacketBuffer** _pbuffer;
    SendBufferList* _next;
};
static_assert(sizeof(SendBufferList) == 0x28, "sizeof SendBufferList");
static_assert(offsetof(SendBufferList, _wsaBuffer) == 0x10, "SendBufferList::_wsaBuffer");
static_assert(offsetof(SendBufferList, _next) == 0x20, "SendBufferList::_next");

class SessionRecvBuffer
{
public:
    virtual ~SessionRecvBuffer();  // 0x1A310 (scalar deleting destructor)

    AsyncRecvContext _context;
    unsigned int _recvdSize;
    char _buffer[4008];
};
static_assert(sizeof(SessionRecvBuffer) == 0xFF8, "sizeof SessionRecvBuffer");
static_assert(offsetof(SessionRecvBuffer, _recvdSize) == 0x48, "SessionRecvBuffer::_recvdSize");
static_assert(offsetof(SessionRecvBuffer, _buffer) == 0x4C, "SessionRecvBuffer::_buffer");

class SessionSendBuffer
{
public:
    virtual ~SessionSendBuffer();  // 0x1A320 (vector deleting destructor)

protected:
    AsyncSendContext* Add(PacketBuffer const** const pbufferList, int count);  // 0x1A350
    AsyncSendContext* RemoveSentBuffer(unsigned long sentSize);               // 0x1A4F0
    bool Initialize(unsigned char* freeBuffer, unsigned long long freeSize);   // 0x1A6B0
    void Clear();                                                             // 0x1A750

private:
    void increaseBuffer(SendBufferList* bufferList);         // 0x1A810
    void clearPacketBufferList(SendBufferList* bufferList);  // 0x1A980

public:
    AsyncSendContext _context;
    PacketBufferHandler* _bufferHandler;
    SendBufferList _bufferList[2];
    SendBufferList* _curSendingList;
    long long _maxBufferCount;

    friend class Session;
};
static_assert(sizeof(SessionSendBuffer) == 0xA8, "sizeof SessionSendBuffer");
static_assert(offsetof(SessionSendBuffer, _bufferHandler) == 0x40, "SessionSendBuffer::_bufferHandler");
static_assert(offsetof(SessionSendBuffer, _bufferList) == 0x48, "SessionSendBuffer::_bufferList");
static_assert(offsetof(SessionSendBuffer, _curSendingList) == 0x98, "SessionSendBuffer::_curSendingList");
static_assert(offsetof(SessionSendBuffer, _maxBufferCount) == 0xA0, "SessionSendBuffer::_maxBufferCount");
