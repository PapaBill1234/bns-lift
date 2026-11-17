// SaleTimeContext.obj (MarketDealerDaemon PDB). Layouts from include/pdb/MarketDealerDaemon/types.h.
#pragma once
#include <stddef.h>
#include <map>
#include "Lock.h"
#include "StlMemory.h"

class SaleContext;

class CompoundKey
{
public:
    // PDB constructor, inlined in SaleTimeContextManager::AddContext (0x2da50).
    CompoundKey(long long const saleId, long long const saleExpirationTime)
        : _saleId(saleId), _saleExpirationTime(saleExpirationTime) {}

    // PDB operator, inlined in the map code (0x2dd30): the expiration time first, then the sale id.
    bool operator<(CompoundKey const& other) const
    {
        if (_saleExpirationTime == other._saleExpirationTime)
            return _saleId < other._saleId;
        return _saleExpirationTime < other._saleExpirationTime;
    }

    long long _saleId;
    long long _saleExpirationTime;
};
static_assert(sizeof(CompoundKey) == 0x10, "sizeof CompoundKey");

class SaleTimeContext
{
public:
    SaleTimeContext(long long saleId, char saleType, SaleContext* const saleContext);  // PDB constructor, inlined in 0x2da50
    ~SaleTimeContext();                                                                 // 0x2d830

    long long _saleId;
    char _saleType;
    SaleContext* _saleContext;
};
static_assert(sizeof(SaleTimeContext) == 0x18, "sizeof SaleTimeContext");
static_assert(offsetof(SaleTimeContext, _saleType) == 0x8, "SaleTimeContext::_saleType");
static_assert(offsetof(SaleTimeContext, _saleContext) == 0x10, "SaleTimeContext::_saleContext");

class SaleTimeContextManager
{
public:
    typedef std::map<CompoundKey, SaleTimeContext*, std::less<CompoundKey>,
                     StlAllocator<std::pair<CompoundKey const, SaleTimeContext*>, 2> > Container;

    bool InitContextManager();  // 0x2d8c0
    bool AddContext(long long saleId, long long expirationTime, char saleType, SaleContext* const saleContext);  // 0x2da50
    bool RemoveContext(long long saleId, long long expirationTime);  // 0x2dd30

    int const _bucketCount;
    CriticalSection* _lockList;
    Container* _containerList;
    long volatile _contextCount;  // PDB: int. long is 4 bytes on Win64 (Interlocked API).

    // LIFT: PDB constructor, inlined in MarketDealerDaemon (later card).
    explicit SaleTimeContextManager(int const bucketCount)
        : _bucketCount(bucketCount), _lockList(nullptr), _containerList(nullptr), _contextCount(0)
    {
    }
};
static_assert(sizeof(SaleTimeContextManager) == 0x20, "sizeof SaleTimeContextManager");
static_assert(offsetof(SaleTimeContextManager, _lockList) == 0x8, "SaleTimeContextManager::_lockList");
static_assert(offsetof(SaleTimeContextManager, _containerList) == 0x10, "SaleTimeContextManager::_containerList");
static_assert(offsetof(SaleTimeContextManager, _contextCount) == 0x18, "SaleTimeContextManager::_contextCount");
