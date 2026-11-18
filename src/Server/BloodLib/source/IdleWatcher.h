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

    enum
    {
        NOT_AVAILABLE = 0,
        BUSY = 1,
        IDLE = 2,
        CLOSE_CANDIDATE = 3,
    };

    // PDB union IdleStateTable::Pos (size 8): port +0, bit +2, index +4.
    union Pos
    {
        __int64 pos;
        struct
        {
            short port;
            short bit;
            int index;
        };
    };

    // Inlined in each caller (CG Session::Accept 0xe7c0, Session::HandleFailedEvent 0xf5d0). The PDB has no
    // signature for these methods. ❓ parameter types
    static Pos GetPos(unsigned __int64 id)
    {
        Pos p;
        p.port = static_cast<short>(id >> 32);
        p.bit = static_cast<short>(id & 3);
        p.index = static_cast<int>(static_cast<unsigned int>(id) >> 2);
        return p;
    }
    // CG 0xf5d0 does not compute the port part: no Pos here.
    void SetNotAvailable(unsigned __int64 id)
    {
        setState(static_cast<unsigned int>(id) >> 2, static_cast<short>(id & 3), NOT_AVAILABLE);
    }
    Pos SetBusyWithPos(unsigned __int64 id)
    {
        Pos p = GetPos(id);
        setState(static_cast<unsigned int>(p.index), p.bit, BUSY);
        return p;
    }

private:
    // LIFT: no PDB name. Common body of the Set* methods. CG 0xf5d0 keeps "or (0 << shift)" for NOT_AVAILABLE.
    void setState(unsigned int index, short bit, unsigned char state)
    {
        _table[index] &= ~STATE_MASK[bit];
        _table[index] |= static_cast<unsigned char>(state << ((3 - bit) * 2));
    }

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
