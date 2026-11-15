// TimerQueue, Timer (CacheGate PDB). Layouts from include/pdb/CacheGate/types.h.
// Declarations only. The bodies are in a later card.
#pragma once
#include "RefCntObject.h"
#include "Lock.h"

class EventContext;

class EventObject : public RefCntObject
{
public:
    virtual unsigned int EventId() const = 0;                     // slot 4
    virtual bool HandleEvent(EventContext* ctx, unsigned long) = 0;  // slot 5
    virtual ~EventObject();
};
static_assert(sizeof(EventObject) == 0x18, "sizeof EventObject");

class DynamicEventObject : public EventObject
{
public:
    virtual ~DynamicEventObject();
private:
    virtual void deallocate_me(void* ptr, wchar_t const* file, int line);
};
static_assert(sizeof(DynamicEventObject) == 0x18, "sizeof DynamicEventObject");

class Timer : public DynamicEventObject
{
public:
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

    // ❓ Inlined in Daemon::start (0xb140).
    TimerQueue() : TimerInterval(0), StqSize(0), StqSlot(nullptr), StqCurrent(0)
    {
        for (int i = 0; i < 0x28; ++i)
            LtQueue[i] = 0;
    }
    virtual ~TimerQueue();

protected:
    bool Initialize(long interval, unsigned int slotCount);  // 0x16400 TODO(lift-timerqueue)
    void TimeExpired(Slot* slot);                            // 0x164e0 TODO(lift-timerqueue)

public:
    long TimerInterval;
    SpinLock Lock;
    unsigned int StqSize;
    void* StqSlot;
    unsigned int StqCurrent;
    // ❓ PDB type: std::priority_queue<Timer*, std::vector<Timer*, StlAllocator<Timer*,2> >,
    // TimerQueue::GreaterBySlotIndex>. The later card puts the real type here.
    alignas(8) unsigned char LtQueue[0x28];

    friend class Daemon;
};
static_assert(sizeof(TimerQueue) == 0x78, "sizeof TimerQueue");
static_assert(offsetof(TimerQueue, StqSlot) == 0x40, "TimerQueue::StqSlot");
static_assert(offsetof(TimerQueue, LtQueue) == 0x50, "TimerQueue::LtQueue");
