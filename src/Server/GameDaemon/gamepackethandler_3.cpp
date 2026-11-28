// gamepackethandler_3.cpp: gamepackethandler.cpp part 3 (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "gamepackethandler.h"
#include "pc.h"
#include "LiftStub.h"

#pragma comment(linker, "/INCLUDE:?HandleGame_CheckRoundTripTimeReq@@YA_NPEAVPc@@PEBVPacket@@@Z")  // LIFT: dead-strip keep (no live caller yet)

// 0x39c3d0
bool __cdecl HandleGame_SkillScoreReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x39c3d0);
}

// 0x39c580
bool __cdecl HandleGame_KillSummonedReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x39c580);
}

// 0x39c730
bool __cdecl HandleGame_AutoLogoutCheckReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x39c730);
}

// 0x39c8e0
bool __cdecl HandleGame_CheckRoundTripTimeReq(::Pc *pc, ::Packet const *packet)
{
    short cmd;
    __int64 data1;
    __int64 data2;
    // ❓ The original tests the result with "xor ecx, ecx; cmp cx, ax; jb". No source form found yet (test ax, ax here).
    if (packet->Decompose("hqq", &cmd, &data1, &data2) == 0)
    {
        Log::Write(Log::LT_ERROR,
                   L"e:\\dailybuild02\\gamedaemon-common-0.0.348\\depot\\branch\\348nc\\program\\server\\gamedaemon\\GamePacketHandler.cpp",
                   12846, L"[game packet], HandleGame_CheckRoundTripTimeReq; decompose failed, pcid:0x%I64x",
                   *reinterpret_cast<unsigned __int64 const *>(reinterpret_cast<char const *>(pc) + 0x28));  // LIFT: GameObject::Id +0x28 (Pc members not declared yet)
        return true;
    }
    pc->Send("hqq", 413, data1, data2);
    return true;
}

// 0x39c980
bool __cdecl HandleGame_WriteLatencyLogReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x39c980);
}

// 0x39cc00
bool __cdecl HandleGame_ReportBotSpammerReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x39cc00);
}

// 0x39f790
bool __cdecl HandleGame_ChattingServerLoginSignatureReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x39f790);
}

// 0x39fc00
bool __cdecl HandleGame_CurrentUTCTimeReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x39fc00);
}

// 0x39fc10
bool __cdecl HandleGame_RegisterPartyMatchReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x39fc10);
}

// 0x39fd60
bool __cdecl HandleGame_RejectPartyMatchReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x39fd60);
}

// 0x39fe50
bool __cdecl HandleGame_CreateGuildReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x39fe50);
}

// 0x3a02f0
bool __cdecl HandleGame_RenameGuildReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3a02f0);
}

// 0x3a13c0
bool __cdecl HandleGame_DestroyGuildReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3a13c0);
}

// 0x3a1770
bool __cdecl HandleGame_RetrieveGuildInfoReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3a1770);
}

// 0x3a1980
bool __cdecl HandleGame_RetrieveGuildMembersReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3a1980);
}

// 0x3a1b80
bool __cdecl HandleGame_EditGuildNotificationMessageReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3a1b80);
}

// 0x3a1ff0
bool __cdecl HandleGame_RetrieveGuildMemberPermissionReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3a1ff0);
}

// 0x3a22f0
bool __cdecl HandleGame_EditGuildMemberPermissionReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3a22f0);
}

// 0x3a27e0
bool __cdecl HandleGame_ChangeGuildFlagBearerReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3a27e0);
}

// 0x3a2c50
bool __cdecl HandleGame_ChangeGuildMemberGradeReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3a2c50);
}

// 0x3a30e0
bool __cdecl HandleGame_DelegateGuildLeaderReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3a30e0);
}

// 0x3a3510
bool __cdecl HandleGame_ConfirmGuildLeaderReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3a3510);
}

// 0x3a3770
bool __cdecl HandleGame_RejectGuildLeaderReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3a3770);
}

// 0x3a39d0
bool __cdecl HandleGame_InviteGuildReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3a39d0);
}

// 0x3a3e90
bool __cdecl HandleGame_ConfirmInvitationGuildReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3a3e90);
}

// 0x3a41f0
bool __cdecl HandleGame_RejectInvitationGuildReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3a41f0);
}

// 0x3a4490
bool __cdecl HandleGame_JoinGuildReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3a4490);
}

// 0x3a49c0
bool __cdecl HandleGame_LeaveGuildReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3a49c0);
}

// 0x3a4c60
bool __cdecl HandleGame_BanishGuildMemberReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3a4c60);
}

// 0x3a5010
bool __cdecl HandleGame_QueryGuildInfoReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3a5010);
}

// 0x3a5840
bool __cdecl HandleGame_QueryGuildInfoToGamedReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3a5840);
}

// 0x3a6030
bool __cdecl HandleGame_WarpToGuildMemberReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3a6030);
}

// 0x3a68a0
bool __cdecl HandleGame_CallGuildMemberReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3a68a0);
}

// 0x3a7000
bool __cdecl HandleGame_WarpToGuildMeetingPlaceReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3a7000);
}

// 0x3a74f0
bool __cdecl HandleGame_GuildLevelUpReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3a74f0);
}

// 0x3a7820
bool __cdecl HandleGame_DepositInGuildBankReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3a7820);
}

// 0x3a8190
bool __cdecl HandleGame_ContractGuildCraftReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3a8190);
}

// 0x3a8f40
bool __cdecl HandleGame_AssentGuildCraftReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3a8f40);
}

// 0x3a9330
bool __cdecl HandleGame_DonateGuildCraftNormalMaterialReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3a9330);
}

// 0x3a9a60
bool __cdecl HandleGame_DonateGuildCraftBrandMaterialReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3a9a60);
}

// 0x3aa1b0
bool __cdecl HandleGame_MakeGuildCraftReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3aa1b0);
}

// 0x3aa5e0
bool __cdecl HandleGame_TakeGuildCraftReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3aa5e0);
}

// 0x3aa8e0
bool __cdecl HandleGame_AbandonGuildCraftReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3aa8e0);
}

// 0x3aac60
bool __cdecl HandleGame_ContractGuildUniformReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3aac60);
}

// 0x3ab9f0
bool __cdecl HandleGame_DonateGuildUniformMaterialReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3ab9f0);
}

// 0x3ac130
bool __cdecl HandleGame_AbandonGuildUniformReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3ac130);
}

// 0x3ac4b0
bool __cdecl HandleGame_MakeGuildUniformReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3ac4b0);
}

// 0x3ac7b0
bool __cdecl HandleGame_RegisterGuildUniformReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3ac7b0);
}

// 0x3acb30
bool __cdecl HandleGame_PutOnGuildUniformReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3acb30);
}

// 0x3aceb0
bool __cdecl HandleGame_RegisterGuildUniformWithDeletionReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3aceb0);
}

// 0x3ad240
bool __cdecl HandleGame_IncreaseUniformRegistrationQuotaReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3ad240);
}

// 0x3ad970
bool __cdecl HandleGame_RetrieveGuildJoinTicketListPerGuildReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3ad970);
}

// 0x3ae050
bool __cdecl HandleGame_RetrieveGuildJoinTicketListPerPcReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3ae050);
}

// 0x3ae440
bool __cdecl HandleGame_SendGuildApplicationReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3ae440);
}

// 0x3aeb80
bool __cdecl HandleGame_CancelGuildApplicationReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3aeb80);
}

// 0x3af190
bool __cdecl HandleGame_RejectGuildApplicationReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3af190);
}

// 0x3af790
bool __cdecl HandleGame_AcceptGuildApplicationReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3af790);
}

// 0x3afd90
bool __cdecl HandleGame_SendGuildInvitationReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3afd90);
}

// 0x3b0390
bool __cdecl HandleGame_SendGuildInvitation2Req(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3b0390);
}

// 0x3b0c60
bool __cdecl HandleGame_CancelGuildInvitationReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3b0c60);
}

// 0x3b1260
bool __cdecl HandleGame_RejectGuildInvitationReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3b1260);
}

// 0x3b1850
bool __cdecl HandleGame_AcceptGuildInvitationReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3b1850);
}

// 0x3b1e60
bool __cdecl HandleGame_UpdateGuildApplicationRefusalReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3b1e60);
}

// 0x3b2470
bool __cdecl HandleGame_UpdateGuildInvitationRefusalReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3b2470);
}

// 0x3b2850
bool __cdecl HandleGame_ProgressMissionByAcquireSummonedReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3b2850);
}

// 0x3b2ab0
bool __cdecl HandleGame_ChangeSummonedReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3b2ab0);
}

// 0x3b2e60
bool __cdecl HandleGame_ChangeSummonedNameReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3b2e60);
}

// 0x3b32e0
bool __cdecl HandleGame_ReserveArenaLobbyReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3b32e0);
}

// 0x3b3800
bool __cdecl HandleGame_ReserveArenaLobbyPartyAgreementReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3b3800);
}

// 0x3b3b80
bool __cdecl HandleGame_ReserveArenaLobbyPartyFinalDecisionReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3b3b80);
}

// 0x3b3e90
bool __cdecl HandleGame_EnterArenaLobbyReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3b3e90);
}

// 0x3b40a0
bool __cdecl HandleGame_LeaveArenaLobbyReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3b40a0);
}

// 0x3b41d0
bool __cdecl HandleGame_ExitFromArenaLobbyRoomReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3b41d0);
}

// 0x3b4300
bool __cdecl HandleGame_SetArenaLobbyRoomMatchOptionReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3b4300);
}

// 0x3b47c0
bool __cdecl HandleGame_DelegateArenaLobbyRoomTeamLeaderReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3b47c0);
}

// 0x3b4970
bool __cdecl HandleGame_SetArenaLobbyRoomPasswordReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3b4970);
}

// 0x3b4b00
bool __cdecl HandleGame_InviteArenaLobbyRoomReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3b4b00);
}

// 0x3b4f20
bool __cdecl HandleGame_BroadcastArenaLobbyRoomUnratedInvitationReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3b4f20);
}

// 0x3b5200
bool __cdecl HandleGame_JoinArenaLobbyRoomReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3b5200);
}

// 0x3b5450
bool __cdecl HandleGame_BanishFromArenaLobbyReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3b5450);
}

// 0x3b5610
bool __cdecl HandleGame_ReadyToMatchArenaLobbyRoomReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3b5610);
}

// 0x3b5840
bool __cdecl HandleGame_UnReadyToMatchArenaLobbyRoomReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3b5840);
}

// 0x3b5970
bool __cdecl HandleGame_MatchArenaLobbyRoomReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3b5970);
}

// 0x3b5c40
bool __cdecl HandleGame_SkipArenaLobbyMatchReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3b5c40);
}

// 0x3b5ec0
bool __cdecl HandleGame_CancelArenaLobbyMatchingReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3b5ec0);
}

// 0x3b6050
bool __cdecl HandleGame_CancelArenaLobbyMatchReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3b6050);
}

// 0x3b6180
bool __cdecl HandleGame_ReadyToGoToArenaReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3b6180);
}

// 0x3b6460
bool __cdecl HandleGame_DecideToGoToArenaReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3b6460);
}

// 0x3b65f0
bool __cdecl HandleGame_CancelArenaLobbyWaitingReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3b65f0);
}

// 0x3b6700
bool __cdecl HandleGame_RetrieveArenaLobbyWaitingNumberReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3b6700);
}

// 0x3b67a0
bool __cdecl HandleGame_EnterArenaReq(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x3b67a0);
}

// 0x3b6d30
bool __cdecl HandleGame_ReturnToArenaLobbyFromDuelReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3b6d30);
}

// 0x3b7060
bool __cdecl HandleGame_ReturnToArenaLobbyFromDungeonReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3b7060);
}

// 0x3b7360
bool __cdecl HandleGame_ArenaSpectateGameReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3b7360);
}

// 0x3b76d0
bool __cdecl HandleGame_ArenaEventTeleportToReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3b76d0);
}

// 0x3b7ab0
bool __cdecl HandleGame_ArenaEventWarpToPosReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3b7ab0);
}

// 0x3b7e10
bool __cdecl HandleGame_ArenaEventRecallReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3b7e10);
}

// 0x3b8320
bool __cdecl HandleGame_ArenaEventDuelGameStartReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3b8320);
}

// 0x3b8590
bool __cdecl HandleGame_ArenaEventFindArenaSessionReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3b8590);
}

// 0x3b8820
bool __cdecl HandleGame_ArenaEventMoveToArenaReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3b8820);
}

// 0x3b8b30
bool __cdecl HandleGame_ArenaSpectateReturnToArenaLobbyReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3b8b30);
}

// 0x3b8e20
bool __cdecl HandleGame_ListArenaSpectateGameReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3b8e20);
}

// 0x3b9330
bool __cdecl HandleGame_ArenaEventReturnToArenaLobbyReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3b9330);
}

// 0x3b9650
bool __cdecl HandleGame_ArenaEventReturnToArenaLobbyAllPcReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3b9650);
}

// 0x3b9980
bool __cdecl HandleGame_ArenaEventRetreivePcAssetReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3b9980);
}

// 0x3b9db0
bool __cdecl HandleGame_ArenaEventWarpToDuelRoundStartPcSpawnReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3b9db0);
}

// 0x3ba100
bool __cdecl HandleGame_ArenaEventSetBattleRoyalStateReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3ba100);
}

// 0x3ba470
bool __cdecl HandleGame_ArenaEventInZonePcLocReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3ba470);
}

// 0x3ba750
bool __cdecl HandleGame_ArenaEventBattleRoyalScoreReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3ba750);
}

// 0x3baa30
bool __cdecl HandleGame_ReturnToGameReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3baa30);
}

// 0x3baaf0
bool __cdecl HandleGame_RetrievePcDbIdReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3baaf0);
}

// 0x3bab00
// LIFT: feature off (owner scope)
bool __cdecl HandleGame_NCGuardMessage(::Pc *, ::Packet const *)
{
    return false;
}

// 0x3bad30
// LIFT: feature off (owner scope)
bool __cdecl HandleGame_XIGNCode3Message(::Pc *, ::Packet const *)
{
    return false;
}

// 0x3baf60
bool __cdecl HandleGame_GetGoodsCountFromAccountInventoryReq(::Pc *, ::Packet const *)
{
    LIFT_STUB(0x3baf60);
}
