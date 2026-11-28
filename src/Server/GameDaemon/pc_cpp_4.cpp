// pc_cpp_4.cpp: pc.cpp part 4 (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "pc.h"
#include "achievementdata.h"
#include "creature.h"
#include "geoworld.h"
#include "contentsruleconfigdefinition_gd.h"
#include "Packet.h"
#include "PacketUtil.h"
#include "Log.h"
#include "Memory.h"
#include "MemoryManager.h"
#include <time.h>
#include <stdio.h>
#include <wchar.h>
#include "LiftStub.h"

#pragma comment(linker, "/INCLUDE:?SetTakingAchievementReward@Pc@@QEAAX_N@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?IsTakingAchievementReward@Pc@@QEAA_NXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?HasCraft@Pc@@QEAA_ND@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?FetchCraftUnionList@Pc@@QEAAXPEAVFragmentPacket@@@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?IsUsingJumpingCharacter2Ticket@Pc@@QEAA?B_NXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?ClearTransformItemRetry@Pc@@QEAAXXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?isAccountExpCharged@Pc@@AEAA_N_J_N@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetPowerInfoForGameLog@Pc@@QEAAXAEAUPcInfoForGameLog@@@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?ClearAttractionReward@Pc@@QEAAXXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?SendInitializeSeasonContentsRecordFail@Pc@@QEAAXW4GameFailReason@@@Z")  // LIFT: dead-strip keep (no live caller yet)

#define PC_CPP_FILE L"e:\\dailybuild02\\gamedaemon-common-0.0.348\\depot\\branch\\348nc\\program\\server\\gamedaemon\\Pc.cpp"

namespace
{
// LIFT: the skeleton class Pc does not declare these PDB members. Read them by PDB offset.
template <class T>
inline T *PcAt(void *self, unsigned offset)
{
    return reinterpret_cast<T *>(static_cast<char *>(self) + offset);
}

// LIFT: PDB offsets in Pc (GameDaemon 2019 + PDB).
enum
{
    PC_Id = 0x28,
    PC_pcDbId = 0x4E10,
    PC_account_exp_last_update_time = 0x370,  // Prop (+0x30) .State (+0xD8) .account_exp_last_update_time (+0x268)
    PC_attractionReward = 0x2FB8,
    PC_accountExpNextChargeTime = 0x3040,
    PC_isUsingJumpingCharacter2TicketLock = 0x3470,
    PC_isUsingJumpingCharacter2Ticket = 0x3478,
    PC_rankingRetrieveTimeLock = 0x4EA8,
    PC_rankingRetrieveTime = 0x4EB0,
    PC_isTakingAchievementReward = 0x4F48,
    PC_craftListLock = 0x9548,
    PC_craftList = 0x9550,
    PC_craftUnion = 0x9570,
    PC_craftUnionCount = 0x9578,
    PC_transformItemRetryRecipeId = 0x9588,
    PC_transformItemRetryMainIngredientDbId = 0x9590,
};

// LIFT: view of std::vector<CraftInfo *> (VS2010: proxy, first, last, end).
struct CraftListView
{
    void *_Myproxy;
    char **_Myfirst;
    char **_Mylast;
    char **_Myend;
};

// LIFT: view of CraftUnion (size 4).
struct CraftUnionView
{
    char unionType;   // +0
    char lift_pad_0;
    short unionExp;   // +2
};

// LIFT: CraftInfo members by PDB offset: recipeId +0x20, groupAlias +0x28, unionType +0x30.
inline int CraftRecipeId(char const *craft) { return *reinterpret_cast<int const *>(craft + 0x20); }
inline unsigned __int64 CraftGroupAlias(char const *craft) { return *reinterpret_cast<unsigned __int64 const *>(craft + 0x28); }
inline char CraftUnionType(char const *craft) { return craft[0x30]; }
}  // namespace

// 0x6048e0
bool __cdecl Pc::CheckToTransferFaction2WithEpicQuest(char, unsigned short &)
{
    LIFT_STUB(0x6048e0);
}

// 0x604990
bool __cdecl Pc::TransferFaction2WithEpicQuest(char, unsigned short)
{
    LIFT_STUB(0x604990);
}

// 0x604b70
bool __cdecl Pc::PostAuctionEscrowTask(__int64, __int64, __int64)
{
    LIFT_STUB(0x604b70);
}

// 0x604dc0
bool __cdecl Pc::PostChangeGradeTask(int, ::GradeInfo &, char)
{
    LIFT_STUB(0x604dc0);
}

// 0x604f70
bool __cdecl Pc::PostChangeGradeLevelTask(int, ::GradeLevelInfo &)
{
    LIFT_STUB(0x604f70);
}

// 0x605110
bool __cdecl Pc::InitGrade(int, ::GradeLevelInfo &, ::GradeInfo *const, short)
{
    LIFT_STUB(0x605110);
}

// 0x6051f0
bool __cdecl Pc::PostActivateAllGradeTask(void)
{
    LIFT_STUB(0x6051f0);
}

// 0x605390
bool __cdecl Pc::PostActivateAllGradeTask(int, ::GradeLevelInfo &, ::GradeInfo *const, short)
{
    LIFT_STUB(0x605390);
}

// 0x605530
bool __cdecl Pc::PostPartyBattleRatingScore(::PartyBattleResult, int, int, __int64, ::PartyBattleSideMember const &)
{
    LIFT_STUB(0x605530);
}

// 0x6056e0
void __cdecl Pc::FetchDungeonRatingScore(::Packet *, ::RepeatPacketComposer *)
{
    LIFT_STUB(0x6056e0);
}

// 0x605900
void __cdecl Pc::FetchDungeonRatingScoreScheduleNo(::Packet *, ::RepeatPacketComposer *)
{
    LIFT_STUB(0x605900);
}

// 0x605c50
int __cdecl Pc::GetDuelRatingScore(char)
{
    LIFT_STUB(0x605c50);
}

// 0x605cd0
int __cdecl Pc::GetIngameChampionshipDuelRatingScore(char)
{
    LIFT_STUB(0x605cd0);
}

// 0x605d50
int __cdecl Pc::GetSeasonContentsCombatRatingScore(char)
{
    LIFT_STUB(0x605d50);
}

// 0x605dc0
int __cdecl Pc::GetDuelRatingScoreScheduleNo(char)
{
    LIFT_STUB(0x605dc0);
}

// 0x605e40
int __cdecl Pc::GetIngameChampionshipDuelRatingScoreScheduleNo(char)
{
    LIFT_STUB(0x605e40);
}

// 0x605ec0
void __cdecl Pc::SetAchievementData(::AchievementData *)
{
    LIFT_STUB(0x605ec0);
}

// 0x606000
void __cdecl Pc::RepairAchievementReward(void)
{
    LIFT_STUB(0x606000);
}

// 0x606380
bool __cdecl Pc::InvokeAchievementAbility(short, short)
{
    LIFT_STUB(0x606380);
}

// 0x606770
void __cdecl Pc::SetNewbieInfoFlag(void)
{
    LIFT_STUB(0x606770);
}

// 0x6068c0
void __cdecl Pc::SetTakingAchievementReward(bool isTakingAchievementReward)
{
    AcquireSRWLockExclusive(&_takingAchievementRewardLock);
    *PcAt<bool>(this, PC_isTakingAchievementReward) = isTakingAchievementReward;
    ReleaseSRWLockExclusive(&_takingAchievementRewardLock);
}

// 0x606910
bool __cdecl Pc::IsTakingAchievementReward(void)
{
    AcquireSRWLockShared(&_takingAchievementRewardLock);
    bool result = *PcAt<bool>(this, PC_isTakingAchievementReward);
    ReleaseSRWLockShared(&_takingAchievementRewardLock);
    return result;
}

// 0x606950
void __cdecl Pc::GetPcInfoForGameLog(::PcInfoForGameLog &)
{
    LIFT_STUB(0x606950);
}

// 0x606be0
void __cdecl Pc::GetVitalityInfoForGameLog(::PcInfoForGameLog &)
{
    LIFT_STUB(0x606be0);
}

// 0x606d10
void __cdecl Pc::GetPowerInfoForGameLog(::PcInfoForGameLog &pcInfo)
{
    // LIFT: the Pc members at these offsets have no PDB name in the skeleton yet. The RVA 0x606d10 body reads them by offset.
    // LIFT: PcInfoForGameLog.power is at +0x570 (PDB). The skeleton struct has no members yet.
    __int64 a = (*PcAt<short>(this, 0x558) + *PcAt<short>(this, 0x550)) / 2;
    __int64 b = (*PcAt<int>(this, 0x540) + *PcAt<int>(this, 0x530)) / 2;
    __int64 c = (*PcAt<short>(this, 0x640) + *PcAt<short>(this, 0x638)) / 2;
    __int64 d = (*PcAt<short>(this, 0x630) + *PcAt<short>(this, 0x628)) / 2;
    __int64 p1 = a + b;
    swprintf_s(PcAt<wchar_t>(&pcInfo, 0x570), 0x80u, L"%I64d/%I64d", p1, d + (p1 + c));
}

// 0x606db0
char __cdecl Pc::IsBannedContentsOnLeaveZone(unsigned int) const
{
    LIFT_STUB(0x606db0);
}

// 0x606f70
bool __cdecl Pc::IsExistBannedContentsForReward(void) const
{
    LIFT_STUB(0x606f70);
}

// 0x607000
void __cdecl Pc::RestorePositionForMobile(void)
{
    LIFT_STUB(0x607000);
}

// 0x6070d0
bool __cdecl Pc::GetPropertyTransactionMoneyDiffEx(__int64, ::PropertyTransactionSyncData &, short)
{
    LIFT_STUB(0x6070d0);
}

// 0x607290
::Data::TendencyFieldPlayerGroupType __cdecl Pc::GetTendencyFieldPlayerGroup(void)
{
    LIFT_STUB(0x607290);
}

// 0x607350
void __cdecl Pc::DecreasePetDurability(void)
{
    LIFT_STUB(0x607350);
}

// 0x607460
void __cdecl Pc::ResetPetDurabilityDecreaseCount(void)
{
    LIFT_STUB(0x607460);
}

// 0x607550
bool __cdecl Pc::EnableToRetrieveMyRanking(char seasonContentsType)
{
    LIFT_STUB(0x607550);
}

// 0x607600
void __cdecl Pc::UpdateBotScore(bool)
{
    LIFT_STUB(0x607600);
}

// 0x607650
void __cdecl Pc::AddBotState(::Data::BotScoringConditionConditionTypeType, __int64, wchar_t const *, int)
{
    LIFT_STUB(0x607650);
}

// 0x6076c0
void __cdecl Pc::SetBotScore(int)
{
    LIFT_STUB(0x6076c0);
}

// 0x607740
void __cdecl Pc::SetBotScoreIgnore(bool, bool)
{
    LIFT_STUB(0x607740);
}

// 0x6077e0
char __cdecl Pc::GetBotScoreLevel(void)
{
    LIFT_STUB(0x6077e0);
}

// 0x607830
bool __cdecl Pc::GetBotScoreRestrictionIsolatePersistentZone(void)
{
    LIFT_STUB(0x607830);
}

// 0x607880
short __cdecl Pc::GetBotScoreRestrictionReduceAttackPower(void)
{
    LIFT_STUB(0x607880);
}

// 0x6078f0
short __cdecl Pc::GetBotScoreRestrictionReduceAcquireMoney(void)
{
    LIFT_STUB(0x6078f0);
}

// 0x607940
short __cdecl Pc::GetBotScoreRestrictionReduceAcquireExp(void)
{
    LIFT_STUB(0x607940);
}

// 0x607990
short __cdecl Pc::GetBotScoreRestrictionReduceAcquireDuelPoint(void)
{
    LIFT_STUB(0x607990);
}

// 0x6079e0
short __cdecl Pc::GetBotScoreRestrictionReduceAcquirePartyBattlePoint(void)
{
    LIFT_STUB(0x6079e0);
}

// 0x607a30
short __cdecl Pc::GetBotScoreRestrictionReduceAcquireFieldPlayPoint(void)
{
    LIFT_STUB(0x607a30);
}

// 0x607a80
void __cdecl Pc::RetrieveCraftList(void)
{
    LIFT_STUB(0x607a80);
}

// 0x607e70
void __cdecl Pc::OnTimeBasedPlayTimeExpired(bool)
{
    LIFT_STUB(0x607e70);
}

// 0x607ed0
void __cdecl Pc::SendFinishCraftNoti(::CraftInfo &)
{
    LIFT_STUB(0x607ed0);
}

// 0x608120
bool __cdecl Pc::EnableJoinCraftUnion(char)
{
    LIFT_STUB(0x608120);
}

// 0x608240
bool __cdecl Pc::JoinCraftUnion(char)
{
    LIFT_STUB(0x608240);
}

// 0x608300
bool __cdecl Pc::HasCraft(char unionType)
{
    bool result = false;
    CraftListView *list = PcAt<CraftListView>(this, PC_craftList);
    AcquireSRWLockShared(PcAt<::_RTL_SRWLOCK>(this, PC_craftListLock));
    if (list->_Mylast - list->_Myfirst != 0)
    {
        for (char **it = list->_Myfirst; it != list->_Mylast; ++it)
        {
            if (*it != nullptr && unionType == CraftUnionType(*it))
            {
                result = true;
                break;
            }
        }
    }
    ReleaseSRWLockShared(PcAt<::_RTL_SRWLOCK>(this, PC_craftListLock));
    return result;
}

// 0x6083a0
bool __cdecl Pc::IsJoinedCraftUnion(char unionType)
{
    LIFT_STUB(0x6083a0);
}

// 0x6083e0
bool __cdecl Pc::LeaveCraftUnion(char)
{
    LIFT_STUB(0x6083e0);
}

// 0x6084c0
short __cdecl Pc::GetCraftUnionExp(char unionType)
{
    LIFT_STUB(0x6084c0);
}

// 0x608500
short __cdecl Pc::AddCraftUnionExp(char, short)
{
    LIFT_STUB(0x608500);
}

// 0x608630
void __cdecl Pc::FetchCraftUnionList(::FragmentPacket *packet)
{
    if (packet->packet.CurHeader == nullptr || static_cast<unsigned short>(4000 - packet->packet.CurHeader->size) < 2u)
        packet->packet.Allocate(&packet->composer);
    packet->composer.PushRepeatCount(&packet->packet);
    CraftUnionView *unions = PcAt<CraftUnionView>(this, PC_craftUnion);
    for (char i = 0; i < 2; ++i)
    {
        if (static_cast<unsigned char>(unions[i].unionType - 1) <= 0xD)
        {
            if (packet->FreeSize() < 3u)
                packet->packet.Allocate(&packet->composer);
            if (packet->Compose(2, static_cast<unsigned int>(unions[i].unionType), static_cast<unsigned int>(unions[i].unionExp)) == 0)
                return;
            packet->IncRepeatCount();
        }
    }
    packet->composer.PopRepeatCount();
}

// 0x608720
bool __cdecl Pc::IsRegisteredCraftRecipe(int recipeId, unsigned __int64 groupAlias)
{
    LIFT_STUB(0x608720);
}

// 0x6087c0
::Pointer2< ::CraftInfo> __cdecl Pc::acquireCraftInfoByRecipeId(int)
{
    LIFT_STUB(0x6087c0);
}

// 0x608880
::Pointer2< ::CraftInfo> __cdecl Pc::acquireCraftInfoByCraftId(unsigned __int64)
{
    LIFT_STUB(0x608880);
}

// 0x608950
void __cdecl Pc::clearCraftList(void)
{
    LIFT_STUB(0x608950);
}

// 0x608a10
bool __cdecl Pc::TryToRegisterCraft(int, unsigned __int64, char, char, ::CraftOutput *const, ::SyncContext &)
{
    LIFT_STUB(0x608a10);
}

// 0x608b30
void __cdecl Pc::CancelToRegisterCraft(int)
{
    LIFT_STUB(0x608b30);
}

// 0x608bf0
void __cdecl Pc::RegisterCraftOk(::RegisterCraftOkParam const *)
{
    LIFT_STUB(0x608bf0);
}

// 0x609280
bool __cdecl Pc::EnableAbortCraft(unsigned __int64)
{
    LIFT_STUB(0x609280);
}

// 0x609340
void __cdecl Pc::FinishCraft(unsigned __int64)
{
    LIFT_STUB(0x609340);
}

// 0x6094b0
void __cdecl Pc::AbortCraft(unsigned __int64)
{
    LIFT_STUB(0x6094b0);
}

// 0x6097c0
bool __cdecl Pc::GetCraftReward(unsigned __int64, ::CraftReward &)
{
    LIFT_STUB(0x6097c0);
}

// 0x609c60
::GameFailReason __cdecl Pc::TryToTakeCraft(unsigned __int64, ::SyncContext &)
{
    LIFT_STUB(0x609c60);
}

// 0x609d60
void __cdecl Pc::TakeCraftOk(unsigned __int64, short)
{
    LIFT_STUB(0x609d60);
}

// 0x60a1e0
void __cdecl Pc::ChangeJumpingCharacterState(char)
{
    LIFT_STUB(0x60a1e0);
}

// 0x60a280
bool __cdecl Pc::SetUsingJumpingCharacter2Ticket(bool)
{
    LIFT_STUB(0x60a280);
}

// 0x60a3c0
bool const __cdecl Pc::IsUsingJumpingCharacter2Ticket(void)
{
    AcquireSRWLockShared(PcAt<::_RTL_SRWLOCK>(this, PC_isUsingJumpingCharacter2TicketLock));
    bool result = *PcAt<bool>(this, PC_isUsingJumpingCharacter2Ticket);
    ReleaseSRWLockShared(PcAt<::_RTL_SRWLOCK>(this, PC_isUsingJumpingCharacter2TicketLock));
    return result;
}

// 0x60a400
void __cdecl Pc::SetUncompletedAccInvenItemConsumptionList(int, ::UncompletedAccInvenItemConsumption *const)
{
    LIFT_STUB(0x60a400);
}

// 0x60a4e0
void __cdecl Pc::RecoverUncompletedAccInvenItemConsumption(void)
{
    LIFT_STUB(0x60a4e0);
}

// 0x60aaa0
void __cdecl Pc::InitPcAttractionState(void)
{
    LIFT_STUB(0x60aaa0);
}

// 0x60ab80
void __cdecl Pc::SetTransformItemRetry(unsigned __int64, unsigned __int64)
{
    LIFT_STUB(0x60ab80);
}

// 0x60ac30
void __cdecl Pc::ClearTransformItemRetry(void)
{
    *PcAt<unsigned __int64>(this, PC_transformItemRetryRecipeId) = 0;
    *PcAt<unsigned __int64>(this, PC_transformItemRetryMainIngredientDbId) = 0;
    Log::Write(Log::LT_DEBUG, PC_CPP_FILE, 20434, L"[pc], transform retry, clear, pc:%#I64x",
               *PcAt<unsigned __int64>(this, PC_Id));
}

// 0x60ac70
void __cdecl Pc::SetEffectPouch(char, short)
{
    LIFT_STUB(0x60ac70);
}

// 0x60ad40
void __cdecl Pc::DropEffectPouch(short &, ::vector16 &)
{
    LIFT_STUB(0x60ad40);
}

// 0x60af20
void __cdecl Pc::ClearAttractionReward(void)
{
    // LIFT: AttractionReward has no declared vfptr yet. Call slot 0 (scalar deleting destructor, flag 1) by the vtable.
    typedef void *(__fastcall *AttractionRewardDtor)(void *, __int64);
    void **slot = PcAt<void *>(this, PC_attractionReward);
    void *attractionReward = *slot;
    if (attractionReward != nullptr)
    {
        (*reinterpret_cast<AttractionRewardDtor *>(*reinterpret_cast<void ***>(attractionReward)))(attractionReward, 1);
        Memory::_Manager[2]->Free(*slot, PC_CPP_FILE, 20525);
        *slot = nullptr;
    }
}

// 0x60af80
bool __cdecl Pc::SetBattleRoyalFieldAttractionReward(char, short)
{
    LIFT_STUB(0x60af80);
}

// 0x60b080
void __cdecl Pc::TakeBattleRoyalFieldAttractionReward(void)
{
    LIFT_STUB(0x60b080);
}

// 0x60b1b0
bool __cdecl Pc::CheckGameTimeSchedule(void)
{
    LIFT_STUB(0x60b1b0);
}

// 0x60b360
bool __cdecl Pc::CheckSeasonContentsTypeNewSeason(char)
{
    LIFT_STUB(0x60b360);
}

// 0x60b480
::GameFailReason __cdecl Pc::CheckSeasonContentsSchedule(::GeoZone const *)
{
    LIFT_STUB(0x60b480);
}

// 0x60b5e0
void __cdecl Pc::SendInitializeSeasonContentsRecordOk(void)
{
    LIFT_STUB(0x60b5e0);
}

// 0x60b880
void __cdecl Pc::SendInitializeSeasonContentsRecordFail(::GameFailReason)
{
    // LIFT: the original logs and sends the constant 2. It does not read the reason argument.
    int v3 = 2;
    Log::Write(Log::LT_ERROR, PC_CPP_FILE, 20768,
               L"[pc], fail to initialize season contents record, pcid:0x%I64X, pcdbid:0x%I64X, reason:%d",
               *PcAt<unsigned __int64>(this, PC_Id), *PcAt<unsigned __int64>(this, PC_pcDbId), v3);
    Send("hh", 105, v3);
}

// 0x60b8f0
void __cdecl Pc::ComposeInitSeasonContentsInfo(char, char const *const)
{
    LIFT_STUB(0x60b8f0);
}

// 0x60bdf0
void __cdecl Pc::FinishSeasonContentsRecordInitialization(::RepeatPacketDecomposer &, ::Packet const *)
{
    LIFT_STUB(0x60bdf0);
}

// 0x60c230
void __cdecl Pc::FinishInitializationSeasonContents(short, ::InitCombatResultList *const, short, ::InitTimeAttackResultList *const)
{
    LIFT_STUB(0x60c230);
}

// 0x60c630
void __cdecl Pc::SeasonContentsRecordSyncToArenaLobby(unsigned __int64, short, ::InitCombatResultList *const)
{
    LIFT_STUB(0x60c630);
}

// 0x60c7b0
void __cdecl Pc::InitializeSeasonContentsRecord(char, char const *const)
{
    LIFT_STUB(0x60c7b0);
}

// 0x60ca00
bool __cdecl Pc::AttachBenefitAbility(int, char const *const, int const *const, ::ChangedProperty *)
{
    LIFT_STUB(0x60ca00);
}

// 0x60cbb0
bool __cdecl Pc::DetachBenefitAbility(int, char const *const, int const *const, ::ChangedProperty *)
{
    LIFT_STUB(0x60cbb0);
}

// 0x60cd60
void __cdecl Pc::activateAccountExp(int, int)
{
    LIFT_STUB(0x60cd60);
}

// 0x60d260
void __cdecl Pc::recoverAccountExp(void)
{
    LIFT_STUB(0x60d260);
}

// 0x60d880
bool __cdecl Pc::isAccountExpCharged(__int64 now, bool isChargeCheck)
{
    __int64 accountExpNextChargeTime = *PcAt<__int64>(this, PC_accountExpNextChargeTime);
    __time64_t Time = now;
    if (accountExpNextChargeTime > 0 && now < accountExpNextChargeTime)
        return true;
    // LIFT: ContentsRuleConfig::_accountExpQuotaResetTime is int at +0x7A8 (PDB).
    int accountExpQuotaResetTime = *reinterpret_cast<int *>(reinterpret_cast<char *>(ContentsRuleConfig::Config) + 0x7A8);
    tm currentTime;
    _localtime64_s(&currentTime, &Time);
    __int64 v8 = 0;
    if (currentTime.tm_hour < accountExpQuotaResetTime)
        v8 = -1;
    __int64 v9 = Time + 60 * (-currentTime.tm_min + 60 * (accountExpQuotaResetTime - currentTime.tm_hour + 24 * v8)) + -currentTime.tm_sec;
    if (isChargeCheck)
        *PcAt<__int64>(this, PC_accountExpNextChargeTime) = v9 + 86400;
    return *PcAt<__int64>(this, PC_account_exp_last_update_time) >= v9;
}

// 0x60d970
bool __cdecl Pc::RechargeAccountExpQuota(void)
{
    LIFT_STUB(0x60d970);
}

// 0x60daa0
bool __cdecl Pc::ApplyAccountExpToLobby(void)
{
    LIFT_STUB(0x60daa0);
}

// 0x60db90
bool __cdecl Pc::SendAccountExpToLobby(void)
{
    LIFT_STUB(0x60db90);
}

// 0x60dd50
bool __cdecl Pc::ActivateAccountLevelBenefits(short, short, ::ChangedProperty *)
{
    LIFT_STUB(0x60dd50);
}

// 0x60dfe0
void __cdecl Pc::SetAccountExp(__int64, ::ChangedProperty *, short)
{
    LIFT_STUB(0x60dfe0);
}

// 0x60e090
bool __cdecl Pc::CheckPcLevelForAccountContents(bool, int, int, int, int)
{
    LIFT_STUB(0x60e090);
}

// 0x60e290
void __cdecl Pc::updateUserAccountExpInfoOnLeaveWolrd(void)
{
    LIFT_STUB(0x60e290);
}

// 0x60e400
::GameLogAccountExpReasonCode __cdecl Pc::GetGameLogAccountExpReasonCode(::Pc::AccountExpReason)
{
    LIFT_STUB(0x60e400);
}

// 0x60e490
void __cdecl Pc::WriteGameLogGetAccountExp(__int64, __int64, short, short, __int64 *, int *)
{
    LIFT_STUB(0x60e490);
}

// 0x60e6d0
bool __cdecl Pc::ApplyClosetCollectingAbility(void)
{
    LIFT_STUB(0x60e6d0);
}

// 0x60e8b0
bool __cdecl Pc::ApplyItemAbility(::Data::EffectRecordItemAbility *)
{
    LIFT_STUB(0x60e8b0);
}

// 0x60e990
void __cdecl Pc::handleItemAbility(::Data::EffectRecordItemAbility *, ::ChangedProperty *)
{
    LIFT_STUB(0x60e990);
}

// 0x60f580
bool __cdecl Pc::IsElevatedJobStyle(void)
{
    LIFT_STUB(0x60f580);
}

// 0x60f670
bool __cdecl Pc::ElevateJobStyle(bool)
{
    LIFT_STUB(0x60f670);
}

// 0x60f8f0
void __cdecl Pc::RefreshSkillInfo(bool)
{
    LIFT_STUB(0x60f8f0);
}

// 0x60f960
void __cdecl Pc::ActivateSlateAbilities(::EnterReason)
{
    LIFT_STUB(0x60f960);
}
