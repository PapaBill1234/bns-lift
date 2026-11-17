// TimeoutTimer.obj (MarketDealerDaemon PDB).
#include "TimeoutTimer.h"
#include <new>
#include <time.h>
#include <windows.h>
#include "Log.h"
#include "AlertSender.h"
#include "Memory.h"
#include "Network.h"
#include "Daemon.h"
#include "TimerQueue.h"
#include "MarketDealerDaemon.h"
#include "SaleContext.h"
#include "SaleTimeContext.h"
#include "TimeoutEvent.h"

#define TIMEOUT_TIMER_FILE L"TimeoutTimer.cpp"
static wchar_t const* const MODULE_NAME = L"timeout timer";  // PDB MODULE_NAME

#define TIMEOUT_TIMER_CRASH(line, fmt, ...)                                    \
    do                                                                         \
    {                                                                          \
        Log::Write(Log::LT_ERROR, TIMEOUT_TIMER_FILE, line, fmt, __VA_ARGS__); \
        AlertSender::Write(TIMEOUT_TIMER_FILE, line, fmt, __VA_ARGS__);        \
    } while (0)

namespace
{
char const kSaleTypeAuction = 1;      // ECONOMY_SALETYPE_AUCTION (EconomySaleType)
char const kSaleTypeInstantSale = 2;  // ECONOMY_SALETYPE_INSTANT_SALE (EconomySaleType)
}  // namespace

static bool isStopState(int state)  // LIFT: inlined switch
{
    return state == Daemon::STATE_STOPPED || state == Daemon::STATE_STOPPING ||
           state == Daemon::STATE_COOLDOWNING || state == Daemon::STATE_COOLDOWNED;
}

// 0x319d0
bool TimeoutTimer::HandleEvent(EventContext* context, unsigned long bytes)
{
    if (isStopState(Daemon::Instance->State))
        return true;

    Log::Write(Log::LT_DEBUG, TIMEOUT_TIMER_FILE, 27, L"[%s], %s; <BEGIN TIMER HANDLER>", MODULE_NAME,
               L"TimeoutTimer::HandleEvent");
    checkSaleExpiration();
    Log::Write(Log::LT_DEBUG, TIMEOUT_TIMER_FILE, 31, L"[%s], %s; <END TIMER HANDLER>", MODULE_NAME,
               L"TimeoutTimer::HandleEvent");

    if (isStopState(Daemon::Instance->State) ||
        MarketDealerDaemon::_instance->AddTimer(1000 * MarketDealerDaemon::_instance->_config->_timeoutCheckInterval,
                                                this))
        return true;

    Log::Write(Log::LT_ERROR, TIMEOUT_TIMER_FILE, 36, L"[%s], %s; failed to add timeout timer", MODULE_NAME,
               L"TimeoutTimer::HandleEvent");
    return false;
}

// 0x31b10
void TimeoutTimer::checkSaleExpiration() const
{
    wchar_t const* const fn = L"TimeoutTimer::checkSaleExpiration";
    SaleTimeContextManager* const saleTimeContextManager = MarketDealerDaemon::_instance->_saleTimeContextManager;
    if (saleTimeContextManager->_lockList == nullptr || saleTimeContextManager->_containerList == nullptr)
    {
        TIMEOUT_TIMER_CRASH(50,
                            L"== CRASH == [%s], %s; invalid saletime context manager, lockList:0x%p, "
                            L"containerList:0x%p",
                            MODULE_NAME, fn, saleTimeContextManager->_lockList,
                            saleTimeContextManager->_containerList);
        return;
    }

    long long const currentTime = _time64(nullptr);
    if (currentTime == -1)
    {
        TIMEOUT_TIMER_CRASH(56, L"== CRASH == [%s], %s; time fuction error, currentTime:%I64d", MODULE_NAME, fn,
                            currentTime);
        return;
    }

    for (int index = 0; index < saleTimeContextManager->_bucketCount; ++index)
    {
        saleTimeContextManager->_lockList[index].Enter();
        SaleTimeContextManager::Container& container = saleTimeContextManager->_containerList[index];
        for (SaleTimeContextManager::Container::iterator it = container.begin(); it != container.end(); ++it)
        {
            if (it->first._saleExpirationTime >= currentTime)
                break;
            SaleTimeContext* const saleTimeContext = it->second;
            if (saleTimeContext == nullptr)
            {
                TIMEOUT_TIMER_CRASH(67,
                                    L"== CRASH == [%s], %s; saletime context is null, saleId:0x%I64X, "
                                    L"saletimeContext:0x%p",
                                    MODULE_NAME, fn, it->first._saleId, static_cast<SaleTimeContext*>(nullptr));
            }
            else if (!postTimeoutEvent(saleTimeContext->_saleId, saleTimeContext->_saleType,
                                       saleTimeContext->_saleContext))
            {
                Log::Write(Log::LT_ERROR, TIMEOUT_TIMER_FILE, 72,
                           L"[%s], %s; failed to post timeout event, saleId:0x%I64X, saleType:%d", MODULE_NAME, fn,
                           saleTimeContext->_saleId, static_cast<int>(saleTimeContext->_saleType));
            }
        }
        saleTimeContextManager->_lockList[index].Leave();
    }
}

// 0x31e20
bool TimeoutTimer::postTimeoutEvent(long long const saleId, char const saleType, SaleContext* const saleContext) const
{
    wchar_t const* const fn = L"TimeoutTimer::postTimeoutEvent";
    if (saleId <= 0 || static_cast<unsigned char>(saleType - 1) > 1 || saleContext == nullptr)
    {
        TIMEOUT_TIMER_CRASH(89,
                            L"== CRASH == [%s], %s; invalid parameter, saleId:0x%I64X, saleType:%d, "
                            L"saleContext:0x%p",
                            MODULE_NAME, fn, saleId, static_cast<int>(saleType), saleContext);
        return false;
    }

    if (saleType == kSaleTypeInstantSale)
    {
        // ❓ Alloc line: the call site has the line folded. 93 is a guess.
        void* const memory = Memory::_Manager[2]->Alloc(sizeof(InstantSaleTimeoutEvent), TIMEOUT_TIMER_FILE, 93);
        InstantSaleTimeoutEvent* const timeoutEvent =
            memory != nullptr ? ::new (memory) InstantSaleTimeoutEvent(saleId, saleContext) : nullptr;
        if (PostQueuedCompletionStatus(Network::iocpHandle(), 0, reinterpret_cast<ULONG_PTR>(timeoutEvent), nullptr))
            return true;
        Log::Write(Log::LT_ERROR, TIMEOUT_TIMER_FILE, 97,
                   L"[%s], %s; failed to post instant sale timeout event in iocp queue, saleId:0x%I64X, saleType:%d",
                   MODULE_NAME, fn, saleId, static_cast<int>(kSaleTypeInstantSale));
        // BUG: 0x31e20 timeoutEvent can be null here (Alloc failed); the call does not check it.
        timeoutEvent->removeReferenceCount(TIMEOUT_TIMER_FILE, 98);
        return false;
    }

    // ❓ Alloc line: the call site has the line folded. 104 is a guess.
    void* const memory = Memory::_Manager[2]->Alloc(sizeof(AuctionTimeoutEvent), TIMEOUT_TIMER_FILE, 104);
    AuctionTimeoutEvent* const timeoutEvent =
        memory != nullptr ? ::new (memory) AuctionTimeoutEvent(saleId, saleContext) : nullptr;
    if (PostQueuedCompletionStatus(Network::iocpHandle(), 0, reinterpret_cast<ULONG_PTR>(timeoutEvent), nullptr))
        return true;
    Log::Write(Log::LT_ERROR, TIMEOUT_TIMER_FILE, 108,
               L"[%s], %s; failed to post auction timeout event in iocp queue, saleId:0x%I64X, saleType:%d",
               MODULE_NAME, fn, saleId, static_cast<int>(kSaleTypeAuction));
    // BUG: 0x31e20 timeoutEvent can be null here (Alloc failed); the call does not check it.
    timeoutEvent->removeReferenceCount(TIMEOUT_TIMER_FILE, 109);
    return false;
}
