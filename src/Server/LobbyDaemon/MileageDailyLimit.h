// MileageDailyLimit.obj (LobbyDaemon PDB, 2019 + PDB). Layout from tools/pdbcls.py LobbyDaemon MileageDailyLimit.
// LIFT: header layout only (fix7). The function bodies are still LIFT_STUB.
#pragma once
#include <stddef.h>
#include "Mileage.h"

// LIFT: PDB layout (sizeof 0x30, MileageLimit base). The PDB ctor MileageDailyLimit(long long, long long, long long,
// long) and the virtual dtor have no own symbol in the lift scope. They are not declared.
class MileageDailyLimit : public MileageLimit
{
protected:
    virtual long long getBoundary(long long);  // 0x62560

private:
    friend struct MileageDailyLimitLayoutCheck;  // LIFT: checks the private PDB offsets.

    long _reset;  // +0x20
    long long _current;  // +0x28
};
static_assert(sizeof(MileageDailyLimit) == 0x30, "sizeof MileageDailyLimit");
struct MileageDailyLimitLayoutCheck
{
    static_assert(offsetof(MileageDailyLimit, _reset) == 0x20, "MileageDailyLimit::_reset");
    static_assert(offsetof(MileageDailyLimit, _current) == 0x28, "MileageDailyLimit::_current");
};
