// ManageChannel.obj (LobbyDaemon PDB, 2019 + PDB). Layouts from tools/pdbcls.py LobbyDaemon <Class>.
// LIFT: header layouts only (fix7). The function bodies are still LIFT_STUB.
// LIFT: the PDB ctors and the virtual dtors have no own symbol in the lift scope. They are not declared.
#pragma once
#include <stddef.h>
#include "Channel.h"

class Packet;
class Session;

// LIFT: PDB layout (sizeof 0x30, Channel base).
class ManageChannel : public Channel
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

private:
    friend struct ManageChannelLayoutCheck;  // LIFT: checks the private PDB offsets.

    unsigned short const _manageWid;  // +0x28
};
static_assert(sizeof(ManageChannel) == 0x30, "sizeof ManageChannel");
struct ManageChannelLayoutCheck
{
    static_assert(offsetof(ManageChannel, _manageWid) == 0x28, "ManageChannel::_manageWid");
};

// LIFT: PDB layout (sizeof 0x8, SessionHandler base, no own members).
class ManageSessionHandler : public SessionHandler
{
public:
    virtual bool OnAccept(Session const*) const;  // 0x5b140
    virtual bool OnConnect(Session const*, bool) const;  // 0x5b180
    virtual void OnClose(Session const*, bool) const;  // 0x5b1c0
    virtual bool PacketHandler(Session const*, Packet const*) const;  // 0x5b2a0
};
static_assert(sizeof(ManageSessionHandler) == 0x8, "sizeof ManageSessionHandler");
