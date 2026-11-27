// item_cpp_1.cpp: item.cpp part 1 (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "item.h"
#include "controlledcreature.h"
#include "pc.h"
#include "weaponproperty.h"
#include "LiftStub.h"

// 0x54ee80
::Item * __cdecl ItemFactory::CreateItem(::ItemClass)
{
    LIFT_STUB(0x54ee80);
}

// 0x54f120
::Item * __cdecl ItemFactory::CreateItem(::Pc *, ::Data::ItemRecordPtr)
{
    LIFT_STUB(0x54f120);
}

// 0x54f400
short __cdecl Item::FetchDbFromXmlData(int, char, wchar_t const *, char *, short, ::EconomyItemCategory *)
{
    LIFT_STUB(0x54f400);
}

// 0x54f780
char __cdecl Item::GetSetItemCount(void)
{
    LIFT_STUB(0x54f780);
}

// 0x54f7b0
void __cdecl Item::DetachEffect(void)
{
    LIFT_STUB(0x54f7b0);
}

// 0x54f840
bool __cdecl Item::CheckTrade(bool) const
{
    LIFT_STUB(0x54f840);
}

// 0x54f940
bool __cdecl Item::CheckRegisterSale(void) const
{
    LIFT_STUB(0x54f940);
}

// 0x54fa40
bool __cdecl Item::CheckRuleDispose(void) const
{
    LIFT_STUB(0x54fa40);
}

// 0x54faa0
bool __cdecl Item::CheckSell(void) const
{
    LIFT_STUB(0x54faa0);
}

// 0x54fb10
bool __cdecl Item::CheckOldItemSell(void) const
{
    LIFT_STUB(0x54fb10);
}

// 0x54fbb0
bool __cdecl Item::CheckMaxDurability(void) const
{
    LIFT_STUB(0x54fbb0);
}

// 0x54fbf0
bool __cdecl Item::CheckWardrobeStoreable(void) const
{
    LIFT_STUB(0x54fbf0);
}

// 0x54fc90
bool __cdecl Item::CheckWarehouseStoreable(void) const
{
    LIFT_STUB(0x54fc90);
}

// 0x54fce0
bool __cdecl Item::CheckBadgeDepositoryStoreable(void) const
{
    LIFT_STUB(0x54fce0);
}

// 0x54fd40
bool __cdecl Item::ConsumeDurability(int)
{
    LIFT_STUB(0x54fd40);
}

// 0x54fe90
bool __cdecl Item::checkAvailableItemInPcCafe(void) const
{
    LIFT_STUB(0x54fe90);
}

// 0x54fed0
bool __cdecl Item::checkEquipLevel(void) const
{
    LIFT_STUB(0x54fed0);
}

// 0x54ff20
void __cdecl Item::calculateExpirationTime(::Data::ItemRecordPtr, __int64 &)
{
    LIFT_STUB(0x54ff20);
}

// 0x54ffc0
void __cdecl Item::handleSkillBuildUpLevel(bool, bool) const
{
    LIFT_STUB(0x54ffc0);
}

// 0x5500c0
bool __cdecl Item::CheckDuelGrade(void) const
{
    LIFT_STUB(0x5500c0);
}

// 0x5501f0
bool __cdecl Item::CheckTimeLimitItem(void) const
{
    LIFT_STUB(0x5501f0);
}

// 0x550230
bool __cdecl Item::IsExpired(__int64) const
{
    LIFT_STUB(0x550230);
}

// 0x550280
__int64 __cdecl Item::CalculateRemainingTime(::Data::ItemRecordPtr, __int64) const
{
    LIFT_STUB(0x550280);
}

// 0x5502d0
bool __cdecl Item::CheckStackable(::Data::ItemRecordGroceryPtr, short) const
{
    LIFT_STUB(0x5502d0);
}

// 0x5503c0
bool __cdecl Item::IsEquipJobNone(void) const
{
    LIFT_STUB(0x5503c0);
}

// 0x550430
bool __cdecl Item::CheckDepositInGuildBank(void) const
{
    LIFT_STUB(0x550430);
}

// 0x550520
bool __cdecl Item::CheckAccountPostCharge(void) const
{
    LIFT_STUB(0x550520);
}

// 0x5505b0
void __cdecl Item::InvokeEffect(::Data::ItemRecordPtr, ::ControlledCreature *, short)
{
    LIFT_STUB(0x5505b0);
}

// 0x5506b0
void __cdecl Item::CalcItemAbility(::Data::ItemRecordPtr, ::Data::EffectRecordItemAbility &)
{
    LIFT_STUB(0x5506b0);
}

// 0x550c70
void __cdecl Item::CalcItemAbilityDetach(::Data::ItemRecordPtr, ::Data::EffectRecordItemAbility &)
{
    LIFT_STUB(0x550c70);
}

// 0x551230
char __cdecl Item::CalcLevel(char, int, int &)
{
    LIFT_STUB(0x551230);
}

// 0x551380
unsigned __int64 __cdecl Item::GetUsedGuildIdForGameLog(::Item const *)
{
    LIFT_STUB(0x551380);
}

// 0x5513d0
bool __cdecl Item::MakeCustomParameterLog(wchar_t *, int, char *const, int)
{
    LIFT_STUB(0x5513d0);
}

// 0x551530
bool __cdecl Item::GetSpiritStatusForGameLog(::Pc const *, ::Item const *, char, char *const, int *const, int *)
{
    LIFT_STUB(0x551530);
}

// 0x551600
::R_EnchantToItemResult __cdecl Item::R_HandleEnchant(short, bool, bool)
{
    LIFT_STUB(0x551600);
}

// 0x551a60
::R_RestoreEnchantFailedItemResult __cdecl Item::R_HandleRestoreEnchantItem(int)
{
    LIFT_STUB(0x551a60);
}

// 0x551bf0
char __cdecl Item::R_HandleEnchantPoint(short)
{
    LIFT_STUB(0x551bf0);
}

// 0x551dd0
void __cdecl Item::R_EnchantFailDestroy(void)
{
    LIFT_STUB(0x551dd0);
}

// 0x551e90
void __cdecl Item::R_ResetEnchant(void)
{
    LIFT_STUB(0x551e90);
}

// 0x551ed0
char __cdecl Item::R_ResetRandomOption(::Data::ItemRecordPtr, ::R_PolishToItemReason, bool const *)
{
    LIFT_STUB(0x551ed0);
}

// 0x552720
char __cdecl Item::R_GetOpenRandomOptionSlotCount(::Data::ItemRecordPtr) const
{
    LIFT_STUB(0x552720);
}

// 0x552800
bool __cdecl WeaponItem::Initialize(::Pc *, ::Data::ItemRecordPtr)
{
    LIFT_STUB(0x552800);
}

// 0x552c80
bool __cdecl WeaponItem::Initialize(::Pc *, ::Data::ItemRecordPtr, bool, unsigned int *const, bool, unsigned int, char, bool, int, char *const, int *const)
{
    LIFT_STUB(0x552c80);
}

// 0x552e00
bool __cdecl WeaponItem::Initialize(::Pc *, ::Data::ItemRecordPtr, int, char *const, int *const)
{
    LIFT_STUB(0x552e00);
}

// 0x552ef0
bool __cdecl WeaponItem::InitializeProperty(::Data::ItemRecordPtr, ::WeaponProperty &)
{
    LIFT_STUB(0x552ef0);
}

// 0x5532c0
char __cdecl WeaponItem::GetSetItemCount(void)
{
    LIFT_STUB(0x5532c0);
}

// 0x5533e0
void __cdecl WeaponItem::SetDurability(short)
{
    LIFT_STUB(0x5533e0);
}

// 0x553490
bool __cdecl WeaponItem::Identified(void) const
{
    LIFT_STUB(0x553490);
}

// 0x5534e0
void __cdecl WeaponItem::HandleSkillBuildUpLevel(bool, bool) const
{
    LIFT_STUB(0x5534e0);
}

// 0x553530
bool __cdecl WeaponItem::R_CheckEnchantTargetItem(void)
{
    LIFT_STUB(0x553530);
}

// 0x5535f0
#pragma comment(linker, "/INCLUDE:?R_GetRandomEffectId@WeaponItem@@UEBA_JD@Z")  // LIFT: dead-strip keep (no live caller yet)
__int64 __cdecl WeaponItem::R_GetRandomEffectId(char groupIndex) const
{
    const ::WeaponItemPropertyView &prop = reinterpret_cast<const ::WeaponItemView *>(this)->prop;
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

// 0x553640
void __cdecl WeaponItem::R_SetRandomEffectId(char, __int64)
{
    LIFT_STUB(0x553640);
}

// 0x5536a0
#pragma comment(linker, "/INCLUDE:?R_GetRandomEffectGroupId@WeaponItem@@UEBA_JD@Z")  // LIFT: dead-strip keep (no live caller yet)
__int64 __cdecl WeaponItem::R_GetRandomEffectGroupId(char groupIndex) const
{
    const ::WeaponItemPropertyView &prop = reinterpret_cast<const ::WeaponItemView *>(this)->prop;
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

// 0x5536f0
void __cdecl WeaponItem::R_SetRandomEffectGroupId(char, __int64)
{
    LIFT_STUB(0x5536f0);
}

// 0x553750
void __cdecl WeaponItem::R_InvokeRandomOptionEffect(void) const
{
    LIFT_STUB(0x553750);
}

// 0x553890
void __cdecl WeaponItem::BroadcastEquip(void) const
{
    LIFT_STUB(0x553890);
}

// 0x553ee0
void __cdecl WeaponItem::BroadcastUnequip(void) const
{
    LIFT_STUB(0x553ee0);
}

// 0x554330
bool __cdecl WeaponItem::checkToInvokeEffect(void) const
{
    LIFT_STUB(0x554330);
}

// 0x554450
void __cdecl WeaponItem::InvokeEffect(void) const
{
    LIFT_STUB(0x554450);
}

// 0x554a80
unsigned int __cdecl WeaponItem::GetGem(int) const
{
    LIFT_STUB(0x554a80);
}

// 0x554af0
void __cdecl WeaponItem::AttachGem(int, unsigned int)
{
    LIFT_STUB(0x554af0);
}

// 0x554bc0
void __cdecl WeaponItem::DetachGem(int, unsigned int)
{
    LIFT_STUB(0x554bc0);
}

// 0x554c90
void __cdecl WeaponItem::AddGemSlot(int, unsigned int)
{
    LIFT_STUB(0x554c90);
}

// 0x554d40
void __cdecl WeaponItem::DeleteGemSlot(int)
{
    LIFT_STUB(0x554d40);
}

// 0x554df0
bool __cdecl WeaponItem::GetEnchantGemData(int, ::Data::ItemRecordGemPtr *) const
{
    LIFT_STUB(0x554df0);
}

// 0x554fa0
bool __cdecl WeaponItem::GetEnchantGemSkill(int, unsigned __int64 *const) const
{
    LIFT_STUB(0x554fa0);
}

// 0x555160
void __cdecl WeaponItem::AttachEnchantGem(int, int, char, int)
{
    LIFT_STUB(0x555160);
}
