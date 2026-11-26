// GetGoodsCountJob.obj (LobbyDaemon PDB, 2019 + PDB). Lifted from the pseudocode with PDB types.
#include <new>
#include <wchar.h>
#include <winsock2.h>
#include <windows.h>
#include "GetGoodsCountJob.h"
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

static wchar_t const kFile[] = L"GetGoodsCountJob.cpp";

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
LobbyJobStateDef const StateDef[] = {{0, L"INIT"}, {1, L"GET_GOODS_COUNT"}, {2, L"FIN"}};  // 0x12df60
}

LobbyJobDef GetGoodsCountJob::_def = {21, StateDef, 2, L"GetGoodsCountJob"};  // 0x201cb0

#include "ObjectPoolLobbyDaemon.h"

// .data 0x2046d0, dynamic init 0x11df30, atexit dtor 0x11ed40.
// The exe .data holds id 1, objsize 0x70, desc L"GetGoodsCountJob".
ObjPool GetGoodsCountJob::_pool(1, 0x70, L"GetGoodsCountJob");

// 0x51460
LobbyJobDef const* GetGoodsCountJob::GetDefinition() const
{
    return &_def;
}

// 0x51470
// LIFT: Not done. The body calls _pool.Checkin. ObjPool is not in lift_lobbydaemon.
void GetGoodsCountJob::deallocate_me(void*, wchar_t const*, int)
{
    LIFT_STUB(0x51470);
}

// 0x514c0
// The original constructs a job on the stack (null owner, null lobby-gate) and returns its vfptr. It does not run
// the destructor.
void* GetGoodsCountJob::_vtbl()
{
    char buf[sizeof(GetGoodsCountJob)];
    GetGoodsCountJob* job = ::new (buf) GetGoodsCountJob(nullptr, nullptr);
    return *reinterpret_cast<void**>(job);
}

// 0x51540
GetGoodsCountJob::GetGoodsCountJob(CliSession* owner, LobbyGateChannel* lgate) : CliSessionJob(owner), _lgate(lgate), _acciv(nullptr), _tran(nullptr)
{
    if (lgate != nullptr)
        lgate->addReferenceCount(false, kFile, 62);
}

// 0x515d0 (scalar deleting destructor)
GetGoodsCountJob::~GetGoodsCountJob()
{
    if (_lgate != nullptr)
        _lgate->removeReferenceCount(kFile, 68);
    if (_tran != nullptr)
        _tran->removeReferenceCount(kFile, 70);
}

// 0x51640
bool GetGoodsCountJob::work(int task, void* param)
{
    bool result = false;
    if (_state == INIT && task == 19)
    {
        result = init();
        task = 0;
    }
    if (_state == GET_GOODS_COUNT)
    {
        if (task == 0)
            return getGoodsCountReq();
        else if (task == 144)
            return getGoodsCountOk(param);
        else if (task == 145)
            return getGoodsCountFail(param);
        else if (task == 146)
            return getGoodsCountTimeout();
    }
    return result;
}

// 0x516e0
bool GetGoodsCountJob::init()
{
    JOB_LOG(Log::LT_DEBUG, 108, L"[job], init param", L", gate-wid:%d", _lgate != nullptr ? (_lgate->_rawChannel != nullptr ? static_cast<short>(_lgate->_rawChannel->GetId()) : 0) : 0);
    short reason = 0;
    int const cliState = _owner->_state;
    if (cliState != 0x20000 && cliState != 0x10003)  // CSS_LOBBY, CSS_INIT_create_initial_user_name
    {
        JOB_LOG(Log::LT_ERROR, 116, L"[job], cli-session not in lobby", L"");
        reason = 5;
    }
    else
    {
        _acciv = LobbyDaemon::_instance->_accountInventoryChannel;
        if (_acciv == nullptr)
        {
            JOB_LOG(Log::LT_ERROR, 125, L"[job], init fail; account-inventory N/A", L"");
            reason = 7;
        }
        else
        {
            _tran = new (Memory::_Manager[2]->Alloc(sizeof(LobbyJobTransaction), kFile, 131)) LobbyJobTransaction;
            JOB_LOG(Log::LT_DEBUG, 133, L"[job], init ok", L"");
        }
    }
    int next = GET_GOODS_COUNT;
    if (reason != 0)
    {
        _lgate->SendGetGoodsCountFail(_owner->_clikey, reason);
        next = FIN;
    }
    transit(next);
    return true;
}

// 0x51a00
bool GetGoodsCountJob::getGoodsCountReq()
{
    if (!_acciv->SendGetGoodsCountReq(_tran->Set(this, 146), _owner->_acb._id))
    {
        JOB_LOG(Log::LT_ERROR, 142, L"[job], get goods count req fail; unsent", L"");
        _lgate->SendGetGoodsCountFail(_owner->_clikey, 7);
        transit(FIN);
    }
    else
    {
        JOB_LOG(Log::LT_DEBUG, 148, L"[job], get goods count req ok", L"");
    }
    return true;
}

// 0x51b80
bool GetGoodsCountJob::getGoodsCountOk(void* param)
{
    _acciv->TRecv(_tran);
    int* const count = static_cast<int*>(param);
    if (count == nullptr)
    {
        JOB_LOG(Log::LT_ERROR, 158, L"[job], invalid param on ok ack", L"");
        _lgate->SendGetGoodsCountFail(_owner->_clikey, 2);
        transit(FIN);
    }
    else
    {
        int const n = *count;
        JOB_LOG(Log::LT_DEBUG, 166, L"[job], ok recv", L", count:%d", n);
        _lgate->SendGetGoodsCountOk(_owner->_clikey, n);
        transit(FIN);
    }
    return true;
}

// 0x51d60
bool GetGoodsCountJob::getGoodsCountFail(void* param)
{
    _acciv->TRecv(_tran);
    short* const fail = static_cast<short*>(param);
    if (fail == nullptr)
    {
        JOB_LOG(Log::LT_ERROR, 179, L"[job], invalid param on fail ack", L"");
        _lgate->SendGetGoodsCountFail(_owner->_clikey, 2);
        transit(FIN);
    }
    else
    {
        short const reason = *fail;
        JOB_LOG(Log::LT_DEBUG, 186, L"[job], fail recv", L", reason:%d", reason);
        _lgate->SendGetGoodsCountFail(_owner->_clikey, reason == 3 || reason == 5 ? 7 : 2);
        transit(FIN);
    }
    return true;
}

// 0x51f60
bool GetGoodsCountJob::getGoodsCountTimeout()
{
    JOB_LOG(Log::LT_ERROR, 207, L"[job], timeout", L"");
    _lgate->SendGetGoodsCountFail(_owner->_clikey, 2);
    transit(FIN);
    return true;
}
