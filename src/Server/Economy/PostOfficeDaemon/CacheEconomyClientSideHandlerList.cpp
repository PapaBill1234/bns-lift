// CacheEconomyClientSideHandlerList.obj (PostOfficeDaemon PDB). Data tables only (IDA 0x976c0, 0x98aa0).
#include "CacheEconomyPacketHandler.h"
#include "ThreadFreePacketPump.h"

// 0x976c0 (index = economy cmd - 1024)
Daemon::PacketHandler CacheEconomyPacketClientSideHandlerList[22] = {
    nullptr,
    nullptr,
    HandleCacheEconomyHelloOk,
    HandleCacheEconomyHelloFail,
    HandleCacheEconomyFail,
    nullptr,
    nullptr,
    nullptr,
    HandleCacheEconomyPingOk,
    HandleCacheEconomyPingFail,
    nullptr,
    HandleCacheEconomyRemovePawnOk,
    HandleCacheEconomyRemovePawnFail,
    nullptr,
    HandleCacheEconomyRetrieveCharacterInfoOk,
    HandleCacheEconomyRetrieveCharacterInfoFail,
    nullptr,
    HandleCacheEconomyCheckPostCapacityOk,
    HandleCacheEconomyCheckPostCapacityFail,
    nullptr,
    HandleCacheEconomyDeliverPostOk,
    HandleCacheEconomyDeliverPostFail,
};

// 0x98aa0 (.bss, all entries are zero). PDB: LF_ARRAY 0x26A2, 176 bytes = 22 entries.
Daemon::PacketHandler CacheEconomyPacketClientSideFragmentHandlerList[22] = {};
