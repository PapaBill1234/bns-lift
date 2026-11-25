// SecondPasswordIsVerifiedJob.obj (LobbyDaemon PDB, 2019 + PDB). Lifted from the pseudocode with PDB types.
#include <new>
#include <wchar.h>
#include <winsock2.h>
#include <windows.h>
#include "SecondPasswordIsVerifiedJob.h"
#include "CliSession.h"
#include "GamedChannel.h"
#include "LiftStub.h"
#include "LobbyDaemon.h"
#include "Log.h"
#include "Memory.h"
#include "MemoryManager.h"
#include "NPServiceChannel.h"

static wchar_t const kFile[] = L"SecondPasswordIsVerifiedJob.cpp";

// LIFT: PDB StsMsgLib::_StsMsgRequestSecondPasswordIsVerified (sizeof 0x28). The type is not in a LobbyDaemon header
// yet. The PDB _StsMsgResponseSecondPasswordIsVerified has no members (the job reads the _StsMsgResponse part only).
namespace StsMsgLib
{
struct _StsMsgRequestSecondPasswordIsVerified : public _StsMsgRequest
{
    id128* pUserId;
    int nType;
    unsigned int nActionIndex;
};
static_assert(sizeof(_StsMsgRequestSecondPasswordIsVerified) == 0x28, "sizeof _StsMsgRequestSecondPasswordIsVerified");
static_assert(offsetof(_StsMsgRequestSecondPasswordIsVerified, nActionIndex) == 0x24, "_StsMsgRequestSecondPasswordIsVerified::nActionIndex");
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
LobbyJobStateDef const StateDef[] = {{0, L"INIT"}, {1, L"IS_VERIFIED"}, {2, L"FIN"}};  // 0x12dd30
}

LobbyJobDef SecondPasswordIsVerifiedJob::_def = {30, StateDef, 2, L"SecondPasswordIsVerifiedJob"};  // 0x201a10
// LIFT: SecondPasswordIsVerifiedJob::_pool (0x204db0) has no definition. The LobbyDaemon ObjectPool module is not in
// lift_lobbydaemon (see CliSession.cpp).

// 0x72110
LobbyJobDef const* SecondPasswordIsVerifiedJob::GetDefinition() const
{
    return &_def;
}

// 0x72120
// LIFT: Not done. The body calls _pool.Checkin. ObjPool is not in lift_lobbydaemon.
void SecondPasswordIsVerifiedJob::deallocate_me(void*, wchar_t const*, int)
{
    LIFT_STUB(0x72120);
}

// 0x72170
// The original constructs a job on the stack (null owner) and returns its vfptr. It does not run the destructor.
void* SecondPasswordIsVerifiedJob::_vtbl()
{
    char buf[sizeof(SecondPasswordIsVerifiedJob)];
    SecondPasswordIsVerifiedJob* job = ::new (buf) SecondPasswordIsVerifiedJob(nullptr);
    return *reinterpret_cast<void**>(job);
}

// 0x721f0 (scalar deleting destructor)
SecondPasswordIsVerifiedJob::~SecondPasswordIsVerifiedJob()
{
    if (_gamed != nullptr)
        _gamed->removeReferenceCount(kFile, 67);
}

// 0x72240
bool SecondPasswordIsVerifiedJob::work(int task, void* param)
{
    bool result = false;
    if (_state == INIT && task == 130)
    {
        result = init(param);
        task = 0;
    }
    if (_state == IS_VERIFIED)
    {
        if (task == 0)
            return requestIsVerified();
        else if (task == 64)
            return responseIsVerified(param);
        else if (task == 65)
            return expireIsVerified();
    }
    return result;
}

// 0x722c0
bool SecondPasswordIsVerifiedJob::init(void* param)
{
    GameSecondPasswordIsVerifiedReqParam* const p = static_cast<GameSecondPasswordIsVerifiedReqParam*>(param);
    if (p == nullptr)
    {
        JOB_LOG(Log::LT_ERROR, 103, L"[job], null parameter", L"");
        return false;
    }
    if (p->gamed == nullptr)
    {
        JOB_LOG(Log::LT_ERROR, 111, L"[job], invalid gamed channel parameter", L"");
        return false;
    }
    _gamed = p->gamed;
    _gametid = p->gametid;
    _pcid = p->pcid;
    _type = p->type;
    _actionIndex = p->actionIndex;
    if (_gamed != nullptr)
        _gamed->addReferenceCount(false, kFile, 122);
    if (_owner->_state != 0x40000)  // CSS_GAME_WORLD
    {
        JOB_LOG(Log::LT_ERROR, 129, L"[job], cli-session not in game-world",
                L", wid:%d, game-tid:0x%I64X, pcid:0x%I64X, 2ndpwd-type:%d, 2ndpwd-action-index:%d",
                _gamed != nullptr ? (_gamed->_rawChannel != nullptr ? static_cast<short>(_gamed->_rawChannel->GetId()) : 0) : 0,
                _gametid, _pcid, _type, _actionIndex);
        // The original sends the get-status fail packet here.
        _gamed->SendSecondPasswordGetStatusFail(_gametid, _pcid, 6);
        return false;
    }
    JOB_LOG(Log::LT_DEBUG, 134, L"[job], init ok",
            L", wid:%d, game-tid:0x%I64X, pcid:0x%I64X, 2ndpwd-type:%d, 2ndpwd-action-index:%d",
            _gamed != nullptr ? (_gamed->_rawChannel != nullptr ? static_cast<short>(_gamed->_rawChannel->GetId()) : 0) : 0,
            _gametid, _pcid, _type, _actionIndex);
    transit(IS_VERIFIED);
    return true;
}

// 0x72640
bool SecondPasswordIsVerifiedJob::requestIsVerified()
{
    NPGameServiceChannel* const gameServChannel = LobbyDaemon::_instance->_npServchmgr->_gameServChannel;
    NPLobbyJobTransaction* const tran =
        new (Memory::_Manager[2]->Alloc(sizeof(NPLobbyJobTransaction), kFile, 146)) NPLobbyJobTransaction;
    if (gameServChannel != nullptr)
    {
        tran->Set(this, 65);
        StsMsgLib::_StsMsgRequestSecondPasswordIsVerified msg;
        msg.msgInfo.eCmd = StsMsgLib::COMMAND_SRV_SECONDPWD_IS_VERIFIED;
        msg.msgInfo.msgType = StsMsgLib::MESSAGE_TYPE_REQUEST;
        msg.msgInfo.nTxnId = 0;
        msg.pUserId = &_owner->_acb._userid;
        msg.nType = _type;
        msg.nActionIndex = _actionIndex;
        if (gameServChannel->SendMsg(&msg, true, tran))
        {
            JOB_LOG(Log::LT_DEBUG, 156, L"[job], req sent", L"");
            return true;
        }
    }
    JOB_LOG(Log::LT_ERROR, 150, L"[job], np not available", L"");
    _gamed->SendSecondPasswordIsVerifiedFail(_gametid, _pcid, 7);
    if (tran != nullptr)
        tran->~NPLobbyJobTransaction();
    Memory::_Manager[2]->Free(tran, kFile, 152);
    return false;
}

// 0x728d0
bool SecondPasswordIsVerifiedJob::responseIsVerified(void* param)
{
    StsMsgLib::_StsMsgResponse* const res = static_cast<StsMsgLib::_StsMsgResponse*>(param);
    if (res == nullptr)
    {
        JOB_LOG(Log::LT_ERROR, 164, L"[job], null param", L"");
        _gamed->SendSecondPasswordIsVerifiedFail(_gametid, _pcid, 2);
        return false;
    }
    JOB_LOG(Log::LT_DEBUG, 170, L"[job], recv resposne is-verified",
            L", np-tid:%u, cmd:%d, type:%d, status-code:%u, reason:%s, error-code:%d", res->GetTransactionId(),
            res->GetCommand(), res->GetMessageType(), res->msgInfo.errInfo.nStatusCode,
            res->msgInfo.errInfo.pwszReason != nullptr ? res->msgInfo.errInfo.pwszReason : L"null",
            res->msgInfo.errInfo.nErrorCode);
    unsigned int const statusCode = res->msgInfo.errInfo.nStatusCode;
    if (statusCode == 200 ||
        (statusCode == 400 &&
         _wcsicmp(L"Success", res->msgInfo.errInfo.pwszReason != nullptr ? res->msgInfo.errInfo.pwszReason : L"null") == 0))
    {
        _gamed->SendSecondPasswordIsVerifiedOk(_gametid, _pcid);
        transit(FIN);
        return true;
    }
    short reason = 1;
    switch (res->msgInfo.errInfo.nErrorCode)
    {
    case 0xD05:
        reason = 68;
        break;
    case 0xD06:
        reason = 69;
        break;
    case 0xD11:
        reason = 70;
        break;
    case 0xD12:
        reason = 71;
        break;
    }
    _gamed->SendSecondPasswordIsVerifiedFail(_gametid, _pcid, reason);
    transit(FIN);
    return true;
}

// 0x72bf0
bool SecondPasswordIsVerifiedJob::expireIsVerified()
{
    JOB_LOG(Log::LT_ERROR, 207, L"[job], expired", L"");
    _gamed->SendSecondPasswordIsVerifiedFail(_gametid, _pcid, 7);
    transit(FIN);
    return true;
}

// LIFT: SecondPasswordIsVerifiedJob::_pool (.data RVA 0x204db0). Dynamic initializer 0x11e250, atexit destructor 0x11efc0. The original static data
// holds id 1, objsize sizeof(SecondPasswordIsVerifiedJob) and desc L"SecondPasswordIsVerifiedJob".
#include "ObjectPool.h"
ObjPool SecondPasswordIsVerifiedJob::_pool(1, sizeof(SecondPasswordIsVerifiedJob), L"SecondPasswordIsVerifiedJob");
