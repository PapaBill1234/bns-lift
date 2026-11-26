// TakeGoodsJob.obj (LobbyDaemon PDB, 2019 + PDB). Lifted from the pseudocode with PDB types.
#include <new>
#include <wchar.h>
#include <winsock2.h>
#include <windows.h>
#include "TakeGoodsJob.h"
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

static wchar_t const kFile[] = L"TakeGoodsJob.cpp";

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
LobbyJobStateDef const StateDef[] = {{0, L"INIT"}, {1, L"TAKE_GOODS"}, {2, L"FIN"}};  // 0x12dbd0
}

LobbyJobDef TakeGoodsJob::_def = {23, StateDef, 2, L"TakeGoodsJob"};  // 0x201950

#include "ObjectPoolLobbyDaemon.h"

// .data 0x2051d0, dynamic init 0x11e430, atexit dtor 0x11f140.
// The exe .data holds id 1, objsize 0x78, desc L"TakeGoodsJob".
ObjPool TakeGoodsJob::_pool(1, 0x78, L"TakeGoodsJob");

// 0x79f00
LobbyJobDef const* TakeGoodsJob::GetDefinition() const
{
    return &_def;
}

// 0x79f10
// LIFT: Not done. The body calls _pool.Checkin. ObjPool is not in lift_lobbydaemon.
void TakeGoodsJob::deallocate_me(void*, wchar_t const*, int)
{
    LIFT_STUB(0x79f10);
}

// 0x79f60
// The original constructs a job on the stack (null owner, null lobby-gate) and returns its vfptr. It does not run
// the destructor.
void* TakeGoodsJob::_vtbl()
{
    char buf[sizeof(TakeGoodsJob)];
    TakeGoodsJob* job = ::new (buf) TakeGoodsJob(nullptr, nullptr, 0);
    return *reinterpret_cast<void**>(job);
}

// 0x79fe0
TakeGoodsJob::TakeGoodsJob(CliSession* owner, LobbyGateChannel* lgate, unsigned long long goodsId) : CliSessionJob(owner), _lgate(lgate), _acciv(nullptr), _tran(nullptr), _goodsId(goodsId)
{
    if (lgate != nullptr)
        lgate->addReferenceCount(false, kFile, 64);
}

// 0x7a080 (scalar deleting destructor)
TakeGoodsJob::~TakeGoodsJob()
{
    if (_lgate != nullptr)
        _lgate->removeReferenceCount(kFile, 70);
    if (_tran != nullptr)
        _tran->removeReferenceCount(kFile, 72);
}

// 0x7a0f0
bool TakeGoodsJob::work(int task, void* param)
{
    bool result = false;
    if (_state == INIT && task == 21)
    {
        result = init();
        task = 0;
    }
    if (_state == TAKE_GOODS)
    {
        if (task == 0)
            return takeGoodsReq();
        else if (task == 150)
            return takeGoodsOk(param);
        else if (task == 151)
            return takeGoodsFail(param);
        else if (task == 152)
            return takeGoodsTimeout();
    }
    return result;
}

// 0x7a190
bool TakeGoodsJob::init()
{
    JOB_LOG(Log::LT_DEBUG, 110, L"[job], init param", L", gate-wid:%d, goods-id:0x%I64X",
            _lgate != nullptr ? (_lgate->_rawChannel != nullptr ? static_cast<short>(_lgate->_rawChannel->GetId()) : 0) : 0, _goodsId);
    short reason = 0;
    if (_goodsId == 0)
    {
        JOB_LOG(Log::LT_ERROR, 113, L"[job], invalid parameter", L"");
        reason = 6;
    }
    else if (_owner->_state != 0x20000)  // CSS_LOBBY
    {
        JOB_LOG(Log::LT_ERROR, 122, L"[job], cli-session not in lobby", L"");
        reason = 5;
    }
    else
    {
        _acciv = LobbyDaemon::_instance->_accountInventoryChannel;
        if (_acciv == nullptr)
        {
            JOB_LOG(Log::LT_ERROR, 131, L"[job], init fail; account-inventory N/A", L"");
            reason = 7;
        }
        else
        {
            _tran = new (Memory::_Manager[2]->Alloc(sizeof(LobbyJobTransaction), kFile, 137)) LobbyJobTransaction;
            JOB_LOG(Log::LT_DEBUG, 139, L"[job], init ok", L"");
        }
    }
    int next = TAKE_GOODS;
    if (reason != 0)
    {
        _lgate->SendTakeGoodsFail(_owner->_clikey, reason);
        next = FIN;
    }
    transit(next);
    return true;
}

// 0x7a540
bool TakeGoodsJob::takeGoodsReq()
{
    if (!_acciv->SendTakeGoodsReq(_tran->Set(this, 152), _owner->_acb._id, _goodsId))
    {
        JOB_LOG(Log::LT_ERROR, 148, L"[job], unsent", L"");
        _lgate->SendTakeGoodsFail(_owner->_clikey, 7);
        transit(FIN);
    }
    else
    {
        JOB_LOG(Log::LT_DEBUG, 154, L"[job], take goods req sent", L"");
    }
    return true;
}

// 0x7a6d0
bool TakeGoodsJob::takeGoodsOk(void* param)
{
    _acciv->TRecv(_tran);
    TakeGoodsOkParam* const ok = static_cast<TakeGoodsOkParam*>(param);
    if (ok == nullptr)
    {
        JOB_LOG(Log::LT_ERROR, 164, L"[job], invalid param on ok ack", L"");
        _lgate->SendTakeGoodsFail(_owner->_clikey, 2);
        transit(FIN);
    }
    else
    {
        JOB_LOG(Log::LT_DEBUG, 173, L"[job], ok recv", L", item-count:%d", ok->itemCount);
        _lgate->SendTakeGoodsOk(_owner->_clikey, _goodsId, ok->items, ok->itemCount);
        transit(FIN);
    }
    return true;
}

// 0x7a8d0
bool TakeGoodsJob::takeGoodsFail(void* param)
{
    _acciv->TRecv(_tran);
    short* const fail = static_cast<short*>(param);
    short reason;
    if (fail == nullptr)
    {
        JOB_LOG(Log::LT_ERROR, 186, L"[job], invalid param on fail ack", L"");
        reason = 2;
    }
    else
    {
        JOB_LOG(Log::LT_DEBUG, 193, L"[job], fail recv", L", reason:%d", *fail);
        switch (*fail)
        {
        case 3:
        case 5:
            reason = 7;
            break;
        case 15:
            reason = 166;
            break;
        case 16:
            reason = 167;
            break;
        case 17:
            reason = 168;
            break;
        case 18:
            reason = 169;
            break;
        case 19:
            reason = 170;
            break;
        default:
            reason = 2;
            break;
        }
    }
    _lgate->SendTakeGoodsFail(_owner->_clikey, reason);
    transit(FIN);
    return true;
}

// 0x7ab30
bool TakeGoodsJob::takeGoodsTimeout()
{
    JOB_LOG(Log::LT_ERROR, 229, L"[job], timeout", L"");
    _lgate->SendTakeGoodsFail(_owner->_clikey, 2);
    transit(FIN);
    return true;
}
