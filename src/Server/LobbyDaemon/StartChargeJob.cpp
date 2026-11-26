// StartChargeJob.obj (LobbyDaemon PDB, 2019 + PDB). Lifted from the pseudocode with PDB types.
#include <new>
#include <wchar.h>
#include <winsock2.h>
#include <windows.h>
#include "StartChargeJob.h"
#include "AlertSender.h"
#include "CliSession.h"
#include "GamedChannel.h"
#include "LiftStub.h"
#include "LobbyDaemon.h"
#include "Log.h"
#include "Memory.h"
#include "MemoryManager.h"
#include "NPServiceChannel.h"

namespace StsMsgLib
{
// PDB StsMsgLib::_StsMsgResponseChargeStart (sizeof 0x110).
struct _StsMsgResponseChargeStart : public _StsMsgResponse
{
    GUID UserId;
    char* pszClientNetAddress;
    wchar_t ChargeKey[65];
    unsigned int nRemainPlayTime;
    int eChargeBaseType;  // PDB EChargeBaseType
    unsigned int nItemId;
    unsigned int nReservations;
};
static_assert(sizeof(_StsMsgResponseChargeStart) == 0x110, "sizeof StsMsgLib::_StsMsgResponseChargeStart");
static_assert(offsetof(_StsMsgResponseChargeStart, ChargeKey) == 0x78, "_StsMsgResponseChargeStart::ChargeKey");
static_assert(offsetof(_StsMsgResponseChargeStart, nRemainPlayTime) == 0xFC, "_StsMsgResponseChargeStart::nRemainPlayTime");
static_assert(offsetof(_StsMsgResponseChargeStart, nReservations) == 0x108, "_StsMsgResponseChargeStart::nReservations");
}  // namespace StsMsgLib

static wchar_t const kFile[] = L"StartChargeJob.cpp";

// The log suffix of all LobbyJob logs. The original reads the owner state 2 times (HIWORD and LOWORD).
#define JOB_LOG(logType, line, msg, fmt, ...)                                                                          \
    Log::Write(logType, kFile, line, msg L", tid:0x%I64X, type:%d, state:%d, cli-key:0x%I64X, cli-state:%d.%d" fmt,   \
               this != nullptr ? _id : 0, this != nullptr ? GetDefinition()->type : -1,                            \
               this != nullptr ? _state : -1, this != nullptr && _owner != nullptr ? _owner->_clikey : 0,          \
               HIWORD(this != nullptr && _owner != nullptr ? _owner->_state : 0),                                  \
               LOWORD(this != nullptr && _owner != nullptr ? _owner->_state : 0), ##__VA_ARGS__)

namespace
{
LobbyJobStateDef const StateDef[] = {{0, L"INIT"}, {1, L"START_CHARGE"}, {2, L"FIN"}};  // 0x12dcb0
}

LobbyJobDef StartChargeJob::_def = {16, StateDef, 2, L"StartChargeJob"};  // 0x2019d0
// LIFT: StartChargeJob::_pool (0x204f10: id 1, size 0x70) is defined at the end of this file (gap-26, LobbyObjectPool.cpp).

// 0x75570
LobbyJobDef const* StartChargeJob::GetDefinition() const
{
    return &_def;
}

// 0x75580
// LIFT: Not done. The body calls _pool.Checkin. ObjPool is not in lift_lobbydaemon.
void StartChargeJob::deallocate_me(void*, wchar_t const*, int)
{
    LIFT_STUB(0x75580);
}

// 0x755d0
// The original constructs a job on the stack (null owner) and returns its vfptr. It does not run the destructor.
void* StartChargeJob::_vtbl()
{
    char buf[sizeof(StartChargeJob)];
    StartChargeJob* job = ::new (buf) StartChargeJob(nullptr);
    return *reinterpret_cast<void**>(job);
}

// 0x75650 (scalar deleting destructor)
StartChargeJob::~StartChargeJob()
{
    if (_gamed != nullptr)
        _gamed->removeReferenceCount(kFile, 65);
}

// 0x756a0
bool StartChargeJob::Initialize(GamedChannel* gamed, unsigned long long tid, unsigned long long pcid)
{
    if (gamed == nullptr)
    {
        JOB_LOG(Log::LT_ERROR, 71, L"[job], init fail; invalid parameter", L"");
        return false;
    }
    _gamed = gamed;
    _gametid = tid;
    _pcid = pcid;
    gamed->addReferenceCount(false, kFile, 79);
    return true;
}

// 0x757b0
bool StartChargeJob::work(int task, void* param)
{
    bool result = false;
    if (_state == INIT && task == 120)
    {
        result = init();
        task = 0;
    }
    if (_state == START_CHARGE)
    {
        if (task == 0)
            return requestStartCharge();
        else if (task == 54)
            return responseStartCharge(param);
        else if (task == 55)
            return expireStartCharge();
    }
    return result;
}

// 0x75830
bool StartChargeJob::init()
{
    JOB_LOG(Log::LT_DEBUG, 115, L"[job], init param", L", wid:%d, game-tid:0x%I64X, pcid:0x%I64X",
            _gamed != nullptr ? (_gamed->_rawChannel != nullptr ? static_cast<short>(_gamed->_rawChannel->GetId()) : 0) : 0,
            _gametid, _pcid);
    int next;
    if (_owner->_state != 0x40000)
    {
        JOB_LOG(Log::LT_ERROR, 120, L"[job], cli-session not in game-world", L"");
        _gamed->SendStartChargeFail(_gametid, 6);
        next = FIN;
    }
    else
    {
        JOB_LOG(Log::LT_DEBUG, 126, L"[job], init ok", L"");
        next = START_CHARGE;
    }
    transit(next);
    return true;
}

// 0x75a60
bool StartChargeJob::requestStartCharge()
{
    NPGameServiceChannel* const gs = LobbyDaemon::_instance->_npServchmgr->_gameServChannel;
    NPLobbyJobTransaction* const tr = new (Memory::_Manager[2]->Alloc(sizeof(NPLobbyJobTransaction), kFile, 135))
        NPLobbyJobTransaction;
    short const wid = _gamed->_rawChannel != nullptr ? static_cast<short>(_gamed->_rawChannel->GetId()) : 0;
    // LIFT: the declared 5th parameter (unsigned int) is not set by the original caller. 0 is given here.
    if (!gs->SendRequestChargeStart(tr->Set(this, 55), _owner->_acb._userid, _owner->_ipv4, wid, 0))
    {
        JOB_LOG(Log::LT_ERROR, 144, L"[job], req charge start fail; unsent", L"");
        _gamed->SendStartChargeFail(_gametid, 2);
        // LIFT: the original calls the scalar deleting destructor (flag 1) and then Free. Its operator delete is empty.
        tr->~NPLobbyJobTransaction();
        Memory::_Manager[2]->Free(tr, kFile, 146);
        transit(FIN);
    }
    return true;
}

// 0x75c10
bool StartChargeJob::responseStartCharge(void* param)
{
    if (param == nullptr)
    {
        JOB_LOG(Log::LT_ERROR, 157, L"[job], null param", L"");
        _gamed->SendStartChargeFail(_gametid, 2);
        transit(FIN);
        return true;
    }

    StsMsgLib::_StsMsgResponseChargeStart* const res = static_cast<StsMsgLib::_StsMsgResponseChargeStart*>(param);
    unsigned int const statusCode = res->msgInfo.errInfo.nStatusCode;
    wchar_t const* const reason = res->msgInfo.errInfo.pwszReason;
    if (statusCode == 200 || (statusCode == 400 && _wcsicmp(L"Success", reason != nullptr ? reason : L"null") == 0))
    {
        if (_owner->_state == 0x40000)
        {
            _owner->setChargeKey(res->ChargeKey);
            char const baseType = static_cast<char>((res->eChargeBaseType != 1) + 1);
            if (res->eChargeBaseType != 1)
                _owner->onPcCafeChargeStart();
            _gamed->SendStartChargeOk(_gametid, res->ChargeKey, res->nRemainPlayTime, baseType, res->nItemId,
                                      static_cast<short>(res->nReservations));
            JOB_LOG(Log::LT_DEBUG, 240, L"[job], start charge ok",
                    L", charge-key:%s, item-id:%d, base-type:%d, remain-play-time:%d, reservations:%d", res->ChargeKey,
                    res->nItemId, res->eChargeBaseType, res->nRemainPlayTime, res->nReservations);
        }
        else
        {
            JOB_LOG(Log::LT_ERROR, 207, L"[job], cli-session not in world; force to stop charge",
                    L", charge-key:%s, item-id:%d, base-type:%d, remain-play-time:%d, reservations:%d", res->ChargeKey,
                    res->nItemId, res->eChargeBaseType, res->nRemainPlayTime, res->nReservations);
            NPGameServiceChannel* const gs = LobbyDaemon::_instance->_npServchmgr->_gameServChannel;
            if (gs != nullptr)
                gs->SendRequestChargeStop(nullptr, _owner->_acb._userid, _owner->_ipv4, res->ChargeKey);
            _gamed->SendStartChargeFail(_gametid, 6);
        }
    }
    else
    {
        JOB_LOG(Log::LT_ERROR, 166, L"[job], start charge fail",
                L",np-tid:%u, cmd:%d, type:%d, status-code:%u, reason:%s, error-code:%d", res->GetTransactionId(),
                res->GetCommand(), res->GetMessageType(), res->msgInfo.errInfo.nStatusCode,
                res->msgInfo.errInfo.pwszReason != nullptr ? res->msgInfo.errInfo.pwszReason : L"null",
                res->msgInfo.errInfo.nErrorCode);
        short err = 1;
        switch (res->msgInfo.errInfo.nErrorCode)
        {
        case 0x1004:
            err = 36;
            break;
        case 0x1005:
            err = 37;
            break;
        case 0x1006:
            err = 38;
            break;
        case 0x1007:
            err = 39;
            break;
        case 0x100B:
            err = 40;
            break;
        case 0x100D:
            err = 41;
            break;
        default:
            break;
        }
        _gamed->SendStartChargeFail(_gametid, err);
    }
    transit(FIN);
    return true;
}

// 0x76150
bool StartChargeJob::expireStartCharge()
{
    JOB_LOG(Log::LT_ERROR, 248, L"[job], start charge expired", L"");
    _gamed->SendStartChargeFail(_gametid, 2);
    transit(FIN);
    return true;
}

// LIFT: StartChargeJob::_pool (.data RVA 0x204f10). Dynamic initializer 0x11e2f0, atexit destructor 0x11f040. The original static data
// holds id 1, objsize sizeof(StartChargeJob) and desc L"StartChargeJob".
#include "ObjectPool.h"
ObjPool StartChargeJob::_pool(1, sizeof(StartChargeJob), L"StartChargeJob");
