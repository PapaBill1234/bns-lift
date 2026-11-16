// Db.obj (SmartCouponDaemon PDB). Layouts from include/pdb/SmartCouponDaemon/types.h.
#pragma once
#include <stddef.h>
#include "Lock.h"

class DbTransaction;

class Db
{
public:
    static bool Initialize(unsigned int dbId, wchar_t const* dsn);  // ❓ arguments
    static void Clear(unsigned int dbId);                           // ❓ address

    static void* EnvHandle;
    static Db* Instance[41];

    wchar_t* Dsn;
    CriticalSection TranListLock;
    DbTransaction* TranList;
};
static_assert(sizeof(Db) == 0x38, "sizeof Db");
