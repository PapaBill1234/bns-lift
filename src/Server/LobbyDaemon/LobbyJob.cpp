// LobbyJob.obj (LobbyDaemon PDB, 2019 + PDB). Source file name from log strings: "LobbyJob.cpp".
// Logic from the 2019 + PDB Hex-Rays pseudocode. Same form as SmartCouponDaemon CouponJob.cpp.
// LIFT: this object has the upper case build path of StlMemory.h (from the HR strings, 0xc1d20).
#define LIFT_STLMEMORY_FILE \
    L"E:\\DailyBuild02\\LobbyDaemon-Common-0.0.348\\depot\\Branch\\348NC\\Program\\Server\\BloodLib\\include\\StlMemory.h"
// LIFT: the original Memory.h (line 181) gives its own placement array new and delete. This stops <new> from giving them.
#define __PLACEMENT_VEC_NEW_INLINE
#include <windows.h>
#include <new>
#include "LobbyJob.h"
#include "LobbyDaemon.h"
#include "Network.h"
#include "Log.h"
#include "AlertSender.h"
#include "Memory.h"
#include "MemoryManager.h"

// PDB S_GTHREAD32 (void*). Defined in CliSessionTable.cpp.
extern __declspec(thread) void* __delv_buf__;

// LIFT: inlined in LobbyJobManager::~LobbyJobManager 0xc1a60.
inline void __cdecl operator delete[](void* p)
{
    __delv_buf__ = p;
}

inline void* __cdecl operator new[](size_t, void* buf) throw()
{
    return buf;
}

inline void __cdecl operator delete[](void*, void*)
{
    Log::Write(Log::LT_ERROR,
               L"e:\\dailybuild02\\lobbydaemon-common-0.0.348\\depot\\branch\\348nc\\program\\server\\bloodlib\\include\\Memory.h",
               181, L"== CRASH == [memory], DO NOT USE THIS DEL OPERATOR");
    AlertSender::Write(
        L"e:\\dailybuild02\\lobbydaemon-common-0.0.348\\depot\\branch\\348nc\\program\\server\\bloodlib\\include\\Memory.h",
        181, L"== CRASH == [memory], DO NOT USE THIS DEL OPERATOR");
}

static wchar_t const* const kFile = L"LobbyJob.cpp";
// LIFT: the dtor of LobbyJobTaskEvent is defined in LobbyJob.h (lower case build path in the HR strings).
static wchar_t const* const kHeader =
    L"e:\\dailybuild02\\lobbydaemon-common-0.0.348\\depot\\branch\\348nc\\program\\server\\lobbydaemon\\LobbyJob.h";

// 0xc1670 (LobbyJob.h lines 200 and 202)
LobbyJobTaskEvent::~LobbyJobTaskEvent()
{
    if (_job != nullptr)
        _job->removeReferenceCount(kHeader, 200);
    if (_param != nullptr)
    {
        _param->~LobbyJobTaskParam();
        Memory::_Manager[2]->Free(_param, kHeader, 202);
    }
}

// 0xc1710
bool LobbyJob::transit(int state)
{
    LobbyJobDef const* def = GetDefinition();
    if (def == nullptr)
    {
        Log::Write(Log::LT_ERROR, kFile, 19, L"== CRASH == [job], transit fail; no definition, tid:0x%I64X", _id);
        AlertSender::Write(kFile, 19, L"== CRASH == [job], transit fail; no definition, tid:0x%I64X", _id);
        return false;
    }
    if (state <= 0 || state > def->fin)
    {
        Log::Write(Log::LT_ERROR, kFile, 24,
                   L"== CRASH == [job], transit fail; state out of range, to:%d, tid:0x%I64X, type:%d, state:%d",
                   state, _id, GetDefinition()->type, _state);
        AlertSender::Write(kFile, 24,
                           L"== CRASH == [job], transit fail; state out of range, to:%d, tid:0x%I64X, type:%d, state:%d",
                           state, _id, GetDefinition()->type, _state);
    }
    else if (state < _state)
    {
        Log::Write(Log::LT_ERROR, kFile, 30,
                   L"== CRASH == [job], transit fail; roll back not allowed, to:%d, tid:0x%I64X, type:%d, state:%d",
                   state, _id, GetDefinition()->type, _state);
        AlertSender::Write(kFile, 30,
                           L"== CRASH == [job], transit fail; roll back not allowed, to:%d, tid:0x%I64X, type:%d, state:%d",
                           state, _id, GetDefinition()->type, _state);
    }
    else
    {
        _lastState = _state;
        _state = state;
        Log::Write(Log::LT_DEBUG, kFile, 37, L"[job], transit ok, from:%d, tid:0x%I64X, type:%d, state:%d",
                   _lastState, _id, GetDefinition()->type, state);
        return true;
    }
    return false;
}

// 0xc18d0
LobbyJob::Result LobbyJob::execute(int task, void* param)
{
    EnterCriticalSection(&_lock.CS);
    if (_state == GetDefinition()->fin)
    {
        LeaveCriticalSection(&_lock.CS);
        return JOB_DONE;
    }
    if (!dispatch_work(task, param) && _state != GetDefinition()->fin)
        transit(GetDefinition()->fin);
    int const state = _state;
    LeaveCriticalSection(&_lock.CS);
    if (state == GetDefinition()->fin)
        return JOB_FIN;
    return JOB_DONE;
}

// 0xc1990
LobbyJob::Result LobbyJob::resume(int state, int task, void* /*param*/)
{
    EnterCriticalSection(&_lock.CS);
    int const cur = _state;
    if (cur == GetDefinition()->fin || cur != state)
    {
        LeaveCriticalSection(&_lock.CS);
        return JOB_DONE;
    }
    // The original passes nullptr, not param.
    if (!dispatch_work(task, nullptr) && _state != GetDefinition()->fin)
        transit(GetDefinition()->fin);
    int const now = _state;
    LeaveCriticalSection(&_lock.CS);
    if (now == GetDefinition()->fin)
        return JOB_FIN;
    return JOB_DONE;
}

// 0xc1a60
LobbyJobManager::~LobbyJobManager()
{
    Clear();
    if (_jobs != nullptr)
    {
        delete[] _jobs;
        Memory::_Manager[2]->Free(__delv_buf__, kFile, 119);
        _jobs = nullptr;
    }
    if (_lock != nullptr)
    {
        delete[] _lock;
        Memory::_Manager[2]->Free(__delv_buf__, kFile, 121);
        _lock = nullptr;
    }
}

// 0xc1b40
bool LobbyJobManager::Initialize(int hashCount)
{
    if (hashCount == 0)
    {
        Log::Write(Log::LT_ERROR, kFile, 127, L"[job-mgr], initialize fail; zero hash count");
        return false;
    }
    _hashCount = hashCount;

    // The count is in the 8 bytes in front of the array.
    _jobs = new (Memory::_Manager[2]->Alloc(sizeof(LobbyJobMap) * hashCount + 8, kFile, 132)) LobbyJobMap[hashCount];
    _lock = new (Memory::_Manager[2]->Alloc(sizeof(CriticalSection) * _hashCount + 8, kFile, 133))
        CriticalSection[_hashCount];
    // BUG: 0xc1b40 the result of both Alloc calls is not checked.
    Log::Write(Log::LT_NOTICE, kFile, 135, L"[job-mgr], initialize ok, hash-count:%d", _hashCount);
    return true;
}

// 0xc1c90
bool LobbyJobManager::Register(LobbyJob* job)
{
    if (job == nullptr)
    {
        Log::Write(Log::LT_ERROR, kFile, 142, L"[job-mgr], register fail; null job");
        return false;
    }
    job->_id = _idgen();
    if (!add(job))
    {
        Log::Write(Log::LT_ERROR, kFile, 149, L"[job-mgr], register fail; add fail, tid:0x%I64X", job->_id);
        return false;
    }
    return true;
}

// 0xc1d20
void LobbyJobManager::Clear()
{
    if (_jobs == nullptr)
        return;
    for (int i = 0; i < _hashCount; ++i)
    {
        LobbyJobMap& jobs = _jobs[i];
        CriticalSection& lock = _lock[i];
        EnterCriticalSection(&lock.CS);
        for (LobbyJobMap::iterator it = jobs.begin(); it != jobs.end(); ++it)
        {
            if (it->second != nullptr)
                it->second->removeReferenceCount(kFile, 168);
        }
        jobs.clear();
        LeaveCriticalSection(&lock.CS);
    }
}

// 0xc1ed0
bool LobbyJobManager::Start(LobbyJob* job, int task, void* param)
{
    if (!Register(job))
        return false;
    Execute(job, task, param);
    return true;
}

// 0xc1f30
bool LobbyJobManager::Postpone(LobbyJob* job, int task, LobbyJobTaskParam* param)
{
    if (!Register(job))
        return false;
    // LIFT: the binary stores 0 in _param. LTCG put in the nullptr that each caller gives (AbandonChargeJob, GameWorld).
    LobbyJobTaskEvent* const event =
        new (Memory::_Manager[2]->Alloc(sizeof(LobbyJobTaskEvent), kFile, 201)) LobbyJobTaskEvent(job, task, param);
    PostQueuedCompletionStatus(Network::iocpHandle(), 0, reinterpret_cast<ULONG_PTR>(event), nullptr);
    return true;
}

// 0xc2020
void LobbyJobManager::Execute(LobbyJob* job, int task, void* param)
{
    if (job == nullptr)
    {
        Log::Write(Log::LT_ERROR, kFile, 209, L"== CRASH == [job-mgr], execute fail; null job");
        AlertSender::Write(kFile, 209, L"== CRASH == [job-mgr], execute fail; null job");
        return;
    }
    if (job->execute(task, param) == LobbyJob::JOB_FIN)
        remove(job->_id);
}

// 0xc20a0
bool LobbyJobManager::ExecuteW(unsigned long long jobid, int task, void* param)
{
    LobbyJob* const job = find(jobid);
    if (job == nullptr)
    {
        Log::Write(Log::LT_ERROR, kFile, 221, L"[job-mgr], execute fail; no such job, tid:0x%I64X", jobid);
        return false;
    }
    Execute(job, task, param);
    job->removeReferenceCount(kFile, 227);
    return true;
}

// 0xc2140
bool LobbyJobManager::ResumeW(unsigned long long jobid, int state, int task, void* param)
{
    LobbyJob* const job = find(jobid);
    if (job == nullptr)
    {
        Log::Write(Log::LT_ERROR, kFile, 246, L"[job-mgr], resume fail; no such job, tid:0x%I64X", jobid);
        return false;
    }
    if (job->resume(state, task, param) == LobbyJob::JOB_FIN)
        remove(job->_id);
    job->removeReferenceCount(kFile, 252);
    return true;
}

// 0xc21f0
bool LobbyJobManager::add(LobbyJob* job)
{
    if (job == nullptr)
        return false;
    if (job->_id == 0)
        return false;
    int const slot = static_cast<int>(job->_id % _hashCount);
    EnterCriticalSection(&_lock[slot].CS);
    bool const inserted = _jobs[slot].insert(std::pair<unsigned long long, LobbyJob*>(job->_id, job)).second;
    if (inserted)
        job->addReferenceCount(kFile, 284);
    LeaveCriticalSection(&_lock[slot].CS);
    return inserted;
}

// 0xc22d0
void LobbyJobManager::remove(unsigned long long jobid)
{
    if (jobid == 0)
        return;
    int const slot = static_cast<int>(jobid % _hashCount);
    LobbyJob* job = nullptr;
    EnterCriticalSection(&_lock[slot].CS);
    LobbyJobMap& jobs = _jobs[slot];
    LobbyJobMap::iterator it = jobs.find(jobid);
    if (it != jobs.end())
    {
        job = it->second;
        jobs.erase(it);
    }
    LeaveCriticalSection(&_lock[slot].CS);
    if (job != nullptr)
        job->removeReferenceCount(kFile, 311);
}

// 0xc23d0
LobbyJob* LobbyJobManager::find(unsigned long long jobid)
{
    if (jobid == 0)
        return nullptr;
    int const slot = static_cast<int>(jobid % _hashCount);
    LobbyJob* job = nullptr;
    EnterCriticalSection(&_lock[slot].CS);
    LobbyJobMap& jobs = _jobs[slot];
    LobbyJobMap::iterator it = jobs.find(jobid);
    if (it != jobs.end())
    {
        job = it->second;
        job->addReferenceCount(kFile, 328);
    }
    LeaveCriticalSection(&_lock[slot].CS);
    return job;
}

// 0xc24c0
bool LobbyJobTaskEvent::HandleEvent(EventContext*, unsigned long)
{
    LobbyDaemon::_instance->_jobMgr->Execute(_job, _task, _param);
    removeReferenceCount(kFile, 342);
    return true;
}
