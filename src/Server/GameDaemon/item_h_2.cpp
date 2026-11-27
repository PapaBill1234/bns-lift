// item_h_2.cpp: item.h part 2 (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "item.h"
#include "LiftStub.h"

#pragma comment(linker, "/INCLUDE:?GetFieldCount@?$ItemBase@VWeaponTrait@@@@UEBAFXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetPos@?$ItemBase@VAccessoryTrait@@@@UEBAGXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetClass@?$ItemBase@VGroceryTrait@@@@UEBADXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetDepot@?$ItemBase@VAccessoryTrait@@@@UEBAEXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetClass@?$ItemBase@VGemTrait@@@@UEBADXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetDataId@?$ItemBase@VAccessoryTrait@@@@UEBAHXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetClass@?$ItemBase@VAccessoryTrait@@@@UEBADXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetSequestration@?$ItemBase@VAccessoryTrait@@@@UEBA_NXZ")  // LIFT: dead-strip keep (no live caller yet)

// 0x667eb0 ItemBase<WeaponTrait>::FetchOpXmlData: LIFT: no body in wave 0 (member of a class template).

// 0x668200 ItemBase<WeaponTrait>::FetchOpDBData: LIFT: no body in wave 0 (member of a class template).

// 0x668830
template <>
short __cdecl ItemBase< ::WeaponTrait>::GetFieldCount(void) const
{
    return 48;  // ❓ the source can use WeaponProperty::FIELD_COUNT. The PDB gives no value for it.
}

// 0x668840 ItemBase<AccessoryTrait>::SetLevel: LIFT: no body in wave 0 (member of a class template).

// 0x668870
template <>
unsigned short __cdecl ItemBase< ::AccessoryTrait>::GetPos(void) const
{
    return prop.Default.pos;
}

// 0x668880 ItemBase<AccessoryTrait>::SetDepot: LIFT: no body in wave 0 (member of a class template).

// 0x6688b0 ItemBase<WeaponTrait>::InitPropertyByXml: LIFT: no body in wave 0 (member of a class template).

// 0x668b80 ItemBase<CostumeTrait>::ItemBase<CostumeTrait>: LIFT: no body in wave 0 (member of a class template).

// 0x668c00 ItemBase<CostumeTrait>::Initialize: LIFT: no body in wave 0 (member of a class template).

// 0x668d20 ItemBase<CostumeTrait>::Initialize: LIFT: no body in wave 0 (member of a class template).

// 0x668e50 ItemBase<CostumeTrait>::Initialize: LIFT: no body in wave 0 (member of a class template).

// 0x668f60 ItemBase<CostumeTrait>::Clone: LIFT: no body in wave 0 (member of a class template).

// 0x6690f0 ItemBase<CostumeTrait>::RefreshSyncBuffer: LIFT: no body in wave 0 (member of a class template).

// 0x669220 ItemBase<CostumeTrait>::FetchBroadcast: LIFT: no body in wave 0 (member of a class template).

// 0x6692b0 ItemBase<CostumeTrait>::FetchBroadcastNull: LIFT: no body in wave 0 (member of a class template).

// 0x669340 ItemBase<CostumeTrait>::FetchDBData: LIFT: no body in wave 0 (member of a class template).

// 0x669600 ItemBase<CostumeTrait>::FetchXmlData: LIFT: no body in wave 0 (member of a class template).

// 0x669820 ItemBase<CostumeTrait>::FetchOpXmlData: LIFT: no body in wave 0 (member of a class template).

// 0x669b70 ItemBase<CostumeTrait>::FetchOpDBData: LIFT: no body in wave 0 (member of a class template).

// 0x66a1b0 ItemBase<CostumeTrait>::InitPropertyByXml: LIFT: no body in wave 0 (member of a class template).

// 0x66a480 ItemBase<GroceryTrait>::ItemBase<GroceryTrait>: LIFT: no body in wave 0 (member of a class template).

// 0x66a500 ItemBase<GroceryTrait>::Initialize: LIFT: no body in wave 0 (member of a class template).

// 0x66a620 ItemBase<GroceryTrait>::Initialize: LIFT: no body in wave 0 (member of a class template).

// 0x66a750 ItemBase<GroceryTrait>::Initialize: LIFT: no body in wave 0 (member of a class template).

// 0x66a860 ItemBase<GroceryTrait>::Clone: LIFT: no body in wave 0 (member of a class template).

// 0x66a9f0 ItemBase<GroceryTrait>::RefreshSyncBuffer: LIFT: no body in wave 0 (member of a class template).

// 0x66ab20 ItemBase<GroceryTrait>::FetchBroadcast: LIFT: no body in wave 0 (member of a class template).

// 0x66abb0 ItemBase<GroceryTrait>::FetchBroadcastNull: LIFT: no body in wave 0 (member of a class template).

// 0x66ac30 ItemBase<GroceryTrait>::FetchDBData: LIFT: no body in wave 0 (member of a class template).

// 0x66aef0 ItemBase<GroceryTrait>::FetchXmlData: LIFT: no body in wave 0 (member of a class template).

// 0x66b110 ItemBase<GroceryTrait>::FetchOpXmlData: LIFT: no body in wave 0 (member of a class template).

// 0x66b460 ItemBase<GroceryTrait>::FetchOpDBData: LIFT: no body in wave 0 (member of a class template).

// 0x66ba90
template <>
char __cdecl ItemBase< ::GroceryTrait>::GetClass(void) const
{
    return 3;  // LIFT: item class grocery
}

// 0x66baa0
template <>
unsigned char __cdecl ItemBase< ::AccessoryTrait>::GetDepot(void) const
{
    return prop.Default.depot;
}

// 0x66bab0 ItemBase<GroceryTrait>::SetSequestration: LIFT: no body in wave 0 (member of a class template).

// 0x66bad0 ItemBase<GroceryTrait>::InitPropertyByXml: LIFT: no body in wave 0 (member of a class template).

// 0x66bda0 ItemBase<GemTrait>::ItemBase<GemTrait>: LIFT: no body in wave 0 (member of a class template).

// 0x66be20 ItemBase<GemTrait>::Initialize: LIFT: no body in wave 0 (member of a class template).

// 0x66bf40 ItemBase<GemTrait>::Initialize: LIFT: no body in wave 0 (member of a class template).

// 0x66c070 ItemBase<GemTrait>::Initialize: LIFT: no body in wave 0 (member of a class template).

// 0x66c180 ItemBase<GemTrait>::Clone: LIFT: no body in wave 0 (member of a class template).

// 0x66c310 ItemBase<GemTrait>::RefreshSyncBuffer: LIFT: no body in wave 0 (member of a class template).

// 0x66c440 ItemBase<AccessoryTrait>::FetchBroadcast: LIFT: no body in wave 0 (member of a class template).

// 0x66c4d0 ItemBase<GemTrait>::FetchBroadcastNull: LIFT: no body in wave 0 (member of a class template).

// 0x66c560 ItemBase<AccessoryTrait>::FetchDb: LIFT: no body in wave 0 (member of a class template).

// 0x66c6b0 ItemBase<GemTrait>::FetchDBData: LIFT: no body in wave 0 (member of a class template).

// 0x66c970 ItemBase<GemTrait>::FetchXmlData: LIFT: no body in wave 0 (member of a class template).

// 0x66cb90 ItemBase<GemTrait>::FetchOpXmlData: LIFT: no body in wave 0 (member of a class template).

// 0x66cee0 ItemBase<GemTrait>::FetchOpDBData: LIFT: no body in wave 0 (member of a class template).

// 0x66d510
template <>
char __cdecl ItemBase< ::GemTrait>::GetClass(void) const
{
    return 4;  // LIFT: item class gem
}

// 0x66d520 ItemBase<AccessoryTrait>::GetData: LIFT: no body in wave 0 (member of a class template).

// 0x66d530 ItemBase<AccessoryTrait>::SetData: LIFT: no body in wave 0 (member of a class template).

// 0x66d580 ItemBase<GemTrait>::InitPropertyByXml: LIFT: no body in wave 0 (member of a class template).

// 0x66d850 ItemBase<AccessoryTrait>::ItemBase<AccessoryTrait>: LIFT: no body in wave 0 (member of a class template).

// 0x66d8d0 ItemBase<AccessoryTrait>::Initialize: LIFT: no body in wave 0 (member of a class template).

// 0x66d9f0 ItemBase<AccessoryTrait>::Initialize: LIFT: no body in wave 0 (member of a class template).

// 0x66db20 ItemBase<AccessoryTrait>::Initialize: LIFT: no body in wave 0 (member of a class template).

// 0x66dc30 ItemBase<AccessoryTrait>::Clone: LIFT: no body in wave 0 (member of a class template).

// 0x66ddc0 ItemBase<AccessoryTrait>::RefreshSyncBuffer: LIFT: no body in wave 0 (member of a class template).

// 0x66def0 ItemBase<AccessoryTrait>::FetchBroadcastNull: LIFT: no body in wave 0 (member of a class template).

// 0x66df80 ItemBase<AccessoryTrait>::FetchDBData: LIFT: no body in wave 0 (member of a class template).

// 0x66e240 ItemBase<AccessoryTrait>::FetchXmlData: LIFT: no body in wave 0 (member of a class template).

// 0x66e460 ItemBase<AccessoryTrait>::FetchOpXmlData: LIFT: no body in wave 0 (member of a class template).

// 0x66e7b0 ItemBase<AccessoryTrait>::FetchOpDBData: LIFT: no body in wave 0 (member of a class template).

// 0x66ede0
template <>
int __cdecl ItemBase< ::AccessoryTrait>::GetDataId(void) const
{
    return prop.Default.data_id;
}

// 0x66edf0
template <>
char __cdecl ItemBase< ::AccessoryTrait>::GetClass(void) const
{
    return 5;  // LIFT: item class accessory
}

// 0x66ee10
template <>
bool __cdecl ItemBase< ::AccessoryTrait>::GetSequestration(void) const
{
    return prop.Default.sequestration;
}

// 0x66ee20 ItemBase<AccessoryTrait>::SetPos: LIFT: no body in wave 0 (member of a class template).

// 0x66ee50 ItemBase<AccessoryTrait>::SetSequestration: LIFT: no body in wave 0 (member of a class template).

// 0x66ee70 ItemBase<AccessoryTrait>::InitPropertyByXml: LIFT: no body in wave 0 (member of a class template).
