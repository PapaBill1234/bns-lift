// effectproperty.h: effectproperty.cpp, effectproperty.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"
#include "propertysync.h"

class EffectProperty
{
public:
    virtual __cdecl ~EffectProperty(void);  // 0x19860
    virtual wchar_t const * __cdecl Name(void) const;  // 0x19870
protected:
    virtual int __cdecl FieldMax(void) const;  // 0x19880
    virtual ::Field::Def const * __cdecl FieldDefine(void) const;  // 0x19890
    virtual int __cdecl SyncMax(void) const;  // 0x198a0
    virtual ::SyncBuffer::Def const * __cdecl SyncDefine(void) const;  // 0x198b0
    static int fieldMax;
    static ::Field::Def const * fieldDefine;
    static int syncMax;
    static ::SyncBuffer::Def const * syncDefine;
public:
    __cdecl EffectProperty(void);  // 0x198f0

    // PDB nested type EffectProperty::__default__ (size 0x18).
    struct __default__
    {
        short pos;                  // +0x00
        int data_id;                // +0x04
        int duration;               // +0x08
        char stack_count;           // +0x0C
        char detach_count;          // +0x0D
        long long expiration_time;  // +0x10
    };

private:
    char _liftPropertyBase[0x28];  // LIFT: Property base members (+0x08 to +0x30), later waves
public:
    EffectProperty::__default__ Default;  // +0x30. LIFT: the PDB type is `__default__ const`
};
static_assert(sizeof(EffectProperty::__default__) == 0x18, "sizeof EffectProperty::__default__");

