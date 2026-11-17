// IdleWatcher.obj (LobbyGate PDB). Layouts from include/pdb/LobbyGate/types.h.
#pragma once
#include <stddef.h>
#include <string.h>
#include "Thread.h"

class Port;
class Session;
class IdleWatcher;

class IdleStateTable
{
public:
    IdleStateTable() : _port(nullptr), _maxIdleTime(60), _disconnect(false), _size(0), _table(nullptr) {}  // LIFT: inlined in Create (0x24CD0)

    static IdleStateTable* Create(Port* port, int size, long maxIdleTime, bool disconnect);  // 0x24CD0

protected:
    void scan();  // 0x24DF0

public:
    // 2 bits for each session. 4 sessions in one byte.
    static unsigned char const STATE_MASK[4];  // 0x6D55C

    Port* _port;
    long _maxIdleTime;
    bool _disconnect;
    int _size;
    unsigned char* _table;

    friend class IdleWatcher;
    friend class Session;
};
static_assert(sizeof(IdleStateTable) == 0x20, "sizeof IdleStateTable");
static_assert(offsetof(IdleStateTable, _maxIdleTime) == 0x8, "IdleStateTable::_maxIdleTime");
static_assert(offsetof(IdleStateTable, _disconnect) == 0xC, "IdleStateTable::_disconnect");
static_assert(offsetof(IdleStateTable, _size) == 0x10, "IdleStateTable::_size");
static_assert(offsetof(IdleStateTable, _table) == 0x18, "IdleStateTable::_table");

class IdleWatcher : public Thread
{
public:
    IdleWatcher()  // LIFT: inlined in Network::SetMaxIdleTime (0x20860)
    {
        _maxFrozenSeconds = 60;
        memset(_table, 0, sizeof(_table));
    }
    virtual ~IdleWatcher();           // slot 0 0x30B50 (vftable 0x845C8)
    virtual wchar_t const* Name();    // 0x24CC0
    virtual void run();               // 0x24FF0

    IdleStateTable* _table[24];
};
static_assert(sizeof(IdleWatcher) == 0xF0, "sizeof IdleWatcher");
static_assert(offsetof(IdleWatcher, _table) == 0x30, "IdleWatcher::_table");
