// GameTimeSchedule.obj (LobbyDaemon PDB, 2019 + PDB). Layouts from tools/pdbcls.py LobbyDaemon <Class>.
// LIFT: header layouts only (fix7). The function bodies are still LIFT_STUB.
// LIFT: PDB methods with no own symbol in the lift scope (SetIndex, Remove, Initialize, Stop, TimerClass, TimerId,
// the GameTimeScheduleNode ctors and dtor) are not declared. GameTimeScheduler stays abstract (Timer pure methods).
#pragma once
#include <stddef.h>
#include "Lock.h"
#include "RefCntList.h"
#include "TimerQueue.h"

class CliSession;
struct EventContext;
class IDEV612_TimeTable;

// LIFT: PDB layout (sizeof 0x40, RefCntListNode base).
class GameTimeScheduleNode : public RefCntListNode
{
private:
    friend struct GameTimeScheduleNodeLayoutCheck;  // LIFT: checks the private PDB offsets.

    unsigned long long _clikey;  // +0x30
    int _queueIndex;  // +0x38
};
static_assert(sizeof(GameTimeScheduleNode) == 0x40, "sizeof GameTimeScheduleNode");
struct GameTimeScheduleNodeLayoutCheck
{
    static_assert(offsetof(GameTimeScheduleNode, _clikey) == 0x30, "GameTimeScheduleNode::_clikey");
    static_assert(offsetof(GameTimeScheduleNode, _queueIndex) == 0x38, "GameTimeScheduleNode::_queueIndex");
};

// LIFT: PDB layout (sizeof 0x48, no base).
class GameTimeQueue
{
public:
    GameTimeQueue();  // 0x4b9a0
    ~GameTimeQueue();  // 0x4b9e0
    bool Pushback(GameTimeScheduleNode*);  // 0x4ba80
    void Block();  // 0x4bb80
    void Release();  // 0x4bf90

private:
    friend struct GameTimeQueueLayoutCheck;  // LIFT: checks the private PDB offsets.

    int _index;  // +0x0
    bool _block;  // +0x4
    CriticalSection _lock;  // +0x8
    RefCntList _queue;  // +0x30
};
static_assert(sizeof(GameTimeQueue) == 0x48, "sizeof GameTimeQueue");
struct GameTimeQueueLayoutCheck
{
    static_assert(offsetof(GameTimeQueue, _index) == 0x0, "GameTimeQueue::_index");
    static_assert(offsetof(GameTimeQueue, _block) == 0x4, "GameTimeQueue::_block");
    static_assert(offsetof(GameTimeQueue, _lock) == 0x8, "GameTimeQueue::_lock");
    static_assert(offsetof(GameTimeQueue, _queue) == 0x30, "GameTimeQueue::_queue");
};

// LIFT: PDB layout (sizeof 0x2f90, Timer base).
class GameTimeScheduler : public Timer
{
public:
    GameTimeScheduler();  // 0x4c020
    virtual ~GameTimeScheduler();  // 0x4c0e0
    bool Start();  // 0x4c150
    virtual bool HandleEvent(EventContext*, unsigned long);  // 0x4c2e0
    bool Schedule(CliSession*, IDEV612_TimeTable const&, long long*);  // 0x4c390
    void Unschedule(CliSession*, GameTimeScheduleNode*);  // 0x4c6a0

private:
    friend struct GameTimeSchedulerLayoutCheck;  // LIFT: checks the private PDB offsets.

    GameTimeQueue _queues[168];  // +0x38 (168 = 7 days x 24 hours)
    int _currentQueue;  // +0x2f78
    long long _currentQueueTime;  // +0x2f80
    bool _run;  // +0x2f88
};
static_assert(sizeof(GameTimeScheduler) == 0x2f90, "sizeof GameTimeScheduler");
struct GameTimeSchedulerLayoutCheck
{
    static_assert(offsetof(GameTimeScheduler, _queues) == 0x38, "GameTimeScheduler::_queues");
    static_assert(offsetof(GameTimeScheduler, _currentQueue) == 0x2f78, "GameTimeScheduler::_currentQueue");
    static_assert(offsetof(GameTimeScheduler, _currentQueueTime) == 0x2f80, "GameTimeScheduler::_currentQueueTime");
    static_assert(offsetof(GameTimeScheduler, _run) == 0x2f88, "GameTimeScheduler::_run");
};

class IDEV612_TimeTable
{
public:
    bool Initialize(char const*);  // 0x4b8e0

    bool _table[168];  // 7 days x 24 hours
};
static_assert(sizeof(IDEV612_TimeTable) == 168, "sizeof IDEV612_TimeTable");
