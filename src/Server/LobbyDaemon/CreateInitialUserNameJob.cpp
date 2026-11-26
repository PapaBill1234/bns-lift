// CreateInitialUserNameJob.obj (LobbyDaemon PDB, 2019 + PDB). Lifted from the pseudocode with PDB types.
#include <new>
#include <string.h>
#include <wchar.h>
#include <winsock2.h>
#include <windows.h>
#include "CreateInitialUserNameJob.h"
#include "CliSession.h"
#include "LiftStub.h"
#include "LobbyConfig.h"
#include "LobbyDaemon.h"
#include "LobbyGateChannel.h"
#include "LobbyJobParams.h"
#include "Log.h"
#include "Memory.h"
#include "MemoryManager.h"
#include "NPServiceChannel.h"
#include "RuleSet.h"
#include "TencentUIC.h"

static wchar_t const kFile[] = L"CreateInitialUserNameJob.cpp";

// The log suffix of all LobbyJob logs. The original reads the owner state 2 times (HIWORD and LOWORD).
#define JOB_SUFFIX L", tid:0x%I64X, type:%d, state:%d, cli-key:0x%I64X, cli-state:%d.%d"
#define JOB_ARGS                                                                                                     \
    this != nullptr ? _id : 0, this != nullptr ? GetDefinition()->type : -1, this != nullptr ? _state : -1,         \
        this != nullptr && _owner != nullptr ? _owner->_clikey : 0,                                                  \
        HIWORD(this != nullptr && _owner != nullptr ? _owner->_state : 0),                                           \
        LOWORD(this != nullptr && _owner != nullptr ? _owner->_state : 0)
#define JOB_LOG(logType, line, msg, fmt, ...) Log::Write(logType, kFile, line, msg JOB_SUFFIX fmt, JOB_ARGS, ##__VA_ARGS__)

// PDB enum ECliSessionState (CliSession.h has no copy yet): 0x10003 is the make-initial-user-name state.
// CSS_LOBBY = 0x20000.

namespace
{
LobbyJobStateDef const StateDef[] = {{0, L"INIT"}, {1, L"CHANGE_USER_NAME"}, {2, L"FIN"}};  // 0x12e0e0
}

LobbyJobDef CreateInitialUserNameJob::_def = {31, StateDef, 2, L"CreateInitialUserNameJob"};  // 0x201eb8

#include "ObjectPoolLobbyDaemon.h"

// .data 0x204200, dynamic init 0x11dd00, atexit dtor 0x11eb80.
// The exe .data holds id 1, objsize 0x68, desc L"CreateInitialUserNameJob".
ObjPool CreateInitialUserNameJob::_pool(1, 0x68, L"CreateInitialUserNameJob");

// 0x2fc20
LobbyJobDef const* CreateInitialUserNameJob::GetDefinition() const
{
    return &_def;
}

// 0x2fc30
// LIFT: Not done. The body calls _pool.Checkin. ObjPool is not in lift_lobbydaemon.
void CreateInitialUserNameJob::deallocate_me(void*, wchar_t const*, int)
{
    LIFT_STUB(0x2fc30);
}

// 0x2fc80
// The original constructs a job on the stack (null owner) and returns its vfptr. It does not run the destructor.
void* CreateInitialUserNameJob::_vtbl()
{
    char buf[sizeof(CreateInitialUserNameJob)];
    CreateInitialUserNameJob* job = ::new (buf) CreateInitialUserNameJob(nullptr);
    return *reinterpret_cast<void**>(job);
}

// 0x2fd20 (scalar deleting destructor 0x2fd00)
CreateInitialUserNameJob::~CreateInitialUserNameJob()
{
    if (_lgate != nullptr)
        _lgate->removeReferenceCount(kFile, 69);
    if (_newUserName != nullptr)
    {
        Memory::_Manager[2]->Free(_newUserName, kFile, 71);
        _newUserName = nullptr;
    }
}

// 0x2fda0
bool CreateInitialUserNameJob::work(int task, void* param)
{
    bool result = false;
    if (_state == INIT && task == 27)
    {
        result = init(param);
        task = 0;
    }
    if (_state == CHANGE_USER_NAME)
    {
        if (task == 0)
            return changeUserNameReq();
        if (task == 70)
            return changeUserNameAck(param);
        if (task == 71)
            return changeUserNameExpire();
    }
    return result;
}

// 0x2fe20
bool CreateInitialUserNameJob::init(void* param)
{
    // The original logs and moves to FIN when the config is off. Then it goes on with the checks.
    if (!LobbyDaemon::_instance->_config->_enableInitialUserName)
    {
        JOB_LOG(Log::LT_ERROR, 107, L"[job], init fail; N/A job", L"");
        transit(FIN);
    }
    CreateInitialUserNameReqParam* const p = static_cast<CreateInitialUserNameReqParam*>(param);
    if (p == nullptr)
    {
        JOB_LOG(Log::LT_ERROR, 113, L"[job], null param", L"");
        return false;
    }
    if (p->lgate == nullptr)
    {
        JOB_LOG(Log::LT_ERROR, 124, L"[job], invalid channel", L", new-user-name:%s",
                p->newUserName != nullptr ? p->newUserName : L"N/A");
        return false;
    }
    _lgate = p->lgate;
    _lgate->addReferenceCount(false, kFile, 129);

    short reason;
    if (p->newUserName == nullptr)
    {
        JOB_LOG(Log::LT_ERROR, 133, L"[job], invalid param", L", new-user-name:%s", L"N/A");
        reason = 6;
    }
    else
    {
        int const len = static_cast<int>(wcslen(p->newUserName));
        if (len <= 0)
        {
            JOB_LOG(Log::LT_ERROR, 141, L"[job], zero length user-name", L", new-user-name:%s", p->newUserName);
            reason = 6;
        }
        else
        {
            _newUserName = static_cast<wchar_t*>(Memory::_Manager[2]->AllocZero(2 * (len + 1), kFile, 146));
            wcscpy_s(_newUserName, len + 1, p->newUserName);
            JOB_LOG(Log::LT_DEBUG, 149, L"[job], init param", L", new-user-name:%s", p->newUserName);
            if (_owner->_state != 0x10003)
            {
                JOB_LOG(Log::LT_ERROR, 152, L"[job], not make-initial-user-name state", L", new-user-name:%s",
                        p->newUserName);
                reason = 5;
            }
            else
            {
                LobbyConfig const* const config = LobbyDaemon::_instance->_config;
                RuleSet::CheckNameResult check;
                if (_newUserName == nullptr)
                    check = RuleSet::CHECKNAME_INVALID_PARAMTER;
                else
                    check = RuleSet::CheckName(LobbyDaemon::_instance->_localeset, _newUserName,
                                               config->_allowedUserNameLenMin, config->_allowedUserNameLenMax, 0, true,
                                               config->_forceSentenceCaseForUserName,
                                               config->_enableMultilingualUserName, nullptr);
                if (check != RuleSet::CHECKNAME_OK)
                {
                    JOB_LOG(Log::LT_ERROR, 172, L"[job], check name fail", L", error:%d, new-user-name:%s", check,
                            p->newUserName);
                    switch (check)
                    {
                    case RuleSet::CHECKNAME_INVALID_PARAMTER:
                    case RuleSet::CHECKNAME_SENTENCE_CASE:
                    case RuleSet::CHECKNAME_MULTILINGUAL:
                        reason = 6;
                        break;
                    case RuleSet::CHECKNAME_TOO_SHORT:
                        reason = 224;
                        break;
                    case RuleSet::CHECKNAME_TOO_LONG:
                        reason = 225;
                        break;
                    case RuleSet::CHECKNAME_NOT_ALLOWED:
                        reason = 227;
                        break;
                    case RuleSet::CHECKNAME_SIDE_SPACE:
                    case RuleSet::CHECKNAME_DOUBLE_SPACE:
                    case RuleSet::CHECKNAME_SPACE_OVERFLOW:
                        reason = 226;
                        break;
                    default:
                        reason = 1;
                        break;
                    }
                }
                else if (LobbyDaemon::_instance->_config->_tencentUICEnable &&
                         _owner->_externalAccountKeySize <= 0)
                {
                    JOB_LOG(Log::LT_ERROR, 211, L"[job], no external info", L", new-user-name:%s", p->newUserName);
                    reason = 2;
                }
                else if (LobbyDaemon::_instance->_config->_tencentUICEnable &&
                         !LobbyDaemon::_instance->_tencentUIC->CheckNameFilter(
                             *reinterpret_cast<unsigned int const*>(_owner->_externalAccountKey), _newUserName))
                {
                    JOB_LOG(Log::LT_ERROR, 221, L"[job], filtered by tencent uic", L", new-user-name:%s",
                            p->newUserName);
                    reason = 228;
                }
                else
                {
                    JOB_LOG(Log::LT_DEBUG, 228, L"[job], init ok", L"");
                    transit(CHANGE_USER_NAME);
                    return true;
                }
            }
        }
    }
    _lgate->SendCreateInitialUserNameFail(_owner->_clikey, reason);
    return false;
}

// 0x30660
bool CreateInitialUserNameJob::changeUserNameReq()
{
    NPGameServiceChannel* const channel = LobbyDaemon::_instance->_npServchmgr->_gameServChannel;
    if (!channel->IsConnected())
    {
        JOB_LOG(Log::LT_ERROR, 240, L"[job], np disconnected", L"");
        _lgate->SendCreateInitialUserNameFail(_owner->_clikey, 7);
        return false;
    }
    NPLobbyJobTransaction* const t =
        new (Memory::_Manager[2]->Alloc(sizeof(NPLobbyJobTransaction), kFile, 245)) NPLobbyJobTransaction;
    if (!channel->SendRequestAuthChangeMyUserNameIncomplete(t->Set(this, 71), _owner->_acb._id,
                                                            _owner->_acb._userName, _newUserName, L"dummy"))
    {
        JOB_LOG(Log::LT_ERROR, 252, L"[job], request fail; unsent", L"");
        _lgate->SendCreateInitialUserNameFail(_owner->_clikey, 2);
        // LIFT: the original calls the scalar deleting destructor (flag 1) and then Free. Its operator delete is empty.
        t->~NPLobbyJobTransaction();
        Memory::_Manager[2]->Free(t, kFile, 254);
        return false;
    }
    JOB_LOG(Log::LT_DEBUG, 258, L"[job], request sent", L"");
    return true;
}

// 0x30980
bool CreateInitialUserNameJob::changeUserNameAck(void* param)
{
    StsMsgLib::_StsMsgResponse* const msg = static_cast<StsMsgLib::_StsMsgResponse*>(param);
    if (msg == nullptr)
    {
        JOB_LOG(Log::LT_ERROR, 265, L"[job], null param", L"");
        _lgate->SendCreateInitialUserNameFail(_owner->_clikey, 2);
        return false;
    }
    unsigned int const status = msg->msgInfo.errInfo.nStatusCode;
    if (status != 200 &&
        (status != 400 ||
         _wcsicmp(L"Success", msg->msgInfo.errInfo.pwszReason != nullptr ? msg->msgInfo.errInfo.pwszReason : L"null") != 0))
    {
        JOB_LOG(Log::LT_ERROR, 273, L"[job], change-user-name fail",
                L",np-tid:%u, cmd:%d, type:%d, status-code:%u, reason:%s, error-code:%d", msg->GetTransactionId(),
                msg->GetCommand(), msg->GetMessageType(), status,
                msg->msgInfo.errInfo.pwszReason != nullptr ? msg->msgInfo.errInfo.pwszReason : L"null",
                msg->msgInfo.errInfo.nErrorCode);
        short reason;
        switch (msg->msgInfo.errInfo.nErrorCode)
        {
        case 3003:
        case 3042:
            reason = 229;
            break;
        case 3041:
            reason = 228;
            break;
        case 3336:
            reason = 231;
            break;
        case 3743:
            reason = 230;
            break;
        case 10:
        case 3035:
            reason = 6;
            break;
        case 4:
        case 48:
        case 3000:
        case 3002:
            reason = 2;
            break;
        default:
            reason = 1;
            break;
        }
        _lgate->SendCreateInitialUserNameFail(_owner->_clikey, reason);
        return false;
    }
    JOB_LOG(Log::LT_DEBUG, 312, L"[job], user-name changed", L", old-user-name:%s, new-user-name:%s",
            _owner != nullptr ? _owner->_acb._userName : L"N/A", _newUserName);
    if (_newUserName != nullptr)
        wcscpy_s(_owner->_acb._userName, 65, _newUserName);
    _owner->_state = 0x20000;  // CSS_LOBBY
    _lgate->SendCreateInitialUserNameOk(_owner->_clikey, _newUserName);
    transit(FIN);
    return true;
}

// 0x30d90
bool CreateInitialUserNameJob::changeUserNameExpire()
{
    JOB_LOG(Log::LT_ERROR, 325, L"[job], expired", L"");
    _lgate->SendCreateInitialUserNameFail(_owner->_clikey, 7);
    transit(FIN);
    return true;
}
