// inventoryaction.h: inventoryaction.cpp, inventoryaction.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"
#include "action.h"
#include "inventory.h"

class AccountInventoryTask
{
public:
    enum Operation {};
public:
    __cdecl AccountInventoryTask(void);  // 0x191910
    virtual __cdecl ~AccountInventoryTask(void);  // 0x541150
    bool __cdecl Initialize(::Zone *, ::Pc *, ::AccountInventoryTask::Operation, ::AccountInventoryTakeWarehouseItemTran *);  // 0x5411b0
private:
    virtual void __cdecl TimerExpired(unsigned int, long);  // 0x541250
    virtual void __cdecl start(void);  // 0x541290
};

class AddWeaponGemSlotTask
{
public:
    __cdecl AddWeaponGemSlotTask(void);  // 0x3504b0
    bool __cdecl Initialize(::Zone *, ::Creature *, unsigned char, unsigned short, short);  // 0x51e1d0
    virtual void __cdecl start(void);  // 0x51e2c0
};

class AssentGuildCraftTask
{
public:
    __cdecl AssentGuildCraftTask(void);  // 0x350890
private:
    virtual void __cdecl TimerExpired(unsigned int, long);  // 0x53a2a0
    virtual void __cdecl start(void);  // 0x53a2e0
};

class AttachEquipGemPieceAction
{
private:
    virtual void __cdecl startAction(void);  // 0x52f8d0
    virtual void __cdecl failAction(::Action::FailReason);  // 0x52fa10
};

class AttachGemToWeaponTask
{
public:
    __cdecl AttachGemToWeaponTask(void);  // 0x51dbd0
    virtual void __cdecl start(void);  // 0x51dc60
};

class AwakeningItemTask
{
public:
    __cdecl AwakeningItemTask(void);  // 0x52fbc0
private:
    virtual void __cdecl start(void);  // 0x52fcb0
};

class BoardGachaDrawByItemAbortTask
{
private:
    virtual void __cdecl start(void);  // 0x542090
};

class BoardGachaDrawByItemStartTask
{
private:
    virtual void __cdecl start(void);  // 0x541a80
};

class BoardGachaDrawByItemTask
{
public:
    virtual __cdecl ~BoardGachaDrawByItemTask(void);  // 0x541800
    bool __cdecl Initialize(::Zone *, ::Pc *, ::AccountInventoryBoardGachaDrawByItemTran *);  // 0x541860
private:
    virtual void __cdecl TimerExpired(unsigned int, long);  // 0x5419b0
protected:
    virtual void __cdecl failProcess(short);  // 0x5419f0
};

class BoardGachaDrawByItemTryConsumeItemOkTask
{
private:
    virtual void __cdecl start(void);  // 0x541df0
};

class BoardGachaDrawByItemTryDrawOkTask
{
private:
    virtual void __cdecl start(void);  // 0x541d00
};

class BuyBaseTask
{
public:
    struct DisposeOrder {};
protected:
    short __cdecl fillItemBuyPriceOrders(::Data::ItemRecordPtr, ::Data::ItemBuyPriceRecordPtr, __int64, ::Inventory::AcquireOrder &, ::Inventory::DisposeOrderWithPos *const);  // 0x516ab0
    bool __cdecl checkLevel(::Creature *, ::Data::ItemBuyPriceRecordPtr, __int64, short &);  // 0x516cb0
    bool __cdecl checkPoint(::Creature *, ::Data::ItemBuyPriceRecordPtr, __int64, short &);  // 0x516e70
    bool __cdecl checkGrade(::Creature *, ::Data::ItemBuyPriceRecordPtr, __int64, short &);  // 0x5171e0
    bool __cdecl checkFaction(::Creature *, ::Data::ItemBuyPriceRecordPtr, __int64, short &);  // 0x5174b0
    bool __cdecl checkAchievement(::Creature *, ::Data::ItemBuyPriceRecordPtr, __int64, short &);  // 0x517610
    bool __cdecl checkDisposeItem(::Creature *, ::Data::ItemBuyPriceRecordPtr, __int64, ::Inventory::DisposeOrderWithPos *const, short &);  // 0x517810
    bool __cdecl checkDisposeBrandItem(::Creature *, ::Data::ItemBuyPriceRecordPtr, __int64, ::Inventory::DisposeOrderWithPos *const, short &, int &);  // 0x518100
    bool __cdecl disposeAll(::Inventory::DisposeOrderWithPos *const, bool);  // 0x518670
    void __cdecl writeItemGameLog(unsigned __int64, wchar_t const *const, wchar_t const *const, wchar_t const *const, wchar_t const *const, ::Inventory::AcquireOrder &, ::Inventory::DisposeOrderWithPos *const, ::Data::ContentQuotaRecordPtr, __int64);  // 0x518a90
    void __cdecl writeGiveMoneyToNpcGameLog(unsigned __int64, wchar_t const *const, wchar_t const *const, wchar_t const *const);  // 0x5192f0
};

class Buy2Task
{
public:
    bool __cdecl Initialize(::Zone *, ::Creature *, unsigned __int64, char, char, short, int, ::BuyBaseTask::DisposeOrder const *const);  // 0x519d60
private:
    virtual void __cdecl start(void);  // 0x519ea0
};

class BuyCollectionItemsTask
{
public:
    __cdecl BuyCollectionItemsTask(void);  // 0x121830
    virtual __cdecl ~BuyCollectionItemsTask(void);  // 0x54cc60
private:
    bool __cdecl Initialize(::Zone *const, ::Pc *const, ::InstantPaymentTran *const);  // 0x54ccc0
public:
    virtual void __cdecl ProcessUnexpired(int);  // 0x54cdc0
private:
    virtual void __cdecl TimerExpired(unsigned int, long);  // 0x54ce60
    virtual void __cdecl start(void);  // 0x54cea0
    short const __cdecl checkTryCondition(void);  // 0x54cee0
    short const __cdecl checkCondition(void);  // 0x54cfe0
    void __cdecl instantPaymentTry(void);  // 0x54d1b0
    void __cdecl instantPaymentOk(void);  // 0x54d3d0
    void __cdecl instantPaymentFail(void);  // 0x54dfc0
};

class BuyTask
{
public:
    struct Order {};
private:
    virtual void __cdecl start(void);  // 0x513110
    bool __cdecl fillOrders(::Data::StoreRecordPtr, ::Inventory::AcquireOrder *const, ::BuyTask::Order const *const, int, __int64 *);  // 0x513b00
};

class CompleteDistributionTask
{
public:
    bool __cdecl Initialize(::Zone *, ::Creature *, unsigned __int64);  // 0x50f110
private:
    virtual void __cdecl start(void);  // 0x50f240
};

class ContractGuildCraftTask
{
public:
    enum Operation {};
public:
    __cdecl ContractGuildCraftTask(void);  // 0x538fe0
    virtual __cdecl ~ContractGuildCraftTask(void);  // 0x5390f0
    bool __cdecl Initialize(::Zone *, ::Pc *, ::ContractGuildCraftTask::Operation, ::ContractGuildCraftTran *, ::ContractGuildCraftTranStartParam *);  // 0x539180
    bool __cdecl InitializeOk(::Zone *, ::Pc *, ::ContractGuildCraftTask::Operation, ::ContractGuildCraftTran *);  // 0x539220
    bool __cdecl InitializeFail(::Zone *, ::Pc *, ::ContractGuildCraftTask::Operation, ::ContractGuildCraftTran *, ::ContractGuildCraftTranFailParam *);  // 0x5392c0
private:
    virtual void __cdecl TimerExpired(unsigned int, long);  // 0x5393f0
    virtual void __cdecl start(void);  // 0x539430
    short __cdecl contractGuildCraftReq(::Pc *);  // 0x539590
};

class DecomposeItem2Task
{
public:
    __cdecl DecomposeItem2Task(void);  // 0x3506a0
    virtual void __cdecl start(void);  // 0x51fd50
};

class DeleteWeaponGemSlotTask
{
public:
    __cdecl DeleteWeaponGemSlotTask(void);  // 0x350520
    virtual void __cdecl start(void);  // 0x51e390
};

class DepositInGuildBankTaskEx
{
public:
    __cdecl DepositInGuildBankTaskEx(void);  // 0x537550
    bool __cdecl InitializeTry(::Zone *, ::Creature *, int, short, short const *const, short const *const);  // 0x537630
    bool __cdecl InitializeOk(::Zone *, ::Creature *, short, char const *const, short const *const);  // 0x537820
    bool __cdecl InitializeFail(::Zone *, ::Creature *, unsigned __int64, int, short, unsigned __int64 const *const, short const *const, char const *const);  // 0x537930
private:
    short __cdecl checkItemForDeposit(short, short const *const, short const *const, unsigned int &, short &, __int64 &, ::Item **const);  // 0x537ac0
    bool __cdecl makeTransaction(::Pc *, unsigned __int64);  // 0x537e50
    void __cdecl depositInGuildBankReq(void);  // 0x5387b0
    virtual void __cdecl TimerExpired(unsigned int, long);  // 0x538d60
    virtual void __cdecl start(void);  // 0x538da0
};

class DetachGemFromWeaponTask
{
public:
    bool __cdecl Initialize(::Zone *, ::Creature *, unsigned char, unsigned short, char, char);  // 0x51dda0
    virtual void __cdecl start(void);  // 0x51de90
};

class DetachPostAttachmentTask_IndetachFixed
{
public:
    enum Operation {};
public:
    __cdecl DetachPostAttachmentTask_IndetachFixed(void);  // 0x191a30
    virtual __cdecl ~DetachPostAttachmentTask_IndetachFixed(void);  // 0x542ca0
    bool __cdecl Initialize(::Zone *, ::Pc *, ::DetachPostAttachmentTask_IndetachFixed::Operation, ::DetachPostAttachmentTran_IndetachFixed *);  // 0x542d00
private:
    virtual void __cdecl TimerExpired(unsigned int, long);  // 0x542da0
    virtual void __cdecl start(void);  // 0x542de0
};

class DisposeItemTask
{
public:
    __cdecl DisposeItemTask(void);  // 0x283ac0
    bool __cdecl Initialize(::Zone *, ::Creature *, unsigned short, short);  // 0x50f7b0
    virtual void __cdecl start(void);  // 0x50f880
};

class DistributeItemTask
{
public:
    struct Order {};
public:
    bool __cdecl Initialize(::Zone *, ::Creature *, unsigned __int64, wchar_t const *, int, ::DistributeItemTask::Order const *const);  // 0x50d6a0
private:
    virtual void __cdecl start(void);  // 0x50d830
    bool __cdecl checkUserGamePlayRestriction(::NpcDeadBody *);  // 0x50f080
};

class DonateGuildCraftBrandMaterialTask
{
public:
    __cdecl DonateGuildCraftBrandMaterialTask(void);  // 0x5329a0
    bool __cdecl InitializeTry(::Zone *, ::Creature *, unsigned __int64, int, char, short, short const *const, short const *const);  // 0x532aa0
    bool __cdecl InitializeOk(::Zone *, ::Creature *, short, char const *const, short const *const);  // 0x532c90
    bool __cdecl InitializeFail(::Zone *, ::Creature *, short, unsigned __int64 const *const, short const *const, char const *const);  // 0x532da0
private:
    short __cdecl checkItemForDonation(short, short const *const, short const *const, int, char, unsigned int &, short &, int &, ::Item **const);  // 0x532f20
    bool __cdecl makeTransaction(::Pc *, unsigned __int64, short);  // 0x533370
    void __cdecl donationGuildCraftBrandMaterialReq(void);  // 0x533ab0
    virtual void __cdecl TimerExpired(unsigned int, long);  // 0x534000
    virtual void __cdecl start(void);  // 0x534040
};

class DonateGuildCraftNormalMaterialTask
{
public:
    __cdecl DonateGuildCraftNormalMaterialTask(void);  // 0x531320
    bool __cdecl InitializeTry(::Zone *, ::Creature *, unsigned __int64, short, short const *const, short const *const);  // 0x531420
    bool __cdecl InitializeOk(::Zone *, ::Creature *, short, char const *const, short const *const);  // 0x5315f0
    bool __cdecl InitializeFail(::Zone *, ::Creature *, short, unsigned __int64 const *const, short const *const, char const *const);  // 0x531700
private:
    short __cdecl checkItemForDonation(short, short const *const, short const *const, unsigned int &, short &, int &, ::Item **const);  // 0x531880
    bool __cdecl makeTransaction(::Pc *, unsigned __int64, short);  // 0x531bf0
    void __cdecl donationGuildCraftNormalMaterialReq(void);  // 0x5322f0
    virtual void __cdecl TimerExpired(unsigned int, long);  // 0x532830
    virtual void __cdecl start(void);  // 0x532870
};

class DonateGuildUniformTask
{
public:
    __cdecl DonateGuildUniformTask(void);  // 0x5349e0
    bool __cdecl InitializeForTry(::Zone *, ::Creature *, unsigned __int64, short, short const *const, short const *const);  // 0x534ad0
    bool __cdecl InitializeForOk(::Zone *, ::Creature *, char, char const *const, short const *const);  // 0x534c90
    bool __cdecl InitializeForFail(::Zone *, ::Creature *, unsigned __int64, short, unsigned __int64 const *const, short const *const, char const *const);  // 0x534de0
private:
    virtual void __cdecl start(void);  // 0x534f30
    bool __cdecl checkItemForDonation(void);  // 0x535570
    bool __cdecl makeTransaction(::Pc *, unsigned __int64);  // 0x535860
    virtual void __cdecl TimerExpired(unsigned int, long);  // 0x536050
};

class EquipAction
{
public:
    bool __cdecl Initialize(::Zone *, ::Creature *, unsigned char, unsigned short, unsigned char, unsigned short);  // 0x51cb30
private:
    virtual void __cdecl startAction(void);  // 0x51cc30
    virtual void __cdecl finishAction(void);  // 0x51d0a0
    virtual void __cdecl cancelAction(::Action::CancelReason, wchar_t const *, int);  // 0x51d250
    virtual void __cdecl failAction(::Action::FailReason);  // 0x51d330
};

class ExchangeFactionScoreTask
{
public:
    bool __cdecl Initialize(::Zone *, ::Creature *, unsigned __int64, int);  // 0x50a230
private:
    virtual void __cdecl start(void);  // 0x50a300
};

class ExchangeItemTask
{
public:
    struct Order {};
public:
    __cdecl ExchangeItemTask(void);  // 0x350900
    bool __cdecl Initialize(::Zone *, ::Creature *, char, unsigned __int64, ::ExchangeItemTask::Order *const, short);  // 0x546e50
private:
    int __cdecl getRecvRequiredItemCount(unsigned __int64);  // 0x546fe0
    short __cdecl getStackCount(unsigned __int64);  // 0x547200
    bool __cdecl determineMultipleReq(void);  // 0x547310
    bool __cdecl checkRequired(void);  // 0x547590
    bool __cdecl pickItems(::Inventory::AcquireOrder *const);  // 0x5476e0
public:
    virtual void __cdecl start(void);  // 0x547810
};

class ExpandInventoryAction
{
private:
    virtual void __cdecl startAction(void);  // 0x52f240
    bool __cdecl checkNpcCond(void);  // 0x52f560
    virtual void __cdecl failAction(::Action::FailReason);  // 0x52f720
};

class ExpandWeaponGemSlotTask
{
public:
    bool __cdecl Initialize(::Zone *, ::Creature *, unsigned char, unsigned short, unsigned short);  // 0x51dfb0
    virtual void __cdecl start(void);  // 0x51e090
};

class FeedingRandomStatEquipGemTask
{
public:
    __cdecl FeedingRandomStatEquipGemTask(void);  // 0x52fd80
private:
    virtual void __cdecl start(void);  // 0x52fe70
};

class GatherAction
{
private:
    virtual void __cdecl startAction(void);  // 0x52d200
    virtual void __cdecl failAction(::Action::FailReason);  // 0x52d340
    virtual void __cdecl finishAction(void);  // 0x52d370
    virtual void __cdecl cancelAction(::Action::CancelReason, wchar_t const *, int);  // 0x52d520
};

class GatherCancelTask
{
private:
    virtual void __cdecl start(void);  // 0x52d5b0
};

class GrowthItemTask
{
public:
    __cdecl GrowthItemTask(void);  // 0x52fa40
private:
    virtual void __cdecl start(void);  // 0x52faf0
};

class GuildTransactionTask
{
public:
    enum TransactionStep {};
public:
    __cdecl GuildTransactionTask(void);  // 0x53d460
    void __cdecl Initialize(::Zone *, ::Creature *, ::GuildTransactionTask::TransactionStep);  // 0x53d4e0
private:
    virtual void __cdecl start(void);  // 0x53d540
    void __cdecl onRegisterGuildOk(unsigned __int64, unsigned __int64);  // 0x53d5a0
    void __cdecl onRegisterGuildFail(short);  // 0x53d830
public:
    static void __cdecl SendFinishRegisterGuild(unsigned __int64, unsigned __int64, short, unsigned __int64);  // 0x53d8d0
private:
    void __cdecl onCreateGuildOk(unsigned __int64);  // 0x53da70
    void __cdecl onCreateGuildFail(short);  // 0x53e040
    virtual void __cdecl TimerExpired(unsigned int, long);  // 0x53e1d0
};

class IdentifyItemAction
{
public:
    virtual void __cdecl startAction(void);  // 0x51fb90
    virtual void __cdecl failAction(::Action::FailReason);  // 0x51fc70
};

class IncreaseUniformRegistrationQuotaTask
{
public:
    __cdecl IncreaseUniformRegistrationQuotaTask(void);  // 0x536090
    bool __cdecl InitializeForTry(::Zone *, ::Creature *, char, short, short const *const, short const *const);  // 0x536180
    bool __cdecl InitializeForOk(::Zone *, ::Creature *, char, char const *const, short const *const);  // 0x536330
    bool __cdecl InitializeForFail(::Zone *, ::Creature *, short, unsigned __int64 const *const, short const *const, char const *const);  // 0x536480
private:
    virtual void __cdecl start(void);  // 0x5365d0
    bool __cdecl checkItemForPayment(void);  // 0x536ad0
    bool __cdecl makeTransaction(::Pc *, unsigned __int64, short);  // 0x536db0
    virtual void __cdecl TimerExpired(unsigned int, long);  // 0x537510
};

class ItemListTask
{
private:
    virtual void __cdecl start(void);  // 0x50a1e0
};

class LockItemTask
{
public:
    bool __cdecl Initialize(::Zone *, ::Creature *, unsigned char, unsigned short);  // 0x52ff40
private:
    virtual void __cdecl start(void);  // 0x530010
};

class LootAction
{
public:
    bool __cdecl Initialize(::Zone *, ::Creature *, unsigned __int64);  // 0x52cd90
private:
    virtual void __cdecl startAction(void);  // 0x52ce90
    virtual void __cdecl failAction(::Action::FailReason);  // 0x52d0e0
    void __cdecl finishAction(void);  // 0x52d110
};

class MakeCustomDressTask
{
public:
    struct RequiredOrder {};
public:
    __cdecl MakeCustomDressTask(void);  // 0x3509c0
    bool __cdecl Initialize(::Zone *, ::Creature *, short, char *const, char *const, short, ::Inventory::DisposeOrderWithPos *const, short);  // 0x548770
    virtual void __cdecl start(void);  // 0x548940
private:
    ::GameFailReason __cdecl calcCost(::Item const *, __int64 &, ::MakeCustomDressTask::RequiredOrder *const, char &);  // 0x54a040
    bool __cdecl accumulateCost(::Data::CustomDressDesignCostRecord::Key, __int64 &, ::MakeCustomDressTask::RequiredOrder *const, char &);  // 0x54a650
    char __cdecl getCustomDressValue(::Item const *, char) const;  // 0x54a750
    bool __cdecl setCustomDressValue(::Item *, char, short);  // 0x54a940
    ::Data::CustomDressDesignTypeInfoItemTypeType __cdecl EquipType2CustomItemType(::Item const *);  // 0x54ab60
    void __cdecl setNoCharge(void);  // 0x54ac60
};

class MarkExpressPostTask2
{
public:
    enum Operation {};
public:
    __cdecl MarkExpressPostTask2(void);  // 0x1919a0
    virtual __cdecl ~MarkExpressPostTask2(void);  // 0x542320
    bool __cdecl Initialize(::Zone *, ::Pc *, ::MarkExpressPostTask2::Operation, ::MarkExpressPostTran *);  // 0x542380
private:
    virtual void __cdecl TimerExpired(unsigned int, long);  // 0x542420
    virtual void __cdecl start(void);  // 0x542460
};

class MarketTask
{
public:
    enum MarketType {};
public:
    __cdecl MarketTask(void);  // 0x53e210
    bool __cdecl Initialize(::Zone *, ::Creature *, ::MarketTask::MarketType, short);  // 0x53e290
private:
    virtual void __cdecl start(void);  // 0x53e360
};

class MoveItemListTask
{
public:
    enum MoveItemListStep {};
public:
    __cdecl MoveItemListTask(void);  // 0x511840
    bool __cdecl Initialize(::Zone *, ::Creature *, char, __int64);  // 0x5118f0
    bool __cdecl Initialize(::Zone *, ::Creature *, ::MoveItemListTask::MoveItemListStep, short);  // 0x511a20
    bool __cdecl Initialize(::Zone *, ::Creature *);  // 0x511b40
    virtual void __cdecl start(void);  // 0x511c50
    short __cdecl CheckPreConditionForMoveItem(void);  // 0x5120b0
private:
    short __cdecl checkNpcCond(void);  // 0x5121b0
    bool __cdecl IsItemListReserved(void);  // 0x5124d0
    void __cdecl SetItemListReserved(void);  // 0x512650
    void __cdecl ResetItemListReserved(void);  // 0x5127c0
    void __cdecl CallInvenMove(void);  // 0x512960
    void __cdecl OnMoveItemReq(void);  // 0x512b00
    void __cdecl OnGetStatusOk(void);  // 0x512d90
    void __cdecl OnGetStatusFail(void);  // 0x512f10
    void __cdecl OnIsVerifiedFail(void);  // 0x512ff0
};

class MoveItemTask
{
public:
    enum MoveItemStep {};
public:
    __cdecl MoveItemTask(void);  // 0x121370
    bool __cdecl Initialize(::Zone *, ::Creature *, unsigned char, unsigned short, unsigned char, unsigned short, short, __int64);  // 0x510520
    bool __cdecl Initialize(::Zone *, ::Creature *, char, __int64);  // 0x510630
    bool __cdecl Initialize(::Zone *, ::Creature *, ::MoveItemTask::MoveItemStep, short);  // 0x510740
    bool __cdecl Initialize(::Zone *, ::Creature *);  // 0x510840
    virtual void __cdecl start(void);  // 0x510930
    short __cdecl CheckPreConditionForMoveItem(void);  // 0x510ca0
private:
    short __cdecl checkNpcCond(void);  // 0x510da0
    bool __cdecl IsItemReserved(void);  // 0x5110c0
    void __cdecl SetItemReserved(void);  // 0x511150
    void __cdecl ResetItemReserved(void);  // 0x5111c0
    void __cdecl CallInvenMove(void);  // 0x511260
    void __cdecl OnMoveItemReq(void);  // 0x5112e0
    void __cdecl OnGetStatusOk(void);  // 0x5114f0
    void __cdecl OnGetStatusFail(void);  // 0x511660
    void __cdecl OnIsVerifiedFail(void);  // 0x511730
};

class MysteriousBuyTask
{
public:
    bool __cdecl Initialize(::Zone *, ::Creature *, unsigned __int64, char, int, ::BuyBaseTask::DisposeOrder const *const);  // 0x51a8f0
private:
    virtual void __cdecl start(void);  // 0x51aa20
    unsigned __int64 __cdecl getMysteriousStoreItemGroup(::Npc const *);  // 0x51b400
};

class OpenWeaponGemSlotTask
{
public:
    __cdecl OpenWeaponGemSlotTask(void);  // 0x3505e0
    virtual void __cdecl start(void);  // 0x51e450
};

class PassingItemAbilityTask
{
public:
    struct DecideAbilityContext {};
    struct Order {};
public:
    __cdecl PassingItemAbilityTask(void);  // 0x3507a0
    bool __cdecl Initialize(::Zone *, ::Creature *, unsigned __int64, ::PassingItemAbilityTask::Order *const, short, ::PassingItemAbilityTask::Order *const, short, ::PassingItemAbilityTask::Order *const, short);  // 0x5287b0
private:
    virtual void __cdecl start(void);  // 0x5289f0
protected:
    ::GameFailReason __cdecl checkTargetItem(void);  // 0x528d30
    ::GameFailReason __cdecl checkMainIngredient(void);  // 0x5291f0
    ::GameFailReason __cdecl checkFixedIngredient(void);  // 0x5294a0
private:
    bool __cdecl applyPassingItemAbilityResult(::Inventory::DisposeOrderWithPos const *const);  // 0x529890
protected:
    bool __cdecl fillOrders(::Inventory::DisposeOrderWithPos *const);  // 0x52ad90
    int __cdecl decideAbilityValue(int, int, ::PassingItemAbilityTask::DecideAbilityContext *);  // 0x52afb0
};

class PawnTask
{
public:
    enum PawnType {};
public:
    __cdecl PawnTask(void);  // 0x5310e0
    bool __cdecl Initialize(::Zone *, ::Creature *, ::PawnTask::PawnType, unsigned __int64, unsigned __int64);  // 0x531160
private:
    virtual void __cdecl start(void);  // 0x531240
};

class PickupAction
{
public:
    bool __cdecl Initialize(::Zone *, ::Creature *, unsigned __int64);  // 0x52b1a0
private:
    virtual void __cdecl startAction(void);  // 0x52b2b0
    void __cdecl sendOpenItemPouchOk(::Pc *, ::ItemPouch *);  // 0x52bf30
    virtual bool __cdecl availableCancel(::CancelActionReason);  // 0x52c230
    virtual void __cdecl cancelAction(::Action::CancelReason, wchar_t const *, int);  // 0x52c240
    virtual void __cdecl failAction(::Action::FailReason);  // 0x52c640
    bool __cdecl openPartyAuction(::ItemPouch *, unsigned __int64 *const, int);  // 0x52c6a0
};

class PickupDeadBodyAction
{
private:
    virtual bool __cdecl availableCancel(::CancelActionReason);  // 0x52e720
    virtual void __cdecl startAction(void);  // 0x52ed10
    virtual void __cdecl finishAction(void);  // 0x52f020
    virtual void __cdecl cancelAction(::Action::CancelReason, wchar_t const *, int);  // 0x52f110
    virtual void __cdecl failAction(::Action::FailReason);  // 0x52f1c0
};

class PickupFieldItemAction
{
private:
    virtual void __cdecl startAction(void);  // 0x52e210
    virtual void __cdecl finishAction(void);  // 0x52e500
    virtual void __cdecl cancelAction(::Action::CancelReason, wchar_t const *, int);  // 0x52e5f0
    virtual void __cdecl failAction(::Action::FailReason);  // 0x52e6a0
};

class PickupItemSessionTask
{
public:
    enum SessionState {};
public:
    __cdecl PickupItemSessionTask(void);  // 0x350450
    bool __cdecl Initialize(::Zone *, ::Creature *, unsigned __int64, ::PickupItemSessionTask::SessionState);  // 0x50ad70
private:
    virtual void __cdecl start(void);  // 0x50ae40
};

class PickupItemTask
{
public:
    struct Order {};
public:
    bool __cdecl Initialize(::Zone *, ::Creature *, unsigned __int64, char, int, ::PickupItemTask::Order const *const);  // 0x50b490
private:
    virtual void __cdecl start(void);  // 0x50b600
    bool __cdecl checkUserGamePlayRestriction(::NpcDeadBody *);  // 0x50d2d0
};

class PrivateItemPouchListTask
{
public:
    bool __cdecl Initialize(::Zone *, ::Creature *, unsigned __int64);  // 0x50b000
private:
    virtual void __cdecl start(void);  // 0x50b0d0
};

class ProcessItemFusionTask
{
public:
    __cdecl ProcessItemFusionTask(void);  // 0x350c00
private:
    virtual void __cdecl start(void);  // 0x54e110
    ::GameFailReason __cdecl fillOrders(int &, ::Inventory::AcquireOrder *const, int &, ::Inventory::DisposeOrderWithPos *const);  // 0x54e430
};

class PutdownFieldItemAction
{
private:
    virtual void __cdecl startAction(void);  // 0x52e730
    virtual void __cdecl finishAction(void);  // 0x52e9f0
    virtual void __cdecl cancelAction(::Action::CancelReason, wchar_t const *, int);  // 0x52eb70
    virtual void __cdecl failAction(::Action::FailReason);  // 0x52ec80
    virtual bool __cdecl availableCancel(::CancelActionReason);  // 0x52ed00
};

class R_EnchantToItemTask
{
public:
    __cdecl R_EnchantToItemTask(void);  // 0x5308d0
    bool __cdecl Initialize(::Zone *, ::Creature *, unsigned char, unsigned short, unsigned __int64);  // 0x530950
private:
    virtual void __cdecl start(void);  // 0x530a30
};

class R_PolishToItemTask
{
public:
    __cdecl R_PolishToItemTask(void);  // 0x530f80
private:
    virtual void __cdecl start(void);  // 0x531010
};

class R_ResetEnchantItemInfoTask
{
public:
    bool __cdecl Initialize(::Zone *, ::Creature *, unsigned char, unsigned short);  // 0x530ad0
private:
    virtual void __cdecl start(void);  // 0x530ba0
};

class R_ResetEnchantRestoreInfoTask
{
public:
    bool __cdecl Initialize(::Zone *, ::Creature *, unsigned char, unsigned short);  // 0x530c20
private:
    virtual void __cdecl start(void);  // 0x530cf0
};

class R_RestoreEnchantFailedItemTask
{
public:
    __cdecl R_RestoreEnchantFailedItemTask(void);  // 0x530d70
    bool __cdecl Initialize(::Zone *, ::Creature *, char, short, short, unsigned __int64);  // 0x530de0
private:
    virtual void __cdecl start(void);  // 0x530ed0
};

class RebuyItemListTask
{
public:
    bool __cdecl Initialize(::Zone *, ::Creature *);  // 0x50ac70
private:
    virtual void __cdecl start(void);  // 0x50ad20
};

class RebuyTask
{
public:
    bool __cdecl Initialize(::Zone *, ::Creature *, unsigned __int64, char);  // 0x5155d0
private:
    virtual void __cdecl start(void);  // 0x5156a0
};

class RegisterBidTask2
{
public:
    enum Operation {};
public:
    __cdecl RegisterBidTask2(void);  // 0x121710
    virtual __cdecl ~RegisterBidTask2(void);  // 0x544650
    bool __cdecl Initialize(::Zone *, ::Pc *, ::RegisterBidTask2::Operation, ::RegisterBidTran *);  // 0x5446b0
private:
    virtual void __cdecl TimerExpired(unsigned int, long);  // 0x544750
    virtual void __cdecl start(void);  // 0x544790
};

class RegisterGuildTask
{
public:
    __cdecl RegisterGuildTask(void);  // 0x53a7d0
    bool __cdecl Initialize(::Zone *, ::Creature *, char, wchar_t *, __int64);  // 0x53a880
private:
    virtual void __cdecl start(void);  // 0x53a9d0
};

class RegisterPurchaseTask2
{
public:
    enum Operation {};
public:
    __cdecl RegisterPurchaseTask2(void);  // 0x121680
    virtual __cdecl ~RegisterPurchaseTask2(void);  // 0x543ad0
    bool __cdecl Initialize(::Zone *, ::Pc *, ::RegisterPurchaseTask2::Operation, ::RegisterPurchaseTran *);  // 0x543b30
private:
    virtual void __cdecl TimerExpired(unsigned int, long);  // 0x543bd0
    virtual void __cdecl start(void);  // 0x543c10
};

class RegisterSaleAction
{
public:
    __cdecl RegisterSaleAction(void);  // 0x53e450
    bool __cdecl Initialize(::Zone *, ::Creature *, __int64, char, __int64, int, short, short, bool);  // 0x53e4d0
    virtual void __cdecl startAction(void);  // 0x53e5c0
    void __cdecl OnReserveSaleOk(__int64);  // 0x53eb60
    void __cdecl OnReserveSaleFail(short);  // 0x53edf0
    void __cdecl OnRegisterPawnOk(__int64);  // 0x53eeb0
    void __cdecl OnRegisterPawnFail(void);  // 0x53ef30
    void __cdecl OnRegisterSaleOk(void);  // 0x53f190
    void __cdecl OnRegisterSaleFail(short);  // 0x53f210
    void __cdecl OnCancelPawnOk(void);  // 0x53f360
    void __cdecl OnCancelPawnFail(void);  // 0x53f580
    void __cdecl OnConfirmedSplitItem(unsigned short, __int64, char);  // 0x53f6b0
private:
    void __cdecl sendRegisterPawn(void);  // 0x53f810
    void __cdecl sendRegisterSale(void);  // 0x53f9e0
    bool __cdecl checkItems(void);  // 0x540240
    __int64 __cdecl getExtraFee(void);  // 0x5408a0
    bool __cdecl pawnItems(void);  // 0x540ca0
public:
    virtual void __cdecl finishAction(void);  // 0x540f30
    virtual void __cdecl cancelAction(::Action::CancelReason, wchar_t const *, int);  // 0x540fc0
    virtual void __cdecl failAction(::Action::FailReason);  // 0x541120
};

class RenameGuildTask
{
public:
    enum TransactionStep {};
public:
    __cdecl RenameGuildTask(void);  // 0x53af70
    bool __cdecl InitializeReqFromClient(::Zone *, ::Creature *, ::RenameGuildTask::TransactionStep, char, wchar_t *, short);  // 0x53b0e0
    bool __cdecl InitializeOkFromLobby(::Zone *, ::Creature *, ::RenameGuildTask::TransactionStep, unsigned __int64, unsigned __int64, char, wchar_t *, short, ::RenameGuildTranPropertyTransactionParam &, unsigned __int64);  // 0x53b290
    bool __cdecl InitializeOkFromCache(::Zone *, ::Creature *, ::RenameGuildTask::TransactionStep, unsigned __int64, unsigned __int64, char, wchar_t *, short, ::RenameGuildTranPropertyTransactionParam &, unsigned __int64, __int64);  // 0x53b4a0
    bool __cdecl InitializeAbort(::Zone *, ::Creature *, ::RenameGuildTask::TransactionStep, unsigned __int64, unsigned __int64, char, wchar_t *, short, ::RenameGuildTranPropertyTransactionParam &, unsigned __int64, short);  // 0x53b6d0
private:
    virtual void __cdecl start(void);  // 0x53b920
    bool __cdecl checkCostItem(void);  // 0x53bb10
    bool __cdecl makeRenameGuildTran(void);  // 0x53bef0
    void __cdecl renameGuildReqFromClient(void);  // 0x53c510
    void __cdecl renameGuildOkFromLobby(void);  // 0x53ca80
    void __cdecl renameGuildOkFromCache(void);  // 0x53d060
    void __cdecl renameGuildAbort(void);  // 0x53d290
    virtual void __cdecl TimerExpired(unsigned int, long);  // 0x53d420
};

class RepairTask
{
private:
    virtual void __cdecl start(void);  // 0x51bd40
    bool __cdecl calculatePrice(unsigned char *const, unsigned short *const, int, unsigned char *const, unsigned short *const, int *, __int64 *);  // 0x51c700
};

class RepairWithCampfireAction
{
public:
    bool __cdecl Initialize(::Zone *, ::Creature *, __int64, short);  // 0x51e590
private:
    virtual void __cdecl failAction(::Action::FailReason);  // 0x51e660
    virtual void __cdecl startAction(void);  // 0x51e690
    bool __cdecl consumeItem(void);  // 0x51edb0
    bool __cdecl repair(void);  // 0x51f2c0
    virtual void __cdecl finishAction(void);  // 0x51f830
    virtual void __cdecl cancelAction(::Action::CancelReason, wchar_t const *, int);  // 0x51f8d0
    virtual bool __cdecl availableCancel(::CancelActionReason);  // 0x51fa50
};

class RevealItemAbilityAction
{
private:
    virtual void __cdecl startAction(void);  // 0x52f750
    virtual void __cdecl failAction(::Action::FailReason);  // 0x52f8a0
};

class SealItemAction
{
public:
    virtual void __cdecl startAction(void);  // 0x51fa70
    virtual void __cdecl failAction(::Action::FailReason);  // 0x51fb60
};

class SellOldItemTask
{
public:
    struct Order {};
private:
    virtual void __cdecl start(void);  // 0x545a60
    bool __cdecl fillOrders(::Inventory::DisposeOrderWithPos *const, int &, char, ::SellOldItemTask::Order const *const, int, __int64 *, int &, int *const);  // 0x546950
};

class SellTask
{
public:
    struct Order {};
private:
    virtual void __cdecl start(void);  // 0x513dd0
    bool __cdecl fillOrders2(::Inventory::DisposeOrderWithPos *const, int &, ::SellTask::Order const *const, int, __int64 *, int &);  // 0x514fd0
    void __cdecl writeGameLogSalesLimitExceed(::Pc *);  // 0x5153d0
};

class SetItemLockExpirationTimeTask
{
public:
    bool __cdecl Initialize(::Zone *, ::Creature *, unsigned char, unsigned short);  // 0x530280
private:
    virtual void __cdecl start(void);  // 0x530350
};

class SetItemUsedTask
{
public:
    struct Order {};
public:
    __cdecl SetItemUsedTask(void);  // 0x530460
    bool __cdecl Initialize(::Zone *, ::Creature *, int, ::SetItemUsedTask::Order *const);  // 0x530530
private:
    virtual void __cdecl start(void);  // 0x5306c0
};

class SynthesisBadgeTask
{
public:
    __cdecl SynthesisBadgeTask(void);  // 0x350a80
private:
    virtual void __cdecl start(void);  // 0x54adc0
    ::GameFailReason __cdecl fillOrders(int &, ::Inventory::AcquireOrder *const, int &, ::Inventory::DisposeOrderWithPos *const, int &, ::Inventory::DisposeOrderWithPos *const);  // 0x54bf10
};

class TakeContributionRewardTask
{
public:
    bool __cdecl Initialize(::Zone *, ::Creature *, unsigned __int64);  // 0x50d380
private:
    virtual void __cdecl start(void);  // 0x50d4b0
};

class TakeGuildCraftTask
{
public:
    enum TakeGuildCraftType {};
public:
    __cdecl TakeGuildCraftTask(void);  // 0x283b20
    bool __cdecl InitializeForTry(::Zone *, ::Creature *, ::TakeGuildCraftTask::TakeGuildCraftType, unsigned __int64, int);  // 0x534170
    bool __cdecl InitializeForOk(::Zone *, ::Creature *, ::TakeGuildCraftTask::TakeGuildCraftType, unsigned __int64, unsigned __int64);  // 0x534250
    bool __cdecl InitializeForFail(::Zone *, ::Creature *, ::TakeGuildCraftTask::TakeGuildCraftType, ::PropertyTransactionFailParam *);  // 0x534330
private:
    virtual void __cdecl start(void);  // 0x534460
    virtual void __cdecl TimerExpired(unsigned int, long);  // 0x5349a0
};

class TradeWithNpcTask
{
private:
    virtual void __cdecl start(void);  // 0x515a40
    bool __cdecl fillOrders(::Data::StoreByItemRecordPtr, ::Inventory::AcquireOrder &, ::Inventory::DisposeOrderWithPos *const);  // 0x5164c0
};

class TransformItemTask
{
public:
    struct Order {};
    enum TransformOperation {};
public:
    __cdecl TransformItemTask(void);  // 0x1213d0
    virtual __cdecl ~TransformItemTask(void);  // 0x51fe20
    virtual void __cdecl ProcessUnexpired(int);  // 0x51fe80
private:
    virtual void __cdecl TimerExpired(unsigned int, long);  // 0x5200c0
    virtual void __cdecl start(void);  // 0x520100
public:
    bool __cdecl Initialize(::Zone *, ::Creature *, unsigned __int64, ::TransformItemTask::Order *const, short, ::TransformItemTask::Order *const, short, ::TransformItemTask::Order *const, short, ::TransformItemTask::Order *const, short, ::TransformItemTask::TransformOperation);  // 0x520290
    bool __cdecl InitializeInstantPaymentOk(::Zone *, ::Creature *, unsigned __int64, ::InstantPaymentTran *, __int64, ::InstantPaymentTransformInfoParam *);  // 0x5204a0
    bool __cdecl InitializeInstantPaymentFail(::Zone *, ::Creature *, unsigned __int64, unsigned __int64, ::InstantPaymentTransformInfoParam *);  // 0x520730
protected:
    char __cdecl getUpgradeGroceryDataIndex(::Data::ItemTransformUpgradeItemRecordPtr &);  // 0x520910
    bool __cdecl checkUpgradeGrocery(void);  // 0x520ae0
    ::GameFailReason __cdecl checkMainIngredientItem(::Data::ItemRecordPtr &);  // 0x520ef0
    ::GameFailReason __cdecl checkMainIngredientItemBrand(::Data::ItemBrandRecordPtr &);  // 0x521380
    bool __cdecl checkMainIngredientWeaponItem(void);  // 0x521760
    bool __cdecl checkMainIngredientSpiritAttachedItem(void);  // 0x521b30
    ::GameFailReason __cdecl checkMainIngredient(void);  // 0x521f40
    bool __cdecl checkSubIngredientItem(::Data::ItemRecordPtr &, int, int &);  // 0x521fe0
    bool __cdecl checkSubIngredientItemBrand(::Data::ItemBrandRecordPtr &, int, int &);  // 0x5225a0
    bool __cdecl checkSubIngredient(void);  // 0x522b50
    bool __cdecl checkFixedIngredient(void);  // 0x522cc0
    bool __cdecl checkWeaponGem(::Data::ItemRecordPtr const &, char, short, char);  // 0x523130
    int __cdecl getDiscountMoney(void);  // 0x523200
    bool __cdecl checkRecipe(::GameFailReason *);  // 0x523530
    ::ItemTransformGroup __cdecl decideTransformGroup(void);  // 0x5237e0
    bool __cdecl fillOrders(::ItemTransformGroup, ::Inventory::AcquireOrder *const, ::Inventory::DisposeOrderWithPos *const, char &);  // 0x5239f0
    void __cdecl fillWeaponGemDisposeOrder(::Inventory::DisposeOrderWithPos *const);  // 0x523fe0
    bool __cdecl pickItems(::ItemTransformGroup, ::Inventory::AcquireOrder *const);  // 0x524260
    unsigned __int64 __cdecl decideItem(::dr_tref const &);  // 0x5246b0
    bool __cdecl pickRandomItems(::Inventory::AcquireOrder *const, char &);  // 0x524860
    bool __cdecl pickWeaponGem(::Inventory::AcquireOrder &);  // 0x524a30
    char __cdecl decideWeaponGemType(char, char);  // 0x524db0
    void __cdecl invokeTransformFailEffect(void);  // 0x524fe0
    bool __cdecl setTransformFailureExp(::Item *);  // 0x5250a0
    void __cdecl setTransformFailureExpDiff(void);  // 0x525400
    void __cdecl handleTransformFailureExp(short &);  // 0x525780
    ::GameFailReason __cdecl checkCondition(void);  // 0x525b70
private:
    void __cdecl startTransformNormal(void);  // 0x525c70
    bool __cdecl applyTransformResult(::Inventory::DisposeOrderWithPos const *const, ::Inventory::AcquireOrder *const, ::ItemTransformGroup, char);  // 0x526140
    ::GameFailReason __cdecl instantPaymentTry(void);  // 0x5275f0
    ::GameFailReason __cdecl instantPaymentOK(void);  // 0x527d20
    void __cdecl instantPaymentFail(void);  // 0x5284b0
    void __cdecl setNoCharge(void);  // 0x528640
};

class UnequipAction
{
public:
    bool __cdecl Initialize(::Zone *, ::Creature *, unsigned char, unsigned short, unsigned char, unsigned short);  // 0x51d360
private:
    virtual void __cdecl startAction(void);  // 0x51d460
    virtual void __cdecl finishAction(void);  // 0x51d830
    virtual void __cdecl cancelAction(::Action::CancelReason, wchar_t const *, int);  // 0x51dab0
    virtual void __cdecl failAction(::Action::FailReason);  // 0x51dba0
};

class UnlockItemTask
{
public:
    bool __cdecl Initialize(::Zone *, ::Creature *, unsigned char, unsigned short);  // 0x530090
private:
    virtual void __cdecl start(void);  // 0x530160
};

class UnlockMasteryLevelAction
{
private:
    virtual void __cdecl startAction(void);  // 0x51b620
    bool __cdecl fillOrders(::Inventory::DisposeOrderWithPos *const, unsigned __int64 &, int &);  // 0x51b8b0
    virtual void __cdecl failAction(::Action::FailReason);  // 0x51bc40
    virtual void __cdecl finishAction(void);  // 0x51bc80
};

class UnsealItemAction
{
public:
    __cdecl UnsealItemAction(void);  // 0x467690
    virtual void __cdecl startAction(void);  // 0x51fca0
    virtual void __cdecl failAction(::Action::FailReason);  // 0x51fd20
};

class UpdateBidTask2
{
public:
    enum Operation {};
public:
    __cdecl UpdateBidTask2(void);  // 0x1217a0
    virtual __cdecl ~UpdateBidTask2(void);  // 0x5451c0
    bool __cdecl Initialize(::Zone *, ::Pc *, ::UpdateBidTask2::Operation, ::UpdateBidTran *);  // 0x545220
private:
    virtual void __cdecl TimerExpired(unsigned int, long);  // 0x5452c0
    virtual void __cdecl start(void);  // 0x545300
};

class UseSkillSkinAcquirementItemAction
{
private:
    virtual void __cdecl startAction(void);  // 0x52d640
    virtual void __cdecl failAction(::Action::FailReason);  // 0x52e170
};

