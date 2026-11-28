// source_logfile.cpp: logfile.cpp (GameDaemon PDB, 2019 + PDB).
#include "GameDaemonFwd.h"
#include "../BloodLib/include/LogFile.h"
#include "LiftStub.h"
#include <stdio.h>
#include <wchar.h>

// 0x69eed0 LogFile::LogFile: LIFT: no body in wave 0 (shared class LogFile has another form or the change needs codegen (W1, pattern 35)).

// 0x69f070 LogFile::initialize: LIFT: no body in wave 0 (shared class LogFile has another form or the change needs codegen (W1, pattern 35)).

// 0x6a0250
// LIFT: log path (E16): LogFile is a log-path class.
void __cdecl LogFile::Write(wchar_t const *, int, wchar_t const *, char *)
{
    LIFT_STUB(0x6a0250);
}
