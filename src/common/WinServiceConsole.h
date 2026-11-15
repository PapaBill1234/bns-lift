// WinServiceConsole.obj (CacheGate PDB). Layout from include/pdb/CacheGate/types.h.
// Vtable 0x1400518B0 (no PDB label).
#pragma once
#include "Console.h"
#include <winsvc.h>

class Daemon;

class WinServiceConsole : public Console
{
public:
    // ❓ Inlined in makeConsole (0xa540). The PDB has no out-of-line copy.
    WinServiceConsole();
    virtual ~WinServiceConsole() {}          // slot 0 (0x17600, folded)
    virtual bool Writable();                 // slot 1
    virtual bool Open();                     // slot 6
    virtual void Close();                    // slot 7
    virtual void SetState(int state);        // slot 8
protected:
    virtual void WriteStartLog(int type, wchar_t const* format, ...);                    // slot 9
    virtual void WriteStatusLog(wchar_t const* format, ...);                             // slot 10
    virtual void Write(Log::Type type, wchar_t const* file, int line,
                       wchar_t const* format, char* args);                               // slot 11
public:
    virtual bool controlHandler(unsigned long ctrlCode);                                 // slot 12
private:
    virtual void write(LogBuffer const* logbuf);                                         // slot 5

public:
    static void ServiceMain(unsigned long argCount, wchar_t** argVector);
    // ❓ The code uses "daemon" as a name postfix string and "postfix" as the conf path.
    static bool InstallService(Daemon* daemon, wchar_t const* postfix, wchar_t const* confdir);
    static bool UninstallService(Daemon* daemon, wchar_t const* postfix);

protected:
    bool reportStatusToSCManager(unsigned long currentState, unsigned long exitCode, unsigned long waitHint);

private:
    static wchar_t const* getLastErrorText(wchar_t* errorString, int size);
    static void addLog(bool error, wchar_t const* message);

public:
    unsigned long ErrorCode;
    unsigned long CheckPoint;
    SERVICE_STATUS Status;
    SERVICE_STATUS_HANDLE Handle;
};
static_assert(sizeof(WinServiceConsole) == 0xE0, "sizeof WinServiceConsole");
static_assert(offsetof(WinServiceConsole, ErrorCode) == 0xB0, "WinServiceConsole::ErrorCode");
static_assert(offsetof(WinServiceConsole, CheckPoint) == 0xB4, "WinServiceConsole::CheckPoint");
static_assert(offsetof(WinServiceConsole, Status) == 0xB8, "WinServiceConsole::Status");
static_assert(offsetof(WinServiceConsole, Handle) == 0xD8, "WinServiceConsole::Handle");

// 0x14005a378
extern WinServiceConsole* _WinServiceConsole;

void WinServiceControlHandler(unsigned long ctrlCode);
