// GetLobbyServiceItemJob.obj (LobbyDaemon PDB, 2019 + PDB). Lifted from the pseudocode with PDB types.
#include <new>
#include <wchar.h>
#include <winsock2.h>
#include <windows.h>
#include "GetLobbyServiceItemJob.h"
#include "AccountInventoryChannel.h"
#include "AlertSender.h"
#include "CliSession.h"
#include "LiftStub.h"
#include "LobbyDaemon.h"
#include "LobbyGateChannel.h"
#include "LobbyJobParams.h"
#include "Log.h"
#include "Memory.h"
#include "MemoryManager.h"
#include "TransactionChannel.h"

static wchar_t const kFile[] = L"GetLobbyServiceItemJob.cpp";

// The log suffix of all LobbyJob logs. The original reads the owner state 2 times (HIWORD and LOWORD).
#define JOB_LOG(logType, line, msg, fmt, ...)                                                                          \
    Log::Write(logType, kFile, line, msg L", tid:0x%I64X, type:%d, state:%d, cli-key:0x%I64X, cli-state:%d.%d" fmt,   \
               this != nullptr ? _id : 0, this != nullptr ? GetDefinition()->type : -1,                            \
               this != nullptr ? _state : -1, this != nullptr && _owner != nullptr ? _owner->_clikey : 0,          \
               HIWORD(this != nullptr && _owner != nullptr ? _owner->_state : 0),                                  \
               LOWORD(this != nullptr && _owner != nullptr ? _owner->_state : 0), ##__VA_ARGS__)

// PDB enum ECliSessionState (CliSession.h has no copy yet): CSS_LOBBY = 0x20000, CSS_INIT_create_initial_user_name = 0x10003.

namespace
{
LobbyJobStateDef const StateDef[] = {{0, L"INIT"}, {1, L"GET_LOBBY_SERVICE_ITEM"}, {2, L"FIN"}};  // 0x12df30
}

LobbyJobDef GetLobbyServiceItemJob::_def = {25, StateDef, 2, L"GetLobbyServiceItemJob"};  // 0x201c90
// LIFT: GetLobbyServiceItemJob::_pool (0x204780) has no definition. The LobbyDaemon ObjectPool module is not in lift_lobbydaemon
// (see CliSession.cpp).

// 0x52060
LobbyJobDef const* GetLobbyServiceItemJob::GetDefinition() const
{
    return &_def;
}

// 0x52070
// LIFT: Not done. The body calls _pool.Checkin. ObjPool is not in lift_lobbydaemon.
void GetLobbyServiceItemJob::deallocate_me(void*, wchar_t const*, int)
{
    LIFT_STUB(0x52070);
}

// 0x520c0
// The original constructs a job on the stack (null owner, null lobby-gate) and returns its vfptr. It does not run
// the destructor.
void* GetLobbyServiceItemJob::_vtbl()
{
    char buf[sizeof(GetLobbyServiceItemJob)];
    GetLobbyServiceItemJob* job = ::new (buf) GetLobbyServiceItemJob(nullptr, nullptr, 0);
    return *reinterpret_cast<void**>(job);
}

// 0x52140
GetLobbyServiceItemJob::GetLobbyServiceItemJob(CliSession* owner, LobbyGateChannel* lgate, unsigned long long itemInstanceId) : CliSessionJob(owner), _lgate(lgate), _acciv(nullptr), _tran(nullptr), _itemInstanceId(itemInstanceId)
{
    if (lgate != nullptr)
        lgate->addReferenceCount(false, kFile, 64);
}

// 0x521e0 (scalar deleting destructor)
GetLobbyServiceItemJob::~GetLobbyServiceItemJob()
{
    if (_lgate != nullptr)
        _lgate->removeReferenceCount(kFile, 70);
    if (_tran != nullptr)
        _tran->removeReferenceCount(kFile, 72);
}

// 0x52250
bool GetLobbyServiceItemJob::work(int task, void* param)
{
    bool result = false;
    if (_state == INIT && task == 23)
    {
        result = init();
        task = 0;
    }
    if (_state == GET_LOBBY_SERVICE_ITEM)
    {
        if (task == 0)
            return getLobbyServiceItemReq();
        else if (task == 156)
            return getLobbyServiceItemOk(param);
        else if (task == 157)
            return getLobbyServiceItemFail(param);
        else if (task == 158)
            return getLobbyServiceItemTimeout();
    }
    return result;
}

// 0x522f0
bool GetLobbyServiceItemJob::init()
{
    JOB_LOG(Log::LT_DEBUG, 110, L"[job], init param", L", item-instance-id:0x%I64X, gate-wid:%d", _itemInstanceId,
            _lgate != nullptr ? (_lgate->_rawChannel != nullptr ? static_cast<short>(_lgate->_rawChannel->GetId()) : 0) : 0);
    short reason = 0;
    if (_owner->_state != 0x20000)  // CSS_LOBBY
    {
        JOB_LOG(Log::LT_ERROR, 115, L"[job], cli-session not in lobby", L"");
        reason = 5;
    }
    else
    {
        _acciv = LobbyDaemon::_instance->_accountInventoryChannel;
        if (_acciv == nullptr)
        {
            JOB_LOG(Log::LT_ERROR, 124, L"[job], init fail; account-inventory N/A", L"");
            reason = 7;
        }
        else
        {
            _tran = new (Memory::_Manager[2]->Alloc(sizeof(LobbyJobTransaction), kFile, 130)) LobbyJobTransaction;
            JOB_LOG(Log::LT_DEBUG, 132, L"[job], init ok", L"");
        }
    }
    int next = GET_LOBBY_SERVICE_ITEM;
    if (reason != 0)
    {
        _lgate->SendGetLobbyServiceItemInfoFail(_owner->_clikey, _itemInstanceId, reason);
        next = FIN;
    }
    transit(next);
    return true;
}

// 0x52620
bool GetLobbyServiceItemJob::getLobbyServiceItemReq()
{
    if (!_acciv->SendRetrieveSingleWarehouseItemReq(_tran->Set(this, 158), _itemInstanceId, _owner->_acb._id, 0))
    {
        JOB_LOG(Log::LT_ERROR, 141, L"[job], unsent", L"");
        _lgate->SendGetLobbyServiceItemInfoFail(_owner->_clikey, _itemInstanceId, 7);
        transit(FIN);
    }
    else
    {
        JOB_LOG(Log::LT_DEBUG, 147, L"[job], list item req sent", L"");
    }
    return true;
}

// 0x527b0
bool GetLobbyServiceItemJob::getLobbyServiceItemOk(void* param)
{
    _acciv->TRecv(_tran);
    RetrieveSingleWarehouseItemOkParam* const ok = static_cast<RetrieveSingleWarehouseItemOkParam*>(param);
    int line;
    wchar_t const* msg;
    if (ok == nullptr)
    {
        line = 157;
        msg = L"[job], invalid param on ok ack, tid:0x%I64X, type:%d, state:%d, cli-key:0x%I64X, cli-state:%d.%d";
    }
    else if (ok->item == nullptr)
    {
        line = 165;
        msg = L"[job], null item, tid:0x%I64X, type:%d, state:%d, cli-key:0x%I64X, cli-state:%d.%d";
    }
    else
    {
        JOB_LOG(Log::LT_DEBUG, 171, L"[job], ok recv", L"");
        _lgate->SendGetLobbyServiceItemInfoOk(_owner->_clikey, *ok->item);
        transit(FIN);
        return true;
    }
    Log::Write(Log::LT_ERROR, kFile, line, msg, this != nullptr ? _id : 0, this != nullptr ? GetDefinition()->type : -1,
               this != nullptr ? _state : -1, this != nullptr && _owner != nullptr ? _owner->_clikey : 0,
               HIWORD(this != nullptr && _owner != nullptr ? _owner->_state : 0),
               LOWORD(this != nullptr && _owner != nullptr ? _owner->_state : 0));
    _lgate->SendGetLobbyServiceItemInfoFail(_owner->_clikey, _itemInstanceId, 2);
    transit(FIN);
    return true;
}

// 0x529d0
bool GetLobbyServiceItemJob::getLobbyServiceItemFail(void* param)
{
    _acciv->TRecv(_tran);
    short* const fail = static_cast<short*>(param);
    if (fail == nullptr)
    {
        JOB_LOG(Log::LT_ERROR, 184, L"[job], invalid param on fail ack", L"");
        _lgate->SendGetLobbyServiceItemInfoFail(_owner->_clikey, _itemInstanceId, 2);
        transit(FIN);
    }
    else
    {
        short const reason = *fail;
        JOB_LOG(Log::LT_DEBUG, 191, L"[job], fail recv", L", reason:%d", reason);
        short out = 2;
        if (reason == 3)
            out = 7;
        else if (reason == 20)
            out = 171;
        _lgate->SendGetLobbyServiceItemInfoFail(_owner->_clikey, _itemInstanceId, out);
        transit(FIN);
    }
    return true;
}

// 0x52be0
bool GetLobbyServiceItemJob::getLobbyServiceItemTimeout()
{
    JOB_LOG(Log::LT_ERROR, 214, L"[job], timeout", L"");
    _lgate->SendGetLobbyServiceItemInfoFail(_owner->_clikey, _itemInstanceId, 2);
    transit(FIN);
    return true;
}
