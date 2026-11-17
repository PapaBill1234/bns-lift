// CacheGateServerSideHandlerList.obj (CacheGate PDB).
#include "CacheGateSessionHandler.h"

// LIFT: name. The slots 6 to 8 point to a function that returns true (COMDAT folded, 0xCD80).
static bool CacheGateReturnTrue(Session const* session, Packet const* packet)
{
    return true;
}

// 0x592d0
Daemon::PacketHandler CacheGatePacketServerSideHandlerList[10] = {
    nullptr,
    HandleCacheGateHello,
    HandleCacheGateHelloOk,
    HandleCacheGateHelloFail,
    HandleCacheGateRelay,
    HandleCacheGateRelayFail,
    CacheGateReturnTrue,
    CacheGateReturnTrue,
    CacheGateReturnTrue,
    HandleCacheGateFragmentRelay,
};

// 0x59320
Daemon::PacketHandler CacheGatePacketServerSideFragmentHandlerList[10] = {
    nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
    HandleCacheGateFragmentRelay,
};
