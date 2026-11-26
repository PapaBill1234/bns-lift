// CouponJob.obj (SmartCouponDaemon PDB). Layouts from include/pdb/SmartCouponDaemon/types.h.
#pragma once
#include <stddef.h>
#include <map>
#include "RefCntObject.h"
#include "Lock.h"
#include "StlMemory.h"

class RefCntPoolObj : public RefCntObject
{
public:
    virtual ~RefCntPoolObj();
};
static_assert(sizeof(RefCntPoolObj) == 0x18, "sizeof RefCntPoolObj");

struct JobStateDef
{
    int state;
    wchar_t const* desc;
};
static_assert(sizeof(JobStateDef) == 0x10, "sizeof JobStateDef");

struct JobDef
{
    int type;
    JobStateDef const* stateDef;
    int fin;
    wchar_t const* desc;
};
static_assert(sizeof(JobDef) == 0x20, "sizeof JobDef");

class CouponJob : public RefCntPoolObj
{
public:
    // LIFT: inlined in EventNotiJob::EventNotiJob (0x99F0): the base stores _id, _state and _lastState before
    // InitializeCriticalSection of _lock.
    CouponJob() : _id(0), _state(0), _lastState(0) {}
    virtual JobDef const* GetDefinition() const = 0;  // slot 4
    virtual bool dispatch_work(int, void*);           // slot 5
    virtual bool work(int, void*) = 0;                // slot 6
    virtual ~CouponJob();

    // PDB: ?execute@CouponJob@@IEAA?AW4Result@1@HPEAX@Z and ?resume@...@@IEAA?AW4Result@1@HHPEAX@Z return Result.
    // JobManager::Execute (0x71A0) tests the result with `cmp eax, 1` (JOB_FIN).
    enum Result : int
    {
        JOB_DONE = 0x0,
        JOB_FIN = 0x1,
    };

    bool transit(int state);                          // 0x6990
    Result execute(int task, void* param);            // 0x6B50
    Result resume(int state, int task, void* param);  // 0x6C10

    unsigned long long _id;
    int _state;
    int _lastState;
    CriticalSection _lock;
};
static_assert(sizeof(CouponJob) == 0x50, "sizeof CouponJob");
static_assert(offsetof(CouponJob, _id) == 0x18, "CouponJob::_id");
static_assert(offsetof(CouponJob, _lock) == 0x28, "CouponJob::_lock");

class JobManager
{
public:
    // LIFT: Inlined in SmartCouponDaemon::initialize (0x150E0).
    explicit JobManager(unsigned long long (*idgen)())
        : _idgen(reinterpret_cast<void*>(idgen)), _hashCount(0), _jobs(nullptr), _lock(nullptr)
    {
    }
    ~JobManager();  // 0x6CE0

    typedef std::map<unsigned long long, CouponJob*, std::less<unsigned long long>,
                     StlAllocator<std::pair<unsigned long long, CouponJob*>, 2> > JobMap;  // PDB JobManager::JobMap

    bool Initialize(int hashCount);                                   // 0x6E10
    bool Register(CouponJob* job);                                    // 0x6F60
    void Clear();                                                     // 0x6FF0
    void Execute(CouponJob* job, int task, void* param);              // 0x71A0
    // PDB: 3 arguments. LTCG removed task in the binary (the callers give 2).
    bool ExecuteW(unsigned long long jobid, int task, void* param);   // 0x7220
    bool ResumeW(unsigned long long jobid, int state, int task);      // 0x72B0

private:
    friend class SendPublicationEvent;  // LIFT: access. SendPublicationEvent::HandleEvent calls remove (0xC12D).
    bool add(CouponJob* job);                     // 0x7360
    void remove(unsigned long long jobid);        // 0x7440
    CouponJob* find(unsigned long long jobid);    // 0x7540

public:
    void* _idgen;
    int _hashCount;
    JobMap* _jobs;
    CriticalSection* _lock;
};
static_assert(sizeof(JobManager) == 0x20, "sizeof JobManager");
