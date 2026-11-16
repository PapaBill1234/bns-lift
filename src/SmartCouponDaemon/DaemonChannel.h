// DaemonChannel.obj (SmartCouponDaemon PDB). Layouts from include/pdb/SmartCouponDaemon/types.h.
#pragma once
#include <stddef.h>
#include <map>
#include "Channel.h"
#include "Lock.h"

class Session;
class Packet;

struct GameEventDaemonId
{
    unsigned char _type;
    unsigned short _wid;
    unsigned char _reserved;

    // ❓ The map uses std::less<GameEventDaemonId>. The compare body is not known.
    bool operator<(GameEventDaemonId const& other) const
    {
        if (_type != other._type)
            return _type < other._type;
        return _wid < other._wid;
    }
};
static_assert(sizeof(GameEventDaemonId) == 0x6, "sizeof GameEventDaemonId");

class DChannel : public Channel
{
public:
    virtual ~DChannel();
    virtual unsigned long long GetId();

    GameEventDaemonId _daemonId;
    unsigned long _addr;
    unsigned short _port;
};
static_assert(sizeof(DChannel) == 0x38, "sizeof DChannel");

class DChannelMgr : public SessionHandler
{
public:
    DChannelMgr();  // ❓ inlined in SmartCouponDaemon::initNetwork (0x155F0)
    virtual ~DChannelMgr();
    virtual bool OnAccept(Session const*) const;
    virtual bool OnConnect(Session const*, bool) const;
    virtual void OnClose(Session const*, bool) const;
    virtual bool PacketHandler(Session const*, Packet const*) const;

    void Finalize();                                        // ❓ address
    bool SetupDaemonListFromXml(wchar_t const* fileName);   // ❓ address
    static bool CreateDaemonListXml(wchar_t const* fileName);  // ❓ static

    CriticalSection _lock;
    std::map<GameEventDaemonId, DChannel*> _list;
};
static_assert(sizeof(DChannelMgr) == 0x50, "sizeof DChannelMgr");
static_assert(offsetof(DChannelMgr, _list) == 0x30, "DChannelMgr::_list");
