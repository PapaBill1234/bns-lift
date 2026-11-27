// inventoryaction_cpp_4.cpp: inventoryaction.cpp part 4 (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "inventoryaction.h"
#include "accountinventorytran.h"
#include "action.h"
#include "creature.h"
#include "instantpaymenttran.h"
#include "inventory.h"
#include "item.h"
#include "marketservicetran.h"
#include "pc.h"
#include "posttran.h"
#include "zone.h"
#include "LiftStub.h"

// 0x53bef0
bool __cdecl RenameGuildTask::makeRenameGuildTran(void)
{
    LIFT_STUB(0x53bef0);
}

// 0x53c510
void __cdecl RenameGuildTask::renameGuildReqFromClient(void)
{
    LIFT_STUB(0x53c510);
}

// 0x53ca80
void __cdecl RenameGuildTask::renameGuildOkFromLobby(void)
{
    LIFT_STUB(0x53ca80);
}

// 0x53d060
void __cdecl RenameGuildTask::renameGuildOkFromCache(void)
{
    LIFT_STUB(0x53d060);
}

// 0x53d290
void __cdecl RenameGuildTask::renameGuildAbort(void)
{
    LIFT_STUB(0x53d290);
}

// 0x53d420
void __cdecl RenameGuildTask::TimerExpired(unsigned int, long)
{
    LIFT_STUB(0x53d420);
}

// 0x53d460
__cdecl GuildTransactionTask::GuildTransactionTask(void)
{
    LIFT_STUB(0x53d460);
}

// 0x53d4e0
void __cdecl GuildTransactionTask::Initialize(::Zone *, ::Creature *, ::GuildTransactionTask::TransactionStep)
{
    LIFT_STUB(0x53d4e0);
}

// 0x53d540
void __cdecl GuildTransactionTask::start(void)
{
    LIFT_STUB(0x53d540);
}

// 0x53d5a0
void __cdecl GuildTransactionTask::onRegisterGuildOk(unsigned __int64, unsigned __int64)
{
    LIFT_STUB(0x53d5a0);
}

// 0x53d830
void __cdecl GuildTransactionTask::onRegisterGuildFail(short)
{
    LIFT_STUB(0x53d830);
}

// 0x53d8d0
void __cdecl GuildTransactionTask::SendFinishRegisterGuild(unsigned __int64, unsigned __int64, short, unsigned __int64)
{
    LIFT_STUB(0x53d8d0);
}

// 0x53da70
void __cdecl GuildTransactionTask::onCreateGuildOk(unsigned __int64)
{
    LIFT_STUB(0x53da70);
}

// 0x53e040
void __cdecl GuildTransactionTask::onCreateGuildFail(short)
{
    LIFT_STUB(0x53e040);
}

// 0x53e1d0
void __cdecl GuildTransactionTask::TimerExpired(unsigned int, long)
{
    LIFT_STUB(0x53e1d0);
}

// 0x53e210
__cdecl MarketTask::MarketTask(void)
{
    LIFT_STUB(0x53e210);
}

// 0x53e290
bool __cdecl MarketTask::Initialize(::Zone *, ::Creature *, ::MarketTask::MarketType, short)
{
    LIFT_STUB(0x53e290);
}

// 0x53e360
void __cdecl MarketTask::start(void)
{
    LIFT_STUB(0x53e360);
}

// 0x53e450
__cdecl RegisterSaleAction::RegisterSaleAction(void)
{
    LIFT_STUB(0x53e450);
}

// 0x53e4d0
bool __cdecl RegisterSaleAction::Initialize(::Zone *, ::Creature *, __int64, char, __int64, int, short, short, bool)
{
    LIFT_STUB(0x53e4d0);
}

// 0x53e5c0
void __cdecl RegisterSaleAction::startAction(void)
{
    LIFT_STUB(0x53e5c0);
}

// 0x53eb60
void __cdecl RegisterSaleAction::OnReserveSaleOk(__int64)
{
    LIFT_STUB(0x53eb60);
}

// 0x53edf0
void __cdecl RegisterSaleAction::OnReserveSaleFail(short)
{
    LIFT_STUB(0x53edf0);
}

// 0x53eeb0
void __cdecl RegisterSaleAction::OnRegisterPawnOk(__int64)
{
    LIFT_STUB(0x53eeb0);
}

// 0x53ef30
void __cdecl RegisterSaleAction::OnRegisterPawnFail(void)
{
    LIFT_STUB(0x53ef30);
}

// 0x53f190
void __cdecl RegisterSaleAction::OnRegisterSaleOk(void)
{
    LIFT_STUB(0x53f190);
}

// 0x53f210
void __cdecl RegisterSaleAction::OnRegisterSaleFail(short)
{
    LIFT_STUB(0x53f210);
}

// 0x53f360
void __cdecl RegisterSaleAction::OnCancelPawnOk(void)
{
    LIFT_STUB(0x53f360);
}

// 0x53f580
void __cdecl RegisterSaleAction::OnCancelPawnFail(void)
{
    LIFT_STUB(0x53f580);
}

// 0x53f6b0
void __cdecl RegisterSaleAction::OnConfirmedSplitItem(unsigned short, __int64, char)
{
    LIFT_STUB(0x53f6b0);
}

// 0x53f810
void __cdecl RegisterSaleAction::sendRegisterPawn(void)
{
    LIFT_STUB(0x53f810);
}

// 0x53f9e0
void __cdecl RegisterSaleAction::sendRegisterSale(void)
{
    LIFT_STUB(0x53f9e0);
}

// 0x540240
bool __cdecl RegisterSaleAction::checkItems(void)
{
    LIFT_STUB(0x540240);
}

// 0x5408a0
__int64 __cdecl RegisterSaleAction::getExtraFee(void)
{
    LIFT_STUB(0x5408a0);
}

// 0x540ca0
bool __cdecl RegisterSaleAction::pawnItems(void)
{
    LIFT_STUB(0x540ca0);
}

// 0x540f30
void __cdecl RegisterSaleAction::finishAction(void)
{
    LIFT_STUB(0x540f30);
}

// 0x540fc0
void __cdecl RegisterSaleAction::cancelAction(::Action::CancelReason, wchar_t const *, int)
{
    LIFT_STUB(0x540fc0);
}

// 0x541120
void __cdecl RegisterSaleAction::failAction(::Action::FailReason)
{
    LIFT_STUB(0x541120);
}

// 0x541150
__cdecl AccountInventoryTask::~AccountInventoryTask(void)
{
    LIFT_STUB(0x541150);
}

// 0x5411b0
bool __cdecl AccountInventoryTask::Initialize(::Zone *, ::Pc *, ::AccountInventoryTask::Operation, ::AccountInventoryTakeWarehouseItemTran *)
{
    LIFT_STUB(0x5411b0);
}

// 0x541250
void __cdecl AccountInventoryTask::TimerExpired(unsigned int, long)
{
    LIFT_STUB(0x541250);
}

// 0x541290
void __cdecl AccountInventoryTask::start(void)
{
    LIFT_STUB(0x541290);
}

// 0x541800
__cdecl BoardGachaDrawByItemTask::~BoardGachaDrawByItemTask(void)
{
    LIFT_STUB(0x541800);
}

// 0x541860
bool __cdecl BoardGachaDrawByItemTask::Initialize(::Zone *, ::Pc *, ::AccountInventoryBoardGachaDrawByItemTran *)
{
    LIFT_STUB(0x541860);
}

// 0x5419b0
void __cdecl BoardGachaDrawByItemTask::TimerExpired(unsigned int, long)
{
    LIFT_STUB(0x5419b0);
}

// 0x5419f0
void __cdecl BoardGachaDrawByItemTask::failProcess(short)
{
    LIFT_STUB(0x5419f0);
}

// 0x541a80
void __cdecl BoardGachaDrawByItemStartTask::start(void)
{
    LIFT_STUB(0x541a80);
}

// 0x541d00
void __cdecl BoardGachaDrawByItemTryDrawOkTask::start(void)
{
    LIFT_STUB(0x541d00);
}

// 0x541df0
void __cdecl BoardGachaDrawByItemTryConsumeItemOkTask::start(void)
{
    LIFT_STUB(0x541df0);
}

// 0x542090
void __cdecl BoardGachaDrawByItemAbortTask::start(void)
{
    LIFT_STUB(0x542090);
}

// 0x542320
__cdecl MarkExpressPostTask2::~MarkExpressPostTask2(void)
{
    LIFT_STUB(0x542320);
}

// 0x542380
bool __cdecl MarkExpressPostTask2::Initialize(::Zone *, ::Pc *, ::MarkExpressPostTask2::Operation, ::MarkExpressPostTran *)
{
    LIFT_STUB(0x542380);
}

// 0x542420
void __cdecl MarkExpressPostTask2::TimerExpired(unsigned int, long)
{
    LIFT_STUB(0x542420);
}

// 0x542460
void __cdecl MarkExpressPostTask2::start(void)
{
    LIFT_STUB(0x542460);
}

// 0x542ca0
__cdecl DetachPostAttachmentTask_IndetachFixed::~DetachPostAttachmentTask_IndetachFixed(void)
{
    LIFT_STUB(0x542ca0);
}

// 0x542d00
bool __cdecl DetachPostAttachmentTask_IndetachFixed::Initialize(::Zone *, ::Pc *, ::DetachPostAttachmentTask_IndetachFixed::Operation, ::DetachPostAttachmentTran_IndetachFixed *)
{
    LIFT_STUB(0x542d00);
}

// 0x542da0
void __cdecl DetachPostAttachmentTask_IndetachFixed::TimerExpired(unsigned int, long)
{
    LIFT_STUB(0x542da0);
}

// 0x542de0
void __cdecl DetachPostAttachmentTask_IndetachFixed::start(void)
{
    LIFT_STUB(0x542de0);
}

// 0x543ad0
__cdecl RegisterPurchaseTask2::~RegisterPurchaseTask2(void)
{
    LIFT_STUB(0x543ad0);
}

// 0x543b30
bool __cdecl RegisterPurchaseTask2::Initialize(::Zone *, ::Pc *, ::RegisterPurchaseTask2::Operation, ::RegisterPurchaseTran *)
{
    LIFT_STUB(0x543b30);
}

// 0x543bd0
void __cdecl RegisterPurchaseTask2::TimerExpired(unsigned int, long)
{
    LIFT_STUB(0x543bd0);
}

// 0x543c10
void __cdecl RegisterPurchaseTask2::start(void)
{
    LIFT_STUB(0x543c10);
}

// 0x544650
__cdecl RegisterBidTask2::~RegisterBidTask2(void)
{
    LIFT_STUB(0x544650);
}

// 0x5446b0
bool __cdecl RegisterBidTask2::Initialize(::Zone *, ::Pc *, ::RegisterBidTask2::Operation, ::RegisterBidTran *)
{
    LIFT_STUB(0x5446b0);
}

// 0x544750
void __cdecl RegisterBidTask2::TimerExpired(unsigned int, long)
{
    LIFT_STUB(0x544750);
}

// 0x544790
void __cdecl RegisterBidTask2::start(void)
{
    LIFT_STUB(0x544790);
}

// 0x5451c0
__cdecl UpdateBidTask2::~UpdateBidTask2(void)
{
    LIFT_STUB(0x5451c0);
}

// 0x545220
bool __cdecl UpdateBidTask2::Initialize(::Zone *, ::Pc *, ::UpdateBidTask2::Operation, ::UpdateBidTran *)
{
    LIFT_STUB(0x545220);
}

// 0x5452c0
void __cdecl UpdateBidTask2::TimerExpired(unsigned int, long)
{
    LIFT_STUB(0x5452c0);
}

// 0x545300
void __cdecl UpdateBidTask2::start(void)
{
    LIFT_STUB(0x545300);
}

// 0x545a60
void __cdecl SellOldItemTask::start(void)
{
    LIFT_STUB(0x545a60);
}

// 0x546950
bool __cdecl SellOldItemTask::fillOrders(::Inventory::DisposeOrderWithPos *const, int &, char, ::SellOldItemTask::Order const *const, int, __int64 *, int &, int *const)
{
    LIFT_STUB(0x546950);
}

// 0x546e50
bool __cdecl ExchangeItemTask::Initialize(::Zone *, ::Creature *, char, unsigned __int64, ::ExchangeItemTask::Order *const, short)
{
    LIFT_STUB(0x546e50);
}

// 0x546fe0
int __cdecl ExchangeItemTask::getRecvRequiredItemCount(unsigned __int64)
{
    LIFT_STUB(0x546fe0);
}

// 0x547200
short __cdecl ExchangeItemTask::getStackCount(unsigned __int64)
{
    LIFT_STUB(0x547200);
}

// 0x547310
bool __cdecl ExchangeItemTask::determineMultipleReq(void)
{
    LIFT_STUB(0x547310);
}

// 0x547590
bool __cdecl ExchangeItemTask::checkRequired(void)
{
    LIFT_STUB(0x547590);
}

// 0x5476e0
bool __cdecl ExchangeItemTask::pickItems(::Inventory::AcquireOrder *const)
{
    LIFT_STUB(0x5476e0);
}

// 0x547810
void __cdecl ExchangeItemTask::start(void)
{
    LIFT_STUB(0x547810);
}

// 0x548770
bool __cdecl MakeCustomDressTask::Initialize(::Zone *, ::Creature *, short, char *const, char *const, short, ::Inventory::DisposeOrderWithPos *const, short)
{
    LIFT_STUB(0x548770);
}

// 0x548940
void __cdecl MakeCustomDressTask::start(void)
{
    LIFT_STUB(0x548940);
}

// 0x54a040
::GameFailReason __cdecl MakeCustomDressTask::calcCost(::Item const *, __int64 &, ::MakeCustomDressTask::RequiredOrder *const, char &)
{
    LIFT_STUB(0x54a040);
}

// 0x54a650
bool __cdecl MakeCustomDressTask::accumulateCost(::Data::CustomDressDesignCostRecord::Key, __int64 &, ::MakeCustomDressTask::RequiredOrder *const, char &)
{
    LIFT_STUB(0x54a650);
}

// 0x54a750
char __cdecl MakeCustomDressTask::getCustomDressValue(::Item const *, char) const
{
    LIFT_STUB(0x54a750);
}

// 0x54a940
bool __cdecl MakeCustomDressTask::setCustomDressValue(::Item *, char, short)
{
    LIFT_STUB(0x54a940);
}

// 0x54ab60
::Data::CustomDressDesignTypeInfoItemTypeType __cdecl MakeCustomDressTask::EquipType2CustomItemType(::Item const *)
{
    LIFT_STUB(0x54ab60);
}

// 0x54ac60
void __cdecl MakeCustomDressTask::setNoCharge(void)
{
    LIFT_STUB(0x54ac60);
}

// 0x54adc0
void __cdecl SynthesisBadgeTask::start(void)
{
    LIFT_STUB(0x54adc0);
}

// 0x54bf10
::GameFailReason __cdecl SynthesisBadgeTask::fillOrders(int &, ::Inventory::AcquireOrder *const, int &, ::Inventory::DisposeOrderWithPos *const, int &, ::Inventory::DisposeOrderWithPos *const)
{
    LIFT_STUB(0x54bf10);
}

// 0x54cc60
__cdecl BuyCollectionItemsTask::~BuyCollectionItemsTask(void)
{
    LIFT_STUB(0x54cc60);
}

// 0x54ccc0
bool __cdecl BuyCollectionItemsTask::Initialize(::Zone *const, ::Pc *const, ::InstantPaymentTran *const)
{
    LIFT_STUB(0x54ccc0);
}

// 0x54cdc0
void __cdecl BuyCollectionItemsTask::ProcessUnexpired(int)
{
    LIFT_STUB(0x54cdc0);
}

// 0x54ce60
void __cdecl BuyCollectionItemsTask::TimerExpired(unsigned int, long)
{
    LIFT_STUB(0x54ce60);
}

// 0x54cea0
void __cdecl BuyCollectionItemsTask::start(void)
{
    LIFT_STUB(0x54cea0);
}

// 0x54cee0
short const __cdecl BuyCollectionItemsTask::checkTryCondition(void)
{
    LIFT_STUB(0x54cee0);
}

// 0x54cfe0
short const __cdecl BuyCollectionItemsTask::checkCondition(void)
{
    LIFT_STUB(0x54cfe0);
}

// 0x54d1b0
void __cdecl BuyCollectionItemsTask::instantPaymentTry(void)
{
    LIFT_STUB(0x54d1b0);
}

// 0x54d3d0
void __cdecl BuyCollectionItemsTask::instantPaymentOk(void)
{
    LIFT_STUB(0x54d3d0);
}

// 0x54dfc0
void __cdecl BuyCollectionItemsTask::instantPaymentFail(void)
{
    LIFT_STUB(0x54dfc0);
}

// 0x54e110
void __cdecl ProcessItemFusionTask::start(void)
{
    LIFT_STUB(0x54e110);
}

// 0x54e430
::GameFailReason __cdecl ProcessItemFusionTask::fillOrders(int &, ::Inventory::AcquireOrder *const, int &, ::Inventory::DisposeOrderWithPos *const)
{
    LIFT_STUB(0x54e430);
}
