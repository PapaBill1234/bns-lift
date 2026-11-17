// RelayTimeContext.obj (PostOfficeDaemon PDB).
#include "RelayTimeContext.h"
#include <new>
#include "Log.h"
#include "AlertSender.h"
#include "Memory.h"
#include "RelayContext.h"

#define RELAY_TIME_CONTEXT_FILE L"RelayTimeContext.cpp"
#define RELAY_TIME_CONTEXT_TAG L"relaytime context"

#define RELAY_TIME_CONTEXT_CRASH(line, fmt, ...)                                              \
    do                                                                                        \
    {                                                                                         \
        Log::Write(Log::LT_ERROR, RELAY_TIME_CONTEXT_FILE, line, fmt, __VA_ARGS__);           \
        AlertSender::Write(RELAY_TIME_CONTEXT_FILE, line, fmt, __VA_ARGS__);                  \
    } while (0)

// ❓ inlined in RelayTimeContextManager::AddContext (0xb2a0)
RelayTimeContext::RelayTimeContext(unsigned long long relayTid, RelayContext* const relayContext)
    : _relayTid(relayTid), _relayContext(relayContext), _disuse(false)
{
    _relayContext->addReferenceCount(RELAY_TIME_CONTEXT_FILE, 27);
}

// 0xb080
RelayTimeContext::~RelayTimeContext()
{
    if (_relayContext != nullptr)
    {
        _relayContext->removeReferenceCount(RELAY_TIME_CONTEXT_FILE, 33);
        _relayContext = nullptr;
    }
}

// 0xb110
bool RelayTimeContextManager::initContextManager()
{
    if (_lockList != nullptr || _containerList != nullptr)
    {
        RELAY_TIME_CONTEXT_CRASH(74,
                                 L"== CRASH == [%s], %s; relaytime context manager is already initialized, lockList:0x%p, containerList:0x%p",
                                 RELAY_TIME_CONTEXT_TAG, L"RelayTimeContextManager::initContextManager", _lockList, _containerList);
        return false;
    }
    _lockList = liftArrayNew<CriticalSection>(_bucketCount, RELAY_TIME_CONTEXT_FILE, 78);
    _containerList = liftArrayNew<Container>(_bucketCount, RELAY_TIME_CONTEXT_FILE, 79);
    return true;
}

// 0xb2a0
bool RelayTimeContextManager::AddContext(unsigned long long relayTid, long long relayLimitTime, RelayContext* const relayContext)
{
    if (relayTid == 0 || relayLimitTime <= 0 || relayContext == nullptr)
    {
        RELAY_TIME_CONTEXT_CRASH(87,
                                 L"== CRASH == [%s], %s; invalid parameter, relayTid:0x%I64X, relayLimitTime:%I64d, relayContext:0x%p",
                                 RELAY_TIME_CONTEXT_TAG, L"RelayTimeContextManager::AddContext", relayTid, relayLimitTime, relayContext);
        return false;
    }
    if (_lockList == nullptr || _containerList == nullptr)
    {
        RELAY_TIME_CONTEXT_CRASH(91, L"== CRASH == [%s], %s; invalid relaytime context manager, lockList:0x%p, containerList:0x%p",
                                 RELAY_TIME_CONTEXT_TAG, L"RelayTimeContextManager::AddContext", _lockList, _containerList);
        return false;
    }

    void* const memory = Memory::_Manager[2]->Alloc(sizeof(RelayTimeContext), RELAY_TIME_CONTEXT_FILE, 99);  // ❓ line
    RelayTimeContext* const relayTimeContext =
        memory != nullptr ? ::new (memory) RelayTimeContext(relayTid, relayContext) : nullptr;

    int const index = static_cast<int>(relayTid % _bucketCount);
    _lockList[index].Enter();
    if (_containerList[index].insert(Container::value_type(CompoundKey(relayTid, relayLimitTime), relayTimeContext)).second)
    {
        InterlockedIncrement(&_contextCount);
        _lockList[index].Leave();
        return true;
    }
    _lockList[index].Leave();
    Log::Write(Log::LT_ERROR, RELAY_TIME_CONTEXT_FILE, 105, L"[%s], %s; failed to add relaytime context, relayTid:0x%I64X, relayLimitTime:%I64d",
               RELAY_TIME_CONTEXT_TAG, L"RelayTimeContextManager::AddContext", relayTid, relayLimitTime);
    if (relayTimeContext != nullptr)
        relayTimeContext->~RelayTimeContext();
    Memory::_Manager[2]->Free(relayTimeContext, RELAY_TIME_CONTEXT_FILE, 106);
    return false;
}

// 0xb550
bool RelayTimeContextManager::RemoveContext(unsigned long long relayTid, long long relayLimitTime)
{
    if (relayTid == 0 || relayLimitTime <= 0)
    {
        RELAY_TIME_CONTEXT_CRASH(121, L"== CRASH == [%s], %s; invalid parameter, relayTid:0x%I64X, relayLimitTime:%I64d",
                                 RELAY_TIME_CONTEXT_TAG, L"RelayTimeContextManager::RemoveContext", relayTid, relayLimitTime);
        return false;
    }
    if (_lockList == nullptr || _containerList == nullptr)
    {
        RELAY_TIME_CONTEXT_CRASH(125, L"== CRASH == [%s], %s; invalid relaytime context manager, lockList:0x%p, containerList:0x%p",
                                 RELAY_TIME_CONTEXT_TAG, L"RelayTimeContextManager::RemoveContext", _lockList, _containerList);
        return false;
    }

    int const index = static_cast<int>(relayTid % _bucketCount);
    _lockList[index].Enter();
    Container::iterator it = _containerList[index].find(CompoundKey(relayTid, relayLimitTime));
    if (it == _containerList[index].end())
    {
        _lockList[index].Leave();
        Log::Write(Log::LT_ERROR, RELAY_TIME_CONTEXT_FILE, 135, L"[%s], %s; no such relaytime context, relayTid:0x%I64X, relayLimitTime:%I64d",
                   RELAY_TIME_CONTEXT_TAG, L"RelayTimeContextManager::RemoveContext", relayTid, relayLimitTime);
        return false;
    }
    RelayTimeContext* const relayTimeContext = it->second;
    if (relayTimeContext != nullptr)
    {
        _containerList[index].erase(it);
        relayTimeContext->~RelayTimeContext();
        Memory::_Manager[2]->Free(relayTimeContext, RELAY_TIME_CONTEXT_FILE, 147);
        InterlockedDecrement(&_contextCount);
        _lockList[index].Leave();
        return true;
    }
    _lockList[index].Leave();
    RELAY_TIME_CONTEXT_CRASH(142,
                             L"== CRASH == [%s], %s; relaytime context is null, relayTid:0x%I64X, relayLimitTime:%I64d, relaytimeContext:0x%p",
                             RELAY_TIME_CONTEXT_TAG, L"RelayTimeContextManager::RemoveContext", relayTid, relayLimitTime, nullptr);
    return false;
}
