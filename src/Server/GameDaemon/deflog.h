// deflog.h: deflog.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class DrDefLog
{
public:
    virtual void __cdecl Write(::DrLog::Type, wchar_t const *, int, wchar_t const *, ...);  // 0x6eb380
};

