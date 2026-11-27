// pc_cpp_2.cpp: pc.cpp part 2 (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "pc.h"
#include "arenaroommanager.h"
#include "convoy.h"
#include "creature.h"
#include "fielditem.h"
#include "gameobject.h"
#include "geoworld.h"
#include "npc.h"
#include "summoned.h"
#include "team.h"
#include "user.h"
#include "zone.h"
#include "LiftStub.h"

// 0x5e5ad0
void __cdecl Pc::CalculateSkillScore(void)
{
    LIFT_STUB(0x5e5ad0);
}

// 0x5e6360
void __cdecl Pc::ModifyEquipBadgeGearScore(int)
{
    LIFT_STUB(0x5e6360);
}

// 0x5e63d0
__int64 __cdecl Pc::CalculateGuildRankingRewardCombatExp(char, __int64)
{
    LIFT_STUB(0x5e63d0);
}

// 0x5e6540
bool __cdecl Pc::GetNearRespawnArea(::vector16, unsigned int &, unsigned __int64 &)
{
    LIFT_STUB(0x5e6540);
}

// 0x5e6a90
bool __cdecl Pc::IsSharableCombatModeZone(void) const
{
    LIFT_STUB(0x5e6a90);
}

// 0x5e6ac0
bool __cdecl Pc::findZoneTeamMemberRemain(unsigned int, int &)
{
    LIFT_STUB(0x5e6ac0);
}

// 0x5e6c20
bool __cdecl Pc::findZonePartyMemberRemain(unsigned int, int &)
{
    LIFT_STUB(0x5e6c20);
}

// 0x5e6cf0
short __cdecl Pc::SelectTransitZone(short, ::LeaveReason, unsigned __int64, unsigned __int64 *, unsigned __int64 *, unsigned __int64 *, unsigned __int64 *, short *, unsigned __int64 *, unsigned int *, unsigned __int64 *, unsigned __int64 *, unsigned __int64 *, unsigned __int64 *, short *, bool, bool, char)
{
    LIFT_STUB(0x5e6cf0);
}

// 0x5e7e50
bool __cdecl Pc::TranslateZoneOnEnterWorld(unsigned __int64 *, unsigned int *, ::vector16 *, short *)
{
    LIFT_STUB(0x5e7e50);
}

// 0x5e81b0
::GameFailReason __cdecl Pc::selectTransitZoneForDungeon(::GeoZone const *, int, bool &, int &)
{
    LIFT_STUB(0x5e81b0);
}

// 0x5e88f0
void __cdecl Pc::CheckConditionAfterSpawn(void)
{
    LIFT_STUB(0x5e88f0);
}

// 0x5e8ef0
void __cdecl Pc::OnTimer(::Zone *, unsigned short)
{
    LIFT_STUB(0x5e8ef0);
}

// 0x5e9190
void __cdecl Pc::OnAttacked(::Zone *, ::GameObject *, unsigned __int64, short)
{
    LIFT_STUB(0x5e9190);
}

// 0x5e91e0
void __cdecl Pc::OnKilled(::Zone *, ::GameObject *, unsigned __int64)
{
    LIFT_STUB(0x5e91e0);
}

// 0x5e93e0
void __cdecl Pc::OnKill(::Zone *, ::Pc *, unsigned __int64, char, char)
{
    LIFT_STUB(0x5e93e0);
}

// 0x5e95c0
void __cdecl Pc::ProcessFactionByKill(::Pc *, unsigned __int64, char, char)
{
    LIFT_STUB(0x5e95c0);
}

// 0x5e9800
void __cdecl Pc::cancelTrade(char, wchar_t const *)
{
    LIFT_STUB(0x5e9800);
}

// 0x5e98b0
void __cdecl Pc::ClearStateOnDead(void)
{
    LIFT_STUB(0x5e98b0);
}

// 0x5e9a70
void __cdecl Pc::SetFieldItem(::FieldItem *)
{
    LIFT_STUB(0x5e9a70);
}

// 0x5e9bf0
void __cdecl Pc::ClearFieldItem(void)
{
    LIFT_STUB(0x5e9bf0);
}

// 0x5e9c50
void __cdecl Pc::ClearFieldItemProperty(void)
{
    LIFT_STUB(0x5e9c50);
}

// 0x5e9cc0
::GameFailReason const __cdecl Pc::CheckMakeSummoned(__int64)
{
    LIFT_STUB(0x5e9cc0);
}

// 0x5e9e00
void __cdecl Pc::MakeSummoned(__int64, wchar_t const *const)
{
    LIFT_STUB(0x5e9e00);
}

// 0x5ea0d0
::Summoned * __cdecl Pc::GetActiveSummoned(void)
{
    LIFT_STUB(0x5ea0d0);
}

// 0x5ea0f0
void __cdecl Pc::SetActiveSummoned(::Summoned *)
{
    LIFT_STUB(0x5ea0f0);
}

// 0x5ea2d0
::Data::MasteryAbilityRecordPtr const __cdecl Pc::GetMasteryAbilityData(char) const
{
    LIFT_STUB(0x5ea2d0);
}

// 0x5ea390
void __cdecl Pc::LeaveWorld(void)
{
    LIFT_STUB(0x5ea390);
}

// 0x5ea760
void __cdecl Pc::WriteGameLogLeaveWorld(char, char)
{
    LIFT_STUB(0x5ea760);
}

// 0x5eace0
void __cdecl Pc::enterArenaLobby(void)
{
    LIFT_STUB(0x5eace0);
}

// 0x5ead90
void __cdecl Pc::ResetSpecialSkillGauge(void)
{
    LIFT_STUB(0x5ead90);
}

// 0x5eaf10
int __cdecl Pc::GetCurrentSpecialSkillGauge(void)
{
    LIFT_STUB(0x5eaf10);
}

// 0x5eaff0
bool __cdecl Pc::IsSpecialSkillGaugeFull(void)
{
    LIFT_STUB(0x5eaff0);
}

// 0x5eb050
void __cdecl Pc::SetUser(::User const *)
{
    LIFT_STUB(0x5eb050);
}

// 0x5eb130
void __cdecl Pc::SendGameBuilderAuth(void)
{
    LIFT_STUB(0x5eb130);
}

// 0x5eb2e0
void __cdecl Pc::Send(char const *, char *)
{
    LIFT_STUB(0x5eb2e0);
}

// 0x5eb350
void __cdecl Pc::Send(char const *, ...)
{
    LIFT_STUB(0x5eb350);
}

// 0x5eb3c0
void __cdecl Pc::Send(::Packet const *)
{
    LIFT_STUB(0x5eb3c0);
}

// 0x5eb420
void __cdecl Pc::Send(::PacketList const *)
{
    LIFT_STUB(0x5eb420);
}

// 0x5eb4a0
void __cdecl Pc::SendChangedPrivateProperty(void)
{
    LIFT_STUB(0x5eb4a0);
}

// 0x5eb4f0
void __cdecl Pc::SendActionPrivatePacket(void)
{
    LIFT_STUB(0x5eb4f0);
}

// 0x5eb540
void __cdecl Pc::SendEnterWorldOk(void)
{
    LIFT_STUB(0x5eb540);
}

// 0x5ec3e0
void __cdecl Pc::writeGameLogEnterWorld(char, char)
{
    LIFT_STUB(0x5ec3e0);
}

// 0x5ec8a0
void __cdecl Pc::SendSummonedEnterWorldOk(void)
{
    LIFT_STUB(0x5ec8a0);
}

// 0x5ecb90
void __cdecl Pc::ChangeEnterArenaParam(unsigned __int64, __int64, unsigned __int64, __int64)
{
    LIFT_STUB(0x5ecb90);
}

// 0x5ecce0
void __cdecl Pc::SendEnterArenaOk(void)
{
    LIFT_STUB(0x5ecce0);
}

// 0x5ed820
bool __cdecl Pc::ReturningToArenaLobby(void)
{
    LIFT_STUB(0x5ed820);
}

// 0x5ed880
void __cdecl Pc::RollbackReturnToArenaLobby(void)
{
    LIFT_STUB(0x5ed880);
}

// 0x5ed8c0
void __cdecl Pc::SendUpdateDodgeInfo(void)
{
    LIFT_STUB(0x5ed8c0);
}

// 0x5ed9c0
void __cdecl Pc::SetArenaRoom(::ArenaRoom *, __int64)
{
    LIFT_STUB(0x5ed9c0);
}

// 0x5edae0
void __cdecl Pc::SetGameGameMode(char)
{
    LIFT_STUB(0x5edae0);
}

// 0x5edb30
char const __cdecl Pc::GetGameGameMode(void) const
{
    LIFT_STUB(0x5edb30);
}

// 0x5edb70
bool __cdecl Pc::SendReturnToGameOk(char)
{
    LIFT_STUB(0x5edb70);
}

// 0x5ee6b0
char __cdecl Pc::GetArenaAttraction(void) const
{
    LIFT_STUB(0x5ee6b0);
}

// 0x5ee6f0
void __cdecl Pc::SendCurrentUTCTimeOk(void)
{
    LIFT_STUB(0x5ee6f0);
}

// 0x5ee830
void __cdecl Pc::SendChatMessage(char, wchar_t const *, int, wchar_t const *, wchar_t const *)
{
    LIFT_STUB(0x5ee830);
}

// 0x5ef4b0
void __cdecl Pc::SendChatMessageByItem(wchar_t const *, char, short)
{
    LIFT_STUB(0x5ef4b0);
}

// 0x5ef760
void __cdecl Pc::SendChatMessageByDice(short, short)
{
    LIFT_STUB(0x5ef760);
}

// 0x5ef9a0
void __cdecl Pc::SendPcDbIdOk(void)
{
    LIFT_STUB(0x5ef9a0);
}

// 0x5efb50
void __cdecl Pc::SendQuestCompleteListOk(void)
{
    LIFT_STUB(0x5efb50);
}

// 0x5efd00
void __cdecl Pc::SendMentoringPropertySync(void)
{
    LIFT_STUB(0x5efd00);
}

// 0x5efec0
void __cdecl Pc::SendActivatedTeleportListOk(void)
{
    LIFT_STUB(0x5efec0);
}

// 0x5f0070
void __cdecl Pc::ChangeTeamPartyProperty(unsigned short)
{
    LIFT_STUB(0x5f0070);
}

// 0x5f00d0
bool __cdecl Pc::FetchTeamPartyProperty(::Packet *, ::Packet *, ::Packet *, ::Packet *)
{
    LIFT_STUB(0x5f00d0);
}

// 0x5f04e0
void __cdecl Pc::BroadcastTeamPartyProperty(void)
{
    LIFT_STUB(0x5f04e0);
}

// 0x5f0970
int __cdecl Pc::GetTeamMembers(unsigned __int64 *const)
{
    LIFT_STUB(0x5f0970);
}

// 0x5f0a90
unsigned short __cdecl Pc::FetchPartyProperty(char *, unsigned short)
{
    LIFT_STUB(0x5f0a90);
}

// 0x5f0bd0
unsigned short __cdecl Pc::FetchTeamProperty(char *, unsigned short)
{
    LIFT_STUB(0x5f0bd0);
}

// 0x5f0d10
::Pointer2< ::User> __cdecl Pc::GetUserPtr(void)
{
    LIFT_STUB(0x5f0d10);
}

// 0x5f0d70
__int64 __cdecl Pc::GetSessionId(void)
{
    LIFT_STUB(0x5f0d70);
}

// 0x5f0df0
void __cdecl Pc::GetGameAccountId(int, wchar_t *const)
{
    LIFT_STUB(0x5f0df0);
}

// 0x5f0f00
void __cdecl Pc::SetIpAddress(unsigned long)
{
    LIFT_STUB(0x5f0f00);
}

// 0x5f0f90
wchar_t const * __cdecl Pc::GetUserExternalAccountKeyString(void)
{
    LIFT_STUB(0x5f0f90);
}

// 0x5f0fe0
unsigned int __cdecl Pc::GetUserGamePlayRestrictLevel(void)
{
    LIFT_STUB(0x5f0fe0);
}

// 0x5f1030
int __cdecl Pc::GetUserGamePlayRestrictLevelRatio(void)
{
    LIFT_STUB(0x5f1030);
}

// 0x5f1080
void __cdecl Pc::UpdatePartyDifficultyType(bool, unsigned __int64, unsigned __int64, char)
{
    LIFT_STUB(0x5f1080);
}

// 0x5f1110
int __cdecl Pc::GetPartyMembers(unsigned __int64 *const)
{
    LIFT_STUB(0x5f1110);
}

// 0x5f1250
void __cdecl Pc::SetTeamInfo(unsigned __int64, unsigned __int64, char, ::Team *)
{
    LIFT_STUB(0x5f1250);
}

// 0x5f12d0
void __cdecl Pc::ClearTeamInfo(::LeavePartyReason, bool, ::TeamPartyProxy *)
{
    LIFT_STUB(0x5f12d0);
}

// 0x5f1460
bool __cdecl Pc::AssignChasePosition(::vector16 const &, int, int *)
{
    LIFT_STUB(0x5f1460);
}

// 0x5f1610
bool __cdecl Pc::ChaseTicketToPos(int, int, ::vector16 *)
{
    LIFT_STUB(0x5f1610);
}

// 0x5f17f0
void __cdecl Pc::ClearChasePosition(int)
{
    LIFT_STUB(0x5f17f0);
}

// 0x5f18b0
bool __cdecl Pc::takeFactionScore(::Pc *)
{
    LIFT_STUB(0x5f18b0);
}

// 0x5f1a20
int __cdecl Pc::DistributeFactionScoreToPc(int, unsigned __int64, char)
{
    LIFT_STUB(0x5f1a20);
}

// 0x5f2680
void __cdecl Pc::DistributeFactionScore(int, ::Creature *)
{
    LIFT_STUB(0x5f2680);
}

// 0x5f4160
::GameFailReason __cdecl Pc::TalkStart(::Npc *)
{
    LIFT_STUB(0x5f4160);
}

// 0x5f42a0
bool __cdecl Pc::TalkStop(::Npc *)
{
    LIFT_STUB(0x5f42a0);
}

// 0x5f4320
bool __cdecl Pc::TalkInterrupted(::Npc *, bool, wchar_t const *)
{
    LIFT_STUB(0x5f4320);
}

// 0x5f43d0
bool __cdecl Pc::AddConvoy(::Convoy *)
{
    LIFT_STUB(0x5f43d0);
}

// 0x5f44a0
void __cdecl Pc::RemoveConvoy(void)
{
    LIFT_STUB(0x5f44a0);
}

// 0x5f4530
int __cdecl Pc::SetDbClientOptionData(short, char const *, int)
{
    LIFT_STUB(0x5f4530);
}

// 0x5f46a0
short __cdecl Pc::FetchDiscoveryArea(char *, short)
{
    LIFT_STUB(0x5f46a0);
}

// 0x5f4730
short __cdecl Pc::FetchActivatedTeleport(char *, short)
{
    LIFT_STUB(0x5f4730);
}

// 0x5f47c0
short __cdecl Pc::FetchSkillSkinAcquired(char *, short)
{
    LIFT_STUB(0x5f47c0);
}

// 0x5f4850
short __cdecl Pc::FetchMentoringProperty(char *, short)
{
    LIFT_STUB(0x5f4850);
}

// 0x5f48e0
bool __cdecl Pc::CheckActivatedTeleport(short)
{
    LIFT_STUB(0x5f48e0);
}

// 0x5f49f0
bool __cdecl Pc::CheckSkillSkinProperty(short)
{
    LIFT_STUB(0x5f49f0);
}

// 0x5f4b30
bool __cdecl Pc::SetDiscoveryAreaBit(short)
{
    LIFT_STUB(0x5f4b30);
}

// 0x5f4cd0
bool __cdecl Pc::SetActivatedTeleportBit(short, unsigned char, bool)
{
    LIFT_STUB(0x5f4cd0);
}

// 0x5f4ec0
void __cdecl Pc::SetActivatedTeleport(unsigned char)
{
    LIFT_STUB(0x5f4ec0);
}

// 0x5f5250
bool __cdecl Pc::SetSkillSkinAcquiredBit(short, bool)
{
    LIFT_STUB(0x5f5250);
}

// 0x5f5440
bool __cdecl Pc::SetMentoringType(char, short)
{
    LIFT_STUB(0x5f5440);
}

// 0x5f56e0
bool __cdecl Pc::IncreaseMentoringFinishCount(::Pc *)
{
    LIFT_STUB(0x5f56e0);
}

// 0x5f5ac0
bool __cdecl Pc::SetMentoringFinishCount(char)
{
    LIFT_STUB(0x5f5ac0);
}

// 0x5f5b90
int __cdecl Pc::GetPartyMembersForDistribute(::Pc **, ::vector16 const &, int, bool, bool)
{
    LIFT_STUB(0x5f5b90);
}

// 0x5f5dc0
void __cdecl Pc::ReleaseMembersForDistribute(::Pc **, int)
{
    LIFT_STUB(0x5f5dc0);
}

// 0x5f5ee0
int __cdecl Pc::GetTeamMembersForDistribute(::Pc **, ::vector16 const &, int, bool)
{
    LIFT_STUB(0x5f5ee0);
}

// 0x5f60a0
bool __cdecl Pc::UpdateLogoutTime(void)
{
    LIFT_STUB(0x5f60a0);
}

// 0x5f60e0
void __cdecl Pc::StartCombat(void)
{
    LIFT_STUB(0x5f60e0);
}

// 0x5f6620
void __cdecl Pc::FinishCombat(void)
{
    LIFT_STUB(0x5f6620);
}

// 0x5f6ba0
void __cdecl Pc::ChangeGradeExpirationTimeForDebug(int, __int64)
{
    LIFT_STUB(0x5f6ba0);
}

// 0x5f6c80
bool __cdecl Pc::AddAndActivateGrade(::GradeInfo &)
{
    LIFT_STUB(0x5f6c80);
}

// 0x5f6e80
bool __cdecl Pc::DeleteGrade(int)
{
    LIFT_STUB(0x5f6e80);
}

// 0x5f7000
void __cdecl Pc::ActivateAllGradeBenefits(void)
{
    LIFT_STUB(0x5f7000);
}
