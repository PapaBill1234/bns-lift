// LogBuffer.obj: LogBuffer, ConsoleLog, LogBufferPool, LogBufferAllocator.
// Layouts from include/pdb/CacheGate/types.h. The SmartCouponDaemon PDB has the same layouts.
#pragma once
#include <windows.h>
#include <stddef.h>
#include "RefCntObject.h"
#include "Lock.h"
#include "Log.h"

class PagePoolMemoryManager;

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

// PDB global (LogBuffer.obj). Maps Log::Type to the ConsoleLog type.
extern int const CONSOLE_LOG_TYPE[11];

class LogBuffer : public RefCntObject, public ConsoleLog
{
public:
    LogBuffer()  // ❓ inlined in LogBufferPool::allocate (0x20200) and LogBufferAllocator::allocate (0x20500)
        : _flush(false)
    {
        _ref = 1;
        _history = nullptr;
        _tag = 266;
        for (int i = 0; i < 8; ++i)
            _next[i] = nullptr;
    }
    virtual ~LogBuffer();
    virtual void deallocate_me(void* ptr, wchar_t const* file, int line);
    virtual int GetType() const;
    virtual bool Acquire();
    virtual void Release();
    virtual bool GetLog(wchar_t* buffer, unsigned long long size) const;

    void Prepare(Log::Type type, wchar_t const* file, int line);

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
    LogBufferPool() : _count(0), _pool(nullptr) {}  // ❓ inlined in LogBufferAllocator::Initialize (0x203D0)
    LogBuffer* allocate();
    void deallocate(LogBuffer* logbuf);

    int _count;
    LogBuffer* _pool;
};
static_assert(sizeof(LogBufferPool) == 0x10, "sizeof LogBufferPool");

class LogBufferAllocator
{
public:
    static void Initialize();

    // PDB S_GTHREAD32, .tls +0x18.
    static __declspec(thread) LogBufferPool* _Local;
    static long long Using;
    static long long Allocated;

protected:
    static LogBuffer* allocate(int count);

private:
    static void initAllocator();

    static SpinLock _Lock;
    static LogBuffer* _Pool;
    static long long _Count;
    static PagePoolMemoryManager* _Allocator;

    friend class LogBufferPool;
};

#include "PacketBuffer.h"  // PacketBufferAllocator::Initialize (callers include LogBuffer.h)
