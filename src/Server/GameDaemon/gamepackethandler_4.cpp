// gamepackethandler_4.cpp: gamepackethandler.cpp part 4 (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "gamepackethandler.h"
#include "pc.h"
#include "LiftStub.h"

#pragma comment(linker, "/INCLUDE:?HandleGame_ExtendJumpingCharacterCreationQuotaWithWarehouseItemReq@@YA_NPEAVPc@@PEBVPacket@@@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?HandleGame_UpgradeJumpingCharacterStateWithCreationQuotaReq@@YA_NPEAVPc@@PEBVPacket@@@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?HandleGame_SaveVitalityReq@@YA_NPEAVPc@@PEBVPacket@@@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?HandleGame_RestoreVitalityReq@@YA_NPEAVPc@@PEBVPacket@@@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?HandleGame_PickGemCardReq@@YA_NPEAVPc@@PEBVPacket@@@Z")  // LIFT: dead-strip keep (no live caller yet)

// LIFT: Pc members are not declared yet (LiftBytes). PDB offsets: GameObject::Id +0x28, Pc::_pcDbId +0x4E10.
#define GPH4_PC_ID(pc) (*reinterpret_cast<unsigned __int64 const *>(reinterpret_cast<char const *>(pc) + 0x28))
#define GPH4_PC_DBID(pc) (*reinterpret_cast<unsigned __int64 const *>(reinterpret_cast<char const *>(pc) + 0x4E10))
#define GPH4_FILE L"e:\\dailybuild02\\gamedaemon-common-0.0.348\\depot\\branch\\348nc\\program\\server\\gamedaemon\\GamePacketHandler.cpp"

// PDB struct (size 0x18). No other source file declares it yet.
struct ExtendJumpingCharacteCreationQuotaWithWarehouseItemReqParam
{
    long long labelId;
    long long itemInstanceId;
    int itemDataId;
};

// 0x3bb180
bool __cdecl HandleGame_ListGoodsFromAccountInventoryReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3bb180);
}

// 0x3bb460
bool __cdecl HandleGame_TakeGoodsFromAccountInventoryReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3bb460);
}

// 0x3bb6d0
bool __cdecl HandleGame_RetrieveWarehouseLobbyServiceItemListReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3bb6d0);
}

// 0x3bb9f0
bool __cdecl HandleGame_RetrieveWarehouseItemListReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3bb9f0);
}

// 0x3bbd60
bool __cdecl HandleGame_TakeWarehouseItemReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3bbd60);
}

// 0x3bc2e0
bool __cdecl HandleGame_ExtendJumpingCharacterCreationQuotaWithWarehouseItemReq(::Pc *pc, ::Packet const *packet)
{
    short c;
    ExtendJumpingCharacteCreationQuotaWithWarehouseItemReqParam param;
    packet->Decompose("hqqi", &c, &param.labelId, &param.itemInstanceId, &param.itemDataId);
    Log::Write(Log::LT_ERROR, GPH4_FILE, 21633,
               L"HandleGame_ExtendJumpingCharacterCreationQuotaReq; not available, pcid:0x%I64x, pcDbId:%#I64x",
               GPH4_PC_ID(pc), GPH4_PC_DBID(pc));
    pc->Send("hEqq", 785, 1886, param.labelId, param.itemInstanceId);
    return true;
}

// 0x3bc3b0
bool __cdecl HandleGame_UpgradeJumpingCharacterStateWithCreationQuotaReq(::Pc *pc, ::Packet const *)
{
    Log::Write(Log::LT_ERROR, GPH4_FILE, 21710,
               L"HandleGame_UpgradeJumpingCharacterStateWithCreationQuotaReq: not available, pcid:0x%I64x, pcDbId:%#I64x",
               GPH4_PC_ID(pc), GPH4_PC_DBID(pc));
    pc->Send("hE", 788, 1893);
    return true;
}

// 0x3bc420
bool __cdecl HandleGame_AntibotClientToServerReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3bc420);
}

// 0x3bc5d0
bool __cdecl HandleGame_TraceRouteIPReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3bc5d0);
}

// 0x3bc9f0
bool __cdecl HandleGame_SaveVitalityReq(::Pc *pc, ::Packet const *)
{
    Log::Write(Log::LT_ERROR, GPH4_FILE, 21879, L"[vitality], deprecated packet, Pc:0x%I64x", GPH4_PC_ID(pc));
    return true;
}

// 0x3bca20
bool __cdecl HandleGame_RechargeVitalityReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3bca20);
}

// 0x3bcd00
bool __cdecl HandleGame_RestoreVitalityReq(::Pc *pc, ::Packet const *)
{
    Log::Write(Log::LT_ERROR, GPH4_FILE, 21976, L"[vitality], deprecated packet, Pc:0x%I64x", GPH4_PC_ID(pc));
    return true;
}

// 0x3bcd30
bool __cdecl HandleGame_TransformItemReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3bcd30);
}

// 0x3bdec0
bool __cdecl HandleGame_PassingItemAbilityReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3bdec0);
}

// 0x3be660
bool __cdecl HandleGame_PickGemCardReq(::Pc *pc, ::Packet const *)
{
    Log::Write(Log::LT_ERROR, GPH4_FILE, 22407, L"HandleGame_PickGemCardReq failed; pc:0x%I64x", GPH4_PC_ID(pc));
    return true;
}

// 0x3be6b0
bool __cdecl HandleGame_BuyCollectionItemsReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3be6b0);
}

// 0x3bf9b0
bool __cdecl HandleGame_TestBotAnswerReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3bf9b0);
}

// 0x3bfa60
bool __cdecl HandleGame_AchievementCompleteReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3bfa60);
}

// 0x3c0560
bool __cdecl HandleGame_AchievementTitleInstallReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3c0560);
}

// 0x3c0940
bool __cdecl HandleGame_AchievementAbilityInstallReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3c0940);
}

// 0x3c0d80
bool __cdecl HandleGame_ActivateGameGradeReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3c0d80);
}

// 0x3c0ea0
bool __cdecl HandleGame_RetrieveBoundRaidDungeonInfoReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3c0ea0);
}

// 0x3c11a0
bool __cdecl HandleGame_UnbindRaidDungeonReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3c11a0);
}

// 0x3c1900
bool __cdecl HandleGame_RaidDungeonOnlinePlayerInfoReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3c1900);
}

// 0x3c1b60
bool __cdecl HandleGame_RaidDungeonExpirationReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3c1b60);
}

// 0x3c1de0
bool __cdecl HandleGame_RandomStoreInfoReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3c1de0);
}

// 0x3c1fd0
bool __cdecl HandleGame_RandomStoreDrawReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3c1fd0);
}

// 0x3c2cc0
bool __cdecl HandleGame_ExpandRandomStoreSlotReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3c2cc0);
}

// 0x3c3bd0
bool __cdecl HandleGame_BuyRandomStoreItemReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3c3bd0);
}

// 0x3c4280
bool __cdecl HandleGame_TakeRandomStoreDrawRewardReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3c4280);
}

// 0x3c4680
bool __cdecl HandleGame_LockItemReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3c4680);
}

// 0x3c4960
bool __cdecl HandleGame_UnlockItemReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3c4960);
}

// 0x3c4c70
bool __cdecl HandleGame_SetItemLockExpirationTimeReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3c4c70);
}

// 0x3c4f50
bool __cdecl HandleGame_ChangeToReplayQuestReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3c4f50);
}

// 0x3c5170
bool __cdecl HandleGame_PutItemIntoClosetReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3c5170);
}

// 0x3c5410
bool __cdecl HandleGame_TakeItemFromClosetReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3c5410);
}

// 0x3c56f0
bool __cdecl HandleGame_DepositMileageReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3c56f0);
}

// 0x3c5e30
bool __cdecl HandleGame_RetrieveMysteriousStoreReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3c5e30);
}

// 0x3c6020
bool __cdecl HandleGame_ChangeWeaponAppearanceReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3c6020);
}

// 0x3c64a0
bool __cdecl HandleGame_FeedPetFoodReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3c64a0);
}

// 0x3c66f0
bool __cdecl HandleGame_ChoiceReturnToArenaLobbyReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3c66f0);
}

// 0x3c70c0
bool __cdecl HandleGame_PublishRecruitArenaDungeonMemberReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3c70c0);
}

// 0x3c7460
bool __cdecl HandleGame_CancelRecruitArenaDungeonMemberReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3c7460);
}

// 0x3c7800
bool __cdecl HandleGame_DuelBotTrainingRoomPickDuelBotReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3c7800);
}

// 0x3c7a60
bool __cdecl HandleGame_DuelBotTrainingRoomCombatStartReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3c7a60);
}

// 0x3c7d20
bool __cdecl HandleGame_DuelBotTrainingRoomRewardReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3c7d20);
}

// 0x3c7f40
bool __cdecl HandleGame_DuelBotChallengeCombatStartReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3c7f40);
}

// 0x3c8130
bool __cdecl HandleGame_DuelBotChallengePickStrategicToolReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3c8130);
}

// 0x3c8320
bool __cdecl HandleGame_DuelBotChallengeUseStrategicToolReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3c8320);
}

// 0x3c8510
bool __cdecl HandleGame_ReviveByAttractionRuleReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3c8510);
}

// 0x3c8750
bool __cdecl HandleGame_EnterAttractionZoneReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3c8750);
}

// 0x3c8cd0
bool __cdecl HandleGame_LeaveAttractionZoneReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3c8cd0);
}

// 0x3c8e70
bool __cdecl HandleGame_TakeAttractionRewardReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3c8e70);
}

// 0x3c9100
bool __cdecl HandleGame_RetrieveSeasonContentsScheduleReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3c9100);
}

// 0x3c93f0
bool __cdecl HandleGame_RetrieveGuildRankingInfoReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3c93f0);
}

// 0x3c9910
bool __cdecl HandleGame_RetrieveMyRankingInfoReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3c9910);
}

// 0x3c9cf0
bool __cdecl HandleGame_RetrieveRankingRewardListReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3c9cf0);
}

// 0x3c9e80
bool __cdecl HandleGame_TakeRankingRewardReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3c9e80);
}

// 0x3ca700
bool __cdecl HandleGame_SellOldItemReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3ca700);
}

// 0x3cad70
bool __cdecl HandleGame_ExchangeItemReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3cad70);
}

// 0x3cb2f0
bool __cdecl HandleGame_NPAuctionBidReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3cb2f0);
}

// 0x3cbb00
bool __cdecl HandleGame_RefreshSimpleQuestPackReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3cbb00);
}

// 0x3cbe00
bool __cdecl HandleGame_SkillTrainingRoomCombatStartReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3cbe00);
}

// 0x3cc060
bool __cdecl HandleGame_SkillTrainingRoomCombatStopReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3cc060);
}

// 0x3cc300
bool __cdecl HandleGame_SkillTrainingRoomCombatRestartReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3cc300);
}

// 0x3cc5a0
bool __cdecl HandleGame_SkillTrainingRoomInitCreatureStateReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3cc5a0);
}

// 0x3cc840
bool __cdecl HandleGame_EnterSkillTrainingRoomReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3cc840);
}

// 0x3ccae0
bool __cdecl HandleGame_MakeCustomDressReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3ccae0);
}

// 0x3cd100
bool __cdecl HandleGame_ResetCombatModeReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3cd100);
}

// 0x3cd3a0
bool __cdecl HandleGame_PublicRaidEventAddScoreReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3cd3a0);
}

// 0x3cd640
bool __cdecl HandleGame_SkillSkinAcquiredListReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3cd640);
}

// 0x3cd8a0
bool __cdecl HandleGame_ApplySkillSkinReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3cd8a0);
}

// 0x3cdc60
bool __cdecl HandleGame_CreateChallengePartyReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3cdc60);
}

// 0x3ce260
bool __cdecl HandleGame_InviteChallengePartyReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3ce260);
}

// 0x3ce760
bool __cdecl HandleGame_ConfirmInvitationChallengePartyReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3ce760);
}

// 0x3ceb60
bool __cdecl HandleGame_RejectInvitationChallengePartyReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3ceb60);
}

// 0x3cee80
bool __cdecl HandleGame_LeaveChallengePartyReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3cee80);
}

// 0x3cf250
bool __cdecl HandleGame_RetrieveChallengePartyRankingInfoReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3cf250);
}

// 0x3cf780
bool __cdecl HandleGame_ChangeMentoringTypeReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3cf780);
}

// 0x3cfb40
bool __cdecl HandleGame_InviteMentoringReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3cfb40);
}

// 0x3d0220
bool __cdecl HandleGame_ConfirmInvitationMentoringReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3d0220);
}

// 0x3d0b70
bool __cdecl HandleGame_RejectInvitationMentoringReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3d0b70);
}

// 0x3d0eb0
bool __cdecl HandleGame_LeaveMentoringReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3d0eb0);
}

// 0x3d11e0
bool __cdecl HandleGame_CallMentoringMemberReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3d11e0);
}

// 0x3d15f0
bool __cdecl HandleGame_WarpToMentoringMemberReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3d15f0);
}

// 0x3d1a50
bool __cdecl HandleGame_SetItemUsedReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3d1a50);
}

// 0x3d1e90
bool __cdecl HandleGame_SetClosetItemUsedReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3d1e90);
}

// 0x3d2060
bool __cdecl HandleGame_CollectingListReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3d2060);
}

// 0x3d2230
bool __cdecl HandleGame_CompleteClosetCollectingReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3d2230);
}

// 0x3d2400
bool __cdecl HandleGame_FishingListReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3d2400);
}

// 0x3d25d0
bool __cdecl HandleGame_ChallengeListsReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3d25d0);
}

// 0x3d2770
bool __cdecl HandleGame_SetPvPModeReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3d2770);
}

// 0x3d29b0
bool __cdecl HandleGame_SecretTreasureExpirationTimeReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3d29b0);
}

// 0x3d2c40
bool __cdecl HandleGame_ChangeBadgeEquipPageReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3d2c40);
}

// 0x3d2e90
bool __cdecl HandleGame_SynthesisBadgeReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3d2e90);
}

// 0x3d3570
bool __cdecl HandleGame_SynthesisBadgeRecipeDataReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3d3570);
}

// 0x3d3600
bool __cdecl HandleGame_UseJumpingCharacterTicketReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3d3600);
}

// 0x3d3ad0
bool __cdecl HandleGame_BoardGachaRetrieveSeasonReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3d3ad0);
}

// 0x3d3c80
bool __cdecl HandleGame_BoardGachaSessionOpenReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3d3c80);
}

// 0x3d3e20
bool __cdecl HandleGame_BoardGachaSessionCloseReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3d3e20);
}

// 0x3d3fd0
bool __cdecl HandleGame_BoardGachaBoardInfoReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3d3fd0);
}

// 0x3d4180
bool __cdecl HandleGame_BoardGachaGetParticipationCountPerSeasonReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3d4180);
}

// 0x3d4380
bool __cdecl HandleGame_BoardGachaRetrieveParticipationInfoPerPcReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3d4380);
}

// 0x3d4580
bool __cdecl HandleGame_BoardGachaRetrieveParticipationInfoAllReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3d4580);
}

// 0x3d4730
bool __cdecl HandleGame_BoardGachaDrawByItemReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3d4730);
}

// 0x3d4ea0
bool __cdecl HandleGame_BoardGachaDrawByInstantPaymentReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3d4ea0);
}

// 0x3d52d0
bool __cdecl HandleGame_BoardGachaRetrieveParticipationRewardStateReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3d52d0);
}

// 0x3d54d0
bool __cdecl HandleGame_BoardGachaTakeParticipationRewardReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3d54d0);
}

// 0x3d57e0
bool __cdecl HandleGame_SetSlateAmpSlotReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3d57e0);
}

// 0x3d5ba0
bool __cdecl HandleGame_DrawSlateNewStoneReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3d5ba0);
}

// 0x3d6200
bool __cdecl HandleGame_SetSlateNewStoneReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3d6200);
}

// 0x3d65c0
bool __cdecl HandleGame_GiveUpSlateNewStoneReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3d65c0);
}

// 0x3d6980
bool __cdecl HandleGame_ChangeSlatePageReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3d6980);
}

// 0x3d6d40
bool __cdecl HandleGame_ProcessItemFusionReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3d6d40);
}
