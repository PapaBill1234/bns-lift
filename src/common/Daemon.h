// Daemon (CacheGate PDB). Layout from include/pdb/CacheGate/types.h.
// This card uses only the data layout and the statics. The Daemon functions
// are in a later card. Only declarations are here, so no vtable is emitted.
#pragma once
#include "Lock.h"

struct ZSTD_CDict_s;
class Console;
class PipeConsole;
class ThreadManager;
class TimerQueue;
class DelayedRelease;

class Daemon
{
public:
    virtual ~Daemon();
    virtual wchar_t const* ServiceName() = 0;
    virtual wchar_t const* ShortName() = 0;
    virtual wchar_t const* Name() = 0;
    virtual wchar_t const* Descriptions() = 0;
    virtual long GetTimerInterval() = 0;
    virtual long GetTimerMaxTime() = 0;
    virtual void PrintDependency() = 0;
    virtual bool initLog() = 0;
    virtual bool setArgument(int argc, wchar_t const** argv) = 0;
    virtual bool initialize() = 0;
    virtual bool initNetwork() = 0;
    virtual bool onStart() = 0;
    virtual void shutdown() = 0;
    virtual bool reload(wchar_t** args, int count) = 0;
    virtual bool cooldown();
    virtual void FlushExtraLog();

    static Daemon* Instance;
    static long long Now;

    ZSTD_CDict_s* _zstdCDic;
    unsigned char* _cDicBuffer;
    unsigned long long _cDicBufferSize;
    Console* console;
    PipeConsole* pipeConsole;
    ThreadManager* threadManager;
    int State;
    SystemEvent EndEvent;
    long StartSystemTick;
    long long StartSystemTick64;
    long CurrentTick;
    long long StartTime;
    alignas(8) unsigned char Ver[0x8];  // ❓ PDB type Daemon::Version
    wchar_t VerStr[32];
    wchar_t hostname[256];
    unsigned long publicAddress;
    wchar_t publicAddrString[20];
    unsigned long internalAddress;
    wchar_t internalAddrString[20];
    wchar_t confDir[520];
    alignas(4) unsigned char internalCIDR[0x8];  // ❓ PDB type _cidraddress
    alignas(4) unsigned char publicCIDR[0x8];    // ❓ PDB type _cidraddress
    bool setInternalCIDR;
    bool setPublicCIDR;
    TimerQueue* GlobalTimerQueue;
    DelayedRelease* GlobalDelayedRelease;
    bool allowClientIPAddressInLogs;
    bool allowClientSessionLifeCycleInLogs;
};
static_assert(sizeof(Daemon) == 0x748, "sizeof Daemon");
static_assert(offsetof(Daemon, threadManager) == 0x30, "Daemon::threadManager");
