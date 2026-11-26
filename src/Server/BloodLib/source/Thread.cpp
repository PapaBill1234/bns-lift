// Thread.obj (CacheGate PDB).
#include "Thread.h"
#include "MemoryManager.h"
#include <process.h>

__declspec(thread) Thread* Thread::Current = nullptr;

// 0x9260
Thread::~Thread()
{
}

// 0x9270
void Thread::yield()
{
    SwitchToThread();
}

// 0x9280
void Thread::stop()
{
    _run = false;
}

// 0x12d50
ThreadManager::~ThreadManager()
{
    StopAll(2000, false);
    if (_threads != nullptr)
    {
        BASE_MEMORY_MANAGER.Free(_threads, L"source\\Thread.cpp", 44);
        _threads = nullptr;
    }
    if (_threadHandles != nullptr)
    {
        BASE_MEMORY_MANAGER.Free(_threadHandles, L"source\\Thread.cpp", 49);
        _threadHandles = nullptr;
    }
}

// 0x12dd0
bool ThreadManager::Initialize(unsigned int maxThreadCount)
{
    if (_maxThreadCount != 0)
        return false;
    _maxThreadCount = maxThreadCount;
    _threads = static_cast<Thread**>(
        BASE_MEMORY_MANAGER.AllocZero(sizeof(Thread*) * maxThreadCount, L"source\\Thread.cpp", 59));
    _threadHandles = static_cast<void**>(
        BASE_MEMORY_MANAGER.AllocZero(sizeof(void*) * _maxThreadCount, L"source\\Thread.cpp", 60));
    return true;
}

// LIFT: The original PDB marks ThreadManager::Initialize as "inlined" (S_FRAMEPROC fWasInlined), but the exe has no
// inlined copy (only 0x12d50 and 0x12dd0 use the Thread.cpp string). So a second caller existed at compile time and the
// linker removed it (/OPT:REF). Its source is not known. With Daemon::Start as the only caller, LTCG puts the constant 128
// into Initialize. This caller and its COMDAT reference (removed by the linker after code generation) keep the
// parameter, as in 0x12dd0 (mov [rcx], edx; shl rdx, 3) and 0xad50 (mov edx, 0x80; call). noinline keeps the call in
// 0xad50. The exe gets no code from this.
void ThreadManagerInitializeCaller(ThreadManager* manager, unsigned int maxThreadCount)
{
    manager->Initialize(maxThreadCount);
}
extern void (*const ThreadManagerInitializeCallerRef)(ThreadManager*, unsigned int);
__declspec(selectany) extern void (*const ThreadManagerInitializeCallerRef)(ThreadManager*, unsigned int) =
    &ThreadManagerInitializeCaller;

// 0x12e40
// BUG: 0x12e40 threadId is never written.
bool ThreadManager::StartThread(Thread* thread, unsigned long long* threadId)
{
    if (thread == nullptr)
        return false;
    if (_threads == nullptr)
        return false;
    if (_runningThreadCount >= _maxThreadCount)
        return false;

    unsigned int i = 0;
    for (; i < _maxThreadCount; ++i)
    {
        if (_threads[i] == nullptr)
            break;
    }
    if (i >= _maxThreadCount)
        return false;

    _threads[i] = thread;
    _threads[i]->_threadManager = this;
    unsigned int threadAddr;
    _threadHandles[i] = reinterpret_cast<void*>(_beginthreadex(nullptr, 0, &ThreadManager::entry, thread, 0, &threadAddr));
    if (_threadHandles[i] != nullptr)
    {
        InterlockedIncrement(reinterpret_cast<volatile long*>(&_runningThreadCount));
        return true;
    }
    _threads[i]->_threadManager = nullptr;
    _threads[i] = nullptr;
    _threadHandles[i] = nullptr;
    return false;
}

// 0x12f40
bool ThreadManager::StopThread(unsigned long long threadId, long waitTime, bool forceTerminate, bool remove)
{
    int index = 0;
    if (_maxThreadCount == 0)
        return false;
    for (Thread** i = _threads; *i == nullptr || (*i)->_id != threadId; ++i)
    {
        if (++index >= static_cast<int>(_maxThreadCount))
            return false;
    }
    return index >= 0 && _threads[index] != nullptr && _threadHandles[index] != nullptr &&
           stopThread(index, waitTime, forceTerminate, remove);
}

// 0x12fe0
void ThreadManager::StopAll(long waitTime, bool forceTerminate)
{
    for (unsigned int i = 0; i < _maxThreadCount; ++i)
    {
        if (_threads[i] != nullptr)
            _threads[i]->stop();
    }
    for (unsigned int i = 0; i < _maxThreadCount; ++i)
    {
        if (_threads[i] != nullptr)
        {
            _threads[i]->stop();
            if (WaitForSingleObject(_threadHandles[i], waitTime) != WAIT_OBJECT_0)
                TerminateThread(_threadHandles[i], 0);
            _threads[i] = nullptr;
            InterlockedDecrement(reinterpret_cast<volatile long*>(&_runningThreadCount));
        }
    }
}

// 0x130b0
bool ThreadManager::stopThread(int index, long waitTime, bool forceTerminate, bool remove)
{
    _threads[index]->stop();
    if (WaitForSingleObject(_threadHandles[index], waitTime) != WAIT_OBJECT_0)
    {
        if (!forceTerminate)
            return false;
        TerminateThread(_threadHandles[index], 0);
    }
    if (remove)
    {
        _threads[index] = nullptr;
        InterlockedDecrement(reinterpret_cast<volatile long*>(&_runningThreadCount));
    }
    return true;
}

// 0x13140
unsigned int __stdcall ThreadManager::entry(void* args)
{
    if (args != nullptr)
    {
        Thread* thread = static_cast<Thread*>(args);
        Thread::Current = thread;
        thread->_id = GetCurrentThreadId();
        thread->_run = true;
        thread->_lastExecuted = thread->_threadManager->_now;
        thread->run();
        thread->_run = false;
    }
    return 0;
}
