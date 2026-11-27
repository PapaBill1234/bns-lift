// team.h: team.cpp, team.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"
#include "teamparty.h"

struct ClearExpiredPartyMemberResult
{
public:
    __cdecl ClearExpiredPartyMemberResult(void);  // 0x1ed9c0
};

struct LeavePartyMemberResult
{
public:
    __cdecl LeavePartyMemberResult(void);  // 0x1edaa0
};

class Team
{
public:
    int __cdecl GetMemberCount(void) const;  // 0x205be0
    int __cdecl GetMembers(unsigned __int64 *const) const;  // 0x205c20
    void __cdecl Broadcast(::Packet const *) const;  // 0x205ce0
    unsigned __int64 __cdecl FindZone(unsigned int);  // 0x205d50
    bool __cdecl UnoccupyRaidDungeon(void);  // 0x205e20
    bool __cdecl IsEnteredTeamMemberByAttraction(int);  // 0x205fe0
    int __cdecl MakeParty(int, unsigned __int64, unsigned __int64, char, ::TeamParty::MemberAppearance *, short);  // 0x206060
    char __cdecl GetPartyDifficultyType(int) const;  // 0x2062f0
    int __cdecl GetPartyMemberCount(int) const;  // 0x206320
    int __cdecl GetPartyMembers(unsigned __int64, unsigned __int64, unsigned __int64 *const) const;  // 0x206380
    int __cdecl GetPartyMembers(int, unsigned __int64 *const) const;  // 0x2066a0
    bool __cdecl IsPartyMember(int, unsigned __int64) const;  // 0x206730
    bool __cdecl CanDestroy(void) const;  // 0x2067c0
    void __cdecl SuggestParty(::TeamMemberIndex const *, ::Pc *, ::Pc *, char, char, char, char, char, char);  // 0x206860
    bool __cdecl StopCinematic(::TeamMemberIndex const *, unsigned int);  // 0x206e00
    short __cdecl CheckInvitePcToTeam(unsigned __int64, unsigned __int64, ::TeamMemberIndex const *, ::InviteTeamGameLogInfo *);  // 0x207100
    short __cdecl CheckJoinTeamToOtherTeam(void);  // 0x2072d0
    short __cdecl CheckInviteTeamToTeam(char, unsigned __int64, unsigned __int64, ::InviteTeamGameLogInfo *);  // 0x207370
    unsigned __int64 __cdecl GetPartyPickupMemberByPickupRule(int);  // 0x207720
    ::PartyAuction * __cdecl GetPartyAuction(int, unsigned __int64) const;  // 0x2077d0
    bool __cdecl AddPartyAuction(int, unsigned __int64, ::PartyAuction *);  // 0x2078c0
    char __cdecl GetPartyDungeonStep(int, short) const;  // 0x207970
    unsigned __int64 __cdecl GetPartyChallengePartyAttractionId(int) const;  // 0x2079e0
    bool __cdecl PartyIsInChallengePartyAttraction(int) const;  // 0x207a40
    bool __cdecl EnterPartyZone(::TeamMemberIndex const *, unsigned __int64, unsigned int, char, char);  // 0x207aa0
    void __cdecl CancelPartyArenaLobbyReservation(int, short);  // 0x207b70
    short __cdecl ReturnToArenaLobbyPartyRequest(int, ::Pc *, ::Data::ArenaPortalRecordPtr, char, char, char);  // 0x207bd0
    bool __cdecl IsPublishedRecruitArenaDungeonPartyMember(int);  // 0x207cb0
    __cdecl Team(void);  // 0x207d10
    virtual __cdecl ~Team(void);  // 0x207e30
private:
    bool __cdecl initialize(unsigned __int64, unsigned __int64, ::Pc const *, char, int);  // 0x207f60
    bool __cdecl initialize(unsigned __int64, unsigned __int64, unsigned __int64, ::ArenaLobbyTeamInfo const *, char, int, bool);  // 0x208320
    bool __cdecl reservePartyMember(::Pc const *, ::Pc const *);  // 0x208740
    bool __cdecl reservePartyMember(char, ::Pc const *, short);  // 0x208880
    bool __cdecl reservePartyMember(char, unsigned __int64, unsigned __int64, ::TeamParty::MemberAppearance *, short, ::PartyMemberState);  // 0x2089a0
    bool __cdecl confirmPartyMember(::TeamMemberIndex const *);  // 0x208ca0
    void __cdecl leavePartyMember(::TeamMemberIndex const *, ::LeavePartyMemberResult *);  // 0x208e20
    bool __cdecl dismissPartyIfSolo(::TeamMemberIndex const *, ::LeavePartyMemberResult *);  // 0x209060
    void __cdecl moveToArenaFailed(::TeamMemberIndex const *, ::LeavePartyMemberResult *);  // 0x209300
    void __cdecl logoutPartyMember(::TeamMemberIndex const *, ::LeavePartyMemberResult *);  // 0x209480
    bool __cdecl findMember(unsigned __int64, unsigned __int64, ::PartyMemberState, ::TeamMember *, ::TeamMemberIndex *) const;  // 0x2096b0
    bool __cdecl findParty(unsigned __int64, int *) const;  // 0x2098f0
    void __cdecl clearExpiredPartyMembers(::TeamMemberIndex const *, ::ClearExpiredPartyMemberResult *);  // 0x2099d0
    bool __cdecl rejoinPartyMember(::Pc const *, ::TeamMemberIndex *, ::RejoinPartyMemberResult *);  // 0x209b30
    bool __cdecl choiceRejoinPartyMemberNotify(int, unsigned __int64, wchar_t const *, char);  // 0x209c80
    void __cdecl onCreated(::Pc *, unsigned int, ::JoinPartyLogInfo *);  // 0x209d40
    void __cdecl onJoined(::Pc *, ::TeamMemberIndex const *, unsigned int, char, ::JoinPartyLogInfo *);  // 0x209f90
    void __cdecl onLeaved(::Pc *, int, unsigned __int64, ::LeavePartyReason, ::LeavePartyMemberResult const *, ::DismissPartyLogInfo const *);  // 0x20a2a0
    void __cdecl onLeaved(unsigned __int64, int, unsigned __int64, ::LeavePartyReason, ::LeavePartyMemberResult const *, bool, ::DismissPartyLogInfo const *);  // 0x20a520
    void __cdecl onPartySwaped(::Pc *, ::TeamMemberIndex const *, unsigned int, char, ::LeavePartyMemberResult *, ::DismissPartyLogInfo const *);  // 0x20a7a0
    void __cdecl onPromoted(::Pc *, unsigned int);  // 0x20aa50
    void __cdecl onClearExpired(::ClearExpiredPartyMemberResult *, int, bool);  // 0x20ac40
    void __cdecl onLogout(::Pc *, ::TeamMemberIndex const *, bool, bool);  // 0x20ae40
    void __cdecl onRejoin(::Pc *, ::TeamMemberIndex const *, ::RejoinPartyMemberResult const *, ::JoinPartyReason);  // 0x20b120
    void __cdecl onMoveToArenaFailed(unsigned __int64, int, ::LeavePartyReason, ::LeavePartyMemberResult const *);  // 0x20b4b0
    void __cdecl onPartyDestoryed(::Pc *, unsigned __int64, ::LeavePartyReason, ::LeavePartyMemberResult const *, ::DismissPartyLogInfo const *);  // 0x20b670
    void __cdecl onPartyDestoryed(unsigned __int64, unsigned __int64, ::LeavePartyReason, ::LeavePartyMemberResult const *, ::DismissPartyLogInfo const *);  // 0x20cd40
public:
    void __cdecl SendLeaveTeam(::Pc *, int, ::LeavePartyReason);  // 0x20df90
private:
    bool __cdecl initPartyList(int);  // 0x20e0e0
    bool __cdecl addParty(int, ::TeamParty *);  // 0x20e1d0
    void __cdecl removeParty(int);  // 0x20e3a0
    void __cdecl removePartyIndex(int);  // 0x20e490
    bool __cdecl findPcParty(unsigned __int64, int *) const;  // 0x20e580
    bool __cdecl addPcParty(unsigned __int64, int);  // 0x20e5f0
    void __cdecl removePcParty(unsigned __int64);  // 0x20e690
    int __cdecl findEmptyPartyIndex(void) const;  // 0x20e710
public:
    bool __cdecl CheckInvitationAuth(char, char, unsigned __int64, unsigned __int64);  // 0x20e740
private:
    bool __cdecl reserveTeamMember(char, ::Pc const *, ::Pc const *, int *);  // 0x20e900
    bool __cdecl setVisible(bool);  // 0x20f150
    bool __cdecl setTeamLeader(unsigned __int64, unsigned __int64, ::BeTeamLeaderLogInfo *);  // 0x20f1a0
    void __cdecl buildInMemberPacket(::FragmentPacket &, char);  // 0x20f740
    void __cdecl postDismissTeamIfSoloPartyTask(void) const;  // 0x20f8b0
};

class TeamBroadcastPropertyList
{
public:
    __cdecl TeamBroadcastPropertyList(::Pc *, char, bool);  // 0x20fb70
    virtual __cdecl ~TeamBroadcastPropertyList(void);  // 0x20fe60
    bool __cdecl Initialize(void);  // 0x20ffe0
    bool __cdecl PropertyChange(unsigned short);  // 0x2100a0
    bool __cdecl ConditionChangeByProperty(unsigned short);  // 0x210220
    bool __cdecl ConditionChange(int, unsigned __int64, void *);  // 0x2103d0
    bool __cdecl FetchTeamPartyPropertyData(short *, char *, short *, short *, char *, short *);  // 0x210490
    bool __cdecl FetchTeamPartyConditionsPacket(::Packet *, ::RepeatPacketComposer *, ::Packet *, ::RepeatPacketComposer *);  // 0x2105e0
};

class TeamManager
{
public:
    __cdecl TeamManager(unsigned int);  // 0x1f0350
    virtual __cdecl ~TeamManager(void);  // 0x1f04b0
    bool __cdecl Initialize(unsigned int, unsigned int, unsigned int);  // 0x1f0680
    void __cdecl Clear(void);  // 0x1f0880
    ::Team * __cdecl AcquireAndLockTeamByPcId(unsigned __int64, unsigned __int64, ::TeamMemberIndex *);  // 0x1f09b0
    ::Team * __cdecl AcquireAndLockTeamByPartyId(unsigned __int64, int *);  // 0x1f0cb0
    ::Team * __cdecl AcquireAndLockTeamById(unsigned __int64);  // 0x1f0e00
    void __cdecl ReleaseAndUnlockTeam(::Team *);  // 0x1f0eb0
    void __cdecl ReservePartyMember(::Pc *, ::Pc *, unsigned int, char);  // 0x1f0f00
    void __cdecl ConfirmPartyMember(::Pc *, unsigned int, char, char);  // 0x1f1a60
    void __cdecl LeavePartyMember(::Pc *, unsigned __int64, ::LeavePartyReason, bool);  // 0x1f24a0
    short __cdecl LeaveTeamParty(::Pc *, unsigned __int64, ::LeavePartyReason);  // 0x1f2b40
    void __cdecl BanishFromParty(::Pc *, char, bool);  // 0x1f3a70
    void __cdecl BanishFromTeam(::Pc *, short, char);  // 0x1f4400
    void __cdecl TeamMemberPartyChange(::Pc *, short, char, __int64, short, char, __int64);  // 0x1f4c60
    void __cdecl ConfirmTeamMemberPartyChange(::Pc *, unsigned int, char, char, ::LeavePartyMemberResult *);  // 0x1f6cf0
    void __cdecl LogoutPc(::Pc *);  // 0x1f7710
    void __cdecl RejoinPc(::Pc *, ::JoinPartyReason, char *);  // 0x1f7c70
    void __cdecl ClearExpiredPartyMember(::Pc *);  // 0x1f80a0
    void __cdecl DismissPartyIfSolo(::Pc *);  // 0x1f88a0
    void __cdecl MoveToArenaFailed(unsigned __int64, bool);  // 0x1f8ea0
    bool __cdecl CreatePartyByMove(unsigned __int64, unsigned __int64, ::ArenaLobbyTeamInfo const *, char, bool);  // 0x1f93f0
    void __cdecl CreateParty(::Pc *, char, bool);  // 0x1f9650
    void __cdecl RemoveTimeoutReservedParty(__int64, __int64);  // 0x1f9a00
    void __cdecl ConfirmPartyMemberFailed(::Pc *, unsigned int, char);  // 0x1f9d10
    void __cdecl AcceptRejoinPartyMember(unsigned __int64, wchar_t const *, char);  // 0x1fa300
    void __cdecl RejectRejoinPartyMember(unsigned __int64, wchar_t const *, ::LeavePartyReason, char);  // 0x1fa670
    unsigned __int64 __cdecl GetTeamLeaderId(unsigned __int64) const;  // 0x1fab70
    unsigned __int64 __cdecl FindZone(unsigned __int64, unsigned int);  // 0x1fabf0
    bool __cdecl IsEnteredTeamMemberByAttraction(unsigned __int64, unsigned __int64, int);  // 0x1faca0
    unsigned __int64 __cdecl GetPartyId(unsigned __int64, unsigned __int64) const;  // 0x1fad30
    char __cdecl GetPartyDifficultyType(unsigned __int64, unsigned __int64) const;  // 0x1fade0
    char __cdecl GetPartyDifficultyType(unsigned __int64) const;  // 0x1fae90
    bool __cdecl IsPartyLeader(unsigned __int64, unsigned __int64) const;  // 0x1faf40
    unsigned __int64 __cdecl GetPartyLeaderDbId(unsigned __int64) const;  // 0x1fb020
    unsigned __int64 __cdecl GetPartyLeaderId(unsigned __int64) const;  // 0x1fb0d0
    int __cdecl GetPartyMemberCount(unsigned __int64, unsigned __int64) const;  // 0x1fb180
    void __cdecl SuggestParty(::Pc *, ::Pc *, char, char, char, char, char, char);  // 0x1fb250
    void __cdecl DelegatePartyLeader(::Pc *, ::Pc *);  // 0x1fb350
    void __cdecl DelegateTeamLeader(::Pc *, ::Pc *);  // 0x1fb700
    void __cdecl NominatePartyLeader(::Pc *, ::Pc *);  // 0x1fc240
    void __cdecl SetTeamInviteAuth(::Pc *, ::TeamInviteAuth);  // 0x1fc8e0
    void __cdecl ChangeTeamPartyDifficultyType(::Pc *, char, char);  // 0x1fca50
    void __cdecl ChangePartyOption(::Pc *, ::PartyPickupRule, char, unsigned __int64, __int64);  // 0x1fcd00
    void __cdecl ChangePartyInviteAuth(::Pc *, ::PartyInviteAuth);  // 0x1fce70
    bool __cdecl StopCinematic(::Pc *, unsigned int);  // 0x1fcfd0
    void __cdecl ChangePartyDifficultyType(::Pc *, char);  // 0x1fd100
    short __cdecl CheckInviteTeamToTeam(char, unsigned __int64, unsigned __int64, unsigned __int64, unsigned __int64, ::InviteTeamGameLogInfo *);  // 0x1fd3c0
    short __cdecl ReserveTeamMember(char, ::Pc *, ::Pc *);  // 0x1fd5f0
    short __cdecl ConfirmTeamMember(char, ::Pc *, char);  // 0x1fe930
    void __cdecl ConfirmTeamMemberFailed(char, ::Pc *);  // 0x1ff3b0
    void __cdecl ClearPartyAuction(unsigned __int64, unsigned __int64);  // 0x1ff940
    bool __cdecl AddPartyPrepareZoneMember(unsigned __int64, unsigned __int64);  // 0x1ffa10
    void __cdecl DelPartyPrepareZoneMember(unsigned __int64, unsigned __int64);  // 0x1ffb00
    short __cdecl GetPartyDungeonId(unsigned __int64) const;  // 0x1ffbe0
    bool __cdecl UpdatePartyDungeonStep(unsigned __int64, unsigned __int64, short, char, bool);  // 0x1ffcb0
    int __cdecl GetPartyDungeonMaxMemberCount(unsigned __int64, unsigned __int64) const;  // 0x1ffdc0
    unsigned __int64 __cdecl GetPartyChallengePartyAttractionId(unsigned __int64) const;  // 0x1ffea0
    char __cdecl GetPartyChallengePartyAttractionMode(unsigned __int64) const;  // 0x1fff70
    short __cdecl CheckPartyChallengePartyAttractionCondition(unsigned __int64, __int64, unsigned __int64, char);  // 0x200050
    unsigned __int64 __cdecl FindPartyZone(unsigned __int64, unsigned __int64, unsigned int) const;  // 0x200150
    unsigned __int64 __cdecl FindPartyZone(unsigned __int64, unsigned int) const;  // 0x200230
    bool __cdecl EnterPartyZone(unsigned __int64, unsigned __int64, unsigned __int64, unsigned int, char, char);  // 0x200310
    void __cdecl SetPartyZoneMemberState(unsigned __int64, unsigned __int64, unsigned __int64, unsigned int, ::TeamParty::ZoneMemberState);  // 0x2003e0
    short __cdecl ReserveArenaLobbyPartyRequest(unsigned __int64, unsigned __int64, ::Data::ArenaPortalRecordPtr, char);  // 0x200590
    short __cdecl StartPartyArenaLobbyReservation(unsigned __int64, unsigned __int64);  // 0x2006a0
    void __cdecl CancelPartyArenaLobbyReservation(unsigned __int64, unsigned __int64, short);  // 0x200780
    short __cdecl SetPartyReserveArenaLobbyState(unsigned __int64, unsigned __int64, char);  // 0x200850
    short __cdecl ReturnToArenaLobbyPartyRequest(::Pc *, ::Data::ArenaPortalRecordPtr, char, char, char);  // 0x200940
    bool __cdecl ReserveReinforcedPartyMember(unsigned __int64, unsigned __int64, unsigned int, unsigned __int64, char, ::ArenaLobbyTeamInfo const &);  // 0x200a40
protected:
    virtual bool __cdecl IsExist(unsigned __int64);  // 0x201370
private:
    unsigned int __cdecl toPcIndex(unsigned __int64) const;  // 0x2013e0
    unsigned int __cdecl toPartyIndex(unsigned __int64) const;  // 0x201460
    void __cdecl sort(::Team **const, int, int);  // 0x2014e0
    ::Team * __cdecl findTeamById(unsigned __int64);  // 0x2015d0
    ::Team * __cdecl findTeamByPcId(unsigned __int64);  // 0x2016e0
    ::Team * __cdecl findTeamByWaitingPcId(unsigned __int64);  // 0x2017f0
    ::Team * __cdecl findTeamByLogoutPcDbId(unsigned __int64);  // 0x201900
    ::Team * __cdecl findTeamByReserveArenaPcDbId(unsigned __int64);  // 0x201970
    ::Team * __cdecl findTeamByPartyId(unsigned __int64);  // 0x2019e0
    bool __cdecl findTeamListByPcId(unsigned __int64, unsigned __int64, ::Team **const);  // 0x201af0
    bool __cdecl addTeam(unsigned __int64, unsigned __int64, unsigned __int64, ::Team *);  // 0x201c30
    bool __cdecl addTeam(::ArenaLobbyTeamInfo const *, unsigned __int64, unsigned __int64, ::Team *);  // 0x201e50
    void __cdecl removeTeam(unsigned __int64);  // 0x202040
    void __cdecl updatePcWaitingTeam(unsigned __int64, unsigned __int64);  // 0x202120
    void __cdecl removePcWaitingTeam(unsigned __int64);  // 0x202250
    void __cdecl updatePcTeam(unsigned __int64, unsigned __int64);  // 0x202310
    void __cdecl removePcTeam(unsigned __int64);  // 0x202400
    void __cdecl updateLogoutPcTeam(unsigned __int64, unsigned __int64);  // 0x2024c0
    void __cdecl removeLogoutPcTeam(unsigned __int64);  // 0x202560
    void __cdecl updateReserveArenaPcTeam(unsigned __int64, unsigned __int64);  // 0x2025e0
    void __cdecl removeReserveArenaPcTeam(unsigned __int64);  // 0x202680
    void __cdecl updatePartyTeam(unsigned __int64, unsigned __int64);  // 0x202700
    void __cdecl removePartyTeam(unsigned __int64);  // 0x2027f0
    void __cdecl lock(void);  // 0x2028c0
    void __cdecl unlock(void);  // 0x202980
    void __cdecl lockAndAddRefTeam(::Team *);  // 0x2029b0
    void __cdecl lockAndAddRefTeams(::Team **const, int);  // 0x202a70
    void __cdecl unlockAndDelRefTeams(::Team **const, int);  // 0x202c20
    bool __cdecl postConfirmPartyMemberTask(::Pc *, unsigned int, char, char) const;  // 0x202d60
    bool __cdecl postLeaveTeamMemberTask(::Pc *, ::Pc *, ::LeavePartyReason);  // 0x202f90
    bool __cdecl postConfirmTeamMemberTask(char, ::Pc *, ::Pc *, char) const;  // 0x2031b0
    bool __cdecl postConfirmTeamMemberPartyChangeTask(::Pc *, unsigned int, char, char, ::LeavePartyMemberResult *) const;  // 0x2033f0
    void __cdecl onTeamDestoryed(::Pc *, unsigned __int64, ::LeavePartyReason, ::LeavePartyMemberResult const *, ::Team *, ::DismissPartyLogInfo const *);  // 0x2035f0
    void __cdecl onTeamDestoryed(unsigned __int64, unsigned __int64, ::LeavePartyReason, ::LeavePartyMemberResult const *, ::DismissPartyLogInfo const *);  // 0x204bd0
};

class TeamPartyIdManager
{
public:
    virtual __cdecl ~TeamPartyIdManager(void);  // 0x1eff00
    bool __cdecl Initialize(unsigned int);  // 0x1eff60
    unsigned __int64 __cdecl Make(void);  // 0x1f0000
    void __cdecl Remove(unsigned __int64);  // 0x1f0120
protected:
    virtual bool __cdecl IsExist(unsigned __int64);  // 0x1f0220
};

