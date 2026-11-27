// parallelworker.h: parallelworker.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class DrParallelWorkerManager
{
public:
    bool __cdecl Init(int);  // 0x6fea70
    bool __cdecl SetWorkerFunc(unsigned int (__cdecl *)(void *));  // 0x6fead0
    bool __cdecl SetWorkerInitFunc(void (__cdecl *)(void));  // 0x6feae0
    int __cdecl Execute(void *);  // 0x6feaf0
    bool __cdecl StopWorkerPool(void);  // 0x6feb20
private:
    static unsigned int __cdecl workerFrame(void *);  // 0x6febc0
public:
    __cdecl ~DrParallelWorkerManager(void);  // 0x6fec80
    bool __cdecl StartWorkerPool(void);  // 0x6fecb0
};

