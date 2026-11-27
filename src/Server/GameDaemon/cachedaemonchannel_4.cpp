// cachedaemonchannel_4.cpp: cachedaemonchannel.cpp part 4 (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "cachedaemonchannel.h"
#include "challengelistcontainer.h"
#include "collectingmanager.h"
#include "contentquota.h"
#include "duelbottrainingroomscorecontainer.h"
#include "fishingcontainer.h"
#include "guild.h"
#include "guildbank.h"
#include "item.h"
#include "mentoringproperty.h"
#include "pc.h"
#include "propertytran.h"
#include "raiddungeon.h"
#include "randomstore.h"
#include "seasonscore.h"
#include "skillpage.h"
#include "skillskinproperty.h"
#include "slatecontents.h"
#include "summoned.h"
#include "LiftStub.h"

// 0x31a400
void __cdecl CachedChannel::SendUpdateSummoned(::Pc const *, ::SummonedEntry *)
{
    LIFT_STUB(0x31a400);
}

// 0x31a730
void __cdecl CachedChannel::SendAddContentQuota(::Pc const *, int, ::ContentQuota const *)
{
    LIFT_STUB(0x31a730);
}

// 0x31aa20
void __cdecl CachedChannel::SendUpdateContentQuota(::Pc const *, int, ::ContentQuota const *)
{
    LIFT_STUB(0x31aa20);
}

// 0x31acf0
void __cdecl CachedChannel::SendSkillPage(::Pc const *, ::SkillPage const *)
{
    LIFT_STUB(0x31acf0);
}

// 0x31b030
void __cdecl CachedChannel::SendRandomStore(::Pc const *const, __int64, ::RandomStore const &)
{
    LIFT_STUB(0x31b030);
}

// 0x31b3f0
void __cdecl CachedChannel::SendAddRaidDungeonBindData(::Pc const *, __int64, ::RaidDungeonBindPropertyEntry const *)
{
    LIFT_STUB(0x31b3f0);
}

// 0x31b700
void __cdecl CachedChannel::SendAddRaidDungeonUnbindData(::Pc const *, int, ::RaidDungeonUnbindPropertyEntry const *)
{
    LIFT_STUB(0x31b700);
}

// 0x31ba10
void __cdecl CachedChannel::SendUpdateRaidDungeonUnbindData(::Pc const *, int, ::RaidDungeonUnbindPropertyEntry const *)
{
    LIFT_STUB(0x31ba10);
}

// 0x31bd00
void __cdecl CachedChannel::SendSkillSkinAcquired(::Pc const *, ::SkillSkinProperty const *)
{
    LIFT_STUB(0x31bd00);
}

// 0x31c040
void __cdecl CachedChannel::SendMentoringProperty(::Pc const *, ::MentoringProperty const *)
{
    LIFT_STUB(0x31c040);
}

// 0x31c380
void __cdecl CachedChannel::SendDetachPostItemForInsert(unsigned __int64, __int64, __int64, char, __int64, __int64, ::Item *)
{
    LIFT_STUB(0x31c380);
}

// 0x31cb90
void __cdecl CachedChannel::SendDetachPostItemForUpdate(unsigned __int64, __int64, __int64, char, __int64, __int64, char, __int64, short)
{
    LIFT_STUB(0x31cb90);
}

// 0x31cdc0
void __cdecl CachedChannel::SendDetachPostMoney(unsigned __int64, __int64, __int64, char, __int64, __int64, __int64)
{
    LIFT_STUB(0x31cdc0);
}

// 0x31cff0
void __cdecl CachedChannel::SendRegisterPawn(::Pc const *, char, unsigned __int64, __int64, char, char, __int64, __int64, char, char *const, __int64 *const, int *const)
{
    LIFT_STUB(0x31cff0);
}

// 0x31d2c0
void __cdecl CachedChannel::SendDeliverPostReq(::Pc *, char, char, short, __int64, wchar_t *, wchar_t *, wchar_t *, ::CachedChannel::AttachedItem *const, short)
{
    LIFT_STUB(0x31d2c0);
}

// 0x31d720
void __cdecl CachedChannel::SendDeliverSystemPostReq(::Pc *, char, char, __int64, short, __int64, wchar_t *, wchar_t *, wchar_t *, ::CachedChannel::SystemPostAttachedItem *const, short)
{
    LIFT_STUB(0x31d720);
}

// 0x31db40
void __cdecl CachedChannel::SendDeliverSystemPostReq(unsigned __int64, ::CachedChannel::SystemPostBodyParam &, ::CachedChannel::SystemPostAttachedItem *const, short)
{
    LIFT_STUB(0x31db40);
}

// 0x31df10
bool __cdecl CachedChannel::SendInitializeGuildCombatScore(::SeasonContentsSchedule const &, bool)
{
    LIFT_STUB(0x31df10);
}

// 0x31e280
bool __cdecl CachedChannel::SendInitializeSeasonContentsChallengePartySchedule(::SeasonContentsSchedule const &, bool)
{
    LIFT_STUB(0x31e280);
}

// 0x31e530
bool __cdecl CachedChannel::SendInitializeMentoring(short, bool)
{
    LIFT_STUB(0x31e530);
}

// 0x31e790
void __cdecl CachedChannel::SendCreateGuild(::Pc const *, unsigned __int64, unsigned __int64, char, wchar_t const *)
{
    LIFT_STUB(0x31e790);
}

// 0x31ea20
bool __cdecl CachedChannel::SendRenameGuild(unsigned __int64, unsigned __int64, unsigned __int64, char, wchar_t const *, unsigned __int64)
{
    LIFT_STUB(0x31ea20);
}

// 0x31eb70
bool __cdecl CachedChannel::SendTryToRenameGuild(::Pc const *, unsigned __int64, unsigned __int64, char, wchar_t const *, unsigned __int64, long, ::PropertyTransactionSyncFetchEx *)
{
    LIFT_STUB(0x31eb70);
}

// 0x31ee40
void __cdecl CachedChannel::SendTencentJoinGuild(::Pc const *, unsigned __int64, char, char, __int64)
{
    LIFT_STUB(0x31ee40);
}

// 0x31ef10
void __cdecl CachedChannel::SendTencentBindingQQGroup(::Pc const *, unsigned __int64, unsigned __int64, char)
{
    LIFT_STUB(0x31ef10);
}

// 0x31efc0
void __cdecl CachedChannel::SendJoinGuild(::Pc const *, unsigned __int64, char, char)
{
    LIFT_STUB(0x31efc0);
}

// 0x31f080
void __cdecl CachedChannel::SendJoinGuildByManager(unsigned __int64, unsigned __int64, char, char, unsigned __int64)
{
    LIFT_STUB(0x31f080);
}

// 0x31f160
void __cdecl CachedChannel::SendLeaveGuild(::Pc const *, unsigned __int64, unsigned __int64, char, char, char)
{
    LIFT_STUB(0x31f160);
}

// 0x31f220
void __cdecl CachedChannel::SendLeaveGuildByManager(unsigned __int64, unsigned __int64, char)
{
    LIFT_STUB(0x31f220);
}

// 0x31f2b0
void __cdecl CachedChannel::SendDelegateGuildleader(::Pc const *, unsigned __int64, unsigned __int64, unsigned __int64)
{
    LIFT_STUB(0x31f2b0);
}

// 0x31f340
void __cdecl CachedChannel::SendDelegateGuildleaderByManager(unsigned __int64, unsigned __int64, unsigned __int64)
{
    LIFT_STUB(0x31f340);
}

// 0x31f3c0
bool __cdecl CachedChannel::SendUpdateGuildLevel(::Pc const *, unsigned __int64, unsigned __int64, char, char, ::GuildBank::GuildBankItem const *const)
{
    LIFT_STUB(0x31f3c0);
}

// 0x31f680
bool __cdecl CachedChannel::SendDepositInGuildBank(::Pc const *, unsigned __int64, unsigned __int64, __int64, ::PropertyTransactionSyncFetch::SyncItem *)
{
    LIFT_STUB(0x31f680);
}

// 0x31f880
bool __cdecl CachedChannel::SendContractGuildCraft(::Pc const *, unsigned __int64, unsigned __int64, char, char, short, unsigned int, char, unsigned __int64, wchar_t const *, short, ::GuildBank::GuildBankItem const *const, ::PropertyTransactionSyncFetch::SyncItem &)
{
    LIFT_STUB(0x31f880);
}

// 0x31fca0
bool __cdecl CachedChannel::SendAssentGuildCraft(::Pc const *, unsigned __int64, unsigned __int64, unsigned __int64, char, char)
{
    LIFT_STUB(0x31fca0);
}

// 0x31fda0
bool __cdecl CachedChannel::SendDonateGuildCraftNormalMaterial(::Pc const *, unsigned __int64, unsigned __int64, unsigned __int64, int, ::PropertyTransactionSyncFetch::SyncItem &)
{
    LIFT_STUB(0x31fda0);
}

// 0x320060
bool __cdecl CachedChannel::SendDonateGuildCraftBrandMaterial(::Pc const *, unsigned __int64, unsigned __int64, unsigned __int64, int, ::PropertyTransactionSyncFetch::SyncItem &)
{
    LIFT_STUB(0x320060);
}

// 0x320320
bool __cdecl CachedChannel::SendMakeGuildCraft(::Pc const *, unsigned __int64, unsigned __int64, unsigned __int64, int, int, short, int)
{
    LIFT_STUB(0x320320);
}

// 0x320420
bool __cdecl CachedChannel::SendTakeGuildCraft(::Pc const *, unsigned __int64, unsigned __int64, ::Item *)
{
    LIFT_STUB(0x320420);
}

// 0x320850
bool __cdecl CachedChannel::SendAbandonGuildCraft(unsigned __int64, unsigned __int64, unsigned __int64, unsigned __int64, char, char)
{
    LIFT_STUB(0x320850);
}

// 0x3209d0
bool __cdecl CachedChannel::SendContractGuildUniform(::Pc const *, unsigned __int64, unsigned __int64, wchar_t const *, char const *const, int const *const, char const *const, int, int, ::GuildBank::GuildBankItem const *const)
{
    LIFT_STUB(0x3209d0);
}

// 0x321160
bool __cdecl CachedChannel::SendDonateGuildUniformMaterial(::Pc const *, unsigned __int64, unsigned __int64, unsigned __int64, unsigned int, ::PropertyTransactionSyncFetch::SyncItem &)
{
    LIFT_STUB(0x321160);
}

// 0x321410
bool __cdecl CachedChannel::SendAbandonGuildUniform(unsigned __int64, unsigned __int64, unsigned __int64, unsigned __int64)
{
    LIFT_STUB(0x321410);
}

// 0x321500
bool __cdecl CachedChannel::SendMakeGuildUniform(::Pc const *, unsigned __int64, unsigned __int64, unsigned __int64, int)
{
    LIFT_STUB(0x321500);
}

// 0x321620
bool __cdecl CachedChannel::SendFinishGuildUniform(unsigned __int64, unsigned __int64)
{
    LIFT_STUB(0x321620);
}

// 0x321710
bool __cdecl CachedChannel::SendRegisterGuildUniform(::Pc const *, unsigned __int64, unsigned __int64, unsigned __int64, short)
{
    LIFT_STUB(0x321710);
}

// 0x321850
bool __cdecl CachedChannel::SendPutOnGuildUniform(::Pc const *, unsigned __int64, unsigned __int64, unsigned __int64, int)
{
    LIFT_STUB(0x321850);
}

// 0x321990
bool __cdecl CachedChannel::SendRegisterGuildUniformWithDeletion(::Pc const *, unsigned __int64, unsigned __int64, unsigned __int64, unsigned __int64, int)
{
    LIFT_STUB(0x321990);
}

// 0x321ad0
bool __cdecl CachedChannel::SendIncreaseGuildUniformRegistrationQuota(::Pc const *, unsigned __int64, unsigned __int64, short, short, short, ::PropertyTransactionSyncFetch::SyncItem &)
{
    LIFT_STUB(0x321ad0);
}

// 0x321d30
bool __cdecl CachedChannel::SendDepositInGuildBankByManager(unsigned __int64, unsigned __int64, unsigned int, short, __int64, __int64)
{
    LIFT_STUB(0x321d30);
}

// 0x321ea0
bool __cdecl CachedChannel::SendWithdrawFromGuildBankByManager(unsigned __int64, unsigned __int64, unsigned int, short, __int64)
{
    LIFT_STUB(0x321ea0);
}

// 0x321fe0
void __cdecl CachedChannel::SendUpdateGuildGradeAuthority(::Pc const *, unsigned __int64, unsigned int, unsigned int, unsigned int, unsigned int)
{
    LIFT_STUB(0x321fe0);
}

// 0x3220a0
void __cdecl CachedChannel::SendUpdateGuildMemberGrade(::Pc const *, unsigned __int64, unsigned __int64, char)
{
    LIFT_STUB(0x3220a0);
}

// 0x322150
void __cdecl CachedChannel::SendSendGuildApplication(unsigned __int64, unsigned __int64, int, short, short, wchar_t const *, short, short, short)
{
    LIFT_STUB(0x322150);
}

// 0x322250
void __cdecl CachedChannel::SendCancelGuildApplication(unsigned __int64, unsigned __int64, unsigned __int64, short)
{
    LIFT_STUB(0x322250);
}

// 0x3222e0
void __cdecl CachedChannel::SendAcceptGuildApplication(unsigned __int64, unsigned __int64, unsigned __int64, int, short)
{
    LIFT_STUB(0x3222e0);
}

// 0x322390
void __cdecl CachedChannel::SendCancelGuildInvitation(unsigned __int64, unsigned __int64, unsigned __int64, short)
{
    LIFT_STUB(0x322390);
}

// 0x322420
void __cdecl CachedChannel::SendJoinGuildRenewal(unsigned __int64, unsigned __int64, char, char)
{
    LIFT_STUB(0x322420);
}

// 0x3224b0
void __cdecl CachedChannel::SendTencentJoinGuildRenewal(unsigned __int64, unsigned __int64, char, __int64, char)
{
    LIFT_STUB(0x3224b0);
}

// 0x322550
void __cdecl CachedChannel::SendUpdateGuildApplicationRefusal(unsigned __int64, unsigned __int64, wchar_t *, char)
{
    LIFT_STUB(0x322550);
}

// 0x3225e0
void __cdecl CachedChannel::SendCreateChallengeParty(unsigned __int64, ::Pc const *, unsigned __int64, wchar_t const *)
{
    LIFT_STUB(0x3225e0);
}

// 0x322690
void __cdecl CachedChannel::SendJoinChallengeParty(unsigned __int64, __int64, unsigned __int64, char, char, int, short)
{
    LIFT_STUB(0x322690);
}

// 0x322780
void __cdecl CachedChannel::SendChangeChallengePartyLeader(unsigned __int64, ::LeaveChallengePartyStartParam const *)
{
    LIFT_STUB(0x322780);
}

// 0x322830
void __cdecl CachedChannel::SendLeaveChallengeParty(unsigned __int64, ::LeaveChallengePartyStartParam const *, char, char, char, int, short)
{
    LIFT_STUB(0x322830);
}

// 0x322940
void __cdecl CachedChannel::SendUpdateSeasonContentsChallengePartyBestRecord(__int64, int, ::SeasonContentsChallengePartyBestRecord const &, bool, ::SeasonContentsRankingLogInfo &)
{
    LIFT_STUB(0x322940);
}

// 0x322c20
void __cdecl CachedChannel::SendInitializeCharacter(unsigned __int64, unsigned __int64, unsigned __int64, ::SeasonContentsSchedule *const, int, ::SeasonContentsSchedule *const, int, bool, int, int, int, int, int, int, int, int, int, int, int, int, int, int, ::RandomStoreInitializationData const &, bool, short, bool, short, short, short)
{
    LIFT_STUB(0x322c20);
}

// 0x3231a0
void __cdecl CachedChannel::SendInitializeCharacterOnlySeasonContentsSchedule(unsigned __int64, unsigned __int64, unsigned __int64, ::SeasonContentsSchedule *const, int)
{
    LIFT_STUB(0x3231a0);
}

// 0x323510
bool __cdecl CachedChannel::SendRegisterCraft(::Pc const *, int, char, int, int, int, short, ::CraftOutput const *const, ::PropertyTransactionSyncFetchEx *)
{
    LIFT_STUB(0x323510);
}

// 0x323a60
bool __cdecl CachedChannel::SendTakeCraft(::Pc const *, unsigned __int64, short, ::PropertyTransactionSyncFetchEx *)
{
    LIFT_STUB(0x323a60);
}

// 0x323da0
void __cdecl CachedChannel::SendAbortCraft(::Pc const *, unsigned __int64)
{
    LIFT_STUB(0x323da0);
}

// 0x323ed0
bool __cdecl CachedChannel::SendJoinCraftUnion(::Pc const *, char, short)
{
    LIFT_STUB(0x323ed0);
}

// 0x324050
bool __cdecl CachedChannel::SendLeaveCraftUnion(::Pc const *, char)
{
    LIFT_STUB(0x324050);
}

// 0x3241c0
bool __cdecl CachedChannel::SendMakeMileageDeposit(::Pc const *, unsigned __int64, short, __int64, __int64, __int64, ::PropertyTransactionSyncFetch::SyncItem *)
{
    LIFT_STUB(0x3241c0);
}

// 0x324490
bool __cdecl CachedChannel::SendChangeWeaponAppearance(::Pc const *, unsigned __int64, unsigned __int64, ::PropertyTransactionSyncFetchEx *)
{
    LIFT_STUB(0x324490);
}

// 0x3246c0
bool __cdecl CachedChannel::SendRetrieveSeasonContentsRankingReward(::Pc *)
{
    LIFT_STUB(0x3246c0);
}

// 0x324940
bool __cdecl CachedChannel::SendTakeRankingReward(::Pc const *, char, int, char, char, int, int, int, int, ::PropertyTransactionSyncFetch::SyncItem &)
{
    LIFT_STUB(0x324940);
}

// 0x324d60
void __cdecl CachedChannel::SendUpdateDuelBotTrainingRoomScore(::Pc const *, unsigned __int64, ::DuelBotTrainingRoomScoreContainer::DuelBotTrainingRoomScoreValue const &, bool)
{
    LIFT_STUB(0x324d60);
}

// 0x325030
bool __cdecl CachedChannel::SendTakeDuelBotTrainingRoomReward(::Pc const *, unsigned __int64, short, short, short, char, int, bool const *const, ::PropertyTransactionSyncFetch::SyncItem &)
{
    LIFT_STUB(0x325030);
}

// 0x325390
bool __cdecl CachedChannel::SendTakeAchievementReward(::Pc const *, unsigned __int64, short, short, bool const *const, ::PropertyTransactionSyncFetch::SyncItem &)
{
    LIFT_STUB(0x325390);
}

// 0x325610
bool __cdecl CachedChannel::SendFinishTakeAchievementReward(::Pc const *, unsigned __int64, unsigned __int64, short, short)
{
    LIFT_STUB(0x325610);
}

// 0x3257d0
bool __cdecl CachedChannel::SendRetryTakeAchievementRewardReq(unsigned __int64, short, unsigned __int64, unsigned __int64)
{
    LIFT_STUB(0x3257d0);
}

// 0x3258f0
bool __cdecl CachedChannel::SendCreateCharacter(__int64, short, unsigned __int64, ::id128 const &, ::FsdShowcaseRecord &, ::Data::PcInitialSettingRecordPtr, char const *, int, bool)
{
    LIFT_STUB(0x3258f0);
}

// 0x328a40
bool __cdecl CachedChannel::SendChangeCharacterAppearance(__int64, __int64, unsigned __int64, ::FsdMakePcRecord const &)
{
    LIFT_STUB(0x328a40);
}

// 0x328c90
bool __cdecl CachedChannel::SendChangeCharacterSex(__int64, __int64, unsigned __int64, ::FsdMakePcRecord const &)
{
    LIFT_STUB(0x328c90);
}

// 0x328ef0
bool __cdecl CachedChannel::SendChangeCharacterRace(__int64, __int64, unsigned __int64, ::FsdMakePcRecord const &)
{
    LIFT_STUB(0x328ef0);
}

// 0x329150
void __cdecl CachedChannel::SendDeleteSeasonContentsRankingLog(unsigned __int64, short, unsigned __int64)
{
    LIFT_STUB(0x329150);
}

// 0x3292a0
void __cdecl CachedChannel::SendUpdateSeasonContentsGuildCombatRecord(unsigned __int64, bool, int, ::SeasonContentsGuildCombatRecord const &, bool, ::SeasonContentsRankingLogInfo const &)
{
    LIFT_STUB(0x3292a0);
}

// 0x329590
void __cdecl CachedChannel::SendUpdateSeasonContentsCombatRecord(::Pc const *, unsigned __int64, char, bool, ::SeasonContentsCombatRecordContainer::SeasonContentsCombatRecordValue const &, bool, ::SeasonContentsRankingLogInfo const &)
{
    LIFT_STUB(0x329590);
}

// 0x329890
void __cdecl CachedChannel::SendUpdateSeasonContentsTimeAttackRecord(::Pc const *, unsigned __int64, char, bool, ::SeasonContentsTimeAttackRecordContainer::SeasonContentsTimeAttackRecordValue const &, bool, ::SeasonContentsRankingLogInfo const &)
{
    LIFT_STUB(0x329890);
}

// 0x329b80
void __cdecl CachedChannel::SendLoadSeasonContentsGuildRankingRewardList(char, int, char)
{
    LIFT_STUB(0x329b80);
}

// 0x329c30
bool __cdecl CachedChannel::SendTakeRankingRewardforGuild(unsigned __int64, char, int, char, int, char, ::GuildBankItem *const)
{
    LIFT_STUB(0x329c30);
}

// 0x32a090
bool __cdecl CachedChannel::SendUpdateGuildFlagBearer(::Pc const *, unsigned __int64, char, unsigned __int64, unsigned __int64, int)
{
    LIFT_STUB(0x32a090);
}

// 0x32a290
void __cdecl CachedChannel::SendJoinMentoring(unsigned __int64, unsigned __int64, unsigned __int64, char)
{
    LIFT_STUB(0x32a290);
}

// 0x32a320
void __cdecl CachedChannel::SendLeaveMentoring(unsigned __int64, unsigned __int64, unsigned __int64, char)
{
    LIFT_STUB(0x32a320);
}

// 0x32a3b0
bool __cdecl CachedChannel::SendCompleteClosetCollecting(::Pc const *, ::CollectingEntry const *, int, ::PropertyTransactionSyncFetchEx *)
{
    LIFT_STUB(0x32a3b0);
}

// 0x32a6e0
bool __cdecl CachedChannel::SendUpdateClosetUsed(::Pc const *, int, int *const)
{
    LIFT_STUB(0x32a6e0);
}

// 0x32aab0
void __cdecl CachedChannel::SendAddFishing(::Pc const *, ::FishingEntry const *)
{
    LIFT_STUB(0x32aab0);
}

// 0x32adc0
void __cdecl CachedChannel::SendUpdateFishing(::Pc const *, ::FishingEntry const *)
{
    LIFT_STUB(0x32adc0);
}

// 0x32b0d0
void __cdecl CachedChannel::SendInsertChallengeList(::Pc const *, ::ChallengeListEntry const *)
{
    LIFT_STUB(0x32b0d0);
}

// 0x32b3c0
void __cdecl CachedChannel::SendUpdateChallengeList(::Pc const *, ::ChallengeListEntry const *)
{
    LIFT_STUB(0x32b3c0);
}

// 0x32b6a0
void __cdecl CachedChannel::SendDeleteChallengeList(::Pc const *, char)
{
    LIFT_STUB(0x32b6a0);
}

// 0x32b8c0
void __cdecl CachedChannel::SendUpdateSlate(::Pc const &, ::Slate const &)
{
    LIFT_STUB(0x32b8c0);
}

// 0x32bcc0
void __cdecl CachedChannel::SendMainSession(char const *, ...)
{
    LIFT_STUB(0x32bcc0);
}

// 0x32bd40
void __cdecl CachedChannel::send(::Pc const *, ::Packet const *)
{
    LIFT_STUB(0x32bd40);
}

// 0x32bf00
void __cdecl CachedChannel::send(unsigned __int64, unsigned __int64, short, ::Packet const *)
{
    LIFT_STUB(0x32bf00);
}

// 0x32bfe0
::Session * __cdecl CachedChannel::getSession(unsigned __int64)
{
    LIFT_STUB(0x32bfe0);
}
