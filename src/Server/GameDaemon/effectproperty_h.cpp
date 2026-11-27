// effectproperty_h.cpp: effectproperty.h (GameDaemon PDB, 2019 + PDB).
#include "effectproperty.h"
#include "propertysync.h"
#include "LiftStub.h"

// LIFT: keep the lifted virtual functions until the callers are lifted. Card lift-gamedaemon-gap-002-e2.
#pragma comment(linker, "/INCLUDE:?Name@EffectProperty@@UEBAPEB_WXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?FieldMax@EffectProperty@@MEBAHXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?FieldDefine@EffectProperty@@MEBAPEBUDef@Field@@XZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?SyncMax@EffectProperty@@MEBAHXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?SyncDefine@EffectProperty@@MEBAPEBUDef@SyncBuffer@@XZ")  // LIFT: dead-strip keep (no live caller yet)


// 0x19860
__cdecl EffectProperty::~EffectProperty(void)
{
    LIFT_STUB(0x19860);
}

// 0x19870
wchar_t const * __cdecl EffectProperty::Name(void) const
{
    return L"EffectProperty";
}

// 0x19880
int __cdecl EffectProperty::FieldMax(void) const
{
    return fieldMax;
}

// 0x19890
::Field::Def const * __cdecl EffectProperty::FieldDefine(void) const
{
    return fieldDefine;
}

// 0x198a0
int __cdecl EffectProperty::SyncMax(void) const
{
    return syncMax;
}

// 0x198b0
::SyncBuffer::Def const * __cdecl EffectProperty::SyncDefine(void) const
{
    return syncDefine;
}

// LIFT: definitions of the PDB static data members.
int EffectProperty::fieldMax;
::Field::Def const * EffectProperty::fieldDefine;
int EffectProperty::syncMax;
::SyncBuffer::Def const * EffectProperty::syncDefine;
