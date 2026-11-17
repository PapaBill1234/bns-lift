// RelayTimeoutChecker.obj (PostOfficeDaemon PDB).
#include "RelayTimeoutChecker.h"
#include <new>
#include <time.h>
#include <windows.h>
#include "Log.h"
#include "AlertSender.h"
#include "Memory.h"
#include "Network.h"
#include "PostOfficeDaemon.h"
#include "RelayContext.h"
#include "RelayTimeContext.h"
#include "RelayTimeoutEvent.h"

#define RELAY_TIMEOUT_CHECKER_FILE L"RelayTimeoutChecker.cpp"
static wchar_t const* const MODULE_NAME = L"relay timeout checker";  // PDB MODULE_NAME

#define RELAY_TIMEOUT_CHECKER_CRASH(line, fmt, ...)                                           \
    do                                                                                        \
    {                                                                                         \
        Log::Write(Log::LT_ERROR, RELAY_TIMEOUT_CHECKER_FILE, line, fmt, __VA_ARGS__);        \
        AlertSender::Write(RELAY_TIMEOUT_CHECKER_FILE, line, fmt, __VA_ARGS__);               \
    } while (0)

static bool isStopState(int state)  // ❓ inlined switch
{
    return state == Daemon::STATE_STOPPED || state == Daemon::STATE_STOPPING ||
           state == Daemon::STATE_COOLDOWNING || state == Daemon::STATE_COOLDOWNED;
}

// 0x1d700
bool RelayTimeoutChecker::HandleEvent(EventContext* context, unsigned long bytes)
{
    if (isStopState(Daemon::Instance->State))
        return true;

    Log::Write(Log::LT_DEBUG, RELAY_TIMEOUT_CHECKER_FILE, 24, L"[%s], %s; <BEGIN TIMER HANDLER>",
               MODULE_NAME, L"RelayTimeoutChecker::HandleEvent");
    checkRelayTimeout();
    Log::Write(Log::LT_DEBUG, RELAY_TIMEOUT_CHECKER_FILE, 28, L"[%s], %s; <END TIMER HANDLER>",
               MODULE_NAME, L"RelayTimeoutChecker::HandleEvent");

    if (isStopState(Daemon::Instance->State) || PostOfficeDaemon::_instance->GlobalTimerQueue->Add(1000, this))
        return true;

    Log::Write(Log::LT_ERROR, RELAY_TIMEOUT_CHECKER_FILE, 32, L"[%s], %s; failed to add relay timeout checker timer",
               MODULE_NAME, L"RelayTimeoutChecker::HandleEvent");
    return false;
}

// 0x1d830
void RelayTimeoutChecker::checkRelayTimeout()
{
    RelayTimeContextManager* const manager = PostOfficeDaemon::_instance->_relayTimeContextManager;
    if (manager->_lockList == nullptr || manager->_containerList == nullptr)
    {
        RELAY_TIMEOUT_CHECKER_CRASH(46,
                                    L"== CRASH == [%s], %s; invalid relaytime context manager, lockList:0x%p, containerList:0x%p",
                                    MODULE_NAME, L"RelayTimeoutChecker::checkRelayTimeout",
                                    manager->_lockList, manager->_containerList);
        return;
    }

    long long const currentTime = _time64(nullptr);
    if (currentTime == -1)
    {
        RELAY_TIMEOUT_CHECKER_CRASH(52, L"== CRASH == [%s], %s; time fuction error, currentTime:%I64d",
                                    MODULE_NAME, L"RelayTimeoutChecker::checkRelayTimeout", currentTime);
        return;
    }

    for (int index = 0; index < manager->_bucketCount; ++index)
    {
        manager->_lockList[index].Enter();
        RelayTimeContextManager::Container& container = manager->_containerList[index];
        for (RelayTimeContextManager::Container::iterator it = container.begin(); it != container.end(); ++it)
        {
            if (it->first._relayLimitTime >= currentTime)
                break;
            RelayTimeContext* const relayTimeContext = it->second;
            if (relayTimeContext == nullptr)
            {
                RELAY_TIMEOUT_CHECKER_CRASH(63,
                                            L"== CRASH == [%s], %s; relaytime context is null, relayTid:0x%I64X, relaytimeContext:0x%p",
                                            MODULE_NAME, L"RelayTimeoutChecker::checkRelayTimeout",
                                            it->first._relayTid, static_cast<RelayTimeContext*>(nullptr));
            }
            else if (!relayTimeContext->_disuse)
            {
                if (occurTimeoutEvent(relayTimeContext->_relayTid, relayTimeContext->_relayContext))
                {
                    relayTimeContext->_disuse = true;
                }
                else
                {
                    Log::Write(Log::LT_ERROR, RELAY_TIMEOUT_CHECKER_FILE, 69,
                               L"[%s], %s; failed to occur relay timeout event, relayTid:0x%I64X",
                               MODULE_NAME, L"RelayTimeoutChecker::checkRelayTimeout", relayTimeContext->_relayTid);
                }
            }
        }
        manager->_lockList[index].Leave();
    }
}

// 0x1db40
bool RelayTimeoutChecker::occurTimeoutEvent(unsigned long long const relayTid, RelayContext* const relayContext) const
{
    if (relayTid == 0 || relayContext == nullptr)
    {
        RELAY_TIMEOUT_CHECKER_CRASH(88, L"== CRASH == [%s], %s; invalid parameter, relayTid:0x%I64X, relayContext:0x%p",
                                    MODULE_NAME, L"RelayTimeoutChecker::occurTimeoutEvent", relayTid, relayContext);
        return false;
    }

    void* const memory = Memory::_Manager[2]->Alloc(sizeof(RelayTimeoutEvent), RELAY_TIMEOUT_CHECKER_FILE, 92);
    RelayTimeoutEvent* const relayTimeoutEvent =
        memory != nullptr ? ::new (memory) RelayTimeoutEvent(relayTid, relayContext) : nullptr;

    if (PostQueuedCompletionStatus(Network::iocpHandle(), 0, reinterpret_cast<ULONG_PTR>(relayTimeoutEvent), nullptr))
        return true;

    Log::Write(RELAY_TIMEOUT_CHECKER_FILE, 95, GetLastError(),
               L"[%s], %s; exception occurred; failed to occur relay timeout event, relayTid:0x%I64X",
               MODULE_NAME, L"RelayTimeoutChecker::occurTimeoutEvent", relayTid);
    // BUG: 0x1db40 relayTimeoutEvent can be null here (Alloc failed); the call does not check it.
    relayTimeoutEvent->removeReferenceCount(RELAY_TIMEOUT_CHECKER_FILE, 96);
    return false;
}
