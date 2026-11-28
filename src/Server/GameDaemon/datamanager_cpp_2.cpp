// datamanager_cpp_2.cpp: datamanager.cpp part 2 (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "datamanager.h"
#include "geoworld.h"
#include "LiftStub.h"

// 0x630ee0
unsigned __int64 __cdecl Data::DataManager::loadHiddenFieldFromBotScoringDestination(void)
{
    LIFT_STUB(0x630ee0);
}

// 0x631120
unsigned __int64 __cdecl Data::DataManager::loadHiddenFieldFromNewbieCare(void)
{
    LIFT_STUB(0x631120);
}

// 0x631380
unsigned __int64 __cdecl Data::DataManager::loadHiddenFieldFromFishingField(void)
{
    LIFT_STUB(0x631380);
}

// 0x631c00
unsigned __int64 __cdecl Data::DataManager::loadHiddenFieldFromItemBrand(void)
{
    LIFT_STUB(0x631c00);
}

// 0x632410
unsigned __int64 __cdecl Data::DataManager::loadHiddenFieldFromContentsReset(void)
{
    LIFT_STUB(0x632410);
}

// 0x632730
bool __cdecl Data::DataManager::IsValidCombatSeasonContentsType(char)
{
    LIFT_STUB(0x632730);
}

// 0x6327a0
#pragma comment(linker, "/INCLUDE:?GetCombatSeasonContentsTypeCount@DataManager@Data@@SAHXZ")  // LIFT: dead-strip keep (no live caller yet)
int __cdecl Data::DataManager::GetCombatSeasonContentsTypeCount(void)
{
    int count = 0;
    for (char i = 1; i < 16; ++i)
    {
        switch (i)
        {
        case 1:
        case 3:
        case 4:
        case 7:
        case 10:
        case 11:
        case 12:
        case 14:
        case 15:
            ++count;
            break;
        }
    }
    return count;
}

// 0x632820
bool __cdecl Data::DataManager::IsWarFieldMainZone(unsigned int)
{
    LIFT_STUB(0x632820);
}

// 0x6328e0
int __cdecl Data::DataManager::GetBattleRoyalFieldScoreConversion(char, char, int)
{
    LIFT_STUB(0x6328e0);
}

// 0x632990
char __cdecl Data::DataManager::GetGameModeFromArenaMatchingRuleDetailType(char, char)
{
    LIFT_STUB(0x632990);
}

// 0x632a70
bool __cdecl Data::DataManager::ConstructItemUsableKeyMap(void)
{
    LIFT_STUB(0x632a70);
}

// 0x632d70
bool __cdecl Data::DataManager::IsItemUsable(unsigned __int64, unsigned __int64, bool &)
{
    LIFT_STUB(0x632d70);
}

// 0x633010
bool __cdecl Data::DataManager::ConstructDuelBotTrainingRoomVersion(void)
{
    LIFT_STUB(0x633010);
}

// 0x633110
bool __cdecl Data::DataManager::ConstructRandomDistributionAccumulated(void)
{
    LIFT_STUB(0x633110);
}

// 0x6332b0
bool __cdecl Data::DataManager::GetRandRangeByDistribution(unsigned __int64, int &, int &)
{
    LIFT_STUB(0x6332b0);
}

// 0x633410
int __cdecl Data::DataManager::GetNextSeasonContentsDefaultRatingScore(char, int)
{
    LIFT_STUB(0x633410);
}

// 0x633490
bool __cdecl Data::DataManager::FindSkillChildren(int, int *const, int &)
{
    LIFT_STUB(0x633490);
}

// 0x6335b0
bool __cdecl Data::DataManager::FindSkill3Keys(int, __int64 *const, int &)
{
    LIFT_STUB(0x6335b0);
}

// 0x633710
void __cdecl Data::DataManager::addSkillAchievementEvent(int *, bool *, int, short)
{
    LIFT_STUB(0x633710);
}

// 0x633960
void __cdecl Data::DataManager::addSkillVariationAchievementEvent(int, short)
{
    LIFT_STUB(0x633960);
}

// 0x633a80
unsigned __int64 __cdecl Data::DataManager::loadHiddenFieldFromCave2(void)
{
    LIFT_STUB(0x633a80);
}

// 0x633c40
unsigned __int64 __cdecl Data::DataManager::loadHiddenFieldFromFieldZone(void)
{
    LIFT_STUB(0x633c40);
}

// 0x633e00
unsigned __int64 __cdecl Data::DataManager::loadHiddenFieldFromJackpotBossZone(void)
{
    LIFT_STUB(0x633e00);
}

// 0x633fa0
unsigned __int64 __cdecl Data::DataManager::loadHiddenFieldFromClassicFieldZone(void)
{
    LIFT_STUB(0x633fa0);
}

// 0x634160
unsigned __int64 __cdecl Data::DataManager::loadHiddenFieldFromDungeon(void)
{
    LIFT_STUB(0x634160);
}

// 0x634980
unsigned __int64 __cdecl Data::DataManager::loadHiddenFieldFromRaidDungeon(void)
{
    LIFT_STUB(0x634980);
}

// 0x634f50
unsigned __int64 __cdecl Data::DataManager::loadHiddenFieldFromBossChallenge(void)
{
    LIFT_STUB(0x634f50);
}

// 0x6353f0
unsigned __int64 __cdecl Data::DataManager::loadHiddenFieldFromCraftRecipe(void)
{
    LIFT_STUB(0x6353f0);
}

// 0x635990
unsigned __int64 __cdecl Data::DataManager::loadHiddenFieldFromTencentQuest(void)
{
    LIFT_STUB(0x635990);
}

// 0x635b10
unsigned __int64 __cdecl Data::DataManager::loadHiddenFieldFromArenaPortal(void)
{
    LIFT_STUB(0x635b10);
}

// 0x635f50
unsigned __int64 __cdecl Data::DataManager::loadHiddenFieldFromDuel(void)
{
    LIFT_STUB(0x635f50);
}

// 0x6360f0
unsigned __int64 __cdecl Data::DataManager::loadHiddenFieldFromDuelBotGroup(void)
{
    LIFT_STUB(0x6360f0);
}

// 0x6361b0
unsigned __int64 __cdecl Data::DataManager::loadHiddenFieldFromFactionBattleFieldZone(void)
{
    LIFT_STUB(0x6361b0);
}

// 0x636350
unsigned __int64 __cdecl Data::DataManager::loadHiddenFieldFromGuildBattleFieldZone(void)
{
    LIFT_STUB(0x636350);
}

// 0x636570
unsigned __int64 __cdecl Data::DataManager::loadHiddenFieldFromMasteryLevel(void)
{
    LIFT_STUB(0x636570);
}

// 0x636830
unsigned __int64 __cdecl Data::DataManager::loadHiddenFieldFromMessageByItemDistrict(void)
{
    LIFT_STUB(0x636830);
}

// 0x636a40
unsigned __int64 __cdecl Data::DataManager::loadHiddenFieldFromPartyBattleFieldZone(void)
{
    LIFT_STUB(0x636a40);
}

// 0x636bf0
unsigned __int64 __cdecl Data::DataManager::loadHiddenFieldFromWeeklyTimeTable(void)
{
    LIFT_STUB(0x636bf0);
}

// 0x636d70
unsigned __int64 __cdecl Data::DataManager::setWeelyTimeTableBitsByData(::Data::WeeklyTimeTableRecordPtr, char *)
{
    LIFT_STUB(0x636d70);
}

// 0x637340
unsigned __int64 __cdecl Data::DataManager::loadHiddenFieldFromDuelBotChallenge(void)
{
    LIFT_STUB(0x637340);
}

// 0x6377a0
unsigned __int64 __cdecl Data::DataManager::loadHiddenFieldFromDuelBotTrainingRoom(void)
{
    LIFT_STUB(0x6377a0);
}

// 0x637a40
unsigned __int64 __cdecl Data::DataManager::loadHiddenFieldFromWeaponAppearanceChangeCost(void)
{
    LIFT_STUB(0x637a40);
}

// 0x637c30
unsigned __int64 __cdecl Data::DataManager::loadHiddenFieldFromRankingGroupReward(void)
{
    LIFT_STUB(0x637c30);
}

// 0x637eb0
unsigned __int64 __cdecl Data::DataManager::loadHiddenFieldFromRankingReward(void)
{
    LIFT_STUB(0x637eb0);
}

// 0x638380
unsigned __int64 __cdecl Data::DataManager::loadHiddenFieldFromRankingPvEStage(void)
{
    LIFT_STUB(0x638380);
}

// 0x6386e0
unsigned __int64 __cdecl Data::DataManager::loadHiddenFieldFromTendencyField(bool)
{
    LIFT_STUB(0x6386e0);
}

// 0x63a1a0
unsigned __int64 __cdecl Data::DataManager::loadHiddenFieldFromSkillTrainingRoom(void)
{
    LIFT_STUB(0x63a1a0);
}

// 0x63a470
unsigned __int64 __cdecl Data::DataManager::loadHiddenFieldFromSkillTrainingRoomGroup(void)
{
    LIFT_STUB(0x63a470);
}

// 0x63a690
unsigned __int64 __cdecl Data::DataManager::loadHiddenFieldFromDefaultRatingScoreGroup(void)
{
    LIFT_STUB(0x63a690);
}

// 0x63a800
unsigned __int64 __cdecl Data::DataManager::loadHiddenFieldFromPublicRaid(void)
{
    LIFT_STUB(0x63a800);
}

// 0x63aac0
unsigned __int64 __cdecl Data::DataManager::loadHiddenFieldFromBattleRoyalField(void)
{
    LIFT_STUB(0x63aac0);
}

// 0x63aee0
bool __cdecl Data::checkWarFieldZone(::Data::ZoneRecordPtr, ::Data::WarFieldWarFieldZoneTypeType)
{
    LIFT_STUB(0x63aee0);
}

// 0x63b070
unsigned __int64 __cdecl Data::DataManager::loadHiddenFieldFromWarField(void)
{
    LIFT_STUB(0x63b070);
}

// 0x63be30
unsigned __int64 __cdecl Data::DataManager::loadHiddenFieldFromSimpleField(void)
{
    LIFT_STUB(0x63be30);
}

// 0x63c060
unsigned __int64 __cdecl Data::DataManager::loadHiddenFieldFromSeasonContentsSchedule(void)
{
    LIFT_STUB(0x63c060);
}

// 0x63c7d0
unsigned __int64 __cdecl Data::DataManager::loadHiddenFieldFromChallengeParty(void)
{
    LIFT_STUB(0x63c7d0);
}

// 0x63cdb0
unsigned __int64 __cdecl Data::DataManager::loadHiddenFieldFromMentoring(void)
{
    LIFT_STUB(0x63cdb0);
}

// 0x63ce80
unsigned __int64 __cdecl Data::DataManager::loadHiddenFieldFromRandomStoreDrawReward(void)
{
    LIFT_STUB(0x63ce80);
}

// 0x63d2c0
unsigned __int64 __cdecl Data::DataManager::loadHiddenFieldFromSecretTreaure(void)
{
    LIFT_STUB(0x63d2c0);
}

// 0x63d5a0
unsigned __int64 __cdecl Data::DataManager::loadHiddenFieldFromSkillBuildUp(void)
{
    LIFT_STUB(0x63d5a0);
}

// 0x63d740
bool __cdecl Data::loadHiddenStopNextSkill(::Data::Skill3RecordActiveSkillPtr, unsigned __int64, wchar_t const *, char &)
{
    LIFT_STUB(0x63d740);
}

// 0x63d9c0
unsigned __int64 __cdecl Data::DataManager::loadHiddenFieldFromSkill3(void)
{
    LIFT_STUB(0x63d9c0);
}

// 0x63df10
unsigned __int64 __cdecl Data::DataManager::loadHiddenFieldFromFishingPaste(void)
{
    LIFT_STUB(0x63df10);
}

// 0x63e270
unsigned __int64 __cdecl Data::DataManager::loadHiddenFieldFromPc(void)
{
    LIFT_STUB(0x63e270);
}

// 0x63e470
unsigned __int64 __cdecl Data::DataManager::loadHiddenFieldFromBadgeSetItem(void)
{
    LIFT_STUB(0x63e470);
}

// 0x63e5d0
unsigned __int64 __cdecl Data::DataManager::loadHiddenFieldFromBadgeSynthesisCost(void)
{
    LIFT_STUB(0x63e5d0);
}

// 0x63e720
unsigned __int64 __cdecl Data::DataManager::loadHiddenFieldFromBadgeSynthesisRecipe(void)
{
    LIFT_STUB(0x63e720);
}

// 0x63eb40
bool __cdecl Data::DataManager::makeBadgeSynthesisResultDataPacket(void)
{
    LIFT_STUB(0x63eb40);
}

// 0x63ef30
unsigned __int64 __cdecl Data::DataManager::loadHiddenFieldFromJumpingCharacter2(void)
{
    LIFT_STUB(0x63ef30);
}

// 0x63f3c0
unsigned __int64 __cdecl Data::DataManager::loadHiddenFieldFromJumpingQuest2(void)
{
    LIFT_STUB(0x63f3c0);
}

// 0x63f5f0
unsigned __int64 __cdecl Data::DataManager::loadHiddenFieldFromJumpingTeleport2(void)
{
    LIFT_STUB(0x63f5f0);
}

// 0x63f770
unsigned __int64 __cdecl Data::DataManager::loadHiddenFieldFromNpc(void)
{
    LIFT_STUB(0x63f770);
}

// 0x63f8b0
unsigned __int64 __cdecl Data::DataManager::loadHiddenFieldFromChallengeList(void)
{
    LIFT_STUB(0x63f8b0);
}

// 0x63f9b0
unsigned __int64 __cdecl Data::DataManager::loadHiddenFieldFromItemFusion(void)
{
    LIFT_STUB(0x63f9b0);
}

// 0x63fc00
unsigned __int64 __cdecl Data::validateZoneAttraction(void)
{
    LIFT_STUB(0x63fc00);
}

// 0x63fdb0
unsigned __int64 __cdecl Data::validateArenaPortal(void)
{
    LIFT_STUB(0x63fdb0);
}

// 0x63ff90
unsigned __int64 __cdecl Data::validateCave(void)
{
    LIFT_STUB(0x63ff90);
}

// 0x640140
unsigned __int64 __cdecl Data::validateFieldZone(void)
{
    LIFT_STUB(0x640140);
}

// 0x6402e0
unsigned __int64 __cdecl Data::validateJackpotBossZone(void)
{
    LIFT_STUB(0x6402e0);
}

// 0x640450
unsigned __int64 __cdecl Data::DataManager::validateGeoZone(void)
{
    LIFT_STUB(0x640450);
}

// 0x6416e0
unsigned __int64 __cdecl Data::validateMysteriousStore(void)
{
    LIFT_STUB(0x6416e0);
}

// 0x6418c0
unsigned __int64 __cdecl Data::validateMysteriousStoreItemGroup(void)
{
    LIFT_STUB(0x6418c0);
}

// 0x641a90
unsigned __int64 __cdecl Data::validateMarketRegisterAmountTax(void)
{
    LIFT_STUB(0x641a90);
}

// 0x641fa0
unsigned __int64 __cdecl Data::validateMasteryStatPoint(void)
{
    LIFT_STUB(0x641fa0);
}

// 0x6423f0
unsigned __int64 __cdecl Data::validateRaidDungeon(void)
{
    LIFT_STUB(0x6423f0);
}

// 0x642530
unsigned __int64 __cdecl Data::validateExp(void)
{
    LIFT_STUB(0x642530);
}

// 0x642b00
unsigned __int64 __cdecl Data::validateGuildAction(void)
{
    LIFT_STUB(0x642b00);
}

// 0x642cf0
unsigned __int64 __cdecl Data::validateGuildDiscount(void)
{
    LIFT_STUB(0x642cf0);
}

// 0x642e80
unsigned __int64 __cdecl Data::validateGuildLevel(void)
{
    LIFT_STUB(0x642e80);
}

// 0x642fa0
unsigned __int64 __cdecl Data::validateContentQuota(void)
{
    LIFT_STUB(0x642fa0);
}

// 0x643500
unsigned __int64 __cdecl Data::validateGrade(void)
{
    LIFT_STUB(0x643500);
}

// 0x643640
unsigned __int64 __cdecl Data::validatePcCafeBenefits(void)
{
    LIFT_STUB(0x643640);
}

// 0x6438e0
unsigned __int64 __cdecl Data::validateInterDungeonList(void)
{
    LIFT_STUB(0x6438e0);
}

// 0x643eb0
unsigned __int64 __cdecl Data::validateDuel(void)
{
    LIFT_STUB(0x643eb0);
}

// 0x644330
unsigned __int64 __cdecl Data::validatePartyBattleFieldZone(void)
{
    LIFT_STUB(0x644330);
}

// 0x644690
unsigned __int64 __cdecl Data::validateExpandRandomStore(void)
{
    LIFT_STUB(0x644690);
}

// 0x6448f0
unsigned __int64 __cdecl Data::validateRandomStoreItemGroup(void)
{
    LIFT_STUB(0x6448f0);
}

// 0x644f30
unsigned __int64 __cdecl Data::validateRandomStoreProbGroup(void)
{
    LIFT_STUB(0x644f30);
}

// 0x645330
unsigned __int64 __cdecl Data::validateRandomStore(void)
{
    LIFT_STUB(0x645330);
}

// 0x645b80
unsigned __int64 __cdecl Data::validateEffect(void)
{
    LIFT_STUB(0x645b80);
}

// 0x646bf0
unsigned __int64 __cdecl Data::validateEnv(void)
{
    LIFT_STUB(0x646bf0);
}

// 0x6472b0
bool __cdecl Data::isValidArea(::GeoZone const &, ::dr_box16, ::dr_box16 &)
{
    LIFT_STUB(0x6472b0);
}

// 0x647410
unsigned __int64 __cdecl Data::validateZoneNpcSpawn(void)
{
    LIFT_STUB(0x647410);
}

// 0x647cb0
unsigned __int64 __cdecl Data::validateChallengeParty(void)
{
    LIFT_STUB(0x647cb0);
}

// 0x647ea0
unsigned __int64 __cdecl Data::validateSeasonContentsSchedule(void)
{
    LIFT_STUB(0x647ea0);
}

// 0x648980
unsigned __int64 __cdecl Data::validateZoneTriggerEventCond(void)
{
    LIFT_STUB(0x648980);
}

// 0x648b00
unsigned __int64 __cdecl Data::validateItemTransformRecipe(void)
{
    LIFT_STUB(0x648b00);
}

// 0x649dd0
unsigned __int64 __cdecl Data::validateItemUsableRelation(void)
{
    LIFT_STUB(0x649dd0);
}

// 0x64a090
unsigned __int64 __cdecl Data::validateWeaponGemTransformResult(void)
{
    LIFT_STUB(0x64a090);
}
