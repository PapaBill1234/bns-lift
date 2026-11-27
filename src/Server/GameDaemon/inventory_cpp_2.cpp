// inventory_cpp_2.cpp: inventory.cpp part 2 (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "inventory.h"
#include "accountinventorytran.h"
#include "item.h"
#include "propertytran.h"
#include "LiftStub.h"

// 0x4e6080
::GameFailReason __cdecl Inventory::R_PolishToItem(unsigned char, unsigned short, short, char const *const, unsigned __int64, unsigned __int64)
{
    LIFT_STUB(0x4e6080);
}

// 0x4e6d40
::GameFailReason __cdecl Inventory::ProcessItemFusion(int, ::Inventory::AcquireOrder *const, int, ::Inventory::DisposeOrderWithPos *const, unsigned __int64)
{
    LIFT_STUB(0x4e6d40);
}

// 0x4e7150
bool __cdecl Inventory::LockItem(unsigned char, short)
{
    LIFT_STUB(0x4e7150);
}

// 0x4e7300
bool __cdecl Inventory::UnlockItem(unsigned char, short)
{
    LIFT_STUB(0x4e7300);
}

// 0x4e7450
bool __cdecl Inventory::SetItemLockExpirationTime(unsigned char, short, __int64)
{
    LIFT_STUB(0x4e7450);
}

// 0x4e75b0
bool __cdecl Inventory::SetItemUsed(unsigned char, short)
{
    LIFT_STUB(0x4e75b0);
}

// 0x4e76f0
bool __cdecl Inventory::CanSetItemUsed(unsigned char, short)
{
    LIFT_STUB(0x4e76f0);
}

// 0x4e7850
short __cdecl Inventory::Rebuy(::Data::NpcRecordPtr, unsigned __int64, char)
{
    LIFT_STUB(0x4e7850);
}

// 0x4e80e0
bool __cdecl Inventory::DisposeAll(void)
{
    LIFT_STUB(0x4e80e0);
}

// 0x4e81d0
short __cdecl Inventory::Move(unsigned char, unsigned short, unsigned char, unsigned short, short)
{
    LIFT_STUB(0x4e81d0);
}

// 0x4ebbc0
bool __cdecl Inventory::Find(unsigned __int64, char, unsigned short &) const
{
    LIFT_STUB(0x4ebbc0);
}

// 0x4ebc80
short __cdecl Inventory::Equip(unsigned char, unsigned short, unsigned short)
{
    LIFT_STUB(0x4ebc80);
}

// 0x4eda60
short __cdecl Inventory::EquipBadge(unsigned char, unsigned short, unsigned char, unsigned short)
{
    LIFT_STUB(0x4eda60);
}

// 0x4ef7b0
short __cdecl Inventory::UnequipFactionItem(unsigned short, bool)
{
    LIFT_STUB(0x4ef7b0);
}

// 0x4effc0
short __cdecl Inventory::Unequip(unsigned short, unsigned short, bool)
{
    LIFT_STUB(0x4effc0);
}

// 0x4f08d0
bool __cdecl Inventory::hasNecessaryCostumeItem(::Data::ItemRecordPtr) const
{
    LIFT_STUB(0x4f08d0);
}

// 0x4f0a40
short __cdecl Inventory::unequip(unsigned short)
{
    LIFT_STUB(0x4f0a40);
}

// 0x4f0df0
short __cdecl Inventory::UnequipBadge(unsigned char, unsigned short, unsigned char, unsigned short, bool)
{
    LIFT_STUB(0x4f0df0);
}

// 0x4f2270
short __cdecl Inventory::unequipBadge(unsigned char, unsigned short)
{
    LIFT_STUB(0x4f2270);
}

// 0x4f24e0
void __cdecl Inventory::activateEquipGemSlot(void)
{
    LIFT_STUB(0x4f24e0);
}

// 0x4f2590
short __cdecl Inventory::AttachGemToWeapon(unsigned char, unsigned short, unsigned short, char)
{
    LIFT_STUB(0x4f2590);
}

// 0x4f38d0
short __cdecl Inventory::AttachEnchantGemToWeapon(unsigned char, unsigned short, unsigned short, char)
{
    LIFT_STUB(0x4f38d0);
}

// 0x4f47f0
unsigned int __cdecl Inventory::GetPredefinedItemGemId(int)
{
    LIFT_STUB(0x4f47f0);
}

// 0x4f4870
short __cdecl Inventory::DetachGemFromWeapon(unsigned char, unsigned short, char)
{
    LIFT_STUB(0x4f4870);
}

// 0x4f5600
short __cdecl Inventory::DetachEnchantGemFromWeapon(unsigned char, unsigned short, char)
{
    LIFT_STUB(0x4f5600);
}

// 0x4f6470
short __cdecl Inventory::ExpandWeaponGemSlot(unsigned char, unsigned short, unsigned short, unsigned char &, int &)
{
    LIFT_STUB(0x4f6470);
}

// 0x4f70d0
short __cdecl Inventory::AddWeaponGemSlot(unsigned char, unsigned short, short, unsigned char &, int &)
{
    LIFT_STUB(0x4f70d0);
}

// 0x4f7d70
short __cdecl Inventory::DeleteWeaponGemSlot(unsigned char, unsigned short, unsigned char, char, ::Inventory::DisposeOrderWithPos *const, short)
{
    LIFT_STUB(0x4f7d70);
}

// 0x4f8bd0
short __cdecl Inventory::OpenWeaponGemSlot(unsigned char, unsigned short, ::Inventory::DisposeOrderWithPos *const, short, char &)
{
    LIFT_STUB(0x4f8bd0);
}

// 0x4f9a70
bool __cdecl Inventory::PrepareEmptyPostions(unsigned short, unsigned short *const)
{
    LIFT_STUB(0x4f9a70);
}

// 0x4f9b70
bool __cdecl Inventory::AcquireToReservationPositions(char, ::Inventory::AcquireOrder *const, unsigned short const *const, ::Item **const)
{
    LIFT_STUB(0x4f9b70);
}

// 0x4f9e20
bool __cdecl Inventory::ReleaseReservationPositions(unsigned short, unsigned short const *const)
{
    LIFT_STUB(0x4f9e20);
}

// 0x4f9ee0
bool __cdecl Inventory::PrepareEmptyOrStackablePositions(char, ::Inventory::AcquireOrder *const, unsigned short *const, bool *const, unsigned short &)
{
    LIFT_STUB(0x4f9ee0);
}

// 0x4fa3a0
bool __cdecl Inventory::AcquireToReservedOrStackablePositions(char, ::Inventory::AcquireOrder *const, unsigned short const *const, unsigned short *const, char *const, bool const *const, ::PropertyTransactionSyncFetch::SyncItem &)
{
    LIFT_STUB(0x4fa3a0);
}

// 0x4fa7a0
bool __cdecl Inventory::ReleaseReservedOrStackablePositions(unsigned short, unsigned short const *const, char const *const, bool const *const)
{
    LIFT_STUB(0x4fa7a0);
}

// 0x4faa70
unsigned short __cdecl Inventory::PrepareEmptyPos(void)
{
    LIFT_STUB(0x4faa70);
}

// 0x4fab40
bool __cdecl Inventory::TryWarehouseItemAcquisition(__int64, ::Inventory::AcquireOrderWithDuration &, unsigned short, ::AccountInventoryTakeWarehouseItemTran *)
{
    LIFT_STUB(0x4fab40);
}

// 0x4fb2a0
bool __cdecl Inventory::AcquireToReservationPos(::Inventory::AcquireOrder &, unsigned short, unsigned __int64, unsigned __int64)
{
    LIFT_STUB(0x4fb2a0);
}

// 0x4fb560
bool __cdecl Inventory::AcquireToReservationPos(::Inventory::AcquireOrder &, unsigned short, bool, bool, __int64, char, __int64, char const *const)
{
    LIFT_STUB(0x4fb560);
}

// 0x4fb930
short __cdecl Inventory::IdentifyItem(unsigned short, unsigned short)
{
    LIFT_STUB(0x4fb930);
}

// 0x4fc510
short __cdecl Inventory::UnsealItem2(unsigned short, char, ::Inventory::DisposeOrderWithPos *const, short)
{
    LIFT_STUB(0x4fc510);
}

// 0x4fd5d0
void __cdecl Inventory::RepairAll(unsigned char *const, unsigned short *const, int)
{
    LIFT_STUB(0x4fd5d0);
}

// 0x4fdd60
bool __cdecl Inventory::Repair(unsigned short, int)
{
    LIFT_STUB(0x4fdd60);
}

// 0x4fe390
short __cdecl Inventory::FeedPetFood(unsigned char, unsigned short, unsigned short, unsigned char)
{
    LIFT_STUB(0x4fe390);
}

// 0x4fefd0
short __cdecl Inventory::SealItem(unsigned short, ::Inventory::DisposeOrderWithPos *const, short)
{
    LIFT_STUB(0x4fefd0);
}

// 0x4ffe90
void __cdecl Inventory::invokeAwakeningFailEffect(::Data::ItemRecordPtr const &)
{
    LIFT_STUB(0x4ffe90);
}

// 0x4fff50
bool __cdecl Inventory::checkDecomposeItem2(::Data::ItemRecordPtr, char, ::Inventory::DisposeOrderWithPos *const, short, char)
{
    LIFT_STUB(0x4fff50);
}

// 0x500270
short __cdecl Inventory::DecomposeItem2(char, unsigned short, char, ::Inventory::DisposeOrderWithPos *const, short, char, char, ::SelectedRewardItemIndexInfo *)
{
    LIFT_STUB(0x500270);
}

// 0x501f40
bool __cdecl Inventory::CheckActivatedEquipGemSot(unsigned short)
{
    LIFT_STUB(0x501f40);
}

// 0x502120
bool __cdecl Inventory::consumeDurability(void)
{
    LIFT_STUB(0x502120);
}

// 0x502380
void __cdecl Inventory::ConsumeDurabilityByHit(void)
{
    LIFT_STUB(0x502380);
}

// 0x502430
void __cdecl Inventory::ConsumeDurabilityByAttacked(void)
{
    LIFT_STUB(0x502430);
}

// 0x5024e0
void __cdecl Inventory::ConsumeDurabilityByParry(void)
{
    LIFT_STUB(0x5024e0);
}

// 0x502590
void __cdecl Inventory::ConsumeDurabilityByDead(void)
{
    LIFT_STUB(0x502590);
}

// 0x502820
void __cdecl Inventory::ConsumePetDurability(void)
{
    LIFT_STUB(0x502820);
}

// 0x502bf0
void __cdecl Inventory::clearDepot(unsigned char)
{
    LIFT_STUB(0x502bf0);
}

// 0x502cf0
bool __cdecl Inventory::reallocSystemDepot(short)
{
    LIFT_STUB(0x502cf0);
}

// 0x502df0
bool __cdecl Inventory::addToSystemDepot(::Item *, int *)
{
    LIFT_STUB(0x502df0);
}

// 0x502f20
bool __cdecl Inventory::acquireForRandomBoxDepot(int, ::Inventory::AcquireOrder const *const)
{
    LIFT_STUB(0x502f20);
}

// 0x503270
bool __cdecl Inventory::isValidPos(unsigned char, unsigned short) const
{
    LIFT_STUB(0x503270);
}

// 0x5032b0
bool __cdecl Inventory::isEmptySlot(unsigned char, unsigned short) const
{
    LIFT_STUB(0x5032b0);
}

// 0x503310
short __cdecl Inventory::getExpandedSlotCount(unsigned char) const
{
    LIFT_STUB(0x503310);
}

// 0x503390
bool __cdecl Inventory::setItem(unsigned char, unsigned short, ::Item *)
{
    LIFT_STUB(0x503390);
}

// 0x5034b0
bool __cdecl Inventory::isDisposableItem(::Item const *, ::ItemReason) const
{
    LIFT_STUB(0x5034b0);
}

// 0x503530
bool __cdecl Inventory::dispose(unsigned char, ::Inventory::DisposeOrder const *, ::ItemReason, ::InventoryClientUpdate *, ::InventoryCacheUpdate *, short &)
{
    LIFT_STUB(0x503530);
}

// 0x503f50
bool __cdecl Inventory::dispose(unsigned char, unsigned __int64, ::ItemReason)
{
    LIFT_STUB(0x503f50);
}

// 0x504a60
bool __cdecl Inventory::setUsed(::Item *)
{
    LIFT_STUB(0x504a60);
}

// 0x504ab0
bool __cdecl Inventory::checkRestoreOne(::Data::ItemRecordPtr, unsigned short *) const
{
    LIFT_STUB(0x504ab0);
}

// 0x504c30
bool __cdecl Inventory::checkEquip(::Item const *, unsigned short, unsigned char) const
{
    LIFT_STUB(0x504c30);
}

// 0x5053f0
bool __cdecl Inventory::checkEquipType(::Data::ItemRecordPtr, unsigned short) const
{
    LIFT_STUB(0x5053f0);
}

// 0x505650
bool __cdecl Inventory::checkBadgeEquipType(::Data::ItemRecordPtr, unsigned short) const
{
    LIFT_STUB(0x505650);
}

// 0x5058e0
short __cdecl Inventory::checkEquipItem(::Item const *, unsigned char, unsigned short, unsigned char, unsigned short) const
{
    LIFT_STUB(0x5058e0);
}

// 0x505db0
void __cdecl Inventory::CheckPreequippedAccessoryConditionAndUnequip(::std::vector< ::Item *, ::StlAllocator< ::Item *, 2> > &)
{
    LIFT_STUB(0x505db0);
}

// 0x506260
void __cdecl Inventory::collapseEffect(unsigned short)
{
    LIFT_STUB(0x506260);
}

// 0x5063d0
__int64 __cdecl Inventory::calcWeaponGemDetachCost(::Data::ItemRecordGemPtr &)
{
    LIFT_STUB(0x5063d0);
}

// 0x506610
char __cdecl Inventory::addSetItemCount(::Item *)
{
    LIFT_STUB(0x506610);
}

// 0x5066e0
char __cdecl Inventory::deleteSetItemCount(::Item *)
{
    LIFT_STUB(0x5066e0);
}

// 0x5067d0
void __cdecl Inventory::equipSetItem(::Item *, unsigned short)
{
    LIFT_STUB(0x5067d0);
}

// 0x506920
void __cdecl Inventory::unequipSetItem(::Item *)
{
    LIFT_STUB(0x506920);
}

// 0x506a60
bool __cdecl Inventory::invokeSetItemEffect(char)
{
    LIFT_STUB(0x506a60);
}

// 0x506d30
bool __cdecl Inventory::invokeSetBadgeEffect(void)
{
    LIFT_STUB(0x506d30);
}

// 0x506f20
bool __cdecl Inventory::addSoldItem(::Item *)
{
    LIFT_STUB(0x506f20);
}

// 0x507050
bool __cdecl Inventory::removeSoldItem(char)
{
    LIFT_STUB(0x507050);
}

// 0x5071e0
unsigned short __cdecl Inventory::getStackableItemPos(::Data::ItemRecordGroceryPtr, short, unsigned char)
{
    LIFT_STUB(0x5071e0);
}

// 0x5073b0
bool __cdecl Inventory::AddTradeSuggestion(unsigned short, short, ::Item **)
{
    LIFT_STUB(0x5073b0);
}

// 0x5077a0
bool __cdecl Inventory::RemoveTradeSuggestion(unsigned short)
{
    LIFT_STUB(0x5077a0);
}

// 0x507920
bool __cdecl Inventory::CheckTradeSuggestion(void) const
{
    LIFT_STUB(0x507920);
}

// 0x507960
char __cdecl Inventory::TakeoutTradeSuggestion(::Item **const)
{
    LIFT_STUB(0x507960);
}

// 0x507ab0
void __cdecl Inventory::RollbackTradeItems(void)
{
    LIFT_STUB(0x507ab0);
}

// 0x507d10
void __cdecl Inventory::ConfirmTradeItems(::Item **const, bool)
{
    LIFT_STUB(0x507d10);
}

// 0x507f30
void __cdecl Inventory::addItemToBag(::Item *, ::InventoryClientUpdate &, ::InventoryCacheUpdate &)
{
    LIFT_STUB(0x507f30);
}

// 0x5081b0
bool __cdecl Inventory::addTimeLimitItem(::TimeLimitItem *)
{
    LIFT_STUB(0x5081b0);
}

// 0x508220
void __cdecl Inventory::processPQTimeLimitItem(void)
{
    LIFT_STUB(0x508220);
}

// 0x5083e0
void __cdecl Inventory::expireTimeLimitItem(::Item const *)
{
    LIFT_STUB(0x5083e0);
}

// 0x508870
void __cdecl Inventory::RefreshGuildUsedItemEquipEffect(void)
{
    LIFT_STUB(0x508870);
}

// 0x508930
bool __cdecl Inventory::CheckDisposableItems(unsigned __int64, short, short, short, short const *const, short const *const, ::Item **const)
{
    LIFT_STUB(0x508930);
}

// 0x508bf0
bool __cdecl Inventory::CheckDisposableSortedMultipleItems(int, unsigned __int64 const *const, short const *const, short, short const *const, short const *const, ::Item **const)
{
    LIFT_STUB(0x508bf0);
}

// 0x509390
unsigned short __cdecl Inventory::FindEquipedItemNecessaryCostumeItem(::Data::ItemRecordPtr) const
{
    LIFT_STUB(0x509390);
}

// 0x5094f0
bool __cdecl Inventory::checkAvailableBadgeDepository(unsigned short)
{
    LIFT_STUB(0x5094f0);
}

// 0x509670
bool __cdecl Inventory::combineCostGroup(unsigned __int64, unsigned __int64, ::Inventory::DisposeOrderForCostGroup *const, int &, __int64 &)
{
    LIFT_STUB(0x509670);
}

// 0x509850
bool __cdecl Inventory::makeDisposeOrderFromCostGroup(::Data::CostGroupRecordPtr, unsigned short, ::Inventory::DisposeOrderWithPos const *const, int &, ::Inventory::DisposeOrderWithPos *const, __int64 &)
{
    LIFT_STUB(0x509850);
}

// 0x509e50
bool __cdecl Inventory::makeDisposeOrder(int, ::Inventory::DisposeOrderForCostGroup const *const, int &, ::Inventory::DisposeOrderWithPos *const)
{
    LIFT_STUB(0x509e50);
}
