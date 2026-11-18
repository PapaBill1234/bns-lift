// LogFile (SmartCouponDaemon PDB, LogFile.obj). Phase 1 lift.
#include <winsock2.h>
#include "LogFile.h"
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <time.h>
#include "AlertSender.h"
#include "CrashHandler.h"
#include "Daemon.h"
#include "LogBuffer.h"
#include "Memory.h"
#include "MemoryManager.h"

#define LOGFILE_FILE L"source\\LogFile.cpp"

// 0x21970 (SmartCouponDaemon)
LogFile::LogFile(wchar_t const* rootDir, int fileType, int logType)
    : _bufmax(0),
      _bufsiz(0),
      _bufcnt(0),
      _buffer(nullptr),
      _prefix(nullptr),
      _codePage(0),
      _filetype(0),
      _trycount(0),
      _lastWritten(0),
      _interval(0)
{
    _lastPrefix[0] = 0;
    _lastFileName[0] = 0;
    initialize(rootDir, logType, fileType);
}

// 0x21A70 (SmartCouponDaemon). The scalar deleting destructor is 0x21A50.
LogFile::~LogFile()
{
    if (_prefix != nullptr)
    {
        Memory::_Manager[2]->Free(_prefix, LOGFILE_FILE, 45);
        _prefix = nullptr;
    }
    if (_buffer != nullptr)
    {
        Memory::_Manager[2]->Free(_buffer, LOGFILE_FILE, 48);
        _buffer = nullptr;
    }
}

// 0x41CC0 (SmartCouponDaemon). Folded with PortListener::EventId.
int LogFile::GetType() const
{
    return 2;
}

// 0x21960 (SmartCouponDaemon)
wchar_t* LogFile::GetLastFileName()
{
    return _lastFileName;
}

// 0x21B10 (SmartCouponDaemon)
void LogFile::initialize(wchar_t const* rootDir, int logType, int fileType)
{
    (void)logType;
    // LIFT: LTCG folded fileType to 2 in each exe (SmartCouponDaemon 0x21b45, PostOfficeDaemon 0x2d935,
    // CacheGate 0x10da5, LobbyGate 0x21ef5). All callers give 2.
    _filetype = fileType;
    if (_bufmax <= 0)
        _bufmax = 8000;

    wchar_t logDirectory[MAX_PATH];
    wcsncpy(logDirectory, rootDir, MAX_PATH);
    // BUG: 0x21B10 reads logDirectory[-1] when rootDir is empty.
    if (logDirectory[wcslen(logDirectory) - 1] != L'\\')
        wcsncat(logDirectory, L"\\", MAX_PATH);
    makeDirectory(logDirectory);

    __time64_t start = Daemon::Instance->StartTime;
    tm stm;
    _localtime64_s(&stm, &start);
    wchar_t daemonName[MAX_PATH];
    swprintf(daemonName, MAX_PATH, L"%s(%04d%02d%02d-%02d%02d%02d,%05d)",
             Daemon::Instance->ShortName(), stm.tm_year + 1900, stm.tm_mon + 1, stm.tm_mday,
             stm.tm_hour, stm.tm_min, stm.tm_sec, GetCurrentProcessId());

    size_t len = wcslen(logDirectory) + wcslen(daemonName);
    _prefix = static_cast<wchar_t*>(
        Memory::_Manager[2]->Alloc(len * sizeof(wchar_t) + sizeof(wchar_t), LOGFILE_FILE, 96));
    swprintf(_prefix, len + 1, L"%s%s", logDirectory, daemonName);

    if (_bufmax >= 0)
    {
        __time64_t now = _time64(nullptr);
        tm cur;
        _localtime64_s(&cur, &now);
        cur.tm_sec = 0;
        switch (_filetype)
        {
        case 0: cur.tm_min = cur.tm_min / 15 * 15; break;
        case 1: cur.tm_min = cur.tm_min / 30 * 30; break;
        case 2: cur.tm_min = 0; break;
        case 3: cur.tm_sec = 0; break;
        }
        _lastWritten = _mktime64(&cur);
    }

    switch (_filetype)
    {
    case 0: _interval = 900; break;
    case 1: _interval = 1800; break;
    case 2: _interval = 3600; break;
    case 3: _interval = 60; break;
    }

    _bufsiz = 8000;
    while (_bufsiz < _bufmax)
        _bufsiz *= 2;
    _buffer = static_cast<char*>(Memory::_Manager[2]->Alloc(_bufsiz, LOGFILE_FILE, 153));
    _bufcnt = 0;
}

// 0x21E20 (SmartCouponDaemon)
void LogFile::MakeFilename(tm* wtime, wchar_t* filename, int count)
{
    (void)count;
    wcsncpy(filename, _prefix, MAX_PATH);
    if (wtime == nullptr)
    {
        wcsncat(filename, L".log", MAX_PATH);
        return;
    }

    switch (_filetype)
    {
    case 0:
    case 1:
        swprintf(filename + wcslen(filename), MAX_PATH - wcslen(filename), L"%04d%02d%02d-%02d_%02d",
                 wtime->tm_year + 1900, wtime->tm_mon + 1, wtime->tm_mday, wtime->tm_hour,
                 wtime->tm_min / 15 + 1);
        break;
    case 2:
        swprintf(filename + wcslen(filename), MAX_PATH - wcslen(filename), L"%04d%02d%02d-%02d",
                 wtime->tm_year + 1900, wtime->tm_mon + 1, wtime->tm_mday, wtime->tm_hour);
        break;
    case 4:
        swprintf(filename + wcslen(filename), MAX_PATH - wcslen(filename), L"%04d%02d%02d-%02d%02d%02d",
                 wtime->tm_year + 1900, wtime->tm_mon + 1, wtime->tm_mday, wtime->tm_hour,
                 wtime->tm_min, wtime->tm_sec);
        break;
    }

    if (_lastPrefix[0] == 0 || wcscmp(_lastPrefix, filename) != 0)
    {
        size_t len = wcslen(filename);
        wcsncpy(_lastPrefix, filename, len);
        _lastPrefix[len] = 0;
        _trycount = 0;
    }

    if (_trycount != 0)
        swprintf(filename + wcslen(filename), MAX_PATH - wcslen(filename), L"_%03d.log", _trycount);
    else
        swprintf(filename + wcslen(filename), MAX_PATH - wcslen(filename), L".log");
}

// 0x220E0 (SmartCouponDaemon)
void LogFile::makeDirectory(wchar_t* directory)
{
    wchar_t drive[3];
    wchar_t dir[MAX_PATH];
    wchar_t fileName[MAX_PATH];
    wchar_t ext[MAX_PATH];
    wchar_t parentPath[MAX_PATH];
    _wsplitpath_s(directory, drive, 3, dir, MAX_PATH, fileName, MAX_PATH, ext, MAX_PATH);

    // The drive branch is first: the original lays out GetCurrentDirectoryW last (CacheGate 0x11340).
    if (wcslen(drive) != 0)
    {
        int dirlen = static_cast<int>(wcslen(dir));
        if (dirlen > 1)
        {
            dir[dirlen - 1] = 0;
            swprintf(parentPath, MAX_PATH, L"%s%s", drive, dir);
            makeDirectory(parentPath);
            if (!CreateDirectoryW(parentPath, nullptr) && GetLastError() != ERROR_ALREADY_EXISTS)
            {
                Log::Write(Log::LT_ERROR, LOGFILE_FILE, 229, L"== CRASH == ASSERT CRASH");
                AlertSender::Write(LOGFILE_FILE, 229, L"== CRASH == ASSERT CRASH");
                CrashHandler::MakeCrash("source\\LogFile.cpp", 229, L"");
            }
        }
    }
    else
    {
        GetCurrentDirectoryW(MAX_PATH, parentPath);
        wcsncat(parentPath, L"\\", MAX_PATH - wcslen(parentPath));
        wcsncat(parentPath, directory, MAX_PATH - wcslen(parentPath));
        makeDirectory(parentPath);
    }
}

// 0x222D0 (SmartCouponDaemon). Thunk to writeFile.
void LogFile::Flush()
{
    writeFile();
}

// 0x222E0 (SmartCouponDaemon)
void LogFile::write(LogBuffer const* logbuf)
{
    __time64_t now = _time64(nullptr);
    if (_bufmax > 0 && now > _interval + _lastWritten)
    {
        writeFile();
        _lastWritten += _interval;
    }
    while (logbuf != nullptr)
    {
        if (!logbuf->_flush)
            writeToBuffer(static_cast<Log::Type>(logbuf->_type), logbuf->_logtime, logbuf->_file,
                          logbuf->_line, logbuf->_log);
        logbuf = (_bufferNodePos >= 0) ? logbuf->_next[_bufferNodePos] : nullptr;
    }
    writeFile();
}

// 0x223A0 (SmartCouponDaemon)
void LogFile::writeFile()
{
    unsigned long written = 0;
    if (_bufcnt <= 0)
        return;

    tm wtm;
    wchar_t filename[MAX_PATH];
    _localtime64_s(&wtm, &_lastWritten);
    MakeFilename(&wtm, filename, MAX_PATH);  // LIFT: LTCG folded count; MakeFilename writes r9d before it reads it (LobbyGate 0x22256)

    // CacheGate 0x11600: up to 100 CreateFileW calls with Sleep(100) between them.
    HANDLE file = CreateFileW(filename, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, nullptr,
                              OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
    if (file == INVALID_HANDLE_VALUE)
    {
        int tries = 1;
        do
        {
            Sleep(100);
            file = CreateFileW(filename, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, nullptr,
                               OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
            if (file != INVALID_HANDLE_VALUE)
                goto opened;
        } while (++tries < 100);
        ++_trycount;
        AlertSender::Write(LOGFILE_FILE, 301,
                           L"[log], file create error, fname:%s, error:%d, trycount:%d",
                           filename, GetLastError(), _trycount);
        return;
    }
opened:

    wcsncpy(_lastFileName, filename, MAX_PATH);
    long highPos = 0;
    SetFilePointer(file, 0, &highPos, FILE_END);
    WriteFile(file, _buffer, _bufcnt, &written, nullptr);
    CloseHandle(file);
    _bufcnt = 0;
}

// 0x22560 (SmartCouponDaemon)
void LogFile::writeToBuffer(Log::Type type, SYSTEMTIME wtime, wchar_t const* file, int line,
                            wchar_t const* log)
{
    wchar_t tstr[32];
    swprintf(tstr, 32, L"%04d/%02d/%02d-%02d:%02d:%02d.%03d%s%s", wtime.wYear, wtime.wMonth,
             wtime.wDay, wtime.wHour, wtime.wMinute, wtime.wSecond, wtime.wMilliseconds, L",", L"");
    int timelen = static_cast<int>(wcslen(tstr));

    wchar_t fstr[MAX_PATH];
    int filelen;
    if (file != nullptr)
    {
        wchar_t name[MAX_PATH];
        wchar_t ext[MAX_PATH];
        _wsplitpath_s(file, nullptr, 0, nullptr, 0, name, MAX_PATH, ext, MAX_PATH);
        swprintf(fstr, MAX_PATH, L"%s%s,", name, ext);
        filelen = static_cast<int>(wcslen(fstr));
    }
    else
    {
        fstr[0] = 0;
        filelen = 0;
    }

    wchar_t lstr[32];
    swprintf(lstr, 32, L"%d,", line);
    int linelen = static_cast<int>(wcslen(lstr));

    wchar_t tystr[16];
    int typelen = 0;
    if (type == Log::LT_MAX)
    {
        tystr[0] = 0;
    }
    else
    {
        swprintf(tystr, 16, L"(%s),", Log::TypeName[type]);
        typelen = static_cast<int>(wcslen(tystr));
    }

    writeToBuffer(tstr, timelen, fstr, filelen, lstr, linelen, tystr, typelen, log,
                  static_cast<int>(wcslen(log)));
}

// 0x227D0 (SmartCouponDaemon)
void LogFile::writeToBuffer(wchar_t const* time, int timelen, wchar_t const* file, int filelen,
                            wchar_t const* line, int linelen, wchar_t const* type, int typelen,
                            wchar_t const* log, int loglen)
{
    int timesz = time != nullptr ? WideCharToMultiByte(_codePage, 0, time, timelen, nullptr, 0, nullptr, nullptr) : 0;
    int filesz = file != nullptr ? WideCharToMultiByte(_codePage, 0, file, filelen, nullptr, 0, nullptr, nullptr) : 0;
    int linesz = line != nullptr ? WideCharToMultiByte(_codePage, 0, line, linelen, nullptr, 0, nullptr, nullptr) : 0;
    int typesz = type != nullptr ? WideCharToMultiByte(_codePage, 0, type, typelen, nullptr, 0, nullptr, nullptr) : 0;
    int logsz = log != nullptr ? WideCharToMultiByte(_codePage, 0, log, loglen, nullptr, 0, nullptr, nullptr) : 0;

    int need = timesz + filesz + linesz + typesz + logsz + 2;
    if (_bufsiz < _bufcnt + need + 1)
    {
        do
            _bufsiz *= 2;
        while (_bufsiz < _bufcnt + need + 1);
        _buffer = static_cast<char*>(Memory::_Manager[2]->Realloc(_buffer, _bufsiz, LOGFILE_FILE, 385));
    }

    _bufcnt += time != nullptr ? WideCharToMultiByte(_codePage, 0, time, timelen, &_buffer[_bufcnt], _bufsiz - _bufcnt, nullptr, nullptr) : 0;
    _bufcnt += file != nullptr ? WideCharToMultiByte(_codePage, 0, file, filelen, &_buffer[_bufcnt], _bufsiz - _bufcnt, nullptr, nullptr) : 0;
    _bufcnt += line != nullptr ? WideCharToMultiByte(_codePage, 0, line, linelen, &_buffer[_bufcnt], _bufsiz - _bufcnt, nullptr, nullptr) : 0;
    _bufcnt += type != nullptr ? WideCharToMultiByte(_codePage, 0, type, typelen, &_buffer[_bufcnt], _bufsiz - _bufcnt, nullptr, nullptr) : 0;
    _bufcnt += log != nullptr ? WideCharToMultiByte(_codePage, 0, log, loglen, &_buffer[_bufcnt], _bufsiz - _bufcnt, nullptr, nullptr) : 0;
    _buffer[_bufcnt++] = '\r';
    _buffer[_bufcnt++] = '\n';
    _buffer[_bufcnt] = 0;
}
