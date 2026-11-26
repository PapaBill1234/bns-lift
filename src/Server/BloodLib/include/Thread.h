// Thread.obj (CacheGate PDB). Layouts from include/pdb/CacheGate/types.h.
#pragma once
#include <windows.h>
#include <stddef.h>
#include <time.h>

class ThreadManager;

class Thread
{
public:
    Thread() : _id(0), _lastExecuted(0), _maxFrozenSeconds(0), _threadManager(nullptr), _run(false) {}  // LIFT: inlined
    virtual ~Thread();                     // slot 0
    virtual void yield();                  // slot 1
    virtual wchar_t const* Name() = 0;     // slot 2
    virtual void run() = 0;                // slot 3
protected:
    virtual void stop();                   // slot 4
public:
    // TLS slot +0x28 in .tls. ThreadManager::entry sets it.
    static __declspec(thread) Thread* Current;

    unsigned long long _id;
    long long _lastExecuted;
    long long _maxFrozenSeconds;
    ThreadManager* _threadManager;
    bool _run;

    friend class ThreadManager;
};
static_assert(sizeof(Thread) == 0x30, "sizeof Thread");
static_assert(offsetof(Thread, _id) == 0x8, "Thread::_id");
static_assert(offsetof(Thread, _lastExecuted) == 0x10, "Thread::_lastExecuted");
static_assert(offsetof(Thread, _maxFrozenSeconds) == 0x18, "Thread::_maxFrozenSeconds");
static_assert(offsetof(Thread, _threadManager) == 0x20, "Thread::_threadManager");
static_assert(offsetof(Thread, _run) == 0x28, "Thread::_run");

class ThreadManager
{
public:
    ThreadManager() : _maxThreadCount(0), _runningThreadCount(0), _threads(nullptr), _threadHandles(nullptr), _now(_time64(nullptr)) {}  // LIFT: inlined in Daemon::Start (0xad50)
    ~ThreadManager();
    __declspec(noinline) bool Initialize(unsigned int maxThreadCount);  // LIFT: see Thread.cpp ThreadManagerInitializeCaller
    bool StartThread(Thread* thread, unsigned long long* threadId);
    bool StopThread(unsigned long long threadId, long waitTime, bool forceTerminate, bool remove);
    void StopAll(long waitTime, bool forceTerminate);

private:
    bool stopThread(int index, long waitTime, bool forceTerminate, bool remove);
    static unsigned int __stdcall entry(void* args);

public:
    unsigned int _maxThreadCount;
    unsigned int _runningThreadCount;
    Thread** _threads;
    void** _threadHandles;
    long long _now;
};
static_assert(sizeof(ThreadManager) == 0x20, "sizeof ThreadManager");
static_assert(offsetof(ThreadManager, _threads) == 0x8, "ThreadManager::_threads");
static_assert(offsetof(ThreadManager, _now) == 0x18, "ThreadManager::_now");
