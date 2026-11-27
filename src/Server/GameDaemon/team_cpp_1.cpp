// team_cpp_1.cpp: team.cpp part 1 (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "team.h"
#include "pc.h"
#include "teamparty.h"
#include "LiftStub.h"

// 0x1eff00
__cdecl TeamPartyIdManager::~TeamPartyIdManager(void)
{
    LIFT_STUB(0x1eff00);
}

// 0x1eff60
bool __cdecl TeamPartyIdManager::Initialize(unsigned int)
{
    LIFT_STUB(0x1eff60);
}

// 0x1f0000
unsigned __int64 __cdecl TeamPartyIdManager::Make(void)
{
    LIFT_STUB(0x1f0000);
}

// 0x1f0120
void __cdecl TeamPartyIdManager::Remove(unsigned __int64)
{
    LIFT_STUB(0x1f0120);
}

// 0x1f0220
bool __cdecl TeamPartyIdManager::IsExist(unsigned __int64)
{
    LIFT_STUB(0x1f0220);
}

// 0x1f0350
__cdecl TeamManager::TeamManager(unsigned int)
{
    LIFT_STUB(0x1f0350);
}

// 0x1f04b0
__cdecl TeamManager::~TeamManager(void)
{
    LIFT_STUB(0x1f04b0);
}

// 0x1f0680
bool __cdecl TeamManager::Initialize(unsigned int, unsigned int, unsigned int)
{
    LIFT_STUB(0x1f0680);
}

// 0x1f0880
void __cdecl TeamManager::Clear(void)
{
    LIFT_STUB(0x1f0880);
}

// 0x1f09b0
::Team * __cdecl TeamManager::AcquireAndLockTeamByPcId(unsigned __int64, unsigned __int64, ::TeamMemberIndex *)
{
    LIFT_STUB(0x1f09b0);
}

// 0x1f0cb0
::Team * __cdecl TeamManager::AcquireAndLockTeamByPartyId(unsigned __int64, int *)
{
    LIFT_STUB(0x1f0cb0);
}

// 0x1f0e00
::Team * __cdecl TeamManager::AcquireAndLockTeamById(unsigned __int64)
{
    LIFT_STUB(0x1f0e00);
}

// 0x1f0eb0
void __cdecl TeamManager::ReleaseAndUnlockTeam(::Team *)
{
    LIFT_STUB(0x1f0eb0);
}

// 0x1f0f00
void __cdecl TeamManager::ReservePartyMember(::Pc *, ::Pc *, unsigned int, char)
{
    LIFT_STUB(0x1f0f00);
}

// 0x1f1a60
void __cdecl TeamManager::ConfirmPartyMember(::Pc *, unsigned int, char, char)
{
    LIFT_STUB(0x1f1a60);
}

// 0x1f24a0
void __cdecl TeamManager::LeavePartyMember(::Pc *, unsigned __int64, ::LeavePartyReason, bool)
{
    LIFT_STUB(0x1f24a0);
}

// 0x1f2b40
short __cdecl TeamManager::LeaveTeamParty(::Pc *, unsigned __int64, ::LeavePartyReason)
{
    LIFT_STUB(0x1f2b40);
}

// 0x1f3a70
void __cdecl TeamManager::BanishFromParty(::Pc *, char, bool)
{
    LIFT_STUB(0x1f3a70);
}

// 0x1f4400
void __cdecl TeamManager::BanishFromTeam(::Pc *, short, char)
{
    LIFT_STUB(0x1f4400);
}

// 0x1f4c60
void __cdecl TeamManager::TeamMemberPartyChange(::Pc *, short, char, __int64, short, char, __int64)
{
    LIFT_STUB(0x1f4c60);
}

// 0x1f6cf0
void __cdecl TeamManager::ConfirmTeamMemberPartyChange(::Pc *, unsigned int, char, char, ::LeavePartyMemberResult *)
{
    LIFT_STUB(0x1f6cf0);
}

// 0x1f7710
void __cdecl TeamManager::LogoutPc(::Pc *)
{
    LIFT_STUB(0x1f7710);
}

// 0x1f7c70
void __cdecl TeamManager::RejoinPc(::Pc *, ::JoinPartyReason, char *)
{
    LIFT_STUB(0x1f7c70);
}

// 0x1f80a0
void __cdecl TeamManager::ClearExpiredPartyMember(::Pc *)
{
    LIFT_STUB(0x1f80a0);
}

// 0x1f88a0
void __cdecl TeamManager::DismissPartyIfSolo(::Pc *)
{
    LIFT_STUB(0x1f88a0);
}

// 0x1f8ea0
void __cdecl TeamManager::MoveToArenaFailed(unsigned __int64, bool)
{
    LIFT_STUB(0x1f8ea0);
}

// 0x1f93f0
bool __cdecl TeamManager::CreatePartyByMove(unsigned __int64, unsigned __int64, ::ArenaLobbyTeamInfo const *, char, bool)
{
    LIFT_STUB(0x1f93f0);
}

// 0x1f9650
void __cdecl TeamManager::CreateParty(::Pc *, char, bool)
{
    LIFT_STUB(0x1f9650);
}

// 0x1f9a00
void __cdecl TeamManager::RemoveTimeoutReservedParty(__int64, __int64)
{
    LIFT_STUB(0x1f9a00);
}

// 0x1f9d10
void __cdecl TeamManager::ConfirmPartyMemberFailed(::Pc *, unsigned int, char)
{
    LIFT_STUB(0x1f9d10);
}

// 0x1fa300
void __cdecl TeamManager::AcceptRejoinPartyMember(unsigned __int64, wchar_t const *, char)
{
    LIFT_STUB(0x1fa300);
}

// 0x1fa670
void __cdecl TeamManager::RejectRejoinPartyMember(unsigned __int64, wchar_t const *, ::LeavePartyReason, char)
{
    LIFT_STUB(0x1fa670);
}

// 0x1fab70
unsigned __int64 __cdecl TeamManager::GetTeamLeaderId(unsigned __int64) const
{
    LIFT_STUB(0x1fab70);
}

// 0x1fabf0
unsigned __int64 __cdecl TeamManager::FindZone(unsigned __int64, unsigned int)
{
    LIFT_STUB(0x1fabf0);
}

// 0x1faca0
bool __cdecl TeamManager::IsEnteredTeamMemberByAttraction(unsigned __int64, unsigned __int64, int)
{
    LIFT_STUB(0x1faca0);
}

// 0x1fad30
unsigned __int64 __cdecl TeamManager::GetPartyId(unsigned __int64, unsigned __int64) const
{
    LIFT_STUB(0x1fad30);
}

// 0x1fade0
char __cdecl TeamManager::GetPartyDifficultyType(unsigned __int64, unsigned __int64) const
{
    LIFT_STUB(0x1fade0);
}

// 0x1fae90
char __cdecl TeamManager::GetPartyDifficultyType(unsigned __int64) const
{
    LIFT_STUB(0x1fae90);
}

// 0x1faf40
bool __cdecl TeamManager::IsPartyLeader(unsigned __int64, unsigned __int64) const
{
    LIFT_STUB(0x1faf40);
}

// 0x1fb020
unsigned __int64 __cdecl TeamManager::GetPartyLeaderDbId(unsigned __int64) const
{
    LIFT_STUB(0x1fb020);
}

// 0x1fb0d0
unsigned __int64 __cdecl TeamManager::GetPartyLeaderId(unsigned __int64) const
{
    LIFT_STUB(0x1fb0d0);
}

// 0x1fb180
int __cdecl TeamManager::GetPartyMemberCount(unsigned __int64, unsigned __int64) const
{
    LIFT_STUB(0x1fb180);
}

// 0x1fb250
void __cdecl TeamManager::SuggestParty(::Pc *, ::Pc *, char, char, char, char, char, char)
{
    LIFT_STUB(0x1fb250);
}

// 0x1fb350
void __cdecl TeamManager::DelegatePartyLeader(::Pc *, ::Pc *)
{
    LIFT_STUB(0x1fb350);
}

// 0x1fb700
void __cdecl TeamManager::DelegateTeamLeader(::Pc *, ::Pc *)
{
    LIFT_STUB(0x1fb700);
}

// 0x1fc240
void __cdecl TeamManager::NominatePartyLeader(::Pc *, ::Pc *)
{
    LIFT_STUB(0x1fc240);
}

// 0x1fc8e0
void __cdecl TeamManager::SetTeamInviteAuth(::Pc *, ::TeamInviteAuth)
{
    LIFT_STUB(0x1fc8e0);
}

// 0x1fca50
void __cdecl TeamManager::ChangeTeamPartyDifficultyType(::Pc *, char, char)
{
    LIFT_STUB(0x1fca50);
}

// 0x1fcd00
void __cdecl TeamManager::ChangePartyOption(::Pc *, ::PartyPickupRule, char, unsigned __int64, __int64)
{
    LIFT_STUB(0x1fcd00);
}

// 0x1fce70
void __cdecl TeamManager::ChangePartyInviteAuth(::Pc *, ::PartyInviteAuth)
{
    LIFT_STUB(0x1fce70);
}

// 0x1fcfd0
bool __cdecl TeamManager::StopCinematic(::Pc *, unsigned int)
{
    LIFT_STUB(0x1fcfd0);
}

// 0x1fd100
void __cdecl TeamManager::ChangePartyDifficultyType(::Pc *, char)
{
    LIFT_STUB(0x1fd100);
}

// 0x1fd3c0
short __cdecl TeamManager::CheckInviteTeamToTeam(char, unsigned __int64, unsigned __int64, unsigned __int64, unsigned __int64, ::InviteTeamGameLogInfo *)
{
    LIFT_STUB(0x1fd3c0);
}

// 0x1fd5f0
short __cdecl TeamManager::ReserveTeamMember(char, ::Pc *, ::Pc *)
{
    LIFT_STUB(0x1fd5f0);
}

// 0x1fe930
short __cdecl TeamManager::ConfirmTeamMember(char, ::Pc *, char)
{
    LIFT_STUB(0x1fe930);
}

// 0x1ff3b0
void __cdecl TeamManager::ConfirmTeamMemberFailed(char, ::Pc *)
{
    LIFT_STUB(0x1ff3b0);
}

// 0x1ff940
void __cdecl TeamManager::ClearPartyAuction(unsigned __int64, unsigned __int64)
{
    LIFT_STUB(0x1ff940);
}

// 0x1ffa10
bool __cdecl TeamManager::AddPartyPrepareZoneMember(unsigned __int64, unsigned __int64)
{
    LIFT_STUB(0x1ffa10);
}

// 0x1ffb00
void __cdecl TeamManager::DelPartyPrepareZoneMember(unsigned __int64, unsigned __int64)
{
    LIFT_STUB(0x1ffb00);
}

// 0x1ffbe0
short __cdecl TeamManager::GetPartyDungeonId(unsigned __int64) const
{
    LIFT_STUB(0x1ffbe0);
}

// 0x1ffcb0
bool __cdecl TeamManager::UpdatePartyDungeonStep(unsigned __int64, unsigned __int64, short, char, bool)
{
    LIFT_STUB(0x1ffcb0);
}

// 0x1ffdc0
int __cdecl TeamManager::GetPartyDungeonMaxMemberCount(unsigned __int64, unsigned __int64) const
{
    LIFT_STUB(0x1ffdc0);
}

// 0x1ffea0
unsigned __int64 __cdecl TeamManager::GetPartyChallengePartyAttractionId(unsigned __int64) const
{
    LIFT_STUB(0x1ffea0);
}

// 0x1fff70
char __cdecl TeamManager::GetPartyChallengePartyAttractionMode(unsigned __int64) const
{
    LIFT_STUB(0x1fff70);
}

// 0x200050
short __cdecl TeamManager::CheckPartyChallengePartyAttractionCondition(unsigned __int64, __int64, unsigned __int64, char)
{
    LIFT_STUB(0x200050);
}

// 0x200150
unsigned __int64 __cdecl TeamManager::FindPartyZone(unsigned __int64, unsigned __int64, unsigned int) const
{
    LIFT_STUB(0x200150);
}

// 0x200230
unsigned __int64 __cdecl TeamManager::FindPartyZone(unsigned __int64, unsigned int) const
{
    LIFT_STUB(0x200230);
}

// 0x200310
bool __cdecl TeamManager::EnterPartyZone(unsigned __int64, unsigned __int64, unsigned __int64, unsigned int, char, char)
{
    LIFT_STUB(0x200310);
}

// 0x2003e0
void __cdecl TeamManager::SetPartyZoneMemberState(unsigned __int64, unsigned __int64, unsigned __int64, unsigned int, ::TeamParty::ZoneMemberState)
{
    LIFT_STUB(0x2003e0);
}

// 0x200590
short __cdecl TeamManager::ReserveArenaLobbyPartyRequest(unsigned __int64, unsigned __int64, ::Data::ArenaPortalRecordPtr, char)
{
    LIFT_STUB(0x200590);
}

// 0x2006a0
short __cdecl TeamManager::StartPartyArenaLobbyReservation(unsigned __int64, unsigned __int64)
{
    LIFT_STUB(0x2006a0);
}

// 0x200780
void __cdecl TeamManager::CancelPartyArenaLobbyReservation(unsigned __int64, unsigned __int64, short)
{
    LIFT_STUB(0x200780);
}

// 0x200850
short __cdecl TeamManager::SetPartyReserveArenaLobbyState(unsigned __int64, unsigned __int64, char)
{
    LIFT_STUB(0x200850);
}

// 0x200940
short __cdecl TeamManager::ReturnToArenaLobbyPartyRequest(::Pc *, ::Data::ArenaPortalRecordPtr, char, char, char)
{
    LIFT_STUB(0x200940);
}

// 0x200a40
bool __cdecl TeamManager::ReserveReinforcedPartyMember(unsigned __int64, unsigned __int64, unsigned int, unsigned __int64, char, ::ArenaLobbyTeamInfo const &)
{
    LIFT_STUB(0x200a40);
}

// 0x201370
bool __cdecl TeamManager::IsExist(unsigned __int64)
{
    LIFT_STUB(0x201370);
}

// 0x2013e0
unsigned int __cdecl TeamManager::toPcIndex(unsigned __int64) const
{
    LIFT_STUB(0x2013e0);
}

// 0x201460
unsigned int __cdecl TeamManager::toPartyIndex(unsigned __int64) const
{
    LIFT_STUB(0x201460);
}

// 0x2014e0
void __cdecl TeamManager::sort(::Team **const, int, int)
{
    LIFT_STUB(0x2014e0);
}

// 0x2015d0
::Team * __cdecl TeamManager::findTeamById(unsigned __int64)
{
    LIFT_STUB(0x2015d0);
}

// 0x2016e0
::Team * __cdecl TeamManager::findTeamByPcId(unsigned __int64)
{
    LIFT_STUB(0x2016e0);
}

// 0x2017f0
::Team * __cdecl TeamManager::findTeamByWaitingPcId(unsigned __int64)
{
    LIFT_STUB(0x2017f0);
}

// 0x201900
::Team * __cdecl TeamManager::findTeamByLogoutPcDbId(unsigned __int64)
{
    LIFT_STUB(0x201900);
}

// 0x201970
::Team * __cdecl TeamManager::findTeamByReserveArenaPcDbId(unsigned __int64)
{
    LIFT_STUB(0x201970);
}

// 0x2019e0
::Team * __cdecl TeamManager::findTeamByPartyId(unsigned __int64)
{
    LIFT_STUB(0x2019e0);
}

// 0x201af0
bool __cdecl TeamManager::findTeamListByPcId(unsigned __int64, unsigned __int64, ::Team **const)
{
    LIFT_STUB(0x201af0);
}

// 0x201c30
bool __cdecl TeamManager::addTeam(unsigned __int64, unsigned __int64, unsigned __int64, ::Team *)
{
    LIFT_STUB(0x201c30);
}

// 0x201e50
bool __cdecl TeamManager::addTeam(::ArenaLobbyTeamInfo const *, unsigned __int64, unsigned __int64, ::Team *)
{
    LIFT_STUB(0x201e50);
}

// 0x202040
void __cdecl TeamManager::removeTeam(unsigned __int64)
{
    LIFT_STUB(0x202040);
}

// 0x202120
void __cdecl TeamManager::updatePcWaitingTeam(unsigned __int64, unsigned __int64)
{
    LIFT_STUB(0x202120);
}

// 0x202250
void __cdecl TeamManager::removePcWaitingTeam(unsigned __int64)
{
    LIFT_STUB(0x202250);
}

// 0x202310
void __cdecl TeamManager::updatePcTeam(unsigned __int64, unsigned __int64)
{
    LIFT_STUB(0x202310);
}

// 0x202400
void __cdecl TeamManager::removePcTeam(unsigned __int64)
{
    LIFT_STUB(0x202400);
}

// 0x2024c0
void __cdecl TeamManager::updateLogoutPcTeam(unsigned __int64, unsigned __int64)
{
    LIFT_STUB(0x2024c0);
}

// 0x202560
void __cdecl TeamManager::removeLogoutPcTeam(unsigned __int64)
{
    LIFT_STUB(0x202560);
}
