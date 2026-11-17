// MarketDB.obj (MarketDealerDaemon PDB).
// Card lift-marketdealerdaemon-4: AutoDbTran dtor, tax rate tables, load lists (0x1b170..0x1e400).
// Cards 5, 6 and 7 add the other bodies.
#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <string.h>
#include <new>
#include "MarketDB.h"
#include "Db.h"
#include "Log.h"
#include "AlertSender.h"
#include "Memory.h"
#include "Dealings.h"
#include "SaleContext.h"
#include "SaleTimeContext.h"
#include "DeliveryContext.h"
#include "TaxRateDataManager.h"
#include "MarketDealerDaemon.h"

#define MARKETDB_FILE L"MarketDB.cpp"
static wchar_t const* const MODULE_NAME = L"market db";  // PDB MODULE_NAME

#define FAIL_ACQUIRE L"[%s], %s; failed to acquire transaction, dbId:%d"
#define FAIL_PREPARE L"[%s], %s; failed to prepare sql, query:%s"
#define FAIL_BIND L"[%s], %s; failed to bind parameter"
#define FAIL_EXECUTE L"[%s], %s; failed to execute stored procedure, dbRetValue:%d"
#define FAIL_FETCH L"[%s], %s; failed to fetch"

namespace
{
unsigned int const kDbId = MarketDealerDaemon::MARKET_DB_ID;
unsigned long long const kNullData = static_cast<unsigned long long>(-1);  // SQL_NULL_DATA
unsigned long long const kNts = static_cast<unsigned long long>(-3);       // SQL_NTS
int const kMaxTaxRateCount = 10;
char const kSaleTypeAuction = 1;      // ECONOMY_SALETYPE_AUCTION (EconomySaleType)
char const kSaleTypeInstantSale = 2;  // ECONOMY_SALETYPE_INSTANT_SALE (EconomySaleType)

wchar_t* Query(wchar_t const* text) { return const_cast<wchar_t*>(text); }

// LIFT: Not a PDB function. The two tax rate setters (0x1b1c0, 0x1b4f0) have the same inlined bind loop.
template <class Table>
bool BindTaxRateParams(DbTransaction* tran, Table& taxRateTable, unsigned long long (*paramLen)[kMaxTaxRateCount])
{
    unsigned int index = 1;
    for (int i = 0; i < kMaxTaxRateCount; ++i)
    {
        void* interval = nullptr;
        void* taxRate = nullptr;
        if (i < taxRateTable._taxRateCount)
        {
            interval = &taxRateTable._taxRateList[i]._interval;
            taxRate = &taxRateTable._taxRateList[i]._taxRate;
        }
        else
        {
            paramLen[0][i] = kNullData;
            paramLen[1][i] = kNullData;
        }
        if (!tran->BindParam(index + 1, SQL_PARAM_INPUT, interval, 0, 0, SQL_BIGINT, SQL_C_SBIGINT, &paramLen[0][i]))
            return false;
        index += 2;
        if (!tran->BindParam(index, SQL_PARAM_INPUT, taxRate, 0, 0, SQL_INTEGER, SQL_C_SLONG, &paramLen[1][i]))
            return false;
    }
    return true;
}
}  // namespace

// 0x1b170
AutoDbTran::~AutoDbTran()
{
    if (Tran != nullptr)
    {
        if (TimeoutSec != 10)
            SQLSetStmtAttrW(Tran->StmtHandle, SQL_QUERY_TIMEOUT,
                            reinterpret_cast<SQLPOINTER>(static_cast<long long>(TimeoutSec)), 0);
        Db::ReleaseTransaction(Tran);
        Tran = nullptr;
    }
}

// 0x1b1c0
bool const MarketDB::SetSaleIncomeTaxRateTable(int& dbRetValue, SaleIncomeTaxRateTable& taxRateTable)
{
    wchar_t const* const fn = L"MarketDB::SetSaleIncomeTaxRateTable";
    AutoDbTran tran(kDbId);
    if (tran.Tran == nullptr)
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 34, FAIL_ACQUIRE, MODULE_NAME, fn, kDbId);
        return false;
    }
    wchar_t const* const query = L"{?=CALL dbo.usp_SetSaleIncomeTaxRate(?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)}";
    if (!tran.Tran->Prepare(Query(query)))
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 50, FAIL_PREPARE, MODULE_NAME, fn, query);
        return false;
    }
    unsigned long long dbRetValueLen = 0;
    unsigned long long paramLen[2][kMaxTaxRateCount] = {{0}};
    if (!tran.Tran->BindParam(1, SQL_PARAM_OUTPUT, &dbRetValue, 0, 0, SQL_INTEGER, SQL_C_SLONG, &dbRetValueLen) ||
        !BindTaxRateParams(tran.Tran, taxRateTable, paramLen))
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 85, FAIL_BIND, MODULE_NAME, fn);
        return false;
    }
    if (!tran.Tran->Execute())
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 75, FAIL_EXECUTE, MODULE_NAME, fn, dbRetValue);
        return false;
    }
    return dbRetValue == 0;
}

// 0x1b4f0
bool const MarketDB::SetGrossIncomeTaxRateTable(int& dbRetValue, GrossIncomeTaxRateTable& taxRateTable)
{
    wchar_t const* const fn = L"MarketDB::SetGrossIncomeTaxRateTable";
    AutoDbTran tran(kDbId);
    if (tran.Tran == nullptr)
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 93, FAIL_ACQUIRE, MODULE_NAME, fn, kDbId);
        return false;
    }
    wchar_t const* const query = L"{?=CALL dbo.usp_SetGrossIncomeTaxRate(?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)}";
    if (!tran.Tran->Prepare(Query(query)))
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 109, FAIL_PREPARE, MODULE_NAME, fn, query);
        return false;
    }
    unsigned long long dbRetValueLen = 0;
    unsigned long long paramLen[2][kMaxTaxRateCount] = {{0}};
    if (!tran.Tran->BindParam(1, SQL_PARAM_OUTPUT, &dbRetValue, 0, 0, SQL_INTEGER, SQL_C_SLONG, &dbRetValueLen) ||
        !BindTaxRateParams(tran.Tran, taxRateTable, paramLen))
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 144, FAIL_BIND, MODULE_NAME, fn);
        return false;
    }
    if (!tran.Tran->Execute())
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 134, FAIL_EXECUTE, MODULE_NAME, fn, dbRetValue);
        return false;
    }
    return dbRetValue == 0;
}

// 0x1b820
bool const MarketDB::LoadSaleList(int& dbRetValue)
{
    wchar_t const* const fn = L"MarketDB::LoadSaleList";
    AutoDbTran tran(kDbId);
    if (tran.Tran != nullptr)
    {
        tran.TimeoutSec = 0;
        SQLSetStmtAttrW(tran.Tran->StmtHandle, SQL_QUERY_TIMEOUT, nullptr, 0);
    }
    if (tran.Tran == nullptr)
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 152, FAIL_ACQUIRE, MODULE_NAME, fn, kDbId);
        return false;
    }
    wchar_t const* const query = L"{?=CALL dbo.usp_LoadSaleList}";
    if (!tran.Tran->Prepare(Query(query)))
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 158, FAIL_PREPARE, MODULE_NAME, fn, query);
        return false;
    }

    SaleInfo saleInfo;
    SaleItemInfo itemInfo;
    memset(&itemInfo, 0, sizeof(itemInfo));
    TIMESTAMP_STRUCT expirationTime;
    memset(&expirationTime, 0, sizeof(expirationTime));
    unsigned long long dbRetValueLen = 0;
    unsigned long long saleLen[18] = {0};  // columns 1..18
    unsigned long long expirationTimeLen = 0;
    unsigned long long itemLen[13] = {0};  // columns 20..32
    saleLen[15] = kNts;
    saleLen[7] = kNts;
    saleLen[6] = kNts;
    itemLen[12] = kNts;

    DbTransaction* const t = tran.Tran;
    bool const bound =
        t->BindParam(1, SQL_PARAM_OUTPUT, &dbRetValue, 0, 0, SQL_INTEGER, SQL_C_SLONG, &dbRetValueLen) &&
        t->BindCol(1, &saleInfo._saleId, 0, SQL_C_SBIGINT, &saleLen[0]) &&
        t->BindCol(2, &saleInfo._pawnId, 0, SQL_C_SBIGINT, &saleLen[1]) &&
        t->BindCol(3, &saleInfo._saleType, 0, SQL_C_STINYINT, &saleLen[2]) &&
        t->BindCol(4, &saleInfo._seller._participantWid, 0, SQL_C_SSHORT, &saleLen[3]) &&
        t->BindCol(5, &saleInfo._seller._participantPcId, 0, SQL_C_SBIGINT, &saleLen[4]) &&
        t->BindCol(6, &saleInfo._seller._participantAccountId, 0, SQL_C_GUID, &saleLen[5]) &&
        t->BindCol(7, saleInfo._seller._participantWorldName, 66, SQL_C_WCHAR, &saleLen[6]) &&
        t->BindCol(8, saleInfo._seller._participantName, 66, SQL_C_WCHAR, &saleLen[7]) &&
        t->BindCol(9, &saleInfo._salePrice, 0, SQL_C_SBIGINT, &saleLen[8]) &&
        t->BindCol(10, &saleInfo._unitPrice, 0, SQL_C_SBIGINT, &saleLen[9]) &&
        t->BindCol(11, &saleInfo._bidUnitPrice, 0, SQL_C_SBIGINT, &saleLen[10]) &&
        t->BindCol(12, &saleInfo._topBidId, 0, SQL_C_SBIGINT, &saleLen[11]) &&
        t->BindCol(13, &saleInfo._topBidderPawnId, 0, SQL_C_SBIGINT, &saleLen[12]) &&
        t->BindCol(14, &saleInfo._topBidder._participantWid, 0, SQL_C_SSHORT, &saleLen[13]) &&
        t->BindCol(15, &saleInfo._topBidder._participantPcId, 0, SQL_C_SBIGINT, &saleLen[14]) &&
        t->BindCol(16, saleInfo._topBidder._participantName, 66, SQL_C_WCHAR, &saleLen[15]) &&
        t->BindCol(17, &saleInfo._topBidPrice, 0, SQL_C_SBIGINT, &saleLen[16]) &&
        t->BindCol(18, &saleInfo._saleStatus, 0, SQL_C_STINYINT, &saleLen[17]) &&
        t->BindCol(19, &expirationTime, sizeof(expirationTime), SQL_C_TYPE_TIMESTAMP, &expirationTimeLen) &&
        t->BindCol(20, &itemInfo._itemCommonCategory, 0, SQL_C_STINYINT, &itemLen[0]) &&
        t->BindCol(21, &itemInfo._itemFirstCategory, 0, SQL_C_STINYINT, &itemLen[1]) &&
        t->BindCol(22, &itemInfo._itemSecondCategory, 0, SQL_C_STINYINT, &itemLen[2]) &&
        t->BindCol(23, &itemInfo._itemThirdCategory, 0, SQL_C_STINYINT, &itemLen[3]) &&
        t->BindCol(24, &itemInfo._itemType, 0, SQL_C_STINYINT, &itemLen[4]) &&
        t->BindCol(25, &itemInfo._itemInstanceId, 0, SQL_C_SBIGINT, &itemLen[5]) &&
        t->BindCol(26, &itemInfo._itemDataId, 0, SQL_C_SLONG, &itemLen[6]) &&
        t->BindCol(27, &itemInfo._itemLevel, 0, SQL_C_SSHORT, &itemLen[7]) &&
        t->BindCol(28, &itemInfo._itemExp, 0, SQL_C_SLONG, &itemLen[8]) &&
        t->BindCol(29, &itemInfo._itemAmount, 0, SQL_C_SLONG, &itemLen[9]) &&
        t->BindCol(30, &itemInfo._itemGrade, 0, SQL_C_STINYINT, &itemLen[10]) &&
        t->BindCol(31, &itemInfo._itemEquipLevel, 0, SQL_C_STINYINT, &itemLen[11]) &&
        t->BindCol(32, itemInfo._itemXmlData, 2050, SQL_C_WCHAR, &itemLen[12]);
    if (!bound)
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 275, FAIL_BIND, MODULE_NAME, fn);
        return false;
    }
    if (!t->Execute())
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 213, FAIL_EXECUTE, MODULE_NAME, fn, dbRetValue);
        return false;
    }

    SaleContextManager* const saleContextManager = MarketDealerDaemon::_instance->_saleContextManager;
    SaleTimeContextManager* const saleTimeContextManager = MarketDealerDaemon::_instance->_saleTimeContextManager;
    for (;;)
    {
        memset(&saleInfo, 0, sizeof(saleInfo));
        memset(&itemInfo, 0, sizeof(itemInfo));
        memset(&expirationTime, 0, sizeof(expirationTime));
        int const result = t->Fetch(0);  // LIFT: folded. edx is not set at the call. Fetch does not read it.
        if (result == -1)
        {
            Log::Write(Log::LT_ERROR, MARKETDB_FILE, 230, FAIL_FETCH, MODULE_NAME, fn);
            return false;
        }
        if (result == 0)
            break;

        if (expirationTimeLen != kNullData)
            saleInfo._saleExpirationTime = Db::ConvertTime(&expirationTime);

        bool const hasItem = itemLen[0] != kNullData;
        // A reserving sale has no item yet. A selling sale must have an item.
        if ((saleInfo._saleStatus == SaleInfo::SALESTATUS_RESERVING && hasItem) ||
            (saleInfo._saleStatus == SaleInfo::SALESTATUS_SELLING && !hasItem))
        {
            Log::Write(Log::LT_ERROR, MARKETDB_FILE, 243, L"[%s], %s; invalid sale item data, saleId:0x%I64X",
                       MODULE_NAME, fn, saleInfo._saleId);
            continue;
        }

        SaleContext* saleContext = nullptr;
        if (hasItem)
        {
            void* const memory = Memory::_Manager[2]->Alloc(sizeof(SaleContext), MARKETDB_FILE, 249);
            if (memory != nullptr)
                saleContext = ::new (memory) SaleContext(saleInfo, itemInfo);
        }
        else
        {
            void* const memory = Memory::_Manager[2]->Alloc(sizeof(SaleContext), MARKETDB_FILE, 251);
            if (memory != nullptr)
                saleContext = ::new (memory) SaleContext(saleInfo);
        }
        // BUG: 0x1b820 no null check after the SaleContext Alloc (AddContext and removeReferenceCount get nullptr).
        if (!saleContextManager->AddContext(saleContext))
        {
            Log::Write(Log::LT_ERROR, MARKETDB_FILE, 254,
                       L"== CRASH == [%s], %s; exception occurred; failed to add sale context, saleId:0x%I64X",
                       MODULE_NAME, fn, saleInfo._saleId);
            AlertSender::Write(MARKETDB_FILE, 254,
                               L"== CRASH == [%s], %s; exception occurred; failed to add sale context, saleId:0x%I64X",
                               MODULE_NAME, fn, saleInfo._saleId);
            saleContext->removeReferenceCount(MARKETDB_FILE, 255);
            continue;
        }
        saleContext->removeReferenceCount(MARKETDB_FILE, 258);
        if (saleInfo._saleStatus == SaleInfo::SALESTATUS_SELLING &&
            !saleTimeContextManager->AddContext(saleInfo._saleId, saleInfo._saleExpirationTime, saleInfo._saleType,
                                                saleContext))
        {
            Log::Write(Log::LT_ERROR, MARKETDB_FILE, 263,
                       L"== CRASH == [%s], %s; exception occurred; failed to add saletime context, saleId:0x%I64X",
                       MODULE_NAME, fn, saleInfo._saleId);
            AlertSender::Write(MARKETDB_FILE, 263,
                               L"== CRASH == [%s], %s; exception occurred; failed to add saletime context, saleId:0x%I64X",
                               MODULE_NAME, fn, saleInfo._saleId);
        }
    }
    return dbRetValue == 0;
}

// 0x1cf40
bool const MarketDB::LoadBidList(int& dbRetValue)
{
    wchar_t const* const fn = L"MarketDB::LoadBidList";
    AutoDbTran tran(kDbId);
    if (tran.Tran != nullptr)
    {
        tran.TimeoutSec = 0;
        SQLSetStmtAttrW(tran.Tran->StmtHandle, SQL_QUERY_TIMEOUT, nullptr, 0);
    }
    if (tran.Tran == nullptr)
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 283, FAIL_ACQUIRE, MODULE_NAME, fn, kDbId);
        return false;
    }
    wchar_t const* const query = L"{?=CALL dbo.usp_LoadBidList}";
    if (!tran.Tran->Prepare(Query(query)))
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 289, FAIL_PREPARE, MODULE_NAME, fn, query);
        return false;
    }

    long long saleId = 0;
    BidInfo bidInfo;
    memset(&bidInfo, 0, sizeof(bidInfo));
    unsigned long long dbRetValueLen = 0;
    unsigned long long saleIdLen = 0;
    unsigned long long bidLen[9] = {0};  // columns 2..10
    bidLen[6] = kNts;
    bidLen[5] = kNts;

    DbTransaction* const t = tran.Tran;
    Participant& trader = bidInfo._dealingInfo._trader;
    bool const bound =
        t->BindParam(1, SQL_PARAM_OUTPUT, &dbRetValue, 0, 0, SQL_INTEGER, SQL_C_SLONG, &dbRetValueLen) &&
        t->BindCol(1, &saleId, 0, SQL_C_SBIGINT, &saleIdLen) &&
        t->BindCol(2, &bidInfo._dealingInfo._dealingId, 0, SQL_C_SBIGINT, &bidLen[0]) &&
        t->BindCol(3, &bidInfo._dealingInfo._pawnId, 0, SQL_C_SBIGINT, &bidLen[1]) &&
        t->BindCol(4, &trader._participantWid, 0, SQL_C_SSHORT, &bidLen[2]) &&
        t->BindCol(5, &trader._participantPcId, 0, SQL_C_SBIGINT, &bidLen[3]) &&
        t->BindCol(6, &trader._participantAccountId, 0, SQL_C_GUID, &bidLen[4]) &&
        t->BindCol(7, trader._participantWorldName, 66, SQL_C_WCHAR, &bidLen[5]) &&
        t->BindCol(8, trader._participantName, 66, SQL_C_WCHAR, &bidLen[6]) &&
        t->BindCol(9, &bidInfo._dealingInfo._dealingPrice, 0, SQL_C_SBIGINT, &bidLen[7]) &&
        t->BindCol(10, &bidInfo._bidStatus, 0, SQL_C_STINYINT, &bidLen[8]);
    if (!bound)
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 383, FAIL_BIND, MODULE_NAME, fn);
        return false;
    }
    if (!t->Execute())
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 318, FAIL_EXECUTE, MODULE_NAME, fn, dbRetValue);
        return false;
    }

    SaleContextManager* const saleContextManager = MarketDealerDaemon::_instance->_saleContextManager;
    for (;;)
    {
        saleId = 0;
        memset(&bidInfo, 0, sizeof(bidInfo));
        int const result = t->Fetch(0);  // LIFT: folded. edx is not set at the call. Fetch does not read it.
        if (result == -1)
        {
            Log::Write(Log::LT_ERROR, MARKETDB_FILE, 333, FAIL_FETCH, MODULE_NAME, fn);
            return false;
        }
        if (result == 0)
            break;

        long long const bidId = bidInfo._dealingInfo._dealingId;
        SaleContext* const saleContext = saleContextManager->GetContext(saleId);
        if (saleContext == nullptr)
        {
            Log::Write(Log::LT_ERROR, MARKETDB_FILE, 341,
                       L"[%s], %s; there is no such sale context, saleId:0x%I64X, bidId:0x%I64X", MODULE_NAME, fn,
                       saleId, bidId);
            continue;
        }
        if (saleContext->_saleInfo._saleStatus != SaleInfo::SALESTATUS_SELLING)
        {
            Log::Write(Log::LT_ERROR, MARKETDB_FILE, 346,
                       L"[%s], %s; sale status is not selling, saleId:0x%I64X, bidId:0x%I64X", MODULE_NAME, fn,
                       saleId, bidId);
            saleContext->removeReferenceCount(MARKETDB_FILE, 347);
            continue;
        }
        if (saleContext->_saleInfo._saleType != kSaleTypeAuction)
        {
            Log::Write(Log::LT_ERROR, MARKETDB_FILE, 352,
                       L"[%s], %s; sale type is not auction, saleId:0x%I64X, bidId:0x%I64X", MODULE_NAME, fn,
                       saleId, bidId);
            saleContext->removeReferenceCount(MARKETDB_FILE, 353);
            continue;
        }
        if (!saleContext->AddBidContext(bidInfo))
        {
            Log::Write(Log::LT_ERROR, MARKETDB_FILE, 358,
                       L"== CRASH == [%s], %s; exception occurred; failed to add bid context, saleId:0x%I64X, "
                       L"bidId:0x%I64X",
                       MODULE_NAME, fn, saleId, bidId);
            AlertSender::Write(MARKETDB_FILE, 358,
                               L"== CRASH == [%s], %s; exception occurred; failed to add bid context, "
                               L"saleId:0x%I64X, bidId:0x%I64X",
                               MODULE_NAME, fn, saleId, bidId);
            saleContext->removeReferenceCount(MARKETDB_FILE, 359);
            continue;
        }
        if (bidInfo._bidStatus == BidInfo::BIDSTATUS_BIDDING)
            ++saleContext->_bidCount;
        saleContext->removeReferenceCount(MARKETDB_FILE, 374);
    }
    return dbRetValue == 0;
}

// 0x1d9b0
bool const MarketDB::LoadPurchaseList(int& dbRetValue)
{
    wchar_t const* const fn = L"MarketDB::LoadPurchaseList";
    AutoDbTran tran(kDbId);
    if (tran.Tran != nullptr)
    {
        tran.TimeoutSec = 0;
        SQLSetStmtAttrW(tran.Tran->StmtHandle, SQL_QUERY_TIMEOUT, nullptr, 0);
    }
    if (tran.Tran == nullptr)
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 391, FAIL_ACQUIRE, MODULE_NAME, fn, kDbId);
        return false;
    }
    wchar_t const* const query = L"{?=CALL dbo.usp_LoadPurchaseList}";
    if (!tran.Tran->Prepare(Query(query)))
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 397, FAIL_PREPARE, MODULE_NAME, fn, query);
        return false;
    }

    long long saleId = 0;
    PurchaseInfo purchaseInfo;
    memset(&purchaseInfo, 0, sizeof(purchaseInfo));
    unsigned long long dbRetValueLen = 0;
    unsigned long long saleIdLen = 0;
    unsigned long long purchaseLen[9] = {0};  // columns 2..10
    purchaseLen[6] = kNts;
    purchaseLen[5] = kNts;

    DbTransaction* const t = tran.Tran;
    Participant& trader = purchaseInfo._dealingInfo._trader;
    bool const bound =
        t->BindParam(1, SQL_PARAM_OUTPUT, &dbRetValue, 0, 0, SQL_INTEGER, SQL_C_SLONG, &dbRetValueLen) &&
        t->BindCol(1, &saleId, 0, SQL_C_SBIGINT, &saleIdLen) &&
        t->BindCol(2, &purchaseInfo._dealingInfo._dealingId, 0, SQL_C_SBIGINT, &purchaseLen[0]) &&
        t->BindCol(3, &purchaseInfo._dealingInfo._pawnId, 0, SQL_C_SBIGINT, &purchaseLen[1]) &&
        t->BindCol(4, &trader._participantWid, 0, SQL_C_SSHORT, &purchaseLen[2]) &&
        t->BindCol(5, &trader._participantPcId, 0, SQL_C_SBIGINT, &purchaseLen[3]) &&
        t->BindCol(6, &trader._participantAccountId, 0, SQL_C_GUID, &purchaseLen[4]) &&
        t->BindCol(7, trader._participantWorldName, 66, SQL_C_WCHAR, &purchaseLen[5]) &&
        t->BindCol(8, trader._participantName, 66, SQL_C_WCHAR, &purchaseLen[6]) &&
        t->BindCol(9, &purchaseInfo._dealingInfo._dealingPrice, 0, SQL_C_SBIGINT, &purchaseLen[7]) &&
        t->BindCol(10, &purchaseInfo._purchaseStatus, 0, SQL_C_STINYINT, &purchaseLen[8]);
    if (!bound)
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 480, FAIL_BIND, MODULE_NAME, fn);
        return false;
    }
    if (!t->Execute())
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 426, FAIL_EXECUTE, MODULE_NAME, fn, dbRetValue);
        return false;
    }

    SaleContextManager* const saleContextManager = MarketDealerDaemon::_instance->_saleContextManager;
    for (;;)
    {
        saleId = 0;
        memset(&purchaseInfo, 0, sizeof(purchaseInfo));
        int const result = t->Fetch(0);  // LIFT: folded. edx is not set at the call. Fetch does not read it.
        if (result == -1)
        {
            Log::Write(Log::LT_ERROR, MARKETDB_FILE, 441, FAIL_FETCH, MODULE_NAME, fn);
            return false;
        }
        if (result == 0)
            break;

        long long const purchaseId = purchaseInfo._dealingInfo._dealingId;
        SaleContext* const saleContext = saleContextManager->GetContext(saleId);
        if (saleContext == nullptr)
        {
            Log::Write(Log::LT_ERROR, MARKETDB_FILE, 449,
                       L"[%s], %s; there is no such sale context, saleId:0x%I64X, purchaseId:0x%I64X", MODULE_NAME,
                       fn, saleId, purchaseId);
            continue;
        }
        if (saleContext->_saleInfo._saleStatus != SaleInfo::SALESTATUS_SELLING)
        {
            Log::Write(Log::LT_ERROR, MARKETDB_FILE, 454,
                       L"[%s], %s; sale status is not selling, saleId:0x%I64X, purchaseId:0x%I64X", MODULE_NAME, fn,
                       saleId, purchaseId);
            saleContext->removeReferenceCount(MARKETDB_FILE, 455);
            continue;
        }
        if (saleContext->_saleInfo._saleType != kSaleTypeInstantSale)
        {
            Log::Write(Log::LT_ERROR, MARKETDB_FILE, 460,
                       L"[%s], %s; sale type is not instant sale, saleId:0x%I64X, purchaseId:0x%I64X", MODULE_NAME,
                       fn, saleId, purchaseId);
            saleContext->removeReferenceCount(MARKETDB_FILE, 461);
            continue;
        }
        if (!saleContext->AddPurchaseContext(purchaseInfo))
        {
            Log::Write(Log::LT_ERROR, MARKETDB_FILE, 466,
                       L"== CRASH == [%s], %s; exception occurred; failed to add purchase context, saleId:0x%I64X, "
                       L"purchaseId:0x%I64X",
                       MODULE_NAME, fn, saleId, purchaseId);
            AlertSender::Write(MARKETDB_FILE, 466,
                               L"== CRASH == [%s], %s; exception occurred; failed to add purchase context, "
                               L"saleId:0x%I64X, purchaseId:0x%I64X",
                               MODULE_NAME, fn, saleId, purchaseId);
            saleContext->removeReferenceCount(MARKETDB_FILE, 467);
            continue;
        }
        saleContext->removeReferenceCount(MARKETDB_FILE, 471);
    }
    return dbRetValue == 0;
}

// 0x1e400
bool const MarketDB::LoadDeliveryList(int& dbRetValue)
{
    wchar_t const* const fn = L"MarketDB::LoadDeliveryList";
    AutoDbTran tran(kDbId);
    if (tran.Tran != nullptr)
    {
        tran.TimeoutSec = 0;
        SQLSetStmtAttrW(tran.Tran->StmtHandle, SQL_QUERY_TIMEOUT, nullptr, 0);
    }
    if (tran.Tran == nullptr)
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 488, FAIL_ACQUIRE, MODULE_NAME, fn, kDbId);
        return false;
    }
    wchar_t const* const query = L"{?=CALL dbo.usp_LoadDeliveryList}";
    if (!tran.Tran->Prepare(Query(query)))
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 494, FAIL_PREPARE, MODULE_NAME, fn, query);
        return false;
    }

    DeliveryInfo deliveryInfo;
    SaleItemInfo itemInfo;
    memset(&itemInfo, 0, sizeof(itemInfo));
    long long moneyAmount = 0;
    unsigned long long dbRetValueLen = 0;
    unsigned long long deliveryLen[15] = {0};  // columns 1..15
    unsigned long long itemLen[13] = {0};      // columns 16..28
    deliveryLen[12] = kNts;
    deliveryLen[11] = kNts;
    deliveryLen[10] = kNts;
    deliveryLen[7] = kNts;
    itemLen[12] = kNts;

    DbTransaction* const t = tran.Tran;
    bool const bound =
        t->BindParam(1, SQL_PARAM_OUTPUT, &dbRetValue, 0, 0, SQL_INTEGER, SQL_C_SLONG, &dbRetValueLen) &&
        t->BindCol(1, &deliveryInfo._deliveryId, 0, SQL_C_SBIGINT, &deliveryLen[0]) &&
        t->BindCol(2, &deliveryInfo._deliveryReason, 0, SQL_C_STINYINT, &deliveryLen[1]) &&
        t->BindCol(3, &deliveryInfo._saleId, 0, SQL_C_SBIGINT, &deliveryLen[2]) &&
        t->BindCol(4, &deliveryInfo._pawnId, 0, SQL_C_SBIGINT, &deliveryLen[3]) &&
        t->BindCol(5, &deliveryInfo._pawnServiceId, 0, SQL_C_SBIGINT, &deliveryLen[4]) &&
        t->BindCol(6, &deliveryInfo._pawnOwner._participantWid, 0, SQL_C_SSHORT, &deliveryLen[5]) &&
        t->BindCol(7, &deliveryInfo._pawnOwner._participantPcId, 0, SQL_C_SBIGINT, &deliveryLen[6]) &&
        t->BindCol(8, deliveryInfo._pawnOwner._participantName, 66, SQL_C_WCHAR, &deliveryLen[7]) &&
        t->BindCol(9, &deliveryInfo._recipient._participantWid, 0, SQL_C_SSHORT, &deliveryLen[8]) &&
        t->BindCol(10, &deliveryInfo._recipient._participantPcId, 0, SQL_C_SBIGINT, &deliveryLen[9]) &&
        t->BindCol(11, deliveryInfo._recipient._participantName, 66, SQL_C_WCHAR, &deliveryLen[10]) &&
        t->BindCol(12, deliveryInfo._marketStatement._statementTitle, 130, SQL_C_WCHAR, &deliveryLen[11]) &&
        t->BindCol(13, deliveryInfo._marketStatement._statementBody, 2050, SQL_C_WCHAR, &deliveryLen[12]) &&
        t->BindCol(14, &deliveryInfo._jobStatus, 0, SQL_C_STINYINT, &deliveryLen[13]) &&
        t->BindCol(15, &moneyAmount, 0, SQL_C_SBIGINT, &deliveryLen[14]) &&
        t->BindCol(16, &itemInfo._itemCommonCategory, 0, SQL_C_STINYINT, &itemLen[0]) &&
        t->BindCol(17, &itemInfo._itemFirstCategory, 0, SQL_C_STINYINT, &itemLen[1]) &&
        t->BindCol(18, &itemInfo._itemSecondCategory, 0, SQL_C_STINYINT, &itemLen[2]) &&
        t->BindCol(19, &itemInfo._itemThirdCategory, 0, SQL_C_STINYINT, &itemLen[3]) &&
        t->BindCol(20, &itemInfo._itemType, 0, SQL_C_STINYINT, &itemLen[4]) &&
        t->BindCol(21, &itemInfo._itemInstanceId, 0, SQL_C_SBIGINT, &itemLen[5]) &&
        t->BindCol(22, &itemInfo._itemDataId, 0, SQL_C_SLONG, &itemLen[6]) &&
        t->BindCol(23, &itemInfo._itemLevel, 0, SQL_C_SSHORT, &itemLen[7]) &&
        t->BindCol(24, &itemInfo._itemExp, 0, SQL_C_SLONG, &itemLen[8]) &&
        t->BindCol(25, &itemInfo._itemAmount, 0, SQL_C_SLONG, &itemLen[9]) &&
        t->BindCol(26, &itemInfo._itemGrade, 0, SQL_C_STINYINT, &itemLen[10]) &&
        t->BindCol(27, &itemInfo._itemEquipLevel, 0, SQL_C_STINYINT, &itemLen[11]) &&
        t->BindCol(28, itemInfo._itemXmlData, 2050, SQL_C_WCHAR, &itemLen[12]);
    if (!bound)
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 595, FAIL_BIND, MODULE_NAME, fn);
        return false;
    }
    if (!t->Execute())
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 544, FAIL_EXECUTE, MODULE_NAME, fn, dbRetValue);
        return false;
    }

    DeliveryContextManager* const deliveryContextManager = MarketDealerDaemon::_instance->_deliveryContextManager;
    for (;;)
    {
        memset(&deliveryInfo, 0, sizeof(deliveryInfo));
        memset(&itemInfo, 0, sizeof(itemInfo));
        moneyAmount = 0;
        int const result = t->Fetch(0);  // LIFT: folded. edx is not set at the call. Fetch does not read it.
        if (result == -1)
        {
            Log::Write(Log::LT_ERROR, MARKETDB_FILE, 560, FAIL_FETCH, MODULE_NAME, fn);
            return false;
        }
        if (result == 0)
            break;

        bool const existItem = itemLen[0] != kNullData;
        // A delivery has an item or money, not both and not neither.
        if ((!existItem && moneyAmount == 0) || (existItem && moneyAmount > 0))
        {
            Log::Write(Log::LT_ERROR, MARKETDB_FILE, 570,
                       L"[%s], %s; invalid delivery item, deliveryId:0x%I64X, saleId:0x%I64X, existItem:%d, "
                       L"moneyAmount:%I64d",
                       MODULE_NAME, fn, deliveryInfo._deliveryId, deliveryInfo._saleId, static_cast<int>(existItem),
                       moneyAmount);
            continue;
        }

        DeliveryContext* deliveryContext = nullptr;
        if (existItem)
        {
            void* const memory = Memory::_Manager[2]->Alloc(sizeof(DeliveryContext), MARKETDB_FILE, 576);
            if (memory != nullptr)
                deliveryContext = ::new (memory) DeliveryContext(deliveryInfo, itemInfo);
        }
        else
        {
            void* const memory = Memory::_Manager[2]->Alloc(sizeof(DeliveryContext), MARKETDB_FILE, 578);
            if (memory != nullptr)
                deliveryContext = ::new (memory) DeliveryContext(deliveryInfo, moneyAmount);
        }
        // BUG: 0x1e400 no null check after the DeliveryContext Alloc (AddContext and the log read nullptr).
        if (!deliveryContextManager->AddContext(deliveryContext))
        {
            Log::Write(Log::LT_ERROR, MARKETDB_FILE, 581,
                       L"== CRASH == [%s], %s; exception occurred; failed to add delivery context, "
                       L"deliveryId:0x%I64X, saleId:0x%I64X",
                       MODULE_NAME, fn, deliveryContext->_deliveryInfo._deliveryId,
                       deliveryContext->_deliveryInfo._saleId);
            AlertSender::Write(MARKETDB_FILE, 581,
                               L"== CRASH == [%s], %s; exception occurred; failed to add delivery context, "
                               L"deliveryId:0x%I64X, saleId:0x%I64X",
                               MODULE_NAME, fn, deliveryContext->_deliveryInfo._deliveryId,
                               deliveryContext->_deliveryInfo._saleId);
            deliveryContext->removeReferenceCount(MARKETDB_FILE, 582);
            continue;
        }
        deliveryContext->removeReferenceCount(MARKETDB_FILE, 586);
    }
    return dbRetValue == 0;
}
