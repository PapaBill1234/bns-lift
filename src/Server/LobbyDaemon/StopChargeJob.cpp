// StopChargeJob.obj (LobbyDaemon PDB, 2019 + PDB). Lifted from the pseudocode with PDB types.
#include <new>
#include <wchar.h>
#include <winsock2.h>
#include <windows.h>
#include "StopChargeJob.h"
#include "AlertSender.h"
#include "CliSession.h"
#include "GamedChannel.h"
#include "LiftStub.h"
#include "LobbyDaemon.h"
#include "Log.h"
#include "Memory.h"
#include "MemoryManager.h"
#include "NPServiceChannel.h"

static wchar_t const kFile[] = L"StopChargeJob.cpp";

// The log suffix of all LobbyJob logs. The original reads the owner state 2 times (HIWORD and LOWORD).
#define JOB_LOG(logType, line, msg, fmt, ...)                                                                          \
    Log::Write(logType, kFile, line, msg L", tid:0x%I64X, type:%d, state:%d, cli-key:0x%I64X, cli-state:%d.%d" fmt,   \
               this != nullptr ? _id : 0, this != nullptr ? GetDefinition()->type : -1,                            \
               this != nullptr ? _state : -1, this != nullptr && _owner != nullptr ? _owner->_clikey : 0,          \
               HIWORD(this != nullptr && _owner != nullptr ? _owner->_state : 0),                                  \
               LOWORD(this != nullptr && _owner != nullptr ? _owner->_state : 0), ##__VA_ARGS__)

namespace
{
LobbyJobStateDef const StateDef[] = {{0, L"INIT"}, {1, L"STOP_CHARGE"}, {2, L"FIN"}};  // 0x12dc30
}

LobbyJobDef StopChargeJob::_def = {17, StateDef, 2, L"StopChargeJob"};  // 0x201990
// LIFT: StopChargeJob::_pool (0x205070: id 1, size 0xf8) is defined at the end of this file (gap-26, LobbyObjectPool.cpp).

// 0x77c90
LobbyJobDef const* StopChargeJob::GetDefinition() const
{
    return &_def;
}

// 0x77ca0
// LIFT: Not done. The body calls _pool.Checkin. ObjPool is not in lift_lobbydaemon.
void StopChargeJob::deallocate_me(void*, wchar_t const*, int)
{
    LIFT_STUB(0x77ca0);
}

// 0x77cf0
// The original constructs a job on the stack (null owner) and returns its vfptr. It does not run the destructor.
void* StopChargeJob::_vtbl()
{
    char buf[sizeof(StopChargeJob)];
    StopChargeJob* job = ::new (buf) StopChargeJob(nullptr);
    return *reinterpret_cast<void**>(job);
}

// 0x77d70 (scalar deleting destructor)
StopChargeJob::~StopChargeJob()
{
    if (_gamed != nullptr)
        _gamed->removeReferenceCount(kFile, 66);
}

// 0x77dc0
bool StopChargeJob::Initialize(GamedChannel* gamed, unsigned long long tid, unsigned long long pcid, wchar_t* chargeKey)
{
    if (gamed != nullptr && chargeKey != nullptr && wcslen(chargeKey) != 0)
    {
        _gamed = gamed;
        _gametid = tid;
        _pcid = pcid;
        wcscpy_s(_chargeKey, 65, chargeKey);
        _gamed->addReferenceCount(false, kFile, 81);
        return true;
    }
    JOB_LOG(Log::LT_ERROR, 72, L"[job], init fail; invalid parameter",
            L", gamed-channel:%p, tid:0x%I64X, pcid:0x%I64X, charge-key:%s", gamed, tid, pcid,
            chargeKey != nullptr ? chargeKey : L"");
    return false;
}

// 0x77f50
bool StopChargeJob::work(int task, void* param)
{
    bool result = false;
    if (_state == INIT && task == 121)
    {
        result = init();
        task = 0;
    }
    if (_state == STOP_CHARGE)
    {
        if (task == 0)
            return requestChargeStop();
        else if (task == 56)
            return responseChargeStop(param);
        else if (task == 57)
            return expireChargeStop();
    }
    return result;
}

// 0x77fd0
bool StopChargeJob::init()
{
    JOB_LOG(Log::LT_DEBUG, 119, L"[job], init param", L", wid:%d, game-tid:0x%I64X, pcid:0x%I64X, charge-key:%s",
            _gamed != nullptr ? (_gamed->_rawChannel != nullptr ? static_cast<short>(_gamed->_rawChannel->GetId()) : 0) : 0,
            _gametid, _pcid, _chargeKey);
    int next;
    wchar_t* const chargeKey = _owner->_chargeKey;
    if (chargeKey == nullptr)
    {
        JOB_LOG(Log::LT_ERROR, 123, L"[job], cli-session not charged", L"");
        _gamed->SendStopChargeFail(_gametid, 42);
        next = FIN;
    }
    else
    {
        if (wcscmp(chargeKey, _chargeKey) != 0)
        {
            JOB_LOG(Log::LT_DEBUG, 130, L"[job], charge-key changed", L", owner:%s, requested:%s", chargeKey, _chargeKey);
            wcscpy_s(_chargeKey, 65, chargeKey);
        }
        _owner->setChargeKey(nullptr);
        if (_owner->_pcCafeCharged)
            _owner->onPcCafeChargeStop();
        next = STOP_CHARGE;
    }
    transit(next);
    return true;
}

// 0x78290
bool StopChargeJob::requestChargeStop()
{
    NPGameServiceChannel* const gs = LobbyDaemon::_instance->_npServchmgr->_gameServChannel;
    NPLobbyJobTransaction* const tr = new (Memory::_Manager[2]->Alloc(sizeof(NPLobbyJobTransaction), kFile, 148))
        NPLobbyJobTransaction;
    if (!gs->SendRequestChargeStop(tr->Set(this, 57), _owner->_acb._userid, _owner->_ipv4, _chargeKey))
    {
        JOB_LOG(Log::LT_ERROR, 155, L"[job], req charge stop fail; unsent", L"");
        _gamed->SendStopChargeFail(_gametid, 2);
        // LIFT: the original calls the scalar deleting destructor (flag 1) and then Free. Its operator delete is empty.
        tr->~NPLobbyJobTransaction();
        Memory::_Manager[2]->Free(tr, kFile, 157);
        transit(FIN);
    }
    return true;
}

// 0x78430
bool StopChargeJob::responseChargeStop(void* param)
{
    if (param == nullptr)
    {
        JOB_LOG(Log::LT_ERROR, 168, L"[job], null param", L"");
        _gamed->SendStopChargeFail(_gametid, 2);
        transit(FIN);
        return true;
    }

    StsMsgLib::_StsMsgResponse* const res = static_cast<StsMsgLib::_StsMsgResponse*>(param);
    unsigned int const statusCode = res->msgInfo.errInfo.nStatusCode;
    wchar_t const* const reason = res->msgInfo.errInfo.pwszReason;
    if (statusCode == 200 || (statusCode == 400 && _wcsicmp(L"Success", reason != nullptr ? reason : L"null") == 0))
    {
        _owner->completeRequestChargeStop(true);
        _gamed->SendStopChargeOk(_gametid);
        JOB_LOG(Log::LT_DEBUG, 206, L"[job], stop charge ok", L"");
    }
    else
    {
        JOB_LOG(Log::LT_ERROR, 177, L"[job], stop charge fail",
                L",np-tid:%u, cmd:%d, type:%d, status-code:%u, reason:%s, error-code:%d", res->GetTransactionId(),
                res->GetCommand(), res->GetMessageType(), res->msgInfo.errInfo.nStatusCode,
                res->msgInfo.errInfo.pwszReason != nullptr ? res->msgInfo.errInfo.pwszReason : L"null",
                res->msgInfo.errInfo.nErrorCode);
        _owner->completeRequestChargeStop(false);
        short err = 1;
        if (res->msgInfo.errInfo.nErrorCode == 4100)
            err = 43;
        else if (res->msgInfo.errInfo.nErrorCode == 4104)
            err = 44;
        _gamed->SendStopChargeFail(_gametid, err);
    }
    transit(FIN);
    return true;
}

// 0x78790
bool StopChargeJob::expireChargeStop()
{
    JOB_LOG(Log::LT_ERROR, 214, L"[job], stop charge expired", L"");
    _owner->completeRequestChargeStop(false);
    _gamed->SendStopChargeFail(_gametid, 2);
    transit(FIN);
    return true;
}

// LIFT: StopChargeJob::_pool (.data RVA 0x205070). Dynamic initializer 0x11e390, atexit destructor 0x11f0c0. The original static data
// holds id 1, objsize sizeof(StopChargeJob) and desc L"StopChargeJob".
#include "ObjectPool.h"
ObjPool StopChargeJob::_pool(1, sizeof(StopChargeJob), L"StopChargeJob");
