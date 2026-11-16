// Stub bodies that the LobbyGate link needs. The functions are not in a LobbyGate PDB module.
#include "Channel.h"

// ❓ CacheGate has this function at 0x40B0. LobbyGate has no ClientSideDaemonChannel vftable, thus no body.
// Channel.cpp emits the vftable, so the link needs a body.
bool ClientSideDaemonChannel::onAccept(Session const* session)
{
    (void)session;
    return true;  // TODO(lift-lobbygate-4) ❓ return value
}
