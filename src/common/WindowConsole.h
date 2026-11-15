// WindowConsole.obj (CacheGate PDB). Layouts from include/pdb/CacheGate/types.h.
#pragma once
#include "Console.h"
#include "Thread.h"
#include "Lock.h"

class ConsoleLog;

// Interface of bsConsole_sv64.dll. Only the vtable is in the PDB.
class ConsoleWindow
{
public:
    struct ReloadHandler
    {
        bool autoEnable;
        void (*reload)();
    };
    struct ShutdownHandler
    {
        bool autoEnable;
        void (*shutdown)();
    };
    struct EndSessionHandler
    {
        void (*logoff)();
        void (*shutdown)();
    };

    virtual bool Initialize(HINSTANCE__* instance, wchar_t const* className, wchar_t const* title,
                            void* icon, void* onClose, void* reloadHandler, void* shutdownHandler,
                            void* connectHandler, void* endSessionHandler) = 0;  // slot 0 (❓ parameter names)
    virtual void Clear() = 0;                                                     // slot 1
    virtual int Run() = 0;                                                        // slot 2
    virtual HWND__* GetMainWindowHandle() = 0;                                    // slot 3
    virtual void SetTitle(wchar_t const* title) = 0;                              // slot 4
    virtual void SetConnectState(bool state) = 0;                                 // slot 5
    virtual void SetConnectEnable(bool enable) = 0;                               // slot 6
    virtual void SetReloadEnable(bool enable) = 0;                                // slot 7
    virtual void SetShutdownEnable(bool enable) = 0;                              // slot 8
    virtual void ConnectConnection() = 0;                                         // slot 9
    virtual void CloseConnection() = 0;                                           // slot 10
    virtual void SetStateString(wchar_t const* state) = 0;                        // slot 11
    virtual void SetActionString(wchar_t const* action, int time) = 0;            // slot 12
    virtual void SetLogString(wchar_t const* log, int time) = 0;                  // slot 13
    virtual void WriteLog(ConsoleLog* log) = 0;                                   // slot 14
    virtual void WriteStatus(int, int, int, int, int, int) = 0;                   // slot 15
};
static_assert(sizeof(ConsoleWindow) == 0x8, "sizeof ConsoleWindow");
static_assert(sizeof(ConsoleWindow::ReloadHandler) == 0x10, "sizeof ConsoleWindow::ReloadHandler");
static_assert(sizeof(ConsoleWindow::EndSessionHandler) == 0x10, "sizeof ConsoleWindow::EndSessionHandler");

struct ConsoleWindowInterface
{
    HINSTANCE__* module;
    ConsoleWindow* console;
    wchar_t const* (*GetInterfaceVersion)();
    ConsoleWindow* (*Create)(HINSTANCE__* module);
    void (*Destroy)(ConsoleWindow* console);
};
static_assert(sizeof(ConsoleWindowInterface) == 0x28, "sizeof ConsoleWindowInterface");

class WindowConsole;

class WinMsgHandler : public Thread
{
public:
    explicit WinMsgHandler(WindowConsole* console);  // ❓ inlined in 0x17090
    virtual ~WinMsgHandler();
    virtual wchar_t const* Name();
    void WaitInit();
protected:
    virtual void run();

private:
    SystemEvent* _initEvent;

    static WindowConsole* _console;
};
static_assert(sizeof(WinMsgHandler) == 0x38, "sizeof WinMsgHandler");

class WindowConsole : public Console
{
public:
    WindowConsole();
    virtual ~WindowConsole();
    virtual bool Open();
    virtual void Close();
    virtual void SetState(int state);
protected:
    virtual void WriteStartLog(int type, wchar_t const* format, ...);
    virtual void WriteStatusLog(wchar_t const* format, ...);
    virtual void Write(Log::Type type, wchar_t const* file, int line, wchar_t const* format, char* args);
    virtual bool controlHandler(unsigned long ctrlCode);
    virtual void setTitle(wchar_t const* title);
private:
    virtual void write(LogBuffer const* logbuf);

public:
    WinMsgHandler* _messageHandler;
    ConsoleWindowInterface _consoleWindow;
    ConsoleWindow::ReloadHandler _reloadHandler;
    ConsoleWindow::ShutdownHandler _shutdownHandler;
    ConsoleWindow::EndSessionHandler _endSessionHandler;

    friend class WinMsgHandler;
};
static_assert(sizeof(WindowConsole) == 0x110, "sizeof WindowConsole");
static_assert(offsetof(WindowConsole, _messageHandler) == 0xB0, "WindowConsole::_messageHandler");
static_assert(offsetof(WindowConsole, _consoleWindow) == 0xB8, "WindowConsole::_consoleWindow");
static_assert(offsetof(WindowConsole, _reloadHandler) == 0xE0, "WindowConsole::_reloadHandler");
static_assert(offsetof(WindowConsole, _shutdownHandler) == 0xF0, "WindowConsole::_shutdownHandler");
static_assert(offsetof(WindowConsole, _endSessionHandler) == 0x100, "WindowConsole::_endSessionHandler");

bool WindowConsoleOnClose();
bool WindowConsoleOnReload();
bool WindowConsoleOnSafeShutdown();
