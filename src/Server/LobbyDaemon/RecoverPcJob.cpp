// RecoverPcJob.obj (LobbyDaemon PDB, 2019 + PDB). Lifted from the pseudocode with PDB types.
#include <new>
#include <wchar.h>
#include <winsock2.h>
#include <windows.h>
#include "RecoverPcJob.h"
#include "AlertSender.h"
#include "Character.h"
#include "CliSession.h"
#include "GameWorld.h"
#include "GamedChannel.h"
#include "LiftStub.h"
#include "LobbyDaemon.h"
#include "LobbyGateChannel.h"
#include "Log.h"
#include "Memory.h"
#include "MemoryManager.h"
#include "TransactionChannel.h"

static wchar_t const kFile[] = L"RecoverPcJob.cpp";

// The log suffix of all LobbyJob logs. The original reads the owner state 2 times (HIWORD and LOWORD).
#define JOB_LOG(logType, line, msg, fmt, ...)                                                                          \
    Log::Write(logType, kFile, line, msg L", tid:0x%I64X, type:%d, state:%d, cli-key:0x%I64X, cli-state:%d.%d" fmt,   \
               this != nullptr ? _id : 0, this != nullptr ? GetDefinition()->type : -1,                            \
               this != nullptr ? _state : -1, this != nullptr && _owner != nullptr ? _owner->_clikey : 0,          \
               HIWORD(this != nullptr && _owner != nullptr ? _owner->_state : 0),                                  \
               LOWORD(this != nullptr && _owner != nullptr ? _owner->_state : 0), ##__VA_ARGS__)

// The slot-id format is "%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X".
#define SLOTID_ARGS(s)                                                                                                 \
    (s).guid.id1, (s).guid.id2, (s).guid.id3, (s).guid.id4[0], (s).guid.id4[1], (s).guid.id4[2], (s).guid.id4[3],     \
        (s).guid.id4[4], (s).guid.id4[5], (s).guid.id4[6], (s).guid.id4[7]

// LobbyErrorDesc: PDB public (.data 0003:2032). LobbyGamePacketHandler.cpp has the placeholder definition.
extern wchar_t const* LobbyErrorDesc[28];

// PDB enum ECliSessionState (CliSession.h has no copy yet): CSS_LOBBY = 0x20000, CSS_FIN = 0x60000.

namespace
{
LobbyJobStateDef const StateDef[] = {{0, L"INIT"}, {1, L"RESTORE_GAMEWORLD_PC"}, {2, L"FIN"}};  // 0x12de10
}

LobbyJobDef RecoverPcJob::_def = {20, StateDef, 2, L"RecoverPcJob"};  // 0x201a98
// LIFT: RecoverPcJob::_pool (0x204ba0) has no definition. The LobbyDaemon ObjectPool module is not in lift_lobbydaemon
// (see CliSession.cpp).

// 0x64e50
LobbyJobDef const* RecoverPcJob::GetDefinition() const
{
    return &_def;
}

// 0x64e60
// LIFT: Not done. The body calls _pool.Checkin. ObjPool is not in lift_lobbydaemon.
void RecoverPcJob::deallocate_me(void*, wchar_t const*, int)
{
    LIFT_STUB(0x64e60);
}

// 0x64eb0
// The original constructs a job on the stack (null owner) and returns its vfptr. It does not run the destructor.
void* RecoverPcJob::_vtbl()
{
    char buf[sizeof(RecoverPcJob)];
    RecoverPcJob* job = ::new (buf) RecoverPcJob(nullptr);
    return *reinterpret_cast<void**>(job);
}

// 0x64f30
RecoverPcJob::RecoverPcJob(CliSession* owner) : CliSessionJob(owner), _tran(nullptr), _lgate(nullptr), _gamed(nullptr), _pcid(0)
{
    _slotid.id[0] = 0;
    _slotid.id[1] = 0;
}

// 0x64fa0 (scalar deleting destructor 0x64f80)
RecoverPcJob::~RecoverPcJob()
{
    if (_tran != nullptr)
    {
        _tran->removeReferenceCount(kFile, 74);
        _tran = nullptr;
    }
    if (_lgate != nullptr)
    {
        _lgate->removeReferenceCount(kFile, 78);
        _lgate = nullptr;
    }
    if (_gamed != nullptr)
    {
        _gamed->removeReferenceCount(kFile, 82);
        _gamed = nullptr;
    }
}

// 0x65040
bool RecoverPcJob::Initialize(LobbyGateChannel* lgate, id128 const& slotid)
{
    if (lgate == nullptr || (slotid.id[0] == ID128_ID_ZERO.id[0] && slotid.id[1] == ID128_ID_ZERO.id[1]))
    {
        JOB_LOG(Log::LT_ERROR, 90, L"[job], invalid parameter",
                L", lgate:%p, slot-id:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X", lgate, SLOTID_ARGS(slotid));
        return false;
    }
    _lgate = lgate;
    _slotid = slotid;
    lgate->addReferenceCount(false, kFile, 97);
    return true;
}

// 0x65260
bool RecoverPcJob::work(int task, void* param)
{
    bool result = false;
    if (_state == INIT && task == 18)
    {
        result = init();
        task = 0;
    }
    if (_state == RESTORE_GAMEWORLD_PC)
    {
        if (task == 0)
            return restoreGameWorldPcReq();
        else if (task == 111)
            return restoreGameWorldPcOk();
        else if (task == 112)
            return restoreGameWorldPcFail(static_cast<short*>(param));
        else if (task == 113)
            return restoreGameWorldPcExpired();
    }
    return result;
}

// 0x652f0
bool RecoverPcJob::init()
{
    if (_owner->_state != 0x20000)  // CSS_LOBBY
    {
        JOB_LOG(Log::LT_ERROR, 136, L"[job], cli-session is not in lobby", L"");
        _lgate->SendRecoverCharacterFail(_owner->_clikey, _slotid, Character::CLIENTSTATE_UNKNOWN, 5);
        transit(FIN);
        return true;
    }

    // LIFT: CliSession::getCharacterInSlot(id128) is inline in the PDB (no body). The search is written here. The
    // original copies _slotid to the stack (by-value parameter).
    Character* pc = nullptr;
    id128 const slotid = _slotid;
    if (slotid.id[0] != ID128_ID_ZERO.id[0] || slotid.id[1] != ID128_ID_ZERO.id[1])
    {
        for (std::vector<Character*, StlAllocator<Character*, 2> >::const_iterator i = _owner->_characters.begin();
             i != _owner->_characters.end(); ++i)
        {
            if (*i != nullptr && (*i)->_db.slotid.id[0] == slotid.id[0] && (*i)->_db.slotid.id[1] == slotid.id[1])
            {
                pc = *i;
                break;
            }
        }
    }
    if (pc == nullptr)
    {
        JOB_LOG(Log::LT_ERROR, 145, L"[job], no such character",
                L", slot-id:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X", SLOTID_ARGS(_slotid));
        _lgate->SendRecoverCharacterFail(_owner->_clikey, _slotid, Character::CLIENTSTATE_UNKNOWN, 158);
        transit(FIN);
        return true;
    }

    if (pc->_db.state != Character::IN_TRY_DELETE && pc->_db.state != Character::IN_TRY_RESTORE)
    {
        JOB_LOG(Log::LT_ERROR, 153, L"[job], not stuck", L", pcid:0x%I64X", pc->_db.pcid);
        _lgate->SendRecoverCharacterFail(_owner->_clikey, _slotid, pc->GetClientState(), 159);
        transit(FIN);
        return true;
    }

    GameWorld* world = LobbyDaemon::_instance->_gameWorldRegistry->Get(pc->_db.belongingWorld);
    if (world == nullptr)
    {
        JOB_LOG(Log::LT_ERROR, 162, L"[job], world not registered", L", wid:%d, pcid:0x%I64X", pc->_db.belongingWorld,
                pc->_db.pcid);
        _lgate->SendRecoverCharacterFail(_owner->_clikey, _slotid, Character::CLIENTSTATE_UNKNOWN, 160);
        transit(FIN);
        return true;
    }

    if (!world->PermitCharacterManagement(_owner, false))
    {
        unsigned int const error = static_cast<unsigned int>(TLobbyError);
        JOB_LOG(Log::LT_ERROR, 171, L"[job], world denied", L", error:%s, wid:%d, pcid:0x%I64X",
                error >= 28 ? L"LOBERR_UNDEFINED" : LobbyErrorDesc[error], pc->_db.belongingWorld, pc->_db.pcid);
        short reason;
        if (error == LOBERR_GAMEWORLD_NOT_USABLE)
            reason = 160;
        else if (error == LOBERR_GAMEWORLD_CHARACTER_MANAGEMENT_NOT_ALLOWED)
            reason = 161;
        else
            reason = 2;
        _lgate->SendRecoverCharacterFail(_owner->_clikey, _slotid, Character::CLIENTSTATE_UNKNOWN, reason);
        transit(FIN);
        return true;
    }

    _gamed = LobbyDaemon::_instance->_gamedchmgr->Acquire(pc->_db.belongingWorld);
    if (_gamed == nullptr)
    {
        JOB_LOG(Log::LT_ERROR, 194, L"[job], gamed channel not available", L", wid:%d, pcid:0x%I64X",
                pc->_db.belongingWorld, pc->_db.pcid);
        _lgate->SendRecoverCharacterFail(_owner->_clikey, _slotid, Character::CLIENTSTATE_UNKNOWN, 160);
        transit(FIN);
        return true;
    }

    _tran = new (Memory::_Manager[2]->Alloc(sizeof(LobbyJobTransaction), kFile, 200)) LobbyJobTransaction;
    _pcid = pc->_db.pcid;
    JOB_LOG(Log::LT_DEBUG, 203, L"[job], init ok",
            L", request-gate-wid:%d, slot-id:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X, pcid:0x%I64X, "
            L"pc-belonging-wid:%d",
            _lgate != nullptr ? (_lgate->_rawChannel != nullptr ? static_cast<short>(_lgate->_rawChannel->GetId()) : 0) : 0,
            SLOTID_ARGS(_slotid), _pcid, pc->_db.belongingWorld);
    transit(RESTORE_GAMEWORLD_PC);
    return true;
}

// 0x65b40
bool RecoverPcJob::restoreGameWorldPcReq()
{
    if (!_gamed->SendRestoreCharacterReq(_tran->Set(this, 113), _pcid))
    {
        JOB_LOG(Log::LT_ERROR, 213, L"[job], req restore pc fail; send req fail", L", wid:%d",
                _gamed != nullptr ? (_gamed->_rawChannel != nullptr ? static_cast<short>(_gamed->_rawChannel->GetId()) : 0) : 0);
        _lgate->SendRecoverCharacterFail(_owner->_clikey, _slotid, Character::CLIENTSTATE_UNKNOWN, 160);
        transit(FIN);
    }
    else
    {
        JOB_LOG(Log::LT_DEBUG, 218, L"[job], restore req sent", L", wid:%d",
                _gamed != nullptr ? (_gamed->_rawChannel != nullptr ? static_cast<short>(_gamed->_rawChannel->GetId()) : 0) : 0);
    }
    return true;
}

// 0x65d30
bool RecoverPcJob::restoreGameWorldPcOk()
{
    JOB_LOG(Log::LT_DEBUG, 224, L"[job], restore ok recv", L"");
    _gamed->TRecv(_tran);
    if (_owner->_state == 0x60000)  // CSS_FIN
    {
        JOB_LOG(Log::LT_ERROR, 233, L"[job], cli-session already fin", L"");
        _lgate->SendRecoverCharacterFail(_owner->_clikey, _slotid, Character::CLIENTSTATE_UNKNOWN, 5);
        transit(FIN);
        return true;
    }

    // LIFT: 0x65d30 inlines the pcid search (CliSession::getCharacter 0x35cf0).
    Character* pc = nullptr;
    if (_pcid != 0)
    {
        for (std::vector<Character*, StlAllocator<Character*, 2> >::const_iterator i = _owner->_characters.begin();
             i != _owner->_characters.end(); ++i)
        {
            if (*i != nullptr && (*i)->_db.pcid == _pcid)
            {
                pc = *i;
                break;
            }
        }
    }
    if (pc == nullptr)
    {
        JOB_LOG(Log::LT_ERROR, 242, L"[job], pc disappeared", L", pcid:0x%I64X", _pcid);
        _lgate->SendRecoverCharacterFail(_owner->_clikey, _slotid, Character::CLIENTSTATE_UNKNOWN, 158);
        transit(FIN);
        return true;
    }

    short failReason = 1;
    if (__restoreStuckPc(pc, failReason))
        _lgate->SendRecoverCharacterOk(_owner->_clikey, _slotid);
    else
        _lgate->SendRecoverCharacterFail(_owner->_clikey, _slotid, pc->GetClientState(), failReason);
    transit(FIN);
    return true;
}

// 0x66070
bool RecoverPcJob::restoreGameWorldPcFail(short* reason)
{
    _gamed->TRecv(_tran);
    if (reason == nullptr)
    {
        JOB_LOG(Log::LT_ERROR, 268, L"[job], invalid parameter", L"");
        _lgate->SendRecoverCharacterFail(_owner->_clikey, _slotid, Character::CLIENTSTATE_UNKNOWN, 2);
        transit(FIN);
        return true;
    }

    JOB_LOG(Log::LT_DEBUG, 276, L"[job], restore fail recv", L", reason:%d", *reason);
    if (*reason == 35)
    {
        JOB_LOG(Log::LT_DEBUG, 294, L"[job], pc already restored in game-world", L", pcid:0x%I64X", _pcid);
        short code;
        if (_owner->_state == 0x60000)  // CSS_FIN
        {
            JOB_LOG(Log::LT_ERROR, 301, L"[job], cli-session already fin", L"");
            code = 5;
        }
        else
        {
            // LIFT: 0x66070 inlines the pcid search (CliSession::getCharacter 0x35cf0).
            Character* pc = nullptr;
            if (_pcid != 0)
            {
                for (std::vector<Character*, StlAllocator<Character*, 2> >::const_iterator i = _owner->_characters.begin();
                     i != _owner->_characters.end(); ++i)
                {
                    if (*i != nullptr && (*i)->_db.pcid == _pcid)
                    {
                        pc = *i;
                        break;
                    }
                }
            }
            if (pc != nullptr)
            {
                short failReason = 1;
                if (__restoreStuckPc(pc, failReason))
                    _lgate->SendRecoverCharacterOk(_owner->_clikey, _slotid);
                else
                    _lgate->SendRecoverCharacterFail(_owner->_clikey, _slotid, pc->GetClientState(), failReason);
                transit(FIN);
                return true;
            }
            JOB_LOG(Log::LT_ERROR, 309, L"[job], pc disappeared", L", pcid:0x%I64X", _pcid);
            code = 158;
        }
        _lgate->SendRecoverCharacterFail(_owner->_clikey, _slotid, Character::CLIENTSTATE_UNKNOWN, code);
    }
    else
    {
        _lgate->SendRecoverCharacterFail(_owner->_clikey, _slotid, Character::CLIENTSTATE_UNKNOWN, 2);
    }
    transit(FIN);
    return true;
}

// 0x664f0
bool RecoverPcJob::restoreGameWorldPcExpired()
{
    JOB_LOG(Log::LT_ERROR, 331, L"[job], restore pc req expired", L"");
    _lgate->SendRecoverCharacterFail(_owner->_clikey, _slotid, Character::CLIENTSTATE_UNKNOWN, 2);
    transit(FIN);
    return true;
}

// 0x66600
bool RecoverPcJob::__restoreStuckPc(Character* pc, short& failReason)
{
    if (pc == nullptr)
    {
        JOB_LOG(Log::LT_ERROR, 341, L"[job], recover fail; invalid parameter", L"");
        failReason = 2;
        return false;
    }

    if (pc->_db.state == Character::IN_TRY_DELETE)
    {
        Character::ErrCode const error = pc->CancelDeletion();
        if (error == Character::ERR_OK)
        {
            JOB_LOG(Log::LT_DEBUG, 353, L"[job], recover from try deletion ok", L", pcid:0x%I64X", pc->_db.pcid);
            return true;
        }
        JOB_LOG(Log::LT_DEBUG, 358, L"[job], recover from try deletion fail", L", error:%d, pcid:0x%I64X", error,
                pc->_db.pcid);
    }
    else if (pc->_db.state == Character::IN_TRY_RESTORE)
    {
        Character::ErrCode const error = pc->FinishRestore();
        if (error == Character::ERR_OK)
        {
            JOB_LOG(Log::LT_DEBUG, 374, L"[job], recover from try restore ok", L", pcid:0x%I64X", _pcid);
            return true;
        }
        JOB_LOG(Log::LT_DEBUG, 379, L"[job], recover from try restore fail", L", error:%d, pcid:0x%I64X", error,
                pc->_db.pcid);
    }
    else
    {
        JOB_LOG(Log::LT_ERROR, 393, L"[job], invalid character state", L", pc-state:%d, pcid:0x%I64X", pc->_db.state,
                pc->_db.pcid);
    }
    failReason = 2;
    return false;
}
