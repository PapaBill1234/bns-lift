// RenameCharacterJob.obj (LobbyDaemon PDB, 2019 + PDB). Lifted from the pseudocode with PDB types.
#include <new>
#include <string.h>
#include <wchar.h>
#include <winsock2.h>
#include <windows.h>
#include "RenameCharacterJob.h"
#include "AccountInventoryChannel.h"
#include "AlertSender.h"
#include "Character.h"
#include "CliSession.h"
#include "GameWorld.h"
#include "GamedChannel.h"
#include "LiftStub.h"
#include "LobbyConfig.h"
#include "LobbyDB.h"
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

static wchar_t const kFile[] = L"RenameCharacterJob.cpp";

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

// The init logs end with the request parameters (the original reads them from the param, not from the job).
#define INIT_FMT                                                                                                     \
    L", gate-wid:%d, slot-id:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X, label-id:0x%I64X, "                  \
    L"item-instance-id:0x%I64X, item-data-id:%u, new-name:%s"
#define INIT_ARGS(p)                                                                                                 \
    (p)->lgate != nullptr ? ((p)->lgate->_rawChannel != nullptr ? static_cast<short>((p)->lgate->_rawChannel->GetId()) : 0) : 0, \
        (p)->slotid.guid.id1, (p)->slotid.guid.id2, (p)->slotid.guid.id3, (p)->slotid.guid.id4[0],                   \
        (p)->slotid.guid.id4[1], (p)->slotid.guid.id4[2], (p)->slotid.guid.id4[3], (p)->slotid.guid.id4[4],          \
        (p)->slotid.guid.id4[5], (p)->slotid.guid.id4[6], (p)->slotid.guid.id4[7], (p)->labelId,                    \
        (p)->itemInstanceId, (p)->itemDataId, (p)->newName

// PDB enum ECliSessionState (CliSession.h has no copy yet): CSS_LOBBY = 0x20000.
// PDB LobbyService::DB::serviceType of RenameCharacterService: 3.

namespace
{
LobbyJobStateDef const StateDef[] = {{0, L"INIT"},
                                     {1, L"CHECK_ACCOUNT_INVENTORY_ITEM"},
                                     {2, L"REGISTER_SERVICE_ENTRY"},
                                     {3, L"TRY_CONSUME_ACCOUNT_INVENTORY_ITEM"},
                                     {4, L"RENAME_CHARACTER"},
                                     {5, L"FIN_CONSUME_ACCOUNT_INVENTORY_ITEM"},
                                     {6, L"FIN_SERVICE_ENTRY"},
                                     {7, L"FIN"}};  // 0x12dd90
}

LobbyJobDef RenameCharacterJob::_def = {28, StateDef, 7, L"RenameCharacterJob"};  // 0x201a78
// LIFT: RenameCharacterJob::_pool has no definition. The LobbyDaemon ObjectPool module is not in lift_lobbydaemon
// (see CliSession.cpp).

// 0x66ae0
LobbyJobDef const* RenameCharacterJob::GetDefinition() const
{
    return &_def;
}

// 0x66af0
// LIFT: Not done. The body calls _pool.Checkin. ObjPool is not in lift_lobbydaemon.
void RenameCharacterJob::deallocate_me(void*, wchar_t const*, int)
{
    LIFT_STUB(0x66af0);
}

// 0x66b40
RenameCharacterJob::RenameCharacterJob(CliSession* owner)
    : CliSessionJob(owner), _tran(nullptr), _lgate(nullptr), _acciv(nullptr), _gamed(nullptr), _isTargetPc(false),
      _labelId(0), _itemInstanceId(0), _itemDataId(0), _serviceId(0)
{
    _slotid.id[0] = 0;
    _slotid.id[1] = 0;
    memset(_oldName, 0, sizeof(_oldName));
    memset(_newName, 0, sizeof(_newName));
}

// 0x66c50 (scalar deleting destructor 0x66c30)
RenameCharacterJob::~RenameCharacterJob()
{
    if (_tran != nullptr)
        _tran->removeReferenceCount(kFile, 102);
    if (_lgate != nullptr)
        _lgate->removeReferenceCount(kFile, 104);
    if (_gamed != nullptr)
        _gamed->removeReferenceCount(kFile, 106);
}

// 0x66cd0
bool RenameCharacterJob::work(int task, void* param)
{
    bool result = false;
    if (_state == INIT && task == 25)
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
    if (_state == REGISTER_SERVICE_ENTRY && task == 0)
        result = registerServiceEntry();
    if (_state == TRY_CONSUME_ACCOUNT_INVENTORY_ITEM)
    {
        if (task == 0)
            result = tryConsumeAccountInventoryItem();
        else if (task == 159)
        {
            result = tryConsumeAccountInventoryItemOk(param);
            task = 0;
        }
        else if (task == 160)
        {
            result = tryConsumeAccountInventoryItemFail(param);
            task = 0;
        }
        else if (task == 161)
        {
            result = tryConsumeAccountInventoryItemTimeout();
            task = 0;
        }
    }
    if (_state == RENAME_CHARACTER)
    {
        if (task == 0)
            result = renameCharacter();
        else if (task == 126)
        {
            result = renameCharacterOk(param);
            task = 0;
        }
        else if (task == 127)
        {
            result = renameCharacterFail(param);
            task = 0;
        }
        else if (task == 128)
        {
            result = renameCharacterTimeout();
            task = 0;
        }
    }
    if (_state == FIN_CONSUME_ACCOUNT_INVENTORY_ITEM)
    {
        if (task == 0)
            result = finConsumeAccountInventoryItem();
        else if (task == 162)
        {
            result = finConsumeAccountInventoryItemOk(param);
            task = 0;
        }
        else if (task == 163)
        {
            result = finConsumeAccountInventoryItemFail(param);
            task = 0;
        }
        else if (task == 164)
        {
            result = finConsumeAccountInventoryItemTimeout();
            task = 0;
        }
    }
    if (_state == FIN_SERVICE_ENTRY && task == 0)
        return finServiceEntry();
    return result;
}

// 0x66e70
bool RenameCharacterJob::init(void* param)
{
    RenameCharacterWithAccountInventoryItemReqParam* const p =
        static_cast<RenameCharacterWithAccountInventoryItemReqParam*>(param);
    if (p == nullptr || p->lgate == nullptr || (p->slotid.id[0] == 0 && p->slotid.id[1] == 0) || p->labelId == 0 ||
        p->itemInstanceId == 0)
    {
        JOB_LOG(Log::LT_ERROR, 216, L"[job], invalid param", L"");
        transit(FIN);
        return true;
    }

    _tran = new (Memory::_Manager[2]->Alloc(sizeof(LobbyJobTransaction), kFile, 224)) LobbyJobTransaction;
    _lgate = p->lgate;
    _lgate->addReferenceCount(false, kFile, 227);
    _slotid = p->slotid;
    _labelId = p->labelId;
    _itemInstanceId = p->itemInstanceId;
    _itemDataId = p->itemDataId;

    _acciv = LobbyDaemon::_instance->_accountInventoryChannel;
    if (_acciv == nullptr || !_acciv->IsConnected())
    {
        JOB_LOG(Log::LT_ERROR, 237, L"[job], init fail; account-inventory N/A", L"");
        // LIFT: the original sends the ChangeCharacterAppearance fail packet here, not the RenameCharacter one. The
        // client sees this packet. Keep it for parity.
        _lgate->SendChangeCharacterAppearanceWithAccountInventoryItemFail(_owner->_clikey, _slotid, _labelId,
                                                                          _itemInstanceId, 7);
        transit(FIN);
        return true;
    }

    short reason = 0;
    _isTargetPc = LobbyDaemon::_instance->CheckServiceItemDataId(LobbyDaemon::SERVICEITEMTYPE_RENAME_CHARACTER_BY_SYSTEM,
                                                                 _itemDataId);
    if (!_isTargetPc &&
        !LobbyDaemon::_instance->CheckServiceItemDataId(LobbyDaemon::SERVICEITEMTYPE_RENAME_CHARACTER, _itemDataId))
    {
        JOB_LOG(Log::LT_ERROR, 246, L"[job], not proper item", INIT_FMT, INIT_ARGS(p));
        reason = 197;
    }
    else if (_owner->_state != 0x20000)  // CSS_LOBBY
    {
        JOB_LOG(Log::LT_ERROR, 255, L"[job], cli-session not in lobby", INIT_FMT, INIT_ARGS(p));
        reason = 5;
    }
    else
    {
        Character* const pc = _owner->getCharacterInSlot(_slotid);
        if (pc == nullptr)
        {
            JOB_LOG(Log::LT_ERROR, 264, L"[job], init fail; no such character", INIT_FMT, INIT_ARGS(p));
            reason = 193;
        }
        else
        {
            Character::ErrCode const err = pc->IsPlayable();
            if (err != 0)
            {
                JOB_LOG(Log::LT_ERROR, 273, L"[job], init fail; not servicable pc", L", error:%d, pcid:0x%I64X" INIT_FMT,
                        err, pc->_db.pcid, INIT_ARGS(p));
                reason = 194;
            }
            else if (_owner->queryLobbyService(pc) != nullptr)
            {
                JOB_LOG(Log::LT_ERROR, 281, L"[job], init fail; pc already in service", L", pcid:0x%I64X" INIT_FMT,
                        pc->_db.pcid, INIT_ARGS(p));
                reason = 9;
            }
            else
            {
                wcscpy_s(_oldName, 33, pc->_db.name);
                wcscpy_s(_newName, 33, p->newName);
                int line = 0;
                wchar_t const* msg = nullptr;
                _gamed = LobbyDaemon::_instance->_gamedchmgr->Acquire(pc->_db.belongingWorld);
                if (_gamed == nullptr)
                {
                    line = 293;
                    msg = L"[job], init fail; world not available" JOB_SUFFIX L", wid:%d" INIT_FMT;
                }
                else
                {
                    GameWorld* const world = LobbyDaemon::_instance->_gameWorldRegistry->Get(pc->_db.belongingWorld);
                    if (world == nullptr)
                    {
                        JOB_LOG(Log::LT_ERROR, 302, L"[job], init fail; world not found", L", wid:%d" INIT_FMT,
                                pc->_db.belongingWorld, INIT_ARGS(p));
                        reason = 2;
                    }
                    else if (!world->IsLive())
                    {
                        line = 310;
                        msg = L"[job], init fail; world not live" JOB_SUFFIX L", wid:%d" INIT_FMT;
                    }
                    else if (!world->GetDB().entrance &&
                             !_owner->_auth.Authorize(Authority::OP_ENTER_GAMEWORLD_ON_ENTRANCE_NOT_ALLOWED))
                    {
                        line = 318;
                        msg = L"[job], init fail; world not allowed" JOB_SUFFIX L", wid:%d" INIT_FMT;
                    }
                    else
                    {
                        if (LobbyDaemon::_instance->_config->_tencentUICEnable)
                        {
                            // LIFT: the tencent checks send the fail packet and return false. They do not move the
                            // job to FIN (as the original does).
                            short tencentReason = 0;
                            if (_owner->_externalAccountKeySize <= 0)
                            {
                                JOB_LOG(Log::LT_ERROR, 332, L"[job], no external info", L", wid:%d" INIT_FMT,
                                        pc->_db.belongingWorld, INIT_ARGS(p));
                                tencentReason = 2;
                            }
                            else if (!LobbyDaemon::_instance->_tencentUIC->CheckNameFilter(
                                         *reinterpret_cast<unsigned int const*>(_owner->_externalAccountKey), _newName))
                            {
                                JOB_LOG(Log::LT_ERROR, 342, L"[job], filtered by tencent uic", L", wid:%d" INIT_FMT,
                                        pc->_db.belongingWorld, INIT_ARGS(p));
                                tencentReason = 199;
                            }
                            if (tencentReason != 0)
                            {
                                _lgate->SendRenameCharacterWithAccountInventoryItemFail(_owner->_clikey, _slotid, _labelId,
                                                                                        _itemInstanceId, tencentReason);
                                return false;
                            }
                        }
                        LobbyConfig const* const config = LobbyDaemon::_instance->_config;
                        RuleSet::CheckNameResult const check = RuleSet::CheckName(
                            LobbyDaemon::_instance->_localeset, _newName, config->_allowedCharacterNameLenMin,
                            config->_allowedCharacterNameLenMax, config->_allowedCharacterNameSpaceAmount,
                            config->_enableNumericForCharacterName, config->_forceSentenceCaseForCharacterName,
                            config->_enableMultilingualCharacterName, config->_forbiddenCharactersForCharacterName);
                        if (check != RuleSet::CHECKNAME_OK)
                        {
                            JOB_LOG(Log::LT_ERROR, 360, L"[job], check name fail", L", error:%d" INIT_FMT, check,
                                    INIT_ARGS(p));
                            if (check == RuleSet::CHECKNAME_INVALID_PARAMTER)
                                reason = 6;
                            else if (check > RuleSet::CHECKNAME_INVALID_PARAMTER && check <= RuleSet::CHECKNAME_MULTILINGUAL)
                                reason = 198;
                            else if (check == RuleSet::CHECKNAME_FORBIDDEN)
                                reason = 199;
                            else
                                reason = 2;
                        }
                        else
                        {
                            int dbrtn = 0;
                            if (!LobbyDB::CheckValidityOfCharacterName(dbrtn, _newName,
                                                                       config->_enableMultilingualCharacterName))
                            {
                                JOB_LOG(Log::LT_ERROR, 394, L"[job], check db name validity fail", L", dbrtn:%d" INIT_FMT,
                                        dbrtn, INIT_ARGS(p));
                                if (dbrtn == 1)
                                    reason = 6;
                                else if (dbrtn == 2)
                                    reason = 200;
                                else if (dbrtn == 3)
                                    reason = 201;
                                else
                                    reason = 2;
                            }
                            else
                            {
                                JOB_LOG(Log::LT_DEBUG, 419, L"[job], init ok", L", old-name:%s" INIT_FMT, _oldName,
                                        INIT_ARGS(p));
                                transit(CHECK_ACCOUNT_INVENTORY_ITEM);
                                return true;
                            }
                        }
                    }
                }
                if (msg != nullptr)
                {
                    Log::Write(Log::LT_ERROR, kFile, line, msg, JOB_ARGS, pc->_db.belongingWorld, INIT_ARGS(p));
                    reason = 202;
                }
            }
        }
    }
    _lgate->SendRenameCharacterWithAccountInventoryItemFail(_owner->_clikey, _slotid, _labelId, _itemInstanceId, reason);
    transit(FIN);
    return true;
}

// 0x68e80
bool RenameCharacterJob::checkAccountInventoryItem()
{
    unsigned long long ownerPcId = 0;
    if (_isTargetPc)
    {
        Character* const pc = _owner->getCharacterInSlot(_slotid);
        if (pc == nullptr)
        {
            JOB_LOG(Log::LT_ERROR, 431, L"[job], not sent; fail to get character in slot, ", L"");
            _lgate->SendRenameCharacterWithAccountInventoryItemFail(_owner->_clikey, _slotid, _labelId, _itemInstanceId, 7);
            transit(FIN);
            return true;
        }
        ownerPcId = pc->_db.pcid;
    }
    if (!_acciv->SendRetrieveSingleWarehouseItemReq(_tran->Set(this, 158), _itemInstanceId, _owner->_acb._id, ownerPcId))
    {
        JOB_LOG(Log::LT_ERROR, 440, L"[job], not sent", L"");
        _lgate->SendRenameCharacterWithAccountInventoryItemFail(_owner->_clikey, _slotid, _labelId, _itemInstanceId, 7);
        transit(FIN);
        return true;
    }
    JOB_LOG(Log::LT_DEBUG, 446, L"[job], sent", L"");
    return true;
}

// 0x69100
bool RenameCharacterJob::checkAccountInventoryItemOk(void* param)
{
    _acciv->TRecv(_tran);
    RetrieveSingleWarehouseItemOkParam* const ok = static_cast<RetrieveSingleWarehouseItemOkParam*>(param);
    short reason;
    if (ok == nullptr)
    {
        JOB_CRASH(455, L"== CRASH == [job], invalid param");
        reason = 2;
    }
    else
    {
        // The original does not check the item pointer here.
        LobbyServiceItem const* const item = ok->item;
        JOB_LOG(Log::LT_DEBUG, 465, L"[job], ok recv",
                L", item-instance-id:0x%I64X, label-id:0x%I64X, item-data-id:%u, state:%d", item->instanceId,
                item->labelId, item->dataId, item->state);
        if (_itemDataId != item->dataId)
        {
            JOB_LOG(Log::LT_ERROR, 468, L"[job], item-data-id mismatch",
                    L", request-item-data-id:%u, required-item-data-id:%u", _itemDataId, item->dataId);
            reason = 197;
        }
        else if (item->state != 1)
        {
            JOB_LOG(Log::LT_ERROR, 475, L"[job], unusable item", L"");
            reason = 196;
        }
        else
        {
            transit(REGISTER_SERVICE_ENTRY);
            return true;
        }
    }
    _lgate->SendRenameCharacterWithAccountInventoryItemFail(_owner->_clikey, _slotid, _labelId, _itemInstanceId, reason);
    transit(FIN);
    return true;
}

// 0x694c0
bool RenameCharacterJob::checkAccountInventoryItemFail(void* param)
{
    _acciv->TRecv(_tran);
    short* const fail = static_cast<short*>(param);
    short reason;
    if (fail == nullptr)
    {
        JOB_CRASH(491, L"== CRASH == [job], invalid param");
        reason = 2;
    }
    else
    {
        JOB_LOG(Log::LT_DEBUG, 500, L"[job], fail recv", L", reason:%d", *fail);
        reason = 2;
        if (*fail == 20)
            reason = 195;
    }
    _lgate->SendRenameCharacterWithAccountInventoryItemFail(_owner->_clikey, _slotid, _labelId, _itemInstanceId, reason);
    transit(FIN);
    return true;
}

// 0x69730
bool RenameCharacterJob::checkAccountInventoryItemTimeout()
{
    JOB_LOG(Log::LT_ERROR, 520, L"[job], timeout", L"");
    _lgate->SendRenameCharacterWithAccountInventoryItemFail(_owner->_clikey, _slotid, _labelId, _itemInstanceId, 7);
    transit(FIN);
    return true;
}

// 0x69850
bool RenameCharacterJob::registerServiceEntry()
{
    Character* const pc = _owner->getCharacterInSlot(_slotid);
    short reason;
    if (pc == nullptr)
    {
        JOB_LOG(Log::LT_ERROR, 534, L"[job], register fail; no such character", L"");
        reason = 193;
    }
    else if (pc->_db.block || pc->_db.state != 2 || pc->_status.in_playing || pc->_status.in_service)
    {
        JOB_LOG(Log::LT_ERROR, 543, L"[job], register fail; not servicable pc", L"");
        reason = 194;
    }
    else if (_owner->queryLobbyService(pc) != nullptr)
    {
        JOB_LOG(Log::LT_ERROR, 551, L"[job], register fail; pc already in service", L"");
        reason = 9;
    }
    else
    {
        RenameCharacterService* const service =
            new (Memory::_Manager[2]->Alloc(sizeof(RenameCharacterService), kFile, 557)) RenameCharacterService;
        LobbyService::DB lsdb;
        memset(&lsdb, 0, sizeof(lsdb));
        lsdb.serviceType = 3;
        lsdb.itemInstanceId = _itemInstanceId;
        RenameCharacterService::DB db;
        db.pcid = pc->_db.pcid;
        service->Setup(&lsdb, &db);
        int line;
        if (!service->Start(_owner, _itemDataId, _newName,
                            LobbyDaemon::_instance->_config->_characterNameReuseLimitDuration))
        {
            LobbyError const error = TLobbyError;
            JOB_LOG(Log::LT_ERROR, 583, L"[job], start new lobby service fail", L", error:%d", error);
            short startReason;
            if (error == LOBERR_NAME_DUPLICATED)
                startReason = 200;
            else if (error == LOBERR_NAME_LIMITED)
                startReason = 201;
            else
                startReason = 2;
            _lgate->SendRenameCharacterWithAccountInventoryItemFail(_owner->_clikey, _slotid, _labelId, _itemInstanceId,
                                                                    startReason);
            line = 601;
        }
        else if (!_owner->addLobbyService(service))
        {
            JOB_LOG(Log::LT_ERROR, 608, L"[job], add new lobby service fail", L", lobby-service-id:0x%I64X",
                    service->GetDB().serviceId);
            _lgate->SendRenameCharacterWithAccountInventoryItemFail(_owner->_clikey, _slotid, _labelId, _itemInstanceId,
                                                                    203);
            line = 610;
        }
        else
        {
            _serviceId = service->GetDB().serviceId;
            if (!pc->SetName(_newName))
            {
                JOB_LOG(Log::LT_ERROR, 619, L"[job], set new name fail", L"");
                _lgate->SendRenameCharacterWithAccountInventoryItemFail(_owner->_clikey, _slotid, _labelId,
                                                                        _itemInstanceId, 203);
                transit(FIN);
                return true;
            }
            JOB_LOG(Log::LT_DEBUG, 625, L"[job], register ok", L", lobby-service-id:0x%I64X", _serviceId);
            transit(TRY_CONSUME_ACCOUNT_INVENTORY_ITEM);
            return true;
        }
        // LIFT: the class operator delete is empty (LobbyService.h). Free gives the memory back.
        delete service;
        Memory::_Manager[2]->Free(service, kFile, line);
        transit(FIN);
        return true;
    }
    _lgate->SendRenameCharacterWithAccountInventoryItemFail(_owner->_clikey, _slotid, _labelId, _itemInstanceId, reason);
    transit(FIN);
    return true;
}

// 0x69f70
bool RenameCharacterJob::tryConsumeAccountInventoryItem()
{
    if (!_acciv->SendTryWarehouseItemConsumptionReq(_tran->Set(this, 161), _labelId, _itemInstanceId, _owner->_acb._id))
    {
        JOB_LOG(Log::LT_ERROR, 635, L"[job], send fail", L"");
        _lgate->SendRenameCharacterWithAccountInventoryItemFail(_owner->_clikey, _slotid, _labelId, _itemInstanceId, 203);
        transit(FIN);
    }
    else
    {
        JOB_LOG(Log::LT_DEBUG, 641, L"[job], send ok", L"");
    }
    return true;
}

// 0x6a120
bool RenameCharacterJob::tryConsumeAccountInventoryItemOk(void*)
{
    _acciv->TRecv(_tran);
    JOB_LOG(Log::LT_DEBUG, 650, L"[job], ok recv", L"");
    RenameCharacterService* const service =
        static_cast<RenameCharacterService*>(_owner->getLobbyServiceByType(_serviceId, 3));
    int line;
    wchar_t const* msg;
    if (service == nullptr)
    {
        line = 655;
        msg = L"[job], no such service-entry" JOB_SUFFIX;
    }
    else if (!service->ConsumeItemTried(_owner))
    {
        line = 663;
        msg = L"[job], update lobby service as 'consume item tried' fail" JOB_SUFFIX;
    }
    else
    {
        JOB_LOG(Log::LT_DEBUG, 669, L"[job], try consume item ok", L"");
        transit(RENAME_CHARACTER);
        return true;
    }
    JOB_LOGV(Log::LT_ERROR, line, msg);
    _lgate->SendRenameCharacterWithAccountInventoryItemFail(_owner->_clikey, _slotid, _labelId, _itemInstanceId, 203);
    transit(FIN);
    return true;
}

// 0x6a3f0
bool RenameCharacterJob::tryConsumeAccountInventoryItemFail(void* param)
{
    _acciv->TRecv(_tran);
    short* const fail = static_cast<short*>(param);
    if (fail == nullptr)
        JOB_CRASH(681, L"== CRASH == [job], invalid param");
    else
        JOB_LOG(Log::LT_DEBUG, 689, L"[job], fail recv", L", reason:%d", *fail);
    _lgate->SendRenameCharacterWithAccountInventoryItemFail(_owner->_clikey, _slotid, _labelId, _itemInstanceId, 203);
    transit(FIN);
    return true;
}

// 0x6a650
bool RenameCharacterJob::tryConsumeAccountInventoryItemTimeout()
{
    JOB_LOG(Log::LT_ERROR, 699, L"[job], timeout", L"");
    _lgate->SendRenameCharacterWithAccountInventoryItemFail(_owner->_clikey, _slotid, _labelId, _itemInstanceId, 203);
    transit(FIN);
    return true;
}

// 0x6a770
bool RenameCharacterJob::renameCharacter()
{
    Character* const pc = _owner->getCharacterInSlot(_slotid);
    if (pc == nullptr)
    {
        JOB_LOG(Log::LT_ERROR, 712, L"[job], no such pc", L"");
        _lgate->SendRenameCharacterWithAccountInventoryItemFail(_owner->_clikey, _slotid, _labelId, _itemInstanceId, 203);
        transit(FIN);
    }
    else
    {
        // The original does not check the send result.
        _gamed->SendRenameCharacterReq(_tran->Set(this, 128), _serviceId, pc->_db.pcid, _oldName, _newName);
        JOB_LOG(Log::LT_DEBUG, 720, L"[job], sent", L"");
    }
    return true;
}

// 0x6a9a0
bool RenameCharacterJob::renameCharacterOk(void* param)
{
    _gamed->TRecv(_tran);
    if (param == nullptr)
    {
        JOB_CRASH(731, L"== CRASH == [job], invalid param");
    }
    else
    {
        JOB_LOG(Log::LT_DEBUG, 739, L"[job], ok recv", L"");
        int line;
        wchar_t const* msg;
        RenameCharacterService* service = nullptr;
        if (_owner->getCharacterInSlot(_slotid) == nullptr)
        {
            line = 744;
            msg = L"[job], no such pc" JOB_SUFFIX;
        }
        else if ((service = static_cast<RenameCharacterService*>(_owner->getLobbyServiceByType(_serviceId, 3))) == nullptr)
        {
            line = 753;
            msg = L"[job], no such service-entry" JOB_SUFFIX;
        }
        else if (!service->TaskDone(_owner))
        {
            line = 761;
            msg = L"[job], set service-entry as 'served' fail" JOB_SUFFIX;
        }
        else
        {
            JOB_LOG(Log::LT_DEBUG, 767, L"[job], set service-entry as 'served' ok", L"");
            transit(FIN_CONSUME_ACCOUNT_INVENTORY_ITEM);
            return true;
        }
        JOB_LOGV(Log::LT_ERROR, line, msg);
    }
    _lgate->SendRenameCharacterWithAccountInventoryItemFail(_owner->_clikey, _slotid, _labelId, _itemInstanceId, 203);
    transit(FIN);
    return true;
}

// 0x6ae30
bool RenameCharacterJob::renameCharacterFail(void* param)
{
    _gamed->TRecv(_tran);
    short* const fail = static_cast<short*>(param);
    if (fail == nullptr)
        JOB_CRASH(779, L"== CRASH == [job], invalid param");
    else
        JOB_LOG(Log::LT_DEBUG, 787, L"[job], fail recv", L", reason:%d", *fail);
    _lgate->SendRenameCharacterWithAccountInventoryItemFail(_owner->_clikey, _slotid, _labelId, _itemInstanceId, 203);
    transit(FIN);
    return true;
}

// 0x6b090
bool RenameCharacterJob::renameCharacterTimeout()
{
    JOB_LOG(Log::LT_ERROR, 797, L"[job], timeout", L"");
    _lgate->SendRenameCharacterWithAccountInventoryItemFail(_owner->_clikey, _slotid, _labelId, _itemInstanceId, 203);
    transit(FIN);
    return true;
}

// 0x6b1b0
bool RenameCharacterJob::finConsumeAccountInventoryItem()
{
    if (!_acciv->SendFinishWarehouseItemConsumptionReq(_tran->Set(this, 164), _labelId, _itemInstanceId,
                                                       _owner->_acb._id, 0))
    {
        JOB_LOG(Log::LT_ERROR, 814, L"[job], send fail", L"");
        _lgate->SendRenameCharacterWithAccountInventoryItemFail(_owner->_clikey, _slotid, _labelId, _itemInstanceId, 203);
        transit(FIN);
    }
    else
    {
        JOB_LOG(Log::LT_DEBUG, 820, L"[job], sent", L"");
    }
    return true;
}

// 0x6b360
bool RenameCharacterJob::finConsumeAccountInventoryItemOk(void*)
{
    _acciv->TRecv(_tran);
    JOB_LOG(Log::LT_DEBUG, 829, L"[job], ok recv", L"");
    RenameCharacterService* const service = static_cast<RenameCharacterService*>(_owner->getLobbyService(_serviceId));
    int line;
    wchar_t const* msg;
    if (service == nullptr)
    {
        line = 834;
        msg = L"[job], no such service-entry" JOB_SUFFIX;
    }
    else if (!service->ConsumeItemFinished(_owner))
    {
        line = 842;
        msg = L"[job], set service-entry as 'consume item fin' fail" JOB_SUFFIX;
    }
    else
    {
        JOB_LOG(Log::LT_DEBUG, 848, L"[job], set service-entry as 'consume item fin' ok", L"");
        transit(FIN_SERVICE_ENTRY);
        return true;
    }
    JOB_LOGV(Log::LT_ERROR, line, msg);
    _lgate->SendRenameCharacterWithAccountInventoryItemFail(_owner->_clikey, _slotid, _labelId, _itemInstanceId, 203);
    transit(FIN);
    return true;
}

// 0x6b630
bool RenameCharacterJob::finConsumeAccountInventoryItemFail(void* param)
{
    _acciv->TRecv(_tran);
    short* const fail = static_cast<short*>(param);
    if (fail == nullptr)
        JOB_CRASH(860, L"== CRASH == [job], invalid param");
    else
        JOB_LOG(Log::LT_DEBUG, 868, L"[job], fail recv", L", reason:%d", *fail);
    _lgate->SendRenameCharacterWithAccountInventoryItemFail(_owner->_clikey, _slotid, _labelId, _itemInstanceId, 203);
    transit(FIN);
    return true;
}

// 0x6b890
bool RenameCharacterJob::finConsumeAccountInventoryItemTimeout()
{
    JOB_LOG(Log::LT_ERROR, 878, L"[job], timeout", L"");
    _lgate->SendRenameCharacterWithAccountInventoryItemFail(_owner->_clikey, _slotid, _labelId, _itemInstanceId, 203);
    transit(FIN);
    return true;
}

// 0x6b9b0
bool RenameCharacterJob::finServiceEntry()
{
    RenameCharacterService* const service = static_cast<RenameCharacterService*>(_owner->getLobbyService(_serviceId));
    int line;
    wchar_t const* msg;
    if (service == nullptr)
    {
        line = 892;
        msg = L"[job], no such service-entry" JOB_SUFFIX;
    }
    else if (!service->Finish(_owner))
    {
        line = 900;
        msg = L"[job], finish service-entry fail" JOB_SUFFIX;
    }
    else
    {
        _owner->removeLobbyService(service->GetDB().serviceId);
        // LIFT: the class operator delete is empty (LobbyService.h). Free gives the memory back.
        delete service;
        Memory::_Manager[2]->Free(service, kFile, 908);
        if (LobbyDaemon::_instance->_config->_enableFriendMessageNotification)
            sendFriendMessageToNP();
        _lgate->SendRenameCharacterWithAccountInventoryItemOk(_owner->_clikey, _slotid, _newName, _labelId,
                                                              _itemInstanceId);
        JOB_LOG(Log::LT_DEBUG, 918, L"[job], finish service-entry ok", L"");
        transit(FIN);
        return true;
    }
    JOB_LOGV(Log::LT_ERROR, line, msg);
    _lgate->SendRenameCharacterWithAccountInventoryItemFail(_owner->_clikey, _slotid, _labelId, _itemInstanceId, 203);
    transit(FIN);
    return true;
}

// 0x6bc50
void RenameCharacterJob::sendFriendMessageToNP()
{
    NPGameServiceChannel* const channel = LobbyDaemon::_instance->_npServchmgr->_gameServChannel;
    if (channel == nullptr)
        return;
    Character* const pc = _owner->getCharacterInSlot(_slotid);
    if (pc == nullptr)
        return;

    StsMsgLib::_StsMsgRequestFriendSendMessage::Contents contents;
    contents.nFieldCount = 1;
    contents.pFields = static_cast<StsMsgLib::_StsMsgRequestFriendSendMessage::Contents::Field*>(
        Memory::_Manager[2]->AllocZero(sizeof(StsMsgLib::_StsMsgRequestFriendSendMessage::Contents::Field), kFile, 937));
    contents.pFields->pszKey = static_cast<char*>(Memory::_Manager[2]->AllocZero(KEY_NAME_LENGTH, kFile, 938));
    contents.pFields->pwszValue =
        static_cast<wchar_t*>(Memory::_Manager[2]->AllocZero(VALUE_NAME_LENGTH * sizeof(wchar_t), kFile, 939));
    strncpy_s(contents.pFields->pszKey, KEY_NAME_LENGTH, "name", _TRUNCATE);
    _snwprintf_s(contents.pFields->pwszValue, VALUE_NAME_LENGTH, _TRUNCATE, L"%I64d.%s", pc->_db.pcid, _newName);

    LobbyConfig const* const config = LobbyDaemon::_instance->_config;
    if (!channel->SendRequestFriendSendMessage(nullptr, _owner->_acb._id, config->_friendMessageRecipientAppIdList,
                                               config->_friendMessageRecipientAppIdCount, L"all", nullptr,
                                               L"charNameChanged", contents))
    {
        JOB_LOG(Log::LT_ERROR, 950, L"[job], finish service-entry; failed to send friend message to np", L"");
    }
    else
    {
        JOB_LOG(Log::LT_DEBUG, 955, L"[job], finish service-entry; send friend message to np ok", L", value:%s",
                contents.pFields->pwszValue);
    }

    if (contents.pFields->pszKey != nullptr)
    {
        Memory::_Manager[2]->Free(contents.pFields->pszKey, kFile, 964);
        contents.pFields->pszKey = nullptr;
    }
    if (contents.pFields->pwszValue != nullptr)
    {
        Memory::_Manager[2]->Free(contents.pFields->pwszValue, kFile, 969);
        contents.pFields->pwszValue = nullptr;
    }
    Memory::_Manager[2]->Free(contents.pFields, kFile, 973);
}
