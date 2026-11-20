// PostOfficeChannel.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once

class Packet;
class Session;

class PostOfficeChannel
{
public:
    virtual bool Connect(unsigned long long, unsigned int, unsigned long, unsigned short, long, bool);  // 0x639f0
    bool SendHelloReq();  // 0x63ba0
};

class PostOfficeSessionHandler
{
public:
    virtual bool OnAccept(Session const*) const;  // 0x64170
    virtual bool OnConnect(Session const*, bool) const;  // 0x641d0
    virtual void OnClose(Session const*, bool) const;  // 0x642e0
    virtual bool PacketHandler(Session const*, Packet const*) const;  // 0x64420
};
