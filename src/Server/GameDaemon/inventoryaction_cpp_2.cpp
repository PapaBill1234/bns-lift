// inventoryaction_cpp_2.cpp: inventoryaction.cpp part 2 (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "inventoryaction.h"
#include "action.h"
#include "creature.h"
#include "instantpaymenttran.h"
#include "inventory.h"
#include "item.h"
#include "itempouch.h"
#include "pc.h"
#include "zone.h"
#include "LiftStub.h"

#pragma comment(linker, "/INCLUDE:?availableCancel@RepairWithCampfireAction@@EEAA_NW4CancelActionReason@@@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?availableCancel@PickupAction@@EEAA_NW4CancelActionReason@@@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?availableCancel@PickupDeadBodyAction@@EEAA_NW4CancelActionReason@@@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?availableCancel@PutdownFieldItemAction@@EEAA_NW4CancelActionReason@@@Z")  // LIFT: dead-strip keep (no live caller yet)

// 0x51e390
void __cdecl DeleteWeaponGemSlotTask::start(void)
{
    LIFT_STUB(0x51e390);
}

// 0x51e450
void __cdecl OpenWeaponGemSlotTask::start(void)
{
    LIFT_STUB(0x51e450);
}

// 0x51e590
bool __cdecl RepairWithCampfireAction::Initialize(::Zone *, ::Creature *, __int64, short)
{
    LIFT_STUB(0x51e590);
}

// 0x51e660
void __cdecl RepairWithCampfireAction::failAction(::Action::FailReason)
{
    LIFT_STUB(0x51e660);
}

// 0x51e690
void __cdecl RepairWithCampfireAction::startAction(void)
{
    LIFT_STUB(0x51e690);
}

// 0x51edb0
bool __cdecl RepairWithCampfireAction::consumeItem(void)
{
    LIFT_STUB(0x51edb0);
}

// 0x51f2c0
bool __cdecl RepairWithCampfireAction::repair(void)
{
    LIFT_STUB(0x51f2c0);
}

// 0x51f830
void __cdecl RepairWithCampfireAction::finishAction(void)
{
    LIFT_STUB(0x51f830);
}

// 0x51f8d0
void __cdecl RepairWithCampfireAction::cancelAction(::Action::CancelReason, wchar_t const *, int)
{
    LIFT_STUB(0x51f8d0);
}

// 0x51fa50
bool __cdecl RepairWithCampfireAction::availableCancel(::CancelActionReason reason)
{
    switch (reason)  // LIFT: switch form (js, jle, jne)
    {
    case CANCELACTIONREASON_USER_REQUEST:
    case CANCELACTIONREASON_MOVE:
    case CANCELACTIONREASON_ATTACKED:
        return true;
    default:
        return false;
    }
}

// 0x51fa70
void __cdecl SealItemAction::startAction(void)
{
    LIFT_STUB(0x51fa70);
}

// 0x51fb60
void __cdecl SealItemAction::failAction(::Action::FailReason)
{
    LIFT_STUB(0x51fb60);
}

// 0x51fb90
void __cdecl IdentifyItemAction::startAction(void)
{
    LIFT_STUB(0x51fb90);
}

// 0x51fc70
void __cdecl IdentifyItemAction::failAction(::Action::FailReason)
{
    LIFT_STUB(0x51fc70);
}

// 0x51fca0
void __cdecl UnsealItemAction::startAction(void)
{
    LIFT_STUB(0x51fca0);
}

// 0x51fd20
void __cdecl UnsealItemAction::failAction(::Action::FailReason)
{
    LIFT_STUB(0x51fd20);
}

// 0x51fd50
void __cdecl DecomposeItem2Task::start(void)
{
    LIFT_STUB(0x51fd50);
}

// 0x51fe20
__cdecl TransformItemTask::~TransformItemTask(void)
{
    LIFT_STUB(0x51fe20);
}

// 0x51fe80
void __cdecl TransformItemTask::ProcessUnexpired(int)
{
    LIFT_STUB(0x51fe80);
}

// 0x5200c0
void __cdecl TransformItemTask::TimerExpired(unsigned int, long)
{
    LIFT_STUB(0x5200c0);
}

// 0x520100
void __cdecl TransformItemTask::start(void)
{
    LIFT_STUB(0x520100);
}

// 0x520290
bool __cdecl TransformItemTask::Initialize(::Zone *, ::Creature *, unsigned __int64, ::TransformItemTask::Order *const, short, ::TransformItemTask::Order *const, short, ::TransformItemTask::Order *const, short, ::TransformItemTask::Order *const, short, ::TransformItemTask::TransformOperation)
{
    LIFT_STUB(0x520290);
}

// 0x5204a0
bool __cdecl TransformItemTask::InitializeInstantPaymentOk(::Zone *, ::Creature *, unsigned __int64, ::InstantPaymentTran *, __int64, ::InstantPaymentTransformInfoParam *)
{
    LIFT_STUB(0x5204a0);
}

// 0x520730
bool __cdecl TransformItemTask::InitializeInstantPaymentFail(::Zone *, ::Creature *, unsigned __int64, unsigned __int64, ::InstantPaymentTransformInfoParam *)
{
    LIFT_STUB(0x520730);
}

// 0x520910
char __cdecl TransformItemTask::getUpgradeGroceryDataIndex(::Data::ItemTransformUpgradeItemRecordPtr &)
{
    LIFT_STUB(0x520910);
}

// 0x520ae0
bool __cdecl TransformItemTask::checkUpgradeGrocery(void)
{
    LIFT_STUB(0x520ae0);
}

// 0x520ef0
::GameFailReason __cdecl TransformItemTask::checkMainIngredientItem(::Data::ItemRecordPtr &)
{
    LIFT_STUB(0x520ef0);
}

// 0x521380
::GameFailReason __cdecl TransformItemTask::checkMainIngredientItemBrand(::Data::ItemBrandRecordPtr &)
{
    LIFT_STUB(0x521380);
}

// 0x521760
bool __cdecl TransformItemTask::checkMainIngredientWeaponItem(void)
{
    LIFT_STUB(0x521760);
}

// 0x521b30
bool __cdecl TransformItemTask::checkMainIngredientSpiritAttachedItem(void)
{
    LIFT_STUB(0x521b30);
}

// 0x521f40
::GameFailReason __cdecl TransformItemTask::checkMainIngredient(void)
{
    LIFT_STUB(0x521f40);
}

// 0x521fe0
bool __cdecl TransformItemTask::checkSubIngredientItem(::Data::ItemRecordPtr &, int, int &)
{
    LIFT_STUB(0x521fe0);
}

// 0x5225a0
bool __cdecl TransformItemTask::checkSubIngredientItemBrand(::Data::ItemBrandRecordPtr &, int, int &)
{
    LIFT_STUB(0x5225a0);
}

// 0x522b50
bool __cdecl TransformItemTask::checkSubIngredient(void)
{
    LIFT_STUB(0x522b50);
}

// 0x522cc0
bool __cdecl TransformItemTask::checkFixedIngredient(void)
{
    LIFT_STUB(0x522cc0);
}

// 0x523130
bool __cdecl TransformItemTask::checkWeaponGem(::Data::ItemRecordPtr const &, char, short, char)
{
    LIFT_STUB(0x523130);
}

// 0x523200
int __cdecl TransformItemTask::getDiscountMoney(void)
{
    LIFT_STUB(0x523200);
}

// 0x523530
bool __cdecl TransformItemTask::checkRecipe(::GameFailReason *)
{
    LIFT_STUB(0x523530);
}

// 0x5237e0
::ItemTransformGroup __cdecl TransformItemTask::decideTransformGroup(void)
{
    LIFT_STUB(0x5237e0);
}

// 0x5239f0
bool __cdecl TransformItemTask::fillOrders(::ItemTransformGroup, ::Inventory::AcquireOrder *const, ::Inventory::DisposeOrderWithPos *const, char &)
{
    LIFT_STUB(0x5239f0);
}

// 0x523fe0
void __cdecl TransformItemTask::fillWeaponGemDisposeOrder(::Inventory::DisposeOrderWithPos *const)
{
    LIFT_STUB(0x523fe0);
}

// 0x524260
bool __cdecl TransformItemTask::pickItems(::ItemTransformGroup, ::Inventory::AcquireOrder *const)
{
    LIFT_STUB(0x524260);
}

// 0x5246b0
unsigned __int64 __cdecl TransformItemTask::decideItem(::dr_tref const &)
{
    LIFT_STUB(0x5246b0);
}

// 0x524860
bool __cdecl TransformItemTask::pickRandomItems(::Inventory::AcquireOrder *const, char &)
{
    LIFT_STUB(0x524860);
}

// 0x524a30
bool __cdecl TransformItemTask::pickWeaponGem(::Inventory::AcquireOrder &)
{
    LIFT_STUB(0x524a30);
}

// 0x524db0
char __cdecl TransformItemTask::decideWeaponGemType(char, char)
{
    LIFT_STUB(0x524db0);
}

// 0x524fe0
void __cdecl TransformItemTask::invokeTransformFailEffect(void)
{
    LIFT_STUB(0x524fe0);
}

// 0x5250a0
bool __cdecl TransformItemTask::setTransformFailureExp(::Item *)
{
    LIFT_STUB(0x5250a0);
}

// 0x525400
void __cdecl TransformItemTask::setTransformFailureExpDiff(void)
{
    LIFT_STUB(0x525400);
}

// 0x525780
void __cdecl TransformItemTask::handleTransformFailureExp(short &)
{
    LIFT_STUB(0x525780);
}

// 0x525b70
::GameFailReason __cdecl TransformItemTask::checkCondition(void)
{
    LIFT_STUB(0x525b70);
}

// 0x525c70
void __cdecl TransformItemTask::startTransformNormal(void)
{
    LIFT_STUB(0x525c70);
}

// 0x526140
bool __cdecl TransformItemTask::applyTransformResult(::Inventory::DisposeOrderWithPos const *const, ::Inventory::AcquireOrder *const, ::ItemTransformGroup, char)
{
    LIFT_STUB(0x526140);
}

// 0x5275f0
::GameFailReason __cdecl TransformItemTask::instantPaymentTry(void)
{
    LIFT_STUB(0x5275f0);
}

// 0x527d20
::GameFailReason __cdecl TransformItemTask::instantPaymentOK(void)
{
    LIFT_STUB(0x527d20);
}

// 0x5284b0
void __cdecl TransformItemTask::instantPaymentFail(void)
{
    LIFT_STUB(0x5284b0);
}

// 0x528640
void __cdecl TransformItemTask::setNoCharge(void)
{
    LIFT_STUB(0x528640);
}

// 0x5287b0
bool __cdecl PassingItemAbilityTask::Initialize(::Zone *, ::Creature *, unsigned __int64, ::PassingItemAbilityTask::Order *const, short, ::PassingItemAbilityTask::Order *const, short, ::PassingItemAbilityTask::Order *const, short)
{
    LIFT_STUB(0x5287b0);
}

// 0x5289f0
void __cdecl PassingItemAbilityTask::start(void)
{
    LIFT_STUB(0x5289f0);
}

// 0x528d30
::GameFailReason __cdecl PassingItemAbilityTask::checkTargetItem(void)
{
    LIFT_STUB(0x528d30);
}

// 0x5291f0
::GameFailReason __cdecl PassingItemAbilityTask::checkMainIngredient(void)
{
    LIFT_STUB(0x5291f0);
}

// 0x5294a0
::GameFailReason __cdecl PassingItemAbilityTask::checkFixedIngredient(void)
{
    LIFT_STUB(0x5294a0);
}

// 0x529890
bool __cdecl PassingItemAbilityTask::applyPassingItemAbilityResult(::Inventory::DisposeOrderWithPos const *const)
{
    LIFT_STUB(0x529890);
}

// 0x52ad90
bool __cdecl PassingItemAbilityTask::fillOrders(::Inventory::DisposeOrderWithPos *const)
{
    LIFT_STUB(0x52ad90);
}

// 0x52afb0
int __cdecl PassingItemAbilityTask::decideAbilityValue(int, int, ::PassingItemAbilityTask::DecideAbilityContext *)
{
    LIFT_STUB(0x52afb0);
}

// 0x52b1a0
bool __cdecl PickupAction::Initialize(::Zone *, ::Creature *, unsigned __int64)
{
    LIFT_STUB(0x52b1a0);
}

// 0x52b2b0
void __cdecl PickupAction::startAction(void)
{
    LIFT_STUB(0x52b2b0);
}

// 0x52bf30
void __cdecl PickupAction::sendOpenItemPouchOk(::Pc *, ::ItemPouch *)
{
    LIFT_STUB(0x52bf30);
}

// 0x52c230
bool __cdecl PickupAction::availableCancel(::CancelActionReason reason)
{
    return reason == CANCELACTIONREASON_MOVE || reason == CANCELACTIONREASON_ATTACKED;
}

// 0x52c240
void __cdecl PickupAction::cancelAction(::Action::CancelReason, wchar_t const *, int)
{
    LIFT_STUB(0x52c240);
}

// 0x52c640
void __cdecl PickupAction::failAction(::Action::FailReason)
{
    LIFT_STUB(0x52c640);
}

// 0x52c6a0
bool __cdecl PickupAction::openPartyAuction(::ItemPouch *, unsigned __int64 *const, int)
{
    LIFT_STUB(0x52c6a0);
}

// 0x52cd90
bool __cdecl LootAction::Initialize(::Zone *, ::Creature *, unsigned __int64)
{
    LIFT_STUB(0x52cd90);
}

// 0x52ce90
void __cdecl LootAction::startAction(void)
{
    LIFT_STUB(0x52ce90);
}

// 0x52d0e0
void __cdecl LootAction::failAction(::Action::FailReason)
{
    LIFT_STUB(0x52d0e0);
}

// 0x52d110
void __cdecl LootAction::finishAction(void)
{
    LIFT_STUB(0x52d110);
}

// 0x52d200
void __cdecl GatherAction::startAction(void)
{
    LIFT_STUB(0x52d200);
}

// 0x52d340
void __cdecl GatherAction::failAction(::Action::FailReason)
{
    LIFT_STUB(0x52d340);
}

// 0x52d370
void __cdecl GatherAction::finishAction(void)
{
    LIFT_STUB(0x52d370);
}

// 0x52d520
void __cdecl GatherAction::cancelAction(::Action::CancelReason, wchar_t const *, int)
{
    LIFT_STUB(0x52d520);
}

// 0x52d5b0
void __cdecl GatherCancelTask::start(void)
{
    LIFT_STUB(0x52d5b0);
}

// 0x52d640
void __cdecl UseSkillSkinAcquirementItemAction::startAction(void)
{
    LIFT_STUB(0x52d640);
}

// 0x52e170
void __cdecl UseSkillSkinAcquirementItemAction::failAction(::Action::FailReason)
{
    LIFT_STUB(0x52e170);
}

// 0x52e210
void __cdecl PickupFieldItemAction::startAction(void)
{
    LIFT_STUB(0x52e210);
}

// 0x52e500
void __cdecl PickupFieldItemAction::finishAction(void)
{
    LIFT_STUB(0x52e500);
}

// 0x52e5f0
void __cdecl PickupFieldItemAction::cancelAction(::Action::CancelReason, wchar_t const *, int)
{
    LIFT_STUB(0x52e5f0);
}

// 0x52e6a0
void __cdecl PickupFieldItemAction::failAction(::Action::FailReason)
{
    LIFT_STUB(0x52e6a0);
}

// 0x52e720
bool __cdecl PickupDeadBodyAction::availableCancel(::CancelActionReason reason)
{
    return reason == CANCELACTIONREASON_USER_REQUEST;
}

// 0x52e730
void __cdecl PutdownFieldItemAction::startAction(void)
{
    LIFT_STUB(0x52e730);
}

// 0x52e9f0
void __cdecl PutdownFieldItemAction::finishAction(void)
{
    LIFT_STUB(0x52e9f0);
}

// 0x52eb70
void __cdecl PutdownFieldItemAction::cancelAction(::Action::CancelReason, wchar_t const *, int)
{
    LIFT_STUB(0x52eb70);
}

// 0x52ec80
void __cdecl PutdownFieldItemAction::failAction(::Action::FailReason)
{
    LIFT_STUB(0x52ec80);
}

// 0x52ed00
bool __cdecl PutdownFieldItemAction::availableCancel(::CancelActionReason reason)
{
    switch (reason)  // LIFT: switch form (js, jg)
    {
    case CANCELACTIONREASON_USER_REQUEST:
    case CANCELACTIONREASON_MOVE:
        return true;
    default:
        return false;
    }
}

// 0x52ed10
void __cdecl PickupDeadBodyAction::startAction(void)
{
    LIFT_STUB(0x52ed10);
}

// 0x52f020
void __cdecl PickupDeadBodyAction::finishAction(void)
{
    LIFT_STUB(0x52f020);
}

// 0x52f110
void __cdecl PickupDeadBodyAction::cancelAction(::Action::CancelReason, wchar_t const *, int)
{
    LIFT_STUB(0x52f110);
}

// 0x52f1c0
void __cdecl PickupDeadBodyAction::failAction(::Action::FailReason)
{
    LIFT_STUB(0x52f1c0);
}

// 0x52f240
void __cdecl ExpandInventoryAction::startAction(void)
{
    LIFT_STUB(0x52f240);
}

// 0x52f560
bool __cdecl ExpandInventoryAction::checkNpcCond(void)
{
    LIFT_STUB(0x52f560);
}

// 0x52f720
void __cdecl ExpandInventoryAction::failAction(::Action::FailReason)
{
    LIFT_STUB(0x52f720);
}

// 0x52f750
void __cdecl RevealItemAbilityAction::startAction(void)
{
    LIFT_STUB(0x52f750);
}
