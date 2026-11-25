// LobbyJob.obj (LobbyDaemon PDB, 2019 + PDB). Layouts from tools/pdbcls.py LobbyDaemon <Class>.
#pragma once
#include <stddef.h>
#include <map>
#include "AuctionDeliverJob.h"
#include "Lock.h"
#include "StlMemory.h"
#include "TimerQueue.h"

struct EventContext;
class LobbyJob;
class LobbyJobManager;

// PDB LobbyJobStateDef (sizeof 0x10).
struct LobbyJobStateDef
{
    int state;
    wchar_t const* desc;
};
static_assert(sizeof(LobbyJobStateDef) == 0x10, "sizeof LobbyJobStateDef");

// PDB LobbyJobDef (sizeof 0x20). Each job class gives a static table of this type.
struct LobbyJobDef
{
    int type;
    LobbyJobStateDef const* stateDef;
    int fin;
    wchar_t const* desc;
};
static_assert(sizeof(LobbyJobDef) == 0x20, "sizeof LobbyJobDef");
static_assert(offsetof(LobbyJobDef, stateDef) == 0x08, "LobbyJobDef::stateDef");
static_assert(offsetof(LobbyJobDef, fin) == 0x10, "LobbyJobDef::fin");
static_assert(offsetof(LobbyJobDef, desc) == 0x18, "LobbyJobDef::desc");

// PDB LobbyJobTaskParam (sizeof 8): vfptr and a virtual dtor only. The job classes derive their task parameters from it.
class LobbyJobTaskParam
{
public:
    virtual ~LobbyJobTaskParam() {}
};
static_assert(sizeof(LobbyJobTaskParam) == 8, "sizeof LobbyJobTaskParam");

// LIFT: PDB layout (sizeof 0x50, RefCntPoolObj base). Only the members that lift-lobbydaemon-16 needs are laid out here.
class LobbyJob : public RefCntPoolObj
{
public:
    // PDB LobbyJob::Result (enum 0x4807). execute and resume return it; the callers test it with cmp eax,1.
    enum Result
    {
        JOB_DONE = 0,
        JOB_FIN = 1
    };

    // LIFT: constructor not in the PDB. Inlined in CliSessionJob::CliSessionJob (0x3bef0): _id, _state and _lastState are set to zero.
    LobbyJob() : _id(0), _state(0), _lastState(0) {}
    int GetState() const { return _state; }  // PDB inline (type 0x4814)
    virtual LobbyJobDef const* GetDefinition() const = 0;  // slot 4
    virtual ~LobbyJob();  // 0x12270
protected:
    virtual bool dispatch_work(int, void*);  // 0x122b0
public:
    virtual bool work(int, void*) = 0;  // slot 6
protected:
    bool transit(int);  // 0xc1710
    friend class LobbyJobManager;  // LIFT: access. LobbyJobManager::Execute and ResumeW call execute and resume.
    Result execute(int, void*);  // 0xc18d0 (PDB: protected, returns LobbyJob::Result)
    Result resume(int, int, void*);  // 0xc1990 (PDB: protected, returns LobbyJob::Result)

public:
    unsigned long long _id;
    int _state;
    int _lastState;
    CriticalSection _lock;
};
static_assert(sizeof(LobbyJob) == 0x50, "sizeof LobbyJob");
static_assert(offsetof(LobbyJob, _id) == 0x18, "LobbyJob::_id");
static_assert(offsetof(LobbyJob, _lock) == 0x28, "LobbyJob::_lock");

// PDB LobbyJobManager (sizeof 0x20).
class LobbyJobManager
{
public:
    typedef std::map<unsigned long long, LobbyJob*, std::less<unsigned long long>,
                     StlAllocator<std::pair<unsigned long long, LobbyJob*>, 2> > LobbyJobMap;  // PDB LobbyJobManager::LobbyJobMap

    // LIFT: the constructor is not in the PDB (inlined). Same form as SmartCouponDaemon JobManager.
    explicit LobbyJobManager(unsigned long long (*idgen)())
        : _idgen(idgen), _hashCount(0), _jobs(nullptr), _lock(nullptr)
    {
    }
    ~LobbyJobManager();  // 0xc1a60
    bool Initialize(int);  // 0xc1b40
    bool Register(LobbyJob*);  // 0xc1c90
    void Clear();  // 0xc1d20
    bool Start(LobbyJob*, int, void*);  // 0xc1ed0
    bool Postpone(LobbyJob*, int, LobbyJobTaskParam*);  // 0xc1f30
    void Execute(LobbyJob*, int, void*);  // 0xc2020
    bool ExecuteW(unsigned long long, int, void*);  // 0xc20a0
    bool ResumeW(unsigned long long, int, int, void*);  // 0xc2140
private:
    bool add(LobbyJob*);  // 0xc21f0
    void remove(unsigned long long);  // 0xc22d0
    LobbyJob* find(unsigned long long);  // 0xc23d0

public:
    unsigned long long (*_idgen)();
    int _hashCount;
    LobbyJobMap* _jobs;
    CriticalSection* _lock;
};
static_assert(sizeof(LobbyJobManager) == 0x20, "sizeof LobbyJobManager");
static_assert(offsetof(LobbyJobManager, _jobs) == 0x10, "LobbyJobManager::_jobs");
static_assert(offsetof(LobbyJobManager, _lock) == 0x18, "LobbyJobManager::_lock");

// PDB LobbyJobTaskEvent (sizeof 0x30, DynamicEventObject base).
class LobbyJobTaskEvent : public DynamicEventObject
{
public:
    // LIFT: the constructor is inlined in LobbyJobManager::Postpone (0xc1f30). LobbyJob.h line 195.
    LobbyJobTaskEvent(LobbyJob* job, int task, LobbyJobTaskParam* param);
    virtual ~LobbyJobTaskEvent();  // 0xc1670
    virtual unsigned int EventId() const { return 0; }  // 0x5a0a0 (folded)
    virtual bool HandleEvent(EventContext*, unsigned long);  // 0xc24c0

private:
    LobbyJobTaskEvent(LobbyJobTaskEvent const&);
    LobbyJobTaskEvent& operator=(LobbyJobTaskEvent const&);

    LobbyJob* _job;
    int _task;
    LobbyJobTaskParam* _param;
};
static_assert(sizeof(LobbyJobTaskEvent) == 0x30, "sizeof LobbyJobTaskEvent");

// LobbyJob.h line 195 (inlined in LobbyJobManager::Postpone 0xc1f30).
inline LobbyJobTaskEvent::LobbyJobTaskEvent(LobbyJob* job, int task, LobbyJobTaskParam* param)
    : _job(job), _task(task), _param(param)
{
    if (job != nullptr)
        job->addReferenceCount(false,
            L"e:\\dailybuild02\\lobbydaemon-common-0.0.348\\depot\\branch\\348nc\\program\\server\\lobbydaemon\\LobbyJob.h",
            195);
}
