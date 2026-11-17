// LogBuffer.obj (SmartCouponDaemon PDB).
#include "LogBuffer.h"
#include <stdio.h>
#include <new>
#include "AlertSender.h"
#include "MemoryManager.h"
#include "SysInfo.h"

static wchar_t const LOGBUFFER_FILE[] = L"source\\LogBuffer.cpp";

// PDB global. Maps Log::Type to the ConsoleLog type.
ConsoleLog::Type const CONSOLE_LOG_TYPE[11] = {
    ConsoleLog::L_ERROR, ConsoleLog::L_DEBUG, ConsoleLog::L_TRACE, ConsoleLog::L_INFO, ConsoleLog::L_NONE, ConsoleLog::L_NONE,
    ConsoleLog::L_NONE,  ConsoleLog::L_NONE,  ConsoleLog::L_NONE,  ConsoleLog::L_NONE, ConsoleLog::L_NONE};

__declspec(thread) LogBufferPool* LogBufferAllocator::_Local = nullptr;
long long LogBufferAllocator::Using = 0;
long long LogBufferAllocator::Allocated = 0;
// 0x52AA0 (SmartCouponDaemon) dynamic initializer, 0x52BE0 (SmartCouponDaemon) atexit destructor
SpinLock LogBufferAllocator::_Lock;
LogBuffer* LogBufferAllocator::_Pool = nullptr;
long long LogBufferAllocator::_Count = 0;
PagePoolMemoryManager* LogBufferAllocator::_Allocator = nullptr;

// 0x20020 (SmartCouponDaemon) scalar deleting destructor
LogBuffer::~LogBuffer()
{
}

// 0x20050 (SmartCouponDaemon)
void LogBuffer::Prepare(Log::Type type, wchar_t const* file, int line)
{
    GetLocalTime(&_logtime);
    _type = type;
    _line = line;
    _file = file;
    _log[0] = L'\0';
}

// 0x20010 (SmartCouponDaemon)
ConsoleLog::Type LogBuffer::GetType() const
{
    return CONSOLE_LOG_TYPE[_type];
}

// 0x200B0 (SmartCouponDaemon)
void LogBuffer::deallocate_me(void* ptr, wchar_t const* file, int line)
{
    LogBufferAllocator::_Local->deallocate(this);
}

// 0x200D0 (SmartCouponDaemon)
bool LogBuffer::Acquire()
{
    addReferenceCount(LOGBUFFER_FILE, 100);
    return true;
}

// 0x20100 (SmartCouponDaemon)
void LogBuffer::Release()
{
    removeReferenceCount(LOGBUFFER_FILE, 106);
}

// 0x20120 (SmartCouponDaemon)
bool LogBuffer::GetLog(wchar_t* buffer, unsigned long long size) const
{
    SYSTEMTIME logtime = _logtime;
    return swprintf(buffer, size, L"%04d/%02d/%02d-%02d:%02d:%02d.%03d%s%s",
                    logtime.wYear, logtime.wMonth, logtime.wDay,
                    logtime.wHour, logtime.wMinute, logtime.wSecond,
                    logtime.wMilliseconds, L",", _log) > 0;
}

// 0x20200 (SmartCouponDaemon)
LogBuffer* LogBufferPool::allocate()
{
    if (_pool == nullptr)
    {
        if (_count != 0)
        {
            Log::Write(Log::LT_ERROR, LOGBUFFER_FILE, 174,
                       L"== CRASH == [LogBuffer], _list는 NULL이지만 _count(%d)는 0이 아닙니다.", _count);
            AlertSender::Write(LOGBUFFER_FILE, 174,
                               L"== CRASH == [LogBuffer], _list는 NULL이지만 _count(%d)는 0이 아닙니다.", _count);
        }
        // ❓ LTCG removed the count argument. LogBufferAllocator::allocate uses 16.
        _pool = LogBufferAllocator::allocate(16);
        _count = 16;
    }
    LogBuffer* logbuf = _pool;
    --_count;
    _pool = logbuf->_next[0];
    logbuf->_next[0] = nullptr;
    InterlockedIncrement(&logbuf->_ref);
    new (logbuf) LogBuffer();
    InterlockedIncrement64(&LogBufferAllocator::Using);
    return logbuf;
}

// 0x202E0 (SmartCouponDaemon)
void LogBufferPool::deallocate(LogBuffer* logbuf)
{
    InterlockedDecrement64(&LogBufferAllocator::Using);
    logbuf->~LogBuffer();
    logbuf->_next[0] = _pool;
    _pool = logbuf;
    if (++_count > 512)
    {
        LogBuffer* last = nullptr;
        LogBuffer* head = logbuf;
        for (int i = 0; i < _count / 2; ++i)
        {
            last = head;
            head = head->_next[0];
        }
        last->_next[0] = nullptr;
        _count /= 2;

        int count = 1;
        LogBuffer* tail = head;
        while (tail->_next[0] != nullptr)
        {
            tail = tail->_next[0];
            ++count;
        }

        LogBufferAllocator::_Lock.Enter();
        LogBufferAllocator::_Count += count;
        tail->_next[0] = LogBufferAllocator::_Pool;
        LogBufferAllocator::_Pool = head;
        LogBufferAllocator::_Lock.Leave();
    }
}

// 0x203D0 (SmartCouponDaemon)
void LogBufferAllocator::Initialize()
{
    if (_Local == nullptr)
    {
        void* memory = BaseMemoryManager::_Instance.Alloc(sizeof(LogBufferPool), LOGBUFFER_FILE, 235);
        _Local = memory != nullptr ? new (memory) LogBufferPool() : nullptr;
    }
    initAllocator();
}

// 0x20440 (SmartCouponDaemon)
void LogBufferAllocator::initAllocator()
{
    _Lock.Enter();
    if (_Allocator == nullptr)
    {
        unsigned long long size = 1024;
        while (size < sizeof(LogBuffer))
            size *= 2;
        void* memory = BaseMemoryManager::_Instance.Alloc(sizeof(PagePoolMemoryManager), LOGBUFFER_FILE, 261);
        _Allocator = memory != nullptr ? new (memory) PagePoolMemoryManager(SysInfo::MemnoryAllocationGranularity()) : nullptr;
        // BUG: 0x20440 (SmartCouponDaemon) no null check of _Allocator before Initialize.
        _Allocator->Initialize(size);
    }
    _Lock.Leave();
}

// 0x20500 (SmartCouponDaemon)
LogBuffer* LogBufferAllocator::allocate(int count)
{
    int taken = 0;
    LogBuffer* last = nullptr;
    _Lock.Enter();
    LogBuffer* head = _Pool;
    LogBuffer* node = _Pool;
    while (node != nullptr && taken < count)
    {
        last = node;
        node = node->_next[0];
        ++taken;
    }
    _Pool = node;
    _Count -= taken;
    if (node != nullptr)
        last->_next[0] = nullptr;
    _Lock.Leave();

    for (int i = taken; i < count; ++i)
    {
        void* memory = _Allocator->Alloc();
        LogBuffer* logbuf = memory != nullptr ? new (memory) LogBuffer() : nullptr;
        // BUG: 0x20500 (SmartCouponDaemon) logbuf can be null here.
        InterlockedDecrement(&logbuf->_ref);
        if (last != nullptr)
            last->_next[0] = logbuf;
        else
            head = logbuf;
        last = logbuf;
        InterlockedIncrement64(&Allocated);
    }
    return head;
}
