// TryEnterGameWorldJob.obj (LobbyDaemon PDB, 2019 + PDB). Lifted from the pseudocode with PDB types.
// gap-25 (part 1): the job frame, init, restore, second password, get slot and the charge-info request.
// LIFT: part 2 (responseChargeGetInfo, expireChargeGetInfo, tryEnterGameWorld, issueGameWorldToken) is still LIFT_STUB.
#include <new>
#include <wchar.h>
#include <winsock2.h>
#include <windows.h>
#include "TryEnterGameWorldJob.h"
#include "Character.h"
#include "CliSession.h"
#include "ContentsRuleConfigDefinition.h"
#include "GamedChannel.h"
#include "LiftStub.h"
#include "LobbyConfig.h"
#include "LobbyDaemon.h"
#include "LobbyGateChannel.h"
#include "LobbyService.h"
#include "Log.h"
#include "Memory.h"
#include "MemoryManager.h"
#include "NPServiceChannel.h"
#include "ObjectPool.h"
#include "TransactionChannel.h"

static wchar_t const kFile[] = L"TryEnterGameWorldJob.cpp";

// The log suffix of all LobbyJob logs. The original reads the owner state 2 times (HIWORD and LOWORD).
#define JOB_LOG(logType, line, msg, fmt, ...)                                                                          \
    Log::Write(logType, kFile, line, msg L", tid:0x%I64X, type:%d, state:%d, cli-key:0x%I64X, cli-state:%d.%d" fmt,   \
               this != nullptr ? _id : 0, this != nullptr ? GetDefinition()->type : -1,                            \
               this != nullptr ? _state : -1, this != nullptr && _owner != nullptr ? _owner->_clikey : 0,          \
               HIWORD(this != nullptr && _owner != nullptr ? _owner->_state : 0),                                  \
               LOWORD(this != nullptr && _owner != nullptr ? _owner->_state : 0), ##__VA_ARGS__)

// The slot id in the logs (guid form).
#define SLOTID_FMT L"%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X"
#define SLOTID_ARGS(s)                                                                                               \
    (s).guid.id1, (s).guid.id2, (s).guid.id3, (s).guid.id4[0], (s).guid.id4[1], (s).guid.id4[2], (s).guid.id4[3],    \
        (s).guid.id4[4], (s).guid.id4[5], (s).guid.id4[6], (s).guid.id4[7]
#define GUID_ARGS(g)                                                                                                 \
    (g).Data1, (g).Data2, (g).Data3, (g).Data4[0], (g).Data4[1], (g).Data4[2], (g).Data4[3], (g).Data4[4],           \
        (g).Data4[5], (g).Data4[6], (g).Data4[7]

// The gate world id in the logs. A null lobby-gate gives 0.
#define GATE_WID(lg) ((lg) != nullptr ? (lg)->GetWid() : 0)

// The NP error info suffix of the NP response logs.
#define NP_RES_FMT L", np-tid:%u, cmd:%d, type:%d, status-code:%u, reason:%s, error-code:%d"
#define NP_RES_ARGS(r)                                                                                               \
    (r)->GetTransactionId(), (r)->GetCommand(), (r)->GetMessageType(), (r)->msgInfo.errInfo.nStatusCode,             \
        (r)->msgInfo.errInfo.pwszReason != nullptr ? (r)->msgInfo.errInfo.pwszReason : L"null",                      \
        (r)->msgInfo.errInfo.nErrorCode

// The NP success test: status 200, or status 400 with the reason "Success".
#define NP_RES_OK(r)                                                                                                 \
    ((r)->msgInfo.errInfo.nStatusCode == 200 ||                                                                      \
     ((r)->msgInfo.errInfo.nStatusCode == 400 &&                                                                     \
      _wcsicmp(L"Success", (r)->msgInfo.errInfo.pwszReason != nullptr ? (r)->msgInfo.errInfo.pwszReason : L"null") == 0))

// PDB enum CliSession state: CSS_LOBBY = 0x20000. 0x30001 is the state of the enter-world try (init sets it).
static int const kCssLobby = 0x20000;
static int const kCssTryEnterWorld = 0x30001;

namespace StsMsgLib
{
// PDB StsMsgLib::_StsMsgRequestSecondPasswordGetStatus (sizeof 0x28).
struct _StsMsgRequestSecondPasswordGetStatus : public _StsMsgRequest
{
    _GUID* pUserId;
    int nType;
};
static_assert(sizeof(_StsMsgRequestSecondPasswordGetStatus) == 0x28, "sizeof StsMsgLib::_StsMsgRequestSecondPasswordGetStatus");
static_assert(offsetof(_StsMsgRequestSecondPasswordGetStatus, pUserId) == 0x18, "_StsMsgRequestSecondPasswordGetStatus::pUserId");
static_assert(offsetof(_StsMsgRequestSecondPasswordGetStatus, nType) == 0x20, "_StsMsgRequestSecondPasswordGetStatus::nType");

// PDB StsMsgLib::_StsMsgRequestSecondPasswordIsVerified (sizeof 0x28).
struct _StsMsgRequestSecondPasswordIsVerified : public _StsMsgRequest
{
    _GUID* pUserId;
    int nType;
    unsigned int nActionIndex;
};
static_assert(sizeof(_StsMsgRequestSecondPasswordIsVerified) == 0x28, "sizeof StsMsgLib::_StsMsgRequestSecondPasswordIsVerified");
static_assert(offsetof(_StsMsgRequestSecondPasswordIsVerified, pUserId) == 0x18, "_StsMsgRequestSecondPasswordIsVerified::pUserId");
static_assert(offsetof(_StsMsgRequestSecondPasswordIsVerified, nType) == 0x20, "_StsMsgRequestSecondPasswordIsVerified::nType");
static_assert(offsetof(_StsMsgRequestSecondPasswordIsVerified, nActionIndex) == 0x24, "_StsMsgRequestSecondPasswordIsVerified::nActionIndex");

// PDB StsMsgLib::_StsMsgResponseSecondPasswordGetStatus (sizeof 0x88).
struct _StsMsgResponseSecondPasswordGetStatus : public _StsMsgResponse
{
    enum EBlockStatus : int
    {
        EBLOCKSTATUS_NOT_BLOCKED = 0x0,
        EBLOCKSTATUS_BLOCKED = 0x1,
    };
    EBlockStatus eBlockStatus;
    unsigned int nAuthFailLimitCount;
    unsigned int nAuthFailCount;
    long long tBlockedUntil;
    long long tDeleteAt;
    unsigned long long nActionMask;
};
static_assert(sizeof(_StsMsgResponseSecondPasswordGetStatus) == 0x88, "sizeof StsMsgLib::_StsMsgResponseSecondPasswordGetStatus");
static_assert(offsetof(_StsMsgResponseSecondPasswordGetStatus, eBlockStatus) == 0x60, "_StsMsgResponseSecondPasswordGetStatus::eBlockStatus");
static_assert(offsetof(_StsMsgResponseSecondPasswordGetStatus, tBlockedUntil) == 0x70, "_StsMsgResponseSecondPasswordGetStatus::tBlockedUntil");
static_assert(offsetof(_StsMsgResponseSecondPasswordGetStatus, nActionMask) == 0x80, "_StsMsgResponseSecondPasswordGetStatus::nActionMask");

// PDB StsMsgLib::_StsMsgResponseSecondPasswordIsVerified (sizeof 0x60). It has no own members.
struct _StsMsgResponseSecondPasswordIsVerified : public _StsMsgResponse
{
};
static_assert(sizeof(_StsMsgResponseSecondPasswordIsVerified) == 0x60, "sizeof StsMsgLib::_StsMsgResponseSecondPasswordIsVerified");

// PDB StsMsgLib::_StsMsgResponseSlotGetSlot (sizeof 0xa0).
struct _StsMsgResponseSlotGetSlot : public _StsMsgResponse
{
    struct _SlotData
    {
        long long serviceId;
    };

    GUID guidSlotId;
    wchar_t* pwszSlotType;
    bool bSystemSlot;
    _SlotData slotData;
    wchar_t* pwszSlotData;
    long long tChanged;
    long long tRegistered;
};
static_assert(sizeof(_StsMsgResponseSlotGetSlot) == 0xA0, "sizeof StsMsgLib::_StsMsgResponseSlotGetSlot");
static_assert(offsetof(_StsMsgResponseSlotGetSlot, guidSlotId) == 0x60, "_StsMsgResponseSlotGetSlot::guidSlotId");
static_assert(offsetof(_StsMsgResponseSlotGetSlot, pwszSlotType) == 0x70, "_StsMsgResponseSlotGetSlot::pwszSlotType");
}  // namespace StsMsgLib

namespace
{
LobbyJobStateDef const StateDef[] = {{0, L"INIT"},
                                     {1, L"RESTORE_PC"},
                                     {2, L"CHECK_SECOND_PASSWORD_STATUS"},
                                     {3, L"CHECK_SECOND_PASSWORD_VERIFIED"},
                                     {4, L"GET_SLOT"},
                                     {5, L"GET_CHARGE_INFO"},
                                     {6, L"TRY_ENTER_GAME_WORLD"},
                                     {7, L"ISSUE_GAME_WORLD_TOKEN"},
                                     {8, L"FIN"}};  // 0x12db40
}

LobbyJobDef TryEnterGameWorldJob::_def = {8, StateDef, 8, L"TryEnterGameWorldJob"};  // 0x201930
ObjPool TryEnterGameWorldJob::_pool(1, sizeof(TryEnterGameWorldJob), L"TryEnterGameWorldJob");  // 0x205280

// 0x7b840
LobbyJobDef const* TryEnterGameWorldJob::GetDefinition() const
{
    return &_def;
}

// 0x7b850
void TryEnterGameWorldJob::deallocate_me(void* ptr, wchar_t const* file, int line)
{
    this->~TryEnterGameWorldJob();
    _pool.Checkin(ptr, file, line);
}

// 0x7b8a0
// The original constructs a job on the stack (null owner) and returns its vfptr. It does not run the destructor.
void* TryEnterGameWorldJob::_vtbl()
{
    char buf[sizeof(TryEnterGameWorldJob)];
    TryEnterGameWorldJob* job = ::new (buf) TryEnterGameWorldJob(nullptr);
    return *reinterpret_cast<void**>(job);
}

// 0x7b920
TryEnterGameWorldJob::TryEnterGameWorldJob(CliSession* owner)
    : CliSessionJob(owner), _tran(nullptr), _lgate(nullptr), _gamed(nullptr), _pcid(0), _belongingWorld(0),
      _chargeApplyType(CHARGEAPPLYTYPE_INVALID)
{
    _slotid.id[0] = 0;
    _slotid.id[1] = 0;
}

// 0x7b9a0
TryEnterGameWorldJob::~TryEnterGameWorldJob()
{
    if (_tran != nullptr)
    {
        _tran->removeReferenceCount(kFile, 96);
        _tran = nullptr;
    }
    if (_lgate != nullptr)
    {
        _lgate->removeReferenceCount(kFile, 100);
        _lgate = nullptr;
    }
    if (_gamed != nullptr)
    {
        _gamed->removeReferenceCount(kFile, 104);
        _gamed = nullptr;
    }
}

// 0x7ba40
bool TryEnterGameWorldJob::Initialize(LobbyGateChannel* lgate, id128 const& slotid)
{
    if (lgate != nullptr && (slotid.id[0] != 0 || slotid.id[1] != 0))
    {
        _lgate = lgate;
        _slotid = slotid;
        lgate->addReferenceCount(false, kFile, 119);
        return true;
    }
    JOB_LOG(Log::LT_ERROR, 112, L"[job], invalid parameter", L"");
    return false;
}

// 0x7bb70
// Tasks: 13 TASK_TRY_ENTER_GAME_WORLD; 111/112/113 restore ok/fail/expire; 62/63 second-password status
// response/expire; 64/65 second-password verified response/expire; 37/38 get slot response/expire; 52/53 charge info
// response/expire. After a handler, the task is 0. Then the next state can run in the same call.
bool TryEnterGameWorldJob::work(int task, void* param)
{
    bool result = false;
    if (_state == INIT && task == 13)
    {
        result = init();
        task = 0;
    }
    if (_state == RESTORE_PC)
    {
        if (task == 0)
        {
            result = restorePcReq();
        }
        else if (task == 111)
        {
            result = restorePcOk();
            task = 0;
        }
        else if (task == 112)
        {
            result = restorePcFail(static_cast<short*>(param));
            task = 0;
        }
        else if (task == 113)
        {
            result = restorePcExpired();
            task = 0;
        }
    }
    if (_state == CHECK_SECOND_PASSWORD_STATUS)
    {
        if (task == 0)
        {
            result = checkSecondPasswordStatus();
        }
        else if (task == 62)
        {
            result = checkSecondPasswordStatusResponse(param);
            task = 0;
        }
        else if (task == 63)
        {
            result = checkSecondPasswordStatusExpire();
            task = 0;
        }
    }
    if (_state == CHECK_SECOND_PASSWORD_VERIFIED)
    {
        if (task == 0)
        {
            result = checkSecondPasswordVerified();
        }
        else if (task == 64)
        {
            result = checkSecondPasswordVerifiedResponse(param);
            task = 0;
        }
        else if (task == 65)
        {
            result = checkSecondPasswordVerifiedExpire();
            task = 0;
        }
    }
    if (_state == GET_SLOT)
    {
        if (task == 0)
        {
            result = requestGetSlot();
        }
        else if (task == 37)
        {
            result = responseGetSlot(param);
            task = 0;
        }
        else if (task == 38)
        {
            result = expireGetSlot();
            task = 0;
        }
    }
    if (_state == GET_CHARGE_INFO)
    {
        if (task == 0)
        {
            result = requestChargeGetInfo();
        }
        else if (task == 52)
        {
            result = responseChargeGetInfo(param);
            task = 0;
        }
        else if (task == 53)
        {
            result = expireChargeGetInfo();
            task = 0;
        }
    }
    if (_state == TRY_ENTER_GAME_WORLD && task == 0)
        result = tryEnterGameWorld();
    if (_state == ISSUE_GAME_WORLD_TOKEN && task == 0)
        return issueGameWorldToken();
    return result;
}

// 0x7bcf0
bool TryEnterGameWorldJob::init()
{
    CliSession* const owner = _owner;
    if (owner->_state != kCssLobby)
    {
        JOB_LOG(Log::LT_ERROR, 214, L"[job], cli-session is not in lobby", L"");
        _lgate->SendGetEnterWorldTokenFail(_owner->_clikey, 5);
        return false;
    }

    Character* const pc = owner->getCharacterInSlot(_slotid);
    if (pc == nullptr)
    {
        JOB_LOG(Log::LT_ERROR, 221, L"[job], no such character", L", slot-id:" SLOTID_FMT, SLOTID_ARGS(_slotid));
        _lgate->SendGetEnterWorldTokenFail(_owner->_clikey, 101);
        return false;
    }
    if (pc->_db.job == 11 && !ContentsRuleConfig::GetContentsRuleConfig()->GetEnablePlayWarrior())
    {
        JOB_LOG(Log::LT_ERROR, 231, L"[job], can not play warrior, check ContentsRuleConfig ", L", slot-id:" SLOTID_FMT,
                SLOTID_ARGS(_slotid));
        _lgate->SendGetEnterWorldTokenFail(_owner->_clikey, 117);
        return false;
    }

    // A character in IN_TRY_RESTORE is restored first (state RESTORE_PC). Else it must be playable.
    bool restore = false;
    if (pc->_db.state == Character::IN_TRY_RESTORE)
    {
        restore = true;
    }
    else
    {
        Character::ErrCode const error = pc->IsPlayable();
        if (error != Character::ERR_OK)
        {
            JOB_LOG(Log::LT_ERROR, 245, L"[job], not playable character", L", error:%d, pcid:0x%I64X", error,
                    pc->_db.pcid);
            short reason;
            if (error == Character::ERR_BLOCKED)
                reason = 109;
            else if (error == Character::ERR_STUCK)
                reason = 110;
            else
                reason = 102;
            _lgate->SendGetEnterWorldTokenFail(_owner->_clikey, reason);
            return false;
        }
    }

    LobbyService* const service = owner->queryLobbyService(pc);
    if (service != nullptr &&
        (service->GetDB().serviceType != 2 ||
         !LobbyDaemon::_instance->_config->_permitEnterWorldInChangeCharacterAppearance))
    {
        JOB_LOG(Log::LT_ERROR, 276, L"[job], in service entry", L", pcid:0x%I64X", pc->_db.pcid);
        _lgate->SendGetEnterWorldTokenFail(_owner->_clikey, 9);
        return false;
    }

    _gamed = LobbyDaemon::_instance->_gamedchmgr->Acquire(pc->_db.belongingWorld);
    if (_gamed == nullptr)
    {
        JOB_LOG(Log::LT_ERROR, 285, L"[job], gamed channel not available", L", wid:%d, pcid:0x%I64X",
                pc->_db.belongingWorld, _pcid);
        _lgate->SendGetEnterWorldTokenFail(_owner->_clikey, 104);
        return false;
    }

    _tran = new (Memory::_Manager[2]->Alloc(sizeof(LobbyJobTransaction), kFile, 290)) LobbyJobTransaction;
    _belongingWorld = pc->_db.belongingWorld;
    _chargeApplyType = CHARGEAPPLYTYPE_FREETOPLAY;
    _pcid = pc->_db.pcid;
    _owner->_state = kCssTryEnterWorld;
    JOB_LOG(Log::LT_DEBUG, 298, L"[job], init ok",
            L", request-gate-wid:%d, slot-id:" SLOTID_FMT L", pcid:0x%I64X, pc-belonging-wid:%d", GATE_WID(_lgate),
            SLOTID_ARGS(_slotid), _pcid, _belongingWorld);

    if (_owner->_isMobile)
    {
        unsigned int ROLES[2] = {2, 3};
        _owner->setRole(ROLES, 2);
        transit(restore ? RESTORE_PC : TRY_ENTER_GAME_WORLD);
        return true;
    }
    if (restore)
    {
        transit(RESTORE_PC);
        return true;
    }
    transit(LobbyDaemon::_instance->_config->_enableSecondPassword ? CHECK_SECOND_PASSWORD_STATUS : GET_SLOT);
    return true;
}

// 0x7c660
bool TryEnterGameWorldJob::restorePcReq()
{
    if (!_gamed->SendRestoreCharacterReq(_tran->Set(this, 113), _pcid))
    {
        JOB_LOG(Log::LT_ERROR, 353, L"[job], req restore pc fail; send req fail", L", wid:%d, pcid:0x%I64X",
                _belongingWorld, _pcid);
        _owner->_state = kCssLobby;
        _lgate->SendGetEnterWorldTokenFail(_owner->_clikey, 104);
        return false;
    }
    JOB_LOG(Log::LT_DEBUG, 359, L"[job], restore req sent", L", wid:%d, pcid:0x%I64X", _belongingWorld, _pcid);
    return true;
}

// 0x7c820
bool TryEnterGameWorldJob::restorePcOk()
{
    JOB_LOG(Log::LT_DEBUG, 366, L"[job], restore ok recv", L"");
    _gamed->TRecv(_tran);
    Character* const pc = _owner->getCharacter(_pcid);
    if (pc == nullptr)
    {
        JOB_LOG(Log::LT_ERROR, 372, L"[job], pc disappeared", L", pcid:0x%I64X", _pcid);
        _lgate->SendGetEnterWorldTokenFail(_owner->_clikey, 101);
        return false;
    }
    Character::ErrCode const error = pc->FinishRestore();
    if (error != Character::ERR_OK)
    {
        JOB_LOG(Log::LT_ERROR, 380, L"[job], finish restore fail", L", error:%d, pcid:0x%I64X", error, _pcid);
        _lgate->SendGetEnterWorldTokenFail(_owner->_clikey, 2);
        return false;
    }
    JOB_LOG(Log::LT_DEBUG, 385, L"[job], finish restore ok", L", pcid:0x%I64X", _pcid);
    if (_owner->_isMobile)
    {
        transit(TRY_ENTER_GAME_WORLD);
        return true;
    }
    transit(LobbyDaemon::_instance->_config->_enableSecondPassword ? CHECK_SECOND_PASSWORD_STATUS : GET_SLOT);
    return true;
}

// 0x7cba0
bool TryEnterGameWorldJob::restorePcFail(short* reason)
{
    _gamed->TRecv(_tran);
    if (reason == nullptr)
    {
        JOB_LOG(Log::LT_ERROR, 418, L"[job], invalid parameter", L"");
        _lgate->SendGetEnterWorldTokenFail(_owner->_clikey, 2);
        return false;
    }
    short const r = *reason;
    JOB_LOG(Log::LT_DEBUG, 425, L"[job], restore fail recv", L", reason:%d", r);
    if (r != 35)
    {
        // Reasons 33 and 34 give 110. All other reasons give 1.
        _lgate->SendGetEnterWorldTokenFail(_owner->_clikey, static_cast<unsigned int>(r - 33) <= 1 ? 110 : 1);
        return false;
    }

    // Reason 35: the character is already restored. Finish the restore here and continue.
    Character* const pc = _owner->getCharacter(_pcid);
    if (pc == nullptr)
    {
        JOB_LOG(Log::LT_ERROR, 445, L"[job], pc disappeared", L", pcid:0x%I64X", _pcid);
        _lgate->SendGetEnterWorldTokenFail(_owner->_clikey, 101);
        return false;
    }
    Character::ErrCode const error = pc->FinishRestore();
    if (error != Character::ERR_OK)
    {
        JOB_LOG(Log::LT_ERROR, 453, L"[job], finish restore fail", L", error:%d, pcid:0x%I64X", error, _pcid);
        _lgate->SendGetEnterWorldTokenFail(_owner->_clikey, 2);
        return false;
    }
    JOB_LOG(Log::LT_DEBUG, 458, L"[job], already restored; continue try enter world", L"");
    if (_owner->_isMobile)
    {
        transit(TRY_ENTER_GAME_WORLD);
        return true;
    }
    transit(LobbyDaemon::_instance->_config->_enableSecondPassword ? CHECK_SECOND_PASSWORD_STATUS : GET_SLOT);
    return true;
}

// 0x7cfe0
bool TryEnterGameWorldJob::restorePcExpired()
{
    JOB_LOG(Log::LT_ERROR, 487, L"[job], restore pc req expired", L"");
    _lgate->SendGetEnterWorldTokenFail(_owner->_clikey, 104);
    transit(FIN);
    return true;
}

// 0x7d0e0
bool TryEnterGameWorldJob::checkSecondPasswordStatus()
{
    NPGameServiceChannel* const gs = LobbyDaemon::_instance->_npServchmgr->_gameServChannel;
    if (gs == nullptr)
    {
        JOB_LOG(Log::LT_ERROR, 500, L"[job], channel not available", L"");
        _owner->_state = kCssLobby;
        _lgate->SendGetEnterWorldTokenFail(_owner->_clikey, 7);
        return false;
    }

    NPLobbyJobTransaction* const tr =
        new (Memory::_Manager[2]->Alloc(sizeof(NPLobbyJobTransaction), kFile, 506)) NPLobbyJobTransaction;
    StsMsgLib::_StsMsgRequestSecondPasswordGetStatus msg;
    msg.msgInfo.eCmd = StsMsgLib::COMMAND_COMMON_SECONDPWD_GET_STATUS;
    msg.msgInfo.msgType = StsMsgLib::MESSAGE_TYPE_REQUEST;
    msg.msgInfo.nTxnId = 0;
    msg.pUserId = reinterpret_cast<_GUID*>(&_owner->_acb._userid);
    msg.nType = LobbyDaemon::_instance->_config->_secondPasswordType;
    if (!gs->SendMsg(&msg, true, tr->Set(this, 63)))
    {
        JOB_LOG(Log::LT_ERROR, 512, L"[job], send fail", L"");
        _owner->_state = kCssLobby;
        _lgate->SendGetEnterWorldTokenFail(_owner->_clikey, 7);
        // The original calls the scalar deleting destructor (flag 1) and then Free. Its operator delete is empty.
        tr->~NPLobbyJobTransaction();
        Memory::_Manager[2]->Free(tr, kFile, 515);
        return false;
    }
    JOB_LOG(Log::LT_DEBUG, 519, L"[job], get status sent", L"");
    return true;
}

// 0x7d400
bool TryEnterGameWorldJob::checkSecondPasswordStatusResponse(void* param)
{
    StsMsgLib::_StsMsgResponseSecondPasswordGetStatus* const res =
        static_cast<StsMsgLib::_StsMsgResponseSecondPasswordGetStatus*>(param);
    if (_owner->_state != kCssTryEnterWorld)
    {
        JOB_LOG(Log::LT_ERROR, 527, L"[job], invalid cli-session state", L"");
        _lgate->SendGetEnterWorldTokenFail(_owner->_clikey, 5);
        return false;
    }

    // LIFT: the original does not check param for null here (checkSecondPasswordVerifiedResponse does).
    JOB_LOG(Log::LT_DEBUG, 533, L"[job], get status response recv", NP_RES_FMT, NP_RES_ARGS(res));
    short reason;
    if (NP_RES_OK(res))
    {
        if ((res->nActionMask & 1) == 0)
        {
            JOB_LOG(Log::LT_DEBUG, 557, L"[job], character lock disabled", L"");
            transit(GET_SLOT);
            return true;
        }
        if (res->eBlockStatus != StsMsgLib::_StsMsgResponseSecondPasswordGetStatus::EBLOCKSTATUS_BLOCKED)
        {
            transit(CHECK_SECOND_PASSWORD_VERIFIED);
            return true;
        }
        JOB_LOG(Log::LT_ERROR, 564, L"[job], in block", L", until:%I64d", res->tBlockedUntil);
        reason = 114;
    }
    else
    {
        if (res->msgInfo.errInfo.nErrorCode == 3333)
        {
            JOB_LOG(Log::LT_DEBUG, 539, L"[job], not use second-password", L"");
            transit(GET_SLOT);
            return true;
        }
        JOB_LOG(Log::LT_ERROR, 545, L"[job], unknown error-code", NP_RES_FMT, NP_RES_ARGS(res));
        reason = 2;
    }
    _owner->_state = kCssLobby;
    _lgate->SendGetEnterWorldTokenFail(_owner->_clikey, reason);
    return false;
}

// 0x7d900
bool TryEnterGameWorldJob::checkSecondPasswordStatusExpire()
{
    JOB_LOG(Log::LT_ERROR, 576, L"[job], get status expired", L"");
    if (_owner->_state != kCssTryEnterWorld)
    {
        JOB_LOG(Log::LT_ERROR, 580, L"[job], invalid cli-session state", L"");
        _lgate->SendGetEnterWorldTokenFail(_owner->_clikey, 5);
        return false;
    }
    _owner->_state = kCssLobby;
    _lgate->SendGetEnterWorldTokenFail(_owner->_clikey, 7);
    transit(FIN);
    return true;
}

// 0x7daa0
bool TryEnterGameWorldJob::checkSecondPasswordVerified()
{
    NPGameServiceChannel* const gs = LobbyDaemon::_instance->_npServchmgr->_gameServChannel;
    if (gs == nullptr)
    {
        JOB_LOG(Log::LT_ERROR, 597, L"[job], channel not available", L"");
        _owner->_state = kCssLobby;
        _lgate->SendGetEnterWorldTokenFail(_owner->_clikey, 7);
        return false;
    }

    NPLobbyJobTransaction* const tr =
        new (Memory::_Manager[2]->Alloc(sizeof(NPLobbyJobTransaction), kFile, 603)) NPLobbyJobTransaction;
    StsMsgLib::_StsMsgRequestSecondPasswordIsVerified msg;
    msg.msgInfo.eCmd = StsMsgLib::COMMAND_SRV_SECONDPWD_IS_VERIFIED;
    msg.msgInfo.msgType = StsMsgLib::MESSAGE_TYPE_REQUEST;
    msg.msgInfo.nTxnId = 0;
    msg.pUserId = reinterpret_cast<_GUID*>(&_owner->_acb._userid);
    msg.nType = LobbyDaemon::_instance->_config->_secondPasswordType;
    msg.nActionIndex = 0;
    if (!gs->SendMsg(&msg, true, tr->Set(this, 65)))
    {
        JOB_LOG(Log::LT_ERROR, 610, L"[job], send fail", L"");
        _owner->_state = kCssLobby;
        _lgate->SendGetEnterWorldTokenFail(_owner->_clikey, 7);
        tr->~NPLobbyJobTransaction();
        Memory::_Manager[2]->Free(tr, kFile, 613);
        return false;
    }
    JOB_LOG(Log::LT_DEBUG, 617, L"[job], req sent", L"");
    return true;
}

// 0x7ddc0
bool TryEnterGameWorldJob::checkSecondPasswordVerifiedResponse(void* param)
{
    StsMsgLib::_StsMsgResponseSecondPasswordIsVerified* const res =
        static_cast<StsMsgLib::_StsMsgResponseSecondPasswordIsVerified*>(param);
    if (_owner->_state != kCssTryEnterWorld)
    {
        JOB_LOG(Log::LT_ERROR, 625, L"[job], invalid cli-session state", L"");
        _lgate->SendGetEnterWorldTokenFail(_owner->_clikey, 5);
        return false;
    }
    if (res == nullptr)
    {
        JOB_LOG(Log::LT_ERROR, 632, L"[job], invalid parameter", L"");
        _owner->_state = kCssLobby;
        _lgate->SendGetEnterWorldTokenFail(_owner->_clikey, 2);
        return false;
    }

    JOB_LOG(Log::LT_DEBUG, 639, L"[job], recv response", NP_RES_FMT, NP_RES_ARGS(res));
    if (!NP_RES_OK(res))
    {
        short reason;
        switch (res->msgInfo.errInfo.nErrorCode)
        {
        case 0xD05:
            reason = 113;
            break;
        case 0xD06:
            reason = 114;
            break;
        case 0xD11:
            reason = 115;
            break;
        case 0xD12:
            reason = 116;
            break;
        default:
            reason = 1;
            break;
        }
        // The original sends first and then resets the session state.
        _lgate->SendGetEnterWorldTokenFail(_owner->_clikey, reason);
        _owner->_state = kCssLobby;
        return false;
    }
    transit(GET_SLOT);
    return true;
}

// 0x7e0f0
bool TryEnterGameWorldJob::checkSecondPasswordVerifiedExpire()
{
    JOB_LOG(Log::LT_ERROR, 674, L"[job], expired", L"");
    if (_owner->_state != kCssTryEnterWorld)
    {
        JOB_LOG(Log::LT_ERROR, 678, L"[job], invalid session state", L"");
        _lgate->SendGetEnterWorldTokenFail(_owner->_clikey, 5);
        return false;
    }
    _owner->_state = kCssLobby;
    _lgate->SendGetEnterWorldTokenFail(_owner->_clikey, 7);
    transit(FIN);
    return true;
}

// 0x7e290
bool TryEnterGameWorldJob::requestGetSlot()
{
    NPGameServiceChannel* const gs = LobbyDaemon::_instance->_npServchmgr->_gameServChannel;
    if (gs == nullptr)
    {
        JOB_LOG(Log::LT_ERROR, 694, L"[job], req get slot fail; np game-service channel not available", L"");
        _owner->_state = kCssLobby;
        _lgate->SendGetEnterWorldTokenFail(_owner->_clikey, 2);
        return false;
    }
    NPLobbyJobTransaction* const tr =
        new (Memory::_Manager[2]->Alloc(sizeof(NPLobbyJobTransaction), kFile, 700)) NPLobbyJobTransaction;
    if (!gs->SendRequestSlotGetSlot(tr->Set(this, 38), _owner->_acb._userid, _slotid))
    {
        JOB_LOG(Log::LT_ERROR, 702, L"[job], req get slot fail; send fail", L"");
        _owner->_state = kCssLobby;
        _lgate->SendGetEnterWorldTokenFail(_owner->_clikey, 2);
        tr->~NPLobbyJobTransaction();
        Memory::_Manager[2]->Free(tr, kFile, 705);
        return false;
    }
    JOB_LOG(Log::LT_DEBUG, 709, L"[job], request get slot sent", L"");
    return true;
}

// 0x7e570
bool TryEnterGameWorldJob::responseGetSlot(void* param)
{
    JOB_LOG(Log::LT_DEBUG, 716, L"[job], get slot recv", L"");
    if (_owner->_state != kCssTryEnterWorld)
    {
        JOB_LOG(Log::LT_ERROR, 719, L"[job], invalid cli-session state", L"");
        _lgate->SendGetEnterWorldTokenFail(_owner->_clikey, 5);
        return false;
    }

    StsMsgLib::_StsMsgResponseSlotGetSlot* const res = static_cast<StsMsgLib::_StsMsgResponseSlotGetSlot*>(param);
    if (!NP_RES_OK(res))
    {
        JOB_LOG(Log::LT_ERROR, 727, L"[job], get slot fail",
                L",np-tid:%u, cmd:%d, type:%d, status-code:%u, reason:%s, error-code:%d", res->GetTransactionId(),
                res->GetCommand(), res->GetMessageType(), res->msgInfo.errInfo.nStatusCode,
                res->msgInfo.errInfo.pwszReason != nullptr ? res->msgInfo.errInfo.pwszReason : L"null",
                res->msgInfo.errInfo.nErrorCode);
        _owner->_state = kCssLobby;
        _lgate->SendGetEnterWorldTokenFail(_owner->_clikey, 2);
        return false;
    }
    id128 const& recvSlotId = reinterpret_cast<id128 const&>(res->guidSlotId);
    if (recvSlotId.id[0] != _slotid.id[0] || recvSlotId.id[1] != _slotid.id[1])
    {
        JOB_LOG(Log::LT_ERROR, 735, L"[job], slot-id mismatch", L", recv:slot-id:" SLOTID_FMT,
                GUID_ARGS(res->guidSlotId));
        _owner->_state = kCssLobby;
        _lgate->SendGetEnterWorldTokenFail(_owner->_clikey, 2);
        return false;
    }
    // The original compares 5 wide chars (with the NUL). LIFT: null check added (not in the original).
    if (res->pwszSlotType == nullptr || wcsncmp(res->pwszSlotType, L"char", 5) != 0)
    {
        JOB_LOG(Log::LT_ERROR, 742, L"[job], not character slot", L", slot-type:%s", res->pwszSlotType);
        _owner->_state = kCssLobby;
        _lgate->SendGetEnterWorldTokenFail(_owner->_clikey, 2);
        return false;
    }
    JOB_LOG(Log::LT_DEBUG, 755, L"[job], get slot ok", L", slot-id:" SLOTID_FMT, GUID_ARGS(res->guidSlotId));
    transit(LobbyDaemon::_instance->_config->_applyCharge ? GET_CHARGE_INFO : TRY_ENTER_GAME_WORLD);
    return true;
}

// 0x7eb60
bool TryEnterGameWorldJob::expireGetSlot()
{
    JOB_LOG(Log::LT_ERROR, 766, L"[job], get slot expired", L"");
    short reason;
    if (_owner->_state == kCssTryEnterWorld)
    {
        _owner->_state = kCssLobby;
        reason = 2;
    }
    else
    {
        JOB_LOG(Log::LT_ERROR, 769, L"[job], invalid cli-session state", L"");
        reason = 5;
    }
    _lgate->SendGetEnterWorldTokenFail(_owner->_clikey, reason);
    transit(FIN);
    return true;
}

// 0x7ecf0
bool TryEnterGameWorldJob::requestChargeGetInfo()
{
    NPGameServiceChannel* const gs = LobbyDaemon::_instance->_npServchmgr->_gameServChannel;
    if (gs == nullptr)
    {
        JOB_LOG(Log::LT_ERROR, 786, L"[job], req charge get info fail; np game-service channel not available", L"");
        _owner->_state = kCssLobby;
        _lgate->SendGetEnterWorldTokenFail(_owner->_clikey, 2);
        return false;
    }
    NPLobbyJobTransaction* const tr =
        new (Memory::_Manager[2]->Alloc(sizeof(NPLobbyJobTransaction), kFile, 792)) NPLobbyJobTransaction;
    if (!gs->SendRequestChargeGetInfo(tr->Set(this, 53), _owner->_acb._userid, _owner->_ipv4))
    {
        JOB_LOG(Log::LT_ERROR, 794, L"[job], req charge get info fail; send fail", L"");
        _owner->_state = kCssLobby;
        _lgate->SendGetEnterWorldTokenFail(_owner->_clikey, 2);
        tr->~NPLobbyJobTransaction();
        Memory::_Manager[2]->Free(tr, kFile, 797);
        return false;
    }
    JOB_LOG(Log::LT_DEBUG, 801, L"[job], request charge get info sent", L"");
    return true;
}

// 0x7efd0
// LIFT: Not done (part 2 of the card pair). The body builds the charge apply type from the charge info.
bool TryEnterGameWorldJob::responseChargeGetInfo(void*)
{
    LIFT_STUB(0x7efd0);
}

// 0x7fa60
// LIFT: Not done (part 2).
bool TryEnterGameWorldJob::expireChargeGetInfo()
{
    LIFT_STUB(0x7fa60);
}

// 0x7fbf0
// LIFT: Not done (part 2).
bool TryEnterGameWorldJob::tryEnterGameWorld()
{
    LIFT_STUB(0x7fbf0);
}

// 0x7ffe0
// LIFT: Not done (part 2). The body calls LobbyTokenDesk::Issue (0x96e20, still LIFT_STUB).
bool TryEnterGameWorldJob::issueGameWorldToken()
{
    LIFT_STUB(0x7ffe0);
}
