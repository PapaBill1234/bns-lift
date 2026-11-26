// LeaveGameWorldJob.obj (LobbyDaemon PDB, 2019 + PDB). Lifted from the pseudocode with PDB types.
#include <new>
#include <wchar.h>
#include <winsock2.h>
#include <windows.h>
#include "LeaveGameWorldJob.h"
#include "AlertSender.h"
#include "Character.h"
#include "CliSession.h"
#include "GamedChannel.h"
#include "LiftStub.h"
#include "LobbyDaemon.h"
#include "LobbyToken.h"
#include "Log.h"
#include "Memory.h"
#include "MemoryManager.h"

static wchar_t const kFile[] = L"LeaveGameWorldJob.cpp";

// The log suffix of all LobbyJob logs. The original reads the owner state 2 times (HIWORD and LOWORD).
#define JOB_LOG(logType, line, msg, fmt, ...)                                                                          \
    Log::Write(logType, kFile, line, msg L", tid:0x%I64X, type:%d, state:%d, cli-key:0x%I64X, cli-state:%d.%d" fmt,   \
               this != nullptr ? _id : 0, this != nullptr ? GetDefinition()->type : -1,                            \
               this != nullptr ? _state : -1, this != nullptr && _owner != nullptr ? _owner->_clikey : 0,          \
               HIWORD(this != nullptr && _owner != nullptr ? _owner->_state : 0),                                  \
               LOWORD(this != nullptr && _owner != nullptr ? _owner->_state : 0), ##__VA_ARGS__)

// The same log, then the same text to the alert sender ("== CRASH ==" logs).
#define JOB_CRASH(line, msg, fmt, ...)                                                                                 \
    do                                                                                                                 \
    {                                                                                                                  \
        JOB_LOG(Log::LT_ERROR, line, L"== CRASH == " msg, fmt, ##__VA_ARGS__);                                         \
        AlertSender::Write(kFile, line, L"== CRASH == " msg L", tid:0x%I64X, type:%d, state:%d, cli-key:0x%I64X, cli-state:%d.%d" fmt, \
                           this != nullptr ? _id : 0, this != nullptr ? GetDefinition()->type : -1,                    \
                           this != nullptr ? _state : -1, this != nullptr && _owner != nullptr ? _owner->_clikey : 0,  \
                           HIWORD(this != nullptr && _owner != nullptr ? _owner->_state : 0),                          \
                           LOWORD(this != nullptr && _owner != nullptr ? _owner->_state : 0), ##__VA_ARGS__);          \
    } while (0)

// PDB enum ECliSessionState (CliSession.h has no copy yet): CSS_LOBBY = 0x20000, CSS_L2W_wait = 0x30002,
// CSS_L2W_ok = 0x30003, CSS_WORLD = 0x40000, CSS_W2L_wait = 0x50001, CSS_FIN = 0x60000.

namespace
{
LobbyJobStateDef const StateDef[] = {{0, L"INIT"}, {1, L"LEAVE_GAME_WORLD"}, {2, L"FIN"}};  // 0x12da80

// The world id of a gamed channel for the logs (PDB GamedChannel::GetWid is inline; the logs also check for null).
short gamedWid(GamedChannel const* gamed)
{
    if (gamed == nullptr)
        return 0;
    return gamed->_rawChannel != nullptr ? static_cast<short>(gamed->_rawChannel->GetId()) : 0;
}
}

LobbyJobDef LeaveGameWorldJob::_def = {13, StateDef, 2, L"LeaveGameWorldJob"};  // 0x2018d0

#include "ObjectPoolLobbyDaemon.h"

// .data 0x205490, dynamic init 0x11e570, atexit dtor 0x11f240.
// The exe .data holds id 1, objsize 0x78, desc L"LeaveGameWorldJob".

// 0x877b0
LobbyJobDef const* LeaveGameWorldJob::GetDefinition() const
{
    return &_def;
}

// 0x877c0
// LIFT: Not done. The body calls _pool.Checkin. ObjPool is not in lift_lobbydaemon.
void LeaveGameWorldJob::deallocate_me(void*, wchar_t const*, int)
{
    LIFT_STUB(0x877c0);
}

// 0x87810
// The original constructs a job on the stack (null owner) and returns its vfptr. It does not run the destructor.
void* LeaveGameWorldJob::_vtbl()
{
    char buf[sizeof(LeaveGameWorldJob)];
    LeaveGameWorldJob* job = ::new (buf) LeaveGameWorldJob(nullptr);
    return *reinterpret_cast<void**>(job);
}

// 0x87890 (scalar deleting destructor)
LeaveGameWorldJob::~LeaveGameWorldJob()
{
    if (_gamed != nullptr)
        _gamed->removeReferenceCount(kFile, 72);
}

// 0x878e0
bool LeaveGameWorldJob::Initialize(GamedChannel* gamed, unsigned long long gametid, unsigned long long pcid)
{
    if (gamed == nullptr || gametid == 0 || pcid == 0)
    {
        JOB_LOG(Log::LT_ERROR, 78, L"[job], invalid parameter", L"");
        return false;
    }
    _gamed = gamed;
    _gametid = gametid;
    _pcid = pcid;
    gamed->addReferenceCount(false, kFile, 86);
    return true;
}

// 0x87a00
bool LeaveGameWorldJob::work(int task, void*)
{
    bool result = false;
    if (_state == INIT && task == 119)
    {
        result = init();
        task = 0;
    }
    if (_state == LEAVE_GAME_WORLD && task == 0)
        return leaveGameWorld();
    return result;
}

// 0x87a40
bool LeaveGameWorldJob::init()
{
    if (_owner->_state != 0x40000)  // CSS_WORLD
    {
        JOB_LOG(Log::LT_ERROR, 112, L"[job], invalid state", L"");
        _gamed->SendLeaveWorldFail(_gametid, 6);
        return false;
    }

    Character* pc = _owner->getPlayingCharacter();
    if (pc == nullptr)
    {
        JOB_LOG(Log::LT_ERROR, 124, L"[job], no such pc", L", wid:%d, game-tid:0x%I64X, pcid:0x%I64X", gamedWid(_gamed), _gametid, _pcid);
        _gamed->SendLeaveWorldFail(_gametid, 21);
        return false;
    }
    if (pc->_db.pcid != _pcid)
    {
        JOB_LOG(Log::LT_ERROR, 130, L"[job], not playing pc", L", wid:%d, game-tid:0x%I64X, pcid:0x%I64X", gamedWid(_gamed), _gametid, _pcid);
        _gamed->SendLeaveWorldFail(_gametid, 23);
        return false;
    }
    // The original reads the world id of _gamed here without a null check (PDB GamedChannel::GetWid, inline).
    if (pc->_db.belongingWorld != (_gamed->_rawChannel != nullptr ? static_cast<short>(_gamed->_rawChannel->GetId()) : 0))
    {
        JOB_LOG(Log::LT_ERROR, 136, L"[job], not belonging world", L", wid:%d, game-tid:0x%I64X, pcid:0x%I64X", gamedWid(_gamed), _gametid, _pcid);
        _gamed->SendLeaveWorldFail(_gametid, 22);
        return false;
    }

    JOB_LOG(Log::LT_DEBUG, 141, L"[job], init ok", L", wid:%d, game-tid:0x%I64X, pcid:0x%I64X", gamedWid(_gamed), _gametid, _pcid);
    transit(LEAVE_GAME_WORLD);
    return true;
}

// 0x87e90
bool LeaveGameWorldJob::leaveGameWorld()
{
    Character* pc = _owner->getCharacter(_pcid);
    if (pc != nullptr)
        pc->EndGameWorldPlay();
    else
        JOB_CRASH(152, L"[job], pc disappear", L", pcid:0x%I64X", _pcid);

    ServiceLocation* srvloc = _owner->_srvloc;
    if (srvloc != nullptr)
        srvloc->OnLeave(_owner);

    LobbyToken* token = new (Memory::_Manager[2]->Alloc(sizeof(LeaveGameWorldToken), kFile, 159)) LeaveGameWorldToken(_owner);
    if (!LobbyDaemon::_instance->_tokenDesk->Issue(token))
    {
        JOB_LOG(Log::LT_ERROR, 161, L"[job], issue token fail; kick cli-session", L"");
        _gamed->SendLeaveWorldFail(_gametid, 2);
        _owner->_state = 0x60000;  // CSS_FIN
        _owner->closePresence();
        _owner->finalize();
        token->removeReferenceCount(kFile, 169);
        return false;
    }

    _leaveWorldTokenKey = token->_tokenkey;
    _owner->_state = 0x50001;  // CSS_W2L_wait
    _gamed->SendLeaveWorldOk(_gametid, _leaveWorldTokenKey);
    JOB_LOG(Log::LT_DEBUG, 179, L"[job], leave game world ok", L"");
    token->removeReferenceCount(kFile, 181);
    transit(FIN);
    return true;
}

// LIFT: LeaveGameWorldJob::_pool (.data RVA 0x205490). Dynamic initializer 0x11e570, atexit destructor 0x11f240. The original static data
// holds id 1, objsize sizeof(LeaveGameWorldJob) and desc L"LeaveGameWorldJob".
ObjPool LeaveGameWorldJob::_pool(1, sizeof(LeaveGameWorldJob), L"LeaveGameWorldJob");
