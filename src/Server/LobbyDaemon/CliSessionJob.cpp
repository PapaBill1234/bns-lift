// CliSessionJob.obj (LobbyDaemon PDB, 2019 + PDB). Lifted from the pseudocode with PDB types.
#include "CliSessionJob.h"
#include "CliSession.h"
#include "LiftStub.h"

// 0x3bef0
// The LobbyJob base is inline (RefCntObject: tag 10, ref 1; LobbyJob: _id, _state and _lastState are zero, lock).
CliSessionJob::CliSessionJob(CliSession* owner) : _owner(owner)
{
    if (owner != nullptr)
        owner->addReferenceCount(false, L"CliSessionJob.cpp", 17);
}

// 0x3bfa0
CliSessionJob::~CliSessionJob()
{
    if (_owner != nullptr)
        _owner->removeReferenceCount(L"CliSessionJob.cpp", 23);
}

// 0x3c010
bool CliSessionJob::dispatch_work(int task, void* param)
{
    // The job works under the lock of its owner session.
    CliSession* const owner = _owner;
    EnterCriticalSection(&owner->_lock.CS);
    bool const result = work(task, param);
    LeaveCriticalSection(&owner->_lock.CS);
    return result;
}
