// effect_h.cpp: effect.h (GameDaemon PDB, 2019 + PDB).
#include "effect.h"
#include "creature.h"
#include "zone.h"
#include "Log.h"
#include "AlertSender.h"
#include "LiftStub.h"

// Path literal of Effect.h in the GameDaemon build (lessons A6).
#define EFFECT_H_FILE L"e:\\dailybuild02\\gamedaemon-common-0.0.348\\depot\\branch\\348nc\\program\\server\\gamedaemon\\Effect.h"

// 0x453a20
bool __cdecl Effect::Initialize2(::EffectSource, ::Zone *, unsigned __int64, unsigned __int64, char, unsigned __int64, ::Data::EffectRecord const *, long)
{
    Log::Write(Log::LT_ERROR, EFFECT_H_FILE, 159, L"== CRASH == [effect], invalid Initialize function called");
    AlertSender::Write(EFFECT_H_FILE, 159, L"== CRASH == [effect], invalid Initialize function called");
    return false;
}

// 0x453a60
bool __cdecl Effect::Initialize3(::EffectSource, ::Zone *, unsigned __int64, unsigned __int64, char, unsigned __int64, ::Data::EffectRecord const *, bool, ::SkillResult, ::ApplySkillModifyInfo *, short, ::vector16, short, short)
{
    Log::Write(Log::LT_ERROR, EFFECT_H_FILE, 170, L"== CRASH == [effect], invalid Initialize function called");
    AlertSender::Write(EFFECT_H_FILE, 170, L"== CRASH == [effect], invalid Initialize function called");
    return false;
}

// 0x453aa0
bool __cdecl Effect::Initialize4(::EffectSource, ::Zone *, unsigned __int64, unsigned __int64, char, unsigned __int64, ::Data::EffectRecord const *, ::vector16, char, ::TargetPart, unsigned __int64, unsigned __int64)
{
    Log::Write(Log::LT_ERROR, EFFECT_H_FILE, 182, L"== CRASH == [effect], invalid Initialize function called");
    AlertSender::Write(EFFECT_H_FILE, 182, L"== CRASH == [effect], invalid Initialize function called");
    return false;
}

// 0x453ae0
bool __cdecl Effect::Initialize5(::EffectSource, ::Zone *, unsigned __int64, unsigned __int64, char, unsigned __int64, long, ::vector16, short, bool, short, int, short, unsigned __int64, unsigned __int64, unsigned __int64, unsigned __int64)
{
    Log::Write(Log::LT_ERROR, EFFECT_H_FILE, 194, L"== CRASH == [effect], invalid Initialize function called");
    AlertSender::Write(EFFECT_H_FILE, 194, L"== CRASH == [effect], invalid Initialize function called");
    return false;
}

// 0x453b20
short __cdecl PassiveEffect::GetDbIndex(void) const
{
    return _prop.Default.pos;
}

// 0x453b30
char __cdecl PassiveEffect::GetStackCount(void) const
{
    return _prop.Default.stack_count;
}

// 0x453b40
::EffectSlotList *const __cdecl ControlledCreatureEffectSlot::GetEffectSlotList(int slot)
{
    if (static_cast<unsigned int>(slot) > 18)
        return nullptr;
    return &slotList[slot];
}

// 0x453b60
bool __cdecl EffectContainer::IsBroadcastSlot(::EffectSlot slot)
{
    switch (static_cast<int>(slot)) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 7:
    case 8:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    case 16:
    case 17:
    case 18:
        return true;
    default:
        return false;
    }
}
