// IdleWatcher (CacheGate PDB type). The PDB has no function of this class and no module for it.
// Network::Clear (0xCFD0) deletes it. Declarations only.
#pragma once
#include <stddef.h>
#include "Thread.h"

class IdleStateTable;

class IdleWatcher : public Thread
{
public:
    virtual ~IdleWatcher();
    virtual wchar_t const* Name();
    virtual void run();

    IdleStateTable* _table[24];
};
static_assert(sizeof(IdleWatcher) == 0xF0, "sizeof IdleWatcher");
static_assert(offsetof(IdleWatcher, _table) == 0x30, "IdleWatcher::_table");
