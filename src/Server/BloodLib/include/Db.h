// Db.obj (SmartCouponDaemon PDB). Layouts from include/pdb/SmartCouponDaemon/types.h.
#pragma once
#include <stddef.h>
#include <stdarg.h>
#include "Lock.h"

class DbTransaction
{
public:
    // PDB names (SmartCouponDaemon S_REGREL32). LIFT: LTCG folded bufferSize (0x20E40, PDB offset 0).
    // LIFT: int index and varType as in the PDB symbol. VS2010 then forms the index from varType (lea edx,[r9+0xd], 0x13c19).
    bool BindCol(int index, void* buffer, int varType, long long* result);
    bool Prepare(wchar_t* query);
    // PDB names (SmartCouponDaemon S_REGREL32). LIFT: LTCG folded bufferSize, columnSize and
    // decimalDigits (0x20FD0, PDB offset 0). dbType is the SQL type. varType is the C type.
    bool BindParam(unsigned int index, unsigned int inout, void* buffer, unsigned int dbType,
                   unsigned int varType, unsigned long long* result);
    // Full PDB signatures (PostOfficeDaemon 0x2d010, 0x2d190). The SmartCouponDaemon copies above are LTCG forms.
    bool BindCol(unsigned int index, void* buffer, long long bufferSize, unsigned int varType,
                 unsigned long long* result);
    // LIFT: LTCG folded decimalDigits (0x2d190, PDB offset 0).
    bool BindParam(unsigned int index, unsigned int inout, void* buffer, long long bufferSize,
                   unsigned long long columnSize, int dbType, int varType, unsigned long long* result);
    bool Execute();
    int Fetch(int fetchCount);

    bool initialize(wchar_t* dsn);
    bool connect(void* envHandle, wchar_t* dsn);
    void close();
    bool initStatement();
    void connectionErrorLog(wchar_t const* fmt, ...);
    void statmentErrorLog(wchar_t const* fmt, ...);

    unsigned int DbId;
    void* ConnHandle;
    void* StmtHandle;
    bool BoundCol;
    bool BoundParam;
    DbTransaction* Next;
};
static_assert(sizeof(DbTransaction) == 0x28, "sizeof DbTransaction");
static_assert(offsetof(DbTransaction, StmtHandle) == 0x10, "DbTransaction::StmtHandle");
static_assert(offsetof(DbTransaction, BoundParam) == 0x19, "DbTransaction::BoundParam");
static_assert(offsetof(DbTransaction, Next) == 0x20, "DbTransaction::Next");

// LIFT: bind macro, no PDB name. The original has the DbTransaction::BindCol body (Db.cpp:286) inline at some call sites:
// SmartCouponDaemon loaders (first column only, 0x13620) and PostOfficeDaemon loaders (17 post columns, 0x14e50).
// VS2010 /LTCG does not give that choice from the source, thus the body is in the caller. The caller includes <sql.h> and Log.h.
#define DB_BIND_COL(tran, index, buffer, bufferSize, varType, result, errorLabel)                                     \
    do                                                                                                               \
    {                                                                                                                \
        if ((tran)->StmtHandle == nullptr)                                                                           \
        {                                                                                                            \
            ::Log::Write(::Log::LT_ERROR, L"source\\Db.cpp", 286, L"DbTransaction::BindCol(), Not initialized");     \
            goto errorLabel;                                                                                         \
        }                                                                                                            \
        *(result) = SQL_NTS;                                                                                         \
        SQLRETURN const bindRet_ = SQLBindCol((tran)->StmtHandle, static_cast<SQLUSMALLINT>(index),                  \
                                              static_cast<SQLSMALLINT>(varType), (buffer), (bufferSize),             \
                                              reinterpret_cast<SQLLEN*>(result));                                    \
        if (!(SQL_SUCCESS == bindRet_ || SQL_SUCCESS_WITH_INFO == bindRet_))                                         \
        {                                                                                                            \
            (tran)->statmentErrorLog(L"SQLBindCol(%d, %d, %d, %p, %p)", (index), static_cast<unsigned int>(varType), \
                                     (buffer), (bufferSize), (result));                                              \
            goto errorLabel;                                                                                         \
        }                                                                                                            \
        (tran)->BoundCol = true;                                                                                     \
    } while (0)

// LIFT: bind macro, no PDB name. Same as DB_BIND_COL, but a null StmtHandle goes to notInitLabel. The caller writes the
// "Not initialized" log one time at that label (PostOfficeDaemon 0x14e50: one log site for 17 columns).
#define DB_BIND_COL_NI(tran, index, buffer, bufferSize, varType, result, notInitLabel, errorLabel)                    \
    do                                                                                                               \
    {                                                                                                                \
        if ((tran)->StmtHandle == nullptr)                                                                           \
            goto notInitLabel;                                                                                       \
        *(result) = SQL_NTS;                                                                                         \
        SQLRETURN const bindRet_ = SQLBindCol((tran)->StmtHandle, static_cast<SQLUSMALLINT>(index),                  \
                                              static_cast<SQLSMALLINT>(varType), (buffer), (bufferSize),             \
                                              reinterpret_cast<SQLLEN*>(result));                                    \
        if (!(SQL_SUCCESS == bindRet_ || SQL_SUCCESS_WITH_INFO == bindRet_))                                         \
        {                                                                                                            \
            (tran)->statmentErrorLog(L"SQLBindCol(%d, %d, %d, %p, %p)", (index), static_cast<unsigned int>(varType), \
                                     (buffer), (bufferSize), (result));                                              \
            goto errorLabel;                                                                                         \
        }                                                                                                            \
        (tran)->BoundCol = true;                                                                                     \
    } while (0)

struct tagTIMESTAMP_STRUCT;

class Db
{
public:
    Db() : Dsn(nullptr), TranList(nullptr) {}  // LIFT: inlined in Initialize
    // LIFT: no PDB name seen. Inlined in Clear (PostOfficeDaemon 0x2c9e0, EH state #wind=1).
    // The body is in Db.cpp (only Clear uses it).
    inline ~Db();

    static bool Initialize(unsigned int dbId, wchar_t const* dsn);  // 0x20690 (dbId is folded to 1)
    static void Clear(unsigned int dbId);                           // 0x20810
    static DbTransaction* AllocTransaction(unsigned int dbId);      // 0x20910
    static void ReleaseTransaction(DbTransaction* tran);            // 0x20A30
    static void Log(short type, void* handle, wchar_t const* fmt, va_list args);  // 0x20B00
    static void errorLog(wchar_t const* fmt, ...);                  // 0x20C70
    static bool initEnv();                                          // 0x20CB0
    void clearList();                                               // 0x20D90
    static long long ConvertTime(tagTIMESTAMP_STRUCT const* ts);    // 0x3c9f0 (MarketDealerDaemon)
    static void ConvertTimeStamp(long long t, tagTIMESTAMP_STRUCT* ts);     // 0xe81f0 (LobbyDaemon)

    static void* EnvHandle;
    static Db* Instance[41];

    wchar_t* Dsn;
    CriticalSection TranListLock;
    DbTransaction* TranList;
};
static_assert(sizeof(Db) == 0x38, "sizeof Db");
