// AddSlotJob.obj (LobbyDaemon PDB, 2019 + PDB). Lifted from the pseudocode with PDB types.
#include <new>
#include <vector>
#include <stdio.h>
#include <wchar.h>
#include <winsock2.h>
#include <windows.h>
#include "AddSlotJob.h"
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
#include "TransactionChannel.h"
#if defined(__clang__)
#include "crt_cpp_overload.h"  // the swprintf_s array template (VS2010 has it in its CRT headers)
#endif

namespace StsMsgLib
{
// PDB StsMsgLib::_StsMsgRequestSlotListSlots (sizeof 0x28).
// LIFT: the PDB type of pUserId is _GUID*. The lift uses id128* (same layout), as in LobbyGamePacketHandler.cpp.
struct _StsMsgRequestSlotListSlots : public _StsMsgRequest
{
    id128* pUserId;
    wchar_t* pwszSlotType;
};
static_assert(sizeof(_StsMsgRequestSlotListSlots) == 0x28, "sizeof StsMsgLib::_StsMsgRequestSlotListSlots");
static_assert(offsetof(_StsMsgRequestSlotListSlots, pUserId) == 0x18, "_StsMsgRequestSlotListSlots::pUserId");
static_assert(offsetof(_StsMsgRequestSlotListSlots, pwszSlotType) == 0x20, "_StsMsgRequestSlotListSlots::pwszSlotType");

// PDB StsMsgLib::_StsMsgResponseSlotListSlots (sizeof 0x70). The lift does not read the slots.
struct _StsMsgResponseSlotListSlots : public _StsMsgResponse
{
    struct _Slot;
    unsigned int nCount;
    _Slot* pSlot;
};
static_assert(sizeof(_StsMsgResponseSlotListSlots) == 0x70, "sizeof StsMsgLib::_StsMsgResponseSlotListSlots");
static_assert(offsetof(_StsMsgResponseSlotListSlots, nCount) == 0x60, "_StsMsgResponseSlotListSlots::nCount");
static_assert(offsetof(_StsMsgResponseSlotListSlots, pSlot) == 0x68, "_StsMsgResponseSlotListSlots::pSlot");

// PDB StsMsgLib::_StsMsgRequestSlotCreateSlots (sizeof 0x48).
struct _StsMsgRequestSlotCreateSlots : public _StsMsgRequest
{
    struct _SlotData
    {
        long long serviceId;
    };
    id128* pUserId;
    wchar_t* pwszSlotType;
    _SlotData slotData;
    wchar_t* pwszSlotData;
    unsigned int nCount;
    wchar_t* pwszTransactionKey;
};
static_assert(sizeof(_StsMsgRequestSlotCreateSlots) == 0x48, "sizeof StsMsgLib::_StsMsgRequestSlotCreateSlots");
static_assert(offsetof(_StsMsgRequestSlotCreateSlots, slotData) == 0x28, "_StsMsgRequestSlotCreateSlots::slotData");
static_assert(offsetof(_StsMsgRequestSlotCreateSlots, nCount) == 0x38, "_StsMsgRequestSlotCreateSlots::nCount");
static_assert(offsetof(_StsMsgRequestSlotCreateSlots, pwszTransactionKey) == 0x40, "_StsMsgRequestSlotCreateSlots::pwszTransactionKey");

// PDB StsMsgLib::_StsMsgResponseSlotCreateSlots (sizeof 0x70). The PDB type of pSlotId is _GUID*.
struct _StsMsgResponseSlotCreateSlots : public _StsMsgResponse
{
    id128* pSlotId;
    unsigned int nCount;
};
static_assert(sizeof(_StsMsgResponseSlotCreateSlots) == 0x70, "sizeof StsMsgLib::_StsMsgResponseSlotCreateSlots");
static_assert(offsetof(_StsMsgResponseSlotCreateSlots, pSlotId) == 0x60, "_StsMsgResponseSlotCreateSlots::pSlotId");
}  // namespace StsMsgLib

static wchar_t const kFile[] = L"AddSlotJob.cpp";

// The log suffix of all LobbyJob logs. The original reads the owner state 2 times (HIWORD and LOWORD).
#define JOB_LOG(logType, line, msg, fmt, ...)                                                                          \
    Log::Write(logType, kFile, line, msg L", tid:0x%I64X, type:%d, state:%d, cli-key:0x%I64X, cli-state:%d.%d" fmt,   \
               this != nullptr ? _id : 0, this != nullptr ? GetDefinition()->type : -1,                            \
               this != nullptr ? _state : -1, this != nullptr && _owner != nullptr ? _owner->_clikey : 0,          \
               HIWORD(this != nullptr && _owner != nullptr ? _owner->_state : 0),                                  \
               LOWORD(this != nullptr && _owner != nullptr ? _owner->_state : 0), ##__VA_ARGS__)

// A CRASH log also goes to AlertSender with the same text.
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

#define GATE_WID(lg) ((lg) != nullptr ? ((lg)->_rawChannel != nullptr ? static_cast<short>((lg)->_rawChannel->GetId()) : 0) : 0)

// The init log suffix. The original reads the values from the parameter, not from the members.
#define INIT_LOG(logType, line, msg)                                                                                 \
    JOB_LOG(logType, line, msg, L", gate-wid:%d, label-id:0x%I64X, item-instance-id:0x%I64X, item-data-id:%u",      \
            GATE_WID(p->lgate), p->labelId, p->itemInstanceId, p->itemDataId)

#define NP_LOG_ARGS(res)                                                                                             \
    (res)->GetTransactionId(), (res)->GetCommand(), (res)->GetMessageType(), (res)->msgInfo.errInfo.nStatusCode,     \
        (res)->msgInfo.errInfo.pwszReason != nullptr ? (res)->msgInfo.errInfo.pwszReason : L"null",                 \
        (res)->msgInfo.errInfo.nErrorCode

#define GUID_ARGS(g)                                                                                                 \
    (g).guid.id1, (g).guid.id2, (g).guid.id3, (g).guid.id4[0], (g).guid.id4[1], (g).guid.id4[2], (g).guid.id4[3],    \
        (g).guid.id4[4], (g).guid.id4[5], (g).guid.id4[6], (g).guid.id4[7]

// PDB enum ECliSessionState (CliSession.h has no copy yet): CSS_LOBBY = 0x20000.
// PDB LobbyService::DB::serviceType of AddSlotService: 1.

namespace
{
LobbyJobStateDef const StateDef[] = {{0, L"INIT"},
                                     {1, L"CHECK_ACCOUNT_INVENTORY_ITEM"},
                                     {2, L"CHECK_SLOT_CAPACITY"},
                                     {3, L"REGISTER_SERVICE_ENTRY"},
                                     {4, L"TRY_CONSUME_ACCOUNT_INVENTORY_ITEM"},
                                     {5, L"CREATE_SLOT"},
                                     {6, L"FIN_CONSUME_ACCOUNT_INVENTORY_ITEM"},
                                     {7, L"FIN_SERVICE_ENTRY"},
                                     {8, L"FIN"}};  // 0x12e4f0

bool IsSuccess(StsMsgLib::_StsMsgResponse const* res)
{
    unsigned int const statusCode = res->msgInfo.errInfo.nStatusCode;
    wchar_t const* const reason = res->msgInfo.errInfo.pwszReason;
    return statusCode == 200 || (statusCode == 400 && _wcsicmp(L"Success", reason != nullptr ? reason : L"null") == 0);
}

// The original has this search inline in each caller.
bool HasAddSlotServiceEntry(CliSession* owner)
{
    for (std::vector<LobbyService*, StlAllocator<LobbyService*, 2> >::iterator it = owner->_serviceEntries.begin();
         it != owner->_serviceEntries.end(); ++it)
    {
        if (*it != nullptr && (*it)->GetDB().serviceType == 1)
            return true;
    }
    return false;
}

// The original has this search inline in each caller. It returns null when the entry is not an AddSlotService.
AddSlotService* FindAddSlotServiceEntry(CliSession* owner, unsigned long long serviceId)
{
    LobbyService* found = nullptr;
    for (std::vector<LobbyService*, StlAllocator<LobbyService*, 2> >::iterator it = owner->_serviceEntries.begin();
         it != owner->_serviceEntries.end(); ++it)
    {
        if (*it != nullptr && (*it)->GetDB().serviceId == serviceId)
        {
            found = *it;
            break;
        }
    }
    if (found == nullptr || found->GetDB().serviceType != 1)
        return nullptr;
    return static_cast<AddSlotService*>(found);
}
}  // namespace

LobbyJobDef AddSlotJob::_def = {27, StateDef, 8, L"AddSlotJob"};  // 0x2020a0
// LIFT: AddSlotJob::_pool has no definition. The LobbyDaemon ObjectPool module is not in lift_lobbydaemon
// (see CliSession.cpp).

// 0xd1e0
LobbyJobDef const* AddSlotJob::GetDefinition() const
{
    return &_def;
}

// 0xd1f0
// LIFT: Not done. The body calls _pool.Checkin. ObjPool is not in lift_lobbydaemon.
void AddSlotJob::deallocate_me(void*, wchar_t const*, int)
{
    LIFT_STUB(0xd1f0);
}

// 0xd240
// The original constructs a job on the stack (null owner) and returns its vfptr. It does not run the destructor.
void* AddSlotJob::_vtbl()
{
    char buf[sizeof(AddSlotJob)];
    AddSlotJob* job = ::new (buf) AddSlotJob(nullptr);
    return *reinterpret_cast<void**>(job);
}

// 0xd2c0
AddSlotJob::AddSlotJob(CliSession* owner)
    : CliSessionJob(owner), _tran(nullptr), _lgate(nullptr), _acciv(nullptr), _labelId(0), _itemInstanceId(0),
      _itemDataId(0), _serviceId(0)
{
    _slotId.id[0] = 0;
    _slotId.id[1] = 0;
}

// 0xd340
AddSlotJob::~AddSlotJob()
{
    if (_tran != nullptr)
        _tran->removeReferenceCount(kFile, 94);
    if (_lgate != nullptr)
        _lgate->removeReferenceCount(kFile, 96);
}

// 0xd3b0
bool AddSlotJob::work(int task, void* param)
{
    bool result = false;
    if (_state == INIT && task == 26)
    {
        result = init(param);
        task = 0;
    }
    if (_state == CHECK_ACCOUNT_INVENTORY_ITEM)
    {
        if (task == 0)
        {
            result = checkAccountInventoryItem();
        }
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
    if (_state == CHECK_SLOT_CAPACITY)
    {
        if (task == 0)
        {
            result = checkSlotCapacity();
        }
        else if (task == 39)
        {
            result = checkSlotCapacityAck(param);
            task = 0;
        }
        else if (task == 40)
        {
            result = checkSlotCapacityExpire();
            task = 0;
        }
    }
    if (_state == REGISTER_SERVICE_ENTRY && task == 0)
        result = registerServiceEntry();
    if (_state == TRY_CONSUME_ACCOUNT_INVENTORY_ITEM)
    {
        if (task == 0)
        {
            result = tryConsumeAccountInventoryItem();
        }
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
    if (_state == CREATE_SLOT)
    {
        if (task == 0)
        {
            result = createSlot();
        }
        else if (task == 41)
        {
            result = createSlotAck(param);
            task = 0;
        }
        else if (task == 42)
        {
            result = createSlotExpire();
            task = 0;
        }
    }
    if (_state == FIN_CONSUME_ACCOUNT_INVENTORY_ITEM)
    {
        if (task == 0)
        {
            result = finConsumeAccountInventoryItem();
        }
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

// 0xd570
bool AddSlotJob::init(void* param)
{
    AddSlotWithAccountInventoryItemReqParam* const p = static_cast<AddSlotWithAccountInventoryItemReqParam*>(param);
    if (p == nullptr || p->lgate == nullptr || p->labelId == 0 || p->itemInstanceId == 0)
    {
        JOB_LOG(Log::LT_ERROR, 215, L"[job], invalid param", L"");
        transit(FIN);
        return true;
    }

    _tran = new (Memory::_Manager[2]->Alloc(sizeof(LobbyJobTransaction), kFile, 223)) LobbyJobTransaction;
    _lgate = p->lgate;
    _labelId = p->labelId;
    _itemInstanceId = p->itemInstanceId;
    _itemDataId = p->itemDataId;
    _lgate->addReferenceCount(false, kFile, 229);
    _acciv = LobbyDaemon::_instance->_accountInventoryChannel;

    short reason;
    NPGameServiceChannel* gs;
    if (_acciv == nullptr || !_acciv->IsConnected())
    {
        INIT_LOG(Log::LT_ERROR, 234, L"[job], init fail; account-inventory N/A");
        reason = 7;
    }
    else if ((gs = LobbyDaemon::_instance->_npServchmgr->_gameServChannel) == nullptr || !gs->IsConnected())
    {
        INIT_LOG(Log::LT_ERROR, 244, L"[job], init fail; np N/A");
        reason = 7;
    }
    else if (!LobbyDaemon::_instance->CheckServiceItemDataId(LobbyDaemon::SERVICEITEMTYPE_ADD_SLOT, _itemDataId))
    {
        INIT_LOG(Log::LT_ERROR, 252, L"[job], not proper item");
        reason = 206;
    }
    else if (_owner->_state != 0x20000)  // CSS_LOBBY
    {
        INIT_LOG(Log::LT_ERROR, 260, L"[job], cli-session not in lobby");
        reason = 5;
    }
    else if (HasAddSlotServiceEntry(_owner))
    {
        INIT_LOG(Log::LT_ERROR, 267, L"[job], init fail; already in service");
        reason = 9;
    }
    else
    {
        INIT_LOG(Log::LT_DEBUG, 273, L"[job], init ok");
        transit(CHECK_ACCOUNT_INVENTORY_ITEM);
        return true;
    }
    _lgate->SendAddSlotWithAccountInventoryItemFail(_owner->_clikey, _labelId, _itemInstanceId, reason);
    transit(FIN);
    return true;
}

// 0xdc90
bool AddSlotJob::checkAccountInventoryItem()
{
    if (!_acciv->SendRetrieveSingleWarehouseItemReq(_tran->Set(this, 158), _itemInstanceId, _owner->_acb._id, 0))
    {
        JOB_LOG(Log::LT_ERROR, 289, L"[job], not sent", L"");
        _lgate->SendAddSlotWithAccountInventoryItemFail(_owner->_clikey, _labelId, _itemInstanceId, 7);
        transit(FIN);
    }
    else
    {
        JOB_LOG(Log::LT_DEBUG, 295, L"[job], sent", L"");
    }
    return true;
}

// 0xde30
bool AddSlotJob::checkAccountInventoryItemOk(void* param)
{
    _acciv->TRecv(_tran);
    RetrieveSingleWarehouseItemOkParam* const ok = static_cast<RetrieveSingleWarehouseItemOkParam*>(param);
    short reason;
    if (ok == nullptr)
    {
        JOB_CRASH(304, L"== CRASH == [job], invalid param");
        reason = 2;
    }
    else if (ok->item == nullptr)
    {
        JOB_LOG(Log::LT_ERROR, 314, L"[job], null item", L"");
        reason = 2;
    }
    else
    {
        LobbyServiceItem const* const item = ok->item;
        JOB_LOG(Log::LT_DEBUG, 322, L"[job], ok recv", L", item-instance-id:0x%I64X, label-id:0x%I64X, item-data-id:%u, state:%d",
                item->instanceId, item->labelId, item->dataId, item->state);
        if (_itemDataId != item->dataId)
        {
            JOB_LOG(Log::LT_ERROR, 325, L"[job], item-data-id mismatch",
                    L", request-item-data-id:%u, required-item-data-id:%u", _itemDataId, item->dataId);
            reason = 206;
        }
        else if (item->state != 1)
        {
            JOB_LOG(Log::LT_ERROR, 332, L"[job], unusable item", L"");
            reason = 205;
        }
        else
        {
            transit(LobbyDaemon::_instance->_config->_checkSlotCapacity ? CHECK_SLOT_CAPACITY : REGISTER_SERVICE_ENTRY);
            return true;
        }
    }
    _lgate->SendAddSlotWithAccountInventoryItemFail(_owner->_clikey, _labelId, _itemInstanceId, reason);
    transit(FIN);
    return true;
}

// 0xe2a0
bool AddSlotJob::checkAccountInventoryItemFail(void* param)
{
    _acciv->TRecv(_tran);
    short* const fail = static_cast<short*>(param);
    short reason;
    if (fail == nullptr)
    {
        JOB_CRASH(351, L"== CRASH == [job], invalid param");
        reason = 2;
    }
    else
    {
        JOB_LOG(Log::LT_DEBUG, 360, L"[job], fail recv", L", reason:%d", *fail);
        reason = 2;
        if (*fail == 20)
            reason = 204;
    }
    _lgate->SendAddSlotWithAccountInventoryItemFail(_owner->_clikey, _labelId, _itemInstanceId, reason);
    transit(FIN);
    return true;
}

// 0xe500
bool AddSlotJob::checkAccountInventoryItemTimeout()
{
    JOB_LOG(Log::LT_ERROR, 380, L"[job], timeout", L"");
    _lgate->SendAddSlotWithAccountInventoryItemFail(_owner->_clikey, _labelId, _itemInstanceId, 7);
    transit(FIN);
    return true;
}

// 0xe610
bool AddSlotJob::checkSlotCapacity()
{
    NPGameServiceChannel* const gs = LobbyDaemon::_instance->_npServchmgr->_gameServChannel;
    NPLobbyJobTransaction* const tr = new (Memory::_Manager[2]->Alloc(sizeof(NPLobbyJobTransaction), kFile, 399))
        NPLobbyJobTransaction;
    if (gs != nullptr)
    {
        StsMsgLib::_StsMsgRequestSlotListSlots msg;
        msg.msgInfo.eCmd = StsMsgLib::COMMAND_COMMON_SLOT_LIST_SLOTS;
        msg.msgInfo.msgType = StsMsgLib::MESSAGE_TYPE_REQUEST;
        msg.msgInfo.nTxnId = 0;
        msg.pUserId = &_owner->_acb._id;
        msg.pwszSlotType = const_cast<wchar_t*>(L"char");
        if (gs->SendMsg(&msg, true, tr->Set(this, 40)))
        {
            JOB_LOG(Log::LT_DEBUG, 411, L"[job], request slot list sent", L"");
            return true;
        }
    }
    JOB_LOG(Log::LT_ERROR, 404, L"[job], send request slot list fail; np N/A", L"");
    _lgate->SendAddSlotWithAccountInventoryItemFail(_owner->_clikey, _labelId, _itemInstanceId, 7);
    // LIFT: the original calls the scalar deleting destructor (flag 1) and then Free. Its operator delete is empty.
    tr->~NPLobbyJobTransaction();
    Memory::_Manager[2]->Free(tr, kFile, 406);
    transit(FIN);
    return true;
}

// 0xe8b0
bool AddSlotJob::checkSlotCapacityAck(void* param)
{
    StsMsgLib::_StsMsgResponseSlotListSlots* const res = static_cast<StsMsgLib::_StsMsgResponseSlotListSlots*>(param);
    if (res == nullptr)
    {
        JOB_LOG(Log::LT_ERROR, 420, L"[job], response slot list fail; invalid param", L"");
        _lgate->SendAddSlotWithAccountInventoryItemFail(_owner->_clikey, _labelId, _itemInstanceId, 2);
        transit(FIN);
        return true;
    }
    if (!IsSuccess(res))
    {
        JOB_LOG(Log::LT_ERROR, 428, L"[job], response slot list error",
                L", np-tid:%u, cmd:%d, type:%d, status-code:%u, reason:%s, error-code:%d", NP_LOG_ARGS(res));
        _lgate->SendAddSlotWithAccountInventoryItemFail(_owner->_clikey, _labelId, _itemInstanceId, 1);
        transit(FIN);
        return true;
    }
    JOB_LOG(Log::LT_DEBUG, 436, L"[job], response slot list",
            L", slot-count:%d, np-tid:%u, cmd:%d, type:%d, status-code:%u, reason:%s, error-code:%d", res->nCount,
            NP_LOG_ARGS(res));
    if (res->nCount < static_cast<unsigned int>(LobbyDaemon::_instance->_config->_maxSlotCount))
    {
        transit(REGISTER_SERVICE_ENTRY);
        return true;
    }
    JOB_LOG(Log::LT_ERROR, 439, L"[job], slot list overflow", L"");
    _lgate->SendAddSlotWithAccountInventoryItemFail(_owner->_clikey, _labelId, _itemInstanceId, 207);
    transit(FIN);
    return true;
}

// 0xedb0
bool AddSlotJob::checkSlotCapacityExpire()
{
    JOB_LOG(Log::LT_ERROR, 451, L"[job], request slot list expired", L"");
    _lgate->SendAddSlotWithAccountInventoryItemFail(_owner->_clikey, _labelId, _itemInstanceId, 7);
    transit(FIN);
    return true;
}

// 0xeec0
bool AddSlotJob::registerServiceEntry()
{
    short reason;
    if (_owner->_state != 0x20000)  // CSS_LOBBY
    {
        JOB_LOG(Log::LT_ERROR, 460, L"[job], register fail; not in lobby state", L"");
        reason = 5;
    }
    else if (HasAddSlotServiceEntry(_owner))
    {
        JOB_LOG(Log::LT_ERROR, 467, L"[job], register fail; already in service", L"");
        reason = 9;
    }
    else
    {
        AddSlotService* const svc =
            new (Memory::_Manager[2]->Alloc(sizeof(AddSlotService), kFile, 473)) AddSlotService;
        LobbyService::DB sedb;
        sedb.serviceId = 0;
        sedb.serviceType = 1;
        sedb.itemInstanceId = _itemInstanceId;
        sedb.serviceState = 0;
        AddSlotService::DB db;
        db.slotid.id[0] = 0;
        db.slotid.id[1] = 0;
        svc->Setup(&sedb, &db);
        int line;
        if (!svc->Start(_owner, _itemDataId))
        {
            JOB_LOG(Log::LT_ERROR, 494, L"[job], start new lobby service fail", L"");
            _lgate->SendAddSlotWithAccountInventoryItemFail(_owner->_clikey, _labelId, _itemInstanceId, 2);
            line = 496;
        }
        else if (!_owner->addLobbyService(svc))
        {
            JOB_LOG(Log::LT_ERROR, 502, L"[job], add new lobby service fail", L", lobby-service-id:0x%I64X",
                    svc->GetDB().serviceId);
            _lgate->SendAddSlotWithAccountInventoryItemFail(_owner->_clikey, _labelId, _itemInstanceId, 208);
            line = 504;
        }
        else
        {
            _serviceId = svc->GetDB().serviceId;
            JOB_LOG(Log::LT_DEBUG, 511, L"[job], register ok", L", lobby-service-id:0x%I64X", _serviceId);
            transit(TRY_CONSUME_ACCOUNT_INVENTORY_ITEM);
            return true;
        }
        // LIFT: the original calls the virtual scalar deleting destructor (flag 1) and then Free.
        static_cast<LobbyService*>(svc)->~LobbyService();
        Memory::_Manager[2]->Free(svc, kFile, line);
        transit(FIN);
        return true;
    }
    _lgate->SendAddSlotWithAccountInventoryItemFail(_owner->_clikey, _labelId, _itemInstanceId, reason);
    transit(FIN);
    return true;
}

// 0xf370
bool AddSlotJob::tryConsumeAccountInventoryItem()
{
    if (!_acciv->SendTryWarehouseItemConsumptionReq(_tran->Set(this, 161), _labelId, _itemInstanceId, _owner->_acb._id))
    {
        JOB_LOG(Log::LT_ERROR, 522, L"[job], send fail", L"");
        _lgate->SendAddSlotWithAccountInventoryItemFail(_owner->_clikey, _labelId, _itemInstanceId, 208);
        transit(FIN);
    }
    else
    {
        JOB_LOG(Log::LT_DEBUG, 530, L"[job], send ok", L"");
    }
    return true;
}

// 0xf510
bool AddSlotJob::tryConsumeAccountInventoryItemOk(void*)
{
    _acciv->TRecv(_tran);
    JOB_LOG(Log::LT_DEBUG, 539, L"[job], ok recv", L"");
    AddSlotService* const svc = FindAddSlotServiceEntry(_owner, _serviceId);
    if (svc == nullptr)
    {
        JOB_LOG(Log::LT_ERROR, 543, L"[job], no such service-entry", L"");
    }
    else if (!svc->ConsumeItemTried(_owner))
    {
        JOB_LOG(Log::LT_ERROR, 550, L"[job], update lobby service as 'consume item tried' fail", L"");
    }
    else
    {
        JOB_LOG(Log::LT_DEBUG, 556, L"[job], try consume item ok", L"");
        transit(CREATE_SLOT);
        return true;
    }
    _lgate->SendAddSlotWithAccountInventoryItemFail(_owner->_clikey, _labelId, _itemInstanceId, 208);
    transit(FIN);
    return true;
}

// 0xf7d0
bool AddSlotJob::tryConsumeAccountInventoryItemFail(void* param)
{
    _acciv->TRecv(_tran);
    short* const fail = static_cast<short*>(param);
    if (fail == nullptr)
        JOB_CRASH(567, L"== CRASH == [job], invalid param");
    else
        JOB_LOG(Log::LT_DEBUG, 575, L"[job], fail recv", L", reason:%d", *fail);
    _lgate->SendAddSlotWithAccountInventoryItemFail(_owner->_clikey, _labelId, _itemInstanceId, 208);
    transit(FIN);
    return true;
}

// 0xfa20
bool AddSlotJob::tryConsumeAccountInventoryItemTimeout()
{
    JOB_LOG(Log::LT_ERROR, 585, L"[job], timeout", L"");
    _lgate->SendAddSlotWithAccountInventoryItemFail(_owner->_clikey, _labelId, _itemInstanceId, 208);
    transit(FIN);
    return true;
}

// 0xfb30
bool AddSlotJob::createSlot()
{
    NPGameServiceChannel* const gs = LobbyDaemon::_instance->_npServchmgr->_gameServChannel;
    NPLobbyJobTransaction* const tr = new (Memory::_Manager[2]->Alloc(sizeof(NPLobbyJobTransaction), kFile, 611))
        NPLobbyJobTransaction;
    wchar_t tkey[129];
    swprintf_s(tkey, L"/bns/lobby/%I64u", _serviceId);
    if (gs != nullptr)
    {
        StsMsgLib::_StsMsgRequestSlotCreateSlots msg;
        msg.msgInfo.eCmd = StsMsgLib::COMMAND_SRV_SLOT_CREATE_SLOTS;
        msg.msgInfo.msgType = StsMsgLib::MESSAGE_TYPE_REQUEST;
        msg.msgInfo.nTxnId = 0;
        msg.pUserId = &_owner->_acb._id;
        msg.pwszSlotType = const_cast<wchar_t*>(L"char");
        msg.slotData.serviceId = static_cast<long long>(_serviceId);
        msg.pwszSlotData = nullptr;
        msg.nCount = 1;
        msg.pwszTransactionKey = tkey;
        if (gs->SendMsg(&msg, true, tr->Set(this, 42)))
        {
            JOB_LOG(Log::LT_DEBUG, 625, L"[job], sent", L"");
            return true;
        }
    }
    JOB_LOG(Log::LT_ERROR, 618, L"[job], send fail", L"");
    _lgate->SendAddSlotWithAccountInventoryItemFail(_owner->_clikey, _labelId, _itemInstanceId, 208);
    // LIFT: the original calls the scalar deleting destructor (flag 1) and then Free. Its operator delete is empty.
    tr->~NPLobbyJobTransaction();
    Memory::_Manager[2]->Free(tr, kFile, 620);
    transit(FIN);
    return true;
}

// 0xfe00
bool AddSlotJob::createSlotAck(void* param)
{
    StsMsgLib::_StsMsgResponseSlotCreateSlots* const res = static_cast<StsMsgLib::_StsMsgResponseSlotCreateSlots*>(param);
    if (res == nullptr)
    {
        JOB_CRASH(635, L"== CRASH == [job], invalid param");
    }
    else
    {
        JOB_LOG(Log::LT_DEBUG, 642, L"[job], create slot response recv",
                L", np-tid:%u, cmd:%d, type:%d, status-code:%u, reason:%s, error-code:%d", NP_LOG_ARGS(res));
        if (!IsSuccess(res))
        {
            JOB_LOG(Log::LT_ERROR, 646, L"[job], create slot fail recv", L"");
        }
        else if (res->pSlotId == nullptr)
        {
            JOB_LOG(Log::LT_ERROR, 656, L"[job], invalid slot id",
                    L", np-tid:%u, cmd:%d, type:%d, status-code:%u, reason:%s, error-code:%d", NP_LOG_ARGS(res));
        }
        else
        {
            _slotId = *res->pSlotId;
            JOB_LOG(Log::LT_DEBUG, 664, L"[job], slot created",
                    L", slot-id:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X", GUID_ARGS(_slotId));
            AddSlotService* const svc = FindAddSlotServiceEntry(_owner, _serviceId);
            if (svc == nullptr)
            {
                JOB_LOG(Log::LT_ERROR, 669, L"[job], no such service-entry", L"");
            }
            else if (!svc->TaskDone(_owner, _slotId))
            {
                JOB_LOG(Log::LT_ERROR, 677, L"[job], set service-entry as 'served' fail", L"");
            }
            else
            {
                JOB_LOG(Log::LT_DEBUG, 683, L"[job], set service-entry as 'served' ok", L"");
                transit(FIN_CONSUME_ACCOUNT_INVENTORY_ITEM);
                return true;
            }
        }
    }
    _lgate->SendAddSlotWithAccountInventoryItemFail(_owner->_clikey, _labelId, _itemInstanceId, 208);
    transit(FIN);
    return true;
}

// 0x105a0
bool AddSlotJob::createSlotExpire()
{
    JOB_LOG(Log::LT_ERROR, 691, L"[job], create slot timeout", L"");
    _lgate->SendAddSlotWithAccountInventoryItemFail(_owner->_clikey, _labelId, _itemInstanceId, 208);
    transit(FIN);
    return true;
}

// 0x106b0
bool AddSlotJob::finConsumeAccountInventoryItem()
{
    // LIFT: the PDB declares a 5th parameter (short result). LTCG folded the constant 0 into the callee (0x7810).
    if (!_acciv->SendFinishWarehouseItemConsumptionReq(_tran->Set(this, 164), _labelId, _itemInstanceId,
                                                       _owner->_acb._id, 0))
    {
        JOB_LOG(Log::LT_ERROR, 708, L"[job], send fail", L"");
        _lgate->SendAddSlotWithAccountInventoryItemFail(_owner->_clikey, _labelId, _itemInstanceId, 208);
        transit(FIN);
    }
    else
    {
        JOB_LOG(Log::LT_DEBUG, 714, L"[job], sent", L"");
    }
    return true;
}

// 0x10850
bool AddSlotJob::finConsumeAccountInventoryItemOk(void*)
{
    _acciv->TRecv(_tran);
    JOB_LOG(Log::LT_DEBUG, 723, L"[job], ok recv", L"");
    AddSlotService* const svc = FindAddSlotServiceEntry(_owner, _serviceId);
    if (svc == nullptr)
    {
        JOB_LOG(Log::LT_ERROR, 728, L"[job], no such service-entry", L"");
    }
    else if (!svc->ConsumeItemFinished(_owner))
    {
        JOB_LOG(Log::LT_ERROR, 736, L"[job], set service-entry as 'consume item fin' fail", L"");
    }
    else
    {
        JOB_LOG(Log::LT_DEBUG, 742, L"[job], set service-entry as 'consume item fin' ok", L"");
        transit(FIN_SERVICE_ENTRY);
        return true;
    }
    _lgate->SendAddSlotWithAccountInventoryItemFail(_owner->_clikey, _labelId, _itemInstanceId, 208);
    transit(FIN);
    return true;
}

// 0x10b10
bool AddSlotJob::finConsumeAccountInventoryItemFail(void* param)
{
    _acciv->TRecv(_tran);
    short* const fail = static_cast<short*>(param);
    if (fail == nullptr)
        JOB_CRASH(754, L"== CRASH == [job], invalid param");
    else
        JOB_LOG(Log::LT_DEBUG, 762, L"[job], fail recv", L", reason:%d", *fail);
    _lgate->SendAddSlotWithAccountInventoryItemFail(_owner->_clikey, _labelId, _itemInstanceId, 208);
    transit(FIN);
    return true;
}

// 0x10d60
bool AddSlotJob::finConsumeAccountInventoryItemTimeout()
{
    JOB_LOG(Log::LT_ERROR, 772, L"[job], timeout", L"");
    _lgate->SendAddSlotWithAccountInventoryItemFail(_owner->_clikey, _labelId, _itemInstanceId, 208);
    transit(FIN);
    return true;
}

// 0x10e70
bool AddSlotJob::finServiceEntry()
{
    AddSlotService* const svc = FindAddSlotServiceEntry(_owner, _serviceId);
    if (svc == nullptr)
    {
        JOB_LOG(Log::LT_ERROR, 786, L"[job], no such service-entry", L"");
        _lgate->SendAddSlotWithAccountInventoryItemFail(_owner->_clikey, _labelId, _itemInstanceId, 208);
    }
    else if (!svc->Finish(_owner))
    {
        JOB_LOG(Log::LT_ERROR, 794, L"[job], finish service-entry fail", L"");
        _lgate->SendAddSlotWithAccountInventoryItemFail(_owner->_clikey, _labelId, _itemInstanceId, 208);
    }
    else
    {
        _owner->removeLobbyService(svc->GetDB().serviceId);
        // LIFT: the original calls the virtual scalar deleting destructor (flag 1) and then Free.
        static_cast<LobbyService*>(svc)->~LobbyService();
        Memory::_Manager[2]->Free(svc, kFile, 802);
        _lgate->SendAddSlotWithAccountInventoryItemOk(_owner->_clikey, _labelId, _itemInstanceId, _slotId);
        JOB_LOG(Log::LT_DEBUG, 807, L"[job], finish service-entry ok", L"");
    }
    transit(FIN);
    return true;
}
