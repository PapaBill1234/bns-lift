// challengeparty.h: challengeparty.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class ChallengeParty
{
public:
    enum ADD_MEMBER_REASON {};
    enum CREATE_PARTY_REASON {};
    struct Member;
    enum UPDATE_MEMBER_REASON {};
public:
    __cdecl ChallengeParty(::LoadChallengePartyInfo const &, unsigned __int64);  // 0x65dd0
    virtual __cdecl ~ChallengeParty(void);  // 0x65f80
private:
    void __cdecl retrieveMembers(::Pc *, ::ChallengeParty::UPDATE_MEMBER_REASON, unsigned __int64, unsigned __int64);  // 0x660f0
    void __cdecl retrieveChallengePartyInfo(::Pc *, ::ChallengeParty::UPDATE_MEMBER_REASON);  // 0x66350
    void __cdecl broadcast(::Packet const *, ::Zone *, unsigned __int64);  // 0x66650
public:
    void __cdecl Broadcast(::Packet const *, ::Zone *);  // 0x66780
    bool __cdecl IsLeaderByPcDbId(unsigned __int64);  // 0x66960
    unsigned __int64 __cdecl GetCandidateLeaderPcDbId(unsigned __int64);  // 0x66a60
    unsigned __int64 __cdecl GetPcDbIdByIndex(char);  // 0x66c90
    unsigned __int64 __cdecl GetPcIdByIndex(char);  // 0x66db0
    bool __cdecl IsFullMember(void);  // 0x66ed0
    int __cdecl GetMemberCount(void);  // 0x66fc0
    bool __cdecl CheckPartyMembers(int, unsigned __int64 *const);  // 0x670b0
    ::Pointer2< ::Pc> __cdecl GetLeaderPcPtr(void);  // 0x672b0
    bool __cdecl CopyChallengePartyName(wchar_t *, unsigned __int64);  // 0x674d0
    bool __cdecl AddMember(::LoadChallengePartyMemberInfo const &, ::ChallengeParty::ADD_MEMBER_REASON);  // 0x675d0
private:
    bool __cdecl removeMember(unsigned __int64, ::LeaveChallengePartyReason);  // 0x67ab0
public:
    bool __cdecl UpdateMember(::Pc *, ::ChallengeParty::UPDATE_MEMBER_REASON);  // 0x68330
    bool __cdecl UpdateZoneInfo(unsigned __int64, int);  // 0x68a50
    bool __cdecl SetModifiable(bool);  // 0x68ca0
    bool __cdecl ChangeLeader(unsigned __int64);  // 0x68de0
private:
    void __cdecl makeRankingDesc(void);  // 0x69500
    void __cdecl updateBestRecord(char, int, __int64, bool);  // 0x696f0
    void __cdecl sendChangedBestRecord(char);  // 0x697d0
public:
    bool __cdecl TryUpdateBestRecord(char, __int64, __int64, ::SeasonContentsSchedule const &);  // 0x699e0
    void __cdecl UpdateBestRecordByGameOver(char, unsigned __int64, __int64);  // 0x69df0
    void __cdecl ResetBestRecordContext(char);  // 0x6a6a0
    bool __cdecl InitializeBestRecordFromDB(::SeasonContentsChallengePartyBestRecord const &);  // 0x6a8c0
    void __cdecl InitializeBestRecord(::SeasonContentsChallengePartyBestRecord const &);  // 0x6aa10
    bool __cdecl EnableRetrieveRankingInfo(char, ::LatestRankingInfo &);  // 0x6ab60
    void __cdecl UpdateRetrieveRankingInfo(char, ::LatestRankingInfo const &);  // 0x6ad50
};

class ChallengePartyManager
{
public:
    bool __cdecl Initialize(void);  // 0x6aed0
    void __cdecl InitializeSeasonContents(::SeasonContentsChallengePartyBestRecord const &);  // 0x6af60
    void __cdecl Clear(void);  // 0x6b040
private:
    ::ChallengeParty * __cdecl findChallengeParty(__int64);  // 0x6b150
    void __cdecl removeChallengePartyList(__int64);  // 0x6b1b0
public:
    ::Pointer2< ::ChallengeParty> __cdecl GetChallengePartyPtr(__int64);  // 0x6b230
    bool __cdecl CreateChallengeParty(::CreateChallengePartyOkFromCacheParam *, wchar_t const *, ::ChallengeParty::CREATE_PARTY_REASON);  // 0x6b300
    bool __cdecl RemoveMember(__int64, unsigned __int64, ::LeaveChallengePartyReason);  // 0x6b640
};

struct ChallengeParty::Member
{
public:
    bool __cdecl Compose(char, char, ::FragmentPacket *) const;  // 0x66010
};

