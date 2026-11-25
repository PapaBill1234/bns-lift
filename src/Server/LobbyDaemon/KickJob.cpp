// KickJob.obj (LobbyDaemon PDB, 2019 + PDB). Lifted from the pseudocode with PDB types.
#include <new>
#include <winsock2.h>
#include <windows.h>
#include "KickJob.h"
#include "AlertSender.h"
#include "Character.h"
#include "CliSession.h"
#include "GamedChannel.h"
#include "LiftStub.h"
#include "LobbyDaemon.h"
#include "LobbyPredefine.h"
#include "Log.h"
#include "ManageChannel.h"
#include "Memory.h"
#include "MemoryManager.h"
#include "NPServiceChannel.h"
#include "Session.h"
#include "TransactionChannel.h"

static wchar_t const kFile[] = L"KickJob.cpp";

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
LobbyJobStateDef const StateDef[] = {{0, L"INIT"},           {1, L"KICK"},     {2, L"WORLD_KICK"},
                                     {3, L"FIN_CLISESSION"}, {4, L"KICK_ACK"}, {5, L"FIN"}};  // 0x12dab0
}

LobbyJobDef KickJob::_def = {4, StateDef, 5, L"KickJob"};  // 0x2018f0
// LIFT: KickJob::_pool has no definition. The LobbyDaemon ObjectPool module is not in lift_lobbydaemon
// (see CliSession.cpp).

// 0x861a0
LobbyJobDef const* KickJob::GetDefinition() const
{
    return &_def;
}

// 0x861b0
// LIFT: Not done. The body calls _pool.Checkin. ObjPool is not in lift_lobbydaemon.
void KickJob::deallocate_me(void*, wchar_t const*, int)
{
    LIFT_STUB(0x861b0);
}

// 0x86200
// The original constructs a job on the stack (null owner) and returns its vfptr. It does not run the destructor.
void* KickJob::_vtbl()
{
    char buf[sizeof(KickJob)];
    KickJob* job = ::new (buf) KickJob(nullptr, 0, nullptr);
    return *reinterpret_cast<void**>(job);
}

// 0x86280
KickJob::KickJob(CliSession* owner, int kickReason, Demander* demander)
    : CliSessionJob(owner), _last(0), _result(0), _kickReason(kickReason), _demander(demander), _tran(nullptr),
      _gamed(nullptr)
{
}

// 0x862f0
KickJob::~KickJob()
{
    if (_tran != nullptr)
    {
        _tran->removeReferenceCount(kFile, 86);
        _tran = nullptr;
    }
    if (_demander != nullptr)
    {
        delete _demander;
        Memory::_Manager[2]->Free(_demander, kFile, 90);
        _demander = nullptr;
    }
}

// 0x86380
bool KickJob::work(int task, void* param)
{
    bool result = false;
    if (_state == INIT && task == 1)
        result = init(1, param);
    if (_state == KICK && task == 0)
        result = kick();
    if (_state == WORLD_KICK)
    {
        switch (task)
        {
        case 0:
            result = worldKickReq();
            break;
        case 'r':
            result = worldKickOk();
            break;
        case 's':
            result = worldKickFail(*static_cast<short*>(param));
            break;
        case 't':
            result = worldKickExpire();
            break;
        }
    }
    if (_state == FIN_CLISESSION && task == 0)
    {
        _owner->finalize();
        transit(KICK_ACK);
        result = true;
    }
    if (_state == KICK_ACK && task == 0)
    {
        if (_demander != nullptr)
            _demander->Response(_result);
        transit(FIN);
        return true;
    }
    return result;
}

// 0x86460
bool KickJob::init(int, void*)
{
    int state = _owner->_state;
    if (state == 0x60000)
    {
        JOB_LOG(Log::LT_ERROR, 139, L"[job], already fin", L"");
        _result = KR_ALREADY_FIN;
        transit(KICK_ACK);
        return false;
    }
    _last = state;
    _owner->_state = 0x60000;
    JOB_LOG(Log::LT_DEBUG, 149, L"[job], init ok", L", last-cli-state:%d.%d, kick-reason:%d", HIWORD(_last), LOWORD(_last),
            _kickReason);
    transit(KICK);
    return true;
}

// 0x865e0
// A failed presence check logs a CRASH. The job then does the action all the same.
bool KickJob::kick()
{
    CliSession* owner = _owner;
    Presence* p = owner->_presence;
    switch (_last)
    {
    case 0x10001:
        JOB_LOG(Log::LT_ERROR, 162, L"[job], invalid state", L"");
        if (p == nullptr || p->GetKind() != Presence::AnonymousLobbyGate)
            JOB_CRASH(166, L"== CRASH == [job], invalid presence");
        owner->closePresence();
        break;
    case 0x10002:
        if (p == nullptr || p->GetKind() != Presence::LobbyGate)
            JOB_CRASH(177, L"== CRASH == [job], invalid presence");
        owner->kickPresence(_kickReason);
        break;
    case 0x10003:
    case 0x20000:
    case 0x30001:
        if (p == nullptr || p->GetKind() != Presence::LobbyGate)
            JOB_CRASH(190, L"== CRASH == [job], invalid presence");
        owner->kickPresence(_kickReason);
        break;
    case 0x30002:
        if (p == nullptr || p->GetKind() != Presence::LobbyGate)
            JOB_CRASH(201, L"== CRASH == [job], invalid presence");
        owner->leave();
        owner->kickPresence(_kickReason);
        break;
    case 0x30003:
        if (p == nullptr || p->GetKind() != Presence::LobbyGate)
            JOB_CRASH(213, L"== CRASH == [job], invalid presence");
        owner->closePresence();
        break;
    case 0x40000:
    {
        Character* pc = owner->getPlayingCharacter();
        if (pc != nullptr)
            pc->EndGameWorldPlay();
        transit(WORLD_KICK);
        return true;
    }
    case 0x50001:
        if (p == nullptr || p->GetKind() != Presence::GameWorld)
            JOB_CRASH(233, L"== CRASH == [job], invalid presence");
        owner->closePresence();
        break;
    case 0x50002:
        if (p == nullptr || p->GetKind() != Presence::AnonymousLobbyGate)
            JOB_CRASH(244, L"== CRASH == [job], invalid presence");
        owner->closePresence();
        break;
    case 0x50003:
        if (p == nullptr || p->GetKind() != Presence::LobbyGate)
            JOB_CRASH(255, L"== CRASH == [job], invalid presence");
        owner->kickPresence(_kickReason);
        break;
    default:
        JOB_LOG(Log::LT_ERROR, 263, L"== CRASH == [job], unknown state", L", cli-state:%d.%d", HIWORD(_last),
                LOWORD(_last));
        AlertSender::Write(kFile, 263,
                           L"== CRASH == [job], unknown state, tid:0x%I64X, type:%d, state:%d, cli-key:0x%I64X, "
                           L"cli-state:%d.%d, cli-state:%d.%d",
                           this != nullptr ? _id : 0, this != nullptr ? GetDefinition()->type : -1,
                           this != nullptr ? _state : -1,
                           this != nullptr && _owner != nullptr ? _owner->_clikey : 0,
                           HIWORD(this != nullptr && _owner != nullptr ? _owner->_state : 0),
                           LOWORD(this != nullptr && _owner != nullptr ? _owner->_state : 0), HIWORD(_last),
                           LOWORD(_last));
        _result = KR_SYSTEM_ERROR;
        transit(FIN_CLISESSION);
        return true;
    }
    _result = KR_OK;
    transit(FIN_CLISESSION);
    return true;
}

// 0x87010
bool KickJob::worldKickReq()
{
    CliSession* owner = _owner;
    Presence* p = owner->_presence;
    if (p == nullptr || p->GetKind() != Presence::GameWorld)
    {
        JOB_CRASH(278, L"== CRASH == [job], invalid presence");
    }
    else
    {
        GameWorldPresence* gw = static_cast<GameWorldPresence*>(p);
        short wid = gw->_wid;
        unsigned long long pcid = gw->_pcid;
        unsigned long long gamekey = gw->_gamekey;
        // LIFT: the original calls OnLeave (vtable +0x28) and does not set the second argument. The PDB signature
        // takes the owner, so the lift passes it.
        if (_owner->_srvloc != nullptr)
            _owner->_srvloc->OnLeave(_owner);
        _gamed = LobbyDaemon::_instance->_gamedchmgr->Acquire(wid);
        if (_gamed != nullptr)
        {
            _tran = new (Memory::_Manager[2]->Alloc(sizeof(LobbyJobTransaction), kFile, 302)) LobbyJobTransaction;
            _gamed->SendKickReq(_tran->Set(this, 116), pcid, owner->_clikey, gamekey,
                                GetGameWorldKickReason(_kickReason));
            return true;
        }
        JOB_LOG(Log::LT_ERROR, 296, L"[job], world not available", L"");
    }
    _result = KR_OK;
    transit(FIN_CLISESSION);
    return true;
}

// 0x872e0
bool KickJob::worldKickOk()
{
    JOB_LOG(Log::LT_DEBUG, 310, L"[job], world kick ok recv", L"");
    _gamed->TRecv(_tran);
    _result = KR_OK;
    transit(FIN_CLISESSION);
    return true;
}

// 0x87420
bool KickJob::worldKickFail(short reason)
{
    JOB_LOG(Log::LT_DEBUG, 321, L"[job], world kick fail recv", L", reason:%d", reason);
    _gamed->TRecv(_tran);
    _result = (reason != 24) + 1;
    transit(FIN_CLISESSION);
    return true;
}

// 0x87580
bool KickJob::worldKickExpire()
{
    JOB_LOG(Log::LT_DEBUG, 340, L"[job], world kick expired", L"");
    _result = KR_SYSTEM_ERROR;
    transit(FIN_CLISESSION);
    return true;
}

// 0x87670 (scalar deleting destructor)
NPDemander::~NPDemander()
{
    if (_channel != nullptr)
        _channel->removeReferenceCount(kFile, 380);
}

// 0x876c0
// LIFT: NPGameServiceChannel::SendResponseGateLogoutUser is still a stub (gap-04).
void NPDemander::Response(int kickResult)
{
    if (_channel != nullptr)
    {
        if (kickResult == KickJob::KR_OK)
            _channel->SendResponseGateLogoutUser(_txnid, 0);
        else
            _channel->SendResponseGateLogoutUser(_txnid, 2);
    }
}

// 0x87700 (scalar deleting destructor)
ManageDemander::~ManageDemander()
{
    if (_session != nullptr)
        const_cast<Session*>(_session)->removeReferenceCount(kFile, 420);
}

// 0x87750
// LIFT: ManageChannel::SendKickOk and SendKickFail are still stubs (gap-23 backlog).
void ManageDemander::Response(int kickResult)
{
    if (_session != nullptr)
    {
        if (kickResult == KickJob::KR_OK)
        {
            ManageChannel::SendKickOk(_session, _tid);
        }
        else
        {
            short code = 1;
            if (kickResult == KickJob::KR_SYSTEM_ERROR)
                code = 2;
            else if (kickResult == KickJob::KR_ALREADY_FIN)
                code = 8;
            ManageChannel::SendKickFail(_session, _tid, code);
        }
    }
}
