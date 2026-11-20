// WaitQueue.obj (LobbyDaemon PDB, 2019 + PDB). Lift from the Hex-Rays pseudocode of LobbyDaemon.exe.
#include "WaitQueue.h"
#include "Daemon.h"
#include "Log.h"

// LIFT: inlined private helper (no body in the binary). WaitQueue::Add (0xdc5e0) has it.
__forceinline void WaitQueue::startWaitAvg()
{
    _waitOrg = GetTickCount64() - Daemon::Instance->StartSystemTick64;
}

// LIFT: inlined private helper (no body in the binary). WaitQueue::Remove (0xdc720) and WaitQueueList::Init
// (0xdc940) have it.
__forceinline void WaitQueue::resetWaitAvg()
{
    _waitOrg = 0;
    _waitAcm = 0;
    _waitAvg = 0.0;
}

// LIFT: inlined private helper (no body in the binary). WaitQueueList::Pop (0xdca20) has it 2 times.
// ❓ The PDB gives one bool argument. The 2 inline copies differ only in the factor of the old average:
// _waitAcm - 1 under the lock, _waitAcm in the second loop. The name "pop" is not from the PDB.
__forceinline void WaitQueue::updateWaitAvg(bool pop)
{
    if (++_waitAcm == 0)
        _waitAcm = 1;
    long long now = GetTickCount64() - Daemon::Instance->StartSystemTick64;
    unsigned long long count = pop ? _waitAcm - 1 : _waitAcm;
    _waitAvg = ((double)count * _waitAvg + (double)(now - _waitOrg)) / (double)_waitAcm;
    _waitOrg = now;
}

// 0xdc540
WaitQueue::WaitQueue()
{
    _waitOrg = 0;
    _waitAcm = 0;
    _waitAvg = 0.0;
}

// 0xdc590
// LIFT: the body is the inline ~BoundedList and ~SpinLock of the members.
WaitQueue::~WaitQueue()
{
}

// LIFT: inline in WaitQueueList::Init (0xdc940). No body in the binary.
__forceinline bool WaitQueue::Init(int capacity)
{
    if (!_waits.Init(capacity))
    {
        Log::Write(Log::LT_ERROR, L"WaitQueue.cpp", 28, L"[wait-queue], init fail; init list fail, capacity:%d", capacity);
        return false;
    }
    resetWaitAvg();
    Log::Write(Log::LT_DEBUG, L"WaitQueue.cpp", 34, L"[wait-queue], init ok, capacity:%d", capacity);
    return true;
}

// 0xdc5e0
bool WaitQueue::Add(unsigned long long clikey, short& waitpos, int& turn)
{
    if (clikey == 0)
    {
        Log::Write(Log::LT_ERROR, L"WaitQueue.cpp", 41, L"[wait-queue], add wait queue fail; invalid cli-key");
        return false;
    }

    bool result = false;
    _lock.Enter();
    bool first = _waits.Empty();
    short pos = _waits.Pushback(reinterpret_cast<void*>(clikey));
    if (pos != INVALID_POS)
    {
        result = true;
        turn = _waits.Size();
        if (first)
            startWaitAvg();
    }
    _lock.Leave();

    if (result)
    {
        waitpos = pos;
        Log::Write(Log::LT_DEBUG, L"WaitQueue.cpp", 68, L"[wait-queue], add wait queue ok, cli-key:0x%I64X, pos:%d, turn:%d",
                   clikey, pos, turn);
    }
    else
    {
        Log::Write(Log::LT_ERROR, L"WaitQueue.cpp", 71, L"[wait-queue], add wait queue fail; push fail, cli-key:0x%I64X",
                   clikey);
    }
    return result;
}

// 0xdc720
bool WaitQueue::Remove(short const& waitpos, unsigned long long clikey)
{
    if (clikey == 0)
    {
        Log::Write(Log::LT_ERROR, L"WaitQueue.cpp", 79,
                   L"[wait-queue], remove wait queue fail; invalid cli-key, wait-position:%d", waitpos);
        return false;
    }

    bool result = false;
    _lock.Enter();
    BoundedList::Node const* node = _waits.GetNode(waitpos);
    if (node != nullptr && node->data == reinterpret_cast<void*>(clikey))
    {
        result = _waits.Remove(waitpos);
        if (result && _waits.Empty())
            resetWaitAvg();
    }
    _lock.Leave();

    if (result)
    {
        Log::Write(Log::LT_DEBUG, L"WaitQueue.cpp", 103,
                   L"[wait-queue], remove wait queue ok, cli-key:0x%I64X, wait-position:%d", clikey, waitpos);
    }
    else if (node != nullptr)
    {
        Log::Write(Log::LT_ERROR, L"WaitQueue.cpp", 109,
                   L"[wait-queue], remove wait queue fail; mismatch, cli-key:0x%I64X, wait-position:%d", clikey, waitpos);
    }
    else
    {
        Log::Write(Log::LT_ERROR, L"WaitQueue.cpp", 107,
                   L"[wait-queue], remove wait queue fail; not found, cli-key:0x%I64X, wait-position:%d", clikey, waitpos);
    }
    return result;
}

// LIFT: inline in WaitQueueList::Pop (0xdca20). No body in the binary.
__forceinline unsigned long long WaitQueue::Pop()
{
    _lock.Enter();
    unsigned long long clikey = reinterpret_cast<unsigned long long>(_waits.Popfront());
    if (clikey != 0)
    {
        if (_waits.Size() != 0)
            updateWaitAvg(true);
        else
            resetWaitAvg();
    }
    _lock.Leave();
    return clikey;
}

// 0xdc870
bool WaitQueue::QueryTurn(short const& waitpos, int& turn) const
{
    bool found = false;
    int count = 0;
    // LIFT: SpinLock::Enter is not const. The original locks a const object.
    const_cast<SpinLock&>(_lock).Enter();
    for (short pos = _waits.Head(); pos != BoundedList::_NIL; pos = _waits.Next(pos))
    {
        ++count;
        if (pos == waitpos)
        {
            found = true;
            break;
        }
    }
    const_cast<SpinLock&>(_lock).Leave();
    if (found)
        turn = count;
    return found;
}

// 0xdc920
WaitQueueList::~WaitQueueList()
{
}

// 0xdc940
bool WaitQueueList::Init(int capacity)
{
    for (int type = 0; type < WaitQueue::MAX_WAIT_QUEUE_TYPE; ++type)
    {
        if (!_waitQueue[type].Init(capacity))
        {
            Log::Write(Log::LT_ERROR, L"WaitQueue.cpp", 178,
                       L"[wait-queue-list], init fail; init list fail, capacity:%d, queueType:%d", capacity, type);
            return false;
        }
    }
    _maxWaitingPlayer = capacity;
    _currentWaitingPlayer = 0;
    return true;
}

// 0xdca20
unsigned long long WaitQueueList::Pop()
{
    unsigned long long clikey = 0;
    int type;
    for (type = 0; type < WaitQueue::MAX_WAIT_QUEUE_TYPE; ++type)
    {
        clikey = _waitQueue[type].Pop();
        if (clikey != 0)
        {
            --_currentWaitingPlayer;
            break;
        }
    }
    if (clikey != 0)
    {
        for (int t = type; t < WaitQueue::MAX_WAIT_QUEUE_TYPE; ++t)
        {
            if (_waitQueue[t].Size() > 0)
                _waitQueue[t].updateWaitAvg(false);
        }
    }
    return clikey;
}
