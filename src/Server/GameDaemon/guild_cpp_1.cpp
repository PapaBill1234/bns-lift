// guild_cpp_1.cpp: guild.cpp part 1 (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "guild.h"
#include "guildbank.h"
#include <time.h>
#include "LiftStub.h"

#pragma comment(linker, "/INCLUDE:?GetBanishOpenGuildMemberCountResetTime@Guild@@SA_J_JH@Z")  // LIFT: dead-strip keep (no live caller yet); static form: the original body has no this (now in rcx)

// 0xe0910
__cdecl Guild::Guild(void)
{
    LIFT_STUB(0xe0910);
}

// 0xe0c30
__cdecl Guild::~Guild(void)
{
    LIFT_STUB(0xe0c30);
}

// 0xe0ea0
bool __cdecl Guild::Initialize(::LoadGuildInfo const *)
{
    LIFT_STUB(0xe0ea0);
}

// 0xe11b0
bool __cdecl Guild::InitializeGuildBankData(void)
{
    LIFT_STUB(0xe11b0);
}

// 0xe1260
bool __cdecl Guild::InitializeGuildUniformList(short, ::GuildUniformInfo *const)
{
    LIFT_STUB(0xe1260);
}

// 0xe15e0
bool __cdecl Guild::InitializeGuildCombatRecords(::FragmentPacketConcatenater *)
{
    LIFT_STUB(0xe15e0);
}

// 0xe1800
bool __cdecl Guild::InitializeGuildJoinTicketList(::FragmentPacketConcatenater *)
{
    LIFT_STUB(0xe1800);
}

// 0xe1a50
bool __cdecl Guild::SetRenameGuildInProgress(bool)
{
    LIFT_STUB(0xe1a50);
}

// 0xe1ac0
void __cdecl Guild::GetGuildInfoForGameLog(::GuildInfoForGameLog &)
{
    LIFT_STUB(0xe1ac0);
}

// 0xe1b40
__int64 __cdecl Guild::GetGuildRegistrationTime(unsigned __int64)
{
    LIFT_STUB(0xe1b40);
}

// 0xe1c40
bool __cdecl Guild::AddGuildMember(unsigned __int64, unsigned __int64, wchar_t const *, short, char, short, short, short, char, __int64, __int64, short, int, short, short, short, __int64)
{
    LIFT_STUB(0xe1c40);
}

// 0xe1ee0
bool __cdecl Guild::JoinGuildReq(unsigned __int64, unsigned __int64, short &)
{
    LIFT_STUB(0xe1ee0);
}

// 0xe2380
bool __cdecl Guild::JoinGuild(unsigned __int64, char, __int64, __int64)
{
    LIFT_STUB(0xe2380);
}

// 0xe2ce0
bool __cdecl Guild::EnterWorldGuildMember(unsigned __int64)
{
    LIFT_STUB(0xe2ce0);
}

// 0xe3040
bool __cdecl Guild::LeaveWorldGuildMember(unsigned __int64)
{
    LIFT_STUB(0xe3040);
}

// 0xe31c0
bool __cdecl Guild::RetrieveGuildInfo(unsigned __int64)
{
    LIFT_STUB(0xe31c0);
}

// 0xe3660
bool __cdecl Guild::RetrieveGuildMembers(unsigned __int64)
{
    LIFT_STUB(0xe3660);
}

// 0xe38f0
bool __cdecl Guild::LevelUpGuildMember(unsigned __int64, char, char, char)
{
    LIFT_STUB(0xe38f0);
}

// 0xe3bc0
bool __cdecl Guild::UpdateGuildMemberFaction2(unsigned __int64, char)
{
    LIFT_STUB(0xe3bc0);
}

// 0xe3cf0
bool __cdecl Guild::SetZoneGuildMember(unsigned __int64, ::EnterReason)
{
    LIFT_STUB(0xe3cf0);
}

// 0xe3ff0
bool __cdecl Guild::UpdateGuildLevelOkFromCache(::UpdateGuildLevelInitParam &)
{
    LIFT_STUB(0xe3ff0);
}

// 0xe4460
short __cdecl Guild::UpdateGuildLevelReq(unsigned __int64, char)
{
    LIFT_STUB(0xe4460);
}

// 0xe4c40
bool __cdecl Guild::UpdateGuildLevelDebugReq(unsigned __int64, char)
{
    LIFT_STUB(0xe4c40);
}

// 0xe5190
bool __cdecl Guild::ReserveDistruction(unsigned __int64)
{
    LIFT_STUB(0xe5190);
}

// 0xe59b0
bool __cdecl Guild::ReserveDistructionByBuilder(unsigned __int64, wchar_t const *)
{
    LIFT_STUB(0xe59b0);
}

// 0xe5f90
void __cdecl Guild::ResetLevelUp(void)
{
    LIFT_STUB(0xe5f90);
}

// 0xe5fd0
__int64 __cdecl Guild::GetBanishOpenGuildMemberCountResetTime(__int64 now, int resetHour)
{
    // LIFT: the body does not read this. LTCG drops the unused this argument (now comes in rcx).
    tm today;
    if (_localtime64_s(&today, &now) != 0)
        return 0;
    today.tm_hour = resetHour;
    today.tm_sec = 0;
    today.tm_min = 0;
    __int64 resetTime = _mktime64(&today);
    if (now < resetTime)
        resetTime -= 86400;
    return resetTime;
}

// 0xe6050
bool __cdecl Guild::BanishGuildMember(unsigned __int64, char, wchar_t *, short &)
{
    LIFT_STUB(0xe6050);
}

// 0xe72a0
bool __cdecl Guild::LeaveGuild(unsigned __int64, wchar_t const *, short &)
{
    LIFT_STUB(0xe72a0);
}

// 0xe79f0
bool __cdecl Guild::LeaveGuildOk(unsigned __int64, unsigned __int64, short, ::GuildFlagBearerInfo &, char, __int64)
{
    LIFT_STUB(0xe79f0);
}

// 0xe7b40
bool __cdecl Guild::RemoveGuildMember(unsigned __int64, short, ::GuildFlagBearerInfo &, char, __int64)
{
    LIFT_STUB(0xe7b40);
}

// 0xe7f20
bool __cdecl Guild::RemoveWaitingMember(unsigned __int64)
{
    LIFT_STUB(0xe7f20);
}

// 0xe7f70
int __cdecl Guild::GetMembers(unsigned __int64 *const)
{
    LIFT_STUB(0xe7f70);
}

// 0xe8050
unsigned __int64 __cdecl Guild::GetGuildMemberPcDbId(wchar_t const *)
{
    LIFT_STUB(0xe8050);
}

// 0xe80e0
bool __cdecl Guild::IsMemberByPcDbId(unsigned __int64)
{
    LIFT_STUB(0xe80e0);
}

// 0xe8170
int __cdecl Guild::GetGuildJoinRenewalInviteGuildMemberManagers(unsigned __int64 *const)
{
    LIFT_STUB(0xe8170);
}

// 0xe8270
int __cdecl Guild::GetGuildJoinRenewalAcceptGuildMemberManagers(unsigned __int64 *const)
{
    LIFT_STUB(0xe8270);
}

// 0xe8370
bool __cdecl Guild::GetGuildMemberName(int, int, wchar_t *const)
{
    LIFT_STUB(0xe8370);
}

// 0xe8440
bool __cdecl Guild::GetMemberIndexByPcDbId(__int64, int &)
{
    LIFT_STUB(0xe8440);
}

// 0xe84c0
void __cdecl Guild::BroadcastPacket(::Packet *)
{
    LIFT_STUB(0xe84c0);
}

// 0xe8680
bool __cdecl Guild::BindingQQGroup(unsigned __int64, __int64, char)
{
    LIFT_STUB(0xe8680);
}

// 0xe8870
bool __cdecl Guild::SetQQGroupMemberInfo(unsigned __int64, __int64, char)
{
    LIFT_STUB(0xe8870);
}

// 0xe8fa0
bool __cdecl Guild::UnbindingQQGroup(unsigned __int64)
{
    LIFT_STUB(0xe8fa0);
}

// 0xe9150
bool __cdecl Guild::QQGroupMemberChangeStatus(unsigned __int64, __int64, __int64, char)
{
    LIFT_STUB(0xe9150);
}

// 0xe93a0
void __cdecl Guild::BroadcastLeaveGuild(char, wchar_t const *, short, ::GuildFlagBearerInfo &, char, __int64)
{
    LIFT_STUB(0xe93a0);
}

// 0xe9650
bool __cdecl Guild::EditNotificationMessageReq(unsigned __int64, wchar_t const *, short &)
{
    LIFT_STUB(0xe9650);
}

// 0xe9980
bool __cdecl Guild::EditNotificationMessageRes(unsigned __int64)
{
    LIFT_STUB(0xe9980);
}

// 0xe9a80
bool __cdecl Guild::RetrieveGuildMemberPermission(unsigned __int64, short &)
{
    LIFT_STUB(0xe9a80);
}

// 0xe9c80
bool __cdecl Guild::EditGuildMemberPermissionReq(unsigned __int64, unsigned int, unsigned int, unsigned int, unsigned int, short &)
{
    LIFT_STUB(0xe9c80);
}

// 0xea060
bool __cdecl Guild::EditGuildMemberPermissionRes(unsigned __int64, short &)
{
    LIFT_STUB(0xea060);
}

// 0xea2c0
bool __cdecl Guild::JoinGuildFail(unsigned __int64, short)
{
    LIFT_STUB(0xea2c0);
}

// 0xea500
bool __cdecl Guild::JoinGuildByInvitationFail(unsigned __int64, short)
{
    LIFT_STUB(0xea500);
}

// 0xea850
bool __cdecl Guild::GetReserveDestruction(void)
{
    LIFT_STUB(0xea850);
}

// 0xea940
bool __cdecl Guild::TryAcceptGuildApplication(unsigned __int64, short &, short &)
{
    LIFT_STUB(0xea940);
}

// 0xeade0
bool __cdecl Guild::TryJoinGuildRenewal(unsigned __int64, short, __int64)
{
    LIFT_STUB(0xeade0);
}

// 0xeba80
bool __cdecl Guild::FinishJoinGuildRenewal(unsigned __int64, short, __int64, char, __int64)
{
    LIFT_STUB(0xeba80);
}

// 0xec670
bool __cdecl Guild::CancelJoinGuildRenewal(unsigned __int64, short)
{
    LIFT_STUB(0xec670);
}

// 0xecbf0
void __cdecl Guild::UpdateGuildApplicationRefusal(bool)
{
    LIFT_STUB(0xecbf0);
}

// 0xecce0
unsigned __int64 __cdecl Guild::FindByGuildMemberIndex(int)
{
    LIFT_STUB(0xecce0);
}

// 0xecdf0
bool __cdecl Guild::InviteGuildRelay(unsigned __int64, wchar_t const *, char, short &)
{
    LIFT_STUB(0xecdf0);
}

// 0xedda0
bool __cdecl Guild::ConfirmInvitation(unsigned __int64, unsigned __int64, short &)
{
    LIFT_STUB(0xedda0);
}

// 0xee230
void __cdecl Guild::CancelInvitation(unsigned __int64, short)
{
    LIFT_STUB(0xee230);
}

// 0xee410
bool __cdecl Guild::RejectInvitation(unsigned __int64)
{
    LIFT_STUB(0xee410);
}

// 0xeeea0
bool __cdecl Guild::DelegateGuildLeaderRelay(unsigned __int64, char, wchar_t const *, short &)
{
    LIFT_STUB(0xeeea0);
}

// 0xef400
bool __cdecl Guild::DelegateGuildLeaderConfirm(unsigned __int64, short &)
{
    LIFT_STUB(0xef400);
}

// 0xef6d0
bool __cdecl Guild::DelegateGuildLeaderConfirmRes(unsigned __int64, short &)
{
    LIFT_STUB(0xef6d0);
}

// 0xefa00
bool __cdecl Guild::DelegateGuildLeaderForcibly(unsigned __int64, char, wchar_t const *, short &)
{
    LIFT_STUB(0xefa00);
}

// 0xf0090
bool __cdecl Guild::DelegateGuildLeaderByBuilder(unsigned __int64, wchar_t const *)
{
    LIFT_STUB(0xf0090);
}

// 0xf0360
bool __cdecl Guild::RenameGuildMember(unsigned __int64, wchar_t const *)
{
    LIFT_STUB(0xf0360);
}

// 0xf0460
bool __cdecl Guild::SetGuildMeetingPlace(short, unsigned int, ::vector16 &, short)
{
    LIFT_STUB(0xf0460);
}

// 0xf05d0
bool __cdecl Guild::GetGuildMeetingPlace(::Guild::MeetingPlace *)
{
    LIFT_STUB(0xf05d0);
}

// 0xf06e0
bool __cdecl Guild::RenameGuild(wchar_t const *, __int64)
{
    LIFT_STUB(0xf06e0);
}

// 0xf08b0
bool __cdecl Guild::BanishGuildMemberByBuilder(unsigned __int64, wchar_t *, short &)
{
    LIFT_STUB(0xf08b0);
}

// 0xf16f0
bool __cdecl Guild::RejectGuildLeader(unsigned __int64, short &)
{
    LIFT_STUB(0xf16f0);
}

// 0xf18c0
void __cdecl Guild::ResetDelegate(unsigned __int64, short)
{
    LIFT_STUB(0xf18c0);
}

// 0xf1a30
bool __cdecl Guild::ChangeGuildMemberGrade(unsigned __int64, char, wchar_t const *, char, short &)
{
    LIFT_STUB(0xf1a30);
}

// 0xf1fe0
bool __cdecl Guild::ChangeGuildMemberGradeOk(unsigned __int64, char, short &)
{
    LIFT_STUB(0xf1fe0);
}

// 0xf2190
void __cdecl Guild::ChangeGuildMemberGradeFail(unsigned __int64, short)
{
    LIFT_STUB(0xf2190);
}

// 0xf2260
void __cdecl Guild::BroadcastChangeGuildMemberGrade(char, wchar_t const *, short, short)
{
    LIFT_STUB(0xf2260);
}

// 0xf23b0
void __cdecl Guild::BroadcastDelegateGuildLeader(char, wchar_t const *)
{
    LIFT_STUB(0xf23b0);
}

// 0xf24e0
void __cdecl Guild::BroadcastRenameGuildMember(char, wchar_t const *)
{
    LIFT_STUB(0xf24e0);
}

// 0xf2610
void __cdecl Guild::BroadcastCallGuildNotify(int)
{
    LIFT_STUB(0xf2610);
}

// 0xf2790
void __cdecl Guild::BroadcastEditGuildNotificationMessage(wchar_t const *)
{
    LIFT_STUB(0xf2790);
}

// 0xf28b0
void __cdecl Guild::BroadcastJoinGuild(char, wchar_t const *, short, char, short, short, short, char, __int64, int, short, short, short)
{
    LIFT_STUB(0xf28b0);
}

// 0xf2aa0
void __cdecl Guild::BroadcastSendGuildApplicationNotify(unsigned __int64, __int64, wchar_t *, short, short, short)
{
    LIFT_STUB(0xf2aa0);
}

// 0xf2bf0
void __cdecl Guild::BroadcastCancelGuildApplicationNotify(unsigned __int64, short)
{
    LIFT_STUB(0xf2bf0);
}

// 0xf2d00
void __cdecl Guild::BroadcastRejectGuildApplicationOk(unsigned __int64, short)
{
    LIFT_STUB(0xf2d00);
}

// 0xf2e10
void __cdecl Guild::BroadcastAcceptGuildApplicationOk(unsigned __int64, __int64)
{
    LIFT_STUB(0xf2e10);
}

// 0xf2f20
void __cdecl Guild::BroadcastSendGuildInvitationOk(unsigned __int64, __int64, wchar_t *, short, short, short)
{
    LIFT_STUB(0xf2f20);
}

// 0xf3070
void __cdecl Guild::BroadcastCancelGuildInvitationOk(unsigned __int64, short)
{
    LIFT_STUB(0xf3070);
}

// 0xf3180
void __cdecl Guild::BroadcastRejectGuildInvitationNotify(unsigned __int64, short)
{
    LIFT_STUB(0xf3180);
}

// 0xf3290
void __cdecl Guild::BroadcastUpdateGuildApplicationRefusal(wchar_t *, bool)
{
    LIFT_STUB(0xf3290);
}

// 0xf33a0
void __cdecl Guild::BroadcastLoginGuildMember(char, wchar_t const *, short, char, short, short, short, char, __int64, int, short, short, short)
{
    LIFT_STUB(0xf33a0);
}

// 0xf35a0
void __cdecl Guild::BroadcastEditedGuildMemberPermission(void)
{
    LIFT_STUB(0xf35a0);
}

// 0xf3700
void __cdecl Guild::BroadcastUpdateGuildLevel(char, char, ::GuildBank::GuildBankItem *const)
{
    LIFT_STUB(0xf3700);
}

// 0xf3900
void __cdecl Guild::BroadcastDepositInGuildBank(wchar_t const *, short, ::GuildBank::GuildBankItem const *const)
{
    LIFT_STUB(0xf3900);
}

// 0xf3ba0
void __cdecl Guild::BroadcastAbandonGuildCraft(unsigned __int64)
{
    LIFT_STUB(0xf3ba0);
}

// 0xf3cf0
void __cdecl Guild::BroadcastContractGuildUniform(::ContractGuildUniformOkParam const *)
{
    LIFT_STUB(0xf3cf0);
}

// 0xf4210
void __cdecl Guild::BroadcastDonationGuildUniformMaterial(unsigned __int64, wchar_t const *, unsigned int, short, __int64)
{
    LIFT_STUB(0xf4210);
}

// 0xf43c0
void __cdecl Guild::BroadcastAbandonGuildUniform(unsigned __int64)
{
    LIFT_STUB(0xf43c0);
}

// 0xf4500
void __cdecl Guild::BroadcastFinishDonationGuildUniform(unsigned __int64)
{
    LIFT_STUB(0xf4500);
}

// 0xf4640
void __cdecl Guild::BroadcastMakeGuildUniform(unsigned __int64, __int64, __int64)
{
    LIFT_STUB(0xf4640);
}

// 0xf47e0
void __cdecl Guild::BroadcastFinishMakeGuildUniform(unsigned __int64)
{
    LIFT_STUB(0xf47e0);
}

// 0xf4950
void __cdecl Guild::BroadcastRegisterGuildUniform(unsigned __int64)
{
    LIFT_STUB(0xf4950);
}

// 0xf4ac0
void __cdecl Guild::BroadcastPutOnGuildUniform(unsigned __int64, __int64)
{
    LIFT_STUB(0xf4ac0);
}
