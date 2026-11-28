// challengeparty.cpp: challengeparty.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "challengeparty.h"
#include "pc.h"
#include "zone.h"
#include "Log.h"
#include "LiftStub.h"

#define CHALLENGEPARTY_FILE L"e:\\dailybuild02\\gamedaemon-common-0.0.348\\depot\\branch\\348nc\\program\\server\\gamedaemon\\ChallengeParty.cpp"

#pragma comment(linker, "/INCLUDE:??1ChallengeParty@@UEAA@XZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?Initialize@ChallengePartyManager@@QEAA_NXZ")  // LIFT: dead-strip keep (no live caller yet)

// 0x65dd0
__cdecl ChallengeParty::ChallengeParty(::LoadChallengePartyInfo const &, unsigned __int64)
{
    LIFT_STUB(0x65dd0);
}

// 0x65f80
__cdecl ChallengeParty::~ChallengeParty(void)
{
    // The _lock member destructor and the DynamicRefCntObj base destructor run after this body.
    Log::Write(Log::LT_DEBUG, CHALLENGEPARTY_FILE, 34, L"[%s], %s; challengePartyId:%#I64x, refCount:%d", L"challenge-party",
               L"ChallengeParty::~ChallengeParty", reinterpret_cast< ::ChallengePartyView *>(this)->_info._challengePartyId, _ref);
}

// 0x66010
bool __cdecl ChallengeParty::Member::Compose(char, char, ::FragmentPacket *) const
{
    LIFT_STUB(0x66010);
}

// 0x660f0
void __cdecl ChallengeParty::retrieveMembers(::Pc *, ::ChallengeParty::UPDATE_MEMBER_REASON, unsigned __int64, unsigned __int64)
{
    LIFT_STUB(0x660f0);
}

// 0x66350
void __cdecl ChallengeParty::retrieveChallengePartyInfo(::Pc *, ::ChallengeParty::UPDATE_MEMBER_REASON)
{
    LIFT_STUB(0x66350);
}

// 0x66650
void __cdecl ChallengeParty::broadcast(::Packet const *, ::Zone *, unsigned __int64)
{
    LIFT_STUB(0x66650);
}

// 0x66780
void __cdecl ChallengeParty::Broadcast(::Packet const *, ::Zone *)
{
    LIFT_STUB(0x66780);
}

// 0x66960
bool __cdecl ChallengeParty::IsLeaderByPcDbId(unsigned __int64)
{
    LIFT_STUB(0x66960);
}

// 0x66a60
unsigned __int64 __cdecl ChallengeParty::GetCandidateLeaderPcDbId(unsigned __int64)
{
    LIFT_STUB(0x66a60);
}

// 0x66c90
unsigned __int64 __cdecl ChallengeParty::GetPcDbIdByIndex(char)
{
    LIFT_STUB(0x66c90);
}

// 0x66db0
unsigned __int64 __cdecl ChallengeParty::GetPcIdByIndex(char)
{
    LIFT_STUB(0x66db0);
}

// 0x66ed0
bool __cdecl ChallengeParty::IsFullMember(void)
{
    LIFT_STUB(0x66ed0);
}

// 0x66fc0
int __cdecl ChallengeParty::GetMemberCount(void)
{
    LIFT_STUB(0x66fc0);
}

// 0x670b0
bool __cdecl ChallengeParty::CheckPartyMembers(int, unsigned __int64 *const)
{
    LIFT_STUB(0x670b0);
}

// 0x672b0
::Pointer2< ::Pc> __cdecl ChallengeParty::GetLeaderPcPtr(void)
{
    LIFT_STUB(0x672b0);
}

// 0x674d0
bool __cdecl ChallengeParty::CopyChallengePartyName(wchar_t *, unsigned __int64)
{
    LIFT_STUB(0x674d0);
}

// 0x675d0
bool __cdecl ChallengeParty::AddMember(::LoadChallengePartyMemberInfo const &, ::ChallengeParty::ADD_MEMBER_REASON)
{
    LIFT_STUB(0x675d0);
}

// 0x67ab0
bool __cdecl ChallengeParty::removeMember(unsigned __int64, ::LeaveChallengePartyReason)
{
    LIFT_STUB(0x67ab0);
}

// 0x68330
bool __cdecl ChallengeParty::UpdateMember(::Pc *, ::ChallengeParty::UPDATE_MEMBER_REASON)
{
    LIFT_STUB(0x68330);
}

// 0x68a50
bool __cdecl ChallengeParty::UpdateZoneInfo(unsigned __int64, int)
{
    LIFT_STUB(0x68a50);
}

// 0x68ca0
bool __cdecl ChallengeParty::SetModifiable(bool)
{
    LIFT_STUB(0x68ca0);
}

// 0x68de0
bool __cdecl ChallengeParty::ChangeLeader(unsigned __int64)
{
    LIFT_STUB(0x68de0);
}

// 0x69500
void __cdecl ChallengeParty::makeRankingDesc(void)
{
    LIFT_STUB(0x69500);
}

// 0x696f0
void __cdecl ChallengeParty::updateBestRecord(char, int, __int64, bool)
{
    LIFT_STUB(0x696f0);
}

// 0x697d0
void __cdecl ChallengeParty::sendChangedBestRecord(char)
{
    LIFT_STUB(0x697d0);
}

// 0x699e0
bool __cdecl ChallengeParty::TryUpdateBestRecord(char, __int64, __int64, ::SeasonContentsSchedule const &)
{
    LIFT_STUB(0x699e0);
}

// 0x69df0
void __cdecl ChallengeParty::UpdateBestRecordByGameOver(char, unsigned __int64, __int64)
{
    LIFT_STUB(0x69df0);
}

// 0x6a6a0
void __cdecl ChallengeParty::ResetBestRecordContext(char)
{
    LIFT_STUB(0x6a6a0);
}

// 0x6a8c0
bool __cdecl ChallengeParty::InitializeBestRecordFromDB(::SeasonContentsChallengePartyBestRecord const &)
{
    LIFT_STUB(0x6a8c0);
}

// 0x6aa10
void __cdecl ChallengeParty::InitializeBestRecord(::SeasonContentsChallengePartyBestRecord const &)
{
    LIFT_STUB(0x6aa10);
}

// 0x6ab60
bool __cdecl ChallengeParty::EnableRetrieveRankingInfo(char, ::LatestRankingInfo &)
{
    LIFT_STUB(0x6ab60);
}

// 0x6ad50
void __cdecl ChallengeParty::UpdateRetrieveRankingInfo(char, ::LatestRankingInfo const &)
{
    LIFT_STUB(0x6ad50);
}

// 0x6aed0
bool __cdecl ChallengePartyManager::Initialize(void)
{
    _challengePartyList.clear();
    InitializeSRWLock(&_challengePartyMgrCS);
    Log::Write(Log::LT_DEBUG, CHALLENGEPARTY_FILE, 1046, L"[%s], %s", L"challenge-party", L"ChallengePartyManager::Initialize");
    return true;
}

// 0x6af60
void __cdecl ChallengePartyManager::InitializeSeasonContents(::SeasonContentsChallengePartyBestRecord const &)
{
    LIFT_STUB(0x6af60);
}

// 0x6b040
void __cdecl ChallengePartyManager::Clear(void)
{
    LIFT_STUB(0x6b040);
}

// 0x6b150
::ChallengeParty * __cdecl ChallengePartyManager::findChallengeParty(__int64)
{
    LIFT_STUB(0x6b150);
}

// 0x6b1b0
void __cdecl ChallengePartyManager::removeChallengePartyList(__int64)
{
    LIFT_STUB(0x6b1b0);
}

// 0x6b230
::Pointer2< ::ChallengeParty> __cdecl ChallengePartyManager::GetChallengePartyPtr(__int64)
{
    LIFT_STUB(0x6b230);
}

// 0x6b300
bool __cdecl ChallengePartyManager::CreateChallengeParty(::CreateChallengePartyOkFromCacheParam *, wchar_t const *, ::ChallengeParty::CREATE_PARTY_REASON)
{
    LIFT_STUB(0x6b300);
}

// 0x6b640
bool __cdecl ChallengePartyManager::RemoveMember(__int64, unsigned __int64, ::LeaveChallengePartyReason)
{
    LIFT_STUB(0x6b640);
}
