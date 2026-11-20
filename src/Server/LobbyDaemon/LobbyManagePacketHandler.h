// LobbyManagePacketHandler.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once

class Packet;
class Session;

bool HandleLobbyManage_HelloReq(Session const*, Packet const*);  // 0x587d0
bool HandleLobbyManage_AnnounceNotify(Session const*, Packet const*);  // 0x589b0
bool HandleLobbyManage_KickReq(Session const*, Packet const*);  // 0x58b00
bool HandleLobbyManage_CleanupGameAccountIdIndexReq(Session const*, Packet const*);  // 0x590a0
bool HandleLobbyManage_CleanupPcidIndexReq(Session const*, Packet const*);  // 0x59470
bool HandleLobbyManage_RetryMileageDepositReq(Session const*, Packet const*);  // 0x59820
