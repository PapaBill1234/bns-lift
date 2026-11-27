// parallelworker.cpp: parallelworker.cpp (GameDaemon PDB, 2019 + PDB).
#include "parallelworker.h"
#include <process.h>
#include "LiftStub.h"

#pragma comment(linker, "/INCLUDE:?Init@DrParallelWorkerManager@@QEAA_NH@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?SetWorkerFunc@DrParallelWorkerManager@@QEAA_NP6AIPEAX@Z@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?SetWorkerInitFunc@DrParallelWorkerManager@@QEAA_NP6AXXZ@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?Execute@DrParallelWorkerManager@@QEAAHPEAX@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?StartWorkerPool@DrParallelWorkerManager@@QEAA_NXZ")  // LIFT: dead-strip keep (no live caller yet)

// 0x6fea70
bool __cdecl DrParallelWorkerManager::Init(int workerCnt)
{
    _workerCnt = workerCnt;
    if (workerCnt <= 0)
    {
        SYSTEM_INFO sysInfo;
        ::GetSystemInfo(&sysInfo);
        _workerCnt = sysInfo.dwNumberOfProcessors * 2 + 1;
    }
    _workerCnt = (_workerCnt > MAX_WORKER) ? MAX_WORKER : _workerCnt;

    _iocpHandle = ::CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
    // BUG: the original returns true when CreateIoCompletionPort fails and false when it succeeds. Kept as is.
    return _iocpHandle == NULL;
}

// 0x6fead0
bool __cdecl DrParallelWorkerManager::SetWorkerFunc(unsigned int (__cdecl *func)(void *))
{
    _workerFunc = func;
    return true;
}

// 0x6feae0
bool __cdecl DrParallelWorkerManager::SetWorkerInitFunc(void (__cdecl *func)(void))
{
    _workerInitFunc = func;
    return true;
}

// 0x6feaf0
int __cdecl DrParallelWorkerManager::Execute(void * args)
{
    // 0 on success, -1 on failure.
    return ::PostQueuedCompletionStatus(_iocpHandle, 0, (ULONG_PTR)args, NULL) ? 0 : -1;
}

// 0x6feb20
bool __cdecl DrParallelWorkerManager::StopWorkerPool(void)
{
    LIFT_STUB(0x6feb20);
}

// 0x6febc0
unsigned int __cdecl DrParallelWorkerManager::workerFrame(void *)
{
    LIFT_STUB(0x6febc0);
}

// 0x6fec80
__cdecl DrParallelWorkerManager::~DrParallelWorkerManager(void)
{
    LIFT_STUB(0x6fec80);
}

// 0x6fecb0
bool __cdecl DrParallelWorkerManager::StartWorkerPool(void)
{
    for (int i = 0; i < _workerCnt; ++i)
    {
        _workerInfo[i].threadHandle = (void *)_beginthreadex(NULL, 0, workerFrame, this, 0, &_workerInfo[i].threadID);
    }
    return true;
}
