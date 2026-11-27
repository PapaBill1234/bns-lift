// cachedaemonchannel.h: cachedaemonchannel.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"
#include "duelbottrainingroomscorecontainer.h"
#include "guildbank.h"
#include "propertytran.h"
#include "seasonscore.h"

class CachedChannel
{
public:
    struct AttachedItem {};
    struct SystemPostAttachedItem {};
    struct SystemPostBodyParam {};
public:
    virtual __cdecl ~CachedChannel(void);  // 0x2e0840
    virtual bool __cdecl PacketHandler(::Session const *, ::Packet const *) const;  // 0x2e0850
protected:
    virtual void __cdecl OnCreated(::Session const *) const;  // 0x2e0bd0
    virtual bool __cdecl onConnect(::Session const *, bool);  // 0x2e0cd0
    virtual void __cdecl onClose(::Session const *, bool, bool);  // 0x2e0eb0
public:
    void __cdecl SendDeleteCacheData(::Pc const *, __int64, char);  // 0x314e50
    void __cdecl SendUpdatePc(::Pc *);  // 0x3150c0
    void __cdecl SendAddInventoryItem(::Pc const *, ::Item *, char);  // 0x315560
    void __cdecl SendAddInventoryItem(::Pc const *, ::Item *, char, unsigned short, __int64);  // 0x315990
    void __cdecl InitChangedCachePacket(::Packet *, bool);  // 0x315de0
    void __cdecl AddChangedInventoryItem(::Packet *, ::Pc const *, ::Item const *, char);  // 0x315e50
    void __cdecl SendChangedCachePacket(::Packet *, ::Pc const *);  // 0x3162b0
    void __cdecl AddUnloadCache(::Packet *, ::RepeatPacketComposer *, ::Pc const *, unsigned __int64, char);  // 0x316340
    void __cdecl SendUnloadCachePacket(::Packet *, ::RepeatPacketComposer *, ::Pc const *);  // 0x316410
    bool __cdecl SendTryWarehouseItemAcquisition(__int64, ::Pc const *, ::PropertyTransactionSyncFetch::SyncItem &, __int64, __int64, bool);  // 0x3164b0
    bool __cdecl SendTryTakeJumpingCharacter2Reward(__int64, ::Pc const *, __int64, __int64, ::PropertyTransactionSyncFetchEx *);  // 0x3167a0
    bool __cdecl SendFinishTakeJumpingCharacter2Reward(__int64, ::Pc const *, unsigned __int64);  // 0x316b00
    bool __cdecl SendTryBoardGachaPayment(__int64, ::Pc const *, __int64, ::PropertyTransactionSyncFetchEx *);  // 0x316cd0
    bool __cdecl SendFinishBoardGachaPayment(__int64, ::Pc const *, __int64);  // 0x316ff0
    bool __cdecl SendPutItemIntoCloset(::Pc const *, unsigned __int64, short, int, unsigned __int64, unsigned int, bool, bool, __int64, char, __int64, char const *const, ::PropertyTransactionSyncFetch::SyncItem &);  // 0x3171c0
    bool __cdecl SendRetrieveClosetItemInfoForTaking(::Pc const *, int, short);  // 0x3177d0
    bool __cdecl SendTakeItemFromCloset(::Pc const *, unsigned __int64, int, ::Item *, unsigned __int64);  // 0x317930
    void __cdecl SendAddQuest(::Pc const *, __int64, unsigned __int64, ::OpenQuest const *);  // 0x317dd0
    void __cdecl SendUpdateQuest(::Pc const *, ::OpenQuest const *);  // 0x3180f0
    void __cdecl SendQuestComplete(::Pc const *, ::QuestList const *);  // 0x3183b0
    void __cdecl SendDiscoveryArea(::Pc const *, ::DiscoveryArea const *);  // 0x3186f0
    void __cdecl SendActivatedTeleport(::Pc const *, ::ActivatedTeleport const *);  // 0x318a30
    void __cdecl SendClientOptionData(::Pc const *, char, char const *, short);  // 0x318d70
    void __cdecl SendAddAcquiredSkill(::Pc const *, char, unsigned int, ::AcquiredSkill1 const *);  // 0x318fe0
    void __cdecl SendUpdateAcquiredSkill(::Pc const *, char, ::SkillEntry const *);  // 0x319310
    void __cdecl SendAddEffect(::Pc const *, ::PassiveEffect const *);  // 0x3195b0
    void __cdecl AddChangedEffect(::Packet *, ::Pc const *, ::PassiveEffect const *);  // 0x319890
    void __cdecl SendAddRecycleTime(::Pc const *, short, ::RecycleTimeProperty *);  // 0x319b50
    void __cdecl SendUpdateRecycleTime(::Pc const *, short, ::RecycleTimeProperty *);  // 0x319e10
    void __cdecl SendAddSummoned(::Pc const *, char, ::SummonedProperty *);  // 0x31a110
    void __cdecl SendUpdateSummoned(::Pc const *, ::SummonedEntry *);  // 0x31a400
    void __cdecl SendAddContentQuota(::Pc const *, int, ::ContentQuota const *);  // 0x31a730
    void __cdecl SendUpdateContentQuota(::Pc const *, int, ::ContentQuota const *);  // 0x31aa20
    void __cdecl SendSkillPage(::Pc const *, ::SkillPage const *);  // 0x31acf0
    void __cdecl SendRandomStore(::Pc const *const, __int64, ::RandomStore const &);  // 0x31b030
    void __cdecl SendAddRaidDungeonBindData(::Pc const *, __int64, ::RaidDungeonBindPropertyEntry const *);  // 0x31b3f0
    void __cdecl SendAddRaidDungeonUnbindData(::Pc const *, int, ::RaidDungeonUnbindPropertyEntry const *);  // 0x31b700
    void __cdecl SendUpdateRaidDungeonUnbindData(::Pc const *, int, ::RaidDungeonUnbindPropertyEntry const *);  // 0x31ba10
    void __cdecl SendSkillSkinAcquired(::Pc const *, ::SkillSkinProperty const *);  // 0x31bd00
    void __cdecl SendMentoringProperty(::Pc const *, ::MentoringProperty const *);  // 0x31c040
    void __cdecl SendDetachPostItemForInsert(unsigned __int64, __int64, __int64, char, __int64, __int64, ::Item *);  // 0x31c380
    void __cdecl SendDetachPostItemForUpdate(unsigned __int64, __int64, __int64, char, __int64, __int64, char, __int64, short);  // 0x31cb90
    void __cdecl SendDetachPostMoney(unsigned __int64, __int64, __int64, char, __int64, __int64, __int64);  // 0x31cdc0
    void __cdecl SendRegisterPawn(::Pc const *, char, unsigned __int64, __int64, char, char, __int64, __int64, char, char *const, __int64 *const, int *const);  // 0x31cff0
    void __cdecl SendDeliverPostReq(::Pc *, char, char, short, __int64, wchar_t *, wchar_t *, wchar_t *, ::CachedChannel::AttachedItem *const, short);  // 0x31d2c0
    void __cdecl SendDeliverSystemPostReq(::Pc *, char, char, __int64, short, __int64, wchar_t *, wchar_t *, wchar_t *, ::CachedChannel::SystemPostAttachedItem *const, short);  // 0x31d720
    void __cdecl SendDeliverSystemPostReq(unsigned __int64, ::CachedChannel::SystemPostBodyParam &, ::CachedChannel::SystemPostAttachedItem *const, short);  // 0x31db40
    bool __cdecl SendInitializeGuildCombatScore(::SeasonContentsSchedule const &, bool);  // 0x31df10
    bool __cdecl SendInitializeSeasonContentsChallengePartySchedule(::SeasonContentsSchedule const &, bool);  // 0x31e280
    bool __cdecl SendInitializeMentoring(short, bool);  // 0x31e530
    void __cdecl SendCreateGuild(::Pc const *, unsigned __int64, unsigned __int64, char, wchar_t const *);  // 0x31e790
    bool __cdecl SendRenameGuild(unsigned __int64, unsigned __int64, unsigned __int64, char, wchar_t const *, unsigned __int64);  // 0x31ea20
    bool __cdecl SendTryToRenameGuild(::Pc const *, unsigned __int64, unsigned __int64, char, wchar_t const *, unsigned __int64, long, ::PropertyTransactionSyncFetchEx *);  // 0x31eb70
    void __cdecl SendTencentJoinGuild(::Pc const *, unsigned __int64, char, char, __int64);  // 0x31ee40
    void __cdecl SendTencentBindingQQGroup(::Pc const *, unsigned __int64, unsigned __int64, char);  // 0x31ef10
    void __cdecl SendJoinGuild(::Pc const *, unsigned __int64, char, char);  // 0x31efc0
    void __cdecl SendJoinGuildByManager(unsigned __int64, unsigned __int64, char, char, unsigned __int64);  // 0x31f080
    void __cdecl SendLeaveGuild(::Pc const *, unsigned __int64, unsigned __int64, char, char, char);  // 0x31f160
    void __cdecl SendLeaveGuildByManager(unsigned __int64, unsigned __int64, char);  // 0x31f220
    void __cdecl SendDelegateGuildleader(::Pc const *, unsigned __int64, unsigned __int64, unsigned __int64);  // 0x31f2b0
    void __cdecl SendDelegateGuildleaderByManager(unsigned __int64, unsigned __int64, unsigned __int64);  // 0x31f340
    bool __cdecl SendUpdateGuildLevel(::Pc const *, unsigned __int64, unsigned __int64, char, char, ::GuildBank::GuildBankItem const *const);  // 0x31f3c0
    bool __cdecl SendDepositInGuildBank(::Pc const *, unsigned __int64, unsigned __int64, __int64, ::PropertyTransactionSyncFetch::SyncItem *);  // 0x31f680
    bool __cdecl SendContractGuildCraft(::Pc const *, unsigned __int64, unsigned __int64, char, char, short, unsigned int, char, unsigned __int64, wchar_t const *, short, ::GuildBank::GuildBankItem const *const, ::PropertyTransactionSyncFetch::SyncItem &);  // 0x31f880
    bool __cdecl SendAssentGuildCraft(::Pc const *, unsigned __int64, unsigned __int64, unsigned __int64, char, char);  // 0x31fca0
    bool __cdecl SendDonateGuildCraftNormalMaterial(::Pc const *, unsigned __int64, unsigned __int64, unsigned __int64, int, ::PropertyTransactionSyncFetch::SyncItem &);  // 0x31fda0
    bool __cdecl SendDonateGuildCraftBrandMaterial(::Pc const *, unsigned __int64, unsigned __int64, unsigned __int64, int, ::PropertyTransactionSyncFetch::SyncItem &);  // 0x320060
    bool __cdecl SendMakeGuildCraft(::Pc const *, unsigned __int64, unsigned __int64, unsigned __int64, int, int, short, int);  // 0x320320
    bool __cdecl SendTakeGuildCraft(::Pc const *, unsigned __int64, unsigned __int64, ::Item *);  // 0x320420
    bool __cdecl SendAbandonGuildCraft(unsigned __int64, unsigned __int64, unsigned __int64, unsigned __int64, char, char);  // 0x320850
    bool __cdecl SendContractGuildUniform(::Pc const *, unsigned __int64, unsigned __int64, wchar_t const *, char const *const, int const *const, char const *const, int, int, ::GuildBank::GuildBankItem const *const);  // 0x3209d0
    bool __cdecl SendDonateGuildUniformMaterial(::Pc const *, unsigned __int64, unsigned __int64, unsigned __int64, unsigned int, ::PropertyTransactionSyncFetch::SyncItem &);  // 0x321160
    bool __cdecl SendAbandonGuildUniform(unsigned __int64, unsigned __int64, unsigned __int64, unsigned __int64);  // 0x321410
    bool __cdecl SendMakeGuildUniform(::Pc const *, unsigned __int64, unsigned __int64, unsigned __int64, int);  // 0x321500
    bool __cdecl SendFinishGuildUniform(unsigned __int64, unsigned __int64);  // 0x321620
    bool __cdecl SendRegisterGuildUniform(::Pc const *, unsigned __int64, unsigned __int64, unsigned __int64, short);  // 0x321710
    bool __cdecl SendPutOnGuildUniform(::Pc const *, unsigned __int64, unsigned __int64, unsigned __int64, int);  // 0x321850
    bool __cdecl SendRegisterGuildUniformWithDeletion(::Pc const *, unsigned __int64, unsigned __int64, unsigned __int64, unsigned __int64, int);  // 0x321990
    bool __cdecl SendIncreaseGuildUniformRegistrationQuota(::Pc const *, unsigned __int64, unsigned __int64, short, short, short, ::PropertyTransactionSyncFetch::SyncItem &);  // 0x321ad0
    bool __cdecl SendDepositInGuildBankByManager(unsigned __int64, unsigned __int64, unsigned int, short, __int64, __int64);  // 0x321d30
    bool __cdecl SendWithdrawFromGuildBankByManager(unsigned __int64, unsigned __int64, unsigned int, short, __int64);  // 0x321ea0
    void __cdecl SendUpdateGuildGradeAuthority(::Pc const *, unsigned __int64, unsigned int, unsigned int, unsigned int, unsigned int);  // 0x321fe0
    void __cdecl SendUpdateGuildMemberGrade(::Pc const *, unsigned __int64, unsigned __int64, char);  // 0x3220a0
    void __cdecl SendSendGuildApplication(unsigned __int64, unsigned __int64, int, short, short, wchar_t const *, short, short, short);  // 0x322150
    void __cdecl SendCancelGuildApplication(unsigned __int64, unsigned __int64, unsigned __int64, short);  // 0x322250
    void __cdecl SendAcceptGuildApplication(unsigned __int64, unsigned __int64, unsigned __int64, int, short);  // 0x3222e0
    void __cdecl SendCancelGuildInvitation(unsigned __int64, unsigned __int64, unsigned __int64, short);  // 0x322390
    void __cdecl SendJoinGuildRenewal(unsigned __int64, unsigned __int64, char, char);  // 0x322420
    void __cdecl SendTencentJoinGuildRenewal(unsigned __int64, unsigned __int64, char, __int64, char);  // 0x3224b0
    void __cdecl SendUpdateGuildApplicationRefusal(unsigned __int64, unsigned __int64, wchar_t *, char);  // 0x322550
    void __cdecl SendCreateChallengeParty(unsigned __int64, ::Pc const *, unsigned __int64, wchar_t const *);  // 0x3225e0
    void __cdecl SendJoinChallengeParty(unsigned __int64, __int64, unsigned __int64, char, char, int, short);  // 0x322690
    void __cdecl SendChangeChallengePartyLeader(unsigned __int64, ::LeaveChallengePartyStartParam const *);  // 0x322780
    void __cdecl SendLeaveChallengeParty(unsigned __int64, ::LeaveChallengePartyStartParam const *, char, char, char, int, short);  // 0x322830
    void __cdecl SendUpdateSeasonContentsChallengePartyBestRecord(__int64, int, ::SeasonContentsChallengePartyBestRecord const &, bool, ::SeasonContentsRankingLogInfo &);  // 0x322940
    void __cdecl SendInitializeCharacter(unsigned __int64, unsigned __int64, unsigned __int64, ::SeasonContentsSchedule *const, int, ::SeasonContentsSchedule *const, int, bool, int, int, int, int, int, int, int, int, int, int, int, int, int, int, ::RandomStoreInitializationData const &, bool, short, bool, short, short, short);  // 0x322c20
    void __cdecl SendInitializeCharacterOnlySeasonContentsSchedule(unsigned __int64, unsigned __int64, unsigned __int64, ::SeasonContentsSchedule *const, int);  // 0x3231a0
    bool __cdecl SendRegisterCraft(::Pc const *, int, char, int, int, int, short, ::CraftOutput const *const, ::PropertyTransactionSyncFetchEx *);  // 0x323510
    bool __cdecl SendTakeCraft(::Pc const *, unsigned __int64, short, ::PropertyTransactionSyncFetchEx *);  // 0x323a60
    void __cdecl SendAbortCraft(::Pc const *, unsigned __int64);  // 0x323da0
    bool __cdecl SendJoinCraftUnion(::Pc const *, char, short);  // 0x323ed0
    bool __cdecl SendLeaveCraftUnion(::Pc const *, char);  // 0x324050
    bool __cdecl SendMakeMileageDeposit(::Pc const *, unsigned __int64, short, __int64, __int64, __int64, ::PropertyTransactionSyncFetch::SyncItem *);  // 0x3241c0
    bool __cdecl SendChangeWeaponAppearance(::Pc const *, unsigned __int64, unsigned __int64, ::PropertyTransactionSyncFetchEx *);  // 0x324490
    bool __cdecl SendRetrieveSeasonContentsRankingReward(::Pc *);  // 0x3246c0
    bool __cdecl SendTakeRankingReward(::Pc const *, char, int, char, char, int, int, int, int, ::PropertyTransactionSyncFetch::SyncItem &);  // 0x324940
    void __cdecl SendUpdateDuelBotTrainingRoomScore(::Pc const *, unsigned __int64, ::DuelBotTrainingRoomScoreContainer::DuelBotTrainingRoomScoreValue const &, bool);  // 0x324d60
    bool __cdecl SendTakeDuelBotTrainingRoomReward(::Pc const *, unsigned __int64, short, short, short, char, int, bool const *const, ::PropertyTransactionSyncFetch::SyncItem &);  // 0x325030
    bool __cdecl SendTakeAchievementReward(::Pc const *, unsigned __int64, short, short, bool const *const, ::PropertyTransactionSyncFetch::SyncItem &);  // 0x325390
    bool __cdecl SendFinishTakeAchievementReward(::Pc const *, unsigned __int64, unsigned __int64, short, short);  // 0x325610
    bool __cdecl SendRetryTakeAchievementRewardReq(unsigned __int64, short, unsigned __int64, unsigned __int64);  // 0x3257d0
    bool __cdecl SendCreateCharacter(__int64, short, unsigned __int64, ::id128 const &, ::FsdShowcaseRecord &, ::Data::PcInitialSettingRecordPtr, char const *, int, bool);  // 0x3258f0
    bool __cdecl SendChangeCharacterAppearance(__int64, __int64, unsigned __int64, ::FsdMakePcRecord const &);  // 0x328a40
    bool __cdecl SendChangeCharacterSex(__int64, __int64, unsigned __int64, ::FsdMakePcRecord const &);  // 0x328c90
    bool __cdecl SendChangeCharacterRace(__int64, __int64, unsigned __int64, ::FsdMakePcRecord const &);  // 0x328ef0
    void __cdecl SendDeleteSeasonContentsRankingLog(unsigned __int64, short, unsigned __int64);  // 0x329150
    void __cdecl SendUpdateSeasonContentsGuildCombatRecord(unsigned __int64, bool, int, ::SeasonContentsGuildCombatRecord const &, bool, ::SeasonContentsRankingLogInfo const &);  // 0x3292a0
    void __cdecl SendUpdateSeasonContentsCombatRecord(::Pc const *, unsigned __int64, char, bool, ::SeasonContentsCombatRecordContainer::SeasonContentsCombatRecordValue const &, bool, ::SeasonContentsRankingLogInfo const &);  // 0x329590
    void __cdecl SendUpdateSeasonContentsTimeAttackRecord(::Pc const *, unsigned __int64, char, bool, ::SeasonContentsTimeAttackRecordContainer::SeasonContentsTimeAttackRecordValue const &, bool, ::SeasonContentsRankingLogInfo const &);  // 0x329890
    void __cdecl SendLoadSeasonContentsGuildRankingRewardList(char, int, char);  // 0x329b80
    bool __cdecl SendTakeRankingRewardforGuild(unsigned __int64, char, int, char, int, char, ::GuildBankItem *const);  // 0x329c30
    bool __cdecl SendUpdateGuildFlagBearer(::Pc const *, unsigned __int64, char, unsigned __int64, unsigned __int64, int);  // 0x32a090
    void __cdecl SendJoinMentoring(unsigned __int64, unsigned __int64, unsigned __int64, char);  // 0x32a290
    void __cdecl SendLeaveMentoring(unsigned __int64, unsigned __int64, unsigned __int64, char);  // 0x32a320
    bool __cdecl SendCompleteClosetCollecting(::Pc const *, ::CollectingEntry const *, int, ::PropertyTransactionSyncFetchEx *);  // 0x32a3b0
    bool __cdecl SendUpdateClosetUsed(::Pc const *, int, int *const);  // 0x32a6e0
    void __cdecl SendAddFishing(::Pc const *, ::FishingEntry const *);  // 0x32aab0
    void __cdecl SendUpdateFishing(::Pc const *, ::FishingEntry const *);  // 0x32adc0
    void __cdecl SendInsertChallengeList(::Pc const *, ::ChallengeListEntry const *);  // 0x32b0d0
    void __cdecl SendUpdateChallengeList(::Pc const *, ::ChallengeListEntry const *);  // 0x32b3c0
    void __cdecl SendDeleteChallengeList(::Pc const *, char);  // 0x32b6a0
    void __cdecl SendUpdateSlate(::Pc const &, ::Slate const &);  // 0x32b8c0
    void __cdecl SendMainSession(char const *, ...);  // 0x32bcc0
protected:
    void __cdecl send(::Pc const *, ::Packet const *);  // 0x32bd40
    void __cdecl send(unsigned __int64, unsigned __int64, short, ::Packet const *);  // 0x32bf00
    virtual ::Session * __cdecl getSession(unsigned __int64);  // 0x32bfe0
};

void __cdecl ComposePropertyPair(::FragmentPacket &, ::Property &);  // 0x2e0720
bool __cdecl HandleCacheGame_HelloOk(::Session const *, ::Packet const *);  // 0x2e1030
bool __cdecl HandleCacheGame_HelloFail(::Session const *, ::Packet const *);  // 0x2e1380
bool __cdecl HandleCacheGame_InitializeSeasonContentsScheduleOk(::Session const *, ::Packet const *);  // 0x2e13b0
bool __cdecl HandleCacheGame_InitializeSeasonContentsScheduleFail(::Session const *, ::Packet const *);  // 0x2e14a0
bool __cdecl HandleCacheGame_InitializeSeasonContentsChallengePartyScheduleOk(::Session const *, ::Packet const *);  // 0x2e14d0
bool __cdecl HandleCacheGame_InitializeSeasonContentsChallengePartyScheduleFail(::Session const *, ::Packet const *);  // 0x2e15b0
bool __cdecl HandleCacheGame_LoadGuildCombatRecordOk(::Session const *, ::Packet const *);  // 0x2e15f0
bool __cdecl HandleCacheGame_LoadGuildCombatRecordFail(::Session const *, ::Packet const *);  // 0x2e1a80
bool __cdecl HandleCacheGame_RetrieveFactionStatisticsFail(::Session const *, ::Packet const *);  // 0x2e1b00
bool __cdecl HandleCacheGame_RetrieveFactionStatisticsOk(::Session const *, ::Packet const *);  // 0x2e1b50
bool __cdecl HandleCacheGame_InsertCacheOk(::Session const *, ::Packet const *);  // 0x2e1d70
bool __cdecl HandleCacheGame_InsertCacheFail(::Session const *, ::Packet const *);  // 0x2e2180
bool __cdecl HandleCacheGame_RetrieveCharacterInfoOk(::Session const *, ::Packet const *);  // 0x2e25b0
bool __cdecl HandleCacheGame_RetrieveCharacterInfoFail(::Session const *, ::Packet const *);  // 0x2e28f0
bool __cdecl HandleCacheGame_RetrieveBuilderRightOk(::Session const *, ::Packet const *);  // 0x2e2b30
bool __cdecl HandleCacheGame_RetrieveBuilderRightFail(::Session const *, ::Packet const *);  // 0x2e2ce0
bool __cdecl HandleCacheGame_RegisterPawnOk(::Session const *, ::Packet const *);  // 0x2e2d90
bool __cdecl HandleCacheGame_RegisterPawnFail(::Session const *, ::Packet const *);  // 0x2e3100
bool __cdecl HandleCacheGame_CancelPawnOk(::Session const *, ::Packet const *);  // 0x2e3450
bool __cdecl HandleCacheGame_CancelPawnFail(::Session const *, ::Packet const *);  // 0x2e36c0
bool __cdecl HandleCacheGame_AddPawnMoneyOk(::Session const *, ::Packet const *);  // 0x2e3a50
bool __cdecl HandleCacheGame_AddPawnMoneyFail(::Session const *, ::Packet const *);  // 0x2e3af0
bool __cdecl HandleCacheGame_SubtractPawnMoneyOk(::Session const *, ::Packet const *);  // 0x2e3c90
bool __cdecl HandleCacheGame_SubtractPawnMoneyFail(::Session const *, ::Packet const *);  // 0x2e3d30
bool __cdecl HandleCacheGame_CheckPostCapacityOk(::Session const *, ::Packet const *);  // 0x2e3de0
bool __cdecl HandleCacheGame_CheckPostCapacityFail(::Session const *, ::Packet const *);  // 0x2e3e80
bool __cdecl HandleCacheGame_DeliverSystemPostOk(::Session const *, ::Packet const *);  // 0x2e4010
bool __cdecl HandleCacheGame_DeliverSystemPostFail(::Session const *, ::Packet const *);  // 0x2e4080
bool __cdecl HandleCacheGame_PostReceiptNotify(::Session const *, ::Packet const *);  // 0x2e40f0
bool __cdecl HandleCacheGame_RetrievePostCountOk(::Session const *, ::Packet const *);  // 0x2e47b0
bool __cdecl HandleCacheGame_RetrievePostCountFail(::Session const *, ::Packet const *);  // 0x2e48f0
bool __cdecl HandleCacheGame_RetrievePostBriefListOk(::Session const *, ::Packet const *);  // 0x2e4a60
bool __cdecl HandleCacheGame_RetrievePostBriefListFail(::Session const *, ::Packet const *);  // 0x2e51c0
bool __cdecl HandleCacheGame_RetrievePostOk(::Session const *, ::Packet const *);  // 0x2e52b0
bool __cdecl HandleCacheGame_RetrievePostFail(::Session const *, ::Packet const *);  // 0x2e5aa0
bool __cdecl HandleCacheGame_DetachPostItemForInsertFail(::Session const *, ::Packet const *);  // 0x2e5bb0
bool __cdecl HandleCacheGame_DetachPostItemForInsertOk(::Session const *, ::Packet const *);  // 0x2e5df0
bool __cdecl HandleCacheGame_DetachPostItemForUpdateFail(::Session const *, ::Packet const *);  // 0x2e6030
bool __cdecl HandleCacheGame_DetachPostItemForUpdateOk(::Session const *, ::Packet const *);  // 0x2e6270
bool __cdecl HandleCacheGame_ReadPostOk(::Session const *, ::Packet const *);  // 0x2e6490
bool __cdecl HandleCacheGame_ArchivePostOk(::Session const *, ::Packet const *);  // 0x2e67c0
bool __cdecl HandleCacheGame_ArchivePostFail(::Session const *, ::Packet const *);  // 0x2e6b00
bool __cdecl HandleCacheGame_MarkPostTypeToExpressOk(::Session const *, ::Packet const *);  // 0x2e6c10
bool __cdecl HandleCacheGame_MarkPostTypeToExpressFail(::Session const *, ::Packet const *);  // 0x2e6e10
bool __cdecl HandleCacheGame_LoadGuildMemberListOk(::Session const *, ::Packet const *);  // 0x2e7030
bool __cdecl HandleCacheGame_LoadGuildMemberListFail(::Session const *, ::Packet const *);  // 0x2e7620
bool __cdecl HandleCacheGame_LoadGuildContentsListOk(::Session const *, ::Packet const *);  // 0x2e7870
bool __cdecl HandleCacheGame_LoadGuildContentsListFail(::Session const *, ::Packet const *);  // 0x2e87e0
bool __cdecl HandleCacheGame_LoadSeasonContentsGuildRankingRewardListOk(::Session const *, ::Packet const *);  // 0x2e8b10
bool __cdecl HandleCacheGame_LoadSeasonContentsGuildRankingRewardListFail(::Session const *, ::Packet const *);  // 0x2e8ba0
bool __cdecl HandleCacheGame_LoadSeasonContentsGuildRankingLogListOk(::Session const *, ::Packet const *);  // 0x2e8ce0
bool __cdecl HandleCacheGame_LoadSeasonContentsGuildRankingLogListFail(::Session const *, ::Packet const *);  // 0x2e9010
bool __cdecl HandleCacheGame_LoadSeasonContentsChallengePartyRankingLogListOk(::Session const *, ::Packet const *);  // 0x2e90d0
bool __cdecl HandleCacheGame_LoadSeasonContentsChallengePartyRankingLogListFail(::Session const *, ::Packet const *);  // 0x2e9410
bool __cdecl HandleCacheGame_UpdateSeasonContentsGuildCombatRecordOk(::Session const *, ::Packet const *);  // 0x2e9520
bool __cdecl HandleCacheGame_UpdateSeasonContentsGuildCombatRecordFail(::Session const *, ::Packet const *);  // 0x2e96a0
bool __cdecl HandleCacheGame_UpdateSeasonContentsChallengePartyBestRecordOk(::Session const *, ::Packet const *);  // 0x2e97e0
bool __cdecl HandleCacheGame_UpdateSeasonContentsChallengePartyBestRecordFail(::Session const *, ::Packet const *);  // 0x2e9990
bool __cdecl HandleCacheGame_TakeRankingRewardForGuildOk(::Session const *, ::Packet const *);  // 0x2e9b00
bool __cdecl HandleCacheGame_TakeRankingRewardForGuildFail(::Session const *, ::Packet const *);  // 0x2ea040
bool __cdecl HandleCacheGame_UpdateGuildFlagBearerOk(::Session const *, ::Packet const *);  // 0x2ea190
bool __cdecl HandleCacheGame_UpdateGuildFlagBearerFail(::Session const *, ::Packet const *);  // 0x2ea570
bool __cdecl HandleCacheGame_CreateGuildOk(::Session const *, ::Packet const *);  // 0x2ea6c0
bool __cdecl HandleCacheGame_CreateGuildFail(::Session const *, ::Packet const *);  // 0x2eaab0
bool __cdecl HandleCacheGame_RenameGuildOk(::Session const *, ::Packet const *);  // 0x2eae60
bool __cdecl HandleCacheGame_RenameGuildFail(::Session const *, ::Packet const *);  // 0x2eafa0
bool __cdecl HandleCacheGame_TryToRenameGuildOk(::Session const *, ::Packet const *);  // 0x2eb1b0
bool __cdecl HandleCacheGame_TryToRenameGuildFail(::Session const *, ::Packet const *);  // 0x2eb500
bool __cdecl HandleCacheGame_RecoverUncompletedRenameGuildOk(::Session const *, ::Packet const *);  // 0x2eb880
bool __cdecl HandleCacheGame_RecoverUncompletedRenameGuildFail(::Session const *, ::Packet const *);  // 0x2ebab0
bool __cdecl HandleCacheGame_DeleteGuildOk(::Session const *, ::Packet const *);  // 0x2ebce0
bool __cdecl HandleCacheGame_DeleteGuildFail(::Session const *, ::Packet const *);  // 0x2ebe30
bool __cdecl HandleCacheGame_JoinGuildOk(::Session const *, ::Packet const *);  // 0x2ec0a0
bool __cdecl HandleCacheGame_JoinGuildFail(::Session const *, ::Packet const *);  // 0x2ec640
bool __cdecl HandleCacheGame_LeaveGuildOk(::Session const *, ::Packet const *);  // 0x2eca80
bool __cdecl HandleCacheGame_LeaveGuildFail(::Session const *, ::Packet const *);  // 0x2ed570
bool __cdecl HandleCacheGame_DelegateGuildLeaderOk(::Session const *, ::Packet const *);  // 0x2ed7f0
bool __cdecl HandleCacheGame_DelegateGuildLeaderFail(::Session const *, ::Packet const *);  // 0x2edbb0
bool __cdecl HandleCacheGame_UpdateGuildNotificationMessageOk(::Session const *, ::Packet const *);  // 0x2edee0
bool __cdecl HandleCacheGame_UpdateGuildNotificationMessageFail(::Session const *, ::Packet const *);  // 0x2ee160
bool __cdecl HandleCacheGame_UpdateGuildGradeAuthorityOk(::Session const *, ::Packet const *);  // 0x2ee420
bool __cdecl HandleCacheGame_UpdateGuildGradeAuthorityFail(::Session const *, ::Packet const *);  // 0x2ee800
bool __cdecl HandleCacheGame_UpdateGuildMemberGradeOk(::Session const *, ::Packet const *);  // 0x2eeb20
bool __cdecl HandleCacheGame_UpdateGuildMemberGradeFail(::Session const *, ::Packet const *);  // 0x2eeee0
bool __cdecl HandleCacheGame_SendGuildApplicationOk(::Session const *, ::Packet const *);  // 0x2ef250
bool __cdecl HandleCacheGame_SendGuildApplicationFail(::Session const *, ::Packet const *);  // 0x2ef980
bool __cdecl HandleCacheGame_CancelGuildApplicationOk(::Session const *, ::Packet const *);  // 0x2efc80
bool __cdecl HandleCacheGame_CancelGuildApplicationFail(::Session const *, ::Packet const *);  // 0x2f07d0
bool __cdecl HandleCacheGame_AcceptGuildApplicationOk(::Session const *, ::Packet const *);  // 0x2f0d40
bool __cdecl HandleCacheGame_AcceptGuildApplicationFail(::Session const *, ::Packet const *);  // 0x2f1630
bool __cdecl HandleCacheGame_SendGuildInvitationOk(::Session const *, ::Packet const *);  // 0x2f1930
bool __cdecl HandleCacheGame_SendGuildInvitationFail(::Session const *, ::Packet const *);  // 0x2f21f0
bool __cdecl HandleCacheGame_CancelGuildInvitationOk(::Session const *, ::Packet const *);  // 0x2f2530
bool __cdecl HandleCacheGame_CancelGuildInvitationFail(::Session const *, ::Packet const *);  // 0x2f3120
bool __cdecl HandleCacheGame_JoinGuildRenewalOk(::Session const *, ::Packet const *);  // 0x2f3620
bool __cdecl HandleCacheGame_JoinGuildRenewalFail(::Session const *, ::Packet const *);  // 0x2f39c0
bool __cdecl HandleCacheGame_TencentJoinGuildRenewalOk(::Session const *, ::Packet const *);  // 0x2f3c80
bool __cdecl HandleCacheGame_TencentJoinGuildRenewalFail(::Session const *, ::Packet const *);  // 0x2f4080
bool __cdecl HandleCacheGame_UpdateGuildApplicationRefusalOk(::Session const *, ::Packet const *);  // 0x2f4380
bool __cdecl HandleCacheGame_UpdateGuildApplicationRefusalFail(::Session const *, ::Packet const *);  // 0x2f46c0
bool __cdecl HandleCacheGame_LoadGuildListOk(::Session const *, ::Packet const *);  // 0x2f4940
bool __cdecl HandleCacheGame_LoadGuildListFail(::Session const *, ::Packet const *);  // 0x2f51f0
bool __cdecl HandleCacheGame_UpdateGuildLevelOk(::Session const *, ::Packet const *);  // 0x2f52e0
bool __cdecl HandleCacheGame_UpdateGuildLevelFail(::Session const *, ::Packet const *);  // 0x2f5720
bool __cdecl HandleCacheGame_DepositInGuildBankOk(::Session const *, ::Packet const *);  // 0x2f5a50
bool __cdecl HandleCacheGame_DepositInGuildBankFail(::Session const *, ::Packet const *);  // 0x2f5f40
bool __cdecl HandleCacheGame_DepositInGuildBankByManagerOk(::Session const *, ::Packet const *);  // 0x2f6540
bool __cdecl HandleCacheGame_DepositInGuildBankByManagerFail(::Session const *, ::Packet const *);  // 0x2f66c0
bool __cdecl HandleCacheGame_WithdrawFromGuildBankByManagerOk(::Session const *, ::Packet const *);  // 0x2f6970
bool __cdecl HandleCacheGame_WithdrawFromGuildBankByManagerFail(::Session const *, ::Packet const *);  // 0x2f6af0
bool __cdecl HandleCacheGame_LoadUncompletedWarehouseItemAcquisitionOk(::Session const *, ::Packet const *);  // 0x2f6da0
bool __cdecl HandleCacheGame_LoadUncompletedWarehouseItemAcquisitionFail(::Session const *, ::Packet const *);  // 0x2f6f60
bool __cdecl HandleCacheGame_TryWarehouseItemAcquisitionOk(::Session const *, ::Packet const *);  // 0x2f70d0
bool __cdecl HandleCacheGame_TryWarehouseItemAcquisitionFail(::Session const *, ::Packet const *);  // 0x2f73a0
bool __cdecl HandleCacheGame_TryTakeJumpingCharacter2RewardOk(::Session const *, ::Packet const *);  // 0x2f7560
bool __cdecl HandleCacheGame_TryTakeJumpingCharacter2RewardFail(::Session const *, ::Packet const *);  // 0x2f7ab0
bool __cdecl HandleCacheGame_FinishTakeJumpingCharacter2RewardOk(::Session const *, ::Packet const *);  // 0x2f7fa0
bool __cdecl HandleCacheGame_FinishTakeJumpingCharacter2RewardFail(::Session const *, ::Packet const *);  // 0x2f80d0
bool __cdecl HandleCacheGame_ContractGuildCraftOk(::Session const *, ::Packet const *);  // 0x2f8300
bool __cdecl HandleCacheGame_ContractGuildCraftFail(::Session const *, ::Packet const *);  // 0x2f8790
bool __cdecl HandleCacheGame_AssentGuildCraftOk(::Session const *, ::Packet const *);  // 0x2f8b90
bool __cdecl HandleCacheGame_AssentGuildCraftFail(::Session const *, ::Packet const *);  // 0x2f8dc0
bool __cdecl HandleCacheGame_DonateGuildCraftNormalMaterialOk(::Session const *, ::Packet const *);  // 0x2f9020
bool __cdecl HandleCacheGame_DonateGuildCraftNormalMaterialFail(::Session const *, ::Packet const *);  // 0x2f9250
bool __cdecl HandleCacheGame_DonateGuildCraftBrandMaterialOk(::Session const *, ::Packet const *);  // 0x2f9790
bool __cdecl HandleCacheGame_DonateGuildCraftBrandMaterialFail(::Session const *, ::Packet const *);  // 0x2f99c0
bool __cdecl HandleCacheGame_MakeGuildCraftOk(::Session const *, ::Packet const *);  // 0x2f9ec0
bool __cdecl HandleCacheGame_MakeGuildCraftFail(::Session const *, ::Packet const *);  // 0x2fa1a0
bool __cdecl HandleCacheGame_FinishGuildCraftOk(::Session const *, ::Packet const *);  // 0x2fa4a0
bool __cdecl HandleCacheGame_FinishGuildCraftFail(::Session const *, ::Packet const *);  // 0x2fa760
bool __cdecl HandleCacheGame_TakeGuildCraftOk(::Session const *, ::Packet const *);  // 0x2fa870
bool __cdecl HandleCacheGame_TakeGuildCraftFail(::Session const *, ::Packet const *);  // 0x2fb170
bool __cdecl HandleCacheGame_AbandonGuildCraftOk(::Session const *, ::Packet const *);  // 0x2fb7c0
bool __cdecl HandleCacheGame_AbandonGuildCraftFail(::Session const *, ::Packet const *);  // 0x2fb9d0
bool __cdecl HandleCacheGame_ContractGuildUniformOk(::Session const *, ::Packet const *);  // 0x2fbcb0
bool __cdecl HandleCacheGame_ContractGuildUniformFail(::Session const *, ::Packet const *);  // 0x2fbe60
bool __cdecl HandleCacheGame_DonateGuildUniformMaterialOk(::Session const *, ::Packet const *);  // 0x2fc0e0
bool __cdecl HandleCacheGame_DonateGuildUniformMaterialFail(::Session const *, ::Packet const *);  // 0x2fc290
bool __cdecl HandleCacheGame_AbandonGuildUniformOk(::Session const *, ::Packet const *);  // 0x2fc6e0
bool __cdecl HandleCacheGame_AbandonGuildUniformFail(::Session const *, ::Packet const *);  // 0x2fc8f0
bool __cdecl HandleCacheGame_MakeGuildUniformOk(::Session const *, ::Packet const *);  // 0x2fcbd0
bool __cdecl HandleCacheGame_MakeGuildUniformFail(::Session const *, ::Packet const *);  // 0x2fcea0
bool __cdecl HandleCacheGame_FinishGuildUniformOk(::Session const *, ::Packet const *);  // 0x2fd140
bool __cdecl HandleCacheGame_FinishGuildUniformFail(::Session const *, ::Packet const *);  // 0x2fd310
bool __cdecl HandleCacheGame_RegisterGuildUniformOk(::Session const *, ::Packet const *);  // 0x2fd430
bool __cdecl HandleCacheGame_RegisterGuildUniformFail(::Session const *, ::Packet const *);  // 0x2fd5c0
bool __cdecl HandleCacheGame_PutOnGuildUniformOk(::Session const *, ::Packet const *);  // 0x2fd860
bool __cdecl HandleCacheGame_PutOnGuildUniformFail(::Session const *, ::Packet const *);  // 0x2fdae0
bool __cdecl HandleCacheGame_RegisterGuildUniformWithDeletionOk(::Session const *, ::Packet const *);  // 0x2fdd80
bool __cdecl HandleCacheGame_RegisterGuildUniformWithDeletionFail(::Session const *, ::Packet const *);  // 0x2fdf50
bool __cdecl HandleCacheGame_IncreaseGuildUniformRegistrationQuotaOk(::Session const *, ::Packet const *);  // 0x2fe140
bool __cdecl HandleCacheGame_IncreaseGuildUniformRegistrationQuotaFail(::Session const *, ::Packet const *);  // 0x2fe2d0
bool __cdecl HandleCacheGame_RetrievePcDataOk(::Session const *, ::Packet const *);  // 0x2fe6e0
bool __cdecl HandleCacheGame_RetrievePcDataFail(::Session const *, ::Packet const *);  // 0x2fee40
bool __cdecl HandleCacheGame_LoadCharacterOk(::Session const *, ::Packet const *);  // 0x2fefa0
bool __cdecl HandleCacheGame_LoadCharacterFail(::Session const *, ::Packet const *);  // 0x2ff180
bool __cdecl HandleCacheGame_UnloadCharacterOk(::Session const *, ::Packet const *);  // 0x2ff2f0
bool __cdecl HandleCacheGame_UnloadCharacterFail(::Session const *, ::Packet const *);  // 0x2ff370
bool __cdecl HandleCacheGame_CreateCharacterOk(::Session const *, ::Packet const *);  // 0x2ff4e0
bool __cdecl HandleCacheGame_CreateCharacterFail(::Session const *, ::Packet const *);  // 0x2ff590
bool __cdecl HandleCacheGame_ChangeCharacterAppearanceOk(::Session const *, ::Packet const *);  // 0x2ff730
bool __cdecl HandleCacheGame_ChangeCharacterAppearanceFail(::Session const *, ::Packet const *);  // 0x2ffaf0
bool __cdecl HandleCacheGame_ChangeCharacterSexOk(::Session const *, ::Packet const *);  // 0x2ffcb0
bool __cdecl HandleCacheGame_ChangeCharacterSexFail(::Session const *, ::Packet const *);  // 0x300080
bool __cdecl HandleCacheGame_ChangeCharacterRaceOk(::Session const *, ::Packet const *);  // 0x300240
bool __cdecl HandleCacheGame_ChangeCharacterRaceFail(::Session const *, ::Packet const *);  // 0x300620
bool __cdecl HandleCacheGame_DeleteCharacterOk(::Session const *, ::Packet const *);  // 0x3007e0
bool __cdecl HandleCacheGame_DeleteCharacterFail(::Session const *, ::Packet const *);  // 0x300aa0
bool __cdecl HandleCacheGame_RestoreCharacterOk(::Session const *, ::Packet const *);  // 0x300c70
bool __cdecl HandleCacheGame_RestoreCharacterFail(::Session const *, ::Packet const *);  // 0x300d30
bool __cdecl HandleCacheGame_TradeItemOk(::Session const *, ::Packet const *);  // 0x300f30
bool __cdecl HandleCacheGame_TradeItemFail(::Session const *, ::Packet const *);  // 0x301020
bool __cdecl HandleCacheGame_RestorePawnOk(::Session const *, ::Packet const *);  // 0x301110
bool __cdecl HandleCacheGame_RestorePawnFail(::Session const *, ::Packet const *);  // 0x301270
bool __cdecl HandleCacheGame_RenameCharacterOk(::Session const *, ::Packet const *);  // 0x301420
bool __cdecl HandleCacheGame_PreLoadSeasonContentsCombatRecordOk(::Session const *, ::Packet const *);  // 0x301700
bool __cdecl HandleCacheGame_PreLoadSeasonContentsCombatRecordFail(::Session const *, ::Packet const *);  // 0x3018c0
bool __cdecl HandleCacheGame_InitializeCharacterOk(::Session const *, ::Packet const *);  // 0x301a70
bool __cdecl HandleCacheGame_InitializeCharacterFail(::Session const *, ::Packet const *);  // 0x301bf0
bool __cdecl HandleCacheGame_InitializeCharacterOnlySeasonContentsScheduleOk(::Session const *, ::Packet const *);  // 0x301db0
bool __cdecl HandleCacheGame_RenameCharacterFail(::Session const *, ::Packet const *);  // 0x301f00
bool __cdecl HandleCacheGame_RetrieveClosetItemInfoForTakingOk(::Session const *, ::Packet const *);  // 0x3020e0
bool __cdecl HandleCacheGame_RetrieveClosetItemInfoForTakingFail(::Session const *, ::Packet const *);  // 0x3027a0
bool __cdecl HandleCacheGame_PutItemIntoClosetOk(::Session const *, ::Packet const *);  // 0x302bf0
bool __cdecl HandleCacheGame_PutItemIntoClosetFail(::Session const *, ::Packet const *);  // 0x302d70
bool __cdecl HandleCacheGame_TakeItemFromClosetOk(::Session const *, ::Packet const *);  // 0x303180
bool __cdecl HandleCacheGame_TakeItemFromClosetFail(::Session const *, ::Packet const *);  // 0x3032f0
bool __cdecl HandleCacheGame_MakeMileageDepositOk(::Session const *, ::Packet const *);  // 0x303700
bool __cdecl HandleCacheGame_MakeMileageDepositFail(::Session const *, ::Packet const *);  // 0x303940
bool __cdecl HandleCacheGame_LoadCharacterMileageDepositRetryListOk(::Session const *, ::Packet const *);  // 0x303cc0
bool __cdecl HandleCacheGame_LoadCharacterMileageDepositRetryListFail(::Session const *, ::Packet const *);  // 0x304060
bool __cdecl HandleCacheGame_LoadMileageDepositRetryListOk(::Session const *, ::Packet const *);  // 0x304120
bool __cdecl HandleCacheGame_LoadMileageDepositRetryListFail(::Session const *, ::Packet const *);  // 0x3041c0
bool __cdecl HandleCacheGame_LoadRaidDungeonListOk(::Session const *, ::Packet const *);  // 0x3041f0
bool __cdecl HandleCacheGame_LoadRaidDungeonListFail(::Session const *, ::Packet const *);  // 0x3042c0
bool __cdecl HandleCacheGame_BindRaidDungeonOk(::Session const *, ::Packet const *);  // 0x304300
bool __cdecl HandleCacheGame_BindRaidDungeonFail(::Session const *, ::Packet const *);  // 0x304520
bool __cdecl HandleCacheGame_UpdateRaidDungeonOk(::Session const *, ::Packet const *);  // 0x304560
bool __cdecl HandleCacheGame_UpdateRaidDungeonFail(::Session const *, ::Packet const *);  // 0x3046b0
bool __cdecl HandleCacheGame_ChangeWeaponAppearanceOk(::Session const *, ::Packet const *);  // 0x3046f0
bool __cdecl HandleCacheGame_ChangeWeaponAppearanceFail(::Session const *, ::Packet const *);  // 0x3048e0
bool __cdecl HandleCacheGame_RecoverUncompletedWeaponAppearanceChangeOk(::Session const *, ::Packet const *);  // 0x304c60
bool __cdecl HandleCacheGame_RecoverUncompletedWeaponAppearanceChangeFail(::Session const *, ::Packet const *);  // 0x304de0
bool __cdecl HandleCacheGame_RetrieveSeasonContentsRankingRewardOk(::Session const *, ::Packet const *);  // 0x304f80
bool __cdecl HandleCacheGame_RetrieveSeasonContentsRankingRewardFail(::Session const *, ::Packet const *);  // 0x305160
bool __cdecl HandleCacheGame_TakeRankingRewardOk(::Session const *, ::Packet const *);  // 0x305290
bool __cdecl HandleCacheGame_TakeRankingRewardFail(::Session const *, ::Packet const *);  // 0x305aa0
bool __cdecl HandleCacheGame_RetryTakeRankingRewardOk(::Session const *, ::Packet const *);  // 0x306260
bool __cdecl HandleCacheGame_RetryTakeRankingRewardFail(::Session const *, ::Packet const *);  // 0x306420
bool __cdecl HandleCacheGame_UpdateSeasonContentsCombatRecordOk(::Session const *, ::Packet const *);  // 0x3065e0
bool __cdecl HandleCacheGame_UpdateSeasonContentsCombatRecordFail(::Session const *, ::Packet const *);  // 0x306a90
bool __cdecl HandleCacheGame_UpdateSeasonContentsTimeAttackRecordOk(::Session const *, ::Packet const *);  // 0x306ed0
bool __cdecl HandleCacheGame_UpdateSeasonContentsTimeAttackRecordFail(::Session const *, ::Packet const *);  // 0x307380
bool __cdecl HandleCacheGame_LoadSeasonContentsRankingLogListOk(::Session const *, ::Packet const *);  // 0x3077c0
bool __cdecl HandleCacheGame_LoadSeasonContentsRankingLogListFail(::Session const *, ::Packet const *);  // 0x307dd0
bool __cdecl HandleCacheGame_UpdateDuelBotTrainingRoomScoreOk(::Session const *, ::Packet const *);  // 0x308000
bool __cdecl HandleCacheGame_UpdateDuelBotTrainingRoomScoreFail(::Session const *, ::Packet const *);  // 0x308200
bool __cdecl HandleCacheGame_TakeDuelBotTrainingRoomRewardOk(::Session const *, ::Packet const *);  // 0x308410
bool __cdecl HandleCacheGame_TakeDuelBotTrainingRoomRewardFail(::Session const *, ::Packet const *);  // 0x308980
bool __cdecl HandleCacheGame_RetryTakeDuelBotTrainingRoomRewardOk(::Session const *, ::Packet const *);  // 0x308e40
bool __cdecl HandleCacheGame_RetryTakeDuelBotTrainingRoomRewardFail(::Session const *, ::Packet const *);  // 0x309000
bool __cdecl HandleCacheGame_RegisterCraftOk(::Session const *, ::Packet const *);  // 0x3091c0
bool __cdecl HandleCacheGame_RegisterCraftFail(::Session const *, ::Packet const *);  // 0x3099f0
bool __cdecl HandleCacheGame_TakeCraftOk(::Session const *, ::Packet const *);  // 0x309d20
bool __cdecl HandleCacheGame_TakeCraftFail(::Session const *, ::Packet const *);  // 0x30a460
bool __cdecl HandleCacheGame_JoinCraftUnionOk(::Session const *, ::Packet const *);  // 0x30aa80
bool __cdecl HandleCacheGame_JoinCraftUnionFail(::Session const *, ::Packet const *);  // 0x30adc0
bool __cdecl HandleCacheGame_LeaveCraftUnionOk(::Session const *, ::Packet const *);  // 0x30af50
bool __cdecl HandleCacheGame_LeaveCraftUnionFail(::Session const *, ::Packet const *);  // 0x30b290
bool __cdecl HandleCacheGame_AbortCraftOk(::Session const *, ::Packet const *);  // 0x30b420
bool __cdecl HandleCacheGame_AbortCraftFail(::Session const *, ::Packet const *);  // 0x30b570
bool __cdecl HandleCacheGame_RecoverUncompletedCraftOk(::Session const *, ::Packet const *);  // 0x30b6f0
bool __cdecl HandleCacheGame_RecoverUncompletedCraftFail(::Session const *, ::Packet const *);  // 0x30b8b0
bool __cdecl HandleCacheGame_TencentLoadGuildMemberListOk(::Session const *, ::Packet const *);  // 0x30ba70
bool __cdecl HandleCacheGame_TencentLoadGuildMemberListFail(::Session const *, ::Packet const *);  // 0x30c0c0
bool __cdecl HandleCacheGame_TencentLoadQQGroupMemberListOk(::Session const *, ::Packet const *);  // 0x30c300
bool __cdecl HandleCacheGame_TencentLoadQQGroupMemberListFail(::Session const *, ::Packet const *);  // 0x30c820
bool __cdecl HandleCacheGame_TencentRetrieveCharacterQQIDOk(::Session const *, ::Packet const *);  // 0x30ca10
bool __cdecl HandleCacheGame_TencentRetrieveCharacterQQIDFail(::Session const *, ::Packet const *);  // 0x30cc20
bool __cdecl HandleCacheGame_TencentBindingQQGroupOk(::Session const *, ::Packet const *);  // 0x30cd90
bool __cdecl HandleCacheGame_TencentBindingQQGroupFail(::Session const *, ::Packet const *);  // 0x30d1d0
bool __cdecl HandleCacheGame_TencentUnbindingQQGroupOk(::Session const *, ::Packet const *);  // 0x30d390
bool __cdecl HandleCacheGame_TencentUnbindingQQGroupFail(::Session const *, ::Packet const *);  // 0x30d740
bool __cdecl HandleCacheGame_TencentCreateGuildOk(::Session const *, ::Packet const *);  // 0x30d870
bool __cdecl HandleCacheGame_TencentCreateGuildFail(::Session const *, ::Packet const *);  // 0x30dc90
bool __cdecl HandleCacheGame_TencentJoinGuildOk(::Session const *, ::Packet const *);  // 0x30e060
bool __cdecl HandleCacheGame_TencentJoinGuildFail(::Session const *, ::Packet const *);  // 0x30e650
bool __cdecl HandleCacheGame_TencentChangeQQGroupMemberBindingStatusOk(::Session const *, ::Packet const *);  // 0x30ea90
bool __cdecl HandleCacheGame_TencentChangeQQGroupMemberBindingStatusFail(::Session const *, ::Packet const *);  // 0x30ed30
bool __cdecl HandleCacheGame_TakeAchievementRewardOk(::Session const *, ::Packet const *);  // 0x30ee00
bool __cdecl HandleCacheGame_TakeAchievementRewardFail(::Session const *, ::Packet const *);  // 0x30f2b0
bool __cdecl HandleCacheGame_FinishTakeAchievementRewardOk(::Session const *, ::Packet const *);  // 0x30f750
bool __cdecl HandleCacheGame_FinishTakeAchievementRewardFail(::Session const *, ::Packet const *);  // 0x30f880
bool __cdecl HandleCacheGame_RetryTakeAchievementRewardOk(::Session const *, ::Packet const *);  // 0x30f9c0
bool __cdecl HandleCacheGame_RetryTakeAchievementRewardFail(::Session const *, ::Packet const *);  // 0x30fb80
void __cdecl checkNextChallengePartyMemberList(::Session const *);  // 0x30fd40
bool __cdecl HandleCacheGame_LoadChallengePartyListOk(::Session const *, ::Packet const *);  // 0x30ff70
bool __cdecl HandleCacheGame_LoadChallengePartyListFail(::Session const *, ::Packet const *);  // 0x310310
bool __cdecl HandleCacheGame_LoadChallengePartyMemberListOk(::Session const *, ::Packet const *);  // 0x310440
bool __cdecl HandleCacheGame_LoadChallengePartyMemberListFail(::Session const *, ::Packet const *);  // 0x310960
bool __cdecl HandleCacheGame_CreateChallengePartyOk(::Session const *, ::Packet const *);  // 0x310ac0
bool __cdecl HandleCacheGame_CreateChallengePartyFail(::Session const *, ::Packet const *);  // 0x310ca0
bool __cdecl HandleCacheGame_JoinChallengePartyOk(::Session const *, ::Packet const *);  // 0x310e90
bool __cdecl HandleCacheGame_JoinChallengePartyFail(::Session const *, ::Packet const *);  // 0x3110c0
bool __cdecl HandleCacheGame_ChangeChallengePartyLeaderOk(::Session const *, ::Packet const *);  // 0x3112b0
bool __cdecl HandleCacheGame_ChangeChallengePartyLeaderFail(::Session const *, ::Packet const *);  // 0x311490
bool __cdecl HandleCacheGame_LeaveChallengePartyOk(::Session const *, ::Packet const *);  // 0x311680
bool __cdecl HandleCacheGame_LeaveChallengePartyFail(::Session const *, ::Packet const *);  // 0x311900
bool __cdecl HandleCacheGame_InitializeMentoringOk(::Session const *, ::Packet const *);  // 0x311b10
bool __cdecl HandleCacheGame_InitializeMentoringFail(::Session const *, ::Packet const *);  // 0x311c10
bool __cdecl HandleCacheGame_LoadMentoringListOk(::Session const *, ::Packet const *);  // 0x311c50
bool __cdecl HandleCacheGame_LoadMentoringListFail(::Session const *, ::Packet const *);  // 0x312020
bool __cdecl HandleCacheGame_JoinMentoringOk(::Session const *, ::Packet const *);  // 0x312150
bool __cdecl HandleCacheGame_JoinMentoringFail(::Session const *, ::Packet const *);  // 0x312350
bool __cdecl HandleCacheGame_LeaveMentoringOk(::Session const *, ::Packet const *);  // 0x312580
bool __cdecl HandleCacheGame_LeaveMentoringFail(::Session const *, ::Packet const *);  // 0x312770
bool __cdecl HandleCacheGame_CompleteClosetCollectingOk(::Session const *, ::Packet const *);  // 0x312980
bool __cdecl HandleCacheGame_CompleteClosetCollectingFail(::Session const *, ::Packet const *);  // 0x313150
bool __cdecl HandleCacheGame_UpdateClosetUsedOk(::Session const *, ::Packet const *);  // 0x313760
bool __cdecl HandleCacheGame_UpdateClosetUsedFail(::Session const *, ::Packet const *);  // 0x313e00
bool __cdecl HandleCacheGame_TryBoardGachaPaymentOk(::Session const *, ::Packet const *);  // 0x3144c0
bool __cdecl HandleCacheGame_TryBoardGachaPaymentFail(::Session const *, ::Packet const *);  // 0x3145f0
bool __cdecl HandleCacheGame_PurePropertyTransactionOk(::Session const *, ::Packet const *);  // 0x314b00
bool __cdecl HandleCacheGame_PurePropertyTransactionFail(::Session const *, ::Packet const *);  // 0x314b70
