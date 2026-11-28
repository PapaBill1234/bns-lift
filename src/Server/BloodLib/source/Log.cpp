// Log.obj (SmartCouponDaemon PDB).
// swprintf (0x22BA0) is the CRT inline. The lift calls the CRT function.
#if defined(LIFT_EXE_GD)
#define LIFT_LOG_ADD_MEMBER  // LIFT: GameDaemon Log::Add is a private member (see Log.h)
#endif
#include "Log.h"
#include <stdarg.h>
#include <stdio.h>
#include <wchar.h>
#include <new>
#include <locale.h>

// msvcr100 export (LobbyGate import __imp__vswprintf_c_l). The Wine msvcrt headers do not declare it.
extern "C" int __cdecl _vswprintf_c_l(wchar_t* buffer, size_t count, wchar_t const* format, _locale_t locale, va_list args);
#include "Daemon.h"
#include "LogBuffer.h"
#include "LogMedia.h"
#include "MemoryManager.h"

static wchar_t const LOG_FILE[] = L"source\\Log.cpp";

#if defined(LIFT_EXE_GD)
// GameDaemon 0x687a10 Log::Write (card lift-gamedaemon-e129).
#pragma comment(linker, "/INCLUDE:?Write@Log@@SAXW4Type@1@PEB_WH1ZZ")  // LIFT: dead-strip keep (no live caller yet)
#endif

Log* Log::instance = nullptr;

// 0x83140 (SmartCouponDaemon) data. The PDB type has no size. LogFile uses LT_MAX entries.
wchar_t const* Log::TypeName[Log::LT_MAX] = {
    L"error", L"debug", L"trace", L"notice", L"resource", L"archive",
    L"undef1", L"undef2", L"undef3", L"undef4", L"undef5",
};

// 0x19620 (SmartCouponDaemon)
wchar_t const* Log::Name()
{
    return L"Log";
}

// 0x19B10 (SmartCouponDaemon) scalar deleting destructor
Log::~Log()
{
}

// 0x19630 (SmartCouponDaemon)
// LIFT: noinline. The orig calls it from Daemon::start only (CG 0x9DA0, LG 0x1A960, POD 0x25660).
__declspec(noinline) bool Log::Initialize()
{
    if (instance != nullptr)
        return true;
    void* memory = BASE_MEMORY_MANAGER.Alloc(sizeof(Log), LOG_FILE, 45);
    instance = memory != nullptr ? new (memory) Log() : nullptr;
    return Daemon::Instance->threadManager->StartThread(instance, nullptr);  // threadId = nullptr (LobbyGate 0x1aa43 xor r8d)
}

// 0x19730 (SmartCouponDaemon)
bool Log::InitMedia(LogMedia* media)
{
    if (instance == nullptr || media == nullptr)
        return false;
    if (!media->Writable())
        return true;
    Log* log = instance;
    if (static_cast<unsigned int>(log->mediaCount) >= 8)
        return false;
    log->media[log->mediaCount] = media;
    media->_bufferNodePos = log->mediaCount++;
    for (int type = 0; type < LT_MAX; ++type)
    {
        if (!media->_enable[type])
            continue;
        LogMedia* last = log->mediaList[type];
        if (last != nullptr)
        {
            while (last->_next[type] != nullptr)
                last = last->_next[type];
            last->_next[type] = media;
        }
        else
        {
            log->mediaList[type] = media;
        }
        ++log->mediaCountPerList[type];
    }
    return true;
}

// 0x19800 (SmartCouponDaemon)
void Log::Close()
{
    if (instance == nullptr)
        return;
    if (instance->open)
    {
        instance->flush = true;
        if (instance->notifyEvent.Event != nullptr)
            SetEvent(instance->notifyEvent.Event);
    }
    instance->open = false;
}

// 0x19840 (SmartCouponDaemon)
// LIFT: noinline. The orig calls it from CrashHandler only (CG 0x9FB0, LG 0x1AB80); it inlines it in Daemon.cpp.
__declspec(noinline) void Log::Flush()
{
    if (instance != nullptr && instance->open)
    {
        instance->flush = true;
        if (instance->notifyEvent.Event != nullptr)
            SetEvent(instance->notifyEvent.Event);
    }
}

// 0x19870 (SmartCouponDaemon)
void Log::WriteV(wchar_t const* file, int line, long errorCode, wchar_t const* format, char* args)
{
    if (instance == nullptr || !instance->open || instance->mediaCountPerList[LT_ERROR] <= 0)
        return;
    wchar_t msg[512];
    wchar_t fmt[512];
    FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM, nullptr, errorCode,
                   MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), msg, 512, nullptr);
    msg[511] = L'\0';
    // BUG: 0x19870 (SmartCouponDaemon) writes before msg when the message has fewer than 2 characters.
    msg[wcslen(msg) - 2] = L'\0';
    swprintf(fmt, 512, L"%s, error: %d, msg: %s", format, errorCode, msg);
    LogBuffer* logbuf = LogBufferAllocator::_Local->allocate();
    logbuf->Prepare(LT_ERROR, file, line);
    _vswprintf_c_l(logbuf->_log, 1980, fmt, nullptr, args);
#if defined(LIFT_EXE_GD)
    instance->Add(logbuf);  // LIFT: GD Log::Add is a member (see Log.h)
#else
    Add(logbuf);
#endif
    logbuf->removeReferenceCount(LOG_FILE, 184);
}

// 0x19A00 (SmartCouponDaemon)
void Log::Write(Type type, wchar_t const* file, int line, wchar_t const* format, ...)
{
    va_list args;
    va_start(args, format);
    if (instance != nullptr && instance->open && instance->mediaCountPerList[type] > 0)
    {
        LogBuffer* logbuf = LogBufferAllocator::_Local->allocate();
        logbuf->Prepare(type, file, line);
        _vswprintf_c_l(logbuf->_log, 1980, format, nullptr, args);  // LobbyGate 0x1adcf
#if defined(LIFT_EXE_GD)
        instance->Add(logbuf);  // LIFT: GD Log::Add is a member (see Log.h)
#else
        Add(logbuf);
#endif
        logbuf->removeReferenceCount(LOG_FILE, 209);
    }
    va_end(args);
}

// 0x19AD0 (SmartCouponDaemon)
void Log::Write(wchar_t const* file, int line, long errorCode, wchar_t const* format, ...)
{
    va_list args;
    va_start(args, format);
    if (instance != nullptr && instance->open && instance->mediaCountPerList[LT_ERROR] > 0)
        WriteV(file, line, errorCode, format, args);
    va_end(args);
}

// 0x19B50 (SmartCouponDaemon)
void Log::Add(LogBuffer* buf)
{
    Log* log = instance;
    bool notify = false;
    if (!log->open)
        return;
    int type = buf->_type;
    LogMedia* media = log->mediaList[type];
    if (media == nullptr)
        return;
    do
    {
        int result = media->Add(buf);
        media = media->_next[type];
        if (result == 0)
            notify = true;
    } while (media != nullptr);
    if (notify && log->notifyEvent.Event != nullptr)
        SetEvent(log->notifyEvent.Event);
}

// 0x19BE0 (SmartCouponDaemon)
void Log::run()
{
    LogBufferAllocator::Initialize();
    PacketBufferAllocator::Initialize();
    notifyEvent.Event = CreateEventW(nullptr, FALSE, FALSE, nullptr);
    while (_run)
    {
        if (notifyEvent.Event != nullptr)
            WaitForSingleObject(notifyEvent.Event, 1000);
        _lastExecuted = _threadManager->_now;
        for (int i = 0; i < 8; ++i)
        {
            if (media[i] != nullptr)
                media[i]->Write();
        }
        if (flush)
        {
            flush = false;
            for (int i = 0; i < 8; ++i)
            {
                if (media[i] != nullptr)
                    media[i]->Flush();
            }
        }
    }
}
