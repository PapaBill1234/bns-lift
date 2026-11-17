// RelayTimeContext.obj (PostOfficeDaemon PDB). Layouts from include/pdb/PostOfficeDaemon/types.h.
#pragma once
#include <stddef.h>
#include <map>
#include "Lock.h"
#include "StlMemory.h"

class RelayContext;

class CompoundKey
{
public:
    CompoundKey(unsigned long long relayTid, long long relayLimitTime)  // ❓ inlined
        : _relayTid(relayTid), _relayLimitTime(relayLimitTime) {}

    // ❓ inlined in the map code: the limit time first, then the tid.
    bool operator<(CompoundKey const& other) const
    {
        if (_relayLimitTime == other._relayLimitTime)
            return _relayTid < other._relayTid;
        return _relayLimitTime < other._relayLimitTime;
    }

    unsigned long long const _relayTid;
    long long const _relayLimitTime;
};
static_assert(sizeof(CompoundKey) == 0x10, "sizeof CompoundKey");

class RelayTimeContext
{
public:
    RelayTimeContext(unsigned long long relayTid, RelayContext* const relayContext);  // ❓ inlined in 0xb2a0
    ~RelayTimeContext();                                                             // 0xb080

    unsigned long long const _relayTid;
    RelayContext* _relayContext;
    bool _disuse;
};
static_assert(sizeof(RelayTimeContext) == 0x18, "sizeof RelayTimeContext");
static_assert(offsetof(RelayTimeContext, _disuse) == 0x10, "RelayTimeContext::_disuse");

class RelayTimeContextManager
{
public:
    typedef std::map<CompoundKey, RelayTimeContext*, std::less<CompoundKey>,
                     StlAllocator<std::pair<CompoundKey const, RelayTimeContext*>, 2> > Container;  // ❓ typedef name

    bool initContextManager();  // 0xb110
    bool AddContext(unsigned long long relayTid, long long relayLimitTime, RelayContext* const relayContext);  // 0xb2a0
    bool RemoveContext(unsigned long long relayTid, long long relayLimitTime);  // 0xb550

    int const _bucketCount;
    CriticalSection* _lockList;
    Container* _containerList;
    long volatile _contextCount;

private:
    RelayTimeContextManager();  // later card (PostOfficeDaemon)
};
static_assert(sizeof(RelayTimeContextManager) == 0x20, "sizeof RelayTimeContextManager");
static_assert(offsetof(RelayTimeContextManager, _contextCount) == 0x18, "RelayTimeContextManager::_contextCount");
