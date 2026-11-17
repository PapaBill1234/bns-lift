// UnsentPostChecker.obj (PostOfficeDaemon PDB).
#include "UnsentPostChecker.h"
#include <windows.h>
#include "Log.h"
#include "PostOfficeDaemon.h"
#include "UnsentPostContext.h"

#define UNSENT_POST_CHECKER_FILE L"UnsentPostChecker.cpp"
static wchar_t const* const MODULE_NAME = L"unsent post checker";  // PDB MODULE_NAME

static bool isStopState(int state)  // ❓ inlined switch
{
    return state == Daemon::STATE_STOPPED || state == Daemon::STATE_STOPPING ||
           state == Daemon::STATE_COOLDOWNING || state == Daemon::STATE_COOLDOWNED;
}

// 0xd770
bool UnsentPostChecker::HandleEvent(EventContext* context, unsigned long bytes)
{
    if (isStopState(Daemon::Instance->State))
        return true;

    Log::Write(Log::LT_DEBUG, UNSENT_POST_CHECKER_FILE, 23, L"[%s], %s; <BEGIN TIMER HANDLER>",
               MODULE_NAME, L"UnsentPostChecker::HandleEvent");
    PostOfficeDaemon::_instance->_unsentPostContextManager->CheckUnsentPost();
    Log::Write(Log::LT_DEBUG, UNSENT_POST_CHECKER_FILE, 27, L"[%s], %s; <END TIMER HANDLER>",
               MODULE_NAME, L"UnsentPostChecker::HandleEvent");

    if (isStopState(Daemon::Instance->State) ||
        PostOfficeDaemon::_instance->GlobalTimerQueue->Add(1000 * PostOfficeDaemon::_instance->_config->_deliveryRetryInterval,
                                                           this))
        return true;

    Log::Write(Log::LT_ERROR, UNSENT_POST_CHECKER_FILE, 32, L"[%s], %s; failed to add unsent post checker timer",
               MODULE_NAME, L"UnsentPostChecker::HandleEvent");
    return false;
}
