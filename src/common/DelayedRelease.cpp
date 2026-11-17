// DelayedRelease.obj (SmartCouponDaemon PDB).
// LTCG folded the arguments of the only callers:
//   Add: callback = Channel::removeSession, ref3 = nullptr.
//   Release: maxRelease = 0, forceNow = false, all = false.
// The lift keeps the PDB signatures and writes the general logic.  // LIFT: mangled names prove the signatures (LobbyGate ?Add@DelayedRelease@@QEAA_N_JP6AXPEAVRefCntObject@@11@Z111@Z, ?Release@DelayedRelease@@QEAAX_JH_N1@Z).
#include "DelayedRelease.h"
#include <windows.h>
#include <new>
#include "Log.h"
#include "Memory.h"
#include "MemoryManager.h"
#include "Network.h"
#include "TimerQueue.h"

static wchar_t const DELAYED_RELEASE_FILE[] = L"source\\DelayedRelease.cpp";

// ReleaseEvent is local to DelayedRelease.obj. PDB type 0x224D (LobbyGate), size 0x20.
class ReleaseEvent : public DynamicEventObject
{
public:
    explicit ReleaseEvent(DelayedRelease::Node* head) : _head(head)
    {
        // LIFT: The inlined RefCntObject constructor at 0x22DA0 sets these fields.
        _tag = 10;
        _ref = 1;
        _history = nullptr;
    }
    virtual ~ReleaseEvent();
    virtual unsigned int EventId() const;
    virtual bool HandleEvent(EventContext* context, unsigned long param);

private:
    DelayedRelease::Node* _head;
};
static_assert(sizeof(ReleaseEvent) == 0x20, "sizeof ReleaseEvent");

// 0x22C60 (SmartCouponDaemon)
unsigned int ReleaseEvent::EventId() const
{
    return 6;
}

// 0x23110 (SmartCouponDaemon) scalar deleting destructor
ReleaseEvent::~ReleaseEvent()
{
}

// 0x23140 (SmartCouponDaemon)
bool ReleaseEvent::HandleEvent(EventContext* context, unsigned long param)
{
    DelayedRelease::releaseNode(_head);
    removeReferenceCount(DELAYED_RELEASE_FILE, 211);
    return true;
}

// 0x22C70 (SmartCouponDaemon)
bool DelayedRelease::Add(long long current, void (*callback)(RefCntObject*, RefCntObject*, RefCntObject*),
                         RefCntObject* ref1, RefCntObject* ref2, RefCntObject* ref3)
{
    Node* node = static_cast<Node*>(Memory::_Manager[2]->Alloc(sizeof(Node), DELAYED_RELEASE_FILE, 38));
    if (node == nullptr)
    {
        Log::Write(Log::LT_ERROR, DELAYED_RELEASE_FILE, 41,
                   L"[delayed release], allocation failed, callback:%p, ref1:%p, ref2:%p, ref3:%p",
                   callback, ref1, ref2, ref3);
        return false;
    }
    node->_added = current;
    node->_ref1 = ref1;
    node->_ref2 = ref2;
    node->_callback = callback;
    node->_ref3 = ref3;
    if (ref1 != nullptr)
        ref1->addReferenceCount(DELAYED_RELEASE_FILE, 51);
    if (ref2 != nullptr)
        ref2->addReferenceCount(DELAYED_RELEASE_FILE, 52);
    if (ref3 != nullptr)
        ref3->addReferenceCount(DELAYED_RELEASE_FILE, 53);  // ❓ LTCG removed this call (ref3 is nullptr)
    node->_next = nullptr;
    _lock.Enter();
    if (_head == nullptr)
        _head = node;
    if (_tail != nullptr)
        _tail->_next = node;
    ++_count;
    _tail = node;
    _lock.Leave();
    return true;
}

// 0x22DA0 (SmartCouponDaemon)
void DelayedRelease::Release(long long current, int maxRelease, bool forceNow, bool all)
{
    Node* head = nullptr;
    Node* last = nullptr;
    // LIFT: LTCG folded maxRelease (0) to the limit 0x7FFFFFFF.
    int limit = maxRelease > 0 ? maxRelease : 0x7FFFFFFF;
    _lock.Enter();
    if (forceNow || _lastReleased == 0 || current - _lastReleased > _interval)
    {
        int released = 0;
        while (_head != nullptr)
        {
            Node* node = _head;
            // ❓ LTCG removed the use of forceNow and all (both false). The use here is a guess.
            if ((!all && current - node->_added <= _delay) || released == limit)
                break;
            if (head == nullptr)
                head = _head;
            _head = node->_next;
            node->_next = nullptr;
            if (last != nullptr)
                last->_next = node;
            --_count;
            ++released;
            last = node;
        }
        if (_head == nullptr)
            _tail = nullptr;
        _lastReleased = current;
    }
    _lock.Leave();
    if (head == nullptr)
        return;

    void* memory = Memory::_Manager[2]->Alloc(sizeof(ReleaseEvent), DELAYED_RELEASE_FILE, 110);
    ReleaseEvent* event = memory != nullptr ? new (memory) ReleaseEvent(head) : nullptr;
    if (event == nullptr)
    {
        releaseNode(head);
        return;
    }
    void* iocpHandle = nullptr;
    if (Network::Instance != nullptr)
        iocpHandle = Network::Instance->_iocpHandle;
    if (!PostQueuedCompletionStatus(iocpHandle, 0, reinterpret_cast<ULONG_PTR>(event), nullptr))
    {
        event->removeReferenceCount(DELAYED_RELEASE_FILE, 115);
        releaseNode(head);
    }
}

// 0x22F00 (SmartCouponDaemon)
void DelayedRelease::Cleanup()
{
    _lock.Enter();
    Node* head = _head;
    _head = nullptr;
    _tail = nullptr;
    _count = 0;
    _lock.Leave();
    releaseNode(head);
}

// 0x22F40 (SmartCouponDaemon)
void DelayedRelease::releaseNode(Node* delHead)
{
    Node* next = delHead;
    while (next != nullptr)
    {
        Node* node = next;
        next = next->_next;
        node->_callback(node->_ref1, node->_ref2, node->_ref3);
        if (node->_ref1 != nullptr)
            node->_ref1->removeReferenceCount(DELAYED_RELEASE_FILE, 189);
        if (node->_ref2 != nullptr)
            node->_ref2->removeReferenceCount(DELAYED_RELEASE_FILE, 190);
        if (node->_ref3 != nullptr)
            node->_ref3->removeReferenceCount(DELAYED_RELEASE_FILE, 191);
        Memory::_Manager[2]->Free(node, DELAYED_RELEASE_FILE, 193);
    }
}
