// summoned_cpp.cpp: summoned.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "summoned.h"
#include "creature.h"
#include "gameobject.h"
#include "pc.h"
#include "zone.h"
#include "LiftStub.h"

// 0x611190
__cdecl Summoned::Summoned(void)
{
    LIFT_STUB(0x611190);
}

// 0x611320
__cdecl Summoned::~Summoned(void)
{
    LIFT_STUB(0x611320);
}

// 0x6113d0
bool __cdecl Summoned::Initialize(unsigned __int64, ::Pc *, ::SummonedEntry *, ::Data::SummonedRecordPtr, ::Data::SummonedLevelRecordPtr)
{
    LIFT_STUB(0x6113d0);
}

// 0x611490
void __cdecl Summoned::EnterZone(::EnterReason, bool, unsigned int)
{
    LIFT_STUB(0x611490);
}

// 0x611830
void __cdecl Summoned::LeaveZone(::LeaveReason)
{
    LIFT_STUB(0x611830);
}

// 0x6119d0
unsigned short __cdecl Summoned::FetchAllSummonedProperty(char *, unsigned short)
{
    LIFT_STUB(0x6119d0);
}

// 0x611a60
void __cdecl Summoned::GetImmuneEffectAttributeValueFromData(unsigned __int64 &, unsigned __int64 &, unsigned __int64 &)
{
    LIFT_STUB(0x611a60);
}

// 0x611af0
void __cdecl Summoned::Send(char const *, ...)
{
    LIFT_STUB(0x611af0);
}

// 0x611b20
void __cdecl Summoned::Send(::Packet const *)
{
    LIFT_STUB(0x611b20);
}

// 0x611b50
void __cdecl Summoned::Send(::PacketList const *)
{
    LIFT_STUB(0x611b50);
}

// 0x611b80
void __cdecl Summoned::OnTimer(::Zone *, unsigned short)
{
    LIFT_STUB(0x611b80);
}

// 0x611ca0
void __cdecl Summoned::DespawnDelaying(void)
{
    LIFT_STUB(0x611ca0);
}

// 0x611d60
void __cdecl Summoned::SetCombatModeByAttack(bool, ::SourceLocation const &)
{
    LIFT_STUB(0x611d60);
}

// 0x611d90
void __cdecl Summoned::SetCombatModeByAttacked(::SourceLocation const &)
{
    LIFT_STUB(0x611d90);
}

// 0x611dc0
void __cdecl Summoned::SetCombatModeByTargeted(::SourceLocation const &)
{
    LIFT_STUB(0x611dc0);
}

// 0x611df0
void __cdecl Summoned::ResetCombatModeByTargeted(::SourceLocation const &)
{
    LIFT_STUB(0x611df0);
}

// 0x611e20
void __cdecl Summoned::SetCombatModeByLink(::SourceLocation const &)
{
    LIFT_STUB(0x611e20);
}

// 0x611e50
void __cdecl Summoned::ResetCombatModeByLink(::SourceLocation const &)
{
    LIFT_STUB(0x611e50);
}

// 0x611e80
void __cdecl Summoned::ResetCombatMode(bool, ::SourceLocation const &)
{
    LIFT_STUB(0x611e80);
}

// 0x611eb0
bool __cdecl Summoned::HandleCombatSide(char, ::ChangedProperty *)
{
    LIFT_STUB(0x611eb0);
}

// 0x611f20
void __cdecl Summoned::Spawn(::EnterReason)
{
    LIFT_STUB(0x611f20);
}

// 0x612090
void __cdecl Summoned::Decompose(void)
{
    LIFT_STUB(0x612090);
}

// 0x6121c0
void __cdecl Summoned::Respawn(void)
{
    LIFT_STUB(0x6121c0);
}

// 0x612380
void __cdecl Summoned::SyncMasterState(void)
{
    LIFT_STUB(0x612380);
}

// 0x612530
void __cdecl Summoned::LoadData(void)
{
    LIFT_STUB(0x612530);
}

// 0x612810
bool __cdecl Summoned::HandleStance(char, unsigned __int64 const *, int, ::ChangedProperty *)
{
    LIFT_STUB(0x612810);
}

// 0x612840
bool __cdecl Summoned::ApplyLevelData(::ChangedProperty *const, char, char)
{
    LIFT_STUB(0x612840);
}

// 0x612950
::Data::SummonedMasteryLevelRecordPtr const __cdecl Summoned::GetSummonedMasterLevel(char)
{
    LIFT_STUB(0x612950);
}

// 0x612a50
bool __cdecl Summoned::ValidateAbility(::ChangedProperty *const, char)
{
    LIFT_STUB(0x612a50);
}

// 0x612e70
bool __cdecl Summoned::RemasterValidateAbility(::ChangedProperty *const, char)
{
    LIFT_STUB(0x612e70);
}

// 0x6133e0
bool __cdecl Summoned::EquipItems(::ChangedProperty *)
{
    LIFT_STUB(0x6133e0);
}

// 0x6134d0
bool __cdecl Summoned::ApplySummonerJobAbility(::ChangedProperty *, ::Data::SummonedLevelRecord const *)
{
    LIFT_STUB(0x6134d0);
}

// 0x615250
void __cdecl Summoned::OnAttacked(::Zone *, ::GameObject *, unsigned __int64, short)
{
    LIFT_STUB(0x615250);
}

// 0x615280
void __cdecl Summoned::OnKill(::Zone *, ::Pc *, unsigned __int64, char, char)
{
    LIFT_STUB(0x615280);
}

// 0x615440
bool __cdecl Summoned::SetDead(bool, ::ChangedProperty *, unsigned __int64, unsigned __int64, unsigned __int64, bool, bool)
{
    LIFT_STUB(0x615440);
}

// 0x6155b0
void __cdecl Summoned::SendSummonedPropertyChangedNotify(void)
{
    LIFT_STUB(0x6155b0);
}

// 0x615800
void __cdecl Summoned::handleSpawningStateProperty(bool)
{
    LIFT_STUB(0x615800);
}

// 0x615950
void __cdecl Summoned::finishSpawning(bool)
{
    LIFT_STUB(0x615950);
}

// 0x615b30
::Pc * __cdecl SummonedManager::GetPc(::Creature *)
{
    LIFT_STUB(0x615b30);
}

// 0x615b60
__cdecl SummonedManager::~SummonedManager(void)
{
    LIFT_STUB(0x615b60);
}

// 0x615be0
void __cdecl SummonedManager::SetSummonedJob(char)
{
    LIFT_STUB(0x615be0);
}

// 0x615d30
void __cdecl SummonedManager::CreateSummoned(int)
{
    LIFT_STUB(0x615d30);
}

// 0x615db0
int __cdecl SummonedManager::SetDbData(short, char const *, int)
{
    LIFT_STUB(0x615db0);
}

// 0x616310
void __cdecl SummonedManager::ConfirmAcquire(char)
{
    LIFT_STUB(0x616310);
}

// 0x616c30
bool __cdecl Summoned::changeMoveState(::CreatureMoveState, short, wchar_t *)
{
    LIFT_STUB(0x616c30);
}

// 0x616f10
void __cdecl Summoned::StartCombat(void)
{
    LIFT_STUB(0x616f10);
}

// 0x616f50
void __cdecl Summoned::FinishCombat(void)
{
    LIFT_STUB(0x616f50);
}
