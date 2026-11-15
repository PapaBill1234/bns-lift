// LogFile (SmartCouponDaemon PDB, LogFile.obj). Layout from include/pdb/CacheGate/types.h.
#pragma once
#include <windows.h>
#include <time.h>
#include <stddef.h>
#include "LogMedia.h"
#include "Log.h"

class LogFile : public LogMedia
{
public:
    // LTCG folded the constant arguments of the one caller (SmartCouponDaemon::initLog, 0x1504F):
    // bufmax 0, codePage 0, fileType 2. The IDA prototype is (rootDir, fileType, logType). ❓
    LogFile(wchar_t const* rootDir, int fileType, int logType);  // 0x21970 (SmartCouponDaemon)
    virtual ~LogFile();                        // 0x21A70 (SmartCouponDaemon)
    virtual int GetType() const;               // 0x41CC0 (SmartCouponDaemon)
    virtual void Flush();                      // 0x222D0 (SmartCouponDaemon)
    virtual wchar_t* GetLastFileName();        // 0x21960 (SmartCouponDaemon)

    void MakeFilename(tm* wtime, wchar_t* filename, int count);  // 0x21E20 (SmartCouponDaemon)

private:
    virtual void write(LogBuffer const* logbuf);  // 0x222E0 (SmartCouponDaemon)

    void initialize(wchar_t const* rootDir, int logType, int fileType);  // 0x21B10 (SmartCouponDaemon)
    void makeDirectory(wchar_t* directory);  // 0x220E0 (SmartCouponDaemon)
    void writeFile();                         // 0x223A0 (SmartCouponDaemon)
    void writeToBuffer(Log::Type type, SYSTEMTIME wtime, wchar_t const* file, int line,
                       wchar_t const* log);  // 0x22560 (SmartCouponDaemon)
    void writeToBuffer(wchar_t const* time, int timelen, wchar_t const* file, int filelen,
                       wchar_t const* line, int linelen, wchar_t const* type, int typelen,
                       wchar_t const* log, int loglen);  // 0x227D0 (SmartCouponDaemon)

public:
    int _bufmax;
    int _bufsiz;
    int _bufcnt;
    char* _buffer;
    wchar_t* _prefix;
    unsigned int _codePage;
    int _filetype;
    int _trycount;
    long long _lastWritten;
    long long _interval;
    wchar_t _lastPrefix[260];
    wchar_t _lastFileName[260];
};
static_assert(sizeof(LogFile) == 0x500, "sizeof LogFile");
static_assert(offsetof(LogFile, _bufmax) == 0xB0, "LogFile::_bufmax");
static_assert(offsetof(LogFile, _buffer) == 0xC0, "LogFile::_buffer");
static_assert(offsetof(LogFile, _prefix) == 0xC8, "LogFile::_prefix");
static_assert(offsetof(LogFile, _codePage) == 0xD0, "LogFile::_codePage");
static_assert(offsetof(LogFile, _trycount) == 0xD8, "LogFile::_trycount");
static_assert(offsetof(LogFile, _lastWritten) == 0xE0, "LogFile::_lastWritten");
static_assert(offsetof(LogFile, _lastPrefix) == 0xF0, "LogFile::_lastPrefix");
static_assert(offsetof(LogFile, _lastFileName) == 0x2F8, "LogFile::_lastFileName");
