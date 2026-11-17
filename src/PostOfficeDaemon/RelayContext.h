// RelayContext.obj (PostOfficeDaemon PDB). Layouts from include/pdb/PostOfficeDaemon/types.h.
#pragma once
#include <stddef.h>
#include <new>
#include <map>
#include "RefCntObject.h"
#include "Lock.h"
#include "StlMemory.h"
#include "Memory.h"

class Channel;
class Packet;
class FragmentPacket;

class RelayResponse
{
public:
    enum RESULTSTATE  // ❓ enum type name
    {
        RESULTSTATE_SUCCESS = 0,
        RESULTSTATE_FAILURE = 1,
        RESULTSTATE_RELAY_ERROR = 2,
        RESULTSTATE_RELAY_TIMEOUT = 3,
        RESULTSTATE_INVALID = 4,  // ❓ value (0x1f650 uses the name, the PDB export has no value)
    };

    int _resultState;
    short _failReason;
};
static_assert(sizeof(RelayResponse) == 0x8, "sizeof RelayResponse");

class EconomyHeader
{
public:
    unsigned short _fromWid;
    unsigned short _toWid;
    unsigned long long _relayTid;
};
static_assert(sizeof(EconomyHeader) == 0x10, "sizeof EconomyHeader");

class RelayHeader
{
public:
    unsigned short _fromWid;
    unsigned short _toWid;
    unsigned long long _relayTid;
    unsigned short _hint;
    unsigned long long _reserved;
};
static_assert(sizeof(RelayHeader) == 0x20, "sizeof RelayHeader");

class RelayContext : public DynamicRefCntObj
{
public:
    enum RELAYSTATUS  // ❓ enum type name
    {
        RELAYSTATUS_INIT = 0,
        RELAYSTATUS_WAITING = 1,
        RELAYSTATUS_FINISH = 2,
        RELAYSTATUS_TIMEOUT = 3,
    };

    RelayContext(EconomyHeader const& economyHeader)  // ❓ inlined in the child ctors
        : _economyHeader(economyHeader), _relayStatus(RELAYSTATUS_INIT), _relayLimitTime(0) {}

    virtual unsigned short const GetRequestWid() const = 0;           // slot 4
    virtual RelayHeader const MakeRelayHeader() const = 0;            // slot 5
    virtual bool ComposeRequestPacket(FragmentPacket&) const = 0;     // slot 6
    virtual bool ComposeRequestPacket(Packet&) const = 0;             // slot 7
    virtual bool ComposeResponsePacket(FragmentPacket&) const = 0;    // slot 8
    virtual bool ComposeResponsePacket(Packet&) const = 0;            // slot 9
    virtual bool processRelayRequest(Channel* const) const = 0;       // slot 10
    virtual bool processRelayResponse() const = 0;                    // slot 11
    virtual bool processRelayTimeout() = 0;                           // slot 12
    virtual void initResponse(RelayResponse* const) = 0;              // slot 13
    virtual ~RelayContext() {}  // ❓ inlined in the child dtors

    bool ProcessRelayRequest(Channel* const channel);         // 0x1bb30
    bool ProcessRelayResponse(RelayResponse* const response); // 0x1c090
    bool ProcessRelayTimeout();                               // 0x1c480

    CriticalSection _lock;
    EconomyHeader const _economyHeader;
    int _relayStatus;
    long long _relayLimitTime;
};
static_assert(sizeof(RelayContext) == 0x60, "sizeof RelayContext");
static_assert(offsetof(RelayContext, _lock) == 0x18, "RelayContext::_lock");
static_assert(offsetof(RelayContext, _economyHeader) == 0x40, "RelayContext::_economyHeader");
static_assert(offsetof(RelayContext, _relayStatus) == 0x50, "RelayContext::_relayStatus");
static_assert(offsetof(RelayContext, _relayLimitTime) == 0x58, "RelayContext::_relayLimitTime");

// ❓ Not in the PDB. The original inlines an array new (`eh vector constructor iterator') with
// Memory::_Manager[2]->Alloc: the count is at the first int, the objects start at +8.
template<class T>
inline T* liftArrayNew(int count, wchar_t const* file, int line)
{
    int* raw = static_cast<int*>(Memory::_Manager[2]->Alloc(sizeof(T) * static_cast<long long>(count) + 8, file, line));
    if (raw == nullptr)
        return nullptr;
    *raw = count;
    T* items = reinterpret_cast<T*>(raw + 2);
    for (int i = 0; i < count; ++i)
        ::new (static_cast<void*>(&items[i])) T();
    return items;
}

class RelayContextManager
{
public:
    typedef std::map<unsigned long long, RelayContext*, std::less<unsigned long long>,
                     StlAllocator<std::pair<unsigned long long const, RelayContext*>, 2> > Container;  // ❓ typedef name

    bool initContextManager();                            // 0x1c780
    RelayContext* GetContext(unsigned long long relayTid);  // 0x1c910
    bool AddContext(RelayContext* const relayContext);    // 0x1cb80
    bool RemoveContext(unsigned long long relayTid);      // 0x1ce10

    int const _bucketCount;
    CriticalSection* _lockList;
    Container* _containerList;
    long volatile _contextCount;

    static unsigned long long _idSeed;

private:
    RelayContextManager();  // later card (PostOfficeDaemon)
};
static_assert(sizeof(RelayContextManager) == 0x20, "sizeof RelayContextManager");
static_assert(offsetof(RelayContextManager, _contextCount) == 0x18, "RelayContextManager::_contextCount");
