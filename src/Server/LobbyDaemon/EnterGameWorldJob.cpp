// EnterGameWorldJob.obj (LobbyDaemon PDB, 2019 + PDB). Lifted from the pseudocode with PDB types.
#include <new>
#include <wchar.h>
#include <winsock2.h>
#include <windows.h>
#include "EnterGameWorldJob.h"
#include "CliSession.h"
#include "GamedChannel.h"
#include "LiftStub.h"
#include "Log.h"

static wchar_t const kFile[] = L"EnterGameWorldJob.cpp";

// The log suffix of all LobbyJob logs. The original reads the owner state 2 times (HIWORD and LOWORD).
#define JOB_LOG(logType, line, msg, fmt, ...)                                                                          \
    Log::Write(logType, kFile, line, msg L", tid:0x%I64X, type:%d, state:%d, cli-key:0x%I64X, cli-state:%d.%d" fmt,   \
               this != nullptr ? _id : 0, this != nullptr ? GetDefinition()->type : -1,                            \
               this != nullptr ? _state : -1, this != nullptr && _owner != nullptr ? _owner->_clikey : 0,          \
               HIWORD(this != nullptr && _owner != nullptr ? _owner->_state : 0),                                  \
               LOWORD(this != nullptr && _owner != nullptr ? _owner->_state : 0), ##__VA_ARGS__)

// PDB enum ECliSessionState (CliSession.h has no copy yet): CSS_LOBBY = 0x20000, CSS_L2W_wait = 0x30002,
// CSS_L2W_ok = 0x30003, CSS_WORLD = 0x40000, CSS_W2L_wait = 0x50001, CSS_FIN = 0x60000.

namespace
{
LobbyJobStateDef const StateDef[] = {{0, L"INIT"}, {1, L"ENTER_GAME_WORLD"}, {2, L"FIN"}};  // 0x12db10
}

LobbyJobDef EnterGameWorldJob::_def = {11, StateDef, 2, L"EnterGameWorldJob"};  // 0x201910

#include "ObjectPoolLobbyDaemon.h"

// .data 0x205330, dynamic init 0x11e4d0, atexit dtor 0x11f1c0.
// The exe .data holds id 1, objsize 0x70, desc L"EnterGameWorldJob".

// 0x84e00
LobbyJobDef const* EnterGameWorldJob::GetDefinition() const
{
    return &_def;
}

// 0x84e10
// LIFT: Not done. The body calls _pool.Checkin. ObjPool is not in lift_lobbydaemon.
void EnterGameWorldJob::deallocate_me(void*, wchar_t const*, int)
{
    LIFT_STUB(0x84e10);
}

// 0x84e60
// The original constructs a job on the stack (null owner) and returns its vfptr. It does not run the destructor.
void* EnterGameWorldJob::_vtbl()
{
    char buf[sizeof(EnterGameWorldJob)];
    EnterGameWorldJob* job = ::new (buf) EnterGameWorldJob(nullptr);
    return *reinterpret_cast<void**>(job);
}

// 0x84ee0 (scalar deleting destructor)
EnterGameWorldJob::~EnterGameWorldJob()
{
    if (_gamed != nullptr)
        _gamed->removeReferenceCount(kFile, 75);
}

// 0x84f30
bool EnterGameWorldJob::Initialize(GamedChannel* gamed, unsigned long long gametid, unsigned long long pcid)
{
    if (gamed == nullptr || gametid == 0 || pcid == 0)
    {
        JOB_LOG(Log::LT_ERROR, 81, L"[job], invalid parameter", L", gamed-channel:%p, game-tid:0x%I64X, pcid:0x%I64X", gamed, gametid, pcid);
        return false;
    }
    _gamed = gamed;
    _gametid = gametid;
    _pcid = pcid;
    gamed->addReferenceCount(false, kFile, 89);
    return true;
}

// 0x85080
bool EnterGameWorldJob::work(int task, void*)
{
    bool result = false;
    if (_state == INIT && task == 117)
    {
        result = init();
        task = 0;
    }
    if (_state == ENTER_GAME_WORLD && task == 0)
        return enterGameWorld();
    return result;
}

// 0x850c0
bool EnterGameWorldJob::init()
{
    if (_owner->_state != 0x30003)  // CSS_L2W_ok
    {
        JOB_LOG(Log::LT_ERROR, 115, L"[job], invalid state", L", tid:0x%I64X, pcid:0x%I64X", _gametid, _pcid);
        _gamed->SendEnterWorldFail(_gametid, 6);
        return false;
    }
    JOB_LOG(Log::LT_DEBUG, 120, L"[job], init ok", L", tid:0x%I64X, pcid:0x%I64X", _gametid, _pcid);
    transit(ENTER_GAME_WORLD);
    return true;
}

// 0x85240
// LIFT: Not done (not in the gap-16 ID list). The body composes the enter-world packet with about 40 FragmentPacket
// calls (pseudocode lines 211-963).
bool EnterGameWorldJob::enterGameWorld()
{
    LIFT_STUB(0x85240);
}

// LIFT: EnterGameWorldJob::_pool (.data RVA 0x205330). Dynamic initializer 0x11e4d0, atexit destructor 0x11f1c0. The original static data
// holds id 1, objsize sizeof(EnterGameWorldJob) and desc L"EnterGameWorldJob".
ObjPool EnterGameWorldJob::_pool(1, sizeof(EnterGameWorldJob), L"EnterGameWorldJob");
