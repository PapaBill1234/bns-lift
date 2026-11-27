// duelbot_cpp.cpp: duelbot.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "duelbot.h"
#include "creature.h"
#include "gameobject.h"
#include "summoned.h"
#include "zone.h"
#include "LiftStub.h"

// 0x9b950
__cdecl DuelBotCreature::~DuelBotCreature(void)
{
    LIFT_STUB(0x9b950);
}

// 0x9b970
void __cdecl DuelBotCreature::Send(char const *, ...)
{
    LIFT_STUB(0x9b970);
}

// 0x9b9d0
void __cdecl DuelBotCreature::Send(::Packet const *)
{
    LIFT_STUB(0x9b9d0);
}

// 0x9ba40
void __cdecl DuelBotCreature::Send(::PacketList const *)
{
    LIFT_STUB(0x9ba40);
}

// 0x9ba90
__cdecl DuelBot::DuelBot(::Data::DuelBotRecordPtr const &, char)
{
    LIFT_STUB(0x9ba90);
}

// 0x9bc50
__cdecl DuelBot::~DuelBot(void)
{
    LIFT_STUB(0x9bc50);
}

// 0x9bd10
bool __cdecl DuelBot::Initialize(unsigned __int64, ::Zone *, char)
{
    LIFT_STUB(0x9bd10);
}

// 0x9bf30
void __cdecl DuelBot::EnterZone(::EnterReason, bool, unsigned int)
{
    LIFT_STUB(0x9bf30);
}

// 0x9c000
void __cdecl DuelBot::LeaveZone(::LeaveReason)
{
    LIFT_STUB(0x9c000);
}

// 0x9c090
void __cdecl DuelBot::loadData(void)
{
    LIFT_STUB(0x9c090);
}

// 0x9c7b0
void __cdecl DuelBot::equipItems(void)
{
    LIFT_STUB(0x9c7b0);
}

// 0x9d0d0
void __cdecl DuelBot::calcItemAbility(::Data::ItemRecordPtr const &, ::Data::EffectRecordItemAbility &)
{
    LIFT_STUB(0x9d0d0);
}

// 0x9d6a0
void __cdecl DuelBot::validateAbility(void)
{
    LIFT_STUB(0x9d6a0);
}

// 0x9d9e0
void __cdecl DuelBot::setMaxHp(void)
{
    LIFT_STUB(0x9d9e0);
}

// 0x9db20
::Data::DuelBotTrainedSkillRecordPtr __cdecl DuelBot::getTrainedSkillData(char)
{
    LIFT_STUB(0x9db20);
}

// 0x9dec0
void __cdecl DuelBot::invokePassiveEffects(void)
{
    LIFT_STUB(0x9dec0);
}

// 0x9df70
bool __cdecl DuelBot::SetDead(bool, ::ChangedProperty *, unsigned __int64, unsigned __int64, unsigned __int64, bool, bool)
{
    LIFT_STUB(0x9df70);
}

// 0x9e030
bool __cdecl DuelBot::HandleStance(char, unsigned __int64 const *, int, ::ChangedProperty *)
{
    LIFT_STUB(0x9e030);
}

// 0x9e0e0
unsigned __int64 __cdecl DuelBot::GetEquippedItemKey(short)
{
    LIFT_STUB(0x9e0e0);
}

// 0x9e1c0
bool __cdecl DuelBot::CheckUseSkill(unsigned __int64, unsigned int, char)
{
    LIFT_STUB(0x9e1c0);
}

// 0x9e220
void __cdecl DuelBot::OnKilled(::Zone *, ::GameObject *, unsigned __int64)
{
    LIFT_STUB(0x9e220);
}

// 0x9e4f0
void __cdecl DuelBot::OnCombatStart(::Creature *)
{
    LIFT_STUB(0x9e4f0);
}

// 0x9e6b0
void __cdecl DuelBot::OnCombatEnd(void)
{
    LIFT_STUB(0x9e6b0);
}

// 0x9e7c0
void __cdecl DuelBot::SetActiveDuelBotSummoned(::DuelBotSummoned *)
{
    LIFT_STUB(0x9e7c0);
}

// 0x9e930
__cdecl DuelBotSummoned::DuelBotSummoned(void)
{
    LIFT_STUB(0x9e930);
}

// 0x9ea50
__cdecl DuelBotSummoned::~DuelBotSummoned(void)
{
    LIFT_STUB(0x9ea50);
}

// 0x9eae0
bool __cdecl DuelBotSummoned::Initialize(unsigned __int64, ::DuelBot *, ::SummonedEntry *, ::Data::SummonedRecordPtr, ::Data::SummonedLevelRecordPtr)
{
    LIFT_STUB(0x9eae0);
}

// 0x9eba0
bool __cdecl DuelBotSummoned::HandleStance(char, unsigned __int64 const *, int, ::ChangedProperty *)
{
    LIFT_STUB(0x9eba0);
}

// 0x9ebd0
void __cdecl DuelBotSummoned::EnterZone(::EnterReason, bool, unsigned int)
{
    LIFT_STUB(0x9ebd0);
}

// 0x9ee60
void __cdecl DuelBotSummoned::LeaveZone(::LeaveReason)
{
    LIFT_STUB(0x9ee60);
}

// 0x9ef30
void __cdecl DuelBotSummoned::GetImmuneEffectAttributeValueFromData(unsigned __int64 &, unsigned __int64 &, unsigned __int64 &)
{
    LIFT_STUB(0x9ef30);
}

// 0x9efc0
void __cdecl DuelBotSummoned::OnTimer(::Zone *, unsigned short)
{
    LIFT_STUB(0x9efc0);
}

// 0x9f0e0
void __cdecl DuelBotSummoned::DespawnDelaying(void)
{
    LIFT_STUB(0x9f0e0);
}

// 0x9f1a0
void __cdecl DuelBotSummoned::Spawn(::EnterReason)
{
    LIFT_STUB(0x9f1a0);
}

// 0x9f310
void __cdecl DuelBotSummoned::Decompose(void)
{
    LIFT_STUB(0x9f310);
}

// 0x9f440
void __cdecl DuelBotSummoned::SyncMasterState(void)
{
    LIFT_STUB(0x9f440);
}

// 0x9f5c0
void __cdecl DuelBotSummoned::LoadData(void)
{
    LIFT_STUB(0x9f5c0);
}

// 0x9f890
bool __cdecl DuelBotSummoned::ApplyLevelData(::ChangedProperty *const, char, char)
{
    LIFT_STUB(0x9f890);
}

// 0x9f9e0
bool __cdecl DuelBotSummoned::ValidateAbility(::ChangedProperty *const, char)
{
    LIFT_STUB(0x9f9e0);
}

// 0x9fe50
bool __cdecl DuelBotSummoned::RemasterValidateAbility(::ChangedProperty *const, char)
{
    LIFT_STUB(0x9fe50);
}

// 0xa03e0
bool __cdecl DuelBotSummoned::ApplySummonerJobAbility(::ChangedProperty *, ::Data::SummonedLevelRecord const *)
{
    LIFT_STUB(0xa03e0);
}

// 0xa1e00
void __cdecl DuelBotSummoned::OnAttacked(::Zone *, ::GameObject *, unsigned __int64, short)
{
    LIFT_STUB(0xa1e00);
}

// 0xa1e30
void __cdecl DuelBotSummoned::OnCombatStart(::Creature *, ::ChangedProperty *)
{
    LIFT_STUB(0xa1e30);
}

// 0xa1e50
bool __cdecl DuelBotSummoned::SetDead(bool, ::ChangedProperty *, unsigned __int64, unsigned __int64, unsigned __int64, bool, bool)
{
    LIFT_STUB(0xa1e50);
}

// 0xa1fa0
void __cdecl DuelBotSummoned::handleSpawningStateProperty(bool)
{
    LIFT_STUB(0xa1fa0);
}

// 0xa20f0
void __cdecl DuelBotSummoned::finishSpawning(bool)
{
    LIFT_STUB(0xa20f0);
}

// 0xa2270
__cdecl DuelBotSummonedManager::~DuelBotSummonedManager(void)
{
    LIFT_STUB(0xa2270);
}

// 0xa22f0
bool __cdecl DuelBotSummonedManager::Initialize(::DuelBot *, int)
{
    LIFT_STUB(0xa22f0);
}

// 0xa2760
void __cdecl DuelBotSummonedManager::CreateSummoned(int)
{
    LIFT_STUB(0xa2760);
}

// 0x5ea260
void __cdecl DuelBot::ClearDuelBotSummoned(void)
{
    LIFT_STUB(0x5ea260);
}
