// datamanager.h: datamanager.cpp, datamanager.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"
#include <stddef.h>
#include <map>
#include "../BloodLib/include/Lock.h"
#include "../BloodLib/include/LogFile.h"
#include "../BloodLib/include/StlMemory.h"
#include "../Packet/FragmentPacket.h"

namespace Data {
class AccountLevelRecordPtr;
class LevelRecordPtr;
struct ExceedLevelData;
struct SoulNpcSkillCategoryData;
struct RandomDistributionAccumulated;
class BoastEventRecord;
}

namespace Data {
class AdditionalServiceItems
{
public:
    enum AdditionalServiceItemType {};
public:
    bool __cdecl Add(::Data::AdditionalServiceItems::AdditionalServiceItemType, wchar_t const *);  // 0x453bc0
};
}

namespace Data {
class BoardGachaData
{
public:
    bool __cdecl SetBoardGachaRecord(::Data::BoardGachaRecordPtr);  // 0x662c10
};
}

namespace Data {
class DataLogger
{
public:
    virtual void __cdecl Write(::DrLog::Type, wchar_t const *, int, wchar_t const *, ...);  // 0x6171b0
};
}

namespace Data {
class DataManager
{
public:
    struct DroppedPouchPosInfo
    {
    public:
        short posCount;  // +0 (0x0)
        short pos[1000];  // +2 (0x2)
    };
    struct PvEStageStartInfoID
    {
    public:
        PvEStageStartInfoID(short a, unsigned __int64 k) : attraction(a), attractionKey(k) {}
        PvEStageStartInfoID() {}
        bool operator==(::Data::DataManager::PvEStageStartInfoID const & o) const { return attraction == o.attraction && attractionKey == o.attractionKey; }
        bool operator<(::Data::DataManager::PvEStageStartInfoID const & o) const { return attraction < o.attraction || (attraction == o.attraction && attractionKey < o.attractionKey); }
        short attraction;  // +0 (0x0)
        unsigned __int64 attractionKey;  // +8 (0x8)
    };
    struct RandomStoreDrawRewardID
    {
    public:
        char _randomStoreNumber;  // +0 (0x0)
        int _accumulatedRequiredDrawCount;  // +4 (0x4)
    };
    struct RankingPvEStageStartInfo
    {
    public:
        ::Data::DataManager::PvEStageStartInfoID id;  // +0 (0x0)
        char seasonContentsType;  // +16 (0x10)
    };
    // PDB layout (size 0xD6E8). Members in PDB order. A by-value type without a lifted layout is a qword array.
    ::DrDataReader * _reader;  // +0 (0x0)
    ::DrAliasMap * _aliasMap;  // +8 (0x8)
    ::DrElReader * _elreader;  // +16 (0x10)
    ::DrLoaderDef _loaderDefs[266];  // +24 (0x18)
    ::CombatSequenceLoader * _combatSequence;  // +0x63D8
    ::ActSequenceLoader * _actSequence;  // +0x63E0
    ::QuestTable * _quest;  // +0x63E8
    ::Data::ScriptTable * _script;  // +0x63F0
    ::GeoWorld * _geoWorld;  // +0x63F8
    ::FilterFactory * _filterFactory;  // +0x6400
    ::ReactionFactory * _reactionFactory;  // +0x6408
    int * _expTable;  // +0x6410
    ::Data::LevelRecordPtr * _levelDataTable;  // +0x6418
    ::Data::ExceedLevelData * _exceedLevelDataList;  // +0x6420
    int _exceedLevelDataListCount;  // +0x6428
    int _exceedLevelFirstLevel;  // +0x642C
    __int64 * _masteryExpTable;  // +0x6430
    __int64 * _accountExpTable;  // +0x6438
    ::Data::AccountLevelRecordPtr * _accountLevelDataTable;  // +0x6440
    wchar_t _rootDataPath[260];  // +0x6448
    wchar_t _zoneRootDataPath[260];  // +0x6650
    wchar_t _scriptRootDataPath[260];  // +0x6858
    wchar_t _questRootDataPath[260];  // +0x6A60
    wchar_t _terrainRootDataPath[260];  // +0x6C68
    wchar_t _socialRootDataPath[260];  // +0x6E70
    wchar_t _zipFileDataPath[260];  // +0x7078
    int _mainFactionCount;  // +0x7280
    char * _mainFactionIds;  // +0x7288
    int _gemGearScoreCount;  // +0x7290
    int _gemCardGearScoreCount;  // +0x7294
    int * _gemGearScoreTable;  // +0x7298
    int * _gemCardGearScoreTable;  // +0x72A0
    int _arenaDungeonZoneIdCapacity;  // +0x72A8
    int _arenaDungeonZoneIdCount;  // +0x72AC
    unsigned __int64 * _arenaDungeonZoneIds;  // +0x72B0
    int _arenaDuelZoneIdCapacity;  // +0x72B8
    int _arenaDuelZoneIdCount;  // +0x72BC
    unsigned __int64 * _arenaDuelZoneIds;  // +0x72C0
    int _vitalityBenefitGradeKey;  // +0x72C8
    int _quotaKeyRecordListCount;  // +0x72CC
    ::Data::ContentQuotaRecordPtr * _quotaKeyRecordList;  // +0x72D0
    unsigned __int64 _zoneBroadcastSocialActionNpc;  // +0x72D8
    unsigned __int64 _zoneBroadcastSocialActionNpc2;  // +0x72E0
    int _bossHpZoneBroadcastGeoZoneId;  // +0x72E8
    __int64 _challengeListWeekStartDateTime;  // +0x72F0
    int _challengeListWeekCount;  // +0x72F8
    ::std::map<unsigned short, ::Data::AcquireSkillByQuestMission *, ::std::less<unsigned short>, ::StlAllocator< ::std::pair<unsigned short, ::Data::AcquireSkillByQuestMission *>, 2> > _skillByQuestMissionList;  // +0x7300
    ::std::map<unsigned __int64, char *, ::std::less<unsigned __int64>, ::StlAllocator< ::std::pair<unsigned __int64, char *>, 2> > _weeklyTimeTableList;  // +0x7320
    ::std::map<unsigned __int64, ::std::pair<int, int>, ::std::less<unsigned __int64>, ::StlAllocator< ::std::pair<unsigned __int64, ::std::pair<int, int> >, 2> > _weeklyTimeMinuteTableList;  // +0x7340
    unsigned __int64 _battleRoyalFieldJobStyleRestrictionList[3];  // +0x7360. LIFT: PDB type std::list<int,StlAllocator<int,2> > (size 0x18, align 8), layout not lifted yet
    unsigned __int64 _arenaDaemonPersistentZoneList[3];  // +0x7378. LIFT: PDB type std::list<int,StlAllocator<int,2> > (size 0x18, align 8), layout not lifted yet
    ::std::multimap<int, int, ::std::less<int>, ::StlAllocator< ::std::pair<int, int>, 2> > _skillChildrenMap;  // +0x7390
    ::std::multimap<int, unsigned __int64, ::std::less<int>, ::StlAllocator< ::std::pair<int, unsigned __int64>, 2> > _skillVariationMap;  // +0x73B0
    ::std::map<int, ::Data::GradeBenefit *, ::std::less<int>, ::StlAllocator< ::std::pair<int, ::Data::GradeBenefit *>, 2> > _gradeBenefitListMap;  // +0x73D0
    ::std::map<unsigned __int64, char, ::std::less<unsigned __int64>, ::StlAllocator< ::std::pair<unsigned __int64, char>, 2> > _weaponBrandMaxGemSlotCountMap;  // +0x73F0
    bool _enableSouNpcSkill;  // +0x7410
    ::Data::SoulNpcSkillCategoryData * * _soulNpcSkills;  // +0x7418
    ::std::map<unsigned __int64, int, ::std::less<unsigned __int64>, ::StlAllocator< ::std::pair<unsigned __int64, int>, 2> > _itemUsableRelationKeyMap;  // +0x7420
    ::std::map<unsigned __int64, unsigned __int64, ::std::less<unsigned __int64>, ::StlAllocator< ::std::pair<unsigned __int64, unsigned __int64>, 2> > _itemUsableRelationAttractionGroupMap;  // +0x7440
    bool _duelBotChallengeDispelEffectType[642];  // +0x7460
    bool _skillTrainingRoomRemainEffectType[642];  // +0x76E2
    bool _challengePartyAttractionRemainEffectType[642];  // +0x7964
    unsigned int _skillTrainingRoomAttractionKey;  // +0x7BE8
    unsigned int _publicRaidAttractionKey;  // +0x7BEC
    unsigned __int64 _challengePartyAttractionKey;  // +0x7BF0
    unsigned int _battleRoyalFieldAttractionKey;  // +0x7BF8
    short _duelBotTrainingRoomVersion;  // +0x7BFC
    __int64 _newbieInfoFlag;  // +0x7C00
    ::std::map<unsigned __int64, ::Data::RandomDistributionAccumulated *, ::std::less<unsigned __int64>, ::StlAllocator< ::std::pair<unsigned __int64, ::Data::RandomDistributionAccumulated *>, 2> > _randomDistributionKeyMap;  // +0x7C08
    unsigned __int64 _mentoringRecordPtr;  // +0x7C28. LIFT: PDB type Data::MentoringRecordPtr (size 8, align 8), layout not lifted yet
    short _mentoringEnableVersion;  // +0x7C30
    short _mentoringLastVersion;  // +0x7C32
    unsigned __int64 _jumpingCharacterData[0x4F8 / 8];  // +0x7C38. LIFT: PDB type Data::JumpingCharacterData (size 0x4F8, align 8), layout not lifted yet
    unsigned __int64 _jumpingCharacterData2[0xD8 / 8];  // +0x8130. LIFT: PDB type Data::JumpingCharacterData2 (size 0xD8, align 8), layout not lifted yet
    unsigned __int64 _noneSpecifyObjectQuest[3][0x140 / 8];  // +0x8208. LIFT: PDB type Data::NoneSpecifyObjectQuestForwarding[3] (size 0x140 each, align 8), layout not lifted yet
    unsigned __int64 _pvpDifficultyTypePtr;  // +0x85C8. LIFT: PDB type Data::DifficultyTypeRecordPtr (size 8, align 8), layout not lifted yet
    unsigned __int64 _defaultDifficultyTypePtr;  // +0x85D0. LIFT: PDB type Data::DifficultyTypeRecordPtr (size 8, align 8), layout not lifted yet
    char _defaultDifficultyTypeId;  // +0x85D8
    int _defaultDifficultyTypeDataIdx;  // +0x85DC
    ::std::multimap<__int64, ::Data::BoastEventRecord *, ::std::less<__int64>, ::StlAllocator< ::std::pair<__int64, ::Data::BoastEventRecord *>, 2> > _boastEventMap[6];  // +0x85E0
    bool _parallelLoad;  // +0x86A0
    ::CriticalSection _dataReaderErrorLogFileLock;  // +0x86A8
    ::LogFile * _dataReaderErrorLogFile;  // +0x86D0
    ::LogFile * _scriptLoaderErrorLogFile;  // +0x86D8
    ::LogFile * _dataLoadErrorLogFile;  // +0x86E0
    ::LogFile * _dataValidationFailureLogFile;  // +0x86E8
    ::std::map< ::Data::DataManager::PvEStageStartInfoID, ::Data::DataManager::RankingPvEStageStartInfo *, ::std::less< ::Data::DataManager::PvEStageStartInfoID>, ::StlAllocator< ::std::pair< ::Data::DataManager::PvEStageStartInfoID, ::Data::DataManager::RankingPvEStageStartInfo *>, 2> > _rankingPvEStageStartInfoMap;  // +0x86F0
    ::std::map< ::Data::DataManager::RandomStoreDrawRewardID, ::Data::RandomStoreDrawRewardRecordPtr, ::std::less< ::Data::DataManager::RandomStoreDrawRewardID>, ::StlAllocator< ::std::pair< ::Data::DataManager::RandomStoreDrawRewardID, ::Data::RandomStoreDrawRewardRecordPtr>, 2> > _RandomStoreDrawRewardSet;  // +0x8710
    int _firstRandomStoreDrawRewardRequiredDrawCount[2];  // +0x8730
    int _lastRandomStoreDrawRewardRequiredDrawCount[2];  // +0x8738
    int _totalRandomStoreDrawRewardRequiredDrawCount[2];  // +0x8740
    ::Data::DataManager::DroppedPouchPosInfo _droppedPouchPos[10];  // +0x8748
    char _droppedPouchPosCount;  // +0xD57C
    unsigned __int64 _elevationJobStyleQuestList[4];  // +0xD580. LIFT: PDB type std::map<unsigned short,char,std::less<unsigned int>,StlAllocator<std::pair<unsigned short,char>,2> > (size 0x20, align 8), layout not lifted yet
    int _badgeSetItemScoreUnitSize;  // +0xD5A0
    int _badgeSynthesisScoreUnitSize;  // +0xD5A4
    ::FragmentPacket _badgeSynthesisResultDataPacket;  // +0xD5A8
    int _maxBadge1SynthesisScore;  // +0xD6A0
    int _maxBadge2SynthesisScore;  // +0xD6A4
    int _maxBadge3SynthesisScore;  // +0xD6A8
    ::Data::AdditionalServiceItems * _additionalServiceItems;  // +0xD6B0
    unsigned __int64 _boardGachaData;  // +0xD6B8. LIFT: PDB type Data::BoardGachaData (size 8, align 8), layout not lifted yet
    unsigned __int64 _slatecaches[2];  // +0xD6C0. LIFT: PDB type Data::SlateRelationCache (size 0x10, align 8), layout not lifted yet
    unsigned __int64 _formulaConstantData;  // +0xD6D0. LIFT: PDB type Data::FormulaConstantData (size 8, align 8), layout not lifted yet
    int _itemFusionScoreUnitSize;  // +0xD6D8
    int * _maxItemFusionScores;  // +0xD6E0
private:
    static ::Data::DataManager * Instance;
public:
    ::Data::RandomStoreDrawRewardRecordPtr const __cdecl GetNextRandomStoreDrawReward(char, int);  // 0x1eddc0
    static bool __cdecl CheckJumpingCharacterTicketItemDataId(unsigned int);  // 0x34ef90
    static ::std::map<unsigned short, ::Data::AcquireSkillByQuestMission *, ::std::less<unsigned short>, ::StlAllocator< ::std::pair<unsigned short, ::Data::AcquireSkillByQuestMission *>, 2> > const __cdecl GetSkillByQuestMissionList(void);  // 0x453e30
    static char __cdecl IsRankingPvEStageStartInfo(short, unsigned __int64);  // 0x453e60
    static ::Data::DataManager * __cdecl InitInstance(long, wchar_t const *);  // 0x618450
    __cdecl DataManager(::DrDataReader *, ::DrAliasMap *, ::DrElReader *, wchar_t const *);  // 0x618710
    __cdecl ~DataManager(void);  // 0x61e640
    void __cdecl CloseLog(void);  // 0x61f330
    void __cdecl FlushLog(void);  // 0x61f4c0
    bool __cdecl Load(::XmlReaderIO *, wchar_t const *);  // 0x61f560
private:
    bool __cdecl loadData(::XmlReader const &, int);  // 0x61f8f0
    bool __cdecl loadGeoData(::XmlReaderIO *);  // 0x61fc80
    void __cdecl onConstructData(void);  // 0x61fe40
    bool __cdecl checkToExistKeyFromAllTable(::Data::TableType, unsigned __int64, bool, bool);  // 0x61ff00
    bool __cdecl constructData(void);  // 0x620270
    unsigned __int64 __cdecl loadHiddenFieldFromZone(void);  // 0x623d00
    unsigned __int64 __cdecl loadHiddenFieldFromNpcBrainParameters(void);  // 0x624e70
    unsigned __int64 __cdecl loadHiddenFieldFromFielditem(void);  // 0x6250c0
    unsigned __int64 __cdecl loadHiddenFieldFromFielditemDrop(void);  // 0x6251b0
    unsigned __int64 __cdecl loadHiddenFieldFromQuest(void);  // 0x6252e0
    unsigned __int64 __cdecl loadHiddenFieldFromEffect(void);  // 0x6284a0
    unsigned __int64 __cdecl loadHiddenFieldFromGuildBankItem(void);  // 0x628b10
    unsigned __int64 __cdecl loadHiddenFieldFromGuildUniformParamTypeCategory(void);  // 0x628c90
    unsigned __int64 __cdecl loadHiddenFieldFromAccountPostCharge(void);  // 0x628ec0
    unsigned __int64 __cdecl loadHiddenFieldFromSkill(void);  // 0x628f90
    unsigned __int64 __cdecl loadHiddenFieldFromEnv(void);  // 0x629330
    unsigned __int64 __cdecl loadExpTableFromLevel(void);  // 0x629a50
    unsigned __int64 __cdecl loadAccountExpTableFromAccountLevel(void);  // 0x629cd0
    unsigned __int64 __cdecl loadQuotaTableFromContentQuota(void);  // 0x629e80
    unsigned __int64 __cdecl loadArenaDungeonZoneFromInterDungeonList(void);  // 0x629fe0
    unsigned __int64 __cdecl loadArenaDuelZoneFromDuel(void);  // 0x62a2b0
    unsigned __int64 __cdecl loadGradeBenefits(void);  // 0x62a390
    unsigned __int64 __cdecl loadItemTransformRecipe(void);  // 0x62aa50
    unsigned __int64 __cdecl loadZoneNpcSpawn(void);  // 0x62ab50
    bool __cdecl addToArenaDungeonZoneIdList(unsigned __int64);  // 0x62aed0
    bool __cdecl addToArenaDuelZoneIdList(unsigned __int64);  // 0x62afc0
    bool __cdecl checkQuestReward(::QuestReward *, unsigned short);  // 0x62b0b0
    bool __cdecl checkDisjoinedQuestReward(unsigned __int64 *&, int, bool, bool, unsigned short, char, ::Quest const *);  // 0x62b1f0
public:
    static int __cdecl GetExp(char);  // 0x62be40
    static bool __cdecl AddExceedLevelData(char, unsigned short, char);  // 0x62be90
    static __int64 __cdecl GetAccountExp(short);  // 0x62c1b0
    static ::Data::ContentQuotaRecordPtr const __cdecl GetQuotaKeyRecord(::Data::ContentQuotaRecordSubType, int);  // 0x62c210
    static __int64 __cdecl GetMasteryExp(char);  // 0x62c2b0
    static ::Data::GradeBenefit * __cdecl GetGradeBenefitList(int);  // 0x62c300
    static char __cdecl GetWeaponBrandMaxGemSlotCount(unsigned __int64);  // 0x62c370
private:
    bool __cdecl loadSoulNpcSkill(void);  // 0x62c3e0
    bool __cdecl getNextSoulNpcSkills(unsigned __int64, char *const);  // 0x62c740
    unsigned __int64 __cdecl loadHiddenFieldZoneConvoy(void);  // 0x62fad0
    unsigned __int64 __cdecl loadHiddenFieldZoneNpcSquad(void);  // 0x62fc90
    unsigned __int64 __cdecl loadHiddenFieldFromFriendNotiLocation(void);  // 0x62ffd0
    unsigned __int64 __cdecl loadHiddenFieldFromAchievement(void);  // 0x6301e0
    unsigned __int64 __cdecl loadHiddenFieldFromAchievementRegister(void);  // 0x630840
    unsigned __int64 __cdecl loadHiddenFieldFromBotScoringDestination(void);  // 0x630ee0
    unsigned __int64 __cdecl loadHiddenFieldFromNewbieCare(void);  // 0x631120
    unsigned __int64 __cdecl loadHiddenFieldFromFishingField(void);  // 0x631380
    unsigned __int64 __cdecl loadHiddenFieldFromItemBrand(void);  // 0x631c00
    unsigned __int64 __cdecl loadHiddenFieldFromContentsReset(void);  // 0x632410
public:
    static bool __cdecl IsValidCombatSeasonContentsType(char);  // 0x632730
    static int __cdecl GetCombatSeasonContentsTypeCount(void);  // 0x6327a0
    static bool __cdecl IsWarFieldMainZone(unsigned int);  // 0x632820
    static int __cdecl GetBattleRoyalFieldScoreConversion(char, char, int);  // 0x6328e0
    static char __cdecl GetGameModeFromArenaMatchingRuleDetailType(char, char);  // 0x632990
private:
    bool __cdecl ConstructItemUsableKeyMap(void);  // 0x632a70
public:
    bool __cdecl IsItemUsable(unsigned __int64, unsigned __int64, bool &);  // 0x632d70
private:
    bool __cdecl ConstructDuelBotTrainingRoomVersion(void);  // 0x633010
    bool __cdecl ConstructRandomDistributionAccumulated(void);  // 0x633110
public:
    bool __cdecl GetRandRangeByDistribution(unsigned __int64, int &, int &);  // 0x6332b0
    int __cdecl GetNextSeasonContentsDefaultRatingScore(char, int);  // 0x633410
    bool __cdecl FindSkillChildren(int, int *const, int &);  // 0x633490
    bool __cdecl FindSkill3Keys(int, __int64 *const, int &);  // 0x6335b0
private:
    void __cdecl addSkillAchievementEvent(int *, bool *, int, short);  // 0x633710
    void __cdecl addSkillVariationAchievementEvent(int, short);  // 0x633960
    unsigned __int64 __cdecl loadHiddenFieldFromCave2(void);  // 0x633a80
    unsigned __int64 __cdecl loadHiddenFieldFromFieldZone(void);  // 0x633c40
    unsigned __int64 __cdecl loadHiddenFieldFromJackpotBossZone(void);  // 0x633e00
    unsigned __int64 __cdecl loadHiddenFieldFromClassicFieldZone(void);  // 0x633fa0
    unsigned __int64 __cdecl loadHiddenFieldFromDungeon(void);  // 0x634160
    unsigned __int64 __cdecl loadHiddenFieldFromRaidDungeon(void);  // 0x634980
    unsigned __int64 __cdecl loadHiddenFieldFromBossChallenge(void);  // 0x634f50
    unsigned __int64 __cdecl loadHiddenFieldFromCraftRecipe(void);  // 0x6353f0
    unsigned __int64 __cdecl loadHiddenFieldFromTencentQuest(void);  // 0x635990
    unsigned __int64 __cdecl loadHiddenFieldFromArenaPortal(void);  // 0x635b10
    unsigned __int64 __cdecl loadHiddenFieldFromDuel(void);  // 0x635f50
    unsigned __int64 __cdecl loadHiddenFieldFromDuelBotGroup(void);  // 0x6360f0
    unsigned __int64 __cdecl loadHiddenFieldFromFactionBattleFieldZone(void);  // 0x6361b0
    unsigned __int64 __cdecl loadHiddenFieldFromGuildBattleFieldZone(void);  // 0x636350
    unsigned __int64 __cdecl loadHiddenFieldFromMasteryLevel(void);  // 0x636570
    unsigned __int64 __cdecl loadHiddenFieldFromMessageByItemDistrict(void);  // 0x636830
    unsigned __int64 __cdecl loadHiddenFieldFromPartyBattleFieldZone(void);  // 0x636a40
    unsigned __int64 __cdecl loadHiddenFieldFromWeeklyTimeTable(void);  // 0x636bf0
    unsigned __int64 __cdecl setWeelyTimeTableBitsByData(::Data::WeeklyTimeTableRecordPtr, char *);  // 0x636d70
    unsigned __int64 __cdecl loadHiddenFieldFromDuelBotChallenge(void);  // 0x637340
    unsigned __int64 __cdecl loadHiddenFieldFromDuelBotTrainingRoom(void);  // 0x6377a0
    unsigned __int64 __cdecl loadHiddenFieldFromWeaponAppearanceChangeCost(void);  // 0x637a40
    unsigned __int64 __cdecl loadHiddenFieldFromRankingGroupReward(void);  // 0x637c30
    unsigned __int64 __cdecl loadHiddenFieldFromRankingReward(void);  // 0x637eb0
    unsigned __int64 __cdecl loadHiddenFieldFromRankingPvEStage(void);  // 0x638380
    unsigned __int64 __cdecl loadHiddenFieldFromTendencyField(bool);  // 0x6386e0
    unsigned __int64 __cdecl loadHiddenFieldFromSkillTrainingRoom(void);  // 0x63a1a0
    unsigned __int64 __cdecl loadHiddenFieldFromSkillTrainingRoomGroup(void);  // 0x63a470
    unsigned __int64 __cdecl loadHiddenFieldFromDefaultRatingScoreGroup(void);  // 0x63a690
    unsigned __int64 __cdecl loadHiddenFieldFromPublicRaid(void);  // 0x63a800
    unsigned __int64 __cdecl loadHiddenFieldFromBattleRoyalField(void);  // 0x63aac0
    unsigned __int64 __cdecl loadHiddenFieldFromWarField(void);  // 0x63b070
    unsigned __int64 __cdecl loadHiddenFieldFromSimpleField(void);  // 0x63be30
    unsigned __int64 __cdecl loadHiddenFieldFromSeasonContentsSchedule(void);  // 0x63c060
    unsigned __int64 __cdecl loadHiddenFieldFromChallengeParty(void);  // 0x63c7d0
    unsigned __int64 __cdecl loadHiddenFieldFromMentoring(void);  // 0x63cdb0
    unsigned __int64 __cdecl loadHiddenFieldFromRandomStoreDrawReward(void);  // 0x63ce80
    unsigned __int64 __cdecl loadHiddenFieldFromSecretTreaure(void);  // 0x63d2c0
    unsigned __int64 __cdecl loadHiddenFieldFromSkillBuildUp(void);  // 0x63d5a0
    unsigned __int64 __cdecl loadHiddenFieldFromSkill3(void);  // 0x63d9c0
    unsigned __int64 __cdecl loadHiddenFieldFromFishingPaste(void);  // 0x63df10
    unsigned __int64 __cdecl loadHiddenFieldFromPc(void);  // 0x63e270
    unsigned __int64 __cdecl loadHiddenFieldFromBadgeSetItem(void);  // 0x63e470
    unsigned __int64 __cdecl loadHiddenFieldFromBadgeSynthesisCost(void);  // 0x63e5d0
    unsigned __int64 __cdecl loadHiddenFieldFromBadgeSynthesisRecipe(void);  // 0x63e720
    bool __cdecl makeBadgeSynthesisResultDataPacket(void);  // 0x63eb40
    unsigned __int64 __cdecl loadHiddenFieldFromJumpingCharacter2(void);  // 0x63ef30
    unsigned __int64 __cdecl loadHiddenFieldFromJumpingQuest2(void);  // 0x63f3c0
    unsigned __int64 __cdecl loadHiddenFieldFromJumpingTeleport2(void);  // 0x63f5f0
    unsigned __int64 __cdecl loadHiddenFieldFromNpc(void);  // 0x63f770
    unsigned __int64 __cdecl loadHiddenFieldFromChallengeList(void);  // 0x63f8b0
    unsigned __int64 __cdecl loadHiddenFieldFromItemFusion(void);  // 0x63f9b0
    unsigned __int64 __cdecl validateGeoZone(void);  // 0x640450
    unsigned __int64 __cdecl validateQuest(void);  // 0x64bed0
public:
    static bool __cdecl SetChallengeListWeekStartDateTime(__int64);  // 0x653180
private:
    unsigned __int64 __cdecl validateBattleRoyalFieldEffectPouch(void);  // 0x658bb0
    ::Data::AcquireSkillByQuestMission * __cdecl getAcquireSkillByQuestMission(unsigned short, unsigned short);  // 0x65fd10
    bool __cdecl constructMainFactionId(void);  // 0x65fe60
    char __cdecl getMaxWeaponGemSlot(::dr_tref const &, wchar_t const *, char);  // 0x660020
    bool __cdecl checkKeepWeaponGemSlot(::Data::ItemTransformRecipeRecordPtr &);  // 0x6604f0
    bool __cdecl checkKeepWeaponAppearance(::Data::ItemTransformRecipeRecordPtr &);  // 0x660a10
public:
    bool __cdecl IsInWeeklyTime(unsigned __int64);  // 0x6612a0
    __int64 __cdecl GetNearbyWeeklyTime(unsigned __int64);  // 0x661460
    bool __cdecl checkDuplicatedWeeklyTimeTable(wchar_t const *, unsigned __int64 *const, int);  // 0x6616e0
    void __cdecl AddArenaDaemonPersistentZone(int);  // 0x6618b0
    int __cdecl GetDifficultyTypeDataIndex(char);  // 0x6621b0
private:
    unsigned __int64 __cdecl loadHiddenFieldFromBoastEvent(void);  // 0x662210
    bool __cdecl setBoastEventSubTypeRecord(::Data::BoastEventRecordPtr);  // 0x662300
public:
    static bool __cdecl GetAbilityFieldValueByBenifitAbilitySeq(char, int, unsigned short &, unsigned short &, __int64 &, short &);  // 0x6626b0
    static char __cdecl GetChallengeTypeDay(void);  // 0x662910
    static char __cdecl GetChallengeTypeWeek(void);  // 0x662990
    void __cdecl WriteDataReaderErrorLog(wchar_t const *, int, wchar_t const *, ...);  // 0x662a10
    void __cdecl WriteScriptLoaderErrorLog(wchar_t const *, int, wchar_t const *, ...);  // 0x662a80
    void __cdecl WriteDataLoadErrorLog(wchar_t const *, int, wchar_t const *, ...);  // 0x662ab0
    void __cdecl WriteDataValidationFailureLog(wchar_t const *, int, wchar_t const *, ...);  // 0x662ae0
    bool __cdecl ConstructAdditionalServiceItems(void);  // 0x662b10
};
}
static_assert(sizeof(Data::DataManager) == 0xD6E8, "sizeof Data::DataManager");
static_assert(offsetof(Data::DataManager, _reader) == 0x0, "Data::DataManager::_reader");
static_assert(offsetof(Data::DataManager, _aliasMap) == 0x8, "Data::DataManager::_aliasMap");
static_assert(offsetof(Data::DataManager, _elreader) == 0x10, "Data::DataManager::_elreader");
static_assert(offsetof(Data::DataManager, _loaderDefs) == 0x18, "Data::DataManager::_loaderDefs");
static_assert(offsetof(Data::DataManager, _combatSequence) == 0x63D8, "Data::DataManager::_combatSequence");
static_assert(offsetof(Data::DataManager, _actSequence) == 0x63E0, "Data::DataManager::_actSequence");
static_assert(offsetof(Data::DataManager, _quest) == 0x63E8, "Data::DataManager::_quest");
static_assert(offsetof(Data::DataManager, _script) == 0x63F0, "Data::DataManager::_script");
static_assert(offsetof(Data::DataManager, _geoWorld) == 0x63F8, "Data::DataManager::_geoWorld");
static_assert(offsetof(Data::DataManager, _filterFactory) == 0x6400, "Data::DataManager::_filterFactory");
static_assert(offsetof(Data::DataManager, _reactionFactory) == 0x6408, "Data::DataManager::_reactionFactory");
static_assert(offsetof(Data::DataManager, _expTable) == 0x6410, "Data::DataManager::_expTable");
static_assert(offsetof(Data::DataManager, _levelDataTable) == 0x6418, "Data::DataManager::_levelDataTable");
static_assert(offsetof(Data::DataManager, _exceedLevelDataList) == 0x6420, "Data::DataManager::_exceedLevelDataList");
static_assert(offsetof(Data::DataManager, _exceedLevelDataListCount) == 0x6428, "Data::DataManager::_exceedLevelDataListCount");
static_assert(offsetof(Data::DataManager, _exceedLevelFirstLevel) == 0x642C, "Data::DataManager::_exceedLevelFirstLevel");
static_assert(offsetof(Data::DataManager, _masteryExpTable) == 0x6430, "Data::DataManager::_masteryExpTable");
static_assert(offsetof(Data::DataManager, _accountExpTable) == 0x6438, "Data::DataManager::_accountExpTable");
static_assert(offsetof(Data::DataManager, _accountLevelDataTable) == 0x6440, "Data::DataManager::_accountLevelDataTable");
static_assert(offsetof(Data::DataManager, _rootDataPath) == 0x6448, "Data::DataManager::_rootDataPath");
static_assert(offsetof(Data::DataManager, _zoneRootDataPath) == 0x6650, "Data::DataManager::_zoneRootDataPath");
static_assert(offsetof(Data::DataManager, _scriptRootDataPath) == 0x6858, "Data::DataManager::_scriptRootDataPath");
static_assert(offsetof(Data::DataManager, _questRootDataPath) == 0x6A60, "Data::DataManager::_questRootDataPath");
static_assert(offsetof(Data::DataManager, _terrainRootDataPath) == 0x6C68, "Data::DataManager::_terrainRootDataPath");
static_assert(offsetof(Data::DataManager, _socialRootDataPath) == 0x6E70, "Data::DataManager::_socialRootDataPath");
static_assert(offsetof(Data::DataManager, _zipFileDataPath) == 0x7078, "Data::DataManager::_zipFileDataPath");
static_assert(offsetof(Data::DataManager, _mainFactionCount) == 0x7280, "Data::DataManager::_mainFactionCount");
static_assert(offsetof(Data::DataManager, _mainFactionIds) == 0x7288, "Data::DataManager::_mainFactionIds");
static_assert(offsetof(Data::DataManager, _gemGearScoreCount) == 0x7290, "Data::DataManager::_gemGearScoreCount");
static_assert(offsetof(Data::DataManager, _gemCardGearScoreCount) == 0x7294, "Data::DataManager::_gemCardGearScoreCount");
static_assert(offsetof(Data::DataManager, _gemGearScoreTable) == 0x7298, "Data::DataManager::_gemGearScoreTable");
static_assert(offsetof(Data::DataManager, _gemCardGearScoreTable) == 0x72A0, "Data::DataManager::_gemCardGearScoreTable");
static_assert(offsetof(Data::DataManager, _arenaDungeonZoneIdCapacity) == 0x72A8, "Data::DataManager::_arenaDungeonZoneIdCapacity");
static_assert(offsetof(Data::DataManager, _arenaDungeonZoneIdCount) == 0x72AC, "Data::DataManager::_arenaDungeonZoneIdCount");
static_assert(offsetof(Data::DataManager, _arenaDungeonZoneIds) == 0x72B0, "Data::DataManager::_arenaDungeonZoneIds");
static_assert(offsetof(Data::DataManager, _arenaDuelZoneIdCapacity) == 0x72B8, "Data::DataManager::_arenaDuelZoneIdCapacity");
static_assert(offsetof(Data::DataManager, _arenaDuelZoneIdCount) == 0x72BC, "Data::DataManager::_arenaDuelZoneIdCount");
static_assert(offsetof(Data::DataManager, _arenaDuelZoneIds) == 0x72C0, "Data::DataManager::_arenaDuelZoneIds");
static_assert(offsetof(Data::DataManager, _vitalityBenefitGradeKey) == 0x72C8, "Data::DataManager::_vitalityBenefitGradeKey");
static_assert(offsetof(Data::DataManager, _quotaKeyRecordListCount) == 0x72CC, "Data::DataManager::_quotaKeyRecordListCount");
static_assert(offsetof(Data::DataManager, _quotaKeyRecordList) == 0x72D0, "Data::DataManager::_quotaKeyRecordList");
static_assert(offsetof(Data::DataManager, _zoneBroadcastSocialActionNpc) == 0x72D8, "Data::DataManager::_zoneBroadcastSocialActionNpc");
static_assert(offsetof(Data::DataManager, _zoneBroadcastSocialActionNpc2) == 0x72E0, "Data::DataManager::_zoneBroadcastSocialActionNpc2");
static_assert(offsetof(Data::DataManager, _bossHpZoneBroadcastGeoZoneId) == 0x72E8, "Data::DataManager::_bossHpZoneBroadcastGeoZoneId");
static_assert(offsetof(Data::DataManager, _challengeListWeekStartDateTime) == 0x72F0, "Data::DataManager::_challengeListWeekStartDateTime");
static_assert(offsetof(Data::DataManager, _challengeListWeekCount) == 0x72F8, "Data::DataManager::_challengeListWeekCount");
static_assert(offsetof(Data::DataManager, _skillByQuestMissionList) == 0x7300, "Data::DataManager::_skillByQuestMissionList");
static_assert(offsetof(Data::DataManager, _weeklyTimeTableList) == 0x7320, "Data::DataManager::_weeklyTimeTableList");
static_assert(offsetof(Data::DataManager, _weeklyTimeMinuteTableList) == 0x7340, "Data::DataManager::_weeklyTimeMinuteTableList");
static_assert(offsetof(Data::DataManager, _battleRoyalFieldJobStyleRestrictionList) == 0x7360, "Data::DataManager::_battleRoyalFieldJobStyleRestrictionList");
static_assert(offsetof(Data::DataManager, _arenaDaemonPersistentZoneList) == 0x7378, "Data::DataManager::_arenaDaemonPersistentZoneList");
static_assert(offsetof(Data::DataManager, _skillChildrenMap) == 0x7390, "Data::DataManager::_skillChildrenMap");
static_assert(offsetof(Data::DataManager, _skillVariationMap) == 0x73B0, "Data::DataManager::_skillVariationMap");
static_assert(offsetof(Data::DataManager, _gradeBenefitListMap) == 0x73D0, "Data::DataManager::_gradeBenefitListMap");
static_assert(offsetof(Data::DataManager, _weaponBrandMaxGemSlotCountMap) == 0x73F0, "Data::DataManager::_weaponBrandMaxGemSlotCountMap");
static_assert(offsetof(Data::DataManager, _enableSouNpcSkill) == 0x7410, "Data::DataManager::_enableSouNpcSkill");
static_assert(offsetof(Data::DataManager, _soulNpcSkills) == 0x7418, "Data::DataManager::_soulNpcSkills");
static_assert(offsetof(Data::DataManager, _itemUsableRelationKeyMap) == 0x7420, "Data::DataManager::_itemUsableRelationKeyMap");
static_assert(offsetof(Data::DataManager, _itemUsableRelationAttractionGroupMap) == 0x7440, "Data::DataManager::_itemUsableRelationAttractionGroupMap");
static_assert(offsetof(Data::DataManager, _duelBotChallengeDispelEffectType) == 0x7460, "Data::DataManager::_duelBotChallengeDispelEffectType");
static_assert(offsetof(Data::DataManager, _skillTrainingRoomRemainEffectType) == 0x76E2, "Data::DataManager::_skillTrainingRoomRemainEffectType");
static_assert(offsetof(Data::DataManager, _challengePartyAttractionRemainEffectType) == 0x7964, "Data::DataManager::_challengePartyAttractionRemainEffectType");
static_assert(offsetof(Data::DataManager, _skillTrainingRoomAttractionKey) == 0x7BE8, "Data::DataManager::_skillTrainingRoomAttractionKey");
static_assert(offsetof(Data::DataManager, _publicRaidAttractionKey) == 0x7BEC, "Data::DataManager::_publicRaidAttractionKey");
static_assert(offsetof(Data::DataManager, _challengePartyAttractionKey) == 0x7BF0, "Data::DataManager::_challengePartyAttractionKey");
static_assert(offsetof(Data::DataManager, _battleRoyalFieldAttractionKey) == 0x7BF8, "Data::DataManager::_battleRoyalFieldAttractionKey");
static_assert(offsetof(Data::DataManager, _duelBotTrainingRoomVersion) == 0x7BFC, "Data::DataManager::_duelBotTrainingRoomVersion");
static_assert(offsetof(Data::DataManager, _newbieInfoFlag) == 0x7C00, "Data::DataManager::_newbieInfoFlag");
static_assert(offsetof(Data::DataManager, _randomDistributionKeyMap) == 0x7C08, "Data::DataManager::_randomDistributionKeyMap");
static_assert(offsetof(Data::DataManager, _mentoringRecordPtr) == 0x7C28, "Data::DataManager::_mentoringRecordPtr");
static_assert(offsetof(Data::DataManager, _mentoringEnableVersion) == 0x7C30, "Data::DataManager::_mentoringEnableVersion");
static_assert(offsetof(Data::DataManager, _mentoringLastVersion) == 0x7C32, "Data::DataManager::_mentoringLastVersion");
static_assert(offsetof(Data::DataManager, _jumpingCharacterData) == 0x7C38, "Data::DataManager::_jumpingCharacterData");
static_assert(offsetof(Data::DataManager, _jumpingCharacterData2) == 0x8130, "Data::DataManager::_jumpingCharacterData2");
static_assert(offsetof(Data::DataManager, _noneSpecifyObjectQuest) == 0x8208, "Data::DataManager::_noneSpecifyObjectQuest");
static_assert(offsetof(Data::DataManager, _pvpDifficultyTypePtr) == 0x85C8, "Data::DataManager::_pvpDifficultyTypePtr");
static_assert(offsetof(Data::DataManager, _defaultDifficultyTypePtr) == 0x85D0, "Data::DataManager::_defaultDifficultyTypePtr");
static_assert(offsetof(Data::DataManager, _defaultDifficultyTypeId) == 0x85D8, "Data::DataManager::_defaultDifficultyTypeId");
static_assert(offsetof(Data::DataManager, _defaultDifficultyTypeDataIdx) == 0x85DC, "Data::DataManager::_defaultDifficultyTypeDataIdx");
static_assert(offsetof(Data::DataManager, _boastEventMap) == 0x85E0, "Data::DataManager::_boastEventMap");
static_assert(offsetof(Data::DataManager, _parallelLoad) == 0x86A0, "Data::DataManager::_parallelLoad");
static_assert(offsetof(Data::DataManager, _dataReaderErrorLogFileLock) == 0x86A8, "Data::DataManager::_dataReaderErrorLogFileLock");
static_assert(offsetof(Data::DataManager, _dataReaderErrorLogFile) == 0x86D0, "Data::DataManager::_dataReaderErrorLogFile");
static_assert(offsetof(Data::DataManager, _scriptLoaderErrorLogFile) == 0x86D8, "Data::DataManager::_scriptLoaderErrorLogFile");
static_assert(offsetof(Data::DataManager, _dataLoadErrorLogFile) == 0x86E0, "Data::DataManager::_dataLoadErrorLogFile");
static_assert(offsetof(Data::DataManager, _dataValidationFailureLogFile) == 0x86E8, "Data::DataManager::_dataValidationFailureLogFile");
static_assert(offsetof(Data::DataManager, _rankingPvEStageStartInfoMap) == 0x86F0, "Data::DataManager::_rankingPvEStageStartInfoMap");
static_assert(offsetof(Data::DataManager, _RandomStoreDrawRewardSet) == 0x8710, "Data::DataManager::_RandomStoreDrawRewardSet");
static_assert(offsetof(Data::DataManager, _firstRandomStoreDrawRewardRequiredDrawCount) == 0x8730, "Data::DataManager::_firstRandomStoreDrawRewardRequiredDrawCount");
static_assert(offsetof(Data::DataManager, _lastRandomStoreDrawRewardRequiredDrawCount) == 0x8738, "Data::DataManager::_lastRandomStoreDrawRewardRequiredDrawCount");
static_assert(offsetof(Data::DataManager, _totalRandomStoreDrawRewardRequiredDrawCount) == 0x8740, "Data::DataManager::_totalRandomStoreDrawRewardRequiredDrawCount");
static_assert(offsetof(Data::DataManager, _droppedPouchPos) == 0x8748, "Data::DataManager::_droppedPouchPos");
static_assert(offsetof(Data::DataManager, _droppedPouchPosCount) == 0xD57C, "Data::DataManager::_droppedPouchPosCount");
static_assert(offsetof(Data::DataManager, _elevationJobStyleQuestList) == 0xD580, "Data::DataManager::_elevationJobStyleQuestList");
static_assert(offsetof(Data::DataManager, _badgeSetItemScoreUnitSize) == 0xD5A0, "Data::DataManager::_badgeSetItemScoreUnitSize");
static_assert(offsetof(Data::DataManager, _badgeSynthesisScoreUnitSize) == 0xD5A4, "Data::DataManager::_badgeSynthesisScoreUnitSize");
static_assert(offsetof(Data::DataManager, _badgeSynthesisResultDataPacket) == 0xD5A8, "Data::DataManager::_badgeSynthesisResultDataPacket");
static_assert(offsetof(Data::DataManager, _maxBadge1SynthesisScore) == 0xD6A0, "Data::DataManager::_maxBadge1SynthesisScore");
static_assert(offsetof(Data::DataManager, _maxBadge2SynthesisScore) == 0xD6A4, "Data::DataManager::_maxBadge2SynthesisScore");
static_assert(offsetof(Data::DataManager, _maxBadge3SynthesisScore) == 0xD6A8, "Data::DataManager::_maxBadge3SynthesisScore");
static_assert(offsetof(Data::DataManager, _additionalServiceItems) == 0xD6B0, "Data::DataManager::_additionalServiceItems");
static_assert(offsetof(Data::DataManager, _boardGachaData) == 0xD6B8, "Data::DataManager::_boardGachaData");
static_assert(offsetof(Data::DataManager, _slatecaches) == 0xD6C0, "Data::DataManager::_slatecaches");
static_assert(offsetof(Data::DataManager, _formulaConstantData) == 0xD6D0, "Data::DataManager::_formulaConstantData");
static_assert(offsetof(Data::DataManager, _itemFusionScoreUnitSize) == 0xD6D8, "Data::DataManager::_itemFusionScoreUnitSize");
static_assert(offsetof(Data::DataManager, _maxItemFusionScores) == 0xD6E0, "Data::DataManager::_maxItemFusionScores");
static_assert(sizeof(Data::DataManager::DroppedPouchPosInfo) == 0x7D2, "sizeof Data::DataManager::DroppedPouchPosInfo");
static_assert(offsetof(Data::DataManager::DroppedPouchPosInfo, posCount) == 0x0, "Data::DataManager::DroppedPouchPosInfo::posCount");
static_assert(offsetof(Data::DataManager::DroppedPouchPosInfo, pos) == 0x2, "Data::DataManager::DroppedPouchPosInfo::pos");
static_assert(sizeof(Data::DataManager::PvEStageStartInfoID) == 0x10, "sizeof Data::DataManager::PvEStageStartInfoID");
static_assert(offsetof(Data::DataManager::PvEStageStartInfoID, attraction) == 0x0, "Data::DataManager::PvEStageStartInfoID::attraction");
static_assert(offsetof(Data::DataManager::PvEStageStartInfoID, attractionKey) == 0x8, "Data::DataManager::PvEStageStartInfoID::attractionKey");
static_assert(sizeof(Data::DataManager::RandomStoreDrawRewardID) == 0x8, "sizeof Data::DataManager::RandomStoreDrawRewardID");
static_assert(offsetof(Data::DataManager::RandomStoreDrawRewardID, _randomStoreNumber) == 0x0, "Data::DataManager::RandomStoreDrawRewardID::_randomStoreNumber");
static_assert(offsetof(Data::DataManager::RandomStoreDrawRewardID, _accumulatedRequiredDrawCount) == 0x4, "Data::DataManager::RandomStoreDrawRewardID::_accumulatedRequiredDrawCount");
static_assert(sizeof(Data::DataManager::RankingPvEStageStartInfo) == 0x18, "sizeof Data::DataManager::RankingPvEStageStartInfo");
static_assert(offsetof(Data::DataManager::RankingPvEStageStartInfo, id) == 0x0, "Data::DataManager::RankingPvEStageStartInfo::id");
static_assert(offsetof(Data::DataManager::RankingPvEStageStartInfo, seasonContentsType) == 0x10, "Data::DataManager::RankingPvEStageStartInfo::seasonContentsType");

namespace Data {
class DataStaticMemoryManager
{
public:
    virtual void * __cdecl Alloc(unsigned __int64, wchar_t const *, int);  // 0x616f60
    virtual void * __cdecl Realloc(void *, unsigned __int64, wchar_t const *, int);  // 0x616f70
    virtual void __cdecl Free(void *, wchar_t const *, int);  // 0x616f90
};
}

namespace Data {
class GamedGeoDataLog
{
private:
    virtual void __cdecl WriteErrorV(wchar_t const *, char *) const;  // 0x617060
    virtual void __cdecl WriteDebugV(wchar_t const *, char *) const;  // 0x617090
    virtual void __cdecl WriteTraceV(wchar_t const *, char *) const;  // 0x6170c0
};
}

namespace Data {
class JumpingCharacterData
{
public:
    __cdecl JumpingCharacterData(void);  // 0x617320
    __cdecl ~JumpingCharacterData(void);  // 0x617490
private:
    bool __cdecl addJumpingQuest(char, short);  // 0x617500
    bool __cdecl addJumpingTeleport(char, short);  // 0x617630
    bool __cdecl addJumpingCharacter(char, ::Data::JumpingCharacterRecord const *);  // 0x617760
    bool __cdecl addJumpingTutorialZone(char, unsigned int);  // 0x617880
};
}

namespace Data {
class JumpingCharacterData2
{
public:
    __cdecl JumpingCharacterData2(void);  // 0x6179a0
    __cdecl ~JumpingCharacterData2(void);  // 0x617a90
    bool __cdecl AddJumpingCharacterQuestsToComplete(::Quest const *, ::Quest const *);  // 0x617b10
    bool __cdecl AddJumpingQuest(char, short);  // 0x617f20
    bool __cdecl AddJumpingTeleport(short);  // 0x6181b0
};
}

namespace Data {
class NoneSpecifyObjectQuestForwarding
{
public:
    bool __cdecl AddNoneSpecifyObjectQuestForwardingInfo(short, char, unsigned __int64, char, char, short, unsigned __int64, unsigned __int64);  // 0x617290
};
}

namespace Data {
class SlateRelationCache
{
public:
    __cdecl ~SlateRelationCache(void);  // 0x618280
private:
    void __cdecl init(__int64);  // 0x6182f0
    void __cdecl addStoneCache(__int64, short, char);  // 0x618390
};
}

namespace Data {
class XmlReaderLogger
{
public:
    virtual void __cdecl Error(wchar_t const *, ...) const;  // 0x6170f0
    virtual void __cdecl Debug(wchar_t const *, ...) const;  // 0x617130
    virtual void __cdecl Trace(wchar_t const *, ...) const;  // 0x617170
};
}

namespace Data {
void __cdecl WriteDataManagerLog(::Log::Type, wchar_t const *, int, wchar_t const *, char *);  // 0x616fb0
void __cdecl insertQuestErrorLog(wchar_t const *, int, char, unsigned __int64, char, char, wchar_t const *, wchar_t const *, ...);  // 0x620b20
void __cdecl insertQuest(::Data::QuestForwarding &, char, unsigned __int64, char, char, short);  // 0x620c40
void __cdecl insertQuestConvoy(::Data::ZoneConvoyRecord *, unsigned __int64, char, char, char, short);  // 0x620d30
void __cdecl insertQuestFactionPcKill(::Data::ZoneRecordPtr, unsigned __int64, char, char, char, short, unsigned __int64);  // 0x620de0
void __cdecl insertQuestAttraction(unsigned __int64 *, int, unsigned __int64, ::dr_tref);  // 0x620ec0
void __cdecl setDungeonInQuest(unsigned __int64 &, unsigned __int64, char);  // 0x620f50
unsigned __int64 __cdecl getNpcScriptId(unsigned __int64);  // 0x621120
unsigned __int64 __cdecl getEnvScriptId(unsigned __int64);  // 0x621180
unsigned __int64 __cdecl getZoneScriptId(unsigned __int64);  // 0x6211c0
bool __cdecl insertQuest(::QuestCase &, char, unsigned __int64, char, char);  // 0x621200
bool __cdecl checkNextQuestConfliction(::Data::QuestNextQuest *, ::Data::QuestAcquisition *, ::Data::QuestQuest *);  // 0x623710
void __cdecl checkZoneAndPcSpawn(::Data::ZoneRecordPtr, int, int);  // 0x6237d0
::Data::QuestDecision const * __cdecl getQuestDecisionFromZoneArray(int, unsigned __int64 *, wchar_t const *);  // 0x623830
void __cdecl linkQuestTransitAndZone(::Transit *, unsigned short, int, ::Quest const *);  // 0x6238f0
bool __cdecl postprocNpc(::DrEl *);  // 0x62c910
bool __cdecl postprocNpcBrainParameters(::DrEl *);  // 0x62c980
bool __cdecl postprocItem(::DrEl *);  // 0x62ca10
bool __cdecl postprocReward(::DrEl *);  // 0x62d390
bool __cdecl postprocItemTransformUpgradeItem(::DrEl *);  // 0x62da90
bool __cdecl postprocExpandInventoryData(::DrEl *);  // 0x62dba0
bool __cdecl postprocDuelBotEquippedItem(::DrEl *);  // 0x62dc10
bool __cdecl postprocGrade(::DrEl *);  // 0x62dc50
bool __cdecl postprocNpcConvoy(::DrEl *);  // 0x62ddf0
bool __cdecl postprocRandomStore(::DrEl *);  // 0x62de60
bool __cdecl postprocRandomStoreItem(::DrEl *);  // 0x62e260
bool __cdecl postprocRandomStoreItemGroup(::DrEl *);  // 0x62e4e0
bool __cdecl postprocRandomStoreProbGroup(::DrEl *);  // 0x62e6f0
bool __cdecl postprocRankingPvEStage(::DrEl *);  // 0x62ef50
bool __cdecl postprocExpandRandomStore(::DrEl *);  // 0x62f140
bool __cdecl postprocZoneTriggerEventStage(::DrEl *);  // 0x62f2b0
bool __cdecl postprocSummoned(::DrEl *);  // 0x62f5d0
bool __cdecl postprocSummonedDesignerPreset(::DrEl *);  // 0x62f600
bool __cdecl postprocAchievement(::DrEl *);  // 0x62f6c0
bool __cdecl postprocNewbieCare(::DrEl *);  // 0x62fa00
bool __cdecl postprocBoardGachaReward(::DrEl *);  // 0x62fa90
bool __cdecl checkWarFieldZone(::Data::ZoneRecordPtr, ::Data::WarFieldWarFieldZoneTypeType);  // 0x63aee0
bool __cdecl loadHiddenStopNextSkill(::Data::Skill3RecordActiveSkillPtr, unsigned __int64, wchar_t const *, char &);  // 0x63d740
unsigned __int64 __cdecl validateZoneAttraction(void);  // 0x63fc00
unsigned __int64 __cdecl validateArenaPortal(void);  // 0x63fdb0
unsigned __int64 __cdecl validateCave(void);  // 0x63ff90
unsigned __int64 __cdecl validateFieldZone(void);  // 0x640140
unsigned __int64 __cdecl validateJackpotBossZone(void);  // 0x6402e0
unsigned __int64 __cdecl validateMysteriousStore(void);  // 0x6416e0
unsigned __int64 __cdecl validateMysteriousStoreItemGroup(void);  // 0x6418c0
unsigned __int64 __cdecl validateMarketRegisterAmountTax(void);  // 0x641a90
unsigned __int64 __cdecl validateMasteryStatPoint(void);  // 0x641fa0
unsigned __int64 __cdecl validateRaidDungeon(void);  // 0x6423f0
unsigned __int64 __cdecl validateExp(void);  // 0x642530
unsigned __int64 __cdecl validateGuildAction(void);  // 0x642b00
unsigned __int64 __cdecl validateGuildDiscount(void);  // 0x642cf0
unsigned __int64 __cdecl validateGuildLevel(void);  // 0x642e80
unsigned __int64 __cdecl validateContentQuota(void);  // 0x642fa0
unsigned __int64 __cdecl validateGrade(void);  // 0x643500
unsigned __int64 __cdecl validatePcCafeBenefits(void);  // 0x643640
unsigned __int64 __cdecl validateInterDungeonList(void);  // 0x6438e0
unsigned __int64 __cdecl validateDuel(void);  // 0x643eb0
unsigned __int64 __cdecl validatePartyBattleFieldZone(void);  // 0x644330
unsigned __int64 __cdecl validateExpandRandomStore(void);  // 0x644690
unsigned __int64 __cdecl validateRandomStoreItemGroup(void);  // 0x6448f0
unsigned __int64 __cdecl validateRandomStoreProbGroup(void);  // 0x644f30
unsigned __int64 __cdecl validateRandomStore(void);  // 0x645330
unsigned __int64 __cdecl validateEffect(void);  // 0x645b80
unsigned __int64 __cdecl validateEnv(void);  // 0x646bf0
bool __cdecl isValidArea(::GeoZone const &, ::dr_box16, ::dr_box16 &);  // 0x6472b0
unsigned __int64 __cdecl validateZoneNpcSpawn(void);  // 0x647410
unsigned __int64 __cdecl validateChallengeParty(void);  // 0x647cb0
unsigned __int64 __cdecl validateSeasonContentsSchedule(void);  // 0x647ea0
unsigned __int64 __cdecl validateZoneTriggerEventCond(void);  // 0x648980
unsigned __int64 __cdecl validateItemTransformRecipe(void);  // 0x648b00
unsigned __int64 __cdecl validateItemUsableRelation(void);  // 0x649dd0
unsigned __int64 __cdecl validateWeaponGemTransformResult(void);  // 0x64a090
unsigned __int64 __cdecl validateZoneTriggerEventStage(void);  // 0x64a210
unsigned __int64 __cdecl validateZoneNpcSpawnEvent(void);  // 0x64a7f0
unsigned __int64 __cdecl validatePcInitialSetting(void);  // 0x64a950
unsigned __int64 __cdecl validatePcRaceSexJob(void);  // 0x64ab10
unsigned __int64 __cdecl validatePcSkill3(void);  // 0x64acf0
unsigned __int64 __cdecl validateNpcBrainParameters(void);  // 0x64ae30
bool __cdecl validateCombatSequenceBossSkill(::Data::CombatSequenceAction const *, wchar_t *&, char &);  // 0x64b360
unsigned __int64 __cdecl validateCombatSequence(void);  // 0x64b660
unsigned __int64 __cdecl validateConvoy(void);  // 0x64bc90
int __cdecl getRequiredSlotCountForReward(unsigned __int64);  // 0x64c730
unsigned __int64 __cdecl validateItem(void);  // 0x64c810
unsigned __int64 __cdecl validateItemRandomAbility(void);  // 0x650190
unsigned __int64 __cdecl validateTrainSkillVersion(void);  // 0x6504e0
unsigned __int64 __cdecl validateGuildBankItem(void);  // 0x650640
unsigned __int64 __cdecl validateGuildCraftRecipe(void);  // 0x650790
unsigned __int64 __cdecl validateGuildUniformComponent(void);  // 0x650b90
unsigned __int64 __cdecl validateGuildUniformParamTypeCategory(void);  // 0x650e50
unsigned __int64 __cdecl validateGuildUniformRegistrationQuota(void);  // 0x650ff0
unsigned __int64 __cdecl validateTeleport(void);  // 0x6511f0
unsigned __int64 __cdecl validatePartyMatch(void);  // 0x651380
unsigned __int64 __cdecl validateNpc(void);  // 0x6514d0
unsigned __int64 __cdecl validateBossNpc(void);  // 0x652110
unsigned __int64 __cdecl validateBossChallenge(void);  // 0x6523d0
unsigned __int64 __cdecl validateChallengeList(void);  // 0x6527c0
unsigned __int64 __cdecl validateMileagePlan(void);  // 0x6533c0
unsigned __int64 __cdecl validateWeaponAppearanceChangeCost(void);  // 0x6537e0
unsigned __int64 __cdecl validateJumpingCharacter(void);  // 0x653ef0
unsigned __int64 __cdecl validateJumpingQuest(void);  // 0x654530
unsigned __int64 __cdecl validateJumpingTeleport(void);  // 0x654760
unsigned __int64 __cdecl validateBotScoringCondition(void);  // 0x654910
unsigned __int64 __cdecl validateBotScoringLevel(void);  // 0x654c70
unsigned __int64 __cdecl validateAccountPostCharge(void);  // 0x654ff0
unsigned __int64 __cdecl validateDuelBot(void);  // 0x655200
unsigned __int64 __cdecl validateBattleFieldGrade(void);  // 0x655350
unsigned __int64 __cdecl validateDuelBotTrainingRoomReward(void);  // 0x655460
unsigned __int64 __cdecl validateDefaultRatingScoreGroup(void);  // 0x655900
unsigned __int64 __cdecl validateDifficultyType(void);  // 0x655c80
unsigned __int64 __cdecl validateSkillTrainingRoomGroup(void);  // 0x655e70
unsigned __int64 __cdecl validateCraftCaseRecipe(void);  // 0x656200
unsigned __int64 __cdecl validateDuelMemberDisplaySkill(void);  // 0x656e00
unsigned __int64 __cdecl validatePublicRaid(void);  // 0x657010
unsigned __int64 __cdecl validatePublicRaidEvent(void);  // 0x6579c0
unsigned __int64 __cdecl validateBattleRoyalField(void);  // 0x657b70
unsigned __int64 __cdecl validateBattleRoyalFieldEvent(void);  // 0x658060
unsigned __int64 __cdecl validateAttractionReward(void);  // 0x659220
unsigned __int64 __cdecl validateSummonedLevel(void);  // 0x6594b0
unsigned __int64 __cdecl validateWarField(void);  // 0x6595a0
unsigned __int64 __cdecl validateZoneRule(void);  // 0x659880
unsigned __int64 __cdecl validateZoneCellAttribute(void);  // 0x659ae0
unsigned __int64 __cdecl validateSimpleField(void);  // 0x65a160
unsigned __int64 __cdecl validateSkillSkin(void);  // 0x65a3f0
unsigned __int64 __cdecl validateMentoring(void);  // 0x65a5b0
unsigned __int64 __cdecl validateZoneNpcSquad(void);  // 0x65a780
unsigned __int64 __cdecl validateCollecting(void);  // 0x65a950
unsigned __int64 __cdecl validateSkill3(void);  // 0x65b120
unsigned __int64 __cdecl validateSecretTreasure(void);  // 0x65b3e0
unsigned __int64 __cdecl validatePc(void);  // 0x65b480
unsigned __int64 __cdecl validateSkillBuildUp(void);  // 0x65b630
bool __cdecl validateSkillTraitEachJob(int);  // 0x65bc60
unsigned __int64 __cdecl validateSkillTrait(void);  // 0x65ccb0
unsigned __int64 __cdecl validateFish(void);  // 0x65cd50
unsigned __int64 __cdecl validateFishingField(void);  // 0x65cf80
unsigned __int64 __cdecl validateBadgeSetItem(void);  // 0x65d0b0
unsigned __int64 __cdecl validateBadgeSynthesisCost(void);  // 0x65d150
unsigned __int64 __cdecl validateBadgeSynthesisRecipe(void);  // 0x65d1f0
unsigned __int64 __cdecl validateClosetGroup(void);  // 0x65d330
unsigned __int64 __cdecl validateSkillSystematization(void);  // 0x65d660
unsigned __int64 __cdecl validateJobStyle(void);  // 0x65d8b0
unsigned __int64 __cdecl validateDifficultyTypeModify(void);  // 0x65daa0
unsigned __int64 __cdecl validateBoardGacha(void);  // 0x65dc50
unsigned __int64 __cdecl validateBoardGachaReward(void);  // 0x65dd70
unsigned __int64 __cdecl validateContentsReset(void);  // 0x65e190
unsigned __int64 __cdecl validateSlateScroll(void);  // 0x65e3d0
unsigned __int64 __cdecl validateSlateScrollStone(void);  // 0x65e6e0
unsigned __int64 __cdecl validateSlateStone(void);  // 0x65e8c0
unsigned __int64 __cdecl validateSoulMaskSet(void);  // 0x65ea20
unsigned __int64 __cdecl validateItemRandomOption(void);  // 0x65ec60
unsigned __int64 __cdecl validateCostGroup(void);  // 0x65f0d0
unsigned __int64 __cdecl validateZoneAreaGroup(void);  // 0x65f360
unsigned __int64 __cdecl validateZoneNpcRandomSpawn(void);  // 0x65f520
unsigned __int64 __cdecl validateSecondaryStat(void);  // 0x65f6a0
unsigned __int64 __cdecl validateFormulaConstant(void);  // 0x65f910
unsigned __int64 __cdecl validateItemFusion(void);  // 0x65fac0
bool __cdecl openXmlReader(::XmlReaderInterface &);  // 0x65fc30
unsigned __int64 __cdecl validateConfigPreDataLoad(void);  // 0x6619b0
}
