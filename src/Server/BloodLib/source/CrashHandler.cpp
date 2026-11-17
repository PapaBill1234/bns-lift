// CrashHandler.obj (LobbyGate PDB, BloodLib/service).
#include "CrashHandler.h"
#include <stdio.h>
#include <string.h>
#include <wchar.h>
#include <time.h>
#include <stdlib.h>
#include <new>
#include <locale.h>
#include <stdarg.h>

// msvcr100 export. The Wine msvcrt headers do not declare it.
extern "C" int __cdecl _vswprintf_c_l(wchar_t* buffer, size_t count, wchar_t const* format, _locale_t locale, va_list args);
#include <dbghelp.h>
#include "AlertSender.h"
#include "Daemon.h"
#include "Lock.h"
#include "Log.h"
#include "Thread.h"

static wchar_t const CRASHHANDLER_FILE[] = L"source\\CrashHandler.cpp";

#define CRASHHANDLER_ASSERT_CRASH(line)                                                  \
    do                                                                                   \
    {                                                                                    \
        Log::Write(Log::LT_ERROR, CRASHHANDLER_FILE, line, L"== CRASH == ASSERT CRASH"); \
        AlertSender::Write(CRASHHANDLER_FILE, line, L"== CRASH == ASSERT CRASH");       \
        CrashHandler::MakeCrash("source\\CrashHandler.cpp", line, L"");                  \
    } while (0)

// The functions use one local buffer and one byte count (PDB locals __write_buffer, __write_bytes).
#define CRASH_WRITE(fileHandle, ...)                                                       \
    do                                                                                     \
    {                                                                                      \
        int __write_length = sprintf_s(__write_buffer, sizeof(__write_buffer), __VA_ARGS__); \
        if (__write_length != 0)                                                           \
            WriteFile(fileHandle, __write_buffer, __write_length, &__write_bytes, nullptr); \
    } while (0)

// PDB: struct SymbolFunctions (sizeof 0x60). The PDB types of the members are function pointers.
struct SymbolFunctions
{
    unsigned long options;
    HINSTANCE__* moduleHandle;
    BOOL(__stdcall* symInitialize)(HANDLE, PCSTR, BOOL);
    BOOL(__stdcall* symCleanup)(HANDLE);
    BOOL(__stdcall* stackWalk)(DWORD, HANDLE, HANDLE, LPSTACKFRAME64, PVOID, PREAD_PROCESS_MEMORY_ROUTINE64,
                               PFUNCTION_TABLE_ACCESS_ROUTINE64, PGET_MODULE_BASE_ROUTINE64,
                               PTRANSLATE_ADDRESS_ROUTINE64);
    PFUNCTION_TABLE_ACCESS_ROUTINE64 symFunctionTableAccess;
    PGET_MODULE_BASE_ROUTINE64 symGetModuleBase;
    BOOL(__stdcall* symGetSymFromAddr)(HANDLE, DWORD64, PDWORD64, PIMAGEHLP_SYMBOL64);
    BOOL(__stdcall* symGetLineFromAddr)(HANDLE, DWORD64, PDWORD, PIMAGEHLP_LINE64);
    DWORD(__stdcall* symGetOptions)();
    DWORD(__stdcall* symSetOptions)(DWORD);
    BOOL(__stdcall* symMiniDumpWriteDump)(HANDLE, DWORD, HANDLE, MINIDUMP_TYPE, PMINIDUMP_EXCEPTION_INFORMATION,
                                          PMINIDUMP_USER_STREAM_INFORMATION, PMINIDUMP_CALLBACK_INFORMATION);
};
static_assert(sizeof(SymbolFunctions) == 0x60, "sizeof SymbolFunctions");
static_assert(offsetof(SymbolFunctions, symMiniDumpWriteDump) == 0x58, "SymbolFunctions::symMiniDumpWriteDump");

// 0x60580 dynamic initializer, 0x606A0 atexit destructor.
static CriticalSection HandlerLock;
static wchar_t CrashLogPath[260];
static wchar_t CrashLogFilenamePrefix[260];

CrashHandler* CrashHandler::Instance = nullptr;

// 0x1C6D0
void DumpStack(void* fileHandle, SymbolFunctions* sym, _EXCEPTION_POINTERS* exceptionInfo)
{
    unsigned long __write_bytes;
    char __write_buffer[2048];
    CONTEXT* context = exceptionInfo->ContextRecord;

    STACKFRAME64 stackFrame;
    memset(&stackFrame, 0, sizeof(stackFrame));
    stackFrame.AddrPC.Offset = context->Rip;
    stackFrame.AddrPC.Mode = AddrModeFlat;
    stackFrame.AddrStack.Offset = context->Rsp;
    stackFrame.AddrStack.Mode = AddrModeFlat;
    stackFrame.AddrFrame.Offset = context->Rbp;
    stackFrame.AddrFrame.Mode = AddrModeFlat;

    CRASH_WRITE(fileHandle, "\r\n\r\nCall Stacks:\r\n");

    HANDLE process = GetCurrentProcess();
    while (sym->stackWalk(IMAGE_FILE_MACHINE_AMD64, process, GetCurrentThread(), &stackFrame, context, nullptr,
                          sym->symFunctionTableAccess, sym->symGetModuleBase, nullptr) != 0)
    {
        if (stackFrame.AddrFrame.Offset == 0 || sym->symGetModuleBase(process, stackFrame.AddrPC.Offset) == 0)
            break;

        CRASH_WRITE(fileHandle, "0x%016I64X", stackFrame.AddrPC.Offset);

        unsigned char buffer[sizeof(IMAGEHLP_SYMBOL64) + 512];
        IMAGEHLP_SYMBOL64* symbol = reinterpret_cast<IMAGEHLP_SYMBOL64*>(buffer);
        symbol->SizeOfStruct = sizeof(buffer);
        symbol->MaxNameLength = 512;
        unsigned long long displacement;
        if (sym->symGetSymFromAddr(process, stackFrame.AddrPC.Offset, &displacement, symbol) != 0)
        {
            if (displacement != 0)
                CRASH_WRITE(fileHandle, "  %s() + %I64d byte(s)", symbol->Name, displacement);
            else
                CRASH_WRITE(fileHandle, "  %s", symbol->Name);
        }

        CRASH_WRITE(fileHandle, "\r\n\t[0x%016I64X 0x%016I64X 0x%016I64X 0x%016I64X]", stackFrame.Params[0],
                    stackFrame.Params[1], stackFrame.Params[2], stackFrame.Params[3]);

        IMAGEHLP_LINE64 line;
        memset(&line, 0, sizeof(line));
        line.SizeOfStruct = sizeof(line);
        unsigned long lineDisplacement;  // PDB: displacement (second local of this name)
        if (sym->symGetLineFromAddr(process, stackFrame.AddrPC.Offset, &lineDisplacement, &line) != 0)
        {
            if (lineDisplacement != 0)
                CRASH_WRITE(fileHandle, "\r\n\t{%s, line %d + %d byte(s)}", line.FileName, line.LineNumber,
                            lineDisplacement);
            else
                CRASH_WRITE(fileHandle, "\r\n\t{%s, line %d}", line.FileName, line.LineNumber);
        }

        CRASH_WRITE(fileHandle, "\r\n\r\n");
    }
}

// 0x1C530
bool InitSymbol(SymbolFunctions* sym, wchar_t const* symbolPath)
{
    sym->moduleHandle = LoadLibraryW(L"dbghelp.dll");
    if (sym->moduleHandle == nullptr)
        return false;

    if ((*reinterpret_cast<FARPROC*>(&sym->symInitialize) = GetProcAddress(sym->moduleHandle, "SymInitialize")) == nullptr ||
        (*reinterpret_cast<FARPROC*>(&sym->symCleanup) = GetProcAddress(sym->moduleHandle, "SymCleanup")) == nullptr ||
        (*reinterpret_cast<FARPROC*>(&sym->stackWalk) = GetProcAddress(sym->moduleHandle, "StackWalk64")) == nullptr ||
        (*reinterpret_cast<FARPROC*>(&sym->symFunctionTableAccess) =
             GetProcAddress(sym->moduleHandle, "SymFunctionTableAccess64")) == nullptr ||
        (*reinterpret_cast<FARPROC*>(&sym->symGetModuleBase) = GetProcAddress(sym->moduleHandle, "SymGetModuleBase64")) ==
            nullptr ||
        (*reinterpret_cast<FARPROC*>(&sym->symGetSymFromAddr) = GetProcAddress(sym->moduleHandle, "SymGetSymFromAddr64")) ==
            nullptr ||
        (*reinterpret_cast<FARPROC*>(&sym->symGetLineFromAddr) =
             GetProcAddress(sym->moduleHandle, "SymGetLineFromAddr64")) == nullptr ||
        (*reinterpret_cast<FARPROC*>(&sym->symGetOptions) = GetProcAddress(sym->moduleHandle, "SymGetOptions")) == nullptr ||
        (*reinterpret_cast<FARPROC*>(&sym->symSetOptions) = GetProcAddress(sym->moduleHandle, "SymSetOptions")) == nullptr ||
        (*reinterpret_cast<FARPROC*>(&sym->symMiniDumpWriteDump) = GetProcAddress(sym->moduleHandle, "MiniDumpWriteDump")) ==
            nullptr)
    {
        FreeLibrary(sym->moduleHandle);
        sym->moduleHandle = nullptr;
        return false;
    }

    sym->options = sym->symGetOptions() | SYMOPT_DEFERRED_LOADS | SYMOPT_LOAD_LINES;
    sym->symSetOptions(sym->options);
    SetCurrentDirectoryW(symbolPath);
    return sym->symInitialize(GetCurrentProcess(), nullptr, TRUE) != 0;
}

// 0x1C380
void DumpRegister(void* fileHandle, _EXCEPTION_POINTERS* exceptionInfo)
{
    unsigned long __write_bytes;
    char __write_buffer[2048];

    CRASH_WRITE(fileHandle, "\r\n\r\nRegisters:\r\n");
    CONTEXT* context = exceptionInfo->ContextRecord;
    CRASH_WRITE(fileHandle,
                "RAX=%016I64X  RBX=%016I64X  RCX=%016I64X  RDX=%016I64X\r\n"
                "RSI=%016I64X  RDI=%016I64X  RBP=%016I64X  RSP=%016I64X\r\n"
                "RIP=%016I64X  FLG=%016X   R8=%016I64X   R9=%016I64X\r\n"
                "R10=%016I64X  R11=%016I64X  R12=%016I64X  R13=%016I64X\r\n"
                "R14=%016I64X  R15=%016I64X\r\n",
                context->Rax, context->Rbx, context->Rcx, context->Rdx, context->Rsi, context->Rdi, context->Rbp,
                context->Rsp, context->Rip, context->EFlags, context->R8, context->R9, context->R10, context->R11,
                context->R12, context->R13, context->R14, context->R15);
}

// 0x1C110
static char const* ExceptionCodeString(unsigned long code)
{
    switch (code)
    {
    case EXCEPTION_GUARD_PAGE: return "GUARD_PAGE";
    case EXCEPTION_DATATYPE_MISALIGNMENT: return "DATATYPE_MISALIGNMENT";
    case EXCEPTION_BREAKPOINT: return "BREAKPOINT";
    case EXCEPTION_SINGLE_STEP: return "SINGLE_STEP";
    case EXCEPTION_ACCESS_VIOLATION: return "ACCESS_VIOLATION";
    case EXCEPTION_IN_PAGE_ERROR: return "IN_PAGE_ERROR";
    case EXCEPTION_INVALID_HANDLE: return "INVALID_HANDLE";
    case EXCEPTION_ILLEGAL_INSTRUCTION: return "ILLEGAL_INSTRUCTION";
    case EXCEPTION_NONCONTINUABLE_EXCEPTION: return "NONCONTINUABLE_EXCEPTION";
    case EXCEPTION_INVALID_DISPOSITION: return "INVALID_DISPOSITION";
    case EXCEPTION_ARRAY_BOUNDS_EXCEEDED: return "ARRAY_BOUNDS_EXCEEDED";
    case EXCEPTION_FLT_DENORMAL_OPERAND: return "FLT_DENORMAL_OPERAND";
    case EXCEPTION_FLT_DIVIDE_BY_ZERO: return "FLT_DIVIDE_BY_ZERO";
    case EXCEPTION_FLT_INEXACT_RESULT: return "FLT_INEXACT_RESULT";
    case EXCEPTION_FLT_INVALID_OPERATION: return "FLT_INVALID_OPERATION";
    case EXCEPTION_FLT_OVERFLOW: return "FLT_OVERFLOW";
    case EXCEPTION_FLT_STACK_CHECK: return "FLT_STACK_CHECK";
    case EXCEPTION_FLT_UNDERFLOW: return "FLT_UNDERFLOW";
    case EXCEPTION_INT_DIVIDE_BY_ZERO: return "INT_DIVIDE_BY_ZERO";
    case EXCEPTION_INT_OVERFLOW: return "INT_OVERFLOW";
    case EXCEPTION_PRIV_INSTRUCTION: return "PRIV_INSTRUCTION";
    case EXCEPTION_STACK_OVERFLOW: return "STACK_OVERFLOW";
    case static_cast<unsigned long>(CrashHandler::USER_ASSERT_FAILED): return "USER_ASSERT_FAILED";
    default: return "?";
    }
}

// 0x1CD20
void CrashHandler::SetLogPath(wchar_t const* path)
{
    wchar_t logDirectory[260];
    wchar_t daemonName[260];

    wcsncpy(logDirectory, path, 260);
    size_t length = wcslen(logDirectory);
    if (logDirectory[length - 1] != L'\\')
        wcsncat(logDirectory, L"\\", 260 - length);
    wcsncat(logDirectory, L"fatal\\", 260 - wcslen(logDirectory));
    wcsncpy(CrashLogPath, logDirectory, 260);

    long long start = Daemon::Instance->StartTime;
    tm startTime;
    _localtime64_s(&startTime, &start);
    swprintf(daemonName, 260, L"%s(", Daemon::Instance->ShortName());  // LIFT: inline CRT swprintf 0x21CE0
    length = wcslen(daemonName);
    wcsftime(&daemonName[length], 260 - length, L"%Y%m%d-%H%M%S", &startTime);
    length = wcslen(daemonName);
    swprintf(&daemonName[length], 260 - length, L",%d),", GetCurrentProcessId());
    swprintf(CrashLogFilenamePrefix, 260, L"%s%s", logDirectory, daemonName);
}

// 0x1BF90
static void makeDirectory(wchar_t* directory)
{
    wchar_t drive[3];
    wchar_t dir[260];
    wchar_t fileName[260];
    wchar_t ext[260];
    wchar_t parentPath[260];

    _wsplitpath_s(directory, drive, 3, dir, 260, fileName, 260, ext, 260);
    if (wcslen(drive) == 0)
    {
        // BUG: 0x1BF90 the path appends CrashLogPath, not directory. The call is only for CrashLogPath.
        GetCurrentDirectoryW(260, parentPath);
        wcsncat(parentPath, L"\\", 260 - wcslen(parentPath));
        wcsncat(parentPath, CrashLogPath, 260 - wcslen(parentPath));
        makeDirectory(parentPath);
    }
    else
    {
        int length = static_cast<int>(wcslen(dir));
        if (length > 1)
        {
            dir[length - 1] = 0;
            swprintf(parentPath, 260, L"%s%s", drive, dir);
            makeDirectory(parentPath);
            CreateDirectoryW(parentPath, nullptr);
        }
    }
}

// 0x1CEE0
void CrashHandler::MakeCrash(char const* file, int line, wchar_t const* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    AssertInfo* info = static_cast<AssertInfo*>(HeapAlloc(GetProcessHeap(), 0, sizeof(AssertInfo)));
    // BUG: 0x1CEE0 no check of the HeapAlloc result.
    info->file = file;
    info->line = line;
    _vswprintf_c_l(info->log, 4096, fmt, nullptr, args);  // LobbyGate 0x1CF3C (import _vswprintf_c_l)
    ULONG_PTR parameter = reinterpret_cast<ULONG_PTR>(info);
    RaiseException(USER_ASSERT_FAILED, EXCEPTION_NONCONTINUABLE, 1, &parameter);
    if (Daemon::Instance->EndEvent.Event != nullptr)
        SetEvent(Daemon::Instance->EndEvent.Event);
    Sleep(1000);
}

// 0x1CC80
void CrashHandler::SetMailInfo(wchar_t const* to, wchar_t const* from, wchar_t const* mailServer)
{
    CrashHandler* handler = Instance;
    if (handler == nullptr || handler->_crashMail._isSetMail || to == nullptr || from == nullptr ||
        mailServer == nullptr)
        return;
    wcsncpy(handler->_crashMail._crashMailTo, to, 260);
    wcsncpy(handler->_crashMail._crashMailFrom, from, 260);
    wcsncpy(handler->_crashMail._crashMailServer, mailServer, 260);
    handler->_crashMail._isSetMail = true;
}

// 0x1CA70
CrashHandler::CrashHandler()
{
    _crashMail._isSetMail = false;
    memset(_crashMail._crashMailServer, 0, sizeof(_crashMail._crashMailServer));
    memset(_crashMail._crashMailTo, 0, sizeof(_crashMail._crashMailTo));
    memset(_crashMail._crashMailFrom, 0, sizeof(_crashMail._crashMailFrom));
    if (Instance != nullptr)
        CRASHHANDLER_ASSERT_CRASH(539);
    Instance = this;
    _orignalHandler = nullptr;
}

// 0x1CF90
// LTCG: the code uses Instance for the members and gets exceptionInfo in rcx.
long CrashHandler::handleCrash(_EXCEPTION_POINTERS* exceptionInfo)
{
    unsigned long __write_bytes;
    char __write_buffer[2048];

    HandlerLock.Enter();
    if (_orignalHandler != nullptr)
    {
        SetUnhandledExceptionFilter(_orignalHandler);
        _orignalHandler = nullptr;
    }

    Log::Write(Log::LT_DEBUG, CRASHHANDLER_FILE, 490,
               L"[crash-mail], PrintMailInfo, setFlag:%d to:%s from:%s mail-server:%s", _crashMail._isSetMail,
               _crashMail._crashMailTo, _crashMail._crashMailFrom, _crashMail._crashMailServer);
    Log::Flush();
    if (Daemon::Instance != nullptr)
        Daemon::Instance->FlushExtraLog();

    EXCEPTION_RECORD* record = exceptionInfo->ExceptionRecord;
    if (record->ExceptionCode == EXCEPTION_STACK_OVERFLOW)
    {
        OutputDebugStringW(L"***************************************\n");
        OutputDebugStringW(L"** EXCEPTION_STACK_OVERFLOW occurred **\n");
        OutputDebugStringW(L"***************************************\n");
    }

    long long now = _time64(nullptr);
    MINIDUMP_EXCEPTION_INFORMATION mdei;
    mdei.ThreadId = GetCurrentThreadId();
    mdei.ExceptionPointers = exceptionInfo;
    mdei.ClientPointers = FALSE;
    tm currentTime;
    _localtime64_s(&currentTime, &now);

    wchar_t logFilename[260];
    wchar_t dmpFilenameTiny[260];
    wchar_t dmpFilename[260];
    if (Thread::Current != nullptr)
        swprintf_s(logFilename, 260, L"%s%s(%d)", CrashLogFilenamePrefix, Thread::Current->Name(),
                   GetCurrentThreadId());
    else
        swprintf_s(logFilename, 260, L"%sMain(%d)", CrashLogFilenamePrefix, GetCurrentThreadId());
    size_t length = wcslen(logFilename);
    wcsftime(&logFilename[length], 260 - length, L",%Y%m%d-%H%M%S", &currentTime);
    length = wcslen(logFilename);
    wcsncpy(dmpFilenameTiny, logFilename, length);
    dmpFilenameTiny[length] = 0;
    wcsncpy(dmpFilename, logFilename, length);
    dmpFilename[length] = 0;
    wcsncat(logFilename, L".log", 260 - length);
    wcsncat(dmpFilenameTiny, L",tiny.dmp", 260 - length);
    wcsncat(dmpFilename, L".dmp", 260 - length);

    char currentTimeString[64];
    strftime(currentTimeString, sizeof(currentTimeString), "%Y/%m/%d %H:%M:%S", &currentTime);

    SymbolFunctions symFunctions;
    memset(&symFunctions, 0, sizeof(symFunctions));
    makeDirectory(CrashLogPath);

    if ((symFunctions.moduleHandle != nullptr || InitSymbol(&symFunctions, _symbolPath)) && (_option & 4) != 0)
    {
        if ((_dumpType & MiniDumpWithDataSegs) != 0)
        {
            HANDLE file = CreateFileW(dmpFilenameTiny, GENERIC_READ | GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS,
                                      FILE_ATTRIBUTE_NORMAL, nullptr);
            if (file != INVALID_HANDLE_VALUE)
            {
                symFunctions.symMiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), file,
                                                  MiniDumpWithDataSegs, &mdei, nullptr, nullptr);
                CloseHandle(file);
            }
        }
        HANDLE file = CreateFileW(dmpFilename, GENERIC_READ | GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS,
                                  FILE_ATTRIBUTE_NORMAL, nullptr);
        if (file != INVALID_HANDLE_VALUE)
        {
            symFunctions.symMiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), file,
                                              static_cast<MINIDUMP_TYPE>(_dumpType), &mdei, nullptr, nullptr);
            CloseHandle(file);
        }
    }

    HANDLE logFile = CreateFileW(logFilename, GENERIC_WRITE, 0, nullptr, OPEN_ALWAYS, FILE_FLAG_WRITE_THROUGH, nullptr);
    if (logFile != INVALID_HANDLE_VALUE)
    {
        CRASH_WRITE(logFile, "Time: %s\r\n", currentTimeString);
        CRASH_WRITE(logFile, "Code: %s [%08X]\r\n", ExceptionCodeString(record->ExceptionCode),
                    record->ExceptionCode);

        // BUG: 0x1CF90 moduleInfo stays not initialized if VirtualQuery, GetModuleFileNameW or the section search fails.
        ModuleInfo moduleInfo;
        void* address = record->ExceptionAddress;
        MEMORY_BASIC_INFORMATION memoryInfo;
        if (VirtualQuery(address, &memoryInfo, sizeof(memoryInfo)) != 0)
        {
            unsigned char* moduleBase = static_cast<unsigned char*>(memoryInfo.AllocationBase);
            wchar_t moduleName[260];
            if (GetModuleFileNameW(reinterpret_cast<HMODULE>(moduleBase), moduleName, 260) != 0)
            {
                moduleInfo.name[259] = 0;
                WideCharToMultiByte(CP_ACP, 0, moduleName, -1, moduleInfo.name, 259, nullptr, nullptr);
                IMAGE_NT_HEADERS* ntHeaders = reinterpret_cast<IMAGE_NT_HEADERS*>(
                    moduleBase + reinterpret_cast<IMAGE_DOS_HEADER*>(moduleBase)->e_lfanew);
                IMAGE_SECTION_HEADER* section = IMAGE_FIRST_SECTION(ntHeaders);
                unsigned long long rva = static_cast<unsigned char*>(address) - moduleBase;
                for (unsigned int i = 0; i < ntHeaders->FileHeader.NumberOfSections; ++i, ++section)
                {
                    unsigned long sectionStart = section->VirtualAddress;
                    unsigned long sectionSize = section->Misc.VirtualSize;
                    if (section->SizeOfRawData > sectionSize)
                        sectionSize = section->SizeOfRawData;
                    if (rva >= sectionStart && rva <= sectionStart + sectionSize)
                    {
                        moduleInfo.section = i + 1;
                        moduleInfo.offset = rva - sectionStart;
                        break;
                    }
                }
            }
        }
        CRASH_WRITE(logFile, "Address: %016p %s [%04X:%016I64X]\r\n", record->ExceptionAddress, moduleInfo.name,
                    moduleInfo.section, moduleInfo.offset);

        if (record->ExceptionCode == USER_ASSERT_FAILED && record->NumberParameters != 0)
        {
            AssertInfo* info = reinterpret_cast<AssertInfo*>(record->ExceptionInformation[0]);
            CRASH_WRITE(logFile, "Assert Failed: %s, %d\r\n", info->file, info->line);
            CRASH_WRITE(logFile, "Assert Description: %S\r\n", info->log);
        }
        else
        {
            unsigned char buffer[sizeof(IMAGEHLP_SYMBOL64) + 512];
            IMAGEHLP_SYMBOL64* symbol = reinterpret_cast<IMAGEHLP_SYMBOL64*>(buffer);
            symbol->SizeOfStruct = sizeof(buffer);
            symbol->MaxNameLength = 512;
            IMAGEHLP_LINE64 line;
            memset(&line, 0, sizeof(line));
            line.SizeOfStruct = sizeof(line);

            CRASH_WRITE(logFile, "Crashed at ");
            if (symFunctions.moduleHandle != nullptr || InitSymbol(&symFunctions, _symbolPath))
            {
                unsigned long long symDisp;
                if (symFunctions.symGetSymFromAddr(GetCurrentProcess(),
                                                   reinterpret_cast<unsigned long long>(record->ExceptionAddress),
                                                   &symDisp, symbol) != 0)
                {
                    if (symDisp != 0)
                        CRASH_WRITE(logFile, "%s() + %I64d byte(s)", symbol->Name, symDisp);
                    else
                        CRASH_WRITE(logFile, "%s", symbol->Name);
                }
            }
            if (symFunctions.moduleHandle != nullptr || InitSymbol(&symFunctions, _symbolPath))
            {
                unsigned long lineDisp;
                if (symFunctions.symGetLineFromAddr(GetCurrentProcess(),
                                                    reinterpret_cast<unsigned long long>(record->ExceptionAddress),
                                                    &lineDisp, &line) != 0)
                {
                    if (lineDisp != 0)
                        CRASH_WRITE(logFile, " {%s, line %d + %d byte(s)}", line.FileName, line.LineNumber, lineDisp);
                    else
                        CRASH_WRITE(logFile, " {%s, line %d}", line.FileName, line.LineNumber);
                }
            }
            CRASH_WRITE(logFile, "\r\n");
            if (record->ExceptionCode == EXCEPTION_ACCESS_VIOLATION && record->NumberParameters >= 2)
                CRASH_WRITE(logFile, "Access Violataion: %s 0x%Ix\r\n",
                            record->ExceptionInformation[0] != 0 ? "Write to" : "Read from",
                            record->ExceptionInformation[1]);
        }

        if ((_option & 1) != 0)
            DumpRegister(logFile, exceptionInfo);
        if ((symFunctions.moduleHandle != nullptr || InitSymbol(&symFunctions, _symbolPath)) && (_option & 2) != 0)
            DumpStack(logFile, &symFunctions, exceptionInfo);
        CloseHandle(logFile);
    }

    HINSTANCE__* moduleHandle = symFunctions.moduleHandle;
    if (moduleHandle != nullptr)
    {
        symFunctions.symCleanup(GetCurrentProcess());
        FreeLibrary(moduleHandle);
    }
    HandlerLock.Leave();
    return EXCEPTION_CONTINUE_SEARCH;
}

// 0x1BF80
long __stdcall CrashHandler::Handle(_EXCEPTION_POINTERS* exceptionInfo)
{
    return Instance->handleCrash(exceptionInfo);
}

// 0x1CBA0
bool CrashHandler::Initialize(int option, bool catchUnhandledException)
{
    (void)option;
    (void)catchUnhandledException;
    void* memory = HeapAlloc(GetProcessHeap(), 0, sizeof(CrashHandler));
    if (memory != nullptr)
        new (memory) CrashHandler();
    // LIFT: LTCG put constants here. 0x1CBF8 writes 3 and 0x1CC0C writes 1. The function never reads ecx or dl.
    // The only call is at 0x1DC63.
    Instance->_option = 3;
    Instance->_dumpType = MiniDumpWithDataSegs | MiniDumpWithHandleData;
    Instance->_catchUnhandledException = true;
    Instance->_orignalHandler = SetUnhandledExceptionFilter(Handle);
    wchar_t currentDirectory[260];
    GetCurrentDirectoryW(260, currentDirectory);
    wcsncpy(Instance->_symbolPath, currentDirectory, 260);
    SetLogPath(L".\\log\\");
    return true;
}
