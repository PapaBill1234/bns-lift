// RefCntObject.obj (CacheGate PDB).
#include "RefCntObject.h"
#include <windows.h>
#include <shlwapi.h>
#include <time.h>
#include <wchar.h>
#include "Log.h"
#include "AlertSender.h"
#include "Memory.h"
#include "MemoryManager.h"
#include "Daemon.h"

#define REFCNT_HEADER \
    L"e:\\dailybuild02\\cachegate-common-0.0.348\\depot\\branch\\348nc\\program\\server\\bloodlib\\include\\RefCntObject.h"

// 0x20f0
// BUG: 0x20f0 the format gets ptr for %s and the low 32 bits of file for %d (0x20FA, 0x2103).
// The caller 0x3A93D passes rcx = ptr, rdx = file, r8 = line. The code does not read line.
void RefCntObject::operator delete(void* ptr, wchar_t const* file, int line)
{
    wchar_t const* argFile = static_cast<wchar_t const*>(ptr);
    int argLine = static_cast<int>(reinterpret_cast<long long>(file));
    Log::Write(Log::LT_ERROR, REFCNT_HEADER, 139,
               L"== CRASH == [ref obj], DO NOT USE DELETE on RefCntObject, file:%s, line:%d", argFile, argLine);
    AlertSender::Write(REFCNT_HEADER, 139,
                       L"== CRASH == [ref obj], DO NOT USE DELETE on RefCntObject, file:%s, line:%d", argFile, argLine);
}

// 0x2150
long RefCntObject::addReferenceCount(wchar_t const* file, int line)
{
    if (_ref <= 0)
    {
        Log::Write(Log::LT_ERROR, REFCNT_HEADER, 153,
                   L"== CRASH == [ref obj], cannot add reference count, this:0x%p, ref:%d, tag:0x%08x, file:%s, line:%d",
                   this, _ref, _tag, file, line);
        AlertSender::Write(REFCNT_HEADER, 153,
                           L"== CRASH == [ref obj], cannot add reference count, this:0x%p, ref:%d, tag:0x%08x, file:%s, line:%d",
                           this, _ref, _tag, file, line);
        return 0;
    }
    if (_history != nullptr)
        _history->add(_ref, file, line, RefCntHistory::OP_ADDREF);
    return InterlockedIncrement(&_ref);
}

// 0x2230
long RefCntObject::removeReferenceCount(wchar_t const* file, int line)
{
    if (_ref <= 0)
    {
        Log::Write(Log::LT_ERROR, REFCNT_HEADER, 177,
                   L"== CRASH == [ref obj], cannot remove reference count, this:0x%p, ref:%d, tag:0x%08x, file:%s, line:%d",
                   this, _ref, _tag, file, line);
        AlertSender::Write(REFCNT_HEADER, 177,
                           L"== CRASH == [ref obj], cannot remove reference count, this:0x%p, ref:%d, tag:0x%08x, file:%s, line:%d",
                           this, _ref, _tag, file, line);
        return 0;
    }
    if (_history != nullptr)
        _history->add(_ref, file, line, RefCntHistory::OP_DELREF);
    long ref = InterlockedDecrement(&_ref);
    if (ref == 0)
        deallocate_object(file, line);
    return ref;
}

// 0x2320
void RefCntObject::deallocate_object(wchar_t const* file, int line)
{
    deallocate_me(this, file, line);
}

// 0x2330
void RefCntObject::DumpRefCntHistory()
{
    if (_history != nullptr)
        _history->dump(this);
}

// 0x2350
void DynamicRefCntObj::deallocate_me(void* ptr, wchar_t const* file, int line)
{
    this->~DynamicRefCntObj();
    Memory::_Manager[2]->Free(ptr, file, line);
}

// 0xccd0
RefCntObject::~RefCntObject()
{
    _tag |= 0xF0;
    if (_ref != 0)
    {
        Log::Write(Log::LT_ERROR, REFCNT_HEADER, 129,
                   L"== CRASH == [ref obj], destructring with not zero reference count, this:0x%p, ref:%d, tag:0x%08x",
                   this, _ref, _tag);
        AlertSender::Write(REFCNT_HEADER, 129,
                           L"== CRASH == [ref obj], destructring with not zero reference count, this:0x%p, ref:%d, tag:0x%08x",
                           this, _ref, _tag);
    }
    _history = nullptr;
}

// 0x10000
bool RefCntHistory::add(long ref, wchar_t const* file, int line, Operation op)
{
    if (_dumped != 0 || _history == nullptr || _historyMax == 0)
        return false;
    long seq = InterlockedIncrement(&_historyPos);
    RefCntHistoryItem& item = _history[seq % _historyMax];
    item._seq = seq;
    item._time = Daemon::Now;
    item._threadId = GetCurrentThreadId();
    item._file = file;
    item._op = static_cast<char>(op);
    item._line = line;
    item._ref = static_cast<short>(ref);
    return true;
}

// 0x100b0
void RefCntHistory::dump(RefCntObject* ptr)
{
    if (_history == nullptr || ptr == nullptr)
        return;
    long tag = ptr->_tag;
    int calcRef = 1;
    if (InterlockedCompareExchange(&_dumped, 1, 0) != 0)
    {
        Log::Write(Log::LT_ERROR, L"source\\RefCntObject.cpp", 306,
                   L"[refcnt-history], already dumped, ptr:0x%p, tag:0x%08x", ptr, tag);
        return;
    }
    Log::Write(Log::LT_DEBUG, L"source\\RefCntObject.cpp", 310,
               L"[refcnt-history], history dump, ptr:0x%p, tag:0x%08x, history-count:%d, history-max:%d",
               ptr, tag, _historyPos, _historyMax);
    for (int i = 0; i < _historyMax; ++i)
    {
        RefCntHistoryItem& item = _history[i];
        if (item._time == 0 && item._file == nullptr && item._line == 0 && item._threadId == 0 &&
            item._ref == 0 && item._op == 0)
            continue;
        wchar_t const* fileName = reinterpret_cast<wchar_t const*>(PathFindFileNameW(reinterpret_cast<LPCWSTR>(item._file)));
        if (fileName == nullptr)
            fileName = L"unknown_file";
        tm localTm;
        _localtime64_s(&localTm, &_history[i]._time);
        wchar_t timeStr[128];
        swprintf(timeStr, 128, L"%04d/%02d/%02d-%02d:%02d:%02d%s%s", localTm.tm_year + 1900, localTm.tm_mon + 1,
                 localTm.tm_mday, localTm.tm_hour, localTm.tm_min, localTm.tm_sec, L"", L"");
        wchar_t const* opName = L"none";
        switch (item._op)
        {
        case RefCntHistory::OP_ADDREF:
            opName = L"addref";
            ++calcRef;
            break;
        case RefCntHistory::OP_DELREF:
            opName = L"delref";
            --calcRef;
            break;
        }
        Log::Write(Log::LT_DEBUG, L"source\\RefCntObject.cpp", 350,
                   L"[refcnt-history], seq:%d, ptr:0x%p, tag:0x%08x, time:%s, thread-id:%d, idx:%d, op:%s, ref:%d, "
                   L"calc-ref:%d, file:%s, line:%d",
                   item._seq, ptr, tag, timeStr, item._threadId, i + 1, opName, item._ref, calcRef, fileName,
                   item._line);
    }
}

// 0x10360
DynamicRefCntObj::~DynamicRefCntObj()
{
}

// 0x18450
BaseRefCntObj::~BaseRefCntObj()
{
}

// 0x18460
void BaseRefCntObj::deallocate_me(void* ptr, wchar_t const* file, int line)
{
    this->~BaseRefCntObj();
    BASE_MEMORY_MANAGER.Free(ptr, file, line);
}
