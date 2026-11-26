// ExtendJumpingCharacterCreationQuotaJob.obj (LobbyDaemon PDB, 2019 + PDB). ExtendJumpingCharacterCreationQuotaJob is lifted
// from the pseudocode with PDB types. UpgradeJumpingCharacterStateJob bodies are still stubs. A stub is not a lift.
#include <new>
#include <string.h>
#include <wchar.h>
#include <winsock2.h>
#include <windows.h>
#include "ExtendJumpingCharacterCreationQuotaJob.h"
#include "AccountInventoryChannel.h"
#include "AlertSender.h"
#include "CliSession.h"
#include "GamedChannel.h"
#include "LiftStub.h"
#include "ObjectPoolLobbyDaemon.h"
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
#include "TransactionChannel.h"

static wchar_t const kFile[] = L"ExtendJumpingCharacterCreationQuotaJob.cpp";

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
// The init logs add the request fields. The original reads the world ids from the request channels.
#define CHANNEL_WID(ch) ((ch) != nullptr ? ((ch)->_rawChannel != nullptr ? static_cast<short>((ch)->_rawChannel->GetId()) : 0) : 0)
#define INIT_FMT L", gate-wid:%d, wid:%d, label-id:0x%I64X, item-instance-id:0x%I64X, item-data-id:%u"
#define INIT_ARGS(p) CHANNEL_WID((p)->lgate), CHANNEL_WID((p)->gamed), (p)->labelId, (p)->itemInstanceId, (p)->itemDataId

// PDB enum ECliSessionState: CSS_LOBBY = 0x20000, CSS_WORLD = 0x40000.
// PDB LobbyService::DB::serviceType of ExtendJumpingCharacterCreationQuotaService: 6.

namespace
{
LobbyJobStateDef const StateDef[] = {{0, L"INIT"},
                                     {1, L"CHECK_ACCOUNT_INVENTORY_ITEM"},
                                     {2, L"REGISTER_SERVICE_ENTRY"},
                                     {3, L"TRY_CONSUME_ACCOUNT_INVENTORY_ITEM"},
                                     {4, L"EXTEND_JUMPING_CHARACTER_CREATION_QUOTA"},
                                     {5, L"FIN_CONSUME_ACCOUNT_INVENTORY_ITEM"},
                                     {6, L"FIN_SERVICE_ENTRY"},
                                     {7, L"FIN"}};  // 0x12e110
}

LobbyJobDef ExtendJumpingCharacterCreationQuotaJob::_def = {39, StateDef, 7, L"ExtendJumpingCharacterCreationQuotaJob"};  // 0x201ed8

// LIFT: body of the PDB inline CliSession::queryLobbyService(QueryExtendJumpingCharacterCreationQuotaService const&).
// From the inlined code in ExtendJumpingCharacterCreationQuotaJob::init (0x2a6a0) and ::registerServiceEntry (0x2b990).
inline LobbyService* CliSession::queryLobbyService(QueryExtendJumpingCharacterCreationQuotaService const&)
{
    for (std::vector<LobbyService*, StlAllocator<LobbyService*, 2> >::iterator i = _serviceEntries.begin();
         i != _serviceEntries.end(); ++i)
    {
        LobbyService* serviceEntry = *i;
        if (serviceEntry != nullptr && serviceEntry->GetDB().serviceType == 6)
            return serviceEntry;
    }
    return nullptr;
}

// 0x2a300
LobbyJobDef const* ExtendJumpingCharacterCreationQuotaJob::GetDefinition() const
{
    return &_def;
}

// 0x2a310
// LIFT: Not done. The body calls _pool.Checkin (0x629a0). ObjPool::Checkin is not lifted.
void ExtendJumpingCharacterCreationQuotaJob::deallocate_me(void*, wchar_t const*, int)
{
    LIFT_STUB(0x2a310);
}

// 0x2a360
LobbyJobDef const* UpgradeJumpingCharacterStateJob::GetDefinition() const
{
    LIFT_STUB(0x2a360);
}

// 0x2a370
void UpgradeJumpingCharacterStateJob::deallocate_me(void*, wchar_t const*, int)
{
    LIFT_STUB(0x2a370);
}


// 0x2a3c0
// The original constructs a job on the stack (null owner) and returns its vfptr. It does not run the destructor.
void* ExtendJumpingCharacterCreationQuotaJob::_vtbl()
{
    char buf[sizeof(ExtendJumpingCharacterCreationQuotaJob)];
    ExtendJumpingCharacterCreationQuotaJob* job = ::new (buf) ExtendJumpingCharacterCreationQuotaJob(nullptr);
    return *reinterpret_cast<void**>(job);
}

// 0x2a440
ExtendJumpingCharacterCreationQuotaJob::ExtendJumpingCharacterCreationQuotaJob(CliSession* owner)
    : CliSessionJob(owner), _tran(nullptr), _lgate(nullptr), _gamed(nullptr), _gamedTid(0), _acciv(nullptr), _labelId(0),
      _itemInstanceId(0), _itemDataId(0), _serviceId(0)
{
}

// 0x2a4c0 (scalar deleting destructor 0x2a4a0)
ExtendJumpingCharacterCreationQuotaJob::~ExtendJumpingCharacterCreationQuotaJob()
{
    if (_tran != nullptr)
        _tran->removeReferenceCount(kFile, 92);
    if (_lgate != nullptr)
        _lgate->removeReferenceCount(kFile, 94);
    if (_gamed != nullptr)
        _gamed->removeReferenceCount(kFile, 96);
}

// 0x2a540
bool ExtendJumpingCharacterCreationQuotaJob::work(int task, void* param)
{
    bool result = false;
    if (_state == INIT && task == 30)
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
    if (_state == EXTEND_JUMPING_CHARACTER_CREATION_QUOTA && task == 0)
        result = extendJumpingCharacterCreationQuota();
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

// 0x2a6a0
bool ExtendJumpingCharacterCreationQuotaJob::init(void* param)
{
    ExtendJumpingCharacterCreationQuotaWithAccountInventoryItemReqParam* const p =
        static_cast<ExtendJumpingCharacterCreationQuotaWithAccountInventoryItemReqParam*>(param);
    if (p == nullptr || (p->lgate == nullptr && p->gamed == nullptr) || p->labelId == 0 || p->itemInstanceId == 0)
    {
        JOB_LOG(Log::LT_ERROR, 193, L"[job], invalid param", L"");
        transit(FIN);
        return true;
    }

    _tran = new (Memory::_Manager[2]->Alloc(sizeof(LobbyJobTransaction), kFile, 201)) LobbyJobTransaction;
    _lgate = p->lgate;
    _gamed = p->gamed;
    _gamedTid = p->gamedTid;
    _labelId = p->labelId;
    _itemInstanceId = p->itemInstanceId;
    _itemDataId = p->itemDataId;
    if (_lgate != nullptr)
        _lgate->addReferenceCount(false, kFile, 210);
    if (_gamed != nullptr)
        _gamed->addReferenceCount(false, kFile, 212);

    // The original sends the fail reason and calls transit(FIN) once for all failure branches.
    short reason;
    if (!LobbyDaemon::_instance->_config->_enableJumpingCharacterCreation)
    {
        JOB_LOG(Log::LT_ERROR, 218, L"[job], jumping character creation is disabled; cannot extend quota", INIT_FMT,
                INIT_ARGS(p));
        reason = 2;
    }
    else if ((_acciv = LobbyDaemon::_instance->_accountInventoryChannel) == nullptr || !_acciv->IsConnected())
    {
        JOB_LOG(Log::LT_ERROR, 227, L"[job], init fail; account-inventory N/A", INIT_FMT, INIT_ARGS(p));
        reason = 7;
    }
    else if (LobbyDaemon::_instance->_npServchmgr->_gameServChannel == nullptr ||
             !LobbyDaemon::_instance->_npServchmgr->_gameServChannel->IsConnected())
    {
        JOB_LOG(Log::LT_ERROR, 237, L"[job], init fail; np N/A", INIT_FMT, INIT_ARGS(p));
        reason = 7;
    }
    else if (!LobbyDaemon::_instance->CheckServiceItemDataId(
                 LobbyDaemon::SERVICEITEMTYPE_EXTEND_JUMPING_CHARACTER_CREATION_QUOTA, _itemDataId))
    {
        JOB_LOG(Log::LT_ERROR, 245, L"[job], not proper item", INIT_FMT, INIT_ARGS(p));
        reason = 222;
    }
    else if (_owner->_state != 0x20000 && _owner->_state != 0x40000)  // CSS_LOBBY, CSS_WORLD
    {
        JOB_LOG(Log::LT_ERROR, 253, L"[job], cli-session not in lobby or world", INIT_FMT L", state:%d", INIT_ARGS(p),
                _owner->_state);
        reason = 5;
    }
    else if (_owner->queryLobbyService(CliSession::QueryExtendJumpingCharacterCreationQuotaService()) != nullptr)
    {
        JOB_LOG(Log::LT_ERROR, 260, L"[job], init fail; already in service", INIT_FMT, INIT_ARGS(p));
        reason = 9;
    }
    else
    {
        JOB_LOG(Log::LT_DEBUG, 266, L"[job], init ok", INIT_FMT, INIT_ARGS(p));
        transit(CHECK_ACCOUNT_INVENTORY_ITEM);
        return true;
    }
    sendFailReason(reason);
    transit(FIN);
    return true;
}

// 0x2b0a0
bool ExtendJumpingCharacterCreationQuotaJob::checkAccountInventoryItem()
{
    if (!_acciv->SendRetrieveSingleWarehouseItemReq(_tran->Set(this, 158), _itemInstanceId, _owner->_acb._id, 0))
    {
        JOB_LOG(Log::LT_ERROR, 282, L"[job], not sent", L"");
        sendFailReason(7);
        transit(FIN);
    }
    else
    {
        JOB_LOG(Log::LT_DEBUG, 288, L"[job], sent", L"");
    }
    return true;
}

// 0x2b220
bool ExtendJumpingCharacterCreationQuotaJob::checkAccountInventoryItemOk(void* param)
{
    _acciv->TRecv(_tran);
    RetrieveSingleWarehouseItemOkParam* const ok = static_cast<RetrieveSingleWarehouseItemOkParam*>(param);
    int next;
    if (ok == nullptr)
    {
        JOB_CRASH(297, L"== CRASH == [job], invalid param");
        sendFailReason(2);
        next = FIN;
    }
    else if (ok->item == nullptr)
    {
        JOB_LOG(Log::LT_ERROR, 307, L"[job], null item", L"");
        sendFailReason(2);
        next = FIN;
    }
    else
    {
        LobbyServiceItem const* const item = ok->item;
        JOB_LOG(Log::LT_DEBUG, 315, L"[job], ok recv",
                L", item-instance-id:0x%I64X, label-id:0x%I64X, item-data-id:%u, state:%d", item->instanceId,
                item->labelId, item->dataId, item->state);
        if (_itemDataId != item->dataId)
        {
            JOB_LOG(Log::LT_ERROR, 318, L"[job], item-data-id mismatch",
                    L", request-item-data-id:%u, required-item-data-id:%u", _itemDataId, item->dataId);
            sendFailReason(222);
            next = FIN;
        }
        else if (item->state != 1)
        {
            JOB_LOG(Log::LT_ERROR, 325, L"[job], unusable item", L"");
            sendFailReason(221);
            next = FIN;
        }
        else
        {
            next = REGISTER_SERVICE_ENTRY;
        }
    }
    // The original has one transit call: the next state is in a register.
    transit(next);
    return true;
}

// 0x2b640
bool ExtendJumpingCharacterCreationQuotaJob::checkAccountInventoryItemFail(void* param)
{
    _acciv->TRecv(_tran);
    short* const fail = static_cast<short*>(param);
    short reason;
    if (fail == nullptr)
    {
        JOB_CRASH(341, L"== CRASH == [job], invalid param");
        reason = 2;
    }
    else
    {
        JOB_LOG(Log::LT_DEBUG, 350, L"[job], fail recv", L", reason:%d", *fail);
        reason = 2;
        if (*fail == 20)
            reason = 220;
    }
    sendFailReason(reason);
    transit(FIN);
    return true;
}

// 0x2b890
bool ExtendJumpingCharacterCreationQuotaJob::checkAccountInventoryItemTimeout()
{
    JOB_LOG(Log::LT_ERROR, 370, L"[job], timeout", L"");
    sendFailReason(7);
    transit(FIN);
    return true;
}

// 0x2b990
bool ExtendJumpingCharacterCreationQuotaJob::registerServiceEntry()
{
    short reason;
    if (_owner->_state != 0x20000 && _owner->_state != 0x40000)  // CSS_LOBBY, CSS_WORLD
    {
        JOB_LOG(Log::LT_ERROR, 381, L"[job], register fail; not in lobby or world state", L"");
        reason = 5;
    }
    else if (_owner->queryLobbyService(CliSession::QueryExtendJumpingCharacterCreationQuotaService()) != nullptr)
    {
        JOB_LOG(Log::LT_ERROR, 388, L"[job], register fail; already in service", L"");
        reason = 9;
    }
    else
    {
        ExtendJumpingCharacterCreationQuotaService* const service =
            new (Memory::_Manager[2]->Alloc(sizeof(ExtendJumpingCharacterCreationQuotaService), kFile, 394))
                ExtendJumpingCharacterCreationQuotaService;
        LobbyService::DB lsdb;
        memset(&lsdb, 0, sizeof(lsdb));
        lsdb.serviceType = 6;
        lsdb.itemInstanceId = _itemInstanceId;
        service->Setup(&lsdb);
        int line;
        if (!service->Start(_owner, _itemDataId))
        {
            JOB_LOG(Log::LT_ERROR, 413, L"[job], start new lobby service fail", L"");
            sendFailReason(2);
            delete service;
            line = 415;
        }
        else if (!_owner->addLobbyService(service))
        {
            JOB_LOG(Log::LT_ERROR, 421, L"[job], add new lobby service fail", L", lobby-service-id:0x%I64X",
                    service->GetDB().serviceId);
            sendFailReason(223);
            delete service;
            line = 423;
        }
        else
        {
            _serviceId = service->GetDB().serviceId;
            JOB_LOG(Log::LT_DEBUG, 430, L"[job], register ok", L", lobby-service-id:0x%I64X", _serviceId);
            transit(TRY_CONSUME_ACCOUNT_INVENTORY_ITEM);
            return true;
        }
        // LIFT: the class operator delete is empty (LobbyService.h). Free gives the memory back. The original
        // destroys the service in each branch and frees it once.
        Memory::_Manager[2]->Free(service, kFile, line);
        transit(FIN);
        return true;
    }
    sendFailReason(reason);
    transit(FIN);
    return true;
}

// 0x2bdf0
bool ExtendJumpingCharacterCreationQuotaJob::tryConsumeAccountInventoryItem()
{
    if (!_acciv->SendTryWarehouseItemConsumptionReq(_tran->Set(this, 161), _labelId, _itemInstanceId, _owner->_acb._id))
    {
        JOB_LOG(Log::LT_ERROR, 441, L"[job], send fail", L"");
        sendFailReason(223);
        transit(FIN);
    }
    else
    {
        JOB_LOG(Log::LT_DEBUG, 447, L"[job], send ok", L"");
    }
    return true;
}

// 0x2bf80
bool ExtendJumpingCharacterCreationQuotaJob::tryConsumeAccountInventoryItemOk(void*)
{
    _acciv->TRecv(_tran);
    JOB_LOG(Log::LT_DEBUG, 456, L"[job], ok recv", L"");
    ExtendJumpingCharacterCreationQuotaService* const service =
        static_cast<ExtendJumpingCharacterCreationQuotaService*>(_owner->getLobbyServiceByType(_serviceId, 6));
    int line = -1;
    wchar_t const* msg = nullptr;
    if (service == nullptr)
    {
        line = 460;
        msg = L"[job], no such service-entry" JOB_SUFFIX;
    }
    else if (!service->ConsumeItemTried(_owner))
    {
        line = 467;
        msg = L"[job], update lobby service as 'consume item tried' fail" JOB_SUFFIX;
    }
    else
    {
        JOB_LOG(Log::LT_DEBUG, 473, L"[job], try consume item ok", L"");
    }
    // The original has one transit call: the next state is in a register.
    int next = EXTEND_JUMPING_CHARACTER_CREATION_QUOTA;
    if (msg != nullptr)
    {
        JOB_LOGV(Log::LT_ERROR, line, msg);
        sendFailReason(223);
        next = FIN;
    }
    transit(next);
    return true;
}

// 0x2c220
bool ExtendJumpingCharacterCreationQuotaJob::tryConsumeAccountInventoryItemFail(void* param)
{
    _acciv->TRecv(_tran);
    short* const fail = static_cast<short*>(param);
    if (fail == nullptr)
        JOB_CRASH(484, L"== CRASH == [job], invalid param");
    else
        JOB_LOG(Log::LT_DEBUG, 492, L"[job], fail recv", L", reason:%d", *fail);
    sendFailReason(223);
    transit(FIN);
    return true;
}

// 0x2c450
bool ExtendJumpingCharacterCreationQuotaJob::tryConsumeAccountInventoryItemTimeout()
{
    JOB_LOG(Log::LT_ERROR, 502, L"[job], timeout", L"");
    sendFailReason(223);
    transit(FIN);
    return true;
}

// 0x2c550
bool ExtendJumpingCharacterCreationQuotaJob::extendJumpingCharacterCreationQuota()
{
    ExtendJumpingCharacterCreationQuotaService* const service =
        static_cast<ExtendJumpingCharacterCreationQuotaService*>(_owner->getLobbyServiceByType(_serviceId, 6));
    int line;
    wchar_t const* msg;
    if (service == nullptr)
    {
        line = 515;
        msg = L"[job], no such service-entry" JOB_SUFFIX;
    }
    else if (!service->TaskDone(_owner))
    {
        line = 524;
        msg = L"[job], set service-entry as 'served' fail" JOB_SUFFIX;
    }
    else
    {
        JOB_LOG(Log::LT_DEBUG, 532, L"[job], set service-entry as 'served' ok", L"");
        transit(FIN_CONSUME_ACCOUNT_INVENTORY_ITEM);
        return true;
    }
    JOB_LOGV(Log::LT_ERROR, line, msg);
    sendFailReason(223);
    transit(FIN);
    return true;
}

// 0x2c730
bool ExtendJumpingCharacterCreationQuotaJob::finConsumeAccountInventoryItem()
{
    if (!_acciv->SendFinishWarehouseItemConsumptionReq(_tran->Set(this, 164), _labelId, _itemInstanceId,
                                                       _owner->_acb._id, 0))
    {
        JOB_LOG(Log::LT_ERROR, 547, L"[job], send fail", L"");
        sendFailReason(223);
        transit(FIN);
    }
    else
    {
        JOB_LOG(Log::LT_DEBUG, 553, L"[job], sent", L"");
    }
    return true;
}

// 0x2c8c0
bool ExtendJumpingCharacterCreationQuotaJob::finConsumeAccountInventoryItemOk(void*)
{
    _acciv->TRecv(_tran);
    JOB_LOG(Log::LT_DEBUG, 562, L"[job], ok recv", L"");
    ExtendJumpingCharacterCreationQuotaService* const service =
        static_cast<ExtendJumpingCharacterCreationQuotaService*>(_owner->getLobbyServiceByType(_serviceId, 6));
    int line = -1;
    wchar_t const* msg = nullptr;
    if (service == nullptr)
    {
        line = 567;
        msg = L"[job], no such service-entry" JOB_SUFFIX;
    }
    else if (!service->ConsumeItemFinished(_owner))
    {
        line = 575;
        msg = L"[job], set service-entry as 'consume item fin' fail" JOB_SUFFIX;
    }
    else
    {
        JOB_LOG(Log::LT_DEBUG, 581, L"[job], set service-entry as 'consume item fin' ok", L"");
    }
    // The original has one transit call: the next state is in a register.
    int next = FIN_SERVICE_ENTRY;
    if (msg != nullptr)
    {
        JOB_LOGV(Log::LT_ERROR, line, msg);
        sendFailReason(223);
        next = FIN;
    }
    transit(next);
    return true;
}

// 0x2cb60
bool ExtendJumpingCharacterCreationQuotaJob::finConsumeAccountInventoryItemFail(void* param)
{
    _acciv->TRecv(_tran);
    short* const fail = static_cast<short*>(param);
    if (fail == nullptr)
        JOB_CRASH(593, L"== CRASH == [job], invalid param");
    else
        JOB_LOG(Log::LT_DEBUG, 601, L"[job], fail recv", L", reason:%d", *fail);
    sendFailReason(223);
    transit(FIN);
    return true;
}

// 0x2cd90
bool ExtendJumpingCharacterCreationQuotaJob::finConsumeAccountInventoryItemTimeout()
{
    JOB_LOG(Log::LT_ERROR, 611, L"[job], timeout", L"");
    sendFailReason(223);
    transit(FIN);
    return true;
}

// 0x2ce90
bool ExtendJumpingCharacterCreationQuotaJob::finServiceEntry()
{
    ExtendJumpingCharacterCreationQuotaService* const service =
        static_cast<ExtendJumpingCharacterCreationQuotaService*>(_owner->getLobbyServiceByType(_serviceId, 6));
    int line;
    wchar_t const* msg;
    if (service == nullptr)
    {
        line = 625;
        msg = L"[job], no such service-entry" JOB_SUFFIX;
    }
    else if (!service->Finish(_owner))
    {
        line = 633;
        msg = L"[job], finish service-entry fail" JOB_SUFFIX;
    }
    else
    {
        _owner->removeLobbyService(service->GetDB().serviceId);
        // LIFT: the class operator delete is empty (LobbyService.h). Free gives the memory back.
        delete service;
        Memory::_Manager[2]->Free(service, kFile, 641);
        ++_owner->_jumpingCharacterCreationQuota._db.creationQuota;
        int const quota = _owner->_jumpingCharacterCreationQuota._db.creationQuota;
        int const count = _owner->_jumpingCharacterCreationQuota._db.creationCount;
        int const remain = quota - count;
        if (_lgate != nullptr)
            _lgate->SendExtendJumpingCharacterCreationQuotaWithAccountInventoryItemOk(_owner->_clikey, _labelId,
                                                                                      _itemInstanceId, remain);
        else if (_gamed != nullptr)
            _gamed->SendExtendJumpingCharacterCreationQuotaWithAccountInventoryItemOk(_gamedTid, remain);
        JOB_LOG(Log::LT_DEBUG, 657, L"[job], finish service-entry ok", L", total(new):%d, used:%d, remain(new):%d",
                quota, count, remain);
        transit(FIN);
        return true;
    }
    JOB_LOGV(Log::LT_ERROR, line, msg);
    sendFailReason(223);
    transit(FIN);
    return true;
}

// 0x2d140
void ExtendJumpingCharacterCreationQuotaJob::sendFailReason(short lobbygateFailReason)
{
    if (_lgate != nullptr)
    {
        _lgate->SendExtendJumpingCharacterCreationQuotaWithAccountInventoryItemFail(_owner->_clikey, _labelId,
                                                                                    _itemInstanceId, lobbygateFailReason);
    }
    else if (_gamed != nullptr)
    {
        // The gamed protocol has its own fail reason values.
        short gamedFailReason = 1;
        switch (lobbygateFailReason)
        {
        case 2:
            gamedFailReason = 2;
            break;
        case 5:
            gamedFailReason = 6;
            break;
        case 7:
            gamedFailReason = 7;
            break;
        case 9:
            gamedFailReason = 59;
            break;
        case 220:
            gamedFailReason = 60;
            break;
        case 221:
            gamedFailReason = 61;
            break;
        case 222:
            gamedFailReason = 62;
            break;
        case 223:
            gamedFailReason = 63;
            break;
        default:
            break;
        }
        _gamed->SendExtendJumpingCharacterCreationQuotaWithAccountInventoryItemFail(_gamedTid, gamedFailReason);
        JOB_LOG(Log::LT_DEBUG, 704, L"[job], send fail reason", L", send to gamed, failreason:%d, game-tid:0x%I64X, wid:%d",
                gamedFailReason, _gamedTid, CHANNEL_WID(_gamed));
    }
}

// 0x2d440
void* UpgradeJumpingCharacterStateJob::_vtbl()
{
    LIFT_STUB(0x2d440);
}

// 0x2d4c0
UpgradeJumpingCharacterStateJob::UpgradeJumpingCharacterStateJob(CliSession* owner)
    : CliSessionJob(owner), _gamed(nullptr), _gamedTid(0), _wid(0), _pcId(0), _jumpingCharacterState(0), _consumeCreationQuota(false)
{
}

// 0x2d550
bool UpgradeJumpingCharacterStateJob::work(int, void*)
{
    LIFT_STUB(0x2d550);
}

// 0x2d580
bool UpgradeJumpingCharacterStateJob::init(int, void*)
{
    LIFT_STUB(0x2d580);
}

// 0x2d9c0
bool UpgradeJumpingCharacterStateJob::upgradeJumpingCharacterState()
{
    LIFT_STUB(0x2d9c0);
}

// LIFT: ExtendJumpingCharacterCreationQuotaJob::_pool (.data RVA 0x2040a0). Dynamic initializer 0x11dc60, atexit destructor 0x11eb00. The original static data
// holds id 1, objsize sizeof(ExtendJumpingCharacterCreationQuotaJob) and desc L"ExtendJumpingCharacterCreationQuotaJob".
ObjPool ExtendJumpingCharacterCreationQuotaJob::_pool(1, sizeof(ExtendJumpingCharacterCreationQuotaJob), L"ExtendJumpingCharacterCreationQuotaJob");

// LIFT: UpgradeJumpingCharacterStateJob::_pool (.data RVA 0x204150). Dynamic initializer 0x11dcb0, atexit destructor 0x11eb40. The original static data
// holds id 1, objsize sizeof(UpgradeJumpingCharacterStateJob) and desc L"UpgradeJumpingCharacterStateJob".
ObjPool UpgradeJumpingCharacterStateJob::_pool(1, sizeof(UpgradeJumpingCharacterStateJob), L"UpgradeJumpingCharacterStateJob");
