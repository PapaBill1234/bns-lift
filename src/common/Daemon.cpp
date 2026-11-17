// Daemon.obj (CacheGate PDB).
#include "AlertSender.h"
#include "Daemon.h"
#include "Console.h"
#include "CrashHandler.h"
#include "DelayedRelease.h"
#include "Log.h"
#include "LogBuffer.h"
#include "Memory.h"
#include "Network.h"
#include "PipeConsole.h"
#include "SysInfo.h"
#include "TextConsole.h"
#include "Thread.h"
#include "TimerQueue.h"
#include "WinServiceConsole.h"
#include "WindowConsole.h"
#include <new>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <wchar.h>
#include <shlwapi.h>

#define DAEMON_FILE L"source\\Daemon.cpp"

// Inlined crash macro.
#define DAEMON_ASSERT_CRASH(line)                                            \
    do                                                                       \
    {                                                                        \
        Log::Write(Log::LT_ERROR, DAEMON_FILE, line, L"== CRASH == ASSERT CRASH"); \
        AlertSender::Write(DAEMON_FILE, line, L"== CRASH == ASSERT CRASH"); \
        CrashHandler::MakeCrash("source\\Daemon.cpp", line, L"");           \
    } while (0)

Daemon* Daemon::Instance = nullptr;
long long Daemon::Now = 0;
wchar_t const* Daemon::StateString[10] = {
    L"UNKNOWN", L"STOPPED", L"STOPPING", L"STARTING", L"RUNNING",
    L"INVALID", L"FLUSHING", L"COOLDOWNING", L"COOLDOWNED", L"RELOADING",
};  // 0x59180
RUN_MODE RunMode = static_cast<RUN_MODE>(-1);  // ❓ initial data is 0xFFFFFFFF
int const CONFIG_DIR_OPTION_LEN = 6;            // wcslen(L"--conf")

namespace
{
// LIFT: Inlined helper of Memory.cpp (source line 57). It creates the manager of one section.
void initMemorySection(int section, void const* option)
{
    if (Memory::_Manager[section] != nullptr)
    {
        Log::Write(Log::LT_ERROR, L"source\\Memory.cpp", 57,
                   L"== CRASH == [memory], already initialized memory manager, section: %d", section);
        AlertSender::Write(L"source\\Memory.cpp", 57,
                           L"== CRASH == [memory], already initialized memory manager, section: %d", section);
    }
    else
    {
        Memory::_Manager[section] = Memory::CreateManager(Memory::MMGR_DEFAULT, option, 0, false);
    }
}

// LIFT: Inlined helper of Memory.cpp (source line 85). It releases the manager of one section.
void finiMemorySection(int section)
{
    MemoryManager* manager = const_cast<MemoryManager*>(Memory::_Manager[section]);
    if (manager != nullptr)
    {
        manager->Clear();
        manager = const_cast<MemoryManager*>(Memory::_Manager[section]);
        if (manager != nullptr)
            manager->~MemoryManager();  // ❓ binary calls the deleting destructor with flag 1
        BaseMemoryManager::_Instance.Free(manager, L"source\\Memory.cpp", 85);
        Memory::_Manager[section] = nullptr;
    }
}

// LIFT: Inlined helper. The IPv4 text buffers are in .tls (+0x40 char[32], +0x60 wchar_t[32]).
__declspec(thread) char addressStringA[32];
__declspec(thread) wchar_t addressStringW[32];

wchar_t const* addressToString(unsigned long address)  // LIFT: lift helper name, not in any PDB
{
    wchar_t* wide = addressStringW;
    char* narrow = addressStringA;
    wide[0] = 0;
    narrow[0] = 0;
    in_addr in;
    in.s_addr = address;
    char const* text = inet_ntoa(in);
    if (text != nullptr)
        strcpy_s(narrow, 32, text);
    if (narrow != nullptr)
    {
        wide[31] = 0;
        MultiByteToWideChar(CP_ACP, 0, narrow, -1, wide, 31);
    }
    return wide;
}

// LIFT: Inlined helper. 3 = 10/8, 2 = 172.16/12, 1 = 192.168/16, 0 = other.
int privateClass(unsigned long address)
{
    if ((htonl(address) & 0xFF000000) == 0x0A000000)
        return 3;
    if ((htonl(address) & 0xFFF00000) == 0xAC100000)
        return 2;
    return (htonl(address) & 0xFFFF0000) == 0xC0A80000;
}
}  // namespace

// 0xa430
static void printUsage(wchar_t const* argv0)
{
    wprintf(L"Usage: %s [<option>]\n", argv0);
    wprintf(L"      %s\n", L"--help");
    wprintf(L"        : this screen.\n");
    wprintf(L"      %s\n", L"--version");
    wprintf(L"        : version.\n");
    wprintf(L"      %s\n", L"--window");
    wprintf(L"        : window console mode. DEFAULT\n");
    wprintf(L"      %s\n", L"--window-exitcmd");
    wprintf(L"        : window console mode and exit cmd\n");
    wprintf(L"      %s\n", L"--text");
    wprintf(L"        : text console mode.\n");
    wprintf(L"      %s [<postfix>] [<confdir>]\n", L"--install");
    wprintf(L"        : install service [with service name <postfix>] [with config dir <confdir>].\n");
    wprintf(L"      %s [<postfix>]\n", L"--uninstall");
    wprintf(L"        : uninstall service [with service name <postfix>].\n");
    exit(1);
}

// 0xa540
static Console* makeConsole()
{
    if (RunMode == DAEMON_MODE)
    {
        // ❓ source line is not in the decompiled call (119 is a guess)
        void* memory = BaseMemoryManager::_Instance.Alloc(sizeof(WinServiceConsole), DAEMON_FILE, 119);
        return memory != nullptr ? new (memory) WinServiceConsole() : nullptr;
    }
    if (RunMode == TEXT_MODE)
    {
        void* memory = BaseMemoryManager::_Instance.Alloc(sizeof(TextConsole), DAEMON_FILE, 121);
        return memory != nullptr ? new (memory) TextConsole() : nullptr;
    }
    if (RunMode == WINDOW_MODE)
    {
        void* memory = BaseMemoryManager::_Instance.Alloc(sizeof(WindowConsole), DAEMON_FILE, 123);
        return memory != nullptr ? new (memory) WindowConsole() : nullptr;
    }
    Log::Write(Log::LT_ERROR, DAEMON_FILE, 126, L"== CRASH == [daemon], invalid run mode");
    AlertSender::Write(DAEMON_FILE, 126, L"== CRASH == [daemon], invalid run mode");
    return nullptr;
}

// 0xa690
void BloodDaemonMain(int argc, wchar_t** argv)
{
    SYSTEM_INFO systemInfo;
    GetSystemInfo(&systemInfo);
    SysInfo::_PageSize = systemInfo.dwPageSize;
    SysInfo::_ProcessorCount = systemInfo.dwNumberOfProcessors;
    SysInfo::_Granularity = systemInfo.dwAllocationGranularity;
    CrashHandler::Initialize(0, false);  // ❓ LTCG removed the arguments
    initMemorySection(1, nullptr);
    initMemorySection(2, HeapMemoryManager::LFH);
    if (Daemon::Instance == nullptr)
        DAEMON_ASSERT_CRASH(166);

    for (int i = 1; i < argc; ++i)
    {
        if (_wcsicmp(argv[i], L"--version") == 0)
        {
            wprintf(L"%s\n", Daemon::Instance->Descriptions());
            wprintf(L"%s %s %s / PlatformBinary server %s\n", Daemon::Instance->Name(), L"service",
                    Daemon::Instance->VerStr, L"0.0.346.440");
            Daemon::Instance->PrintDependency();
            exit(0);
        }
    }

    wchar_t path[MAX_PATH + 4];
    GetModuleFileNameW(nullptr, path, MAX_PATH);
    PathRemoveFileSpecW(path);
    PathAddBackslashW(path);
    // BUG: 0xa690 the path is used as the format string of swprintf_s.
    // 0xc5d0 is the template swprintf_s<520>. The Wine headers do not have it, so the size is explicit.
    swprintf_s(Daemon::Instance->confDir, 520, path);

    if (GetConsoleWindow() != nullptr)
    {
        RunMode = WINDOW_MODE;
        for (int i = 1; i < argc; ++i)
        {
            if (_wcsicmp(argv[i], L"--help") == 0)
                printUsage(argv[0]);
            if (_wcsicmp(argv[i], L"--text") == 0)
            {
                RunMode = TEXT_MODE;
            }
            else if (_wcsicmp(argv[i], L"--window") == 0)
            {
                RunMode = WINDOW_MODE;
            }
            else
            {
                if (_wcsicmp(argv[i], L"--install") == 0 && i + 2 < argc)
                {
                    // ❓ LTCG removed the daemon argument (rcx = postfix).
                    WinServiceConsole::InstallService(Daemon::Instance, argv[i + 1], argv[i + 2]);
                    exit(0);
                }
                if (_wcsicmp(argv[i], L"--uninstall") == 0)
                {
                    // ❓ LTCG removed the daemon argument (rcx = postfix).
                    WinServiceConsole::UninstallService(Daemon::Instance, argv[i + 1]);
                    exit(0);
                }
                if (_wcsnicmp(argv[i], L"--conf", CONFIG_DIR_OPTION_LEN) != 0)
                    printUsage(argv[0]);
                // BUG: 0xa690 the argument is used as the format string of swprintf_s.
                swprintf_s(Daemon::Instance->confDir, 520, &argv[i][CONFIG_DIR_OPTION_LEN + 1]);
            }
        }
    }
    else
    {
        RunMode = DAEMON_MODE;
    }

    Console* console = makeConsole();
    Daemon::Start(console, RunMode != DAEMON_MODE, argc, const_cast<wchar_t const**>(argv));
}

// 0xaa90
Daemon::Daemon()
{
    if (Instance != nullptr)
        DAEMON_ASSERT_CRASH(264);
    Instance = this;
    Now = _time64(nullptr);
    console = nullptr;
    pipeConsole = nullptr;
    threadManager = nullptr;
    State = STATE_STOPPED;
    StartSystemTick = GetTickCount();
    StartSystemTick64 = GetTickCount64();
    CurrentTick = 0;
    StartTime = _time64(nullptr);
    Ver.version = 0;
    memset(VerStr, 0, sizeof(VerStr));
    memset(hostname, 0, sizeof(hostname));
    memset(publicAddrString, 0, sizeof(publicAddrString));
    memset(internalAddrString, 0, sizeof(internalAddrString));
    memset(confDir, 0, sizeof(confDir));
    publicAddress = 0;
    internalAddress = 0;
    GlobalTimerQueue = nullptr;
    GlobalDelayedRelease = nullptr;
    internalCIDR.address = 0;
    internalCIDR.netmask = 0;
    setInternalCIDR = false;
    setPublicCIDR = false;
    publicCIDR.address = 0;
    publicCIDR.netmask = 0;
    allowClientIPAddressInLogs = true;
    allowClientSessionLifeCycleInLogs = true;
    _zstdCDic = nullptr;
    _cDicBuffer = nullptr;
    _cDicBufferSize = 8000;
    LoadVersion(&Ver, VerStr, 32);  // ❓ r8 is not set at the call; 32 is the size of VerStr
}

// 0xacf0
Daemon::~Daemon()
{
    Instance = nullptr;
    if (_zstdCDic != nullptr)
    {
        ZSTD_freeCDict(_zstdCDic);
        _zstdCDic = nullptr;
    }
    // EndEvent: SystemEvent::~SystemEvent closes the handle.
}

// LIFT: Inlined helper. It sets the state of the pipe console and of the console.
void Daemon::setState(int state)
{
    State = state;
    if (pipeConsole != nullptr)
    {
        pipeConsole->_lock.Enter();
        pipeConsole->_state = state;
        pipeConsole->_lock.Leave();
    }
    if (console != nullptr)
        console->SetState(state);
}

// 0xad50
bool Daemon::Start(Console* console, bool debugMode, int argc, wchar_t const** argv)
{
    Daemon* daemon = Instance;
    if (console == nullptr)
        DAEMON_ASSERT_CRASH(332);

    void* memory = BaseMemoryManager::_Instance.Alloc(sizeof(ThreadManager), DAEMON_FILE, 336);
    ThreadManager* threadManager = memory != nullptr ? new (memory) ThreadManager() : nullptr;
    daemon->threadManager = threadManager;
    if (threadManager == nullptr || !threadManager->Initialize(128))
        return false;

    memory = BaseMemoryManager::_Instance.Alloc(sizeof(PipeConsole), DAEMON_FILE, 341);
    PipeConsole* pipeConsole = memory != nullptr ? new (memory) PipeConsole() : nullptr;
    daemon->pipeConsole = pipeConsole;
    if (pipeConsole == nullptr || !pipeConsole->init())
        return false;

    daemon->console = console;
    if (!console->Open())
    {
        console->WriteStartLog(0, L"[%s], cannot open console, daemon: %s", daemon->ShortName(),
                               daemon->Descriptions());
        return false;
    }
    if (debugMode)
    {
        if (!daemon->start(argc, argv))
        {
            console->WriteStartLog(0, L"[%s], cannot start, daemon: %s", daemon->ShortName(), daemon->Descriptions());
            console->Close();
            return false;
        }
    }
    else
    {
        daemon->startDaemon();
    }
    return true;
}

// 0xaf30
bool Daemon::Reload(wchar_t** argv, int argc)
{
    Daemon* daemon = Instance;
    if (daemon->State != STATE_RUNNING)
    {
        Log::Write(Log::LT_ERROR, DAEMON_FILE, 375, L"[%s], reload failed; not running", daemon->ShortName());
        return false;
    }
    daemon->setState(STATE_RELOADING);
    if (daemon->reload(argv, argc))
        daemon->setState(STATE_RUNNING);
    return true;
}

// 0xb050
bool Daemon::Cooldown()
{
    Daemon* daemon = Instance;
    if (daemon->State != STATE_RUNNING)
    {
        Log::Write(Log::LT_ERROR, DAEMON_FILE, 412, L"[%s], cooldown failed; not running", daemon->ShortName());
        return false;
    }
    daemon->setState(STATE_COOLDOWNING);
    if (daemon->cooldown())
        daemon->setState(STATE_COOLDOWNED);
    return true;
}

// 0xb140
bool Daemon::start(int argc, wchar_t const** argv)
{
    srand(static_cast<unsigned int>(_time64(nullptr)));
    LogBufferAllocator::Initialize();
    PacketBufferAllocator::Initialize();
    EndEvent.Event = CreateEventW(nullptr, FALSE, FALSE, nullptr);
    SysInfo::Hostname(0, hostname, 256);  // ❓ LTCG removed the address and length arguments
    console->SetTitle(nullptr);           // ❓ LTCG removed the title argument
    setState(STATE_STARTING);

    unsigned long long startTick = GetTickCount64();
    console->WriteStartLog(1, L"[%s], starting, daemon: %s, version: %s", ShortName(), Descriptions(), VerStr);
    initMemorySection(0, nullptr);
    Log::Initialize();
    if (Log::instance != nullptr)
        Log::instance->open = true;
    if (RunMode == DAEMON_MODE)
        setCurrentDirectory();

    if (!initLog())
    {
        console->WriteStartLog(0, L"[%s], log initialize failed, daemon: %s", ShortName(), Descriptions());
        return false;
    }
    setAddress();
    Log::Write(Log::LT_DEBUG, DAEMON_FILE, 496, L"[%s], Starting, daemon: %s, version: %s, desc: %s", ShortName(),
               Descriptions(), VerStr, Descriptions());
    Log::Write(Log::LT_DEBUG, DAEMON_FILE, 497,
               L"[%s], Network Configuration, daemon: %s, hostname: %s, public: %s, internal: %s", ShortName(),
               Descriptions(), Instance->hostname, Instance->publicAddrString, Instance->internalAddrString);

    Network* network = nullptr;
    if (!initialize())
    {
        Log::Write(Log::LT_ERROR, DAEMON_FILE, 507, L"[%s], initialize error, daemon: %s", ShortName(), Descriptions());
        goto fail;
    }

    StartSystemTick = GetTickCount();
    StartSystemTick64 = GetTickCount64();
    CurrentTick = 0;
    StartTime = _time64(nullptr);
    if (GetTimerInterval() != 0)
    {
        void* memory = BaseMemoryManager::_Instance.Alloc(sizeof(TimerQueue), DAEMON_FILE, 520);
        GlobalTimerQueue = memory != nullptr ? new (memory) TimerQueue() : nullptr;
        int slotCount = 1000 / GetTimerInterval() * GetTimerMaxTime();
        GlobalTimerQueue->Initialize(GetTimerInterval(), slotCount + 1);
    }
    {
        void* memory = BaseMemoryManager::_Instance.Alloc(sizeof(DelayedRelease), DAEMON_FILE, 525);
        GlobalDelayedRelease = memory != nullptr ? new (memory) DelayedRelease(DelayedRelease::DEFAULT_INTERVAL, DelayedRelease::DEFAULT_DELAY) : nullptr;
    }

    network = Network::initInstance(threadManager);
    if (network == nullptr || !initNetwork())
    {
        Log::Write(Log::LT_ERROR, DAEMON_FILE, 530, L"[%s], network initialize error, daemon: %s", ShortName(),
                   Descriptions());
        goto fail;
    }
    if (!onStart())
    {
        Log::Write(Log::LT_ERROR, DAEMON_FILE, 537, L"[%s], onStart fail, daemon: %s", ShortName(), Descriptions());
        Log::Close();
        return false;
    }
    finiMemorySection(0);

    setState(STATE_RUNNING);
    Log::Write(Log::LT_DEBUG, DAEMON_FILE, 545, L"[%s], start, daemon: %s, version: %s, loading time: %I64d",
               ShortName(), Descriptions(), VerStr, GetTickCount64() - startTick);
    console->WriteStartLog(1, L"[%s], start, daemon: %s, version: %s", ShortName(), Descriptions(), VerStr);
    if (GetTimerInterval() != 0)
        timerMain(network);
    else
        noTimerMain(network);

    Log::Write(Log::LT_DEBUG, DAEMON_FILE, 553, L"[%s], stop, daemon: %s, version: %s", ShortName(), Descriptions(),
               VerStr);
    console->WriteStartLog(1, L"[%s], stopping, daemon: %s, version: %s", ShortName(), Descriptions(), VerStr);
    setState(STATE_STOPPING);
    shutdown();
    GlobalDelayedRelease->Cleanup();
    Log::Close();
    AlertSender::_alertSender.fini();
    pipeConsole->cleanup();
    threadManager->StopAll(3000, false);  // ❓ LTCG removed forceTerminate

    // ❓ The binary calls each destructor and then BaseMemoryManager::Free (a delete macro).
    if (threadManager != nullptr)
        threadManager->~ThreadManager();
    BaseMemoryManager::_Instance.Free(threadManager, DAEMON_FILE, 570);
    threadManager = nullptr;
    if (pipeConsole != nullptr)
        pipeConsole->~PipeConsole();
    BaseMemoryManager::_Instance.Free(pipeConsole, DAEMON_FILE, 571);
    pipeConsole = nullptr;
    if (GlobalTimerQueue != nullptr)
        GlobalTimerQueue->~TimerQueue();
    BaseMemoryManager::_Instance.Free(GlobalTimerQueue, DAEMON_FILE, 572);
    GlobalTimerQueue = nullptr;
    if (GlobalDelayedRelease != nullptr)
        GlobalDelayedRelease->~DelayedRelease();
    BaseMemoryManager::_Instance.Free(GlobalDelayedRelease, DAEMON_FILE, 573);
    GlobalDelayedRelease = nullptr;

    setState(STATE_STOPPED);
    console->WriteStartLog(1, L"[%s], stopped, daemon: %s, version: %s", ShortName(), Descriptions(), VerStr);
    console->Close();
    return true;

fail:
    // LIFT: Inlined Log code: flush and close the log.
    if (Log::instance != nullptr)
    {
        Log::Flush();
        Log::instance->open = false;
    }
    return false;
}

// 0xba80
bool Daemon::startDaemon()
{
    SERVICE_TABLE_ENTRYW dispatchTable[2];
    dispatchTable[0].lpServiceName = const_cast<wchar_t*>(ServiceName());
    dispatchTable[0].lpServiceProc = reinterpret_cast<LPSERVICE_MAIN_FUNCTIONW>(WinServiceConsole::ServiceMain);
    dispatchTable[1].lpServiceName = nullptr;
    dispatchTable[1].lpServiceProc = nullptr;
    if (StartServiceCtrlDispatcherW(dispatchTable))
        return true;
    unsigned long lastError = GetLastError();
    // BUG: 0xba80 the format has %s for the DWORD error code.
    console->WriteStartLog(0, L"[%s], service control dispatcher faild, daemon: %s, code: %s", ShortName(),
                           Descriptions(), lastError);
    return false;
}

// 0xbb30
void Daemon::LoadVersion(Version* ver, wchar_t* verStr, unsigned long long strLength)
{
    if (ver == nullptr || verStr == nullptr)
        return;
    wchar_t path[512];
    if (GetModuleFileNameW(nullptr, path, 512) == 512)
        DAEMON_ASSERT_CRASH(660);
    unsigned long zero[4];
    unsigned long size = GetFileVersionInfoSizeW(path, zero);
    if (size == 0)
        return;
    void* buffer = _alloca(size);
    VS_FIXEDFILEINFO* ffi;
    unsigned int length;
    if (buffer != nullptr && GetFileVersionInfoW(path, 0, size, buffer) &&
        VerQueryValueW(buffer, L"\\", reinterpret_cast<void**>(&ffi), &length))
    {
        ver->unit[0] = HIWORD(ffi->dwFileVersionMS);
        ver->unit[1] = LOWORD(ffi->dwFileVersionMS);
        ver->unit[2] = HIWORD(ffi->dwFileVersionLS);
        ver->unit[3] = LOWORD(ffi->dwFileVersionLS);
        swprintf_s(verStr, 32, L"%d.%d.%d.%d", ver->unit[0], ver->unit[1], ver->unit[2], ver->unit[3]);
    }
}

// 0xbcc0
void Daemon::setCurrentDirectory()
{
    wchar_t path[264];
    wchar_t drive[8];
    wchar_t dir[264];
    wchar_t filename[264];
    wchar_t ext[264];
    wchar_t cur[264];
    GetModuleFileNameW(nullptr, path, MAX_PATH);
    _wsplitpath_s(path, drive, 3, dir, MAX_PATH, filename, MAX_PATH, ext, MAX_PATH);
    swprintf_s(cur, MAX_PATH, L"%s%s", drive, dir);
    SetCurrentDirectoryW(cur);
}

// 0xbda0
void Daemon::setAddress()
{
    int count = 16;
    unsigned long address[16];
    int type[16];
    unsigned long internal = 0;
    unsigned long publicAddr = 0;
    SysInfo::IpAddress(hostname, &count, address);

    if (setInternalCIDR)
    {
        for (int i = 0; i < count; ++i)
        {
            if ((internalCIDR.netmask & internalCIDR.address) == (address[i] & internalCIDR.netmask))
            {
                internal = address[i];
                break;
            }
        }
    }
    if (setPublicCIDR)
    {
        for (int i = 0; i < count; ++i)
        {
            if ((publicCIDR.netmask & publicCIDR.address) == (address[i] & publicCIDR.netmask))
            {
                publicAddr = address[i];
                break;
            }
        }
    }
    for (int i = 0; i < count; ++i)
    {
        unsigned long current = address[i];
        if (privateClass(current) != 0)
        {
            if (!setInternalCIDR || internal == 0)
            {
                if (internal == 0 || privateClass(internal) < privateClass(current))
                    internal = current;
            }
        }
        else if ((htonl(current) & 0xFFFF0000) != 0xA9FE0000 && (htonl(current) & 0xFF000000) != 0x7F000000 &&
                 (htonl(current) & 0xF0000000) != 0xE0000000 && (htonl(current) & 0xF0000000) != 0xF0000000 &&
                 (!setPublicCIDR || publicAddr == 0))
        {
            type[i] = 2;  // the value is not read again
            if (publicAddr == 0)
                publicAddr = current;
        }
    }

    if (internal != 0)
    {
        internalAddress = internal;
    }
    else
    {
        Log::Write(Log::LT_ERROR, DAEMON_FILE, 914, L"[%s], internal address is not found; set public address",
                   ShortName());
        if (publicAddr == 0)
            Log::Write(Log::LT_ERROR, DAEMON_FILE, 918, L"[%s], public address is not found", ShortName());
        internalAddress = publicAddr;
    }
    publicAddress = publicAddr;
    wcsncpy(publicAddrString, addressToString(publicAddress), 20);
    wcsncpy(internalAddrString, addressToString(internalAddress), 20);
    (void)type;
}

// 0xc220
void Daemon::noTimerMain(Network* networkInstance)
{
    int flushCount = 1;
    long long flushTime = Instance->StartTime + 600;
    tm local;
    _localtime64_s(&local, &flushTime);
    local.tm_sec = 0;
    local.tm_min = 0;
    flushTime = _mktime64(&local);
    for (;;)
    {
        long interval = GlobalDelayedRelease->_interval;
        if (static_cast<int>(1000 * (flushTime - _time64(nullptr))) < interval)
            interval = static_cast<long>(1000 * (flushTime - _time64(nullptr)));
        if (EndEvent.Event != nullptr && WaitForSingleObject(EndEvent.Event, interval) == WAIT_OBJECT_0)
            break;
        long long now = _time64(nullptr);
        threadManager->_now = now;
        Now = now;
        // ❓ LTCG removed count, force and all
        GlobalDelayedRelease->Release(GetTickCount64() - Instance->StartSystemTick64, 0, false, false);
        if (flushTime <= now)
        {
            if (--flushCount == 0)
            {
                Log::Flush();  // LIFT: inlined
                flushCount = 1;
            }
            flushTime += 600;
        }
    }
}

// 0xc370
void Daemon::timerMain(Network* networkInstance)
{
    void* iocpHandle = networkInstance->_iocpHandle;
    int flushCount = 1;
    long long flushTime = Instance->StartTime + 600;
    tm local;
    _localtime64_s(&local, &flushTime);
    local.tm_sec = 0;
    local.tm_min = 0;
    flushTime = _mktime64(&local);
    long long interval = GetTimerInterval();
    unsigned long long nextTick = GetTickCount64();
    CurrentTick = 0;
    TimerQueue::Slot slot;
    slot.head = nullptr;
    slot.tail = nullptr;
    for (;;)
    {
        nextTick += interval;
        int wait = static_cast<int>(nextTick - GetTickCount64());
        if (wait <= 0)
        {
            Log::Write(Log::LT_DEBUG, DAEMON_FILE, 1065,
                       L"[%s], no wait; wait interval is less than threshold, wait: %d, threshold: %d", ShortName(),
                       wait, 0);
        }
        else if (EndEvent.Event != nullptr && WaitForSingleObject(EndEvent.Event, wait) == WAIT_OBJECT_0)
        {
            break;
        }
        long long now = _time64(nullptr);
        threadManager->_now = now;
        Now = now;
        // ❓ LTCG removed count, force and all
        GlobalDelayedRelease->Release(GetTickCount64() - Instance->StartSystemTick64, 0, false, false);
        ++CurrentTick;
        GlobalTimerQueue->TimeExpired(&slot);
        while (slot.head != nullptr)
        {
            Timer* timer = slot.head;
            timer->prev = nullptr;
            slot.head = timer->next;
            timer->next = nullptr;
            timer->SlotIndex = -1;
            if (slot.head == nullptr)
                slot.tail = nullptr;
            timer->preprocessExpireEvent();
            PostQueuedCompletionStatus(iocpHandle, 0, reinterpret_cast<ULONG_PTR>(timer), nullptr);
            timer->removeReferenceCount(DAEMON_FILE, 1091);
        }
        if (flushTime <= now)
        {
            if (--flushCount == 0)
            {
                Log::Flush();  // LIFT: inlined
                flushCount = 1;
            }
            flushTime += 600;
        }
    }
}

// ❓ Not in the CacheGate hr export (the CacheGate class overrides it).
bool Daemon::cooldown()
{
    return true;  // TODO(lift-cg-5)
}

// ❓ Not in the CacheGate hr export (the CacheGate class overrides it).
void Daemon::FlushExtraLog()
{
    // TODO(lift-cg-5)
}
