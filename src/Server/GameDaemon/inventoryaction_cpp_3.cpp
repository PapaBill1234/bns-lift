// inventoryaction_cpp_3.cpp: inventoryaction.cpp part 3 (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "inventoryaction.h"
#include "action.h"
#include "creature.h"
#include "guildtran.h"
#include "item.h"
#include "pc.h"
#include "zone.h"
#include "LiftStub.h"

// 0x52f8a0
void __cdecl RevealItemAbilityAction::failAction(::Action::FailReason)
{
    LIFT_STUB(0x52f8a0);
}

// 0x52f8d0
void __cdecl AttachEquipGemPieceAction::startAction(void)
{
    LIFT_STUB(0x52f8d0);
}

// 0x52fa10
void __cdecl AttachEquipGemPieceAction::failAction(::Action::FailReason)
{
    LIFT_STUB(0x52fa10);
}

// 0x52fa40
__cdecl GrowthItemTask::GrowthItemTask(void)
{
    LIFT_STUB(0x52fa40);
}

// 0x52faf0
void __cdecl GrowthItemTask::start(void)
{
    LIFT_STUB(0x52faf0);
}

// 0x52fbc0
__cdecl AwakeningItemTask::AwakeningItemTask(void)
{
    LIFT_STUB(0x52fbc0);
}

// 0x52fcb0
void __cdecl AwakeningItemTask::start(void)
{
    LIFT_STUB(0x52fcb0);
}

// 0x52fd80
__cdecl FeedingRandomStatEquipGemTask::FeedingRandomStatEquipGemTask(void)
{
    LIFT_STUB(0x52fd80);
}

// 0x52fe70
void __cdecl FeedingRandomStatEquipGemTask::start(void)
{
    LIFT_STUB(0x52fe70);
}

// 0x52ff40
bool __cdecl LockItemTask::Initialize(::Zone *, ::Creature *, unsigned char, unsigned short)
{
    LIFT_STUB(0x52ff40);
}

// 0x530010
void __cdecl LockItemTask::start(void)
{
    LIFT_STUB(0x530010);
}

// 0x530090
bool __cdecl UnlockItemTask::Initialize(::Zone *, ::Creature *, unsigned char, unsigned short)
{
    LIFT_STUB(0x530090);
}

// 0x530160
void __cdecl UnlockItemTask::start(void)
{
    LIFT_STUB(0x530160);
}

// 0x530280
bool __cdecl SetItemLockExpirationTimeTask::Initialize(::Zone *, ::Creature *, unsigned char, unsigned short)
{
    LIFT_STUB(0x530280);
}

// 0x530350
void __cdecl SetItemLockExpirationTimeTask::start(void)
{
    LIFT_STUB(0x530350);
}

// 0x530460
__cdecl SetItemUsedTask::SetItemUsedTask(void)
{
    LIFT_STUB(0x530460);
}

// 0x530530
bool __cdecl SetItemUsedTask::Initialize(::Zone *, ::Creature *, int, ::SetItemUsedTask::Order *const)
{
    LIFT_STUB(0x530530);
}

// 0x5306c0
void __cdecl SetItemUsedTask::start(void)
{
    LIFT_STUB(0x5306c0);
}

// 0x5308d0
__cdecl R_EnchantToItemTask::R_EnchantToItemTask(void)
{
    LIFT_STUB(0x5308d0);
}

// 0x530950
bool __cdecl R_EnchantToItemTask::Initialize(::Zone *, ::Creature *, unsigned char, unsigned short, unsigned __int64)
{
    LIFT_STUB(0x530950);
}

// 0x530a30
void __cdecl R_EnchantToItemTask::start(void)
{
    LIFT_STUB(0x530a30);
}

// 0x530ad0
bool __cdecl R_ResetEnchantItemInfoTask::Initialize(::Zone *, ::Creature *, unsigned char, unsigned short)
{
    LIFT_STUB(0x530ad0);
}

// 0x530ba0
void __cdecl R_ResetEnchantItemInfoTask::start(void)
{
    LIFT_STUB(0x530ba0);
}

// 0x530c20
bool __cdecl R_ResetEnchantRestoreInfoTask::Initialize(::Zone *, ::Creature *, unsigned char, unsigned short)
{
    LIFT_STUB(0x530c20);
}

// 0x530cf0
void __cdecl R_ResetEnchantRestoreInfoTask::start(void)
{
    LIFT_STUB(0x530cf0);
}

// 0x530d70
__cdecl R_RestoreEnchantFailedItemTask::R_RestoreEnchantFailedItemTask(void)
{
    LIFT_STUB(0x530d70);
}

// 0x530de0
bool __cdecl R_RestoreEnchantFailedItemTask::Initialize(::Zone *, ::Creature *, char, short, short, unsigned __int64)
{
    LIFT_STUB(0x530de0);
}

// 0x530ed0
void __cdecl R_RestoreEnchantFailedItemTask::start(void)
{
    LIFT_STUB(0x530ed0);
}

// 0x530f80
__cdecl R_PolishToItemTask::R_PolishToItemTask(void)
{
    LIFT_STUB(0x530f80);
}

// 0x531010
void __cdecl R_PolishToItemTask::start(void)
{
    LIFT_STUB(0x531010);
}

// 0x5310e0
__cdecl PawnTask::PawnTask(void)
{
    LIFT_STUB(0x5310e0);
}

// 0x531160
bool __cdecl PawnTask::Initialize(::Zone *, ::Creature *, ::PawnTask::PawnType, unsigned __int64, unsigned __int64)
{
    LIFT_STUB(0x531160);
}

// 0x531240
void __cdecl PawnTask::start(void)
{
    LIFT_STUB(0x531240);
}

// 0x531320
__cdecl DonateGuildCraftNormalMaterialTask::DonateGuildCraftNormalMaterialTask(void)
{
    LIFT_STUB(0x531320);
}

// 0x531420
bool __cdecl DonateGuildCraftNormalMaterialTask::InitializeTry(::Zone *, ::Creature *, unsigned __int64, short, short const *const, short const *const)
{
    LIFT_STUB(0x531420);
}

// 0x5315f0
bool __cdecl DonateGuildCraftNormalMaterialTask::InitializeOk(::Zone *, ::Creature *, short, char const *const, short const *const)
{
    LIFT_STUB(0x5315f0);
}

// 0x531700
bool __cdecl DonateGuildCraftNormalMaterialTask::InitializeFail(::Zone *, ::Creature *, short, unsigned __int64 const *const, short const *const, char const *const)
{
    LIFT_STUB(0x531700);
}

// 0x531880
short __cdecl DonateGuildCraftNormalMaterialTask::checkItemForDonation(short, short const *const, short const *const, unsigned int &, short &, int &, ::Item **const)
{
    LIFT_STUB(0x531880);
}

// 0x531bf0
bool __cdecl DonateGuildCraftNormalMaterialTask::makeTransaction(::Pc *, unsigned __int64, short)
{
    LIFT_STUB(0x531bf0);
}

// 0x5322f0
void __cdecl DonateGuildCraftNormalMaterialTask::donationGuildCraftNormalMaterialReq(void)
{
    LIFT_STUB(0x5322f0);
}

// 0x532830
void __cdecl DonateGuildCraftNormalMaterialTask::TimerExpired(unsigned int, long)
{
    LIFT_STUB(0x532830);
}

// 0x532870
void __cdecl DonateGuildCraftNormalMaterialTask::start(void)
{
    LIFT_STUB(0x532870);
}

// 0x5329a0
__cdecl DonateGuildCraftBrandMaterialTask::DonateGuildCraftBrandMaterialTask(void)
{
    LIFT_STUB(0x5329a0);
}

// 0x532aa0
bool __cdecl DonateGuildCraftBrandMaterialTask::InitializeTry(::Zone *, ::Creature *, unsigned __int64, int, char, short, short const *const, short const *const)
{
    LIFT_STUB(0x532aa0);
}

// 0x532c90
bool __cdecl DonateGuildCraftBrandMaterialTask::InitializeOk(::Zone *, ::Creature *, short, char const *const, short const *const)
{
    LIFT_STUB(0x532c90);
}

// 0x532da0
bool __cdecl DonateGuildCraftBrandMaterialTask::InitializeFail(::Zone *, ::Creature *, short, unsigned __int64 const *const, short const *const, char const *const)
{
    LIFT_STUB(0x532da0);
}

// 0x532f20
short __cdecl DonateGuildCraftBrandMaterialTask::checkItemForDonation(short, short const *const, short const *const, int, char, unsigned int &, short &, int &, ::Item **const)
{
    LIFT_STUB(0x532f20);
}

// 0x533370
bool __cdecl DonateGuildCraftBrandMaterialTask::makeTransaction(::Pc *, unsigned __int64, short)
{
    LIFT_STUB(0x533370);
}

// 0x533ab0
void __cdecl DonateGuildCraftBrandMaterialTask::donationGuildCraftBrandMaterialReq(void)
{
    LIFT_STUB(0x533ab0);
}

// 0x534000
void __cdecl DonateGuildCraftBrandMaterialTask::TimerExpired(unsigned int, long)
{
    LIFT_STUB(0x534000);
}

// 0x534040
void __cdecl DonateGuildCraftBrandMaterialTask::start(void)
{
    LIFT_STUB(0x534040);
}

// 0x534170
bool __cdecl TakeGuildCraftTask::InitializeForTry(::Zone *, ::Creature *, ::TakeGuildCraftTask::TakeGuildCraftType, unsigned __int64, int)
{
    LIFT_STUB(0x534170);
}

// 0x534250
bool __cdecl TakeGuildCraftTask::InitializeForOk(::Zone *, ::Creature *, ::TakeGuildCraftTask::TakeGuildCraftType, unsigned __int64, unsigned __int64)
{
    LIFT_STUB(0x534250);
}

// 0x534330
bool __cdecl TakeGuildCraftTask::InitializeForFail(::Zone *, ::Creature *, ::TakeGuildCraftTask::TakeGuildCraftType, ::PropertyTransactionFailParam *)
{
    LIFT_STUB(0x534330);
}

// 0x534460
void __cdecl TakeGuildCraftTask::start(void)
{
    LIFT_STUB(0x534460);
}

// 0x5349a0
void __cdecl TakeGuildCraftTask::TimerExpired(unsigned int, long)
{
    LIFT_STUB(0x5349a0);
}

// 0x5349e0
__cdecl DonateGuildUniformTask::DonateGuildUniformTask(void)
{
    LIFT_STUB(0x5349e0);
}

// 0x534ad0
bool __cdecl DonateGuildUniformTask::InitializeForTry(::Zone *, ::Creature *, unsigned __int64, short, short const *const, short const *const)
{
    LIFT_STUB(0x534ad0);
}

// 0x534c90
bool __cdecl DonateGuildUniformTask::InitializeForOk(::Zone *, ::Creature *, char, char const *const, short const *const)
{
    LIFT_STUB(0x534c90);
}

// 0x534de0
bool __cdecl DonateGuildUniformTask::InitializeForFail(::Zone *, ::Creature *, unsigned __int64, short, unsigned __int64 const *const, short const *const, char const *const)
{
    LIFT_STUB(0x534de0);
}

// 0x534f30
void __cdecl DonateGuildUniformTask::start(void)
{
    LIFT_STUB(0x534f30);
}

// 0x535570
bool __cdecl DonateGuildUniformTask::checkItemForDonation(void)
{
    LIFT_STUB(0x535570);
}

// 0x535860
bool __cdecl DonateGuildUniformTask::makeTransaction(::Pc *, unsigned __int64)
{
    LIFT_STUB(0x535860);
}

// 0x536050
void __cdecl DonateGuildUniformTask::TimerExpired(unsigned int, long)
{
    LIFT_STUB(0x536050);
}

// 0x536090
__cdecl IncreaseUniformRegistrationQuotaTask::IncreaseUniformRegistrationQuotaTask(void)
{
    LIFT_STUB(0x536090);
}

// 0x536180
bool __cdecl IncreaseUniformRegistrationQuotaTask::InitializeForTry(::Zone *, ::Creature *, char, short, short const *const, short const *const)
{
    LIFT_STUB(0x536180);
}

// 0x536330
bool __cdecl IncreaseUniformRegistrationQuotaTask::InitializeForOk(::Zone *, ::Creature *, char, char const *const, short const *const)
{
    LIFT_STUB(0x536330);
}

// 0x536480
bool __cdecl IncreaseUniformRegistrationQuotaTask::InitializeForFail(::Zone *, ::Creature *, short, unsigned __int64 const *const, short const *const, char const *const)
{
    LIFT_STUB(0x536480);
}

// 0x5365d0
void __cdecl IncreaseUniformRegistrationQuotaTask::start(void)
{
    LIFT_STUB(0x5365d0);
}

// 0x536ad0
bool __cdecl IncreaseUniformRegistrationQuotaTask::checkItemForPayment(void)
{
    LIFT_STUB(0x536ad0);
}

// 0x536db0
bool __cdecl IncreaseUniformRegistrationQuotaTask::makeTransaction(::Pc *, unsigned __int64, short)
{
    LIFT_STUB(0x536db0);
}

// 0x537510
void __cdecl IncreaseUniformRegistrationQuotaTask::TimerExpired(unsigned int, long)
{
    LIFT_STUB(0x537510);
}

// 0x537550
__cdecl DepositInGuildBankTaskEx::DepositInGuildBankTaskEx(void)
{
    LIFT_STUB(0x537550);
}

// 0x537630
bool __cdecl DepositInGuildBankTaskEx::InitializeTry(::Zone *, ::Creature *, int, short, short const *const, short const *const)
{
    LIFT_STUB(0x537630);
}

// 0x537820
bool __cdecl DepositInGuildBankTaskEx::InitializeOk(::Zone *, ::Creature *, short, char const *const, short const *const)
{
    LIFT_STUB(0x537820);
}

// 0x537930
bool __cdecl DepositInGuildBankTaskEx::InitializeFail(::Zone *, ::Creature *, unsigned __int64, int, short, unsigned __int64 const *const, short const *const, char const *const)
{
    LIFT_STUB(0x537930);
}

// 0x537ac0
short __cdecl DepositInGuildBankTaskEx::checkItemForDeposit(short, short const *const, short const *const, unsigned int &, short &, __int64 &, ::Item **const)
{
    LIFT_STUB(0x537ac0);
}

// 0x537e50
bool __cdecl DepositInGuildBankTaskEx::makeTransaction(::Pc *, unsigned __int64)
{
    LIFT_STUB(0x537e50);
}

// 0x5387b0
void __cdecl DepositInGuildBankTaskEx::depositInGuildBankReq(void)
{
    LIFT_STUB(0x5387b0);
}

// 0x538d60
void __cdecl DepositInGuildBankTaskEx::TimerExpired(unsigned int, long)
{
    LIFT_STUB(0x538d60);
}

// 0x538da0
void __cdecl DepositInGuildBankTaskEx::start(void)
{
    LIFT_STUB(0x538da0);
}

// 0x538fe0
__cdecl ContractGuildCraftTask::ContractGuildCraftTask(void)
{
    LIFT_STUB(0x538fe0);
}

// 0x5390f0
__cdecl ContractGuildCraftTask::~ContractGuildCraftTask(void)
{
    LIFT_STUB(0x5390f0);
}

// 0x539180
bool __cdecl ContractGuildCraftTask::Initialize(::Zone *, ::Pc *, ::ContractGuildCraftTask::Operation, ::ContractGuildCraftTran *, ::ContractGuildCraftTranStartParam *)
{
    LIFT_STUB(0x539180);
}

// 0x539220
bool __cdecl ContractGuildCraftTask::InitializeOk(::Zone *, ::Pc *, ::ContractGuildCraftTask::Operation, ::ContractGuildCraftTran *)
{
    LIFT_STUB(0x539220);
}

// 0x5392c0
bool __cdecl ContractGuildCraftTask::InitializeFail(::Zone *, ::Pc *, ::ContractGuildCraftTask::Operation, ::ContractGuildCraftTran *, ::ContractGuildCraftTranFailParam *)
{
    LIFT_STUB(0x5392c0);
}

// 0x5393f0
void __cdecl ContractGuildCraftTask::TimerExpired(unsigned int, long)
{
    LIFT_STUB(0x5393f0);
}

// 0x539430
void __cdecl ContractGuildCraftTask::start(void)
{
    LIFT_STUB(0x539430);
}

// 0x539590
short __cdecl ContractGuildCraftTask::contractGuildCraftReq(::Pc *)
{
    LIFT_STUB(0x539590);
}

// 0x53a2a0
void __cdecl AssentGuildCraftTask::TimerExpired(unsigned int, long)
{
    LIFT_STUB(0x53a2a0);
}

// 0x53a2e0
void __cdecl AssentGuildCraftTask::start(void)
{
    LIFT_STUB(0x53a2e0);
}

// 0x53a7d0
__cdecl RegisterGuildTask::RegisterGuildTask(void)
{
    LIFT_STUB(0x53a7d0);
}

// 0x53a880
bool __cdecl RegisterGuildTask::Initialize(::Zone *, ::Creature *, char, wchar_t *, __int64)
{
    LIFT_STUB(0x53a880);
}

// 0x53a9d0
void __cdecl RegisterGuildTask::start(void)
{
    LIFT_STUB(0x53a9d0);
}

// 0x53af70
__cdecl RenameGuildTask::RenameGuildTask(void)
{
    LIFT_STUB(0x53af70);
}

// 0x53b0e0
bool __cdecl RenameGuildTask::InitializeReqFromClient(::Zone *, ::Creature *, ::RenameGuildTask::TransactionStep, char, wchar_t *, short)
{
    LIFT_STUB(0x53b0e0);
}

// 0x53b290
bool __cdecl RenameGuildTask::InitializeOkFromLobby(::Zone *, ::Creature *, ::RenameGuildTask::TransactionStep, unsigned __int64, unsigned __int64, char, wchar_t *, short, ::RenameGuildTranPropertyTransactionParam &, unsigned __int64)
{
    LIFT_STUB(0x53b290);
}

// 0x53b4a0
bool __cdecl RenameGuildTask::InitializeOkFromCache(::Zone *, ::Creature *, ::RenameGuildTask::TransactionStep, unsigned __int64, unsigned __int64, char, wchar_t *, short, ::RenameGuildTranPropertyTransactionParam &, unsigned __int64, __int64)
{
    LIFT_STUB(0x53b4a0);
}

// 0x53b6d0
bool __cdecl RenameGuildTask::InitializeAbort(::Zone *, ::Creature *, ::RenameGuildTask::TransactionStep, unsigned __int64, unsigned __int64, char, wchar_t *, short, ::RenameGuildTranPropertyTransactionParam &, unsigned __int64, short)
{
    LIFT_STUB(0x53b6d0);
}

// 0x53b920
void __cdecl RenameGuildTask::start(void)
{
    LIFT_STUB(0x53b920);
}

// 0x53bb10
bool __cdecl RenameGuildTask::checkCostItem(void)
{
    LIFT_STUB(0x53bb10);
}
