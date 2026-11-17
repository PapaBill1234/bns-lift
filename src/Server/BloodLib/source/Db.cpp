// Db.obj (SmartCouponDaemon PDB). Source file name from log strings: "source\Db.cpp".
#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <wchar.h>
#include <new>
#include <locale.h>
#include <stdarg.h>

// msvcr100 export. The Wine msvcrt headers do not declare it.
extern "C" int __cdecl _vswprintf_c_l(wchar_t* buffer, size_t count, wchar_t const* format, _locale_t locale, va_list args);
#include "Db.h"
#include "AlertSender.h"
#include "CrashHandler.h"
#include "Log.h"
#include "Memory.h"
#include "MemoryManager.h"

static wchar_t const kFile[] = L"source\\Db.cpp";

// Inlined crash macro. Db::Log hides the Log class in the Db scope, so use ::Log.
#define DB_ASSERT_CRASH(line)                                                     \
    do                                                                            \
    {                                                                             \
        ::Log::Write(::Log::LT_ERROR, kFile, line, L"== CRASH == ASSERT CRASH"); \
        AlertSender::Write(kFile, line, L"== CRASH == ASSERT CRASH");            \
        CrashHandler::MakeCrash("source\\Db.cpp", line, L"");                     \
    } while (0)

// LIFT: helper for the SQL result test. The original compares with SQL_SUCCESS and SQL_SUCCESS_WITH_INFO
// one by one, constant first (SmartCouponDaemon 0x21118: xor ecx,ecx; cmp cx,ax; mov ecx,1; cmp cx,ax).
// VS2010 gives `cmp cx,ax` only for the form `CONST == ret`. `ret == CONST` and `< 2` give `test ax,ax; cmp ax,1`.
static inline bool sqlSucceeded(SQLRETURN ret)
{
    return SQL_SUCCESS == ret || SQL_SUCCESS_WITH_INFO == ret;
}

void* Db::EnvHandle = nullptr;
Db* Db::Instance[41];

// 0x20690
// The compiler folds dbId to 1 (the only caller is SmartCouponDaemon::initialize).
bool Db::Initialize(unsigned int dbId, wchar_t const* dsn)
{
    if (dsn == nullptr)
        DB_ASSERT_CRASH(41);
    if (Instance[dbId] != nullptr)
        DB_ASSERT_CRASH(42);
    if (EnvHandle == nullptr && !initEnv())
        return false;
    void* mem = Memory::_Manager[2]->Alloc(sizeof(Db), kFile, 50);
    Db* db = mem != nullptr ? new (mem) Db() : nullptr;
    Instance[dbId] = db;
    db->TranList = nullptr;  // BUG: 0x20690 no null check after a failed Alloc.
    size_t const length = wcslen(dsn) + 1;
    wchar_t* copy = static_cast<wchar_t*>(BASE_MEMORY_MANAGER.Alloc(length * sizeof(wchar_t), kFile, 53));
    Instance[dbId]->Dsn = copy;
    wcsncpy(copy, dsn, wcslen(dsn) + 1);
    return true;
}

// LIFT: inlined in Clear. The member ~CriticalSection gives the EH state of the original.
inline Db::~Db()
{
    if (Dsn != nullptr)
    {
        BASE_MEMORY_MANAGER.Free(Dsn, kFile, 36);
        Dsn = nullptr;
    }
}

// 0x20810
void Db::Clear(unsigned int dbId)
{
    if (dbId == 0)
    {
        if (EnvHandle != nullptr)
        {
            SQLFreeHandle(SQL_HANDLE_ENV, EnvHandle);
            EnvHandle = nullptr;
        }
        for (unsigned int i = 1; i <= 40; ++i)
        {
            if (Instance[i] != nullptr)
                Clear(i);
        }
        return;
    }
    if (dbId > 40)
        return;
    Db* db = Instance[dbId];
    if (db == nullptr)
        return;
    db->clearList();
    db->~Db();
    Memory::_Manager[2]->Free(Instance[dbId], kFile, 78);
    Instance[dbId] = nullptr;
}

// 0x20910
// The compiler folds dbId to 1. The good path is first (SmartCouponDaemon 0x20910 logs at the end).
DbTransaction* Db::AllocTransaction(unsigned int dbId)
{
    if (Instance[dbId] != nullptr)
    {
        EnterCriticalSection(&Instance[dbId]->TranListLock.CS);
        DbTransaction* tran = nullptr;
        DbTransaction* tail = Instance[dbId]->TranList;
        if (tail != nullptr)
        {
            tran = tail->Next;
            if (tran->Next == tran)
                Instance[dbId]->TranList = nullptr;
            else
                tail->Next = tran->Next;
            tran->Next = nullptr;
        }
        LeaveCriticalSection(&Instance[dbId]->TranListLock.CS);
        if (tran == nullptr)
        {
            tran = static_cast<DbTransaction*>(Memory::_Manager[2]->Alloc(sizeof(DbTransaction), kFile, 96));
            if (tran != nullptr)
            {
                tran->DbId = dbId;
                tran->ConnHandle = nullptr;
                tran->StmtHandle = nullptr;
                tran->BoundCol = false;
                tran->BoundParam = false;
                tran->Next = nullptr;
            }
        }
        // BUG: 0x20910 no null check of tran after a failed Alloc.
        if (tran->initialize(Instance[dbId]->Dsn))
            return tran;
        ReleaseTransaction(tran);
        return nullptr;
    }
    ::Log::Write(::Log::LT_ERROR, kFile, 85, L"Invalid DB ID, %d, %p", dbId, nullptr);
    return nullptr;
}

// 0x20A30
void Db::ReleaseTransaction(DbTransaction* tran)
{
    if (tran == nullptr)
        return;
    unsigned int const dbId = tran->DbId;
    EnterCriticalSection(&Instance[dbId]->TranListLock.CS);
    if (tran->StmtHandle != nullptr)
    {
        SQLFreeStmt(tran->StmtHandle, SQL_CLOSE);
        if (tran->BoundCol)
        {
            SQLFreeStmt(tran->StmtHandle, SQL_UNBIND);
            tran->BoundCol = false;
        }
        if (tran->BoundParam)
        {
            SQLFreeStmt(tran->StmtHandle, SQL_RESET_PARAMS);
            tran->BoundParam = false;
        }
    }
    Db* db = Instance[dbId];
    if (db->TranList != nullptr)
    {
        tran->Next = db->TranList->Next;
        Instance[dbId]->TranList->Next = tran;
        Instance[dbId]->TranList = tran;
    }
    else
    {
        db->TranList = tran;
        Instance[dbId]->TranList->Next = Instance[dbId]->TranList;
    }
    LeaveCriticalSection(&Instance[dbId]->TranListLock.CS);
}

// 0x20B00
void Db::Log(short type, void* handle, wchar_t const* fmt, va_list args)
{
    wchar_t msg[520];
    SQLWCHAR sqlState[12];
    SQLWCHAR errorMsg[520];
    SQLINTEGER nativeError;
    SQLSMALLINT errMsgLen;

    if (fmt != nullptr && _vswprintf_c_l(msg, 512, fmt, nullptr, args) <= 0)  // SmartCouponDaemon 0x20B41 (import _vswprintf_c_l)
        msg[0] = 0;
    // BUG: 0x20B00 msg is not set when fmt is null.
    SQLSMALLINT record = 1;
    SQLRETURN ret = SQLGetDiagRecW(type, handle, record, sqlState, &nativeError, errorMsg, 512, &errMsgLen);
    while (SQL_NO_DATA != ret)
    {
        ++record;
        if (SQL_ERROR == ret)
            break;
        ::Log::Write(::Log::LT_ERROR, kFile, 186, L"%s: [%d] %s, %s", msg, nativeError, sqlState, errorMsg);
        ret = SQLGetDiagRecW(type, handle, record, sqlState, &nativeError, errorMsg, 512, &errMsgLen);
    }
}

// 0x20C70
void Db::errorLog(wchar_t const* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    Log(SQL_HANDLE_ENV, EnvHandle, fmt, args);
    va_end(args);
}

// 0x20CB0
bool Db::initEnv()
{
    if (EnvHandle != nullptr)
        return true;
    if (sqlSucceeded(SQLAllocHandle(SQL_HANDLE_ENV, nullptr, &EnvHandle)))
    {
        if (sqlSucceeded(SQLSetEnvAttr(EnvHandle, SQL_ATTR_ODBC_VERSION, reinterpret_cast<SQLPOINTER>(SQL_OV_ODBC3), 0)))
            return true;
        errorLog(L"SQLSetEnvAttr(SQL_ATTR_ODBC_VERSION, %d)", SQL_OV_ODBC3);
        if (EnvHandle != nullptr)
        {
            SQLFreeHandle(SQL_HANDLE_ENV, EnvHandle);
            EnvHandle = nullptr;
        }
        return false;
    }
    ::Log::Write(::Log::LT_ERROR, kFile, 207, L"SQLAllocHandle(SQL_HANDLE_ENV)");
    return false;
}

// 0x20D90
void Db::clearList()
{
    EnterCriticalSection(&TranListLock.CS);
    while (TranList != nullptr)
    {
        DbTransaction* tail = TranList;
        DbTransaction* tran = nullptr;
        if (tail != nullptr)
        {
            tran = tail->Next;
            if (tran->Next == tran)
                TranList = nullptr;
            else
                tail->Next = tran->Next;
            tran->Next = nullptr;
            tran->close();
        }
        Memory::_Manager[2]->Free(tran, kFile, 234);
    }
    LeaveCriticalSection(&TranListLock.CS);
}

// 0x20E40
bool DbTransaction::BindCol(unsigned int index, void* buffer, unsigned int varType, long long* result)
{
    if (StmtHandle != nullptr)
    {
        *result = SQL_NTS;
        if (sqlSucceeded(SQLBindCol(StmtHandle, static_cast<SQLUSMALLINT>(index), static_cast<SQLSMALLINT>(varType),
                                    buffer, 0, reinterpret_cast<SQLLEN*>(result))))
        {
            BoundCol = true;
            return true;
        }
        statmentErrorLog(L"SQLBindCol(%d, %d, %d, %p, %p)", index, varType, buffer, 0, result);
        return false;
    }
    ::Log::Write(::Log::LT_ERROR, kFile, 286, L"DbTransaction::BindCol(), Not initialized");
    return false;
}

// 0x20F20
bool DbTransaction::Prepare(wchar_t* query)
{
    if (StmtHandle == nullptr)
    {
        ::Log::Write(::Log::LT_ERROR, kFile, 327, L"DbTransaction::Prepare(), Not initialized");
        return false;
    }
    if (BoundParam)
    {
        ::Log::Write(::Log::LT_ERROR, kFile, 331, L"DbTransaction::Prepare(), Already called");
        return false;
    }
    if (sqlSucceeded(SQLPrepareW(StmtHandle, reinterpret_cast<SQLWCHAR*>(query), SQL_NTS)))
    {
        BoundParam = true;
        return true;
    }
    statmentErrorLog(L"SQLPrepare(%s)", query);
    return false;
}

// 0x20FD0
// LIFT: noinline. Without it LTCG moves the StmtHandle null check into the 10 SmartCouponDB callers
// (ours: "Not initialized" ref in SmartCouponDB::RegisterGameEventLog). The original keeps it here.
__declspec(noinline) bool DbTransaction::BindParam(unsigned int index, unsigned int inout, void* buffer,
                                                   unsigned int dbType, unsigned int varType,
                                                   unsigned long long* result)
{
    if (StmtHandle == nullptr)
    {
        ::Log::Write(::Log::LT_ERROR, kFile, 373, L"DbTransaction::BindParam(), Not initialized");
        return false;
    }
    if (!BoundParam)
    {
        ::Log::Write(::Log::LT_ERROR, kFile, 377, L"DbTransaction::BindParam(), Not prepared");
        return false;
    }
    if (sqlSucceeded(SQLBindParameter(StmtHandle, static_cast<SQLUSMALLINT>(index), static_cast<SQLSMALLINT>(inout),
                                      static_cast<SQLSMALLINT>(varType), static_cast<SQLSMALLINT>(dbType), 0, 0,
                                      buffer, 0, reinterpret_cast<SQLLEN*>(result))))
        return true;
    statmentErrorLog(L"SQLBindParameter(%d, %d, %d, %d, %d, %d, %p, %d, %p)", index, inout, varType, dbType, 0, 0,
                     buffer, 0, result);
    return false;
}

// 0x2d010 (PostOfficeDaemon)
bool DbTransaction::BindCol(unsigned int index, void* buffer, long long bufferSize, unsigned int varType,
                            unsigned long long* result)
{
    // The original calls Log::Write first in the call order (PostOfficeDaemon 0x2d010).
    if (StmtHandle == nullptr)
    {
        ::Log::Write(::Log::LT_ERROR, kFile, 286, L"DbTransaction::BindCol(), Not initialized");
        return false;
    }
    *result = static_cast<unsigned long long>(SQL_NTS);
    if (sqlSucceeded(SQLBindCol(StmtHandle, static_cast<SQLUSMALLINT>(index), static_cast<SQLSMALLINT>(varType),
                                buffer, bufferSize, reinterpret_cast<SQLLEN*>(result))))
    {
        BoundCol = true;
        return true;
    }
    statmentErrorLog(L"SQLBindCol(%d, %d, %d, %p, %p)", index, varType, buffer, bufferSize, result);
    return false;
}

// 0x2d190 (PostOfficeDaemon)
bool DbTransaction::BindParam(unsigned int index, unsigned int inout, void* buffer, long long bufferSize,
                              unsigned long long columnSize, int dbType, int varType, unsigned long long* result)
{
    if (StmtHandle == nullptr)
    {
        ::Log::Write(::Log::LT_ERROR, kFile, 373, L"DbTransaction::BindParam(), Not initialized");
        return false;
    }
    if (!BoundParam)
    {
        ::Log::Write(::Log::LT_ERROR, kFile, 377, L"DbTransaction::BindParam(), Not prepared");
        return false;
    }
    if (sqlSucceeded(SQLBindParameter(StmtHandle, static_cast<SQLUSMALLINT>(index), static_cast<SQLSMALLINT>(inout),
                                      static_cast<SQLSMALLINT>(varType), static_cast<SQLSMALLINT>(dbType), columnSize,
                                      0, buffer, bufferSize, reinterpret_cast<SQLLEN*>(result))))
        return true;
    statmentErrorLog(L"SQLBindParameter(%d, %d, %d, %d, %d, %d, %p, %d, %p)", index, inout, varType, dbType,
                     columnSize, 0, buffer, bufferSize, result);
    return false;
}

// 0x21100
bool DbTransaction::Execute()
{
    if (StmtHandle != nullptr && BoundParam)
    {
        if (sqlSucceeded(SQLExecute(StmtHandle)))
            return true;
        statmentErrorLog(L"SQLExecute()");
        return false;
    }
    ::Log::Write(::Log::LT_ERROR, kFile, 415, L"DbTransaction::Execute(), Not initialized");
    return false;
}

// 0x21180
// Returns 1 for a row, 0 for no row, -1 for an error. fetchCount is not used.
// The original has one statmentErrorLog call for SQL_ERROR and SQL_SUCCESS_WITH_INFO.
int DbTransaction::Fetch(int fetchCount)
{
    (void)fetchCount;
    if (StmtHandle == nullptr)
    {
        ::Log::Write(::Log::LT_ERROR, kFile, 433, L"DbTransaction::Fetch(), Not initialized");
        return -1;
    }
    SQLRETURN const ret = SQLFetch(StmtHandle);
    if (SQL_ERROR == ret)
    {
        statmentErrorLog(L"SQLFetch()");
        return -1;
    }
    if (SQL_SUCCESS_WITH_INFO == ret)
    {
        statmentErrorLog(L"SQLFetch()");
        return 1;
    }
    if (SQL_SUCCESS == ret)
        return 1;
    return 0;
}

// 0x21210
bool DbTransaction::initialize(wchar_t* dsn)
{
    void* const envHandle = Db::EnvHandle;
    if (ConnHandle != nullptr)
    {
        SQLINTEGER state;
        if (SQL_SUCCESS != SQLGetConnectAttrW(ConnHandle, SQL_ATTR_CONNECTION_DEAD, &state, 4, nullptr) ||
            SQL_CD_TRUE == state)
            close();
    }
    if (ConnHandle == nullptr)
    {
        if (!connect(envHandle, dsn))
            return false;
        if (!initStatement())
        {
            close();
            return false;
        }
    }
    return true;
}

// 0x212C0
bool DbTransaction::connect(void* envHandle, wchar_t* dsn)
{
    if (envHandle == nullptr)
    {
        ::Log::Write(::Log::LT_ERROR, kFile, 508, L"DbConnection::connect(%p), Environment is not initialized",
                     nullptr);
        return false;
    }
    if (ConnHandle != nullptr)
        return true;
    if (!sqlSucceeded(SQLAllocHandle(SQL_HANDLE_DBC, envHandle, &ConnHandle)))
    {
        Db::errorLog(L"SQLAllocHandle(SQL_HANDLE_DBC, %p)", envHandle);
        return false;
    }
    if (sqlSucceeded(SQLDriverConnectW(ConnHandle, nullptr, reinterpret_cast<SQLWCHAR*>(dsn), SQL_NTS, nullptr, 0,
                                       nullptr, SQL_DRIVER_NOPROMPT)))
        return true;
    connectionErrorLog(L"SQLDriverConnect()");
    SQLFreeHandle(SQL_HANDLE_DBC, ConnHandle);
    ConnHandle = nullptr;
    return false;
}

// 0x213D0
// LIFT: noinline. The original calls it from clearList (SmartCouponDaemon 0x20d90) and initialize.
__declspec(noinline) void DbTransaction::close()
{
    if (StmtHandle != nullptr)
    {
        SQLFreeStmt(StmtHandle, SQL_CLOSE);
        if (BoundCol)
        {
            SQLFreeStmt(StmtHandle, SQL_UNBIND);
            BoundCol = false;
        }
        if (BoundParam)
        {
            SQLFreeStmt(StmtHandle, SQL_RESET_PARAMS);
            BoundParam = false;
        }
        SQLFreeHandle(SQL_HANDLE_STMT, StmtHandle);
        StmtHandle = nullptr;
    }
    if (ConnHandle != nullptr)
    {
        SQLDisconnect(ConnHandle);
        SQLFreeHandle(SQL_HANDLE_DBC, ConnHandle);
        ConnHandle = nullptr;
    }
}

// 0x21460
bool DbTransaction::initStatement()
{
    if (ConnHandle == nullptr)
    {
        ::Log::Write(::Log::LT_ERROR, kFile, 550, L"DbConnection::initStatement(), Connection is not initialized");
        return false;
    }
    if (StmtHandle == nullptr)
    {
        if (!sqlSucceeded(SQLAllocHandle(SQL_HANDLE_STMT, ConnHandle, &StmtHandle)))
        {
            connectionErrorLog(L"SQLAllocHandle(SQL_HANDLE_STMT, %p)", ConnHandle);
            return false;
        }
        SQLSetStmtAttrW(StmtHandle, SQL_ATTR_CONCURRENCY, reinterpret_cast<SQLPOINTER>(SQL_CONCUR_READ_ONLY), 0);
        SQLSetStmtAttrW(StmtHandle, SQL_QUERY_TIMEOUT, reinterpret_cast<SQLPOINTER>(10), 0);
    }
    return true;
}

// 0x21520
void DbTransaction::connectionErrorLog(wchar_t const* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    Db::Log(SQL_HANDLE_DBC, ConnHandle, fmt, args);
    va_end(args);
}

// 0x21550
void DbTransaction::statmentErrorLog(wchar_t const* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    Db::Log(SQL_HANDLE_STMT, StmtHandle, fmt, args);
    va_end(args);
}

// 0x3c9f0 (MarketDealerDaemon)
long long Db::ConvertTime(tagTIMESTAMP_STRUCT const* ts)
{
    tm time;
    memset(&time, 0, sizeof(time));
    time.tm_year = ts->year - 1900;
    if (ts->month != 0)
        time.tm_mon = ts->month - 1;
    else
        time.tm_mon = 0;
    time.tm_mday = ts->day;
    time.tm_hour = ts->hour;
    time.tm_min = ts->minute;
    time.tm_sec = ts->second;
    return _mktime64(&time);
}
