// AbandonChargeJob.obj (LobbyDaemon PDB, 2019 + PDB). Lifted from the pseudocode with PDB types.
#include <new>
#include <wchar.h>
#include <winsock2.h>
#include <windows.h>
#include "AbandonChargeJob.h"
#include "CliSession.h"
#include "LiftStub.h"
#include "LobbyDaemon.h"
#include "Log.h"
#include "Memory.h"
#include "MemoryManager.h"
#include "NPServiceChannel.h"

static wchar_t const kFile[] = L"AbandonChargeJob.cpp";

// The log suffix of all LobbyJob logs. The original reads the owner state 2 times (HIWORD and LOWORD).
#define JOB_LOG(logType, line, msg, fmt, ...)                                                                          \
    Log::Write(logType, kFile, line, msg L", tid:0x%I64X, type:%d, state:%d, cli-key:0x%I64X, cli-state:%d.%d" fmt,   \
               this != nullptr ? _id : 0, this != nullptr ? GetDefinition()->type : -1,                            \
               this != nullptr ? _state : -1, this != nullptr && _owner != nullptr ? _owner->_clikey : 0,          \
               HIWORD(this != nullptr && _owner != nullptr ? _owner->_state : 0),                                  \
               LOWORD(this != nullptr && _owner != nullptr ? _owner->_state : 0), ##__VA_ARGS__)

namespace
{
LobbyJobStateDef const StateDef[] = {{0, L"INIT"}, {1, L"ABANDON_CHARGE"}, {2, L"FIN"}};  // 0x12e5b0
}

LobbyJobDef AbandonChargeJob::_def = {18, StateDef, 2, L"AbandonChargeJob"};  // 0x2020e0
// LIFT: AbandonChargeJob::_pool (0x2037b0: id 1, size 0xf0) is defined at the end of this file (gap-26).

#include "ObjectPoolLobbyDaemon.h"

// .data 0x2037b0, dynamic init 0x11d850, atexit dtor 0x11e7c0.
// The exe .data holds id 1, objsize 0xf0, desc L"AbandonChargeJob".

// 0x4f70
LobbyJobDef const* AbandonChargeJob::GetDefinition() const
{
    return &_def;
}

// 0x4f80
// LIFT: Not done. The body calls _pool.Checkin. ObjPool is not in lift_lobbydaemon.
void AbandonChargeJob::deallocate_me(void*, wchar_t const*, int)
{
    LIFT_STUB(0x4f80);
}

// 0x5020
// The original constructs a job on the stack (null owner) and returns its vfptr. It does not run the destructor.
void* AbandonChargeJob::_vtbl()
{
    char buf[sizeof(AbandonChargeJob)];
    AbandonChargeJob* job = ::new (buf) AbandonChargeJob(nullptr);
    return *reinterpret_cast<void**>(job);
}

// 0x50d0
bool AbandonChargeJob::Initialize(unsigned long long pcid, wchar_t const* chargeKey)
{
    if (chargeKey == nullptr || wcslen(chargeKey) == 0)
    {
        JOB_LOG(Log::LT_ERROR, 69, L"[job], init fail; invalid parameter", L", pcid:0x%I64X, charge-key:%s", pcid,
                chargeKey != nullptr ? chargeKey : L"null");
        return false;
    }
    _pcid = pcid;
    wcscpy_s(_chargeKey, 65, chargeKey);
    return true;
}

// 0x5220
bool AbandonChargeJob::work(int task, void* param)
{
    bool result = false;
    if (_state == INIT && task == 122)
    {
        result = init();
        task = 0;
    }
    if (_state == ABANDON_CHARGE)
    {
        if (task == 0)
            return requestChargeAbandon();
        else if (task == 58)
            return responseChargeAbandon(param);
        else if (task == 59)
            return expireChargeAbandon();
    }
    return result;
}

// 0x52a0
bool AbandonChargeJob::init()
{
    JOB_LOG(Log::LT_DEBUG, 110, L"[job], init param", L", pcid:0x%I64X, charge-key:%s", _pcid, _chargeKey);
    int next;
    if (_owner->_state == 0x40000)
    {
        JOB_LOG(Log::LT_DEBUG, 118, L"[job], init ok", L"");
        next = ABANDON_CHARGE;
    }
    else
    {
        JOB_LOG(Log::LT_ERROR, 113, L"[job], init fail; state not in world", L"");
        next = FIN;
    }
    transit(next);
    return true;
}

// 0x54a0
bool AbandonChargeJob::requestChargeAbandon()
{
    NPGameServiceChannel* const gs = LobbyDaemon::_instance->_npServchmgr->_gameServChannel;
    NPLobbyJobTransaction* const tr = new (Memory::_Manager[2]->Alloc(sizeof(NPLobbyJobTransaction), kFile, 127))
        NPLobbyJobTransaction;
    // The original gives task 57 here (not the expire task 59 of this job).
    if (!gs->SendRequestChargeAbandon(tr->Set(this, 57), _owner->_acb._userid, _chargeKey))
    {
        JOB_LOG(Log::LT_ERROR, 131, L"[job], req charge abandon fail; unsent", L"");
        // LIFT: the original calls the scalar deleting destructor (flag 1) and then Free. Its operator delete is empty.
        tr->~NPLobbyJobTransaction();
        Memory::_Manager[2]->Free(tr, kFile, 132);
        transit(FIN);
    }
    else
    {
        JOB_LOG(Log::LT_DEBUG, 137, L"[job], req charge abandon ok", L"");
    }
    return true;
}

// 0x5690
// LIFT: Not done. The body starts a KickJob (KickJob.h is a stub class). Card gap-08 or later owns KickJob.
bool AbandonChargeJob::responseChargeAbandon(void*)
{
    LIFT_STUB(0x5690);
}

// 0x5b10
// LIFT: Not done. The body starts a KickJob (KickJob.h is a stub class).
bool AbandonChargeJob::expireChargeAbandon()
{
    LIFT_STUB(0x5b10);
}

// LIFT: AbandonChargeJob::_pool (.data RVA 0x2037b0). Dynamic initializer 0x11d850, atexit destructor 0x11e7c0. The original static data
// holds id 1, objsize sizeof(AbandonChargeJob) and desc L"AbandonChargeJob".
ObjPool AbandonChargeJob::_pool(1, sizeof(AbandonChargeJob), L"AbandonChargeJob");
