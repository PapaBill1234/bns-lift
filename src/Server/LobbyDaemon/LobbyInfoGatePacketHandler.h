// LobbyInfoGatePacketHandler.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once

class Packet;
class Session;
class SharedChannel;

bool HandleLobbyInfoGate_HelloReq(Session const*, Packet const*);  // 0x56d40
bool HandleLobbyInfoGate_AuthTokenReq(SharedChannel*, Packet const*);  // 0x57350
bool HandleLobbyInfoGate_GetWorldInfoListReq(SharedChannel*, Packet const*);  // 0x57880

// PDB LobbyInfoGatePacketHandlerDef (sizeof 16).
struct LobbyInfoGatePacketHandlerDef
{
    void* handler;
    bool auth;
    bool fragment;
};
static_assert(sizeof(LobbyInfoGatePacketHandlerDef) == 0x10, "sizeof LobbyInfoGatePacketHandlerDef");

// PDB global (11 entries), defined in LobbyInfoGatePacketLobbySideHandlerList.cpp (data only, .data rva 0x202D30).
extern LobbyInfoGatePacketHandlerDef LobbyInfoGatePacketLobbySideHandlerList[11];
