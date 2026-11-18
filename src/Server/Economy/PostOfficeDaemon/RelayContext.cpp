// RelayContext.obj (PostOfficeDaemon PDB).
// LIFT: PostOfficeDaemon build path of StlMemory.h, mixed case in this module (HR strings). Keeps the _Erase copies apart from the lower-case ones (no ICF fold).
#define LIFT_STLMEMORY_FILE \
    L"E:\\DailyBuild02\\PostOfficeDaemon-Common-0.0.348\\depot\\Branch\\348NC\\Program\\Server\\BloodLib\\include\\StlMemory.h"
#include "RelayContext.h"
#include <time.h>
#include "Log.h"
#include "AlertSender.h"
#include "CrashHandler.h"
#include "PostOfficeDaemon.h"
#include "RelayTimeContext.h"

#define RELAY_CONTEXT_FILE L"RelayContext.cpp"
static wchar_t const* const MODULE_NAME = L"relay context";  // PDB MODULE_NAME

// The original writes each "== CRASH ==" text to Log (LT_ERROR) and to AlertSender.
#define RELAY_CONTEXT_CRASH(line, fmt, ...)                                                   \
    do                                                                                        \
    {                                                                                         \
        Log::Write(Log::LT_ERROR, RELAY_CONTEXT_FILE, line, fmt, __VA_ARGS__);                \
        AlertSender::Write(RELAY_CONTEXT_FILE, line, fmt, __VA_ARGS__);                       \
    } while (0)

unsigned long long RelayContextManager::_idSeed = 0xFFFFFFFFFFFFFFFFULL;  // .data rva 0x98BE0

// ---- RelayContext ----

// 0x1bb30
bool RelayContext::ProcessRelayRequest(Channel* const channel)
{
    if (channel == nullptr)
    {
        RELAY_CONTEXT_CRASH(25, L"== CRASH == [%s], %s; invalid parameter, channel:0x%p",
                            MODULE_NAME, L"RelayContext::ProcessRelayRequest", nullptr);
        return false;
    }

    unsigned long long const relayTid = _economyHeader._relayTid;
    AutoCS lock(&_lock);

    if (_relayStatus != RELAYSTATUS_INIT)
    {
        RELAY_CONTEXT_CRASH(36, L"== CRASH == [%s], %s; relay status is not init, relayTid:0x%I64X, relayStatus:%d",
                            MODULE_NAME, L"RelayContext::ProcessRelayRequest", relayTid, _relayStatus);
        return false;
    }

    PostOfficeDaemon* const daemon = PostOfficeDaemon::_instance;
    if (!daemon->_relayContextManager->AddContext(this))
    {
        RELAY_CONTEXT_CRASH(41, L"== CRASH == [%s], %s; exception occurred; faile to add relay context, relayTid:0x%I64X",
                            MODULE_NAME, L"RelayContext::ProcessRelayRequest", relayTid);
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
                                MODULE_NAME, L"RelayContext::ProcessRelayRequest", relayTid, relayLimitTime);
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
                   MODULE_NAME, L"RelayContext::ProcessRelayRequest", relayTid);
        failed = true;
    }

    if (failed)
    {
        lock.Leave();
        if (!PostOfficeDaemon::_instance->_relayContextManager->RemoveContext(relayTid))
        {
            RELAY_CONTEXT_CRASH(69, L"== CRASH == [%s], %s; exception occurred; faile to remove relay context, relayTid:0x%I64X",
                                MODULE_NAME, L"RelayContext::ProcessRelayRequest", relayTid);
        }
        if (_relayLimitTime > 0 &&
            !PostOfficeDaemon::_instance->_relayTimeContextManager->RemoveContext(relayTid, _relayLimitTime))
        {
            RELAY_CONTEXT_CRASH(74,
                                L"== CRASH == [%s], %s; exception occurred; faile to remove relaytime context, relayTid:0x%I64X, relayLimitTime:%I64d",
                                MODULE_NAME, L"RelayContext::ProcessRelayRequest", relayTid, _relayLimitTime);
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
                            MODULE_NAME, L"RelayContext::ProcessRelayResponse", nullptr);
        return false;
    }

    unsigned long long const relayTid = _economyHeader._relayTid;
    if (response->_resultState != RelayResponse::RESULTSTATE_SUCCESS &&
        response->_resultState != RelayResponse::RESULTSTATE_FAILURE &&
        response->_resultState != RelayResponse::RESULTSTATE_RELAY_ERROR)
    {
        RELAY_CONTEXT_CRASH(88, L"== CRASH == [%s], %s; invalid relay response result state, relayTid:0x%I64X, resultState:%d",
                            MODULE_NAME, L"RelayContext::ProcessRelayResponse", relayTid, response->_resultState);
        return false;
    }

    AutoCS lock(&_lock);
    if (_relayStatus != RELAYSTATUS_WAITING)
    {
        Log::Write(Log::LT_ERROR, RELAY_CONTEXT_FILE, 99, L"[%s], %s; relay status is not waiting, relayTid:0x%I64X, relayStatus:%d",
                   MODULE_NAME, L"RelayContext::ProcessRelayResponse", relayTid, _relayStatus);
        lock.Leave();
        return false;
    }

    initResponse(response);
    if (!processRelayResponse())
    {
        Log::Write(Log::LT_ERROR, RELAY_CONTEXT_FILE, 106, L"[%s], %s; failed to process relay response, relayTid:0x%I64X",
                   MODULE_NAME, L"RelayContext::ProcessRelayResponse", relayTid);
    }
    _relayStatus = RELAYSTATUS_FINISH;
    lock.Leave();

    PostOfficeDaemon* const daemon = PostOfficeDaemon::_instance;
    if (daemon->_config->_relayTimeoutInterval > 0 &&
        !daemon->_relayTimeContextManager->RemoveContext(relayTid, _relayLimitTime))
    {
        RELAY_CONTEXT_CRASH(117,
                            L"== CRASH == [%s], %s; exception occurred; failed to remove relaytime context, relayTid:0x%I64X, relayLimitTime:%I64d",
                            MODULE_NAME, L"RelayContext::ProcessRelayResponse", relayTid, _relayLimitTime);
    }
    if (!PostOfficeDaemon::_instance->_relayContextManager->RemoveContext(relayTid))
    {
        RELAY_CONTEXT_CRASH(122, L"== CRASH == [%s], %s; exception occurred; faile to remove relay context, relayTid:0x%I64X",
                            MODULE_NAME, L"RelayContext::ProcessRelayResponse", relayTid);
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
                   MODULE_NAME, L"RelayContext::ProcessRelayTimeout", relayTid, _relayStatus);
        lock.Leave();
        return false;
    }

    if (processRelayTimeout())
    {
        Log::Write(Log::LT_ERROR, RELAY_CONTEXT_FILE, 145, L"[%s], %s; succeeded to process relay timeout, relayTid:0x%I64X",
                   MODULE_NAME, L"RelayContext::ProcessRelayTimeout", relayTid);
    }
    else
    {
        Log::Write(Log::LT_ERROR, RELAY_CONTEXT_FILE, 142, L"[%s], %s; failed to process relay timeout, relayTid:0x%I64X",
                   MODULE_NAME, L"RelayContext::ProcessRelayTimeout", relayTid);
    }
    _relayStatus = RELAYSTATUS_TIMEOUT;
    lock.Leave();

    PostOfficeDaemon* const daemon = PostOfficeDaemon::_instance;
    if (daemon->_config->_relayTimeoutInterval > 0 &&
        !daemon->_relayTimeContextManager->RemoveContext(relayTid, _relayLimitTime))
    {
        RELAY_CONTEXT_CRASH(153,
                            L"== CRASH == [%s], %s; exception occurred; failed to remove relaytime context, relayTid:0x%I64X, relayLimitTime:%I64d",
                            MODULE_NAME, L"RelayContext::ProcessRelayTimeout", relayTid, _relayLimitTime);
    }
    if (!PostOfficeDaemon::_instance->_relayContextManager->RemoveContext(relayTid))
    {
        RELAY_CONTEXT_CRASH(158, L"== CRASH == [%s], %s; exception occurred; failed to remove relay context, relayTid:0x%I64X",
                            MODULE_NAME, L"RelayContext::ProcessRelayTimeout", relayTid);
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
                            MODULE_NAME, L"RelayContextManager::initContextManager", _lockList, _containerList);
        return false;
    }
    _lockList = liftArrayNew(CriticalSection, _bucketCount, RELAY_CONTEXT_FILE, 216);
    _containerList = liftArrayNew(Container, _bucketCount, RELAY_CONTEXT_FILE, 217);
    return true;
}

// 0x1c910
RelayContext* RelayContextManager::GetContext(unsigned long long relayTid)
{
    if (relayTid == 0)
    {
        RELAY_CONTEXT_CRASH(225, L"== CRASH == [%s], %s; invalid parameter, relayTid:0x%I64X",
                            MODULE_NAME, L"RelayContextManager::GetContext", 0ULL);
        return nullptr;
    }
    if (_lockList == nullptr || _containerList == nullptr)
    {
        RELAY_CONTEXT_CRASH(229, L"== CRASH == [%s], %s; invalid relay context manager, lockList:0x%p, containerList:0x%p",
                            MODULE_NAME, L"RelayContextManager::GetContext", _lockList, _containerList);
        return nullptr;
    }

    int const index = static_cast<int>(relayTid % _bucketCount);
    RelayContext* relayContext = nullptr;
    _lockList[index].Enter();
    Container::iterator it = _containerList[index].find(relayTid);
    if (it != _containerList[index].end())
    {
        relayContext = it->second;
        if (relayContext == nullptr)
        {
            _lockList[index].Leave();
            RELAY_CONTEXT_CRASH(242, L"== CRASH == [%s], %s; relay context is null, relayTid:0x%I64X, relayContext:0x%p",
                                MODULE_NAME, L"RelayContextManager::GetContext", relayTid, nullptr);
            return nullptr;
        }
        relayContext->addReferenceCount(RELAY_CONTEXT_FILE, 245);
    }
    _lockList[index].Leave();
    return relayContext;
}

// 0x1cb80
bool RelayContextManager::AddContext(RelayContext* const relayContext)
{
    if (relayContext == nullptr)
    {
        RELAY_CONTEXT_CRASH(255, L"== CRASH == [%s], %s; invalid parameter, relayContext:0x%p",
                            MODULE_NAME, L"RelayContextManager::AddContext", nullptr);
        return false;
    }
    if (_lockList == nullptr || _containerList == nullptr)
    {
        RELAY_CONTEXT_CRASH(259, L"== CRASH == [%s], %s; invalid relay context manager, lockList:0x%p, containerList:0x%p",
                            MODULE_NAME, L"RelayContextManager::AddContext", _lockList, _containerList);
        return false;
    }
    unsigned long long const relayTid = relayContext->_economyHeader._relayTid;
    if (relayTid == 0)
    {
        RELAY_CONTEXT_CRASH(265, L"== CRASH == [%s], %s; invalid relay tid, relayTid:0x%I64X",
                            MODULE_NAME, L"RelayContextManager::AddContext", 0ULL);
        return false;
    }

    int const index = static_cast<int>(relayTid % _bucketCount);
    _lockList[index].Enter();
    if (!_containerList[index].insert(std::pair<unsigned long long, RelayContext*>(relayTid, relayContext)).second)
    {
        _lockList[index].Leave();
        Log::Write(Log::LT_ERROR, RELAY_CONTEXT_FILE, 276, L"[%s], %s; failed to add relay context, relayTid:0x%I64X",
                   MODULE_NAME, L"RelayContextManager::AddContext", relayTid);
        return false;
    }
    relayContext->addReferenceCount(RELAY_CONTEXT_FILE, 280);
    InterlockedIncrement(&_contextCount);
    _lockList[index].Leave();
    return true;
}

// 0x1ce10
bool RelayContextManager::RemoveContext(unsigned long long relayTid)
{
    if (relayTid == 0)
    {
        RELAY_CONTEXT_CRASH(292, L"== CRASH == [%s], %s; invalid parameter, relayTid:0x%I64X",
                            MODULE_NAME, L"RelayContextManager::RemoveContext", 0ULL);
        return false;
    }
    if (_lockList == nullptr || _containerList == nullptr)
    {
        RELAY_CONTEXT_CRASH(296, L"== CRASH == [%s], %s; invalid relay context manager, lockList:0x%p, containerList:0x%p",
                            MODULE_NAME, L"RelayContextManager::RemoveContext", _lockList, _containerList);
        return false;
    }

    int const index = static_cast<int>(relayTid % _bucketCount);
    _lockList[index].Enter();
    Container::iterator it = _containerList[index].find(relayTid);
    if (it == _containerList[index].end())
    {
        _lockList[index].Leave();
        Log::Write(Log::LT_ERROR, RELAY_CONTEXT_FILE, 306, L"[%s], %s; no such relay context, relayTid:0x%I64X",
                   MODULE_NAME, L"RelayContextManager::RemoveContext", relayTid);
        return false;
    }
    RelayContext* const relayContext = it->second;
    if (relayContext == nullptr)
    {
        _lockList[index].Leave();
        RELAY_CONTEXT_CRASH(313, L"== CRASH == [%s], %s; relay context is null, relayTid:0x%I64X, relayContext:0x%p",
                            MODULE_NAME, L"RelayContextManager::RemoveContext", relayTid, nullptr);
        return false;
    }
    _containerList[index].erase(it);
    relayContext->removeReferenceCount(RELAY_CONTEXT_FILE, 318);
    InterlockedDecrement(&_contextCount);
    _lockList[index].Leave();
    return true;
}
