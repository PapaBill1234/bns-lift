// Daemon.obj (CacheGate PDB). Layout from include/pdb/CacheGate/types.h.
#pragma once
#include "Lock.h"

struct ZSTD_CDict_s;
extern "C" size_t ZSTD_freeCDict(ZSTD_CDict_s* cdict);  // 0x18380 TODO(lift-zstd)
class Console;
class Session;
class Packet;
class PipeConsole;
class ThreadManager;
class TimerQueue;
class Timer;
class DelayedRelease;
class Network;

// Layout from the IDA type _cidraddress.
struct _cidraddress
{
    unsigned long address;
    unsigned long netmask;
};
static_assert(sizeof(_cidraddress) == 0x8, "sizeof _cidraddress");

// PDB: the enum has no name (type <unnamed-type-RunMode>, 0x304D). The value names are PDB names.
enum RUN_MODE  // LIFT: The PDB enum has no name (0x304D).
{
    DAEMON_MODE = 0,
    TEXT_MODE = 1,
    WINDOW_MODE = 2,
};
extern RUN_MODE RunMode;                       // 0x5a148
extern int const CONFIG_DIR_OPTION_LEN;        // 0x593c0 (value 6)

void BloodDaemonMain(int argc, wchar_t** argv);  // 0xa690

class Daemon
{
public:
    typedef bool (*PacketHandler)(Session const* session, Packet const* packet);  // PDB nested type (0x259E)

    enum DaemonState  // PDB type 0x259A
    {
        STATE_UNKNOWN = 0,
        STATE_STOPPED = 1,
        STATE_STOPPING = 2,
        STATE_STARTING = 3,
        STATE_RUNNING = 4,
        STATE_INVALID = 5,
        STATE_FLUSHING = 6,
        STATE_COOLDOWNING = 7,
        STATE_COOLDOWNED = 8,
        STATE_RELOADING = 9,
        STATE_MAX = 10,
    };

    // PDB type 0x25E8: unit and version are at offset 0.
    struct Version
    {
        union
        {
            unsigned short unit[4];
            unsigned long long version;
        };
    };

    Daemon();                                  // 0xaa90
    virtual ~Daemon();                         // 0xacf0
    virtual wchar_t const* ServiceName() = 0;
    virtual wchar_t const* ShortName() = 0;
    virtual wchar_t const* Name() = 0;
    virtual wchar_t const* Descriptions() = 0;
    virtual long GetTimerInterval() = 0;
    virtual long GetTimerMaxTime() = 0;
    virtual void PrintDependency() = 0;
protected:
    virtual bool initLog() = 0;
    virtual bool setArgument(int argc, wchar_t const** argv) = 0;
    virtual bool initialize() = 0;
    virtual bool initNetwork() = 0;
    virtual bool onStart() = 0;
    virtual void shutdown() = 0;
    virtual bool reload(wchar_t** args, int count) = 0;
    virtual bool cooldown();
public:
    virtual void FlushExtraLog();

    static bool Start(Console* console, bool debugMode, int argc, wchar_t const** argv);  // 0xad50
    // ❓ The PDB name is "public: bool Daemon::Reload(wchar_t**,int)" (not static), but the code
    // uses Daemon::Instance and the call gives argv in rcx. Thus the lift declares them static.
    static bool Reload(wchar_t** argv, int argc);  // 0xaf30
    static bool Cooldown();                        // 0xb050

    bool start(int argc, wchar_t const** argv);    // 0xb140
    static void LoadVersion(Version* ver, wchar_t* verStr, unsigned long long strLength);  // 0xbb30

protected:
    bool startDaemon();                            // 0xba80

private:
    void setCurrentDirectory();                    // 0xbcc0
    void setAddress();                             // 0xbda0
    void noTimerMain(Network* networkInstance);    // 0xc220
    void timerMain(Network* networkInstance);      // 0xc370
    void setState(int state);                      // LIFT: inlined helper (PipeConsole and Console state)
    friend class LobbyGateCooldownTimer;           // ❓ access for LobbyGateCooldownTimer::HandleEvent (0x13bf0, LobbyGate)

public:
    // PDB: Daemon::AddTimer, RemoveTimer (public). LIFT: no S_GPROC32 in the PDB; LTCG inlines them into the callers.
    bool AddTimer(long elapse, Timer* timer);
    bool RemoveTimer(Timer* timer);

    static Daemon* Instance;
    static long long Now;
    static wchar_t const* StateString[10];

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
    Version Ver;
    wchar_t VerStr[32];
    wchar_t hostname[256];
    unsigned long publicAddress;
    wchar_t publicAddrString[20];
    unsigned long internalAddress;
    wchar_t internalAddrString[20];
    wchar_t confDir[520];
    _cidraddress internalCIDR;
    _cidraddress publicCIDR;
    bool setInternalCIDR;
    bool setPublicCIDR;
    TimerQueue* GlobalTimerQueue;
    DelayedRelease* GlobalDelayedRelease;
    bool allowClientIPAddressInLogs;
    bool allowClientSessionLifeCycleInLogs;
};
static_assert(sizeof(Daemon) == 0x748, "sizeof Daemon");
static_assert(offsetof(Daemon, threadManager) == 0x30, "Daemon::threadManager");
static_assert(offsetof(Daemon, EndEvent) == 0x40, "Daemon::EndEvent");
static_assert(offsetof(Daemon, StartSystemTick64) == 0x50, "Daemon::StartSystemTick64");
static_assert(offsetof(Daemon, hostname) == 0xB0, "Daemon::hostname");
