// CancelWaitCharacterDeletionJob.obj (LobbyDaemon PDB, 2019 + PDB). Lifted from the pseudocode with PDB types.
#include <new>
#include <wchar.h>
#include <winsock2.h>
#include <windows.h>
#include "CancelWaitCharacterDeletionJob.h"
#include "AlertSender.h"
#include "Character.h"
#include "CliSession.h"
#include "GameWorld.h"
#include "GamedChannel.h"
#include "LiftStub.h"
#include "LobbyDaemon.h"
#include "LobbyGateChannel.h"
#include "LobbyJobParams.h"
#include "Log.h"
#include "Memory.h"
#include "MemoryManager.h"
#include "TransactionChannel.h"

// LIFT: PDB public LobbyErrorDesc (.data 0003:2032). LobbyGamePacketHandler.cpp has the definition (placeholder).
extern wchar_t const* LobbyErrorDesc[28];

static wchar_t const kFile[] = L"CancelWaitCharacterDeletionJob.cpp";

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

// PDB enum CliSession state: CSS_LOBBY = 0x20000.

namespace
{
LobbyJobStateDef const StateDef[] = {{0, L"INIT"}, {1, L"RESTORE_LOBBY"}, {2, L"RESTORE_GAMEWORLD"}, {3, L"FIN"}};  // 0x12e3c0
}

LobbyJobDef CancelWaitCharacterDeletionJob::_def = {7, StateDef, 3, L"CancelWaitCharacterDeletionJob"};  // 0x201fe0
// LIFT: CancelWaitCharacterDeletionJob::_pool (0x203d30) has no definition. The LobbyDaemon ObjectPool module is not
// in lift_lobbydaemon (see CliSession.cpp).

// 0x18890
LobbyJobDef const* CancelWaitCharacterDeletionJob::GetDefinition() const
{
    return &_def;
}

// 0x188a0
// LIFT: Not done. The body calls _pool.Checkin. ObjPool is not in lift_lobbydaemon.
void CancelWaitCharacterDeletionJob::deallocate_me(void*, wchar_t const*, int)
{
    LIFT_STUB(0x188a0);
}

// 0x188f0
// The original constructs a job on the stack (null owner) and returns its vfptr. It does not run the destructor.
void* CancelWaitCharacterDeletionJob::_vtbl()
{
    char buf[sizeof(CancelWaitCharacterDeletionJob)];
    CancelWaitCharacterDeletionJob* job = ::new (buf) CancelWaitCharacterDeletionJob(nullptr);
    return *reinterpret_cast<void**>(job);
}

// 0x18970
CancelWaitCharacterDeletionJob::CancelWaitCharacterDeletionJob(CliSession* owner)
    : CliSessionJob(owner), _tran(nullptr), _lgate(nullptr), _gamed(nullptr)
{
    _slotid.id[0] = 0;
    _slotid.id[1] = 0;
}

// 0x189e0 (scalar deleting destructor 0x189c0)
CancelWaitCharacterDeletionJob::~CancelWaitCharacterDeletionJob()
{
    if (_tran != nullptr)
    {
        _tran->removeReferenceCount(kFile, 71);
        _tran = nullptr;
    }
    if (_lgate != nullptr)
    {
        _lgate->removeReferenceCount(kFile, 75);
        _lgate = nullptr;
    }
    if (_gamed != nullptr)
    {
        _gamed->removeReferenceCount(kFile, 79);
        _gamed = nullptr;
    }
}

// 0x18a80
// Tasks: 12 TASK_CANCEL_WAIT_CHARACTER_DELETION_REQ, 111 TASK_RESTORE_CHARACTER_OK, 112 TASK_RESTORE_CHARACTER_FAIL,
// 113 TASK_RESTORE_CHARACTER_EXPIRE.
bool CancelWaitCharacterDeletionJob::work(int task, void* param)
{
    bool result = false;
    if (_state == INIT && task == 12)
    {
        result = init(static_cast<CancelWaitCharacterDeletionReqParam*>(param));
        task = 0;
    }
    if (_state == RESTORE_LOBBY && task == 0)
        result = restore();
    if (_state == RESTORE_GAMEWORLD)
    {
        if (task == 0)
            return restoreCharacterReq();
        else if (task == 111)
            return restoreCharacterOk();
        else if (task == 112)
            return restoreCharacterFail(static_cast<short*>(param));
        else if (task == 113)
            return restoreCharacterExpire();
    }
    return result;
}

// 0x18b40
bool CancelWaitCharacterDeletionJob::init(CancelWaitCharacterDeletionReqParam* param)
{
    if (_owner->_state != 0x20000)  // CSS_LOBBY
    {
        JOB_LOG(Log::LT_ERROR, 128, L"[job], cli-session not in lobby", L"");
        transit(FIN);
        return true;
    }
    if (param == nullptr)
    {
        JOB_CRASH(134, L"== CRASH == [job], invalid task parameter");
        transit(FIN);
        return true;
    }
    if (param->lgate == nullptr || (param->slotid.id[0] == ID128_ID_ZERO.id[0] && param->slotid.id[1] == ID128_ID_ZERO.id[1]))
    {
        JOB_LOG(Log::LT_ERROR, 147, L"[job], invalid parameter", L", gate-wid:%d, slot-id:" SLOTID_FMT,
                GATE_WID(param->lgate), SLOTID_ARGS(param->slotid));
        if (param->lgate != nullptr)
            param->lgate->SendCancelWaitCharacterDeletionFail(_owner->_clikey, param->slotid,
                                                              Character::CLIENTSTATE_UNKNOWN, 6);
        transit(FIN);
        return true;
    }

    Character* pc = _owner->getCharacterInSlot(param->slotid);
    if (pc == nullptr)
    {
        JOB_LOG(Log::LT_ERROR, 156, L"[job], no such character", L", gate-wid:%d, slot-id:" SLOTID_FMT,
                GATE_WID(param->lgate), SLOTID_ARGS(param->slotid));
        param->lgate->SendCancelWaitCharacterDeletionFail(_owner->_clikey, param->slotid,
                                                          Character::CLIENTSTATE_UNKNOWN, 150);  // INVALID_SLOT
        transit(FIN);
        return true;
    }

    GameWorld* world = LobbyDaemon::_instance->_gameWorldRegistry->Get(pc->_db.belongingWorld);
    if (world == nullptr)
    {
        JOB_LOG(Log::LT_ERROR, 164, L"[job], world not registered", L", wid:%d, gate-wid:%d, slot-id:" SLOTID_FMT,
                pc->_db.belongingWorld, GATE_WID(param->lgate), SLOTID_ARGS(param->slotid));
        param->lgate->SendCancelWaitCharacterDeletionFail(_owner->_clikey, param->slotid,
                                                          Character::CLIENTSTATE_UNKNOWN, 154);  // WORLD_NOT_AVAILABLE
        transit(FIN);
        return true;
    }

    if (!world->PermitCharacterManagement(_owner, false))
    {
        int const error = TLobbyError;
        JOB_LOG(Log::LT_ERROR, 173, L"[job], world denied", L", error:%s, wid:%d, gate-wid:%d, slot-id:" SLOTID_FMT,
                static_cast<unsigned int>(error) >= 28 ? L"LOBERR_UNDEFINED" : LobbyErrorDesc[error],
                pc->_db.belongingWorld, GATE_WID(param->lgate), SLOTID_ARGS(param->slotid));
        short reason;
        switch (error)
        {
        case LOBERR_GAMEWORLD_NOT_USABLE:
            reason = 154;  // WORLD_NOT_AVAILABLE
            break;
        case LOBERR_GAMEWORLD_CHARACTER_MANAGEMENT_NOT_ALLOWED:
            reason = 155;  // CANCEL_NOT_AVAILABLE
            break;
        default:
            reason = 2;
            break;
        }
        param->lgate->SendCancelWaitCharacterDeletionFail(_owner->_clikey, param->slotid,
                                                          Character::CLIENTSTATE_UNKNOWN, reason);
        transit(FIN);
        return true;
    }

    _tran = new (Memory::_Manager[2]->Alloc(sizeof(LobbyJobTransaction), kFile, 193)) LobbyJobTransaction;
    _lgate = param->lgate;
    _slotid = param->slotid;
    _lgate->addReferenceCount(false, kFile, 197);
    JOB_LOG(Log::LT_DEBUG, 199, L"[job], init ok", L", gate-wid:%d, slot-id:" SLOTID_FMT, GATE_WID(param->lgate),
            SLOTID_ARGS(param->slotid));
    transit(RESTORE_LOBBY);
    return true;
}

// 0x196f0
bool CancelWaitCharacterDeletionJob::restore()
{
    Character* pc = _owner->getCharacterInSlot(_slotid);
    if (pc == nullptr)
    {
        JOB_LOG(Log::LT_ERROR, 210, L"[job], no such character", L", slot-id:" SLOTID_FMT, SLOTID_ARGS(_slotid));
        _lgate->SendCancelWaitCharacterDeletionFail(_owner->_clikey, _slotid, Character::CLIENTSTATE_UNKNOWN,
                                                    150);  // INVALID_SLOT
        transit(FIN);
        return true;
    }

    Character::ErrCode const err = pc->TryRestore();
    if (err != Character::ERR_OK)
    {
        JOB_LOG(Log::LT_ERROR, 219, L"[job], try restore pc fail", L", error:%d, pcid:0x%I64X", err, pc->_db.pcid);
        switch (err)
        {
        case Character::ERR_BLOCKED:
            _lgate->SendCancelWaitCharacterDeletionFail(_owner->_clikey, _slotid, Character::CLIENTSTATE_UNKNOWN,
                                                        152);  // BLOCKED
            break;
        case Character::ERR_STUCK:
            _lgate->SendCancelWaitCharacterDeletionFail(_owner->_clikey, _slotid, Character::CLIENTSTATE_UNKNOWN,
                                                        153);  // STUCK
            break;
        default:
            _lgate->SendCancelWaitCharacterDeletionFail(_owner->_clikey, _slotid, Character::CLIENTSTATE_UNKNOWN, 2);
            break;
        }
        transit(FIN);
        return true;
    }

    JOB_LOG(Log::LT_DEBUG, 237, L"[job], try restore ok", L", pcid:0x%I64X, slot-id:" SLOTID_FMT, pc->_db.pcid,
            SLOTID_ARGS(_slotid));
    transit(RESTORE_GAMEWORLD);
    return true;
}

// 0x19ad0
bool CancelWaitCharacterDeletionJob::restoreCharacterReq()
{
    Character* pc = _owner->getCharacterInSlot(_slotid);
    if (pc == nullptr)
    {
        JOB_LOG(Log::LT_ERROR, 250, L"[job], no such character", L", slot-id:" SLOTID_FMT, SLOTID_ARGS(_slotid));
        _lgate->SendCancelWaitCharacterDeletionFail(_owner->_clikey, _slotid, Character::CLIENTSTATE_UNKNOWN,
                                                    150);  // INVALID_SLOT
        transit(FIN);
        return true;
    }

    _gamed = LobbyDaemon::_instance->_gamedchmgr->Acquire(pc->_db.belongingWorld);
    if (_gamed == nullptr)
    {
        JOB_LOG(Log::LT_ERROR, 259, L"[job], world not available", L", wid:%d", pc->_db.belongingWorld);
        _lgate->SendCancelWaitCharacterDeletionFail(_owner->_clikey, _slotid, pc->GetClientState(),
                                                    154);  // WORLD_NOT_AVAILABLE
        transit(FIN);
        return true;
    }

    if (!_gamed->SendRestoreCharacterReq(_tran->Set(this, 113), pc->_db.pcid))
    {
        JOB_LOG(Log::LT_ERROR, 267, L"[job], send restore character req fail", L", wid:%d, pcid:0x%I64X",
                pc->_db.belongingWorld, pc->_db.pcid);
        _lgate->SendCancelWaitCharacterDeletionFail(_owner->_clikey, _slotid, pc->GetClientState(),
                                                    154);  // WORLD_NOT_AVAILABLE
        transit(FIN);
        return true;
    }

    JOB_LOG(Log::LT_DEBUG, 273, L"[job], send restore character req ok", L", wid:%d, pcid:0x%I64X",
            pc->_db.belongingWorld, pc->_db.pcid);
    return true;
}

// 0x19f30
bool CancelWaitCharacterDeletionJob::restoreCharacterOk()
{
    JOB_LOG(Log::LT_DEBUG, 279, L"[job], restore ok recv", L"");
    _gamed->TRecv(_tran);

    Character* pc = _owner->getCharacterInSlot(_slotid);
    if (pc == nullptr)
    {
        JOB_LOG(Log::LT_ERROR, 286, L"[job], pc disappears", L", slot-id:" SLOTID_FMT, SLOTID_ARGS(_slotid));
        _lgate->SendCancelWaitCharacterDeletionFail(_owner->_clikey, _slotid, Character::CLIENTSTATE_UNKNOWN,
                                                    150);  // INVALID_SLOT
        transit(FIN);
        return true;
    }

    Character::ErrCode const err = pc->FinishRestore();
    if (err != Character::ERR_OK)
    {
        JOB_LOG(Log::LT_ERROR, 295, L"[job], finish restore fail", L", error:%d, pcid:0x%I64X", err, pc->_db.pcid);
        _lgate->SendCancelWaitCharacterDeletionFail(_owner->_clikey, _slotid, pc->GetClientState(), 2);
    }
    else
    {
        JOB_LOG(Log::LT_DEBUG, 301, L"[job], finish restore ok", L", pcid:0x%I64X", pc->_db.pcid);
        _lgate->SendCancelWaitCharacterDeletionOk(_owner->_clikey, _slotid);
    }
    transit(FIN);
    return true;
}

// 0x1a3b0
bool CancelWaitCharacterDeletionJob::restoreCharacterFail(short* reason)
{
    _gamed->TRecv(_tran);

    Character* pc = _owner->getCharacterInSlot(_slotid);
    if (pc == nullptr)
    {
        JOB_LOG(Log::LT_ERROR, 316, L"[job], pc disappears", L", slot-id:" SLOTID_FMT, SLOTID_ARGS(_slotid));
        _lgate->SendCancelWaitCharacterDeletionFail(_owner->_clikey, _slotid, Character::CLIENTSTATE_UNKNOWN,
                                                    150);  // INVALID_SLOT
        transit(FIN);
        return true;
    }

    if (reason == nullptr)
    {
        JOB_CRASH(324, L"== CRASH == [job], invalid parameter");
        _lgate->SendCancelWaitCharacterDeletionFail(_owner->_clikey, _slotid, pc->GetClientState(), 2);
        transit(FIN);
        return true;
    }

    JOB_LOG(Log::LT_DEBUG, 330, L"[job], restore character fail recv", L", reason:%d", *reason);
    _lgate->SendCancelWaitCharacterDeletionFail(_owner->_clikey, _slotid, pc->GetClientState(), 2);
    transit(FIN);
    return true;
}

// 0x1a860
// The expired transaction is out of the manager. This handler does not call TRecv.
bool CancelWaitCharacterDeletionJob::restoreCharacterExpire()
{
    JOB_LOG(Log::LT_ERROR, 352, L"[job], restore character req expired", L"");

    Character* pc = _owner->getCharacterInSlot(_slotid);
    if (pc == nullptr)
    {
        JOB_LOG(Log::LT_ERROR, 357, L"[job], pc disappears", L", slot-id:" SLOTID_FMT, SLOTID_ARGS(_slotid));
        _lgate->SendCancelWaitCharacterDeletionFail(_owner->_clikey, _slotid, Character::CLIENTSTATE_UNKNOWN,
                                                    150);  // INVALID_SLOT
        transit(FIN);
        return true;
    }

    _lgate->SendCancelWaitCharacterDeletionFail(_owner->_clikey, _slotid, pc->GetClientState(), 2);
    transit(FIN);
    return true;
}
