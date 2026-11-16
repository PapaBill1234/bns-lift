// SmartCouponDB.obj (SmartCouponDaemon PDB).
#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <string.h>
#include "SmartCouponDB.h"
#include "Db.h"

#define SMARTCOUPONDB_FILE L"SmartCouponDB.cpp"

#define GUID_ARGS(g)                                                                                               \
    *reinterpret_cast<unsigned int const*>(&(g).guid[0]), *reinterpret_cast<unsigned short const*>(&(g).guid[4]), \
        *reinterpret_cast<unsigned short const*>(&(g).guid[6]), (g).guid[8], (g).guid[9], (g).guid[10],            \
        (g).guid[11], (g).guid[12], (g).guid[13], (g).guid[14], (g).guid[15]

#define GUID_FMT L"%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X"

namespace
{
// ❓ word_1400544F4: an empty text.
wchar_t const kEmpty[] = L"";

unsigned long long const kNullData = static_cast<unsigned long long>(-1);  // SQL_NULL_DATA

bool IsZeroGuid(id128 const* id) { return id->id[0] == 0 && id->id[1] == 0; }

unsigned long long* LenPtr(long long* len) { return reinterpret_cast<unsigned long long*>(len); }
}  // namespace

// 0x10850
AutoDbTran::~AutoDbTran()
{
    if (Tran != nullptr)
    {
        if (TimeoutSec != 10)
            SQLSetStmtAttrW(Tran->StmtHandle, SQL_QUERY_TIMEOUT, reinterpret_cast<SQLPOINTER>(static_cast<long long>(TimeoutSec)), 0);
        Db::ReleaseTransaction(Tran);
        Tran = nullptr;
    }
}

// 0x108e0
bool RetrievePublicationContext::AddPublicationInfo(PublicationInfo const* info)
{
    if (_maxCount <= _count)
    {
        PublicationInfo* list = static_cast<PublicationInfo*>(Memory::_Manager[2]->ReallocZero(
            _publicationList, sizeof(PublicationInfo) * 2 * _maxCount, sizeof(PublicationInfo) * _count,
            SMARTCOUPONDB_FILE, 49));
        if (list == nullptr)
        {
            Log::Write(Log::LT_ERROR, SMARTCOUPONDB_FILE, 51,
                       L"failed to realloc publication list, maxCount:%d, itemCount:%d", _maxCount, _count);
            return false;
        }
        _maxCount *= 2;
        _publicationList = list;
    }
    _publicationList[_count] = *info;
    ++_count;
    return true;
}

// 0x10a00
bool RetrieveEventLogContext::AddEventLogInfo(EventLogInfo const* info)
{
    if (_maxCount <= _count)
    {
        EventLogInfo* list = static_cast<EventLogInfo*>(Memory::_Manager[2]->ReallocZero(
            _eventLogList, sizeof(EventLogInfo) * 2 * _maxCount, sizeof(EventLogInfo) * _count, SMARTCOUPONDB_FILE,
            94));
        if (list == nullptr)
        {
            Log::Write(Log::LT_ERROR, SMARTCOUPONDB_FILE, 96,
                       L"failed to realloc eventlog list, maxCount:%d, listCount:%d", _maxCount, _count);
            return false;
        }
        _maxCount *= 2;
        _eventLogList = list;
    }
    _eventLogList[_count] = *info;
    ++_count;
    return true;
}

// 0x10b00
bool SmartCouponDB::RegisterGameEventLog(int* dbRetValue, id128* gameAccountId, short worldId, long long pcdbid,
                                         int gameEventId, long long* outGameEventLogId)
{
    *dbRetValue = 0;
    *outGameEventLogId = 0;
    if (IsZeroGuid(gameAccountId) || gameEventId == 0)
    {
        Log::Write(Log::LT_ERROR, SMARTCOUPONDB_FILE, 129,
                   L"[%s], invalid parameter, reg-game-event-log, account-id:" GUID_FMT
                   L", wid:%d, pcdbid:0x%I64X, game-event-id:%d",
                   L"db", GUID_ARGS(*gameAccountId), worldId, pcdbid, gameEventId);
        return false;
    }
    AutoDbTran tran(1);
    if (tran.Tran == nullptr)
    {
        Log::Write(Log::LT_ERROR, SMARTCOUPONDB_FILE, 136,
                   L"[%s], failed to acquire transaction, dbId:%d, reg-game-event-log, account-id:" GUID_FMT
                   L", wid:%d, pcdbid:0x%I64X, game-event-id:%d",
                   L"db", 1, GUID_ARGS(*gameAccountId), worldId, pcdbid, gameEventId);
        return false;
    }
    wchar_t const* const query = L"{?=CALL dbo.usp_RegisterGameEventLog(?,?,?,?,?)}";
    if (!tran.Tran->Prepare(const_cast<wchar_t*>(query)))
    {
        Log::Write(Log::LT_ERROR, SMARTCOUPONDB_FILE, 142,
                   L"[%s], failed to prepare sql, reg-game-event-log, account-id:" GUID_FMT
                   L", wid:%d, pcdbid:0x%I64X, game-event-id:%d, query:%s",
                   L"db", GUID_ARGS(*gameAccountId), worldId, pcdbid, gameEventId, query);
        return false;
    }
    unsigned long long retLen = 0;
    unsigned long long gameAccountIdLen = 0;
    unsigned long long widLen = (worldId != 0) ? 0 : kNullData;
    unsigned long long pcdbidLen = (pcdbid != 0) ? 0 : kNullData;
    unsigned long long gameEventIdLen = 0;
    unsigned long long outLen = 0;
    if (tran.Tran->BindParam(1, SQL_PARAM_OUTPUT, dbRetValue, SQL_INTEGER, SQL_C_SLONG, &retLen) &&
        tran.Tran->BindParam(2, SQL_PARAM_INPUT, gameAccountId, SQL_GUID, SQL_C_GUID, &gameAccountIdLen) &&
        tran.Tran->BindParam(3, SQL_PARAM_INPUT, (worldId != 0) ? &worldId : nullptr, SQL_SMALLINT, SQL_C_SSHORT,
                             &widLen) &&
        tran.Tran->BindParam(4, SQL_PARAM_INPUT, (pcdbid != 0) ? &pcdbid : nullptr, SQL_BIGINT, SQL_C_SBIGINT,
                             &pcdbidLen) &&
        tran.Tran->BindParam(5, SQL_PARAM_INPUT, &gameEventId, SQL_INTEGER, SQL_C_SLONG, &gameEventIdLen) &&
        tran.Tran->BindParam(6, SQL_PARAM_OUTPUT, outGameEventLogId, SQL_BIGINT, SQL_C_SBIGINT, &outLen))
    {
        if (!tran.Tran->Execute())
        {
            Log::Write(Log::LT_ERROR, SMARTCOUPONDB_FILE, 164,
                       L"[%s], failed to execute sql, reg-game-event-log, account-id:" GUID_FMT
                       L", wid:%d, pcdbid:0x%I64X, game-event-id:%d, query:%s",
                       L"db", GUID_ARGS(*gameAccountId), worldId, pcdbid, gameEventId, query);
            return false;
        }
        return *dbRetValue == 0;
    }
    Log::Write(Log::LT_ERROR, SMARTCOUPONDB_FILE, 175,
               L"[%s], failed to bind parameter, reg-game-event-log, account-id:" GUID_FMT
               L", wid:%d, pcdbid:0x%I64X, game-event-id:%d",
               L"db", GUID_ARGS(*gameAccountId), worldId, pcdbid, gameEventId);
    return false;
}

// 0x11130
bool SmartCouponDB::UpdateStatusToProcessFailure(int* dbRetValue, long long gameEventLogId, id128* gameAccountId,
                                                 short worldId, long long pcdbid, int gameEventId)
{
    *dbRetValue = 0;
    if (gameEventLogId == 0 || IsZeroGuid(gameAccountId) || worldId < 0 || pcdbid < 0 || gameEventId == 0)
    {
        Log::Write(Log::LT_ERROR, SMARTCOUPONDB_FILE, 188,
                   L"[%s], invalid parameter,update-process-fail, logid:%I64d, account-id:" GUID_FMT
                   L", wid:%d, pcdbid:0x%I64X, game-event-id:%d",
                   L"db", gameEventLogId, GUID_ARGS(*gameAccountId), worldId, pcdbid, gameEventId);
        return false;
    }
    AutoDbTran tran(1);
    if (tran.Tran == nullptr)
    {
        Log::Write(Log::LT_ERROR, SMARTCOUPONDB_FILE, 195,
                   L"[%s], failed to acquire transaction, dbId:%d, update-process-fail, logid:%I64d, account-id:" GUID_FMT
                   L", wid:%d, pcdbid:0x%I64X, game-event-id:%d",
                   L"db", 1, gameEventLogId, GUID_ARGS(*gameAccountId), worldId, pcdbid, gameEventId);
        return false;
    }
    wchar_t const* const query = L"{?=CALL dbo.usp_UpdateStatusToProcessFailure(?,?,?,?,?)}";
    if (!tran.Tran->Prepare(const_cast<wchar_t*>(query)))
    {
        Log::Write(Log::LT_ERROR, SMARTCOUPONDB_FILE, 201,
                   L"[%s], failed to prepare sql,update-process-fail, logid:%I64d, account-id:" GUID_FMT
                   L", wid:%d, pcdbid:0x%I64X, game-event-id:%d, query:%s",
                   L"db", gameEventLogId, GUID_ARGS(*gameAccountId), worldId, pcdbid, gameEventId, query);
        return false;
    }
    unsigned long long retLen = 0;
    unsigned long long logIdLen = 0;
    unsigned long long gameAccountIdLen = 0;
    unsigned long long widLen = (worldId != 0) ? 0 : kNullData;
    unsigned long long pcdbidLen = (pcdbid != 0) ? 0 : kNullData;
    unsigned long long gameEventIdLen = 0;
    if (tran.Tran->BindParam(1, SQL_PARAM_OUTPUT, dbRetValue, SQL_INTEGER, SQL_C_SLONG, &retLen) &&
        tran.Tran->BindParam(2, SQL_PARAM_INPUT, &gameEventLogId, SQL_BIGINT, SQL_C_SBIGINT, &logIdLen) &&
        tran.Tran->BindParam(3, SQL_PARAM_INPUT, gameAccountId, SQL_GUID, SQL_C_GUID, &gameAccountIdLen) &&
        tran.Tran->BindParam(4, SQL_PARAM_INPUT, (worldId != 0) ? &worldId : nullptr, SQL_SMALLINT, SQL_C_SSHORT,
                             &widLen) &&
        tran.Tran->BindParam(5, SQL_PARAM_INPUT, (pcdbid != 0) ? &pcdbid : nullptr, SQL_BIGINT, SQL_C_SBIGINT,
                             &pcdbidLen) &&
        tran.Tran->BindParam(6, SQL_PARAM_INPUT, &gameEventId, SQL_INTEGER, SQL_C_SLONG, &gameEventIdLen))
    {
        if (!tran.Tran->Execute())
        {
            Log::Write(Log::LT_ERROR, SMARTCOUPONDB_FILE, 222,
                       L"[%s], failed to execute sql,update-process-fail, logid:%I64d, account-id:" GUID_FMT
                       L", wid:%d, pcdbid:0x%I64X, game-event-id:%d, query:%s",
                       L"db", gameEventLogId, GUID_ARGS(*gameAccountId), worldId, pcdbid, gameEventId, query);
            return false;
        }
        return *dbRetValue == 0;
    }
    Log::Write(Log::LT_ERROR, SMARTCOUPONDB_FILE, 233,
               L"[%s], failed to bind parameter,update-process-fail, logid:%I64d, account-id:" GUID_FMT
               L", wid:%d, pcdbid:0x%I64X, game-event-id:%d",
               L"db", gameEventLogId, GUID_ARGS(*gameAccountId), worldId, pcdbid, gameEventId);
    return false;
}

// 0x117c0
bool SmartCouponDB::ProcessCharacterGameEventLog(int* dbRetValue, long long gameEventLogId, id128* gameAccountId,
                                                 short worldId, long long pcdbid, int gameEventId,
                                                 RetrievePublicationContext* outPublicationContext)
{
    *dbRetValue = 0;
    if (gameEventLogId <= 0 || IsZeroGuid(gameAccountId) || worldId <= 0 || pcdbid <= 0 || gameEventId <= 0)
    {
        Log::Write(Log::LT_ERROR, SMARTCOUPONDB_FILE, 246,
                   L"[%s], invalid parameter,process-char, logid:%I64d, account-id:" GUID_FMT
                   L", wid:%d, pcdbid:0x%I64X, game-event-id:%d",
                   L"db", gameEventLogId, GUID_ARGS(*gameAccountId), worldId, pcdbid, gameEventId);
        return false;
    }
    AutoDbTran tran(1);
    if (tran.Tran == nullptr)
    {
        Log::Write(Log::LT_ERROR, SMARTCOUPONDB_FILE, 253,
                   L"[%s], failed to acquire transaction, dbId:%d, process-char, logid:%I64d, account-id:" GUID_FMT
                   L", wid:%d, pcdbid:0x%I64X, game-event-id:%d",
                   L"db", 1, gameEventLogId, GUID_ARGS(*gameAccountId), worldId, pcdbid, gameEventId);
        return false;
    }
    wchar_t const* const query = L"{?=CALL dbo.usp_ProcessCharacterGameEventLog(?,?,?,?,?)}";
    if (!tran.Tran->Prepare(const_cast<wchar_t*>(query)))
    {
        Log::Write(Log::LT_ERROR, SMARTCOUPONDB_FILE, 259,
                   L"[%s], failed to prepare sql,process-char, logid:%I64d, account-id:" GUID_FMT
                   L", wid:%d, pcdbid:0x%I64X, game-event-id:%d, query:%s",
                   L"db", gameEventLogId, GUID_ARGS(*gameAccountId), worldId, pcdbid, gameEventId, query);
        return false;
    }
    unsigned long long retLen = 0;
    unsigned long long logIdLen = 0;
    unsigned long long gameAccountIdLen = 0;
    unsigned long long widLen = 0;
    unsigned long long pcdbidLen = 0;
    unsigned long long gameEventIdLen = 0;
    PublicationInfo publicationInfo;
    long long publicationLen[9] = {0};
    if (tran.Tran->BindParam(1, SQL_PARAM_OUTPUT, dbRetValue, SQL_INTEGER, SQL_C_SLONG, &retLen) &&
        tran.Tran->BindParam(2, SQL_PARAM_INPUT, &gameEventLogId, SQL_BIGINT, SQL_C_SBIGINT, &logIdLen) &&
        tran.Tran->BindParam(3, SQL_PARAM_INPUT, gameAccountId, SQL_GUID, SQL_C_GUID, &gameAccountIdLen) &&
        tran.Tran->BindParam(4, SQL_PARAM_INPUT, &worldId, SQL_SMALLINT, SQL_C_SSHORT, &widLen) &&
        tran.Tran->BindParam(5, SQL_PARAM_INPUT, &pcdbid, SQL_BIGINT, SQL_C_SBIGINT, &pcdbidLen) &&
        tran.Tran->BindParam(6, SQL_PARAM_INPUT, &gameEventId, SQL_INTEGER, SQL_C_SLONG, &gameEventIdLen) &&
        tran.Tran->BindCol(1, &publicationInfo.publicationId, SQL_C_SBIGINT, &publicationLen[0]) &&
        tran.Tran->BindCol(2, &publicationInfo.gameAccountId, SQL_C_GUID, &publicationLen[1]) &&
        tran.Tran->BindCol(3, &publicationInfo.couponEventId, SQL_C_SLONG, &publicationLen[4]))
    {
        if (!tran.Tran->Execute())
        {
            Log::Write(Log::LT_ERROR, SMARTCOUPONDB_FILE, 290,
                       L"[%s], failed to execute sql,process-char, logid:%I64d, account-id:" GUID_FMT
                       L", wid:%d, pcdbid:0x%I64X, game-event-id:%d, query:%s",
                       L"db", gameEventLogId, GUID_ARGS(*gameAccountId), worldId, pcdbid, gameEventId, query);
            return false;
        }
        for (;;)
        {
            memset(&publicationInfo, 0, sizeof(publicationInfo));
            int const result = tran.Tran->Fetch(0);  // ❓ argument
            if (result == -1)
            {
                Log::Write(Log::LT_ERROR, SMARTCOUPONDB_FILE, 302,
                           L"[%s], failed to fetch,process-char, logid:%I64d, account-id:" GUID_FMT
                           L", wid:%d, pcdbid:0x%I64X, game-event-id:%d",
                           L"db", gameEventLogId, GUID_ARGS(*gameAccountId), worldId, pcdbid, gameEventId);
                return false;
            }
            if (result == 0)
                break;
            if (publicationLen[0] == -1 || publicationLen[1] == -1 || publicationLen[4] == -1)
                Log::Write(Log::LT_ERROR, SMARTCOUPONDB_FILE, 314,
                           L"[%s], invalid db data,process-char, logid:%I64d, account-id:" GUID_FMT
                           L", wid:%d, pcdbid:0x%I64X, game-event-id:%d, publicationdLen:0x%I64X, "
                           L"gameAccountIdLen:0x%I64X, couponEventIdLen:0x%I64X",
                           L"db", gameEventLogId, GUID_ARGS(*gameAccountId), worldId, pcdbid, gameEventId,
                           publicationLen[0], publicationLen[1], publicationLen[4]);
            else
                outPublicationContext->AddPublicationInfo(&publicationInfo);
        }
        return *dbRetValue == 0;
    }
    Log::Write(Log::LT_ERROR, SMARTCOUPONDB_FILE, 329,
               L"[%s], failed to bind parameter,process-char, logid:%I64d, account-id:" GUID_FMT
               L", wid:%d, pcdbid:0x%I64X, game-event-id:%d",
               L"db", gameEventLogId, GUID_ARGS(*gameAccountId), worldId, pcdbid, gameEventId);
    return false;
}

// 0x12170
bool SmartCouponDB::ProcessAccountGameEventLog(int* dbRetValue, long long gameEventLogId, id128* gameAccountId,
                                               int gameEventId, RetrievePublicationContext* outPublicationContext)
{
    *dbRetValue = 0;
    if (gameEventLogId <= 0 || IsZeroGuid(gameAccountId) || gameEventId <= 0)
    {
        Log::Write(Log::LT_ERROR, SMARTCOUPONDB_FILE, 342,
                   L"[%s], invalid parameter,process-acc, logid:%I64d, account-id:" GUID_FMT L", game-event-id:%d",
                   L"db", gameEventLogId, GUID_ARGS(*gameAccountId), gameEventId);
        return false;
    }
    AutoDbTran tran(1);
    if (tran.Tran == nullptr)
    {
        Log::Write(Log::LT_ERROR, SMARTCOUPONDB_FILE, 349,
                   L"[%s], failed to acquire transaction, dbId:%d, process-acc, logid:%I64d, account-id:" GUID_FMT
                   L", game-event-id:%d",
                   L"db", 1, gameEventLogId, GUID_ARGS(*gameAccountId), gameEventId);
        return false;
    }
    wchar_t const* const query = L"{?=CALL dbo.usp_ProcessAccountGameEventLog(?,?,?)}";
    if (!tran.Tran->Prepare(const_cast<wchar_t*>(query)))
    {
        Log::Write(Log::LT_ERROR, SMARTCOUPONDB_FILE, 355,
                   L"[%s], failed to prepare sql,process-acc, logid:%I64d, account-id:" GUID_FMT
                   L", game-event-id:%d, query:%s",
                   L"db", gameEventLogId, GUID_ARGS(*gameAccountId), gameEventId, query);
        return false;
    }
    unsigned long long retLen = 0;
    unsigned long long logIdLen = 0;
    unsigned long long gameAccountIdLen = 0;
    unsigned long long gameEventIdLen = 0;
    PublicationInfo publicationInfo;
    long long publicationLen[9] = {0};
    if (tran.Tran->BindParam(1, SQL_PARAM_OUTPUT, dbRetValue, SQL_INTEGER, SQL_C_SLONG, &retLen) &&
        tran.Tran->BindParam(2, SQL_PARAM_INPUT, &gameEventLogId, SQL_BIGINT, SQL_C_SBIGINT, &logIdLen) &&
        tran.Tran->BindParam(3, SQL_PARAM_INPUT, gameAccountId, SQL_GUID, SQL_C_GUID, &gameAccountIdLen) &&
        tran.Tran->BindParam(4, SQL_PARAM_INPUT, &gameEventId, SQL_INTEGER, SQL_C_SLONG, &gameEventIdLen) &&
        tran.Tran->BindCol(1, &publicationInfo.publicationId, SQL_C_SBIGINT, &publicationLen[0]) &&
        tran.Tran->BindCol(2, &publicationInfo.gameAccountId, SQL_C_GUID, &publicationLen[1]) &&
        tran.Tran->BindCol(3, &publicationInfo.couponEventId, SQL_C_SLONG, &publicationLen[4]))
    {
        if (!tran.Tran->Execute())
        {
            Log::Write(Log::LT_ERROR, SMARTCOUPONDB_FILE, 382,
                       L"[%s], failed to execute sql,process-acc, logid:%I64d, account-id:" GUID_FMT
                       L", game-event-id:%d, query:%s",
                       L"db", gameEventLogId, GUID_ARGS(*gameAccountId), gameEventId, query);
            return false;
        }
        for (;;)
        {
            memset(&publicationInfo, 0, sizeof(publicationInfo));
            int const result = tran.Tran->Fetch(0);  // ❓ argument
            if (result == -1)
            {
                Log::Write(Log::LT_ERROR, SMARTCOUPONDB_FILE, 394,
                           L"[%s], failed to fetch,process-acc, logid:%I64d, account-id:" GUID_FMT
                           L", game-event-id:%d",
                           L"db", gameEventLogId, GUID_ARGS(*gameAccountId), gameEventId);
                return false;
            }
            if (result == 0)
                break;
            if (publicationLen[0] == -1 || publicationLen[1] == -1 || publicationLen[4] == -1)
                Log::Write(Log::LT_ERROR, SMARTCOUPONDB_FILE, 406,
                           L"[%s], invalid db data,process-acc, logid:%I64d, account-id:" GUID_FMT
                           L", game-event-id:%d, publicationdLen:0x%I64X, gameAccountIdLen:0x%I64X, "
                           L"couponEventIdLen:0x%I64X",
                           L"db", gameEventLogId, GUID_ARGS(*gameAccountId), gameEventId, publicationLen[0],
                           publicationLen[1], publicationLen[4]);
            else
                outPublicationContext->AddPublicationInfo(&publicationInfo);
        }
        return *dbRetValue == 0;
    }
    Log::Write(Log::LT_ERROR, SMARTCOUPONDB_FILE, 421,
               L"[%s], failed to bind parameter,process-acc, logid:%I64d, account-id:" GUID_FMT L", game-event-id:%d",
               L"db", gameEventLogId, GUID_ARGS(*gameAccountId), gameEventId);
    return false;
}

// 0x129c0
bool SmartCouponDB::UpdateStatusToPublicationSuccess(int* dbRetValue, long long publicationId,
                                                     id128 const* gameAccountId, int couponEventId,
                                                     long long const* acceptTid)
{
    *dbRetValue = 0;
    long long const receiptId = (acceptTid != nullptr) ? *acceptTid : 0;
    wchar_t const* const receiptNull = (acceptTid != nullptr) ? L"" : L"(NULL)";
    if (publicationId == 0 || IsZeroGuid(gameAccountId) || couponEventId == 0)
    {
        Log::Write(Log::LT_ERROR, SMARTCOUPONDB_FILE, 434,
                   L"[%s], invalid parameter, update-publication-succ, publication-id:%I64d, account-id:" GUID_FMT
                   L", coupon-event-id:%d, receipt-id:%I64d%s",
                   L"db", publicationId, GUID_ARGS(*gameAccountId), couponEventId, receiptId, receiptNull);
        return false;
    }
    AutoDbTran tran(1);
    if (tran.Tran == nullptr)
    {
        Log::Write(Log::LT_ERROR, SMARTCOUPONDB_FILE, 441,
                   L"[%s], failed to acquire transaction, dbId:%d, update-publication-succ, publication-id:%I64d, "
                   L"account-id:" GUID_FMT L", coupon-event-id:%d, receipt-id:%I64d%s",
                   L"db", 1, publicationId, GUID_ARGS(*gameAccountId), couponEventId, receiptId, receiptNull);
        return false;
    }
    wchar_t const* const query = L"{?=CALL dbo.usp_UpdateStatusToPublicationSuccess(?,?,?,?)}";
    if (!tran.Tran->Prepare(const_cast<wchar_t*>(query)))
    {
        Log::Write(Log::LT_ERROR, SMARTCOUPONDB_FILE, 447,
                   L"[%s], failed to prepare sql, update-publication-succ, publication-id:%I64d, account-id:" GUID_FMT
                   L", coupon-event-id:%d, receipt-id:%I64d%s, query:%s",
                   L"db", publicationId, GUID_ARGS(*gameAccountId), couponEventId, receiptId, receiptNull, query);
        return false;
    }
    unsigned long long retLen = 0;
    unsigned long long publicationIdLen = 0;
    unsigned long long gameAccountIdLen = 0;
    unsigned long long couponEventIdLen = 0;
    unsigned long long receiptIdLen = (acceptTid != nullptr) ? 0 : kNullData;
    if (tran.Tran->BindParam(1, SQL_PARAM_OUTPUT, dbRetValue, SQL_INTEGER, SQL_C_SLONG, &retLen) &&
        tran.Tran->BindParam(2, SQL_PARAM_INPUT, &publicationId, SQL_BIGINT, SQL_C_SBIGINT, &publicationIdLen) &&
        tran.Tran->BindParam(3, SQL_PARAM_INPUT, const_cast<id128*>(gameAccountId), SQL_GUID, SQL_C_GUID,
                             &gameAccountIdLen) &&
        tran.Tran->BindParam(4, SQL_PARAM_INPUT, &couponEventId, SQL_INTEGER, SQL_C_SLONG, &couponEventIdLen) &&
        tran.Tran->BindParam(5, SQL_PARAM_INPUT, const_cast<long long*>(acceptTid), SQL_BIGINT, SQL_C_SBIGINT,
                             &receiptIdLen))
    {
        if (!tran.Tran->Execute())
        {
            Log::Write(Log::LT_ERROR, SMARTCOUPONDB_FILE, 468,
                       L"[%s], failed to execute sql, update-publication-succ, publication-id:%I64d, account-id:" GUID_FMT
                       L", coupon-event-id:%d, receipt-id:%I64d%s, query:%s",
                       L"db", publicationId, GUID_ARGS(*gameAccountId), couponEventId, receiptId, receiptNull, query);
            return false;
        }
        return *dbRetValue == 0;
    }
    Log::Write(Log::LT_ERROR, SMARTCOUPONDB_FILE, 479,
               L"[%s], failed to bind parameter, update-publication-succ, publication-id:%I64d, account-id:" GUID_FMT
               L", coupon-event-id:%d, receipt-id:%I64d%s",
               L"db", publicationId, GUID_ARGS(*gameAccountId), couponEventId, receiptId, receiptNull);
    return false;
}

// 0x13060
bool SmartCouponDB::UpdateStatusToPublicationFailure(int* dbRetValue, long long publicationId,
                                                     id128 const* gameAccountId, int couponEventId)
{
    *dbRetValue = 0;
    if (publicationId == 0 || IsZeroGuid(gameAccountId) || couponEventId == 0)
    {
        Log::Write(Log::LT_ERROR, SMARTCOUPONDB_FILE, 491,
                   L"[%s], invalid parameter, update-publication-fail, publication-id:%I64d, account-id:" GUID_FMT
                   L", coupon-event-id:%d",
                   L"db", publicationId, GUID_ARGS(*gameAccountId), couponEventId);
        return false;
    }
    AutoDbTran tran(1);
    if (tran.Tran == nullptr)
    {
        Log::Write(Log::LT_ERROR, SMARTCOUPONDB_FILE, 498,
                   L"[%s], failed to acquire transaction, dbId:%d, update-publication-fail, publication-id:%I64d, "
                   L"account-id:" GUID_FMT L", coupon-event-id:%d",
                   L"db", 1, publicationId, GUID_ARGS(*gameAccountId), couponEventId);
        return false;
    }
    wchar_t const* const query = L"{?=CALL dbo.usp_UpdateStatusToPublicationFailure(?,?,?)}";
    if (!tran.Tran->Prepare(const_cast<wchar_t*>(query)))
    {
        Log::Write(Log::LT_ERROR, SMARTCOUPONDB_FILE, 504,
                   L"[%s], failed to prepare sql, update-publication-fail, publication-id:%I64d, account-id:" GUID_FMT
                   L", coupon-event-id:%d, query:%s",
                   L"db", publicationId, GUID_ARGS(*gameAccountId), couponEventId, query);
        return false;
    }
    unsigned long long retLen = 0;
    unsigned long long publicationIdLen = 0;
    unsigned long long gameAccountIdLen = 0;
    unsigned long long couponEventIdLen = 0;
    if (tran.Tran->BindParam(1, SQL_PARAM_OUTPUT, dbRetValue, SQL_INTEGER, SQL_C_SLONG, &retLen) &&
        tran.Tran->BindParam(2, SQL_PARAM_INPUT, &publicationId, SQL_BIGINT, SQL_C_SBIGINT, &publicationIdLen) &&
        tran.Tran->BindParam(3, SQL_PARAM_INPUT, const_cast<id128*>(gameAccountId), SQL_GUID, SQL_C_GUID,
                             &gameAccountIdLen) &&
        tran.Tran->BindParam(4, SQL_PARAM_INPUT, &couponEventId, SQL_INTEGER, SQL_C_SLONG, &couponEventIdLen))
    {
        if (!tran.Tran->Execute())
        {
            Log::Write(Log::LT_ERROR, SMARTCOUPONDB_FILE, 521,
                       L"[%s], failed to execute sql, update-publication-fail, publication-id:%I64d, account-id:" GUID_FMT
                       L", coupon-event-id:%d, query:%s",
                       L"db", publicationId, GUID_ARGS(*gameAccountId), couponEventId, query);
            return false;
        }
        return *dbRetValue == 0;
    }
    Log::Write(Log::LT_ERROR, SMARTCOUPONDB_FILE, 532,
               L"[%s], failed to bind parameter, update-publication-fail, publication-id:%I64d, account-id:" GUID_FMT
               L", coupon-event-id:%d",
               L"db", publicationId, GUID_ARGS(*gameAccountId), couponEventId);
    return false;
}

// ❓ Shared body of LoadGameEventLogList and LoadRetryReadyGameEventLogList. The compiler made two copies.
static bool loadEventLogList(int* dbRetValue, RetrieveEventLogContext* outEventLogContext, wchar_t const* tag,
                             wchar_t const* query, int lineAcquire, int linePrepare, int lineExecute, int lineFetch,
                             int lineInvalid, int lineBind)
{
    *dbRetValue = 0;
    AutoDbTran tran(1);
    if (tran.Tran == nullptr)
    {
        Log::Write(Log::LT_ERROR, SMARTCOUPONDB_FILE, lineAcquire,
                   L"[%s], failed to acquire transaction, dbId:%d,  %s %s", L"db", 1, tag, kEmpty);
        return false;
    }
    if (!tran.Tran->Prepare(const_cast<wchar_t*>(query)))
    {
        Log::Write(Log::LT_ERROR, SMARTCOUPONDB_FILE, linePrepare, L"[%s], failed to prepare sql, %s %s, query:%s",
                   L"db", tag, kEmpty, query);
        return false;
    }
    unsigned long long retLen = 0;
    EventLogInfo eventLogInfo;
    long long eventLogLen[5] = {0};
    if (tran.Tran->BindParam(1, SQL_PARAM_OUTPUT, dbRetValue, SQL_INTEGER, SQL_C_SLONG, &retLen) &&
        tran.Tran->BindCol(1, &eventLogInfo.logId, SQL_C_SBIGINT, &eventLogLen[0]) &&
        tran.Tran->BindCol(2, &eventLogInfo.gameAccountId, SQL_C_GUID, &eventLogLen[1]) &&
        tran.Tran->BindCol(3, &eventLogInfo.wid, SQL_C_SSHORT, &eventLogLen[2]) &&
        tran.Tran->BindCol(4, &eventLogInfo.pcdbid, SQL_C_SBIGINT, &eventLogLen[3]) &&
        tran.Tran->BindCol(5, &eventLogInfo.gameEventId, SQL_C_SLONG, &eventLogLen[4]))
    {
        if (!tran.Tran->Execute())
        {
            Log::Write(Log::LT_ERROR, SMARTCOUPONDB_FILE, lineExecute, L"[%s], failed to execute sql, %s %s, query:%s",
                       L"db", tag, kEmpty, query);
            return false;
        }
        for (;;)
        {
            memset(&eventLogInfo, 0, sizeof(eventLogInfo));
            int const result = tran.Tran->Fetch(0);  // ❓ argument
            if (result == -1)
            {
                Log::Write(Log::LT_ERROR, SMARTCOUPONDB_FILE, lineFetch, L"[%s], failed to fetch, %s %s", L"db", tag,
                           kEmpty);
                return false;
            }
            if (result == 0)
                break;
            if (eventLogLen[0] == -1 || eventLogLen[1] == -1 || eventLogLen[4] == -1)
                Log::Write(Log::LT_ERROR, SMARTCOUPONDB_FILE, lineInvalid,
                           L"[%s], invalid db data, %s %s, logIdLen:0x%I64X, gameAccountIdLen:0x%I64X, "
                           L"widLen:0x%I64X, pcIdLen:0x%I64X, EventIdLen:0x%I64X",
                           L"db", tag, kEmpty, eventLogLen[0], eventLogLen[1], eventLogLen[2], eventLogLen[3],
                           eventLogLen[4]);
            else
                outEventLogContext->AddEventLogInfo(&eventLogInfo);
        }
        return *dbRetValue == 0;
    }
    Log::Write(Log::LT_ERROR, SMARTCOUPONDB_FILE, lineBind, L"[%s], failed to bind parameter, %s %s", L"db", tag,
               kEmpty);
    return false;
}

// 0x13620
bool SmartCouponDB::LoadGameEventLogList(int* dbRetValue, RetrieveEventLogContext* outEventLogContext)
{
    // ❓ The original has the tag inside each format text ("load-game-event-log %s"). The output text is the same.
    return loadEventLogList(dbRetValue, outEventLogContext, L"load-game-event-log",
                            L"{?=CALL dbo.usp_LoadGameEventLogList}", 600, 606, 628, 640, 655, 670);
}

// 0x13a30
bool SmartCouponDB::LoadCouponPublicationList(int* dbRetValue, RetrievePublicationContext* outPublicationContext)
{
    *dbRetValue = 0;
    AutoDbTran tran(1);
    if (tran.Tran == nullptr)
    {
        Log::Write(Log::LT_ERROR, SMARTCOUPONDB_FILE, 685,
                   L"[%s], failed to acquire transaction, dbId:%d,  load-coupon-publication %s", L"db", 1, kEmpty);
        return false;
    }
    wchar_t const* const query = L"{?=CALL dbo.usp_LoadCouponPublicationList}";
    if (!tran.Tran->Prepare(const_cast<wchar_t*>(query)))
    {
        Log::Write(Log::LT_ERROR, SMARTCOUPONDB_FILE, 691,
                   L"[%s], failed to prepare sql, load-coupon-publication %s, query:%s", L"db", kEmpty, query);
        return false;
    }
    unsigned long long retLen = 0;
    PublicationInfo publicationInfo;
    long long publicationLen[5] = {0};
    if (tran.Tran->BindParam(1, SQL_PARAM_OUTPUT, dbRetValue, SQL_INTEGER, SQL_C_SLONG, &retLen) &&
        tran.Tran->BindCol(1, &publicationInfo.publicationId, SQL_C_SBIGINT, &publicationLen[0]) &&
        tran.Tran->BindCol(2, &publicationInfo.gameAccountId, SQL_C_GUID, &publicationLen[1]) &&
        tran.Tran->BindCol(3, &publicationInfo.couponEventId, SQL_C_SLONG, &publicationLen[4]))
    {
        if (!tran.Tran->Execute())
        {
            Log::Write(Log::LT_ERROR, SMARTCOUPONDB_FILE, 711,
                       L"[%s], failed to execute sql, load-coupon-publication %s, query:%s", L"db", kEmpty, query);
            return false;
        }
        for (;;)
        {
            memset(&publicationInfo, 0, sizeof(publicationInfo));
            int const result = tran.Tran->Fetch(0);  // ❓ argument
            if (result == -1)
            {
                Log::Write(Log::LT_ERROR, SMARTCOUPONDB_FILE, 723, L"[%s], failed to fetch, load-coupon-publication %s",
                           L"db", kEmpty);
                return false;
            }
            if (result == 0)
                break;
            if (publicationLen[0] == -1 || publicationLen[1] == -1 || publicationLen[4] == -1)
                Log::Write(Log::LT_ERROR, SMARTCOUPONDB_FILE, 735,
                           L"[%s], invalid db data, load-coupon-publication %s, publicationdLen:0x%I64X, "
                           L"gameAccountIdLen:0x%I64X, couponEventIdLen:0x%I64X",
                           L"db", kEmpty, publicationLen[0], publicationLen[1], publicationLen[4]);
            else
                outPublicationContext->AddPublicationInfo(&publicationInfo);
        }
        return *dbRetValue == 0;
    }
    Log::Write(Log::LT_ERROR, SMARTCOUPONDB_FILE, 750, L"[%s], failed to bind parameter, load-coupon-publication %s",
               L"db", kEmpty);
    return false;
}

// 0x13dd0
bool SmartCouponDB::LoadSingleCouponPublication(int* dbRetValue, long long publicationId, id128* gameAccountId,
                                                int* outCouponEventId)
{
    *dbRetValue = 0;
    *outCouponEventId = 0;
    AutoDbTran tran(1);
    if (tran.Tran == nullptr)
    {
        Log::Write(Log::LT_ERROR, SMARTCOUPONDB_FILE, 766,
                   L"[%s], failed to acquire transaction, dbId:%d, load single coupon publication, acc:" GUID_FMT
                   L", publication-id:%I64d",
                   L"db", 1, GUID_ARGS(*gameAccountId), publicationId);
        return false;
    }
    wchar_t const* const query = L"{?=CALL dbo.usp_LoadSingleCouponPublication(?,?)}";
    if (!tran.Tran->Prepare(const_cast<wchar_t*>(query)))
    {
        Log::Write(Log::LT_ERROR, SMARTCOUPONDB_FILE, 772,
                   L"[%s], failed to prepare sql,load single coupon publication, acc:" GUID_FMT
                   L", publication-id:%I64d, query:%s",
                   L"db", GUID_ARGS(*gameAccountId), publicationId, query);
        return false;
    }
    unsigned long long retLen = 0;
    unsigned long long publicationIdLen = 0;
    unsigned long long gameAccountIdLen = 0;
    PublicationInfo publicationInfo;
    long long publicationLen[5] = {0};
    if (tran.Tran->BindParam(1, SQL_PARAM_OUTPUT, dbRetValue, SQL_INTEGER, SQL_C_SLONG, &retLen) &&
        tran.Tran->BindParam(2, SQL_PARAM_INPUT, &publicationId, SQL_BIGINT, SQL_C_SBIGINT, &publicationIdLen) &&
        tran.Tran->BindParam(3, SQL_PARAM_INPUT, gameAccountId, SQL_GUID, SQL_C_GUID, &gameAccountIdLen) &&
        tran.Tran->BindCol(1, &publicationInfo.publicationId, SQL_C_SBIGINT, &publicationLen[0]) &&
        tran.Tran->BindCol(2, &publicationInfo.gameAccountId, SQL_C_GUID, &publicationLen[1]) &&
        tran.Tran->BindCol(3, &publicationInfo.couponEventId, SQL_C_SLONG, &publicationLen[4]))
    {
        if (!tran.Tran->Execute())
        {
            Log::Write(Log::LT_ERROR, SMARTCOUPONDB_FILE, 796,
                       L"[%s], failed to execute sql,load single coupon publication, acc:" GUID_FMT
                       L", publication-id:%I64d, query:%s",
                       L"db", GUID_ARGS(*gameAccountId), publicationId, query);
            return false;
        }
        for (;;)
        {
            memset(&publicationInfo, 0, sizeof(publicationInfo));
            int const result = tran.Tran->Fetch(0);  // ❓ argument
            if (result == -1)
            {
                Log::Write(Log::LT_ERROR, SMARTCOUPONDB_FILE, 808,
                           L"[%s], failed to fetch,load single coupon publication, acc:" GUID_FMT
                           L", publication-id:%I64d",
                           L"db", GUID_ARGS(*gameAccountId), publicationId);
                return false;
            }
            if (result == 0)
                break;
            if (publicationLen[0] == -1 || publicationLen[1] == -1 || publicationLen[4] == -1)
            {
                Log::Write(Log::LT_ERROR, SMARTCOUPONDB_FILE, 820,
                           L"[%s], invalid db data,load single coupon publication, acc:" GUID_FMT
                           L", publication-id:%I64d, publicationdLen:0x%I64X, gameAccountIdLen:0x%I64X, "
                           L"couponEventIdLen:0x%I64X",
                           L"db", GUID_ARGS(*gameAccountId), publicationId, publicationLen[0], publicationLen[1],
                           publicationLen[4]);
                continue;
            }
            *outCouponEventId = publicationInfo.couponEventId;
            if (publicationInfo.couponEventId <= 0)
                Log::Write(Log::LT_DEBUG, SMARTCOUPONDB_FILE, 829,
                           L"[%s], invalid coupon-event-id,load single coupon publication, acc:" GUID_FMT
                           L", publication-id:%I64d, publication-id:%I64d, acc:" GUID_FMT L",coupon-event-id:%d",
                           L"db", GUID_ARGS(*gameAccountId), publicationId, publicationInfo.publicationId,
                           GUID_ARGS(publicationInfo.gameAccountId), publicationInfo.couponEventId);
        }
        return *dbRetValue == 0;
    }
    Log::Write(Log::LT_ERROR, SMARTCOUPONDB_FILE, 845,
               L"[%s], failed to bind parameter,load single coupon publication, acc:" GUID_FMT
               L", publication-id:%I64d",
               L"db", GUID_ARGS(*gameAccountId), publicationId);
    return false;
}

// 0x145f0
bool SmartCouponDB::LoadRetryReadyGameEventLogList(int* dbRetValue, RetrieveEventLogContext* outEventLogContext)
{
    return loadEventLogList(dbRetValue, outEventLogContext, L"load-retryready-game-event-log",
                            L"{?=CALL dbo.usp_LoadRetryReadyGameEventLogList}", 860, 866, 888, 900, 915, 930);
}
