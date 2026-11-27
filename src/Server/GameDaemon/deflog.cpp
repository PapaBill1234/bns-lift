// deflog.cpp: deflog.h (GameDaemon PDB, 2019 + PDB).
#include "deflog.h"
#include <stdarg.h>
#include <stdio.h>
#include "LiftStub.h"

#pragma comment(linker, "/INCLUDE:?Write@DrDefLog@@UEAAXW4Type@DrLog@@PEB_WH1ZZ")  // LIFT: dead-strip keep (no live caller yet)

// 0x6eb380
void __cdecl DrDefLog::Write(::DrLog::Type type, wchar_t const* file, int line, wchar_t const* format, ...)
{
    // ❓ The PDB does not give the strings of the local static TypeStr. The names follow DrLog::Type.
    static const wchar_t* TypeStr[] = { L"Trace", L"Debug", L"Error" };

    wchar_t buffer[1025];
    va_list args;
    va_start(args, format);
    _vsnwprintf_s(buffer, 1025, 1024, format, args);
    va_end(args);

    wprintf(L"{%s} %s\r\n", TypeStr[type], buffer);
}
