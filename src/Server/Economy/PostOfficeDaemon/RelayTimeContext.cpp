// RelayTimeContext.obj (PostOfficeDaemon PDB).
// LIFT: PostOfficeDaemon build path of StlMemory.h, mixed case in this module (HR strings). Keeps the _Erase copies apart from the lower-case ones (no ICF fold).
#define LIFT_STLMEMORY_FILE \
    L"E:\\DailyBuild02\\PostOfficeDaemon-Common-0.0.348\\depot\\Branch\\348NC\\Program\\Server\\BloodLib\\include\\StlMemory.h"
#include "PlacementVecNew.h"
#include "RelayTimeContext.h"
#include <new>
#include "Log.h"
#include "AlertSender.h"
#include "Memory.h"
#include "RelayContext.h"

#define LIFT_MEMORY_H_FILE_POD \
    L"e:\\dailybuild02\\postofficedaemon-common-0.0.348\\depot\\branch\\348nc\\program\\server\\bloodlib\\include\\Memory.h"

// 0xb040
void __cdecl operator delete[](void*, void*)
{
    Log::Write(Log::LT_ERROR, LIFT_MEMORY_H_FILE_POD, 181, L"== CRASH == [memory], DO NOT USE THIS DEL OPERATOR");
    AlertSender::Write(LIFT_MEMORY_H_FILE_POD, 181, L"== CRASH == [memory], DO NOT USE THIS DEL OPERATOR");
}

#define RELAY_TIME_CONTEXT_FILE L"RelayTimeContext.cpp"
static wchar_t const* const MODULE_NAME = L"relaytime context";  // PDB MODULE_NAME

#define RELAY_TIME_CONTEXT_CRASH(line, fmt, ...)                                              \
    do                                                                                        \
    {                                                                                         \
        Log::Write(Log::LT_ERROR, RELAY_TIME_CONTEXT_FILE, line, fmt, __VA_ARGS__);           \
        AlertSender::Write(RELAY_TIME_CONTEXT_FILE, line, fmt, __VA_ARGS__);                  \
    } while (0)

// LIFT: inlined in RelayTimeContextManager::AddContext (0xb2a0)
RelayTimeContext::RelayTimeContext(unsigned long long relayTid, RelayContext* const relayContext)
    : _relayTid(relayTid), _relayContext(relayContext), _disuse(false)
{
    _relayContext->addReferenceCount(false, RELAY_TIME_CONTEXT_FILE, 27);
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
                                 MODULE_NAME, L"RelayTimeContextManager::initContextManager", _lockList, _containerList);
        return false;
    }
    _lockList = liftArrayNew(CriticalSection, _bucketCount, RELAY_TIME_CONTEXT_FILE, 78);
    _containerList = liftArrayNew(Container, _bucketCount, RELAY_TIME_CONTEXT_FILE, 79);
    return true;
}

// 0xb2a0
bool RelayTimeContextManager::AddContext(unsigned long long relayTid, long long relayLimitTime, RelayContext* const relayContext)
{
    if (relayTid == 0 || relayLimitTime <= 0 || relayContext == nullptr)
    {
        RELAY_TIME_CONTEXT_CRASH(87,
                                 L"== CRASH == [%s], %s; invalid parameter, relayTid:0x%I64X, relayLimitTime:%I64d, relayContext:0x%p",
                                 MODULE_NAME, L"RelayTimeContextManager::AddContext", relayTid, relayLimitTime, relayContext);
        return false;
    }
    if (_lockList == nullptr || _containerList == nullptr)
    {
        RELAY_TIME_CONTEXT_CRASH(91, L"== CRASH == [%s], %s; invalid relaytime context manager, lockList:0x%p, containerList:0x%p",
                                 MODULE_NAME, L"RelayTimeContextManager::AddContext", _lockList, _containerList);
        return false;
    }

    void* const memory = Memory::_Manager[2]->Alloc(sizeof(RelayTimeContext), RELAY_TIME_CONTEXT_FILE, 96);
    RelayTimeContext* const relayTimeContext =
        memory != nullptr ? ::new (memory) RelayTimeContext(relayTid, relayContext) : nullptr;

    int const index = static_cast<int>(relayTid % _bucketCount);
    _lockList[index].Enter();
    if (!_containerList[index].insert(std::pair<CompoundKey, RelayTimeContext*>(CompoundKey(relayTid, relayLimitTime), relayTimeContext)).second)
    {
        _lockList[index].Leave();
        Log::Write(Log::LT_ERROR, RELAY_TIME_CONTEXT_FILE, 105, L"[%s], %s; failed to add relaytime context, relayTid:0x%I64X, relayLimitTime:%I64d",
                   MODULE_NAME, L"RelayTimeContextManager::AddContext", relayTid, relayLimitTime);
        if (relayTimeContext != nullptr)
            relayTimeContext->~RelayTimeContext();
        Memory::_Manager[2]->Free(relayTimeContext, RELAY_TIME_CONTEXT_FILE, 106);
        return false;
    }
    InterlockedIncrement(&_contextCount);
    _lockList[index].Leave();
    return true;
}

// 0xb550
bool RelayTimeContextManager::RemoveContext(unsigned long long relayTid, long long relayLimitTime)
{
    if (relayTid == 0 || relayLimitTime <= 0)
    {
        RELAY_TIME_CONTEXT_CRASH(121, L"== CRASH == [%s], %s; invalid parameter, relayTid:0x%I64X, relayLimitTime:%I64d",
                                 MODULE_NAME, L"RelayTimeContextManager::RemoveContext", relayTid, relayLimitTime);
        return false;
    }
    if (_lockList == nullptr || _containerList == nullptr)
    {
        RELAY_TIME_CONTEXT_CRASH(125, L"== CRASH == [%s], %s; invalid relaytime context manager, lockList:0x%p, containerList:0x%p",
                                 MODULE_NAME, L"RelayTimeContextManager::RemoveContext", _lockList, _containerList);
        return false;
    }

    int const index = static_cast<int>(relayTid % _bucketCount);
    _lockList[index].Enter();
    Container::iterator it = _containerList[index].find(CompoundKey(relayTid, relayLimitTime));
    if (it == _containerList[index].end())
    {
        _lockList[index].Leave();
        Log::Write(Log::LT_ERROR, RELAY_TIME_CONTEXT_FILE, 135, L"[%s], %s; no such relaytime context, relayTid:0x%I64X, relayLimitTime:%I64d",
                   MODULE_NAME, L"RelayTimeContextManager::RemoveContext", relayTid, relayLimitTime);
        return false;
    }
    RelayTimeContext* const relayTimeContext = it->second;
    if (relayTimeContext == nullptr)
    {
        _lockList[index].Leave();
        RELAY_TIME_CONTEXT_CRASH(142,
                                 L"== CRASH == [%s], %s; relaytime context is null, relayTid:0x%I64X, relayLimitTime:%I64d, relaytimeContext:0x%p",
                                 MODULE_NAME, L"RelayTimeContextManager::RemoveContext", relayTid, relayLimitTime, nullptr);
        return false;
    }
    _containerList[index].erase(it);
    relayTimeContext->~RelayTimeContext();
    Memory::_Manager[2]->Free(relayTimeContext, RELAY_TIME_CONTEXT_FILE, 147);
    InterlockedDecrement(&_contextCount);
    _lockList[index].Leave();
    return true;
}
