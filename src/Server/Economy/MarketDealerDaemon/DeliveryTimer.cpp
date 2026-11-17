// DeliveryTimer.obj (MarketDealerDaemon PDB).
#include "DeliveryTimer.h"
#include <windows.h>
#include "Log.h"
#include "AlertSender.h"
#include "Daemon.h"
#include "TimerQueue.h"
#include "MarketDealerDaemon.h"
#include "AgentChannel.h"
#include "DeliveryContext.h"
#include "Postman.h"

#define DELIVERY_TIMER_FILE L"DeliveryTimer.cpp"
static wchar_t const* const MODULE_NAME = L"delivery timer";  // PDB MODULE_NAME

#define DELIVERY_TIMER_CRASH(line, fmt, ...)                                    \
    do                                                                          \
    {                                                                           \
        Log::Write(Log::LT_ERROR, DELIVERY_TIMER_FILE, line, fmt, __VA_ARGS__); \
        AlertSender::Write(DELIVERY_TIMER_FILE, line, fmt, __VA_ARGS__);        \
    } while (0)

static bool isStopState(int state)  // LIFT: inlined switch
{
    return state == Daemon::STATE_STOPPED || state == Daemon::STATE_STOPPING ||
           state == Daemon::STATE_COOLDOWNING || state == Daemon::STATE_COOLDOWNED;
}

// 0x82e0
bool DeliveryTimer::HandleEvent(EventContext* context, unsigned long bytes)
{
    if (isStopState(Daemon::Instance->State))
        return true;

    Log::Write(Log::LT_DEBUG, DELIVERY_TIMER_FILE, 25, L"[%s], %s; <BEGIN TIMER HANDLER>", MODULE_NAME,
               L"DeliveryTimer::HandleEvent");
    checkDelivery();
    Log::Write(Log::LT_DEBUG, DELIVERY_TIMER_FILE, 29, L"[%s], %s; <END TIMER HANDLER>", MODULE_NAME,
               L"DeliveryTimer::HandleEvent");

    if (isStopState(Daemon::Instance->State) ||
        MarketDealerDaemon::_instance->AddTimer(1000 * MarketDealerDaemon::_instance->_config->_deliveryCheckInterval,
                                                this))
        return true;

    Log::Write(Log::LT_ERROR, DELIVERY_TIMER_FILE, 34, L"[%s], %s; failed to add delivery timer", MODULE_NAME,
               L"DeliveryTimer::HandleEvent");
    return false;
}

// 0x8420
void DeliveryTimer::checkDelivery() const
{
    wchar_t const* const fn = L"DeliveryTimer::checkDelivery";
    if (MarketDealerDaemon::_instance->_agentChannelManager->_marketAgentChannel == nullptr)
    {
        Log::Write(Log::LT_DEBUG, DELIVERY_TIMER_FILE, 48,
                   L"[%s], %s; market agent is not connecting; cannot send packet; timer will try to send at next "
                   L"time again",
                   MODULE_NAME, fn);
        return;
    }

    DeliveryContextManager* const deliveryContextManager = MarketDealerDaemon::_instance->_deliveryContextManager;
    if (deliveryContextManager->_lockList == nullptr || deliveryContextManager->_containerList == nullptr)
    {
        DELIVERY_TIMER_CRASH(54,
                             L"== CRASH == [%s], %s; invalid delivery context manager, lockList:0x%p, "
                             L"containerList:0x%p",
                             MODULE_NAME, fn, deliveryContextManager->_lockList,
                             deliveryContextManager->_containerList);
        return;
    }

    for (int index = 0; index < deliveryContextManager->_bucketCount; ++index)
    {
        deliveryContextManager->_lockList[index].Enter();
        DeliveryContextManager::Container& container = deliveryContextManager->_containerList[index];
        for (DeliveryContextManager::Container::iterator it = container.begin(); it != container.end(); ++it)
        {
            DeliveryContext* const deliveryContext = it->second;
            long long const deliveryId = it->first;
            if (deliveryContext == nullptr)
            {
                DELIVERY_TIMER_CRASH(65,
                                     L"== CRASH == [%s], %s; delivery context is null, deliveryId:0x%I64X, "
                                     L"deliveryContext:0x%p",
                                     MODULE_NAME, fn, deliveryId, static_cast<DeliveryContext*>(nullptr));
                continue;
            }
            deliveryContext->addReferenceCount(DELIVERY_TIMER_FILE, 69);
            deliveryContext->_lock.Enter();
            char const jobStatus = deliveryContext->_deliveryInfo._jobStatus;
            if ((jobStatus == DeliveryInfo::JOBSTATUS_DELIVERY_READY ||
                 jobStatus == DeliveryInfo::JOBSTATUS_RETRY_READY) &&
                !Postman::DeliverPost(deliveryContext))
            {
                Log::Write(Log::LT_ERROR, DELIVERY_TIMER_FILE, 77,
                           L"[%s], %s; failed to deliver post, deliveryId:0x%I64X", MODULE_NAME, fn, deliveryId);
                deliveryContext->_lock.Leave();
                deliveryContext->removeReferenceCount(DELIVERY_TIMER_FILE, 79);
            }
            else
            {
                deliveryContext->_lock.Leave();
                deliveryContext->removeReferenceCount(DELIVERY_TIMER_FILE, 85);
            }
        }
        deliveryContextManager->_lockList[index].Leave();
    }
}
