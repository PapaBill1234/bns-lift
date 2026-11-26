// SessionBuffer.obj (CacheGate PDB).
#include "SessionBuffer.h"
#include <string.h>
#include "AlertSender.h"
#include "Log.h"
#include "MemoryManager.h"
#include "PacketBuffer.h"
#include "PacketBufferHandler.h"
#include "Session.h"

static wchar_t const SESSIONBUFFER_FILE[] = L"source\\SessionBuffer.cpp";

// 0x1A310 scalar deleting destructor. The body only resets the vtable.
SessionRecvBuffer::~SessionRecvBuffer()
{
}

// 0x1A320 vector deleting destructor
SessionSendBuffer::~SessionSendBuffer()
{
    Clear();
}

// 0x1A350
AsyncSendContext* SessionSendBuffer::Add(PacketBuffer const** const pbufferList, int count)
{
    AsyncSendContext* context = nullptr;
    // LIFT: good path first, error block last, as in the original block order (0x1a350).
    if (pbufferList != nullptr)
    {
        char* buf = nullptr;
        SendBufferList* next = _curSendingList != nullptr ? _curSendingList->_next : &_bufferList[0];
        for (PacketBuffer* i = const_cast<PacketBuffer*>(pbufferList[0]); i != nullptr; i = i->Next)
        {
            if (next->_size <= next->_count + 1)
                increaseBuffer(next);
            i->addReferenceCount(false, SESSIONBUFFER_FILE, 116);
            char const* sendBuffer = i->sendBuffer != nullptr ? i->sendBuffer : &i->Buffer[8];
            WSABUF* wsaBuffer = static_cast<WSABUF*>(next->_wsaBuffer);
            wsaBuffer[next->_count].len =
                _bufferHandler->ToBuffer(nullptr, i->Buffer, 4008, sendBuffer, const_cast<char const**>(&buf));
            wsaBuffer[next->_count].buf = buf;
            next->_pbuffer[next->_count++] = i;
        }
        if (_curSendingList == nullptr && next->_count != 0)
        {
            _curSendingList = next;
            _context._bufferList = next;
            context = &_context;
        }
        long long total =
            static_cast<long long>(_bufferList[0]._count + static_cast<unsigned long long>(_bufferList[1]._count));
        if (_maxBufferCount < total)
            _maxBufferCount = total;
        return context;
    }

    // LIFT: LTCG put constants in the log: count = 1 (0x1A4AD, 0x1A4BA), pbufferList = 0 (ebp, 0x1A35A).
    Log::Write(Log::LT_ERROR, SESSIONBUFFER_FILE, 94,
               L"== CRASH == [session], send parameter is invalid, count %d, pbufferList: %p", count, pbufferList);
    AlertSender::Write(SESSIONBUFFER_FILE, 94,
                       L"== CRASH == [session], send parameter is invalid, count %d, pbufferList: %p", count,
                       pbufferList);
    return nullptr;
}

// 0x1A4F0
AsyncSendContext* SessionSendBuffer::RemoveSentBuffer(unsigned long sentSize)
{
    // LIFT: error block first, as in the original block order (0x1a4f0: Log::Write before removeReferenceCount).
    if (_curSendingList == nullptr)
    {
        Log::Write(Log::LT_ERROR, SESSIONBUFFER_FILE, 163,
                   L"== CRASH == [session], cannot remove send buffer; curSendingList is NULL, session-id:%I64X, "
                   L"sent-size:%u, context-buffer:0x%p, context-buffer-count:%d",
                   _context._session->_id, sentSize, _context._bufferList,
                   _context._bufferList != nullptr ? _context._bufferList->_count : 0);
        AlertSender::Write(SESSIONBUFFER_FILE, 163,
                           L"== CRASH == [session], cannot remove send buffer; curSendingList is NULL, session-id:%I64X, "
                           L"sent-size:%u, context-buffer:0x%p, context-buffer-count:%d",
                           _context._session->_id, sentSize, _context._bufferList,
                           _context._bufferList != nullptr ? _context._bufferList->_count : 0);
        return nullptr;
    }

    for (unsigned int i = 0; i < _curSendingList->_count; ++i)
    {
        if (_curSendingList->_pbuffer[i] != nullptr)
            _curSendingList->_pbuffer[i]->removeReferenceCount(SESSIONBUFFER_FILE, 175);
        _curSendingList->_pbuffer[i] = nullptr;
        WSABUF* wsaBuffer = static_cast<WSABUF*>(_curSendingList->_wsaBuffer);
        wsaBuffer[i].buf = nullptr;
        wsaBuffer[i].len = 0;
    }
    _curSendingList->_count = 0;
    SendBufferList* next = _curSendingList->_next;
    if (next->_count != 0)
    {
        _curSendingList = next;
        _context._bufferList = next;
        return &_context;
    }
    _curSendingList = nullptr;
    _context._bufferList = nullptr;
    return nullptr;
}

// 0x1A6B0
bool SessionSendBuffer::Initialize(unsigned char* freeBuffer, unsigned long long freeSize)
{
    (void)freeSize;  // The original code does not use it.
    // LIFT: unsigned index (0x1a6b0 computes (i - 1) & 1 with no 0xffffffff constant).
    for (unsigned int i = 0; i < 2; ++i)
    {
        if (_bufferList[i]._size != 0)
        {
            Log::Write(Log::LT_ERROR, SESSIONBUFFER_FILE, 216,
                       L"== CRASH == [session], SessionSendBuffer Initialize error");
            AlertSender::Write(SESSIONBUFFER_FILE, 216, L"== CRASH == [session], SessionSendBuffer Initialize error");
            return false;
        }
        _bufferList[i]._wsaBuffer = freeBuffer;
        freeBuffer += 672;  // 42 * sizeof(WSABUF)
        _bufferList[i]._pbuffer = reinterpret_cast<PacketBuffer**>(freeBuffer);
        freeBuffer += 336;  // 42 * sizeof(PacketBuffer*)
        _bufferList[i]._external = false;
        _bufferList[i]._size = 42;
        _bufferList[i]._count = 0;
        _bufferList[i]._next = &_bufferList[(i + 1) & 1];
    }
    return true;
}

// 0x1A750
void SessionSendBuffer::Clear()
{
    for (int i = 0; i < 2; ++i)
    {
        SendBufferList* bufferList = &_bufferList[i];
        clearPacketBufferList(bufferList);
        if (bufferList->_external)
        {
            if (bufferList->_wsaBuffer != nullptr)
            {
                BASE_MEMORY_MANAGER.Free(bufferList->_wsaBuffer, SESSIONBUFFER_FILE, 255);
                bufferList->_wsaBuffer = nullptr;
            }
            if (bufferList->_pbuffer != nullptr)
            {
                BASE_MEMORY_MANAGER.Free(bufferList->_pbuffer, SESSIONBUFFER_FILE, 260);
                bufferList->_pbuffer = nullptr;
            }
            bufferList->_size = 0;
            bufferList->_external = false;
        }
    }
    _curSendingList = nullptr;
}

// 0x1A810
void SessionSendBuffer::increaseBuffer(SendBufferList* bufferList)
{
    unsigned int size = bufferList->_size;
    // LIFT: the not-external path first, as in the original block order (0x1a810: AllocZero before ReallocZero).
    if (bufferList->_external == false)
    {
        void* wsaBuffer = bufferList->_wsaBuffer;
        PacketBuffer** pbuffer = bufferList->_pbuffer;
        bufferList->_size = 2;
        while (bufferList->_size < size * 2)
            bufferList->_size *= 2;
        bufferList->_external = true;
        bufferList->_wsaBuffer = BASE_MEMORY_MANAGER.AllocZero(
            sizeof(WSABUF) * static_cast<unsigned long long>(bufferList->_size), SESSIONBUFFER_FILE, 289);
        bufferList->_pbuffer = static_cast<PacketBuffer**>(BASE_MEMORY_MANAGER.AllocZero(
            sizeof(PacketBuffer*) * static_cast<unsigned long long>(bufferList->_size), SESSIONBUFFER_FILE, 290));
        if (wsaBuffer != nullptr)
            memcpy(bufferList->_wsaBuffer, wsaBuffer, sizeof(WSABUF) * static_cast<unsigned long long>(size));
        if (pbuffer != nullptr)
            memcpy(bufferList->_pbuffer, pbuffer, sizeof(PacketBuffer*) * static_cast<unsigned long long>(size));
    }
    else
    {
        bufferList->_size = size * 2;
        bufferList->_wsaBuffer = BASE_MEMORY_MANAGER.ReallocZero(
            bufferList->_wsaBuffer, sizeof(WSABUF) * static_cast<unsigned long long>(bufferList->_size),
            sizeof(WSABUF) * static_cast<unsigned long long>(size), SESSIONBUFFER_FILE, 305);
        bufferList->_pbuffer = static_cast<PacketBuffer**>(BASE_MEMORY_MANAGER.ReallocZero(
            bufferList->_pbuffer, sizeof(PacketBuffer*) * static_cast<unsigned long long>(bufferList->_size),
            sizeof(PacketBuffer*) * static_cast<unsigned long long>(size), SESSIONBUFFER_FILE, 306));
    }
}

// 0x1A980
// LIFT: noinline. The original Clear (0x1a750) calls this function in all 4 exes. VS2010 /LTCG inlines it without the attribute.
// LIFT: per-exe form. The path of include\RefCntObject.h is the build path of each exe (pseudocode of 4 exes).
#if defined(LIFT_EXE_LG)
#define SESSIONBUFFER_REFCNT_EXE L"lobbygate"
#elif defined(LIFT_EXE_SCD)
#define SESSIONBUFFER_REFCNT_EXE L"smartcoupondaemon"
#elif defined(LIFT_EXE_POD)
#define SESSIONBUFFER_REFCNT_EXE L"postofficedaemon"
#elif defined(LIFT_EXE_LD)
#define SESSIONBUFFER_REFCNT_EXE L"lobbydaemon"
#else
#define SESSIONBUFFER_REFCNT_EXE L"cachegate"
#endif
#define SESSIONBUFFER_REFCNT_HEADER                                                                                        \
    L"e:\\dailybuild02\\" SESSIONBUFFER_REFCNT_EXE                                                                       \
    L"-common-0.0.348\\depot\\branch\\348nc\\program\\server\\bloodlib\\include\\RefCntObject.h"

// LIFT: the original inlines RefCntObject::removeReferenceCount here, but calls RefCntHistory::add out of line
// (CacheGate 0x1aa73). Our compiler also inlines add. The body of removeReferenceCount is here by hand, and
// inline_depth(0) keeps the call to add (lessons A20).
#if defined(_MSC_VER) && !defined(__clang__)
#pragma inline_depth(0)
#endif
__declspec(noinline) void SessionSendBuffer::clearPacketBufferList(SendBufferList* bufferList)
{
    if (bufferList->_pbuffer != nullptr)
    {
        for (unsigned int i = 0; i < bufferList->_count; ++i)
        {
            if (bufferList->_pbuffer[i] != nullptr)
            {
                // LIFT: RefCntObject::removeReferenceCount(SESSIONBUFFER_FILE, 321), inlined (RefCntObject.h:177).
                PacketBuffer* pbuffer = bufferList->_pbuffer[i];
                if (pbuffer->_ref <= 0)
                {
                    Log::Write(Log::LT_ERROR, SESSIONBUFFER_REFCNT_HEADER, 177,
                               L"== CRASH == [ref obj], cannot remove reference count, this:0x%p, ref:%d, tag:0x%08x, file:%s, line:%d",
                               pbuffer, pbuffer->_ref, pbuffer->_tag, SESSIONBUFFER_FILE, 321);
                    AlertSender::Write(SESSIONBUFFER_REFCNT_HEADER, 177,
                                       L"== CRASH == [ref obj], cannot remove reference count, this:0x%p, ref:%d, tag:0x%08x, file:%s, line:%d",
                                       pbuffer, pbuffer->_ref, pbuffer->_tag, SESSIONBUFFER_FILE, 321);
                }
                else
                {
                    if (pbuffer->_history != nullptr)
                        pbuffer->_history->add(pbuffer->_ref, SESSIONBUFFER_FILE, 321, RefCntHistory::OP_DELREF);
                    long ref = InterlockedDecrement(&pbuffer->_ref);
                    if (ref == 0)
                        pbuffer->deallocate_object(SESSIONBUFFER_FILE, 321);
                }
                bufferList->_pbuffer[i] = nullptr;
            }
        }
        bufferList->_count = 0;
    }
}
#if defined(_MSC_VER) && !defined(__clang__)
#pragma inline_depth()
#endif
