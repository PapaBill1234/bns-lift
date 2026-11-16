// CacheDChannel.obj (CacheGate PDB). Layout from include/pdb/CacheGate/types.h.
#pragma once
#include <stddef.h>
#include "Channel.h"

class Session;
class Packet;

class CacheDChannel : public ClientSideDaemonChannel
{
public:
    // ❓ The constructor is inlined in wmain (0x4180). It sets the fields to 0.
    CacheDChannel()
    {
        PortId = 0;
        ServerIp = 0;
        ServerPort = 0;
        SessionSize = 0;
        session = nullptr;
    }
    virtual ~CacheDChannel();                                                    // 0x3C70
    virtual bool PacketHandler(Session const* session, Packet const* packet) const;  // 0x4150

protected:
    virtual bool onConnect(Session const* session, bool firstConnected);         // 0x3C80
    virtual void onClose(Session const* session, bool tryReconnect, bool closeAll);  // 0x3E40
};
static_assert(sizeof(CacheDChannel) == 0x28, "sizeof CacheDChannel");
