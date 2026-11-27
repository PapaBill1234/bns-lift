// datamanager_cpp_1.cpp: datamanager.cpp part 1 (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "datamanager.h"
#include "scripttable.h"
#include "LiftStub.h"

// 0x616f60
void * __cdecl Data::DataStaticMemoryManager::Alloc(unsigned __int64, wchar_t const *, int)
{
    LIFT_STUB(0x616f60);
}

// 0x616f70
void * __cdecl Data::DataStaticMemoryManager::Realloc(void *, unsigned __int64, wchar_t const *, int)
{
    LIFT_STUB(0x616f70);
}

// 0x616f90
void __cdecl Data::DataStaticMemoryManager::Free(void *, wchar_t const *, int)
{
    LIFT_STUB(0x616f90);
}

// 0x616fb0
void __cdecl Data::WriteDataManagerLog(::Log::Type, wchar_t const *, int, wchar_t const *, char *)
{
    LIFT_STUB(0x616fb0);
}

// 0x617060
void __cdecl Data::GamedGeoDataLog::WriteErrorV(wchar_t const *, char *) const
{
    LIFT_STUB(0x617060);
}

// 0x617090
void __cdecl Data::GamedGeoDataLog::WriteDebugV(wchar_t const *, char *) const
{
    LIFT_STUB(0x617090);
}

// 0x6170c0
void __cdecl Data::GamedGeoDataLog::WriteTraceV(wchar_t const *, char *) const
{
    LIFT_STUB(0x6170c0);
}

// 0x6170f0
void __cdecl Data::XmlReaderLogger::Error(wchar_t const *, ...) const
{
    LIFT_STUB(0x6170f0);
}

// 0x617130
void __cdecl Data::XmlReaderLogger::Debug(wchar_t const *, ...) const
{
    LIFT_STUB(0x617130);
}

// 0x617170
void __cdecl Data::XmlReaderLogger::Trace(wchar_t const *, ...) const
{
    LIFT_STUB(0x617170);
}

// 0x6171b0
void __cdecl Data::DataLogger::Write(::DrLog::Type, wchar_t const *, int, wchar_t const *, ...)
{
    LIFT_STUB(0x6171b0);
}

// 0x617290
bool __cdecl Data::NoneSpecifyObjectQuestForwarding::AddNoneSpecifyObjectQuestForwardingInfo(short, char, unsigned __int64, char, char, short, unsigned __int64, unsigned __int64)
{
    LIFT_STUB(0x617290);
}

// 0x617320
__cdecl Data::JumpingCharacterData::JumpingCharacterData(void)
{
    LIFT_STUB(0x617320);
}

// 0x617490
__cdecl Data::JumpingCharacterData::~JumpingCharacterData(void)
{
    LIFT_STUB(0x617490);
}

// 0x617500
bool __cdecl Data::JumpingCharacterData::addJumpingQuest(char, short)
{
    LIFT_STUB(0x617500);
}

// 0x617630
bool __cdecl Data::JumpingCharacterData::addJumpingTeleport(char, short)
{
    LIFT_STUB(0x617630);
}

// 0x617760
bool __cdecl Data::JumpingCharacterData::addJumpingCharacter(char, ::Data::JumpingCharacterRecord const *)
{
    LIFT_STUB(0x617760);
}

// 0x617880
bool __cdecl Data::JumpingCharacterData::addJumpingTutorialZone(char, unsigned int)
{
    LIFT_STUB(0x617880);
}

// 0x6179a0
__cdecl Data::JumpingCharacterData2::JumpingCharacterData2(void)
{
    LIFT_STUB(0x6179a0);
}

// 0x617a90
__cdecl Data::JumpingCharacterData2::~JumpingCharacterData2(void)
{
    LIFT_STUB(0x617a90);
}

// 0x617b10
bool __cdecl Data::JumpingCharacterData2::AddJumpingCharacterQuestsToComplete(::Quest const *, ::Quest const *)
{
    LIFT_STUB(0x617b10);
}

// 0x617f20
bool __cdecl Data::JumpingCharacterData2::AddJumpingQuest(char, short)
{
    LIFT_STUB(0x617f20);
}

// 0x6181b0
bool __cdecl Data::JumpingCharacterData2::AddJumpingTeleport(short)
{
    LIFT_STUB(0x6181b0);
}

// 0x618280
__cdecl Data::SlateRelationCache::~SlateRelationCache(void)
{
    LIFT_STUB(0x618280);
}

// 0x6182f0
void __cdecl Data::SlateRelationCache::init(__int64)
{
    LIFT_STUB(0x6182f0);
}

// 0x618390
void __cdecl Data::SlateRelationCache::addStoneCache(__int64, short, char)
{
    LIFT_STUB(0x618390);
}

// 0x618450
::Data::DataManager * __cdecl Data::DataManager::InitInstance(long, wchar_t const *)
{
    LIFT_STUB(0x618450);
}

// 0x618710
__cdecl Data::DataManager::DataManager(::DrDataReader *, ::DrAliasMap *, ::DrElReader *, wchar_t const *)
{
    LIFT_STUB(0x618710);
}

// 0x61e640
__cdecl Data::DataManager::~DataManager(void)
{
    LIFT_STUB(0x61e640);
}

// 0x61f330
void __cdecl Data::DataManager::CloseLog(void)
{
    LIFT_STUB(0x61f330);
}

// 0x61f4c0
void __cdecl Data::DataManager::FlushLog(void)
{
    LIFT_STUB(0x61f4c0);
}

// 0x61f560
bool __cdecl Data::DataManager::Load(::XmlReaderIO *, wchar_t const *)
{
    LIFT_STUB(0x61f560);
}

// 0x61f8f0
bool __cdecl Data::DataManager::loadData(::XmlReader const &, int)
{
    LIFT_STUB(0x61f8f0);
}

// 0x61fc80
bool __cdecl Data::DataManager::loadGeoData(::XmlReaderIO *)
{
    LIFT_STUB(0x61fc80);
}

// 0x61fe40
void __cdecl Data::DataManager::onConstructData(void)
{
    LIFT_STUB(0x61fe40);
}

// 0x61ff00
bool __cdecl Data::DataManager::checkToExistKeyFromAllTable(::Data::TableType, unsigned __int64, bool, bool)
{
    LIFT_STUB(0x61ff00);
}

// 0x620270
bool __cdecl Data::DataManager::constructData(void)
{
    LIFT_STUB(0x620270);
}

// 0x620b20
void __cdecl Data::insertQuestErrorLog(wchar_t const *, int, char, unsigned __int64, char, char, wchar_t const *, wchar_t const *, ...)
{
    LIFT_STUB(0x620b20);
}

// 0x620c40
void __cdecl Data::insertQuest(::Data::QuestForwarding &, char, unsigned __int64, char, char, short)
{
    LIFT_STUB(0x620c40);
}

// 0x620d30
void __cdecl Data::insertQuestConvoy(::Data::ZoneConvoyRecord *, unsigned __int64, char, char, char, short)
{
    LIFT_STUB(0x620d30);
}

// 0x620de0
void __cdecl Data::insertQuestFactionPcKill(::Data::ZoneRecordPtr, unsigned __int64, char, char, char, short, unsigned __int64)
{
    LIFT_STUB(0x620de0);
}

// 0x620ec0
void __cdecl Data::insertQuestAttraction(unsigned __int64 *, int, unsigned __int64, ::dr_tref)
{
    LIFT_STUB(0x620ec0);
}

// 0x620f50
void __cdecl Data::setDungeonInQuest(unsigned __int64 &, unsigned __int64, char)
{
    LIFT_STUB(0x620f50);
}

// 0x621120
unsigned __int64 __cdecl Data::getNpcScriptId(unsigned __int64)
{
    LIFT_STUB(0x621120);
}

// 0x621180
unsigned __int64 __cdecl Data::getEnvScriptId(unsigned __int64)
{
    LIFT_STUB(0x621180);
}

// 0x6211c0
unsigned __int64 __cdecl Data::getZoneScriptId(unsigned __int64)
{
    LIFT_STUB(0x6211c0);
}

// 0x621200
bool __cdecl Data::insertQuest(::QuestCase &, char, unsigned __int64, char, char)
{
    LIFT_STUB(0x621200);
}

// 0x623710
bool __cdecl Data::checkNextQuestConfliction(::Data::QuestNextQuest *, ::Data::QuestAcquisition *, ::Data::QuestQuest *)
{
    LIFT_STUB(0x623710);
}

// 0x6237d0
void __cdecl Data::checkZoneAndPcSpawn(::Data::ZoneRecordPtr, int, int)
{
    LIFT_STUB(0x6237d0);
}

// 0x623830
::Data::QuestDecision const * __cdecl Data::getQuestDecisionFromZoneArray(int, unsigned __int64 *, wchar_t const *)
{
    LIFT_STUB(0x623830);
}

// 0x6238f0
void __cdecl Data::linkQuestTransitAndZone(::Transit *, unsigned short, int, ::Quest const *)
{
    LIFT_STUB(0x6238f0);
}

// 0x623d00
unsigned __int64 __cdecl Data::DataManager::loadHiddenFieldFromZone(void)
{
    LIFT_STUB(0x623d00);
}

// 0x624e70
unsigned __int64 __cdecl Data::DataManager::loadHiddenFieldFromNpcBrainParameters(void)
{
    LIFT_STUB(0x624e70);
}

// 0x6250c0
unsigned __int64 __cdecl Data::DataManager::loadHiddenFieldFromFielditem(void)
{
    LIFT_STUB(0x6250c0);
}

// 0x6251b0
unsigned __int64 __cdecl Data::DataManager::loadHiddenFieldFromFielditemDrop(void)
{
    LIFT_STUB(0x6251b0);
}

// 0x6252e0
unsigned __int64 __cdecl Data::DataManager::loadHiddenFieldFromQuest(void)
{
    LIFT_STUB(0x6252e0);
}

// 0x6284a0
unsigned __int64 __cdecl Data::DataManager::loadHiddenFieldFromEffect(void)
{
    LIFT_STUB(0x6284a0);
}

// 0x628b10
unsigned __int64 __cdecl Data::DataManager::loadHiddenFieldFromGuildBankItem(void)
{
    LIFT_STUB(0x628b10);
}

// 0x628c90
unsigned __int64 __cdecl Data::DataManager::loadHiddenFieldFromGuildUniformParamTypeCategory(void)
{
    LIFT_STUB(0x628c90);
}

// 0x628ec0
unsigned __int64 __cdecl Data::DataManager::loadHiddenFieldFromAccountPostCharge(void)
{
    LIFT_STUB(0x628ec0);
}

// 0x628f90
unsigned __int64 __cdecl Data::DataManager::loadHiddenFieldFromSkill(void)
{
    LIFT_STUB(0x628f90);
}

// 0x629330
unsigned __int64 __cdecl Data::DataManager::loadHiddenFieldFromEnv(void)
{
    LIFT_STUB(0x629330);
}

// 0x629a50
unsigned __int64 __cdecl Data::DataManager::loadExpTableFromLevel(void)
{
    LIFT_STUB(0x629a50);
}

// 0x629cd0
unsigned __int64 __cdecl Data::DataManager::loadAccountExpTableFromAccountLevel(void)
{
    LIFT_STUB(0x629cd0);
}

// 0x629e80
unsigned __int64 __cdecl Data::DataManager::loadQuotaTableFromContentQuota(void)
{
    LIFT_STUB(0x629e80);
}

// 0x629fe0
unsigned __int64 __cdecl Data::DataManager::loadArenaDungeonZoneFromInterDungeonList(void)
{
    LIFT_STUB(0x629fe0);
}

// 0x62a2b0
unsigned __int64 __cdecl Data::DataManager::loadArenaDuelZoneFromDuel(void)
{
    LIFT_STUB(0x62a2b0);
}

// 0x62a390
unsigned __int64 __cdecl Data::DataManager::loadGradeBenefits(void)
{
    LIFT_STUB(0x62a390);
}

// 0x62aa50
unsigned __int64 __cdecl Data::DataManager::loadItemTransformRecipe(void)
{
    LIFT_STUB(0x62aa50);
}

// 0x62ab50
unsigned __int64 __cdecl Data::DataManager::loadZoneNpcSpawn(void)
{
    LIFT_STUB(0x62ab50);
}

// 0x62aed0
bool __cdecl Data::DataManager::addToArenaDungeonZoneIdList(unsigned __int64)
{
    LIFT_STUB(0x62aed0);
}

// 0x62afc0
bool __cdecl Data::DataManager::addToArenaDuelZoneIdList(unsigned __int64)
{
    LIFT_STUB(0x62afc0);
}

// 0x62b0b0
bool __cdecl Data::DataManager::checkQuestReward(::QuestReward *, unsigned short)
{
    LIFT_STUB(0x62b0b0);
}

// 0x62b1f0
bool __cdecl Data::DataManager::checkDisjoinedQuestReward(unsigned __int64 *&, int, bool, bool, unsigned short, char, ::Quest const *)
{
    LIFT_STUB(0x62b1f0);
}

// 0x62be40
int __cdecl Data::DataManager::GetExp(char)
{
    LIFT_STUB(0x62be40);
}

// 0x62be90
bool __cdecl Data::DataManager::AddExceedLevelData(char, unsigned short, char)
{
    LIFT_STUB(0x62be90);
}

// 0x62c1b0
__int64 __cdecl Data::DataManager::GetAccountExp(short)
{
    LIFT_STUB(0x62c1b0);
}

// 0x62c210
::Data::ContentQuotaRecordPtr const __cdecl Data::DataManager::GetQuotaKeyRecord(::Data::ContentQuotaRecordSubType, int)
{
    LIFT_STUB(0x62c210);
}

// 0x62c2b0
__int64 __cdecl Data::DataManager::GetMasteryExp(char)
{
    LIFT_STUB(0x62c2b0);
}

// 0x62c300
::Data::GradeBenefit * __cdecl Data::DataManager::GetGradeBenefitList(int)
{
    LIFT_STUB(0x62c300);
}

// 0x62c370
char __cdecl Data::DataManager::GetWeaponBrandMaxGemSlotCount(unsigned __int64)
{
    LIFT_STUB(0x62c370);
}

// 0x62c3e0
bool __cdecl Data::DataManager::loadSoulNpcSkill(void)
{
    LIFT_STUB(0x62c3e0);
}

// 0x62c740
bool __cdecl Data::DataManager::getNextSoulNpcSkills(unsigned __int64, char *const)
{
    LIFT_STUB(0x62c740);
}

// 0x62c910
bool __cdecl Data::postprocNpc(::DrEl *)
{
    LIFT_STUB(0x62c910);
}

// 0x62c980
bool __cdecl Data::postprocNpcBrainParameters(::DrEl *)
{
    LIFT_STUB(0x62c980);
}

// 0x62ca10
bool __cdecl Data::postprocItem(::DrEl *)
{
    LIFT_STUB(0x62ca10);
}

// 0x62d390
bool __cdecl Data::postprocReward(::DrEl *)
{
    LIFT_STUB(0x62d390);
}

// 0x62da90
bool __cdecl Data::postprocItemTransformUpgradeItem(::DrEl *)
{
    LIFT_STUB(0x62da90);
}

// 0x62dba0
bool __cdecl Data::postprocExpandInventoryData(::DrEl *)
{
    LIFT_STUB(0x62dba0);
}

// 0x62dc10
bool __cdecl Data::postprocDuelBotEquippedItem(::DrEl *)
{
    LIFT_STUB(0x62dc10);
}

// 0x62dc50
bool __cdecl Data::postprocGrade(::DrEl *)
{
    LIFT_STUB(0x62dc50);
}

// 0x62ddf0
bool __cdecl Data::postprocNpcConvoy(::DrEl *)
{
    LIFT_STUB(0x62ddf0);
}

// 0x62de60
bool __cdecl Data::postprocRandomStore(::DrEl *)
{
    LIFT_STUB(0x62de60);
}

// 0x62e260
bool __cdecl Data::postprocRandomStoreItem(::DrEl *)
{
    LIFT_STUB(0x62e260);
}

// 0x62e4e0
bool __cdecl Data::postprocRandomStoreItemGroup(::DrEl *)
{
    LIFT_STUB(0x62e4e0);
}

// 0x62e6f0
bool __cdecl Data::postprocRandomStoreProbGroup(::DrEl *)
{
    LIFT_STUB(0x62e6f0);
}

// 0x62ef50
bool __cdecl Data::postprocRankingPvEStage(::DrEl *)
{
    LIFT_STUB(0x62ef50);
}

// 0x62f140
bool __cdecl Data::postprocExpandRandomStore(::DrEl *)
{
    LIFT_STUB(0x62f140);
}

// 0x62f2b0
bool __cdecl Data::postprocZoneTriggerEventStage(::DrEl *)
{
    LIFT_STUB(0x62f2b0);
}

// 0x62f5d0
bool __cdecl Data::postprocSummoned(::DrEl *)
{
    LIFT_STUB(0x62f5d0);
}

// 0x62f600
bool __cdecl Data::postprocSummonedDesignerPreset(::DrEl *)
{
    LIFT_STUB(0x62f600);
}

// 0x62f6c0
bool __cdecl Data::postprocAchievement(::DrEl *)
{
    LIFT_STUB(0x62f6c0);
}

// 0x62fa00
bool __cdecl Data::postprocNewbieCare(::DrEl *)
{
    LIFT_STUB(0x62fa00);
}

// 0x62fa90
bool __cdecl Data::postprocBoardGachaReward(::DrEl *)
{
    LIFT_STUB(0x62fa90);
}

// 0x62fad0
unsigned __int64 __cdecl Data::DataManager::loadHiddenFieldZoneConvoy(void)
{
    LIFT_STUB(0x62fad0);
}

// 0x62fc90
unsigned __int64 __cdecl Data::DataManager::loadHiddenFieldZoneNpcSquad(void)
{
    LIFT_STUB(0x62fc90);
}

// 0x62ffd0
unsigned __int64 __cdecl Data::DataManager::loadHiddenFieldFromFriendNotiLocation(void)
{
    LIFT_STUB(0x62ffd0);
}

// 0x6301e0
unsigned __int64 __cdecl Data::DataManager::loadHiddenFieldFromAchievement(void)
{
    LIFT_STUB(0x6301e0);
}

// 0x630840
unsigned __int64 __cdecl Data::DataManager::loadHiddenFieldFromAchievementRegister(void)
{
    LIFT_STUB(0x630840);
}
