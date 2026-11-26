// GetChargeInfoJob.obj (LobbyDaemon PDB, 2019 + PDB). Lifted from the pseudocode with PDB types.
#include <new>
#include <wchar.h>
#include <winsock2.h>
#include <windows.h>
#include "GetChargeInfoJob.h"
#include "CliSession.h"
#include "LobbyGateChannel.h"
#include "LiftStub.h"
#include "LobbyDaemon.h"
#include "Log.h"
#include "Memory.h"
#include "MemoryManager.h"
#include "NPServiceChannel.h"

static wchar_t const kFile[] = L"GetChargeInfoJob.cpp";

// The log suffix of all LobbyJob logs. The original reads the owner state 2 times (HIWORD and LOWORD).
#define JOB_LOG(logType, line, msg, fmt, ...)                                                                          \
    Log::Write(logType, kFile, line, msg L", tid:0x%I64X, type:%d, state:%d, cli-key:0x%I64X, cli-state:%d.%d" fmt,   \
               this != nullptr ? _id : 0, this != nullptr ? GetDefinition()->type : -1,                            \
               this != nullptr ? _state : -1, this != nullptr && _owner != nullptr ? _owner->_clikey : 0,          \
               HIWORD(this != nullptr && _owner != nullptr ? _owner->_state : 0),                                  \
               LOWORD(this != nullptr && _owner != nullptr ? _owner->_state : 0), ##__VA_ARGS__)

namespace
{
LobbyJobStateDef const StateDef[] = {{0, L"INIT"}, {1, L"GET_CHARGE_INFO"}, {2, L"FIN"}};  // 0x12df90
}

LobbyJobDef GetChargeInfoJob::_def = {19, StateDef, 2, L"GetChargeInfoJob"};  // 0x201cd0

#include "ObjectPoolLobbyDaemon.h"

// .data 0x204620, dynamic init 0x11dee0, atexit dtor 0x11ed00.
// The exe .data holds id 1, objsize 0x68, desc L"GetChargeInfoJob".
ObjPool GetChargeInfoJob::_pool(1, 0x68, L"GetChargeInfoJob");

// 0x50550
LobbyJobDef const* GetChargeInfoJob::GetDefinition() const
{
    return &_def;
}

// 0x50560
// LIFT: Not done. The body calls _pool.Checkin. ObjPool is not in lift_lobbydaemon.
void GetChargeInfoJob::deallocate_me(void*, wchar_t const*, int)
{
    LIFT_STUB(0x50560);
}

// 0x505b0
// The original constructs a job on the stack (null owner, null lobby-gate) and returns its vfptr. It does not run
// the destructor.
void* GetChargeInfoJob::_vtbl()
{
    char buf[sizeof(GetChargeInfoJob)];
    GetChargeInfoJob* job = ::new (buf) GetChargeInfoJob(nullptr, nullptr);
    return *reinterpret_cast<void**>(job);
}

// 0x50630
// The constructor does not set _clikey.
GetChargeInfoJob::GetChargeInfoJob(CliSession* owner, LobbyGateChannel* lgate) : CliSessionJob(owner), _lgate(lgate)
{
    if (lgate != nullptr)
        lgate->addReferenceCount(false, kFile, 60);
}

// 0x50690 (scalar deleting destructor)
GetChargeInfoJob::~GetChargeInfoJob()
{
    if (_lgate != nullptr)
        _lgate->removeReferenceCount(kFile, 66);
}

// 0x506e0
bool GetChargeInfoJob::work(int task, void* param)
{
    bool result = false;
    if (_state == INIT && task == 17)
    {
        result = init();
        task = 0;
    }
    if (_state == GET_CHARGE_INFO)
    {
        if (task == 0)
            return requestChargeGetInfo();
        else if (task == 52)
            return responseChargeGetInfo(param);
        else if (task == 53)
            return expireChargeGetInfo();
    }
    return result;
}

// 0x50760
bool GetChargeInfoJob::init()
{
    if (_owner->_state == 0x20000)
    {
        if (_lgate != nullptr)
        {
            JOB_LOG(Log::LT_DEBUG, 112, L"[job], init ok", L", wid:%d", _lgate->GetWid());
            transit(GET_CHARGE_INFO);
            return true;
        }
        JOB_LOG(Log::LT_ERROR, 107, L"[job], init fail; invalid parameter", L"");
        transit(FIN);
        return true;
    }
    JOB_LOG(Log::LT_ERROR, 101, L"[job], init fail; cli-session not in lobby", L"");
    transit(FIN);
    return true;
}

// 0x50970
bool GetChargeInfoJob::requestChargeGetInfo()
{
    NPGameServiceChannel* const gs = LobbyDaemon::_instance->_npServchmgr->_gameServChannel;
    if (gs == nullptr)
    {
        JOB_LOG(Log::LT_ERROR, 122, L"[job], req charge get info fail; np game-service channel not available", L"");
        _lgate->SendGetChargeInfoFail(_owner->_clikey, 2);
        return false;
    }
    NPLobbyJobTransaction* const tr = new (Memory::_Manager[2]->Alloc(sizeof(NPLobbyJobTransaction), kFile, 127))
        NPLobbyJobTransaction;
    if (!gs->SendRequestChargeGetInfo(tr->Set(this, 53), _owner->_acb._userid, _owner->_ipv4))
    {
        JOB_LOG(Log::LT_ERROR, 129, L"[job], req charge get info fail; send fail", L"");
        _lgate->SendGetChargeInfoFail(_owner->_clikey, 2);
        // LIFT: the original calls the scalar deleting destructor (flag 1) and then Free. Its operator delete is empty.
        tr->~NPLobbyJobTransaction();
        Memory::_Manager[2]->Free(tr, kFile, 131);
        return false;
    }
    JOB_LOG(Log::LT_DEBUG, 135, L"[job], request charge get info sent", L"");
    return true;
}

// 0x50c30
// LIFT: Not done. The body builds the charge-info packet for the lobby-gate. It is out of the gap-05 scope.
bool GetChargeInfoJob::responseChargeGetInfo(void*)
{
    LIFT_STUB(0x50c30);
}

// 0x51360
bool GetChargeInfoJob::expireChargeGetInfo()
{
    JOB_LOG(Log::LT_ERROR, 260, L"[job], charge get info expired", L"");
    _lgate->SendGetChargeInfoFail(_owner->_clikey, 2);
    transit(FIN);
    return true;
}
