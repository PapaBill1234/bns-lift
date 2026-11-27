// effectcontent_h.cpp: effectcontent.h (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "effectcontent.h"
#include "gameobject.h"
#include "LiftStub.h"

// 0x479cf0
__cdecl CommonPassiveEffect::CommonPassiveEffect(void)
{
    LIFT_STUB(0x479cf0);
}

// LIFT: the Data::EffectRecordSubType enumerators are not declared yet; the values come from the 2019 bodies.

// 0x479ee0
#pragma comment(linker, "/INCLUDE:?GetDataSubType@TransitEffect@@UEAA?AW4EffectRecordSubType@Data@@XZ")  // LIFT: dead-strip keep (no live caller yet)
::Data::EffectRecordSubType __cdecl TransitEffect::GetDataSubType(void)
{
    return static_cast< ::Data::EffectRecordSubType>(44);
}

// 0x47a4a0
#pragma comment(linker, "/INCLUDE:?GetDataSubType@DashEffect@@UEAA?AW4EffectRecordSubType@Data@@XZ")  // LIFT: dead-strip keep (no live caller yet)
::Data::EffectRecordSubType __cdecl DashEffect::GetDataSubType(void)
{
    return static_cast< ::Data::EffectRecordSubType>(612);
}

// 0x47a520
#pragma comment(linker, "/INCLUDE:?GetDataSubType@FallDamageEffect@@UEAA?AW4EffectRecordSubType@Data@@XZ")  // LIFT: dead-strip keep (no live caller yet)
::Data::EffectRecordSubType __cdecl FallDamageEffect::GetDataSubType(void)
{
    return static_cast< ::Data::EffectRecordSubType>(613);
}

// 0x47a530
#pragma comment(linker, "/INCLUDE:?GetDataSubType@AirDashEffect@@UEAA?AW4EffectRecordSubType@Data@@XZ")  // LIFT: dead-strip keep (no live caller yet)
::Data::EffectRecordSubType __cdecl AirDashEffect::GetDataSubType(void)
{
    return static_cast< ::Data::EffectRecordSubType>(614);
}

// 0x47a770
#pragma comment(linker, "/INCLUDE:?GetDataSubType@OceanicEffect@@UEAA?AW4EffectRecordSubType@Data@@XZ")  // LIFT: dead-strip keep (no live caller yet)
::Data::EffectRecordSubType __cdecl OceanicEffect::GetDataSubType(void)
{
    return static_cast< ::Data::EffectRecordSubType>(622);
}

// 0x47a7f0
#pragma comment(linker, "/INCLUDE:?GetDataSubType@FallDeathEffect@@UEAA?AW4EffectRecordSubType@Data@@XZ")  // LIFT: dead-strip keep (no live caller yet)
::Data::EffectRecordSubType __cdecl FallDeathEffect::GetDataSubType(void)
{
    return static_cast< ::Data::EffectRecordSubType>(623);
}

// 0x47a800
// LIFT: object type 1 (the high 16 bits of the id) is a Pc.
#pragma comment(linker, "/INCLUDE:?checkApply@IncreaseSpecialSkillGaugeEffect@@EEAA_NXZ")  // LIFT: dead-strip keep (no live caller yet)
bool __cdecl IncreaseSpecialSkillGaugeEffect::checkApply(void)
{
    ::GameObject const *const target = reinterpret_cast< ::EffectTargetView const *>(this)->target;
    return static_cast<unsigned short>(reinterpret_cast< ::GameObjectIdView const *>(target)->Id >> 48) == 1;
}

// 0x47a820
__cdecl DuelFighterTimeLimitEffect::~DuelFighterTimeLimitEffect(void)
{
    LIFT_STUB(0x47a820);
}

// 0x47a8a0
__cdecl DuelInterferenceEffect::~DuelInterferenceEffect(void)
{
    LIFT_STUB(0x47a8a0);
}
