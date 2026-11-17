// CacheGateClientSideHandlerList.obj (PostOfficeDaemon PDB). Data tables only (IDA 0x97570, 0x975c0).
#include "CacheGatePacketHandler.h"
#include "ThreadFreePacketPump.h"

// 0x97570
Daemon::PacketHandler CacheGatePacketClientSideHandlerList[10] = {
    nullptr,
    HandleCacheGateHello,
    HandleCacheGateHelloOk,
    HandleCacheGateHelloFail,
    HandleCacheGateRelay,
    HandleCacheGateRelayFail,
    HandleCacheGateRelayInvalid,
    HandleCacheGateTheOtherSideListReq,
    HandleCacheGateTheOtherSideListAck,
    HandleCacheGateFragmentRelay,
};

// 0x975c0
Daemon::PacketHandler CacheGatePacketClientSideFragmentHandlerList[10] = {
    nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
    HandleCacheGateFragmentRelay,
};
