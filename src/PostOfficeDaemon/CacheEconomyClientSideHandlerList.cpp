// CacheEconomyClientSideHandlerList.obj (PostOfficeDaemon PDB). Data tables only (IDA 0x976c0, 0x98aa0).
#include "CacheEconomyPacketHandler.h"
#include "ThreadFreePacketPump.h"

// 0x976c0 (index = economy cmd - 1024)
TFPP_PacketHandler CacheEconomyPacketClientSideHandlerList[22] = {
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

// 0x98aa0 (.bss, all entries are zero). ❓ size 22 from the distance to the next symbol (0x98b50).
TFPP_PacketHandler CacheEconomyPacketClientSideFragmentHandlerList[22] = {};
