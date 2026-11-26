// WindowConsole.obj (CacheGate PDB).
#include "WindowConsole.h"
#include "Daemon.h"
#include "Log.h"
#include "AlertSender.h"
#include "LogBuffer.h"
#include "MemoryManager.h"
#include <new>
#include <stdarg.h>
#include <stdio.h>
#include <wchar.h>

static wchar_t const* const WINDOW_CONSOLE_FILE = L"source\\WindowConsole.cpp";

WindowConsole* WinMsgHandler::_console = nullptr;

// LIFT: Inlined in WindowConsole::Open (0x17090). The PDB has no out-of-line copy.
WinMsgHandler::WinMsgHandler(WindowConsole* console)
{
    _console = console;
    // 0x17090: the event pointer stays in a register. CreateEventW stores through it (no reload of _initEvent).
    void* memory = BASE_MEMORY_MANAGER.Alloc(sizeof(SystemEvent), WINDOW_CONSOLE_FILE, 44);
    SystemEvent* initEvent;
    if (memory != nullptr)
        initEvent = new (memory) SystemEvent();
    else
        initEvent = nullptr;
    _initEvent = initEvent;
    initEvent->Event = CreateEventW(nullptr, FALSE, FALSE, nullptr);
}

// 0x16d50
wchar_t const* WinMsgHandler::Name()
{
    return L"WinMsgHandler";
}

// 0x16d80 (0x16d60 is the vector deleting destructor)
WinMsgHandler::~WinMsgHandler()
{
    SystemEvent* initEvent = _initEvent;
    if (initEvent != nullptr)
    {
        // Inlined SystemEvent::~SystemEvent.
        if (initEvent->Event != nullptr)
        {
            CloseHandle(initEvent->Event);
            initEvent->Event = nullptr;
        }
        BASE_MEMORY_MANAGER.Free(_initEvent, WINDOW_CONSOLE_FILE, 51);
        _initEvent = nullptr;
    }
}

// 0x16e10
void WinMsgHandler::WaitInit()
{
    SystemEvent* initEvent = _initEvent;
    if (initEvent == nullptr)
        return;
    if (initEvent->Event != nullptr)
        WaitForSingleObject(initEvent->Event, INFINITE);
    initEvent = _initEvent;
    // Inlined SystemEvent::~SystemEvent.
    if (initEvent != nullptr && initEvent->Event != nullptr)
    {
        CloseHandle(initEvent->Event);
        initEvent->Event = nullptr;
    }
    BASE_MEMORY_MANAGER.Free(_initEvent, WINDOW_CONSOLE_FILE, 58);
    _initEvent = nullptr;
}

// 0x16e90
void WinMsgHandler::run()
{
    if (_initEvent->Event != nullptr)
        SetEvent(_initEvent->Event);
    WindowConsole* console = _console;
    LogBufferAllocator::Initialize();
    PacketBufferAllocator::Initialize();
    console->_consoleWindow.console->Run();
}

// 0x16ed0
bool WindowConsoleOnClose()
{
    if (Daemon::Instance != nullptr && Daemon::Instance->EndEvent.Event != nullptr)
        SetEvent(Daemon::Instance->EndEvent.Event);
    return false;
}

// 0x16f00
bool WindowConsoleOnReload()
{
    wchar_t* argv[1] = { (wchar_t*)L"reload-req" };
    if (Daemon::Instance != nullptr)
        return Daemon::Reload(argv, 1);
    // BUG: 0x16f00 without a daemon the result is the low byte of the string address (not zero).
    return true;
}

// 0x16f30
bool WindowConsoleOnSafeShutdown()
{
    if (Daemon::Instance != nullptr)
        return Daemon::Cooldown();
    // BUG: 0x16f30 without a daemon the result is not set (al is undefined).
    return false;
}

// 0x16f50 (CacheGate), 0x126f0 (LobbyGate). Both handlers are empty. ICF folded them with other empty functions.
static void WindowConsoleOnLogoff()
{
}

// 0x16f50 (CacheGate), 0x126f0 (LobbyGate). Same folded body as WindowConsoleOnLogoff.
static void WindowConsoleOnShutdown()
{
}

// 0x16f60
WindowConsole::WindowConsole()
{
    _messageHandler = nullptr;
    _consoleWindow.module = nullptr;
    _consoleWindow.console = nullptr;
    _consoleWindow.GetInterfaceVersion = nullptr;
    _consoleWindow.Create = nullptr;
    _consoleWindow.Destroy = nullptr;
    _reloadHandler.autoEnable = false;
    _reloadHandler.reload = nullptr;
    _shutdownHandler.autoEnable = false;
    _shutdownHandler.shutdown = nullptr;
    _endSessionHandler.logoff = nullptr;
    _endSessionHandler.shutdown = nullptr;
}

// 0x17000 (0x16fe0 is the vector deleting destructor)
WindowConsole::~WindowConsole()
{
    Close();
    if (_messageHandler != nullptr)
    {
        _messageHandler->~WinMsgHandler();
        BASE_MEMORY_MANAGER.Free(_messageHandler, WINDOW_CONSOLE_FILE, 120);
        _messageHandler = nullptr;
    }
}

// 0x17090
bool WindowConsole::Open()
{
    if (_messageHandler != nullptr)
    {
        Log::Write(Log::LT_ERROR, WINDOW_CONSOLE_FILE, 126, L"== CRASH == [console], already opened");
        AlertSender::Write(WINDOW_CONSOLE_FILE, 126, L"== CRASH == [console], already opened");
        return false;
    }

    _reloadHandler.autoEnable = true;
    _reloadHandler.reload = (void (*)())WindowConsoleOnReload;
    _shutdownHandler.autoEnable = true;
    _shutdownHandler.shutdown = (void (*)())WindowConsoleOnSafeShutdown;
    _endSessionHandler.logoff = WindowConsoleOnLogoff;
    _endSessionHandler.shutdown = WindowConsoleOnShutdown;

    _consoleWindow.module = nullptr;
    _consoleWindow.console = nullptr;
    _consoleWindow.GetInterfaceVersion = nullptr;
    _consoleWindow.Create = nullptr;
    _consoleWindow.Destroy = nullptr;
    _consoleWindow.module = LoadLibraryW((LPCWSTR)L"bsConsole_sv64.dll");
    if (_consoleWindow.module != nullptr)
    {
        _consoleWindow.GetInterfaceVersion =
            (wchar_t const* (*)())GetProcAddress(_consoleWindow.module, "GetInterfaceVersion");
        _consoleWindow.Create =
            (ConsoleWindow* (*)(HINSTANCE__*))GetProcAddress(_consoleWindow.module, "CreateConsoleWindow");
        _consoleWindow.Destroy =
            (void (*)(ConsoleWindow*))GetProcAddress(_consoleWindow.module, "DestroyConsoleWindow");
        _consoleWindow.console = _consoleWindow.Create(_consoleWindow.module);
    }
    if (_consoleWindow.module == nullptr)
        return false;
    if (_consoleWindow.console == nullptr)
        return false;

    // 0x17090 loads the vtable before the two Name calls and reloads `this` after them.
    // The arguments are evaluated from right to left: the first Name call gives the title.
    if (!_consoleWindow.console->Initialize(nullptr, Daemon::Instance->Name(), Daemon::Instance->Name(), nullptr,
                                            (void*)WindowConsoleOnClose, &_reloadHandler, &_shutdownHandler,
                                            nullptr, &_endSessionHandler))
        return false;

    void* memory = BASE_MEMORY_MANAGER.Alloc(sizeof(WinMsgHandler), WINDOW_CONSOLE_FILE, 157);
    WinMsgHandler* handler = (memory != nullptr) ? new (memory) WinMsgHandler(this) : nullptr;
    _messageHandler = handler;
    // LIFT: LTCG folded threadId. The call (0x17325) sets no r8. StartThread (0x12E40) writes r8
    // at 0x12E5F before it reads it.
    Daemon::Instance->threadManager->StartThread(handler, nullptr);
    _messageHandler->WaitInit();
    FreeConsole();
    return true;
}

// 0x17360
void WindowConsole::Close()
{
    if (Daemon::Instance != nullptr && Daemon::Instance->threadManager != nullptr)
        Daemon::Instance->threadManager->StopThread(_messageHandler->_id, 2000, true, true);
    if (_consoleWindow.console == nullptr)
        return;
    _consoleWindow.console->Clear();
    if (_consoleWindow.module == nullptr)
        return;
    _consoleWindow.Destroy(_consoleWindow.console);
    FreeLibrary(_consoleWindow.module);
    _consoleWindow.module = nullptr;
    _consoleWindow.console = nullptr;
    _consoleWindow.GetInterfaceVersion = nullptr;
    _consoleWindow.Create = nullptr;
    _consoleWindow.Destroy = nullptr;
}

// 0x17410
void WindowConsole::SetState(int state)
{
    _consoleWindow.console->SetStateString(Daemon::StateString[state]);
}

// 0x17430
void WindowConsole::write(LogBuffer const* logbuf)
{
    for (LogBuffer const* node = logbuf; node != nullptr;
         node = (_bufferNodePos >= 0) ? node->_next[_bufferNodePos] : nullptr)
    {
        if (node->_flush)
            continue;
        ConsoleLog* log = (ConsoleLog*)static_cast<ConsoleLog const*>(node);
        if (log->GetType() != ConsoleLog::L_NONE)
            _consoleWindow.console->WriteLog(log);
    }
}

// 0x174b0
void WindowConsole::Write(Log::Type type, wchar_t const* file, int line, wchar_t const* format, char* args)
{
    if (CONSOLE_LOG_TYPE[type] == ConsoleLog::L_NONE)
        return;
    LogBuffer* logbuf = LogBufferAllocator::_Local->allocate();
    GetLocalTime(&logbuf->_logtime);
    logbuf->_type = type;
    logbuf->_file = file;
    logbuf->_line = line;
    logbuf->_log[0] = 0;
    vswprintf(logbuf->_log, 1980, format, (va_list)args);
    write(logbuf);
}

// 0x13fd0 (folded with TextConsole::WriteStatusLog: empty function)
void WindowConsole::WriteStatusLog(wchar_t const* format, ...)
{
}

// 0xcd80 (folded: returns true)
bool WindowConsole::controlHandler(unsigned long ctrlCode)
{
    return true;
}

// 0x17570
void WindowConsole::WriteStartLog(int type, wchar_t const* format, ...)
{
    wchar_t log[1984];
    va_list args;
    va_start(args, format);
    vswprintf(log, 1980, format, args);
    va_end(args);
    if (_consoleWindow.console != nullptr)
        _consoleWindow.console->SetLogString(log, 10000);
}

// 0x175f0
void WindowConsole::setTitle(wchar_t const* title)
{
    _consoleWindow.console->SetTitle(title);
}
