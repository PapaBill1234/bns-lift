// inventoryaction_cpp_1.cpp: inventoryaction.cpp part 1 (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "inventoryaction.h"
#include "action.h"
#include "creature.h"
#include "inventory.h"
#include "moveaction.h"
#include "npc.h"
#include "npcdeadbody.h"
#include "pc.h"
#include "zone.h"
#include "LiftStub.h"

// 0x47c7a0
void __cdecl AirDashAction::intervalAction(long)
{
    LIFT_STUB(0x47c7a0);
}

// 0x50a1e0
void __cdecl ItemListTask::start(void)
{
    LIFT_STUB(0x50a1e0);
}

// 0x50a230
bool __cdecl ExchangeFactionScoreTask::Initialize(::Zone *, ::Creature *, unsigned __int64, int)
{
    LIFT_STUB(0x50a230);
}

// 0x50a300
void __cdecl ExchangeFactionScoreTask::start(void)
{
    LIFT_STUB(0x50a300);
}

// 0x50ac70
bool __cdecl RebuyItemListTask::Initialize(::Zone *, ::Creature *)
{
    LIFT_STUB(0x50ac70);
}

// 0x50ad20
void __cdecl RebuyItemListTask::start(void)
{
    LIFT_STUB(0x50ad20);
}

// 0x50ad70
bool __cdecl PickupItemSessionTask::Initialize(::Zone *, ::Creature *, unsigned __int64, ::PickupItemSessionTask::SessionState)
{
    LIFT_STUB(0x50ad70);
}

// 0x50ae40
void __cdecl PickupItemSessionTask::start(void)
{
    LIFT_STUB(0x50ae40);
}

// 0x50b000
bool __cdecl PrivateItemPouchListTask::Initialize(::Zone *, ::Creature *, unsigned __int64)
{
    LIFT_STUB(0x50b000);
}

// 0x50b0d0
void __cdecl PrivateItemPouchListTask::start(void)
{
    LIFT_STUB(0x50b0d0);
}

// 0x50b490
bool __cdecl PickupItemTask::Initialize(::Zone *, ::Creature *, unsigned __int64, char, int, ::PickupItemTask::Order const *const)
{
    LIFT_STUB(0x50b490);
}

// 0x50b600
void __cdecl PickupItemTask::start(void)
{
    LIFT_STUB(0x50b600);
}

// 0x50d2d0
bool __cdecl PickupItemTask::checkUserGamePlayRestriction(::NpcDeadBody *)
{
    LIFT_STUB(0x50d2d0);
}

// 0x50d380
bool __cdecl TakeContributionRewardTask::Initialize(::Zone *, ::Creature *, unsigned __int64)
{
    LIFT_STUB(0x50d380);
}

// 0x50d4b0
void __cdecl TakeContributionRewardTask::start(void)
{
    LIFT_STUB(0x50d4b0);
}

// 0x50d6a0
bool __cdecl DistributeItemTask::Initialize(::Zone *, ::Creature *, unsigned __int64, wchar_t const *, int, ::DistributeItemTask::Order const *const)
{
    LIFT_STUB(0x50d6a0);
}

// 0x50d830
void __cdecl DistributeItemTask::start(void)
{
    LIFT_STUB(0x50d830);
}

// 0x50f080
bool __cdecl DistributeItemTask::checkUserGamePlayRestriction(::NpcDeadBody *)
{
    LIFT_STUB(0x50f080);
}

// 0x50f110
bool __cdecl CompleteDistributionTask::Initialize(::Zone *, ::Creature *, unsigned __int64)
{
    LIFT_STUB(0x50f110);
}

// 0x50f240
void __cdecl CompleteDistributionTask::start(void)
{
    LIFT_STUB(0x50f240);
}

// 0x50f7b0
bool __cdecl DisposeItemTask::Initialize(::Zone *, ::Creature *, unsigned short, short)
{
    LIFT_STUB(0x50f7b0);
}

// 0x50f880
void __cdecl DisposeItemTask::start(void)
{
    LIFT_STUB(0x50f880);
}

// 0x510520
bool __cdecl MoveItemTask::Initialize(::Zone *, ::Creature *, unsigned char, unsigned short, unsigned char, unsigned short, short, __int64)
{
    LIFT_STUB(0x510520);
}

// 0x510630
bool __cdecl MoveItemTask::Initialize(::Zone *, ::Creature *, char, __int64)
{
    LIFT_STUB(0x510630);
}

// 0x510740
bool __cdecl MoveItemTask::Initialize(::Zone *, ::Creature *, ::MoveItemTask::MoveItemStep, short)
{
    LIFT_STUB(0x510740);
}

// 0x510840
bool __cdecl MoveItemTask::Initialize(::Zone *, ::Creature *)
{
    LIFT_STUB(0x510840);
}

// 0x510930
void __cdecl MoveItemTask::start(void)
{
    LIFT_STUB(0x510930);
}

// 0x510ca0
short __cdecl MoveItemTask::CheckPreConditionForMoveItem(void)
{
    LIFT_STUB(0x510ca0);
}

// 0x510da0
short __cdecl MoveItemTask::checkNpcCond(void)
{
    LIFT_STUB(0x510da0);
}

// 0x5110c0
bool __cdecl MoveItemTask::IsItemReserved(void)
{
    LIFT_STUB(0x5110c0);
}

// 0x511150
void __cdecl MoveItemTask::SetItemReserved(void)
{
    LIFT_STUB(0x511150);
}

// 0x5111c0
void __cdecl MoveItemTask::ResetItemReserved(void)
{
    LIFT_STUB(0x5111c0);
}

// 0x511260
void __cdecl MoveItemTask::CallInvenMove(void)
{
    LIFT_STUB(0x511260);
}

// 0x5112e0
void __cdecl MoveItemTask::OnMoveItemReq(void)
{
    LIFT_STUB(0x5112e0);
}

// 0x5114f0
void __cdecl MoveItemTask::OnGetStatusOk(void)
{
    LIFT_STUB(0x5114f0);
}

// 0x511660
void __cdecl MoveItemTask::OnGetStatusFail(void)
{
    LIFT_STUB(0x511660);
}

// 0x511730
void __cdecl MoveItemTask::OnIsVerifiedFail(void)
{
    LIFT_STUB(0x511730);
}

// 0x511840
__cdecl MoveItemListTask::MoveItemListTask(void)
{
    LIFT_STUB(0x511840);
}

// 0x5118f0
bool __cdecl MoveItemListTask::Initialize(::Zone *, ::Creature *, char, __int64)
{
    LIFT_STUB(0x5118f0);
}

// 0x511a20
bool __cdecl MoveItemListTask::Initialize(::Zone *, ::Creature *, ::MoveItemListTask::MoveItemListStep, short)
{
    LIFT_STUB(0x511a20);
}

// 0x511b40
bool __cdecl MoveItemListTask::Initialize(::Zone *, ::Creature *)
{
    LIFT_STUB(0x511b40);
}

// 0x511c50
void __cdecl MoveItemListTask::start(void)
{
    LIFT_STUB(0x511c50);
}

// 0x5120b0
short __cdecl MoveItemListTask::CheckPreConditionForMoveItem(void)
{
    LIFT_STUB(0x5120b0);
}

// 0x5121b0
short __cdecl MoveItemListTask::checkNpcCond(void)
{
    LIFT_STUB(0x5121b0);
}

// 0x5124d0
bool __cdecl MoveItemListTask::IsItemListReserved(void)
{
    LIFT_STUB(0x5124d0);
}

// 0x512650
void __cdecl MoveItemListTask::SetItemListReserved(void)
{
    LIFT_STUB(0x512650);
}

// 0x5127c0
void __cdecl MoveItemListTask::ResetItemListReserved(void)
{
    LIFT_STUB(0x5127c0);
}

// 0x512960
void __cdecl MoveItemListTask::CallInvenMove(void)
{
    LIFT_STUB(0x512960);
}

// 0x512b00
void __cdecl MoveItemListTask::OnMoveItemReq(void)
{
    LIFT_STUB(0x512b00);
}

// 0x512d90
void __cdecl MoveItemListTask::OnGetStatusOk(void)
{
    LIFT_STUB(0x512d90);
}

// 0x512f10
void __cdecl MoveItemListTask::OnGetStatusFail(void)
{
    LIFT_STUB(0x512f10);
}

// 0x512ff0
void __cdecl MoveItemListTask::OnIsVerifiedFail(void)
{
    LIFT_STUB(0x512ff0);
}

// 0x513110
void __cdecl BuyTask::start(void)
{
    LIFT_STUB(0x513110);
}

// 0x513b00
bool __cdecl BuyTask::fillOrders(::Data::StoreRecordPtr, ::Inventory::AcquireOrder *const, ::BuyTask::Order const *const, int, __int64 *)
{
    LIFT_STUB(0x513b00);
}

// 0x513dd0
void __cdecl SellTask::start(void)
{
    LIFT_STUB(0x513dd0);
}

// 0x514fd0
bool __cdecl SellTask::fillOrders2(::Inventory::DisposeOrderWithPos *const, int &, ::SellTask::Order const *const, int, __int64 *, int &)
{
    LIFT_STUB(0x514fd0);
}

// 0x5153d0
void __cdecl SellTask::writeGameLogSalesLimitExceed(::Pc *)
{
    LIFT_STUB(0x5153d0);
}

// 0x5155d0
bool __cdecl RebuyTask::Initialize(::Zone *, ::Creature *, unsigned __int64, char)
{
    LIFT_STUB(0x5155d0);
}

// 0x5156a0
void __cdecl RebuyTask::start(void)
{
    LIFT_STUB(0x5156a0);
}

// 0x515a40
void __cdecl TradeWithNpcTask::start(void)
{
    LIFT_STUB(0x515a40);
}

// 0x5164c0
bool __cdecl TradeWithNpcTask::fillOrders(::Data::StoreByItemRecordPtr, ::Inventory::AcquireOrder &, ::Inventory::DisposeOrderWithPos *const)
{
    LIFT_STUB(0x5164c0);
}

// 0x516ab0
short __cdecl BuyBaseTask::fillItemBuyPriceOrders(::Data::ItemRecordPtr, ::Data::ItemBuyPriceRecordPtr, __int64, ::Inventory::AcquireOrder &, ::Inventory::DisposeOrderWithPos *const)
{
    LIFT_STUB(0x516ab0);
}

// 0x516cb0
bool __cdecl BuyBaseTask::checkLevel(::Creature *, ::Data::ItemBuyPriceRecordPtr, __int64, short &)
{
    LIFT_STUB(0x516cb0);
}

// 0x516e70
bool __cdecl BuyBaseTask::checkPoint(::Creature *, ::Data::ItemBuyPriceRecordPtr, __int64, short &)
{
    LIFT_STUB(0x516e70);
}

// 0x5171e0
bool __cdecl BuyBaseTask::checkGrade(::Creature *, ::Data::ItemBuyPriceRecordPtr, __int64, short &)
{
    LIFT_STUB(0x5171e0);
}

// 0x5174b0
bool __cdecl BuyBaseTask::checkFaction(::Creature *, ::Data::ItemBuyPriceRecordPtr, __int64, short &)
{
    LIFT_STUB(0x5174b0);
}

// 0x517610
bool __cdecl BuyBaseTask::checkAchievement(::Creature *, ::Data::ItemBuyPriceRecordPtr, __int64, short &)
{
    LIFT_STUB(0x517610);
}

// 0x517810
bool __cdecl BuyBaseTask::checkDisposeItem(::Creature *, ::Data::ItemBuyPriceRecordPtr, __int64, ::Inventory::DisposeOrderWithPos *const, short &)
{
    LIFT_STUB(0x517810);
}

// 0x518100
bool __cdecl BuyBaseTask::checkDisposeBrandItem(::Creature *, ::Data::ItemBuyPriceRecordPtr, __int64, ::Inventory::DisposeOrderWithPos *const, short &, int &)
{
    LIFT_STUB(0x518100);
}

// 0x518670
bool __cdecl BuyBaseTask::disposeAll(::Inventory::DisposeOrderWithPos *const, bool)
{
    LIFT_STUB(0x518670);
}

// 0x518a90
void __cdecl BuyBaseTask::writeItemGameLog(unsigned __int64, wchar_t const *const, wchar_t const *const, wchar_t const *const, wchar_t const *const, ::Inventory::AcquireOrder &, ::Inventory::DisposeOrderWithPos *const, ::Data::ContentQuotaRecordPtr, __int64)
{
    LIFT_STUB(0x518a90);
}

// 0x5192f0
void __cdecl BuyBaseTask::writeGiveMoneyToNpcGameLog(unsigned __int64, wchar_t const *const, wchar_t const *const, wchar_t const *const)
{
    LIFT_STUB(0x5192f0);
}

// 0x519d60
bool __cdecl Buy2Task::Initialize(::Zone *, ::Creature *, unsigned __int64, char, char, short, int, ::BuyBaseTask::DisposeOrder const *const)
{
    LIFT_STUB(0x519d60);
}

// 0x519ea0
void __cdecl Buy2Task::start(void)
{
    LIFT_STUB(0x519ea0);
}

// 0x51a8f0
bool __cdecl MysteriousBuyTask::Initialize(::Zone *, ::Creature *, unsigned __int64, char, int, ::BuyBaseTask::DisposeOrder const *const)
{
    LIFT_STUB(0x51a8f0);
}

// 0x51aa20
void __cdecl MysteriousBuyTask::start(void)
{
    LIFT_STUB(0x51aa20);
}

// 0x51b400
unsigned __int64 __cdecl MysteriousBuyTask::getMysteriousStoreItemGroup(::Npc const *)
{
    LIFT_STUB(0x51b400);
}

// 0x51b620
void __cdecl UnlockMasteryLevelAction::startAction(void)
{
    LIFT_STUB(0x51b620);
}

// 0x51b8b0
bool __cdecl UnlockMasteryLevelAction::fillOrders(::Inventory::DisposeOrderWithPos *const, unsigned __int64 &, int &)
{
    LIFT_STUB(0x51b8b0);
}

// 0x51bc40
void __cdecl UnlockMasteryLevelAction::failAction(::Action::FailReason)
{
    LIFT_STUB(0x51bc40);
}

// 0x51bc80
void __cdecl UnlockMasteryLevelAction::finishAction(void)
{
    LIFT_STUB(0x51bc80);
}

// 0x51bd40
void __cdecl RepairTask::start(void)
{
    LIFT_STUB(0x51bd40);
}

// 0x51c700
bool __cdecl RepairTask::calculatePrice(unsigned char *const, unsigned short *const, int, unsigned char *const, unsigned short *const, int *, __int64 *)
{
    LIFT_STUB(0x51c700);
}

// 0x51cb30
bool __cdecl EquipAction::Initialize(::Zone *, ::Creature *, unsigned char, unsigned short, unsigned char, unsigned short)
{
    LIFT_STUB(0x51cb30);
}

// 0x51cc30
void __cdecl EquipAction::startAction(void)
{
    LIFT_STUB(0x51cc30);
}

// 0x51d0a0
void __cdecl EquipAction::finishAction(void)
{
    LIFT_STUB(0x51d0a0);
}

// 0x51d250
void __cdecl EquipAction::cancelAction(::Action::CancelReason, wchar_t const *, int)
{
    LIFT_STUB(0x51d250);
}

// 0x51d330
void __cdecl EquipAction::failAction(::Action::FailReason)
{
    LIFT_STUB(0x51d330);
}

// 0x51d360
bool __cdecl UnequipAction::Initialize(::Zone *, ::Creature *, unsigned char, unsigned short, unsigned char, unsigned short)
{
    LIFT_STUB(0x51d360);
}

// 0x51d460
void __cdecl UnequipAction::startAction(void)
{
    LIFT_STUB(0x51d460);
}

// 0x51d830
void __cdecl UnequipAction::finishAction(void)
{
    LIFT_STUB(0x51d830);
}

// 0x51dab0
void __cdecl UnequipAction::cancelAction(::Action::CancelReason, wchar_t const *, int)
{
    LIFT_STUB(0x51dab0);
}

// 0x51dba0
void __cdecl UnequipAction::failAction(::Action::FailReason)
{
    LIFT_STUB(0x51dba0);
}

// 0x51dbd0
__cdecl AttachGemToWeaponTask::AttachGemToWeaponTask(void)
{
    LIFT_STUB(0x51dbd0);
}

// 0x51dc60
void __cdecl AttachGemToWeaponTask::start(void)
{
    LIFT_STUB(0x51dc60);
}

// 0x51dda0
bool __cdecl DetachGemFromWeaponTask::Initialize(::Zone *, ::Creature *, unsigned char, unsigned short, char, char)
{
    LIFT_STUB(0x51dda0);
}

// 0x51de90
void __cdecl DetachGemFromWeaponTask::start(void)
{
    LIFT_STUB(0x51de90);
}

// 0x51dfb0
bool __cdecl ExpandWeaponGemSlotTask::Initialize(::Zone *, ::Creature *, unsigned char, unsigned short, unsigned short)
{
    LIFT_STUB(0x51dfb0);
}

// 0x51e090
void __cdecl ExpandWeaponGemSlotTask::start(void)
{
    LIFT_STUB(0x51e090);
}

// 0x51e1d0
bool __cdecl AddWeaponGemSlotTask::Initialize(::Zone *, ::Creature *, unsigned char, unsigned short, short)
{
    LIFT_STUB(0x51e1d0);
}

// 0x51e2c0
void __cdecl AddWeaponGemSlotTask::start(void)
{
    LIFT_STUB(0x51e2c0);
}
