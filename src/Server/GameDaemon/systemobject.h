// systemobject.h: systemobject.h (GameDaemon PDB, 2019 + PDB).
#pragma once
#include "GameDaemonFwd.h"

// PDB layout: size 0x328.
class SystemMultiEvent
{
public:
    __cdecl ~SystemMultiEvent(void);  // 0x1dc1a0

private:
    char Count;         // +0x00
    char SetCount;      // +0x01
    bool WaitAll;       // +0x02
    void* Event[100];   // +0x08
};

