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
};

class WaitQueueList
{
public:
    // LIFT: WaitQueueList::WaitQueueList has no body in the binary. The implicit ctor is used.
    ~WaitQueueList();  // 0xdc920
    bool Init(int capacity);   // 0xdc940
    // LIFT: Inlined in GameWorldCluster::giveupWait (0x4e310).
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
};
