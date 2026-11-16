// CacheGateSessionHandler.obj and CacheGateServerSideHandlerList.obj (CacheGate PDB).
#pragma once
#include "Channel.h"

class Session;
class Packet;

class CacheGateSessionHandler : public SessionHandler
{
public:
    virtual ~CacheGateSessionHandler();                                              // 0x4040
    virtual bool OnAccept(Session const* session) const;                             // ❓ not in index
    virtual bool OnConnect(Session const* session, bool firstConnected) const;       // 0x40C0
    virtual void OnClose(Session const* session, bool tryReconnect) const;           // 0x4100
    virtual bool PacketHandler(Session const* session, Packet const* packet) const;  // 0x4150 (folded)
};
static_assert(sizeof(CacheGateSessionHandler) == 0x8, "sizeof CacheGateSessionHandler");

typedef bool (*CacheGatePacketHandler)(Session const* session, Packet const* packet);  // ❓ typedef name

extern CacheGatePacketHandler CacheGatePacketServerSideHandlerList[10];          // 0x592D0
extern CacheGatePacketHandler CacheGatePacketServerSideFragmentHandlerList[10];  // 0x59320

bool HandleCacheGateHello(Session const* session, Packet const* packet);          // 0x4C00
bool HandleCacheGateHelloOk(Session const* session, Packet const* packet);        // 0x4F20
bool HandleCacheGateHelloFail(Session const* session, Packet const* packet);      // 0x5040
bool HandleCacheGateRelay(Session const* session, Packet const* packet);          // 0x51C0
bool HandleCacheGateRelayFail(Session const* session, Packet const* packet);      // 0x57A0
bool HandleCacheGateFragmentRelay(Session const* session, Packet const* packet);  // 0x5880
