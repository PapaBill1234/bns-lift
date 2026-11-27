// inventory.h: inventory.cpp, inventory.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"
#include "propertytran.h"

class Inventory
{
public:
    struct AcquireOrder {};
    struct AcquireOrderWithDbId {};
    struct AcquireOrderWithDuration {};
    struct CloneOrderWithDbId {};
    struct DisposeOrder {};
    struct DisposeOrderForCostGroup {};
    struct DisposeOrderWithPos  // PDB layout (size 0x4)
    {
        unsigned short pos;  // +0x0
        short count;         // +0x2
    };
    enum ItemTransitType {};
    struct SetItemInfo {};
public:
    short __cdecl GetEmptyBagSlotCount(void) const;  // 0x34f000
    static bool __cdecl IsActivatedGemSlot(unsigned int);  // 0x4bec40
    static bool __cdecl CheckActivatedGemSlotExist(::Item const *);  // 0x4becb0
    static char __cdecl GetCacheId(::Item const *);  // 0x4bed10
    static void __cdecl Cleanup(::std::vector< ::Item *, ::StlAllocator< ::Item *, 2> > &);  // 0x4bed60
    __cdecl Inventory(void);  // 0x4bee00
    __cdecl ~Inventory(void);  // 0x4bef10
    bool __cdecl Initialize(::Pc *, short *const);  // 0x4bf140
    int __cdecl SetDbData(::ItemClass, short, char const *, int, ::std::vector< ::Item *, ::StlAllocator< ::Item *, 2> > &);  // 0x4bf2a0
    void __cdecl SetInvalidPosItems(::std::vector< ::Item *, ::StlAllocator< ::Item *, 2> > &);  // 0x4bfaa0
    void __cdecl SendItemList(void);  // 0x4bfd80
    void __cdecl FetchItemListForBuilder(::FragmentPacket &);  // 0x4bfef0
    void __cdecl SendRebuyItemList(void);  // 0x4c0130
    void __cdecl EnterZone(::EnterReason);  // 0x4c0490
    void __cdecl ActivateEquipBadgeAbility(void);  // 0x4c06c0
    void __cdecl DeactivateEquipBadgeAbility(void);  // 0x4c0920
    void __cdecl RefreshEquipEffect(void);  // 0x4c0ad0
    void __cdecl CollapseEquipEffect(void);  // 0x4c0c80
    void __cdecl InvokeEquipEffect(void);  // 0x4c0d60
    ::Item * __cdecl GetItem(unsigned char, unsigned short) const;  // 0x4c0e40
    ::Inventory::SetItemInfo const *const __cdecl GetSkillSkinSetItemInfo(short) const;  // 0x4c0ef0
    static ::ItemClass __cdecl GetItemClass(short);  // 0x4c10d0
    static bool __cdecl AddRevealItemAbility(::Data::EffectRecordItemAbility &, ::Data::ItemRecordPtr, char, int);  // 0x4c1150
    static bool __cdecl AddItemAbilityBySeq(::Data::EffectRecordItemAbility &, ::Data::ItemRecordPtr, char, int, bool);  // 0x4c1c10
    static short __cdecl CalcRevealedItemAbility(::Data::ItemRecordPtr, char, short, short &);  // 0x4c2670
    static char __cdecl GetItemTypeFromCondType(char);  // 0x4c3610
    static bool __cdecl CheckItemCondType(::Data::ItemRecordPtr const &, char);  // 0x4c3720
    static char __cdecl GetBadgeCategory(::Data::ItemRecordGroceryPtr);  // 0x4c3d90
    bool __cdecl CheckAcquire(int, ::Inventory::AcquireOrder const *const) const;  // 0x4c3df0
    bool __cdecl CheckAcquire(int, ::Inventory::AcquireOrderWithDbId const *const) const;  // 0x4c4220
    bool __cdecl Acquire(int, ::Inventory::AcquireOrder *const, int *, unsigned short *const);  // 0x4c4640
    bool __cdecl AcquireWithSpirit(int, ::Inventory::AcquireOrder *const, int, char *const, int *const, int &, unsigned short *const);  // 0x4c54e0
    bool __cdecl AcquireWeaponItem(int, ::Inventory::AcquireOrder *const, bool, unsigned int *const, bool, unsigned int, char, bool, int, char *const, int *const, int &, unsigned short *const);  // 0x4c5d30
    bool __cdecl AcquirePostAttachment(__int64, char, __int64, ::Inventory::AcquireOrderWithDbId const *);  // 0x4c62b0
    bool __cdecl AcquireEnvReward(int, ::Inventory::AcquireOrder *const);  // 0x4c6e30
    bool __cdecl Clone(int, ::Inventory::CloneOrderWithDbId const *const);  // 0x4c6f80
    bool __cdecl ClonePostAttachment(__int64, char, __int64, ::Inventory::CloneOrderWithDbId const *);  // 0x4c7d90
    void __cdecl ConfirmAcquire(unsigned __int64, unsigned __int64, __int64, char);  // 0x4c8960
    void __cdecl ConfirmAcquirePostAttachment(short, unsigned __int64);  // 0x4c9d50
    void __cdecl FailConfirmAcquirePostAttachment(short);  // 0x4ca810
    void __cdecl ConfirmAcquireTakeGuildCraft(unsigned __int64, unsigned __int64);  // 0x4ca920
    void __cdecl FailToConfirmAcquireByPropertyTransaction(unsigned __int64);  // 0x4cafa0
    void __cdecl ConfirmAcquireReservedClosetItem(unsigned __int64, unsigned __int64, ::ItemReason);  // 0x4cb0e0
    void __cdecl FailConfirmAcquireReservedClosetItem(unsigned __int64);  // 0x4cb8f0
    void __cdecl FailConfirmAcquire(unsigned __int64, unsigned __int64, short);  // 0x4cba30
    void __cdecl ConfirmAcquireRankingRewardItem(unsigned __int64, unsigned __int64, char, int, char, short, short, int);  // 0x4cbb20
    void __cdecl ConfirmAcquireDuelBotTrainingRoomRewardItem(unsigned __int64, unsigned __int64, short, char, char, bool, char, unsigned short);  // 0x4cc0c0
    void __cdecl ConfirmAcquireChangeWeaponAppearance(short, unsigned __int64);  // 0x4cc700
    void __cdecl ConfirmAcquireAchievementRewardItem(wchar_t const *, unsigned __int64, unsigned __int64, ::ItemReason, bool, char, unsigned short);  // 0x4cd1c0
private:
    void __cdecl writeGameLogGetItem(::Item *, short);  // 0x4cda60
public:
    void __cdecl ConfirmAcquirePropertyTransaction(char, char, unsigned __int64, unsigned __int64, char, short, ::ItemReason, void *);  // 0x4cdea0
private:
    void __cdecl writeGameLog(char, ::Item *, void *);  // 0x4ce2b0
public:
    bool __cdecl CheckDispose(::Inventory::DisposeOrder const *, ::ItemReason) const;  // 0x4ce8e0
    bool __cdecl Dispose(::Inventory::DisposeOrder const *, ::ItemReason);  // 0x4ce9f0
    bool __cdecl CheckDispose(int, ::Inventory::DisposeOrderWithPos const *const, ::ItemReason) const;  // 0x4cebc0
    bool __cdecl Dispose(int, ::Inventory::DisposeOrderWithPos const *const, ::ItemReason, unsigned __int64, wchar_t const *);  // 0x4cede0
    bool __cdecl Dispose(unsigned short, short, ::ItemReason);  // 0x4cfcc0
    bool __cdecl CheckDisposeWithDepot(char, int, ::Inventory::DisposeOrderWithPos const *const, ::ItemReason) const;  // 0x4cfd00
    bool __cdecl DisposeWithDepot(char, int, ::Inventory::DisposeOrderWithPos const *const, ::ItemReason, unsigned __int64);  // 0x4cff00
    char __cdecl PawnItemInItems(unsigned short);  // 0x4d0dc0
    char __cdecl SplitPawn(::Item *, short);  // 0x4d0eb0
    bool __cdecl RollbackPawn(void);  // 0x4d1310
    void __cdecl ClearPawn(bool);  // 0x4d1950
    bool __cdecl SequesterItem(unsigned char, unsigned short, bool);  // 0x4d1bd0
    char __cdecl MoveToTransitItems(unsigned short, short, short, wchar_t *, short, wchar_t *);  // 0x4d2100
    bool __cdecl MoveToTransitItemList(short, short const *const, short const *const, short &, ::PropertyTransactionSyncFetch::SyncItem &, char *const, ::Item **const);  // 0x4d2720
    char __cdecl HideFromInventory(unsigned short, short, ::Inventory::ItemTransitType, ::PropertyTransactionSyncFetch::ItemData *);  // 0x4d28f0
    bool __cdecl RollbackTransitItems(char, char *const);  // 0x4d3050
    bool __cdecl RollbackTransitOccupiedItems(char, char *const);  // 0x4d3e80
    ::GameFailReason __cdecl AcquirePropertyTransaction(::PropertyTransactionSyncFetchEx &, char, ::Inventory::AcquireOrder *const, ::SyncContext *);  // 0x4d4dd0
    void __cdecl ReleasePropertyTransaction(::SyncContext &);  // 0x4d5630
private:
    void __cdecl rollbackTransitItem(short);  // 0x4d5730
public:
    void __cdecl RollbackTransitItems(short, unsigned __int64 const *const, short const *const, char const *const);  // 0x4d6480
    void __cdecl ClearTransitItems(short, char const *const, short const *const);  // 0x4d65b0
private:
    void __cdecl clearTransitItem(char, short);  // 0x4d6610
public:
    char __cdecl MoveToTransitItem(unsigned short, int, ::OpXmlData const *, ::PropertyTransactionSyncData &, ::SyncContext *, ::ItemReason);  // 0x4d73a0
    void __cdecl ClearTransitItem(char, char, int, ::OpXmlData const *, ::ItemReason);  // 0x4d8200
private:
    void __cdecl arrangeItem(::Item *, short, ::ItemReason);  // 0x4d8ff0
public:
    void __cdecl RollbackTransitItem(char, char, char, int, ::OpXmlData const *);  // 0x4d97c0
private:
    void __cdecl addAmountTransitItem(char, short, unsigned short, bool, ::ItemReason, wchar_t const *);  // 0x4d99c0
    bool __cdecl insertPropertyTransaction(::Item const *, ::PropertyTransactionSyncData &, unsigned __int64);  // 0x4da0a0
    bool __cdecl deletePropertyTransaction(::Item const *, ::PropertyTransactionSyncData &);  // 0x4da230
    bool __cdecl updatePropertyTransaction(::Item const *, ::PropertyTransactionSyncData &, int, ::OpXmlData const *);  // 0x4da420
public:
    ::GameFailReason __cdecl Expand(char, bool, int, ::Inventory::DisposeOrderWithPos *);  // 0x4da7e0
    ::GameFailReason __cdecl ExpandSkillPage2(char, wchar_t const *, int, ::Inventory::DisposeOrderWithPos *);  // 0x4db2d0
    ::GameFailReason __cdecl RevealItemAbility(unsigned char, short, short, char, int, ::Inventory::DisposeOrderWithPos *const);  // 0x4dba20
    ::GameFailReason __cdecl AttachEquipGemPiece(unsigned char, short, short, int, ::Inventory::DisposeOrderWithPos *const);  // 0x4dd2a0
private:
    ::GameFailReason __cdecl checkGrowthMaterial(::Data::ItemRecordPtr, int, ::Inventory::DisposeOrderWithPos *const, bool);  // 0x4de650
public:
    ::GameFailReason __cdecl GrowthItem(unsigned char, short, short, short, int, ::Inventory::DisposeOrderWithPos *const);  // 0x4dec80
    ::GameFailReason __cdecl AwakeningItem(unsigned char, short, short, int, ::Inventory::DisposeOrderWithPos *const, int, ::Inventory::DisposeOrderWithPos *const);  // 0x4e0900
    ::GameFailReason __cdecl FeedingRandomStatEquipGem(unsigned char, short, short, int, ::Inventory::DisposeOrderWithPos *const, int, ::Inventory::DisposeOrderWithPos *const);  // 0x4e22c0
    ::GameFailReason __cdecl R_EnchantToItem(unsigned char, unsigned short, unsigned __int64);  // 0x4e3ec0
    ::GameFailReason __cdecl R_ResetEnchantItemInfo(unsigned char, short);  // 0x4e4b80
    ::GameFailReason __cdecl R_ResetEnchantRestoreInfo(unsigned char, short);  // 0x4e4f30
    ::GameFailReason __cdecl R_RestoreEnchantFailedItem(unsigned char, unsigned short, unsigned short, unsigned __int64);  // 0x4e52e0
    ::GameFailReason __cdecl R_PolishToItem(unsigned char, unsigned short, short, char const *const, unsigned __int64, unsigned __int64);  // 0x4e6080
    ::GameFailReason __cdecl ProcessItemFusion(int, ::Inventory::AcquireOrder *const, int, ::Inventory::DisposeOrderWithPos *const, unsigned __int64);  // 0x4e6d40
    bool __cdecl LockItem(unsigned char, short);  // 0x4e7150
    bool __cdecl UnlockItem(unsigned char, short);  // 0x4e7300
    bool __cdecl SetItemLockExpirationTime(unsigned char, short, __int64);  // 0x4e7450
    bool __cdecl SetItemUsed(unsigned char, short);  // 0x4e75b0
    bool __cdecl CanSetItemUsed(unsigned char, short);  // 0x4e76f0
    short __cdecl Rebuy(::Data::NpcRecordPtr, unsigned __int64, char);  // 0x4e7850
    bool __cdecl DisposeAll(void);  // 0x4e80e0
    short __cdecl Move(unsigned char, unsigned short, unsigned char, unsigned short, short);  // 0x4e81d0
    bool __cdecl Find(unsigned __int64, char, unsigned short &) const;  // 0x4ebbc0
    short __cdecl Equip(unsigned char, unsigned short, unsigned short);  // 0x4ebc80
    short __cdecl EquipBadge(unsigned char, unsigned short, unsigned char, unsigned short);  // 0x4eda60
    short __cdecl UnequipFactionItem(unsigned short, bool);  // 0x4ef7b0
    short __cdecl Unequip(unsigned short, unsigned short, bool);  // 0x4effc0
private:
    bool __cdecl hasNecessaryCostumeItem(::Data::ItemRecordPtr) const;  // 0x4f08d0
    short __cdecl unequip(unsigned short);  // 0x4f0a40
public:
    short __cdecl UnequipBadge(unsigned char, unsigned short, unsigned char, unsigned short, bool);  // 0x4f0df0
private:
    short __cdecl unequipBadge(unsigned char, unsigned short);  // 0x4f2270
    void __cdecl activateEquipGemSlot(void);  // 0x4f24e0
public:
    short __cdecl AttachGemToWeapon(unsigned char, unsigned short, unsigned short, char);  // 0x4f2590
    short __cdecl AttachEnchantGemToWeapon(unsigned char, unsigned short, unsigned short, char);  // 0x4f38d0
    unsigned int __cdecl GetPredefinedItemGemId(int);  // 0x4f47f0
    short __cdecl DetachGemFromWeapon(unsigned char, unsigned short, char);  // 0x4f4870
    short __cdecl DetachEnchantGemFromWeapon(unsigned char, unsigned short, char);  // 0x4f5600
    short __cdecl ExpandWeaponGemSlot(unsigned char, unsigned short, unsigned short, unsigned char &, int &);  // 0x4f6470
    short __cdecl AddWeaponGemSlot(unsigned char, unsigned short, short, unsigned char &, int &);  // 0x4f70d0
    short __cdecl DeleteWeaponGemSlot(unsigned char, unsigned short, unsigned char, char, ::Inventory::DisposeOrderWithPos *const, short);  // 0x4f7d70
    short __cdecl OpenWeaponGemSlot(unsigned char, unsigned short, ::Inventory::DisposeOrderWithPos *const, short, char &);  // 0x4f8bd0
    bool __cdecl PrepareEmptyPostions(unsigned short, unsigned short *const);  // 0x4f9a70
    bool __cdecl AcquireToReservationPositions(char, ::Inventory::AcquireOrder *const, unsigned short const *const, ::Item **const);  // 0x4f9b70
    bool __cdecl ReleaseReservationPositions(unsigned short, unsigned short const *const);  // 0x4f9e20
    bool __cdecl PrepareEmptyOrStackablePositions(char, ::Inventory::AcquireOrder *const, unsigned short *const, bool *const, unsigned short &);  // 0x4f9ee0
    bool __cdecl AcquireToReservedOrStackablePositions(char, ::Inventory::AcquireOrder *const, unsigned short const *const, unsigned short *const, char *const, bool const *const, ::PropertyTransactionSyncFetch::SyncItem &);  // 0x4fa3a0
    bool __cdecl ReleaseReservedOrStackablePositions(unsigned short, unsigned short const *const, char const *const, bool const *const);  // 0x4fa7a0
    unsigned short __cdecl PrepareEmptyPos(void);  // 0x4faa70
    bool __cdecl TryWarehouseItemAcquisition(__int64, ::Inventory::AcquireOrderWithDuration &, unsigned short, ::AccountInventoryTakeWarehouseItemTran *);  // 0x4fab40
    bool __cdecl AcquireToReservationPos(::Inventory::AcquireOrder &, unsigned short, unsigned __int64, unsigned __int64);  // 0x4fb2a0
    bool __cdecl AcquireToReservationPos(::Inventory::AcquireOrder &, unsigned short, bool, bool, __int64, char, __int64, char const *const);  // 0x4fb560
    short __cdecl IdentifyItem(unsigned short, unsigned short);  // 0x4fb930
    short __cdecl UnsealItem2(unsigned short, char, ::Inventory::DisposeOrderWithPos *const, short);  // 0x4fc510
    void __cdecl RepairAll(unsigned char *const, unsigned short *const, int);  // 0x4fd5d0
    bool __cdecl Repair(unsigned short, int);  // 0x4fdd60
    short __cdecl FeedPetFood(unsigned char, unsigned short, unsigned short, unsigned char);  // 0x4fe390
    short __cdecl SealItem(unsigned short, ::Inventory::DisposeOrderWithPos *const, short);  // 0x4fefd0
private:
    void __cdecl invokeAwakeningFailEffect(::Data::ItemRecordPtr const &);  // 0x4ffe90
    bool __cdecl checkDecomposeItem2(::Data::ItemRecordPtr, char, ::Inventory::DisposeOrderWithPos *const, short, char);  // 0x4fff50
public:
    short __cdecl DecomposeItem2(char, unsigned short, char, ::Inventory::DisposeOrderWithPos *const, short, char, char, ::SelectedRewardItemIndexInfo *);  // 0x500270
    bool __cdecl CheckActivatedEquipGemSot(unsigned short);  // 0x501f40
private:
    bool __cdecl consumeDurability(void);  // 0x502120
public:
    void __cdecl ConsumeDurabilityByHit(void);  // 0x502380
    void __cdecl ConsumeDurabilityByAttacked(void);  // 0x502430
    void __cdecl ConsumeDurabilityByParry(void);  // 0x5024e0
    void __cdecl ConsumeDurabilityByDead(void);  // 0x502590
    void __cdecl ConsumePetDurability(void);  // 0x502820
private:
    void __cdecl clearDepot(unsigned char);  // 0x502bf0
    bool __cdecl reallocSystemDepot(short);  // 0x502cf0
    bool __cdecl addToSystemDepot(::Item *, int *);  // 0x502df0
    bool __cdecl acquireForRandomBoxDepot(int, ::Inventory::AcquireOrder const *const);  // 0x502f20
    bool __cdecl isValidPos(unsigned char, unsigned short) const;  // 0x503270
    bool __cdecl isEmptySlot(unsigned char, unsigned short) const;  // 0x5032b0
    short __cdecl getExpandedSlotCount(unsigned char) const;  // 0x503310
    bool __cdecl setItem(unsigned char, unsigned short, ::Item *);  // 0x503390
    bool __cdecl isDisposableItem(::Item const *, ::ItemReason) const;  // 0x5034b0
    bool __cdecl dispose(unsigned char, ::Inventory::DisposeOrder const *, ::ItemReason, ::InventoryClientUpdate *, ::InventoryCacheUpdate *, short &);  // 0x503530
    bool __cdecl dispose(unsigned char, unsigned __int64, ::ItemReason);  // 0x503f50
    bool __cdecl setUsed(::Item *);  // 0x504a60
    bool __cdecl checkRestoreOne(::Data::ItemRecordPtr, unsigned short *) const;  // 0x504ab0
    bool __cdecl checkEquip(::Item const *, unsigned short, unsigned char) const;  // 0x504c30
    bool __cdecl checkEquipType(::Data::ItemRecordPtr, unsigned short) const;  // 0x5053f0
    bool __cdecl checkBadgeEquipType(::Data::ItemRecordPtr, unsigned short) const;  // 0x505650
    short __cdecl checkEquipItem(::Item const *, unsigned char, unsigned short, unsigned char, unsigned short) const;  // 0x5058e0
public:
    void __cdecl CheckPreequippedAccessoryConditionAndUnequip(::std::vector< ::Item *, ::StlAllocator< ::Item *, 2> > &);  // 0x505db0
private:
    void __cdecl collapseEffect(unsigned short);  // 0x506260
    __int64 __cdecl calcWeaponGemDetachCost(::Data::ItemRecordGemPtr &);  // 0x5063d0
    char __cdecl addSetItemCount(::Item *);  // 0x506610
    char __cdecl deleteSetItemCount(::Item *);  // 0x5066e0
    void __cdecl equipSetItem(::Item *, unsigned short);  // 0x5067d0
    void __cdecl unequipSetItem(::Item *);  // 0x506920
    bool __cdecl invokeSetItemEffect(char);  // 0x506a60
    bool __cdecl invokeSetBadgeEffect(void);  // 0x506d30
    bool __cdecl addSoldItem(::Item *);  // 0x506f20
    bool __cdecl removeSoldItem(char);  // 0x507050
    unsigned short __cdecl getStackableItemPos(::Data::ItemRecordGroceryPtr, short, unsigned char);  // 0x5071e0
public:
    bool __cdecl AddTradeSuggestion(unsigned short, short, ::Item **);  // 0x5073b0
    bool __cdecl RemoveTradeSuggestion(unsigned short);  // 0x5077a0
    bool __cdecl CheckTradeSuggestion(void) const;  // 0x507920
    char __cdecl TakeoutTradeSuggestion(::Item **const);  // 0x507960
    void __cdecl RollbackTradeItems(void);  // 0x507ab0
    void __cdecl ConfirmTradeItems(::Item **const, bool);  // 0x507d10
private:
    void __cdecl addItemToBag(::Item *, ::InventoryClientUpdate &, ::InventoryCacheUpdate &);  // 0x507f30
    bool __cdecl addTimeLimitItem(::TimeLimitItem *);  // 0x5081b0
    void __cdecl processPQTimeLimitItem(void);  // 0x508220
    void __cdecl expireTimeLimitItem(::Item const *);  // 0x5083e0
public:
    void __cdecl RefreshGuildUsedItemEquipEffect(void);  // 0x508870
    bool __cdecl CheckDisposableItems(unsigned __int64, short, short, short, short const *const, short const *const, ::Item **const);  // 0x508930
    bool __cdecl CheckDisposableSortedMultipleItems(int, unsigned __int64 const *const, short const *const, short, short const *const, short const *const, ::Item **const);  // 0x508bf0
    unsigned short __cdecl FindEquipedItemNecessaryCostumeItem(::Data::ItemRecordPtr) const;  // 0x509390
private:
    bool __cdecl checkAvailableBadgeDepository(unsigned short);  // 0x5094f0
    bool __cdecl combineCostGroup(unsigned __int64, unsigned __int64, ::Inventory::DisposeOrderForCostGroup *const, int &, __int64 &);  // 0x509670
    bool __cdecl makeDisposeOrderFromCostGroup(::Data::CostGroupRecordPtr, unsigned short, ::Inventory::DisposeOrderWithPos const *const, int &, ::Inventory::DisposeOrderWithPos *const, __int64 &);  // 0x509850
    bool __cdecl makeDisposeOrder(int, ::Inventory::DisposeOrderForCostGroup const *const, int &, ::Inventory::DisposeOrderWithPos *const);  // 0x509e50

    // PDB data members (partial layout, size 0x5B8).
private:
    ::Pc* owner;                                  // +0x000
    unsigned __int64 _depotList[13][4];           // +0x008. LIFT: the PDB type is Inventory::Depot[13] (0x20 each), not declared yet
    unsigned __int64 _setItemList[38][2];         // +0x1A8. LIFT: the PDB type is Inventory::SetItemInfo[38] (0x10 each), not declared yet
    char _setItemListCount;                       // +0x408
    char _soldFront;                              // +0x409
    char _soldRear;                               // +0x40A
    ::Item* _soldItems[11];                       // +0x410
    ::Item* _pawnItems[11];                       // +0x468
    char _pawnItemCount;                          // +0x4C0
    ::Item* _tranItems[11];                       // +0x4C8
    char _tranItemCount;                          // +0x520
    bool _leavedZone;                             // +0x521
    ::Item* _tradeItems[9];                       // +0x528
    unsigned __int64 _timeLimitItemPQ[5];         // +0x570. LIFT: the PDB type is TimeLimitItemPriorityQueue (0x28), not declared yet
    unsigned __int64 _timeLimitItemIDList[4];     // +0x598. LIFT: the PDB type is std::vector<unsigned __int64, StlAllocator<unsigned __int64,2> > (0x20), not declared yet
};
static_assert(sizeof(Inventory) == 0x5B8, "sizeof Inventory");

class InventoryCacheUpdate
{
public:
    __cdecl InventoryCacheUpdate(::Pc *, bool);  // 0x4be980
    void __cdecl AddChange(::Item const *);  // 0x4bea20
    void __cdecl SendAdd(__int64, ::Item *);  // 0x4bea70
    void __cdecl SendDelete(::Item const *);  // 0x4beb50
    __cdecl ~InventoryCacheUpdate(void);  // 0x4bfa70
};

class InventoryClientUpdate
{
public:
    __cdecl InventoryClientUpdate(::Pc *, ::ItemReason);  // 0x4be600
    void __cdecl AddChange(::Item const *);  // 0x4be6e0
    void __cdecl AddDelete(::Item const *);  // 0x4be7f0
    void __cdecl Send(void);  // 0x4be900
    __cdecl ~InventoryClientUpdate(void);  // 0x4bfee0
};

class MoneyLimit
{
public:
    enum LIMIT_CASE {};
public:
    static __int64 __cdecl GetMoneyLimitCase(::MoneyLimit::LIMIT_CASE);  // 0x4beba0
};

