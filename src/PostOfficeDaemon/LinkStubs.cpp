// Stub bodies that the PostOfficeDaemon link needs. The functions are not in a PostOfficeDaemon PDB module.
#include "Channel.h"

// ❓ CacheGate has this function at 0x40B0. PostOfficeDaemon has no ClientSideDaemonChannel vftable, thus no body.
// Channel.cpp emits the vftable, so the link needs a body.
bool ClientSideDaemonChannel::onAccept(Session const* session)
{
    (void)session;
    return true;  // TODO(lift-postofficedaemon-5) ❓ return value
}
