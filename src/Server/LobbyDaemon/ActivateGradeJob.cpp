// ActivateGradeJob.obj (LobbyDaemon PDB, 2019 + PDB). Lifted from the pseudocode with PDB types.
#include <new>
#include <stdlib.h>
#include <wchar.h>
#include <winsock2.h>
#include <windows.h>
#include "ActivateGradeJob.h"
#include "AlertSender.h"
#include "CliSession.h"
#include "GamedChannel.h"
#include "LiftStub.h"
#include "LobbyConfig.h"
#include "LobbyDaemon.h"
#include "LobbyGateChannel.h"
#include "Log.h"
#include "Memory.h"
#include "MemoryManager.h"
#include "NPServiceChannel.h"

static wchar_t const kFile[] = L"ActivateGradeJob.cpp";

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

namespace StsMsgLib
{
// PDB StsMsgLib::_StsMsgResponseGradeActivateGrade (sizeof 0x108).
struct _StsMsgResponseGradeActivateGrade : public _StsMsgResponse
{
    GUID UserId;
    int nGradeId;
    wchar_t AppGroupCode[9];
    wchar_t GameGradeKey[51];
    long long tEffectiveFrom;
    long long tEffectiveTo;
    int nRemainingGradeTimePerSeconds;
};
static_assert(sizeof(_StsMsgResponseGradeActivateGrade) == 0x108, "sizeof StsMsgLib::_StsMsgResponseGradeActivateGrade");
static_assert(offsetof(_StsMsgResponseGradeActivateGrade, nGradeId) == 0x70, "_StsMsgResponseGradeActivateGrade::nGradeId");
static_assert(offsetof(_StsMsgResponseGradeActivateGrade, GameGradeKey) == 0x86, "_StsMsgResponseGradeActivateGrade::GameGradeKey");
static_assert(offsetof(_StsMsgResponseGradeActivateGrade, tEffectiveFrom) == 0xF0, "_StsMsgResponseGradeActivateGrade::tEffectiveFrom");
}  // namespace StsMsgLib

namespace
{
LobbyJobStateDef const StateDef[] = {{0, L"INIT"}, {1, L"ACTIVATE_GRADE"}, {2, L"FIN"}};  // 0x12e580
}

LobbyJobDef ActivateGradeJob::_def = {32, StateDef, 2, L"ActivateGradeJob"};  // 0x2020c0
// LIFT: ActivateGradeJob::_pool (0x203860: id 1, size 0x80) has no definition. The LobbyDaemon ObjectPool module is
// not in lift_lobbydaemon (see CliSession.cpp).

// 0xbac0
LobbyJobDef const* ActivateGradeJob::GetDefinition() const
{
    return &_def;
}

// 0xbad0
// LIFT: Not done. The body calls _pool.Checkin. ObjPool is not in lift_lobbydaemon.
void ActivateGradeJob::deallocate_me(void*, wchar_t const*, int)
{
    LIFT_STUB(0xbad0);
}

// 0xbb20
// The original constructs a job on the stack (null owner) and returns its vfptr. It does not run the destructor.
void* ActivateGradeJob::_vtbl()
{
    char buf[sizeof(ActivateGradeJob)];
    ActivateGradeJob* job = ::new (buf) ActivateGradeJob(nullptr);
    return *reinterpret_cast<void**>(job);
}

// 0xbba0
ActivateGradeJob::ActivateGradeJob(CliSession* owner)
    : CliSessionJob(owner), _lgate(nullptr), _gamed(nullptr), _gameTid(0), _pcid(0), _gameGradeKey(0), _gradeId(0)
{
}

// 0xbc00
ActivateGradeJob::~ActivateGradeJob()
{
    if (_lgate != nullptr)
        _lgate->removeReferenceCount(kFile, 71);
    if (_gamed != nullptr)
        _gamed->removeReferenceCount(kFile, 73);
}

// 0xbc70
bool ActivateGradeJob::work(int task, void* param)
{
    bool result = false;
    if (_state == INIT)
    {
        if (task == 28)
        {
            result = initFromLobbyGate(static_cast<LobbyGate_ActivateGradeReqParam*>(param));
            task = 0;
        }
        else if (task == 134)
        {
            result = initFromGame(static_cast<Game_ActivateGradeReqParam*>(param));
            task = 0;
        }
    }
    if (_state == ACTIVATE_GRADE)
    {
        if (task == 0)
            return activateGradeReq();
        else if (task == 80)
            return activateGradeResponse(param);
        else if (task == 81)
            return activateGradeExpire();
    }
    return result;
}

// 0xbd00
bool ActivateGradeJob::initFromLobbyGate(LobbyGate_ActivateGradeReqParam* param)
{
    if (param == nullptr || param->lgate == nullptr)
    {
        JOB_CRASH(112, L"== CRASH == [job], init from lobby-gate fail; invalid param");
        return false;
    }
    _lgate = param->lgate;
    _gameGradeKey = param->gameGradeKey;
    _gradeId = param->gradeId;
    if (_lgate != nullptr)
        _lgate->addReferenceCount(false, kFile, 121);
    if (_owner->_state != 0x20000)
    {
        JOB_LOG(Log::LT_ERROR, 124, L"[job], init from lobby-gate fail; cli-session not in lobby", L"");
        sendFail(ERR_INVALID_SESSION_STATE);
        return false;
    }
    if (!LobbyDaemon::_instance->_config->_useGrade)
    {
        JOB_LOG(Log::LT_ERROR, 130, L"[job], grade service not enabled", L"");
        sendFail(ERR_SYSTEM_ERROR);
        return false;
    }
    JOB_LOG(Log::LT_DEBUG, 135, L"[job], init from lobby-gate ok", L", wid:%d, , game-grade-key:%d, grade-id:%d",
            _lgate != nullptr ? _lgate->GetWid() : 0, _gameGradeKey, _gradeId);
    transit(ACTIVATE_GRADE);
    return true;
}

// 0xc1a0
bool ActivateGradeJob::initFromGame(Game_ActivateGradeReqParam* param)
{
    if (param == nullptr || param->gamed == nullptr)
    {
        JOB_CRASH(144, L"== CRASH == [job], init from game fail; invalid param");
        return false;
    }
    _gamed = param->gamed;
    _gameTid = param->gameTid;
    _pcid = param->pcid;
    _gameGradeKey = param->gameGradeKey;
    _gradeId = param->gradeId;
    if (_gamed != nullptr)
        _gamed->addReferenceCount(false, kFile, 155);
    if (_owner->_state != 0x40000)
    {
        JOB_LOG(Log::LT_ERROR, 158, L"[job], init from game fail; not in world state", L"");
        sendFail(ERR_INVALID_SESSION_STATE);
        return false;
    }
    if (!LobbyDaemon::_instance->_config->_useGrade)
    {
        JOB_LOG(Log::LT_ERROR, 164, L"[job], grade service not enabled", L"");
        sendFail(ERR_SYSTEM_ERROR);
        return false;
    }
    JOB_LOG(Log::LT_DEBUG, 171, L"[job], init from game ok",
            L", wid:%d, game-tid:0x%I64X, pcid:0x%I64X, game-grade-key:%d, grade-id:%d",
            _gamed != nullptr ? (_gamed->_rawChannel != nullptr ? static_cast<short>(_gamed->_rawChannel->GetId()) : 0) : 0,
            _gameTid, _pcid, _gameGradeKey, _gradeId);
    transit(ACTIVATE_GRADE);
    return true;
}

// 0xc670
bool ActivateGradeJob::activateGradeReq()
{
    NPGameServiceChannel* const gs = LobbyDaemon::_instance->_npServchmgr->_gameServChannel;
    if (gs == nullptr)
    {
        JOB_LOG(Log::LT_ERROR, 181, L"[job], req fail; np game-service channel N/A", L"");
        sendFail(ERR_SYSTEM_ERROR);
        return false;
    }
    NPLobbyJobTransaction* const tr = new (Memory::_Manager[2]->Alloc(sizeof(NPLobbyJobTransaction), kFile, 186))
        NPLobbyJobTransaction;
    if (!gs->SendRequestGradeActivateGrade(tr->Set(this, 81), _owner->_acb._userid, _gradeId, _gameGradeKey))
    {
        JOB_LOG(Log::LT_ERROR, 188, L"[job], req fail; send fail", L"");
        sendFail(ERR_SYSTEM_ERROR);
        // LIFT: the original calls the scalar deleting destructor (flag 1) and then Free. Its operator delete is empty.
        tr->~NPLobbyJobTransaction();
        Memory::_Manager[2]->Free(tr, kFile, 190);
        return false;
    }
    JOB_LOG(Log::LT_DEBUG, 194, L"[job], req sent", L"");
    return true;
}

// 0xca10
bool ActivateGradeJob::activateGradeResponse(void* param)
{
    if (param == nullptr)
    {
        JOB_LOG(Log::LT_ERROR, 201, L"[job], invalid parameter", L"");
        sendFail(ERR_SYSTEM_ERROR);
        return false;
    }

    StsMsgLib::_StsMsgResponseGradeActivateGrade* const res =
        static_cast<StsMsgLib::_StsMsgResponseGradeActivateGrade*>(param);
    unsigned int const statusCode = res->msgInfo.errInfo.nStatusCode;
    wchar_t const* const reason = res->msgInfo.errInfo.pwszReason;
    if (!(statusCode == 200 || (statusCode == 400 && _wcsicmp(L"Success", reason != nullptr ? reason : L"null") == 0)))
    {
        JOB_LOG(Log::LT_ERROR, 208, L"[job], recv fail response",
                L", np-tid:%u, cmd:%d, type:%d, status-code:%u, reason:%s, error-code:%d", res->GetTransactionId(),
                res->GetCommand(), res->GetMessageType(), res->msgInfo.errInfo.nStatusCode,
                res->msgInfo.errInfo.pwszReason != nullptr ? res->msgInfo.errInfo.pwszReason : L"null",
                res->msgInfo.errInfo.nErrorCode);
        int err = ERR_UNKNOWN_ERROR;
        switch (res->msgInfo.errInfo.nErrorCode)
        {
        case 0xA:
            err = ERR_INVALID_PARAMETER;
            break;
        case 0x15E3:
            err = ERR_EXISTS_ACTIVATED_USERGRADE;
            break;
        case 0x15E4:
            err = ERR_NO_AVAILABLE_USERGRADE;
            break;
        default:
            break;
        }
        sendFail(err);
        return false;
    }

    int const gameGradeKey = _wtoi(res->GameGradeKey);
    JOB_LOG(Log::LT_DEBUG, 236, L"[job], activate-grade ok",
            L", grade-id:%d, game-grade-key:%d, effective-from:%I64d, effective-to:%I64d, np-tid:%u, cmd:%d, type:%d, "
            L"status-code:%u, reason:%s, error-code:%d",
            res->nGradeId, gameGradeKey, res->tEffectiveFrom, res->tEffectiveTo, res->GetTransactionId(),
            res->GetCommand(), res->GetMessageType(), res->msgInfo.errInfo.nStatusCode,
            res->msgInfo.errInfo.pwszReason != nullptr ? res->msgInfo.errInfo.pwszReason : L"null",
            res->msgInfo.errInfo.nErrorCode);
    sendOk(gameGradeKey, res->nGradeId, res->tEffectiveFrom, res->tEffectiveTo);
    transit(FIN);
    return true;
}

// 0xcf50
bool ActivateGradeJob::activateGradeExpire()
{
    JOB_LOG(Log::LT_ERROR, 246, L"[job], expired", L"");
    sendFail(ERR_SYSTEM_ERROR);
    transit(FIN);
    return true;
}

// 0xd0a0
void ActivateGradeJob::sendFail(int errCode)
{
    if (_lgate != nullptr)
    {
        short reason = 1;
        switch (errCode)
        {
        case ERR_SYSTEM_ERROR:
            reason = 2;
            break;
        case ERR_INVALID_SESSION_STATE:
            reason = 5;
            break;
        case ERR_INVALID_PARAMETER:
            reason = 6;
            break;
        case ERR_EXISTS_ACTIVATED_USERGRADE:
            reason = 232;
            break;
        case ERR_NO_AVAILABLE_USERGRADE:
            reason = 233;
            break;
        default:
            break;
        }
        _lgate->SendActivateGradeFail(_owner->_clikey, _gameGradeKey <= 0, _gameGradeKey <= 0 ? _gradeId : _gameGradeKey,
                                      reason);
    }
    else if (_gamed != nullptr)
    {
        short reason = 1;
        switch (errCode)
        {
        case ERR_SYSTEM_ERROR:
            reason = 2;
            break;
        case ERR_INVALID_SESSION_STATE:
            reason = 6;
            break;
        case ERR_INVALID_PARAMETER:
            reason = 4;
            break;
        case ERR_EXISTS_ACTIVATED_USERGRADE:
            reason = 87;
            break;
        case ERR_NO_AVAILABLE_USERGRADE:
            reason = 88;
            break;
        default:
            break;
        }
        _gamed->SendActivateGradeFail(_gameTid, _pcid, _gameGradeKey <= 0,
                                      _gameGradeKey <= 0 ? _gradeId : _gameGradeKey, reason);
    }
}

// PDB inline (inlined in activateGradeResponse 0xca10).
void ActivateGradeJob::sendOk(int gameGradeKey, int gradeId, long long effectiveFrom, long long effectiveTo)
{
    if (_lgate != nullptr)
        _lgate->SendActivateGradeOk(_owner->_clikey, gameGradeKey, gradeId, effectiveFrom, effectiveTo);
    else if (_gamed != nullptr)
        _gamed->SendActivateGradeOk(_gameTid, _pcid, gameGradeKey, gradeId, effectiveFrom, effectiveTo);
}
