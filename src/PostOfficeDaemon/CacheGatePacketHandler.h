// CacheGatePacketHandler.obj (PostOfficeDaemon PDB).
#pragma once
#include "RelayContext.h"

class Session;
class Packet;

#include "DeliverPostRelay.h"

bool HandleCacheGateHelloOk(Session const* session, Packet const* packet);               // 0x7e90
bool HandleCacheGateHelloFail(Session const* session, Packet const* packet);             // 0x7fc0
bool HandleCacheGateRelay(Session const* session, Packet const* packet);                 // 0x8070
bool HandleCacheGateFragmentRelay(Session const* session, Packet const* packet);         // 0x82c0
bool HandleCacheGateRelayFail(Session const* session, Packet const* packet);             // 0x8540
bool HandleCacheGateRelayInvalid(Session const* session, Packet const* packet);          // 0x8a60
bool HandleCacheGateHello(Session const* session, Packet const* packet);                 // 0x8fa0
bool HandleCacheGateTheOtherSideListReq(Session const* session, Packet const* packet);   // 0x9040
bool HandleCacheGateTheOtherSideListAck(Session const* session, Packet const* packet);   // 0x90e0
