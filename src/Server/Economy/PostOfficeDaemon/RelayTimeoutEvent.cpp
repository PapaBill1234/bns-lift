// RelayTimeoutEvent.obj (PostOfficeDaemon PDB).
#include "RelayTimeoutEvent.h"
#include "Log.h"
#include "RelayContext.h"

#define RELAY_TIMEOUT_EVENT_FILE L"RelayTimeoutEvent.cpp"
static wchar_t const* const MODULE_NAME = L"relay timeout event";  // PDB MODULE_NAME

// LIFT: inlined in RelayTimeoutChecker::occurTimeoutEvent (0x1db40). RelayTimeoutEvent.obj (Mod 0032) has no constructor.
RelayTimeoutEvent::RelayTimeoutEvent(unsigned long long relayTid, RelayContext* const relayContext)
    : _relayTid(relayTid), _relayContext(relayContext)
{
    _relayContext->addReferenceCount(RELAY_TIMEOUT_EVENT_FILE, 25);
}

// 0x1dcf0
unsigned int RelayTimeoutEvent::EventId() const
{
    return 129;
}

// 0x1dd00
RelayTimeoutEvent::~RelayTimeoutEvent()
{
    if (_relayContext != nullptr)
    {
        _relayContext->removeReferenceCount(RELAY_TIMEOUT_EVENT_FILE, 31);
        _relayContext = nullptr;
    }
}

// 0x1dd60
bool RelayTimeoutEvent::HandleEvent(EventContext* context, unsigned long param)
{
    Log::Write(Log::LT_DEBUG, RELAY_TIMEOUT_EVENT_FILE, 38, L"[%s], %s; <BEGIN EVENT HANDLER>",
               MODULE_NAME, L"RelayTimeoutEvent::HandleEvent");
    if (!_relayContext->ProcessRelayTimeout())
    {
        Log::Write(Log::LT_ERROR, RELAY_TIMEOUT_EVENT_FILE, 41, L"[%s], %s; failed to process relay timeout, relayTid:0x%I64X",
                   MODULE_NAME, L"RelayTimeoutEvent::HandleEvent", _relayTid);
    }
    Log::Write(Log::LT_DEBUG, RELAY_TIMEOUT_EVENT_FILE, 44, L"[%s], %s; <END EVENT HANDLER>",
               MODULE_NAME, L"RelayTimeoutEvent::HandleEvent");
    removeReferenceCount(RELAY_TIMEOUT_EVENT_FILE, 46);
    return true;
}
