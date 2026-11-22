// LobbyPerfMonitor.obj (LobbyDaemon PDB, 2019 + PDB).
#include "LobbyPerfMonitor.h"
#include "Daemon.h"
#include "LiftStub.h"
#include "Log.h"
#include <wchar.h>
#if defined(__clang__)
#include <crt_cpp_overload.h>
#else
#pragma comment(linker, "/INCLUDE:??1SystemPerfMonitor@@UEAA@XZ")  // LIFT: keep until the caller is lifted (0x59ce0).
#pragma comment(linker, "/INCLUDE:?Initialize@SystemPerfMonitor@@QEAA_NXZ")  // LIFT: keep until the caller is lifted (0x59d60).
#pragma comment(linker, "/INCLUDE:?Start@SystemPerfMonitor@@QEAA_NXZ")  // LIFT: keep until the caller is lifted (0x59e30).
#endif

// 0x201ab8
GUID const SystemCounterSet::ID = {0xcc569971, 0x85f5, 0x43f2, {0xb8, 0xc7, 0x74, 0xd8, 0x51, 0xdd, 0x57, 0xd9}};

// 0x59ce0
SystemPerfMonitor::~SystemPerfMonitor()
{
}

// 0x59d60
bool SystemPerfMonitor::Initialize()
{
    wchar_t name[128];
    swprintf_s(name, L"lobby_%d", static_cast<int>(GetCurrentProcessId()));
    if (!_systemCounterSet.Create(name))
    {
        Log::Write(Log::LT_ERROR, L"LobbyPerfMonitor.cpp", 32,
            L"[perfmon-system], init fail; create counter set fail, name:%s", name);
        return false;
    }
    Log::Write(Log::LT_NOTICE, L"LobbyPerfMonitor.cpp", 39, L"[perfmon-system], init ok");
    return true;
}

// 0x59e30
bool SystemPerfMonitor::Start()
{
    if (_run)
    {
        Log::Write(Log::LT_NOTICE, L"LobbyPerfMonitor.cpp", 52,
            L"[perfmon-system], start fail; alread run");
        return false;
    }

    _run = true;
    if (Daemon::Instance->AddTimer(1000, this))
    {
        Log::Write(Log::LT_NOTICE, L"LobbyPerfMonitor.cpp", 64,
            L"[perfmon-system], start ok, update-period:%d(msec)", 1000);
        return true;
    }

    _run = false;
    Log::Write(Log::LT_ERROR, L"LobbyPerfMonitor.cpp", 60,
        L"[perfmon-system], start fail; add timer fail");
    return false;
}

// 0x59ee0
bool SystemPerfMonitor::HandleEvent(EventContext*, unsigned long)
{
    if (_run)
    {
        update();
        if (!Daemon::Instance->AddTimer(1000, this))
        {
            _run = false;
            Log::Write(Log::LT_ERROR, L"LobbyPerfMonitor.cpp", 83,
                L"[perfmon-system], add timer fail");
        }
    }
    return true;
}

// 0x59f40
void SystemPerfMonitor::update()
{
    LIFT_STUB(0x59f40);
}
