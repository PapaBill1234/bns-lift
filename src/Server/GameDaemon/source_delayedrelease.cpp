// source_delayedrelease.cpp: delayedrelease.cpp (GameDaemon PDB, 2019 + PDB).
#include "delayedrelease_gd.h"
#include "leadtheballmanager.h"
#include "../BloodLib/include/DelayedRelease.h"
#include "../BloodLib/include/Memory.h"
#include "../BloodLib/include/MemoryManager.h"
#include "LiftStub.h"

#if defined(LIFT_EXE_GD)
#pragma comment(linker, "/INCLUDE:??0DelayedRelease@@QEAA@JJ@Z")  // LIFT: dead-strip keep (no live caller yet)
#endif
#pragma comment(linker, "/INCLUDE:?Cleanup@DelayedDelete@@QEAAXXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?HandleEvent@DeleteEvent@@UEAA_NPEAUEventContext@@K@Z")  // LIFT: dead-strip keep (no live caller yet)

static wchar_t const DELAYED_RELEASE_FILE[] = L"source\\DelayedRelease.cpp";

// 0x6a11d0
// LIFT: GameDaemon has an out-of-line constructor (DelayedRelease.h, LIFT_EXE_GD). The stores follow the original order.
// LIFT: only tools/vs2010/build.sh defines LIFT_EXE_GD. Other builds use the inline constructor of DelayedRelease.h.
#if defined(LIFT_EXE_GD)
DelayedRelease::DelayedRelease(long interval, long delay)
{
    _interval = interval;
    _delay = delay;
    _head = nullptr;
    _tail = nullptr;
    _count = 0;
    _lastReleased = 0;
}
#endif

// 0x6a16d0
bool __cdecl DelayedDelete::Add(__int64, bool (__cdecl *)(void *), void (__cdecl *)(void *), void *)
{
    LIFT_STUB(0x6a16d0);
}

// 0x6a17c0
void __cdecl DelayedDelete::Delete(__int64, int, bool, bool)
{
    LIFT_STUB(0x6a17c0);
}

// 0x6a1960
void __cdecl DelayedDelete::Cleanup(void)
{
    _lock.Enter();
    Node* head = _head;
    _head = nullptr;
    _tail = nullptr;
    _count = 0;
    _lock.Leave();
    deleteNode(head);
}

// 0x6a19d0
void __cdecl DelayedDelete::deleteNode(::DelayedDelete::Node *delHead)
{
    while (delHead != nullptr)
    {
        Node* node = delHead;
        delHead = delHead->_next;
        node->_doDelete(node->_ptr);
        Memory::_Manager[2]->Free(node, DELAYED_RELEASE_FILE, 407);
    }
}

// 0x6a1a50
bool __cdecl DeleteEvent::HandleEvent(::EventContext *, unsigned long)
{
    DelayedDelete::deleteNode(_head);
    removeReferenceCount(DELAYED_RELEASE_FILE, 425);
    return true;
}
