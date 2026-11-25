// BindCharacterSlotJob.obj (LobbyDaemon PDB, 2019 + PDB). Lifted from the pseudocode with PDB types.
#include <new>
#include <wchar.h>
#include <winsock2.h>
#include <windows.h>
#include "BindCharacterSlotJob.h"
#include "Character.h"
#include "CliSession.h"
#include "LiftStub.h"
#include "LobbyDaemon.h"
#include "LobbyGateChannel.h"
#include "LobbyJobParams.h"
#include "Log.h"
#include "Memory.h"
#include "MemoryManager.h"
#include "NPServiceChannel.h"

namespace StsMsgLib
{
// PDB StsMsgLib::_StsMsgResponseSlotGetSlot (sizeof 0xA0). The PDB type of guidSlotId is _GUID.
struct _StsMsgResponseSlotGetSlot : public _StsMsgResponse
{
    struct _SlotData
    {
        long long serviceId;
    };
    id128 guidSlotId;
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
static_assert(offsetof(_StsMsgResponseSlotGetSlot, slotData) == 0x80, "_StsMsgResponseSlotGetSlot::slotData");
static_assert(offsetof(_StsMsgResponseSlotGetSlot, tRegistered) == 0x98, "_StsMsgResponseSlotGetSlot::tRegistered");
}  // namespace StsMsgLib

static wchar_t const kFile[] = L"BindCharacterSlotJob.cpp";

// The log suffix of all LobbyJob logs. The original reads the owner state 2 times (HIWORD and LOWORD).
#define JOB_LOG(logType, line, msg, fmt, ...)                                                                          \
    Log::Write(logType, kFile, line, msg L", tid:0x%I64X, type:%d, state:%d, cli-key:0x%I64X, cli-state:%d.%d" fmt,   \
               this != nullptr ? _id : 0, this != nullptr ? GetDefinition()->type : -1,                            \
               this != nullptr ? _state : -1, this != nullptr && _owner != nullptr ? _owner->_clikey : 0,          \
               HIWORD(this != nullptr && _owner != nullptr ? _owner->_state : 0),                                  \
               LOWORD(this != nullptr && _owner != nullptr ? _owner->_state : 0), ##__VA_ARGS__)

#define GATE_WID(lg) ((lg) != nullptr ? ((lg)->_rawChannel != nullptr ? static_cast<short>((lg)->_rawChannel->GetId()) : 0) : 0)

#define GUID_ARGS(g)                                                                                                 \
    (g).guid.id1, (g).guid.id2, (g).guid.id3, (g).guid.id4[0], (g).guid.id4[1], (g).guid.id4[2], (g).guid.id4[3],    \
        (g).guid.id4[4], (g).guid.id4[5], (g).guid.id4[6], (g).guid.id4[7]

#define SLOT_FMT L"%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X"

// The member suffix of the init and bind logs.
#define BIND_LOG(logType, line, msg)                                                                                 \
    JOB_LOG(logType, line, msg, L", gate-wid:%d, slot-id:" SLOT_FMT L", pcid:0x%I64X", GATE_WID(_lgate),             \
            GUID_ARGS(_slotId), _pcId)

// PDB enum ECliSessionState (CliSession.h has no copy yet): CSS_LOBBY = 0x20000.

namespace
{
// The original table has no entry for GET_SLOT (1).
LobbyJobStateDef const StateDef[] = {{0, L"INIT"}, {2, L"BIND_CHARACTER_SLOT"}, {3, L"FIN"}};  // 0x12e400
}

LobbyJobDef BindCharacterSlotJob::_def = {42, StateDef, 3, L"BindCharacterSlotJob"};  // 0x202000
// LIFT: BindCharacterSlotJob::_pool has no definition. The LobbyDaemon ObjectPool module is not in lift_lobbydaemon
// (see CliSession.cpp).

// 0x16e90
LobbyJobDef const* BindCharacterSlotJob::GetDefinition() const
{
    return &_def;
}

// 0x16ea0
// LIFT: Not done. The body calls _pool.Checkin. ObjPool is not in lift_lobbydaemon.
void BindCharacterSlotJob::deallocate_me(void*, wchar_t const*, int)
{
    LIFT_STUB(0x16ea0);
}

// 0x16ef0
// The original constructs a job on the stack (null owner) and returns its vfptr. It does not run the destructor.
void* BindCharacterSlotJob::_vtbl()
{
    char buf[sizeof(BindCharacterSlotJob)];
    BindCharacterSlotJob* job = ::new (buf) BindCharacterSlotJob(nullptr);
    return *reinterpret_cast<void**>(job);
}

// 0x16f70 (scalar deleting destructor)
BindCharacterSlotJob::~BindCharacterSlotJob()
{
    if (_lgate != nullptr)
        _lgate->removeReferenceCount(kFile, 66);
}

// 0x16fc0
bool BindCharacterSlotJob::work(int task, void* param)
{
    bool result = false;
    if (_state == INIT && task == 33)
    {
        result = init(param);
        task = 0;
    }
    if (_state == GET_SLOT)
    {
        if (task == 0)
        {
            result = reqGetSlot();
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
    if (_state == BIND_CHARACTER_SLOT && task == 0)
        return bindCharacterSlot();
    return result;
}

// 0x17050
bool BindCharacterSlotJob::init(void* param)
{
    BindCharacterSlotReqParam* const p = static_cast<BindCharacterSlotReqParam*>(param);
    if (p == nullptr || p->lgate == nullptr || (p->slotid.id[0] == 0 && p->slotid.id[1] == 0) || p->pcId == 0)
    {
        JOB_LOG(Log::LT_ERROR, 109, L"[job], invalid param", L"");
        transit(FIN);
        return true;
    }

    _lgate = p->lgate;
    _slotId = p->slotid;
    _pcId = p->pcId;
    _lgate->addReferenceCount(false, kFile, 121);

    short reason;
    Character* character;
    if (_owner->_state != 0x20000)  // CSS_LOBBY
    {
        BIND_LOG(Log::LT_ERROR, 125, L"[job], cli-session not in lobby");
        reason = 5;
    }
    else if ((character = _owner->getCharacter(_pcId)) == nullptr)
    {
        BIND_LOG(Log::LT_ERROR, 134, L"[job], no such character");
        reason = 164;
    }
    else if (character->_db.slotid.id[0] != 0 || character->_db.slotid.id[1] != 0)
    {
        BIND_LOG(Log::LT_ERROR, 141, L"[job], already bind slot");
        reason = 165;
    }
    else
    {
        BIND_LOG(Log::LT_DEBUG, 147, L"[job], init ok");
        transit(GET_SLOT);
        return true;
    }
    _lgate->SendBindCharacterSlotFail(_owner->_clikey, _slotId, _pcId, reason);
    transit(FIN);
    return true;
}

// 0x17840
// The original does not check the game service channel for null here.
bool BindCharacterSlotJob::reqGetSlot()
{
    NPGameServiceChannel* const gs = LobbyDaemon::_instance->_npServchmgr->_gameServChannel;
    NPLobbyJobTransaction* const tr = new (Memory::_Manager[2]->Alloc(sizeof(NPLobbyJobTransaction), kFile, 159))
        NPLobbyJobTransaction;
    if (gs->SendRequestSlotGetSlot(tr->Set(this, 38), _owner->_acb._id, _slotId))
        return true;
    JOB_LOG(Log::LT_ERROR, 161, L"[job], req get slot fail; unsent", L"");
    _lgate->SendBindCharacterSlotFail(_owner->_clikey, _slotId, _pcId, 2);
    // LIFT: the original calls the scalar deleting destructor (flag 1) and then Free. Its operator delete is empty.
    tr->~NPLobbyJobTransaction();
    Memory::_Manager[2]->Free(tr, kFile, 163);
    return false;
}

// 0x179e0
bool BindCharacterSlotJob::responseGetSlot(void* param)
{
    if (_owner->_state != 0x20000)  // CSS_LOBBY
    {
        JOB_LOG(Log::LT_ERROR, 172, L"[job], cli-session not in lobby", L"");
        _lgate->SendBindCharacterSlotFail(_owner->_clikey, _slotId, _pcId, 5);
        transit(FIN);
        return true;
    }
    StsMsgLib::_StsMsgResponseSlotGetSlot* const res = static_cast<StsMsgLib::_StsMsgResponseSlotGetSlot*>(param);
    if (res == nullptr)
    {
        JOB_LOG(Log::LT_ERROR, 179, L"[job], null param", L"");
        _lgate->SendBindCharacterSlotFail(_owner->_clikey, _slotId, _pcId, 2);
        transit(FIN);
        return true;
    }

    short reason;
    unsigned int const statusCode = res->msgInfo.errInfo.nStatusCode;
    wchar_t const* const npReason = res->msgInfo.errInfo.pwszReason;
    if (!(statusCode == 200 || (statusCode == 400 && _wcsicmp(L"Success", npReason != nullptr ? npReason : L"null") == 0)))
    {
        JOB_LOG(Log::LT_ERROR, 188, L"[job], get slot fail",
                L",np-tid:%u, cmd:%d, type:%d, status-code:%u, reason:%s, error-code:%d", res->GetTransactionId(),
                res->GetCommand(), res->GetMessageType(), res->msgInfo.errInfo.nStatusCode,
                res->msgInfo.errInfo.pwszReason != nullptr ? res->msgInfo.errInfo.pwszReason : L"null",
                res->msgInfo.errInfo.nErrorCode);
        reason = 163;
    }
    else if (res->guidSlotId.id[0] != _slotId.id[0] || res->guidSlotId.id[1] != _slotId.id[1])
    {
        JOB_LOG(Log::LT_ERROR, 196, L"[job], slot-id mismatch", L",recv:slot-id:" SLOT_FMT, GUID_ARGS(res->guidSlotId));
        reason = 2;
    }
    else if (wcscmp(res->pwszSlotType, L"char") == 0)
    {
        JOB_LOG(Log::LT_DEBUG, 209, L"[job], get slot ok", L", slot-id:" SLOT_FMT, GUID_ARGS(res->guidSlotId));
        transit(BIND_CHARACTER_SLOT);
        return true;
    }
    else
    {
        JOB_LOG(Log::LT_ERROR, 203, L"[job], invalid slot type", L", slot-type:%s", res->pwszSlotType);
        reason = 162;
    }
    _lgate->SendBindCharacterSlotFail(_owner->_clikey, _slotId, _pcId, reason);
    transit(FIN);
    return true;
}

// 0x17ff0
bool BindCharacterSlotJob::expireGetSlot()
{
    JOB_LOG(Log::LT_ERROR, 217, L"[job], get slot expired", L"");
    _lgate->SendBindCharacterSlotFail(_owner->_clikey, _slotId, _pcId, 2);
    transit(FIN);
    return true;
}

// 0x18100
bool BindCharacterSlotJob::bindCharacterSlot()
{
    if (_owner->_state != 0x20000)  // CSS_LOBBY
    {
        // The original message has no ", " before "cli-session not in lobby".
        JOB_LOG(Log::LT_ERROR, 229, L"[job], bind character slot fail;",
                L"cli-session not in lobby,gate-wid:%d, slot-id:" SLOT_FMT L", pcid:0x%I64X", GATE_WID(_lgate),
                GUID_ARGS(_slotId), _pcId);
        _lgate->SendBindCharacterSlotFail(_owner->_clikey, _slotId, _pcId, 5);
    }
    else if (_owner->BindCharacterSlot(_pcId, _slotId))
    {
        BIND_LOG(Log::LT_DEBUG, 261, L"[job], bind character slot ok");
        id128 slot = _slotId;
        _lgate->Send("hqoq", 58, _owner->_clikey, &slot, _pcId);
    }
    else
    {
        short reason;
        switch (TLobbyError)
        {
        case LOBERR_DB_FAIL:
            reason = 3;
            break;
        case LOBERR_INVALID_PARAMETER:
            reason = 6;
            break;
        case LOBERR_NO_SUCH_CHARACTER:
            reason = 164;
            break;
        case LOBERR_NOT_FOUND:
            reason = 3;
            break;
        default:
            reason = 1;
            break;
        }
        _lgate->SendBindCharacterSlotFail(_owner->_clikey, _slotId, _pcId, reason);
    }
    transit(FIN);
    return true;
}
