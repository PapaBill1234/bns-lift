// logarchivecontext.h: logarchivecontext.cpp (GameDaemon PDB, 2019 + PDB).
#pragma once
#include "GameDaemonFwd.h"

// PDB: LogArchiveReadBuffer (GameDaemon), size 0x30. Base _OVERLAPPED +0.
class LogArchiveReadBuffer : public _OVERLAPPED
{
public:
    __cdecl LogArchiveReadBuffer(void);  // 0x6d8430
    __cdecl ~LogArchiveReadBuffer(void);  // 0x6d84c0
    bool __cdecl ClearBuffer(void);  // 0x6d84f0

private:
    _WSABUF _wsaBuf;  // +0x20
};
static_assert(sizeof(LogArchiveReadBuffer) == 0x30, "sizeof LogArchiveReadBuffer");
static_assert(offsetof(LogArchiveReadBuffer, _wsaBuf) == 0x20, "LogArchiveReadBuffer::_wsaBuf");

// PDB: LogArchiveWriteBuffer (GameDaemon), size 0x30.
class LogArchiveWriteBuffer
{
    friend class LogArchiveWriteContext;  // LIFT: access helper. ~LogArchiveWriteBuffer is protected in the PDB; the context destructor inlines it.

protected:
    __cdecl LogArchiveWriteBuffer(int);  // 0x6d8560
    __cdecl ~LogArchiveWriteBuffer(void);  // inlined in 0x6d8e80
public:
    bool __cdecl PushNetworkData(char const *const, unsigned int);  // 0x6d8650
    bool __cdecl PushFileData(char const *const, unsigned int);  // 0x6d8860
    bool __cdecl ClearNetworkBuffer(void);  // 0x6d89e0
    bool __cdecl ClearFileBuffer(void);  // 0x6d8aa0
protected:
    bool __cdecl growBufferChunkSize(unsigned int);  // 0x6d8b30
    bool __cdecl growBufferCount(unsigned int);  // 0x6d8ca0

private:
    char *_pBufferChunkHead;  // +0x0
    char *_pBufferChunkTail;  // +0x8
    _WSABUF *_pWsaBufs;  // +0x10
    unsigned int _maxBufferChunkSize;  // +0x18
    unsigned int _currBufferChunkSize;  // +0x1c
    unsigned int _maxBufferCount;  // +0x20
    unsigned int _currBufferCount;  // +0x24
    int _mode;  // +0x28
};
static_assert(sizeof(LogArchiveWriteBuffer) == 0x30, "sizeof LogArchiveWriteBuffer");
static_assert(offsetof(LogArchiveWriteBuffer, _pWsaBufs) == 0x10, "LogArchiveWriteBuffer::_pWsaBufs");
static_assert(offsetof(LogArchiveWriteBuffer, _mode) == 0x28, "LogArchiveWriteBuffer::_mode");

// PDB: LogArchiveWriteContext (GameDaemon), size 0x38. Base _OVERLAPPED +0.
class LogArchiveWriteContext : public _OVERLAPPED
{
public:
    __cdecl LogArchiveWriteContext(int);  // 0x6d8de0
    __cdecl ~LogArchiveWriteContext(void);  // 0x6d8e80
    bool __cdecl SwitchStatus(void);  // 0x6d8f20
    ::LogArchiveWriteBuffer *const __cdecl GetWritingBuffer(void) const;  // 0x6d8fa0

private:
    LogArchiveWriteBuffer *_pWriteBuffers[2];  // +0x20
    int _status;  // +0x30
    int _mode;  // +0x34
};
static_assert(sizeof(LogArchiveWriteContext) == 0x38, "sizeof LogArchiveWriteContext");
static_assert(offsetof(LogArchiveWriteContext, _pWriteBuffers) == 0x20, "LogArchiveWriteContext::_pWriteBuffers");
static_assert(offsetof(LogArchiveWriteContext, _status) == 0x30, "LogArchiveWriteContext::_status");
static_assert(offsetof(LogArchiveWriteContext, _mode) == 0x34, "LogArchiveWriteContext::_mode");
