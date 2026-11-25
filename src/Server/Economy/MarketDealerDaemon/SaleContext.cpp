// SaleContext.obj (MarketDealerDaemon PDB).
// No code: std::map code (_Buynode, _Linsert, _Erase, erase) is STL.
#include "SaleContext.h"
#include <string.h>
#include <wchar.h>
#include <new>
#include <windows.h>
#include "Log.h"
#include "AlertSender.h"
#include "Memory.h"
#include "BidContext.h"
#include "PurchaseContext.h"
#include "MarketDealerDaemon.h"

#define SALE_CONTEXT_FILE L"SaleContext.cpp"
static wchar_t const* const MODULE_NAME = L"sale context";  // PDB MODULE_NAME

#define SALE_CONTEXT_CRASH(line, fmt, ...)                                       \
    do                                                                           \
    {                                                                            \
        Log::Write(Log::LT_ERROR, SALE_CONTEXT_FILE, line, fmt, __VA_ARGS__);    \
        AlertSender::Write(SALE_CONTEXT_FILE, line, fmt, __VA_ARGS__);           \
    } while (0)

// LIFT: Not in the PDB. The original inlines an array new (`eh vector constructor iterator') with
// Memory::_Manager[2]->Alloc: the count is at the first int, the objects start at +8 (0x2c6f0).
template<class T>
static T* saleArrayNew(int count, wchar_t const* file, int line)
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

// ---- SaleInfo ----

// 0x2adb0
SaleInfo::SaleInfo()
{
    _saleId = 0;
    _pawnId = 0;
    _saleType = 0;
    _seller._participantWid = 0;
    _seller._participantPcId = 0;
    _seller._participantAccountId.id[0] = 0;
    _seller._participantAccountId.id[1] = 0;
    memset(_seller._participantWorldName, 0, sizeof(_seller._participantWorldName));
    memset(_seller._participantName, 0, sizeof(_seller._participantName));
    _salePrice = 0;
    _unitPrice = 0;
    _bidUnitPrice = 0;
    _topBidId = 0;
    _topBidderPawnId = 0;
    _topBidder._participantWid = 0;
    _topBidder._participantPcId = 0;
    _topBidder._participantAccountId.id[0] = 0;
    _topBidder._participantAccountId.id[1] = 0;
    memset(_topBidder._participantWorldName, 0, sizeof(_topBidder._participantWorldName));
    memset(_topBidder._participantName, 0, sizeof(_topBidder._participantName));
    _saleStatus = 0;
    _topBidPrice = 0;
    _saleExpirationTime = 0;
}

// ---- SaleItemInfo ----

// 0x2af30
MarketDealerFailReason SaleItemInfo::CheckItemDataValidity() const
{
    if (_itemCommonCategory <= 1 || _itemCommonCategory >= 7)
        return static_cast<MarketDealerFailReason>(17);
    if (_itemFirstCategory <= 0 || _itemSecondCategory <= 0 || _itemThirdCategory <= 0)
        return static_cast<MarketDealerFailReason>(17);
    if (_itemType <= 0 || _itemType >= 4 || _itemExp < 0 || _itemAmount <= 0 || _itemGrade <= 0 || _itemEquipLevel <= 0)
        return static_cast<MarketDealerFailReason>(17);

    switch (_itemType)
    {
    case 1:
        if (_itemInstanceId != 0 || _itemDataId != 0 || _itemLevel != 0)
            return static_cast<MarketDealerFailReason>(18);
        if (wcslen(_itemXmlData) != 0)
            return static_cast<MarketDealerFailReason>(18);
        break;
    case 2:
        if (_itemInstanceId <= 0 || _itemDataId <= 0 || _itemLevel <= 0)
            return static_cast<MarketDealerFailReason>(19);
        if (wcslen(_itemXmlData) != 0)
            return static_cast<MarketDealerFailReason>(19);
        break;
    case 3:
        if (_itemInstanceId <= 0 || _itemDataId <= 0 || _itemLevel <= 0)
            return static_cast<MarketDealerFailReason>(20);
        if (wcslen(_itemXmlData) == 0)
            return static_cast<MarketDealerFailReason>(20);
        break;
    default:
        return static_cast<MarketDealerFailReason>(17);
    }
    return static_cast<MarketDealerFailReason>(0);
}

// ---- SaleContext ----

// 0x2b080
SaleContext::SaleContext(SaleInfo const& saleInfo) : _bidCount(0)
{
    memcpy(&_saleInfo, &saleInfo, sizeof(_saleInfo));
    _saleItemInfo._itemCommonCategory = 0;
    _saleItemInfo._itemFirstCategory = 0;
    _saleItemInfo._itemSecondCategory = 0;
    _saleItemInfo._itemThirdCategory = 0;
    _saleItemInfo._itemType = 0;
    _saleItemInfo._itemInstanceId = 0;
    _saleItemInfo._itemDataId = 0;
    _saleItemInfo._itemLevel = 0;
    _saleItemInfo._itemExp = 0;
    _saleItemInfo._itemAmount = 0;
    _saleItemInfo._itemGrade = 0;
    _saleItemInfo._itemEquipLevel = 0;
    memset(_saleItemInfo._itemXmlData, 0, sizeof(_saleItemInfo._itemXmlData));
}

// 0x2b260
SaleContext::SaleContext(SaleInfo const& saleInfo, SaleItemInfo const& saleItemInfo) : _bidCount(0)
{
    memcpy(&_saleInfo, &saleInfo, sizeof(_saleInfo));
    memcpy(&_saleItemInfo, &saleItemInfo, sizeof(_saleItemInfo));
}

// 0x2b3b0
SaleContext::~SaleContext()
{
    for (DealingList::iterator it = _bidList.begin(); it != _bidList.end(); ++it)
    {
        if (it->second != nullptr)
            it->second->removeReferenceCount(SALE_CONTEXT_FILE, 155);
    }
    _bidList.clear();

    for (DealingList::iterator it = _purchaseList.begin(); it != _purchaseList.end(); ++it)
    {
        if (it->second != nullptr)
            it->second->removeReferenceCount(SALE_CONTEXT_FILE, 163);
    }
    _purchaseList.clear();
}

// 0x2b880
bool SaleContext::DetermineUnitPrice(long long salePrice, int itemAmount, long long& unitPrice)
{
    if (salePrice <= 0 || itemAmount <= 0)
    {
        SALE_CONTEXT_CRASH(172, L"== CRASH == [%s], %s; invalid parameter, salePrice:%I64d, itemAmount:%d",
                           MODULE_NAME, L"SaleContext::DetermineUnitPrice", salePrice, itemAmount);
        return false;
    }
    long long price = salePrice / itemAmount;
    if (price < 1)
        price = 1;
    unitPrice = price;
    return true;
}

// 0x2b950
bool SaleContext::DetermineBidUnitPrice(long long salePrice, long long& bidUnitPrice)
{
    if (salePrice <= 0)
    {
        SALE_CONTEXT_CRASH(186, L"== CRASH == [%s], %s; invalid parameter, salePrice:%I64d",
                           MODULE_NAME, L"SaleContext::DetermineBidUnitPrice", salePrice);
        return false;
    }
    // The divisor is the double 100.0 at rva 0xa9718 (ratio in percent).
    long long price = static_cast<long long>(
        static_cast<double>(MarketDealerDaemon::_instance->_config->_bidPriceUnitRatio) / 100.0 * static_cast<double>(salePrice));
    if (price < 1)
        price = 1;
    bidUnitPrice = price;
    return true;
}

// 0x2ba20
bool SaleContext::SetTopBidInfo(BidInfo const& newTopBidInfo)
{
    if (_saleInfo._topBidId == newTopBidInfo._dealingInfo._dealingId ||
        _saleInfo._topBidPrice < newTopBidInfo._dealingInfo._dealingPrice)
    {
        _saleInfo._topBidId = newTopBidInfo._dealingInfo._dealingId;
        _saleInfo._topBidderPawnId = newTopBidInfo._dealingInfo._pawnId;
        memcpy(&_saleInfo._topBidder, &newTopBidInfo._dealingInfo._trader, sizeof(_saleInfo._topBidder));
        _saleInfo._topBidPrice = newTopBidInfo._dealingInfo._dealingPrice;
        return true;
    }
    SALE_CONTEXT_CRASH(202,
                       L"== CRASH == [%s], %s; invalid parameter, currTopBidId:0x%I64X, newTopBidId:0x%I64X, "
                       L"currTopBidPrice:%I64d, newTopBidPrice:%I64d",
                       MODULE_NAME, L"SaleContext::SetTopBidInfo", _saleInfo._topBidId,
                       newTopBidInfo._dealingInfo._dealingId, _saleInfo._topBidPrice,
                       newTopBidInfo._dealingInfo._dealingPrice);
    return false;
}

// 0x2bb50
BidContext* SaleContext::GetBidContext(long long bidderPcId)
{
    if (bidderPcId <= 0)
    {
        SALE_CONTEXT_CRASH(220, L"== CRASH == [%s], %s; invalid parameter, bidderPcId:0x%I64X",
                           MODULE_NAME, L"SaleContext::GetBidContext", bidderPcId);
        return nullptr;
    }
    DealingList::iterator it = _bidList.find(bidderPcId);
    if (it == _bidList.end())
        return nullptr;
    DealingContext* const bidContext = it->second;
    if (bidContext == nullptr)
    {
        SALE_CONTEXT_CRASH(230, L"== CRASH == [%s], %s; bid context is null, bidderPcId:0x%I64X, bidContext:0x%p",
                           MODULE_NAME, L"SaleContext::GetBidContext", bidderPcId, nullptr);
        return nullptr;
    }
    bidContext->addReferenceCount(false, SALE_CONTEXT_FILE, 233);
    return static_cast<BidContext*>(bidContext);
}

// 0x2bcf0
bool SaleContext::IsBidding(long long bidderPcId) const
{
    if (bidderPcId <= 0)
    {
        SALE_CONTEXT_CRASH(242, L"== CRASH == [%s], %s; invalid parameter, bidderPcId:0x%I64X",
                           MODULE_NAME, L"SaleContext::IsBidding", bidderPcId);
        return false;
    }
    return _bidList.find(bidderPcId) != _bidList.end();
}

// 0x2be00
bool SaleContext::AddBidContext(BidInfo const& bidInfo)
{
    void* const memory = Memory::_Manager[2]->Alloc(sizeof(BidContext), SALE_CONTEXT_FILE, 255);
    DealingContext* const bidContext = memory != nullptr ? new (memory) BidContext(bidInfo) : nullptr;
    // BUG: 0x2be00 no null check after Alloc; the failure path calls removeReferenceCount on nullptr.
    if (_bidList.insert(DealingList::value_type(bidInfo._dealingInfo._trader._participantPcId, bidContext)).second)
        return true;

    Log::Write(Log::LT_ERROR, SALE_CONTEXT_FILE, 261,
               L"[%s], %s; failed to add bid context, saleId:0x%I64X, bidId:0x%I64X, bidderPcId:0x%I64X",
               MODULE_NAME, L"SaleContext::AddBidContext", _saleInfo._saleId, bidInfo._dealingInfo._dealingId,
               bidInfo._dealingInfo._trader._participantPcId);
    bidContext->removeReferenceCount(SALE_CONTEXT_FILE, 262);
    return false;
}

// 0x2bf30
bool SaleContext::RemoveBidContext(long long bidderPcId)
{
    if (bidderPcId <= 0)
    {
        SALE_CONTEXT_CRASH(274, L"== CRASH == [%s], %s; invalid parameter, bidderPcId:0x%I64X",
                           MODULE_NAME, L"SaleContext::RemoveBidContext", bidderPcId);
        return false;
    }
    DealingList::iterator it = _bidList.find(bidderPcId);
    if (it == _bidList.end())
    {
        Log::Write(Log::LT_ERROR, SALE_CONTEXT_FILE, 280, L"[%s], %s; there is no such bid context, bidderPcId:0x%I64X",
                   MODULE_NAME, L"SaleContext::RemoveBidContext", bidderPcId);
        return false;
    }
    DealingContext* const bidContext = it->second;
    if (bidContext == nullptr)
    {
        SALE_CONTEXT_CRASH(286, L"== CRASH == [%s], %s; bid context is null, bidderPcId:0x%I64X, bidContext:0x%p",
                           MODULE_NAME, L"SaleContext::RemoveBidContext", bidderPcId, nullptr);
        return false;
    }
    _bidList.erase(it);
    bidContext->removeReferenceCount(SALE_CONTEXT_FILE, 293);
    return true;
}

// 0x2c120
PurchaseContext* SaleContext::GetPurchaseContext(long long purchaserPcId)
{
    if (purchaserPcId <= 0)
    {
        SALE_CONTEXT_CRASH(303, L"== CRASH == [%s], %s; invalid parameter, purchaserPcId:0x%I64X",
                           MODULE_NAME, L"SaleContext::GetPurchaseContext", purchaserPcId);
        return nullptr;
    }
    DealingList::iterator it = _purchaseList.find(purchaserPcId);
    if (it == _purchaseList.end())
        return nullptr;
    DealingContext* const purchaseContext = it->second;
    if (purchaseContext == nullptr)
    {
        SALE_CONTEXT_CRASH(313,
                           L"== CRASH == [%s], %s; purchase context is null, purchaserPcId:0x%I64X, purchaseContext:0x%p",
                           MODULE_NAME, L"SaleContext::GetPurchaseContext", purchaserPcId, nullptr);
        return nullptr;
    }
    purchaseContext->addReferenceCount(false, SALE_CONTEXT_FILE, 316);
    return static_cast<PurchaseContext*>(purchaseContext);
}

// 0x2c2c0
bool SaleContext::IsPurchasing(long long purchaserPcId) const
{
    if (purchaserPcId <= 0)
    {
        SALE_CONTEXT_CRASH(325, L"== CRASH == [%s], %s; invalid parameter, purchaserPcId:0x%I64X",
                           MODULE_NAME, L"SaleContext::IsPurchasing", purchaserPcId);
        return false;
    }
    return _purchaseList.find(purchaserPcId) != _purchaseList.end();
}

// 0x2c3d0
bool SaleContext::AddPurchaseContext(PurchaseInfo const& purchaseInfo)
{
    void* const memory = Memory::_Manager[2]->Alloc(sizeof(PurchaseContext), SALE_CONTEXT_FILE, 338);
    DealingContext* const purchaseContext = memory != nullptr ? new (memory) PurchaseContext(purchaseInfo) : nullptr;
    // BUG: 0x2c3d0 no null check after Alloc; the failure path calls removeReferenceCount on nullptr.
    if (_purchaseList.insert(DealingList::value_type(purchaseInfo._dealingInfo._trader._participantPcId, purchaseContext))
            .second)
        return true;

    Log::Write(Log::LT_ERROR, SALE_CONTEXT_FILE, 344,
               L"[%s], %s; failed to add purchase context, saleId:0x%I64X, purchaseId:0x%I64X, purchaserPcId:0x%I64X",
               MODULE_NAME, L"SaleContext::AddPurchaseContext", _saleInfo._saleId, purchaseInfo._dealingInfo._dealingId,
               purchaseInfo._dealingInfo._trader._participantPcId);
    purchaseContext->removeReferenceCount(SALE_CONTEXT_FILE, 345);
    return false;
}

// 0x2c500
bool SaleContext::RemovePurchaseContext(long long purchaserPcId)
{
    if (purchaserPcId <= 0)
    {
        SALE_CONTEXT_CRASH(357, L"== CRASH == [%s], %s; invalid parameter, purchaserPcId:0x%I64X",
                           MODULE_NAME, L"SaleContext::RemovePurchaseContext", purchaserPcId);
        return false;
    }
    DealingList::iterator it = _purchaseList.find(purchaserPcId);
    if (it == _purchaseList.end())
    {
        Log::Write(Log::LT_ERROR, SALE_CONTEXT_FILE, 363,
                   L"[%s], %s; there is no such purchase context, purchaserPcId:0x%I64X",
                   MODULE_NAME, L"SaleContext::RemovePurchaseContext", purchaserPcId);
        return false;
    }
    DealingContext* const purchaseContext = it->second;
    if (purchaseContext == nullptr)
    {
        SALE_CONTEXT_CRASH(369,
                           L"== CRASH == [%s], %s; purchase context is null, purchaserPcId:0x%I64X, purchaseContext:0x%p",
                           MODULE_NAME, L"SaleContext::RemovePurchaseContext", purchaserPcId, nullptr);
        return false;
    }
    _purchaseList.erase(it);
    purchaseContext->removeReferenceCount(SALE_CONTEXT_FILE, 376);
    return true;
}

// ---- SaleContextManager ----

// 0x2c6f0
bool SaleContextManager::InitContextManager()
{
    if (_lockList != nullptr || _containerList != nullptr)
    {
        SALE_CONTEXT_CRASH(422,
                           L"== CRASH == [%s], %s; sale context manager is already initialized, lockList:0x%p, containerList:0x%p",
                           MODULE_NAME, L"SaleContextManager::InitContextManager", _lockList, _containerList);
        return false;
    }
    _lockList = saleArrayNew<CriticalSection>(_bucketCount, SALE_CONTEXT_FILE, 426);
    _containerList = saleArrayNew<Container>(_bucketCount, SALE_CONTEXT_FILE, 427);
    return true;
}

// 0x2c880
SaleContext* SaleContextManager::GetContext(long long saleId) const
{
    if (saleId <= 0)
    {
        SALE_CONTEXT_CRASH(435, L"== CRASH == [%s], %s; invalid parameter, saleId:0x%I64X",
                           MODULE_NAME, L"SaleContextManager::GetContext", saleId);
        return nullptr;
    }
    if (_lockList == nullptr || _containerList == nullptr)
    {
        SALE_CONTEXT_CRASH(439, L"== CRASH == [%s], %s; invalid sale context manager, lockList:0x%p, containerList:0x%p",
                           MODULE_NAME, L"SaleContextManager::GetContext", _lockList, _containerList);
        return nullptr;
    }

    int const index = static_cast<int>(saleId % _bucketCount);
    _lockList[index].Enter();
    Container::iterator it = _containerList[index].find(saleId);
    if (it == _containerList[index].end())
    {
        _lockList[index].Leave();
        return nullptr;
    }
    SaleContext* const saleContext = it->second;
    if (saleContext != nullptr)
    {
        saleContext->addReferenceCount(false, SALE_CONTEXT_FILE, 455);
        _lockList[index].Leave();
        return saleContext;
    }
    _lockList[index].Leave();
    SALE_CONTEXT_CRASH(452, L"== CRASH == [%s], %s; sale context is null, saleId:0x%I64X, saleContext:0x%p",
                       MODULE_NAME, L"SaleContextManager::GetContext", saleId, nullptr);
    return nullptr;
}

// 0x2caf0
bool SaleContextManager::AddContext(SaleContext* const saleContext)
{
    if (saleContext == nullptr)
    {
        SALE_CONTEXT_CRASH(465, L"== CRASH == [%s], %s; invalid parameter, saleContext:0x%p",
                           MODULE_NAME, L"SaleContextManager::AddContext", nullptr);
        return false;
    }
    if (_lockList == nullptr || _containerList == nullptr)
    {
        SALE_CONTEXT_CRASH(469, L"== CRASH == [%s], %s; invalid sale context manager, lockList:0x%p, containerList:0x%p",
                           MODULE_NAME, L"SaleContextManager::AddContext", _lockList, _containerList);
        return false;
    }
    long long const saleId = saleContext->_saleInfo._saleId;
    if (saleId <= 0)
    {
        Log::Write(Log::LT_ERROR, SALE_CONTEXT_FILE, 475, L"[%s], %s; invalid sale id, saleId:0x%I64X",
                   MODULE_NAME, L"SaleContextManager::AddContext", saleId);
        return false;
    }

    int const index = static_cast<int>(saleId % _bucketCount);
    _lockList[index].Enter();
    if (_containerList[index].insert(Container::value_type(saleId, saleContext)).second)
    {
        saleContext->addReferenceCount(false, SALE_CONTEXT_FILE, 490);
        InterlockedIncrement(&_contextCount);
        _lockList[index].Leave();
        return true;
    }
    _lockList[index].Leave();
    Log::Write(Log::LT_ERROR, SALE_CONTEXT_FILE, 486, L"[%s], %s; failed to add sale context, saleId:0x%I64X",
               MODULE_NAME, L"SaleContextManager::AddContext", saleId);
    return false;
}

// 0x2cd50
bool SaleContextManager::RemoveContext(long long saleId)
{
    if (saleId <= 0)
    {
        SALE_CONTEXT_CRASH(502, L"== CRASH == [%s], %s; invalid parameter, saleId:0x%I64X",
                           MODULE_NAME, L"SaleContextManager::RemoveContext", saleId);
        return false;
    }
    if (_lockList == nullptr || _containerList == nullptr)
    {
        SALE_CONTEXT_CRASH(506, L"== CRASH == [%s], %s; invalid sale context manager, lockList:0x%p, containerList:0x%p",
                           MODULE_NAME, L"SaleContextManager::RemoveContext", _lockList, _containerList);
        return false;
    }

    int const index = static_cast<int>(saleId % _bucketCount);
    _lockList[index].Enter();
    Container::iterator it = _containerList[index].find(saleId);
    if (it == _containerList[index].end())
    {
        _lockList[index].Leave();
        Log::Write(Log::LT_ERROR, SALE_CONTEXT_FILE, 516, L"[%s], %s; there is no such sale context, saleId:0x%I64X",
                   MODULE_NAME, L"SaleContextManager::RemoveContext", saleId);
        return false;
    }
    SaleContext* const saleContext = it->second;
    if (saleContext != nullptr)
    {
        _containerList[index].erase(it);
        saleContext->removeReferenceCount(SALE_CONTEXT_FILE, 528);
        InterlockedDecrement(&_contextCount);
        _lockList[index].Leave();
        return true;
    }
    _lockList[index].Leave();
    SALE_CONTEXT_CRASH(523, L"== CRASH == [%s], %s; sale context is null, saleId:0x%I64X, saleContext:0x%p",
                       MODULE_NAME, L"SaleContextManager::RemoveContext", saleId, nullptr);
    return false;
}
