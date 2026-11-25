// ChangeUserNameJob.obj (LobbyDaemon PDB, 2019 + PDB). Lifted from the pseudocode with PDB types.
#include <new>
#include <string.h>
#include <wchar.h>
#include <winsock2.h>
#include <windows.h>
#include "ChangeUserNameJob.h"
#include "AccountInventoryChannel.h"
#include "AlertSender.h"
#include "CliSession.h"
#include "LiftStub.h"
#include "LobbyConfig.h"
#include "LobbyDaemon.h"
#include "LobbyGateChannel.h"
#include "LobbyGoodsTypes.h"
#include "LobbyJobParams.h"
#include "LobbyService.h"
#include "Log.h"
#include "Memory.h"
#include "MemoryManager.h"
#include "NPServiceChannel.h"
#include "RuleSet.h"
#include "TencentUIC.h"
#include "TransactionChannel.h"

static wchar_t const kFile[] = L"ChangeUserNameJob.cpp";

// The log suffix of all LobbyJob logs. The original reads the owner state 2 times (HIWORD and LOWORD).
#define JOB_SUFFIX L", tid:0x%I64X, type:%d, state:%d, cli-key:0x%I64X, cli-state:%d.%d"
#define JOB_ARGS                                                                                                     \
    this != nullptr ? _id : 0, this != nullptr ? GetDefinition()->type : -1, this != nullptr ? _state : -1,         \
        this != nullptr && _owner != nullptr ? _owner->_clikey : 0,                                                  \
        HIWORD(this != nullptr && _owner != nullptr ? _owner->_state : 0),                                           \
        LOWORD(this != nullptr && _owner != nullptr ? _owner->_state : 0)
#define JOB_LOG(logType, line, msg, fmt, ...) Log::Write(logType, kFile, line, msg JOB_SUFFIX fmt, JOB_ARGS, ##__VA_ARGS__)
// The original selects the message and the line, and then makes one log call (msg holds the full format).
#define JOB_LOGV(logType, line, msg) Log::Write(logType, kFile, line, msg, JOB_ARGS)
#define JOB_CRASH(line, msg)                                                                                         \
    do                                                                                                               \
    {                                                                                                                \
        JOB_LOG(Log::LT_ERROR, line, msg, L"");                                                                      \
        AlertSender::Write(kFile, line, msg JOB_SUFFIX, JOB_ARGS);                                                   \
    } while (0)

// PDB enum ECliSessionState (CliSession.h has no copy yet): CSS_LOBBY = 0x20000.
// PDB LobbyService::DB::serviceType of RenameUserService: 5.

namespace
{
LobbyJobStateDef const StateDef[] = {{0, L"INIT"},
                                     {1, L"CHECK_ACCOUNT_INVENTORY_ITEM"},
                                     {2, L"CHANGE_USER_NAME"},
                                     {3, L"CONSUME_LOBBY_SERVICE_ITEM"},
                                     {4, L"FIN_LOBBY_SERVICE"},
                                     {5, L"FIN"}};  // 0x12e1e0
}

LobbyJobDef ChangeUserNameJob::_def = {37, StateDef, 5, L"ChangeUserNameJob"};  // 0x201f60
// LIFT: ChangeUserNameJob::_pool has no definition. The LobbyDaemon ObjectPool module is not in lift_lobbydaemon
// (see CliSession.cpp).

// 0x26990
LobbyJobDef const* ChangeUserNameJob::GetDefinition() const
{
    return &_def;
}

// 0x269a0
// LIFT: Not done. The body calls _pool.Checkin. ObjPool is not in lift_lobbydaemon.
void ChangeUserNameJob::deallocate_me(void*, wchar_t const*, int)
{
    LIFT_STUB(0x269a0);
}

// 0x269f0
// The original constructs a job on the stack (null owner) and returns its vfptr. It does not run the destructor.
void* ChangeUserNameJob::_vtbl()
{
    char buf[sizeof(ChangeUserNameJob)];
    ChangeUserNameJob* job = ::new (buf) ChangeUserNameJob(nullptr);
    return *reinterpret_cast<void**>(job);
}

// 0x26a70
ChangeUserNameJob::ChangeUserNameJob(CliSession* owner)
    : CliSessionJob(owner), _tran(nullptr), _lgate(nullptr), _acciv(nullptr), _labelId(0), _itemInstanceId(0),
      _itemDataId(0)
{
    _newUserName[0] = 0;
}

// 0x26ae0 (scalar deleting destructor 0x26ac0)
ChangeUserNameJob::~ChangeUserNameJob()
{
    if (_tran != nullptr)
        _tran->removeReferenceCount(kFile, 89);
    if (_lgate != nullptr)
        _lgate->removeReferenceCount(kFile, 91);
}

// 0x26b50
bool ChangeUserNameJob::work(int task, void* param)
{
    bool result = false;
    if (_state == INIT && task == 29)
    {
        result = init(param);
        task = 0;
    }
    if (_state == CHECK_ACCOUNT_INVENTORY_ITEM)
    {
        if (task == 0)
            result = checkAccountInventoryItem();
        else if (task == 156)
        {
            result = checkAccountInventoryItemOk(param);
            task = 0;
        }
        else if (task == 157)
        {
            result = checkAccountInventoryItemFail(param);
            task = 0;
        }
        else if (task == 158)
        {
            result = checkAccountInventoryItemTimeout();
            task = 0;
        }
    }
    if (_state == CHANGE_USER_NAME)
    {
        if (task == 0)
            result = changeUserName();
        else if (task == 70)
        {
            result = changeUserNameResponse(param);
            task = 0;
        }
        else if (task == 71)
        {
            result = changeUserNameExpire();
            task = 0;
        }
    }
    if (_state == CONSUME_LOBBY_SERVICE_ITEM)
    {
        if (task == 0)
            result = consumeLobbyServiceItem();
        else if (task == 165)
        {
            result = consumeLobbyServiceItemOk(param);
            task = 0;
        }
        else if (task == 166)
        {
            result = consumeLobbyServiceItemFail(param);
            task = 0;
        }
        else if (task == 167)
        {
            result = consumeLobbyServiceItemTimeout();
            task = 0;
        }
    }
    if (_state == FIN_LOBBY_SERVICE && task == 0)
        return finLobbyService();
    return result;
}

// 0x26c80
bool ChangeUserNameJob::init(void* param)
{
    ChangeUserNameWithAccountInventoryItemReqParam* const p =
        static_cast<ChangeUserNameWithAccountInventoryItemReqParam*>(param);
    if (p == nullptr || p->lgate == nullptr || wcslen(p->newUserName) == 0 || p->labelId == 0 ||
        p->itemInstanceId == 0 || p->itemDataId == 0)
    {
        JOB_LOG(Log::LT_ERROR, 174, L"[job], invalid param", L"");
        if (p != nullptr && p->lgate != nullptr)
            p->lgate->SendChangeUserNameWithAccountInventoryItemFail(_owner->_clikey, p->labelId, p->itemInstanceId, 6);
        return false;
    }

    _tran = new (Memory::_Manager[2]->Alloc(sizeof(LobbyJobTransaction), kFile, 185)) LobbyJobTransaction;
    _lgate = p->lgate;
    _lgate->addReferenceCount(false, kFile, 188);
    _acciv = LobbyDaemon::_instance->_accountInventoryChannel;
    wcscpy_s(_newUserName, 65, p->newUserName);
    _labelId = p->labelId;
    _itemInstanceId = p->itemInstanceId;
    _itemDataId = p->itemDataId;

    short reason;
    if (!LobbyDaemon::_instance->_config->_enableChangeUserNameService)
    {
        JOB_LOG(Log::LT_ERROR, 200, L"[job], service config not enabled", L"");
        reason = 7;
    }
    else if (_owner->_state != 0x20000)  // CSS_LOBBY
    {
        JOB_LOG(Log::LT_ERROR, 207, L"[job], cli-session not in lobby", L"");
        reason = 5;
    }
    else if (_owner->_renameUserServiceEntry != nullptr)
    {
        JOB_LOG(Log::LT_ERROR, 213, L"[job], init fail; already in rename user service", L"");
        reason = 9;
    }
    else if (_acciv == nullptr || !_acciv->IsConnected())
    {
        JOB_LOG(Log::LT_ERROR, 219, L"[job], init fail; account-inventory N/A", L"");
        reason = 7;
    }
    else if (!LobbyDaemon::_instance->CheckServiceItemDataId(LobbyDaemon::SERVICEITEMTYPE_CHANGE_USER_NAME, _itemDataId))
    {
        JOB_LOG(Log::LT_ERROR, 225, L"[job], not proper item", L", item-data-id:%u", _itemDataId);
        reason = 211;
    }
    else if (wcslen(_newUserName) == 0)
    {
        JOB_LOG(Log::LT_ERROR, 234, L"[job], invalid name length", L"");
        reason = 6;
    }
    else
    {
        LobbyConfig const* const config = LobbyDaemon::_instance->_config;
        RuleSet::CheckNameResult const check = RuleSet::CheckName(
            LobbyDaemon::_instance->_localeset, _newUserName, config->_allowedUserNameLenMin,
            config->_allowedUserNameLenMax, 0, true, config->_forceSentenceCaseForUserName,
            config->_enableMultilingualUserName, nullptr);
        if (check != RuleSet::CHECKNAME_OK)
        {
            JOB_LOG(Log::LT_ERROR, 251, L"[job], check name fail", L", error:%d, new-user-name:%s", check,
                    _newUserName);
            short checkReason;
            switch (check)
            {
            case RuleSet::CHECKNAME_INVALID_PARAMTER:
            case RuleSet::CHECKNAME_SENTENCE_CASE:
            case RuleSet::CHECKNAME_MULTILINGUAL:
                checkReason = 6;
                break;
            case RuleSet::CHECKNAME_TOO_SHORT:
                checkReason = 212;
                break;
            case RuleSet::CHECKNAME_TOO_LONG:
                checkReason = 213;
                break;
            case RuleSet::CHECKNAME_NOT_ALLOWED:
                checkReason = 215;
                break;
            case RuleSet::CHECKNAME_SIDE_SPACE:
            case RuleSet::CHECKNAME_DOUBLE_SPACE:
            case RuleSet::CHECKNAME_SPACE_OVERFLOW:
                checkReason = 214;
                break;
            case RuleSet::CHECKNAME_FORBIDDEN:
                checkReason = 216;
                break;
            default:
                checkReason = 1;
                break;
            }
            _lgate->SendChangeUserNameWithAccountInventoryItemFail(_owner->_clikey, _labelId, _itemInstanceId,
                                                                   checkReason);
            return false;
        }
        if (LobbyDaemon::_instance->_config->_tencentUICEnable)
        {
            if (_owner->_externalAccountKeySize <= 0)
            {
                JOB_LOG(Log::LT_ERROR, 291, L"[job], no external account key", L"");
                _lgate->SendChangeUserNameWithAccountInventoryItemFail(_owner->_clikey, _labelId, _itemInstanceId, 2);
                return false;
            }
            if (!LobbyDaemon::_instance->_tencentUIC->CheckNameFilter(
                    *reinterpret_cast<unsigned int const*>(_owner->_externalAccountKey), _newUserName))
            {
                JOB_LOG(Log::LT_ERROR, 300, L"[job], filtered by tencent uic", L", new-user-name:%s", _newUserName);
                _lgate->SendChangeUserNameWithAccountInventoryItemFail(_owner->_clikey, _labelId, _itemInstanceId, 216);
                return false;
            }
        }
        JOB_LOG(Log::LT_DEBUG, 311, L"[job], init ok",
                L", gate-wid:%d, old-user-name:%s, new-user-name:%s, label-id:0x%I64X, item-instance-id:0x%I64X, "
                L"item-data-id:%u",
                _lgate != nullptr ? (_lgate->_rawChannel != nullptr ? static_cast<short>(_lgate->_rawChannel->GetId()) : 0) : 0,
                _owner->_acb._userName, _newUserName, _labelId, _itemInstanceId, _itemDataId);
        transit(CHECK_ACCOUNT_INVENTORY_ITEM);
        return true;
    }
    _lgate->SendChangeUserNameWithAccountInventoryItemFail(_owner->_clikey, _labelId, _itemInstanceId, reason);
    return false;
}

// 0x275f0
bool ChangeUserNameJob::checkAccountInventoryItem()
{
    if (!_acciv->SendRetrieveSingleWarehouseItemReq(_tran->Set(this, 158), _itemInstanceId, _owner->_acb._id, 0))
    {
        JOB_LOG(Log::LT_ERROR, 320, L"[job], not sent", L"");
        _lgate->SendChangeUserNameWithAccountInventoryItemFail(_owner->_clikey, _labelId, _itemInstanceId, 7);
        return false;
    }
    JOB_LOG(Log::LT_DEBUG, 325, L"[job], sent", L"");
    return true;
}

// 0x27790
bool ChangeUserNameJob::checkAccountInventoryItemOk(void* param)
{
    _acciv->TRecv(_tran);
    RetrieveSingleWarehouseItemOkParam* const ok = static_cast<RetrieveSingleWarehouseItemOkParam*>(param);
    short reason;
    if (ok == nullptr)
    {
        JOB_CRASH(334, L"== CRASH == [job], invalid param");
        reason = 2;
    }
    else if (ok->item == nullptr)
    {
        JOB_LOG(Log::LT_ERROR, 343, L"[job], null item", L"");
        reason = 2;
    }
    else
    {
        LobbyServiceItem const* const item = ok->item;
        JOB_LOG(Log::LT_DEBUG, 349, L"[job], ok recv",
                L", item-instance-id:0x%I64X, label-id:0x%I64X, item-data-id:%u, state:%d", item->instanceId,
                item->labelId, item->dataId, item->state);
        if (_itemDataId != item->dataId)
        {
            JOB_LOG(Log::LT_ERROR, 352, L"[job], item-data-id mismatch",
                    L", request-item-data-id:%u, required-item-data-id:%u", _itemDataId, item->dataId);
            reason = 211;
        }
        else if (item->state != 1)
        {
            JOB_LOG(Log::LT_ERROR, 358, L"[job], unusable item", L"");
            reason = 210;
        }
        else
        {
            transit(CHANGE_USER_NAME);
            return true;
        }
    }
    _lgate->SendChangeUserNameWithAccountInventoryItemFail(_owner->_clikey, _labelId, _itemInstanceId, reason);
    return false;
}

// 0x27bc0
bool ChangeUserNameJob::checkAccountInventoryItemFail(void* param)
{
    _acciv->TRecv(_tran);
    short* const fail = static_cast<short*>(param);
    if (fail == nullptr)
    {
        JOB_CRASH(372, L"== CRASH == [job], invalid param");
        _lgate->SendChangeUserNameWithAccountInventoryItemFail(_owner->_clikey, _labelId, _itemInstanceId, 2);
        return false;
    }
    JOB_LOG(Log::LT_DEBUG, 380, L"[job], fail recv", L", reason:%d", *fail);
    short reason = 2;
    if (*fail == 20)
        reason = 209;
    _lgate->SendChangeUserNameWithAccountInventoryItemFail(_owner->_clikey, _labelId, _itemInstanceId, reason);
    transit(FIN);
    return true;
}

// 0x27e50
bool ChangeUserNameJob::checkAccountInventoryItemTimeout()
{
    JOB_LOG(Log::LT_ERROR, 400, L"[job], timeout", L"");
    _lgate->SendChangeUserNameWithAccountInventoryItemFail(_owner->_clikey, _labelId, _itemInstanceId, 7);
    transit(FIN);
    return true;
}

// 0x27f70
bool ChangeUserNameJob::changeUserName()
{
    if (_owner->_state != 0x20000)  // CSS_LOBBY
    {
        JOB_LOG(Log::LT_ERROR, 411, L"[job], not in lobby state", L"");
        _lgate->SendChangeUserNameWithAccountInventoryItemFail(_owner->_clikey, _labelId, _itemInstanceId, 5);
        return false;
    }
    if (_owner->_renameUserServiceEntry != nullptr)
    {
        JOB_LOG(Log::LT_ERROR, 417, L"[job], already in rename user service", L"");
        _lgate->SendChangeUserNameWithAccountInventoryItemFail(_owner->_clikey, _labelId, _itemInstanceId, 9);
        return false;
    }

    RenameUserService* const service =
        new (Memory::_Manager[2]->Alloc(sizeof(RenameUserService), kFile, 424)) RenameUserService;
    LobbyService::DB lsdb;
    memset(&lsdb, 0, sizeof(lsdb));
    lsdb.serviceType = 5;
    lsdb.itemInstanceId = _itemInstanceId;
    service->Setup(&lsdb);
    int line;
    if (!service->Start(_owner, _owner->_acb._userName, _newUserName))
    {
        JOB_LOG(Log::LT_ERROR, 442, L"[job], start service fail", L"");
        line = 444;
    }
    else if (!_owner->addRenameUserService(service))
    {
        JOB_LOG(Log::LT_ERROR, 449, L"[job], add service fail", L"");
        line = 451;
    }
    else
    {
        NPLobbyJobTransaction* const t =
            new (Memory::_Manager[2]->Alloc(sizeof(NPLobbyJobTransaction), kFile, 458)) NPLobbyJobTransaction;
        if (!LobbyDaemon::_instance->_npServchmgr->_gameServChannel->SendRequestAuthChangeMyUserNameIncomplete(
                t->Set(this, 71), _owner->_acb._id, _owner->_acb._userName, _newUserName, L"dummy"))
        {
            JOB_LOG(Log::LT_ERROR, 461, L"[job], request change user name fail", L"");
            // LIFT: the original calls the scalar deleting destructor (flag 1) and then Free. Its operator delete is
            // empty.
            t->~NPLobbyJobTransaction();
            Memory::_Manager[2]->Free(t, kFile, 462);
            releaseService();
            return false;
        }
        JOB_LOG(Log::LT_DEBUG, 467, L"[job], request sent", L"");
        return true;
    }
    _lgate->SendChangeUserNameWithAccountInventoryItemFail(_owner->_clikey, _labelId, _itemInstanceId, 2);
    // LIFT: the class operator delete is empty (LobbyService.h). Free gives the memory back.
    delete service;
    Memory::_Manager[2]->Free(service, kFile, line);
    return false;
}

// 0x28580
bool ChangeUserNameJob::changeUserNameResponse(void* param)
{
    StsMsgLib::_StsMsgResponse* const msg = static_cast<StsMsgLib::_StsMsgResponse*>(param);
    if (msg == nullptr)
    {
        JOB_CRASH(474, L"== CRASH == [job], null param");
        _lgate->SendChangeUserNameWithAccountInventoryItemFail(_owner->_clikey, _labelId, _itemInstanceId, 2);
        releaseService();
        return false;
    }
    unsigned int const status = msg->msgInfo.errInfo.nStatusCode;
    if (status != 200 &&
        (status != 400 ||
         _wcsicmp(L"Success", msg->msgInfo.errInfo.pwszReason != nullptr ? msg->msgInfo.errInfo.pwszReason : L"null") != 0))
    {
        JOB_LOG(Log::LT_ERROR, 482, L"[job], change-user-name fail",
                L",np-tid:%u, cmd:%d, type:%d, status-code:%u, reason:%s, error-code:%d", msg->GetTransactionId(),
                msg->GetCommand(), msg->GetMessageType(), status,
                msg->msgInfo.errInfo.pwszReason != nullptr ? msg->msgInfo.errInfo.pwszReason : L"null",
                msg->msgInfo.errInfo.nErrorCode);
        short reason;
        switch (msg->msgInfo.errInfo.nErrorCode)
        {
        case 3003:
        case 3042:
            reason = 217;
            break;
        case 3041:
            reason = 216;
            break;
        case 3336:
            reason = 219;
            break;
        case 3743:
            reason = 218;
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
        _lgate->SendChangeUserNameWithAccountInventoryItemFail(_owner->_clikey, _labelId, _itemInstanceId, reason);
        releaseService();
        return false;
    }
    JOB_LOG(Log::LT_DEBUG, 522, L"[job], user-name changed", L", old-user-name:%s, new-user-name:%s",
            _owner->_acb._userName, _newUserName);
    wcscpy_s(_owner->_acb._userName, 65, _newUserName);
    transit(CONSUME_LOBBY_SERVICE_ITEM);
    return true;
}

// 0x28a80
bool ChangeUserNameJob::changeUserNameExpire()
{
    JOB_LOG(Log::LT_ERROR, 533, L"[job], timeout", L"");
    _lgate->SendChangeUserNameWithAccountInventoryItemFail(_owner->_clikey, _labelId, _itemInstanceId, 2);
    releaseService();
    transit(FIN);
    return true;
}

// 0x28bd0
// After the user name is changed, the client gets the Ok packet also when the item consumption fails.
bool ChangeUserNameJob::consumeLobbyServiceItem()
{
    if (!_acciv->SendConsumeWarehouseItemReq(_tran->Set(this, 167), _labelId, _itemInstanceId, _owner->_acb._id))
    {
        JOB_LOG(Log::LT_ERROR, 545, L"[job], send fail", L"");
        _lgate->SendChangeUserNameWithAccountInventoryItemOk(_owner->_clikey, _newUserName, _labelId, _itemInstanceId,
                                                             _itemDataId);
        releaseService();
        return false;
    }
    JOB_LOG(Log::LT_DEBUG, 551, L"[job], send ok", L"");
    return true;
}

// 0x28dc0
bool ChangeUserNameJob::consumeLobbyServiceItemOk(void*)
{
    _acciv->TRecv(_tran);
    JOB_LOG(Log::LT_DEBUG, 559, L"[job], ok recv", L"");
    transit(FIN_LOBBY_SERVICE);
    return true;
}

// 0x28ed0
bool ChangeUserNameJob::consumeLobbyServiceItemFail(void* param)
{
    _acciv->TRecv(_tran);
    short* const fail = static_cast<short*>(param);
    if (fail == nullptr)
    {
        JOB_CRASH(570, L"== CRASH == [job], invalid param");
        _lgate->SendChangeUserNameWithAccountInventoryItemOk(_owner->_clikey, _newUserName, _labelId, _itemInstanceId,
                                                             _itemDataId);
        releaseService();
        return false;
    }
    JOB_LOG(Log::LT_DEBUG, 578, L"[job], fail recv", L", reason:%d", *fail);
    _lgate->SendChangeUserNameWithAccountInventoryItemOk(_owner->_clikey, _newUserName, _labelId, _itemInstanceId,
                                                         _itemDataId);
    releaseService();
    transit(FIN);
    return true;
}

// 0x291f0
bool ChangeUserNameJob::consumeLobbyServiceItemTimeout()
{
    JOB_LOG(Log::LT_ERROR, 589, L"[job], timeout", L"");
    _lgate->SendChangeUserNameWithAccountInventoryItemOk(_owner->_clikey, _newUserName, _labelId, _itemInstanceId,
                                                         _itemDataId);
    releaseService();
    transit(FIN);
    return true;
}

// 0x29350
bool ChangeUserNameJob::finLobbyService()
{
    RenameUserService* const service = static_cast<RenameUserService*>(_owner->_renameUserServiceEntry);
    if (service == nullptr)
    {
        JOB_LOG(Log::LT_ERROR, 603, L"[job], no such service-entry", L"");
    }
    else if (!service->Finish(_owner, _itemInstanceId, _itemDataId))
    {
        JOB_LOG(Log::LT_ERROR, 610, L"[job], finish service-entry fail", L"");
    }
    else
    {
        releaseService();
        _lgate->SendChangeUserNameWithAccountInventoryItemOk(_owner->_clikey, _newUserName, _labelId, _itemInstanceId,
                                                             _itemDataId);
        JOB_LOG(Log::LT_DEBUG, 621, L"[job], finish service-entry ok", L"");
        transit(FIN);
        return true;
    }
    _lgate->SendChangeUserNameWithAccountInventoryItemOk(_owner->_clikey, _newUserName, _labelId, _itemInstanceId,
                                                         _itemDataId);
    releaseService();
    return false;
}

// 0x29630
void ChangeUserNameJob::releaseService()
{
    LobbyService* const entry = _owner->_renameUserServiceEntry;
    if (entry != nullptr)
    {
        _owner->_renameUserServiceEntry = nullptr;
        // LIFT: the class operator delete is empty (LobbyService.h). Free gives the memory back.
        delete entry;
        Memory::_Manager[2]->Free(entry, kFile, 637);
    }
}
