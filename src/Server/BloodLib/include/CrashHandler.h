// CrashHandler.obj (LobbyGate PDB, BloodLib/service). Layout from include/pdb/LobbyGate/types.h.
#pragma once
#include <windows.h>
#include <stddef.h>

// PDB: struct AssertInfo (sizeof 0x2010). MakeCrash gives it as the exception parameter.
struct AssertInfo
{
    char const* file;
    int line;
    wchar_t log[4096];
};
static_assert(sizeof(AssertInfo) == 0x2010, "sizeof AssertInfo");
static_assert(offsetof(AssertInfo, line) == 0x8, "AssertInfo::line");
static_assert(offsetof(AssertInfo, log) == 0xC, "AssertInfo::log");

// PDB: struct ModuleInfo (sizeof 0x110). Local of CrashHandler::handleCrash.
struct ModuleInfo
{
    char name[260];
    unsigned long section;
    unsigned long long offset;
};
static_assert(sizeof(ModuleInfo) == 0x110, "sizeof ModuleInfo");
static_assert(offsetof(ModuleInfo, section) == 0x104, "ModuleInfo::section");
static_assert(offsetof(ModuleInfo, offset) == 0x108, "ModuleInfo::offset");

class CrashHandler
{
public:
    enum
    {
        USER_ASSERT_FAILED = 0xC000FFFF  // LIFT: No PDB name. The name comes from the ExceptionCodeString text.
    };

    // PDB: struct CrashHandler::CrashMail.
    struct CrashMail
    {
        bool _isSetMail;
        wchar_t _crashMailTo[260];
        wchar_t _crashMailFrom[260];
        wchar_t _crashMailServer[260];
    };

    // 0x1CBA0
    // The PDB has (int option, bool catchUnhandledException). LTCG removed the arguments.
    static bool Initialize(int option, bool catchUnhandledException);
    // 0x1CC80
    static void SetMailInfo(wchar_t const* to, wchar_t const* from, wchar_t const* mailServer);
    // 0x1CEE0
    static void MakeCrash(char const* file, int line, wchar_t const* fmt, ...);
    // 0x1CD20
    static void SetLogPath(wchar_t const* path);
    // 0x1BF80
    static long __stdcall Handle(_EXCEPTION_POINTERS* exceptionInfo);

    static CrashHandler* Instance;

protected:
    CrashHandler();                 // 0x1CA70
    virtual ~CrashHandler() {}      // LIFT: body inlined in the scalar deleting destructor

private:
    long handleCrash(_EXCEPTION_POINTERS* exceptionInfo);  // 0x1CF90

public:
    LPTOP_LEVEL_EXCEPTION_FILTER _orignalHandler;  // 0x8
    wchar_t _symbolPath[260];                      // 0x10
    int _option;                                   // 0x218
    int _dumpType;                                 // 0x21C
    bool _catchUnhandledException;                 // 0x220
    CrashMail _crashMail;                          // 0x222
};
static_assert(sizeof(CrashHandler) == 0x840, "sizeof CrashHandler");
static_assert(offsetof(CrashHandler, _orignalHandler) == 0x8, "CrashHandler::_orignalHandler");
static_assert(offsetof(CrashHandler, _symbolPath) == 0x10, "CrashHandler::_symbolPath");
static_assert(offsetof(CrashHandler, _option) == 0x218, "CrashHandler::_option");
static_assert(offsetof(CrashHandler, _dumpType) == 0x21C, "CrashHandler::_dumpType");
static_assert(offsetof(CrashHandler, _catchUnhandledException) == 0x220, "CrashHandler::_catchUnhandledException");
static_assert(offsetof(CrashHandler, _crashMail) == 0x222, "CrashHandler::_crashMail");
