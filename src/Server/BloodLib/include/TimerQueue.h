// TimerQueue, Timer (CacheGate PDB). Layouts from include/pdb/CacheGate/types.h.
// TimerQueue bodies: src/common/Timer.cpp (SmartCouponDaemon Timer.obj).
#pragma once
#include "RefCntObject.h"
#include "Lock.h"
#include <queue>
#include "StlMemory.h"

struct EventContext;

class EventObject : public RefCntObject
{
public:
    virtual unsigned int EventId() const = 0;                     // slot 4
    virtual bool HandleEvent(EventContext* ctx, unsigned long) = 0;  // slot 5
    // LIFT: no user-declared dtor. The PDB dtor (CG 0xCD60, SCD 0x1170) is a thunk to
    // RefCntObject::~RefCntObject with no vtable store: a compiler-generated dtor.
};
static_assert(sizeof(EventObject) == 0x18, "sizeof EventObject");

class DynamicEventObject : public EventObject
{
    // LIFT: compiler-generated dtor (see EventObject).
private:
    virtual void deallocate_me(void* ptr, wchar_t const* file, int line);
};
static_assert(sizeof(DynamicEventObject) == 0x18, "sizeof DynamicEventObject");

class Timer : public DynamicEventObject
{
public:
    // Inline ctor (seen in SmartCouponDaemon::initialize 0x150E0).
    // LIFT: body stores in the original order (LG 0x12bf0, LD LobbyDaemon.c): StartTick, InLtq, prev, next, SlotIndex.
    Timer()
    {
        StartTick = 0;
        InLtq = false;
        prev = nullptr;
        next = nullptr;
        SlotIndex = -1;
    }
    virtual unsigned int TimerClass() const = 0;          // slot 6
    virtual unsigned long long TimerId() const = 0;       // slot 7
    virtual void preprocessExpireEvent();                 // slot 8
    virtual ~Timer();
    virtual unsigned int EventId() const;

    unsigned int StartTick;
    Timer* next;
    Timer* prev;
    int SlotIndex;
    bool InLtq;
};
static_assert(sizeof(Timer) == 0x38, "sizeof Timer");
static_assert(offsetof(Timer, next) == 0x20, "Timer::next");
static_assert(offsetof(Timer, SlotIndex) == 0x30, "Timer::SlotIndex");

// LIFT: GameDaemon only (card lift-gamedaemon-0c). Types of the declarations in TimerQueue.
class Timer;
class TimerQueue
{
public:
    // Layout from the IDA type TimerQueue::Slot.
    struct Slot
    {
        int index;
        Timer* head;
        Timer* tail;
    };

    // PDB: TimerQueue::GreaterBySlotIndex (1 byte). The smallest SlotIndex is on top.
    struct GreaterBySlotIndex
    {
        bool operator()(Timer const* left, Timer const* right) const { return left->SlotIndex > right->SlotIndex; }
    };
    typedef std::vector<Timer*, StlAllocator<Timer*, 2> > LtqList;
    typedef std::priority_queue<Timer*, LtqList, GreaterBySlotIndex> LtqType;

    // Inlined in Daemon::start (0xb140). The PDB has this constructor (protected).
    TimerQueue() : TimerInterval(0), StqSize(0), StqSlot(nullptr), StqCurrent(0), LtQueue() {}
    virtual ~TimerQueue();  // 0x25EC0 (SmartCouponDaemon)

protected:
    bool Initialize(long timerInterval, unsigned int shortTermQueueSize);  // 0x25FF0 (SmartCouponDaemon)
    bool Add(long elapse, Timer* timer);                                    // 0x26270 (SmartCouponDaemon)
    bool Remove(Timer* timer);                                              // 0x26390 (SmartCouponDaemon)
    void TimeExpired(Slot* slot);                                           // 0x260D0 (SmartCouponDaemon)

private:
    void removeShortTermQueue(Slot* slot, Timer* timer);  // 0x26480 (SmartCouponDaemon)
    void clearShortTermQueueSlot(Slot* slot);             // 0x264F0 (SmartCouponDaemon)
    void addLongTermQueue(unsigned int slice, Timer* timer);  // 0x26560 (SmartCouponDaemon)
    void clearLongTermQueueSlot();                        // 0x26680 (SmartCouponDaemon)

private:
    // PDB: all members are private. Only Daemon (friend) reaches the protected methods.
    long TimerInterval;
    SpinLock Lock;
    unsigned int StqSize;
    Slot* StqSlot;
    unsigned int StqCurrent;
    LtqType LtQueue;

    friend class Daemon;

    // Layout checks. They are in the class because the members are private.
    static void checkLayout()
    {
        static_assert(offsetof(TimerQueue, StqSlot) == 0x40, "TimerQueue::StqSlot");
        static_assert(offsetof(TimerQueue, LtQueue) == 0x50, "TimerQueue::LtQueue");
    }
    // LIFT: GameDaemon only (card lift-gamedaemon-0c). Declarations for the wave-0 stubs in
    // src/Server/GameDaemon. They add no code to the other exes.
protected:
    bool __cdecl RemoveAndAdd(::Timer *, long, ::Timer *);  // GameDaemon 0x6b0ec0
};
static_assert(sizeof(TimerQueue) == 0x78, "sizeof TimerQueue");
