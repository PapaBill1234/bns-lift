// Timer.obj (SmartCouponDaemon PDB): TimerQueue.
// LTCG removed the unused `this` argument of removeShortTermQueue and
// clearShortTermQueueSlot. The lift keeps the PDB member signatures.
// STL code in Timer.obj is the VS2010 STL from include/vs2010 (not lifted by hand):
//   0xE3A0  priority_queue<Timer*,...>::~priority_queue
//   0x1B50  std::_Uninit_move<Timer**,...> (+ catch$0 0x51FF0)
//   0x267A0 vector<Timer*,StlAllocator<Timer*,2>>::reserve (+ catch$0 0x51EB0)
//   0x26710 vector<Timer*,StlAllocator<Timer*,2>>::_Reserve
//   0x26890 std::_Pop_heap_0<Timer**,Timer*,TimerQueue::GreaterBySlotIndex>
//   0x520A0 / 0x520B0 ~TimerQueue dtor$0 / dtor$1 (EH funclets of the member destructors)
#include "TimerQueue.h"
#include <windows.h>
#include "AlertSender.h"
#include "CrashHandler.h"
#include "Daemon.h"
#include "Log.h"
#include "Memory.h"
#include "MemoryManager.h"

#define TIMER_FILE L"source\\Timer.cpp"

// Inlined crash macro.
#define TIMER_ASSERT_CRASH(line)                                                  \
    do                                                                            \
    {                                                                             \
        Log::Write(Log::LT_ERROR, TIMER_FILE, line, L"== CRASH == ASSERT CRASH"); \
        AlertSender::Write(TIMER_FILE, line, L"== CRASH == ASSERT CRASH");       \
        CrashHandler::MakeCrash("source\\Timer.cpp", line, L"");                  \
    } while (0)

// 0x25EC0 (SmartCouponDaemon)
// 0x25EA0 (SmartCouponDaemon) scalar deleting destructor: the compiler makes it.
TimerQueue::~TimerQueue()
{
    clearLongTermQueueSlot();
    if (StqSlot != nullptr)
    {
        for (unsigned int i = 0; i < StqSize; ++i)
        {
            // Inlined clearShortTermQueueSlot(&StqSlot[i]).
            Slot* slot = &StqSlot[i];
            Timer* timer;
            while ((timer = slot->head) != nullptr)
            {
                slot->head = timer->next;
                if (slot->head == nullptr)
                    slot->tail = nullptr;
                timer->prev = nullptr;
                timer->next = nullptr;
                timer->SlotIndex = -1;
                timer->preprocessExpireEvent();
                timer->removeReferenceCount(TIMER_FILE, 312);
            }
        }
        Memory::_Manager[2]->Free(StqSlot, TIMER_FILE, 35);
        StqSlot = nullptr;
    }
    // The LtQueue and Lock destructors run here (LtQueue frees its buffer, Lock calls DeleteCriticalSection).
}

// 0x25FF0 (SmartCouponDaemon)
bool TimerQueue::Initialize(long timerInterval, unsigned int shortTermQueueSize)
{
    if (StqSlot != nullptr)
        TIMER_ASSERT_CRASH(41);
    TimerInterval = timerInterval;
    StqSize = shortTermQueueSize;
    StqSlot = static_cast<Slot*>(Memory::_Manager[2]->AllocZero(sizeof(Slot) * shortTermQueueSize, TIMER_FILE, 46));
    for (unsigned int i = 0; i < StqSize; ++i)
        StqSlot[i].index = i;
    StqCurrent = 0;
    return true;
}

// 0x260D0 (SmartCouponDaemon)
void TimerQueue::TimeExpired(Slot* slot)
{
    EnterCriticalSection(&Lock.SL);
    StqCurrent = (StqCurrent + 1) % StqSize;
    if (slot != nullptr)
    {
        // Move the timers of the current slot to the caller.
        Slot& current = StqSlot[StqCurrent];
        Timer* tail = current.tail;
        Timer* head = current.head;
        current.tail = nullptr;
        slot->tail = tail;
        slot->head = head;
        StqSlot[StqCurrent].head = nullptr;
        for (; head != nullptr; head = head->next)
            head->SlotIndex = -1;
    }
    else
    {
        clearShortTermQueueSlot(&StqSlot[StqCurrent]);
    }

    while (!LtQueue.empty())
    {
        Timer* timer = LtQueue.top();
        if (timer->SlotIndex >= static_cast<int>(StqSize + Daemon::Instance->CurrentTick))
            break;
        LtQueue.pop();
        if (timer->InLtq)
        {
            unsigned int startTick = timer->StartTick;
            timer->InLtq = false;
            // Inlined short-term insert into the last slot.
            Slot& last = StqSlot[(StqSize + StqCurrent - 1) % StqSize];
            if (last.tail != nullptr)
            {
                last.tail->next = timer;
                timer->prev = last.tail;
            }
            else
            {
                last.head = timer;
            }
            last.tail = timer;
            timer->StartTick = startTick;
            timer->SlotIndex = last.index;
            timer->addReferenceCount(false, TIMER_FILE, 288);
        }
        timer->removeReferenceCount(TIMER_FILE, 114);
    }
    LeaveCriticalSection(&Lock.SL);
}

// 0x26270 (SmartCouponDaemon)
bool TimerQueue::Add(long elapse, Timer* timer)
{
    if (timer == nullptr || timer->SlotIndex >= 0)
        TIMER_ASSERT_CRASH(155);
    EnterCriticalSection(&Lock.SL);
    unsigned int slice = elapse / TimerInterval;
    if (slice < StqSize)
    {
        long currentTick = Daemon::Instance->CurrentTick;
        Slot& slot = StqSlot[(slice + StqCurrent) % StqSize];
        if (slot.tail != nullptr)
        {
            slot.tail->next = timer;
            timer->prev = slot.tail;
        }
        else
        {
            slot.head = timer;
        }
        slot.tail = timer;
        timer->StartTick = currentTick;
        timer->SlotIndex = slot.index;
        timer->addReferenceCount(false, TIMER_FILE, 288);
    }
    else
    {
        addLongTermQueue(slice, timer);
    }
    LeaveCriticalSection(&Lock.SL);
    return true;
}

// 0x26390 (SmartCouponDaemon)
bool TimerQueue::Remove(Timer* timer)
{
    if (timer == nullptr)
        TIMER_ASSERT_CRASH(183);
    EnterCriticalSection(&Lock.SL);
    int index = timer->SlotIndex;
    if (index < 0)
    {
        LeaveCriticalSection(&Lock.SL);
        Log::Write(Log::LT_DEBUG, TIMER_FILE, 196, L"TimerQueue::Remove() Error, timer index = %d", index);
        return false;
    }
    if (index >= static_cast<int>(StqSize))
        timer->InLtq = false;  // TimeExpired drops the timer when it leaves LtQueue.
    else
        removeShortTermQueue(&StqSlot[index], timer);
    LeaveCriticalSection(&Lock.SL);
    return true;
}

// 0x26480 (SmartCouponDaemon)
// LIFT: noinline. The original Remove (0x26390) calls this function in all exes. VS2010 /LTCG inlines it without the attribute.
__declspec(noinline) void TimerQueue::removeShortTermQueue(Slot* slot, Timer* timer)
{
    if (slot->head == timer)
        slot->head = timer->next;
    if (slot->tail == timer)
        slot->tail = timer->prev;
    if (timer->next != nullptr)
        timer->next->prev = timer->prev;
    if (timer->prev != nullptr)
        timer->prev->next = timer->next;
    timer->SlotIndex = -1;
    timer->prev = nullptr;
    timer->next = nullptr;
    timer->removeReferenceCount(TIMER_FILE, 304);
}

// 0x264F0 (SmartCouponDaemon)
#if defined(_MSC_VER) && !defined(__clang__)
#pragma inline_depth(0)
#endif
void TimerQueue::clearShortTermQueueSlot(Slot* slot)
{
    Timer* timer;
    while ((timer = slot->head) != nullptr)
    {
        slot->head = timer->next;
        if (slot->head == nullptr)
            slot->tail = nullptr;
        timer->prev = nullptr;
        timer->next = nullptr;
        timer->SlotIndex = -1;
        timer->preprocessExpireEvent();
        timer->removeReferenceCount(TIMER_FILE, 312);
    }
}
#if defined(_MSC_VER) && !defined(__clang__)
#pragma inline_depth()
#endif

// 0x26560 (SmartCouponDaemon)
void TimerQueue::addLongTermQueue(unsigned int slice, Timer* timer)
{
    timer->StartTick = Daemon::Instance->CurrentTick;
    timer->SlotIndex = Daemon::Instance->CurrentTick + slice;
    timer->InLtq = true;
    timer->addReferenceCount(false, TIMER_FILE, 326);
    LtQueue.push(timer);
}

// 0x26680 (SmartCouponDaemon)
void TimerQueue::clearLongTermQueueSlot()
{
    while (!LtQueue.empty())
    {
        Timer* timer = LtQueue.top();
        LtQueue.pop();
        timer->removeReferenceCount(TIMER_FILE, 342);
    }
}
