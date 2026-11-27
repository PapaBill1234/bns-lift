// item_h_1.cpp: item.h part 1 (GameDaemon PDB, 2019 + PDB).
#include "item.h"
#include "pc.h"
#include "LiftStub.h"
// LIFT: the BloodLib headers come last. Their Windows macros must not rename the GameDaemon declarations.
#include "AlertSender.h"
#include "Log.h"

// 0x453ef0
bool __cdecl ItemXmlHelper::Parse(wchar_t const *, wchar_t *, int &, ::ItemXmlHelper::XmlAttr *, int &)
{
    LIFT_STUB(0x453ef0);
}

// 0x454250
// LIFT: a static function (no public name), so no /INCLUDE pragma. The caller keeps it when it is lifted.
static EconomyItemCategory GetEconomyCommonItemCategory(char itemClass)
{
    switch (itemClass)
    {
    case ITEMCLASS_WEAPON:
        return ECONOMY_ITEMCATEGORY_WEAPON;
    case ITEMCLASS_COSTUME:
        return ECONOMY_ITEMCATEGORY_COSTUME;
    case ITEMCLASS_GROCERY:
        return ECONOMY_ITEMCATEGORY_GROCERY;
    case ITEMCLASS_GEM:
        return ECONOMY_ITEMCATEGORY_GEM;
    case ITEMCLASS_ACCESSORY:
        return ECONOMY_ITEMCATEGORY_ACCESSORY;
    default:
        return ECONOMY_ITEMCATEGORY_INVALID_CATEGORY;
    }
}

// 0x454290
__cdecl Item::~Item(void)
{
    LIFT_STUB(0x454290);
}

// 0x4542d0
void __cdecl WeaponItem::SetCount(short count)
{
    if (count != 1)
    {
        Log::Write(Log::LT_ERROR, L"e:\\dailybuild02\\gamedaemon-common-0.0.348\\depot\\branch\\348nc\\program\\server\\gamedaemon\\Item.h", 1447,
                   L"== CRASH == [weapon-item], set count failed; count is not 1, count:%d", count);
        AlertSender::Write(L"e:\\dailybuild02\\gamedaemon-common-0.0.348\\depot\\branch\\348nc\\program\\server\\gamedaemon\\Item.h", 1447,
                           L"== CRASH == [weapon-item], set count failed; count is not 1, count:%d", count);
    }
}

// 0x454330
int __cdecl AccessoryItem::GetExp(void) const
{
    LIFT_STUB(0x454330);
}

// 0x454340
short __cdecl WeaponItem::GetMaxDurability(void) const
{
    LIFT_STUB(0x454340);
}

// 0x454350
short __cdecl WeaponItem::GetDurability(void) const
{
    LIFT_STUB(0x454350);
}

// 0x454360 ItemBase<GroceryTrait>::GetSequestration: LIFT: no body in wave 0 (member of a class template).

// 0x454370
void __cdecl AccessoryItem::Lock(void)
{
    LIFT_STUB(0x454370);
}

// 0x4543b0
void __cdecl AccessoryItem::SetLockExpirationTime(__int64)
{
    LIFT_STUB(0x4543b0);
}

// 0x4543e0
int __cdecl WeaponItem::GetAppearanceItemDataId(void) const
{
    LIFT_STUB(0x4543e0);
}

// 0x4543f0
void __cdecl WeaponItem::SetAppearanceItemDataId(int)
{
    LIFT_STUB(0x4543f0);
}

// 0x454420
char __cdecl WeaponItem::GetAppearanceItemLevel(void) const
{
    LIFT_STUB(0x454420);
}

// 0x454430
void __cdecl WeaponItem::SetAppearanceItemLevel(char)
{
    LIFT_STUB(0x454430);
}

// 0x454460
bool __cdecl WeaponItem::IsAppearanceApplied(void) const
{
    LIFT_STUB(0x454460);
}

// 0x4544a0
void __cdecl WeaponItem::R_SetEnchantPoint(short)
{
    LIFT_STUB(0x4544a0);
}

// 0x4544d0
char __cdecl WeaponItem::R_GetEnchantConsecutiveTrial(void) const
{
    LIFT_STUB(0x4544d0);
}

// 0x4544e0
void __cdecl WeaponItem::R_SetEnchantConsecutiveTrial(char)
{
    LIFT_STUB(0x4544e0);
}

// 0x454510
void __cdecl WeaponItem::R_IncEnchantConsecutiveTrial(void)
{
    LIFT_STUB(0x454510);
}

// 0x454540
char __cdecl WeaponItem::R_GetEnchantCrack(void) const
{
    LIFT_STUB(0x454540);
}

// 0x454550
void __cdecl WeaponItem::R_SetEnchantCrack(char)
{
    LIFT_STUB(0x454550);
}

// 0x454580
void __cdecl WeaponItem::R_IncEnchantCrack(void)
{
    LIFT_STUB(0x454580);
}

// 0x4545b0
bool __cdecl WeaponItem::R_GetEnchantRestore(void) const
{
    LIFT_STUB(0x4545b0);
}

// 0x4545c0
void __cdecl WeaponItem::R_SetEnchantRestore(bool)
{
    LIFT_STUB(0x4545c0);
}

// 0x4545f0
short __cdecl WeaponItem::GetTransformFailureExp(void) const
{
    LIFT_STUB(0x4545f0);
}

// 0x454600
void __cdecl AccessoryItem::SetTimeLimitType(char)
{
    LIFT_STUB(0x454600);
}

// 0x454630
void __cdecl CostumeItem::SetCount(short count)
{
    if (count != 1)
    {
        Log::Write(Log::LT_ERROR, L"e:\\dailybuild02\\gamedaemon-common-0.0.348\\depot\\branch\\348nc\\program\\server\\gamedaemon\\Item.h", 1586,
                   L"== CRASH == [costume-item], set count failed; count is not 1, count:%d", count);
        AlertSender::Write(L"e:\\dailybuild02\\gamedaemon-common-0.0.348\\depot\\branch\\348nc\\program\\server\\gamedaemon\\Item.h", 1586,
                           L"== CRASH == [costume-item], set count failed; count is not 1, count:%d", count);
    }
}

// 0x454690
short __cdecl CostumeItem::R_GetEnchantPoint(void) const
{
    LIFT_STUB(0x454690);
}

// 0x4546a0
void __cdecl CostumeItem::R_SetEnchantPoint(short)
{
    LIFT_STUB(0x4546a0);
}

// 0x4546d0
bool __cdecl GroceryItem::Initialize(::Pc *, ::Data::ItemRecordPtr)
{
    LIFT_STUB(0x4546d0);
}

// 0x4547c0
void __cdecl GroceryItem::HandleExp(int)
{
    LIFT_STUB(0x4547c0);
}

// 0x454810
short __cdecl GroceryItem::GetCount(void) const
{
    LIFT_STUB(0x454810);
}

// 0x454820
void __cdecl GroceryItem::SetCount(short)
{
    LIFT_STUB(0x454820);
}

// 0x4548b0
short __cdecl GroceryItem::R_GetEnchantPoint(void) const
{
    LIFT_STUB(0x4548b0);
}

// 0x4548c0
void __cdecl GroceryItem::R_SetEnchantPoint(short)
{
    LIFT_STUB(0x4548c0);
}

// 0x4548f0
void __cdecl GemItem::SetCount(short count)
{
    if (count != 1)
    {
        Log::Write(Log::LT_ERROR, L"e:\\dailybuild02\\gamedaemon-common-0.0.348\\depot\\branch\\348nc\\program\\server\\gamedaemon\\Item.h", 1765,
                   L"== CRASH == [gem-item], set count failed; count is not 1, count:%d", count);
        AlertSender::Write(L"e:\\dailybuild02\\gamedaemon-common-0.0.348\\depot\\branch\\348nc\\program\\server\\gamedaemon\\Item.h", 1765,
                           L"== CRASH == [gem-item], set count failed; count is not 1, count:%d", count);
    }
}

// 0x454950
bool __cdecl AccessoryItem::Locked(void) const
{
    LIFT_STUB(0x454950);
}

// 0x454960
__int64 __cdecl AccessoryItem::GetLockExpirationTime(void) const
{
    LIFT_STUB(0x454960);
}

// 0x454970
short __cdecl GemItem::R_GetEnchantPoint(void) const
{
    LIFT_STUB(0x454970);
}

// 0x454980
void __cdecl AccessoryItem::R_SetEnchantPoint(short)
{
    LIFT_STUB(0x454980);
}

// 0x4549b0
char __cdecl GemItem::R_GetEnchantConsecutiveTrial(void) const
{
    LIFT_STUB(0x4549b0);
}

// 0x4549c0
void __cdecl AccessoryItem::R_SetEnchantConsecutiveTrial(char)
{
    LIFT_STUB(0x4549c0);
}

// 0x4549f0
void __cdecl GemItem::R_IncEnchantConsecutiveTrial(void)
{
    LIFT_STUB(0x4549f0);
}

// 0x454a20
char __cdecl GemItem::R_GetEnchantCrack(void) const
{
    LIFT_STUB(0x454a20);
}

// 0x454a30
void __cdecl AccessoryItem::R_SetEnchantCrack(char)
{
    LIFT_STUB(0x454a30);
}

// 0x454a60
void __cdecl GemItem::R_IncEnchantCrack(void)
{
    LIFT_STUB(0x454a60);
}

// 0x454a90
bool __cdecl GemItem::R_GetEnchantRestore(void) const
{
    LIFT_STUB(0x454a90);
}

// 0x454aa0
void __cdecl AccessoryItem::R_SetEnchantRestore(bool)
{
    LIFT_STUB(0x454aa0);
}

// 0x454ad0
void __cdecl AccessoryItem::SetCount(short count)
{
    if (count != 1)
    {
        Log::Write(Log::LT_ERROR, L"e:\\dailybuild02\\gamedaemon-common-0.0.348\\depot\\branch\\348nc\\program\\server\\gamedaemon\\Item.h", 1886,
                   L"== CRASH == [accessory-item], set count failed; count is not 1, count:%d", count);
        AlertSender::Write(L"e:\\dailybuild02\\gamedaemon-common-0.0.348\\depot\\branch\\348nc\\program\\server\\gamedaemon\\Item.h", 1886,
                           L"== CRASH == [accessory-item], set count failed; count is not 1, count:%d", count);
    }
}

// 0x454b30
char __cdecl AccessoryItem::GetLevel(void) const
{
    LIFT_STUB(0x454b30);
}

// 0x454b40
void __cdecl AccessoryItem::Unlock(void)
{
    LIFT_STUB(0x454b40);
}

// 0x454b80
char __cdecl AccessoryItem::GetTimeLimitType(void) const
{
    LIFT_STUB(0x454b80);
}

// 0x454b90
__int64 __cdecl AccessoryItem::GetTimeLimitExpirationTime(void) const
{
    LIFT_STUB(0x454b90);
}

// 0x454ba0
void __cdecl AccessoryItem::SetTimeLimitExpirationTime(__int64)
{
    LIFT_STUB(0x454ba0);
}

// 0x454bd0
short __cdecl AccessoryItem::GetTransformFailureExp(void) const
{
    LIFT_STUB(0x454bd0);
}

// 0x454be0
short __cdecl AccessoryItem::R_GetEnchantPoint(void) const
{
    LIFT_STUB(0x454be0);
}

// 0x454bf0
char __cdecl AccessoryItem::R_GetEnchantConsecutiveTrial(void) const
{
    LIFT_STUB(0x454bf0);
}

// 0x454c00
void __cdecl AccessoryItem::R_IncEnchantConsecutiveTrial(void)
{
    LIFT_STUB(0x454c00);
}

// 0x454c30
char __cdecl AccessoryItem::R_GetEnchantCrack(void) const
{
    LIFT_STUB(0x454c30);
}

// 0x454c40
void __cdecl AccessoryItem::R_IncEnchantCrack(void)
{
    LIFT_STUB(0x454c40);
}

// 0x454c70
bool __cdecl AccessoryItem::R_GetEnchantRestore(void) const
{
    LIFT_STUB(0x454c70);
}

// 0x667210 ItemBase<WeaponTrait>::ItemBase<WeaponTrait>: LIFT: no body in wave 0 (member of a class template).

// 0x667290 ItemBase<WeaponTrait>::Initialize: LIFT: no body in wave 0 (member of a class template).

// 0x6673b0 ItemBase<WeaponTrait>::Initialize: LIFT: no body in wave 0 (member of a class template).

// 0x6674e0 ItemBase<WeaponTrait>::Initialize: LIFT: no body in wave 0 (member of a class template).

// 0x6675f0 ItemBase<WeaponTrait>::Clone: LIFT: no body in wave 0 (member of a class template).

// 0x667780 ItemBase<WeaponTrait>::RefreshSyncBuffer: LIFT: no body in wave 0 (member of a class template).

// 0x6678b0 ItemBase<WeaponTrait>::FetchBroadcast: LIFT: no body in wave 0 (member of a class template).

// 0x667940 ItemBase<WeaponTrait>::FetchBroadcastNull: LIFT: no body in wave 0 (member of a class template).

// 0x6679d0 ItemBase<WeaponTrait>::FetchDBData: LIFT: no body in wave 0 (member of a class template).

// 0x667c90 ItemBase<WeaponTrait>::FetchXmlData: LIFT: no body in wave 0 (member of a class template).
