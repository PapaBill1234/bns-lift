// Db.obj (SmartCouponDaemon PDB). Layouts from include/pdb/SmartCouponDaemon/types.h.
#pragma once
#include <stddef.h>
#include <stdarg.h>
#include "Lock.h"

class DbTransaction
{
public:
    // ❓ The PDB parameter names do not match the role. BindCol: bufferSize is the C type.
    bool BindCol(unsigned int index, void* buffer, unsigned long long bufferSize, long long* varType);
    bool Prepare(wchar_t* query);
    // ❓ The PDB parameter names do not match the role. bufferSize is the SQL type, columnSize is the C type,
    // decimalDigits is the length/indicator pointer.
    bool BindParam(unsigned int index, unsigned int inout, void* buffer, unsigned long long bufferSize,
                   unsigned long long columnSize, unsigned long long* decimalDigits);
    // Full PDB signatures (PostOfficeDaemon 0x2d010, 0x2d190). The SmartCouponDaemon copies above are LTCG forms.
    bool BindCol(unsigned int index, void* buffer, long long bufferSize, unsigned int varType,
                 unsigned long long* result);
    bool BindParam(unsigned int index, unsigned int inout, void* buffer, long long bufferSize,
                   unsigned long long columnSize, int decimalDigits, int dbType, unsigned long long* varType);
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

class Db
{
public:
    Db() : Dsn(nullptr), TranList(nullptr) {}  // ❓ inlined in Initialize

    static bool Initialize(unsigned int dbId, wchar_t const* dsn);  // 0x20690 (dbId is folded to 1)
    static void Clear(unsigned int dbId);                           // 0x20810
    static DbTransaction* AllocTransaction(unsigned int dbId);      // 0x20910
    static void ReleaseTransaction(DbTransaction* tran);            // 0x20A30
    static void Log(short type, void* handle, wchar_t const* fmt, va_list args);  // 0x20B00
    static void errorLog(wchar_t const* fmt, ...);                  // 0x20C70
    static bool initEnv();                                          // 0x20CB0
    void clearList();                                               // 0x20D90

    static void* EnvHandle;
    static Db* Instance[41];

    wchar_t* Dsn;
    CriticalSection TranListLock;
    DbTransaction* TranList;
};
static_assert(sizeof(Db) == 0x38, "sizeof Db");
