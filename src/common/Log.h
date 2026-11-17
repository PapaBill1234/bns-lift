// Log.obj (CacheGate PDB). Layouts from include/pdb/CacheGate/types.h.
#pragma once
#include "Thread.h"
#include "Lock.h"

class LogMedia;
class LogBuffer;

class Log : public Thread
{
public:
    enum Type
    {
        LT_ERROR = 0,
        LT_DEBUG = 1,
        LT_TRACE = 2,
        LT_NOTICE = 3,
        LT_RESOURCE = 4,
        LT_ARCHIVE = 5,
        LT_USER_DEFINED_MIN = 6,
        LT_USER_DEFINED_1 = 6,
        LT_USER_DEFINED_2 = 7,
        LT_USER_DEFINED_3 = 8,
        LT_USER_DEFINED_4 = 9,
        LT_USER_DEFINED_5 = 10,
        LT_USER_DEFINED_MAX = 10,
        LT_MAX = 11,
    };

    static bool Initialize();
    static bool InitMedia(LogMedia* media);
    static void Close();
    static void Flush();
    static void WriteV(wchar_t const* file, int line, long errorCode, wchar_t const* format, char* args);
    static void Write(Type type, wchar_t const* file, int line, wchar_t const* format, ...);
    static void Write(wchar_t const* file, int line, long errorCode, wchar_t const* format, ...);

    static wchar_t const* TypeName[LT_MAX];  // 0x83140 (SmartCouponDaemon)

private:
    Log()  // PDB constructor, inlined in Initialize (0x9DA0)
        : open(false), flush(false), mediaCount(0)
    {
        _maxFrozenSeconds = 60;
        for (int i = 0; i < 8; ++i)
            media[i] = nullptr;
        for (int i = 0; i < LT_MAX; ++i)
        {
            mediaList[i] = nullptr;
            mediaCountPerList[i] = 0;
        }
    }
    virtual ~Log();
    virtual wchar_t const* Name();
    virtual void run();
    static void Add(LogBuffer* buf);  // SmartCouponDaemon 0x19B50: static, uses instance

    static Log* instance;

    friend class Daemon;

public:
    bool open;
    bool flush;
    SystemEvent notifyEvent;
    LogMedia* media[8];
    int mediaCount;
    LogMedia* mediaList[11];
    int mediaCountPerList[11];
};
static_assert(sizeof(Log) == 0x110, "sizeof Log");
static_assert(offsetof(Log, open) == 0x30, "Log::open");
static_assert(offsetof(Log, notifyEvent) == 0x38, "Log::notifyEvent");
static_assert(offsetof(Log, media) == 0x40, "Log::media");
static_assert(offsetof(Log, mediaCount) == 0x80, "Log::mediaCount");
static_assert(offsetof(Log, mediaList) == 0x88, "Log::mediaList");
static_assert(offsetof(Log, mediaCountPerList) == 0xE0, "Log::mediaCountPerList");
