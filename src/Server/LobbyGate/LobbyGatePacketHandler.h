// LobbyGatePacketHandler.obj (LobbyGate PDB).
#pragma once

class Session;
class Packet;
class Client;

// PDB: each list is 880 bytes (110 entries). AnyAuthed and NotAuthed use type 0x2631: pointers (0x20EA) to
// bool(Session const*, Packet const*). Authed uses type 0x2637: pointers (0x2636) to bool(Client*, Packet const*).
// LIFT: the lift stores the entries as void*. Callers cast an entry to the PDB pointer type.

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
bool HandleLobbyGate_LogoutReq(Client*, Packet const*);  // 0x12650
bool HandleLobbyGate_GetEnterWorldTokenReq(Client*, Packet const*);  // 0x12650
bool HandleLobbyGate_GetWaitInfoReq(Client*, Packet const*);  // 0x12650
bool HandleLobbyGate_GiveupWaitReq(Client*, Packet const*);  // 0x12650
bool HandleLobbyGate_GetCharacterInfoListReq(Client*, Packet const*);  // 0x12650
bool HandleLobbyGate_GetCharacterInfoReq(Client*, Packet const*);  // 0x12650
bool HandleLobbyGate_CheckCharacterNameReq(Client*, Packet const*);  // 0x12650
bool HandleLobbyGate_CreateCharacterReq(Client*, Packet const*);  // 0x12650
bool HandleLobbyGate_DeleteCharacterReq(Client*, Packet const*);  // 0x12650
bool HandleLobbyGate_CancelWaitCharacterDeletionReq(Client*, Packet const*);  // 0x12650
bool HandleLobbyGate_RecoverCharacterReq(Client*, Packet const*);  // 0x12650
bool HandleLobbyGate_BindCharacterSlotReq(Client*, Packet const*);  // 0x12650
bool HandleLobbyGate_GetChargeInfoReq(Client*, Packet const*);  // 0x12650
bool HandleLobbyGate_GetGoodsCountReq(Client*, Packet const*);  // 0x12650
bool HandleLobbyGate_ListGoodsReq(Client*, Packet const*);  // 0x12650
bool HandleLobbyGate_TakeGoodsReq(Client*, Packet const*);  // 0x12650
bool HandleLobbyGate_ListLobbyServiceItemInfoReq(Client*, Packet const*);  // 0x12650
bool HandleLobbyGate_GetLobbyServiceItemInfoReq(Client*, Packet const*);  // 0x12650
bool HandleLobbyGate_GetServiceEntryListReq(Client*, Packet const*);  // 0x12650
bool HandleLobbyGate_ChangeCharacterAppearanceWithAccountInventoryItemReq(Client*, Packet const*);  // 0x12650
bool HandleLobbyGate_ChangeCharacterSexWithAccountInventoryItemReq(Client*, Packet const*);  // 0x12650
bool HandleLobbyGate_ChangeCharacterRaceWithAccountInventoryItemReq(Client*, Packet const*);  // 0x12650
bool HandleLobbyGate_RenameCharacterWithAccountInventoryItemReq(Client*, Packet const*);  // 0x12650
bool HandleLobbyGate_AddSlotWithAccountInventoryItemReq(Client*, Packet const*);  // 0x12650
bool HandleLobbyGate_ChangeUserNameWithAccountInventoryItemReq(Client*, Packet const*);  // 0x12650
bool HandleLobbyGate_ExtendJumpingCharacterCreationQuotaWithAccountInventoryItemReq(Client*, Packet const*);  // 0x12650
bool HandleLobbyGate_CreateInitialUserNameReq(Client*, Packet const*);  // 0x12650
bool HandleLobbyGate_ActivateGradeReq(Client*, Packet const*);  // 0x12650
