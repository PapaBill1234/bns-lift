// WaitQueue.obj (LobbyDaemon PDB, 2019 + PDB). Layouts from the PDB (WaitQueue size 0x58, WaitQueueList size 0x110).
#pragma once
#include <stddef.h>
#include "Lock.h"
#include "BoundedList.h"

class WaitQueue
{
public:
    typedef short Pos;
    static short const INVALID_POS = -1;

    enum Type
    {
        WAIT_QUEUE_TYPE_NONE = -1,
        WAIT_QUEUE_TYPE_VIP = 0,
        WAIT_QUEUE_TYPE_NORMAL = 1,
        WAIT_QUEUE_TYPE_BOT = 2,
        MAX_WAIT_QUEUE_TYPE = 3,
    };

    WaitQueue();   // 0xdc540
    ~WaitQueue();  // 0xdc590
    bool Init(int capacity);  // LIFT: inline in WaitQueueList::Init (0xdc940)
    bool Add(unsigned long long clikey, short& waitpos, int& turn);  // 0xdc5e0
    bool Remove(short const& waitpos, unsigned long long clikey);    // 0xdc720
    unsigned long long Pop();  // LIFT: inline in WaitQueueList::Pop (0xdca20)
    bool QueryTurn(short const& waitpos, int& turn) const;  // 0xdc870
    int Size() const { return _waits.Size(); }

private:
    void startWaitAvg();
    void resetWaitAvg();
    void updateWaitAvg(bool pop);

    SpinLock _lock;               // +0
    BoundedList _waits;           // +40
    long long _waitOrg;           // +64
    unsigned long long _waitAcm;  // +72
    double _waitAvg;              // +80

    // ❓ Not in the PDB. WaitQueueList::Pop (0xdca20) calls the private updateWaitAvg.
    friend class WaitQueueList;
    // ❓ Not in the PDB. GameWorldCluster::enterUser (0x4dd90) reads _waitAvg (+80) and Size() of each queue.
    friend class GameWorldCluster;
};

class WaitQueueList
{
public:
    // LIFT: WaitQueueList::WaitQueueList has no body in the binary. The implicit ctor is used.
    ~WaitQueueList();  // 0xdc920
    bool Init(int capacity);   // 0xdc940
    // LIFT: Inlined in GameWorldCluster::giveupWait (0x4e310).
    // BUG: The original indexes _waitQueue with the type and does not check the range (0x4e310).
    bool Remove(WaitQueue::Type type, short const& waitpos, unsigned long long clikey)
    {
        if (static_cast<unsigned int>(type) >= WaitQueue::MAX_WAIT_QUEUE_TYPE)
            return false;
        if (!_waitQueue[type].Remove(waitpos, clikey))
            return false;
        --_currentWaitingPlayer;
        return true;
    }
    unsigned long long Pop();  // 0xdca20
    // LIFT: Inlined in GameWorldCluster::UpdateCounters (0x4dc70).
    int GetAllWaitingPlayer() const { return _currentWaitingPlayer; }

private:
    WaitQueue _waitQueue[WaitQueue::MAX_WAIT_QUEUE_TYPE];  // +0
    int _maxWaitingPlayer;                                 // +264
    int _currentWaitingPlayer;                             // +268

    // ❓ Not in the PDB. GameWorldCluster::enterUser (0x4dd90) reads and writes the members.
    friend class GameWorldCluster;
};

// LIFT: WaitQueueInfo and WaitInfo are PDB structs (sizes 0x8 and 0x2C). Used by LobbyGateChannel::SendStartWaitNotify (0xbd6e0).
struct WaitQueueInfo
{
    // PDB method WaitQueueInfo::Init (no RVA, inlined in GameServiceLocation::Enter 0x3b6f0).
    void Init()
    {
        queueType = WaitQueue::WAIT_QUEUE_TYPE_NONE;
        waitingPlayerCount = 0;
    }

    WaitQueue::Type queueType;
    short waitingPlayerCount;
};
static_assert(sizeof(WaitQueueInfo) == 0x8, "sizeof WaitQueueInfo");
static_assert(offsetof(WaitQueueInfo, queueType) == 0x0, "WaitQueueInfo::queueType");
static_assert(offsetof(WaitQueueInfo, waitingPlayerCount) == 0x4, "WaitQueueInfo::waitingPlayerCount");

struct WaitInfo
{
    // PDB method WaitInfo::Init (no RVA, inlined in GameServiceLocation::Enter 0x3b6f0).
    // LIFT: the original does not set waitQueueInfoCount here.
    void Init()
    {
        pos = WaitQueue::INVALID_POS;
        turn = 0;
        avg = 0;
        queueType = WaitQueue::WAIT_QUEUE_TYPE_NONE;
        for (int i = 0; i < 3; ++i)
            waitQueueInfo[i].Init();
    }

    short pos;
    int turn;
    long avg;
    WaitQueue::Type queueType;
    int waitQueueInfoCount;
    WaitQueueInfo waitQueueInfo[3];
};
static_assert(sizeof(WaitInfo) == 0x2C, "sizeof WaitInfo");
static_assert(offsetof(WaitInfo, pos) == 0x0, "WaitInfo::pos");
static_assert(offsetof(WaitInfo, turn) == 0x4, "WaitInfo::turn");
static_assert(offsetof(WaitInfo, avg) == 0x8, "WaitInfo::avg");
static_assert(offsetof(WaitInfo, queueType) == 0xC, "WaitInfo::queueType");
static_assert(offsetof(WaitInfo, waitQueueInfoCount) == 0x10, "WaitInfo::waitQueueInfoCount");
static_assert(offsetof(WaitInfo, waitQueueInfo) == 0x14, "WaitInfo::waitQueueInfo");
