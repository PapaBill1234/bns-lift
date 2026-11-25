// StartCliSessionWlobbyTokenJob.obj (LobbyDaemon PDB, 2019 + PDB). Lifted from the pseudocode with PDB types.
#include <new>
#include <stddef.h>
#include <wchar.h>
#include <winsock2.h>
#include <windows.h>
#include "NPServiceChannel.h"
#include "StsMsgGrade.h"
#include "StartCliSessionWlobbyTokenJob.h"
#include "AlertSender.h"
#include "BnsCommonConfigDefinition.h"
#include "CliSession.h"
#include "GradeService.h"
#include "LiftStub.h"
#include "LobbyConfig.h"
#include "LobbyDaemon.h"
#include "LobbyGateChannel.h"
#include "Log.h"
#include "Memory.h"
#include "MemoryManager.h"

static wchar_t const kFile[] = L"StartCliSessionWlobbyTokenJob.cpp";

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

// LIFT: PDB StsMsgLib::_StsMsgRequestGradeGetLevel (sizeof 0x30) and _StsMsgRequestPresenceSetAppData (sizeof 0x38).
// The types are not in a LobbyDaemon header yet. The second one is the same as in LobbyGamePacketHandler.cpp.
namespace StsMsgLib
{
struct _StsMsgRequestGradeGetLevel : public _StsMsgRequest
{
    id128* pUserId;
    int nLevelGroupId;
    int nGradeId;
    int nGameGradeKey;
};
static_assert(sizeof(_StsMsgRequestGradeGetLevel) == 0x30, "sizeof _StsMsgRequestGradeGetLevel");
static_assert(offsetof(_StsMsgRequestGradeGetLevel, nGameGradeKey) == 0x28, "_StsMsgRequestGradeGetLevel::nGameGradeKey");

struct _StsMsgRequestPresenceSetAppData : public _StsMsgRequest
{
    struct AppData
    {
        struct Field
        {
            char* pszKey;
            wchar_t* pwszValue;
        };
        Field* pFields;
        int nFieldCount;
    };
    id128* pUserId;
    id128* pAppId;
    AppData appData;
};
static_assert(sizeof(_StsMsgRequestPresenceSetAppData) == 0x38, "sizeof _StsMsgRequestPresenceSetAppData");
static_assert(offsetof(_StsMsgRequestPresenceSetAppData, appData) == 0x28, "_StsMsgRequestPresenceSetAppData::appData");
}  // namespace StsMsgLib

namespace
{
LobbyJobStateDef const StateDef[] = {
    {0, L"INIT"}, {1, L"GET_GRADE_LEVEL"}, {2, L"LIST_ALL_GRADES"}, {3, L"START"}, {4, L"FIN"}};  // 0x12dc60
}

LobbyJobDef StartCliSessionWlobbyTokenJob::_def = {15, StateDef, 4, L"StartCliSessionWlobbyTokenJob"};  // 0x2019b0
// LIFT: StartCliSessionWlobbyTokenJob::_pool has no definition. The LobbyDaemon ObjectPool module is not in
// lift_lobbydaemon (see CliSession.cpp).

// 0x76250
LobbyJobDef const* StartCliSessionWlobbyTokenJob::GetDefinition() const
{
    return &_def;
}

// 0x76260
// LIFT: Not done. The body calls _pool.Checkin. ObjPool is not in lift_lobbydaemon.
void StartCliSessionWlobbyTokenJob::deallocate_me(void*, wchar_t const*, int)
{
    LIFT_STUB(0x76260);
}

// 0x762b0
// The original constructs a job on the stack (null owner) and returns its vfptr. It does not run the destructor.
void* StartCliSessionWlobbyTokenJob::_vtbl()
{
    char buf[sizeof(StartCliSessionWlobbyTokenJob)];
    StartCliSessionWlobbyTokenJob* job = ::new (buf) StartCliSessionWlobbyTokenJob(nullptr);
    return *reinterpret_cast<void**>(job);
}

// 0x76330 (scalar deleting destructor)
StartCliSessionWlobbyTokenJob::~StartCliSessionWlobbyTokenJob()
{
    if (_lgate != nullptr)
        _lgate->removeReferenceCount(kFile, 74);
}

// 0x76380
bool StartCliSessionWlobbyTokenJob::Initialize(LobbyGateChannel* lgate)
{
    if (lgate != nullptr)
    {
        _lgate = lgate;
        lgate->addReferenceCount(false, kFile, 84);
        return true;
    }
    JOB_LOG(Log::LT_ERROR, 80, L"[job], invalid parameter", L"");
    return false;
}

// 0x76490
bool StartCliSessionWlobbyTokenJob::work(int task, void* param)
{
    bool result = false;
    if (_state == INIT && task == 15)
    {
        result = init();
        task = 0;
    }
    if (_state == GET_GRADE_LEVEL)
    {
        switch (task)
        {
        case 0:
            result = getGradeLevelReq();
            break;
        case 'N':
            result = getGradeLevelResponse(param);
            task = 0;
            break;
        case 'O':
            result = getGradeLevelExpire();
            task = 0;
            break;
        }
    }
    if (_state == LIST_ALL_GRADES)
    {
        switch (task)
        {
        case 0:
            result = listAllGradesReq();
            break;
        case 'L':
            result = listAllGradesResponse(param);
            task = 0;
            break;
        case 'M':
            result = listAllGradesExpire();
            task = 0;
            break;
        }
    }
    if (_state == START && task == 0)
        return start();
    return result;
}

// 0x76550
bool StartCliSessionWlobbyTokenJob::init()
{
    if (_owner->_state != 0x50002)
    {
        JOB_LOG(Log::LT_ERROR, 133, L"[job], invalid state", L"");
        _lgate->SendStartSessionWithLobbyTokenFail(_owner->_clikey, 5);
        return false;
    }
    JOB_LOG(Log::LT_DEBUG, 138, L"[job], init ok", L", gate-wid:%d", _lgate != nullptr ? _lgate->GetWid() : 0);
    LobbyConfig const* config = LobbyDaemon::_instance->_config;
    int next;
    if (config->_useGradeLevel)
        next = GET_GRADE_LEVEL;
    else if (config->_useGrade && config->_enableReloadGradeWhileReturnToLobby)
        next = LIST_ALL_GRADES;
    else
        next = START;
    transit(next);
    return true;
}

// 0x76720
bool StartCliSessionWlobbyTokenJob::getGradeLevelReq()
{
    NPGameServiceChannel* gs = LobbyDaemon::_instance->_npServchmgr->_gameServChannel;
    if (gs == nullptr)
    {
        JOB_LOG(Log::LT_ERROR, 165, L"[job], np game-service channel not available", L"");
    }
    else
    {
        NPLobbyJobTransaction* tr =
            new (Memory::_Manager[2]->Alloc(sizeof(NPLobbyJobTransaction), kFile, 172)) NPLobbyJobTransaction;
        LobbyConfig const* config = LobbyDaemon::_instance->_config;
        StsMsgLib::_StsMsgRequestGradeGetLevel msg;
        bool built = true;
        if (config->_gradeLevelGroupId > 0)
        {
            msg.nLevelGroupId = config->_gradeLevelGroupId;
            msg.nGradeId = 0;
            msg.nGameGradeKey = 0;
        }
        else if (config->_gameGradeKeyForGetLevel > 0)
        {
            msg.nLevelGroupId = 0;
            msg.nGradeId = 0;
            msg.nGameGradeKey = config->_gameGradeKeyForGetLevel;
        }
        else
        {
            // LIFT: the original does not free the transaction on this path.
            built = false;
        }
        if (built)
        {
            tr->Set(this, 79);
            msg.msgInfo.eCmd = StsMsgLib::COMMAND_COMMON_GRADE_GET_LEVEL;
            msg.msgInfo.msgType = StsMsgLib::MESSAGE_TYPE_REQUEST;
            msg.msgInfo.nTxnId = 0;
            msg.pUserId = &_owner->_acb._userid;
            if (gs->SendMsg(&msg, true, tr))
            {
                JOB_LOG(Log::LT_DEBUG, 189, L"[job], sent", L"");
                return true;
            }
        }
        JOB_LOG(Log::LT_ERROR, 182, L"[job], unsent", L"");
    }
    _lgate->SendStartSessionWithLobbyTokenFail(_owner->_clikey, 2);
    _owner->_state = 0x60000;
    _owner->finalize();
    return false;
}

// 0x76a50
bool StartCliSessionWlobbyTokenJob::getGradeLevelResponse(void* param)
{
    StsMsgLib::_StsMsgResponseGradeGetLevel* res = static_cast<StsMsgLib::_StsMsgResponseGradeGetLevel*>(param);
    if (res == nullptr)
    {
        JOB_CRASH(196, L"== CRASH == [job], invalid parameter");
    }
    else
    {
        unsigned int status = res->msgInfo.errInfo.nStatusCode;
        if (status == 200 ||
            (status == 400 &&
             _wcsicmp(L"Success", res->msgInfo.errInfo.pwszReason != nullptr ? res->msgInfo.errInfo.pwszReason : L"null") == 0))
        {
            JOB_LOG(Log::LT_DEBUG, 213, L"[job], ok response",
                    L", level:%d, score:%d, np-tid:%u, cmd:%d, type:%d, status-code:%u, reason:%s, error-code:%d",
                    res->nLevelId, res->nAccumulateGradeScore, res->GetTransactionId(), res->GetCommand(),
                    res->GetMessageType(), res->msgInfo.errInfo.nStatusCode,
                    res->msgInfo.errInfo.pwszReason != nullptr ? res->msgInfo.errInfo.pwszReason : L"null",
                    res->msgInfo.errInfo.nErrorCode);
            _owner->_gradeService.SetGradeLevel(_owner, res);
            transit(LobbyDaemon::_instance->_config->_enableReloadGradeWhileReturnToLobby ? LIST_ALL_GRADES : START);
            return true;
        }
        JOB_LOG(Log::LT_ERROR, 205, L"[job], fail response",
                L", np-tid:%u, cmd:%d, type:%d, status-code:%u, reason:%s, error-code:%d", res->GetTransactionId(),
                res->GetCommand(), res->GetMessageType(), res->msgInfo.errInfo.nStatusCode,
                res->msgInfo.errInfo.pwszReason != nullptr ? res->msgInfo.errInfo.pwszReason : L"null",
                res->msgInfo.errInfo.nErrorCode);
    }
    _lgate->SendStartSessionWithLobbyTokenFail(_owner->_clikey, 2);
    _owner->_state = 0x60000;
    _owner->finalize();
    return false;
}

// 0x76f30
bool StartCliSessionWlobbyTokenJob::getGradeLevelExpire()
{
    JOB_LOG(Log::LT_ERROR, 228, L"[job], expired", L"");
    _lgate->SendStartSessionWithLobbyTokenFail(_owner->_clikey, 2);
    _owner->_state = 0x60000;
    _owner->finalize();
    transit(FIN);
    return true;
}

// 0x77050
// LIFT: NPGameServiceChannel::SendRequestGradeListAllGrades is still a stub (gap-04).
bool StartCliSessionWlobbyTokenJob::listAllGradesReq()
{
    NPGameServiceChannel* gs = LobbyDaemon::_instance->_npServchmgr->_gameServChannel;
    if (gs != nullptr)
    {
        NPLobbyJobTransaction* tr =
            new (Memory::_Manager[2]->Alloc(sizeof(NPLobbyJobTransaction), kFile, 250)) NPLobbyJobTransaction;
        tr->Set(this, 75);
        if (!gs->SendRequestGradeListAllGrades(tr, _owner->_acb._userid))
        {
            JOB_LOG(Log::LT_ERROR, 252, L"[job], send list all grades failed; unsent", L"");
            _lgate->SendStartSessionWithLobbyTokenFail(_owner->_clikey, 2);
            _owner->_state = 0x60000;
            _owner->finalize();
            delete tr;
            Memory::_Manager[2]->Free(tr, kFile, 256);
            return false;
        }
        JOB_LOG(Log::LT_DEBUG, 260, L"[job], sent", L"");
        return true;
    }
    JOB_LOG(Log::LT_ERROR, 243, L"[job], np game-service channel not available", L"");
    _lgate->SendStartSessionWithLobbyTokenFail(_owner->_clikey, 2);
    _owner->_state = 0x60000;
    _owner->finalize();
    return false;
}

// 0x77340
bool StartCliSessionWlobbyTokenJob::listAllGradesResponse(void* param)
{
    StsMsgLib::_StsMsgResponseGradeListAllGrades* res =
        static_cast<StsMsgLib::_StsMsgResponseGradeListAllGrades*>(param);
    if (res == nullptr)
    {
        JOB_CRASH(267, L"== CRASH == [job], invalid parameter");
    }
    else
    {
        unsigned int status = res->msgInfo.errInfo.nStatusCode;
        if (status == 200 ||
            (status == 400 &&
             _wcsicmp(L"Success", res->msgInfo.errInfo.pwszReason != nullptr ? res->msgInfo.errInfo.pwszReason : L"null") == 0))
        {
            JOB_LOG(Log::LT_DEBUG, 285, L"[job], ok response",
                    L", np-tid:%u, cmd:%d, type:%d, status-code:%u, reason:%s, error-code:%d, grade-list-count:%d",
                    res->GetTransactionId(), res->GetCommand(), res->GetMessageType(), res->msgInfo.errInfo.nStatusCode,
                    res->msgInfo.errInfo.pwszReason != nullptr ? res->msgInfo.errInfo.pwszReason : L"null",
                    res->msgInfo.errInfo.nErrorCode, res->nGradeListCount);
            _owner->_gradeService.SetGradeList(_owner, res);
            transit(START);
            return true;
        }
        JOB_LOG(Log::LT_ERROR, 277, L"[job], fail response",
                L", np-tid:%u, cmd:%d, type:%d, status-code:%u, reason:%s, error-code:%d", res->GetTransactionId(),
                res->GetCommand(), res->GetMessageType(), res->msgInfo.errInfo.nStatusCode,
                res->msgInfo.errInfo.pwszReason != nullptr ? res->msgInfo.errInfo.pwszReason : L"null",
                res->msgInfo.errInfo.nErrorCode);
    }
    _lgate->SendStartSessionWithLobbyTokenFail(_owner->_clikey, 2);
    _owner->_state = 0x60000;
    _owner->finalize();
    return false;
}

// 0x777f0
bool StartCliSessionWlobbyTokenJob::listAllGradesExpire()
{
    JOB_LOG(Log::LT_ERROR, 296, L"[job], expired", L"");
    _lgate->SendStartSessionWithLobbyTokenFail(_owner->_clikey, 2);
    _owner->_state = 0x60000;
    _owner->finalize();
    transit(FIN);
    return true;
}

// 0x77910
bool StartCliSessionWlobbyTokenJob::start()
{
    LobbyGatePresence* presence =
        new (Memory::_Manager[2]->Alloc(sizeof(LobbyGatePresence), kFile, 309)) LobbyGatePresence(_lgate->GetWid());
    if (!_owner->setPresence(presence))
    {
        JOB_LOG(Log::LT_ERROR, 312, L"[job], set lobby-gate presence fail", L", gate-wid:%d", _lgate->GetWid());
        _owner->_state = 0x60000;
        _owner->finalize();
        _lgate->SendStartSessionWithLobbyTokenFail(_owner->_clikey, 2);
        delete presence;
        Memory::_Manager[2]->Free(presence, kFile, 316);
        return false;
    }
    _owner->_state = 0x20000;
    JOB_LOG(Log::LT_DEBUG, 322, L"[job], start cli-session ok", L"");
    CliSession* owner = _owner;
    _lgate->SendStartSessionWithLobbyTokenOk(
        owner->_clikey, LobbyDaemon::_instance->_config->_useGrade, owner->_gradeService,
        owner->_jumpingCharacterCreationQuota._db.creationQuota - owner->_jumpingCharacterCreationQuota._db.creationCount,
        owner->_acb._accountExp);
    if (LobbyDaemon::_instance->_config->_enableFriendMessageNotification)
    {
        NPGameServiceChannel* gs = LobbyDaemon::_instance->_npServchmgr->_gameServChannel;
        if (gs != nullptr)
        {
            StsMsgLib::_StsMsgRequestPresenceSetAppData::AppData::Field field;
            field.pszKey = const_cast<char*>("location");
            field.pwszValue = const_cast<wchar_t*>(L"lobby");
            StsMsgLib::_StsMsgRequestPresenceSetAppData::AppData appData;
            appData.pFields = &field;
            appData.nFieldCount = 1;
            StsMsgLib::_StsMsgRequestPresenceSetAppData msg;
            msg.msgInfo.eCmd = StsMsgLib::COMMAND_SRV_PRES_SET_APP_DATA;
            msg.msgInfo.msgType = StsMsgLib::MESSAGE_TYPE_REQUEST;
            msg.msgInfo.nTxnId = 0;
            msg.pUserId = &_owner->_acb._id;
            msg.pAppId = &BnsCommonConfig::Config->_npAppId;
            msg.appData = appData;
            gs->SendMsg(&msg, true, nullptr);
        }
    }
    transit(FIN);
    return true;
}
