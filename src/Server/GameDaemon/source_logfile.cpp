// source_logfile.cpp: logfile.cpp (GameDaemon PDB, 2019 + PDB).
#include "GameDaemonFwd.h"
#include "../BloodLib/include/LogFile.h"
#include "LiftStub.h"
#include <stdio.h>
#include <wchar.h>

#pragma comment(linker, "/INCLUDE:?Write@LogFile@@QEAAXPEB_WHPEB_WPEAD@Z")  // LIFT: dead-strip keep (no live caller yet)

// 0x69eed0 LogFile::LogFile: LIFT: no body in wave 0 (shared class LogFile has another form or the change needs codegen (W1, pattern 35)).

// 0x69f070 LogFile::initialize: LIFT: no body in wave 0 (shared class LogFile has another form or the change needs codegen (W1, pattern 35)).

// 0x6a0250
void __cdecl LogFile::Write(wchar_t const *file, int line, wchar_t const *format, char *args)
{
    SYSTEMTIME systm;
    GetLocalTime(&systm);

    wchar_t log[4000];
    vswprintf(log, 4000, format, args);

    writeToBuffer(Log::LT_MAX, systm, file, line, log);
    if (_bufcnt > _bufmax)
        writeFile();
}
