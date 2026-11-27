// effect_h.cpp: effect.h (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "effect.h"
#include "creature.h"
#include "zone.h"
#include "LiftStub.h"

// 0x453a20
bool __cdecl Effect::Initialize2(::EffectSource, ::Zone *, unsigned __int64, unsigned __int64, char, unsigned __int64, ::Data::EffectRecord const *, long)
{
    LIFT_STUB(0x453a20);
}

// 0x453a60
bool __cdecl Effect::Initialize3(::EffectSource, ::Zone *, unsigned __int64, unsigned __int64, char, unsigned __int64, ::Data::EffectRecord const *, bool, ::SkillResult, ::ApplySkillModifyInfo *, short, ::vector16, short, short)
{
    LIFT_STUB(0x453a60);
}

// 0x453aa0
bool __cdecl Effect::Initialize4(::EffectSource, ::Zone *, unsigned __int64, unsigned __int64, char, unsigned __int64, ::Data::EffectRecord const *, ::vector16, char, ::TargetPart, unsigned __int64, unsigned __int64)
{
    LIFT_STUB(0x453aa0);
}

// 0x453ae0
bool __cdecl Effect::Initialize5(::EffectSource, ::Zone *, unsigned __int64, unsigned __int64, char, unsigned __int64, long, ::vector16, short, bool, short, int, short, unsigned __int64, unsigned __int64, unsigned __int64, unsigned __int64)
{
    LIFT_STUB(0x453ae0);
}

// 0x453b20
short __cdecl PassiveEffect::GetDbIndex(void) const
{
    LIFT_STUB(0x453b20);
}

// 0x453b30
char __cdecl PassiveEffect::GetStackCount(void) const
{
    LIFT_STUB(0x453b30);
}

// 0x453b40
::EffectSlotList *const __cdecl ControlledCreatureEffectSlot::GetEffectSlotList(int)
{
    LIFT_STUB(0x453b40);
}

// 0x453b60
bool __cdecl EffectContainer::IsBroadcastSlot(::EffectSlot)
{
    LIFT_STUB(0x453b60);
}
