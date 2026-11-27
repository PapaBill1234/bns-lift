// source_logarchive.cpp: logarchive.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "logarchive.h"
#include "LiftStub.h"

#pragma comment(linker, "/INCLUDE:?IsUnsentFileExist@LogArchive@@IEAA_NXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?isPingTimeExpired@LogArchive@@AEAA_NXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?startupWinSockLib@LogArchive@@AEAA_NXZ")  // LIFT: dead-strip keep (no live caller yet)

// 0x694070
__cdecl LogArchive::LogArchive(int)
{
    LIFT_STUB(0x694070);
}

// 0x6942d0
__cdecl LogArchive::~LogArchive(void)
{
    LIFT_STUB(0x6942d0);
}

// 0x6944f0
bool __cdecl LogArchive::Initialize(::LogArchive::DaemonType, unsigned short, wchar_t const *, unsigned long, bool, unsigned __int64, int, unsigned long, unsigned short, unsigned short)
{
    LIFT_STUB(0x6944f0);
}

// 0x694730
bool __cdecl LogArchive::Start(bool)
{
    LIFT_STUB(0x694730);
}

// 0x694810
void __cdecl LogArchive::Write(char const *, ...)
{
    LIFT_STUB(0x694810);
}

// 0x694980
void __cdecl LogArchive::run(void)
{
    LIFT_STUB(0x694980);
}

// 0x694b90
bool __cdecl LogArchive::AccessLogServer(long)
{
    LIFT_STUB(0x694b90);
}

// 0x695070
bool __cdecl LogArchive::IsUnsentFileExist(void)
{
    wchar_t searchFilePath[MAX_PATH] = { 0 };
    swprintf_s(searchFilePath, MAX_PATH, L"%s\\*.unsent", _unsentPath);

    WIN32_FIND_DATAW wfd;
    HANDLE find = FindFirstFileW(searchFilePath, &wfd);
    if (find == INVALID_HANDLE_VALUE)
        return false;

    if (!FindClose(find))
    {
        Log::Write(Log::LT_ERROR, L"source\\LogArchive.cpp", 464, L"== CRASH == [LogArchive], FindClose failed");
        AlertSender::Write(L"source\\LogArchive.cpp", 464, L"== CRASH == [LogArchive], FindClose failed");
    }
    return true;
}

// 0x695150
bool __cdecl LogArchive::ChangeFileMode(void)
{
    LIFT_STUB(0x695150);
}

// 0x6951e0
unsigned long __cdecl LogArchive::constructEventArray(void **const)
{
    LIFT_STUB(0x6951e0);
}

// 0x6952f0
void __cdecl LogArchive::processTimeout(void)
{
    LIFT_STUB(0x6952f0);
}

// 0x6953d0
void __cdecl LogArchive::processEventInFileMode(void *)
{
    LIFT_STUB(0x6953d0);
}

// 0x6954a0
void __cdecl LogArchive::processEventInNetMode(void *)
{
    LIFT_STUB(0x6954a0);
}

// 0x695530
void __cdecl LogArchive::flush(void)
{
    LIFT_STUB(0x695530);
}

// 0x6955b0
void __cdecl LogArchive::write(::LogBuffer const *)
{
    LIFT_STUB(0x6955b0);
}

// 0x695610
void __cdecl LogArchive::pushLogData(::LogBuffer const *)
{
    LIFT_STUB(0x695610);
}

// 0x695870
bool __cdecl LogArchive::isPingTimeExpired(void)
{
    static long long tick = GetTickCount64() - Daemon::Instance->StartSystemTick64;

    long long elapsed = GetTickCount64() - Daemon::Instance->StartSystemTick64 - tick;
    if (elapsed < _pingInterval)
        return false;

    tick = GetTickCount64() - Daemon::Instance->StartSystemTick64;
    return true;
}

// 0x6958f0
bool __cdecl LogArchive::pushPingReqPacket(void)
{
    LIFT_STUB(0x6958f0);
}

// 0x695aa0
bool __cdecl LogArchive::startupWinSockLib(void)
{
    WSADATA data;
    int error = WSAStartup(MAKEWORD(2, 2), &data);
    if (error == 0)
        return true;

    Log::Write(L"source\\LogArchive.cpp", 762, error, L"WSAStartup()");
    return false;
}
