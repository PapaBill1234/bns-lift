// WinServiceConsole.obj (CacheGate PDB).
#include "WinServiceConsole.h"
#include "Daemon.h"
#include "Log.h"
#include "AlertSender.h"
#include "CrashHandler.h"
#include <shellapi.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <wchar.h>
#if defined(__clang__)
#include <crt_cpp_overload.h>  // The Wine headers do not have swprintf_s<N>. VS2010 has it.
#endif

// 0x14005a378
WinServiceConsole* _WinServiceConsole = nullptr;

// LIFT: Inlined in makeConsole (0xa540): Console() and then all members are 0.
WinServiceConsole::WinServiceConsole()
    : ErrorCode(0), CheckPoint(0), Handle(nullptr)
{
    memset(&Status, 0, sizeof(Status));
}

// 0x40b0 (folded: return false)
bool WinServiceConsole::Writable()
{
    return false;
}

// 0x16f50 (folded: empty function)
void WinServiceConsole::write(LogBuffer const* logbuf)
{
}

// 0x16f50 (folded: empty function)
void WinServiceConsole::Write(Log::Type type, wchar_t const* file, int line, wchar_t const* format, char* args)
{
}

// 0x13fd0 (folded: empty function)
void WinServiceConsole::WriteStatusLog(wchar_t const* format, ...)
{
}

// 0x17630
void WinServiceControlHandler(unsigned long ctrlCode)
{
    if (Daemon::Instance != nullptr)
    {
        Console* console = Daemon::Instance->console;
        if (console != nullptr)
            console->controlHandler(ctrlCode);
    }
}

// 0x17660
bool WinServiceConsole::Open()
{
    if (_WinServiceConsole != nullptr)
    {
        Log::Write(Log::LT_ERROR, L"source\\WinServiceConsole.cpp", 32, L"== CRASH == ASSERT CRASH");
        AlertSender::Write(L"source\\WinServiceConsole.cpp", 32, L"== CRASH == ASSERT CRASH");
        CrashHandler::MakeCrash("source\\WinServiceConsole.cpp", 32, L"");
    }
    _WinServiceConsole = this;
    return true;
}

// 0x176e0
void WinServiceConsole::Close()
{
    if (Handle != nullptr)
    {
        Status.dwCurrentState = SERVICE_STOPPED;
        Status.dwControlsAccepted = SERVICE_ACCEPT_STOP;
        Status.dwWin32ExitCode = 0;
        Status.dwCheckPoint = 0;
        Status.dwWaitHint = 0;
        if (!SetServiceStatus(Handle, &Status))
            addLog(true, L"SetServiceStatus failed");
    }
}

// 0x17740
void WinServiceConsole::SetState(int state)
{
    if (Handle == nullptr)
        return;
    if (state == 4)
    {
        Status.dwCurrentState = SERVICE_RUNNING;
        Status.dwCheckPoint = 0;
        Status.dwWaitHint = 0;
    }
    else
    {
        if (state != 2)
            return;
        Status.dwCurrentState = SERVICE_STOP_PENDING;
        Status.dwWaitHint = 0;
        Status.dwCheckPoint = CheckPoint++;
    }
    Status.dwControlsAccepted = SERVICE_ACCEPT_STOP;
    Status.dwWin32ExitCode = 0;
    if (!SetServiceStatus(Handle, &Status))
        addLog(true, L"SetServiceStatus failed");
}

// 0x177d0
void WinServiceConsole::ServiceMain(unsigned long argCount, wchar_t** argVector)
{
    int argc = 0;
    LPWSTR* argv = CommandLineToArgvW(GetCommandLineW(), &argc);
    if (argv != nullptr)
    {
        for (int i = 1; i < argc; ++i)
        {
            if (_wcsnicmp(argv[i], L"--conf", 6) == 0)
                // BUG: 0x177d0 the command-line text is the format string (format-string injection).
                swprintf_s(Daemon::Instance->confDir, argv[i] + 7);
        }
        LocalFree(argv);
    }

    WinServiceConsole* self = _WinServiceConsole;
    self->Handle = RegisterServiceCtrlHandlerW(Daemon::Instance->ServiceName(), WinServiceControlHandler);
    if (self->Handle == nullptr)
    {
        addLog(true, L"RegisterServiceCtrlHandler failed");
        return;
    }
    self->Status.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
    self->Status.dwServiceSpecificExitCode = 0;
    self->Status.dwCurrentState = SERVICE_START_PENDING;
    self->Status.dwControlsAccepted = SERVICE_ACCEPT_STOP;
    self->Status.dwWin32ExitCode = 0;
    self->Status.dwWaitHint = 0;
    self->Status.dwCheckPoint = self->CheckPoint++;

    wchar_t const* message;
    if (!SetServiceStatus(self->Handle, &self->Status))
    {
        addLog(true, L"SetServiceStatus failed");
        message = L"reportStatusToSCManager(SERVICE_START_PENDING) failed";
    }
    else
    {
        // LIFT: SmartCouponDaemon 0x27512 sets only rcx. Daemon::start (0x171e0) writes edx/r8 before it reads them. The args are not used.
        if (Daemon::Instance->start(0, nullptr))
            return;
        message = L"Daemon Start failed";
    }
    addLog(true, message);
    self->Close();
}

// 0x17960
void WinServiceConsole::WriteStartLog(int type, wchar_t const* format, ...)
{
    wchar_t msg[256];
    va_list args;
    va_start(args, format);
    _vsnwprintf_s(msg, 256, 255, format, args);
    va_end(args);
    addLog(type == 0, msg);
}

// 0x179e0
bool WinServiceConsole::controlHandler(unsigned long ctrlCode)
{
    if (ctrlCode != SERVICE_CONTROL_STOP)
    {
        // LIFT: SmartCouponDaemon 0x275e2 tail jump sets only edx. The callee does not use exitCode and waitHint here.
        return reportStatusToSCManager(Status.dwCurrentState, 0, 0);
    }
    if (Daemon::Instance != nullptr && Daemon::Instance->EndEvent.Event != nullptr)
        SetEvent(Daemon::Instance->EndEvent.Event);
    return false;
}

// 0x17a20
// LIFT: noinline. The original controlHandler (0x179e0) calls this function. VS2010 /LTCG inlines it without the attribute.
__declspec(noinline) bool WinServiceConsole::reportStatusToSCManager(unsigned long currentState, unsigned long exitCode,
                                                unsigned long waitHint)
{
    Status.dwCurrentState = currentState;
    Status.dwControlsAccepted = SERVICE_ACCEPT_STOP;
    Status.dwWin32ExitCode = 0;
    Status.dwWaitHint = 0;
    if (currentState == SERVICE_RUNNING || currentState == SERVICE_STOPPED)
        Status.dwCheckPoint = 0;
    else
        Status.dwCheckPoint = CheckPoint++;
    if (SetServiceStatus(Handle, &Status))
        return true;
    addLog(true, L"SetServiceStatus failed");
    return false;
}

// 0x17aa0
// LIFT: SmartCouponDaemon 0x27690 writes edx at 0x276ba before it reads it. The body uses 255 (0x27708).
wchar_t const* WinServiceConsole::getLastErrorText(wchar_t* errorString, int size)
{
    wchar_t* tempString = nullptr;
    DWORD ret = FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM |
                                   FORMAT_MESSAGE_ARGUMENT_ARRAY,
                               nullptr, GetLastError(), 0, (LPWSTR)&tempString, 0, nullptr);
    if (ret != 0 && (int)(ret + 14) <= 255)
    {
        tempString[lstrlenW(tempString) - 2] = L'\0';
        swprintf(errorString, 255, L"%s (0x%x)", tempString, GetLastError());
    }
    else
    {
        errorString[0] = L'\0';
    }
    if (tempString != nullptr)
        LocalFree(tempString);
    return errorString;
}

// 0x17b50
void WinServiceConsole::addLog(bool error, wchar_t const* message)
{
    _WinServiceConsole->ErrorCode = GetLastError();
    HANDLE eventSource = RegisterEventSourceW(nullptr, Daemon::Instance->ServiceName());
    wchar_t const* type = error ? L"error" : L"log";
    wchar_t msg[256];
    swprintf(msg, 255, L"%s %s: %d", Daemon::Instance->ServiceName(), type, _WinServiceConsole->ErrorCode);
    wchar_t const* str[2] = { msg, message };
    if (eventSource != nullptr)
    {
        ReportEventW(eventSource, error ? EVENTLOG_ERROR_TYPE : EVENTLOG_INFORMATION_TYPE, 0, 0, nullptr, 2, 0,
                     str, nullptr);
        DeregisterEventSource(eventSource);
    }
}

// 0x17c80
bool WinServiceConsole::InstallService(Daemon* daemon, wchar_t const* postfix, wchar_t const* confdir)
{
    Daemon* instance = Daemon::Instance;
    if (instance == nullptr || instance->ServiceName() == nullptr || instance->Descriptions() == nullptr)
        return false;

    wchar_t desc[264];
    wchar_t name[264];
    wchar_t errorString[256];
    wchar_t path[784];

    wcscpy_s(name, 260, instance->ServiceName());
    wcscpy_s(desc, 260, instance->Descriptions());
    if (daemon != nullptr)
    {
        // PDB: param type is Daemon* (0x4D56, 0x4D58). The caller at 0x16aea gives an argv string. 0x278e4 passes it to wcscat_s as Source.
        wcscat_s(name, 260, (wchar_t const*)daemon);
        wcscat_s(desc, 260, (wchar_t const*)daemon);
    }

    path[0] = L'"';
    if (GetModuleFileNameW(nullptr, &path[1], 780) == 0)
    {
        wprintf(L"Unable to register [%s] - %s\n", desc, getLastErrorText(errorString, 0));
        return false;
    }
    size_t len = wcslen(path);
    path[len] = L'"';
    swprintf_s(&path[len + 1], 779 - len, L" \"--conf=%s\"", postfix);

    SC_HANDLE manager = OpenSCManagerW(nullptr, nullptr, SC_MANAGER_ALL_ACCESS);
    if (manager != nullptr)
    {
        // The dependency list is double-null terminated: the original string is 6 bytes.
        SC_HANDLE service = CreateServiceW(manager, name, desc, SERVICE_ALL_ACCESS, SERVICE_WIN32_OWN_PROCESS,
                                           SERVICE_DEMAND_START, SERVICE_ERROR_NORMAL, path, nullptr, nullptr,
                                           L"\0\0", nullptr, nullptr);
        if (service != nullptr)
        {
            wprintf(L"[%s] was registered.\n", desc);
            CloseServiceHandle(service);
            CloseServiceHandle(manager);
            return true;
        }
        else
        {
            wprintf(L"CreateService failed - %s\n", getLastErrorText(errorString, 0));
            CloseServiceHandle(manager);
            return false;
        }
    }
    else
    {
        wprintf(L"OpenSCManager failed - %s\n", getLastErrorText(errorString, 0));
        return false;
    }
}

// 0x17f00
bool WinServiceConsole::UninstallService(Daemon* daemon, wchar_t const* postfix)
{
    Daemon* instance = Daemon::Instance;
    if (instance == nullptr || instance->ServiceName() == nullptr || instance->Descriptions() == nullptr)
        return false;

    SERVICE_STATUS status;
    wchar_t desc[264];
    wchar_t errorString[256];
    wchar_t name[264];

    wcscpy_s(name, 260, instance->ServiceName());
    wcscpy_s(desc, 260, instance->Descriptions());
    if (daemon != nullptr)
    {
        // PDB: param type is Daemon* (0x4D56, 0x4D58). The caller at 0x16aea gives an argv string. 0x278e4 passes it to wcscat_s as Source.
        wcscat_s(name, 260, (wchar_t const*)daemon);
        wcscat_s(desc, 260, (wchar_t const*)daemon);
    }

    SC_HANDLE manager = OpenSCManagerW(nullptr, nullptr, SC_MANAGER_ALL_ACCESS);
    if (manager != nullptr)
    {
        SC_HANDLE service = OpenServiceW(manager, name, SERVICE_ALL_ACCESS);
        if (service != nullptr)
        {
            if (ControlService(service, SERVICE_CONTROL_STOP, &status))
            {
                wprintf(L"Stopping [%s]...", desc);
                Sleep(1000);
                while (QueryServiceStatus(service, &status))
                {
                    if (status.dwCurrentState != SERVICE_STOP_PENDING)
                        break;
                    wprintf(L".");
                    Sleep(1000);
                }
                if (status.dwCurrentState == SERVICE_STOPPED)
                    wprintf(L"\n[%s] was stopped.\n", desc);
                else
                    wprintf(L"\nFailed to stop [%s].\n", desc);
            }

            if (DeleteService(service))
            {
                wprintf(L"[%s] was unregistered.\n", desc);
                CloseServiceHandle(service);
                CloseServiceHandle(manager);
                return true;
            }
            else
            {
                wprintf(L"DeleteService failed - %s\n", getLastErrorText(errorString, 0));
                CloseServiceHandle(service);
                CloseServiceHandle(manager);
                return false;
            }
        }
        else
        {
            wprintf(L"OpenService failed - %s\n", getLastErrorText(errorString, 0));
            CloseServiceHandle(manager);
            return false;
        }
    }
    else
    {
        wprintf(L"OpenSCManager failed - %s\n", getLastErrorText(errorString, 0));
        return false;
    }
}
