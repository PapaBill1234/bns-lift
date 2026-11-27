// logarchive.h: logarchive.cpp, logarchive.h (GameDaemon PDB, 2019 + PDB).
// LIFT: card lift-gamedaemon-e12 adds the PDB bases and data members (size 0x358).
#pragma once
#include "GameDaemonFwd.h"
#include "../BloodLib/include/Thread.h"
#include "../BloodLib/include/LogMedia.h"

class LogArchive : public Thread, public LogMedia
{
public:
    enum DaemonType {};
public:
    virtual wchar_t const * __cdecl Name(void);  // 0x694060
private:
    __cdecl LogArchive(int);  // 0x694070
    virtual __cdecl ~LogArchive(void);  // 0x6942d0
public:
    static bool __cdecl Initialize(::LogArchive::DaemonType, unsigned short, wchar_t const *, unsigned long, bool, unsigned __int64, int, unsigned long, unsigned short, unsigned short);  // 0x6944f0
    static bool __cdecl Start(bool);  // 0x694730
    static void __cdecl Write(char const *, ...);  // 0x694810
protected:
    virtual void __cdecl run(void);  // 0x694980
    bool __cdecl AccessLogServer(long);  // 0x694b90
    bool __cdecl IsUnsentFileExist(void);  // 0x695070
    bool __cdecl ChangeFileMode(void);  // 0x695150
private:
    unsigned long __cdecl constructEventArray(void **const);  // 0x6951e0
    void __cdecl processTimeout(void);  // 0x6952f0
    void __cdecl processEventInFileMode(void *);  // 0x6953d0
    void __cdecl processEventInNetMode(void *);  // 0x6954a0
    void __cdecl flush(void);  // 0x695530
protected:
    virtual void __cdecl write(::LogBuffer const *);  // 0x6955b0
private:
    void __cdecl pushLogData(::LogBuffer const *);  // 0x695610
    bool __cdecl isPingTimeExpired(void);  // 0x695870
    bool __cdecl pushPingReqPacket(void);  // 0x6958f0
    bool __cdecl startupWinSockLib(void);  // 0x695aa0

private:
    unsigned short _daemonType;                 // +0xE0
    unsigned short _daemonNo;                   // +0xE2
    wchar_t _unsentPath[260];                   // +0xE4
    unsigned long _logAgentAddr;                // +0x2EC
    unsigned short _logAgentPort;               // +0x2F0
    unsigned short _logServerPort;              // +0x2F2
    void* _terminateEvent;                      // +0x2F8
    bool _isLogServerEnable;                    // +0x300
    bool _isRecvPingAck;                        // +0x301
    unsigned long _waitTime;                    // +0x304
    unsigned long _queryReason;                 // +0x308
    unsigned long long _threadId;               // +0x310
    unsigned long long _logSequenceId;          // +0x318
    SystemEvent* _initWait;                     // +0x320
    LogAgent* _logAgent;                        // +0x328
    LogServer* _logServer;                      // +0x330
    LogArchiveFileManager* _fileManager;        // +0x338
    unsigned long _pingInterval;                // +0x340
    bool _seqIdLogEnable;                       // +0x344
    unsigned long long _seqIdLogMaxCount;       // +0x348
    bool _unsentOnly;                           // +0x350

    friend struct LogArchiveLayoutCheck;
};

struct LogArchiveLayoutCheck
{
    static_assert(offsetof(LogArchive, _daemonType) == 0xE0, "LogArchive::_daemonType");
    static_assert(offsetof(LogArchive, _unsentPath) == 0xE4, "LogArchive::_unsentPath");
    static_assert(offsetof(LogArchive, _pingInterval) == 0x340, "LogArchive::_pingInterval");
    static_assert(sizeof(LogArchive) == 0x358, "sizeof LogArchive");
};

