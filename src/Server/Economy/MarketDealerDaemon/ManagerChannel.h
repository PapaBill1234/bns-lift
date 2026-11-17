// ManagerChannel.obj (MarketDealerDaemon PDB). Layouts from include/pdb/MarketDealerDaemon/types.h.
// This is not the SmartCouponDaemon class. The names are the same, the code is different.
#pragma once
#include <stddef.h>
#include "Channel.h"
#include "Daemon.h"

class Session;
class Packet;

class ManagerChannel : public Channel
{
public:
    virtual ~ManagerChannel();           // later card
    virtual unsigned long long GetId();  // later card

    unsigned short const _managerWid;
};
static_assert(sizeof(ManagerChannel) == 0x30, "sizeof ManagerChannel");
static_assert(offsetof(ManagerChannel, _managerWid) == 0x28, "ManagerChannel::_managerWid");

class ManagerSessionHandler : public SessionHandler
{
public:
    virtual bool OnAccept(Session const* session) const;                             // 0x1a4c0
    virtual bool OnConnect(Session const* session, bool firstConnected) const;       // 0x1a520
    virtual void OnClose(Session const* session, bool tryReconnect) const;           // 0x1a580
    virtual bool PacketHandler(Session const* session, Packet const* packet) const;  // 0x1a6c0
    virtual ~ManagerSessionHandler() {}
};
static_assert(sizeof(ManagerSessionHandler) == 0x8, "sizeof ManagerSessionHandler");

// Handler list objects (data only, later card). PDB type in types.h is void*; the element type is Daemon::PacketHandler.
extern Daemon::PacketHandler MarketManagerPacketServerSideHandlerList[16];
extern Daemon::PacketHandler MarketManagerPacketServerSideFragmentHandlerList[16];
