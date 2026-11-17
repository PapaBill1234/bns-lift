// SaleTimeContext.obj (MarketDealerDaemon PDB). Source: .scratch/hr/SaleTimeContext.c
// The 11 std::map/_Tree instances of this module (0x2d870, 0x2e000..0x2eaa0) come from include/vs2010.
#include "SaleTimeContext.h"
#include <new>
#include <windows.h>
#include "Log.h"
#include "AlertSender.h"
#include "Memory.h"
#include "SaleContext.h"

#define SALE_TIME_CONTEXT_FILE L"SaleTimeContext.cpp"
static wchar_t const* const MODULE_NAME = L"saletime context";  // PDB MODULE_NAME

#define SALE_TIME_CONTEXT_CRASH(line, fmt, ...)                                         \
    do                                                                                  \
    {                                                                                   \
        Log::Write(Log::LT_ERROR, SALE_TIME_CONTEXT_FILE, line, fmt, __VA_ARGS__);      \
        AlertSender::Write(SALE_TIME_CONTEXT_FILE, line, fmt, __VA_ARGS__);             \
    } while (0)

// LIFT: Not in the PDB. The original inlines an array new (`eh vector constructor iterator') with
// Memory::_Manager[2]->Alloc: the count is at the first int, the objects start at +8.
template<class T>
static T* saleTimeArrayNew(int count, wchar_t const* file, int line)
{
    int* raw = static_cast<int*>(Memory::_Manager[2]->Alloc(sizeof(T) * static_cast<long long>(count) + 8, file, line));
    if (raw == nullptr)
        return nullptr;
    *raw = count;
    T* items = reinterpret_cast<T*>(raw + 2);
    for (int i = 0; i < count; ++i)
        ::new (static_cast<void*>(&items[i])) T();
    return items;
}

// LIFT: inlined in SaleTimeContextManager::AddContext (0x2da50)
SaleTimeContext::SaleTimeContext(long long saleId, char saleType, SaleContext* const saleContext)
    : _saleId(saleId), _saleType(saleType), _saleContext(saleContext)
{
    _saleContext->addReferenceCount(SALE_TIME_CONTEXT_FILE, 38);
}

// 0x2d830
SaleTimeContext::~SaleTimeContext()
{
    if (_saleContext != nullptr)
    {
        _saleContext->removeReferenceCount(SALE_TIME_CONTEXT_FILE, 44);
        _saleContext = nullptr;
    }
}

// 0x2d8c0
bool SaleTimeContextManager::InitContextManager()
{
    if (_lockList != nullptr || _containerList != nullptr)
    {
        SALE_TIME_CONTEXT_CRASH(88,
                                L"== CRASH == [%s], %s; saletime context manager is already initialized, lockList:0x%p, containerList:0x%p",
                                MODULE_NAME, L"SaleTimeContextManager::InitContextManager", _lockList, _containerList);
        return false;
    }
    _lockList = saleTimeArrayNew<CriticalSection>(_bucketCount, SALE_TIME_CONTEXT_FILE, 92);
    _containerList = saleTimeArrayNew<Container>(_bucketCount, SALE_TIME_CONTEXT_FILE, 93);
    return true;
}

// 0x2da50
bool SaleTimeContextManager::AddContext(long long saleId, long long expirationTime, char saleType, SaleContext* const saleContext)
{
    if (saleId <= 0 || expirationTime <= 0 || static_cast<unsigned char>(saleType - 1) > 1 || saleContext == nullptr)
    {
        SALE_TIME_CONTEXT_CRASH(104,
                                L"== CRASH == [%s], %s; invalid parameter, saleId:0x%I64X, expirationTime:%I64d, saleType:%d, saleContext:0x%p",
                                MODULE_NAME, L"SaleTimeContextManager::AddContext", saleId, expirationTime,
                                static_cast<int>(saleType), saleContext);
        return false;
    }
    if (_lockList == nullptr || _containerList == nullptr)
    {
        SALE_TIME_CONTEXT_CRASH(108, L"== CRASH == [%s], %s; invalid saletime context manager, lockList:0x%p, containerList:0x%p",
                                MODULE_NAME, L"SaleTimeContextManager::AddContext", _lockList, _containerList);
        return false;
    }

    void* const memory = Memory::_Manager[2]->Alloc(sizeof(SaleTimeContext), SALE_TIME_CONTEXT_FILE, 113);
    SaleTimeContext* const saleTimeContext =
        memory != nullptr ? ::new (memory) SaleTimeContext(saleId, saleType, saleContext) : nullptr;

    int const index = static_cast<int>(saleId % _bucketCount);
    _lockList[index].Enter();
    if (_containerList[index].insert(Container::value_type(CompoundKey(saleId, expirationTime), saleTimeContext)).second)
    {
        InterlockedIncrement(&_contextCount);
        _lockList[index].Leave();
        return true;
    }
    _lockList[index].Leave();
    Log::Write(Log::LT_ERROR, SALE_TIME_CONTEXT_FILE, 122,
               L"[%s], %s; failed to add saletime context, saleId:0x%I64X, expirationTime:%I64d", MODULE_NAME,
               L"SaleTimeContextManager::AddContext", saleId, expirationTime);
    if (saleTimeContext != nullptr)
        saleTimeContext->~SaleTimeContext();
    Memory::_Manager[2]->Free(saleTimeContext, SALE_TIME_CONTEXT_FILE, 123);
    return false;
}

// 0x2dd30
bool SaleTimeContextManager::RemoveContext(long long saleId, long long expirationTime)
{
    if (saleId <= 0 || expirationTime <= 0)
    {
        SALE_TIME_CONTEXT_CRASH(138, L"== CRASH == [%s], %s; invalid parameter, saleId:0x%I64X, expirationTime:%I64d",
                                MODULE_NAME, L"SaleTimeContextManager::RemoveContext", saleId, expirationTime);
        return false;
    }
    if (_lockList == nullptr || _containerList == nullptr)
    {
        SALE_TIME_CONTEXT_CRASH(142, L"== CRASH == [%s], %s; invalid saletime context manager, lockList:0x%p, containerList:0x%p",
                                MODULE_NAME, L"SaleTimeContextManager::RemoveContext", _lockList, _containerList);
        return false;
    }

    int const index = static_cast<int>(saleId % _bucketCount);
    _lockList[index].Enter();
    Container::iterator it = _containerList[index].find(CompoundKey(saleId, expirationTime));
    if (it == _containerList[index].end())
    {
        _lockList[index].Leave();
        Log::Write(Log::LT_ERROR, SALE_TIME_CONTEXT_FILE, 152,
                   L"[%s], %s; there is no such saletime context, saleId:0x%I64X, expirationTime:%I64d", MODULE_NAME,
                   L"SaleTimeContextManager::RemoveContext", saleId, expirationTime);
        return false;
    }
    SaleTimeContext* const saleTimeContext = it->second;
    if (saleTimeContext != nullptr)
    {
        _containerList[index].erase(it);
        saleTimeContext->~SaleTimeContext();
        Memory::_Manager[2]->Free(saleTimeContext, SALE_TIME_CONTEXT_FILE, 164);
        InterlockedDecrement(&_contextCount);
        _lockList[index].Leave();
        return true;
    }
    _lockList[index].Leave();
    SALE_TIME_CONTEXT_CRASH(159, L"== CRASH == [%s], %s; saletime context is null, saleId:0x%I64X, expirationTime:%I64d",
                            MODULE_NAME, L"SaleTimeContextManager::RemoveContext", saleId, expirationTime);
    return false;
}
