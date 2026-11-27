// DelayedRelease (SmartCouponDaemon PDB). Bodies: DelayedRelease.cpp.
#pragma once
#include "Lock.h"

class RefCntObject;

class DelayedRelease
{
public:
    struct Node
    {
        Node* _next;
        long long _added;
        void (*_callback)(RefCntObject*, RefCntObject*, RefCntObject*);
        RefCntObject* _ref1;
        RefCntObject* _ref2;
        RefCntObject* _ref3;
    };

    // PDB static constants. The compiler folded them. The values come from the inlined constructor.
    static long const DEFAULT_INTERVAL = 1000;
    static long const DEFAULT_DELAY = 10000;

#if defined(LIFT_EXE_GD)
    // GameDaemon 0x6a11d0: out-of-line (body: src/Server/GameDaemon/source_delayedrelease.cpp).
    DelayedRelease(long interval, long delay);
#else
    // PDB constructor, inlined in Daemon::start (0xb140).
    DelayedRelease(long interval, long delay)
        : _head(nullptr), _tail(nullptr), _count(0), _lastReleased(0), _interval(interval), _delay(delay)
    {
    }
#endif
    // PDB destructor, inlined in Daemon::start (0xb140).
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

    // 0x22C70 (SmartCouponDaemon)
    bool Add(long long current, void (*callback)(RefCntObject*, RefCntObject*, RefCntObject*),
             RefCntObject* ref1, RefCntObject* ref2, RefCntObject* ref3);
    // 0x22DA0 (SmartCouponDaemon)
    void Release(long long current, int maxRelease, bool forceNow, bool all);
    // 0x22F00 (SmartCouponDaemon)
    void Cleanup();

private:
    // 0x22F40 (SmartCouponDaemon)
    static void releaseNode(Node* delHead);

    friend class ReleaseEvent;  // LIFT: friend; PDB: Node and releaseNode are private. HandleEvent calls releaseNode (SmartCouponDaemon 0x2314d).

public:
    CriticalSection _lock;
    Node* _head;
    Node* _tail;
    int _count;
    long long _lastReleased;
    long _interval;
    long _delay;
};
static_assert(sizeof(DelayedRelease::Node) == 0x30, "sizeof DelayedRelease::Node");
static_assert(sizeof(DelayedRelease) == 0x50, "sizeof DelayedRelease");
static_assert(offsetof(DelayedRelease, _count) == 0x38, "DelayedRelease::_count");
static_assert(offsetof(DelayedRelease, _interval) == 0x48, "DelayedRelease::_interval");
