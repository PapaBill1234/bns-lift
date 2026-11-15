// LogBuffer, ConsoleLog, LogBufferPool, LogBufferAllocator (CacheGate PDB).
// Layouts from include/pdb/CacheGate/types.h. The functions are in a later card.
// Only declarations are here.
#pragma once
#include <windows.h>
#include <stddef.h>
#include "RefCntObject.h"

class ConsoleLog
{
public:
    virtual bool Acquire() = 0;                                              // slot 0
    virtual void Release() = 0;                                              // slot 1
    virtual int GetType() const = 0;                                         // slot 2
    virtual bool GetLog(wchar_t* buffer, unsigned long long size) const = 0;  // slot 3
};
static_assert(sizeof(ConsoleLog) == 0x8, "sizeof ConsoleLog");

// ❓ The name of the ConsoleLog type enum is not in the PDB. L_NONE is the value
// that WindowConsole compares with (0).
enum ConsoleLogType  // ❓
{
    L_NONE = 0,  // ❓
};

// ❓ PDB global. Maps Log::Type to the ConsoleLog type. Defined in a later card.
extern int const CONSOLE_LOG_TYPE[11];

class LogBuffer : public RefCntObject, public ConsoleLog
{
public:
    virtual ~LogBuffer();
    virtual void deallocate_me(void* ptr, wchar_t const* file, int line);
    virtual int GetType() const;
    virtual bool Acquire();
    virtual void Release();
    virtual bool GetLog(wchar_t* buffer, unsigned long long size) const;

    LogBuffer* _next[8];
    SYSTEMTIME _logtime;
    int _type;
    wchar_t const* _file;
    int _line;
    bool _flush;
    wchar_t _log[1980];
};
static_assert(sizeof(LogBuffer) == 0x1000, "sizeof LogBuffer");
static_assert(offsetof(LogBuffer, _next) == 0x20, "LogBuffer::_next");
static_assert(offsetof(LogBuffer, _logtime) == 0x60, "LogBuffer::_logtime");
static_assert(offsetof(LogBuffer, _type) == 0x70, "LogBuffer::_type");
static_assert(offsetof(LogBuffer, _file) == 0x78, "LogBuffer::_file");
static_assert(offsetof(LogBuffer, _line) == 0x80, "LogBuffer::_line");
static_assert(offsetof(LogBuffer, _flush) == 0x84, "LogBuffer::_flush");
static_assert(offsetof(LogBuffer, _log) == 0x86, "LogBuffer::_log");

class LogBufferPool
{
public:
    LogBuffer* allocate();

    int _count;
    LogBuffer* _pool;
};
static_assert(sizeof(LogBufferPool) == 0x10, "sizeof LogBufferPool");

class LogBufferAllocator
{
public:
    static void Initialize();

    // PDB S_GTHREAD32, .tls +0x18. Defined in a later card.
    static __declspec(thread) LogBufferPool* _Local;
};

class PacketBufferAllocator
{
public:
    static void Initialize();
};
