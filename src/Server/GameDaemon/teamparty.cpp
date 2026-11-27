// teamparty.cpp: teamparty.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "teamparty.h"
#include "partyauction.h"
#include "pc.h"
#include "team.h"
#include "LiftStub.h"

// 0x211170
int __cdecl TeamParty::GetMaxMemberCountByPartyType(char)
{
    LIFT_STUB(0x211170);
}

// 0x2111c0
__cdecl TeamParty::TeamParty(::Team *)
{
    LIFT_STUB(0x2111c0);
}

// 0x2113c0
__cdecl TeamParty::~TeamParty(void)
{
    LIFT_STUB(0x2113c0);
}

// 0x211450
int __cdecl TeamParty::GetMembersPcDbId(unsigned __int64 *const) const
{
    LIFT_STUB(0x211450);
}

// 0x2114e0
bool __cdecl TeamParty::CanDestroy(void) const
{
    LIFT_STUB(0x2114e0);
}

// 0x2115a0
void __cdecl TeamParty::Broadcast(::Packet const *) const
{
    LIFT_STUB(0x2115a0);
}

// 0x2116b0
bool __cdecl TeamParty::DelegateLeader(int *, int *, short)
{
    LIFT_STUB(0x2116b0);
}

// 0x211800
void __cdecl TeamParty::Suggest(int, ::Pc *, ::Pc *, char, char, char, char, char, char)
{
    LIFT_STUB(0x211800);
}

// 0x211ba0
bool __cdecl TeamParty::ChangeOption(int, ::PartyPickupRule, char, unsigned __int64, __int64)
{
    LIFT_STUB(0x211ba0);
}

// 0x2122c0
short __cdecl TeamParty::ChangeInviteAuth(int, ::PartyInviteAuth)
{
    LIFT_STUB(0x2122c0);
}

// 0x212430
bool __cdecl TeamParty::StopCinematic(int, unsigned int)
{
    LIFT_STUB(0x212430);
}

// 0x212570
short __cdecl TeamParty::ChangeDifficultyType(int, char, bool)
{
    LIFT_STUB(0x212570);
}

// 0x212cb0
void __cdecl TeamParty::Broadcast(unsigned __int64, unsigned __int64, ::Packet const *) const
{
    LIFT_STUB(0x212cb0);
}

// 0x212df0
short __cdecl TeamParty::CheckInvite(int, ::InviteTeamGameLogInfo *) const
{
    LIFT_STUB(0x212df0);
}

// 0x212fa0
void __cdecl TeamParty::FetchMemberInfoForBuilder(::Packet &) const
{
    LIFT_STUB(0x212fa0);
}

// 0x213250
bool __cdecl TeamParty::AddAuction(unsigned __int64, ::PartyAuction *)
{
    LIFT_STUB(0x213250);
}

// 0x213310
void __cdecl TeamParty::ClearAuction(unsigned __int64)
{
    LIFT_STUB(0x213310);
}

// 0x213410
bool __cdecl TeamParty::UpdateDungeonStep(short, char, bool)
{
    LIFT_STUB(0x213410);
}

// 0x213520
short __cdecl TeamParty::CheckChallengePartyAttractionCondition(__int64, unsigned __int64, char)
{
    LIFT_STUB(0x213520);
}

// 0x213720
unsigned __int64 __cdecl TeamParty::FindZone(unsigned int) const
{
    LIFT_STUB(0x213720);
}

// 0x213890
bool __cdecl TeamParty::EnterZone(int, unsigned __int64, unsigned int, char, char)
{
    LIFT_STUB(0x213890);
}

// 0x214300
void __cdecl TeamParty::LeaveZone(unsigned __int64, unsigned int, bool)
{
    LIFT_STUB(0x214300);
}

// 0x2147a0
bool __cdecl TeamParty::IsEnteredMemberByAttraction(int)
{
    LIFT_STUB(0x2147a0);
}

// 0x214840
bool __cdecl TeamParty::IsEnteredMemberInTeamPartyZone(void)
{
    LIFT_STUB(0x214840);
}

// 0x2149c0
short __cdecl TeamParty::ReserveArenaLobbyRequest(int, ::Data::ArenaPortalRecordPtr, char)
{
    LIFT_STUB(0x2149c0);
}

// 0x214b60
short __cdecl TeamParty::StartArenaLobbyReservation(int)
{
    LIFT_STUB(0x214b60);
}

// 0x215030
void __cdecl TeamParty::CancelArenaLobbyReservation(short)
{
    LIFT_STUB(0x215030);
}

// 0x215180
short __cdecl TeamParty::SetReserveArenaLobbyState(int, char)
{
    LIFT_STUB(0x215180);
}

// 0x215290
short __cdecl TeamParty::ReturnToArenaLobbyRequest(::Pc *, ::Data::ArenaPortalRecordPtr, char, char, char)
{
    LIFT_STUB(0x215290);
}

// 0x2155f0
bool __cdecl TeamParty::PublishedRecruitArenaDungeonMember(::Pc *, char)
{
    LIFT_STUB(0x2155f0);
}

// 0x2158c0
bool __cdecl TeamParty::CancelRecruitArenaDungeonMember(::Pc *, char)
{
    LIFT_STUB(0x2158c0);
}

// 0x215b70
bool __cdecl TeamParty::initialize(unsigned __int64, ::Pc const *, ::PartyMemberState, char, int, short)
{
    LIFT_STUB(0x215b70);
}

// 0x215d00
bool __cdecl TeamParty::initialize(unsigned __int64, unsigned __int64, unsigned __int64, ::TeamParty::MemberAppearance *, ::PartyMemberState, char, int, short)
{
    LIFT_STUB(0x215d00);
}

// 0x216080
bool __cdecl TeamParty::initialize(unsigned __int64, unsigned __int64, ::ArenaLobbyTeamInfo const *, char, int, bool)
{
    LIFT_STUB(0x216080);
}

// 0x216330
bool __cdecl TeamParty::reserveMember(::Pc const *, short)
{
    LIFT_STUB(0x216330);
}

// 0x216490
bool __cdecl TeamParty::reserveMember(unsigned __int64, unsigned __int64, ::TeamParty::MemberAppearance *, short, ::PartyMemberState)
{
    LIFT_STUB(0x216490);
}

// 0x216570
bool __cdecl TeamParty::checkAttractionConditionBeforeConfirm(int)
{
    LIFT_STUB(0x216570);
}

// 0x216a00
bool __cdecl TeamParty::confirmMember(int)
{
    LIFT_STUB(0x216a00);
}

// 0x216b50
void __cdecl TeamParty::leaveMember(int, ::LeavePartyMemberResult *)
{
    LIFT_STUB(0x216b50);
}

// 0x216fc0
void __cdecl TeamParty::logoutMember(int, ::LeavePartyMemberResult *)
{
    LIFT_STUB(0x216fc0);
}

// 0x2173b0
bool __cdecl TeamParty::rejoinMember(::Pc const *, int *, ::RejoinPartyMemberResult *)
{
    LIFT_STUB(0x2173b0);
}

// 0x217610
void __cdecl TeamParty::choiceRejoinMemberNotify(unsigned __int64, wchar_t const *, char)
{
    LIFT_STUB(0x217610);
}

// 0x217720
void __cdecl TeamParty::clearExpiredMembers(int, ::ClearExpiredPartyMemberResult *)
{
    LIFT_STUB(0x217720);
}

// 0x217a00
void __cdecl TeamParty::moveToArenaFailed(int, ::LeavePartyMemberResult *)
{
    LIFT_STUB(0x217a00);
}

// 0x217db0
void __cdecl TeamParty::onCreated(::Pc *, unsigned int, char, ::JoinPartyLogInfo *)
{
    LIFT_STUB(0x217db0);
}

// 0x218580
void __cdecl TeamParty::onJoined(::Pc *, int, unsigned int, char, ::JoinPartyLogInfo *)
{
    LIFT_STUB(0x218580);
}

// 0x218e90
void __cdecl TeamParty::onLeaved(::Pc *, unsigned __int64, ::LeavePartyReason, ::LeavePartyMemberResult const *, ::DismissPartyLogInfo const *)
{
    LIFT_STUB(0x218e90);
}

// 0x219f90
void __cdecl TeamParty::onLeaved(unsigned __int64, unsigned __int64, ::LeavePartyReason, ::LeavePartyMemberResult const *, bool, ::DismissPartyLogInfo const *)
{
    LIFT_STUB(0x219f90);
}

// 0x21ac50
void __cdecl TeamParty::onLogout(::Pc *, int, bool)
{
    LIFT_STUB(0x21ac50);
}

// 0x21adc0
void __cdecl TeamParty::onRejoin(::Pc *, int, ::RejoinPartyMemberResult const *, ::JoinPartyReason)
{
    LIFT_STUB(0x21adc0);
}

// 0x21b740
void __cdecl TeamParty::onMoveToArenaFailed(unsigned __int64, ::LeavePartyReason, ::LeavePartyMemberResult const *)
{
    LIFT_STUB(0x21b740);
}

// 0x21b880
bool __cdecl TeamParty::findMember(unsigned __int64, unsigned __int64, ::PartyMemberState, ::TeamMember *, int *) const
{
    LIFT_STUB(0x21b880);
}

// 0x21b970
bool __cdecl TeamParty::addMember(::ArenaLobbyTeamMemberInfo const *, int *)
{
    LIFT_STUB(0x21b970);
}

// 0x21ba40
bool __cdecl TeamParty::addMember(unsigned __int64, unsigned __int64, ::TeamParty::MemberAppearance const *, int *, short)
{
    LIFT_STUB(0x21ba40);
}

// 0x21bca0
void __cdecl TeamParty::swapMember(int, int)
{
    LIFT_STUB(0x21bca0);
}

// 0x21bd80
void __cdecl TeamParty::buildAppearance(::TeamParty::MemberAppearance *, ::Pc const *) const
{
    LIFT_STUB(0x21bd80);
}

// 0x21be30
bool __cdecl TeamParty::addPrepareZoneMember(unsigned __int64)
{
    LIFT_STUB(0x21be30);
}

// 0x21bee0
void __cdecl TeamParty::delPrepareZoneMember(unsigned __int64)
{
    LIFT_STUB(0x21bee0);
}

// 0x21bfa0
void __cdecl TeamParty::setZoneMemberState(unsigned __int64, unsigned int, ::TeamParty::ZoneMemberState, bool)
{
    LIFT_STUB(0x21bfa0);
}

// 0x21c1c0
bool __cdecl TeamParty::isFull(void) const
{
    LIFT_STUB(0x21c1c0);
}

// 0x21c230
bool __cdecl TeamParty::isSolo(void) const
{
    LIFT_STUB(0x21c230);
}

// 0x21c350
void __cdecl TeamParty::buildInMemberPacket(::FragmentPacket &, char)
{
    LIFT_STUB(0x21c350);
}

// 0x21c920
void __cdecl TeamParty::sendJoinParty(::Pc *, int, char) const
{
    LIFT_STUB(0x21c920);
}

// 0x21cda0
void __cdecl TeamParty::sendDelegatePartyLeader(unsigned __int64, short) const
{
    LIFT_STUB(0x21cda0);
}

// 0x21d5e0
void __cdecl TeamParty::SendLeaveMember(::Pc *, char, ::LeavePartyReason) const
{
    LIFT_STUB(0x21d5e0);
}

// 0x21d6f0
void __cdecl TeamParty::postDismissPartyIfSoloTask(void) const
{
    LIFT_STUB(0x21d6f0);
}

// 0x21d980
void __cdecl TeamParty::postUpdatePcTeamInfoTask(int, bool) const
{
    LIFT_STUB(0x21d980);
}

// 0x21dcd0
bool __cdecl TeamParty::CheckInviteTeam(void) const
{
    LIFT_STUB(0x21dcd0);
}

// 0x21dd60
short __cdecl TeamParty::PartyVoteCast(int, char, char, bool &)
{
    LIFT_STUB(0x21dd60);
}

// 0x21dfc0
short __cdecl TeamParty::PartyVoteCancelCast(int)
{
    LIFT_STUB(0x21dfc0);
}

// 0x21e0f0
void __cdecl TeamParty::PartyVoteReset(short, bool)
{
    LIFT_STUB(0x21e0f0);
}

// 0x21e2a0
void __cdecl TeamParty::buildInTeamMemberPacket(::FragmentPacket &, char)
{
    LIFT_STUB(0x21e2a0);
}

// 0x21e770
bool __cdecl TeamParty::buildJoinTeamMemberPacket(::Packet &, ::Pc *, int, int, char)
{
    LIFT_STUB(0x21e770);
}
