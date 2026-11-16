// CouponJob.obj (SmartCouponDaemon PDB). Layouts from include/pdb/SmartCouponDaemon/types.h.
#pragma once
#include <stddef.h>
#include <map>
#include "RefCntObject.h"
#include "Lock.h"

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
    virtual JobDef const* GetDefinition() const = 0;  // slot 4
    virtual bool dispatch_work(int, void*);           // slot 5
    virtual bool work(int, void*) = 0;                // slot 6
    virtual ~CouponJob();

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
    // ❓ Inlined in SmartCouponDaemon::initialize (0x150E0).
    explicit JobManager(unsigned long long (*idgen)())
        : _idgen(reinterpret_cast<void*>(idgen)), _hashCount(0), _jobs(nullptr), _lock(nullptr)
    {
    }
    ~JobManager();  // ❓ address

    bool Initialize(int hashCount);  // ❓ address
    void Clear();                    // ❓ address

    void* _idgen;
    int _hashCount;
    std::map<unsigned long long, CouponJob*>* _jobs;
    CriticalSection* _lock;
};
static_assert(sizeof(JobManager) == 0x20, "sizeof JobManager");
