// LobbyGamePacketHandler.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once

class Packet;
class Session;
class SharedChannel;

bool HandleLobbyGame_HelloReq(Session const*, Packet const*);  // 0x88260
bool HandleLobbyGame_ServiceOpenNotify(Session const*, Packet const*);  // 0x88cd0
bool HandleLobbyGame_NPPresenceKickReq(SharedChannel*, Packet const*);  // 0x88f30
bool HandleLobbyGame_EnterWorldReq(SharedChannel*, Packet const*);  // 0x89270
bool HandleLobbyGame_LeaveWorldReq(SharedChannel*, Packet const*);  // 0x899a0
bool HandleLobbyGame_UpdateBotScoreNotify(SharedChannel*, Packet const*);  // 0x89d90
bool HandleLobbyGame_LogoutNotify(SharedChannel*, Packet const*);  // 0x8a060
bool HandleLobbyGame_KickOk(SharedChannel*, Packet const*);  // 0x8a400
bool HandleLobbyGame_KickFail(SharedChannel*, Packet const*);  // 0x8a560
bool HandleLobbyGame_CreateCharacterOk(SharedChannel*, Packet const*);  // 0x8a7c0
bool HandleLobbyGame_CreateCharacterFail(SharedChannel*, Packet const*);  // 0x8aad0
bool HandleLobbyGame_DeleteCharacterOk(SharedChannel*, Packet const*);  // 0x8ad30
bool HandleLobbyGame_DeleteCharacterFail(SharedChannel*, Packet const*);  // 0x8af90
bool HandleLobbyGame_RestoreCharacterOk(SharedChannel*, Packet const*);  // 0x8b1f0
bool HandleLobbyGame_RestoreCharacterFail(SharedChannel*, Packet const*);  // 0x8b350
bool HandleLobbyGame_StartChargeReq(SharedChannel*, Packet const*);  // 0x8b5b0
bool HandleLobbyGame_StopChargeReq(SharedChannel*, Packet const*);  // 0x8b9b0
bool HandleLobbyGame_AbandonChargeNotify(SharedChannel*, Packet const*);  // 0x8be60
bool HandleLobbyGame_UpdateCharacterDataReq(SharedChannel*, Packet const*);  // 0x8c250
bool HandleLobbyGame_UpdateAccountDataReq(SharedChannel*, Packet const*);  // 0x8c660
bool HandleLobbyGame_TryRegisterGuildReq(SharedChannel*, Packet const*);  // 0x8d590
bool HandleLobbyGame_FinishRegisterGuildNotify(SharedChannel*, Packet const*);  // 0x8d9a0
bool HandleLobbyGame_CancelRegisterGuildNotify(SharedChannel*, Packet const*);  // 0x8db10
bool HandleLobbyGame_TryRenameGuildReq(SharedChannel*, Packet const*);  // 0x8dc80
bool HandleLobbyGame_FinishRenameGuildNotify(SharedChannel*, Packet const*);  // 0x8e010
bool HandleLobbyGame_CancelRenameGuildNotify(SharedChannel*, Packet const*);  // 0x8e220
bool HandleLobbyGame_DeleteGuildNotify(SharedChannel*, Packet const*);  // 0x8e390
bool HandleLobbyGame_ChangeCharacterAppearanceOk(SharedChannel*, Packet const*);  // 0x8e520
bool HandleLobbyGame_ChangeCharacterAppearanceFail(SharedChannel*, Packet const*);  // 0x8e820
bool HandleLobbyGame_ChangeCharacterSexOk(SharedChannel*, Packet const*);  // 0x8eab0
bool HandleLobbyGame_ChangeCharacterSexFail(SharedChannel*, Packet const*);  // 0x8edb0
bool HandleLobbyGame_ChangeCharacterRaceOk(SharedChannel*, Packet const*);  // 0x8f040
bool HandleLobbyGame_ChangeCharacterRaceFail(SharedChannel*, Packet const*);  // 0x8f340
bool HandleLobbyGame_RenameCharacterOk(SharedChannel*, Packet const*);  // 0x8f5d0
bool HandleLobbyGame_RenameCharacterFail(SharedChannel*, Packet const*);  // 0x8f870
bool HandleLobbyGame_ExtendJumpingCharacterCreationQuotaWithAccountInventoryItemReq(SharedChannel*, Packet const*);  // 0x8fb00
bool HandleLobbyGame_UpgradeJumpingCharacterStateWithCreationQuotaReq(SharedChannel*, Packet const*);  // 0x8ffc0
bool HandleLobbyGame_UpdateJumpingCharacterStateReq(SharedChannel*, Packet const*);  // 0x903d0
bool HandleLobbyGame_SetAppDataNotify(SharedChannel*, Packet const*);  // 0x907e0
bool HandleLobbyGame_FriendMessageNotify(SharedChannel*, Packet const*);  // 0x90f70
bool HandleLobbyGame_SecondPasswordGetStatusReq(SharedChannel*, Packet const*);  // 0x91ab0
bool HandleLobbyGame_SecondPasswordIsVerifiedReq(SharedChannel*, Packet const*);  // 0x91e80
bool HandleLobbyGame_AuctionEscrowOk(SharedChannel*, Packet const*);  // 0x92280
bool HandleLobbyGame_AuctionEscrowFail(SharedChannel*, Packet const*);  // 0x92400
bool HandleLobbyGame_AuctionBidReq(SharedChannel*, Packet const*);  // 0x926a0
bool HandleLobbyGame_GetGradeListReq(SharedChannel*, Packet const*);  // 0x92ca0
bool HandleLobbyGame_ActivateGradeReq(SharedChannel*, Packet const*);  // 0x92f00
bool HandleLobbyGame_DepositGameMileageReq(SharedChannel*, Packet const*);  // 0x93540
bool HandleLobbyGame_BoastEventInWorldNotify(SharedChannel*, Packet const*);  // 0x94780
bool HandleLobbyGame_TakeAccountTimeBasedPlayRewardReq(SharedChannel*, Packet const*);  // 0x94910
bool HandleLobbyGame_UpdateAccountExpReq(SharedChannel*, Packet const*);  // 0x94df0
bool HandleLobbyGame_UpdateAccountContentQuotaReq(SharedChannel*, Packet const*);  // 0x951f0
bool HandleLobbyGame_UpdateAccountRecycleTimeReq(SharedChannel*, Packet const*);  // 0x95890
