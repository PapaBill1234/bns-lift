// ManageChannel.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once

class Packet;
class Session;

class ManageChannel
{
public:
    virtual unsigned long long GetId();  // 0x58770
    static void SendKickOk(Session const*, unsigned long long);  // 0x5b630
    static void SendKickFail(Session const*, unsigned long long, short);  // 0x5b760
    static void SendCleanupGameAccountIdIndexOk(Session const*, unsigned long long);  // 0x5b8a0
    static void SendCleanupGameAccountIdIndexFail(Session const*, unsigned long long, short);  // 0x5b9d0
    static void SendCleanupPcidIndexOk(Session const*, unsigned long long);  // 0x5bb10
    static void SendCleanupPcidIndexFail(Session const*, unsigned long long, short);  // 0x5bc40
    static void SendRetryMileageDepositOk(Session const*, unsigned long long);  // 0x5bd80
    static void SendRetryMileageDepositFail(Session const*, unsigned long long, short);  // 0x5beb0
};

class ManageSessionHandler
{
public:
    virtual bool OnAccept(Session const*) const;  // 0x5b140
    virtual bool OnConnect(Session const*, bool) const;  // 0x5b180
    virtual void OnClose(Session const*, bool) const;  // 0x5b1c0
    virtual bool PacketHandler(Session const*, Packet const*) const;  // 0x5b2a0
};
