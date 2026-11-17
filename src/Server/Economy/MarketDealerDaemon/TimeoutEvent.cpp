// TimeoutEvent.obj (MarketDealerDaemon PDB).
// LIFT: The scoped lock of Lock.h (AutoCS) is inlined in processTimeout. The AutoCS bodies are in JobContext.cpp.
#include <winsock2.h>
#include <windows.h>
#include <string.h>
#include <new>

#include "TimeoutEvent.h"
#include "MarketDealerDefine.h"
#include "MarketDB.h"
#include "MarketDealerDaemon.h"
#include "SaleContext.h"
#include "SaleTimeContext.h"
#include "BidContext.h"
#include "DeliveryContext.h"
#include "DeliveryRelation.h"
#include "MarketStatement.h"
#include "Postman.h"
#include "Lock.h"
#include "Log.h"
#include "AlertSender.h"
#include "Memory.h"
#include "MemoryManager.h"

#define TIMEOUT_EVENT_FILE L"TimeoutEvent.cpp"
static wchar_t const* const MODULE_NAME = L"timeout event";

#define TIMEOUT_EVENT_CRASH(line, ...)                                    \
    do                                                                    \
    {                                                                     \
        Log::Write(Log::LT_ERROR, TIMEOUT_EVENT_FILE, line, __VA_ARGS__); \
        AlertSender::Write(TIMEOUT_EVENT_FILE, line, __VA_ARGS__);        \
    } while (0)

// LIFT: inlined array new of DeliveryRelation (0x30240). It allocates 8 bytes more than the elements, but it does
// not write a count. The element init is the same as in MarketDB::ExpireAuction.
static DeliveryRelation* newDeliveryRelationArray(int const count, int const line)
{
    void* const raw =
        Memory::_Manager[2]->Alloc(sizeof(DeliveryRelation) * static_cast<long long>(count) + 8, TIMEOUT_EVENT_FILE,
                                   line);
    if (raw == nullptr)
        return nullptr;
    DeliveryRelation* const items = static_cast<DeliveryRelation*>(raw);
    for (int i = count - 1, n = 0; i >= 0; --i, ++n)
    {
        DeliveryRelation& relation = items[n];
        relation._deliveryId = 0;
        relation._deliveryReason = 0;
        relation._pawnOwnerServiceId = 0;
        relation._pawnOwnerPcId = 0;
        relation._recipientPcId = 0;
        memset(relation._marketStatement._statementTitle, 0, sizeof(relation._marketStatement._statementTitle));
        memset(relation._marketStatement._statementBody, 0, sizeof(relation._marketStatement._statementBody));
        relation._moneyAmount = 0;
    }
    return items;
}

// LIFT: inlined array delete (0x30240).
// ❓ The original also writes the pointer to a thread-local slot (TLS block + 0x10) before Free.
static void deleteArray(void* const items, int const line)
{
    Memory::_Manager[2]->Free(items, TIMEOUT_EVENT_FILE, line);
}

// 0x2f9a0
unsigned int InstantSaleTimeoutEvent::EventId() const
{
    return 128;
}

// 0x2f9b0
unsigned int AuctionTimeoutEvent::EventId() const
{
    return 129;
}

// 0x2f9c0 (scalar deleting destructor)
InstantSaleTimeoutEvent::~InstantSaleTimeoutEvent()
{
    if (_saleContext != nullptr)
    {
        _saleContext->removeReferenceCount(TIMEOUT_EVENT_FILE, 41);
        _saleContext = nullptr;
    }
}

// 0x2fa20
bool InstantSaleTimeoutEvent::HandleEvent(EventContext* context, unsigned long bytes)
{
    Log::Write(Log::LT_DEBUG, TIMEOUT_EVENT_FILE, 48, L"[%s], %s; <BEGIN EVENT HANDLER>", MODULE_NAME,
               L"InstantSaleTimeoutEvent::HandleEvent");
    processTimeout();
    Log::Write(Log::LT_DEBUG, TIMEOUT_EVENT_FILE, 52, L"[%s], %s; <END EVENT HANDLER>", MODULE_NAME,
               L"InstantSaleTimeoutEvent::HandleEvent");
    removeReferenceCount(TIMEOUT_EVENT_FILE, 54);
    return true;
}

// 0x2fac0
void InstantSaleTimeoutEvent::processTimeout()
{
    wchar_t const* const fn = L"InstantSaleTimeoutEvent::processTimeout";
    long long itemDeliveryId = 0;
    MarketStatement marketStatement;
    memset(marketStatement._statementTitle, 0, sizeof(marketStatement._statementTitle));
    memset(marketStatement._statementBody, 0, sizeof(marketStatement._statementBody));

    AutoCS autoLock(&_saleContext->_lock);
    char const saleStatus = _saleContext->_saleInfo._saleStatus;
    if (saleStatus != SaleInfo::SALESTATUS_SELLING)
    {
        Log::Write(Log::LT_ERROR, TIMEOUT_EVENT_FILE, 69,
                   L"[%s], %s; sale status is not selling, saleId:0x%I64X, saleStatus:%d", MODULE_NAME, fn, _saleId,
                   static_cast<int>(saleStatus));
        autoLock.Leave();
        return;
    }

    int dbRetValue = 0;
    if (!MarketDB::ExpireSale(dbRetValue, _saleId, itemDeliveryId, marketStatement))
    {
        Log::Write(Log::LT_ERROR, TIMEOUT_EVENT_FILE, 75,
                   L"[%s], %s; failed to expire instant sale, dbRetValue:%d, saleId:0x%I64X", MODULE_NAME, fn,
                   dbRetValue, _saleId);
        autoLock.Leave();
        return;
    }

    _saleContext->_saleInfo._saleStatus = SaleInfo::SALESTATUS_SALE_TIMEOUT;
    autoLock.Leave();

    if (!MarketDealerDaemon::_instance->_saleTimeContextManager->RemoveContext(
            _saleId, _saleContext->_saleInfo._saleExpirationTime))
    {
        TIMEOUT_EVENT_CRASH(90,
                            L"== CRASH == [%s], %s; exception occurred; failed to remove saletime context, "
                            L"saleId:0x%I64X, saleExpirationTime:%I64d",
                            MODULE_NAME, fn, _saleId, _saleContext->_saleInfo._saleExpirationTime);
    }

    DeliveryContext* deliveryContext = nullptr;
    void* const memory = Memory::_Manager[2]->Alloc(sizeof(DeliveryContext), TIMEOUT_EVENT_FILE, 94);
    if (memory != nullptr)
    {
        DeliveryInfo deliveryInfo;
        deliveryInfo._deliveryId = itemDeliveryId;
        deliveryInfo._deliveryReason = ECONOMY_MARKET_DELIVERYREASON_SALE_TIMEOUT;
        deliveryInfo._saleId = _saleId;
        deliveryInfo._pawnId = _saleContext->_saleInfo._pawnId;
        deliveryInfo._pawnServiceId = _saleId;
        memcpy(&deliveryInfo._pawnOwner, &_saleContext->_saleInfo._seller, sizeof(Participant));
        memcpy(&deliveryInfo._recipient, &_saleContext->_saleInfo._seller, sizeof(Participant));
        memcpy(&deliveryInfo._marketStatement, &marketStatement, sizeof(MarketStatement));
        deliveryInfo._jobStatus = DeliveryInfo::JOBSTATUS_DELIVERY_READY;
        deliveryContext = ::new (memory) DeliveryContext(deliveryInfo, _saleContext->_saleItemInfo);
    }

    if (!MarketDealerDaemon::_instance->_saleContextManager->RemoveContext(_saleId))
    {
        TIMEOUT_EVENT_CRASH(106, L"== CRASH == [%s], %s; exception occurred; failed to remove sale context, saleId:0x%I64X",
                            MODULE_NAME, fn, _saleId);
    }
    Log::Write(Log::LT_DEBUG, TIMEOUT_EVENT_FILE, 109, L"[%s], %s; succeeded to expire instant sale, saleId:0x%I64X",
               MODULE_NAME, fn, _saleId);

    {
        // BUG: 0x2fac0 no null check after the DeliveryContext alloc; the lock uses a null context.
        AutoCS deliveryLock(&deliveryContext->_lock);
        if (!MarketDealerDaemon::_instance->_deliveryContextManager->AddContext(deliveryContext))
        {
            TIMEOUT_EVENT_CRASH(117,
                                L"== CRASH == [%s], %s; exception occurred; failed to add delivery context, "
                                L"deliveryId:0x%I64X",
                                MODULE_NAME, fn, itemDeliveryId);
        }
        if (!Postman::DeliverPost(deliveryContext))
        {
            Log::Write(Log::LT_ERROR, TIMEOUT_EVENT_FILE, 121, L"[%s], %s; failed to deliver post, deliveryId:0x%I64X",
                       MODULE_NAME, fn, itemDeliveryId);
        }
    }
    deliveryContext->removeReferenceCount(TIMEOUT_EVENT_FILE, 125);
}

// 0x30140 (scalar deleting destructor)
AuctionTimeoutEvent::~AuctionTimeoutEvent()
{
    if (_saleContext != nullptr)
    {
        _saleContext->removeReferenceCount(TIMEOUT_EVENT_FILE, 145);
        _saleContext = nullptr;
    }
}

// 0x301a0
bool AuctionTimeoutEvent::HandleEvent(EventContext* context, unsigned long bytes)
{
    Log::Write(Log::LT_DEBUG, TIMEOUT_EVENT_FILE, 152, L"[%s], %s; <BEGIN EVENT HANDLER>", MODULE_NAME,
               L"AuctionTimeoutEvent::HandleEvent");
    processTimeout();
    Log::Write(Log::LT_DEBUG, TIMEOUT_EVENT_FILE, 156, L"[%s], %s; <END EVENT HANDLER>", MODULE_NAME,
               L"AuctionTimeoutEvent::HandleEvent");
    removeReferenceCount(TIMEOUT_EVENT_FILE, 158);
    return true;
}

// 0x30240
void AuctionTimeoutEvent::processTimeout()
{
    wchar_t const* const fn = L"AuctionTimeoutEvent::processTimeout";
    int deliveryCount = 0;

    AutoCS autoLock(&_saleContext->_lock);
    char const saleStatus = _saleContext->_saleInfo._saleStatus;
    if (saleStatus != SaleInfo::SALESTATUS_SELLING)
    {
        Log::Write(Log::LT_ERROR, TIMEOUT_EVENT_FILE, 174,
                   L"[%s], %s; sale status is not selling, saleId:0x%I64X, saleStatus:%d", MODULE_NAME, fn, _saleId,
                   static_cast<int>(saleStatus));
        autoLock.Leave();
        return;
    }

    int const arraySize = _saleContext->_bidCount + 1;
    DeliveryRelation* relation = newDeliveryRelationArray(arraySize, 179);
    int dbRetValue = 0;
    if (!MarketDB::ExpireAuction(dbRetValue, _saleId, MarketDealerDaemon::_instance->_config->_ruleResetTime,
                                 deliveryCount, relation, arraySize))
    {
        Log::Write(Log::LT_ERROR, TIMEOUT_EVENT_FILE, 183,
                   L"[%s], %s; failed to expire auction, dbRetValue:%d, saleId:0x%I64X", MODULE_NAME, fn, dbRetValue,
                   _saleId);
        deleteArray(relation, 184);
        autoLock.Leave();
        return;
    }

    _saleContext->_saleInfo._saleStatus = SaleInfo::SALESTATUS_SOLDOUT;
    autoLock.Leave();

    if (arraySize != deliveryCount)
    {
        Log::Write(Log::LT_ERROR, TIMEOUT_EVENT_FILE, 198,
                   L"[%s], %s; exception occurred; delivery count is not same, saleId:0x%I64X, arraySize:%d, "
                   L"deliveryCount:%d",
                   MODULE_NAME, fn, _saleId, arraySize, deliveryCount);
        deleteArray(relation, 199);
        return;
    }

    if (!MarketDealerDaemon::_instance->_saleTimeContextManager->RemoveContext(
            _saleId, _saleContext->_saleInfo._saleExpirationTime))
    {
        TIMEOUT_EVENT_CRASH(205,
                            L"== CRASH == [%s], %s; exception occurred; failed to remove saletime context, "
                            L"saleId:0x%I64X, saleExpirationTime:%I64d",
                            MODULE_NAME, fn, _saleId, _saleContext->_saleInfo._saleExpirationTime);
    }

    DeliveryContext** const deliveryContextList = static_cast<DeliveryContext**>(Memory::_Manager[2]->AllocZero(
        sizeof(DeliveryContext*) * static_cast<long long>(deliveryCount), TIMEOUT_EVENT_FILE, 209));
    for (int i = 0; i < deliveryCount; ++i)
    {
        DeliveryRelation const& rel = relation[i];
        int const deliveryReason = rel._deliveryReason;
        switch (rel._deliveryReason)
        {
        case ECONOMY_MARKET_DELIVERYREASON_SALE_TIMEOUT:
        {
            if (rel._pawnOwnerServiceId != _saleId)
            {
                TIMEOUT_EVENT_CRASH(219,
                                    L"== CRASH == [%s], %s; exception occurred; pawn owner service id is not same, "
                                    L"saleId:0x%I64X, deliveryId:0x%I64X, deliveryReason:%d, "
                                    L"pawnOwnerServiceId:0x%I64X, saleId:0x%I64X",
                                    MODULE_NAME, fn, _saleId, rel._deliveryId, deliveryReason, rel._pawnOwnerServiceId,
                                    _saleId);
                break;
            }
            long long const sellerPcId = _saleContext->_saleInfo._seller._participantPcId;
            if (rel._pawnOwnerPcId != sellerPcId)
            {
                TIMEOUT_EVENT_CRASH(224,
                                    L"== CRASH == [%s], %s; exception occurred; pawn owner pcid is not same, "
                                    L"saleId:0x%I64X, deliveryId:0x%I64X, deliveryReason:%d, pawnOwnerPcId:0x%I64X, "
                                    L"sellerPcId:0x%I64X",
                                    MODULE_NAME, fn, _saleId, rel._deliveryId, deliveryReason, rel._pawnOwnerPcId,
                                    _saleContext->_saleInfo._seller._participantPcId);
                break;
            }
            if (rel._recipientPcId != sellerPcId)
            {
                TIMEOUT_EVENT_CRASH(229,
                                    L"== CRASH == [%s], %s; exception occurred; recipient pcid is not same, "
                                    L"saleId:0x%I64X, deliveryId:0x%I64X, deliveryReason:%d, recipientPcId:0x%I64X, "
                                    L"sellerPcId:0x%I64X",
                                    MODULE_NAME, fn, _saleId, rel._deliveryId, deliveryReason, rel._recipientPcId,
                                    _saleContext->_saleInfo._seller._participantPcId);
                break;
            }
            DeliveryContext* deliveryContext = nullptr;
            void* const memory = Memory::_Manager[2]->Alloc(sizeof(DeliveryContext), TIMEOUT_EVENT_FILE, 233);
            if (memory != nullptr)
            {
                DeliveryInfo deliveryInfo;
                deliveryInfo._deliveryId = rel._deliveryId;
                deliveryInfo._deliveryReason = rel._deliveryReason;
                deliveryInfo._saleId = _saleId;
                deliveryInfo._pawnId = _saleContext->_saleInfo._pawnId;
                deliveryInfo._pawnServiceId = _saleId;
                memcpy(&deliveryInfo._pawnOwner, &_saleContext->_saleInfo._seller, sizeof(Participant));
                memcpy(&deliveryInfo._recipient, &_saleContext->_saleInfo._seller, sizeof(Participant));
                memcpy(&deliveryInfo._marketStatement, &rel._marketStatement, sizeof(MarketStatement));
                deliveryInfo._jobStatus = DeliveryInfo::JOBSTATUS_DELIVERY_READY;
                deliveryContext = ::new (memory) DeliveryContext(deliveryInfo, _saleContext->_saleItemInfo);
            }
            deliveryContextList[i] = deliveryContext;
            break;
        }
        case ECONOMY_MARKET_DELIVERYREASON_SALE_SUCCESS:
        {
            BidContext* const bidContext = _saleContext->GetBidContext(rel._pawnOwnerPcId);
            if (bidContext == nullptr)
            {
                TIMEOUT_EVENT_CRASH(250,
                                    L"== CRASH == [%s], %s; exception occurred; there is no such bid context, "
                                    L"saleId:0x%I64X, deliveryId:0x%I64X, deliveryReason:%d, pawnOwnerPcId:0x%I64X",
                                    MODULE_NAME, fn, _saleId, rel._deliveryId, deliveryReason, rel._pawnOwnerPcId);
                break;
            }
            DealingInfo const& dealingInfo = bidContext->_bidInfo._dealingInfo;
            if (rel._pawnOwnerServiceId != dealingInfo._dealingId)
            {
                TIMEOUT_EVENT_CRASH(255,
                                    L"== CRASH == [%s], %s; exception occurred; pawn owner service id is not same, "
                                    L"saleId:0x%I64X, deliveryId:0x%I64X, deliveryReason:%d, "
                                    L"pawnOwnerServiceId:0x%I64X, bidId:0x%I64X",
                                    MODULE_NAME, fn, _saleId, rel._deliveryId, deliveryReason, rel._pawnOwnerServiceId,
                                    dealingInfo._dealingId);
                bidContext->removeReferenceCount(TIMEOUT_EVENT_FILE, 256);
                break;
            }
            if (rel._pawnOwnerPcId != dealingInfo._trader._participantPcId)
            {
                TIMEOUT_EVENT_CRASH(261,
                                    L"== CRASH == [%s], %s; exception occurred; pawn owner pcid is not same, "
                                    L"saleId:0x%I64X, deliveryId:0x%I64X, deliveryReason:%d, pawnOwnerPcId:0x%I64X, "
                                    L"bidderPcId:0x%I64X",
                                    MODULE_NAME, fn, _saleId, rel._deliveryId, deliveryReason, rel._pawnOwnerPcId,
                                    dealingInfo._trader._participantPcId);
                bidContext->removeReferenceCount(TIMEOUT_EVENT_FILE, 262);
                break;
            }
            if (rel._recipientPcId != _saleContext->_saleInfo._seller._participantPcId)
            {
                TIMEOUT_EVENT_CRASH(267,
                                    L"== CRASH == [%s], %s; exception occurred; recipient pcid is not same, "
                                    L"saleId:0x%I64X, deliveryId:0x%I64X, deliveryReason:%d, recipientPcId:0x%I64X, "
                                    L"sellerPcId:0x%I64X",
                                    MODULE_NAME, fn, _saleId, rel._deliveryId, deliveryReason, rel._recipientPcId,
                                    _saleContext->_saleInfo._seller._participantPcId);
                bidContext->removeReferenceCount(TIMEOUT_EVENT_FILE, 268);
                break;
            }
            DeliveryContext* deliveryContext = nullptr;
            void* const memory = Memory::_Manager[2]->Alloc(sizeof(DeliveryContext), TIMEOUT_EVENT_FILE, 272);
            if (memory != nullptr)
            {
                DeliveryInfo deliveryInfo;
                deliveryInfo._deliveryId = rel._deliveryId;
                deliveryInfo._deliveryReason = rel._deliveryReason;
                deliveryInfo._saleId = _saleId;
                deliveryInfo._pawnId = dealingInfo._pawnId;
                deliveryInfo._pawnServiceId = dealingInfo._dealingId;
                memcpy(&deliveryInfo._pawnOwner, &dealingInfo._trader, sizeof(Participant));
                memcpy(&deliveryInfo._recipient, &_saleContext->_saleInfo._seller, sizeof(Participant));
                memcpy(&deliveryInfo._marketStatement, &rel._marketStatement, sizeof(MarketStatement));
                deliveryInfo._jobStatus = DeliveryInfo::JOBSTATUS_DELIVERY_READY;
                deliveryContext = ::new (memory) DeliveryContext(deliveryInfo, rel._moneyAmount);
            }
            deliveryContextList[i] = deliveryContext;
            bidContext->removeReferenceCount(TIMEOUT_EVENT_FILE, 282);
            break;
        }
        case ECONOMY_MARKET_DELIVERYREASON_BID_WINNER:
        {
            if (rel._pawnOwnerServiceId != _saleId)
            {
                TIMEOUT_EVENT_CRASH(289,
                                    L"== CRASH == [%s], %s; exception occurred; pawn owner service id is not same, "
                                    L"saleId:0x%I64X, deliveryId:0x%I64X, deliveryReason:%d, "
                                    L"pawnOwnerServiceId:0x%I64X, saleId:0x%I64X",
                                    MODULE_NAME, fn, _saleId, rel._deliveryId, deliveryReason, rel._pawnOwnerServiceId,
                                    _saleId);
                break;
            }
            if (rel._pawnOwnerPcId != _saleContext->_saleInfo._seller._participantPcId)
            {
                TIMEOUT_EVENT_CRASH(294,
                                    L"== CRASH == [%s], %s; exception occurred; pawn owner pcid is not same, "
                                    L"saleId:0x%I64X, deliveryId:0x%I64X, deliveryReason:%d, pawnOwnerPcId:0x%I64X, "
                                    L"sellerPcId:0x%I64X",
                                    MODULE_NAME, fn, _saleId, rel._deliveryId, deliveryReason, rel._pawnOwnerPcId,
                                    _saleContext->_saleInfo._seller._participantPcId);
                break;
            }
            BidContext* const bidContext =
                _saleContext->GetBidContext(_saleContext->_saleInfo._topBidder._participantPcId);
            if (bidContext == nullptr)
            {
                TIMEOUT_EVENT_CRASH(301,
                                    L"== CRASH == [%s], %s; exception occurred; there is no such bid context, "
                                    L"saleId:0x%I64X, deliveryId:0x%I64X, deliveryReason:%d, topBidderPcId:0x%I64X",
                                    MODULE_NAME, fn, _saleId, rel._deliveryId, deliveryReason,
                                    _saleContext->_saleInfo._topBidder._participantPcId);
                break;
            }
            DealingInfo const& dealingInfo = bidContext->_bidInfo._dealingInfo;
            if (rel._recipientPcId != dealingInfo._trader._participantPcId)
            {
                TIMEOUT_EVENT_CRASH(306,
                                    L"== CRASH == [%s], %s; exception occurred; recipient pcid is not same, "
                                    L"saleId:0x%I64X, deliveryId:0x%I64X, deliveryReason:%d, recipientPcId:0x%I64X, "
                                    L"bidderPcId:0x%I64X",
                                    MODULE_NAME, fn, _saleId, rel._deliveryId, deliveryReason, rel._recipientPcId,
                                    dealingInfo._trader._participantPcId);
                bidContext->removeReferenceCount(TIMEOUT_EVENT_FILE, 307);
                break;
            }
            DeliveryContext* deliveryContext = nullptr;
            void* const memory = Memory::_Manager[2]->Alloc(sizeof(DeliveryContext), TIMEOUT_EVENT_FILE, 311);
            if (memory != nullptr)
            {
                DeliveryInfo deliveryInfo;
                deliveryInfo._deliveryId = rel._deliveryId;
                deliveryInfo._deliveryReason = rel._deliveryReason;
                deliveryInfo._saleId = _saleId;
                deliveryInfo._pawnId = _saleContext->_saleInfo._pawnId;
                deliveryInfo._pawnServiceId = _saleId;
                memcpy(&deliveryInfo._pawnOwner, &_saleContext->_saleInfo._seller, sizeof(Participant));
                memcpy(&deliveryInfo._recipient, &dealingInfo._trader, sizeof(Participant));
                memcpy(&deliveryInfo._marketStatement, &rel._marketStatement, sizeof(MarketStatement));
                deliveryInfo._jobStatus = DeliveryInfo::JOBSTATUS_DELIVERY_READY;
                deliveryContext = ::new (memory) DeliveryContext(deliveryInfo, _saleContext->_saleItemInfo);
            }
            deliveryContextList[i] = deliveryContext;
            bidContext->removeReferenceCount(TIMEOUT_EVENT_FILE, 321);
            break;
        }
        case ECONOMY_MARKET_DELIVERYREASON_BID_LOSER:
        {
            BidContext* const bidContext = _saleContext->GetBidContext(rel._pawnOwnerPcId);
            if (bidContext == nullptr)
            {
                TIMEOUT_EVENT_CRASH(329,
                                    L"== CRASH == [%s], %s; exception occurred; there is no such bid context, "
                                    L"saleId:0x%I64X, deliveryId:0x%I64X, deliveryReason:%d, pawnOwnerPcId:0x%I64X",
                                    MODULE_NAME, fn, _saleId, rel._deliveryId, deliveryReason, rel._pawnOwnerPcId);
                break;
            }
            DealingInfo const& dealingInfo = bidContext->_bidInfo._dealingInfo;
            if (rel._pawnOwnerServiceId != dealingInfo._dealingId)
            {
                TIMEOUT_EVENT_CRASH(334,
                                    L"== CRASH == [%s], %s; exception occurred; pawn owner service id is not same, "
                                    L"saleId:0x%I64X, deliveryId:0x%I64X, deliveryReason:%d, "
                                    L"pawnOwnerServiceId:0x%I64X, bidId:0x%I64X",
                                    MODULE_NAME, fn, _saleId, rel._deliveryId, deliveryReason, rel._pawnOwnerServiceId,
                                    dealingInfo._dealingId);
                bidContext->removeReferenceCount(TIMEOUT_EVENT_FILE, 335);
                break;
            }
            if (rel._pawnOwnerPcId != dealingInfo._trader._participantPcId)
            {
                TIMEOUT_EVENT_CRASH(340,
                                    L"== CRASH == [%s], %s; exception occurred; pawn owner pcid is not same, "
                                    L"saleId:0x%I64X, deliveryId:0x%I64X, deliveryReason:%d, pawnOwnerPcId:0x%I64X, "
                                    L"bidderPcId:0x%I64X",
                                    MODULE_NAME, fn, _saleId, rel._deliveryId, deliveryReason, rel._pawnOwnerPcId,
                                    dealingInfo._trader._participantPcId);
                bidContext->removeReferenceCount(TIMEOUT_EVENT_FILE, 341);
                break;
            }
            if (rel._recipientPcId != dealingInfo._trader._participantPcId)
            {
                TIMEOUT_EVENT_CRASH(346,
                                    L"== CRASH == [%s], %s; exception occurred; recipient pcid is not same, "
                                    L"saleId:0x%I64X, deliveryId:0x%I64X, deliveryReason:%d, recipientPcId:0x%I64X, "
                                    L"bidderPcId:0x%I64X",
                                    MODULE_NAME, fn, _saleId, rel._deliveryId, deliveryReason, rel._recipientPcId,
                                    dealingInfo._trader._participantPcId);
                bidContext->removeReferenceCount(TIMEOUT_EVENT_FILE, 347);
                break;
            }
            if (rel._moneyAmount != dealingInfo._dealingPrice)
            {
                TIMEOUT_EVENT_CRASH(352,
                                    L"== CRASH == [%s], %s; exception occurred; money amount is not same, "
                                    L"saleId:0x%I64X, deliveryId:0x%I64X, deliveryReason:%d, moneyAmount:%I64d, "
                                    L"bidPrice:%I64d",
                                    MODULE_NAME, fn, _saleId, rel._deliveryId, deliveryReason, rel._moneyAmount,
                                    dealingInfo._dealingPrice);
                bidContext->removeReferenceCount(TIMEOUT_EVENT_FILE, 353);
                break;
            }
            DeliveryContext* deliveryContext = nullptr;
            void* const memory = Memory::_Manager[2]->Alloc(sizeof(DeliveryContext), TIMEOUT_EVENT_FILE, 357);
            if (memory != nullptr)
            {
                DeliveryInfo deliveryInfo;
                deliveryInfo._deliveryId = rel._deliveryId;
                deliveryInfo._deliveryReason = rel._deliveryReason;
                deliveryInfo._saleId = _saleId;
                deliveryInfo._pawnId = dealingInfo._pawnId;
                deliveryInfo._pawnServiceId = dealingInfo._dealingId;
                memcpy(&deliveryInfo._pawnOwner, &dealingInfo._trader, sizeof(Participant));
                memcpy(&deliveryInfo._recipient, &dealingInfo._trader, sizeof(Participant));
                memcpy(&deliveryInfo._marketStatement, &rel._marketStatement, sizeof(MarketStatement));
                deliveryInfo._jobStatus = DeliveryInfo::JOBSTATUS_DELIVERY_READY;
                deliveryContext = ::new (memory) DeliveryContext(deliveryInfo, rel._moneyAmount);
            }
            deliveryContextList[i] = deliveryContext;
            bidContext->removeReferenceCount(TIMEOUT_EVENT_FILE, 367);
            break;
        }
        default:
            TIMEOUT_EVENT_CRASH(371,
                                L"== CRASH == [%s], %s; invalid delivery reason, saleId:0x%I64X, deliveryId:0x%I64X, "
                                L"deliveryReason:%d",
                                MODULE_NAME, fn, _saleId, rel._deliveryId, deliveryReason);
            break;
        }
    }
    deleteArray(relation, 375);

    if (!MarketDealerDaemon::_instance->_saleContextManager->RemoveContext(_saleId))
    {
        TIMEOUT_EVENT_CRASH(379, L"== CRASH == [%s], %s; exception occurred; failed to remove sale context, saleId:0x%I64X",
                            MODULE_NAME, fn, _saleId);
    }
    Log::Write(Log::LT_DEBUG, TIMEOUT_EVENT_FILE, 382, L"[%s], %s; succeeded to expire auction, saleId:0x%I64X",
               MODULE_NAME, fn, _saleId);

    DeliveryContextManager* const deliveryContextManager = MarketDealerDaemon::_instance->_deliveryContextManager;
    for (int i = 0; i < deliveryCount; ++i)
    {
        // BUG: 0x30240 a list entry is null when a check above fails or the alloc fails; the lock then uses a
        // null context.
        DeliveryContext* const deliveryContext = deliveryContextList[i];
        AutoCS deliveryLock(&deliveryContext->_lock);
        if (!deliveryContextManager->AddContext(deliveryContext))
        {
            TIMEOUT_EVENT_CRASH(392,
                                L"== CRASH == [%s], %s; exception occurred; failed to add delivery context, "
                                L"deliveryId:0x%I64X",
                                MODULE_NAME, fn, deliveryContext->_deliveryInfo._deliveryId);
        }
        if (!Postman::DeliverPost(deliveryContext))
        {
            Log::Write(Log::LT_ERROR, TIMEOUT_EVENT_FILE, 396, L"[%s], %s; failed to deliver post, deliveryId:0x%I64X",
                       MODULE_NAME, fn, deliveryContext->_deliveryInfo._deliveryId);
        }
        deliveryContext->removeReferenceCount(TIMEOUT_EVENT_FILE, 399);
    }
    Memory::_Manager[2]->Free(deliveryContextList, TIMEOUT_EVENT_FILE, 402);
}
