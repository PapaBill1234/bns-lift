// Link bodies for functions that are not in the SmartCouponDaemon PDB.
#include "Channel.h"

// Channel.obj (lift_common). ❓ Not in the SmartCouponDaemon PDB. The ClientSideDaemonChannel vftable in
// Channel.cpp needs it. CacheGate has its body in src/CacheGate/CacheDChannel.cpp.
bool ClientSideDaemonChannel::onAccept(Session const*) { return false; }  // ❓
