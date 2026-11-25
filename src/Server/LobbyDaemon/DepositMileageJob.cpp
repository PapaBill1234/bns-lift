// DepositMileageJob.obj (LobbyDaemon PDB, 2019 + PDB). Lifted from the pseudocode with PDB types.
#include <new>
#include <stdio.h>
#include <string.h>
#include <wchar.h>
#include <winsock2.h>
#include <windows.h>
#include "DepositMileageJob.h"
#include "AlertSender.h"
#include "BnsCommonConfigDefinition.h"
#include "LiftStub.h"
#include "LobbyDaemon.h"
#include "Log.h"
#include "Memory.h"
#include "MemoryManager.h"
#include "NPServiceChannel.h"

static wchar_t const kFile[] = L"DepositMileageJob.cpp";

// LIFT: PDB StsMsgLib::_StsMsgRequestVirtualCurrencyDeposit (sizeof 0x68), _StsMsgResponseVirtualCurrencyDeposit
// (sizeof 0x70) and _StsMsgRequestPresenceMessage (sizeof 0x38). The types are not in a LobbyDaemon header yet.
namespace StsMsgLib
{
struct _StsMsgRequestVirtualCurrencyDeposit : public _StsMsgRequest
{
    _GUID* pUserId;
    int nCurrencyId;
    long long nAmount;
    char* pszRequestId;
    int nRequestCode;
    long long tEffectiveTo;
    int nIsRefundable;
    int nDepositReasonCode;
    char* pszDepositReason;
    char* pszClientNetAddress;
    wchar_t* pwszAdditionalInfo;
};
static_assert(sizeof(_StsMsgRequestVirtualCurrencyDeposit) == 0x68, "sizeof _StsMsgRequestVirtualCurrencyDeposit");
static_assert(offsetof(_StsMsgRequestVirtualCurrencyDeposit, pUserId) == 0x18, "_StsMsgRequestVirtualCurrencyDeposit::pUserId");
static_assert(offsetof(_StsMsgRequestVirtualCurrencyDeposit, nIsRefundable) == 0x48, "_StsMsgRequestVirtualCurrencyDeposit::nIsRefundable");
static_assert(offsetof(_StsMsgRequestVirtualCurrencyDeposit, pwszAdditionalInfo) == 0x60, "_StsMsgRequestVirtualCurrencyDeposit::pwszAdditionalInfo");

struct _StsMsgResponseVirtualCurrencyDeposit : public _StsMsgResponse
{
    unsigned long long nDepositId;
    int nBalance;
};
static_assert(sizeof(_StsMsgResponseVirtualCurrencyDeposit) == 0x70, "sizeof _StsMsgResponseVirtualCurrencyDeposit");
static_assert(offsetof(_StsMsgResponseVirtualCurrencyDeposit, nDepositId) == 0x60, "_StsMsgResponseVirtualCurrencyDeposit::nDepositId");

struct _StsMsgRequestPresenceMessage : public _StsMsgRequest
{
    _GUID* pUserId;
    _GUID* pAppId;
    wchar_t const* pwszMessageName;
    wchar_t const* pwszContent;
};
static_assert(sizeof(_StsMsgRequestPresenceMessage) == 0x38, "sizeof _StsMsgRequestPresenceMessage");
static_assert(offsetof(_StsMsgRequestPresenceMessage, pwszContent) == 0x30, "_StsMsgRequestPresenceMessage::pwszContent");
}  // namespace StsMsgLib

// PDB inline method (no RVA). The body comes from the inlined code in depositAck (0x4aa40): no null check of t.
inline bool NPGameServiceChannel::SendRequestPresenceMessage(NPTransaction* t, id128 const& userId, id128 const& appId,
                                                             wchar_t const* messageName, wchar_t const* content)
{
    StsMsgLib::_StsMsgRequestPresenceMessage msg;
    msg.msgInfo.eCmd = StsMsgLib::COMMAND_SRV_PRES_MESSAGE;
    msg.msgInfo.msgType = StsMsgLib::MESSAGE_TYPE_REQUEST;
    msg.msgInfo.nTxnId = 0;
    msg.pUserId = reinterpret_cast<_GUID*>(const_cast<id128*>(&userId));
    msg.pAppId = reinterpret_cast<_GUID*>(const_cast<id128*>(&appId));
    msg.pwszMessageName = messageName;
    msg.pwszContent = content;
    return SendMsg(&msg, true, t);
}

// PDB inline method (no RVA). The body comes from the inlined code in depositReq (0x4a3e0). The original zeroes a
// 32-byte stack buffer and sends a null pszClientNetAddress when clientNetAddr is 0.
// LIFT: ❓ the code for a clientNetAddr other than 0 is not in the binary (all callers give 0). The inet_ntoa copy
// follows SendRequestPresenceLogin (0xd0650).
inline bool NPGameServiceChannel::SendRequestVirtualCurrencyDeposit(NPTransaction* t, id128 const& userId, short currencyId,
                                                                    long long amount, char* requestId, int requestCode,
                                                                    long long effectiveTo, bool refundable,
                                                                    int depositReasonCode, char* depositReason,
                                                                    unsigned long clientNetAddr, wchar_t* additionalInfo)
{
    char clientNetAddrA[32] = {0};
    if (clientNetAddr != 0)
    {
        in_addr addr;
        addr.s_addr = clientNetAddr;
        char const* const s = inet_ntoa(addr);
        if (s != nullptr)
            strcpy_s(clientNetAddrA, sizeof(clientNetAddrA), s);
    }
    StsMsgLib::_StsMsgRequestVirtualCurrencyDeposit msg;
    msg.msgInfo.eCmd = StsMsgLib::COMMAND_SRV_VIRTUALCURRENCY_DEPOSIT;
    msg.msgInfo.msgType = StsMsgLib::MESSAGE_TYPE_REQUEST;
    msg.msgInfo.nTxnId = 0;
    msg.pUserId = reinterpret_cast<_GUID*>(const_cast<id128*>(&userId));
    msg.nCurrencyId = currencyId;
    msg.nAmount = amount;
    msg.pszRequestId = requestId;
    msg.nRequestCode = requestCode;
    msg.tEffectiveTo = effectiveTo;
    msg.nIsRefundable = refundable ? 1 : 0;
    msg.nDepositReasonCode = depositReasonCode;
    msg.pszDepositReason = depositReason;
    msg.pszClientNetAddress = clientNetAddr != 0 ? clientNetAddrA : nullptr;
    msg.pwszAdditionalInfo = additionalInfo;
    return SendMsg(&msg, true, t);
}

// The log suffix of the DepositMileageJob logs (LobbyJob base, no owner).
#define JOB_LOG(logType, line, msg, fmt, ...)                                                                          \
    Log::Write(logType, kFile, line, msg L", tid:0x%I64X, type:%d, state:%d" fmt, this != nullptr ? _id : 0,          \
               this != nullptr ? GetDefinition()->type : -1, this != nullptr ? _state : -1, ##__VA_ARGS__)

#define JOB_ALERT(line, msg, fmt, ...)                                                                                 \
    AlertSender::Write(kFile, line, msg L", tid:0x%I64X, type:%d, state:%d" fmt, this != nullptr ? _id : 0,           \
                       this != nullptr ? GetDefinition()->type : -1, this != nullptr ? _state : -1, ##__VA_ARGS__)

// The user-id format of the init logs.
#define USER_ID_FMT L"%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X"
#define USER_ID_ARGS(u)                                                                                                \
    (u).guid.id1, (u).guid.id2, (u).guid.id3, (u).guid.id4[0], (u).guid.id4[1], (u).guid.id4[2], (u).guid.id4[3],      \
        (u).guid.id4[4], (u).guid.id4[5], (u).guid.id4[6], (u).guid.id4[7]

namespace
{
LobbyJobStateDef const StateDef[] = {{0, L"INIT"}, {1, L"DEPOSIT"}, {2, L"FIN"}};  // 0x12dff0
}

LobbyJobDef DepositMileageJob::_def = {38, StateDef, 2, L"DepositMileageJob"};  // 0x201d10
// LIFT: DepositMileageJob::_pool (0x2044c0) has no definition. The LobbyDaemon ObjectPool module is not in
// lift_lobbydaemon (see CliSession.cpp).

// 0x49b40
LobbyJobDef const* DepositMileageJob::GetDefinition() const
{
    return &_def;
}

// 0x49b50
// LIFT: Not done. The body calls _pool.Checkin. ObjPool is not in lift_lobbydaemon.
void DepositMileageJob::deallocate_me(void*, wchar_t const*, int)
{
    LIFT_STUB(0x49b50);
}

// 0x49ba0
DepositMileageJob::DepositMileageJob(Callback* callback)
    : _requestLocation(0), _requestType(0), _requestId(0), _userId(ID128_GUID_ZERO), _virtualCurrencyId(0), _virtualCurrencyAmount(0),
      _virtualCurrencyExpireTime(0), _requestCode(0), _depositReasonCode(0), _refundable(false), _notification(false),
      _pcDbId(0), _requestSubId(0), _locationHint(0), _pcRace(0), _pcSex(0), _pcJob(0), _callback(callback)
{
    _depositReason[0] = 0;
    _notificationName[0] = 0;
    _notificationContent[0] = 0;
}

// 0x49c90 (scalar deleting destructor 0x49c70)
DepositMileageJob::~DepositMileageJob()
{
    if (_callback != nullptr)
    {
        _callback->~Callback();
        Memory::_Manager[2]->Free(_callback, kFile, 120);
        _callback = nullptr;
    }
}

// 0x49d20
bool DepositMileageJob::work(int task, void* param)
{
    bool result = false;
    if (_state == INIT && task == 5)
    {
        result = init(param);
        task = 0;
    }
    if (_state == DEPOSIT)
    {
        if (task == 0)
            return depositReq();
        else if (task == 91)
            return depositAck(param);
        else if (task == 92)
            return depositExpire();
    }
    return result;
}

// 0x49da0
bool DepositMileageJob::init(void* param)
{
    DepositMileageReqParam* const p = static_cast<DepositMileageReqParam*>(param);
    if (p == nullptr)
    {
        JOB_LOG(Log::LT_ERROR, 165, L"[job], init fail; null parameter", L"");
        return false;
    }
    _depositType = p->depositType;
    _requestLocation = p->requestLocation;
    _requestType = p->requestType;
    _requestId = p->requestId;
    _userId = p->userId;
    _virtualCurrencyId = p->virtualCurrencyId;
    _virtualCurrencyAmount = p->virtualCurrencyAmount;
    _virtualCurrencyExpireTime = p->virtualCurrencyExpireTime;
    _requestCode = p->requestCode;
    _depositReasonCode = p->depositReasonCode;
    strcpy_s(_depositReason, 201, p->depositReason);
    _refundable = p->refundable;
    _notification = p->notification;
    wcscpy_s(_notificationName, 65, p->notificationName);
    wcscpy_s(_notificationContent, 513, p->notificationContent);
    _pcDbId = p->pcDbId;
    _requestSubId = p->requestSubId;
    _locationHint = p->locationHint;
    _pcRace = p->pcRace;
    _pcSex = p->pcSex;
    _pcJob = p->pcJob;
    // The original compares _userId with the ID128_GUID_ZERO global (0x14012d880).
    if (_requestLocation < 0 || _requestLocation > 9 || _requestType < 0 || _requestType > 19 || _requestId == 0 ||
        (_userId.id[0] == ID128_GUID_ZERO.id[0] && _userId.id[1] == ID128_GUID_ZERO.id[1]) || _virtualCurrencyId <= 0 ||
        _virtualCurrencyAmount <= 0 || _virtualCurrencyExpireTime <= 0)
    {
        JOB_LOG(Log::LT_ERROR, 201, L"[job], init fail; invalid parameter",
                L", user-id:" USER_ID_FMT L", deposit-type:%d, req-loc:%d, req-type:%d, request-id:%d, vc-id:%d, "
                L"vc-amout:%I64d, vc-expire-time:%I64d, request-code:%d, deposit-reason-code:%d, notify:%s",
                USER_ID_ARGS(_userId), _depositType, _requestLocation, _requestType, _requestId, _virtualCurrencyId,
                _virtualCurrencyAmount, _virtualCurrencyExpireTime, _requestCode, _depositReasonCode,
                _notification ? L"yes" : L"no");
        if (_callback != nullptr)
        {
            CallbackParam makeCallbackParam;
            _callback->OnError(makeCallbackParam(p));
        }
        return false;
    }
    JOB_LOG(Log::LT_DEBUG, 209, L"[job], init ok",
            L", user-id:" USER_ID_FMT L", deposit-type:%d, req-loc:%d, req-type:%d, request-id:%d, vc-id:%d, "
            L"vc-amout:%I64d, vc-expire-time:%I64d, request-code:%d, deposit-reason-code:%d, notify:%s",
            USER_ID_ARGS(_userId), _depositType, _requestLocation, _requestType, _requestId, _virtualCurrencyId,
            _virtualCurrencyAmount, _virtualCurrencyExpireTime, _requestCode, _depositReasonCode,
            _notification ? L"yes" : L"no");
    transit(DEPOSIT);
    return true;
}

// 0x4a3e0
bool DepositMileageJob::depositReq()
{
    char requestIdStr[51];
    switch (_depositType)
    {
    case 0:
        if (_requestLocation == 0)
        {
            if (_snprintf_s(requestIdStr, 51, _TRUNCATE, "%I64u", _requestId) < 0)
            {
                JOB_LOG(Log::LT_ERROR, 228, L"== CRASH == [job], req fail; make id fail",
                        L", req-loc:%d, req-type:%d, request-id:%I64u", _requestLocation, _requestType, _requestId);
                JOB_ALERT(228, L"== CRASH == [job], req fail; make id fail",
                          L", req-loc:%d, req-type:%d, request-id:%I64u", _requestLocation, _requestType, _requestId);
                if (_callback != nullptr)
                {
                    CallbackParam makeCallbackParam;
                    _callback->OnError(makeCallbackParam(this));
                }
                return false;
            }
        }
        else
        {
            if (_snprintf_s(requestIdStr, 51, _TRUNCATE, "%d%.2d+%I64u", _requestLocation, _requestType, _requestId) < 0)
            {
                JOB_LOG(Log::LT_ERROR, 246, L"== CRASH == [job], req fail; make id fail",
                        L", req-loc:%d, req-type:%d, request-id:%I64u", _requestLocation, _requestType, _requestId);
                JOB_ALERT(246, L"== CRASH == [job], req fail; make id fail",
                          L", req-loc:%d, req-type:%d, request-id:%I64u", _requestLocation, _requestType, _requestId);
                if (_callback != nullptr)
                {
                    CallbackParam makeCallbackParam;
                    _callback->OnError(makeCallbackParam(this));
                }
                return false;
            }
        }
        break;
    case 1:
        if (_snprintf_s(requestIdStr, 51, _TRUNCATE, "%d%.2d+%I64u+%d+%d+%d+%I64u_%I64u", _requestLocation, _requestType,
                        _pcDbId, _pcSex, _pcJob, _pcRace, _requestId, _requestSubId) < 0)
        {
            JOB_LOG(Log::LT_ERROR, 272, L"== CRASH == [job], req fail; make id fail",
                    L", req-loc:%d, req-type:%d, pcdbid:0x%I64x, request-id:%I64u, request-sub-id:%I64u", _requestLocation,
                    _requestType, _pcDbId, _requestId, _requestSubId);
            JOB_ALERT(272, L"== CRASH == [job], req fail; make id fail",
                      L", req-loc:%d, req-type:%d, pcdbid:0x%I64x, request-id:%I64u, request-sub-id:%I64u", _requestLocation,
                      _requestType, _pcDbId, _requestId, _requestSubId);
            if (_callback != nullptr)
            {
                CallbackParam makeCallbackParam;
                _callback->OnError(makeCallbackParam(this));
            }
            return false;
        }
        break;
    }

    // LIFT: the original does not check gameServChannel for null here.
    NPGameServiceChannel* const gameServChannel = LobbyDaemon::_instance->_npServchmgr->_gameServChannel;
    NPLobbyJobTransaction* const tran =
        new (Memory::_Manager[2]->Alloc(sizeof(NPLobbyJobTransaction), kFile, 285)) NPLobbyJobTransaction;
    if (!gameServChannel->SendRequestVirtualCurrencyDeposit(tran->Set(this, 92), _userId, _virtualCurrencyId,
                                                            _virtualCurrencyAmount, requestIdStr, _requestCode,
                                                            _virtualCurrencyExpireTime, _refundable, _depositReasonCode,
                                                            _depositReason, 0, nullptr))
    {
        JOB_LOG(Log::LT_ERROR, 299, L"[job], req deposit fail; unsent", L"");
        if (_callback != nullptr)
        {
            CallbackParam makeCallbackParam;
            _callback->OnError(makeCallbackParam(this));
        }
        tran->~NPLobbyJobTransaction();
        Memory::_Manager[2]->Free(tran, kFile, 304);
        return false;
    }
    JOB_LOG(Log::LT_DEBUG, 308, L"[job], req deposit ok", L"");
    return true;
}

// 0x4aa40
bool DepositMileageJob::depositAck(void* param)
{
    StsMsgLib::_StsMsgResponseVirtualCurrencyDeposit* const res =
        static_cast<StsMsgLib::_StsMsgResponseVirtualCurrencyDeposit*>(param);
    CallbackParam makeCallbackParam;
    if (res == nullptr)
    {
        JOB_LOG(Log::LT_ERROR, 317, L"[job], null param", L"");
        if (_callback != nullptr)
            _callback->OnError(makeCallbackParam(this));
        return false;
    }
    int errorCode = 0;
    if (res->msgInfo.errInfo.nStatusCode == 200 ||
        (res->msgInfo.errInfo.nStatusCode == 400 &&
         _wcsicmp(L"Success", res->msgInfo.errInfo.pwszReason != nullptr ? res->msgInfo.errInfo.pwszReason : L"null") == 0))
    {
        JOB_LOG(Log::LT_DEBUG, 353, L"[job], deposit ok",
                L", req-loc:%d, req-type:%d, request-id:%I64d, deposit-id:%I64u, balance:%d", _requestLocation, _requestType,
                _requestId, res->nDepositId, res->nBalance);
        if (_notification)
        {
            NPGameServiceChannel* const gameServChannel = LobbyDaemon::_instance->_npServchmgr->_gameServChannel;
            if (gameServChannel != nullptr)
                gameServChannel->SendRequestPresenceMessage(nullptr, _userId, BnsCommonConfig::Config->_npClientAppId,
                                                            _notificationName, _notificationContent);
        }
    }
    else
    {
        JOB_LOG(Log::LT_ERROR, 327, L"[job], deposit failed",
                L",np-tid:%u, cmd:%d, type:%d, status-code:%u, reason:%s, error-code:%d", res->GetTransactionId(),
                res->GetCommand(), res->GetMessageType(), res->msgInfo.errInfo.nStatusCode,
                res->msgInfo.errInfo.pwszReason != nullptr ? res->msgInfo.errInfo.pwszReason : L"null",
                res->msgInfo.errInfo.nErrorCode);
        errorCode = res->msgInfo.errInfo.nErrorCode;
        if (errorCode == 42)
        {
            if (_callback != nullptr)
                _callback->OnTimeout(makeCallbackParam(this));
            transit(FIN);
            return true;
        }
        if (errorCode != 4901)
        {
            if (_callback != nullptr)
                _callback->OnFail(makeCallbackParam(this), errorCode);
            transit(FIN);
            return true;
        }
    }
    if (_callback != nullptr)
        _callback->OnSuccess(makeCallbackParam(this), res->nDepositId, errorCode);
    transit(FIN);
    return true;
}

// 0x4aee0
bool DepositMileageJob::depositExpire()
{
    JOB_LOG(Log::LT_ERROR, 376, L"[job], deposit expired", L"");
    if (_callback != nullptr)
    {
        CallbackParam makeCallbackParam;
        _callback->OnTimeout(makeCallbackParam(this));
    }
    transit(FIN);
    return true;
}
