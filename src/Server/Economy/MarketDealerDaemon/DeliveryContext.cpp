// DeliveryContext.obj (MarketDealerDaemon PDB). Source: .scratch/hr/DeliveryContext.c
// No code here (COMDAT copies of common code): CriticalSection::CriticalSection 0x6ff0 (Lock.h),
// operator delete[] 0x7010 (Memory.h), FragmentPacket::FreeSize 0x7050, FragmentPacket::Compose 0x7070.
// The std::map functions (0x8020..0x8260, 0x2b210, 0x2d000..0x2d580) come from include/vs2010.
#include "DeliveryContext.h"
#include <string.h>
#include <wchar.h>
#include <new>
#include <windows.h>
#include "Log.h"
#include "AlertSender.h"
#include "Memory.h"
#include "FragmentPacket.h"
#include "SaleContext.h"

#define DELIVERY_CONTEXT_FILE L"DeliveryContext.cpp"
static wchar_t const* const MODULE_NAME = L"delivery context";  // PDB MODULE_NAME

#define DELIVERY_CONTEXT_CRASH(line, fmt, ...)                                     \
    do                                                                             \
    {                                                                              \
        Log::Write(Log::LT_ERROR, DELIVERY_CONTEXT_FILE, line, fmt, __VA_ARGS__);  \
        AlertSender::Write(DELIVERY_CONTEXT_FILE, line, fmt, __VA_ARGS__);         \
    } while (0)

// LIFT: inlined array new of BloodLib (count prefix + placement new), as in 0x7710.
template <typename T>
static T* deliveryArrayNew(int count, wchar_t const* file, int line)
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

// ---- DeliveryInfo ----

// 0x7100
DeliveryInfo::DeliveryInfo()
{
    _deliveryId = 0;
    _deliveryReason = 0;
    _saleId = 0;
    _pawnId = 0;
    _pawnServiceId = 0;
    _pawnOwner._participantWid = 0;
    _pawnOwner._participantPcId = 0;
    _pawnOwner._participantAccountId.id[0] = 0;
    _pawnOwner._participantAccountId.id[1] = 0;
    memset(_pawnOwner._participantWorldName, 0, sizeof(_pawnOwner._participantWorldName));
    memset(_pawnOwner._participantName, 0, sizeof(_pawnOwner._participantName));
    _recipient._participantWid = 0;
    _recipient._participantPcId = 0;
    _recipient._participantAccountId.id[0] = 0;
    _recipient._participantAccountId.id[1] = 0;
    memset(_recipient._participantWorldName, 0, sizeof(_recipient._participantWorldName));
    memset(_recipient._participantName, 0, sizeof(_recipient._participantName));
    memset(_marketStatement._statementTitle, 0, sizeof(_marketStatement._statementTitle));
    memset(_marketStatement._statementBody, 0, sizeof(_marketStatement._statementBody));
    _jobStatus = 0;
}

// ---- DeliveryContext ----

// 0x72a0
DeliveryContext::DeliveryContext(DeliveryInfo const& deliveryInfo, SaleItemInfo const& saleItemInfo)
{
    memcpy(&_deliveryInfo, &deliveryInfo, sizeof(_deliveryInfo));
    _deliveryItemInfo._itemType = saleItemInfo._itemType;
    _deliveryItemInfo._itemCommonCategory = saleItemInfo._itemCommonCategory;
    _deliveryItemInfo._itemInstanceId = saleItemInfo._itemInstanceId;
    _deliveryItemInfo._itemDataId = saleItemInfo._itemDataId;
    _deliveryItemInfo._itemLevel = saleItemInfo._itemLevel;
    _deliveryItemInfo._itemAmount = saleItemInfo._itemAmount;
    wcsncpy(_deliveryItemInfo._itemXmlData, saleItemInfo._itemXmlData, 1025);
    _reportTime = 0;
}

// 0x7370
DeliveryContext::DeliveryContext(DeliveryInfo const& deliveryInfo, long long moneyAmount)
{
    memcpy(&_deliveryInfo, &deliveryInfo, sizeof(_deliveryInfo));
    _deliveryItemInfo._itemType = 1;
    _deliveryItemInfo._itemCommonCategory = 1;
    _deliveryItemInfo._itemInstanceId = 0;
    _deliveryItemInfo._itemDataId = 0;
    _deliveryItemInfo._itemLevel = 0;
    _deliveryItemInfo._itemAmount = moneyAmount;
    memset(_deliveryItemInfo._itemXmlData, 0, sizeof(_deliveryItemInfo._itemXmlData));
    _reportTime = 0;
}

// 0x70c0 (scalar deleting destructor; the destructor body is inlined there). _lock deletes its critical section.
DeliveryContext::~DeliveryContext()
{
}

// 0x7420
bool DeliveryContext::ComposeReportPacket(FragmentPacket& packet) const
{
    DeliveryInfo const& info = _deliveryInfo;
    // postType 1 and serviceWorldType 2 are constants in the binary. ❓ Names of the constants.
    if (!packet.Compose(14, info._deliveryId, 1, static_cast<int>(info._deliveryReason), info._saleId, 2, info._pawnId,
                        info._pawnServiceId, static_cast<int>(info._pawnOwner._participantWid),
                        info._pawnOwner._participantPcId, static_cast<int>(info._recipient._participantWid),
                        info._recipient._participantPcId, info._recipient._participantName,
                        info._marketStatement._statementTitle, info._marketStatement._statementBody))
    {
        Log::Write(Log::LT_ERROR, DELIVERY_CONTEXT_FILE, 115,
                   L"[%s], %s; failed to compose report packet, deliveryId:0x%I64X", MODULE_NAME,
                   L"DeliveryContext::ComposeReportPacket", info._deliveryId);
        return false;
    }

    Log::Write(Log::LT_DEBUG, DELIVERY_CONTEXT_FILE, 121,
               L"[%s], %s; composed report packet, deliveryId:0x%I64X, postType:%d, deliveryReason:%d, saleId:0x%I64X, "
               L"serviceWorldType:%d, pawnId:0x%I64X, pawnServiceId:0x%I64X, pawnOwnerWid:%d, pawnOwnerPcId:0x%I64X, "
               L"recipientWid:%d, recipientPcId:0x%I64X, recipientName:%s, marketStatementTitle:%s, marketStatementBody:%s",
               MODULE_NAME, L"DeliveryContext::ComposeReportPacket", info._deliveryId, 1,
               static_cast<int>(info._deliveryReason), info._saleId, 2, info._pawnId, info._pawnServiceId,
               static_cast<int>(info._pawnOwner._participantWid), info._pawnOwner._participantPcId,
               static_cast<int>(info._recipient._participantWid), info._recipient._participantPcId,
               info._recipient._participantName, info._marketStatement._statementTitle,
               info._marketStatement._statementBody);

    DeliveryItemInfo const& item = _deliveryItemInfo;
    if (packet.FreeSize() <= 2 * (wcslen(item._itemXmlData) + 1) + 24)
        packet.packet.Allocate(&packet.composer);

    if (!packet.Compose(7, static_cast<int>(item._itemType), static_cast<int>(item._itemCommonCategory),
                        item._itemInstanceId, item._itemDataId, static_cast<int>(item._itemLevel), item._itemAmount,
                        item._itemXmlData))
    {
        Log::Write(Log::LT_ERROR, DELIVERY_CONTEXT_FILE, 139,
                   L"[%s], %s; failed to compose report packet, deliveryId:0x%I64X", MODULE_NAME,
                   L"DeliveryContext::ComposeReportPacket", info._deliveryId);
        return false;
    }

    Log::Write(Log::LT_DEBUG, DELIVERY_CONTEXT_FILE, 142,
               L"[%s], %s; composed report packet, deliveryId:0x%I64X, itemType:%d, itemCommonCategory:%d, "
               L"itemInstanceId:0x%I64X, itemDataId:%d, itemLevel:%d, itemAmount:%I64d, itemXmlData:%s",
               MODULE_NAME, L"DeliveryContext::ComposeReportPacket", info._deliveryId, static_cast<int>(item._itemType),
               static_cast<int>(item._itemCommonCategory), item._itemInstanceId, item._itemDataId,
               static_cast<int>(item._itemLevel), item._itemAmount, item._itemXmlData);
    return true;
}

// ---- DeliveryContextManager ----

// 0x7710
bool DeliveryContextManager::InitContextManager()
{
    if (_lockList != nullptr || _containerList != nullptr)
    {
        DELIVERY_CONTEXT_CRASH(186,
                               L"== CRASH == [%s], %s; delivery context manager is already initialized, lockList:0x%p, "
                               L"containerList:0x%p",
                               MODULE_NAME, L"DeliveryContextManager::InitContextManager", _lockList, _containerList);
        return false;
    }
    _lockList = deliveryArrayNew<CriticalSection>(_bucketCount, DELIVERY_CONTEXT_FILE, 190);
    _containerList = deliveryArrayNew<Container>(_bucketCount, DELIVERY_CONTEXT_FILE, 191);
    return true;
}

// 0x78a0
DeliveryContext* DeliveryContextManager::GetContext(long long deliveryId) const
{
    if (deliveryId <= 0)
    {
        DELIVERY_CONTEXT_CRASH(199, L"== CRASH == [%s], %s; invalid parameter, deliveryId:0x%I64X",
                               MODULE_NAME, L"DeliveryContextManager::GetContext", deliveryId);
        return nullptr;
    }
    if (_lockList == nullptr || _containerList == nullptr)
    {
        DELIVERY_CONTEXT_CRASH(203,
                               L"== CRASH == [%s], %s; invalid delivery context manager, lockList:0x%p, containerList:0x%p",
                               MODULE_NAME, L"DeliveryContextManager::GetContext", _lockList, _containerList);
        return nullptr;
    }

    int const index = static_cast<int>(deliveryId % _bucketCount);
    _lockList[index].Enter();
    Container::iterator it = _containerList[index].find(deliveryId);
    if (it == _containerList[index].end())
    {
        _lockList[index].Leave();
        return nullptr;
    }
    DeliveryContext* const deliveryContext = it->second;
    if (deliveryContext != nullptr)
    {
        deliveryContext->addReferenceCount(false, DELIVERY_CONTEXT_FILE, 219);
        _lockList[index].Leave();
        return deliveryContext;
    }
    _lockList[index].Leave();
    DELIVERY_CONTEXT_CRASH(216,
                           L"== CRASH == [%s], %s; delivery context is null, deliveryId:0x%I64X, deliveryContext:0x%p",
                           MODULE_NAME, L"DeliveryContextManager::GetContext", deliveryId, nullptr);
    return nullptr;
}

// 0x7b10
bool DeliveryContextManager::AddContext(DeliveryContext* const deliveryContext)
{
    if (deliveryContext == nullptr)
    {
        DELIVERY_CONTEXT_CRASH(229, L"== CRASH == [%s], %s; invalid parameter, deliveryContext:0x%p",
                               MODULE_NAME, L"DeliveryContextManager::AddContext", nullptr);
        return false;
    }
    if (_lockList == nullptr || _containerList == nullptr)
    {
        DELIVERY_CONTEXT_CRASH(233,
                               L"== CRASH == [%s], %s; invalid delivery context manager, lockList:0x%p, containerList:0x%p",
                               MODULE_NAME, L"DeliveryContextManager::AddContext", _lockList, _containerList);
        return false;
    }
    long long const deliveryId = deliveryContext->_deliveryInfo._deliveryId;
    if (deliveryId <= 0)
    {
        Log::Write(Log::LT_ERROR, DELIVERY_CONTEXT_FILE, 239, L"[%s], %s; invalid delivery id, deliveryId:0x%I64X",
                   MODULE_NAME, L"DeliveryContextManager::AddContext", deliveryId);
        return false;
    }

    int const index = static_cast<int>(deliveryId % _bucketCount);
    _lockList[index].Enter();
    if (_containerList[index].insert(Container::value_type(deliveryId, deliveryContext)).second)
    {
        deliveryContext->addReferenceCount(false, DELIVERY_CONTEXT_FILE, 254);
        InterlockedIncrement(&_contextCount);
        _lockList[index].Leave();
        return true;
    }
    _lockList[index].Leave();
    Log::Write(Log::LT_ERROR, DELIVERY_CONTEXT_FILE, 250, L"[%s], %s; failed to add delivery context, deliveryId:0x%I64X",
               MODULE_NAME, L"DeliveryContextManager::AddContext", deliveryId);
    return false;
}

// 0x7d70
bool DeliveryContextManager::RemoveContext(long long deliveryId)
{
    if (deliveryId <= 0)
    {
        DELIVERY_CONTEXT_CRASH(266, L"== CRASH == [%s], %s; invalid parameter, deliveryId:0x%I64X",
                               MODULE_NAME, L"DeliveryContextManager::RemoveContext", deliveryId);
        return false;
    }
    if (_lockList == nullptr || _containerList == nullptr)
    {
        DELIVERY_CONTEXT_CRASH(270,
                               L"== CRASH == [%s], %s; invalid delivery context manager, lockList:0x%p, containerList:0x%p",
                               MODULE_NAME, L"DeliveryContextManager::RemoveContext", _lockList, _containerList);
        return false;
    }

    int const index = static_cast<int>(deliveryId % _bucketCount);
    _lockList[index].Enter();
    Container::iterator it = _containerList[index].find(deliveryId);
    if (it == _containerList[index].end())
    {
        _lockList[index].Leave();
        Log::Write(Log::LT_ERROR, DELIVERY_CONTEXT_FILE, 280,
                   L"[%s], %s; there is no such delivery context, deliveryId:0x%I64X", MODULE_NAME,
                   L"DeliveryContextManager::RemoveContext", deliveryId);
        return false;
    }
    DeliveryContext* const deliveryContext = it->second;
    if (deliveryContext != nullptr)
    {
        _containerList[index].erase(it);
        deliveryContext->removeReferenceCount(DELIVERY_CONTEXT_FILE, 292);
        InterlockedDecrement(&_contextCount);
        _lockList[index].Leave();
        return true;
    }
    _lockList[index].Leave();
    DELIVERY_CONTEXT_CRASH(287,
                           L"== CRASH == [%s], %s; delivery context is null, deliveryId:0x%I64X, deliveryContext:0x%p",
                           MODULE_NAME, L"DeliveryContextManager::RemoveContext", deliveryId, nullptr);
    return false;
}
