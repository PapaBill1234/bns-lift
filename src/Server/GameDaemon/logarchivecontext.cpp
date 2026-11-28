// logarchivecontext.cpp: logarchivecontext.cpp (GameDaemon PDB, 2019 + PDB).
#include "logarchivecontext.h"
#include <string.h>
#include <new>
#include "../BloodLib/include/AlertSender.h"
#include "../BloodLib/include/Log.h"
#include "../BloodLib/include/MemoryManager.h"
#include "LiftStub.h"

#pragma comment(linker, "/INCLUDE:??0LogArchiveReadBuffer@@QEAA@XZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:??1LogArchiveReadBuffer@@QEAA@XZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?ClearBuffer@LogArchiveReadBuffer@@QEAA_NXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?PushNetworkData@LogArchiveWriteBuffer@@QEAA_NQEBDI@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?PushFileData@LogArchiveWriteBuffer@@QEAA_NQEBDI@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?ClearFileBuffer@LogArchiveWriteBuffer@@QEAA_NXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:??0LogArchiveWriteContext@@QEAA@H@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?SwitchStatus@LogArchiveWriteContext@@QEAA_NXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetWritingBuffer@LogArchiveWriteContext@@QEBAQEAVLogArchiveWriteBuffer@@XZ")  // LIFT: dead-strip keep (no live caller yet)

static wchar_t const LOG_ARCHIVE_CONTEXT_FILE[] = L"source\\LogArchiveContext.cpp";

// 0x6d8430
__cdecl LogArchiveReadBuffer::LogArchiveReadBuffer(void)
{
    Internal = 0;
    InternalHigh = 0;
    Pointer = nullptr;
    hEvent = nullptr;
    _wsaBuf.buf = static_cast<char *>(Memory::_Manager[2]->AllocZero(0x2000, LOG_ARCHIVE_CONTEXT_FILE, 18));
    if (_wsaBuf.buf == nullptr)
    {
        Log::Write(Log::LT_ERROR, LOG_ARCHIVE_CONTEXT_FILE, 20,
                   L"== CRASH == [log archive], default read buffer allocation failed");
        AlertSender::Write(LOG_ARCHIVE_CONTEXT_FILE, 20,
                           L"== CRASH == [log archive], default read buffer allocation failed");
    }
    _wsaBuf.len = 0x2000;
}

// 0x6d84c0
__cdecl LogArchiveReadBuffer::~LogArchiveReadBuffer(void)
{
    if (_wsaBuf.buf != nullptr)
        Memory::_Manager[2]->Free(_wsaBuf.buf, LOG_ARCHIVE_CONTEXT_FILE, 28);
}

// 0x6d84f0
bool __cdecl LogArchiveReadBuffer::ClearBuffer(void)
{
    if (_wsaBuf.buf != nullptr)
    {
        memset(_wsaBuf.buf, 0, _wsaBuf.len);
        return true;
    }
    // LIFT: HR shows the constant 0 in the Log::Write call (the member is null here). Both calls pass the member.
    Log::Write(Log::LT_ERROR, LOG_ARCHIVE_CONTEXT_FILE, 34,
               L"== CRASH == [log archive], invalid buffer, _wsaBuf.buf:0x%p", _wsaBuf.buf);
    AlertSender::Write(LOG_ARCHIVE_CONTEXT_FILE, 34,
                       L"== CRASH == [log archive], invalid buffer, _wsaBuf.buf:0x%p", _wsaBuf.buf);
    return false;
}

// LIFT: no stand-alone body in the exe. The destructor is inlined in 0x6d8e80 (lines 66 and 69).
__cdecl LogArchiveWriteBuffer::~LogArchiveWriteBuffer(void)
{
    if (_pBufferChunkHead != nullptr)
        Memory::_Manager[2]->Free(_pBufferChunkHead, LOG_ARCHIVE_CONTEXT_FILE, 66);
    if (_pWsaBufs != nullptr)
        Memory::_Manager[2]->Free(_pWsaBufs, LOG_ARCHIVE_CONTEXT_FILE, 69);
}

// 0x6d8560
__cdecl LogArchiveWriteBuffer::LogArchiveWriteBuffer(int mode)
{
    _mode = mode;
    _maxBufferChunkSize = 0x10000;
    _currBufferChunkSize = 0;
    _maxBufferCount = 0x10;
    _currBufferCount = 0;
    _pWsaBufs = nullptr;
    _pBufferChunkHead = static_cast<char *>(Memory::_Manager[2]->AllocZero(0x10000, LOG_ARCHIVE_CONTEXT_FILE, 52));
    _pBufferChunkTail = _pBufferChunkHead;
    if (_pBufferChunkHead == nullptr)
    {
        Log::Write(Log::LT_ERROR, LOG_ARCHIVE_CONTEXT_FILE, 54,
                   L"== CRASH == [log archive], default write buffer chunk allocation failed");
        AlertSender::Write(LOG_ARCHIVE_CONTEXT_FILE, 54,
                           L"== CRASH == [log archive], default write buffer chunk allocation failed");
    }
    if (_mode == 0)
    {
        _pWsaBufs = static_cast<_WSABUF *>(Memory::_Manager[2]->AllocZero(256, LOG_ARCHIVE_CONTEXT_FILE, 57));
        if (_pWsaBufs == nullptr)
        {
            Log::Write(Log::LT_ERROR, LOG_ARCHIVE_CONTEXT_FILE, 59,
                       L"== CRASH == [log archive], default wsabufs allocation failed");
            AlertSender::Write(LOG_ARCHIVE_CONTEXT_FILE, 59,
                               L"== CRASH == [log archive], default wsabufs allocation failed");
        }
    }
}

// 0x6d8650
bool __cdecl LogArchiveWriteBuffer::PushNetworkData(char const *const pBuffer, unsigned int bufferSize)
{
    if (pBuffer == nullptr || bufferSize - 6 > 0x1FFA)
    {
        Log::Write(Log::LT_ERROR, LOG_ARCHIVE_CONTEXT_FILE, 75,
                   L"== CRASH == [log archive], invalid parameter, pBuffer:0x%p, bufferSize:%d", pBuffer, bufferSize);
        AlertSender::Write(LOG_ARCHIVE_CONTEXT_FILE, 75,
                           L"== CRASH == [log archive], invalid parameter, pBuffer:0x%p, bufferSize:%d", pBuffer,
                           bufferSize);
        return false;
    }
    if (_mode != 0 || _pBufferChunkTail == nullptr || _pWsaBufs == nullptr)
    {
        Log::Write(Log::LT_ERROR, LOG_ARCHIVE_CONTEXT_FILE, 79,
                   L"== CRASH == [log archive], invalid buffer, mode:%d, pBufferChunkTail:0x%p, pWsaBufs:0x%p", _mode,
                   _pBufferChunkTail, _pWsaBufs);
        AlertSender::Write(LOG_ARCHIVE_CONTEXT_FILE, 79,
                           L"== CRASH == [log archive], invalid buffer, mode:%d, pBufferChunkTail:0x%p, pWsaBufs:0x%p",
                           _mode, _pBufferChunkTail, _pWsaBufs);
        return false;
    }
    if (_currBufferChunkSize + bufferSize >= _maxBufferChunkSize)
    {
        unsigned int newSize = 2 * _maxBufferChunkSize;
        while (bufferSize + _currBufferChunkSize >= newSize)
            newSize *= 2;
        if (!growBufferChunkSize(newSize))
        {
            Log::Write(Log::LT_ERROR, LOG_ARCHIVE_CONTEXT_FILE, 89,
                       L"[log archive], cannot push to network write buffer");
            return false;
        }
    }
    if (_currBufferCount >= _maxBufferCount && !growBufferCount(2 * _maxBufferCount))
    {
        Log::Write(Log::LT_ERROR, LOG_ARCHIVE_CONTEXT_FILE, 95, L"[log archive], cannot push to network write buffer");
        return false;
    }
    memcpy(_pBufferChunkTail, pBuffer, bufferSize);
    _pWsaBufs[_currBufferCount].buf = _pBufferChunkTail;
    _pWsaBufs[_currBufferCount].len = bufferSize;
    _pBufferChunkTail += bufferSize;
    _currBufferChunkSize += bufferSize;
    ++_currBufferCount;
    return true;
}

// 0x6d8860
bool __cdecl LogArchiveWriteBuffer::PushFileData(char const *const pBuffer, unsigned int bufferSize)
{
    // LIFT: HR compares the size as a signed int (bufferSize > 0).
    if (pBuffer == nullptr || static_cast<int>(bufferSize) <= 0)
    {
        Log::Write(Log::LT_ERROR, LOG_ARCHIVE_CONTEXT_FILE, 114,
                   L"== CRASH == [log archive], invalid parameter, pBuffer:0x%p, bufferSize:%d", pBuffer, bufferSize);
        AlertSender::Write(LOG_ARCHIVE_CONTEXT_FILE, 114,
                           L"== CRASH == [log archive], invalid parameter, pBuffer:0x%p, bufferSize:%d", pBuffer,
                           bufferSize);
        return false;
    }
    if (_mode != 1 || _pBufferChunkTail == nullptr)
    {
        Log::Write(Log::LT_ERROR, LOG_ARCHIVE_CONTEXT_FILE, 118,
                   L"== CRASH == [log archive], invalid buffer, mode:%d, pBufferChunkTail:0x%p", _mode,
                   _pBufferChunkTail);
        AlertSender::Write(LOG_ARCHIVE_CONTEXT_FILE, 118,
                           L"== CRASH == [log archive], invalid buffer, mode:%d, pBufferChunkTail:0x%p", _mode,
                           _pBufferChunkTail);
        return false;
    }
    if (_currBufferChunkSize + bufferSize >= _maxBufferChunkSize)
    {
        unsigned int newSize = 2 * _maxBufferChunkSize;
        while (bufferSize + _currBufferChunkSize >= newSize)
            newSize *= 2;
        if (!growBufferChunkSize(newSize))
        {
            Log::Write(Log::LT_ERROR, LOG_ARCHIVE_CONTEXT_FILE, 128, L"[log archive], cannot push to file write buffer");
            return false;
        }
    }
    memcpy(_pBufferChunkTail, pBuffer, bufferSize);
    _pBufferChunkTail += bufferSize;
    _currBufferChunkSize += bufferSize;
    ++_currBufferCount;
    return true;
}

// 0x6d89e0
bool __cdecl LogArchiveWriteBuffer::ClearNetworkBuffer(void)
{
    if (_mode != 0 || _pBufferChunkHead == nullptr || _pWsaBufs == nullptr)
    {
        Log::Write(Log::LT_ERROR, LOG_ARCHIVE_CONTEXT_FILE, 145,
                   L"== CRASH == [log archive], invalid buffer, mode:%d, pBufferChunkHead:0x%p, pWsaBufs:0x%p", _mode,
                   _pBufferChunkHead, _pWsaBufs);
        AlertSender::Write(LOG_ARCHIVE_CONTEXT_FILE, 145,
                           L"== CRASH == [log archive], invalid buffer, mode:%d, pBufferChunkHead:0x%p, pWsaBufs:0x%p",
                           _mode, _pBufferChunkHead, _pWsaBufs);
        return false;
    }
    memset(_pBufferChunkHead, 0, _currBufferChunkSize);
    _pBufferChunkTail = _pBufferChunkHead;
    _currBufferChunkSize = 0;
    memset(_pWsaBufs, 0, 16ull * _currBufferCount);
    _currBufferCount = 0;
    return true;
}

// 0x6d8aa0
bool __cdecl LogArchiveWriteBuffer::ClearFileBuffer(void)
{
    if (_mode != 1 || _pBufferChunkHead == nullptr)
    {
        Log::Write(Log::LT_ERROR, LOG_ARCHIVE_CONTEXT_FILE, 162,
                   L"== CRASH == [log archive], invalid buffer, mode:%d, pBufferChunkHead:0x%p", _mode,
                   _pBufferChunkHead);
        AlertSender::Write(LOG_ARCHIVE_CONTEXT_FILE, 162,
                           L"== CRASH == [log archive], invalid buffer, mode:%d, pBufferChunkHead:0x%p", _mode,
                           _pBufferChunkHead);
        return false;
    }
    memset(_pBufferChunkHead, 0, _currBufferChunkSize);
    _currBufferChunkSize = 0;
    _currBufferCount = 0;
    _pBufferChunkTail = _pBufferChunkHead;
    return true;
}

// 0x6d8b30
bool __cdecl LogArchiveWriteBuffer::growBufferChunkSize(unsigned int newChunkSize)
{
    if (newChunkSize <= _maxBufferChunkSize)
    {
        Log::Write(Log::LT_ERROR, LOG_ARCHIVE_CONTEXT_FILE, 177,
                   L"== CRASH == [log archive], invalid parameter, newChunkSize:%u", newChunkSize);
        AlertSender::Write(LOG_ARCHIVE_CONTEXT_FILE, 177,
                           L"== CRASH == [log archive], invalid parameter, newChunkSize:%u", newChunkSize);
        return false;
    }
    if (_pBufferChunkHead == nullptr)
    {
        // LIFT: HR passes the constant 0 to the Log::Write call and the member to AlertSender::Write.
        Log::Write(Log::LT_ERROR, LOG_ARCHIVE_CONTEXT_FILE, 181,
                   L"== CRASH == [log archive], invalid buffer, pBufferChunkHead:%d", 0);
        AlertSender::Write(LOG_ARCHIVE_CONTEXT_FILE, 181,
                           L"== CRASH == [log archive], invalid buffer, pBufferChunkHead:%d", _pBufferChunkHead);
        return false;
    }
    char *newHead =
        static_cast<char *>(Memory::_Manager[2]->Realloc(_pBufferChunkHead, newChunkSize, LOG_ARCHIVE_CONTEXT_FILE, 186));
    if (newHead == nullptr)
    {
        Log::Write(LOG_ARCHIVE_CONTEXT_FILE, 188, GetLastError(), L"[log archive], buffer chunk reallocation failed");
        return false;
    }
    _pBufferChunkHead = newHead;
    _pBufferChunkTail = &newHead[_currBufferChunkSize];
    if (_mode == 0)
    {
        // The chunk can move: point each wsabuf at its new place.
        int offset = 0;
        for (unsigned int i = 0; i < _currBufferCount; ++i)
        {
            _pWsaBufs[i].buf = &_pBufferChunkHead[offset];
            offset += _pWsaBufs[i].len;
        }
    }
    _maxBufferChunkSize = newChunkSize;
    return true;
}

// 0x6d8ca0
bool __cdecl LogArchiveWriteBuffer::growBufferCount(unsigned int newBufferCount)
{
    if (newBufferCount <= _maxBufferCount)
    {
        Log::Write(Log::LT_ERROR, LOG_ARCHIVE_CONTEXT_FILE, 214,
                   L"== CRASH == [log archive], invalid parameter, newBufferCount:%u", newBufferCount);
        AlertSender::Write(LOG_ARCHIVE_CONTEXT_FILE, 214,
                           L"== CRASH == [log archive], invalid parameter, newBufferCount:%u", newBufferCount);
        return false;
    }
    if (_mode != 0 || _pWsaBufs == nullptr)
    {
        Log::Write(Log::LT_ERROR, LOG_ARCHIVE_CONTEXT_FILE, 218,
                   L"== CRASH == [log archive], invalid buffer, mode:%d, pWsaBufs:0x%p", _mode, _pWsaBufs);
        AlertSender::Write(LOG_ARCHIVE_CONTEXT_FILE, 218,
                           L"== CRASH == [log archive], invalid buffer, mode:%d, pWsaBufs:0x%p", _mode, _pWsaBufs);
        return false;
    }
    _WSABUF *newBufs = static_cast<_WSABUF *>(
        Memory::_Manager[2]->Realloc(_pWsaBufs, 16ull * newBufferCount, LOG_ARCHIVE_CONTEXT_FILE, 223));
    if (newBufs == nullptr)
    {
        Log::Write(LOG_ARCHIVE_CONTEXT_FILE, 225, GetLastError(), L"[log archive], wsabufs reallocation failed");
        return false;
    }
    _pWsaBufs = newBufs;
    _maxBufferCount = newBufferCount;
    return true;
}

// 0x6d8de0
__cdecl LogArchiveWriteContext::LogArchiveWriteContext(int mode)
{
    _status = 2;
    _mode = mode;
    Internal = 0;
    InternalHigh = 0;
    Pointer = nullptr;
    hEvent = nullptr;
    for (int i = 0; i < 2; ++i)
    {
        LogArchiveWriteBuffer *buffer =
            static_cast<LogArchiveWriteBuffer *>(Memory::_Manager[2]->Alloc(48, LOG_ARCHIVE_CONTEXT_FILE, 247));
        if (buffer != nullptr)
            buffer = new (buffer) LogArchiveWriteBuffer(_mode);
        _pWriteBuffers[i] = buffer;
    }
}

// 0x6d8e80
__cdecl LogArchiveWriteContext::~LogArchiveWriteContext(void)
{
    LIFT_STUB(0x6d8e80);
}

// 0x6d8f20
bool __cdecl LogArchiveWriteContext::SwitchStatus(void)
{
    switch (_status)
    {
    case 0:
        _status = 1;
        return true;
    case 1:
    case 2:
        _status = 0;
        return true;
    default:
        Log::Write(Log::LT_ERROR, LOG_ARCHIVE_CONTEXT_FILE, 269,
                   L"== CRASH == [log archive], invalid status, status:%d", _status);
        AlertSender::Write(LOG_ARCHIVE_CONTEXT_FILE, 269, L"== CRASH == [log archive], invalid status, status:%d",
                           _status);
        return false;
    }
}

// 0x6d8fa0
::LogArchiveWriteBuffer *const __cdecl LogArchiveWriteContext::GetWritingBuffer(void) const
{
    if (_status == 2)
    {
        Log::Write(Log::LT_ERROR, LOG_ARCHIVE_CONTEXT_FILE, 278,
                   L"== CRASH == [log archive], invalid status, status:%d", 2);
        AlertSender::Write(LOG_ARCHIVE_CONTEXT_FILE, 278, L"== CRASH == [log archive], invalid status, status:%d",
                           _status);
        return nullptr;
    }
    if (_status != 0)
        return _pWriteBuffers[1];
    return _pWriteBuffers[0];
}
