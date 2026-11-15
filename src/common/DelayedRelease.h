// DelayedRelease (CacheGate PDB). Layout from include/pdb/CacheGate/types.h.
// Declarations only. The bodies are in a later card.
#pragma once
#include "Lock.h"

class DelayedRelease
{
public:
    struct Node;  // ❓ layout not used here

    // ❓ Inlined in Daemon::start (0xb140).
    DelayedRelease() : _head(nullptr), _tail(nullptr), _count(0), _lastReleased(0), _interval(1000), _delay(10000) {}
    // ❓ Inlined in Daemon::start (0xb140).
    ~DelayedRelease()
    {
        _lock.Enter();
        Node* head = _head;
        _head = nullptr;
        _tail = nullptr;
        _count = 0;
        _lock.Leave();
        releaseNode(head);
    }

    void Release(long long current, int count, bool force, bool all);  // 0x13b80 TODO(lift-delayedrelease)
    void Cleanup();                                                      // 0x13ce0 TODO(lift-delayedrelease)

private:
    static void releaseNode(Node* node);                                 // 0x13d20 TODO(lift-delayedrelease)

public:
    CriticalSection _lock;
    Node* _head;
    Node* _tail;
    int _count;
    long long _lastReleased;
    long _interval;
    long _delay;
};
static_assert(sizeof(DelayedRelease) == 0x50, "sizeof DelayedRelease");
static_assert(offsetof(DelayedRelease, _count) == 0x38, "DelayedRelease::_count");
static_assert(offsetof(DelayedRelease, _interval) == 0x48, "DelayedRelease::_interval");
