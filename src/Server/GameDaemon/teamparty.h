// teamparty.h: teamparty.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class TeamParty
{
public:
    struct MemberAppearance {};
    enum ZoneMemberState {};
public:
    static int __cdecl GetMaxMemberCountByPartyType(char);  // 0x211170
    __cdecl TeamParty(::Team *);  // 0x2111c0
    virtual __cdecl ~TeamParty(void);  // 0x2113c0
    int __cdecl GetMembersPcDbId(unsigned __int64 *const) const;  // 0x211450
    bool __cdecl CanDestroy(void) const;  // 0x2114e0
    void __cdecl Broadcast(::Packet const *) const;  // 0x2115a0
    bool __cdecl DelegateLeader(int *, int *, short);  // 0x2116b0
    void __cdecl Suggest(int, ::Pc *, ::Pc *, char, char, char, char, char, char);  // 0x211800
    bool __cdecl ChangeOption(int, ::PartyPickupRule, char, unsigned __int64, __int64);  // 0x211ba0
    short __cdecl ChangeInviteAuth(int, ::PartyInviteAuth);  // 0x2122c0
    bool __cdecl StopCinematic(int, unsigned int);  // 0x212430
    short __cdecl ChangeDifficultyType(int, char, bool);  // 0x212570
    void __cdecl Broadcast(unsigned __int64, unsigned __int64, ::Packet const *) const;  // 0x212cb0
    short __cdecl CheckInvite(int, ::InviteTeamGameLogInfo *) const;  // 0x212df0
    void __cdecl FetchMemberInfoForBuilder(::Packet &) const;  // 0x212fa0
    bool __cdecl AddAuction(unsigned __int64, ::PartyAuction *);  // 0x213250
    void __cdecl ClearAuction(unsigned __int64);  // 0x213310
    bool __cdecl UpdateDungeonStep(short, char, bool);  // 0x213410
    short __cdecl CheckChallengePartyAttractionCondition(__int64, unsigned __int64, char);  // 0x213520
    unsigned __int64 __cdecl FindZone(unsigned int) const;  // 0x213720
    bool __cdecl EnterZone(int, unsigned __int64, unsigned int, char, char);  // 0x213890
    void __cdecl LeaveZone(unsigned __int64, unsigned int, bool);  // 0x214300
    bool __cdecl IsEnteredMemberByAttraction(int);  // 0x2147a0
    bool __cdecl IsEnteredMemberInTeamPartyZone(void);  // 0x214840
    short __cdecl ReserveArenaLobbyRequest(int, ::Data::ArenaPortalRecordPtr, char);  // 0x2149c0
    short __cdecl StartArenaLobbyReservation(int);  // 0x214b60
    void __cdecl CancelArenaLobbyReservation(short);  // 0x215030
    short __cdecl SetReserveArenaLobbyState(int, char);  // 0x215180
    short __cdecl ReturnToArenaLobbyRequest(::Pc *, ::Data::ArenaPortalRecordPtr, char, char, char);  // 0x215290
    bool __cdecl PublishedRecruitArenaDungeonMember(::Pc *, char);  // 0x2155f0
    bool __cdecl CancelRecruitArenaDungeonMember(::Pc *, char);  // 0x2158c0
private:
    bool __cdecl initialize(unsigned __int64, ::Pc const *, ::PartyMemberState, char, int, short);  // 0x215b70
    bool __cdecl initialize(unsigned __int64, unsigned __int64, unsigned __int64, ::TeamParty::MemberAppearance *, ::PartyMemberState, char, int, short);  // 0x215d00
    bool __cdecl initialize(unsigned __int64, unsigned __int64, ::ArenaLobbyTeamInfo const *, char, int, bool);  // 0x216080
    bool __cdecl reserveMember(::Pc const *, short);  // 0x216330
    bool __cdecl reserveMember(unsigned __int64, unsigned __int64, ::TeamParty::MemberAppearance *, short, ::PartyMemberState);  // 0x216490
    bool __cdecl checkAttractionConditionBeforeConfirm(int);  // 0x216570
    bool __cdecl confirmMember(int);  // 0x216a00
    void __cdecl leaveMember(int, ::LeavePartyMemberResult *);  // 0x216b50
    void __cdecl logoutMember(int, ::LeavePartyMemberResult *);  // 0x216fc0
    bool __cdecl rejoinMember(::Pc const *, int *, ::RejoinPartyMemberResult *);  // 0x2173b0
    void __cdecl choiceRejoinMemberNotify(unsigned __int64, wchar_t const *, char);  // 0x217610
    void __cdecl clearExpiredMembers(int, ::ClearExpiredPartyMemberResult *);  // 0x217720
    void __cdecl moveToArenaFailed(int, ::LeavePartyMemberResult *);  // 0x217a00
    void __cdecl onCreated(::Pc *, unsigned int, char, ::JoinPartyLogInfo *);  // 0x217db0
    void __cdecl onJoined(::Pc *, int, unsigned int, char, ::JoinPartyLogInfo *);  // 0x218580
    void __cdecl onLeaved(::Pc *, unsigned __int64, ::LeavePartyReason, ::LeavePartyMemberResult const *, ::DismissPartyLogInfo const *);  // 0x218e90
    void __cdecl onLeaved(unsigned __int64, unsigned __int64, ::LeavePartyReason, ::LeavePartyMemberResult const *, bool, ::DismissPartyLogInfo const *);  // 0x219f90
    void __cdecl onLogout(::Pc *, int, bool);  // 0x21ac50
    void __cdecl onRejoin(::Pc *, int, ::RejoinPartyMemberResult const *, ::JoinPartyReason);  // 0x21adc0
    void __cdecl onMoveToArenaFailed(unsigned __int64, ::LeavePartyReason, ::LeavePartyMemberResult const *);  // 0x21b740
    bool __cdecl findMember(unsigned __int64, unsigned __int64, ::PartyMemberState, ::TeamMember *, int *) const;  // 0x21b880
    bool __cdecl addMember(::ArenaLobbyTeamMemberInfo const *, int *);  // 0x21b970
    bool __cdecl addMember(unsigned __int64, unsigned __int64, ::TeamParty::MemberAppearance const *, int *, short);  // 0x21ba40
    void __cdecl swapMember(int, int);  // 0x21bca0
    void __cdecl buildAppearance(::TeamParty::MemberAppearance *, ::Pc const *) const;  // 0x21bd80
    bool __cdecl addPrepareZoneMember(unsigned __int64);  // 0x21be30
    void __cdecl delPrepareZoneMember(unsigned __int64);  // 0x21bee0
    void __cdecl setZoneMemberState(unsigned __int64, unsigned int, ::TeamParty::ZoneMemberState, bool);  // 0x21bfa0
    bool __cdecl isFull(void) const;  // 0x21c1c0
    bool __cdecl isSolo(void) const;  // 0x21c230
    void __cdecl buildInMemberPacket(::FragmentPacket &, char);  // 0x21c350
    void __cdecl sendJoinParty(::Pc *, int, char) const;  // 0x21c920
    void __cdecl sendDelegatePartyLeader(unsigned __int64, short) const;  // 0x21cda0
public:
    void __cdecl SendLeaveMember(::Pc *, char, ::LeavePartyReason) const;  // 0x21d5e0
private:
    void __cdecl postDismissPartyIfSoloTask(void) const;  // 0x21d6f0
    void __cdecl postUpdatePcTeamInfoTask(int, bool) const;  // 0x21d980
public:
    bool __cdecl CheckInviteTeam(void) const;  // 0x21dcd0
    short __cdecl PartyVoteCast(int, char, char, bool &);  // 0x21dd60
    short __cdecl PartyVoteCancelCast(int);  // 0x21dfc0
    void __cdecl PartyVoteReset(short, bool);  // 0x21e0f0
private:
    void __cdecl buildInTeamMemberPacket(::FragmentPacket &, char);  // 0x21e2a0
    bool __cdecl buildJoinTeamMemberPacket(::Packet &, ::Pc *, int, int, char);  // 0x21e770
};

