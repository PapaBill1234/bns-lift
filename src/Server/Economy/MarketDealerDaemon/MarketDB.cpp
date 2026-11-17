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
#include "DeliveryRelation.h"
#include "MarketStatement.h"
#include "TaxRateDataManager.h"
#include "MarketDealerDaemon.h"
#include "JobContext.h"
#include "ManagementJobContext.h"
#include <wchar.h>

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

// Card lift-marketdealerdaemon-5: sale, bid and purchase jobs (0x1f840..0x23b40).

// 0x1f840
bool const MarketDB::RetrieveSaleList(int& dbRetValue, RetrieveSaleListJob& job)
{
    wchar_t const* const fn = L"MarketDB::RetrieveSaleList";
    AutoDbTran tran(kDbId);
    if (tran.Tran == nullptr)
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 603, FAIL_ACQUIRE, MODULE_NAME, fn, kDbId);
        return false;
    }
    wchar_t const* const query = L"{?=CALL dbo.usp_RetrieveSaleList(?,?,?,?,?)}";
    if (!tran.Tran->Prepare(Query(query)))
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 609, FAIL_PREPARE, MODULE_NAME, fn, query);
        return false;
    }

    MySaleInfo mySaleInfo;
    memset(&mySaleInfo._saleItemInfo, 0, sizeof(mySaleInfo._saleItemInfo));
    TIMESTAMP_STRUCT expirationTime;
    memset(&expirationTime, 0, sizeof(expirationTime));
    unsigned long long paramLen[RetrieveSaleListJob::MAX_PARAM_COUNT] = {0};
    unsigned long long mySaleLen[MySaleInfo::MAX_COLUMN_COUNT] = {0};
    unsigned long long itemLen[13] = {0};  // same slots as in LoadSaleList
    itemLen[12] = kNts;

    DbTransaction* const t = tran.Tran;
    SaleInfo& saleInfo = mySaleInfo._saleInfo;
    SaleItemInfo& itemInfo = mySaleInfo._saleItemInfo;
    bool const bound =
        t->BindParam(1, SQL_PARAM_OUTPUT, &dbRetValue, 0, 0, SQL_INTEGER, SQL_C_SLONG, &paramLen[0]) &&
        t->BindParam(2, SQL_PARAM_INPUT, &job._sellerPcId, 0, 0, SQL_BIGINT, SQL_C_SBIGINT, &paramLen[1]) &&
        t->BindParam(3, SQL_PARAM_INPUT, &job._searchCount, 0, 0, SQL_INTEGER, SQL_C_SLONG, &paramLen[2]) &&
        t->BindParam(4, SQL_PARAM_INPUT, &job._searchType, 0, 0, SQL_TINYINT, SQL_C_STINYINT, &paramLen[3]) &&
        t->BindParam(5, SQL_PARAM_INPUT, &job._orderType, 0, 0, SQL_TINYINT, SQL_C_STINYINT, &paramLen[4]) &&
        t->BindParam(6, SQL_PARAM_INPUT, &job._searchKey, 0, 0, SQL_BIGINT, SQL_C_SBIGINT, &paramLen[5]) &&
        t->BindCol(1, &saleInfo._saleId, 0, SQL_C_SBIGINT, &mySaleLen[0]) &&
        t->BindCol(2, &saleInfo._saleType, 0, SQL_C_STINYINT, &mySaleLen[1]) &&
        t->BindCol(3, &saleInfo._salePrice, 0, SQL_C_SBIGINT, &mySaleLen[2]) &&
        t->BindCol(4, &saleInfo._unitPrice, 0, SQL_C_SBIGINT, &mySaleLen[3]) &&
        t->BindCol(5, &saleInfo._topBidPrice, 0, SQL_C_SBIGINT, &mySaleLen[4]) &&
        t->BindCol(6, &expirationTime, sizeof(expirationTime), SQL_C_TYPE_TIMESTAMP, &mySaleLen[5]) &&
        t->BindCol(7, &itemInfo._itemType, 0, SQL_C_STINYINT, &itemLen[4]) &&
        t->BindCol(8, &itemInfo._itemDataId, 0, SQL_C_SLONG, &itemLen[6]) &&
        t->BindCol(9, &itemInfo._itemLevel, 0, SQL_C_SSHORT, &itemLen[7]) &&
        t->BindCol(10, &itemInfo._itemExp, 0, SQL_C_SLONG, &itemLen[8]) &&
        t->BindCol(11, &itemInfo._itemAmount, 0, SQL_C_SLONG, &itemLen[9]) &&
        t->BindCol(12, itemInfo._itemXmlData, 2050, SQL_C_WCHAR, &itemLen[12]);
    if (!bound)
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 679, FAIL_BIND, MODULE_NAME, fn);
        return false;
    }
    if (!t->Execute())
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 648, FAIL_EXECUTE, MODULE_NAME, fn, dbRetValue);
        return false;
    }
    do
    {
        memset(&mySaleInfo, 0, sizeof(mySaleInfo));
        memset(&expirationTime, 0, sizeof(expirationTime));
        int const result = t->Fetch(0);  // LIFT: folded. edx is not set at the call. Fetch does not read it.
        if (result == -1)
        {
            Log::Write(Log::LT_ERROR, MARKETDB_FILE, 661, FAIL_FETCH, MODULE_NAME, fn);
            return false;
        }
        if (result == 0)
            break;
        saleInfo._saleExpirationTime = Db::ConvertTime(&expirationTime);
    } while (job.addMySaleInfo(mySaleInfo));
    return dbRetValue == 0;
}

// 0x20000
bool const MarketDB::RetrieveBidList(int& dbRetValue, RetrieveBidListJob& job)
{
    wchar_t const* const fn = L"MarketDB::RetrieveBidList";
    AutoDbTran tran(kDbId);
    if (tran.Tran == nullptr)
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 687, FAIL_ACQUIRE, MODULE_NAME, fn, kDbId);
        return false;
    }
    wchar_t const* const query = L"{?=CALL dbo.usp_RetrieveBidList(?)}";
    if (!tran.Tran->Prepare(Query(query)))
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 693, FAIL_PREPARE, MODULE_NAME, fn, query);
        return false;
    }

    MyBidInfo myBidInfo;
    myBidInfo._bidId = 0;
    myBidInfo._bidPrice = 0;
    memset(&myBidInfo._saleItemInfo, 0, sizeof(myBidInfo._saleItemInfo));
    TIMESTAMP_STRUCT expirationTime;
    memset(&expirationTime, 0, sizeof(expirationTime));
    unsigned long long paramLen[RetrieveBidListJob::MAX_PARAM_COUNT] = {0};
    unsigned long long myBidLen[MyBidInfo::MAX_COLUMN_COUNT] = {0};
    unsigned long long itemLen[13] = {0};  // same slots as in LoadSaleList
    myBidLen[4] = kNts;
    itemLen[12] = kNts;

    DbTransaction* const t = tran.Tran;
    SaleInfo& saleInfo = myBidInfo._saleInfo;
    SaleItemInfo& itemInfo = myBidInfo._saleItemInfo;
    bool const bound =
        t->BindParam(1, SQL_PARAM_OUTPUT, &dbRetValue, 0, 0, SQL_INTEGER, SQL_C_SLONG, &paramLen[0]) &&
        t->BindParam(2, SQL_PARAM_INPUT, &job._bidderPcId, 0, 0, SQL_BIGINT, SQL_C_SBIGINT, &paramLen[1]) &&
        t->BindCol(1, &myBidInfo._bidId, 0, SQL_C_SBIGINT, &myBidLen[0]) &&
        t->BindCol(2, &saleInfo._saleId, 0, SQL_C_SBIGINT, &myBidLen[1]) &&
        t->BindCol(3, &myBidInfo._bidPrice, 0, SQL_C_SBIGINT, &myBidLen[2]) &&
        t->BindCol(4, &saleInfo._seller._participantWid, 0, SQL_C_SSHORT, &myBidLen[3]) &&
        t->BindCol(5, saleInfo._seller._participantName, 66, SQL_C_WCHAR, &myBidLen[4]) &&
        t->BindCol(6, &saleInfo._bidUnitPrice, 0, SQL_C_SBIGINT, &myBidLen[5]) &&
        t->BindCol(7, &saleInfo._topBidPrice, 0, SQL_C_SBIGINT, &myBidLen[6]) &&
        t->BindCol(8, &expirationTime, sizeof(expirationTime), SQL_C_TYPE_TIMESTAMP, &myBidLen[7]) &&
        t->BindCol(9, &itemInfo._itemType, 0, SQL_C_STINYINT, &itemLen[4]) &&
        t->BindCol(10, &itemInfo._itemDataId, 0, SQL_C_SLONG, &itemLen[6]) &&
        t->BindCol(11, &itemInfo._itemLevel, 0, SQL_C_SSHORT, &itemLen[7]) &&
        t->BindCol(12, &itemInfo._itemExp, 0, SQL_C_SLONG, &itemLen[8]) &&
        t->BindCol(13, &itemInfo._itemAmount, 0, SQL_C_SLONG, &itemLen[9]) &&
        t->BindCol(14, itemInfo._itemXmlData, 2050, SQL_C_WCHAR, &itemLen[12]);
    if (!bound)
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 762, FAIL_BIND, MODULE_NAME, fn);
        return false;
    }
    if (!t->Execute())
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 731, FAIL_EXECUTE, MODULE_NAME, fn, dbRetValue);
        return false;
    }
    do
    {
        memset(&myBidInfo, 0, sizeof(myBidInfo));
        memset(&expirationTime, 0, sizeof(expirationTime));
        int const result = t->Fetch(0);  // LIFT: folded. edx is not set at the call. Fetch does not read it.
        if (result == -1)
        {
            Log::Write(Log::LT_ERROR, MARKETDB_FILE, 744, FAIL_FETCH, MODULE_NAME, fn);
            return false;
        }
        if (result == 0)
            break;
        saleInfo._saleExpirationTime = Db::ConvertTime(&expirationTime);
    } while (job.addMyBidInfo(myBidInfo));
    return dbRetValue == 0;
}

// 0x20760
bool const MarketDB::RetrieveReservationList(int& dbRetValue, RetrieveReservationListJob& job)
{
    wchar_t const* const fn = L"MarketDB::RetrieveReservationList";
    AutoDbTran tran(kDbId);
    if (tran.Tran == nullptr)
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 770, FAIL_ACQUIRE, MODULE_NAME, fn, kDbId);
        return false;
    }
    wchar_t const* const query = L"{?=CALL dbo.usp_RetrieveReservationList(?)}";
    if (!tran.Tran->Prepare(Query(query)))
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 776, FAIL_PREPARE, MODULE_NAME, fn, query);
        return false;
    }

    MyReservationInfo myReservationInfo;
    myReservationInfo._serviceType = 0;
    myReservationInfo._saleId = 0;
    myReservationInfo._serviceId = 0;
    unsigned long long paramLen[RetrieveReservationListJob::MAX_PARAM_COUNT] = {0};
    unsigned long long columnLen[MyReservationInfo::MAX_COLUMN_COUNT] = {0};

    DbTransaction* const t = tran.Tran;
    bool const bound =
        t->BindParam(1, SQL_PARAM_OUTPUT, &dbRetValue, 0, 0, SQL_INTEGER, SQL_C_SLONG, &paramLen[0]) &&
        t->BindParam(2, SQL_PARAM_INPUT, &job._pcId, 0, 0, SQL_BIGINT, SQL_C_SBIGINT, &paramLen[1]) &&
        t->BindCol(1, &myReservationInfo._serviceType, 0, SQL_C_STINYINT, &columnLen[0]) &&
        t->BindCol(2, &myReservationInfo._saleId, 0, SQL_C_SBIGINT, &columnLen[1]) &&
        t->BindCol(3, &myReservationInfo._serviceId, 0, SQL_C_SBIGINT, &columnLen[2]);
    if (!bound)
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 824, FAIL_BIND, MODULE_NAME, fn);
        return false;
    }
    if (!t->Execute())
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 796, FAIL_EXECUTE, MODULE_NAME, fn, dbRetValue);
        return false;
    }
    for (;;)
    {
        memset(&myReservationInfo, 0, sizeof(myReservationInfo));
        int const result = t->Fetch(0);  // LIFT: folded. edx is not set at the call. Fetch does not read it.
        if (result == -1)
        {
            Log::Write(Log::LT_ERROR, MARKETDB_FILE, 808, FAIL_FETCH, MODULE_NAME, fn);
            return false;
        }
        if (result == 0)
            break;
        job.addMyReservationInfo(myReservationInfo);  // The return value is not used.
    }
    return dbRetValue == 0;
}

// 0x20b90
bool const MarketDB::ReserveSale(int& dbRetValue, ReserveSaleJob& job)
{
    wchar_t const* const fn = L"MarketDB::ReserveSale";
    AutoDbTran tran(kDbId);
    if (tran.Tran == nullptr)
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 832, FAIL_ACQUIRE, MODULE_NAME, fn, kDbId);
        return false;
    }
    wchar_t const* const query = L"{?=CALL dbo.usp_ReserveSale(?,?,?,?,?,?,?,?,?,?,?,?,?)}";
    if (!tran.Tran->Prepare(Query(query)))
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 838, FAIL_PREPARE, MODULE_NAME, fn, query);
        return false;
    }

    unsigned long long paramLen[ReserveSaleJob::MAX_PARAM_COUNT] = {0};
    paramLen[ReserveSaleJob::PARAM_SELLER_NAME] = kNts;
    paramLen[ReserveSaleJob::PARAM_SELLER_WORLD_NAME] = kNts;
    // Only an auction has a bid unit price.
    if (job._saleInfo._saleType != kSaleTypeAuction)
        paramLen[ReserveSaleJob::PARAM_BID_UNIT_PRICE] = kNullData;

    DbTransaction* const t = tran.Tran;
    SaleInfo& saleInfo = job._saleInfo;
    Participant& seller = saleInfo._seller;
    bool const bound =
        t->BindParam(1, SQL_PARAM_OUTPUT, &dbRetValue, 0, 0, SQL_INTEGER, SQL_C_SLONG, &paramLen[0]) &&
        t->BindParam(2, SQL_PARAM_INPUT, &job._concurrentSaleCount, 0, 0, SQL_INTEGER, SQL_C_SLONG, &paramLen[1]) &&
        t->BindParam(3, SQL_PARAM_INPUT, &job._accumulatedSaleCount, 0, 0, SQL_INTEGER, SQL_C_SLONG, &paramLen[2]) &&
        t->BindParam(4, SQL_PARAM_INPUT, &job._ruleResetTime, 0, 0, SQL_INTEGER, SQL_C_SLONG, &paramLen[3]) &&
        t->BindParam(5, SQL_PARAM_INPUT, &saleInfo._saleType, 0, 0, SQL_TINYINT, SQL_C_STINYINT, &paramLen[4]) &&
        t->BindParam(6, SQL_PARAM_INPUT, &seller._participantWid, 0, 0, SQL_SMALLINT, SQL_C_SSHORT, &paramLen[5]) &&
        t->BindParam(7, SQL_PARAM_INPUT, &seller._participantPcId, 0, 0, SQL_BIGINT, SQL_C_SBIGINT, &paramLen[6]) &&
        t->BindParam(8, SQL_PARAM_INPUT, &seller._participantAccountId, 0, 0, SQL_GUID, SQL_C_GUID, &paramLen[7]) &&
        t->BindParam(9, SQL_PARAM_INPUT, seller._participantWorldName, 66, 32, SQL_WVARCHAR, SQL_C_WCHAR,
                     &paramLen[8]) &&
        t->BindParam(10, SQL_PARAM_INPUT, seller._participantName, 66, 32, SQL_WVARCHAR, SQL_C_WCHAR, &paramLen[9]) &&
        t->BindParam(11, SQL_PARAM_INPUT, &saleInfo._salePrice, 0, 0, SQL_BIGINT, SQL_C_SBIGINT, &paramLen[10]) &&
        t->BindParam(12, SQL_PARAM_INPUT, &saleInfo._unitPrice, 0, 0, SQL_BIGINT, SQL_C_SBIGINT, &paramLen[11]) &&
        t->BindParam(13, SQL_PARAM_INPUT, &saleInfo._bidUnitPrice, 0, 0, SQL_BIGINT, SQL_C_SBIGINT, &paramLen[12]) &&
        t->BindParam(14, SQL_PARAM_OUTPUT, &saleInfo._saleId, 0, 0, SQL_BIGINT, SQL_C_SBIGINT, &paramLen[13]);
    if (!bound)
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 879, FAIL_BIND, MODULE_NAME, fn);
        return false;
    }
    if (!t->Execute())
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 869, FAIL_EXECUTE, MODULE_NAME, fn, dbRetValue);
        return false;
    }
    return dbRetValue == 0;
}

// 0x21150
bool const MarketDB::CancelSaleReservation(int& dbRetValue, CancelSaleReservationJob& job)
{
    wchar_t const* const fn = L"MarketDB::CancelSaleReservation";
    AutoDbTran tran(kDbId);
    if (tran.Tran == nullptr)
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 887, FAIL_ACQUIRE, MODULE_NAME, fn, kDbId);
        return false;
    }
    wchar_t const* const query = L"{?=CALL dbo.usp_CancelSaleReservation(?,?)}";
    if (!tran.Tran->Prepare(Query(query)))
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 893, FAIL_PREPARE, MODULE_NAME, fn, query);
        return false;
    }

    unsigned long long paramLen[CancelSaleReservationJob::MAX_PARAM_COUNT] = {0};
    DbTransaction* const t = tran.Tran;
    bool const bound =
        t->BindParam(1, SQL_PARAM_OUTPUT, &dbRetValue, 0, 0, SQL_INTEGER, SQL_C_SLONG, &paramLen[0]) &&
        t->BindParam(2, SQL_PARAM_INPUT, &job._saleId, 0, 0, SQL_BIGINT, SQL_C_SBIGINT, &paramLen[1]) &&
        t->BindParam(3, SQL_PARAM_INPUT, &job._sellerPcId, 0, 0, SQL_BIGINT, SQL_C_SBIGINT, &paramLen[2]);
    if (!bound)
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 916, FAIL_BIND, MODULE_NAME, fn);
        return false;
    }
    if (!t->Execute())
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 906, FAIL_EXECUTE, MODULE_NAME, fn, dbRetValue);
        return false;
    }
    return dbRetValue == 0;
}

// 0x213c0
bool const MarketDB::RegisterSale(int& dbRetValue, RegisterSaleJob& job)
{
    wchar_t const* const fn = L"MarketDB::RegisterSale";
    AutoDbTran tran(kDbId);
    if (tran.Tran == nullptr)
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 924, FAIL_ACQUIRE, MODULE_NAME, fn, kDbId);
        return false;
    }
    wchar_t const* const query = L"{?=CALL dbo.usp_RegisterSale(?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)}";
    if (!tran.Tran->Prepare(Query(query)))
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 930, FAIL_PREPARE, MODULE_NAME, fn, query);
        return false;
    }

    TIMESTAMP_STRUCT expirationTime;
    memset(&expirationTime, 0, sizeof(expirationTime));
    unsigned long long paramLen[RegisterSaleJob::MAX_PARAM_COUNT] = {0};
    unsigned long long itemLen[13] = {0};  // same slots as in LoadSaleList
    SaleItemInfo& itemInfo = job._saleItemInfo;
    // An empty xml text goes to the db as NULL.
    itemLen[12] = wcslen(itemInfo._itemXmlData) == 0 ? kNullData : kNts;

    DbTransaction* const t = tran.Tran;
    bool const bound =
        t->BindParam(1, SQL_PARAM_OUTPUT, &dbRetValue, 0, 0, SQL_INTEGER, SQL_C_SLONG, &paramLen[0]) &&
        t->BindParam(2, SQL_PARAM_INPUT, &job._saleId, 0, 0, SQL_BIGINT, SQL_C_SBIGINT, &paramLen[1]) &&
        t->BindParam(3, SQL_PARAM_INPUT, &job._sellerPcId, 0, 0, SQL_BIGINT, SQL_C_SBIGINT, &paramLen[2]) &&
        t->BindParam(4, SQL_PARAM_INPUT, &job._pawnId, 0, 0, SQL_BIGINT, SQL_C_SBIGINT, &paramLen[3]) &&
        t->BindParam(5, SQL_PARAM_INPUT, &job._unitPrice, 0, 0, SQL_BIGINT, SQL_C_SBIGINT, &paramLen[4]) &&
        t->BindParam(6, SQL_PARAM_INPUT, &job._saleDuration, 0, 0, SQL_INTEGER, SQL_C_SLONG, &paramLen[5]) &&
        t->BindParam(7, SQL_PARAM_OUTPUT, &expirationTime, sizeof(expirationTime), sizeof(expirationTime),
                     SQL_TIMESTAMP, SQL_C_TYPE_TIMESTAMP, &paramLen[6]) &&
        t->BindParam(8, SQL_PARAM_INPUT, &itemInfo._itemCommonCategory, 0, 0, SQL_TINYINT, SQL_C_STINYINT,
                     &itemLen[0]) &&
        t->BindParam(9, SQL_PARAM_INPUT, &itemInfo._itemFirstCategory, 0, 0, SQL_TINYINT, SQL_C_STINYINT,
                     &itemLen[1]) &&
        t->BindParam(10, SQL_PARAM_INPUT, &itemInfo._itemSecondCategory, 0, 0, SQL_TINYINT, SQL_C_STINYINT,
                     &itemLen[2]) &&
        t->BindParam(11, SQL_PARAM_INPUT, &itemInfo._itemThirdCategory, 0, 0, SQL_TINYINT, SQL_C_STINYINT,
                     &itemLen[3]) &&
        t->BindParam(12, SQL_PARAM_INPUT, &itemInfo._itemType, 0, 0, SQL_TINYINT, SQL_C_STINYINT, &itemLen[4]) &&
        t->BindParam(13, SQL_PARAM_INPUT, &itemInfo._itemInstanceId, 0, 0, SQL_BIGINT, SQL_C_SBIGINT, &itemLen[5]) &&
        t->BindParam(14, SQL_PARAM_INPUT, &itemInfo._itemDataId, 0, 0, SQL_INTEGER, SQL_C_SLONG, &itemLen[6]) &&
        t->BindParam(15, SQL_PARAM_INPUT, &itemInfo._itemLevel, 0, 0, SQL_SMALLINT, SQL_C_SSHORT, &itemLen[7]) &&
        t->BindParam(16, SQL_PARAM_INPUT, &itemInfo._itemExp, 0, 0, SQL_INTEGER, SQL_C_SLONG, &itemLen[8]) &&
        t->BindParam(17, SQL_PARAM_INPUT, &itemInfo._itemAmount, 0, 0, SQL_INTEGER, SQL_C_SLONG, &itemLen[9]) &&
        t->BindParam(18, SQL_PARAM_INPUT, &itemInfo._itemGrade, 0, 0, SQL_TINYINT, SQL_C_STINYINT, &itemLen[10]) &&
        t->BindParam(19, SQL_PARAM_INPUT, &itemInfo._itemEquipLevel, 0, 0, SQL_TINYINT, SQL_C_STINYINT,
                     &itemLen[11]) &&
        t->BindParam(20, SQL_PARAM_INPUT, itemInfo._itemXmlData, 2050, 1024, SQL_WVARCHAR, SQL_C_WCHAR,
                     &itemLen[12]);
    if (!bound)
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 983, FAIL_BIND, MODULE_NAME, fn);
        return false;
    }
    if (!t->Execute())
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 971, FAIL_EXECUTE, MODULE_NAME, fn, dbRetValue);
        return false;
    }
    if (dbRetValue != 0)
        return false;
    job._saleExpirationTime = Db::ConvertTime(&expirationTime);
    return true;
}

// 0x21b00
bool const MarketDB::UpdateSalePrice(int& dbRetValue, UpdateSalePriceJob& job)
{
    wchar_t const* const fn = L"MarketDB::UpdateSalePrice";
    AutoDbTran tran(kDbId);
    if (tran.Tran == nullptr)
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 991, FAIL_ACQUIRE, MODULE_NAME, fn, kDbId);
        return false;
    }
    wchar_t const* const query = L"{?=CALL dbo.usp_UpdateSalePrice(?,?,?,?,?,?)}";
    if (!tran.Tran->Prepare(Query(query)))
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 997, FAIL_PREPARE, MODULE_NAME, fn, query);
        return false;
    }

    unsigned long long paramLen[UpdateSalePriceJob::MAX_PARAM_COUNT] = {0};
    // A bid unit price of 0 goes to the db as NULL.
    paramLen[UpdateSalePriceJob::PARAM_NEW_BID_UNIT_PRICE] = job._newBidUnitPrice == 0 ? kNullData : 0;

    DbTransaction* const t = tran.Tran;
    bool const bound =
        t->BindParam(1, SQL_PARAM_OUTPUT, &dbRetValue, 0, 0, SQL_INTEGER, SQL_C_SLONG, &paramLen[0]) &&
        t->BindParam(2, SQL_PARAM_INPUT, &job._saleId, 0, 0, SQL_BIGINT, SQL_C_SBIGINT, &paramLen[1]) &&
        t->BindParam(3, SQL_PARAM_INPUT, &job._saleType, 0, 0, SQL_TINYINT, SQL_C_STINYINT, &paramLen[2]) &&
        t->BindParam(4, SQL_PARAM_INPUT, &job._sellerPcId, 0, 0, SQL_BIGINT, SQL_C_SBIGINT, &paramLen[3]) &&
        t->BindParam(5, SQL_PARAM_INPUT, &job._newSalePrice, 0, 0, SQL_BIGINT, SQL_C_SBIGINT, &paramLen[4]) &&
        t->BindParam(6, SQL_PARAM_INPUT, &job._newUnitPrice, 0, 0, SQL_BIGINT, SQL_C_SBIGINT, &paramLen[5]) &&
        t->BindParam(7, SQL_PARAM_INPUT, &job._newBidUnitPrice, 0, 0, SQL_BIGINT, SQL_C_SBIGINT, &paramLen[6]);
    if (!bound)
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 1028, FAIL_BIND, MODULE_NAME, fn);
        return false;
    }
    if (!t->Execute())
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 1018, FAIL_EXECUTE, MODULE_NAME, fn, dbRetValue);
        return false;
    }
    return dbRetValue == 0;
}

// 0x21ec0
bool const MarketDB::AbandonSale(int& dbRetValue, AbandonSaleJob& job)
{
    wchar_t const* const fn = L"MarketDB::AbandonSale";
    AutoDbTran tran(kDbId);
    if (tran.Tran == nullptr)
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 1036, FAIL_ACQUIRE, MODULE_NAME, fn, kDbId);
        return false;
    }
    wchar_t const* const query = L"{?=CALL dbo.usp_AbandonSale(?,?,?,?,?,?)}";
    if (!tran.Tran->Prepare(Query(query)))
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 1042, FAIL_PREPARE, MODULE_NAME, fn, query);
        return false;
    }

    unsigned long long paramLen[AbandonSaleJob::MAX_PARAM_COUNT] = {0};
    paramLen[AbandonSaleJob::PARAM_STATEMENT_BODY] = kNts;
    paramLen[AbandonSaleJob::PARAM_STATEMENT_TITLE] = kNts;

    DbTransaction* const t = tran.Tran;
    MarketStatement& statement = job._marketStatement;
    bool const bound =
        t->BindParam(1, SQL_PARAM_OUTPUT, &dbRetValue, 0, 0, SQL_INTEGER, SQL_C_SLONG, &paramLen[0]) &&
        t->BindParam(2, SQL_PARAM_INPUT, &job._saleId, 0, 0, SQL_BIGINT, SQL_C_SBIGINT, &paramLen[1]) &&
        t->BindParam(3, SQL_PARAM_INPUT, &job._saleType, 0, 0, SQL_TINYINT, SQL_C_STINYINT, &paramLen[2]) &&
        t->BindParam(4, SQL_PARAM_INPUT, &job._sellerPcId, 0, 0, SQL_BIGINT, SQL_C_SBIGINT, &paramLen[3]) &&
        t->BindParam(5, SQL_PARAM_OUTPUT, &job._deliveryId, 0, 0, SQL_BIGINT, SQL_C_SBIGINT, &paramLen[4]) &&
        t->BindParam(6, SQL_PARAM_OUTPUT, statement._statementTitle, 130, 64, SQL_WVARCHAR, SQL_C_WCHAR,
                     &paramLen[5]) &&
        t->BindParam(7, SQL_PARAM_OUTPUT, statement._statementBody, 2050, 1024, SQL_WVARCHAR, SQL_C_WCHAR,
                     &paramLen[6]);
    if (!bound)
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 1072, FAIL_BIND, MODULE_NAME, fn);
        return false;
    }
    if (!t->Execute())
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 1062, FAIL_EXECUTE, MODULE_NAME, fn, dbRetValue);
        return false;
    }
    return dbRetValue == 0;
}

// 0x222a0
bool const MarketDB::ReserveBid(int& dbRetValue, ReserveBidJob& job)
{
    wchar_t const* const fn = L"MarketDB::ReserveBid";
    AutoDbTran tran(kDbId);
    if (tran.Tran == nullptr)
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 1080, FAIL_ACQUIRE, MODULE_NAME, fn, kDbId);
        return false;
    }
    wchar_t const* const query = L"{?=CALL dbo.usp_ReserveBid(?,?,?,?,?,?,?,?,?)}";
    if (!tran.Tran->Prepare(Query(query)))
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 1086, FAIL_PREPARE, MODULE_NAME, fn, query);
        return false;
    }

    unsigned long long paramLen[ReserveBidJob::MAX_PARAM_COUNT] = {0};
    paramLen[ReserveBidJob::PARAM_BIDDER_NAME] = kNts;
    paramLen[ReserveBidJob::PARAM_BIDDER_WORLD_NAME] = kNts;

    DbTransaction* const t = tran.Tran;
    DealingInfo& dealingInfo = job._bidInfo._dealingInfo;
    Participant& bidder = dealingInfo._trader;
    bool const bound =
        t->BindParam(1, SQL_PARAM_OUTPUT, &dbRetValue, 0, 0, SQL_INTEGER, SQL_C_SLONG, &paramLen[0]) &&
        t->BindParam(2, SQL_PARAM_INPUT, &job._concurrentBidCount, 0, 0, SQL_INTEGER, SQL_C_SLONG, &paramLen[1]) &&
        t->BindParam(3, SQL_PARAM_INPUT, &job._saleId, 0, 0, SQL_BIGINT, SQL_C_SBIGINT, &paramLen[2]) &&
        t->BindParam(4, SQL_PARAM_INPUT, &bidder._participantWid, 0, 0, SQL_SMALLINT, SQL_C_SSHORT, &paramLen[3]) &&
        t->BindParam(5, SQL_PARAM_INPUT, &bidder._participantPcId, 0, 0, SQL_BIGINT, SQL_C_SBIGINT, &paramLen[4]) &&
        t->BindParam(6, SQL_PARAM_INPUT, &bidder._participantAccountId, 0, 0, SQL_GUID, SQL_C_GUID, &paramLen[5]) &&
        t->BindParam(7, SQL_PARAM_INPUT, bidder._participantWorldName, 66, 32, SQL_WVARCHAR, SQL_C_WCHAR,
                     &paramLen[6]) &&
        t->BindParam(8, SQL_PARAM_INPUT, bidder._participantName, 66, 32, SQL_WVARCHAR, SQL_C_WCHAR, &paramLen[7]) &&
        t->BindParam(9, SQL_PARAM_INPUT, &dealingInfo._dealingPrice, 0, 0, SQL_BIGINT, SQL_C_SBIGINT, &paramLen[8]) &&
        t->BindParam(10, SQL_PARAM_OUTPUT, &dealingInfo._dealingId, 0, 0, SQL_BIGINT, SQL_C_SBIGINT, &paramLen[9]);
    if (!bound)
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 1119, FAIL_BIND, MODULE_NAME, fn);
        return false;
    }
    if (!t->Execute())
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 1109, FAIL_EXECUTE, MODULE_NAME, fn, dbRetValue);
        return false;
    }
    return dbRetValue == 0;
}

// 0x22710
bool const MarketDB::CancelBidReservation(int& dbRetValue, CancelBidReservationJob& job)
{
    wchar_t const* const fn = L"MarketDB::CancelBidReservation";
    AutoDbTran tran(kDbId);
    if (tran.Tran == nullptr)
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 1127, FAIL_ACQUIRE, MODULE_NAME, fn, kDbId);
        return false;
    }
    wchar_t const* const query = L"{?=CALL dbo.usp_CancelBidReservation(?,?)}";
    if (!tran.Tran->Prepare(Query(query)))
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 1133, FAIL_PREPARE, MODULE_NAME, fn, query);
        return false;
    }

    unsigned long long paramLen[CancelBidReservationJob::MAX_PARAM_COUNT] = {0};
    DbTransaction* const t = tran.Tran;
    bool const bound =
        t->BindParam(1, SQL_PARAM_OUTPUT, &dbRetValue, 0, 0, SQL_INTEGER, SQL_C_SLONG, &paramLen[0]) &&
        t->BindParam(2, SQL_PARAM_INPUT, &job._bidId, 0, 0, SQL_BIGINT, SQL_C_SBIGINT, &paramLen[1]) &&
        t->BindParam(3, SQL_PARAM_INPUT, &job._bidderPcId, 0, 0, SQL_BIGINT, SQL_C_SBIGINT, &paramLen[2]);
    if (!bound)
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 1156, FAIL_BIND, MODULE_NAME, fn);
        return false;
    }
    if (!t->Execute())
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 1146, FAIL_EXECUTE, MODULE_NAME, fn, dbRetValue);
        return false;
    }
    return dbRetValue == 0;
}

// 0x22980
bool const MarketDB::RegisterBid(int& dbRetValue, RegisterBidJob& job)
{
    wchar_t const* const fn = L"MarketDB::RegisterBid";
    AutoDbTran tran(kDbId);
    if (tran.Tran == nullptr)
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 1164, FAIL_ACQUIRE, MODULE_NAME, fn, kDbId);
        return false;
    }
    wchar_t const* const query = L"{?=CALL dbo.usp_RegisterBid(?,?,?,?,?,?)}";
    if (!tran.Tran->Prepare(Query(query)))
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 1170, FAIL_PREPARE, MODULE_NAME, fn, query);
        return false;
    }

    unsigned long long paramLen[RegisterBidJob::MAX_PARAM_COUNT] = {0};
    DbTransaction* const t = tran.Tran;
    bool const bound =
        t->BindParam(1, SQL_PARAM_OUTPUT, &dbRetValue, 0, 0, SQL_INTEGER, SQL_C_SLONG, &paramLen[0]) &&
        t->BindParam(2, SQL_PARAM_INPUT, &job._saleId, 0, 0, SQL_BIGINT, SQL_C_SBIGINT, &paramLen[1]) &&
        t->BindParam(3, SQL_PARAM_INPUT, &job._bidId, 0, 0, SQL_BIGINT, SQL_C_SBIGINT, &paramLen[2]) &&
        t->BindParam(4, SQL_PARAM_INPUT, &job._bidderPcId, 0, 0, SQL_BIGINT, SQL_C_SBIGINT, &paramLen[3]) &&
        t->BindParam(5, SQL_PARAM_INPUT, &job._pawnId, 0, 0, SQL_BIGINT, SQL_C_SBIGINT, &paramLen[4]) &&
        t->BindParam(6, SQL_PARAM_INPUT, &job._bidPrice, 0, 0, SQL_BIGINT, SQL_C_SBIGINT, &paramLen[5]) &&
        t->BindParam(7, SQL_PARAM_INPUT, &job._newUnitPrice, 0, 0, SQL_BIGINT, SQL_C_SBIGINT, &paramLen[6]);
    if (!bound)
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 1197, FAIL_BIND, MODULE_NAME, fn);
        return false;
    }
    if (!t->Execute())
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 1187, FAIL_EXECUTE, MODULE_NAME, fn, dbRetValue);
        return false;
    }
    return dbRetValue == 0;
}

// 0x22d20
bool const MarketDB::UpdateBidPrice(int& dbRetValue, UpdateBidPriceJob& job)
{
    wchar_t const* const fn = L"MarketDB::UpdateBidPrice";
    AutoDbTran tran(kDbId);
    if (tran.Tran == nullptr)
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 1205, FAIL_ACQUIRE, MODULE_NAME, fn, kDbId);
        return false;
    }
    wchar_t const* const query = L"{?=CALL dbo.usp_UpdateBidPrice(?,?,?,?,?)}";
    if (!tran.Tran->Prepare(Query(query)))
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 1211, FAIL_PREPARE, MODULE_NAME, fn, query);
        return false;
    }

    unsigned long long paramLen[UpdateBidPriceJob::MAX_PARAM_COUNT] = {0};
    DbTransaction* const t = tran.Tran;
    bool const bound =
        t->BindParam(1, SQL_PARAM_OUTPUT, &dbRetValue, 0, 0, SQL_INTEGER, SQL_C_SLONG, &paramLen[0]) &&
        t->BindParam(2, SQL_PARAM_INPUT, &job._saleId, 0, 0, SQL_BIGINT, SQL_C_SBIGINT, &paramLen[1]) &&
        t->BindParam(3, SQL_PARAM_INPUT, &job._bidId, 0, 0, SQL_BIGINT, SQL_C_SBIGINT, &paramLen[2]) &&
        t->BindParam(4, SQL_PARAM_INPUT, &job._bidderPcId, 0, 0, SQL_BIGINT, SQL_C_SBIGINT, &paramLen[3]) &&
        t->BindParam(5, SQL_PARAM_INPUT, &job._newBidPrice, 0, 0, SQL_BIGINT, SQL_C_SBIGINT, &paramLen[4]) &&
        t->BindParam(6, SQL_PARAM_INPUT, &job._newUnitPrice, 0, 0, SQL_BIGINT, SQL_C_SBIGINT, &paramLen[5]);
    if (!bound)
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 1237, FAIL_BIND, MODULE_NAME, fn);
        return false;
    }
    if (!t->Execute())
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 1227, FAIL_EXECUTE, MODULE_NAME, fn, dbRetValue);
        return false;
    }
    return dbRetValue == 0;
}

// 0x23070
bool const MarketDB::AbandonBid(int& dbRetValue, AbandonBidJob& job)
{
    wchar_t const* const fn = L"MarketDB::AbandonBid";
    AutoDbTran tran(kDbId);
    if (tran.Tran == nullptr)
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 1245, FAIL_ACQUIRE, MODULE_NAME, fn, kDbId);
        return false;
    }
    wchar_t const* const query = L"{?=CALL dbo.usp_AbandonBid(?,?,?,?,?,?)}";
    if (!tran.Tran->Prepare(Query(query)))
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 1251, FAIL_PREPARE, MODULE_NAME, fn, query);
        return false;
    }

    unsigned long long paramLen[AbandonBidJob::MAX_PARAM_COUNT] = {0};
    paramLen[AbandonBidJob::PARAM_MARKETSTATEMENT_BODY] = kNts;
    paramLen[AbandonBidJob::PARAM_MARKETSTATEMENT_TITLE] = kNts;

    DbTransaction* const t = tran.Tran;
    MarketStatement& statement = job._marketStatement;
    bool const bound =
        t->BindParam(1, SQL_PARAM_OUTPUT, &dbRetValue, 0, 0, SQL_INTEGER, SQL_C_SLONG, &paramLen[0]) &&
        t->BindParam(2, SQL_PARAM_INPUT, &job._saleId, 0, 0, SQL_BIGINT, SQL_C_SBIGINT, &paramLen[1]) &&
        t->BindParam(3, SQL_PARAM_INPUT, &job._bidId, 0, 0, SQL_BIGINT, SQL_C_SBIGINT, &paramLen[2]) &&
        t->BindParam(4, SQL_PARAM_INPUT, &job._bidderPcId, 0, 0, SQL_BIGINT, SQL_C_SBIGINT, &paramLen[3]) &&
        t->BindParam(5, SQL_PARAM_OUTPUT, &job._deliveryId, 0, 0, SQL_BIGINT, SQL_C_SBIGINT, &paramLen[4]) &&
        t->BindParam(6, SQL_PARAM_OUTPUT, statement._statementTitle, 130, 64, SQL_WVARCHAR, SQL_C_WCHAR,
                     &paramLen[5]) &&
        t->BindParam(7, SQL_PARAM_OUTPUT, statement._statementBody, 2050, 1024, SQL_WVARCHAR, SQL_C_WCHAR,
                     &paramLen[6]);
    if (!bound)
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 1281, FAIL_BIND, MODULE_NAME, fn);
        return false;
    }
    if (!t->Execute())
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 1271, FAIL_EXECUTE, MODULE_NAME, fn, dbRetValue);
        return false;
    }
    return dbRetValue == 0;
}

// 0x23450
bool const MarketDB::ReservePurchase(int& dbRetValue, ReservePurchaseJob& job)
{
    wchar_t const* const fn = L"MarketDB::ReservePurchase";
    AutoDbTran tran(kDbId);
    if (tran.Tran == nullptr)
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 1289, FAIL_ACQUIRE, MODULE_NAME, fn, kDbId);
        return false;
    }
    wchar_t const* const query = L"{?=CALL dbo.usp_ReservePurchase(?,?,?,?,?,?,?,?)}";
    if (!tran.Tran->Prepare(Query(query)))
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 1295, FAIL_PREPARE, MODULE_NAME, fn, query);
        return false;
    }

    unsigned long long paramLen[ReservePurchaseJob::MAX_PARAM_COUNT] = {0};
    paramLen[ReservePurchaseJob::PARAM_PURCHASER_NAME] = kNts;
    paramLen[ReservePurchaseJob::PARAM_PURCHASER_WORLD_NAME] = kNts;

    DbTransaction* const t = tran.Tran;
    DealingInfo& dealingInfo = job._purchaseInfo._dealingInfo;
    Participant& purchaser = dealingInfo._trader;
    bool const bound =
        t->BindParam(1, SQL_PARAM_OUTPUT, &dbRetValue, 0, 0, SQL_INTEGER, SQL_C_SLONG, &paramLen[0]) &&
        t->BindParam(2, SQL_PARAM_INPUT, &job._saleId, 0, 0, SQL_BIGINT, SQL_C_SBIGINT, &paramLen[1]) &&
        t->BindParam(3, SQL_PARAM_INPUT, &purchaser._participantWid, 0, 0, SQL_SMALLINT, SQL_C_SSHORT,
                     &paramLen[2]) &&
        t->BindParam(4, SQL_PARAM_INPUT, &purchaser._participantPcId, 0, 0, SQL_BIGINT, SQL_C_SBIGINT,
                     &paramLen[3]) &&
        t->BindParam(5, SQL_PARAM_INPUT, &purchaser._participantAccountId, 0, 0, SQL_GUID, SQL_C_GUID,
                     &paramLen[4]) &&
        t->BindParam(6, SQL_PARAM_INPUT, purchaser._participantWorldName, 66, 32, SQL_WVARCHAR, SQL_C_WCHAR,
                     &paramLen[5]) &&
        t->BindParam(7, SQL_PARAM_INPUT, purchaser._participantName, 66, 32, SQL_WVARCHAR, SQL_C_WCHAR,
                     &paramLen[6]) &&
        t->BindParam(8, SQL_PARAM_INPUT, &dealingInfo._dealingPrice, 0, 0, SQL_BIGINT, SQL_C_SBIGINT, &paramLen[7]) &&
        t->BindParam(9, SQL_PARAM_OUTPUT, &dealingInfo._dealingId, 0, 0, SQL_BIGINT, SQL_C_SBIGINT, &paramLen[8]);
    if (!bound)
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 1327, FAIL_BIND, MODULE_NAME, fn);
        return false;
    }
    if (!t->Execute())
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 1317, FAIL_EXECUTE, MODULE_NAME, fn, dbRetValue);
        return false;
    }
    return dbRetValue == 0;
}

// 0x238d0
bool const MarketDB::CancelPurchaseReservation(int& dbRetValue, CancelPurchaseReservationJob& job)
{
    wchar_t const* const fn = L"MarketDB::CancelPurchaseReservation";
    AutoDbTran tran(kDbId);
    if (tran.Tran == nullptr)
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 1335, FAIL_ACQUIRE, MODULE_NAME, fn, kDbId);
        return false;
    }
    wchar_t const* const query = L"{?=CALL dbo.usp_CancelPurchaseReservation(?,?)}";
    if (!tran.Tran->Prepare(Query(query)))
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 1341, FAIL_PREPARE, MODULE_NAME, fn, query);
        return false;
    }

    unsigned long long paramLen[CancelPurchaseReservationJob::MAX_PARAM_COUNT] = {0};
    DbTransaction* const t = tran.Tran;
    bool const bound =
        t->BindParam(1, SQL_PARAM_OUTPUT, &dbRetValue, 0, 0, SQL_INTEGER, SQL_C_SLONG, &paramLen[0]) &&
        t->BindParam(2, SQL_PARAM_INPUT, &job._purchaseId, 0, 0, SQL_BIGINT, SQL_C_SBIGINT, &paramLen[1]) &&
        t->BindParam(3, SQL_PARAM_INPUT, &job._purchaserPcId, 0, 0, SQL_BIGINT, SQL_C_SBIGINT, &paramLen[2]);
    if (!bound)
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 1364, FAIL_BIND, MODULE_NAME, fn);
        return false;
    }
    if (!t->Execute())
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 1354, FAIL_EXECUTE, MODULE_NAME, fn, dbRetValue);
        return false;
    }
    return dbRetValue == 0;
}

// 0x23b40
bool const MarketDB::RegisterPurchase(int& dbRetValue, RegisterPurchaseJob& job)
{
    wchar_t const* const fn = L"MarketDB::RegisterPurchase";
    AutoDbTran tran(kDbId);
    if (tran.Tran == nullptr)
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 1372, FAIL_ACQUIRE, MODULE_NAME, fn, kDbId);
        return false;
    }
    wchar_t const* const query = L"{?=CALL dbo.usp_RegisterPurchase(?,?,?,?,?,?,?,?,?,?,?,?,?)}";
    if (!tran.Tran->Prepare(Query(query)))
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 1378, FAIL_PREPARE, MODULE_NAME, fn, query);
        return false;
    }

    unsigned long long paramLen[RegisterPurchaseJob::MAX_PARAM_COUNT] = {0};
    paramLen[RegisterPurchaseJob::PARAM_ITEM_MARKETSTATEMENT_BODY] = kNts;
    paramLen[RegisterPurchaseJob::PARAM_ITEM_MARKETSTATEMENT_TITLE] = kNts;
    paramLen[RegisterPurchaseJob::PARAM_MONEY_MARKETSTATEMENT_BODY] = kNts;
    paramLen[RegisterPurchaseJob::PARAM_MONEY_MARKETSTATEMENT_TITLE] = kNts;

    DbTransaction* const t = tran.Tran;
    MarketStatement& moneyStatement = job._moneyMarketStatement;
    MarketStatement& itemStatement = job._itemMarketStatement;
    bool const bound =
        t->BindParam(1, SQL_PARAM_OUTPUT, &dbRetValue, 0, 0, SQL_INTEGER, SQL_C_SLONG, &paramLen[0]) &&
        t->BindParam(2, SQL_PARAM_INPUT, &job._saleId, 0, 0, SQL_BIGINT, SQL_C_SBIGINT, &paramLen[1]) &&
        t->BindParam(3, SQL_PARAM_INPUT, &job._purchaseId, 0, 0, SQL_BIGINT, SQL_C_SBIGINT, &paramLen[2]) &&
        t->BindParam(4, SQL_PARAM_INPUT, &job._purchaserPcId, 0, 0, SQL_BIGINT, SQL_C_SBIGINT, &paramLen[3]) &&
        t->BindParam(5, SQL_PARAM_INPUT, &job._pawnId, 0, 0, SQL_BIGINT, SQL_C_SBIGINT, &paramLen[4]) &&
        t->BindParam(6, SQL_PARAM_INPUT, &job._purchasePrice, 0, 0, SQL_BIGINT, SQL_C_SBIGINT, &paramLen[5]) &&
        t->BindParam(7, SQL_PARAM_INPUT, &job._ruleResetTime, 0, 0, SQL_INTEGER, SQL_C_SLONG, &paramLen[6]) &&
        t->BindParam(8, SQL_PARAM_OUTPUT, &job._moneyDeliveryId, 0, 0, SQL_BIGINT, SQL_C_SBIGINT, &paramLen[7]) &&
        t->BindParam(9, SQL_PARAM_OUTPUT, moneyStatement._statementTitle, 130, 64, SQL_WVARCHAR, SQL_C_WCHAR,
                     &paramLen[8]) &&
        t->BindParam(10, SQL_PARAM_OUTPUT, moneyStatement._statementBody, 2050, 1024, SQL_WVARCHAR, SQL_C_WCHAR,
                     &paramLen[9]) &&
        t->BindParam(11, SQL_PARAM_OUTPUT, &job._resultMoneyAmount, 0, 0, SQL_BIGINT, SQL_C_SBIGINT,
                     &paramLen[10]) &&
        t->BindParam(12, SQL_PARAM_OUTPUT, &job._itemDeliveryId, 0, 0, SQL_BIGINT, SQL_C_SBIGINT, &paramLen[11]) &&
        t->BindParam(13, SQL_PARAM_OUTPUT, itemStatement._statementTitle, 130, 64, SQL_WVARCHAR, SQL_C_WCHAR,
                     &paramLen[12]) &&
        t->BindParam(14, SQL_PARAM_OUTPUT, itemStatement._statementBody, 2050, 1024, SQL_WVARCHAR, SQL_C_WCHAR,
                     &paramLen[13]);
    if (!bound)
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 1416, FAIL_BIND, MODULE_NAME, fn);
        return false;
    }
    if (!t->Execute())
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 1406, FAIL_EXECUTE, MODULE_NAME, fn, dbRetValue);
        return false;
    }
    return dbRetValue == 0;
}

// Card lift-marketdealerdaemon-6: expire, delivery status, retry (0x24100..0x27230).

// 0x24100
bool const MarketDB::ExpireSale(int& dbRetValue, long long saleId, long long& outItemDeliveryId,
                                MarketStatement& outMarketStatement)
{
    enum Param
    {
        PARAM_RETURN_VALUE = 0,
        PARAM_SALE_ID = 1,
        PARAM_DELIVERY_ID = 2,
        PARAM_MARKETSTATEMENT_TITLE = 3,
        PARAM_MARKETSTATEMENT_BODY = 4,
        MAX_PARAM_COUNT = 5,
    };
    wchar_t const* const fn = L"MarketDB::ExpireSale";
    AutoDbTran tran(kDbId);
    if (tran.Tran != nullptr)
    {
        tran.TimeoutSec = 0;
        SQLSetStmtAttrW(tran.Tran->StmtHandle, SQL_QUERY_TIMEOUT, nullptr, 0);
    }
    if (tran.Tran == nullptr)
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 1424, FAIL_ACQUIRE, MODULE_NAME, fn, kDbId);
        return false;
    }
    wchar_t const* const query = L"{?=CALL dbo.usp_ExpireSale(?,?,?,?)}";
    if (!tran.Tran->Prepare(Query(query)))
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 1430, FAIL_PREPARE, MODULE_NAME, fn, query);
        return false;
    }

    unsigned long long paramLen[MAX_PARAM_COUNT] = {0};
    paramLen[PARAM_MARKETSTATEMENT_BODY] = kNts;
    paramLen[PARAM_MARKETSTATEMENT_TITLE] = kNts;

    DbTransaction* const t = tran.Tran;
    bool const bound =
        t->BindParam(1, SQL_PARAM_OUTPUT, &dbRetValue, 0, 0, SQL_INTEGER, SQL_C_SLONG,
                     &paramLen[PARAM_RETURN_VALUE]) &&
        t->BindParam(2, SQL_PARAM_INPUT, &saleId, 0, 0, SQL_BIGINT, SQL_C_SBIGINT, &paramLen[PARAM_SALE_ID]) &&
        t->BindParam(3, SQL_PARAM_OUTPUT, &outItemDeliveryId, 0, 0, SQL_BIGINT, SQL_C_SBIGINT,
                     &paramLen[PARAM_DELIVERY_ID]) &&
        t->BindParam(4, SQL_PARAM_OUTPUT, outMarketStatement._statementTitle, 130, 64, SQL_WVARCHAR, SQL_C_WCHAR,
                     &paramLen[PARAM_MARKETSTATEMENT_TITLE]) &&
        t->BindParam(5, SQL_PARAM_OUTPUT, outMarketStatement._statementBody, 2050, 1024, SQL_WVARCHAR, SQL_C_WCHAR,
                     &paramLen[PARAM_MARKETSTATEMENT_BODY]);
    if (!bound)
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 1466, FAIL_BIND, MODULE_NAME, fn);
        return false;
    }
    if (!t->Execute())
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 1456, FAIL_EXECUTE, MODULE_NAME, fn, dbRetValue);
        return false;
    }
    return dbRetValue == 0;
}

// 0x24490
bool const MarketDB::ExpireAuction(int& dbRetValue, long long saleId, int ruleResetTime, int& outDeliveryCount,
                                   DeliveryRelation*& deliveryRelation, int const arraySize)
{
    wchar_t const* const fn = L"MarketDB::ExpireAuction";
    if (saleId <= 0 || deliveryRelation == nullptr || arraySize <= 0)
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 1473,
                   L"== CRASH == [%s], %s; invalid parameter, saleId:0x%I64X, deliveryRelation:0x%p, arraySize:%d",
                   MODULE_NAME, fn, saleId, deliveryRelation, arraySize);
        AlertSender::Write(MARKETDB_FILE, 1473,
                           L"== CRASH == [%s], %s; invalid parameter, saleId:0x%I64X, deliveryRelation:0x%p, "
                           L"arraySize:%d",
                           MODULE_NAME, fn, saleId, deliveryRelation, arraySize);
        return false;
    }
    AutoDbTran tran(kDbId);
    if (tran.Tran != nullptr)
    {
        tran.TimeoutSec = 0;
        SQLSetStmtAttrW(tran.Tran->StmtHandle, SQL_QUERY_TIMEOUT, nullptr, 0);
    }
    if (tran.Tran == nullptr)
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 1479, FAIL_ACQUIRE, MODULE_NAME, fn, kDbId);
        return false;
    }
    wchar_t const* const query = L"{?=CALL dbo.usp_ExpireAuction(?,?,?)}";
    if (!tran.Tran->Prepare(Query(query)))
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 1485, FAIL_PREPARE, MODULE_NAME, fn, query);
        return false;
    }

    DeliveryRelation relation;
    relation._deliveryId = 0;
    relation._deliveryReason = 0;
    relation._pawnOwnerServiceId = 0;
    relation._pawnOwnerPcId = 0;
    relation._recipientPcId = 0;
    memset(relation._marketStatement._statementTitle, 0, sizeof(relation._marketStatement._statementTitle));
    memset(relation._marketStatement._statementBody, 0, sizeof(relation._marketStatement._statementBody));
    relation._moneyAmount = 0;
    unsigned long long paramLen[4] = {0};
    unsigned long long columnLen[DeliveryRelation::MAX_COLUMN_COUNT] = {0};

    DbTransaction* const t = tran.Tran;
    MarketStatement& statement = relation._marketStatement;
    bool const bound =
        t->BindParam(1, SQL_PARAM_OUTPUT, &dbRetValue, 0, 0, SQL_INTEGER, SQL_C_SLONG, &paramLen[0]) &&
        t->BindParam(2, SQL_PARAM_INPUT, &saleId, 0, 0, SQL_BIGINT, SQL_C_SBIGINT, &paramLen[1]) &&
        t->BindParam(3, SQL_PARAM_INPUT, &ruleResetTime, 0, 0, SQL_INTEGER, SQL_C_SLONG, &paramLen[2]) &&
        t->BindParam(4, SQL_PARAM_OUTPUT, &outDeliveryCount, 0, 0, SQL_INTEGER, SQL_C_SLONG, &paramLen[3]) &&
        t->BindCol(1, &relation._deliveryId, 0, SQL_C_SBIGINT, &columnLen[DeliveryRelation::COLUMN_DELIVERY_ID]) &&
        t->BindCol(2, &relation._deliveryReason, 0, SQL_C_STINYINT,
                   &columnLen[DeliveryRelation::COLUMN_DELIVERY_REASON]) &&
        t->BindCol(3, &relation._pawnOwnerServiceId, 0, SQL_C_SBIGINT,
                   &columnLen[DeliveryRelation::COLUMN_PAWN_OWNER_SERVICE_ID]) &&
        t->BindCol(4, &relation._pawnOwnerPcId, 0, SQL_C_SBIGINT,
                   &columnLen[DeliveryRelation::COLUMN_PAWN_OWNER_PCID]) &&
        t->BindCol(5, &relation._recipientPcId, 0, SQL_C_SBIGINT,
                   &columnLen[DeliveryRelation::COLUMN_RECIPIENT_PCID]) &&
        t->BindCol(6, statement._statementTitle, 130, SQL_C_WCHAR,
                   &columnLen[DeliveryRelation::COLUMN_MARKETSTATEMENT_TITLE]) &&
        t->BindCol(7, statement._statementBody, 2050, SQL_C_WCHAR,
                   &columnLen[DeliveryRelation::COLUMN_MARKETSTATEMENT_BODY]) &&
        t->BindCol(8, &relation._moneyAmount, 0, SQL_C_SBIGINT, &columnLen[DeliveryRelation::COLUMN_MONEY_AMOUNT]);
    if (!bound)
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 1562, FAIL_BIND, MODULE_NAME, fn);
        return false;
    }
    if (!t->Execute())
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 1521, FAIL_EXECUTE, MODULE_NAME, fn, dbRetValue);
        return false;
    }

    int currentIndex = 0;
    for (long long index = 0;; ++index)
    {
        memset(&relation, 0, sizeof(relation));
        int const result = t->Fetch(0);  // LIFT: folded. edx is not set at the call. Fetch does not read it.
        if (result == -1)
        {
            Log::Write(Log::LT_ERROR, MARKETDB_FILE, 1535, FAIL_FETCH, MODULE_NAME, fn);
            return false;
        }
        if (result == 0)
            break;
        if (index >= arraySize)
        {
            Log::Write(Log::LT_ERROR, MARKETDB_FILE, 1542,
                       L"[%s], %s; fecth count is more than array size, arraySize:%d, currentIndex:%d", MODULE_NAME,
                       fn, arraySize, currentIndex);
            return false;
        }
        DeliveryRelation& target = deliveryRelation[index];
        target._deliveryId = relation._deliveryId;
        target._deliveryReason = relation._deliveryReason;
        target._pawnOwnerServiceId = relation._pawnOwnerServiceId;
        target._pawnOwnerPcId = relation._pawnOwnerPcId;
        target._recipientPcId = relation._recipientPcId;
        memcpy(&target._marketStatement, &relation._marketStatement, sizeof(target._marketStatement));
        target._moneyAmount = relation._moneyAmount;
        ++currentIndex;
    }
    return dbRetValue == 0;
}

// 0x24e90
bool const MarketDB::UpdateStatusToReporting(int& dbRetValue, long long deliveryId)
{
    wchar_t const* const fn = L"MarketDB::UpdateStatusToReporting";
    if (deliveryId <= 0)
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 1572, L"== CRASH == [%s], %s; invalid parameter, deliveryId:0x%I64X",
                   MODULE_NAME, fn, deliveryId);
        AlertSender::Write(MARKETDB_FILE, 1572, L"== CRASH == [%s], %s; invalid parameter, deliveryId:0x%I64X",
                           MODULE_NAME, fn, deliveryId);
        return false;
    }
    AutoDbTran tran(kDbId);
    if (tran.Tran == nullptr)
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 1578, FAIL_ACQUIRE, MODULE_NAME, fn, kDbId);
        return false;
    }
    wchar_t const* const query = L"{?=CALL dbo.usp_UpdateStatusToReporting(?)}";
    if (!tran.Tran->Prepare(Query(query)))
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 1584, FAIL_PREPARE, MODULE_NAME, fn, query);
        return false;
    }
    unsigned long long paramLen[2] = {0};
    DbTransaction* const t = tran.Tran;
    if (!t->BindParam(1, SQL_PARAM_OUTPUT, &dbRetValue, 0, 0, SQL_INTEGER, SQL_C_SLONG, &paramLen[0]) ||
        !t->BindParam(2, SQL_PARAM_INPUT, &deliveryId, 0, 0, SQL_BIGINT, SQL_C_SBIGINT, &paramLen[1]))
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 1613, FAIL_BIND, MODULE_NAME, fn);
        return false;
    }
    if (!t->Execute())
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 1603, FAIL_EXECUTE, MODULE_NAME, fn, dbRetValue);
        return false;
    }
    return dbRetValue == 0;
}

// 0x25110
bool const MarketDB::UpdateStatusToReportSuccess(int& dbRetValue, UpdateStatusToReportSuccessJob& job)
{
    wchar_t const* const fn = L"MarketDB::UpdateStatusToReportSuccess";
    AutoDbTran tran(kDbId);
    if (tran.Tran == nullptr)
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 1621, FAIL_ACQUIRE, MODULE_NAME, fn, kDbId);
        return false;
    }
    wchar_t const* const query = L"{?=CALL dbo.usp_UpdateStatusToReportSuccess(?)}";
    if (!tran.Tran->Prepare(Query(query)))
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 1627, FAIL_PREPARE, MODULE_NAME, fn, query);
        return false;
    }
    unsigned long long paramLen[UpdateStatusToReportSuccessJob::MAX_PARAM_COUNT] = {0};
    DbTransaction* const t = tran.Tran;
    if (!t->BindParam(1, SQL_PARAM_OUTPUT, &dbRetValue, 0, 0, SQL_INTEGER, SQL_C_SLONG, &paramLen[0]) ||
        !t->BindParam(2, SQL_PARAM_INPUT, &job._deliveryId, 0, 0, SQL_BIGINT, SQL_C_SBIGINT, &paramLen[1]))
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 1649, FAIL_BIND, MODULE_NAME, fn);
        return false;
    }
    if (!t->Execute())
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 1639, FAIL_EXECUTE, MODULE_NAME, fn, dbRetValue);
        return false;
    }
    return dbRetValue == 0;
}

// 0x25320
bool const MarketDB::UpdateStatusToPawnRemovalSuccess(int& dbRetValue, UpdateStatusToPawnRemovalSuccessJob& job)
{
    wchar_t const* const fn = L"MarketDB::UpdateStatusToPawnRemovalSuccess";
    AutoDbTran tran(kDbId);
    if (tran.Tran == nullptr)
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 1657, FAIL_ACQUIRE, MODULE_NAME, fn, kDbId);
        return false;
    }
    wchar_t const* const query = L"{?=CALL dbo.usp_UpdateStatusToPawnRemovalSuccess(?)}";
    if (!tran.Tran->Prepare(Query(query)))
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 1663, FAIL_PREPARE, MODULE_NAME, fn, query);
        return false;
    }
    unsigned long long paramLen[UpdateStatusToPawnRemovalSuccessJob::MAX_PARAM_COUNT] = {0};
    DbTransaction* const t = tran.Tran;
    if (!t->BindParam(1, SQL_PARAM_OUTPUT, &dbRetValue, 0, 0, SQL_INTEGER, SQL_C_SLONG, &paramLen[0]) ||
        !t->BindParam(2, SQL_PARAM_INPUT, &job._deliveryId, 0, 0, SQL_BIGINT, SQL_C_SBIGINT, &paramLen[1]))
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 1685, FAIL_BIND, MODULE_NAME, fn);
        return false;
    }
    if (!t->Execute())
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 1675, FAIL_EXECUTE, MODULE_NAME, fn, dbRetValue);
        return false;
    }
    return dbRetValue == 0;
}

// 0x25530
bool const MarketDB::UpdateStatusToPawnRemovalFailure(int& dbRetValue, UpdateStatusToPawnRemovalFailureJob& job)
{
    wchar_t const* const fn = L"MarketDB::UpdateStatusToPawnRemovalFailure";
    AutoDbTran tran(kDbId);
    if (tran.Tran == nullptr)
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 1693, FAIL_ACQUIRE, MODULE_NAME, fn, kDbId);
        return false;
    }
    wchar_t const* const query = L"{?=CALL dbo.usp_UpdateStatusToPawnRemovalFailure(?)}";
    if (!tran.Tran->Prepare(Query(query)))
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 1699, FAIL_PREPARE, MODULE_NAME, fn, query);
        return false;
    }
    unsigned long long paramLen[UpdateStatusToPawnRemovalFailureJob::MAX_PARAM_COUNT] = {0};
    DbTransaction* const t = tran.Tran;
    if (!t->BindParam(1, SQL_PARAM_OUTPUT, &dbRetValue, 0, 0, SQL_INTEGER, SQL_C_SLONG, &paramLen[0]) ||
        !t->BindParam(2, SQL_PARAM_INPUT, &job._deliveryId, 0, 0, SQL_BIGINT, SQL_C_SBIGINT, &paramLen[1]))
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 1721, FAIL_BIND, MODULE_NAME, fn);
        return false;
    }
    if (!t->Execute())
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 1711, FAIL_EXECUTE, MODULE_NAME, fn, dbRetValue);
        return false;
    }
    return dbRetValue == 0;
}

// 0x25740
bool const MarketDB::UpdateStatusToPostRegistrationSuccess(int& dbRetValue,
                                                           UpdateStatusToPostRegistrationSuccessJob& job)
{
    wchar_t const* const fn = L"MarketDB::UpdateStatusToPostRegistrationSuccess";
    AutoDbTran tran(kDbId);
    if (tran.Tran == nullptr)
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 1729, FAIL_ACQUIRE, MODULE_NAME, fn, kDbId);
        return false;
    }
    wchar_t const* const query = L"{?=CALL dbo.usp_UpdateStatusToPostRegistrationSuccess(?,?)}";
    if (!tran.Tran->Prepare(Query(query)))
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 1735, FAIL_PREPARE, MODULE_NAME, fn, query);
        return false;
    }
    unsigned long long paramLen[UpdateStatusToPostRegistrationSuccessJob::MAX_PARAM_COUNT] = {0};
    DbTransaction* const t = tran.Tran;
    if (!t->BindParam(1, SQL_PARAM_OUTPUT, &dbRetValue, 0, 0, SQL_INTEGER, SQL_C_SLONG, &paramLen[0]) ||
        !t->BindParam(2, SQL_PARAM_INPUT, &job._deliveryId, 0, 0, SQL_BIGINT, SQL_C_SBIGINT, &paramLen[1]) ||
        !t->BindParam(3, SQL_PARAM_INPUT, &job._receiptId, 0, 0, SQL_BIGINT, SQL_C_SBIGINT, &paramLen[2]))
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 1758, FAIL_BIND, MODULE_NAME, fn);
        return false;
    }
    if (!t->Execute())
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 1748, FAIL_EXECUTE, MODULE_NAME, fn, dbRetValue);
        return false;
    }
    return dbRetValue == 0;
}

// 0x259b0
bool const MarketDB::UpdateStatusToPostRegistrationFailure(int& dbRetValue,
                                                           UpdateStatusToPostRegistrationFailureJob& job)
{
    wchar_t const* const fn = L"MarketDB::UpdateStatusToPostRegistrationFailure";
    AutoDbTran tran(kDbId);
    if (tran.Tran == nullptr)
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 1766, FAIL_ACQUIRE, MODULE_NAME, fn, kDbId);
        return false;
    }
    wchar_t const* const query = L"{?=CALL dbo.usp_UpdateStatusToPostRegistrationFailure(?)}";
    if (!tran.Tran->Prepare(Query(query)))
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 1772, FAIL_PREPARE, MODULE_NAME, fn, query);
        return false;
    }
    unsigned long long paramLen[UpdateStatusToPostRegistrationFailureJob::MAX_PARAM_COUNT] = {0};
    DbTransaction* const t = tran.Tran;
    if (!t->BindParam(1, SQL_PARAM_OUTPUT, &dbRetValue, 0, 0, SQL_INTEGER, SQL_C_SLONG, &paramLen[0]) ||
        !t->BindParam(2, SQL_PARAM_INPUT, &job._deliveryId, 0, 0, SQL_BIGINT, SQL_C_SBIGINT, &paramLen[1]))
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 1794, FAIL_BIND, MODULE_NAME, fn);
        return false;
    }
    if (!t->Execute())
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 1784, FAIL_EXECUTE, MODULE_NAME, fn, dbRetValue);
        return false;
    }
    return dbRetValue == 0;
}

// 0x25bc0
bool const MarketDB::UpdateStatusToRetryReady(int& dbRetValue, UpdateStatusToRetryReadyJob& job)
{
    wchar_t const* const fn = L"MarketDB::UpdateStatusToRetryReady";
    AutoDbTran tran(kDbId);
    if (tran.Tran == nullptr)
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 1802, FAIL_ACQUIRE, MODULE_NAME, fn, kDbId);
        return false;
    }
    wchar_t const* const query = L"{?=CALL dbo.usp_UpdateStatusToRetryReady(?)}";
    if (!tran.Tran->Prepare(Query(query)))
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 1808, FAIL_PREPARE, MODULE_NAME, fn, query);
        return false;
    }
    unsigned long long paramLen[UpdateStatusToRetryReadyJob::MAX_PARAM_COUNT] = {0};
    DbTransaction* const t = tran.Tran;
    if (!t->BindParam(1, SQL_PARAM_OUTPUT, &dbRetValue, 0, 0, SQL_INTEGER, SQL_C_SLONG, &paramLen[0]) ||
        !t->BindParam(2, SQL_PARAM_INPUT, &job._deliveryId, 0, 0, SQL_BIGINT, SQL_C_SBIGINT, &paramLen[1]))
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 1830, FAIL_BIND, MODULE_NAME, fn);
        return false;
    }
    if (!t->Execute())
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 1820, FAIL_EXECUTE, MODULE_NAME, fn, dbRetValue);
        return false;
    }
    return dbRetValue == 0;
}

// 0x25dd0
bool const MarketDB::LoadRetryReadySingleDelivery(int& dbRetValue, long long deliveryId)
{
    wchar_t const* const fn = L"MarketDB::LoadRetryReadySingleDelivery";
    AutoDbTran tran(kDbId);
    if (tran.Tran != nullptr)
    {
        tran.TimeoutSec = 0;
        SQLSetStmtAttrW(tran.Tran->StmtHandle, SQL_QUERY_TIMEOUT, nullptr, 0);
    }
    if (tran.Tran == nullptr)
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 1838, FAIL_ACQUIRE, MODULE_NAME, fn, kDbId);
        return false;
    }
    wchar_t const* const query = L"{?=CALL dbo.usp_LoadRetryReadySingleDelivery(?)}";
    if (!tran.Tran->Prepare(Query(query)))
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 1844, FAIL_PREPARE, MODULE_NAME, fn, query);
        return false;
    }

    DeliveryInfo deliveryInfo;
    SaleItemInfo itemInfo;
    memset(&itemInfo, 0, sizeof(itemInfo));
    long long moneyAmount = 0;
    unsigned long long paramLen[2] = {0};
    unsigned long long deliveryLen[15] = {0};  // columns 1..15
    unsigned long long itemLen[13] = {0};      // columns 16..28
    deliveryLen[12] = kNts;
    deliveryLen[11] = kNts;
    deliveryLen[10] = kNts;
    deliveryLen[7] = kNts;
    itemLen[12] = kNts;

    DbTransaction* const t = tran.Tran;
    bool const bound =
        t->BindParam(1, SQL_PARAM_OUTPUT, &dbRetValue, 0, 0, SQL_INTEGER, SQL_C_SLONG, &paramLen[0]) &&
        t->BindParam(2, SQL_PARAM_INPUT, &deliveryId, 0, 0, SQL_BIGINT, SQL_C_SBIGINT, &paramLen[1]) &&
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
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 1949, FAIL_BIND, MODULE_NAME, fn);
        return false;
    }
    if (!t->Execute())
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 1902, FAIL_EXECUTE, MODULE_NAME, fn, dbRetValue);
        return false;
    }

    int const result = t->Fetch(0);  // LIFT: folded. edx is not set at the call. Fetch does not read it.
    if (result == -1)
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 1911, FAIL_FETCH, MODULE_NAME, fn);
        return false;
    }
    if (result == 0)
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 1915, L"[%s], %s; there is no such delivery, deliveryId:0x%I64X",
                   MODULE_NAME, fn, deliveryId);
        return false;
    }

    bool const existItem = itemLen[0] != kNullData;
    // A delivery has an item or money, not both and not neither.
    if ((!existItem && moneyAmount == 0) || (existItem && moneyAmount > 0))
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 1924,
                   L"[%s], %s; invalid delivery item, deliveryId:0x%I64X, saleId:0x%I64X", MODULE_NAME, fn,
                   deliveryInfo._deliveryId, deliveryInfo._saleId);
        return false;
    }

    DeliveryContext* deliveryContext = nullptr;
    if (existItem)
    {
        void* const memory = Memory::_Manager[2]->Alloc(sizeof(DeliveryContext), MARKETDB_FILE, 1930);
        if (memory != nullptr)
            deliveryContext = ::new (memory) DeliveryContext(deliveryInfo, itemInfo);
    }
    else
    {
        void* const memory = Memory::_Manager[2]->Alloc(sizeof(DeliveryContext), MARKETDB_FILE, 1932);
        if (memory != nullptr)
            deliveryContext = ::new (memory) DeliveryContext(deliveryInfo, moneyAmount);
    }
    // BUG: 0x25dd0 no null check after the DeliveryContext Alloc (AddContext and the log read nullptr).
    if (!MarketDealerDaemon::_instance->_deliveryContextManager->AddContext(deliveryContext))
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 1935,
                   L"[%s], %s; failed to add delivery context, deliveryId:0x%I64X, saleId:0x%I64X", MODULE_NAME, fn,
                   deliveryContext->_deliveryInfo._deliveryId, deliveryContext->_deliveryInfo._saleId);
        deliveryContext->removeReferenceCount(MARKETDB_FILE, 1936);
        return false;
    }
    deliveryContext->removeReferenceCount(MARKETDB_FILE, 1940);
    return dbRetValue == 0;
}

// 0x27230
bool const MarketDB::ResetUncompletedDeliveryStatus(int& dbRetValue, int& resetCount)
{
    enum Param
    {
        PARAM_RETURN_VALUE = 0,
        PARAM_RESET_COUNT = 1,
        MAX_PARAM_COUNT = 2,
    };
    wchar_t const* const fn = L"MarketDB::ResetUncompletedDeliveryStatus";
    AutoDbTran tran(kDbId);
    if (tran.Tran == nullptr)
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 1958, FAIL_ACQUIRE, MODULE_NAME, fn, kDbId);
        return false;
    }
    wchar_t const* const query = L"{?=CALL dbo.usp_ResetUncompletedDeliveryStatus(?)}";
    if (!tran.Tran->Prepare(Query(query)))
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 1964, FAIL_PREPARE, MODULE_NAME, fn, query);
        return false;
    }
    unsigned long long paramLen[MAX_PARAM_COUNT] = {0};
    DbTransaction* const t = tran.Tran;
    if (!t->BindParam(1, SQL_PARAM_OUTPUT, &dbRetValue, 0, 0, SQL_INTEGER, SQL_C_SLONG,
                      &paramLen[PARAM_RETURN_VALUE]) ||
        !t->BindParam(2, SQL_PARAM_OUTPUT, &resetCount, 0, 0, SQL_INTEGER, SQL_C_SLONG,
                      &paramLen[PARAM_RESET_COUNT]))
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 1993, FAIL_BIND, MODULE_NAME, fn);
        return false;
    }
    if (!t->Execute())
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 1983, FAIL_EXECUTE, MODULE_NAME, fn, dbRetValue);
        return false;
    }
    return dbRetValue == 0;
}

// 0x27440
bool const MarketDB::SuspendSaleByManager(int& dbRetValue, SuspendSaleManagementJob& job)
{
    wchar_t const* const fn = L"MarketDB::SuspendSaleByManager";
    AutoDbTran tran(kDbId);
    if (tran.Tran == nullptr)
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 2002, FAIL_ACQUIRE, MODULE_NAME, fn, kDbId);
        return false;
    }
    wchar_t const* const query = L"{?=CALL dbo.usp_SuspendSaleByManager(?,?)}";
    if (!tran.Tran->Prepare(Query(query)))
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 2008, FAIL_PREPARE, MODULE_NAME, fn, query);
        return false;
    }
    unsigned long long paramLen[SuspendSaleManagementJob::MAX_PARAM_COUNT] = {0};
    DbTransaction* const t = tran.Tran;
    if (!t->BindParam(1, SQL_PARAM_OUTPUT, &dbRetValue, 0, 0, SQL_INTEGER, SQL_C_SLONG, &paramLen[0]) ||
        !t->BindParam(2, SQL_PARAM_INPUT, &job._saleId, 0, 0, SQL_BIGINT, SQL_C_SBIGINT, &paramLen[1]) ||
        !t->BindParam(3, SQL_PARAM_INPUT, &job._sellerPcId, 0, 0, SQL_BIGINT, SQL_C_SBIGINT, &paramLen[2]))
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 2031, FAIL_BIND, MODULE_NAME, fn);
        return false;
    }
    if (!t->Execute())
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 2021, FAIL_EXECUTE, MODULE_NAME, fn, dbRetValue);
        return false;
    }
    return dbRetValue == 0;
}

// 0x276b0
bool const MarketDB::ResetDeliveryFailureByManager(int& dbRetValue, RetrySingleDeliveryFailureManagementJob& job)
{
    wchar_t const* const fn = L"MarketDB::ResetDeliveryFailureByManager";
    AutoDbTran tran(kDbId);
    if (tran.Tran == nullptr)
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 2039, FAIL_ACQUIRE, MODULE_NAME, fn, kDbId);
        return false;
    }
    wchar_t const* const query = L"{?=CALL dbo.usp_ResetDeliveryFailureByManager(?,?,?)}";
    if (!tran.Tran->Prepare(Query(query)))
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 2045, FAIL_PREPARE, MODULE_NAME, fn, query);
        return false;
    }
    unsigned long long paramLen[RetrySingleDeliveryFailureManagementJob::MAX_PARAM_COUNT] = {0};
    DbTransaction* const t = tran.Tran;
    if (!t->BindParam(1, SQL_PARAM_OUTPUT, &dbRetValue, 0, 0, SQL_INTEGER, SQL_C_SLONG, &paramLen[0]) ||
        !t->BindParam(2, SQL_PARAM_INPUT, &job._deliveryId, 0, 0, SQL_BIGINT, SQL_C_SBIGINT, &paramLen[1]) ||
        !t->BindParam(3, SQL_PARAM_INPUT, &job._saleId, 0, 0, SQL_BIGINT, SQL_C_SBIGINT, &paramLen[2]) ||
        !t->BindParam(4, SQL_PARAM_INPUT, &job._recipientPcId, 0, 0, SQL_BIGINT, SQL_C_SBIGINT, &paramLen[3]))
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 2069, FAIL_BIND, MODULE_NAME, fn);
        return false;
    }
    if (!t->Execute())
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 2059, FAIL_EXECUTE, MODULE_NAME, fn, dbRetValue);
        return false;
    }
    return dbRetValue == 0;
}

// 0x27970
bool const MarketDB::ResetAllDeliveryFailureByManager(int& dbRetValue)
{
    wchar_t const* const fn = L"MarketDB::ResetAllDeliveryFailureByManager";
    AutoDbTran tran(kDbId);
    if (tran.Tran == nullptr)
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 2077, FAIL_ACQUIRE, MODULE_NAME, fn, kDbId);
        return false;
    }
    wchar_t const* const query = L"{?=CALL dbo.usp_ResetAllDeliveryFailureByManager}";
    if (!tran.Tran->Prepare(Query(query)))
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 2083, FAIL_PREPARE, MODULE_NAME, fn, query);
        return false;
    }
    unsigned long long paramLen[1] = {0};
    DbTransaction* const t = tran.Tran;
    if (!t->BindParam(1, SQL_PARAM_OUTPUT, &dbRetValue, 0, 0, SQL_INTEGER, SQL_C_SLONG, &paramLen[0]))
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 2110, FAIL_BIND, MODULE_NAME, fn);
        return false;
    }
    if (!t->Execute())
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 2100, FAIL_EXECUTE, MODULE_NAME, fn, dbRetValue);
        return false;
    }
    return dbRetValue == 0;
}

// 0x27b50
bool const MarketDB::LoadRetryReadyDeliveryList(int& dbRetValue)
{
    wchar_t const* const fn = L"MarketDB::LoadRetryReadyDeliveryList";
    AutoDbTran tran(kDbId);
    if (tran.Tran != nullptr)
    {
        tran.TimeoutSec = 0;
        SQLSetStmtAttrW(tran.Tran->StmtHandle, SQL_QUERY_TIMEOUT, nullptr, 0);
    }
    if (tran.Tran == nullptr)
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 2118, FAIL_ACQUIRE, MODULE_NAME, fn, kDbId);
        return false;
    }
    wchar_t const* const query = L"{?=CALL dbo.usp_LoadRetryReadyDeliveryList}";
    if (!tran.Tran->Prepare(Query(query)))
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 2124, FAIL_PREPARE, MODULE_NAME, fn, query);
        return false;
    }

    DeliveryInfo deliveryInfo;
    SaleItemInfo itemInfo;
    memset(&itemInfo, 0, sizeof(itemInfo));
    long long moneyAmount = 0;
    unsigned long long paramLen[1] = {0};
    unsigned long long deliveryLen[15] = {0};  // columns 1..15
    unsigned long long itemLen[13] = {0};      // columns 16..28
    deliveryLen[12] = kNts;
    deliveryLen[11] = kNts;
    deliveryLen[10] = kNts;
    deliveryLen[7] = kNts;
    itemLen[12] = kNts;

    DbTransaction* const t = tran.Tran;
    bool const bound =
        t->BindParam(1, SQL_PARAM_OUTPUT, &dbRetValue, 0, 0, SQL_INTEGER, SQL_C_SLONG, &paramLen[0]) &&
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
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 2231, FAIL_BIND, MODULE_NAME, fn);
        return false;
    }
    if (!t->Execute())
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 2180, FAIL_EXECUTE, MODULE_NAME, fn, dbRetValue);
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
            Log::Write(Log::LT_ERROR, MARKETDB_FILE, 2196, FAIL_FETCH, MODULE_NAME, fn);
            return false;
        }
        if (result == 0)
            break;

        bool const existItem = itemLen[0] != kNullData;
        // A delivery has an item or money, not both and not neither.
        if ((!existItem && moneyAmount == 0) || (existItem && moneyAmount > 0))
        {
            Log::Write(Log::LT_ERROR, MARKETDB_FILE, 2206,
                       L"[%s], %s; invalid delivery item, deliveryId:0x%I64X, saleId:0x%I64X", MODULE_NAME, fn,
                       deliveryInfo._deliveryId, deliveryInfo._saleId);
            continue;
        }

        DeliveryContext* deliveryContext = nullptr;
        if (existItem)
        {
            void* const memory = Memory::_Manager[2]->Alloc(sizeof(DeliveryContext), MARKETDB_FILE, 2212);
            if (memory != nullptr)
                deliveryContext = ::new (memory) DeliveryContext(deliveryInfo, itemInfo);
        }
        else
        {
            void* const memory = Memory::_Manager[2]->Alloc(sizeof(DeliveryContext), MARKETDB_FILE, 2214);
            if (memory != nullptr)
                deliveryContext = ::new (memory) DeliveryContext(deliveryInfo, moneyAmount);
        }
        // BUG: 0x27b50 no null check after the DeliveryContext Alloc (AddContext and the log read nullptr).
        if (!deliveryContextManager->AddContext(deliveryContext))
        {
            Log::Write(Log::LT_ERROR, MARKETDB_FILE, 2217,
                       L"[%s], %s; failed to add delivery context, deliveryId:0x%I64X, saleId:0x%I64X", MODULE_NAME,
                       fn, deliveryContext->_deliveryInfo._deliveryId, deliveryContext->_deliveryInfo._saleId);
            deliveryContext->removeReferenceCount(MARKETDB_FILE, 2218);
        }
        else
        {
            deliveryContext->removeReferenceCount(MARKETDB_FILE, 2222);
        }
    }
    return dbRetValue == 0;
}

// 0x28f50
bool const MarketDB::UpdateStatusToReportFailure(int& dbRetValue, UpdateStatusToReportFailureManagementJob& job)
{
    wchar_t const* const fn = L"MarketDB::UpdateStatusToReportFailure";
    AutoDbTran tran(kDbId);
    if (tran.Tran == nullptr)
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 2239, FAIL_ACQUIRE, MODULE_NAME, fn, kDbId);
        return false;
    }
    wchar_t const* const query = L"{?=CALL dbo.usp_UpdateStatusToReportFailure(?)}";
    if (!tran.Tran->Prepare(Query(query)))
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 2245, FAIL_PREPARE, MODULE_NAME, fn, query);
        return false;
    }
    unsigned long long paramLen[UpdateStatusToReportFailureManagementJob::MAX_PARAM_COUNT] = {0};
    DbTransaction* const t = tran.Tran;
    if (!t->BindParam(1, SQL_PARAM_OUTPUT, &dbRetValue, 0, 0, SQL_INTEGER, SQL_C_SLONG, &paramLen[0]) ||
        !t->BindParam(2, SQL_PARAM_INPUT, &job._deliveryId, 0, 0, SQL_BIGINT, SQL_C_SBIGINT, &paramLen[1]))
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 2267, FAIL_BIND, MODULE_NAME, fn);
        return false;
    }
    if (!t->Execute())
    {
        Log::Write(Log::LT_ERROR, MARKETDB_FILE, 2257, FAIL_EXECUTE, MODULE_NAME, fn, dbRetValue);
        return false;
    }
    return dbRetValue == 0;
}
