// gamepackethandler_2.cpp: gamepackethandler.cpp part 2 (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "gamepackethandler.h"
#include "controlledcreature.h"
#include "pc.h"
#include "LiftStub.h"
#include "Log.h"

#pragma comment(linker, "/INCLUDE:?HandleGame_CreatePartyReq@@YA_NPEAVPc@@PEBVPacket@@@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?HandleGame_SendPetitionChatNotifyReq@@YA_NPEAVPc@@PEBVPacket@@@Z")  // LIFT: dead-strip keep (no live caller yet)

// LIFT: Pc members are not declared yet (LiftBytes). PDB offsets: GameObject::Id +0x28, Pc::_pcDbId +0x4E10.
#define GPH2_PC_ID(pc) (*reinterpret_cast<unsigned __int64 const *>(reinterpret_cast<char const *>(pc) + 0x28))
#define GPH2_PC_DBID(pc) (*reinterpret_cast<unsigned __int64 const *>(reinterpret_cast<char const *>(pc) + 0x4E10))
#define GPH2_FILE L"e:\\dailybuild02\\gamedaemon-common-0.0.348\\depot\\branch\\348nc\\program\\server\\gamedaemon\\GamePacketHandler.cpp"

// 0x387980
bool __cdecl HandleGame_FishManipulateReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x387980);
}

// 0x387f00
bool __cdecl HandleGame_GiveFactionScoreToRefinerReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x387f00);
}

// 0x388090
bool __cdecl HandleGame_TakeRefinerRewardReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x388090);
}

// 0x388250
bool __cdecl HandleGame_NpcManipulateReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x388250);
}

// 0x3887c0
bool __cdecl HandleGame_MoveReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3887c0);
}

// 0x389400
bool __cdecl HandleGame_AirDashReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x389400);
}

// 0x389580
bool __cdecl HandleGame_RecallSummonReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x389580);
}

// 0x389850
bool __cdecl HandleGame_SpecialSkillGaugeFullReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x389850);
}

// 0x389ab0
bool __cdecl HandleGame_MessageReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x389ab0);
}

// 0x389dc0
bool __cdecl HandleGame_MessageByItemReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x389dc0);
}

// 0x38a100
bool __cdecl HandleGame_MessageByDiceReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x38a100);
}

// 0x38a270
bool __cdecl HandleGame_SelectTargetReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x38a270);
}

// 0x38a410
bool __cdecl HandleGame_RespawnReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x38a410);
}

// 0x38a620
bool __cdecl HandleGame_DieInExhaustionReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x38a620);
}

// 0x38a870
bool __cdecl HandleGame_RestorationInExhaustionReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x38a870);
}

// 0x38aa50
bool __cdecl HandleGame_HelpRestorationReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x38aa50);
}

// 0x38ad80
bool __cdecl HandleGame_ReturnToBaseCampReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x38ad80);
}

// 0x38af50
bool __cdecl HandleGame_TurnReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x38af50);
}

// 0x38b240
bool __cdecl HandleGame_SetPcSocialReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x38b240);
}

// 0x38b430
void __cdecl SendWalk2FailPacket(::ControlledCreature *, short)
{
    LIFT_STUB(0x38b430);
}

// 0x38b4c0
bool __cdecl HandleGame_SuggestPartyReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x38b4c0);
}

// 0x38bcd0
bool __cdecl HandleGame_RejectSuggestPartyReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x38bcd0);
}

// 0x38c070
bool __cdecl HandleGame_CreatePartyReq(::Pc *pc, ::Packet const *)
{
    Log::Write(Log::LT_ERROR, GPH2_FILE, 8211, L"[party], create party, not available, pcid:0x%I64x, pcDbId:%#I64x",
               GPH2_PC_ID(pc), GPH2_PC_DBID(pc));
    pc->Send("hE", 154, 2);
    return true;
}

// 0x38c0e0
bool __cdecl HandleGame_InvitePartyReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x38c0e0);
}

// 0x38cc10
bool __cdecl HandleGame_JoinPartyReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x38cc10);
}

// 0x38d060
bool __cdecl HandleGame_LeavePartyReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x38d060);
}

// 0x38d230
bool __cdecl HandleGame_DelegatePartyLeaderReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x38d230);
}

// 0x38d440
bool __cdecl HandleGame_BanishPartyReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x38d440);
}

// 0x38d6a0
bool __cdecl HandleGame_ClearLogoutPartyMemberReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x38d6a0);
}

// 0x38d850
bool __cdecl HandleGame_ChangePartyPickupRuleReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x38d850);
}

// 0x38dad0
bool __cdecl HandleGame_RejectPartyReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x38dad0);
}

// 0x38dd60
bool __cdecl HandleGame_StopCinematicReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x38dd60);
}

// 0x38df70
bool __cdecl HandleGame_ChangePartyDifficultyTypeReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x38df70);
}

// 0x38e260
bool __cdecl HandleGame_ChangePartyInviteAuthReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x38e260);
}

// 0x38e500
bool __cdecl HandleGame_PassPartyAuctionReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x38e500);
}

// 0x38e730
bool __cdecl HandleGame_DistributionCurrentAuctionItemReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x38e730);
}

// 0x38e960
bool __cdecl HandleGame_GiveUpCurrentAuctionItemReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x38e960);
}

// 0x38ebb0
bool __cdecl HandleGame_BidCurrentAuctionItemReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x38ebb0);
}

// 0x38ee80
bool __cdecl HandleGame_FinishPartyAuctionReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x38ee80);
}

// 0x38f0d0
bool __cdecl HandleGame_PartyVoteCastReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x38f0d0);
}

// 0x38f3f0
bool __cdecl HandleGame_PartyVoteCancelCastReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x38f3f0);
}

// 0x38f590
bool __cdecl HandleGame_PartyVoteResetReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x38f590);
}

// 0x38f640
bool __cdecl HandleGame_SuggestTeamReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x38f640);
}

// 0x38fe40
bool __cdecl HandleGame_RejectSuggestTeamReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x38fe40);
}

// 0x390210
bool __cdecl HandleGame_InviteTeamReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x390210);
}

// 0x391420
bool __cdecl HandleGame_JoinTeamReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x391420);
}

// 0x3918f0
bool __cdecl HandleGame_LeaveTeamReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3918f0);
}

// 0x391d30
bool __cdecl HandleGame_RejectTeamReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x391d30);
}

// 0x391f50
bool __cdecl HandleGame_BanishTeamReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x391f50);
}

// 0x392230
bool __cdecl HandleGame_TeamMemberPartyChangeReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x392230);
}

// 0x3926a0
bool __cdecl HandleGame_DelegateTeamLeaderReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3926a0);
}

// 0x392940
bool __cdecl HandleGame_NominatePartyLeaderReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x392940);
}

// 0x392be0
bool __cdecl HandleGame_ChangeTeamInviteAuthReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x392be0);
}

// 0x392ed0
bool __cdecl HandleGame_ChangeTeamPartyDifficultyTypeReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x392ed0);
}

// 0x3931a0
bool __cdecl HandleGame_ClearLogoutTeamMemberReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3931a0);
}

// 0x393370
bool __cdecl HandleGame_DuelChooseDuelOrderReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x393370);
}

// 0x393590
bool __cdecl HandleGame_DuelReadyRoundReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x393590);
}

// 0x393700
bool __cdecl HandleGame_DuelTakeTagTokenReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x393700);
}

// 0x393870
bool __cdecl HandleGame_PartyBattleReadyReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x393870);
}

// 0x393a00
bool __cdecl HandleGame_PartyBattleStartReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x393a00);
}

// 0x393ba0
bool __cdecl HandleGame_PartyBattleVoteCastReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x393ba0);
}

// 0x393dd0
bool __cdecl HandleGame_EnterPortalReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x393dd0);
}

// 0x393fd0
bool __cdecl HandleGame_TurnBackFromPortalReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x393fd0);
}

// 0x394200
bool __cdecl HandleGame_ChannelListReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x394200);
}

// 0x394480
bool __cdecl HandleGame_ChangeChannelReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x394480);
}

// 0x394750
bool __cdecl HandleGame_SaveClientOptionReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x394750);
}

// 0x394920
bool __cdecl HandleGame_InviteTradeReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x394920);
}

// 0x394c70
bool __cdecl HandleGame_JoinTradeReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x394c70);
}

// 0x394fd0
bool __cdecl HandleGame_DeclineTradeReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x394fd0);
}

// 0x395360
bool __cdecl HandleGame_CancelTradeReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x395360);
}

// 0x395670
bool __cdecl HandleGame_AppendTradeSuggestionReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x395670);
}

// 0x395990
bool __cdecl HandleGame_RemoveTradeSuggestionReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x395990);
}

// 0x395c80
bool __cdecl HandleGame_SuggestTradeMoneyReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x395c80);
}

// 0x395f70
bool __cdecl HandleGame_SubmitTradeReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x395f70);
}

// 0x396240
bool __cdecl HandleGame_RetractTradeReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x396240);
}

// 0x396510
bool __cdecl HandleGame_ConfirmTradeReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x396510);
}

// 0x3967e0
bool __cdecl HandleGame_JoinChattingChannelReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3967e0);
}

// 0x396960
bool __cdecl HandleGame_LeaveChattingChannelReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x396960);
}

// 0x396ac0
// LIFT: feature off (owner scope)
bool __cdecl HandleGame_GameGuardAuthAnswerReq(::Pc *, ::Packet const *)
{
    return false;
}

// 0x396c70
bool __cdecl HandleGame_RetrievePostCountReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x396c70);
}

// 0x396e10
bool __cdecl HandleGame_RetrievePostBriefListReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x396e10);
}

// 0x396fd0
bool __cdecl HandleGame_RetrievePostReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x396fd0);
}

// 0x3971e0
bool __cdecl HandleGame_ArchivePostReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3971e0);
}

// 0x397420
bool __cdecl HandleGame_DeliverPostReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x397420);
}

// 0x397f20
bool __cdecl HandleGame_DetachPostAttachmentReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x397f20);
}

// 0x3982e0
bool __cdecl HandleGame_MarkExpressPostReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3982e0);
}

// 0x398630
bool __cdecl HandleGame_RetrieveCraftListReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x398630);
}

// 0x398640
bool __cdecl HandleGame_RegisterCraftReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x398640);
}

// 0x398880
bool __cdecl HandleGame_TakeCraftReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x398880);
}

// 0x398a90
bool __cdecl HandleGame_AbortCraftReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x398a90);
}

// 0x398c40
bool __cdecl HandleGame_JoinCraftUnionReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x398c40);
}

// 0x398f00
bool __cdecl HandleGame_LeaveCraftUnionReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x398f00);
}

// 0x399170
bool __cdecl HandleGame_RegisterSaleReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x399170);
}

// 0x399540
bool __cdecl HandleGame_UpdateSalePriceReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x399540);
}

// 0x399740
bool __cdecl HandleGame_AbandonSaleReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x399740);
}

// 0x3998c0
bool __cdecl HandleGame_RetrieveSaleListReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3998c0);
}

// 0x399a60
bool __cdecl HandleGame_RegisterBidReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x399a60);
}

// 0x399e40
bool __cdecl HandleGame_UpdateBidPriceReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x399e40);
}

// 0x39a220
bool __cdecl HandleGame_AbandonBidReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x39a220);
}

// 0x39a3b0
bool __cdecl HandleGame_RetrieveBidListReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x39a3b0);
}

// 0x39a4d0
bool __cdecl HandleGame_RetrieveBidRankStatusReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x39a4d0);
}

// 0x39a8a0
bool __cdecl HandleGame_RegisterPurchaseReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x39a8a0);
}

// 0x39ac20
bool __cdecl HandleGame_MarketSearchItemReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x39ac20);
}

// 0x39af00
bool __cdecl HandleGame_RetrieveInstantSaleItemLowestPriceReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x39af00);
}

// 0x39b040
bool __cdecl HandleGame_CurrentPetitionReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x39b040);
}

// 0x39b080
bool __cdecl HandleGame_SubmitPetitionReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x39b080);
}

// 0x39b3e0
bool __cdecl HandleGame_CancelPetitionReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x39b3e0);
}

// 0x39b500
bool __cdecl HandleGame_FeedbackPetitionReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x39b500);
}

// 0x39b970
bool __cdecl HandleGame_SendPetitionChatNotifyReq(::Pc *, ::Packet const *)
{
    Log::Write(Log::LT_DEBUG, GPH2_FILE, 12557, L"[petition], HandleGame_FeedbackPetitionReq not supported");
    return true;
}

// 0x39b9a0
bool __cdecl HandleGame_EndPetitionNotifyReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x39b9a0);
}

// 0x39ba40
bool __cdecl HandleGame_RegisterSurveyReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x39ba40);
}

// 0x39be40
bool __cdecl HandleGame_AnswerSurveyReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x39be40);
}

// 0x39c0d0
bool __cdecl HandleGame_AnswerExtraSurveyReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x39c0d0);
}

// 0x39c230
bool __cdecl HandleGame_WriteClientLogReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x39c230);
}
