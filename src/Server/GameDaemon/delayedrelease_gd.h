// delayedrelease_gd.h: delayedrelease.cpp, delayedrelease.h (GameDaemon PDB, 2019 + PDB).
#pragma once
#include "GameDaemonFwd.h"

class DeleteEvent;

// PDB: DelayedDelete (GameDaemon), size 0x50.
class DelayedDelete
{
public:
    typedef bool (*CheckDelete)(void*);
    typedef void (*DoDelete)(void*);

    struct Node
    {
        Node* _next;
        long long _added;
        bool (*_checkDelete)(void*);
        void (*_doDelete)(void*);
        void* _ptr;
    };

public:
    bool __cdecl Add(__int64, bool (__cdecl *)(void *), void (__cdecl *)(void *), void *);  // 0x6a16d0
    void __cdecl Delete(__int64, int, bool, bool);  // 0x6a17c0
    void __cdecl Cleanup(void);  // 0x6a1960
private:
    static void __cdecl deleteNode(::DelayedDelete::Node *);  // 0x6a19d0

    friend class DeleteEvent;  // LIFT: friend; PDB: Node and deleteNode are private. HandleEvent inlines deleteNode (0x6a1a50).

    CriticalSection _lock;
    Node* _head;
    Node* _tail;
    int _count;
    long long _lastDeleted;
    long _interval;
    long _delay;
};
static_assert(sizeof(DelayedDelete::Node) == 0x28, "sizeof DelayedDelete::Node");
static_assert(sizeof(DelayedDelete) == 0x50, "sizeof DelayedDelete");
