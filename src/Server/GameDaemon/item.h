// item.h: item.cpp, item.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class AccessoryItem
{
public:
    virtual int __cdecl GetExp(void) const;  // 0x454330
    virtual void __cdecl Lock(void);  // 0x454370
    virtual void __cdecl SetLockExpirationTime(__int64);  // 0x4543b0
    virtual void __cdecl SetTimeLimitType(char);  // 0x454600
    virtual bool __cdecl Locked(void) const;  // 0x454950
    virtual __int64 __cdecl GetLockExpirationTime(void) const;  // 0x454960
    virtual void __cdecl R_SetEnchantPoint(short);  // 0x454980
    virtual void __cdecl R_SetEnchantConsecutiveTrial(char);  // 0x4549c0
    virtual void __cdecl R_SetEnchantCrack(char);  // 0x454a30
    virtual void __cdecl R_SetEnchantRestore(bool);  // 0x454aa0
    virtual void __cdecl SetCount(short);  // 0x454ad0
    virtual char __cdecl GetLevel(void) const;  // 0x454b30
    virtual void __cdecl Unlock(void);  // 0x454b40
    virtual char __cdecl GetTimeLimitType(void) const;  // 0x454b80
    virtual __int64 __cdecl GetTimeLimitExpirationTime(void) const;  // 0x454b90
    virtual void __cdecl SetTimeLimitExpirationTime(__int64);  // 0x454ba0
    virtual short __cdecl GetTransformFailureExp(void) const;  // 0x454bd0
    virtual short __cdecl R_GetEnchantPoint(void) const;  // 0x454be0
    virtual char __cdecl R_GetEnchantConsecutiveTrial(void) const;  // 0x454bf0
    virtual void __cdecl R_IncEnchantConsecutiveTrial(void);  // 0x454c00
    virtual char __cdecl R_GetEnchantCrack(void) const;  // 0x454c30
    virtual void __cdecl R_IncEnchantCrack(void);  // 0x454c40
    virtual bool __cdecl R_GetEnchantRestore(void) const;  // 0x454c70
    virtual void __cdecl HandleExp(int);  // 0x5564b0
    virtual bool __cdecl Initialize(::Pc *, ::Data::ItemRecordPtr);  // 0x557130
    virtual bool __cdecl Initialize(::Pc *, ::Data::ItemRecordPtr, int, char *const, int *const);  // 0x557470
    bool __cdecl CheckGuildUsed(void) const;  // 0x557560
    virtual void __cdecl BroadcastEquip(void) const;  // 0x5576c0
    virtual void __cdecl BroadcastUnequip(void) const;  // 0x557b60
private:
    virtual bool __cdecl checkToInvokeEffect(void) const;  // 0x557eb0
public:
    virtual __int64 __cdecl R_GetRandomEffectId(char) const;  // 0x557fe0
    virtual void __cdecl R_SetRandomEffectId(char, __int64);  // 0x558030
    virtual __int64 __cdecl R_GetRandomEffectGroupId(char) const;  // 0x558090
    virtual void __cdecl R_SetRandomEffectGroupId(char, __int64);  // 0x5580e0
    virtual void __cdecl R_InvokeRandomOptionEffect(void) const;  // 0x558140
    virtual void __cdecl InvokeEffect(void) const;  // 0x558280
    virtual void __cdecl HandleTransformFailureExp(short);  // 0x558440
    char __cdecl GetCustomDressValue(char) const;  // 0x558490
    void __cdecl SetCustomDressValue(char, short);  // 0x558580
    virtual void __cdecl SetSpiritDataId(int);  // 0x5586c0
    virtual void __cdecl HandleSkillBuildUpLevel(bool, bool) const;  // 0x5586f0
    virtual int __cdecl GetSpiritDataId(void) const;  // 0x55b120
    virtual void __cdecl GetSpiritAbility(char, char &, int &) const;  // 0x55b150
    virtual void __cdecl SetSpiritAbility(char, char, int);  // 0x55b1c0
};

class CostumeItem
{
public:
    virtual void __cdecl SetCount(short);  // 0x454630
    virtual short __cdecl R_GetEnchantPoint(void) const;  // 0x454690
    virtual void __cdecl R_SetEnchantPoint(short);  // 0x4546a0
    virtual bool __cdecl Initialize(::Pc *, ::Data::ItemRecordPtr);  // 0x556150
    bool __cdecl CheckGuildUsed(void) const;  // 0x556620
    char __cdecl GetCustomDressValue(char) const;  // 0x556780
    void __cdecl SetCustomDressValue(char, short);  // 0x5568f0
    virtual void __cdecl BroadcastEquip(void) const;  // 0x556a30
    virtual void __cdecl BroadcastUnequip(void) const;  // 0x556d30
private:
    virtual bool __cdecl checkToInvokeEffect(void) const;  // 0x556f10
public:
    virtual void __cdecl InvokeEffect(void) const;  // 0x556ff0
};

class GemItem
{
public:
    struct RandomStatGemInfo {};
    enum RandomStatSubIndex {};
public:
    virtual void __cdecl SetCount(short);  // 0x4548f0
    virtual short __cdecl R_GetEnchantPoint(void) const;  // 0x454970
    virtual char __cdecl R_GetEnchantConsecutiveTrial(void) const;  // 0x4549b0
    virtual void __cdecl R_IncEnchantConsecutiveTrial(void);  // 0x4549f0
    virtual char __cdecl R_GetEnchantCrack(void) const;  // 0x454a20
    virtual void __cdecl R_IncEnchantCrack(void);  // 0x454a60
    virtual bool __cdecl R_GetEnchantRestore(void) const;  // 0x454a90
    virtual bool __cdecl Initialize(::Pc *, ::Data::ItemRecordPtr);  // 0x558700
    virtual void __cdecl BroadcastEquip(void) const;  // 0x558a40
    virtual void __cdecl BroadcastUnequip(void) const;  // 0x558a70
    virtual bool __cdecl R_CheckEnchantTargetItem(void);  // 0x558aa0
    virtual __int64 __cdecl R_GetRandomEffectId(char) const;  // 0x558b50
    virtual __int64 __cdecl R_GetRandomEffectGroupId(char) const;  // 0x558ba0
    virtual void __cdecl R_InvokeRandomOptionEffect(void) const;  // 0x558bf0
private:
    virtual bool __cdecl checkToInvokeEffect(void) const;  // 0x558d30
public:
    static bool __cdecl FindRandomStatSubAbility(::Data::ItemRecordGemPtr &, char, ::Data::ItemRandomAbilitySlotRecordPtr *);  // 0x558e30
    virtual void __cdecl InvokeEffect(void) const;  // 0x558f50
    bool __cdecl DetermineRandomStatEquipGem(::Data::ItemRecordGemPtr &);  // 0x559460
    bool __cdecl DetermineFeedGem(::Data::ItemRecordGemPtr &);  // 0x559820
    bool __cdecl SetRandomStatMainAbility(char, int, ::Data::ItemRandomAbilitySlotRecordPtr const &);  // 0x559bc0
    bool __cdecl SetRandomStatSubAbility(::GemItem::RandomStatSubIndex, char, int, ::Data::ItemRandomAbilitySlotRecordPtr const &);  // 0x559e50
    bool __cdecl GetRandomStatMainAbility(char &, int &, int &, ::Data::ItemRandomAbilitySlotRecordPtr *) const;  // 0x55a1a0
    bool __cdecl GetRandomStatSubAbility(::GemItem::RandomStatSubIndex, char &, int &, int &, ::Data::ItemRandomAbilitySlotRecordPtr *) const;  // 0x55a310
    void __cdecl GetRandomStatGemInfoForGameLog(::GemItem::RandomStatGemInfo &) const;  // 0x55a560
private:
    bool __cdecl FeedRandomStat(bool, ::GemItem::RandomStatSubIndex, bool, unsigned __int64, int &, int &, int &, int &);  // 0x55a6f0
};

class GroceryItem
{
public:
    virtual bool __cdecl Initialize(::Pc *, ::Data::ItemRecordPtr);  // 0x4546d0
    virtual void __cdecl HandleExp(int);  // 0x4547c0
    virtual short __cdecl GetCount(void) const;  // 0x454810
    virtual void __cdecl SetCount(short);  // 0x454820
    virtual short __cdecl R_GetEnchantPoint(void) const;  // 0x4548b0
    virtual void __cdecl R_SetEnchantPoint(short);  // 0x4548c0
    virtual void __cdecl HandleSkillBuildUpLevel(bool, bool) const;  // 0x55b250
    virtual void __cdecl BroadcastEquip(void) const;  // 0x55b2b0
    virtual void __cdecl BroadcastUnequip(void) const;  // 0x55b3a0
    virtual void __cdecl ActivateAbility(void) const;  // 0x55b490
    virtual void __cdecl DeactivateAbility(void) const;  // 0x55b570
    bool __cdecl CheckUsableZone(void) const;  // 0x55b640
};

class Item
{
public:
    virtual __cdecl ~Item(void);  // 0x454290

    // PDB data members (size 0x28). LIFT: the virtual slot order is not the PDB order yet.
    unsigned __int64 GetDbId(void) const { return dbid; }  // PDB inline (no RVA)
protected:
    ::Pc* _owner;                // +0x08
    unsigned __int64 dbid;       // +0x10
    bool _reserved;              // +0x18
    __int64 _insertReqTick;      // +0x20
public:
    static short __cdecl FetchDbFromXmlData(int, char, wchar_t const *, char *, short, ::EconomyItemCategory *);  // 0x54f400
    virtual char __cdecl GetSetItemCount(void);  // 0x54f780
    void __cdecl DetachEffect(void);  // 0x54f7b0
    bool __cdecl CheckTrade(bool) const;  // 0x54f840
    bool __cdecl CheckRegisterSale(void) const;  // 0x54f940
    bool __cdecl CheckRuleDispose(void) const;  // 0x54fa40
    bool __cdecl CheckSell(void) const;  // 0x54faa0
    bool __cdecl CheckOldItemSell(void) const;  // 0x54fb10
    bool __cdecl CheckMaxDurability(void) const;  // 0x54fbb0
    bool __cdecl CheckWardrobeStoreable(void) const;  // 0x54fbf0
    bool __cdecl CheckWarehouseStoreable(void) const;  // 0x54fc90
    bool __cdecl CheckBadgeDepositoryStoreable(void) const;  // 0x54fce0
    bool __cdecl ConsumeDurability(int);  // 0x54fd40
protected:
    bool __cdecl checkAvailableItemInPcCafe(void) const;  // 0x54fe90
    bool __cdecl checkEquipLevel(void) const;  // 0x54fed0
    void __cdecl calculateExpirationTime(::Data::ItemRecordPtr, __int64 &);  // 0x54ff20
    void __cdecl handleSkillBuildUpLevel(bool, bool) const;  // 0x54ffc0
public:
    bool __cdecl CheckDuelGrade(void) const;  // 0x5500c0
    bool __cdecl CheckTimeLimitItem(void) const;  // 0x5501f0
    bool __cdecl IsExpired(__int64) const;  // 0x550230
    __int64 __cdecl CalculateRemainingTime(::Data::ItemRecordPtr, __int64) const;  // 0x550280
    bool __cdecl CheckStackable(::Data::ItemRecordGroceryPtr, short) const;  // 0x5502d0
    bool __cdecl IsEquipJobNone(void) const;  // 0x5503c0
    bool __cdecl CheckDepositInGuildBank(void) const;  // 0x550430
    bool __cdecl CheckAccountPostCharge(void) const;  // 0x550520
protected:
    static void __cdecl InvokeEffect(::Data::ItemRecordPtr, ::ControlledCreature *, short);  // 0x5505b0
    static void __cdecl CalcItemAbility(::Data::ItemRecordPtr, ::Data::EffectRecordItemAbility &);  // 0x5506b0
public:
    static void __cdecl CalcItemAbilityDetach(::Data::ItemRecordPtr, ::Data::EffectRecordItemAbility &);  // 0x550c70
    static char __cdecl CalcLevel(char, int, int &);  // 0x551230
    static unsigned __int64 __cdecl GetUsedGuildIdForGameLog(::Item const *);  // 0x551380
    static bool __cdecl MakeCustomParameterLog(wchar_t *, int, char *const, int);  // 0x5513d0
    static bool __cdecl GetSpiritStatusForGameLog(::Pc const *, ::Item const *, char, char *const, int *const, int *);  // 0x551530
    ::R_EnchantToItemResult __cdecl R_HandleEnchant(short, bool, bool);  // 0x551600
    ::R_RestoreEnchantFailedItemResult __cdecl R_HandleRestoreEnchantItem(int);  // 0x551a60
    char __cdecl R_HandleEnchantPoint(short);  // 0x551bf0
    void __cdecl R_EnchantFailDestroy(void);  // 0x551dd0
    void __cdecl R_ResetEnchant(void);  // 0x551e90
    char __cdecl R_ResetRandomOption(::Data::ItemRecordPtr, ::R_PolishToItemReason, bool const *);  // 0x551ed0
    char __cdecl R_GetOpenRandomOptionSlotCount(::Data::ItemRecordPtr) const;  // 0x552720
};

class AccessoryTrait;
class GemTrait;
class GroceryTrait;
class WeaponTrait;

// LIFT: view of the PDB group AccessoryProperty::__default__ at AccessoryProperty+48.
// The base Property (+0 to +47) is not declared yet.
struct ItemBaseAccessoryPropertyView
{
    char lift_pad_0[0x30];  // ❓ no PDB name: base Property (+0 to +0x2F) is not declared yet
    struct
    {
        char depot;  // +0
        short pos;  // +2
        int data_id;  // +4
        char level;  // +8
        int exp;  // +12
        unsigned char used : 1;  // +16 bit 0
        unsigned char sequestration : 1;  // +16 bit 1
        unsigned char locked : 1;  // +16 bit 2
    } Default;  // +48
};

// LIFT: class template ItemBase<Trait> (PDB, base Item, size 0x110 for AccessoryTrait).
// Only the members of the lifted bodies are declared. The Item members (+8 to +39) are in class Item.
// LIFT: the PDB member prop has the type <Trait>Property. Only the AccessoryProperty layout is declared.
template <class Trait>
class ItemBase : public ::Item  // LIFT: the Item members (+8 to +0x27) are declared in Item (card e17)
{
public:
    virtual int __cdecl GetDataId(void) const;
    virtual char __cdecl GetClass(void) const;
    virtual short __cdecl GetFieldCount(void) const;
    virtual unsigned char __cdecl GetDepot(void) const;
    virtual unsigned short __cdecl GetPos(void) const;
    virtual bool __cdecl GetSequestration(void) const;
protected:
    void *data;  // +40 (PDB: Data::ItemRecord<Trait>Ptr)
    ::ItemBaseAccessoryPropertyView prop;  // +48 (PDB: <Trait>Property)
};

class ItemFactory
{
public:
    static ::Item * __cdecl CreateItem(::ItemClass);  // 0x54ee80
    static ::Item * __cdecl CreateItem(::Pc *, ::Data::ItemRecordPtr);  // 0x54f120
};

class ItemXmlHelper
{
public:
    struct XmlAttr {};
public:
    static bool __cdecl Parse(wchar_t const *, wchar_t *, int &, ::ItemXmlHelper::XmlAttr *, int &);  // 0x453ef0
};

class TimeLimitItemPriorityQueue
{
public:
    __cdecl ~TimeLimitItemPriorityQueue(void);  // 0x55b7e0
    bool __cdecl Push(::TimeLimitItem *);  // 0x55b840
    void __cdecl Clear(void);  // 0x55b960
};

// LIFT: view of the PDB WeaponProperty (size 0x110). Only the group Remaster (+0xB8) is declared.
struct WeaponItemPropertyView
{
    char lift_pad_0[0xB8];  // ❓ no PDB name: base Property and the groups Default, Gem, EnchantGem are not declared yet
    struct
    {
        short enchant_point;  // +0
        char enchant_consecutive_trial;  // +2
        char enchant_crack;  // +3
        char enchant_restore;  // +4
        __int64 random_effect_group_id_1;  // +8
        __int64 random_effect_group_id_2;  // +16
        __int64 random_effect_group_id_3;  // +24
        __int64 random_effect_group_id_4;  // +32
        __int64 random_effect_group_id_5;  // +40
        __int64 random_effect_id_1;  // +48
        __int64 random_effect_id_2;  // +56
        __int64 random_effect_id_3;  // +64
        __int64 random_effect_id_4;  // +72
        __int64 random_effect_id_5;  // +80
    } Remaster;  // +0xB8 (PDB: WeaponProperty::__remaster__)
};

// LIFT: view of a PDB WeaponItem object. Only the member ItemBase<WeaponTrait>::prop (+0x30) is declared.
struct WeaponItemView
{
    char lift_pad_0[0x30];  // ❓ no PDB name: vfptr, Item members (+8 to +0x27) and ItemBase::data (+0x28)
    ::WeaponItemPropertyView prop;  // +0x30 (PDB: WeaponProperty)
};

// LIFT: the group Remaster of AccessoryProperty and GemProperty has the same fields as the WeaponProperty group.
struct ItemRemasterPropertyView
{
    short enchant_point;  // +0
    char enchant_consecutive_trial;  // +2
    char enchant_crack;  // +3
    char enchant_restore;  // +4
    __int64 random_effect_group_id_1;  // +8
    __int64 random_effect_group_id_2;  // +16
    __int64 random_effect_group_id_3;  // +24
    __int64 random_effect_group_id_4;  // +32
    __int64 random_effect_group_id_5;  // +40
    __int64 random_effect_id_1;  // +48
    __int64 random_effect_id_2;  // +56
    __int64 random_effect_id_3;  // +64
    __int64 random_effect_id_4;  // +72
    __int64 random_effect_id_5;  // +80
};

// LIFT: view of the PDB AccessoryProperty (size 0xE0). Only the group Remaster (+0x88) is declared.
struct AccessoryItemPropertyView
{
    char lift_pad_0[0x88];  // ❓ no PDB name: base Property and the group Default are not declared here
    ::ItemRemasterPropertyView Remaster;  // +0x88 (PDB: AccessoryProperty::__remaster__)
};

// LIFT: view of a PDB AccessoryItem object. Only the member ItemBase<AccessoryTrait>::prop (+0x30) is declared.
struct AccessoryItemView
{
    char lift_pad_0[0x30];  // ❓ no PDB name: vfptr, Item members (+8 to +0x27) and ItemBase::data (+0x28)
    ::AccessoryItemPropertyView prop;  // +0x30 (PDB: AccessoryProperty)
};

// LIFT: view of the PDB GemProperty (size 0xD8). Only the group Remaster (+0x80) is declared.
struct GemItemPropertyView
{
    char lift_pad_0[0x80];  // ❓ no PDB name: base Property and the group Default are not declared here
    ::ItemRemasterPropertyView Remaster;  // +0x80 (PDB: GemProperty::__remaster__)
};

// LIFT: view of a PDB GemItem object. Only the member ItemBase<GemTrait>::prop (+0x30) is declared.
struct GemItemView
{
    char lift_pad_0[0x30];  // ❓ no PDB name: vfptr, Item members (+8 to +0x27) and ItemBase::data (+0x28)
    ::GemItemPropertyView prop;  // +0x30 (PDB: GemProperty)
};

// LIFT: PDB class WeaponItem derives from ItemBase<WeaponTrait>. The base is not declared here yet.
class WeaponItem
{
public:
    virtual void __cdecl SetCount(short);  // 0x4542d0
    virtual short __cdecl GetMaxDurability(void) const;  // 0x454340
    virtual short __cdecl GetDurability(void) const;  // 0x454350
    virtual int __cdecl GetAppearanceItemDataId(void) const;  // 0x4543e0
    virtual void __cdecl SetAppearanceItemDataId(int);  // 0x4543f0
    virtual char __cdecl GetAppearanceItemLevel(void) const;  // 0x454420
    virtual void __cdecl SetAppearanceItemLevel(char);  // 0x454430
    virtual bool __cdecl IsAppearanceApplied(void) const;  // 0x454460
    virtual void __cdecl R_SetEnchantPoint(short);  // 0x4544a0
    virtual char __cdecl R_GetEnchantConsecutiveTrial(void) const;  // 0x4544d0
    virtual void __cdecl R_SetEnchantConsecutiveTrial(char);  // 0x4544e0
    virtual void __cdecl R_IncEnchantConsecutiveTrial(void);  // 0x454510
    virtual char __cdecl R_GetEnchantCrack(void) const;  // 0x454540
    virtual void __cdecl R_SetEnchantCrack(char);  // 0x454550
    virtual void __cdecl R_IncEnchantCrack(void);  // 0x454580
    virtual bool __cdecl R_GetEnchantRestore(void) const;  // 0x4545b0
    virtual void __cdecl R_SetEnchantRestore(bool);  // 0x4545c0
    virtual short __cdecl GetTransformFailureExp(void) const;  // 0x4545f0
    virtual bool __cdecl Initialize(::Pc *, ::Data::ItemRecordPtr);  // 0x552800
    virtual bool __cdecl Initialize(::Pc *, ::Data::ItemRecordPtr, bool, unsigned int *const, bool, unsigned int, char, bool, int, char *const, int *const);  // 0x552c80
    virtual bool __cdecl Initialize(::Pc *, ::Data::ItemRecordPtr, int, char *const, int *const);  // 0x552e00
    static bool __cdecl InitializeProperty(::Data::ItemRecordPtr, ::WeaponProperty &);  // 0x552ef0
    virtual char __cdecl GetSetItemCount(void);  // 0x5532c0
    virtual void __cdecl SetDurability(short);  // 0x5533e0
    virtual bool __cdecl Identified(void) const;  // 0x553490
    virtual void __cdecl HandleSkillBuildUpLevel(bool, bool) const;  // 0x5534e0
    virtual bool __cdecl R_CheckEnchantTargetItem(void);  // 0x553530
    virtual __int64 __cdecl R_GetRandomEffectId(char) const;  // 0x5535f0
    virtual void __cdecl R_SetRandomEffectId(char, __int64);  // 0x553640
    virtual __int64 __cdecl R_GetRandomEffectGroupId(char) const;  // 0x5536a0
    virtual void __cdecl R_SetRandomEffectGroupId(char, __int64);  // 0x5536f0
    virtual void __cdecl R_InvokeRandomOptionEffect(void) const;  // 0x553750
    virtual void __cdecl BroadcastEquip(void) const;  // 0x553890
    virtual void __cdecl BroadcastUnequip(void) const;  // 0x553ee0
private:
    virtual bool __cdecl checkToInvokeEffect(void) const;  // 0x554330
public:
    virtual void __cdecl InvokeEffect(void) const;  // 0x554450
    unsigned int __cdecl GetGem(int) const;  // 0x554a80
    void __cdecl AttachGem(int, unsigned int);  // 0x554af0
    void __cdecl DetachGem(int, unsigned int);  // 0x554bc0
    void __cdecl AddGemSlot(int, unsigned int);  // 0x554c90
    void __cdecl DeleteGemSlot(int);  // 0x554d40
    bool __cdecl GetEnchantGemData(int, ::Data::ItemRecordGemPtr *) const;  // 0x554df0
    bool __cdecl GetEnchantGemSkill(int, unsigned __int64 *const) const;  // 0x554fa0
    void __cdecl AttachEnchantGem(int, int, char, int);  // 0x555160
    void __cdecl DetachEnchantGem(int);  // 0x5552a0
    void __cdecl Identify(void);  // 0x5553c0
private:
    void __cdecl InitializeGemSlot(::Data::ItemRecordWeaponPtr);  // 0x5555b0
    bool __cdecl invokeAttackEffect(::Creature *, ::Creature *, ::SkillResult, bool, unsigned __int64 *, char, char, char, char, short *, short, short *, short) const;  // 0x555a70
public:
    void __cdecl InvokeWeaponGemEffect(::Creature *, ::Creature *, ::SkillResult, bool) const;  // 0x555c20
    void __cdecl GetGemInfoString(wchar_t *, unsigned __int64) const;  // 0x555e50
    virtual void __cdecl HandleTransformFailureExp(short);  // 0x555fa0
    virtual int __cdecl GetSpiritDataId(void) const;  // 0x555ff0
    virtual void __cdecl SetSpiritDataId(int);  // 0x556020
    virtual void __cdecl GetSpiritAbility(char, char &, int &) const;  // 0x556050
    virtual void __cdecl SetSpiritAbility(char, char, int);  // 0x5560c0
};

