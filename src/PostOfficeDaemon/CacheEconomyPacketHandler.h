// CacheEconomyPacketHandler.obj (PostOfficeDaemon PDB).
#pragma once

class Session;
class Packet;

bool HandleCacheEconomyPingOk(Session const* session, Packet const* packet);                      // 0x5120
bool HandleCacheEconomyPingFail(Session const* session, Packet const* packet);                    // 0x5490
bool HandleCacheEconomyRetrieveCharacterInfoOk(Session const* session, Packet const* packet);     // 0x57f0
bool HandleCacheEconomyRetrieveCharacterInfoFail(Session const* session, Packet const* packet);   // 0x5b80
bool HandleCacheEconomyCheckPostCapacityOk(Session const* session, Packet const* packet);         // 0x5ee0
bool HandleCacheEconomyCheckPostCapacityFail(Session const* session, Packet const* packet);       // 0x6260
bool HandleCacheEconomyDeliverPostOk(Session const* session, Packet const* packet);               // 0x65c0
bool HandleCacheEconomyDeliverPostFail(Session const* session, Packet const* packet);             // 0x6920
bool HandleCacheEconomyHelloOk(Session const* session, Packet const* packet);                     // 0x6c90
bool HandleCacheEconomyHelloFail(Session const* session, Packet const* packet);                   // 0x6d30
bool HandleCacheEconomyFail(Session const* session, Packet const* packet);                        // 0x6dd0
bool HandleCacheEconomyRemovePawnOk(Session const* session, Packet const* packet);                // 0x6e70
bool HandleCacheEconomyRemovePawnFail(Session const* session, Packet const* packet);              // 0x6f10
