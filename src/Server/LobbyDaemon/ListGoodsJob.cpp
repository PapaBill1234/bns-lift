// ListGoodsJob.obj (LobbyDaemon PDB, 2019 + PDB). Lifted from the pseudocode with PDB types.
#include <new>
#include <wchar.h>
#include <winsock2.h>
#include <windows.h>
#include "ListGoodsJob.h"
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

static wchar_t const kFile[] = L"ListGoodsJob.cpp";

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
LobbyJobStateDef const StateDef[] = {{0, L"INIT"}, {1, L"LIST_GOODS"}, {2, L"FIN"}};  // 0x12dea0
}

LobbyJobDef ListGoodsJob::_def = {22, StateDef, 2, L"ListGoodsJob"};  // 0x201c30
// LIFT: ListGoodsJob::_pool (0x204990) has no definition. The LobbyDaemon ObjectPool module is not in lift_lobbydaemon
// (see CliSession.cpp).

// 0x54ee0
LobbyJobDef const* ListGoodsJob::GetDefinition() const
{
    return &_def;
}

// 0x54ef0
// LIFT: Not done. The body calls _pool.Checkin. ObjPool is not in lift_lobbydaemon.
void ListGoodsJob::deallocate_me(void*, wchar_t const*, int)
{
    LIFT_STUB(0x54ef0);
}

// 0x54f40
// The original constructs a job on the stack (null owner, null lobby-gate) and returns its vfptr. It does not run
// the destructor.
void* ListGoodsJob::_vtbl()
{
    char buf[sizeof(ListGoodsJob)];
    ListGoodsJob* job = ::new (buf) ListGoodsJob(nullptr, nullptr);
    return *reinterpret_cast<void**>(job);
}

// 0x54fc0
ListGoodsJob::ListGoodsJob(CliSession* owner, LobbyGateChannel* lgate) : CliSessionJob(owner), _languageCode(0), _lgate(lgate), _acciv(nullptr), _tran(nullptr)
{
    if (lgate != nullptr)
        lgate->addReferenceCount(false, kFile, 64);
}

// 0x55050 (scalar deleting destructor)
ListGoodsJob::~ListGoodsJob()
{
    if (_lgate != nullptr)
        _lgate->removeReferenceCount(kFile, 70);
    if (_tran != nullptr)
        _tran->removeReferenceCount(kFile, 72);
}

// 0x550c0
bool ListGoodsJob::work(int task, void* param)
{
    bool result = false;
    if (_state == INIT && task == 20)
    {
        result = init(param);
        task = 0;
    }
    if (_state == LIST_GOODS)
    {
        if (task == 0)
            return listGoodsReq();
        else if (task == 147)
            return listGoodsOk(param);
        else if (task == 148)
            return listGoodsFail(param);
        else if (task == 149)
            return listGoodsTimeout();
    }
    return result;
}

// 0x55160
bool ListGoodsJob::init(void* param)
{
    JOB_LOG(Log::LT_DEBUG, 110, L"[job], init param", L", gate-wid:%d", _lgate != nullptr ? (_lgate->_rawChannel != nullptr ? static_cast<short>(_lgate->_rawChannel->GetId()) : 0) : 0);
    short reason = 0;
    if (_owner->_state != 0x20000)  // CSS_LOBBY
    {
        JOB_LOG(Log::LT_ERROR, 115, L"[job], cli-session not in lobby", L"");
        reason = 5;
    }
    else
    {
        _acciv = LobbyDaemon::_instance->_accountInventoryChannel;
        if (param != nullptr)
            _languageCode = *static_cast<char*>(param);
        if (_acciv == nullptr)
        {
            JOB_LOG(Log::LT_ERROR, 130, L"[job], init fail; account-inventory N/A", L"");
            reason = 7;
        }
        else
        {
            _tran = new (Memory::_Manager[2]->Alloc(sizeof(LobbyJobTransaction), kFile, 136)) LobbyJobTransaction;
            JOB_LOG(Log::LT_DEBUG, 138, L"[job], init ok", L"");
        }
    }
    int next = LIST_GOODS;
    if (reason != 0)
    {
        _lgate->SendListGoodsFail(_owner->_clikey, reason);
        next = FIN;
    }
    transit(next);
    return true;
}

// 0x55490
bool ListGoodsJob::listGoodsReq()
{
    if (!_acciv->SendListGoodsReq(_tran->Set(this, 149), _owner->_acb._id, _languageCode))
    {
        JOB_LOG(Log::LT_ERROR, 147, L"[job], unsent", L"");
        _lgate->SendListGoodsFail(_owner->_clikey, 7);
        transit(FIN);
    }
    else
    {
        JOB_LOG(Log::LT_DEBUG, 153, L"[job], list goods req sent", L"");
    }
    return true;
}

// 0x55620
bool ListGoodsJob::listGoodsOk(void* param)
{
    _acciv->TRecv(_tran);
    ListGoodsOkParam* const ok = static_cast<ListGoodsOkParam*>(param);
    if (ok == nullptr)
    {
        JOB_LOG(Log::LT_ERROR, 163, L"[job], invalid param on ok ack", L"");
        _lgate->SendListGoodsFail(_owner->_clikey, 2);
        transit(FIN);
    }
    else
    {
        JOB_LOG(Log::LT_DEBUG, 172, L"[job], ok recv", L", goods-count:%d", ok->goodsCount);
        _lgate->SendListGoodsOk(_owner->_clikey, ok->goodsList, ok->goodsCount);
        transit(FIN);
    }
    return true;
}

// 0x55820
bool ListGoodsJob::listGoodsFail(void* param)
{
    _acciv->TRecv(_tran);
    short* const fail = static_cast<short*>(param);
    if (fail == nullptr)
    {
        JOB_LOG(Log::LT_ERROR, 185, L"[job], invalid param on fail ack", L"");
        _lgate->SendListGoodsFail(_owner->_clikey, 2);
        transit(FIN);
    }
    else
    {
        short const reason = *fail;
        JOB_LOG(Log::LT_DEBUG, 192, L"[job], fail recv", L", reason:%d", reason);
        _lgate->SendListGoodsFail(_owner->_clikey, reason == 3 || reason == 5 ? 7 : 2);
        transit(FIN);
    }
    return true;
}

// 0x55a20
bool ListGoodsJob::listGoodsTimeout()
{
    JOB_LOG(Log::LT_ERROR, 214, L"[job], timeout", L"");
    _lgate->SendListGoodsFail(_owner->_clikey, 2);
    transit(FIN);
    return true;
}
