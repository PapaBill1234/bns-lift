// parallelworker.h: parallelworker.cpp (GameDaemon PDB, 2019 + PDB).
#pragma once
#include "GameDaemonFwd.h"

// PDB layout (size 0x668).
class DrParallelWorkerManager
{
public:
    typedef void (__cdecl *WorkerInitFunc)(void);
    typedef unsigned int (__cdecl *WorkerFunc)(void *);
    enum { MAX_WORKER = 100 };  // LIFT: the PDB has an unnamed enum here. The value comes from _workerInfo[100].

    // PDB layout (size 0x10).
    typedef struct _WorkerInfo
    {
        void * threadHandle;
        unsigned int threadID;
    } WorkerInfo;

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

private:
    WorkerInitFunc _workerInitFunc;       // +0x0
    WorkerFunc _workerFunc;               // +0x8
    int _workerCnt;                       // +0x10
    WorkerInfo _workerInfo[MAX_WORKER];   // +0x18
    void * _iocpHandle;                   // +0x658
    bool _workerStarted;                  // +0x660
};
