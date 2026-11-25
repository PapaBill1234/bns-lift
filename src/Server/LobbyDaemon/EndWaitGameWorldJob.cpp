// EndWaitGameWorldJob.obj (LobbyDaemon PDB, 2019 + PDB). Lifted from the pseudocode with PDB types.
#include <new>
#include <wchar.h>
#include <winsock2.h>
#include <windows.h>
#include "EndWaitGameWorldJob.h"
#include "AlertSender.h"
#include "CliSession.h"
#include "LiftStub.h"
#include "LobbyDaemon.h"
#include "LobbyGateChannel.h"
#include "LobbyToken.h"
#include "Log.h"
#include "Memory.h"
#include "MemoryManager.h"

static wchar_t const kFile[] = L"EndWaitGameWorldJob.cpp";

// The log suffix of all LobbyJob logs. The original reads the owner state 2 times (HIWORD and LOWORD).
#define JOB_LOG(logType, line, msg, fmt, ...)                                                                          \
    Log::Write(logType, kFile, line, msg L", tid:0x%I64X, type:%d, state:%d, cli-key:0x%I64X, cli-state:%d.%d" fmt,   \
               this != nullptr ? _id : 0, this != nullptr ? GetDefinition()->type : -1,                            \
               this != nullptr ? _state : -1, this != nullptr && _owner != nullptr ? _owner->_clikey : 0,          \
               HIWORD(this != nullptr && _owner != nullptr ? _owner->_state : 0),                                  \
               LOWORD(this != nullptr && _owner != nullptr ? _owner->_state : 0), ##__VA_ARGS__)

// The same log, then the same text to the alert sender ("== CRASH ==" logs).
#define JOB_CRASH(line, msg, fmt, ...)                                                                                 \
    do                                                                                                                 \
    {                                                                                                                  \
        JOB_LOG(Log::LT_ERROR, line, L"== CRASH == " msg, fmt, ##__VA_ARGS__);                                         \
        AlertSender::Write(kFile, line, L"== CRASH == " msg L", tid:0x%I64X, type:%d, state:%d, cli-key:0x%I64X, cli-state:%d.%d" fmt, \
                           this != nullptr ? _id : 0, this != nullptr ? GetDefinition()->type : -1,                    \
                           this != nullptr ? _state : -1, this != nullptr && _owner != nullptr ? _owner->_clikey : 0,  \
                           HIWORD(this != nullptr && _owner != nullptr ? _owner->_state : 0),                          \
                           LOWORD(this != nullptr && _owner != nullptr ? _owner->_state : 0), ##__VA_ARGS__);          \
    } while (0)

// PDB enum ECliSessionState (CliSession.h has no copy yet): CSS_LOBBY = 0x20000, CSS_L2W_wait = 0x30002,
// CSS_L2W_ok = 0x30003, CSS_WORLD = 0x40000, CSS_W2L_wait = 0x50001, CSS_FIN = 0x60000.

namespace
{
LobbyJobStateDef const StateDef[] = {{0, L"INIT"}, {1, L"END_WAIT"}, {2, L"FIN"}};  // 0x12dfc0
}

LobbyJobDef EndWaitGameWorldJob::_def = {9, StateDef, 2, L"EndWaitGameWorldJob"};  // 0x201cf0
// LIFT: EndWaitGameWorldJob::_pool has no definition. The LobbyDaemon ObjectPool module is not in lift_lobbydaemon
// (see CliSession.cpp).

// 0x4afe0
LobbyJobDef const* EndWaitGameWorldJob::GetDefinition() const
{
    return &_def;
}

// 0x4aff0
// LIFT: Not done. The body calls _pool.Checkin. ObjPool is not in lift_lobbydaemon.
void EndWaitGameWorldJob::deallocate_me(void*, wchar_t const*, int)
{
    LIFT_STUB(0x4aff0);
}

// 0x4b040
// The original constructs a job on the stack (null owner) and returns its vfptr. It does not run the destructor.
void* EndWaitGameWorldJob::_vtbl()
{
    char buf[sizeof(EndWaitGameWorldJob)];
    EndWaitGameWorldJob* job = ::new (buf) EndWaitGameWorldJob(nullptr);
    return *reinterpret_cast<void**>(job);
}

// 0x4b0c0 (scalar deleting destructor)
EndWaitGameWorldJob::~EndWaitGameWorldJob()
{
    if (_lgate != nullptr)
        _lgate->removeReferenceCount(kFile, 61);
}

// 0x4b110
bool EndWaitGameWorldJob::work(int task, void* param)
{
    bool result = false;
    if (_state == INIT && task == 3)
    {
        result = init(task, param);
        task = 0;
    }
    if (_state == END_WAIT && task == 0)
        return endWait();
    return result;
}

// 0x4b150
bool EndWaitGameWorldJob::init(int, void*)
{
    if (_owner->_state != 0x30002)  // CSS_L2W_wait
    {
        JOB_LOG(Log::LT_ERROR, 90, L"[job], cli-session not in L2W.wait", L"");
        transit(FIN);
        return true;
    }

    Presence* presence = _owner->_presence;
    if (presence == nullptr)
    {
        JOB_LOG(Log::LT_ERROR, 97, L"[job], null presence", L"");
        _owner->_state = 0x60000;  // CSS_FIN
        _owner->finalize();
        transit(FIN);
        return true;
    }

    LobbyGatePresence* lgp = presence->GetKind() == Presence::LobbyGate ? static_cast<LobbyGatePresence*>(presence) : nullptr;
    if (lgp == nullptr)
    {
        JOB_LOG(Log::LT_ERROR, 108, L"[job], unexpected presence", L", kind:%d", presence->GetKind());
        _owner->_state = 0x60000;  // CSS_FIN
        _owner->finalize();
        transit(FIN);
        return true;
    }

    _lgate = LobbyDaemon::_instance->_lgatechmgr->Acquire(lgp->_gatewid);
    if (_lgate == nullptr)
    {
        JOB_LOG(Log::LT_ERROR, 118, L"[job], lobby gate not exists", L", gate-wid:%d", lgp->_gatewid);
        _owner->_state = 0x60000;  // CSS_FIN
        _owner->finalize();
        transit(FIN);
        return true;
    }

    transit(END_WAIT);
    return true;
}

// 0x4b460
bool EndWaitGameWorldJob::endWait()
{
    ServiceLocation* srvloc = _owner->_srvloc;
    if (srvloc == nullptr)
    {
        JOB_LOG(Log::LT_ERROR, 134, L"[job], not in service location", L"");
        _owner->_state = 0x60000;  // CSS_FIN
        _owner->finalize();
        transit(FIN);
        return true;
    }
    if (srvloc->GetKind() != ServiceLocation::KIND_GAMEWORLD)
    {
        JOB_LOG(Log::LT_ERROR, 142, L"[job], not in game service location", L", kind:%d, wid:%d", srvloc->GetKind(), srvloc->_wid);
        _owner->_state = 0x60000;  // CSS_FIN
        _owner->finalize();
        transit(FIN);
        return true;
    }

    GameServiceLocation* gsl = static_cast<GameServiceLocation*>(srvloc);
    gsl->_waitPos = -1;
    JOB_LOG(Log::LT_DEBUG, 152, L"[job], end wait ok", L", wid:%d, pcid:0x%I64X", srvloc->_wid, gsl->_pcid);

    LobbyToken* token = new (Memory::_Manager[2]->Alloc(sizeof(EnterGameWorldToken), kFile, 154))
        EnterGameWorldToken(_owner, srvloc->_wid, gsl->_pcid);
    if (!LobbyDaemon::_instance->_tokenDesk->Issue(token))
    {
        JOB_CRASH(156, L"[job], issue token fail", L"");
        _owner->_state = 0x60000;  // CSS_FIN
        _owner->finalize();
        token->removeReferenceCount(kFile, 159);
    }
    else
    {
        _owner->_state = 0x30003;  // CSS_L2W_ok
        JOB_LOG(Log::LT_DEBUG, 166, L"[job], issue token ok", L"");
        _lgate->SendEndWaitNotify(_owner->_clikey, token->_tokenkey);
        token->removeReferenceCount(kFile, 170);
    }
    transit(FIN);
    return true;
}
