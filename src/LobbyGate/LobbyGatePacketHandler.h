// LobbyGatePacketHandler.obj (LobbyGate PDB). Declarations only. The bodies come from a later card.
#pragma once

class Session;
class Packet;
class Client;

// ❓ The PDB type of the list entries is void*. Callers cast an entry to this type.
typedef bool (*LobbyGatePacketHandlerFunc)(Session const* session, Packet const* packet);  // ❓ name

extern void* AnyAuthedLobbyGatePacketHandlerList[110];
extern void* AuthedLobbyGatePacketHandlerList[110];
extern void* NotAuthedLobbyGatePacketHandlerList[110];

bool HandleLobbyGate_BypassPacket(Client* client, Packet const* packet);                              // 0x14c90
bool HandleLobbyGate_GetWorldInfoListReq(Client* client, Packet const* packet);                       // 0x14f40
bool HandleLobbyGate_GetPcCafeMileageFeverTimeScheduleListReq(Client* client, Packet const* packet);  // 0x150f0
