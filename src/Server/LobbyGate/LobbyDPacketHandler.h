// LobbyDPacketHandler.obj (LobbyGate PDB).
#pragma once

class Session;
class Packet;

bool HandleLobbyLobbyGate_HelloOk(Session const* session, Packet* packet);                         // 0xaf20
bool HandleLobbyLobbyGate_HelloFail(Session const* session, Packet* packet);                       // 0xb750
bool HandleLobbyLobbyGate_UpdateWorldInfoListNotify(Session const* session, Packet* packet);       // 0xb890
bool HandleLobbyLobbyGate_AnnounceNotify(Session const* session, Packet* packet);                  // 0xbce0
bool HandleLobbyLobbyGate_InitSessionWithNPTokenOk(Session const* session, Packet* packet);        // 0xbe90
bool HandleLobbyLobbyGate_InitSessionWithNPTokenFail(Session const* session, Packet* packet);      // 0xca10
bool HandleLobbyLobbyGate_StartSessionWithNPTokenOk(Session const* session, Packet* packet);       // 0xcd00
bool HandleLobbyLobbyGate_StartSessionWithNPTokenFail(Session const* session, Packet* packet);     // 0xe810
bool HandleLobbyLobbyGate_InitSessionWithLobbyTokenOk(Session const* session, Packet* packet);     // 0xeb30
bool HandleLobbyLobbyGate_InitSessionWithLobbyTokenFail(Session const* session, Packet* packet);   // 0xef10
bool HandleLobbyLobbyGate_StartSessionWithLobbyTokenOk(Session const* session, Packet* packet);    // 0xf230
bool HandleLobbyLobbyGate_StartSessionWithLobbyTokenFail(Session const* session, Packet* packet);  // 0xffc0
bool HandleLobbyLobbyGate_CloseAnonymousSessionNotify(Session const* session, Packet* packet);     // 0x102b0
bool HandleLobbyLobbyGate_CloseSessionNotify(Session const* session, Packet* packet);              // 0x10440
bool HandleLobbyLobbyGate_KickNotify(Session const* session, Packet* packet);                      // 0x10660
bool HandleLobbyLobbyGate_GetCharacterInfoListOk(Session const* session, Packet* packet);          // 0x10ab0
bool HandleLobbyLobbyGate_ListGoodsOk(Session const* session, Packet* packet);                     // 0x11060
bool HandleLobbyLobbyGate_TakeGoodsOk(Session const* session, Packet* packet);                     // 0x113e0
bool HandleLobbyLobbyGate_ListLobbyServiceItemInfoOk(Session const* session, Packet* packet);      // 0x117a0
bool HandleLobbyLobbyGate_GetServiceEntryListOk(Session const* session, Packet* packet);           // 0x11b60
bool HandleLobbyLobbyGate_GetEnterWorldTokenOk(Session const* session, Packet* packet);            // 0x11ee0
bool HandleLobbyLobbyGate_BypassPacket(Session const* session, Packet* packet);                    // 0x121d0
// 0x12650. The linker folded many `return true;` handlers to this one body (IDA name
// HandleLobbyLobbyGate_GetGoodsCountFail). The handler lists use this address for all of them.
bool HandleLobbyLobbyGate_GetEnterWorldTokenFail(Session const* session, Packet const* packet);  // 0x12650
bool HandleLobbyLobbyGate_StartWaitNotify(Session const* session, Packet const* packet);  // 0x12650
bool HandleLobbyLobbyGate_GetWaitInfoOk(Session const* session, Packet const* packet);  // 0x12650
bool HandleLobbyLobbyGate_GetWaitInfoFail(Session const* session, Packet const* packet);  // 0x12650
bool HandleLobbyLobbyGate_GiveupWaitOk(Session const* session, Packet const* packet);  // 0x12650
bool HandleLobbyLobbyGate_GiveupWaitFail(Session const* session, Packet const* packet);  // 0x12650
bool HandleLobbyLobbyGate_EndWaitNotify(Session const* session, Packet const* packet);  // 0x12650
bool HandleLobbyLobbyGate_GetCharacterInfoListFail(Session const* session, Packet const* packet);  // 0x12650
bool HandleLobbyLobbyGate_GetCharacterInfoOk(Session const* session, Packet const* packet);  // 0x12650
bool HandleLobbyLobbyGate_GetCharacterInfoFail(Session const* session, Packet const* packet);  // 0x12650
bool HandleLobbyLobbyGate_CheckCharacterNameOk(Session const* session, Packet const* packet);  // 0x12650
bool HandleLobbyLobbyGate_CheckCharacterNameFail(Session const* session, Packet const* packet);  // 0x12650
bool HandleLobbyLobbyGate_CreateCharacterOk(Session const* session, Packet const* packet);  // 0x12650
bool HandleLobbyLobbyGate_CreateCharacterFail(Session const* session, Packet const* packet);  // 0x12650
bool HandleLobbyLobbyGate_DeleteCharacterOk(Session const* session, Packet const* packet);  // 0x12650
bool HandleLobbyLobbyGate_DeleteCharacterFail(Session const* session, Packet const* packet);  // 0x12650
bool HandleLobbyLobbyGate_EndWaitCharacterDeletionNotify(Session const* session, Packet const* packet);  // 0x12650
bool HandleLobbyLobbyGate_CancelWaitCharacterDeletionOk(Session const* session, Packet const* packet);  // 0x12650
bool HandleLobbyLobbyGate_CancelWaitCharacterDeletionFail(Session const* session, Packet const* packet);  // 0x12650
bool HandleLobbyLobbyGate_RecoverCharacterOk(Session const* session, Packet const* packet);  // 0x12650
bool HandleLobbyLobbyGate_RecoverCharacterFail(Session const* session, Packet const* packet);  // 0x12650
bool HandleLobbyLobbyGate_BindCharacterSlotOk(Session const* session, Packet const* packet);  // 0x12650
bool HandleLobbyLobbyGate_BindCharacterSlotFail(Session const* session, Packet const* packet);  // 0x12650
bool HandleLobbyLobbyGate_GetChargeInfoOk(Session const* session, Packet const* packet);  // 0x12650
bool HandleLobbyLobbyGate_GetChargeInfoFail(Session const* session, Packet const* packet);  // 0x12650
bool HandleLobbyLobbyGate_AccountInventoryNotify(Session const* session, Packet const* packet);  // 0x12650
bool HandleLobbyLobbyGate_GetGoodsCountOk(Session const* session, Packet const* packet);  // 0x12650
bool HandleLobbyLobbyGate_GetGoodsCountFail(Session const* session, Packet const* packet);  // 0x12650
bool HandleLobbyLobbyGate_ListGoodsFail(Session const* session, Packet const* packet);  // 0x12650
bool HandleLobbyLobbyGate_TakeGoodsFail(Session const* session, Packet const* packet);  // 0x12650
bool HandleLobbyLobbyGate_ListLobbyServiceItemInfoFail(Session const* session, Packet const* packet);  // 0x12650
bool HandleLobbyLobbyGate_GetLobbyServiceItemInfoOk(Session const* session, Packet const* packet);  // 0x12650
bool HandleLobbyLobbyGate_GetLobbyServiceItemInfoFail(Session const* session, Packet const* packet);  // 0x12650
bool HandleLobbyLobbyGate_GetServiceEntryListFail(Session const* session, Packet const* packet);  // 0x12650
bool HandleLobbyLobbyGate_ChangeCharacterAppearanceWithAccountInventoryItemOk(Session const* session, Packet const* packet);  // 0x12650
bool HandleLobbyLobbyGate_ChangeCharacterAppearanceWithAccountInventoryItemFail(Session const* session, Packet const* packet);  // 0x12650
bool HandleLobbyLobbyGate_ChangeCharacterSexWithAccountInventoryItemOk(Session const* session, Packet const* packet);  // 0x12650
bool HandleLobbyLobbyGate_ChangeCharacterSexWithAccountInventoryItemFail(Session const* session, Packet const* packet);  // 0x12650
bool HandleLobbyLobbyGate_ChangeCharacterRaceWithAccountInventoryItemOk(Session const* session, Packet const* packet);  // 0x12650
bool HandleLobbyLobbyGate_ChangeCharacterRaceWithAccountInventoryItemFail(Session const* session, Packet const* packet);  // 0x12650
bool HandleLobbyLobbyGate_RenameCharacterWithAccountInventoryItemOk(Session const* session, Packet const* packet);  // 0x12650
bool HandleLobbyLobbyGate_RenameCharacterWithAccountInventoryItemFail(Session const* session, Packet const* packet);  // 0x12650
bool HandleLobbyLobbyGate_AddSlotWithAccountInventoryItemOk(Session const* session, Packet const* packet);  // 0x12650
bool HandleLobbyLobbyGate_AddSlotWithAccountInventoryItemFail(Session const* session, Packet const* packet);  // 0x12650
bool HandleLobbyLobbyGate_ChangeUserNameWithAccountInventoryItemOk(Session const* session, Packet const* packet);  // 0x12650
bool HandleLobbyLobbyGate_ChangeUserNameWithAccountInventoryItemFail(Session const* session, Packet const* packet);  // 0x12650
bool HandleLobbyLobbyGate_ExtendJumpingCharacterCreationQuotaWithAccountInventoryItemOk(Session const* session, Packet const* packet);  // 0x12650
bool HandleLobbyLobbyGate_ExtendJumpingCharacterCreationQuotaWithAccountInventoryItemFail(Session const* session, Packet const* packet);  // 0x12650
bool HandleLobbyLobbyGate_CreateInitialUserNameOk(Session const* session, Packet const* packet);  // 0x12650
bool HandleLobbyLobbyGate_CreateInitialUserNameFail(Session const* session, Packet const* packet);  // 0x12650
bool HandleLobbyLobbyGate_ActivateGradeOk(Session const* session, Packet const* packet);  // 0x12650
bool HandleLobbyLobbyGate_ActivateGradeFail(Session const* session, Packet const* packet);  // 0x12650
bool HandleLobbyLobbyGate_ChangedGradeNotify(Session const* session, Packet const* packet);  // 0x12650
bool HandleLobbyLobbyGate_ChangedGradeLevelNotify(Session const* session, Packet const* packet);  // 0x12650
