// DeleteCharacterJob.obj (LobbyDaemon PDB, 2019 + PDB). Lifted from the pseudocode with PDB types.
#include <new>
#include <wchar.h>
#include <winsock2.h>
#include <windows.h>
#include "DeleteCharacterJob.h"
#include "AccountInventoryChannel.h"
#include "AlertSender.h"
#include "Character.h"
#include "CliSession.h"
#include "GameWorld.h"
#include "GamedChannel.h"
#include "LiftStub.h"
#include "LobbyConfig.h"
#include "LobbyDaemon.h"
#include "LobbyGateChannel.h"
#include "LobbyJobParams.h"
#include "Log.h"
#include "Memory.h"
#include "MemoryManager.h"
#include "NPServiceChannel.h"
#include "TransactionChannel.h"

// LIFT: PDB public LobbyErrorDesc (.data 0003:2032). LobbyGamePacketHandler.cpp has the definition (placeholder).
extern wchar_t const* LobbyErrorDesc[28];

static wchar_t const kFile[] = L"DeleteCharacterJob.cpp";

// The log suffix of all LobbyJob logs. The original reads the owner state 2 times (HIWORD and LOWORD).
#define JOB_LOG(logType, line, msg, fmt, ...)                                                                          \
    Log::Write(logType, kFile, line, msg L", tid:0x%I64X, type:%d, state:%d, cli-key:0x%I64X, cli-state:%d.%d" fmt,   \
               this != nullptr ? _id : 0, this != nullptr ? GetDefinition()->type : -1,                            \
               this != nullptr ? _state : -1, this != nullptr && _owner != nullptr ? _owner->_clikey : 0,          \
               HIWORD(this != nullptr && _owner != nullptr ? _owner->_state : 0),                                  \
               LOWORD(this != nullptr && _owner != nullptr ? _owner->_state : 0), ##__VA_ARGS__)

// The "== CRASH ==" form: the log and then the alert with the same text. Each call reads its arguments again.
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

// The slot id in the logs (guid form).
#define SLOTID_FMT L"%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X"
#define SLOTID_ARGS(s)                                                                                               \
    (s).guid.id1, (s).guid.id2, (s).guid.id3, (s).guid.id4[0], (s).guid.id4[1], (s).guid.id4[2], (s).guid.id4[3],    \
        (s).guid.id4[4], (s).guid.id4[5], (s).guid.id4[6], (s).guid.id4[7]

// The gate world id in the logs. A null lobby-gate gives 0.
#define GATE_WID(lg) ((lg) != nullptr ? (lg)->GetWid() : 0)

// The NP error info suffix of the second-password response logs.
#define NP_RES_FMT L", np-tid:%u, cmd:%d, type:%d, status-code:%u, reason:%s, error-code:%d"
#define NP_RES_ARGS(r)                                                                                               \
    (r)->GetTransactionId(), (r)->GetCommand(), (r)->GetMessageType(), (r)->msgInfo.errInfo.nStatusCode,             \
        (r)->msgInfo.errInfo.pwszReason != nullptr ? (r)->msgInfo.errInfo.pwszReason : L"null",                      \
        (r)->msgInfo.errInfo.nErrorCode

// PDB enum CliSession state: CSS_LOBBY = 0x20000.

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
}  // namespace StsMsgLib

namespace
{
LobbyJobStateDef const StateDef[] = {{0, L"INIT"},
                                     {1, L"CHECK_SECOND_PASSWORD_STATUS"},
                                     {2, L"CHECK_SECOND_PASSWORD_VERIFIED"},
                                     {3, L"CHECK_ACCOUNT_INVENTORY_CHARACTER_GOODS"},
                                     {4, L"TRY_DELETION"},
                                     {5, L"DIRECT_DELETION"},
                                     {6, L"SCHEDULE_DELETION"},
                                     {7, L"FIN"}};  // 0x12e020
}

LobbyJobDef DeleteCharacterJob::_def = {6, StateDef, 7, L"DeleteCharacterJob"};  // 0x201d30

#include "ObjectPoolLobbyDaemon.h"

// .data 0x204410, dynamic init 0x11ddf0, atexit dtor 0x11ec40.
// The exe .data holds id 1, objsize 0x90, desc L"DeleteCharacterJob".
ObjPool DeleteCharacterJob::_pool(1, 0x90, L"DeleteCharacterJob");

// 0x45040
LobbyJobDef const* DeleteCharacterJob::GetDefinition() const
{
    return &_def;
}

// 0x45050
// LIFT: Not done. The body calls _pool.Checkin. ObjPool is not in lift_lobbydaemon.
void DeleteCharacterJob::deallocate_me(void*, wchar_t const*, int)
{
    LIFT_STUB(0x45050);
}

// 0x450a0
// The original constructs a job on the stack (null owner) and returns its vfptr. It does not run the destructor.
void* DeleteCharacterJob::_vtbl()
{
    char buf[sizeof(DeleteCharacterJob)];
    DeleteCharacterJob* job = ::new (buf) DeleteCharacterJob(nullptr);
    return *reinterpret_cast<void**>(job);
}

// 0x45120
DeleteCharacterJob::DeleteCharacterJob(CliSession* owner)
    : CliSessionJob(owner), _tran(nullptr), _lgate(nullptr), _gamed(nullptr), _acciv(nullptr), _level(0)
{
    _slotid.id[0] = 0;
    _slotid.id[1] = 0;
}

// 0x451a0
// LIFT: the original does not release _acciv. init does not add a reference to it.
DeleteCharacterJob::~DeleteCharacterJob()
{
    if (_tran != nullptr)
    {
        _tran->removeReferenceCount(kFile, 90);
        _tran = nullptr;
    }
    if (_lgate != nullptr)
    {
        _lgate->removeReferenceCount(kFile, 94);
        _lgate = nullptr;
    }
    if (_gamed != nullptr)
    {
        _gamed->removeReferenceCount(kFile, 98);
        _gamed = nullptr;
    }
}

// 0x45240
// Tasks: 11 TASK_DELETE_CHARACTER_REQ; 62/63 second-password status response/expire; 64/65 second-password
// verified response/expire; 168/169/170 character goods count ok/fail/expire; 108/109/110 delete ok/fail/expire.
// After a handler, the task is 0. Then the next state can run in the same call.
bool DeleteCharacterJob::work(int task, void* param)
{
    bool result = false;
    if (_state == INIT && task == 11)
    {
        result = init(11, param);
        task = 0;
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
    if (_state == CHECK_ACCOUNT_INVENTORY_CHARACTER_GOODS)
    {
        if (task == 0)
        {
            result = getCharacterGoodsReq();
        }
        else if (task == 168)
        {
            result = getCharacterGoodsCountOk(param);
            task = 0;
        }
        else if (task == 169)
        {
            result = getCharacterGoodsCountFail(param);
            task = 0;
        }
        else if (task == 170)
        {
            result = getCharacterGoodsCountExpire();
            task = 0;
        }
    }
    if (_state == TRY_DELETION)
    {
        if (task == 0)
        {
            result = deleteReq();
        }
        else if (task == 108)
        {
            result = deleteOk(static_cast<DeleteCharacterOkParam*>(param));
            task = 0;
        }
        else if (task == 109)
        {
            result = deleteFail(param);
            task = 0;
        }
        else if (task == 110)
        {
            result = deleteExpire();
            task = 0;
        }
    }
    if (_state == DIRECT_DELETION && task == 0)
        result = directDelete();
    if (_state == SCHEDULE_DELETION && task == 0)
        return scheduleDelete();
    return result;
}

// 0x453a0
bool DeleteCharacterJob::init(int task, void* param)
{
    if (_owner->_state != 0x20000)  // CSS_LOBBY
    {
        JOB_LOG(Log::LT_ERROR, 196, L"[job], cli-session not in lobby", L"");
        transit(FIN);
        return true;
    }
    if (task != 11 || param == nullptr)
    {
        JOB_CRASH(202, L"== CRASH == [job], invalid task parameter");
        transit(FIN);
        return true;
    }
    DeleteCharacterReqParam* const p = static_cast<DeleteCharacterReqParam*>(param);
    if (p->lgate == nullptr || (p->slotid.id[0] == ID128_ID_ZERO.id[0] && p->slotid.id[1] == ID128_ID_ZERO.id[1]))
    {
        JOB_LOG(Log::LT_ERROR, 215, L"[job], invalid parameter", L", gate-wid:%d, slot-id:" SLOTID_FMT,
                GATE_WID(p->lgate), SLOTID_ARGS(p->slotid));
        if (p->lgate != nullptr)
            p->lgate->SendDeleteCharacterFail(_owner->_clikey, p->slotid, Character::CLIENTSTATE_UNKNOWN, 6);
        transit(FIN);
        return true;
    }

    Character* const pc = _owner->getCharacterInSlot(p->slotid);
    if (pc == nullptr)
    {
        JOB_LOG(Log::LT_ERROR, 224, L"[job], no such character", L", gate-wid:%d, slot-id:" SLOTID_FMT,
                GATE_WID(p->lgate), SLOTID_ARGS(p->slotid));
        p->lgate->SendDeleteCharacterFail(_owner->_clikey, p->slotid, Character::CLIENTSTATE_UNKNOWN, 134);
        transit(FIN);
        return true;
    }
    if (_owner->queryLobbyService(pc) != nullptr)
    {
        JOB_LOG(Log::LT_ERROR, 231, L"[job], pc in service-entry", L", gate-wid:%d, slot-id:" SLOTID_FMT,
                GATE_WID(p->lgate), SLOTID_ARGS(p->slotid));
        p->lgate->SendDeleteCharacterFail(_owner->_clikey, p->slotid, Character::CLIENTSTATE_UNKNOWN, 9);
        transit(FIN);
        return true;
    }

    GameWorld* const world = LobbyDaemon::_instance->_gameWorldRegistry->Get(pc->_db.belongingWorld);
    if (world == nullptr)
    {
        JOB_LOG(Log::LT_ERROR, 239, L"[job], world not registered", L", wid:%d, gate-wid:%d, slot-id:" SLOTID_FMT,
                pc->_db.belongingWorld, GATE_WID(p->lgate), SLOTID_ARGS(p->slotid));
        p->lgate->SendDeleteCharacterFail(_owner->_clikey, p->slotid, Character::CLIENTSTATE_UNKNOWN, 138);
        transit(FIN);
        return true;
    }
    if (!world->PermitCharacterManagement(_owner, false))
    {
        int const error = TLobbyError;
        JOB_LOG(Log::LT_ERROR, 248, L"[job], world denied", L", error:%s, wid:%d, gate-wid:%d, slot-id:" SLOTID_FMT,
                static_cast<unsigned int>(error) >= 28 ? L"LOBERR_UNDEFINED" : LobbyErrorDesc[error],
                pc->_db.belongingWorld, GATE_WID(p->lgate), SLOTID_ARGS(p->slotid));
        if (error == LOBERR_GAMEWORLD_NOT_USABLE)
            p->lgate->SendDeleteCharacterFail(_owner->_clikey, p->slotid, Character::CLIENTSTATE_UNKNOWN, 138);
        else if (error == LOBERR_GAMEWORLD_CHARACTER_MANAGEMENT_NOT_ALLOWED)
            p->lgate->SendDeleteCharacterFail(_owner->_clikey, p->slotid, Character::CLIENTSTATE_UNKNOWN, 143);
        else
            p->lgate->SendDeleteCharacterFail(_owner->_clikey, p->slotid, Character::CLIENTSTATE_UNKNOWN, 2);
        transit(FIN);
        return true;
    }

    _gamed = LobbyDaemon::_instance->_gamedchmgr->Acquire(pc->_db.belongingWorld);
    if (_gamed == nullptr)
    {
        JOB_LOG(Log::LT_ERROR, 270, L"[job], world not available", L", wid:%d, gate-wid:%d, slot-id:" SLOTID_FMT,
                pc->_db.belongingWorld, GATE_WID(p->lgate), SLOTID_ARGS(p->slotid));
        p->lgate->SendDeleteCharacterFail(_owner->_clikey, p->slotid, Character::CLIENTSTATE_UNKNOWN, 138);
        transit(FIN);
        return true;
    }

    LobbyConfig const* config = LobbyDaemon::_instance->_config;
    if (config->_useAccountInventory && config->_checkCharacterGoodsForCharacterDeletion)
    {
        _acciv = LobbyDaemon::_instance->_accountInventoryChannel;
        if (_acciv == nullptr || !_acciv->IsConnected())
        {
            JOB_LOG(Log::LT_ERROR, 279, L"[job], account-inventory not available",
                    L", wid:%d, gate-wid:%d, slot-id:" SLOTID_FMT, pc->_db.belongingWorld, GATE_WID(p->lgate),
                    SLOTID_ARGS(p->slotid));
            p->lgate->SendDeleteCharacterFail(_owner->_clikey, p->slotid, Character::CLIENTSTATE_UNKNOWN, 7);
            transit(FIN);
            return true;
        }
    }

    _tran = new (Memory::_Manager[2]->Alloc(sizeof(LobbyJobTransaction), kFile, 286)) LobbyJobTransaction;
    _lgate = p->lgate;
    _slotid = p->slotid;
    _lgate->addReferenceCount(false, kFile, 290);
    JOB_LOG(Log::LT_DEBUG, 292, L"[job], init ok", L", gate-wid:%d, slot-id:" SLOTID_FMT, GATE_WID(p->lgate),
            SLOTID_ARGS(p->slotid));

    config = LobbyDaemon::_instance->_config;
    int next;
    if (config->_enableSecondPassword)
        next = CHECK_SECOND_PASSWORD_STATUS;
    else if (config->_useAccountInventory && config->_checkCharacterGoodsForCharacterDeletion)
        next = CHECK_ACCOUNT_INVENTORY_CHARACTER_GOODS;
    else
        next = TRY_DELETION;
    transit(next);
    return true;
}

// 0x46440
bool DeleteCharacterJob::checkSecondPasswordStatus()
{
    NPGameServiceChannel* const gs = LobbyDaemon::_instance->_npServchmgr->_gameServChannel;
    if (gs == nullptr)
    {
        JOB_LOG(Log::LT_ERROR, 308, L"[job], channel not available", L"");
        _lgate->SendDeleteCharacterFail(_owner->_clikey, _slotid, Character::CLIENTSTATE_UNKNOWN, 7);
        return false;
    }

    NPLobbyJobTransaction* const tr =
        new (Memory::_Manager[2]->Alloc(sizeof(NPLobbyJobTransaction), kFile, 313)) NPLobbyJobTransaction;
    StsMsgLib::_StsMsgRequestSecondPasswordGetStatus msg;
    msg.msgInfo.eCmd = StsMsgLib::COMMAND_COMMON_SECONDPWD_GET_STATUS;
    msg.msgInfo.msgType = StsMsgLib::MESSAGE_TYPE_REQUEST;
    msg.msgInfo.nTxnId = 0;
    // LIFT: Hex-Rays lost this store. The disassembly (0x465c9) gives owner + 0xd8 = _acb._userid.
    msg.pUserId = reinterpret_cast<_GUID*>(&_owner->_acb._userid);
    msg.nType = LobbyDaemon::_instance->_config->_secondPasswordType;
    if (!gs->SendMsg(&msg, true, tr->Set(this, 63)))
    {
        JOB_LOG(Log::LT_ERROR, 319, L"[job], send fail", L"");
        _lgate->SendDeleteCharacterFail(_owner->_clikey, _slotid, Character::CLIENTSTATE_UNKNOWN, 7);
        tr->~NPLobbyJobTransaction();
        Memory::_Manager[2]->Free(tr, kFile, 321);
        return false;
    }
    JOB_LOG(Log::LT_DEBUG, 325, L"[job], get status sent", L"");
    return true;
}

// 0x46760
bool DeleteCharacterJob::checkSecondPasswordStatusResponse(void* param)
{
    StsMsgLib::_StsMsgResponseSecondPasswordGetStatus* const res =
        static_cast<StsMsgLib::_StsMsgResponseSecondPasswordGetStatus*>(param);
    JOB_LOG(Log::LT_DEBUG, 331, L"[job], get status response recv", L"");
    if (_owner->_state != 0x20000)  // CSS_LOBBY
    {
        JOB_LOG(Log::LT_ERROR, 335, L"[job], invalid cli-session state", L"");
        _lgate->SendDeleteCharacterFail(_owner->_clikey, _slotid, Character::CLIENTSTATE_UNKNOWN, 5);
        return false;
    }

    // LIFT: the original does not check param for null here (checkSecondPasswordVerifiedResponse does).
    JOB_LOG(Log::LT_DEBUG, 341, L"[job], get status response recv", NP_RES_FMT, NP_RES_ARGS(res));
    short reason;
    unsigned int const statusCode = res->msgInfo.errInfo.nStatusCode;
    if (statusCode == 200 ||
        (statusCode == 400 &&
         _wcsicmp(L"Success", res->msgInfo.errInfo.pwszReason != nullptr ? res->msgInfo.errInfo.pwszReason : L"null") == 0))
    {
        if ((res->nActionMask & 1) == 0)
        {
            JOB_LOG(Log::LT_DEBUG, 367, L"[job], character lock disabled", L"");
            LobbyConfig const* const config = LobbyDaemon::_instance->_config;
            transit(config->_useAccountInventory && config->_checkCharacterGoodsForCharacterDeletion
                        ? CHECK_ACCOUNT_INVENTORY_CHARACTER_GOODS
                        : TRY_DELETION);
            return true;
        }
        if (res->eBlockStatus != StsMsgLib::_StsMsgResponseSecondPasswordGetStatus::EBLOCKSTATUS_BLOCKED)
        {
            transit(CHECK_SECOND_PASSWORD_VERIFIED);
            return true;
        }
        JOB_LOG(Log::LT_ERROR, 377, L"[job], in block", L", until:%I64d", res->tBlockedUntil);
        reason = 145;
    }
    else
    {
        if (res->msgInfo.errInfo.nErrorCode == 3333)
        {
            JOB_LOG(Log::LT_DEBUG, 347, L"[job], not use second-password", L"");
            LobbyConfig const* const config = LobbyDaemon::_instance->_config;
            transit(config->_useAccountInventory && config->_checkCharacterGoodsForCharacterDeletion
                        ? CHECK_ACCOUNT_INVENTORY_CHARACTER_GOODS
                        : TRY_DELETION);
            return true;
        }
        JOB_LOG(Log::LT_ERROR, 356, L"[job], unknown error-code", NP_RES_FMT, NP_RES_ARGS(res));
        reason = 2;
    }
    _lgate->SendDeleteCharacterFail(_owner->_clikey, _slotid, Character::CLIENTSTATE_UNKNOWN, reason);
    return false;
}

// 0x46d20
bool DeleteCharacterJob::checkSecondPasswordStatusExpire()
{
    JOB_LOG(Log::LT_ERROR, 388, L"[job], get status expired", L"");
    if (_owner->_state != 0x20000)  // CSS_LOBBY
    {
        JOB_LOG(Log::LT_ERROR, 392, L"[job], invalid cli-session state", L"");
        _lgate->SendDeleteCharacterFail(_owner->_clikey, _slotid, Character::CLIENTSTATE_UNKNOWN, 5);
        return false;
    }
    _lgate->SendDeleteCharacterFail(_owner->_clikey, _slotid, Character::CLIENTSTATE_UNKNOWN, 7);
    transit(FIN);
    return true;
}

// 0x46ed0
bool DeleteCharacterJob::checkSecondPasswordVerified()
{
    NPGameServiceChannel* const gs = LobbyDaemon::_instance->_npServchmgr->_gameServChannel;
    if (gs == nullptr)
    {
        JOB_LOG(Log::LT_ERROR, 408, L"[job], channel not available", L"");
        _lgate->SendDeleteCharacterFail(_owner->_clikey, _slotid, Character::CLIENTSTATE_UNKNOWN, 7);
        return false;
    }

    NPLobbyJobTransaction* const tr =
        new (Memory::_Manager[2]->Alloc(sizeof(NPLobbyJobTransaction), kFile, 413)) NPLobbyJobTransaction;
    StsMsgLib::_StsMsgRequestSecondPasswordIsVerified msg;
    msg.msgInfo.eCmd = StsMsgLib::COMMAND_SRV_SECONDPWD_IS_VERIFIED;
    msg.msgInfo.msgType = StsMsgLib::MESSAGE_TYPE_REQUEST;
    msg.msgInfo.nTxnId = 0;
    // LIFT: Hex-Rays lost this store. The disassembly (0x47059) gives owner + 0xd8 = _acb._userid.
    msg.pUserId = reinterpret_cast<_GUID*>(&_owner->_acb._userid);
    msg.nType = LobbyDaemon::_instance->_config->_secondPasswordType;
    msg.nActionIndex = 0;
    if (!gs->SendMsg(&msg, true, tr->Set(this, 65)))
    {
        JOB_LOG(Log::LT_ERROR, 420, L"[job], send fail", L"");
        _lgate->SendDeleteCharacterFail(_owner->_clikey, _slotid, Character::CLIENTSTATE_UNKNOWN, 7);
        tr->~NPLobbyJobTransaction();
        Memory::_Manager[2]->Free(tr, kFile, 422);
        return false;
    }
    JOB_LOG(Log::LT_DEBUG, 426, L"[job], req sent", L"");
    return true;
}

// 0x47200
bool DeleteCharacterJob::checkSecondPasswordVerifiedResponse(void* param)
{
    StsMsgLib::_StsMsgResponseSecondPasswordIsVerified* const res =
        static_cast<StsMsgLib::_StsMsgResponseSecondPasswordIsVerified*>(param);
    if (_owner->_state != 0x20000)  // CSS_LOBBY
    {
        JOB_LOG(Log::LT_ERROR, 434, L"[job], invalid cli-session state", L"");
        _lgate->SendDeleteCharacterFail(_owner->_clikey, _slotid, Character::CLIENTSTATE_UNKNOWN, 5);
        return false;
    }
    if (res == nullptr)
    {
        JOB_LOG(Log::LT_ERROR, 441, L"[job], invalid parameter", L"");
        _lgate->SendDeleteCharacterFail(_owner->_clikey, _slotid, Character::CLIENTSTATE_UNKNOWN, 2);
        return false;
    }

    JOB_LOG(Log::LT_DEBUG, 447, L"[job], recv response", NP_RES_FMT, NP_RES_ARGS(res));
    unsigned int const statusCode = res->msgInfo.errInfo.nStatusCode;
    if (statusCode != 200 &&
        (statusCode != 400 ||
         _wcsicmp(L"Success", res->msgInfo.errInfo.pwszReason != nullptr ? res->msgInfo.errInfo.pwszReason : L"null") != 0))
    {
        short reason;
        switch (res->msgInfo.errInfo.nErrorCode)
        {
        case 0xD05:
            reason = 144;
            break;
        case 0xD06:
            reason = 145;
            break;
        case 0xD11:
            reason = 146;
            break;
        case 0xD12:
            reason = 147;
            break;
        default:
            reason = 1;
            break;
        }
        _lgate->SendDeleteCharacterFail(_owner->_clikey, _slotid, Character::CLIENTSTATE_UNKNOWN, reason);
        return false;
    }

    LobbyConfig const* const config = LobbyDaemon::_instance->_config;
    transit(config->_useAccountInventory && config->_checkCharacterGoodsForCharacterDeletion
                ? CHECK_ACCOUNT_INVENTORY_CHARACTER_GOODS
                : TRY_DELETION);
    return true;
}

// 0x47560
bool DeleteCharacterJob::checkSecondPasswordVerifiedExpire()
{
    JOB_LOG(Log::LT_ERROR, 486, L"[job], expired", L"");
    if (_owner->_state != 0x20000)  // CSS_LOBBY
    {
        JOB_LOG(Log::LT_ERROR, 490, L"[job], invalid session state", L"");
        _lgate->SendDeleteCharacterFail(_owner->_clikey, _slotid, Character::CLIENTSTATE_UNKNOWN, 5);
        return false;
    }
    _lgate->SendDeleteCharacterFail(_owner->_clikey, _slotid, Character::CLIENTSTATE_UNKNOWN, 7);
    transit(FIN);
    return true;
}

// 0x47710
bool DeleteCharacterJob::getCharacterGoodsReq()
{
    Character* const pc = _owner->getCharacterInSlot(_slotid);
    if (pc == nullptr)
    {
        JOB_LOG(Log::LT_ERROR, 507, L"[job], no such character", L", slot-id:" SLOTID_FMT, SLOTID_ARGS(_slotid));
        _lgate->SendDeleteCharacterFail(_owner->_clikey, _slotid, Character::CLIENTSTATE_UNKNOWN, 134);
        transit(FIN);
        return true;
    }
    if (!_acciv->SendRetrieveCharacterGoodsCountReq(_tran->Set(this, 170), _owner->_acb._id, pc->_db.pcid))
    {
        JOB_LOG(Log::LT_ERROR, 514, L"[job], get character goods count req fail; unsent", L"");
        _lgate->SendDeleteCharacterFail(_owner->_clikey, _slotid, pc->GetClientState(), 7);
        transit(FIN);
        return true;
    }
    JOB_LOG(Log::LT_DEBUG, 520, L"[job], send get character goods count req ok", L", wid:%d, pcid:0x%I64X",
            pc->_db.belongingWorld, pc->_db.pcid);
    return true;
}

// 0x47ac0
bool DeleteCharacterJob::getCharacterGoodsCountOk(void* param)
{
    _acciv->TRecv(_tran);
    GetCharacterGoodsCountOkParam* const ok = static_cast<GetCharacterGoodsCountOkParam*>(param);
    if (ok == nullptr)
    {
        JOB_LOG(Log::LT_ERROR, 529, L"[job], invalid param on ok ack", L"");
        _lgate->SendDeleteCharacterFail(_owner->_clikey, _slotid, Character::CLIENTSTATE_UNKNOWN, 2);
        transit(FIN);
        return true;
    }
    JOB_LOG(Log::LT_DEBUG, 537, L"[job], ok recv", L", goods-count:%d, taked-goods-count:%d", ok->goodsCount,
            ok->takedGoodsCount);
    if (ok->goodsCount > 0 || ok->takedGoodsCount > 0)
    {
        JOB_LOG(Log::LT_ERROR, 540, L"[job], exist character goods", L", goods-count:%d, taked-goods-count:%d",
                ok->goodsCount, ok->takedGoodsCount);
        _lgate->SendDeleteCharacterFail(_owner->_clikey, _slotid, Character::CLIENTSTATE_UNKNOWN, 142);
        transit(FIN);
        return true;
    }
    transit(TRY_DELETION);
    return true;
}

// 0x47d80
bool DeleteCharacterJob::getCharacterGoodsCountFail(void* param)
{
    _acciv->TRecv(_tran);
    short* const fail = static_cast<short*>(param);
    if (fail == nullptr)
    {
        JOB_LOG(Log::LT_ERROR, 555, L"[job], invalid param on fail ack", L"");
        _lgate->SendDeleteCharacterFail(_owner->_clikey, _slotid, Character::CLIENTSTATE_UNKNOWN, 2);
        transit(FIN);
        return true;
    }
    short const acciveReason = *fail;
    JOB_LOG(Log::LT_DEBUG, 562, L"[job], get character goods count fail recv", L", acciv-reason:%d", acciveReason);
    _lgate->SendDeleteCharacterFail(_owner->_clikey, _slotid, Character::CLIENTSTATE_UNKNOWN,
                                    acciveReason == 3 || acciveReason == 5 ? 7 : 2);
    transit(FIN);
    return true;
}

// 0x47fa0
bool DeleteCharacterJob::getCharacterGoodsCountExpire()
{
    JOB_LOG(Log::LT_ERROR, 584, L"[job], get character goods count expired", L"");
    Character* const pc = _owner->getCharacterInSlot(_slotid);
    if (pc != nullptr)
    {
        _lgate->SendDeleteCharacterFail(_owner->_clikey, _slotid, pc->GetClientState(), 2);
        transit(FIN);
        return true;
    }
    JOB_LOG(Log::LT_ERROR, 588, L"[job], character disappear", L", slot-id:" SLOTID_FMT, SLOTID_ARGS(_slotid));
    _lgate->SendDeleteCharacterFail(_owner->_clikey, _slotid, Character::CLIENTSTATE_UNKNOWN, 2);
    transit(FIN);
    return true;
}

// 0x482b0
bool DeleteCharacterJob::deleteReq()
{
    Character* const pc = _owner->getCharacterInSlot(_slotid);
    if (pc == nullptr)
    {
        JOB_LOG(Log::LT_ERROR, 605, L"[job], no such character", L", slot-id:" SLOTID_FMT, SLOTID_ARGS(_slotid));
        _lgate->SendDeleteCharacterFail(_owner->_clikey, _slotid, Character::CLIENTSTATE_UNKNOWN, 134);
        transit(FIN);
        return true;
    }
    if (_owner->queryLobbyService(pc) != nullptr)
    {
        JOB_LOG(Log::LT_ERROR, 611, L"[job], pc in service-entry", L", slot-id:" SLOTID_FMT, SLOTID_ARGS(_slotid));
        _lgate->SendDeleteCharacterFail(_owner->_clikey, _slotid, Character::CLIENTSTATE_UNKNOWN, 9);
        transit(FIN);
        return true;
    }

    Character::ErrCode const err = pc->TryDeletion();
    if (err != Character::ERR_OK)
    {
        JOB_LOG(Log::LT_ERROR, 619, L"[job], try delete pc fail", L", error:%d, pcid:0x%I64X", err, pc->_db.pcid);
        short reason;
        if (err == Character::ERR_BLOCKED)
            reason = 136;
        else if (err == Character::ERR_STUCK)
            reason = 137;
        else
            reason = 2;
        _lgate->SendDeleteCharacterFail(_owner->_clikey, _slotid, pc->GetClientState(), reason);
        transit(FIN);
        return true;
    }

    if (!_gamed->SendDeleteCharacterReq(_tran->Set(this, 110), pc->_db.pcid, _owner->_externalAccountKey,
                                        _owner->_externalAccountKeySize, _owner->_ipv4))
    {
        JOB_LOG(Log::LT_ERROR, 641, L"[job], send delete character req fail; deletion canceled", L", wid:%d, pcid:0x%I64X",
                pc->_db.belongingWorld, pc->_db.pcid);
        pc->CancelDeletion();
        // The reason 138 comes from the disassembly (0x48689). Hex-Rays did not show it.
        _lgate->SendDeleteCharacterFail(_owner->_clikey, _slotid, pc->GetClientState(), 138);
        transit(FIN);
        return true;
    }
    JOB_LOG(Log::LT_DEBUG, 647, L"[job], send delete character req ok", L", wid:%d, pcid:0x%I64X",
            pc->_db.belongingWorld, pc->_db.pcid);
    return true;
}

// 0x48890
bool DeleteCharacterJob::deleteOk(DeleteCharacterOkParam* param)
{
    JOB_LOG(Log::LT_DEBUG, 657, L"[job], delete ok recv", L", level:%d", param != nullptr ? param->level : 0);
    _gamed->TRecv(_tran);
    _level = param != nullptr ? param->level : 0;
    transit(LobbyDaemon::_instance->_config->_waitCharacterDeletion ? SCHEDULE_DELETION : DIRECT_DELETION);
    return true;
}

// 0x48a10
bool DeleteCharacterJob::deleteFail(void* param)
{
    short* const fail = static_cast<short*>(param);
    short reason = 1;
    if (fail != nullptr)
    {
        reason = *fail;
        JOB_LOG(Log::LT_ERROR, 676, L"[job], delete fail recv", L", reason:%d", reason);
    }
    else
    {
        JOB_CRASH(679, L"== CRASH == [job], delete fail recv; invalid parameter");
    }
    _gamed->TRecv(_tran);

    Character* const pc = _owner->getCharacterInSlot(_slotid);
    if (pc == nullptr)
    {
        JOB_LOG(Log::LT_ERROR, 685, L"[job], character disappear", L", slot-id:" SLOTID_FMT, SLOTID_ARGS(_slotid));
        _lgate->SendDeleteCharacterFail(_owner->_clikey, _slotid, Character::CLIENTSTATE_UNKNOWN, 2);
        transit(FIN);
        return true;
    }

    Character::ErrCode const err = pc->CancelDeletion();
    if (err != Character::ERR_OK)
    {
        JOB_LOG(Log::LT_ERROR, 693, L"[job], cancel deletion fail", L", error:%d, pcid:0x%I64X", err, pc->_db.pcid);
        _lgate->SendDeleteCharacterFail(_owner->_clikey, _slotid, pc->GetClientState(), 2);
        transit(FIN);
        return true;
    }

    JOB_LOG(Log::LT_DEBUG, 699, L"[job], cancel deletion ok", L", pcid:0x%I64X", pc->_db.pcid);
    short mapped;
    switch (reason)
    {
    case 28:
        mapped = 139;
        break;
    case 29:
        mapped = 140;
        break;
    case 30:
        mapped = 141;
        break;
    case 31:
        mapped = 148;
        break;
    case 32:
        mapped = 149;
        break;
    default:
        mapped = 2;
        break;
    }
    _lgate->SendDeleteCharacterFail(_owner->_clikey, _slotid, pc->GetClientState(), mapped);
    transit(FIN);
    return true;
}

// 0x49090
bool DeleteCharacterJob::deleteExpire()
{
    JOB_LOG(Log::LT_ERROR, 733, L"[job], delete expired", L"");
    Character* const pc = _owner->getCharacterInSlot(_slotid);
    if (pc != nullptr)
    {
        _lgate->SendDeleteCharacterFail(_owner->_clikey, _slotid, pc->GetClientState(), 2);
        transit(FIN);
        return true;
    }
    JOB_LOG(Log::LT_ERROR, 737, L"[job], character disappear", L", slot-id:" SLOTID_FMT, SLOTID_ARGS(_slotid));
    _lgate->SendDeleteCharacterFail(_owner->_clikey, _slotid, Character::CLIENTSTATE_UNKNOWN, 2);
    transit(FIN);
    return true;
}

// 0x493a0
bool DeleteCharacterJob::directDelete()
{
    Character* const pc = _owner->getCharacterInSlot(_slotid);
    if (pc == nullptr)
    {
        JOB_LOG(Log::LT_ERROR, 753, L"[job], character disappear", L", slot-id:" SLOTID_FMT, SLOTID_ARGS(_slotid));
        _lgate->SendDeleteCharacterFail(_owner->_clikey, _slotid, Character::CLIENTSTATE_UNKNOWN, 2);
        transit(FIN);
        return true;
    }

    Character::ErrCode const err = pc->FinishDeletion(0);
    if (err != Character::ERR_OK)
    {
        JOB_LOG(Log::LT_ERROR, 761, L"[job], finish deletion fail", L", error:%d, pcid:0x%I64X", err, pc->_db.pcid);
        _lgate->SendDeleteCharacterFail(_owner->_clikey, _slotid, pc->GetClientState(), 2);
        transit(FIN);
        return true;
    }

    _owner->removeCharacter(pc->_db.pcid);
    JOB_LOG(Log::LT_DEBUG, 769, L"[job], delete ok", L", pcid:0x%I64X", pc->_db.pcid);
    _lgate->SendDeleteCharacterOk(_owner->_clikey, _slotid, 0, 0);
    // LIFT: the original calls the Character destructor (0x33c80) and then frees the object. Character.h has no
    // destructor declaration (adding one is not an append). This is the destructor body by hand.
    if (pc->_db.showcase != nullptr)
    {
        Memory::_Manager[2]->Free(pc->_db.showcase, L"Character.cpp", 51);
        pc->_db.showcase = nullptr;
    }
    Memory::_Manager[2]->Free(pc, kFile, 773);
    transit(FIN);
    return true;
}

// 0x49770
bool DeleteCharacterJob::scheduleDelete()
{
    Character* const pc = _owner->getCharacterInSlot(_slotid);
    if (pc == nullptr)
    {
        JOB_LOG(Log::LT_ERROR, 782, L"[job], character disappear", L", slot-id:" SLOTID_FMT, SLOTID_ARGS(_slotid));
        _lgate->SendDeleteCharacterFail(_owner->_clikey, _slotid, Character::CLIENTSTATE_UNKNOWN, 2);
        transit(FIN);
        return true;
    }

    LobbyConfig const* const config = LobbyDaemon::_instance->_config;
    long const remain = pc->_db.jumpingCharacterState == 1 || _level < config->_longTermWaitCharacterDeletionCriteriaLevel
                            ? config->_shortTermWaitCharacterDeletionTime
                            : config->_longTermWaitCharacterDeletionTime;
    Character::ErrCode const err = pc->FinishDeletion(remain);
    if (err != Character::ERR_OK)
    {
        JOB_LOG(Log::LT_ERROR, 804, L"[job], finish deletion fail", L", error:%d, pcid:0x%I64X", err, pc->_db.pcid);
        _lgate->SendDeleteCharacterFail(_owner->_clikey, _slotid, pc->GetClientState(), 2);
        transit(FIN);
        return true;
    }

    // The original format has no comma before "pcid".
    JOB_LOG(Log::LT_DEBUG, 810, L"[job], wait delete ok", L", remain:%d(sec)pcid:0x%I64X", remain, pc->_db.pcid);
    _lgate->SendDeleteCharacterOk(_owner->_clikey, _slotid, 1, remain);
    transit(FIN);
    return true;
}
