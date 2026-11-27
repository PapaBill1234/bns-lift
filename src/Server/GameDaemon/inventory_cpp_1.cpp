// inventory_cpp_1.cpp: inventory.cpp part 1 (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "inventory.h"
#include "item.h"
#include "pc.h"
#include "propertytran.h"
#include "Log.h"
#include "LiftStub.h"

#pragma comment(linker, "/INCLUDE:?AddChange@InventoryCacheUpdate@@QEAAXPEBVItem@@@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?IsActivatedGemSlot@Inventory@@SA_NI@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetItemClass@Inventory@@SA?AW4ItemClass@@F@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?Dispose@Inventory@@QEAA_NGFW4ItemReason@@@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetCacheId@Inventory@@SADPEBVItem@@@Z")  // LIFT: dead-strip keep (no live caller yet)

// 0x4be600
__cdecl InventoryClientUpdate::InventoryClientUpdate(::Pc *, ::ItemReason)
{
    LIFT_STUB(0x4be600);
}

// 0x4be6e0
void __cdecl InventoryClientUpdate::AddChange(::Item const *)
{
    LIFT_STUB(0x4be6e0);
}

// 0x4be7f0
void __cdecl InventoryClientUpdate::AddDelete(::Item const *)
{
    LIFT_STUB(0x4be7f0);
}

// 0x4be900
void __cdecl InventoryClientUpdate::Send(void)
{
    LIFT_STUB(0x4be900);
}

// 0x4be980
__cdecl InventoryCacheUpdate::InventoryCacheUpdate(::Pc *, bool)
{
    LIFT_STUB(0x4be980);
}

// 0x4bea20
void __cdecl InventoryCacheUpdate::AddChange(::Item const *)
{
    // The 2019 build has an empty body.
}

// 0x4bea70
void __cdecl InventoryCacheUpdate::SendAdd(__int64, ::Item *)
{
    LIFT_STUB(0x4bea70);
}

// 0x4beb50
void __cdecl InventoryCacheUpdate::SendDelete(::Item const *)
{
    LIFT_STUB(0x4beb50);
}

// 0x4beba0
__int64 __cdecl MoneyLimit::GetMoneyLimitCase(::MoneyLimit::LIMIT_CASE)
{
    LIFT_STUB(0x4beba0);
}

// 0x4bec40
bool __cdecl Inventory::IsActivatedGemSlot(unsigned int gemId)
{
    // Gem id 0 and gem ids 65001 to 65011 are not an activated slot.
    return gemId != 0 && gemId != 65001 && gemId != 65002 && gemId != 65003 && gemId != 65004 && gemId != 65005 &&
           gemId != 65006 && gemId != 65007 && gemId != 65008 && gemId != 65009 && gemId != 65010 && gemId != 65011;
}

// 0x4becb0
bool __cdecl Inventory::CheckActivatedGemSlotExist(::Item const *)
{
    LIFT_STUB(0x4becb0);
}

// 0x4bed10
char __cdecl Inventory::GetCacheId(::Item const *item)
{
    // LIFT: the case values are ItemClass and the results are cache ids. The PDB enumerator names are not used here.
    switch (item->GetClass())
    {
    case 1:
        return 3;
    case 2:
        return 4;
    case 3:
        return 5;
    case 4:
        return 11;
    case 5:
        return 15;
    default:
        return 0;
    }
}

// 0x4bed60
void __cdecl Inventory::Cleanup(::std::vector< ::Item *, ::StlAllocator< ::Item *, 2> > &)
{
    LIFT_STUB(0x4bed60);
}

// 0x4bee00
__cdecl Inventory::Inventory(void)
{
    LIFT_STUB(0x4bee00);
}

// 0x4bef10
__cdecl Inventory::~Inventory(void)
{
    LIFT_STUB(0x4bef10);
}

// 0x4bf140
bool __cdecl Inventory::Initialize(::Pc *, short *const)
{
    LIFT_STUB(0x4bf140);
}

// 0x4bf2a0
int __cdecl Inventory::SetDbData(::ItemClass, short, char const *, int, ::std::vector< ::Item *, ::StlAllocator< ::Item *, 2> > &)
{
    LIFT_STUB(0x4bf2a0);
}

// 0x4bfaa0
void __cdecl Inventory::SetInvalidPosItems(::std::vector< ::Item *, ::StlAllocator< ::Item *, 2> > &)
{
    LIFT_STUB(0x4bfaa0);
}

// 0x4bfd80
void __cdecl Inventory::SendItemList(void)
{
    LIFT_STUB(0x4bfd80);
}

// 0x4bfef0
void __cdecl Inventory::FetchItemListForBuilder(::FragmentPacket &)
{
    LIFT_STUB(0x4bfef0);
}

// 0x4c0130
void __cdecl Inventory::SendRebuyItemList(void)
{
    LIFT_STUB(0x4c0130);
}

// 0x4c0490
void __cdecl Inventory::EnterZone(::EnterReason)
{
    LIFT_STUB(0x4c0490);
}

// 0x4c06c0
void __cdecl Inventory::ActivateEquipBadgeAbility(void)
{
    LIFT_STUB(0x4c06c0);
}

// 0x4c0920
void __cdecl Inventory::DeactivateEquipBadgeAbility(void)
{
    LIFT_STUB(0x4c0920);
}

// 0x4c0ad0
void __cdecl Inventory::RefreshEquipEffect(void)
{
    LIFT_STUB(0x4c0ad0);
}

// 0x4c0c80
void __cdecl Inventory::CollapseEquipEffect(void)
{
    LIFT_STUB(0x4c0c80);
}

// 0x4c0d60
void __cdecl Inventory::InvokeEquipEffect(void)
{
    LIFT_STUB(0x4c0d60);
}

// 0x4c0e40
::Item * __cdecl Inventory::GetItem(unsigned char, unsigned short) const
{
    LIFT_STUB(0x4c0e40);
}

// 0x4c0ef0
::Inventory::SetItemInfo const *const __cdecl Inventory::GetSkillSkinSetItemInfo(short) const
{
    LIFT_STUB(0x4c0ef0);
}

// 0x4c10d0
::ItemClass __cdecl Inventory::GetItemClass(short subtype)
{
    switch (subtype)
    {
    case 0:
        return ITEMCLASS_WEAPON;
    case 1:
        return ITEMCLASS_COSTUME;
    case 2:
        return ITEMCLASS_GROCERY;
    case 3:
        return ITEMCLASS_GEM;
    case 4:
        return ITEMCLASS_ACCESSORY;
    default:
        break;
    }
    Log::Write(Log::LT_ERROR,
               L"e:\\dailybuild02\\gamedaemon-common-0.0.348\\depot\\branch\\348nc\\program\\server\\gamedaemon\\Inventory.cpp", 1210,
               L"[inventory], GetItemClass, invalid subtype %d", subtype);
    return ITEMCLASS_NONE;
}

// 0x4c1150
bool __cdecl Inventory::AddRevealItemAbility(::Data::EffectRecordItemAbility &, ::Data::ItemRecordPtr, char, int)
{
    LIFT_STUB(0x4c1150);
}

// 0x4c1c10
bool __cdecl Inventory::AddItemAbilityBySeq(::Data::EffectRecordItemAbility &, ::Data::ItemRecordPtr, char, int, bool)
{
    LIFT_STUB(0x4c1c10);
}

// 0x4c2670
short __cdecl Inventory::CalcRevealedItemAbility(::Data::ItemRecordPtr, char, short, short &)
{
    LIFT_STUB(0x4c2670);
}

// 0x4c3610
char __cdecl Inventory::GetItemTypeFromCondType(char)
{
    LIFT_STUB(0x4c3610);
}

// 0x4c3720
bool __cdecl Inventory::CheckItemCondType(::Data::ItemRecordPtr const &, char)
{
    LIFT_STUB(0x4c3720);
}

// 0x4c3d90
char __cdecl Inventory::GetBadgeCategory(::Data::ItemRecordGroceryPtr)
{
    LIFT_STUB(0x4c3d90);
}

// 0x4c3df0
bool __cdecl Inventory::CheckAcquire(int, ::Inventory::AcquireOrder const *const) const
{
    LIFT_STUB(0x4c3df0);
}

// 0x4c4220
bool __cdecl Inventory::CheckAcquire(int, ::Inventory::AcquireOrderWithDbId const *const) const
{
    LIFT_STUB(0x4c4220);
}

// 0x4c4640
bool __cdecl Inventory::Acquire(int, ::Inventory::AcquireOrder *const, int *, unsigned short *const)
{
    LIFT_STUB(0x4c4640);
}

// 0x4c54e0
bool __cdecl Inventory::AcquireWithSpirit(int, ::Inventory::AcquireOrder *const, int, char *const, int *const, int &, unsigned short *const)
{
    LIFT_STUB(0x4c54e0);
}

// 0x4c5d30
bool __cdecl Inventory::AcquireWeaponItem(int, ::Inventory::AcquireOrder *const, bool, unsigned int *const, bool, unsigned int, char, bool, int, char *const, int *const, int &, unsigned short *const)
{
    LIFT_STUB(0x4c5d30);
}

// 0x4c62b0
bool __cdecl Inventory::AcquirePostAttachment(__int64, char, __int64, ::Inventory::AcquireOrderWithDbId const *)
{
    LIFT_STUB(0x4c62b0);
}

// 0x4c6e30
bool __cdecl Inventory::AcquireEnvReward(int, ::Inventory::AcquireOrder *const)
{
    LIFT_STUB(0x4c6e30);
}

// 0x4c6f80
bool __cdecl Inventory::Clone(int, ::Inventory::CloneOrderWithDbId const *const)
{
    LIFT_STUB(0x4c6f80);
}

// 0x4c7d90
bool __cdecl Inventory::ClonePostAttachment(__int64, char, __int64, ::Inventory::CloneOrderWithDbId const *)
{
    LIFT_STUB(0x4c7d90);
}

// 0x4c8960
void __cdecl Inventory::ConfirmAcquire(unsigned __int64, unsigned __int64, __int64, char)
{
    LIFT_STUB(0x4c8960);
}

// 0x4c9d50
void __cdecl Inventory::ConfirmAcquirePostAttachment(short, unsigned __int64)
{
    LIFT_STUB(0x4c9d50);
}

// 0x4ca810
void __cdecl Inventory::FailConfirmAcquirePostAttachment(short)
{
    LIFT_STUB(0x4ca810);
}

// 0x4ca920
void __cdecl Inventory::ConfirmAcquireTakeGuildCraft(unsigned __int64, unsigned __int64)
{
    LIFT_STUB(0x4ca920);
}

// 0x4cafa0
void __cdecl Inventory::FailToConfirmAcquireByPropertyTransaction(unsigned __int64)
{
    LIFT_STUB(0x4cafa0);
}

// 0x4cb0e0
void __cdecl Inventory::ConfirmAcquireReservedClosetItem(unsigned __int64, unsigned __int64, ::ItemReason)
{
    LIFT_STUB(0x4cb0e0);
}

// 0x4cb8f0
void __cdecl Inventory::FailConfirmAcquireReservedClosetItem(unsigned __int64)
{
    LIFT_STUB(0x4cb8f0);
}

// 0x4cba30
void __cdecl Inventory::FailConfirmAcquire(unsigned __int64, unsigned __int64, short)
{
    LIFT_STUB(0x4cba30);
}

// 0x4cbb20
void __cdecl Inventory::ConfirmAcquireRankingRewardItem(unsigned __int64, unsigned __int64, char, int, char, short, short, int)
{
    LIFT_STUB(0x4cbb20);
}

// 0x4cc0c0
void __cdecl Inventory::ConfirmAcquireDuelBotTrainingRoomRewardItem(unsigned __int64, unsigned __int64, short, char, char, bool, char, unsigned short)
{
    LIFT_STUB(0x4cc0c0);
}

// 0x4cc700
void __cdecl Inventory::ConfirmAcquireChangeWeaponAppearance(short, unsigned __int64)
{
    LIFT_STUB(0x4cc700);
}

// 0x4cd1c0
void __cdecl Inventory::ConfirmAcquireAchievementRewardItem(wchar_t const *, unsigned __int64, unsigned __int64, ::ItemReason, bool, char, unsigned short)
{
    LIFT_STUB(0x4cd1c0);
}

// 0x4cda60
void __cdecl Inventory::writeGameLogGetItem(::Item *, short)
{
    LIFT_STUB(0x4cda60);
}

// 0x4cdea0
void __cdecl Inventory::ConfirmAcquirePropertyTransaction(char, char, unsigned __int64, unsigned __int64, char, short, ::ItemReason, void *)
{
    LIFT_STUB(0x4cdea0);
}

// 0x4ce2b0
void __cdecl Inventory::writeGameLog(char, ::Item *, void *)
{
    LIFT_STUB(0x4ce2b0);
}

// 0x4ce8e0
bool __cdecl Inventory::CheckDispose(::Inventory::DisposeOrder const *, ::ItemReason) const
{
    LIFT_STUB(0x4ce8e0);
}

// 0x4ce9f0
bool __cdecl Inventory::Dispose(::Inventory::DisposeOrder const *, ::ItemReason)
{
    LIFT_STUB(0x4ce9f0);
}

// 0x4cebc0
bool __cdecl Inventory::CheckDispose(int, ::Inventory::DisposeOrderWithPos const *const, ::ItemReason) const
{
    LIFT_STUB(0x4cebc0);
}

// 0x4cede0
bool __cdecl Inventory::Dispose(int, ::Inventory::DisposeOrderWithPos const *const, ::ItemReason, unsigned __int64, wchar_t const *)
{
    LIFT_STUB(0x4cede0);
}

// 0x4cfcc0
bool __cdecl Inventory::Dispose(unsigned short pos, short count, ::ItemReason reason)
{
    // ❓ The 2019 code sets the order count to 1 and passes the 32-bit register of count (r8d) as the reason.
    // The source form is not known. This form differs by one instruction (movsx r9d, r8w for mov r9d, r8d).
    (void)reason;
    Inventory::DisposeOrderWithPos order;
    order.pos = pos;
    order.count = 1;
    return Dispose(1, &order, static_cast<::ItemReason>(count), 0, L"");
}

// 0x4cfd00
bool __cdecl Inventory::CheckDisposeWithDepot(char, int, ::Inventory::DisposeOrderWithPos const *const, ::ItemReason) const
{
    LIFT_STUB(0x4cfd00);
}

// 0x4cff00
bool __cdecl Inventory::DisposeWithDepot(char, int, ::Inventory::DisposeOrderWithPos const *const, ::ItemReason, unsigned __int64)
{
    LIFT_STUB(0x4cff00);
}

// 0x4d0dc0
char __cdecl Inventory::PawnItemInItems(unsigned short)
{
    LIFT_STUB(0x4d0dc0);
}

// 0x4d0eb0
char __cdecl Inventory::SplitPawn(::Item *, short)
{
    LIFT_STUB(0x4d0eb0);
}

// 0x4d1310
bool __cdecl Inventory::RollbackPawn(void)
{
    LIFT_STUB(0x4d1310);
}

// 0x4d1950
void __cdecl Inventory::ClearPawn(bool)
{
    LIFT_STUB(0x4d1950);
}

// 0x4d1bd0
bool __cdecl Inventory::SequesterItem(unsigned char, unsigned short, bool)
{
    LIFT_STUB(0x4d1bd0);
}

// 0x4d2100
char __cdecl Inventory::MoveToTransitItems(unsigned short, short, short, wchar_t *, short, wchar_t *)
{
    LIFT_STUB(0x4d2100);
}

// 0x4d2720
bool __cdecl Inventory::MoveToTransitItemList(short, short const *const, short const *const, short &, ::PropertyTransactionSyncFetch::SyncItem &, char *const, ::Item **const)
{
    LIFT_STUB(0x4d2720);
}

// 0x4d28f0
char __cdecl Inventory::HideFromInventory(unsigned short, short, ::Inventory::ItemTransitType, ::PropertyTransactionSyncFetch::ItemData *)
{
    LIFT_STUB(0x4d28f0);
}

// 0x4d3050
bool __cdecl Inventory::RollbackTransitItems(char, char *const)
{
    LIFT_STUB(0x4d3050);
}

// 0x4d3e80
bool __cdecl Inventory::RollbackTransitOccupiedItems(char, char *const)
{
    LIFT_STUB(0x4d3e80);
}

// 0x4d4dd0
::GameFailReason __cdecl Inventory::AcquirePropertyTransaction(::PropertyTransactionSyncFetchEx &, char, ::Inventory::AcquireOrder *const, ::SyncContext *)
{
    LIFT_STUB(0x4d4dd0);
}

// 0x4d5630
void __cdecl Inventory::ReleasePropertyTransaction(::SyncContext &)
{
    LIFT_STUB(0x4d5630);
}

// 0x4d5730
void __cdecl Inventory::rollbackTransitItem(short)
{
    LIFT_STUB(0x4d5730);
}

// 0x4d6480
void __cdecl Inventory::RollbackTransitItems(short, unsigned __int64 const *const, short const *const, char const *const)
{
    LIFT_STUB(0x4d6480);
}

// 0x4d65b0
void __cdecl Inventory::ClearTransitItems(short, char const *const, short const *const)
{
    LIFT_STUB(0x4d65b0);
}

// 0x4d6610
void __cdecl Inventory::clearTransitItem(char, short)
{
    LIFT_STUB(0x4d6610);
}

// 0x4d73a0
char __cdecl Inventory::MoveToTransitItem(unsigned short, int, ::OpXmlData const *, ::PropertyTransactionSyncData &, ::SyncContext *, ::ItemReason)
{
    LIFT_STUB(0x4d73a0);
}

// 0x4d8200
void __cdecl Inventory::ClearTransitItem(char, char, int, ::OpXmlData const *, ::ItemReason)
{
    LIFT_STUB(0x4d8200);
}

// 0x4d8ff0
void __cdecl Inventory::arrangeItem(::Item *, short, ::ItemReason)
{
    LIFT_STUB(0x4d8ff0);
}

// 0x4d97c0
void __cdecl Inventory::RollbackTransitItem(char, char, char, int, ::OpXmlData const *)
{
    LIFT_STUB(0x4d97c0);
}

// 0x4d99c0
void __cdecl Inventory::addAmountTransitItem(char, short, unsigned short, bool, ::ItemReason, wchar_t const *)
{
    LIFT_STUB(0x4d99c0);
}

// 0x4da0a0
bool __cdecl Inventory::insertPropertyTransaction(::Item const *, ::PropertyTransactionSyncData &, unsigned __int64)
{
    LIFT_STUB(0x4da0a0);
}

// 0x4da230
bool __cdecl Inventory::deletePropertyTransaction(::Item const *, ::PropertyTransactionSyncData &)
{
    LIFT_STUB(0x4da230);
}

// 0x4da420
bool __cdecl Inventory::updatePropertyTransaction(::Item const *, ::PropertyTransactionSyncData &, int, ::OpXmlData const *)
{
    LIFT_STUB(0x4da420);
}

// 0x4da7e0
::GameFailReason __cdecl Inventory::Expand(char, bool, int, ::Inventory::DisposeOrderWithPos *)
{
    LIFT_STUB(0x4da7e0);
}

// 0x4db2d0
::GameFailReason __cdecl Inventory::ExpandSkillPage2(char, wchar_t const *, int, ::Inventory::DisposeOrderWithPos *)
{
    LIFT_STUB(0x4db2d0);
}

// 0x4dba20
::GameFailReason __cdecl Inventory::RevealItemAbility(unsigned char, short, short, char, int, ::Inventory::DisposeOrderWithPos *const)
{
    LIFT_STUB(0x4dba20);
}

// 0x4dd2a0
::GameFailReason __cdecl Inventory::AttachEquipGemPiece(unsigned char, short, short, int, ::Inventory::DisposeOrderWithPos *const)
{
    LIFT_STUB(0x4dd2a0);
}

// 0x4de650
::GameFailReason __cdecl Inventory::checkGrowthMaterial(::Data::ItemRecordPtr, int, ::Inventory::DisposeOrderWithPos *const, bool)
{
    LIFT_STUB(0x4de650);
}

// 0x4dec80
::GameFailReason __cdecl Inventory::GrowthItem(unsigned char, short, short, short, int, ::Inventory::DisposeOrderWithPos *const)
{
    LIFT_STUB(0x4dec80);
}

// 0x4e0900
::GameFailReason __cdecl Inventory::AwakeningItem(unsigned char, short, short, int, ::Inventory::DisposeOrderWithPos *const, int, ::Inventory::DisposeOrderWithPos *const)
{
    LIFT_STUB(0x4e0900);
}

// 0x4e22c0
::GameFailReason __cdecl Inventory::FeedingRandomStatEquipGem(unsigned char, short, short, int, ::Inventory::DisposeOrderWithPos *const, int, ::Inventory::DisposeOrderWithPos *const)
{
    LIFT_STUB(0x4e22c0);
}

// 0x4e3ec0
::GameFailReason __cdecl Inventory::R_EnchantToItem(unsigned char, unsigned short, unsigned __int64)
{
    LIFT_STUB(0x4e3ec0);
}

// 0x4e4b80
::GameFailReason __cdecl Inventory::R_ResetEnchantItemInfo(unsigned char, short)
{
    LIFT_STUB(0x4e4b80);
}

// 0x4e4f30
::GameFailReason __cdecl Inventory::R_ResetEnchantRestoreInfo(unsigned char, short)
{
    LIFT_STUB(0x4e4f30);
}

// 0x4e52e0
::GameFailReason __cdecl Inventory::R_RestoreEnchantFailedItem(unsigned char, unsigned short, unsigned short, unsigned __int64)
{
    LIFT_STUB(0x4e52e0);
}
