// CacheDChannel.obj (CacheGate PDB). Layout from include/pdb/CacheGate/types.h.
#pragma once
#include <stddef.h>
#include "Channel.h"

class Session;
class Packet;

class CacheDChannel : public ClientSideDaemonChannel
{
public:
    // LIFT: The constructor is inlined in wmain (0x4180). The ClientSideDaemonChannel constructor sets the fields to 0.
    CacheDChannel() {}
    virtual ~CacheDChannel();                                                    // 0x3C70
    virtual bool PacketHandler(Session const* session, Packet const* packet) const;  // 0x4150

protected:
    virtual bool onConnect(Session const* session, bool firstConnected);         // 0x3C80
    virtual void onClose(Session const* session, bool tryReconnect, bool closeAll);  // 0x3E40
};
static_assert(sizeof(CacheDChannel) == 0x28, "sizeof CacheDChannel");
