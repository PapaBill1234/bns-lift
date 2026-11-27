// team_cpp_2.cpp: team.cpp part 2 (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "team.h"
#include "partyauction.h"
#include "pc.h"
#include "teamparty.h"
#include "LiftStub.h"

// 0x2025e0
void __cdecl TeamManager::updateReserveArenaPcTeam(unsigned __int64, unsigned __int64)
{
    LIFT_STUB(0x2025e0);
}

// 0x202680
void __cdecl TeamManager::removeReserveArenaPcTeam(unsigned __int64)
{
    LIFT_STUB(0x202680);
}

// 0x202700
void __cdecl TeamManager::updatePartyTeam(unsigned __int64, unsigned __int64)
{
    LIFT_STUB(0x202700);
}

// 0x2027f0
void __cdecl TeamManager::removePartyTeam(unsigned __int64)
{
    LIFT_STUB(0x2027f0);
}

// 0x2028c0
void __cdecl TeamManager::lock(void)
{
    LIFT_STUB(0x2028c0);
}

// 0x202980
void __cdecl TeamManager::unlock(void)
{
    LIFT_STUB(0x202980);
}

// 0x2029b0
void __cdecl TeamManager::lockAndAddRefTeam(::Team *)
{
    LIFT_STUB(0x2029b0);
}

// 0x202a70
void __cdecl TeamManager::lockAndAddRefTeams(::Team **const, int)
{
    LIFT_STUB(0x202a70);
}

// 0x202c20
void __cdecl TeamManager::unlockAndDelRefTeams(::Team **const, int)
{
    LIFT_STUB(0x202c20);
}

// 0x202d60
bool __cdecl TeamManager::postConfirmPartyMemberTask(::Pc *, unsigned int, char, char) const
{
    LIFT_STUB(0x202d60);
}

// 0x202f90
bool __cdecl TeamManager::postLeaveTeamMemberTask(::Pc *, ::Pc *, ::LeavePartyReason)
{
    LIFT_STUB(0x202f90);
}

// 0x2031b0
bool __cdecl TeamManager::postConfirmTeamMemberTask(char, ::Pc *, ::Pc *, char) const
{
    LIFT_STUB(0x2031b0);
}

// 0x2033f0
bool __cdecl TeamManager::postConfirmTeamMemberPartyChangeTask(::Pc *, unsigned int, char, char, ::LeavePartyMemberResult *) const
{
    LIFT_STUB(0x2033f0);
}

// 0x2035f0
void __cdecl TeamManager::onTeamDestoryed(::Pc *, unsigned __int64, ::LeavePartyReason, ::LeavePartyMemberResult const *, ::Team *, ::DismissPartyLogInfo const *)
{
    LIFT_STUB(0x2035f0);
}

// 0x204bd0
void __cdecl TeamManager::onTeamDestoryed(unsigned __int64, unsigned __int64, ::LeavePartyReason, ::LeavePartyMemberResult const *, ::DismissPartyLogInfo const *)
{
    LIFT_STUB(0x204bd0);
}

// 0x205be0
int __cdecl Team::GetMemberCount(void) const
{
    LIFT_STUB(0x205be0);
}

// 0x205c20
int __cdecl Team::GetMembers(unsigned __int64 *const) const
{
    LIFT_STUB(0x205c20);
}

// 0x205ce0
void __cdecl Team::Broadcast(::Packet const *) const
{
    LIFT_STUB(0x205ce0);
}

// 0x205d50
unsigned __int64 __cdecl Team::FindZone(unsigned int)
{
    LIFT_STUB(0x205d50);
}

// 0x205e20
bool __cdecl Team::UnoccupyRaidDungeon(void)
{
    LIFT_STUB(0x205e20);
}

// 0x205fe0
bool __cdecl Team::IsEnteredTeamMemberByAttraction(int)
{
    LIFT_STUB(0x205fe0);
}

// 0x206060
int __cdecl Team::MakeParty(int, unsigned __int64, unsigned __int64, char, ::TeamParty::MemberAppearance *, short)
{
    LIFT_STUB(0x206060);
}

// 0x2062f0
char __cdecl Team::GetPartyDifficultyType(int) const
{
    LIFT_STUB(0x2062f0);
}

// 0x206320
int __cdecl Team::GetPartyMemberCount(int) const
{
    LIFT_STUB(0x206320);
}

// 0x206380
int __cdecl Team::GetPartyMembers(unsigned __int64, unsigned __int64, unsigned __int64 *const) const
{
    LIFT_STUB(0x206380);
}

// 0x2066a0
int __cdecl Team::GetPartyMembers(int, unsigned __int64 *const) const
{
    LIFT_STUB(0x2066a0);
}

// 0x206730
bool __cdecl Team::IsPartyMember(int, unsigned __int64) const
{
    LIFT_STUB(0x206730);
}

// 0x2067c0
bool __cdecl Team::CanDestroy(void) const
{
    LIFT_STUB(0x2067c0);
}

// 0x206860
void __cdecl Team::SuggestParty(::TeamMemberIndex const *, ::Pc *, ::Pc *, char, char, char, char, char, char)
{
    LIFT_STUB(0x206860);
}

// 0x206e00
bool __cdecl Team::StopCinematic(::TeamMemberIndex const *, unsigned int)
{
    LIFT_STUB(0x206e00);
}

// 0x207100
short __cdecl Team::CheckInvitePcToTeam(unsigned __int64, unsigned __int64, ::TeamMemberIndex const *, ::InviteTeamGameLogInfo *)
{
    LIFT_STUB(0x207100);
}

// 0x2072d0
short __cdecl Team::CheckJoinTeamToOtherTeam(void)
{
    LIFT_STUB(0x2072d0);
}

// 0x207370
short __cdecl Team::CheckInviteTeamToTeam(char, unsigned __int64, unsigned __int64, ::InviteTeamGameLogInfo *)
{
    LIFT_STUB(0x207370);
}

// 0x207720
unsigned __int64 __cdecl Team::GetPartyPickupMemberByPickupRule(int)
{
    LIFT_STUB(0x207720);
}

// 0x2077d0
::PartyAuction * __cdecl Team::GetPartyAuction(int, unsigned __int64) const
{
    LIFT_STUB(0x2077d0);
}

// 0x2078c0
bool __cdecl Team::AddPartyAuction(int, unsigned __int64, ::PartyAuction *)
{
    LIFT_STUB(0x2078c0);
}

// 0x207970
char __cdecl Team::GetPartyDungeonStep(int, short) const
{
    LIFT_STUB(0x207970);
}

// 0x2079e0
unsigned __int64 __cdecl Team::GetPartyChallengePartyAttractionId(int) const
{
    LIFT_STUB(0x2079e0);
}

// 0x207a40
bool __cdecl Team::PartyIsInChallengePartyAttraction(int) const
{
    LIFT_STUB(0x207a40);
}

// 0x207aa0
bool __cdecl Team::EnterPartyZone(::TeamMemberIndex const *, unsigned __int64, unsigned int, char, char)
{
    LIFT_STUB(0x207aa0);
}

// 0x207b70
void __cdecl Team::CancelPartyArenaLobbyReservation(int, short)
{
    LIFT_STUB(0x207b70);
}

// 0x207bd0
short __cdecl Team::ReturnToArenaLobbyPartyRequest(int, ::Pc *, ::Data::ArenaPortalRecordPtr, char, char, char)
{
    LIFT_STUB(0x207bd0);
}

// 0x207cb0
bool __cdecl Team::IsPublishedRecruitArenaDungeonPartyMember(int)
{
    LIFT_STUB(0x207cb0);
}

// 0x207d10
__cdecl Team::Team(void)
{
    LIFT_STUB(0x207d10);
}

// 0x207e30
__cdecl Team::~Team(void)
{
    LIFT_STUB(0x207e30);
}

// 0x207f60
bool __cdecl Team::initialize(unsigned __int64, unsigned __int64, ::Pc const *, char, int)
{
    LIFT_STUB(0x207f60);
}

// 0x208320
bool __cdecl Team::initialize(unsigned __int64, unsigned __int64, unsigned __int64, ::ArenaLobbyTeamInfo const *, char, int, bool)
{
    LIFT_STUB(0x208320);
}

// 0x208740
bool __cdecl Team::reservePartyMember(::Pc const *, ::Pc const *)
{
    LIFT_STUB(0x208740);
}

// 0x208880
bool __cdecl Team::reservePartyMember(char, ::Pc const *, short)
{
    LIFT_STUB(0x208880);
}

// 0x2089a0
bool __cdecl Team::reservePartyMember(char, unsigned __int64, unsigned __int64, ::TeamParty::MemberAppearance *, short, ::PartyMemberState)
{
    LIFT_STUB(0x2089a0);
}

// 0x208ca0
bool __cdecl Team::confirmPartyMember(::TeamMemberIndex const *)
{
    LIFT_STUB(0x208ca0);
}

// 0x208e20
void __cdecl Team::leavePartyMember(::TeamMemberIndex const *, ::LeavePartyMemberResult *)
{
    LIFT_STUB(0x208e20);
}

// 0x209060
bool __cdecl Team::dismissPartyIfSolo(::TeamMemberIndex const *, ::LeavePartyMemberResult *)
{
    LIFT_STUB(0x209060);
}

// 0x209300
void __cdecl Team::moveToArenaFailed(::TeamMemberIndex const *, ::LeavePartyMemberResult *)
{
    LIFT_STUB(0x209300);
}

// 0x209480
void __cdecl Team::logoutPartyMember(::TeamMemberIndex const *, ::LeavePartyMemberResult *)
{
    LIFT_STUB(0x209480);
}

// 0x2096b0
bool __cdecl Team::findMember(unsigned __int64, unsigned __int64, ::PartyMemberState, ::TeamMember *, ::TeamMemberIndex *) const
{
    LIFT_STUB(0x2096b0);
}

// 0x2098f0
bool __cdecl Team::findParty(unsigned __int64, int *) const
{
    LIFT_STUB(0x2098f0);
}

// 0x2099d0
void __cdecl Team::clearExpiredPartyMembers(::TeamMemberIndex const *, ::ClearExpiredPartyMemberResult *)
{
    LIFT_STUB(0x2099d0);
}

// 0x209b30
bool __cdecl Team::rejoinPartyMember(::Pc const *, ::TeamMemberIndex *, ::RejoinPartyMemberResult *)
{
    LIFT_STUB(0x209b30);
}

// 0x209c80
bool __cdecl Team::choiceRejoinPartyMemberNotify(int, unsigned __int64, wchar_t const *, char)
{
    LIFT_STUB(0x209c80);
}

// 0x209d40
void __cdecl Team::onCreated(::Pc *, unsigned int, ::JoinPartyLogInfo *)
{
    LIFT_STUB(0x209d40);
}

// 0x209f90
void __cdecl Team::onJoined(::Pc *, ::TeamMemberIndex const *, unsigned int, char, ::JoinPartyLogInfo *)
{
    LIFT_STUB(0x209f90);
}

// 0x20a2a0
void __cdecl Team::onLeaved(::Pc *, int, unsigned __int64, ::LeavePartyReason, ::LeavePartyMemberResult const *, ::DismissPartyLogInfo const *)
{
    LIFT_STUB(0x20a2a0);
}

// 0x20a520
void __cdecl Team::onLeaved(unsigned __int64, int, unsigned __int64, ::LeavePartyReason, ::LeavePartyMemberResult const *, bool, ::DismissPartyLogInfo const *)
{
    LIFT_STUB(0x20a520);
}

// 0x20a7a0
void __cdecl Team::onPartySwaped(::Pc *, ::TeamMemberIndex const *, unsigned int, char, ::LeavePartyMemberResult *, ::DismissPartyLogInfo const *)
{
    LIFT_STUB(0x20a7a0);
}

// 0x20aa50
void __cdecl Team::onPromoted(::Pc *, unsigned int)
{
    LIFT_STUB(0x20aa50);
}

// 0x20ac40
void __cdecl Team::onClearExpired(::ClearExpiredPartyMemberResult *, int, bool)
{
    LIFT_STUB(0x20ac40);
}

// 0x20ae40
void __cdecl Team::onLogout(::Pc *, ::TeamMemberIndex const *, bool, bool)
{
    LIFT_STUB(0x20ae40);
}

// 0x20b120
void __cdecl Team::onRejoin(::Pc *, ::TeamMemberIndex const *, ::RejoinPartyMemberResult const *, ::JoinPartyReason)
{
    LIFT_STUB(0x20b120);
}

// 0x20b4b0
void __cdecl Team::onMoveToArenaFailed(unsigned __int64, int, ::LeavePartyReason, ::LeavePartyMemberResult const *)
{
    LIFT_STUB(0x20b4b0);
}

// 0x20b670
void __cdecl Team::onPartyDestoryed(::Pc *, unsigned __int64, ::LeavePartyReason, ::LeavePartyMemberResult const *, ::DismissPartyLogInfo const *)
{
    LIFT_STUB(0x20b670);
}

// 0x20cd40
void __cdecl Team::onPartyDestoryed(unsigned __int64, unsigned __int64, ::LeavePartyReason, ::LeavePartyMemberResult const *, ::DismissPartyLogInfo const *)
{
    LIFT_STUB(0x20cd40);
}

// 0x20df90
void __cdecl Team::SendLeaveTeam(::Pc *, int, ::LeavePartyReason)
{
    LIFT_STUB(0x20df90);
}

// 0x20e0e0
bool __cdecl Team::initPartyList(int)
{
    LIFT_STUB(0x20e0e0);
}

// 0x20e1d0
bool __cdecl Team::addParty(int, ::TeamParty *)
{
    LIFT_STUB(0x20e1d0);
}

// 0x20e3a0
void __cdecl Team::removeParty(int)
{
    LIFT_STUB(0x20e3a0);
}

// 0x20e490
void __cdecl Team::removePartyIndex(int)
{
    LIFT_STUB(0x20e490);
}

// 0x20e580
bool __cdecl Team::findPcParty(unsigned __int64, int *) const
{
    LIFT_STUB(0x20e580);
}

// 0x20e5f0
bool __cdecl Team::addPcParty(unsigned __int64, int)
{
    LIFT_STUB(0x20e5f0);
}

// 0x20e690
void __cdecl Team::removePcParty(unsigned __int64)
{
    LIFT_STUB(0x20e690);
}

// 0x20e710
int __cdecl Team::findEmptyPartyIndex(void) const
{
    LIFT_STUB(0x20e710);
}

// 0x20e740
bool __cdecl Team::CheckInvitationAuth(char, char, unsigned __int64, unsigned __int64)
{
    LIFT_STUB(0x20e740);
}

// 0x20e900
bool __cdecl Team::reserveTeamMember(char, ::Pc const *, ::Pc const *, int *)
{
    LIFT_STUB(0x20e900);
}

// 0x20f150
bool __cdecl Team::setVisible(bool)
{
    LIFT_STUB(0x20f150);
}

// 0x20f1a0
bool __cdecl Team::setTeamLeader(unsigned __int64, unsigned __int64, ::BeTeamLeaderLogInfo *)
{
    LIFT_STUB(0x20f1a0);
}

// 0x20f740
void __cdecl Team::buildInMemberPacket(::FragmentPacket &, char)
{
    LIFT_STUB(0x20f740);
}

// 0x20f8b0
void __cdecl Team::postDismissTeamIfSoloPartyTask(void) const
{
    LIFT_STUB(0x20f8b0);
}

// 0x20fb70
__cdecl TeamBroadcastPropertyList::TeamBroadcastPropertyList(::Pc *, char, bool)
{
    LIFT_STUB(0x20fb70);
}

// 0x20fe60
__cdecl TeamBroadcastPropertyList::~TeamBroadcastPropertyList(void)
{
    LIFT_STUB(0x20fe60);
}

// 0x20ffe0
bool __cdecl TeamBroadcastPropertyList::Initialize(void)
{
    LIFT_STUB(0x20ffe0);
}

// 0x2100a0
bool __cdecl TeamBroadcastPropertyList::PropertyChange(unsigned short)
{
    LIFT_STUB(0x2100a0);
}

// 0x210220
bool __cdecl TeamBroadcastPropertyList::ConditionChangeByProperty(unsigned short)
{
    LIFT_STUB(0x210220);
}

// 0x2103d0
bool __cdecl TeamBroadcastPropertyList::ConditionChange(int, unsigned __int64, void *)
{
    LIFT_STUB(0x2103d0);
}

// 0x210490
bool __cdecl TeamBroadcastPropertyList::FetchTeamPartyPropertyData(short *, char *, short *, short *, char *, short *)
{
    LIFT_STUB(0x210490);
}

// 0x2105e0
bool __cdecl TeamBroadcastPropertyList::FetchTeamPartyConditionsPacket(::Packet *, ::RepeatPacketComposer *, ::Packet *, ::RepeatPacketComposer *)
{
    LIFT_STUB(0x2105e0);
}
