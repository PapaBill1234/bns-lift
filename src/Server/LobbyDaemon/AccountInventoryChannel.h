// AccountInventoryChannel.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once

class Packet;
class Session;
union id128;

class AccountInventoryChannel
{
public:
    virtual bool Connect(unsigned long long, unsigned int, unsigned long, unsigned short, long, bool);  // 0x6500
    bool SendHelloReq(short, short, short);  // 0x66b0
    bool SendLoginNotify(id128 const&);  // 0x67b0
    bool SendLogoutNotify(id128 const&);  // 0x68a0
};

class AccountInventorySessionHandler
{
public:
    virtual bool OnAccept(Session const*) const;  // 0x8020
    virtual bool OnConnect(Session const*, bool) const;  // 0x8080
    virtual void OnClose(Session const*, bool) const;  // 0x81b0
    virtual bool PacketHandler(Session const*, Packet const*) const;  // 0x82f0
};
