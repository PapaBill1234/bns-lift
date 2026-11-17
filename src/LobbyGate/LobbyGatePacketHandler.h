// LobbyGatePacketHandler.obj (LobbyGate PDB).
#pragma once

class Session;
class Packet;
class Client;

// ❓ The PDB type of the list entries is void*. Callers cast an entry to Daemon::PacketHandler
// (PDB nested type 0x20EA, also LobbyGate::NotAuthedPacketHandler).

extern void* AnyAuthedLobbyGatePacketHandlerList[110];  // 0x91b00
extern void* AuthedLobbyGatePacketHandlerList[110];     // 0x921e0
extern void* NotAuthedLobbyGatePacketHandlerList[110];  // 0x91e70

bool HandleLobbyGate_PingReq(Session const* session, Packet const* packet);                           // 0x142a0
bool HandleLobbyGate_ContentsRuleListReq(Session* session, Packet const* packet);                     // 0x142e0
bool HandleLobbyGate_HelloReq(Session* session, Packet* packet);                                      // 0x14470
bool HandleLobbyGate_LoginWithNPTokenReq(Session* session, Packet* packet);                           // 0x14750
bool HandleLobbyGate_LoginWithLobbyTokenReq(Session* session, Packet* packet);                        // 0x14ae0
bool HandleLobbyGate_BypassPacket(Client* client, Packet const* packet);                              // 0x14c90
bool HandleLobbyGate_GetWorldInfoListReq(Client* client, Packet const* packet);                       // 0x14f40
bool HandleLobbyGate_GetPcCafeMileageFeverTimeScheduleListReq(Client* client, Packet const* packet);  // 0x150f0
