// CouponJob.obj (SmartCouponDaemon PDB). Source file name from log strings: "CouponJob.cpp".
// LIFT: SCD build path of StlMemory.h (lower case form, from the HR strings).
#define LIFT_STLMEMORY_FILE \
    L"e:\\dailybuild02\\smartcoupondaemon-common-0.0.348\\depot\\branch\\348nc\\program\\server\\bloodlib\\include\\StlMemory.h"
// LIFT: the original Memory.h (line 181) gives its own placement array new and delete. This stops <new> from giving them.
#define __PLACEMENT_VEC_NEW_INLINE
#include <windows.h>
#include <new>
#include "CouponJob.h"
#include "Log.h"
#include "AlertSender.h"
#include "Memory.h"

// PDB S_GTHREAD32 (void*, .tls +0x20). The original operator delete[] only keeps the pointer here. ❓ module of the definition.
__declspec(thread) void* __delv_buf__;

// LIFT: inlined in JobManager::~JobManager 0x6CE0. No exe imports ??_V@YAXPEAX@Z.
inline void __cdecl operator delete[](void* p)
{
    __delv_buf__ = p;
}

inline void* __cdecl operator new[](size_t, void* buf) throw()
{
    return buf;
}

// 0x6850
inline void __cdecl operator delete[](void*, void*)
{
    Log::Write(Log::LT_ERROR,
               L"E:\\DailyBuild02\\SmartCouponDaemon-Common-0.0.348\\depot\\Branch\\348NC\\Program\\Server\\BloodLib\\include\\Memory.h",
               181, L"== CRASH == [memory], DO NOT USE THIS DEL OPERATOR");
    AlertSender::Write(
        L"E:\\DailyBuild02\\SmartCouponDaemon-Common-0.0.348\\depot\\Branch\\348NC\\Program\\Server\\BloodLib\\include\\Memory.h",
        181, L"== CRASH == [memory], DO NOT USE THIS DEL OPERATOR");
}

static wchar_t const* const kFile = L"CouponJob.cpp";

// 0x6990
bool CouponJob::transit(int state)
{
    JobDef const* def = GetDefinition();
    if (def == nullptr)
    {
        Log::Write(Log::LT_ERROR, kFile, 17, L"== CRASH == [job], transit fail; no definition, id:0x%I64X", _id);
        AlertSender::Write(kFile, 17, L"== CRASH == [job], transit fail; no definition, id:0x%I64X", _id);
        return false;
    }
    if (state <= 0 || state > def->fin)
    {
        Log::Write(Log::LT_ERROR, kFile, 22,
                   L"== CRASH == [job], transit fail; state out of range, to:%d, jobid:0x%I64X, type:%d, state:%d",
                   state, _id, GetDefinition()->type, _state);
        AlertSender::Write(kFile, 22,
                           L"== CRASH == [job], transit fail; state out of range, to:%d, jobid:0x%I64X, type:%d, state:%d",
                           state, _id, GetDefinition()->type, _state);
        return false;
    }
    if (state >= _state)
    {
        _lastState = _state;
        _state = state;
        Log::Write(Log::LT_DEBUG, kFile, 35, L"[job], transit ok, from:%d, jobid:0x%I64X, type:%d, state:%d",
                   _lastState, _id, GetDefinition()->type, state);
        return true;
    }
    Log::Write(Log::LT_ERROR, kFile, 28,
               L"== CRASH == [job], transit fail; roll back not allowed, to:%d, jobid:0x%I64X, type:%d, state:%d",
               state, _id, GetDefinition()->type, _state);
    AlertSender::Write(kFile, 28,
                       L"== CRASH == [job], transit fail; roll back not allowed, to:%d, jobid:0x%I64X, type:%d, state:%d",
                       state, _id, GetDefinition()->type, _state);
    return false;
}

// 0x6B50
bool CouponJob::execute(int task, void* param)
{
    EnterCriticalSection(&_lock.CS);
    if (_state == GetDefinition()->fin)
    {
        LeaveCriticalSection(&_lock.CS);
        return false;
    }
    if (!dispatch_work(task, param) && _state != GetDefinition()->fin)
        transit(GetDefinition()->fin);
    int const state = _state;
    LeaveCriticalSection(&_lock.CS);
    return state == GetDefinition()->fin;
}

// 0x6C10
bool CouponJob::resume(int state, int task, void* /*param*/)
{
    EnterCriticalSection(&_lock.CS);
    int const cur = _state;
    if (cur == GetDefinition()->fin || cur != state)
    {
        LeaveCriticalSection(&_lock.CS);
        return false;
    }
    // The original passes nullptr, not param.
    if (!dispatch_work(task, nullptr) && _state != GetDefinition()->fin)
        transit(GetDefinition()->fin);
    int const now = _state;
    LeaveCriticalSection(&_lock.CS);
    return now == GetDefinition()->fin;
}

// 0x6CE0
JobManager::~JobManager()
{
    Clear();
    if (_jobs != nullptr)
    {
        delete[] _jobs;
        Memory::_Manager[2]->Free(__delv_buf__, kFile, 116);
        _jobs = nullptr;
    }
    if (_lock != nullptr)
    {
        delete[] _lock;
        Memory::_Manager[2]->Free(__delv_buf__, kFile, 118);
        _lock = nullptr;
    }
}

// 0x6E10
bool JobManager::Initialize(int hashCount)
{
    if (hashCount == 0)
    {
        Log::Write(Log::LT_ERROR, kFile, 124, L"[job-mgr], initialize fail; zero hash count");
        return false;
    }
    _hashCount = hashCount;

    // The count is in the 8 bytes in front of the array.
    _jobs = new (Memory::_Manager[2]->Alloc(sizeof(JobMap) * hashCount + 8, kFile, 129)) JobMap[hashCount];
    _lock = new (Memory::_Manager[2]->Alloc(sizeof(CriticalSection) * _hashCount + 8, kFile, 130))
        CriticalSection[_hashCount];
    // BUG: 0x6E10 the result of both Alloc calls is not checked.
    Log::Write(Log::LT_NOTICE, kFile, 132, L"[job-mgr], initialize ok, hash-count:%d", _hashCount);
    return true;
}

// 0x6F60
bool JobManager::Register(CouponJob* job)
{
    if (job == nullptr)
    {
        Log::Write(Log::LT_ERROR, kFile, 139, L"[job-mgr], register fail; null job");
        return false;
    }
    job->_id = reinterpret_cast<unsigned long long (*)()>(_idgen)();
    if (!add(job))
    {
        Log::Write(Log::LT_ERROR, kFile, 146, L"[job-mgr], register fail; add fail, jobid:0x%I64X", job->_id);
        return false;
    }
    return true;
}

// 0x6FF0
void JobManager::Clear()
{
    if (_jobs == nullptr)
        return;
    for (int i = 0; i < _hashCount; ++i)
    {
        JobMap& jobs = _jobs[i];
        CriticalSection& lock = _lock[i];
        EnterCriticalSection(&lock.CS);
        for (JobMap::iterator it = jobs.begin(); it != jobs.end(); ++it)
        {
            if (it->second != nullptr)
                it->second->removeReferenceCount(kFile, 165);
        }
        jobs.clear();
        LeaveCriticalSection(&lock.CS);
    }
}

// 0x71A0
void JobManager::Execute(CouponJob* job, int task, void* param)
{
    if (job == nullptr)
    {
        Log::Write(Log::LT_ERROR, kFile, 206, L"== CRASH == [job-mgr], execute fail; null job");
        AlertSender::Write(kFile, 206, L"== CRASH == [job-mgr], execute fail; null job");
        return;
    }
    if (job->execute(task, param))
        remove(job->_id);
}

// 0x7220
bool JobManager::ExecuteW(unsigned long long jobid, int task, void* param)
{
    CouponJob* const job = find(jobid);
    if (job == nullptr)
    {
        Log::Write(Log::LT_ERROR, kFile, 218, L"[job-mgr], execute fail; no such job, jobid:0x%I64X", jobid);
        return false;
    }
    Execute(job, task, param);
    job->removeReferenceCount(kFile, 224);
    return true;
}

// 0x72B0
bool JobManager::ResumeW(unsigned long long jobid, int state, int task)
{
    CouponJob* const job = find(jobid);
    if (job == nullptr)
    {
        Log::Write(Log::LT_ERROR, kFile, 243, L"[job-mgr], resume fail; no such job, jobid:0x%I64X", jobid);
        return false;
    }
    // BUG: 0x72B0 the param argument of resume is an uninitialized register (r9). resume does not use it.
    if (job->resume(state, task, nullptr))
        remove(job->_id);
    job->removeReferenceCount(kFile, 249);
    return true;
}

// 0x7360
bool JobManager::add(CouponJob* job)
{
    if (job == nullptr)
        return false;
    if (job->_id == 0)
        return false;
    int const slot = static_cast<int>(job->_id % _hashCount);
    EnterCriticalSection(&_lock[slot].CS);
    bool const inserted = _jobs[slot].insert(std::pair<unsigned long long, CouponJob*>(job->_id, job)).second;
    if (inserted)
        job->addReferenceCount(kFile, 281);
    LeaveCriticalSection(&_lock[slot].CS);
    return inserted;
}

// 0x7440
void JobManager::remove(unsigned long long jobid)
{
    if (jobid == 0)
        return;
    int const slot = static_cast<int>(jobid % _hashCount);
    CouponJob* job = nullptr;
    EnterCriticalSection(&_lock[slot].CS);
    JobMap& jobs = _jobs[slot];
    JobMap::iterator it = jobs.find(jobid);
    if (it != jobs.end())
    {
        job = it->second;
        jobs.erase(it);
    }
    LeaveCriticalSection(&_lock[slot].CS);
    if (job != nullptr)
        job->removeReferenceCount(kFile, 308);
}

// 0x7540
CouponJob* JobManager::find(unsigned long long jobid)
{
    if (jobid == 0)
        return nullptr;
    int const slot = static_cast<int>(jobid % _hashCount);
    CouponJob* job = nullptr;
    EnterCriticalSection(&_lock[slot].CS);
    JobMap& jobs = _jobs[slot];
    JobMap::iterator it = jobs.find(jobid);
    if (it != jobs.end())
    {
        job = it->second;
        job->addReferenceCount(kFile, 325);
    }
    LeaveCriticalSection(&_lock[slot].CS);
    return job;
}
