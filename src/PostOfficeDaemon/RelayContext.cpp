// RelayContext.obj (PostOfficeDaemon PDB).
#include "RelayContext.h"
#include <time.h>
#include "Log.h"
#include "AlertSender.h"
#include "CrashHandler.h"
#include "PostOfficeDaemon.h"
#include "RelayTimeContext.h"

#define RELAY_CONTEXT_FILE L"RelayContext.cpp"
#define RELAY_CONTEXT_TAG L"relay context"

// The original writes each "== CRASH ==" text to Log (LT_ERROR) and to AlertSender.
#define RELAY_CONTEXT_CRASH(line, fmt, ...)                                                   \
    do                                                                                        \
    {                                                                                         \
        Log::Write(Log::LT_ERROR, RELAY_CONTEXT_FILE, line, fmt, __VA_ARGS__);                \
        AlertSender::Write(RELAY_CONTEXT_FILE, line, fmt, __VA_ARGS__);                       \
    } while (0)

#define LOCK_H_WIDE L"e:\\dailybuild02\\postofficedaemon-common-0.0.348\\depot\\branch\\348nc\\program\\server\\bloodlib\\include\\Lock.h"
#define LOCK_H_NARROW "e:\\dailybuild02\\postofficedaemon-common-0.0.348\\depot\\branch\\348nc\\program\\server\\bloodlib\\include\\Lock.h"

unsigned long long RelayContextManager::_idSeed = 0;  // ❓ initial value

// ---- AutoCS (Lock.h, inline in the original) ----

// ❓ inlined
AutoCS::AutoCS(CriticalSection* cs) : CS(cs), EnterCount(0)
{
    if (cs == nullptr)
    {
        Log::Write(Log::LT_ERROR, LOCK_H_WIDE, 113, L"== CRASH == ASSERT CRASH");
        AlertSender::Write(LOCK_H_WIDE, 113, L"== CRASH == ASSERT CRASH");
        CrashHandler::MakeCrash(LOCK_H_NARROW, 113, L"");
    }
    EnterCriticalSection(&CS->CS);
    EnterCount = 1;
}

// 0x3c80
AutoCS::~AutoCS()
{
    Leave();
}

// 0x3c90
void AutoCS::Leave()
{
    if (CS == nullptr)
    {
        Log::Write(Log::LT_ERROR, LOCK_H_WIDE, 122, L"== CRASH == ASSERT CRASH");
        AlertSender::Write(LOCK_H_WIDE, 122, L"== CRASH == ASSERT CRASH");
        CrashHandler::MakeCrash(LOCK_H_NARROW, 122, L"");
    }
    if (EnterCount == 1)
        LeaveCriticalSection(&CS->CS);
    --EnterCount;  // BUG: 0x3c90 the dtor after an explicit Leave makes EnterCount wrap to 0xFFFFFFFF.
}

// ---- RelayContext ----

// 0x1bb30
bool RelayContext::ProcessRelayRequest(Channel* const channel)
{
    if (channel == nullptr)
    {
        RELAY_CONTEXT_CRASH(25, L"== CRASH == [%s], %s; invalid parameter, channel:0x%p",
                            RELAY_CONTEXT_TAG, L"RelayContext::ProcessRelayRequest", nullptr);
        return false;
    }

    unsigned long long const relayTid = _economyHeader._relayTid;
    AutoCS lock(&_lock);

    if (_relayStatus != RELAYSTATUS_INIT)
    {
        RELAY_CONTEXT_CRASH(36, L"== CRASH == [%s], %s; relay status is not init, relayTid:0x%I64X, relayStatus:%d",
                            RELAY_CONTEXT_TAG, L"RelayContext::ProcessRelayRequest", relayTid, _relayStatus);
        return false;
    }

    PostOfficeDaemon* const daemon = PostOfficeDaemon::_instance;
    if (!daemon->_relayContextManager->AddContext(this))
    {
        RELAY_CONTEXT_CRASH(41, L"== CRASH == [%s], %s; exception occurred; faile to add relay context, relayTid:0x%I64X",
                            RELAY_CONTEXT_TAG, L"RelayContext::ProcessRelayRequest", relayTid);
        return false;
    }

    bool failed = false;
    if (daemon->_config->_relayTimeoutInterval > 0)
    {
        long long const relayLimitTime = _time64(nullptr) + daemon->_config->_relayTimeoutInterval;
        if (!daemon->_relayTimeContextManager->AddContext(relayTid, relayLimitTime, this))
        {
            RELAY_CONTEXT_CRASH(49,
                                L"== CRASH == [%s], %s; exception occurred; failed to add relaytime context, relayTid:0x%I64X, relayLimitTime:%I64d",
                                RELAY_CONTEXT_TAG, L"RelayContext::ProcessRelayRequest", relayTid, relayLimitTime);
            failed = true;
        }
        else
        {
            _relayLimitTime = relayLimitTime;
        }
    }

    if (!failed && !processRelayRequest(channel))
    {
        Log::Write(Log::LT_ERROR, RELAY_CONTEXT_FILE, 57, L"[%s], %s; failed to send relay request packet, relayTid:0x%I64X",
                   RELAY_CONTEXT_TAG, L"RelayContext::ProcessRelayRequest", relayTid);
        failed = true;
    }

    if (failed)
    {
        lock.Leave();
        if (!PostOfficeDaemon::_instance->_relayContextManager->RemoveContext(relayTid))
        {
            RELAY_CONTEXT_CRASH(69, L"== CRASH == [%s], %s; exception occurred; faile to remove relay context, relayTid:0x%I64X",
                                RELAY_CONTEXT_TAG, L"RelayContext::ProcessRelayRequest", relayTid);
        }
        if (_relayLimitTime > 0 &&
            !PostOfficeDaemon::_instance->_relayTimeContextManager->RemoveContext(relayTid, _relayLimitTime))
        {
            RELAY_CONTEXT_CRASH(74,
                                L"== CRASH == [%s], %s; exception occurred; faile to remove relaytime context, relayTid:0x%I64X, relayLimitTime:%I64d",
                                RELAY_CONTEXT_TAG, L"RelayContext::ProcessRelayRequest", relayTid, _relayLimitTime);
        }
        return false;
    }

    _relayStatus = RELAYSTATUS_WAITING;
    lock.Leave();
    return true;
}

// 0x1c090
bool RelayContext::ProcessRelayResponse(RelayResponse* const response)
{
    if (response == nullptr)
    {
        RELAY_CONTEXT_CRASH(84, L"== CRASH == [%s], %s; invalid parameter, response:0x%p",
                            RELAY_CONTEXT_TAG, L"RelayContext::ProcessRelayResponse", nullptr);
        return false;
    }

    unsigned long long const relayTid = _economyHeader._relayTid;
    if (response->_resultState != RelayResponse::RESULTSTATE_SUCCESS &&
        response->_resultState != RelayResponse::RESULTSTATE_FAILURE &&
        response->_resultState != RelayResponse::RESULTSTATE_RELAY_ERROR)
    {
        RELAY_CONTEXT_CRASH(88, L"== CRASH == [%s], %s; invalid relay response result state, relayTid:0x%I64X, resultState:%d",
                            RELAY_CONTEXT_TAG, L"RelayContext::ProcessRelayResponse", relayTid, response->_resultState);
        return false;
    }

    AutoCS lock(&_lock);
    if (_relayStatus != RELAYSTATUS_WAITING)
    {
        Log::Write(Log::LT_ERROR, RELAY_CONTEXT_FILE, 99, L"[%s], %s; relay status is not waiting, relayTid:0x%I64X, relayStatus:%d",
                   RELAY_CONTEXT_TAG, L"RelayContext::ProcessRelayResponse", relayTid, _relayStatus);
        lock.Leave();
        return false;
    }

    initResponse(response);
    if (!processRelayResponse())
    {
        Log::Write(Log::LT_ERROR, RELAY_CONTEXT_FILE, 106, L"[%s], %s; failed to process relay response, relayTid:0x%I64X",
                   RELAY_CONTEXT_TAG, L"RelayContext::ProcessRelayResponse", relayTid);
    }
    _relayStatus = RELAYSTATUS_FINISH;
    lock.Leave();

    PostOfficeDaemon* const daemon = PostOfficeDaemon::_instance;
    if (daemon->_config->_relayTimeoutInterval > 0 &&
        !daemon->_relayTimeContextManager->RemoveContext(relayTid, _relayLimitTime))
    {
        RELAY_CONTEXT_CRASH(117,
                            L"== CRASH == [%s], %s; exception occurred; failed to remove relaytime context, relayTid:0x%I64X, relayLimitTime:%I64d",
                            RELAY_CONTEXT_TAG, L"RelayContext::ProcessRelayResponse", relayTid, _relayLimitTime);
    }
    if (!PostOfficeDaemon::_instance->_relayContextManager->RemoveContext(relayTid))
    {
        RELAY_CONTEXT_CRASH(122, L"== CRASH == [%s], %s; exception occurred; faile to remove relay context, relayTid:0x%I64X",
                            RELAY_CONTEXT_TAG, L"RelayContext::ProcessRelayResponse", relayTid);
    }
    return true;
}

// 0x1c480
bool RelayContext::ProcessRelayTimeout()
{
    unsigned long long const relayTid = _economyHeader._relayTid;
    AutoCS lock(&_lock);
    if (_relayStatus != RELAYSTATUS_WAITING)
    {
        Log::Write(Log::LT_ERROR, RELAY_CONTEXT_FILE, 137, L"[%s], %s; relay status is not waiting, relayTid:0x%I64X, relayStatus:%d",
                   RELAY_CONTEXT_TAG, L"RelayContext::ProcessRelayTimeout", relayTid, _relayStatus);
        lock.Leave();
        return false;
    }

    if (processRelayTimeout())
    {
        Log::Write(Log::LT_ERROR, RELAY_CONTEXT_FILE, 145, L"[%s], %s; succeeded to process relay timeout, relayTid:0x%I64X",
                   RELAY_CONTEXT_TAG, L"RelayContext::ProcessRelayTimeout", relayTid);
    }
    else
    {
        Log::Write(Log::LT_ERROR, RELAY_CONTEXT_FILE, 142, L"[%s], %s; failed to process relay timeout, relayTid:0x%I64X",
                   RELAY_CONTEXT_TAG, L"RelayContext::ProcessRelayTimeout", relayTid);
    }
    _relayStatus = RELAYSTATUS_TIMEOUT;
    lock.Leave();

    PostOfficeDaemon* const daemon = PostOfficeDaemon::_instance;
    if (daemon->_config->_relayTimeoutInterval > 0 &&
        !daemon->_relayTimeContextManager->RemoveContext(relayTid, _relayLimitTime))
    {
        RELAY_CONTEXT_CRASH(153,
                            L"== CRASH == [%s], %s; exception occurred; failed to remove relaytime context, relayTid:0x%I64X, relayLimitTime:%I64d",
                            RELAY_CONTEXT_TAG, L"RelayContext::ProcessRelayTimeout", relayTid, _relayLimitTime);
    }
    if (!PostOfficeDaemon::_instance->_relayContextManager->RemoveContext(relayTid))
    {
        RELAY_CONTEXT_CRASH(158, L"== CRASH == [%s], %s; exception occurred; failed to remove relay context, relayTid:0x%I64X",
                            RELAY_CONTEXT_TAG, L"RelayContext::ProcessRelayTimeout", relayTid);
    }
    return true;
}

// ---- RelayContextManager ----

// 0x1c780
bool RelayContextManager::initContextManager()
{
    if (_lockList != nullptr || _containerList != nullptr)
    {
        RELAY_CONTEXT_CRASH(212, L"== CRASH == [%s], %s; relay context manager is already initialized, lockList:0x%p, containerList:0x%p",
                            RELAY_CONTEXT_TAG, L"RelayContextManager::initContextManager", _lockList, _containerList);
        return false;
    }
    _lockList = liftArrayNew<CriticalSection>(_bucketCount, RELAY_CONTEXT_FILE, 216);
    _containerList = liftArrayNew<Container>(_bucketCount, RELAY_CONTEXT_FILE, 217);
    return true;
}

// 0x1c910
RelayContext* RelayContextManager::GetContext(unsigned long long relayTid)
{
    if (relayTid == 0)
    {
        RELAY_CONTEXT_CRASH(225, L"== CRASH == [%s], %s; invalid parameter, relayTid:0x%I64X",
                            RELAY_CONTEXT_TAG, L"RelayContextManager::GetContext", 0ULL);
        return nullptr;
    }
    if (_lockList == nullptr || _containerList == nullptr)
    {
        RELAY_CONTEXT_CRASH(229, L"== CRASH == [%s], %s; invalid relay context manager, lockList:0x%p, containerList:0x%p",
                            RELAY_CONTEXT_TAG, L"RelayContextManager::GetContext", _lockList, _containerList);
        return nullptr;
    }

    int const index = static_cast<int>(relayTid % _bucketCount);
    _lockList[index].Enter();
    Container::iterator it = _containerList[index].find(relayTid);
    if (it == _containerList[index].end())
    {
        _lockList[index].Leave();
        return nullptr;
    }
    RelayContext* const relayContext = it->second;
    if (relayContext != nullptr)
    {
        relayContext->addReferenceCount(RELAY_CONTEXT_FILE, 245);
        _lockList[index].Leave();
        return relayContext;
    }
    _lockList[index].Leave();
    RELAY_CONTEXT_CRASH(242, L"== CRASH == [%s], %s; relay context is null, relayTid:0x%I64X, relayContext:0x%p",
                        RELAY_CONTEXT_TAG, L"RelayContextManager::GetContext", relayTid, nullptr);
    return nullptr;
}

// 0x1cb80
bool RelayContextManager::AddContext(RelayContext* const relayContext)
{
    if (relayContext == nullptr)
    {
        RELAY_CONTEXT_CRASH(255, L"== CRASH == [%s], %s; invalid parameter, relayContext:0x%p",
                            RELAY_CONTEXT_TAG, L"RelayContextManager::AddContext", nullptr);
        return false;
    }
    if (_lockList == nullptr || _containerList == nullptr)
    {
        RELAY_CONTEXT_CRASH(259, L"== CRASH == [%s], %s; invalid relay context manager, lockList:0x%p, containerList:0x%p",
                            RELAY_CONTEXT_TAG, L"RelayContextManager::AddContext", _lockList, _containerList);
        return false;
    }
    unsigned long long const relayTid = relayContext->_economyHeader._relayTid;
    if (relayTid == 0)
    {
        RELAY_CONTEXT_CRASH(265, L"== CRASH == [%s], %s; invalid relay tid, relayTid:0x%I64X",
                            RELAY_CONTEXT_TAG, L"RelayContextManager::AddContext", 0ULL);
        return false;
    }

    int const index = static_cast<int>(relayTid % _bucketCount);
    _lockList[index].Enter();
    if (_containerList[index].insert(Container::value_type(relayTid, relayContext)).second)
    {
        relayContext->addReferenceCount(RELAY_CONTEXT_FILE, 280);
        InterlockedIncrement(&_contextCount);
        _lockList[index].Leave();
        return true;
    }
    _lockList[index].Leave();
    Log::Write(Log::LT_ERROR, RELAY_CONTEXT_FILE, 276, L"[%s], %s; failed to add relay context, relayTid:0x%I64X",
               RELAY_CONTEXT_TAG, L"RelayContextManager::AddContext", relayTid);
    return false;
}

// 0x1ce10
bool RelayContextManager::RemoveContext(unsigned long long relayTid)
{
    if (relayTid == 0)
    {
        RELAY_CONTEXT_CRASH(292, L"== CRASH == [%s], %s; invalid parameter, relayTid:0x%I64X",
                            RELAY_CONTEXT_TAG, L"RelayContextManager::RemoveContext", 0ULL);
        return false;
    }
    if (_lockList == nullptr || _containerList == nullptr)
    {
        RELAY_CONTEXT_CRASH(296, L"== CRASH == [%s], %s; invalid relay context manager, lockList:0x%p, containerList:0x%p",
                            RELAY_CONTEXT_TAG, L"RelayContextManager::RemoveContext", _lockList, _containerList);
        return false;
    }

    int const index = static_cast<int>(relayTid % _bucketCount);
    _lockList[index].Enter();
    Container::iterator it = _containerList[index].find(relayTid);
    if (it == _containerList[index].end())
    {
        _lockList[index].Leave();
        Log::Write(Log::LT_ERROR, RELAY_CONTEXT_FILE, 306, L"[%s], %s; no such relay context, relayTid:0x%I64X",
                   RELAY_CONTEXT_TAG, L"RelayContextManager::RemoveContext", relayTid);
        return false;
    }
    RelayContext* const relayContext = it->second;
    if (relayContext != nullptr)
    {
        _containerList[index].erase(it);
        relayContext->removeReferenceCount(RELAY_CONTEXT_FILE, 318);
        InterlockedDecrement(&_contextCount);
        _lockList[index].Leave();
        return true;
    }
    _lockList[index].Leave();
    RELAY_CONTEXT_CRASH(313, L"== CRASH == [%s], %s; relay context is null, relayTid:0x%I64X, relayContext:0x%p",
                        RELAY_CONTEXT_TAG, L"RelayContextManager::RemoveContext", relayTid, nullptr);
    return false;
}
