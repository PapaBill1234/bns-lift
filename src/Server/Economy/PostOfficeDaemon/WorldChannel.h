// WorldChannel.obj (PostOfficeDaemon PDB). Layouts from include/pdb/PostOfficeDaemon/types.h.
#pragma once
#include <stddef.h>
#include <map>
#include "Channel.h"
#include "Lock.h"
#include "StlMemory.h"

class Session;
class Packet;
class RelayContext;

class WorldChannel : public Channel
{
public:
    // LIFT: Inlined in HandlePostOfficeServiceHelloReq (0x1f890).
    WorldChannel(unsigned short wid, unsigned long ipAddress, unsigned short portNo)
        : _wid(wid), _ipAddress(ipAddress), _portNo(portNo) {}
    virtual ~WorldChannel();             // LIFT: folded with ~AgentChannel (0x1f620)
    virtual unsigned long long GetId();  // LIFT: folded with AgentChannel::GetId (0x1a6e0)

    static unsigned short GetWid(Session const* session);    // 0x1e490
    bool SendRelayResponse(RelayContext const* const relayContext);       // 0x1e570

    unsigned short const _wid;
    unsigned long const _ipAddress;
    unsigned short const _portNo;
};
static_assert(sizeof(WorldChannel) == 0x38, "sizeof WorldChannel");
static_assert(offsetof(WorldChannel, _wid) == 0x28, "WorldChannel::_wid");
static_assert(offsetof(WorldChannel, _ipAddress) == 0x2C, "WorldChannel::_ipAddress");
static_assert(offsetof(WorldChannel, _portNo) == 0x30, "WorldChannel::_portNo");

class WorldChannelManager
{
public:
    typedef std::map<unsigned short, WorldChannel*, std::less<unsigned short>,
                     StlAllocator<std::pair<unsigned short, WorldChannel*>, 2> > Container;

    bool initChannelManager();                                // 0x1e720
    WorldChannel* GetWorldChannel(unsigned short wid);        // 0x1e8b0
    bool AddWorldChannel(WorldChannel* const worldChannel);   // 0x1eb20
    bool RemoveWorldChannel(unsigned short wid);              // 0x1ed90

    int const _bucketCount;
    CriticalSection* _lockList;
    Container* _containerList;
    long volatile _worldCount;

    // LIFT: Inlined at 0x14090.
    explicit WorldChannelManager(int bucketCount)
        : _bucketCount(bucketCount), _lockList(nullptr), _containerList(nullptr), _worldCount(0)
    {
    }
};
static_assert(sizeof(WorldChannelManager) == 0x20, "sizeof WorldChannelManager");
static_assert(offsetof(WorldChannelManager, _worldCount) == 0x18, "WorldChannelManager::_worldCount");

class WorldSessionHandler : public SessionHandler
{
public:
    virtual ~WorldSessionHandler();
    virtual bool OnAccept(Session const* session) const;                             // 0x1f060
    virtual bool OnConnect(Session const* session, bool firstConnected) const;       // 0x1f0c0
    virtual void OnClose(Session const* session, bool tryReconnect) const;           // 0x1f120
    virtual bool PacketHandler(Session const* session, Packet const* packet) const;  // 0x1f270
};
static_assert(sizeof(WorldSessionHandler) == 0x8, "sizeof WorldSessionHandler");
