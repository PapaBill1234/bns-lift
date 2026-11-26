// InitCliSessionWlobbyTokenJob.obj (LobbyDaemon PDB, 2019 + PDB). Lifted from the pseudocode with PDB types.
#include <new>
#include <winsock2.h>
#include <windows.h>
#include "InitCliSessionWlobbyTokenJob.h"
#include "CliSession.h"
#include "LiftStub.h"
#include "LobbyGateChannel.h"
#include "Log.h"
#include "Memory.h"
#include "MemoryManager.h"

static wchar_t const kFile[] = L"InitCliSessionWlobbyTokenJob.cpp";

// The log suffix of all LobbyJob logs. The original reads the owner state 2 times (HIWORD and LOWORD).
#define JOB_LOG(logType, line, msg, fmt, ...)                                                                          \
    Log::Write(logType, kFile, line, msg L", tid:0x%I64X, type:%d, state:%d, cli-key:0x%I64X, cli-state:%d.%d" fmt,   \
               this != nullptr ? _id : 0, this != nullptr ? GetDefinition()->type : -1,                            \
               this != nullptr ? _state : -1, this != nullptr && _owner != nullptr ? _owner->_clikey : 0,          \
               HIWORD(this != nullptr && _owner != nullptr ? _owner->_state : 0),                                  \
               LOWORD(this != nullptr && _owner != nullptr ? _owner->_state : 0), ##__VA_ARGS__)

namespace
{
LobbyJobStateDef const StateDef[] = {{0, L"INIT"}, {1, L"INIT_CLISESSION_OK"}, {2, L"FIN"}};  // 0x12ded0
}

LobbyJobDef InitCliSessionWlobbyTokenJob::_def = {14, StateDef, 2, L"InitCliSessionWlobbyTokenJob"};  // 0x201c50

#include "ObjectPoolLobbyDaemon.h"

// .data 0x2048e0, dynamic init 0x11e020, atexit dtor 0x11ee00.
// The exe .data holds id 1, objsize 0x68, desc L"InitCliSessionWlobbyTokenJob".
ObjPool InitCliSessionWlobbyTokenJob::_pool(1, 0x68, L"InitCliSessionWlobbyTokenJob");

// 0x54830
LobbyJobDef const* InitCliSessionWlobbyTokenJob::GetDefinition() const
{
    return &_def;
}

// 0x54840
// LIFT: Not done. The body calls _pool.Checkin. ObjPool is not in lift_lobbydaemon.
void InitCliSessionWlobbyTokenJob::deallocate_me(void*, wchar_t const*, int)
{
    LIFT_STUB(0x54840);
}

// 0x54890
// The original constructs a job on the stack (null owner) and returns its vfptr. It does not run the destructor.
void* InitCliSessionWlobbyTokenJob::_vtbl()
{
    char buf[sizeof(InitCliSessionWlobbyTokenJob)];
    InitCliSessionWlobbyTokenJob* job = ::new (buf) InitCliSessionWlobbyTokenJob(nullptr);
    return *reinterpret_cast<void**>(job);
}

// 0x54910 (scalar deleting destructor)
InitCliSessionWlobbyTokenJob::~InitCliSessionWlobbyTokenJob()
{
    if (_lgate != nullptr)
        _lgate->removeReferenceCount(kFile, 62);
}

// 0x54960
bool InitCliSessionWlobbyTokenJob::Initialize(LobbyGateChannel* lgate, unsigned long long gatekey)
{
    if (lgate != nullptr && gatekey != 0)
    {
        _lgate = lgate;
        _gatekey = gatekey;
        lgate->addReferenceCount(false, kFile, 75);
        return true;
    }
    JOB_LOG(Log::LT_ERROR, 68, L"[job], invalid parameter", L", lgate:%p, gate-key:0x%I64X", lgate, gatekey);
    return false;
}

// 0x54aa0
bool InitCliSessionWlobbyTokenJob::work(int task, void* param)
{
    bool result = false;
    if (_state == INIT && task == 14)
    {
        result = init();
        task = 0;
    }
    if (_state == INIT_CLISESSION_OK && task == 0)
        return initOk();
    return result;
}

// 0x54ae0
bool InitCliSessionWlobbyTokenJob::init()
{
    if (_owner->_state != 0x50001)
    {
        JOB_LOG(Log::LT_ERROR, 101, L"[job], invalid state", L"");
        _lgate->SendInitSessionWithLobbyTokenFail(_gatekey, 5);
        return false;
    }
    JOB_LOG(Log::LT_DEBUG, 106, L"[job], init ok", L", gate-key:0x%I64X", _gatekey);
    transit(INIT_CLISESSION_OK);
    return true;
}

// 0x54c40
bool InitCliSessionWlobbyTokenJob::initOk()
{
    _owner->closePresence();
    Presence* const presence = new (Memory::_Manager[2]->Alloc(sizeof(AnonymousLobbyGatePresence), kFile, 118))
        AnonymousLobbyGatePresence(_lgate, _gatekey);
    if (!_owner->setPresence(presence))
    {
        JOB_LOG(Log::LT_ERROR, 120, L"[job], set anonymous lobby-gate presence fail", L", gate-wid:%d, gate-key:0x%I64X",
                _lgate->GetWid(), _gatekey);
        _owner->_state = 0x60000;
        _owner->finalize();
        _lgate->SendInitSessionWithLobbyTokenFail(_gatekey, 2);
        // LIFT: the original calls the scalar deleting destructor (flag 1) and then Free. Its operator delete is empty.
        delete presence;
        Memory::_Manager[2]->Free(presence, kFile, 124);
        return false;
    }
    _owner->leave();
    _owner->_state = 0x50002;
    JOB_LOG(Log::LT_DEBUG, 131, L"[job], cli-session respawned", L"");
    _lgate->SendInitSessionWithLobbyTokenOk(_gatekey, _owner->_clikey);
    transit(FIN);
    return true;
}
