// logarchivecontext.cpp: logarchivecontext.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "logarchivecontext.h"
#include <string.h>
#include "../BloodLib/include/AlertSender.h"
#include "../BloodLib/include/Log.h"
#include "../BloodLib/include/MemoryManager.h"
#include "LiftStub.h"

#pragma comment(linker, "/INCLUDE:??0LogArchiveReadBuffer@@QEAA@XZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:??1LogArchiveReadBuffer@@QEAA@XZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?ClearBuffer@LogArchiveReadBuffer@@QEAA_NXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:??1LogArchiveWriteContext@@QEAA@XZ")  // LIFT: dead-strip keep (no live caller yet)

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
__cdecl LogArchiveWriteBuffer::LogArchiveWriteBuffer(int)
{
    LIFT_STUB(0x6d8560);
}

// 0x6d8650
bool __cdecl LogArchiveWriteBuffer::PushNetworkData(char const *const, unsigned int)
{
    LIFT_STUB(0x6d8650);
}

// 0x6d8860
bool __cdecl LogArchiveWriteBuffer::PushFileData(char const *const, unsigned int)
{
    LIFT_STUB(0x6d8860);
}

// 0x6d89e0
bool __cdecl LogArchiveWriteBuffer::ClearNetworkBuffer(void)
{
    LIFT_STUB(0x6d89e0);
}

// 0x6d8aa0
bool __cdecl LogArchiveWriteBuffer::ClearFileBuffer(void)
{
    LIFT_STUB(0x6d8aa0);
}

// 0x6d8b30
bool __cdecl LogArchiveWriteBuffer::growBufferChunkSize(unsigned int)
{
    LIFT_STUB(0x6d8b30);
}

// 0x6d8ca0
bool __cdecl LogArchiveWriteBuffer::growBufferCount(unsigned int)
{
    LIFT_STUB(0x6d8ca0);
}

// 0x6d8de0
__cdecl LogArchiveWriteContext::LogArchiveWriteContext(int)
{
    LIFT_STUB(0x6d8de0);
}

// 0x6d8e80
__cdecl LogArchiveWriteContext::~LogArchiveWriteContext(void)
{
    for (int i = 0; i < 2; ++i)
    {
        LogArchiveWriteBuffer *buffer = _pWriteBuffers[i];
        if (buffer != nullptr)
        {
            buffer->~LogArchiveWriteBuffer();
            Memory::_Manager[2]->Free(buffer, LOG_ARCHIVE_CONTEXT_FILE, 255);
        }
    }
}

// 0x6d8f20
bool __cdecl LogArchiveWriteContext::SwitchStatus(void)
{
    LIFT_STUB(0x6d8f20);
}

// 0x6d8fa0
::LogArchiveWriteBuffer *const __cdecl LogArchiveWriteContext::GetWritingBuffer(void) const
{
    LIFT_STUB(0x6d8fa0);
}
