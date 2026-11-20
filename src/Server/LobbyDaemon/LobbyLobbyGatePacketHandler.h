// LobbyLobbyGatePacketHandler.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once

class Packet;
class Session;
class SharedChannel;

bool HandleLobbyLobbyGate_HelloReq(Session const*, Packet const*);  // 0xc25c0
bool HandleLobbyLobbyGate_InitSessionWithNPTokenReq(SharedChannel*, Packet const*);  // 0xc2d90
bool HandleLobbyLobbyGate_StartSessionWithNPTokenReq(SharedChannel*, Packet const*);  // 0xc3380
bool HandleLobbyLobbyGate_InitSessionWithLobbyTokenReq(SharedChannel*, Packet const*);  // 0xc3890
bool HandleLobbyLobbyGate_StartSessionWithLobbyTokenReq(SharedChannel*, Packet const*);  // 0xc3e70
bool HandleLobbyLobbyGate_LostAnonymousConnectionNotify(SharedChannel*, Packet const*);  // 0xc4180
bool HandleLobbyLobbyGate_LostConnectionNotify(SharedChannel*, Packet const*);  // 0xc43f0
bool HandleLobbyLobbyGate_LogoutNotify(SharedChannel*, Packet const*);  // 0xc4650
bool HandleLobbyLobbyGate_GetEnterWorldTokenReq(SharedChannel*, Packet const*);  // 0xc48b0
bool HandleLobbyLobbyGate_GetWaitInfoReq(SharedChannel*, Packet const*);  // 0xc4df0
bool HandleLobbyLobbyGate_GiveupWaitReq(SharedChannel*, Packet const*);  // 0xc5040
bool HandleLobbyLobbyGate_GetCharacterInfoListReq(SharedChannel*, Packet const*);  // 0xc5360
bool HandleLobbyLobbyGate_GetCharacterInfoReq(SharedChannel*, Packet const*);  // 0xc5630
bool HandleLobbyLobbyGate_CheckCharacterNameReq(SharedChannel*, Packet const*);  // 0xc5ae0
bool HandleLobbyLobbyGate_CreateCharacterReq(SharedChannel*, Packet const*);  // 0xc5b10
bool HandleLobbyLobbyGate_DeleteCharacterReq(SharedChannel*, Packet const*);  // 0xc6190
bool HandleLobbyLobbyGate_CancelWaitCharacterDeletionReq(SharedChannel*, Packet const*);  // 0xc67e0
bool HandleLobbyLobbyGate_RecoverCharacterReq(SharedChannel*, Packet const*);  // 0xc6e30
bool HandleLobbyLobbyGate_BindCharacterSlotReq(SharedChannel*, Packet const*);  // 0xc7540
bool HandleLobbyLobbyGate_GetChargeInfoReq(SharedChannel*, Packet const*);  // 0xc7af0
bool HandleLobbyLobbyGate_GetGoodsCountReq(SharedChannel*, Packet const*);  // 0xc7df0
bool HandleLobbyLobbyGate_ListGoodsReq(SharedChannel*, Packet const*);  // 0xc8080
bool HandleLobbyLobbyGate_TakeGoodsReq(SharedChannel*, Packet const*);  // 0xc83d0
bool HandleLobbyLobbyGate_ListLobbyServiceItemInfoReq(SharedChannel*, Packet const*);  // 0xc85e0
bool HandleLobbyLobbyGate_GetLobbyServiceItemInfoReq(SharedChannel*, Packet const*);  // 0xc8860
bool HandleLobbyLobbyGate_GetServiceEntryListReq(SharedChannel*, Packet const*);  // 0xc8aa0
bool HandleLobbyLobbyGate_ChangeCharacterAppearanceWithAccountInventoryItemReq(SharedChannel*, Packet const*);  // 0xc8d00
bool HandleLobbyLobbyGate_ChangeCharacterSexWithAccountInventoryItemReq(SharedChannel*, Packet const*);  // 0xc9300
bool HandleLobbyLobbyGate_ChangeCharacterRaceWithAccountInventoryItemReq(SharedChannel*, Packet const*);  // 0xc9940
bool HandleLobbyLobbyGate_RenameCharacterWithAccountInventoryItemReq(SharedChannel*, Packet const*);  // 0xc9fc0
bool HandleLobbyLobbyGate_AddSlotWithAccountInventoryItemReq(SharedChannel*, Packet const*);  // 0xca560
bool HandleLobbyLobbyGate_ChangeUserNameWithAccountInventoryItemReq(SharedChannel*, Packet const*);  // 0xca8b0
bool HandleLobbyLobbyGate_ExtendJumpingCharacterCreationQuotaWithAccountInventoryItemReq(SharedChannel*, Packet const*);  // 0xcac70
bool HandleLobbyLobbyGate_CreateInitialUserNameReq(SharedChannel*, Packet const*);  // 0xcafd0
bool HandleLobbyLobbyGate_ActivateGradeReq(SharedChannel*, Packet const*);  // 0xcb330
