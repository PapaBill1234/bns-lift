// deflog.h: deflog.h (GameDaemon PDB, 2019 + PDB).
#pragma once
#include "GameDaemonFwd.h"

// PDB layout (size 0x8): base DrLog.
class DrDefLog : public DrLog
{
public:
    static DrDefLog* Instance();
    virtual void __cdecl Write(::DrLog::Type type, wchar_t const* file, int line, wchar_t const* format, ...);  // 0x6eb380
};

