// pc.h: pc.cpp, pc.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"
#include "transactionexpirechecker.h"

class CraftInfo
{
public:
    __cdecl CraftInfo(void);  // 0x5d4bf0
    virtual __cdecl ~CraftInfo(void);  // 0x5d4cc0
    bool __cdecl TryToRegister(int, unsigned __int64, char, ::CraftOutput *, char, ::SyncContext *);  // 0x5d4d30
    bool __cdecl TryToTake(::SyncContext &);  // 0x5d4e00
    void __cdecl CancelToTake(void);  // 0x5d4f80
};

class Pc : private ::LiftBytes<0x4e30 - 8>  // LIFT: PDB bases and members +8 to +0x4E2F are not declared yet
{
public:
    enum AccountExpReason {};
    enum ArenaSession {};
    enum CombatModeType {};
    enum ExpReason {};
    enum ExpireReason {};
    enum FriendNotiLocationType {};
    struct SeasonContentsRewardsOfGuild {};
    enum SkillScoreRateReason {};
    enum UpdateReturnPosType {};
    enum ZSOType {};
public:
    void __cdecl GetGuildCombatRewardDataId(char, ::Pc::SeasonContentsRewardsOfGuild &);  // 0x97130
    virtual short __cdecl GetAttackHitValueModify(void);  // 0x4554d0
    virtual short __cdecl GetAttackCriticalValueModify(void);  // 0x455550
    virtual short __cdecl GetDefendCriticalValueModify(void);  // 0x4555d0
    virtual short __cdecl GetDefendDodgeValueModify(void);  // 0x455650
    virtual short __cdecl GetDefendParryValueModify(void);  // 0x4556d0
    virtual short __cdecl GetDefendPhysicalValueModify(void);  // 0x455750
    virtual short __cdecl GetDefendForceValueModify(void);  // 0x4557d0
    virtual short __cdecl GetAttackStiffDurationValueModify(void);  // 0x455850
    virtual short __cdecl GetDefendStiffDurationValueModify(void);  // 0x4558d0
    virtual short __cdecl GetCastDurationValueModify(void);  // 0x455950
    virtual short __cdecl GetAttackCriticalDamageModify(void);  // 0x4559d0
    virtual short __cdecl GetDefendCriticalDamageModify(void);  // 0x455a50
    virtual short __cdecl GetAttackPierceModify(void);  // 0x455ad0
    virtual short __cdecl GetAttackParryPierceModify(void);  // 0x455b50
    virtual short __cdecl GetDefendParryReduceModify(void);  // 0x455bd0
    virtual short __cdecl GetAttackPerfectParryDamageModify(void);  // 0x455c50
    virtual short __cdecl GetDefendPerfectParryReduceModify(void);  // 0x455cd0
    virtual short __cdecl GetAttackCounterDamageModify(void);  // 0x455d50
    virtual short __cdecl GetDefendCounterReduceModify(void);  // 0x455dd0
    virtual short __cdecl GetHealPowerModify(void);  // 0x455e50
    virtual short __cdecl GetAOEDefendPowerModify(void);  // 0x455ed0
    virtual short __cdecl GetAbnormalAttackPowerModify(void);  // 0x455f50
    virtual short __cdecl GetAbnormalDefendPowerModify(void);  // 0x455fd0
    virtual short __cdecl GetHatePowerModify(void);  // 0x456050
    virtual short __cdecl GetAttackAttributeModify(void);  // 0x4560d0
    virtual short __cdecl GetRAttackAoePierceModify(void);  // 0x456150
    virtual short __cdecl GetRAttackAbnormalHitModify(void);  // 0x4561d0
    virtual short __cdecl GetRDefendAbnormalDodgeModify(void);  // 0x456250
    virtual short __cdecl GetRSupportPowerModify(void);  // 0x4562d0
    virtual short __cdecl GetRHypermovePowerModify(void);  // 0x456350
    virtual bool __cdecl IsExceptHate(void);  // 0x4563d0
    virtual void __cdecl SetExceptHate(bool);  // 0x4563e0
    virtual void __cdecl ClearLastComboSkillValue(void);  // 0x4563f0
    virtual unsigned int __cdecl GetLastComboSkill(void) const;  // 0x456420
    virtual void __cdecl SetLastComboSkill(unsigned int);  // 0x456430
    virtual __int64 __cdecl GetLastComboFireLimitTime(void) const;  // 0x456440
    virtual void __cdecl SetLastComboFireLimitTime(__int64);  // 0x456450
    virtual __int64 __cdecl GetLastComboExecFirstLimitTime(void) const;  // 0x456460
    virtual void __cdecl SetLastComboExecFirstLimitTime(__int64);  // 0x456470
    virtual __int64 __cdecl GetLastComboExecLastLimitTime(void) const;  // 0x456480
    virtual void __cdecl SetLastComboExecLastLimitTime(__int64);  // 0x456490
    virtual ::SkillResult __cdecl GetLastComboExecFirstResult(void) const;  // 0x4564a0
    virtual void __cdecl SetLastComboExecFirstResult(::SkillResult);  // 0x4564b0
    virtual ::SkillResult __cdecl GetLastComboExecLastResult(void) const;  // 0x4564c0
    virtual void __cdecl SetLastComboExecLastResult(::SkillResult);  // 0x4564d0
    virtual __int64 __cdecl GetLastAttackLimitTime(::SkillResult) const;  // 0x4564e0
    virtual void __cdecl SetLastAttackLimitTime(::SkillResult, __int64);  // 0x4564f0
    virtual __int64 __cdecl GetLastAttackedLimitTime(::SkillResult) const;  // 0x456500
    virtual void __cdecl SetLastAttackedLimitTime(::SkillResult, __int64);  // 0x456510
    virtual ::SkillResultContext & __cdecl GetSkillResultContext(void);  // 0x456520
    static ::GameLogExpReasonCode __cdecl GetGameLogExpReasonCode(::Pc::ExpReason);  // 0x5d5de0
    __cdecl Pc(void);  // 0x5d5ea0
    virtual __cdecl ~Pc(void);  // 0x5d6b60
    bool __cdecl IsTryingInstantPayment(void);  // 0x5d7180
private:
    void __cdecl clearRankingRewardList(void);  // 0x5d71c0
public:
    bool __cdecl AddRankingRewardList(char, int, char, short, int, __int64, __int64);  // 0x5d7310
    bool __cdecl FetchRankingRewardListToCache(::RepeatPacketComposer *, ::Packet *);  // 0x5d7690
    bool __cdecl UpdateRankingRewardList(::RepeatPacketDecomposer *, ::Packet const *);  // 0x5d7930
    bool __cdecl GetRankingRewardInfo(char, int, char, ::RankingRewardInfo &);  // 0x5d7d70
    short __cdecl TakeRankingRewardOkFromCache(char, int, char);  // 0x5d7e80
    bool __cdecl SendRetrieveRankingRewardListOk(void);  // 0x5d7f30
    void __cdecl SendRetrieveRankingRewardListFail(short);  // 0x5d8320
    void __cdecl SendRetrieveGuildRankingInfoFail(short);  // 0x5d8390
    void __cdecl SendRetrieveChallengePartyRankingInfoFail(short);  // 0x5d8400
    void __cdecl SendTakeRankingRewardFail(short);  // 0x5d8490
    void __cdecl SendRegisterCraftFail(int, short);  // 0x5d8500
    void __cdecl SendTakeCraftFail(unsigned __int64, short);  // 0x5d8590
    void __cdecl SendAbortCraftFail(unsigned __int64, short);  // 0x5d8620
    void __cdecl SendJoinCraftUnionFail(char, short);  // 0x5d86a0
    void __cdecl SendLeaveCraftUnionFail(char, short);  // 0x5d8730
    void __cdecl InitailizeJoinedGuildInfo(unsigned __int64);  // 0x5d87c0
private:
    bool __cdecl updateRankingRewardInfo(unsigned __int64, __int64);  // 0x5d8bc0
public:
    bool __cdecl Initialize(unsigned __int64, char);  // 0x5d8cc0
    virtual void __cdecl EnterZone(::EnterReason, bool, unsigned int);  // 0x5d8ef0
    virtual void __cdecl LeaveZone(::LeaveReason);  // 0x5da450
    void __cdecl WriteGameLogFactionScoreDisappear(int, int, int);  // 0x5dafc0
    bool __cdecl IsInTeamPartyZone(void);  // 0x5db450
    bool __cdecl IsInPartyBattleFieldZone(void);  // 0x5db4a0
    bool __cdecl IsInPartyZone(void);  // 0x5db4e0
    virtual bool __cdecl SetDead(bool, ::ChangedProperty *, unsigned __int64, unsigned __int64, unsigned __int64, bool, bool);  // 0x5db520
    bool __cdecl SetAllDbData(unsigned __int64, ::FragmentPacketConcatenater *, ::std::vector< ::Item *, ::StlAllocator< ::Item *, 2> > &);  // 0x5de2f0
    int __cdecl SetExtraDbData(unsigned __int64, char const *, int);  // 0x5debc0
    int __cdecl SetDbEffectData(short, char const *, int);  // 0x5dec60
    bool __cdecl SetDbSeasonContentsCombatRecordData(::FragmentPacketConcatenater *);  // 0x5ded20
    bool __cdecl SetDbSeasonContentsTimeAttackRecordData(::FragmentPacketConcatenater *);  // 0x5def40
    bool __cdecl SetDbDuelBotTrainingRoomScoreData(::FragmentPacketConcatenater *);  // 0x5df130
    bool __cdecl SetDbCompletedAchievementRewardData(::FragmentPacketConcatenater *);  // 0x5df350
    bool __cdecl SetDbJoinCraftUnionData(::FragmentPacketConcatenater *);  // 0x5df500
    bool __cdecl SetDbCraftData(::FragmentPacketConcatenater *);  // 0x5df630
    bool __cdecl LoadData(void);  // 0x5dfc40
    bool __cdecl ApplyAbility(::ChangedProperty *const, char, char);  // 0x5dfd20
    bool __cdecl RemasterApplyAbility(::ChangedProperty *const, char, char);  // 0x5e01e0
    bool __cdecl ReturnToRespawn(bool);  // 0x5e07f0
    bool __cdecl LevelUp(::ChangedProperty *, int, int, int, int, short);  // 0x5e0bb0
    bool __cdecl OpenMasteryLevel(::ChangedProperty *const);  // 0x5e14d0
    static ::Data::PcContentsTypeType __cdecl GetPcContentsType(::Pc *);  // 0x5e1650
    static void __cdecl FullRecovery(::Pc *);  // 0x5e16c0
    bool __cdecl HandleJobStyle(::ChangedProperty *);  // 0x5e1a00
    virtual bool __cdecl HandleStance(char, unsigned __int64 const *, int, ::ChangedProperty *);  // 0x5e1ad0
    void __cdecl RefreshSkillList(void);  // 0x5e1bc0
    bool __cdecl AcquireSkillFromLevel(char, bool);  // 0x5e1d70
    bool __cdecl InvokeMasteryStatBonusAbility(void);  // 0x5e1fa0
    ::Data::ItemRecordCostumePtr const __cdecl GetCostume(void) const;  // 0x5e2030
    bool __cdecl CheckUsableWeapon(void) const;  // 0x5e20e0
    bool __cdecl CheckToEquipMainFactionItem(void) const;  // 0x5e21b0
    bool __cdecl CheckResurrectPosition(void) const;  // 0x5e22e0
    bool __cdecl CheckSkillSkinCondition(short) const;  // 0x5e2430
    void __cdecl ResetUnacquiredSkillSkin(bool);  // 0x5e27f0
    ::GameFailReason __cdecl CheckUsableGrocery(::Data::ItemRecordGroceryPtr);  // 0x5e28f0
    virtual void __cdecl SetCombatModeByAttack(bool, ::SourceLocation const &);  // 0x5e2ba0
    virtual void __cdecl SetCombatModeByAttacked(::SourceLocation const &);  // 0x5e2cd0
    virtual void __cdecl SetCombatModeByTargeted(::SourceLocation const &);  // 0x5e2dc0
    virtual void __cdecl SetCombatModeByLink(::SourceLocation const &);  // 0x5e2dd0
    virtual void __cdecl ResetCombatModeByLink(::SourceLocation const &);  // 0x5e2e50
    virtual void __cdecl ResetCombatModeByTargeted(::SourceLocation const &);  // 0x5e2ef0
    void __cdecl ResetCombatModeByKill(::SourceLocation const &);  // 0x5e2fa0
    void __cdecl StartRestoration(void);  // 0x5e3030
    __int64 __cdecl GetGradeBenefitValue(int);  // 0x5e30b0
    __int64 const __cdecl GetGradeBenefitRandomStoreProbGroup(int, char) const;  // 0x5e3190
    unsigned __int64 const * __cdecl GetGradeBenefitAchievementRef(int, char &) const;  // 0x5e3280
    virtual void __cdecl ResetCombatMode(bool, ::SourceLocation const &);  // 0x5e3360
    bool __cdecl SetCombatSide(char, ::ChangedProperty *const);  // 0x5e3610
    void __cdecl InvokeReviveExceptionRuleEffect(void);  // 0x5e3750
    void __cdecl InvokeRevivalEffect(void);  // 0x5e3820
private:
    void __cdecl setCombatMode(::Pc::CombatModeType, long, ::SourceLocation const &);  // 0x5e3930
public:
    bool __cdecl banishFromInstantPartyZone(void);  // 0x5e3a00
    bool __cdecl CheckPcCafe(void);  // 0x5e3b80
    bool __cdecl UseHeartCount(unsigned __int64, unsigned int);  // 0x5e3c00
    bool __cdecl CheckEnableHeartCount(void);  // 0x5e40a0
private:
    char __cdecl getPcCafePublisherCode(void);  // 0x5e41d0
    unsigned __int64 __cdecl getPcCafeEffect(void);  // 0x5e42e0
public:
    int __cdecl GetPcCafePointBonusPercent(int);  // 0x5e43e0
    int __cdecl GetPcCafeExpBonusPercent(int);  // 0x5e4510
private:
    int __cdecl getPcCafeNpcLootingMoneyRewardPercent(void);  // 0x5e4630
public:
    bool __cdecl UsablePcCafeUnlocatedWareHouse(void);  // 0x5e46d0
    bool __cdecl UsablePcCafeQuestReward(void);  // 0x5e4770
    ::Data::PcCafeBenefitsRecordPtr const __cdecl GetPcCafeBenefitsData(void);  // 0x5e4810
    bool __cdecl SetPcCafeDebugCode(wchar_t *, char);  // 0x5e4880
private:
    bool __cdecl invokePcCafeEffect(void);  // 0x5e4960
public:
    int __cdecl CalcNpcLootingMoney(__int64, int, bool);  // 0x5e4a10
    bool __cdecl AcquireFactionScore(int);  // 0x5e4c40
    char __cdecl GetActivatedMainFactionId(void);  // 0x5e4d40
    void __cdecl ClearFactionKilledCount(void);  // 0x5e4dd0
    void __cdecl RestoreActivatedFaction(void);  // 0x5e4e50
    void __cdecl AcquireStyleScore(short, short, long);  // 0x5e5030
    void __cdecl ClearStyleScore(void);  // 0x5e5130
    __int64 __cdecl CalculateStyleScoreBonus(__int64);  // 0x5e51b0
    void __cdecl SendSkillScoreNotify(void);  // 0x5e5220
    void __cdecl ActivateSkillScore(__int64);  // 0x5e5380
    void __cdecl DeactivateSkillScore(void);  // 0x5e5510
    void __cdecl AcquireSkillScore(int);  // 0x5e5560
    void __cdecl AcquireSkillScoreRate(::Pc::SkillScoreRateReason, int);  // 0x5e56d0
    void __cdecl IncreaseSkillScoreCombo(bool);  // 0x5e57c0
    void __cdecl FinishedSkillScoreCombo(void);  // 0x5e5890
    void __cdecl CalculateSkillScore(void);  // 0x5e5ad0
    void __cdecl ModifyEquipBadgeGearScore(int);  // 0x5e6360
    __int64 __cdecl CalculateGuildRankingRewardCombatExp(char, __int64);  // 0x5e63d0
    bool __cdecl GetNearRespawnArea(::vector16, unsigned int &, unsigned __int64 &);  // 0x5e6540
    bool __cdecl IsSharableCombatModeZone(void) const;  // 0x5e6a90
private:
    bool __cdecl findZoneTeamMemberRemain(unsigned int, int &);  // 0x5e6ac0
    bool __cdecl findZonePartyMemberRemain(unsigned int, int &);  // 0x5e6c20
public:
    short __cdecl SelectTransitZone(short, ::LeaveReason, unsigned __int64, unsigned __int64 *, unsigned __int64 *, unsigned __int64 *, unsigned __int64 *, short *, unsigned __int64 *, unsigned int *, unsigned __int64 *, unsigned __int64 *, unsigned __int64 *, unsigned __int64 *, short *, bool, bool, char);  // 0x5e6cf0
    bool __cdecl TranslateZoneOnEnterWorld(unsigned __int64 *, unsigned int *, ::vector16 *, short *);  // 0x5e7e50
    ::GameFailReason __cdecl selectTransitZoneForDungeon(::GeoZone const *, int, bool &, int &);  // 0x5e81b0
    void __cdecl CheckConditionAfterSpawn(void);  // 0x5e88f0
    virtual void __cdecl OnTimer(::Zone *, unsigned short);  // 0x5e8ef0
    virtual void __cdecl OnAttacked(::Zone *, ::GameObject *, unsigned __int64, short);  // 0x5e9190
    void __cdecl OnKilled(::Zone *, ::GameObject *, unsigned __int64);  // 0x5e91e0
    void __cdecl OnKill(::Zone *, ::Pc *, unsigned __int64, char, char);  // 0x5e93e0
    void __cdecl ProcessFactionByKill(::Pc *, unsigned __int64, char, char);  // 0x5e95c0
private:
    void __cdecl cancelTrade(char, wchar_t const *);  // 0x5e9800
public:
    void __cdecl ClearStateOnDead(void);  // 0x5e98b0
    void __cdecl SetFieldItem(::FieldItem *);  // 0x5e9a70
    void __cdecl ClearFieldItem(void);  // 0x5e9bf0
    void __cdecl ClearFieldItemProperty(void);  // 0x5e9c50
    ::GameFailReason const __cdecl CheckMakeSummoned(__int64);  // 0x5e9cc0
    void __cdecl MakeSummoned(__int64, wchar_t const *const);  // 0x5e9e00
    ::Summoned * __cdecl GetActiveSummoned(void);  // 0x5ea0d0
    void __cdecl SetActiveSummoned(::Summoned *);  // 0x5ea0f0
    ::Data::MasteryAbilityRecordPtr const __cdecl GetMasteryAbilityData(char) const;  // 0x5ea2d0
    void __cdecl LeaveWorld(void);  // 0x5ea390
    void __cdecl WriteGameLogLeaveWorld(char, char);  // 0x5ea760
private:
    void __cdecl enterArenaLobby(void);  // 0x5eace0
public:
    void __cdecl ResetSpecialSkillGauge(void);  // 0x5ead90
    int __cdecl GetCurrentSpecialSkillGauge(void);  // 0x5eaf10
    bool __cdecl IsSpecialSkillGaugeFull(void);  // 0x5eaff0
protected:
    void __cdecl SetUser(::User const *);  // 0x5eb050
public:
    void __cdecl SendGameBuilderAuth(void);  // 0x5eb130
    void __cdecl Send(char const *, char *);  // 0x5eb2e0
    virtual void __cdecl Send(char const *, ...);  // 0x5eb350
    virtual void __cdecl Send(::Packet const *);  // 0x5eb3c0
    virtual void __cdecl Send(::PacketList const *);  // 0x5eb420
    virtual void __cdecl SendChangedPrivateProperty(void);  // 0x5eb4a0
    virtual void __cdecl SendActionPrivatePacket(void);  // 0x5eb4f0
    void __cdecl SendEnterWorldOk(void);  // 0x5eb540
private:
    void __cdecl writeGameLogEnterWorld(char, char);  // 0x5ec3e0
public:
    void __cdecl SendSummonedEnterWorldOk(void);  // 0x5ec8a0
    void __cdecl ChangeEnterArenaParam(unsigned __int64, __int64, unsigned __int64, __int64);  // 0x5ecb90
    void __cdecl SendEnterArenaOk(void);  // 0x5ecce0
    bool __cdecl ReturningToArenaLobby(void);  // 0x5ed820
    void __cdecl RollbackReturnToArenaLobby(void);  // 0x5ed880
    void __cdecl SendUpdateDodgeInfo(void);  // 0x5ed8c0
    void __cdecl SetArenaRoom(::ArenaRoom *, __int64);  // 0x5ed9c0
    void __cdecl SetGameGameMode(char);  // 0x5edae0
    char const __cdecl GetGameGameMode(void) const;  // 0x5edb30
    bool __cdecl SendReturnToGameOk(char);  // 0x5edb70
    char __cdecl GetArenaAttraction(void) const;  // 0x5ee6b0
    void __cdecl SendCurrentUTCTimeOk(void);  // 0x5ee6f0
    void __cdecl SendChatMessage(char, wchar_t const *, int, wchar_t const *, wchar_t const *);  // 0x5ee830
    void __cdecl SendChatMessageByItem(wchar_t const *, char, short);  // 0x5ef4b0
    void __cdecl SendChatMessageByDice(short, short);  // 0x5ef760
    void __cdecl SendPcDbIdOk(void);  // 0x5ef9a0
    void __cdecl SendQuestCompleteListOk(void);  // 0x5efb50
    void __cdecl SendMentoringPropertySync(void);  // 0x5efd00
    void __cdecl SendActivatedTeleportListOk(void);  // 0x5efec0
    virtual void __cdecl ChangeTeamPartyProperty(unsigned short);  // 0x5f0070
    bool __cdecl FetchTeamPartyProperty(::Packet *, ::Packet *, ::Packet *, ::Packet *);  // 0x5f00d0
    void __cdecl BroadcastTeamPartyProperty(void);  // 0x5f04e0
    int __cdecl GetTeamMembers(unsigned __int64 *const);  // 0x5f0970
    unsigned short __cdecl FetchPartyProperty(char *, unsigned short);  // 0x5f0a90
    unsigned short __cdecl FetchTeamProperty(char *, unsigned short);  // 0x5f0bd0
    ::Pointer2< ::User> __cdecl GetUserPtr(void);  // 0x5f0d10
    __int64 __cdecl GetSessionId(void);  // 0x5f0d70
    void __cdecl GetGameAccountId(int, wchar_t *const);  // 0x5f0df0
    void __cdecl SetIpAddress(unsigned long);  // 0x5f0f00
    wchar_t const * __cdecl GetUserExternalAccountKeyString(void);  // 0x5f0f90
    unsigned int __cdecl GetUserGamePlayRestrictLevel(void);  // 0x5f0fe0
    int __cdecl GetUserGamePlayRestrictLevelRatio(void);  // 0x5f1030
    void __cdecl UpdatePartyDifficultyType(bool, unsigned __int64, unsigned __int64, char);  // 0x5f1080
    int __cdecl GetPartyMembers(unsigned __int64 *const);  // 0x5f1110
    void __cdecl SetTeamInfo(unsigned __int64, unsigned __int64, char, ::Team *);  // 0x5f1250
    void __cdecl ClearTeamInfo(::LeavePartyReason, bool, ::TeamPartyProxy *);  // 0x5f12d0
    bool __cdecl AssignChasePosition(::vector16 const &, int, int *);  // 0x5f1460
    bool __cdecl ChaseTicketToPos(int, int, ::vector16 *);  // 0x5f1610
    void __cdecl ClearChasePosition(int);  // 0x5f17f0
private:
    bool __cdecl takeFactionScore(::Pc *);  // 0x5f18b0
public:
    int __cdecl DistributeFactionScoreToPc(int, unsigned __int64, char);  // 0x5f1a20
    void __cdecl DistributeFactionScore(int, ::Creature *);  // 0x5f2680
    ::GameFailReason __cdecl TalkStart(::Npc *);  // 0x5f4160
    bool __cdecl TalkStop(::Npc *);  // 0x5f42a0
    bool __cdecl TalkInterrupted(::Npc *, bool, wchar_t const *);  // 0x5f4320
    bool __cdecl AddConvoy(::Convoy *);  // 0x5f43d0
    void __cdecl RemoveConvoy(void);  // 0x5f44a0
    int __cdecl SetDbClientOptionData(short, char const *, int);  // 0x5f4530
    short __cdecl FetchDiscoveryArea(char *, short);  // 0x5f46a0
    short __cdecl FetchActivatedTeleport(char *, short);  // 0x5f4730
    short __cdecl FetchSkillSkinAcquired(char *, short);  // 0x5f47c0
    short __cdecl FetchMentoringProperty(char *, short);  // 0x5f4850
    bool __cdecl CheckActivatedTeleport(short);  // 0x5f48e0
    bool __cdecl CheckSkillSkinProperty(short);  // 0x5f49f0
    bool __cdecl SetDiscoveryAreaBit(short);  // 0x5f4b30
    bool __cdecl SetActivatedTeleportBit(short, unsigned char, bool);  // 0x5f4cd0
    void __cdecl SetActivatedTeleport(unsigned char);  // 0x5f4ec0
    bool __cdecl SetSkillSkinAcquiredBit(short, bool);  // 0x5f5250
    bool __cdecl SetMentoringType(char, short);  // 0x5f5440
    bool __cdecl IncreaseMentoringFinishCount(::Pc *);  // 0x5f56e0
    bool __cdecl SetMentoringFinishCount(char);  // 0x5f5ac0
    int __cdecl GetPartyMembersForDistribute(::Pc **, ::vector16 const &, int, bool, bool);  // 0x5f5b90
    void __cdecl ReleaseMembersForDistribute(::Pc **, int);  // 0x5f5dc0
    int __cdecl GetTeamMembersForDistribute(::Pc **, ::vector16 const &, int, bool);  // 0x5f5ee0
    bool __cdecl UpdateLogoutTime(void);  // 0x5f60a0
    virtual void __cdecl StartCombat(void);  // 0x5f60e0
    virtual void __cdecl FinishCombat(void);  // 0x5f6620
    void __cdecl ChangeGradeExpirationTimeForDebug(int, __int64);  // 0x5f6ba0
    bool __cdecl AddAndActivateGrade(::GradeInfo &);  // 0x5f6c80
    bool __cdecl DeleteGrade(int);  // 0x5f6e80
    void __cdecl ActivateAllGradeBenefits(void);  // 0x5f7000
    void __cdecl ActivateGradeBenefit(int);  // 0x5f70b0
    void __cdecl ActivateGradeEffectBenefits(void);  // 0x5f7390
    void __cdecl DeactivateAllGradeBenefits(bool);  // 0x5f7580
    void __cdecl DeactivateGradeBenefit(int, bool &);  // 0x5f7610
private:
    void __cdecl onGradeTimerExpired(void);  // 0x5f7860
public:
    bool __cdecl IsAvailableGradeAchievement(short, short);  // 0x5f7a90
    bool __cdecl IsAllowedContent(char);  // 0x5f7b90
private:
    bool __cdecl isActivatedGrade(int) const;  // 0x5f7d50
    void __cdecl invokeGradeEffect(int);  // 0x5f7d90
    void __cdecl deactivateGradeVitalityBonus(void);  // 0x5f7f00
    void __cdecl checkAndDeactivateGradeAchievementBenefit(void);  // 0x5f8180
public:
    void __cdecl IncreaseContribution(unsigned __int64, __int64, char, __int64);  // 0x5f8350
private:
    void __cdecl insertContribution(unsigned __int64, __int64, char, __int64);  // 0x5f8400
public:
    __int64 __cdecl GetRewardContribution(unsigned __int64, __int64);  // 0x5f8590
    __int64 __cdecl RegisterContributionPouch(::NpcDeadBody &, __int64, __int64, __int64);  // 0x5f85e0
private:
    void __cdecl insertContributionPouch(::NpcDeadBody &, __int64, __int64);  // 0x5f8800
public:
    ::GameFailReason __cdecl TakeContributionReward(::NpcDeadBody &);  // 0x5f8bc0
    int __cdecl TakeContributionFactionScore(::NpcDeadBody &, int, __int64);  // 0x5f8e60
    bool __cdecl SetExceptLootCaseBitMap(unsigned __int64, int, char);  // 0x5f8f50
private:
    void __cdecl sendContributionPouchList(unsigned __int64);  // 0x5f8fb0
public:
    void __cdecl ResetAllGroupContribution(void);  // 0x5f9220
    void __cdecl ResetContribution(char, __int64);  // 0x5f9360
    void __cdecl SetMaxLevel(void);  // 0x5f95b0
    bool __cdecl CheckRechargeVitality(void);  // 0x5f9860
    bool __cdecl RechargeVitality(::ChangedProperty *);  // 0x5f99a0
    void __cdecl CutOffVitality(::ChangedProperty *);  // 0x5f9e00
    void __cdecl SendEnterPortalFail(::GameFailReason);  // 0x5fa120
    bool __cdecl AvailableTurnBack(void);  // 0x5fa2a0
private:
    bool __cdecl executeZSO(::Zone *);  // 0x5fa360
    void __cdecl destroyZSO(::Pc::ExpireReason, wchar_t const *);  // 0x5fa5b0
    bool __cdecl postZSO(::ZoneSerializedObject *, ::Pc::ZSOType, bool);  // 0x5fa710
public:
    bool __cdecl HandleChallengePartyId(__int64, ::ChangedProperty *);  // 0x5fa8b0
    bool __cdecl HandleChallengePartyOutTime(__int64, ::ChangedProperty *);  // 0x5fa9b0
    __int64 __cdecl GetGuildRegistrationTime(void);  // 0x5faab0
    void __cdecl UpdateGeoZoneToGuild(::EnterReason);  // 0x5fab60
    bool __cdecl PostSetGuildIdTask(unsigned __int64, wchar_t const *);  // 0x5faca0
    bool __cdecl PostCompleteChallengeList(unsigned __int64, char, char, char, char, wchar_t const *);  // 0x5fb150
    void __cdecl SendGetGradeListFailToArena(short);  // 0x5fb1f0
    void __cdecl SendGradeList(void);  // 0x5fb3a0
    void __cdecl SendGradeListToArena(int, ::GradeLevelInfo &, ::GradeInfo *const, short);  // 0x5fb630
    void __cdecl SendGradeToArena(int, ::GradeInfo &, char);  // 0x5fb940
    void __cdecl SendGradeLevelToArena(int, ::GradeLevelInfo &);  // 0x5fbb50
    void __cdecl SendGuildInfoToArena(::Session const *);  // 0x5fbd40
    void __cdecl SendGamePlayRestrictLevelToArena(::Session const *);  // 0x5fc020
    void __cdecl SendGamePlayRestrictLevelForHealthySystemToArena(::Session const *);  // 0x5fc1a0
    void __cdecl SendChangedGuildBuff(::SeasonContentsResultInfoOfGuild const *);  // 0x5fc300
    short __cdecl CheckArenaPortalUsable(::Data::ArenaPortalRecordPtr);  // 0x5fc650
    bool __cdecl BeginArenaLobbyReservation(unsigned __int64, char);  // 0x5fc9f0
    void __cdecl RollbackArenaLobbyReservation(void);  // 0x5fca90
    bool __cdecl CreateArenaLobbyRoomNotify(::ArenaLobbyEnterParam const &, bool, char);  // 0x5fcae0
    void __cdecl SendReserveArenaLobbyFail(short);  // 0x5fcc00
    void __cdecl SendFriendNotiLocation(::Pc::FriendNotiLocationType);  // 0x5fcd70
    short __cdecl SendEnterArenaLobby(char const *, short);  // 0x5fcfe0
    void __cdecl SendLeaveArenaLobbyByDisconnect(void);  // 0x5fd820
    short __cdecl SendLeaveArenaLobbyByUserRequest(void);  // 0x5fd930
    bool __cdecl SendLeaveArenaLobbyByAASFatiqueRule(void);  // 0x5fda50
    bool __cdecl EnterArenaLobbyOk(char);  // 0x5fdb60
    bool __cdecl LeaveArenaLobbyOk(void);  // 0x5fdc40
    short __cdecl SendExitFromArenaLobbyRoom(void);  // 0x5fdcc0
    short __cdecl SendSetArenaLobbyRoomMatchOption(char, char, char, char, short, short const *const);  // 0x5fddc0
    short __cdecl SendDelegateArenaLobbyRoomLeader(short, unsigned __int64);  // 0x5fe780
    short __cdecl SendSetArenaLobbyRoomPassword(short);  // 0x5fe880
    short __cdecl SendJoinArenaLobbyRoom(__int64, wchar_t const *, short, char, char);  // 0x5fe970
    short __cdecl SendBanishFromArenaLobby(short, unsigned __int64);  // 0x5fead0
    bool __cdecl ReturnToGame(void);  // 0x5febd0
    short __cdecl SendReadyToMatchArenaLobbyRoom(void);  // 0x5fec90
    short __cdecl SendUnReadyToMatchArenaLobbyRoom(void);  // 0x5fed90
    short __cdecl SendArenaLobbyMatchReq(char);  // 0x5fee70
    short __cdecl SendSkipArenaLobbyMatchReq(void);  // 0x5ff000
    short __cdecl SendCancelArenaLobbyMatchingReq(char);  // 0x5ff0e0
    short __cdecl SendCancelArenaLobbyMatchReq(void);  // 0x5ff1d0
    short __cdecl SendDecideToGoToArena(::Data::ArenaMatchingRuleDetailType);  // 0x5ff2b0
    bool __cdecl ReserveArena(::ReserveArenaParam const &);  // 0x5ff3a0
    void __cdecl RetrieveArenaLobbyWaitingNumber(void);  // 0x5ff580
    void __cdecl RetrieveArenaLobbyWaitingNumberComplete(unsigned __int64, int);  // 0x5ff6f0
    short __cdecl CancelArenaLobbyWaiting(void);  // 0x5ff7f0
    void __cdecl CancelArenaLobbyWaitingComplete(unsigned __int64);  // 0x5ff8e0
    bool __cdecl SendEnterArena(char const *, int);  // 0x5ff990
    void __cdecl InitArenaGradeParam(void);  // 0x6004f0
    bool __cdecl SetArenaGradeParam(::ArenaGradeParam &);  // 0x6006f0
    bool __cdecl GetArenaGradeParam(::ArenaGradeParam &);  // 0x600850
    bool __cdecl SendLogoutReqToArena(::TransactionExpireChecker::ExpireToken *, short);  // 0x6009b0
    bool __cdecl SendLogoutReqToArena(unsigned __int64, short);  // 0x600a80
    void __cdecl LogoutOkFromArena(void);  // 0x600b30
    void __cdecl UpdateReturnPos(::Pc::UpdateReturnPosType);  // 0x600b90
    void __cdecl ArenaLobbyClosed(short);  // 0x600ce0
    void __cdecl ReturnToGameByEnterFail(void);  // 0x600e20
    short __cdecl SendMoveToArena(int, bool, char);  // 0x600eb0
    ::Pc::ArenaSession __cdecl GetArenaSessionState(void) const;  // 0x600fe0
    bool __cdecl IsInArenaOrArenaLobby(void) const;  // 0x601020
    char __cdecl GetArenaLobbySessionForClient(void);  // 0x601080
    wchar_t const * __cdecl GetArenaSessionString(void) const;  // 0x601100
    bool __cdecl FetchShowcaseData(::FsdShowcaseRecord *);  // 0x601200
private:
    void __cdecl resetExhaustionTimer(bool);  // 0x601600
    void __cdecl exhaustionExceptRule(bool);  // 0x601b00
    void __cdecl onExhaustionTimer(void);  // 0x601c00
    void __cdecl onAutoRespawnTimer(void);  // 0x601da0
public:
    bool __cdecl UseHyperEnergy(int);  // 0x601e50
private:
    int __cdecl getMaxHyperEnergyPoint(void);  // 0x601f10
    void __cdecl calcHyperEnergyPoint(void);  // 0x602090
    virtual bool __cdecl changeMoveState(::CreatureMoveState, short, wchar_t *);  // 0x602150
public:
    void __cdecl StopTrialPlay(void);  // 0x602810
    bool __cdecl IsBoundRaidDungeon(unsigned __int64);  // 0x602910
    int __cdecl GetAllBoundRaidDungeon(::Pointer2< ::RaidDungeon> *const);  // 0x602990
    void __cdecl LogoutBoundRaidDungeon(void);  // 0x602b80
    bool __cdecl SetOccupyingRaidDungeon(unsigned __int64);  // 0x602c50
    bool __cdecl InitializeRaidDungeonInfo(bool);  // 0x602e30
private:
    ::GameFailReason __cdecl isEnterableRaidDungeon(short, unsigned __int64 &, char);  // 0x603290
    void __cdecl writeLogMoveHacking(void);  // 0x604020
    void __cdecl checkToEnterZoneCount(void);  // 0x6041c0
public:
    void __cdecl CheckToInvalidPartyPacket(void);  // 0x6042c0
    bool __cdecl checkTeamFactionBattleFieldWithTarget(::Creature *);  // 0x604350
    bool __cdecl checkTeamGuildBattleFieldWithTarget(::Creature *);  // 0x604430
    char __cdecl CheckTeamAttractionCondition(unsigned int);  // 0x6044d0
    bool __cdecl CheckToTransferFaction2WithEpicQuest(char, unsigned short &);  // 0x6048e0
    bool __cdecl TransferFaction2WithEpicQuest(char, unsigned short);  // 0x604990
    bool __cdecl PostAuctionEscrowTask(__int64, __int64, __int64);  // 0x604b70
    bool __cdecl PostChangeGradeTask(int, ::GradeInfo &, char);  // 0x604dc0
    bool __cdecl PostChangeGradeLevelTask(int, ::GradeLevelInfo &);  // 0x604f70
    bool __cdecl InitGrade(int, ::GradeLevelInfo &, ::GradeInfo *const, short);  // 0x605110
    bool __cdecl PostActivateAllGradeTask(void);  // 0x6051f0
    bool __cdecl PostActivateAllGradeTask(int, ::GradeLevelInfo &, ::GradeInfo *const, short);  // 0x605390
    bool __cdecl PostPartyBattleRatingScore(::PartyBattleResult, int, int, __int64, ::PartyBattleSideMember const &);  // 0x605530
    void __cdecl FetchDungeonRatingScore(::Packet *, ::RepeatPacketComposer *);  // 0x6056e0
    void __cdecl FetchDungeonRatingScoreScheduleNo(::Packet *, ::RepeatPacketComposer *);  // 0x605900
    int __cdecl GetDuelRatingScore(char);  // 0x605c50
    int __cdecl GetIngameChampionshipDuelRatingScore(char);  // 0x605cd0
    int __cdecl GetSeasonContentsCombatRatingScore(char);  // 0x605d50
    int __cdecl GetDuelRatingScoreScheduleNo(char);  // 0x605dc0
    int __cdecl GetIngameChampionshipDuelRatingScoreScheduleNo(char);  // 0x605e40
    void __cdecl SetAchievementData(::AchievementData *);  // 0x605ec0
    void __cdecl RepairAchievementReward(void);  // 0x606000
    bool __cdecl InvokeAchievementAbility(short, short);  // 0x606380
    void __cdecl SetNewbieInfoFlag(void);  // 0x606770
    void __cdecl SetTakingAchievementReward(bool);  // 0x6068c0
    bool __cdecl IsTakingAchievementReward(void);  // 0x606910
    void __cdecl GetPcInfoForGameLog(::PcInfoForGameLog &);  // 0x606950
    void __cdecl GetVitalityInfoForGameLog(::PcInfoForGameLog &);  // 0x606be0
    void __cdecl GetPowerInfoForGameLog(::PcInfoForGameLog &);  // 0x606d10
    char __cdecl IsBannedContentsOnLeaveZone(unsigned int) const;  // 0x606db0
    bool __cdecl IsExistBannedContentsForReward(void) const;  // 0x606f70
    void __cdecl RestorePositionForMobile(void);  // 0x607000
    bool __cdecl GetPropertyTransactionMoneyDiffEx(__int64, ::PropertyTransactionSyncData &, short);  // 0x6070d0
    ::Data::TendencyFieldPlayerGroupType __cdecl GetTendencyFieldPlayerGroup(void);  // 0x607290
    void __cdecl DecreasePetDurability(void);  // 0x607350
    void __cdecl ResetPetDurabilityDecreaseCount(void);  // 0x607460
    bool __cdecl EnableToRetrieveMyRanking(char);  // 0x607550
    void __cdecl UpdateBotScore(bool);  // 0x607600
    void __cdecl AddBotState(::Data::BotScoringConditionConditionTypeType, __int64, wchar_t const *, int);  // 0x607650
    void __cdecl SetBotScore(int);  // 0x6076c0
    void __cdecl SetBotScoreIgnore(bool, bool);  // 0x607740
    char __cdecl GetBotScoreLevel(void);  // 0x6077e0
    bool __cdecl GetBotScoreRestrictionIsolatePersistentZone(void);  // 0x607830
    short __cdecl GetBotScoreRestrictionReduceAttackPower(void);  // 0x607880
    short __cdecl GetBotScoreRestrictionReduceAcquireMoney(void);  // 0x6078f0
    short __cdecl GetBotScoreRestrictionReduceAcquireExp(void);  // 0x607940
    short __cdecl GetBotScoreRestrictionReduceAcquireDuelPoint(void);  // 0x607990
    short __cdecl GetBotScoreRestrictionReduceAcquirePartyBattlePoint(void);  // 0x6079e0
    short __cdecl GetBotScoreRestrictionReduceAcquireFieldPlayPoint(void);  // 0x607a30
    void __cdecl RetrieveCraftList(void);  // 0x607a80
    void __cdecl OnTimeBasedPlayTimeExpired(bool);  // 0x607e70
    void __cdecl SendFinishCraftNoti(::CraftInfo &);  // 0x607ed0
    bool __cdecl EnableJoinCraftUnion(char);  // 0x608120
    bool __cdecl JoinCraftUnion(char);  // 0x608240
    bool __cdecl HasCraft(char);  // 0x608300
    bool __cdecl IsJoinedCraftUnion(char);  // 0x6083a0
    bool __cdecl LeaveCraftUnion(char);  // 0x6083e0
    short __cdecl GetCraftUnionExp(char);  // 0x6084c0
    short __cdecl AddCraftUnionExp(char, short);  // 0x608500
    void __cdecl FetchCraftUnionList(::FragmentPacket *);  // 0x608630
    bool __cdecl IsRegisteredCraftRecipe(int, unsigned __int64);  // 0x608720
private:
    ::Pointer2< ::CraftInfo> __cdecl acquireCraftInfoByRecipeId(int);  // 0x6087c0
    ::Pointer2< ::CraftInfo> __cdecl acquireCraftInfoByCraftId(unsigned __int64);  // 0x608880
    void __cdecl clearCraftList(void);  // 0x608950
public:
    bool __cdecl TryToRegisterCraft(int, unsigned __int64, char, char, ::CraftOutput *const, ::SyncContext &);  // 0x608a10
    void __cdecl CancelToRegisterCraft(int);  // 0x608b30
    void __cdecl RegisterCraftOk(::RegisterCraftOkParam const *);  // 0x608bf0
    bool __cdecl EnableAbortCraft(unsigned __int64);  // 0x609280
    void __cdecl FinishCraft(unsigned __int64);  // 0x609340
    void __cdecl AbortCraft(unsigned __int64);  // 0x6094b0
    bool __cdecl GetCraftReward(unsigned __int64, ::CraftReward &);  // 0x6097c0
    ::GameFailReason __cdecl TryToTakeCraft(unsigned __int64, ::SyncContext &);  // 0x609c60
    void __cdecl TakeCraftOk(unsigned __int64, short);  // 0x609d60
    void __cdecl ChangeJumpingCharacterState(char);  // 0x60a1e0
    bool __cdecl SetUsingJumpingCharacter2Ticket(bool);  // 0x60a280
    bool const __cdecl IsUsingJumpingCharacter2Ticket(void);  // 0x60a3c0
    void __cdecl SetUncompletedAccInvenItemConsumptionList(int, ::UncompletedAccInvenItemConsumption *const);  // 0x60a400
    void __cdecl RecoverUncompletedAccInvenItemConsumption(void);  // 0x60a4e0
    void __cdecl InitPcAttractionState(void);  // 0x60aaa0
    void __cdecl SetTransformItemRetry(unsigned __int64, unsigned __int64);  // 0x60ab80
    void __cdecl ClearTransformItemRetry(void);  // 0x60ac30
    void __cdecl SetEffectPouch(char, short);  // 0x60ac70
    void __cdecl DropEffectPouch(short &, ::vector16 &);  // 0x60ad40
    void __cdecl ClearAttractionReward(void);  // 0x60af20
    bool __cdecl SetBattleRoyalFieldAttractionReward(char, short);  // 0x60af80
    void __cdecl TakeBattleRoyalFieldAttractionReward(void);  // 0x60b080
    bool __cdecl CheckGameTimeSchedule(void);  // 0x60b1b0
    bool __cdecl CheckSeasonContentsTypeNewSeason(char);  // 0x60b360
    ::GameFailReason __cdecl CheckSeasonContentsSchedule(::GeoZone const *);  // 0x60b480
    void __cdecl SendInitializeSeasonContentsRecordOk(void);  // 0x60b5e0
    void __cdecl SendInitializeSeasonContentsRecordFail(::GameFailReason);  // 0x60b880
    void __cdecl ComposeInitSeasonContentsInfo(char, char const *const);  // 0x60b8f0
    void __cdecl FinishSeasonContentsRecordInitialization(::RepeatPacketDecomposer &, ::Packet const *);  // 0x60bdf0
    void __cdecl FinishInitializationSeasonContents(short, ::InitCombatResultList *const, short, ::InitTimeAttackResultList *const);  // 0x60c230
    void __cdecl SeasonContentsRecordSyncToArenaLobby(unsigned __int64, short, ::InitCombatResultList *const);  // 0x60c630
    void __cdecl InitializeSeasonContentsRecord(char, char const *const);  // 0x60c7b0
    bool __cdecl AttachBenefitAbility(int, char const *const, int const *const, ::ChangedProperty *);  // 0x60ca00
    bool __cdecl DetachBenefitAbility(int, char const *const, int const *const, ::ChangedProperty *);  // 0x60cbb0
private:
    void __cdecl activateAccountExp(int, int);  // 0x60cd60
    void __cdecl recoverAccountExp(void);  // 0x60d260
    bool __cdecl isAccountExpCharged(__int64, bool);  // 0x60d880
public:
    bool __cdecl RechargeAccountExpQuota(void);  // 0x60d970
    bool __cdecl ApplyAccountExpToLobby(void);  // 0x60daa0
    bool __cdecl SendAccountExpToLobby(void);  // 0x60db90
    bool __cdecl ActivateAccountLevelBenefits(short, short, ::ChangedProperty *);  // 0x60dd50
    void __cdecl SetAccountExp(__int64, ::ChangedProperty *, short);  // 0x60dfe0
    bool __cdecl CheckPcLevelForAccountContents(bool, int, int, int, int);  // 0x60e090
private:
    void __cdecl updateUserAccountExpInfoOnLeaveWolrd(void);  // 0x60e290
public:
    static ::GameLogAccountExpReasonCode __cdecl GetGameLogAccountExpReasonCode(::Pc::AccountExpReason);  // 0x60e400
    void __cdecl WriteGameLogGetAccountExp(__int64, __int64, short, short, __int64 *, int *);  // 0x60e490
    bool __cdecl ApplyClosetCollectingAbility(void);  // 0x60e6d0
    bool __cdecl ApplyItemAbility(::Data::EffectRecordItemAbility *);  // 0x60e8b0
private:
    void __cdecl handleItemAbility(::Data::EffectRecordItemAbility *, ::ChangedProperty *);  // 0x60e990
public:
    bool __cdecl IsElevatedJobStyle(void);  // 0x60f580
    bool __cdecl ElevateJobStyle(bool);  // 0x60f670
    void __cdecl RefreshSkillInfo(bool);  // 0x60f8f0
    void __cdecl ActivateSlateAbilities(::EnterReason);  // 0x60f960
private:
    // LIFT: Pc has only part of its PDB members yet (size 0x95A8). The LiftBytes base holds the PDB bases and
    // the members from +8 to +0x4E2F. A char array with the PDB name of the first member holds each other gap.
    bool _exceptHate;  // +0x4E30
    char _combatModeType[0x8cc8 - 0x4e34];  // +0x4E34 (LIFT: PDB members _combatModeType to before _skillResultContext, not declared yet)
    ::SkillResultContext _skillResultContext;  // +0x8CC8
    char _inviteMentoringContext[0x95a8 - 0x8d78];  // +0x8D78 (LIFT: PDB members _inviteMentoringContext to the end, not declared yet)
};

struct PcInfoForGameLog
{
public:
    __cdecl PcInfoForGameLog(void);  // 0xe830
};

class SeasonContentsTimeAttackRecordContext
{
public:
    void __cdecl Init(::Pc *, char, __int64, short);  // 0x5d50b0
    bool __cdecl Start(short, __int64);  // 0x5d5210
    bool __cdecl Progress(short, __int64);  // 0x5d53e0
    bool __cdecl End(void);  // 0x5d5680
private:
    bool __cdecl startTran(short, int);  // 0x5d58a0
};

