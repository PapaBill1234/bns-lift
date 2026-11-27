// lock_gd.h: lock.h (GameDaemon PDB, 2019 + PDB).
#pragma once
#include "GameDaemonFwd.h"
#include <windows.h>

// PDB: AutoSRW (GameDaemon), size 0x10. The ctor is inline.
class AutoSRW
{
public:
    enum Mode
    {
        EXCLUSIVE = 0,
        SHARED = 1,
    };

    __cdecl ~AutoSRW(void);  // 0x1dc200

private:
    _RTL_SRWLOCK const* _lock;
    Mode const _mode;
};
static_assert(sizeof(AutoSRW) == 0x10, "sizeof AutoSRW");
