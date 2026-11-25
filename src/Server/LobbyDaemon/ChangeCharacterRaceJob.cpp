// ChangeCharacterRaceJob.obj (LobbyDaemon PDB, 2019 + PDB). Lifted from the pseudocode with PDB types.
#include <new>
#include <string.h>
#include <wchar.h>
#include <winsock2.h>
#include <windows.h>
#include "ChangeCharacterRaceJob.h"
#include "AccountInventoryChannel.h"
#include "AlertSender.h"
#include "Character.h"
#include "CliSession.h"
#include "GameWorld.h"
#include "GamedChannel.h"
#include "LiftStub.h"
#include "LobbyDB.h"
#include "LobbyDaemon.h"
#include "LobbyGateChannel.h"
#include "LobbyGoodsTypes.h"
#include "LobbyJobParams.h"
#include "LobbyService.h"
#include "Log.h"
#include "Memory.h"
#include "MemoryManager.h"
#include "TransactionChannel.h"

static wchar_t const kFile[] = L"ChangeCharacterRaceJob.cpp";

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
#define SLOT_FMT L", slot-id:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X"
#define SLOT_ARGS(s)                                                                                                 \
    (s).guid.id1, (s).guid.id2, (s).guid.id3, (s).guid.id4[0], (s).guid.id4[1], (s).guid.id4[2], (s).guid.id4[3],   \
        (s).guid.id4[4], (s).guid.id4[5], (s).guid.id4[6], (s).guid.id4[7]

// PDB enum ECliSessionState (CliSession.h has no copy yet): CSS_LOBBY = 0x20000.
// PDB LobbyService::DB::serviceType of ChangeCharacterRaceService: 8.

namespace
{
LobbyJobStateDef const StateDef[] = {{0, L"INIT"},
                                     {1, L"CHECK_ACCOUNT_INVENTORY_ITEM"},
                                     {2, L"REGISTER_SERVICE_ENTRY"},
                                     {3, L"TRY_CONSUME_ACCOUNT_INVENTORY_ITEM"},
                                     {4, L"CHANGE_CHARACTER_RACE"},
                                     {5, L"FIN_CONSUME_ACCOUNT_INVENTORY_ITEM"},
                                     {6, L"FIN_SERVICE_ENTRY"},
                                     {7, L"FIN"}};  // 0x12e2c0
}

LobbyJobDef ChangeCharacterRaceJob::_def = {41, StateDef, 7, L"ChangeCharacterRaceJob"};  // 0x201fa0
// LIFT: ChangeCharacterRaceJob::_pool has no definition. The LobbyDaemon ObjectPool module is not in lift_lobbydaemon
// (see CliSession.cpp).

// 0x1ea40
LobbyJobDef const* ChangeCharacterRaceJob::GetDefinition() const
{
    return &_def;
}

// 0x1ea50
// LIFT: Not done. The body calls _pool.Checkin. ObjPool is not in lift_lobbydaemon.
void ChangeCharacterRaceJob::deallocate_me(void*, wchar_t const*, int)
{
    LIFT_STUB(0x1ea50);
}

// 0x1eaa0
ChangeCharacterRaceJob::ChangeCharacterRaceJob(CliSession* owner)
    : CliSessionJob(owner), _tran(nullptr), _lgate(nullptr), _acciv(nullptr), _gamed(nullptr), _labelId(0),
      _itemInstanceId(0), _newRace(0), _newSex(0), _makingData(nullptr), _makingDataSize(0), _itemDataId(0),
      _serviceId(0)
{
    _slotid.id[0] = 0;
    _slotid.id[1] = 0;
}

// 0x1eb40 (scalar deleting destructor 0x1eb20)
ChangeCharacterRaceJob::~ChangeCharacterRaceJob()
{
    if (_tran != nullptr)
        _tran->removeReferenceCount(kFile, 95);
    if (_lgate != nullptr)
        _lgate->removeReferenceCount(kFile, 97);
    if (_gamed != nullptr)
        _gamed->removeReferenceCount(kFile, 99);
    if (_makingData != nullptr)
    {
        Memory::_Manager[2]->Free(_makingData, kFile, 101);
        _makingData = nullptr;
    }
}

// 0x1ebf0
bool ChangeCharacterRaceJob::work(int task, void* param)
{
    bool result = false;
    if (_state == INIT && task == 32)
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
    if (_state == CHANGE_CHARACTER_RACE)
    {
        if (task == 0)
            result = changeCharacterRace();
        else if (task == 139)
        {
            result = changeCharacterRaceOk(param);
            task = 0;
        }
        else if (task == 140)
        {
            result = changeCharacterRaceFail(param);
            task = 0;
        }
        else if (task == 141)
        {
            result = changeCharacterRaceTimeout();
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

// 0x1ed90
bool ChangeCharacterRaceJob::init(void* param)
{
    ChangeCharacterRaceWithAccountInventoryItemReqParam* const p =
        static_cast<ChangeCharacterRaceWithAccountInventoryItemReqParam*>(param);
    if (p == nullptr || p->lgate == nullptr || (p->slotid.id[0] == 0 && p->slotid.id[1] == 0) || p->newRace <= 0 ||
        p->newSex <= 0 || p->makingData == nullptr || p->makingDataSize == 0 || p->labelId == 0 ||
        p->itemInstanceId == 0)
    {
        JOB_LOG(Log::LT_ERROR, 212, L"[job], invalid param", L"");
        transit(FIN);
        return true;
    }

    _tran = new (Memory::_Manager[2]->Alloc(sizeof(LobbyJobTransaction), kFile, 217)) LobbyJobTransaction;
    _lgate = p->lgate;
    _slotid = p->slotid;
    _labelId = p->labelId;
    _itemInstanceId = p->itemInstanceId;
    _newRace = p->newRace;
    _newSex = p->newSex;
    _makingData = static_cast<char*>(Memory::_Manager[2]->AllocZero(p->makingDataSize, kFile, 225));
    memcpy(_makingData, p->makingData, p->makingDataSize);
    _makingDataSize = p->makingDataSize;
    _itemDataId = p->itemDataId;
    _lgate->addReferenceCount(false, kFile, 230);

    short reason = 0;
    _acciv = LobbyDaemon::_instance->_accountInventoryChannel;
    if (_acciv == nullptr || !_acciv->IsConnected())
    {
        JOB_LOG(Log::LT_ERROR, 235, L"[job], init fail; account-inventory N/A", L"");
        reason = 7;
    }
    else if (!LobbyDaemon::_instance->CheckServiceItemDataId(LobbyDaemon::SERVICEITEMTYPE_CHANGE_CHARACTER_RACE,
                                                             _itemDataId))
    {
        JOB_LOG(Log::LT_ERROR, 243, L"[job], not proper item", L", item-data-id:%u", _itemDataId);
        reason = 190;
    }
    else if (_owner->_state != 0x20000)  // CSS_LOBBY
    {
        JOB_LOG(Log::LT_ERROR, 252, L"[job], cli-session not in lobby", L"");
        reason = 5;
    }
    else
    {
        Character* const pc = _owner->getCharacterInSlot(_slotid);
        if (pc == nullptr)
        {
            JOB_LOG(Log::LT_ERROR, 261, L"[job], init fail; no such character", SLOT_FMT, SLOT_ARGS(_slotid));
            reason = 186;
        }
        else
        {
            Character::ErrCode const err = pc->IsPlayable();
            if (err != 0)
            {
                JOB_LOG(Log::LT_ERROR, 270, L"[job], init fail; not servicable pc", L", error:%d, pcid:0x%I64X", err,
                        pc->_db.pcid);
                reason = 187;
            }
            else if (_owner->queryLobbyService(pc) != nullptr)
            {
                JOB_LOG(Log::LT_ERROR, 278, L"[job], init fail; pc already in service", L", pcid:0x%I64X", pc->_db.pcid);
                reason = 9;
            }
            else
            {
                int line = 0;
                wchar_t const* msg = nullptr;
                _gamed = LobbyDaemon::_instance->_gamedchmgr->Acquire(pc->_db.belongingWorld);
                if (_gamed == nullptr)
                {
                    line = 287;
                    msg = L"[job], init fail; world not available" JOB_SUFFIX L", wid:%d";
                }
                else
                {
                    GameWorld* const world = LobbyDaemon::_instance->_gameWorldRegistry->Get(pc->_db.belongingWorld);
                    if (world == nullptr)
                    {
                        JOB_LOG(Log::LT_ERROR, 296, L"[job], init fail; world not found", L", wid:%d",
                                pc->_db.belongingWorld);
                        reason = 2;
                    }
                    else if (!world->IsLive())
                    {
                        line = 304;
                        msg = L"[job], init fail; world not live" JOB_SUFFIX L", wid:%d";
                    }
                    else if (!world->GetDB().entrance &&
                             !_owner->_auth.Authorize(Authority::OP_ENTER_GAMEWORLD_ON_ENTRANCE_NOT_ALLOWED))
                    {
                        line = 312;
                        msg = L"[job], init fail; world not allowed" JOB_SUFFIX L", wid:%d";
                    }
                    else
                    {
                        JOB_LOG(Log::LT_DEBUG, 320, L"[job], init ok",
                                L", gate-wid:%d, wid:%d" SLOT_FMT
                                L", label-id:0x%I64X, item-instance-id:0x%I64X, item-data-id:%u, making-data-size:%d",
                                _lgate != nullptr ? (_lgate->_rawChannel != nullptr ? static_cast<short>(_lgate->_rawChannel->GetId()) : 0) : 0,
                                pc->_db.belongingWorld, SLOT_ARGS(_slotid), _labelId, _itemInstanceId, _itemDataId,
                                _makingDataSize);
                    }
                }
                if (msg != nullptr)
                {
                    Log::Write(Log::LT_ERROR, kFile, line, msg, JOB_ARGS, pc->_db.belongingWorld);
                    reason = 191;
                }
            }
        }
    }
    int next = CHECK_ACCOUNT_INVENTORY_ITEM;
    if (reason != 0)
    {
        _lgate->SendChangeCharacterRaceWithAccountInventoryItemFail(_owner->_clikey, _slotid, _labelId, _itemInstanceId,
                                                                    reason);
        next = FIN;
    }
    transit(next);
    return true;
}

// 0x1fa00
bool ChangeCharacterRaceJob::checkAccountInventoryItem()
{
    if (!_acciv->SendRetrieveSingleWarehouseItemReq(_tran->Set(this, 158), _itemInstanceId, _owner->_acb._id, 0))
    {
        JOB_LOG(Log::LT_ERROR, 330, L"[job], not sent", L"");
        _lgate->SendChangeCharacterRaceWithAccountInventoryItemFail(_owner->_clikey, _slotid, _labelId, _itemInstanceId, 7);
        transit(FIN);
    }
    else
    {
        JOB_LOG(Log::LT_DEBUG, 336, L"[job], sent", L"");
    }
    return true;
}

// 0x1fbb0
bool ChangeCharacterRaceJob::checkAccountInventoryItemOk(void* param)
{
    _acciv->TRecv(_tran);
    RetrieveSingleWarehouseItemOkParam* const ok = static_cast<RetrieveSingleWarehouseItemOkParam*>(param);
    short reason;
    if (ok == nullptr)
    {
        JOB_CRASH(346, L"== CRASH == [job], invalid param");
        reason = 2;
    }
    else if (ok->item == nullptr)
    {
        JOB_LOG(Log::LT_ERROR, 356, L"[job], null item", L"");
        reason = 2;
    }
    else
    {
        LobbyServiceItem const* const item = ok->item;
        JOB_LOG(Log::LT_DEBUG, 363, L"[job], ok recv",
                L", item-instance-id:0x%I64X, label-id:0x%I64X, item-data-id:%u, state:%d", item->instanceId,
                item->labelId, item->dataId, item->state);
        if (_itemDataId != item->dataId)
        {
            JOB_LOG(Log::LT_ERROR, 366, L"[job], item-data-id mismatch",
                    L", request-item-data-id:%u, required-item-data-id:%u", _itemDataId, item->dataId);
            reason = 190;
        }
        else if (item->state != 1)
        {
            JOB_LOG(Log::LT_ERROR, 373, L"[job], unusable item", L"");
            reason = 189;
        }
        else
        {
            transit(REGISTER_SERVICE_ENTRY);
            return true;
        }
    }
    _lgate->SendChangeCharacterRaceWithAccountInventoryItemFail(_owner->_clikey, _slotid, _labelId, _itemInstanceId,
                                                                reason);
    transit(FIN);
    return true;
}

// 0x20020
bool ChangeCharacterRaceJob::checkAccountInventoryItemFail(void* param)
{
    _acciv->TRecv(_tran);
    short* const fail = static_cast<short*>(param);
    short reason;
    if (fail == nullptr)
    {
        JOB_CRASH(389, L"== CRASH == [job], invalid param");
        reason = 2;
    }
    else
    {
        JOB_LOG(Log::LT_DEBUG, 398, L"[job], fail recv", L", reason:%d", *fail);
        reason = 2;
        if (*fail == 20)
            reason = 188;
    }
    _lgate->SendChangeCharacterRaceWithAccountInventoryItemFail(_owner->_clikey, _slotid, _labelId, _itemInstanceId,
                                                                reason);
    transit(FIN);
    return true;
}

// 0x20290
bool ChangeCharacterRaceJob::checkAccountInventoryItemTimeout()
{
    JOB_LOG(Log::LT_ERROR, 418, L"[job], timeout", L"");
    _lgate->SendChangeCharacterRaceWithAccountInventoryItemFail(_owner->_clikey, _slotid, _labelId, _itemInstanceId, 7);
    transit(FIN);
    return true;
}

// 0x203b0
bool ChangeCharacterRaceJob::registerServiceEntry()
{
    Character* const pc = _owner->getCharacterInSlot(_slotid);
    short reason;
    if (pc == nullptr)
    {
        JOB_LOG(Log::LT_ERROR, 432, L"[job], init fail; no such character", L"");
        reason = 186;
    }
    else if (pc->_db.block || pc->_db.state != 2 || pc->_status.in_playing || pc->_status.in_service)
    {
        JOB_LOG(Log::LT_ERROR, 441, L"[job], init fail; not servicable pc", L"");
        reason = 187;
    }
    else if (_owner->queryLobbyService(pc) != nullptr)
    {
        JOB_LOG(Log::LT_ERROR, 449, L"[job], init fail; pc already in service", L"");
        reason = 9;
    }
    else
    {
        ChangeCharacterRaceService* const service =
            new (Memory::_Manager[2]->Alloc(sizeof(ChangeCharacterRaceService), kFile, 455)) ChangeCharacterRaceService;
        LobbyService::DB lsdb;
        memset(&lsdb, 0, sizeof(lsdb));
        lsdb.serviceType = 8;
        lsdb.itemInstanceId = _itemInstanceId;
        ChangeCharacterRaceService::DB db;
        db.pcid = pc->_db.pcid;
        service->Setup(&lsdb, &db);
        int line;
        if (!service->Start(_owner, _itemDataId, _newRace, _newSex, _makingData, _makingDataSize))
        {
            JOB_LOG(Log::LT_ERROR, 480, L"[job], start new lobby service fail", L"");
            _lgate->SendChangeCharacterRaceWithAccountInventoryItemFail(_owner->_clikey, _slotid, _labelId,
                                                                        _itemInstanceId, 2);
            line = 482;
        }
        else if (!_owner->addLobbyService(service))
        {
            // The original format has no ", " before "lobby-service-id".
            JOB_LOG(Log::LT_ERROR, 489, L"[job], add new lobby service fail", L"lobby-service-id:0x%I64X",
                    service->GetDB().serviceId);
            _lgate->SendChangeCharacterRaceWithAccountInventoryItemFail(_owner->_clikey, _slotid, _labelId,
                                                                        _itemInstanceId, 192);
            line = 491;
        }
        else
        {
            _serviceId = service->GetDB().serviceId;
            pc->SetServiceStatus(true);
            JOB_LOG(Log::LT_DEBUG, 502, L"[job], register ok", L", lobby-service-id:0x%I64X", _serviceId);
            transit(TRY_CONSUME_ACCOUNT_INVENTORY_ITEM);
            return true;
        }
        // LIFT: the class operator delete is empty (LobbyService.h). Free gives the memory back.
        delete service;
        Memory::_Manager[2]->Free(service, kFile, line);
        transit(FIN);
        return true;
    }
    _lgate->SendChangeCharacterRaceWithAccountInventoryItemFail(_owner->_clikey, _slotid, _labelId, _itemInstanceId,
                                                                reason);
    transit(FIN);
    return true;
}

// 0x20a10
bool ChangeCharacterRaceJob::tryConsumeAccountInventoryItem()
{
    if (!_acciv->SendTryWarehouseItemConsumptionReq(_tran->Set(this, 161), _labelId, _itemInstanceId, _owner->_acb._id))
    {
        JOB_LOG(Log::LT_ERROR, 512, L"[job], send fail", L"");
        _lgate->SendChangeCharacterRaceWithAccountInventoryItemFail(_owner->_clikey, _slotid, _labelId, _itemInstanceId,
                                                                    192);
        releasePcServiceStatus();
        transit(FIN);
    }
    else
    {
        JOB_LOG(Log::LT_DEBUG, 519, L"[job], send ok", L"");
    }
    return true;
}

// 0x20bd0
bool ChangeCharacterRaceJob::tryConsumeAccountInventoryItemOk(void*)
{
    _acciv->TRecv(_tran);
    JOB_LOG(Log::LT_DEBUG, 528, L"[job], ok recv", L"");
    ChangeCharacterRaceService* const service =
        static_cast<ChangeCharacterRaceService*>(_owner->getLobbyServiceByType(_serviceId, 8));
    int line;
    wchar_t const* msg;
    if (service == nullptr)
    {
        line = 533;
        msg = L"[job], no such service-entry" JOB_SUFFIX;
    }
    else if (!service->ConsumeItemTried(_owner))
    {
        line = 542;
        msg = L"[job], update lobby service as 'consume item tried' fail" JOB_SUFFIX;
    }
    else
    {
        JOB_LOG(Log::LT_DEBUG, 549, L"[job], try consume item ok", L"");
        transit(CHANGE_CHARACTER_RACE);
        return true;
    }
    JOB_LOGV(Log::LT_ERROR, line, msg);
    _lgate->SendChangeCharacterRaceWithAccountInventoryItemFail(_owner->_clikey, _slotid, _labelId, _itemInstanceId, 192);
    releasePcServiceStatus();
    transit(FIN);
    return true;
}

// 0x20eb0
bool ChangeCharacterRaceJob::tryConsumeAccountInventoryItemFail(void* param)
{
    _acciv->TRecv(_tran);
    short* const fail = static_cast<short*>(param);
    if (fail == nullptr)
        JOB_CRASH(561, L"== CRASH == [job], invalid param");
    else
        JOB_LOG(Log::LT_DEBUG, 570, L"[job], fail recv", L", reason:%d", *fail);
    _lgate->SendChangeCharacterRaceWithAccountInventoryItemFail(_owner->_clikey, _slotid, _labelId, _itemInstanceId, 192);
    releasePcServiceStatus();
    transit(FIN);
    return true;
}

// 0x21110
bool ChangeCharacterRaceJob::tryConsumeAccountInventoryItemTimeout()
{
    JOB_LOG(Log::LT_ERROR, 581, L"[job], timeout", L"");
    _lgate->SendChangeCharacterRaceWithAccountInventoryItemFail(_owner->_clikey, _slotid, _labelId, _itemInstanceId, 192);
    releasePcServiceStatus();
    transit(FIN);
    return true;
}

// 0x21240
bool ChangeCharacterRaceJob::changeCharacterRace()
{
    Character* const pc = _owner->getCharacterInSlot(_slotid);
    if (pc == nullptr)
    {
        JOB_LOG(Log::LT_ERROR, 595, L"[job], no such pc", L"");
        _lgate->SendChangeCharacterRaceWithAccountInventoryItemFail(_owner->_clikey, _slotid, _labelId, _itemInstanceId,
                                                                    192);
        releasePcServiceStatus();
        transit(FIN);
    }
    else
    {
        _gamed->SendChangeCharacterRaceReq(_tran->Set(this, 141), _serviceId, pc->_db.pcid, _newRace, _newSex,
                                           pc->_db.showcase, pc->_db.showcaseSize, _makingData,
                                           static_cast<short>(_makingDataSize));
        JOB_LOG(Log::LT_DEBUG, 604, L"[job], sent", L"");
    }
    return true;
}

// 0x214a0
bool ChangeCharacterRaceJob::changeCharacterRaceOk(void* param)
{
    _gamed->TRecv(_tran);
    ChangeCharacterRaceOkParam* const ok = static_cast<ChangeCharacterRaceOkParam*>(param);
    if (ok == nullptr)
    {
        JOB_CRASH(615, L"== CRASH == [job], invalid param");
    }
    else
    {
        JOB_LOG(Log::LT_DEBUG, 624, L"[job], ok recv", L", showcase-size:%d", ok->showcaseDataSize);
        int line = 0;
        wchar_t const* msg = nullptr;
        Character* const pc = _owner->getCharacterInSlot(_slotid);
        if (pc == nullptr)
        {
            line = 629;
            msg = L"[job], no such pc" JOB_SUFFIX;
        }
        else
        {
            int dbrtn = 0;
            if (!LobbyDB::UpdateCharacterData(dbrtn, pc->_db.pcid, pc->_db.job, pc->_db.level, ok->showcaseData,
                                              ok->showcaseDataSize))
            {
                JOB_LOG(Log::LT_ERROR, 639, L"[job], update db showcase data fail", L", dbrtn:%d", dbrtn);
            }
            else
            {
                pc->SetShowcase(ok->showcaseData, ok->showcaseDataSize);
                ChangeCharacterRaceService* const service =
                    static_cast<ChangeCharacterRaceService*>(_owner->getLobbyServiceByType(_serviceId, 8));
                if (service == nullptr)
                {
                    line = 651;
                    msg = L"[job], no such service-entry" JOB_SUFFIX;
                }
                else if (!service->TaskDone(_owner))
                {
                    line = 660;
                    msg = L"[job], set service-entry as 'served' fail" JOB_SUFFIX;
                }
                else
                {
                    JOB_LOG(Log::LT_DEBUG, 667, L"[job], set service-entry as 'served' ok", L"");
                    transit(FIN_CONSUME_ACCOUNT_INVENTORY_ITEM);
                    return true;
                }
            }
        }
        if (msg != nullptr)
            JOB_LOGV(Log::LT_ERROR, line, msg);
    }
    _lgate->SendChangeCharacterRaceWithAccountInventoryItemFail(_owner->_clikey, _slotid, _labelId, _itemInstanceId, 192);
    releasePcServiceStatus();
    transit(FIN);
    return true;
}

// 0x21a30
bool ChangeCharacterRaceJob::changeCharacterRaceFail(void* param)
{
    _gamed->TRecv(_tran);
    short* const fail = static_cast<short*>(param);
    if (fail == nullptr)
        JOB_CRASH(679, L"== CRASH == [job], invalid param");
    else
        JOB_LOG(Log::LT_DEBUG, 688, L"[job], fail recv", L", reason:%d", *fail);
    _lgate->SendChangeCharacterRaceWithAccountInventoryItemFail(_owner->_clikey, _slotid, _labelId, _itemInstanceId, 192);
    releasePcServiceStatus();
    transit(FIN);
    return true;
}

// 0x21c90
bool ChangeCharacterRaceJob::changeCharacterRaceTimeout()
{
    JOB_LOG(Log::LT_ERROR, 699, L"[job], timeout", L"");
    _lgate->SendChangeCharacterRaceWithAccountInventoryItemFail(_owner->_clikey, _slotid, _labelId, _itemInstanceId, 192);
    releasePcServiceStatus();
    transit(FIN);
    return true;
}

// 0x21dc0
bool ChangeCharacterRaceJob::finConsumeAccountInventoryItem()
{
    if (!_acciv->SendFinishWarehouseItemConsumptionReq(_tran->Set(this, 164), _labelId, _itemInstanceId,
                                                       _owner->_acb._id, 0))
    {
        JOB_LOG(Log::LT_ERROR, 717, L"[job], send fail", L"");
        _lgate->SendChangeCharacterRaceWithAccountInventoryItemFail(_owner->_clikey, _slotid, _labelId, _itemInstanceId,
                                                                    192);
        releasePcServiceStatus();
        transit(FIN);
    }
    else
    {
        JOB_LOG(Log::LT_DEBUG, 724, L"[job], sent", L"");
    }
    return true;
}

// 0x21f80
bool ChangeCharacterRaceJob::finConsumeAccountInventoryItemOk(void*)
{
    _acciv->TRecv(_tran);
    JOB_LOG(Log::LT_DEBUG, 733, L"[job], ok recv", L"");
    ChangeCharacterRaceService* const service = static_cast<ChangeCharacterRaceService*>(_owner->getLobbyService(_serviceId));
    int line;
    wchar_t const* msg;
    if (service == nullptr)
    {
        line = 738;
        msg = L"[job], no such service-entry" JOB_SUFFIX;
    }
    else if (!service->ConsumeItemFinished(_owner))
    {
        line = 747;
        msg = L"[job], set service-entry as 'consume item fin' fail" JOB_SUFFIX;
    }
    else
    {
        JOB_LOG(Log::LT_DEBUG, 754, L"[job], set service-entry as 'consume item fin' ok", L"");
        transit(FIN_SERVICE_ENTRY);
        return true;
    }
    JOB_LOGV(Log::LT_ERROR, line, msg);
    _lgate->SendChangeCharacterRaceWithAccountInventoryItemFail(_owner->_clikey, _slotid, _labelId, _itemInstanceId, 192);
    releasePcServiceStatus();
    transit(FIN);
    return true;
}

// 0x22250
bool ChangeCharacterRaceJob::finConsumeAccountInventoryItemFail(void* param)
{
    _acciv->TRecv(_tran);
    short* const fail = static_cast<short*>(param);
    if (fail == nullptr)
        JOB_CRASH(766, L"== CRASH == [job], invalid param");
    else
        JOB_LOG(Log::LT_DEBUG, 775, L"[job], fail recv", L", reason:%d", *fail);
    _lgate->SendChangeCharacterRaceWithAccountInventoryItemFail(_owner->_clikey, _slotid, _labelId, _itemInstanceId, 192);
    releasePcServiceStatus();
    transit(FIN);
    return true;
}

// 0x224b0
bool ChangeCharacterRaceJob::finConsumeAccountInventoryItemTimeout()
{
    JOB_LOG(Log::LT_ERROR, 786, L"[job], timeout", L"");
    _lgate->SendChangeCharacterRaceWithAccountInventoryItemFail(_owner->_clikey, _slotid, _labelId, _itemInstanceId, 192);
    releasePcServiceStatus();
    transit(FIN);
    return true;
}

// 0x225e0
bool ChangeCharacterRaceJob::finServiceEntry()
{
    ChangeCharacterRaceService* const service = static_cast<ChangeCharacterRaceService*>(_owner->getLobbyService(_serviceId));
    int line;
    wchar_t const* msg;
    if (service == nullptr)
    {
        line = 801;
        msg = L"[job], no such service-entry" JOB_SUFFIX;
    }
    else if (!service->Finish(_owner))
    {
        line = 810;
        msg = L"[job], finish service-entry fail" JOB_SUFFIX;
    }
    else
    {
        _owner->removeLobbyService(service->GetDB().serviceId);
        // LIFT: the class operator delete is empty (LobbyService.h). Free gives the memory back.
        delete service;
        Memory::_Manager[2]->Free(service, kFile, 819);
        Character* const pc = _owner->getCharacterInSlot(_slotid);
        if (pc == nullptr)
        {
            JOB_LOG(Log::LT_ERROR, 825, L"[job], no such pc", L"");
            _lgate->SendChangeCharacterRaceWithAccountInventoryItemFail(_owner->_clikey, _slotid, _labelId,
                                                                        _itemInstanceId, 2);
        }
        else
        {
            _lgate->SendChangeCharacterRaceWithAccountInventoryItemOk(_owner->_clikey, _slotid, pc->_db.showcase,
                                                                      pc->_db.showcaseSize, _labelId, _itemInstanceId);
            JOB_LOG(Log::LT_DEBUG, 834, L"[job], finish service-entry ok", L"");
        }
        releasePcServiceStatus();
        transit(FIN);
        return true;
    }
    JOB_LOGV(Log::LT_ERROR, line, msg);
    _lgate->SendChangeCharacterRaceWithAccountInventoryItemFail(_owner->_clikey, _slotid, _labelId, _itemInstanceId, 192);
    releasePcServiceStatus();
    transit(FIN);
    return true;
}

// 0x229a0 (ChangeCharacterAppearanceJob.obj in the PDB: the Race, Sex and Appearance copies fold by ICF)
bool ChangeCharacterRaceJob::releasePcServiceStatus()
{
    Character* const pc = _owner->getCharacterInSlot(_slotid);
    if (pc != nullptr)
        pc->SetServiceStatus(false);
    return true;
}
