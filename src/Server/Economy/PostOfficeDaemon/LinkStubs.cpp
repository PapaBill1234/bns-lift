// Stub bodies that the PostOfficeDaemon link needs. The functions are not in a PostOfficeDaemon PDB module.
#include "Channel.h"

// LIFT: CacheGate has this function at 0x40B0. PostOfficeDaemon has no ClientSideDaemonChannel vftable, thus no body.
// Channel.cpp emits the vftable, so the link needs a body.
bool ClientSideDaemonChannel::onAccept(Session const* session)
{
    (void)session;
    return true;  // LIFT: no body in PostOfficeDaemon, so no original return value.
}
