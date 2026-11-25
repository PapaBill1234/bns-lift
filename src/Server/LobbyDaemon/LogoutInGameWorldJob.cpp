// LogoutInGameWorldJob.obj (LobbyDaemon PDB, 2019 + PDB). Lifted from the pseudocode with PDB types.
#include <new>
#include <winsock2.h>
#include <windows.h>
#include "LogoutInGameWorldJob.h"
#include "AlertSender.h"
#include "Character.h"
#include "CliSession.h"
#include "LiftStub.h"
#include "Log.h"

static wchar_t const kFile[] = L"LogoutInGameWorldJob.cpp";

// The log suffix of all LobbyJob logs. The original reads the owner state 2 times (HIWORD and LOWORD).
#define JOB_LOG(logType, line, msg, fmt, ...)                                                                          \
    Log::Write(logType, kFile, line, msg L", tid:0x%I64X, type:%d, state:%d, cli-key:0x%I64X, cli-state:%d.%d" fmt,   \
               this != nullptr ? _id : 0, this != nullptr ? GetDefinition()->type : -1,                            \
               this != nullptr ? _state : -1, this != nullptr && _owner != nullptr ? _owner->_clikey : 0,          \
               HIWORD(this != nullptr && _owner != nullptr ? _owner->_state : 0),                                  \
               LOWORD(this != nullptr && _owner != nullptr ? _owner->_state : 0), ##__VA_ARGS__)

// The "== CRASH ==" form: the log and then the alert with the same text. Each call reads its arguments again.
#define JOB_CRASH(line, msg)                                                                                         \
    do                                                                                                               \
    {                                                                                                                \
        JOB_LOG(Log::LT_ERROR, line, msg, L"");                                                                      \
        AlertSender::Write(kFile, line, msg L", tid:0x%I64X, type:%d, state:%d, cli-key:0x%I64X, cli-state:%d.%d",   \
                           this != nullptr ? _id : 0, this != nullptr ? GetDefinition()->type : -1,                 \
                           this != nullptr ? _state : -1,                                                            \
                           this != nullptr && _owner != nullptr ? _owner->_clikey : 0,                              \
                           HIWORD(this != nullptr && _owner != nullptr ? _owner->_state : 0),                       \
                           LOWORD(this != nullptr && _owner != nullptr ? _owner->_state : 0));                      \
    } while (0)

namespace
{
LobbyJobStateDef const StateDef[] = {{0, L"INIT"}, {1, L"LOGOUT"}, {2, L"FIN"}};  // 0x12de40
}

LobbyJobDef LogoutInGameWorldJob::_def = {12, StateDef, 2, L"LogoutInGameWorldJob"};  // 0x201b58

// 0x5aa80
LobbyJobDef const* LogoutInGameWorldJob::GetDefinition() const
{
    return &_def;
}

// 0x5aa90
// LIFT: Not done. The body calls _pool.Checkin. ObjPool is not in lift_lobbydaemon.
void LogoutInGameWorldJob::deallocate_me(void*, wchar_t const*, int)
{
    LIFT_STUB(0x5aa90);
}

// 0x5aae0
// The original constructs a job on the stack (null owner) and returns its vfptr. It does not run the destructor.
void* LogoutInGameWorldJob::_vtbl()
{
    char buf[sizeof(LogoutInGameWorldJob)];
    LogoutInGameWorldJob* job = ::new (buf) LogoutInGameWorldJob(nullptr);
    return *reinterpret_cast<void**>(job);
}

// 0x5ab90
bool LogoutInGameWorldJob::Initialize(short wid)
{
    if (wid != 0)
    {
        _wid = wid;
        return true;
    }
    JOB_LOG(Log::LT_ERROR, 68, L"[job], initialize fail; invalid wid", L"");
    return false;
}

// 0x5ac80
bool LogoutInGameWorldJob::work(int task, void*)
{
    bool result = false;
    if (_state == 0 && task == 118)
    {
        result = init();
        task = 0;
    }
    if (_state == 1 && task == 0)
        return logout();
    return result;
}

// 0x5acc0
bool LogoutInGameWorldJob::init()
{
    if (_owner->_state != 0x40000)
    {
        JOB_LOG(Log::LT_ERROR, 103, L"[job], invalid state", L", wid:%d", _wid);
        return false;
    }
    Character* const pc = _owner->getPlayingCharacter();
    if (pc == nullptr)
    {
        JOB_LOG(Log::LT_ERROR, 109, L"[job], owner has no playing pc", L", wid:%d", _wid);
        return false;
    }
    if (pc->_db.belongingWorld != _wid)
    {
        JOB_LOG(Log::LT_ERROR, 114, L"[job], not belonging world", L", pcid:0x%I64X, wid:%d", pc->_db.pcid, _wid);
        return false;
    }
    _owner->_state = 0x60000;
    JOB_LOG(Log::LT_DEBUG, 121, L"[job], init ok", L", pcid:0x%I64X, wid:%d", pc->_db.pcid, _wid);
    transit(1);
    return true;
}

// 0x5af30
bool LogoutInGameWorldJob::logout()
{
    Character* const pc = _owner->getPlayingCharacter();
    if (pc == nullptr)
    {
        JOB_CRASH(131, L"== CRASH == [job], pc disappear...");
        _owner->finalize();
        return false;
    }
    pc->EndGameWorldPlay();
    if (_owner->_srvloc != nullptr)
        _owner->_srvloc->OnLeave(_owner);
    JOB_LOG(Log::LT_DEBUG, 143, L"[job], logout ok", L", pcid:0x%I64X", pc->_db.pcid);
    _owner->finalize();
    transit(2);
    return true;
}
