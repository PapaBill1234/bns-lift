// ManagerPacketHandler.obj (MarketDealerDaemon PDB). Handlers of the market manager channel.
#pragma once

class Session;
class Packet;

bool HandleMarketManagerHelloReq(Session const* session, Packet const* packet);                       // 0x1a940
bool HandleMarketManagerSuspendSaleReq(Session const* session, Packet const* packet);                 // 0x1ac40
bool HandleMarketManagerRetrySingleDeliveryFailureReq(Session const* session, Packet const* packet);  // 0x1ad20
bool HandleMarketManagerRetryAllDeliveryFailureReq(Session const* session, Packet const* packet);     // 0x1ae50
bool HandleMarketManagerUpdateStatusToReportFailureReq(Session const* session, Packet const* packet);  // 0x1b040
