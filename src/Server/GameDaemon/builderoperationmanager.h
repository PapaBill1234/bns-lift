// builderoperationmanager.h: builderoperationmanager.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class BuilderOperationManager
{
public:
    __cdecl BuilderOperationManager(void);  // 0x21eb90
    void __cdecl TestBotQuery(::Pc *, ::Pc *);  // 0x21ec30
    void __cdecl TestBotCheckAnswer(::Pc *, __int64, int, int);  // 0x21ee90
    void __cdecl TestBotExpire(void);  // 0x21f260
};

