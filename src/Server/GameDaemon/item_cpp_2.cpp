// item_cpp_2.cpp: item.cpp part 2 (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "item.h"
#include "creature.h"
#include "pc.h"
#include "LiftStub.h"

// 0x5552a0
void __cdecl WeaponItem::DetachEnchantGem(int)
{
    LIFT_STUB(0x5552a0);
}

// 0x5553c0
void __cdecl WeaponItem::Identify(void)
{
    LIFT_STUB(0x5553c0);
}

// 0x5555b0
void __cdecl WeaponItem::InitializeGemSlot(::Data::ItemRecordWeaponPtr)
{
    LIFT_STUB(0x5555b0);
}

// 0x555a70
bool __cdecl WeaponItem::invokeAttackEffect(::Creature *, ::Creature *, ::SkillResult, bool, unsigned __int64 *, char, char, char, char, short *, short, short *, short) const
{
    LIFT_STUB(0x555a70);
}

// 0x555c20
void __cdecl WeaponItem::InvokeWeaponGemEffect(::Creature *, ::Creature *, ::SkillResult, bool) const
{
    LIFT_STUB(0x555c20);
}

// 0x555e50
void __cdecl WeaponItem::GetGemInfoString(wchar_t *, unsigned __int64) const
{
    LIFT_STUB(0x555e50);
}

// 0x555fa0
void __cdecl WeaponItem::HandleTransformFailureExp(short)
{
    LIFT_STUB(0x555fa0);
}

// 0x555ff0
int __cdecl WeaponItem::GetSpiritDataId(void) const
{
    LIFT_STUB(0x555ff0);
}

// 0x556020
void __cdecl WeaponItem::SetSpiritDataId(int)
{
    LIFT_STUB(0x556020);
}

// 0x556050
void __cdecl WeaponItem::GetSpiritAbility(char, char &, int &) const
{
    LIFT_STUB(0x556050);
}

// 0x5560c0
void __cdecl WeaponItem::SetSpiritAbility(char, char, int)
{
    LIFT_STUB(0x5560c0);
}

// 0x556150
bool __cdecl CostumeItem::Initialize(::Pc *, ::Data::ItemRecordPtr)
{
    LIFT_STUB(0x556150);
}

// 0x5564b0
void __cdecl AccessoryItem::HandleExp(int)
{
    LIFT_STUB(0x5564b0);
}

// 0x556620
bool __cdecl CostumeItem::CheckGuildUsed(void) const
{
    LIFT_STUB(0x556620);
}

// 0x556780
char __cdecl CostumeItem::GetCustomDressValue(char) const
{
    LIFT_STUB(0x556780);
}

// 0x5568f0
void __cdecl CostumeItem::SetCustomDressValue(char, short)
{
    LIFT_STUB(0x5568f0);
}

// 0x556a30
void __cdecl CostumeItem::BroadcastEquip(void) const
{
    LIFT_STUB(0x556a30);
}

// 0x556d30
void __cdecl CostumeItem::BroadcastUnequip(void) const
{
    LIFT_STUB(0x556d30);
}

// 0x556f10
bool __cdecl CostumeItem::checkToInvokeEffect(void) const
{
    LIFT_STUB(0x556f10);
}

// 0x556ff0
void __cdecl CostumeItem::InvokeEffect(void) const
{
    LIFT_STUB(0x556ff0);
}

// 0x557130
bool __cdecl AccessoryItem::Initialize(::Pc *, ::Data::ItemRecordPtr)
{
    LIFT_STUB(0x557130);
}

// 0x557470
bool __cdecl AccessoryItem::Initialize(::Pc *, ::Data::ItemRecordPtr, int, char *const, int *const)
{
    LIFT_STUB(0x557470);
}

// 0x557560
bool __cdecl AccessoryItem::CheckGuildUsed(void) const
{
    LIFT_STUB(0x557560);
}

// 0x5576c0
void __cdecl AccessoryItem::BroadcastEquip(void) const
{
    LIFT_STUB(0x5576c0);
}

// 0x557b60
void __cdecl AccessoryItem::BroadcastUnequip(void) const
{
    LIFT_STUB(0x557b60);
}

// 0x557eb0
bool __cdecl AccessoryItem::checkToInvokeEffect(void) const
{
    LIFT_STUB(0x557eb0);
}

// 0x557fe0
#pragma comment(linker, "/INCLUDE:?R_GetRandomEffectId@AccessoryItem@@UEBA_JD@Z")  // LIFT: dead-strip keep (no live caller yet)
__int64 __cdecl AccessoryItem::R_GetRandomEffectId(char groupIndex) const
{
    const ::AccessoryItemPropertyView &prop = reinterpret_cast<const ::AccessoryItemView *>(this)->prop;
    switch (groupIndex)
    {
    case 0:
        return prop.Remaster.random_effect_id_1;
    case 1:
        return prop.Remaster.random_effect_id_2;
    case 2:
        return prop.Remaster.random_effect_id_3;
    case 3:
        return prop.Remaster.random_effect_id_4;
    case 4:
        return prop.Remaster.random_effect_id_5;
    }
    return 0;
}

// 0x558030
void __cdecl AccessoryItem::R_SetRandomEffectId(char, __int64)
{
    LIFT_STUB(0x558030);
}

// 0x558090
#pragma comment(linker, "/INCLUDE:?R_GetRandomEffectGroupId@AccessoryItem@@UEBA_JD@Z")  // LIFT: dead-strip keep (no live caller yet)
__int64 __cdecl AccessoryItem::R_GetRandomEffectGroupId(char groupIndex) const
{
    const ::AccessoryItemPropertyView &prop = reinterpret_cast<const ::AccessoryItemView *>(this)->prop;
    switch (groupIndex)
    {
    case 0:
        return prop.Remaster.random_effect_group_id_1;
    case 1:
        return prop.Remaster.random_effect_group_id_2;
    case 2:
        return prop.Remaster.random_effect_group_id_3;
    case 3:
        return prop.Remaster.random_effect_group_id_4;
    case 4:
        return prop.Remaster.random_effect_group_id_5;
    }
    return 0;
}

// 0x5580e0
void __cdecl AccessoryItem::R_SetRandomEffectGroupId(char, __int64)
{
    LIFT_STUB(0x5580e0);
}

// 0x558140
void __cdecl AccessoryItem::R_InvokeRandomOptionEffect(void) const
{
    LIFT_STUB(0x558140);
}

// 0x558280
void __cdecl AccessoryItem::InvokeEffect(void) const
{
    LIFT_STUB(0x558280);
}

// 0x558440
void __cdecl AccessoryItem::HandleTransformFailureExp(short)
{
    LIFT_STUB(0x558440);
}

// 0x558490
char __cdecl AccessoryItem::GetCustomDressValue(char) const
{
    LIFT_STUB(0x558490);
}

// 0x558580
void __cdecl AccessoryItem::SetCustomDressValue(char, short)
{
    LIFT_STUB(0x558580);
}

// 0x5586c0
void __cdecl AccessoryItem::SetSpiritDataId(int)
{
    LIFT_STUB(0x5586c0);
}

// 0x5586f0
void __cdecl AccessoryItem::HandleSkillBuildUpLevel(bool, bool) const
{
    LIFT_STUB(0x5586f0);
}

// 0x558700
bool __cdecl GemItem::Initialize(::Pc *, ::Data::ItemRecordPtr)
{
    LIFT_STUB(0x558700);
}

// 0x558a40
void __cdecl GemItem::BroadcastEquip(void) const
{
    LIFT_STUB(0x558a40);
}

// 0x558a70
void __cdecl GemItem::BroadcastUnequip(void) const
{
    LIFT_STUB(0x558a70);
}

// 0x558aa0
bool __cdecl GemItem::R_CheckEnchantTargetItem(void)
{
    LIFT_STUB(0x558aa0);
}

// 0x558b50
#pragma comment(linker, "/INCLUDE:?R_GetRandomEffectId@GemItem@@UEBA_JD@Z")  // LIFT: dead-strip keep (no live caller yet)
__int64 __cdecl GemItem::R_GetRandomEffectId(char groupIndex) const
{
    const ::GemItemPropertyView &prop = reinterpret_cast<const ::GemItemView *>(this)->prop;
    switch (groupIndex)
    {
    case 0:
        return prop.Remaster.random_effect_id_1;
    case 1:
        return prop.Remaster.random_effect_id_2;
    case 2:
        return prop.Remaster.random_effect_id_3;
    case 3:
        return prop.Remaster.random_effect_id_4;
    case 4:
        return prop.Remaster.random_effect_id_5;
    }
    return 0;
}

// 0x558ba0
#pragma comment(linker, "/INCLUDE:?R_GetRandomEffectGroupId@GemItem@@UEBA_JD@Z")  // LIFT: dead-strip keep (no live caller yet)
__int64 __cdecl GemItem::R_GetRandomEffectGroupId(char groupIndex) const
{
    const ::GemItemPropertyView &prop = reinterpret_cast<const ::GemItemView *>(this)->prop;
    switch (groupIndex)
    {
    case 0:
        return prop.Remaster.random_effect_group_id_1;
    case 1:
        return prop.Remaster.random_effect_group_id_2;
    case 2:
        return prop.Remaster.random_effect_group_id_3;
    case 3:
        return prop.Remaster.random_effect_group_id_4;
    case 4:
        return prop.Remaster.random_effect_group_id_5;
    }
    return 0;
}

// 0x558bf0
void __cdecl GemItem::R_InvokeRandomOptionEffect(void) const
{
    LIFT_STUB(0x558bf0);
}

// 0x558d30
bool __cdecl GemItem::checkToInvokeEffect(void) const
{
    LIFT_STUB(0x558d30);
}

// 0x558e30
bool __cdecl GemItem::FindRandomStatSubAbility(::Data::ItemRecordGemPtr &, char, ::Data::ItemRandomAbilitySlotRecordPtr *)
{
    LIFT_STUB(0x558e30);
}

// 0x558f50
void __cdecl GemItem::InvokeEffect(void) const
{
    LIFT_STUB(0x558f50);
}

// 0x559460
bool __cdecl GemItem::DetermineRandomStatEquipGem(::Data::ItemRecordGemPtr &)
{
    LIFT_STUB(0x559460);
}

// 0x559820
bool __cdecl GemItem::DetermineFeedGem(::Data::ItemRecordGemPtr &)
{
    LIFT_STUB(0x559820);
}

// 0x559bc0
bool __cdecl GemItem::SetRandomStatMainAbility(char, int, ::Data::ItemRandomAbilitySlotRecordPtr const &)
{
    LIFT_STUB(0x559bc0);
}

// 0x559e50
bool __cdecl GemItem::SetRandomStatSubAbility(::GemItem::RandomStatSubIndex, char, int, ::Data::ItemRandomAbilitySlotRecordPtr const &)
{
    LIFT_STUB(0x559e50);
}

// 0x55a1a0
bool __cdecl GemItem::GetRandomStatMainAbility(char &, int &, int &, ::Data::ItemRandomAbilitySlotRecordPtr *) const
{
    LIFT_STUB(0x55a1a0);
}

// 0x55a310
bool __cdecl GemItem::GetRandomStatSubAbility(::GemItem::RandomStatSubIndex, char &, int &, int &, ::Data::ItemRandomAbilitySlotRecordPtr *) const
{
    LIFT_STUB(0x55a310);
}

// 0x55a560
void __cdecl GemItem::GetRandomStatGemInfoForGameLog(::GemItem::RandomStatGemInfo &) const
{
    LIFT_STUB(0x55a560);
}

// 0x55a6f0
bool __cdecl GemItem::FeedRandomStat(bool, ::GemItem::RandomStatSubIndex, bool, unsigned __int64, int &, int &, int &, int &)
{
    LIFT_STUB(0x55a6f0);
}

// 0x55b120
int __cdecl AccessoryItem::GetSpiritDataId(void) const
{
    LIFT_STUB(0x55b120);
}

// 0x55b150
void __cdecl AccessoryItem::GetSpiritAbility(char, char &, int &) const
{
    LIFT_STUB(0x55b150);
}

// 0x55b1c0
void __cdecl AccessoryItem::SetSpiritAbility(char, char, int)
{
    LIFT_STUB(0x55b1c0);
}

// 0x55b250
void __cdecl GroceryItem::HandleSkillBuildUpLevel(bool, bool) const
{
    LIFT_STUB(0x55b250);
}

// 0x55b2b0
void __cdecl GroceryItem::BroadcastEquip(void) const
{
    LIFT_STUB(0x55b2b0);
}

// 0x55b3a0
void __cdecl GroceryItem::BroadcastUnequip(void) const
{
    LIFT_STUB(0x55b3a0);
}

// 0x55b490
void __cdecl GroceryItem::ActivateAbility(void) const
{
    LIFT_STUB(0x55b490);
}

// 0x55b570
void __cdecl GroceryItem::DeactivateAbility(void) const
{
    LIFT_STUB(0x55b570);
}

// 0x55b640
bool __cdecl GroceryItem::CheckUsableZone(void) const
{
    LIFT_STUB(0x55b640);
}

// 0x55b7e0
__cdecl TimeLimitItemPriorityQueue::~TimeLimitItemPriorityQueue(void)
{
    LIFT_STUB(0x55b7e0);
}

// 0x55b840
bool __cdecl TimeLimitItemPriorityQueue::Push(::TimeLimitItem *)
{
    LIFT_STUB(0x55b840);
}

// 0x55b960
void __cdecl TimeLimitItemPriorityQueue::Clear(void)
{
    LIFT_STUB(0x55b960);
}
