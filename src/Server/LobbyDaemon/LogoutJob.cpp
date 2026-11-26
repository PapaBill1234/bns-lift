// LogoutJob.obj (LobbyDaemon PDB, 2019 + PDB). Lifted from the pseudocode with PDB types.
#include <new>
#include <winsock2.h>
#include <windows.h>
#include "LogoutJob.h"
#include "AlertSender.h"
#include "CliSession.h"
#include "LiftStub.h"
#include "LobbyGateChannel.h"
#include "Log.h"

static wchar_t const kFile[] = L"LogoutJob.cpp";

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
LobbyJobStateDef const StateDef[] = {{0, L"INIT"}, {1, L"LOGOUT"}, {2, L"FIN"}};  // 0x12da50
}

LobbyJobDef LogoutJob::_def = {3, StateDef, 2, L"LogoutJob"};  // 0x2017d0

#include "ObjectPoolLobbyDaemon.h"

// .data 0x205540, dynamic init 0x11e5c0, atexit dtor 0x11f280.
// The exe .data holds id 1, objsize 0x70, desc L"LogoutJob".
ObjPool LogoutJob::_pool(1, 0x70, L"LogoutJob");

// 0x97a10
LobbyJobDef const* LogoutJob::GetDefinition() const
{
    return &_def;
}

// 0x97a20
// LIFT: Not done. The body calls _pool.Checkin. ObjPool is not in lift_lobbydaemon.
void LogoutJob::deallocate_me(void*, wchar_t const*, int)
{
    LIFT_STUB(0x97a20);
}

// 0x97a70
// The original constructs a job on the stack (null owner) and returns its vfptr. It does not run the destructor.
void* LogoutJob::_vtbl()
{
    char buf[sizeof(LogoutJob)];
    LogoutJob* job = ::new (buf) LogoutJob(nullptr, nullptr, false);
    return *reinterpret_cast<void**>(job);
}

// 0x97af0
LogoutJob::LogoutJob(CliSession* owner, LobbyGateChannel* lgate, bool close) : CliSessionJob(owner), _lgate(lgate), _close(close)
{
    if (lgate != nullptr)
        lgate->addReferenceCount(false, kFile, 59);
}

// 0x97b60 (scalar deleting destructor)
LogoutJob::~LogoutJob()
{
    if (_lgate != nullptr)
        _lgate->removeReferenceCount(kFile, 65);
}

// 0x97bb0
bool LogoutJob::work(int task, void* param)
{
    bool result = false;
    if (_state == INIT && task == 9)
    {
        result = init(9, param);
        task = 0;
    }
    if (_state == LOGOUT && task == 0)
        return logout();
    return result;
}

// 0x97bf0
bool LogoutJob::init(int, void*)
{
    _last = _owner->_state;
    int next;
    if (_last == 0x60000)
    {
        JOB_LOG(Log::LT_ERROR, 94, L"[job], already fin", L"");
        next = FIN;
    }
    else
    {
        JOB_LOG(Log::LT_DEBUG, 99, L"[job], init ok", L"");
        next = LOGOUT;
    }
    transit(next);
    return true;
}

// 0x97d30
bool LogoutJob::logout()
{
    JOB_LOG(Log::LT_DEBUG, 107, L"[job], process logout", L"");
    switch (_last)
    {
    case 0x10001:
    case 0x50002:
        if (_close)
            _owner->closePresence();
        _owner->_state = 0x60000;
        _owner->finalize();
        break;
    case 0x10002:
    case 0x10003:
    case 0x20000:
    case 0x30001:
    case 0x50003:
        _owner->_state = 0x60000;
        _owner->finalize();
        if (_lgate != nullptr && _close)
            _lgate->SendCloseSessionNotify(_owner->_clikey);
        break;
    case 0x30002:
        _owner->_state = 0x60000;
        _owner->leave();
        _owner->finalize();
        if (_lgate != nullptr && _close)
            _lgate->SendCloseSessionNotify(_owner->_clikey);
        break;
    case 0x40000:
    case 0x50001:
        JOB_LOG(Log::LT_ERROR, 163, L"[job], invalid state", L"");
        break;
    case 0x30003:
        JOB_LOG(Log::LT_DEBUG, 155, L"[job], absorb logout by L2W_ok state", L"");
        if (_lgate != nullptr && _close)
            _lgate->SendCloseSessionNotify(_owner->_clikey);
        break;
    default:
        JOB_CRASH(184, L"== CRASH == [job], unknown state");
        break;
    }
    transit(FIN);
    return true;
}
