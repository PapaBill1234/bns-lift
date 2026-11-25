// GiveupWaitGameWorldJob.obj (LobbyDaemon PDB, 2019 + PDB). Lifted from the pseudocode with PDB types.
#include <new>
#include <wchar.h>
#include <winsock2.h>
#include <windows.h>
#include "GiveupWaitGameWorldJob.h"
#include "CliSession.h"
#include "LiftStub.h"
#include "LobbyGateChannel.h"
#include "Log.h"

static wchar_t const kFile[] = L"GiveupWaitGameWorldJob.cpp";

// The log suffix of all LobbyJob logs. The original reads the owner state 2 times (HIWORD and LOWORD).
#define JOB_LOG(logType, line, msg, fmt, ...)                                                                          \
    Log::Write(logType, kFile, line, msg L", tid:0x%I64X, type:%d, state:%d, cli-key:0x%I64X, cli-state:%d.%d" fmt,   \
               this != nullptr ? _id : 0, this != nullptr ? GetDefinition()->type : -1,                            \
               this != nullptr ? _state : -1, this != nullptr && _owner != nullptr ? _owner->_clikey : 0,          \
               HIWORD(this != nullptr && _owner != nullptr ? _owner->_state : 0),                                  \
               LOWORD(this != nullptr && _owner != nullptr ? _owner->_state : 0), ##__VA_ARGS__)

// PDB enum ECliSessionState (CliSession.h has no copy yet): CSS_LOBBY = 0x20000, CSS_L2W_wait = 0x30002,
// CSS_L2W_ok = 0x30003, CSS_WORLD = 0x40000, CSS_W2L_wait = 0x50001, CSS_FIN = 0x60000.

namespace
{
LobbyJobStateDef const StateDef[] = {{0, L"INIT"}, {1, L"GIVEUP_WAIT"}, {2, L"FIN"}};  // 0x12df00
}

LobbyJobDef GiveupWaitGameWorldJob::_def = {10, StateDef, 2, L"GiveupWaitGameWorldJob"};  // 0x201c70
// LIFT: GiveupWaitGameWorldJob::_pool has no definition. The LobbyDaemon ObjectPool module is not in lift_lobbydaemon
// (see CliSession.cpp).

// 0x52cf0
LobbyJobDef const* GiveupWaitGameWorldJob::GetDefinition() const
{
    return &_def;
}

// 0x52d00
// LIFT: Not done. The body calls _pool.Checkin. ObjPool is not in lift_lobbydaemon.
void GiveupWaitGameWorldJob::deallocate_me(void*, wchar_t const*, int)
{
    LIFT_STUB(0x52d00);
}

// 0x52d50
// The original constructs a job on the stack (null owner) and returns its vfptr. It does not run the destructor.
void* GiveupWaitGameWorldJob::_vtbl()
{
    char buf[sizeof(GiveupWaitGameWorldJob)];
    GiveupWaitGameWorldJob* job = ::new (buf) GiveupWaitGameWorldJob(nullptr);
    return *reinterpret_cast<void**>(job);
}

// 0x52dd0 (scalar deleting destructor)
GiveupWaitGameWorldJob::~GiveupWaitGameWorldJob()
{
    if (_lgate != nullptr)
        _lgate->removeReferenceCount(kFile, 63);
}

// 0x52e20
bool GiveupWaitGameWorldJob::Initialize(LobbyGateChannel* lgate)
{
    if (lgate == nullptr)
    {
        JOB_LOG(Log::LT_ERROR, 69, L"[job], init fail; invalid parameter", L"");
        return false;
    }
    _lgate = lgate;
    lgate->addReferenceCount(false, kFile, 75);
    return true;
}

// 0x52f30
bool GiveupWaitGameWorldJob::work(int task, void*)
{
    bool result = false;
    if (_state == INIT && task == 16)
    {
        result = init();
        task = 0;
    }
    if (_state == GIVEUP_WAIT && task == 0)
        return giveupWait();
    return result;
}

// 0x52f70
bool GiveupWaitGameWorldJob::init()
{
    int next = GIVEUP_WAIT;
    if (_owner->_state != 0x30002)  // CSS_L2W_wait
    {
        JOB_LOG(Log::LT_ERROR, 105, L"[job], cli-session not in L2W.wait", L"");
        _lgate->SendGiveupWaitFail(_owner->_clikey, 5);
        next = FIN;
    }
    else
    {
        JOB_LOG(Log::LT_DEBUG, 111, L"[job], init ok", L"");
    }
    transit(next);
    return true;
}

// 0x530d0
bool GiveupWaitGameWorldJob::giveupWait()
{
    ServiceLocation* srvloc = _owner->_srvloc;
    if (srvloc == nullptr)
    {
        JOB_LOG(Log::LT_ERROR, 125, L"[job], null residence", L"");
        _lgate->SendGiveupWaitFail(_owner->_clikey, 2);
        transit(FIN);
        return true;
    }
    if (srvloc->GetKind() != ServiceLocation::KIND_GAMEWORLD)
    {
        JOB_LOG(Log::LT_ERROR, 132, L"[job], invalid residence", L", kind:%d, wid:%d", srvloc->GetKind(), srvloc->_wid);
        _lgate->SendGiveupWaitFail(_owner->_clikey, 2);
        transit(FIN);
        return true;
    }

    GameServiceLocation* gsl = static_cast<GameServiceLocation*>(srvloc);
    short wid = gsl->_wid;
    unsigned long long pcid = gsl->_pcid;
    _owner->leave();
    _owner->_state = 0x20000;  // CSS_LOBBY
    _lgate->SendGiveupWaitOk(_owner->_clikey);
    JOB_LOG(Log::LT_DEBUG, 148, L"[job], giveup wait ok", L", wid:%d, pcid:0x%I64X", wid, pcid);
    transit(FIN);
    return true;
}
