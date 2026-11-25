// SecondPasswordGetStatusJob.obj (LobbyDaemon PDB, 2019 + PDB). Lifted from the pseudocode with PDB types.
#include <new>
#include <wchar.h>
#include <winsock2.h>
#include <windows.h>
#include "SecondPasswordGetStatusJob.h"
#include "CliSession.h"
#include "GamedChannel.h"
#include "LiftStub.h"
#include "LobbyDaemon.h"
#include "Log.h"
#include "Memory.h"
#include "MemoryManager.h"
#include "NPServiceChannel.h"

static wchar_t const kFile[] = L"SecondPasswordGetStatusJob.cpp";

// LIFT: PDB StsMsgLib::_StsMsgRequestSecondPasswordGetStatus (sizeof 0x28) and _StsMsgResponseSecondPasswordGetStatus
// (sizeof 0x88). The types are not in a LobbyDaemon header yet.
namespace StsMsgLib
{
struct _StsMsgRequestSecondPasswordGetStatus : public _StsMsgRequest
{
    id128* pUserId;
    int nType;
};
static_assert(sizeof(_StsMsgRequestSecondPasswordGetStatus) == 0x28, "sizeof _StsMsgRequestSecondPasswordGetStatus");
static_assert(offsetof(_StsMsgRequestSecondPasswordGetStatus, nType) == 0x20, "_StsMsgRequestSecondPasswordGetStatus::nType");

struct _StsMsgResponseSecondPasswordGetStatus : public _StsMsgResponse
{
    enum EBlockStatus : int
    {
        EBLOCKSTATUS_NOT_BLOCKED = 0x0,
        EBLOCKSTATUS_BLOCKED = 0x1,
    };
    EBlockStatus eBlockStatus;
    unsigned int nAuthFailLimitCount;
    unsigned int nAuthFailCount;
    long long tBlockedUntil;
    long long tDeleteAt;
    unsigned long long nActionMask;
};
static_assert(sizeof(_StsMsgResponseSecondPasswordGetStatus) == 0x88, "sizeof _StsMsgResponseSecondPasswordGetStatus");
static_assert(offsetof(_StsMsgResponseSecondPasswordGetStatus, eBlockStatus) == 0x60, "_StsMsgResponseSecondPasswordGetStatus::eBlockStatus");
static_assert(offsetof(_StsMsgResponseSecondPasswordGetStatus, tBlockedUntil) == 0x70, "_StsMsgResponseSecondPasswordGetStatus::tBlockedUntil");
}  // namespace StsMsgLib

// The log suffix of all LobbyJob logs. The original reads the owner state 2 times (HIWORD and LOWORD).
#define JOB_LOG(logType, line, msg, fmt, ...)                                                                          \
    Log::Write(logType, kFile, line, msg L", tid:0x%I64X, type:%d, state:%d, cli-key:0x%I64X, cli-state:%d.%d" fmt,   \
               this != nullptr ? _id : 0, this != nullptr ? GetDefinition()->type : -1,                            \
               this != nullptr ? _state : -1, this != nullptr && _owner != nullptr ? _owner->_clikey : 0,          \
               HIWORD(this != nullptr && _owner != nullptr ? _owner->_state : 0),                                  \
               LOWORD(this != nullptr && _owner != nullptr ? _owner->_state : 0), ##__VA_ARGS__)

namespace
{
LobbyJobStateDef const StateDef[] = {{0, L"INIT"}, {1, L"GET_STATUS"}, {2, L"FIN"}};  // 0x12dd60
}

LobbyJobDef SecondPasswordGetStatusJob::_def = {29, StateDef, 2, L"SecondPasswordGetStatusJob"};  // 0x201a30
// LIFT: SecondPasswordGetStatusJob::_pool (0x204d00) has no definition. The LobbyDaemon ObjectPool module is not in
// lift_lobbydaemon (see CliSession.cpp).

// 0x71550
LobbyJobDef const* SecondPasswordGetStatusJob::GetDefinition() const
{
    return &_def;
}

// 0x71560
// LIFT: Not done. The body calls _pool.Checkin. ObjPool is not in lift_lobbydaemon.
void SecondPasswordGetStatusJob::deallocate_me(void*, wchar_t const*, int)
{
    LIFT_STUB(0x71560);
}

// 0x715b0
// The original constructs a job on the stack (null owner) and returns its vfptr. It does not run the destructor.
void* SecondPasswordGetStatusJob::_vtbl()
{
    char buf[sizeof(SecondPasswordGetStatusJob)];
    SecondPasswordGetStatusJob* job = ::new (buf) SecondPasswordGetStatusJob(nullptr);
    return *reinterpret_cast<void**>(job);
}

// 0x71630 (scalar deleting destructor)
SecondPasswordGetStatusJob::~SecondPasswordGetStatusJob()
{
    if (_gamed != nullptr)
        _gamed->removeReferenceCount(kFile, 66);
}

// 0x71680
bool SecondPasswordGetStatusJob::work(int task, void* param)
{
    bool result = false;
    if (_state == INIT && task == 129)
    {
        result = init(param);
        task = 0;
    }
    if (_state == GET_STATUS)
    {
        if (task == 0)
            return requestGetStatus();
        else if (task == 62)
            return responseGetStatus(param);
        else if (task == 63)
            return expireGetStatus();
    }
    return result;
}

// 0x71700
bool SecondPasswordGetStatusJob::init(void* param)
{
    GameSecondPasswordGetStatusReqParam* const p = static_cast<GameSecondPasswordGetStatusReqParam*>(param);
    if (p == nullptr)
    {
        JOB_LOG(Log::LT_ERROR, 102, L"[job], null parameter", L"");
        return false;
    }
    if (p->gamed == nullptr)
    {
        JOB_LOG(Log::LT_ERROR, 110, L"[job], invalid gamed channel parameter", L"");
        return false;
    }
    _gamed = p->gamed;
    _gametid = p->gametid;
    _pcid = p->pcid;
    _type = p->type;
    if (_gamed != nullptr)
        _gamed->addReferenceCount(false, kFile, 120);
    if (_owner->_state != 0x40000)  // CSS_GAME_WORLD
    {
        JOB_LOG(Log::LT_ERROR, 127, L"[job], cli-session not in game-world",
                L", wid:%d, game-tid:0x%I64X, pcid:0x%I64X, 2ndpwd-type:%d",
                _gamed != nullptr ? (_gamed->_rawChannel != nullptr ? static_cast<short>(_gamed->_rawChannel->GetId()) : 0) : 0,
                _gametid, _pcid, _type);
        _gamed->SendSecondPasswordGetStatusFail(_gametid, _pcid, 6);
        return false;
    }
    JOB_LOG(Log::LT_DEBUG, 132, L"[job], init ok", L", wid:%d, game-tid:0x%I64X, pcid:0x%I64X, 2ndpwd-type:%d",
            _gamed != nullptr ? (_gamed->_rawChannel != nullptr ? static_cast<short>(_gamed->_rawChannel->GetId()) : 0) : 0,
            _gametid, _pcid, _type);
    transit(GET_STATUS);
    return true;
}

// 0x71a60
bool SecondPasswordGetStatusJob::requestGetStatus()
{
    NPGameServiceChannel* const gameServChannel = LobbyDaemon::_instance->_npServchmgr->_gameServChannel;
    NPLobbyJobTransaction* const tran =
        new (Memory::_Manager[2]->Alloc(sizeof(NPLobbyJobTransaction), kFile, 144)) NPLobbyJobTransaction;
    if (gameServChannel != nullptr)
    {
        tran->Set(this, 63);
        StsMsgLib::_StsMsgRequestSecondPasswordGetStatus msg;
        msg.msgInfo.eCmd = StsMsgLib::COMMAND_COMMON_SECONDPWD_GET_STATUS;
        msg.msgInfo.msgType = StsMsgLib::MESSAGE_TYPE_REQUEST;
        msg.msgInfo.nTxnId = 0;
        msg.pUserId = &_owner->_acb._userid;
        msg.nType = _type;
        if (gameServChannel->SendMsg(&msg, true, tran))
        {
            JOB_LOG(Log::LT_DEBUG, 154, L"[job], req sent", L"");
            return true;
        }
    }
    JOB_LOG(Log::LT_ERROR, 148, L"[job], np not available", L"");
    _gamed->SendSecondPasswordGetStatusFail(_gametid, _pcid, 7);
    if (tran != nullptr)
        tran->~NPLobbyJobTransaction();
    Memory::_Manager[2]->Free(tran, kFile, 150);
    return false;
}

// 0x71ce0
bool SecondPasswordGetStatusJob::responseGetStatus(void* param)
{
    StsMsgLib::_StsMsgResponseSecondPasswordGetStatus* const res =
        static_cast<StsMsgLib::_StsMsgResponseSecondPasswordGetStatus*>(param);
    if (res == nullptr)
    {
        JOB_LOG(Log::LT_ERROR, 162, L"[job], null param", L"");
        _gamed->SendSecondPasswordGetStatusFail(_gametid, _pcid, 2);
        return false;
    }
    JOB_LOG(Log::LT_DEBUG, 168, L"[job], recv resposne get-status",
            L", np-tid:%u, cmd:%d, type:%d, status-code:%u, reason:%s, error-code:%d", res->GetTransactionId(),
            res->GetCommand(), res->GetMessageType(), res->msgInfo.errInfo.nStatusCode,
            res->msgInfo.errInfo.pwszReason != nullptr ? res->msgInfo.errInfo.pwszReason : L"null",
            res->msgInfo.errInfo.nErrorCode);
    unsigned int const statusCode = res->msgInfo.errInfo.nStatusCode;
    if (statusCode == 200 ||
        (statusCode == 400 &&
         _wcsicmp(L"Success", res->msgInfo.errInfo.pwszReason != nullptr ? res->msgInfo.errInfo.pwszReason : L"null") == 0))
    {
        _gamed->SendSecondPasswordGetStatusOk(_gametid, _pcid,
                                              res->eBlockStatus == StsMsgLib::_StsMsgResponseSecondPasswordGetStatus::EBLOCKSTATUS_BLOCKED,
                                              res->nAuthFailLimitCount, res->nAuthFailCount, res->tBlockedUntil,
                                              res->tDeleteAt, res->nActionMask);
        transit(FIN);
        return true;
    }
    short reason = 1;
    if (res->msgInfo.errInfo.nErrorCode == 3333)
        reason = 67;
    _gamed->SendSecondPasswordGetStatusFail(_gametid, _pcid, reason);
    transit(FIN);
    return true;
}

// 0x72010
bool SecondPasswordGetStatusJob::expireGetStatus()
{
    JOB_LOG(Log::LT_ERROR, 213, L"[job], expired", L"");
    _gamed->SendSecondPasswordGetStatusFail(_gametid, _pcid, 7);
    transit(FIN);
    return true;
}

// LIFT: SecondPasswordGetStatusJob::_pool (.data RVA 0x204d00). Dynamic initializer 0x11e200, atexit destructor 0x11ef80. The original static data
// holds id 1, objsize sizeof(SecondPasswordGetStatusJob) and desc L"SecondPasswordGetStatusJob".
#include "ObjectPool.h"
ObjPool SecondPasswordGetStatusJob::_pool(1, sizeof(SecondPasswordGetStatusJob), L"SecondPasswordGetStatusJob");
