// logarchive.h: logarchive.cpp, logarchive.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class LogArchive
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
};

