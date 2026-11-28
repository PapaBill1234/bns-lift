// logarchivesession.h: logarchivesession.cpp (GameDaemon PDB, 2019 + PDB).
#pragma once
#include "GameDaemonFwd.h"

// PDB: LogArchiveSession (GameDaemon), size 0x18.
class LogArchiveSession
{
public:
    enum SessionType
    {
        LOGARCHIVE_SESSION_INVALID = 0,
        LOGARCHIVE_SESSION_LOGAGENT = 1,
        LOGARCHIVE_SESSION_LOGSERVER = 2,
        LOGARCHIVE_SESSION_MAX = 3,
    };

    static wchar_t const *sessionNames[LOGARCHIVE_SESSION_MAX];  // rva 0xE761F8

    virtual __cdecl ~LogArchiveSession(void);  // 0x6b9d00
    virtual bool __cdecl Connect(unsigned long, unsigned short);  // 0x6b9d60
    bool __cdecl Send(::Packet const *);  // 0x6b9fd0
    bool __cdecl Recv(::Packet *);  // 0x6ba1f0
private:
    int __cdecl recv(char *, int, int);  // 0x6ba300
public:
    virtual void __cdecl Close(void);  // 0x6ba510

protected:
    unsigned long long _sock;    // +0x8
    unsigned int _timeoutSecond;  // +0x10
    SessionType _sessionType;     // +0x14
};
static_assert(sizeof(LogArchiveSession) == 0x18, "sizeof LogArchiveSession");
