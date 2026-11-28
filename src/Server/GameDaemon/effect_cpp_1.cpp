// effect_cpp_1.cpp: effect.cpp part 1 (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "effect.h"
#include "creature.h"
#include "effectproperty.h"
#include "zone.h"
#include "RefCntObject.h"
#include "Daemon.h"
#include "Log.h"
#include "LiftStub.h"

#pragma comment(linker, "/INCLUDE:?GetRemainDuration@PassiveEffect@@QEAAJPEA_W@Z")  // LIFT: dead-strip keep (no live caller yet)

#define EFFECT_FILE L"e:\\dailybuild02\\gamedaemon-common-0.0.348\\depot\\branch\\348nc\\program\\server\\gamedaemon\\Effect.cpp"

namespace
{
// LIFT: view of GameObject (PDB: base RefCntObject at +0, Id at +0x28). The skeleton GameObject has no base yet.
struct GameObjectView
{
    char lift_pad_0[0x28];
    unsigned __int64 Id;  // +40 (0x28)
};

// LIFT: view of DrEl (PDB: subtype at +2), the base of Data::EffectRecord.
struct DrElView
{
    char type;            // +0
    short subtype;        // +2
    unsigned short size;  // +4
};

// LIFT: object type of a GameObject id (high 16 bits). ❓ PDB name of the inline helper.
inline unsigned short GetObjectType(unsigned __int64 id)
{
    return static_cast<unsigned short>(id >> 48);
}

const unsigned short OBJECT_TYPE_32 = 32;  // LIFT: object type value 32 (pseudocode); ❓ enumerator name

// LIFT: view of Creature (PDB: Prop at +0x30, CreatureProperty::Abnormality at +0x738, __abnormality__::immune_debuff at +7).
struct CreatureAbnormalityView
{
    char lift_pad_0[0x30 + 0x738 + 7];
    bool immune_debuff;  // +0x76F (Prop.Abnormality.immune_debuff)
};

// LIFT: view of Data::EffectRecord (PDB: key at +8, buff_type at +0x38, ignore_immune_debuff at +0xC2).
struct EffectRecordView
{
    char lift_pad_0[8];
    int id;                     // +0x8 (key.id)
    char lift_pad_1[0x38 - 0xC];
    char buff_type;             // +0x38
    char lift_pad_2[0xC2 - 0x39];
    bool ignore_immune_debuff;  // +0xC2
};

const char BUFF_TYPE_DEBUFF = 2;  // LIFT: buff_type value 2 (pseudocode); ❓ enumerator name
}

// 0x5a2ec0
__cdecl Effect::~Effect(void)
{
    LIFT_STUB(0x5a2ec0);
}

// 0x5a2f30
::Data::EffectRecordSubType __cdecl Effect::GetDataSubType(void)
{
    LIFT_STUB(0x5a2f30);
}

// 0x5a2f40
bool __cdecl Effect::Initialize1(::EffectSource, ::Zone *, unsigned __int64, unsigned __int64, char, unsigned __int64, ::Data::EffectRecord const *)
{
    LIFT_STUB(0x5a2f40);
}

// 0x5a3480
bool __cdecl Effect::GetCreatureFunctionFieldId(::Data::EffectFunctionType, unsigned short &)
{
    LIFT_STUB(0x5a3480);
}

// 0x5a35b0
void __cdecl Effect::CalcDamagePowerPercent(int, int, int, int, __int64 &, int &, ::ApplySkillModifyInfo *)
{
    LIFT_STUB(0x5a35b0);
}

// 0x5a3610
void __cdecl Effect::InvokeEffects(::EffectSource, ::Zone *, unsigned __int64, unsigned __int64, unsigned __int64 const *const, char)
{
    LIFT_STUB(0x5a3610);
}

// 0x5a3720
void __cdecl Effect::InvokePassiveEffects(::EffectSource, ::Zone *, unsigned __int64, unsigned __int64, unsigned __int64 const *const, char)
{
    LIFT_STUB(0x5a3720);
}

// 0x5a38d0
bool __cdecl Effect::getPosition(::vector16 &)
{
    LIFT_STUB(0x5a38d0);
}

// 0x5a39a0
void __cdecl Effect::transferEvent(void)
{
    LIFT_STUB(0x5a39a0);
}

// 0x5a3ab0
void __cdecl Effect::broadcastOther(char, char, unsigned int, ::ChangedProperty *, char const *, int, ...)
{
    LIFT_STUB(0x5a3ab0);
}

// 0x5a3ca0
void __cdecl Effect::broadcast(char, unsigned int, ::ChangedProperty *, char const *, int, ...)
{
    LIFT_STUB(0x5a3ca0);
}

// 0x5a3e90
void __cdecl Effect::createDuelbotEffectAction(char, unsigned int, char const *, int, ...)
{
    LIFT_STUB(0x5a3e90);
}

// 0x5a3fd0
bool __cdecl Effect::checkImmuneDebuff(void)
{
    LIFT_STUB(0x5a3fd0);
}

// 0x5a4060
bool __cdecl Effect::checkEffectAttribute(::ChangedProperty *)
{
    LIFT_STUB(0x5a4060);
}

// 0x5a4210
bool __cdecl Effect::dropFieldItem(void)
{
    LIFT_STUB(0x5a4210);
}

// 0x5a4260
::EffectAttachFail __cdecl InstantEffect::Invoke(short, unsigned int)
{
    LIFT_STUB(0x5a4260);
}

// 0x5a4430
void __cdecl InstantEffect::postApply(void)
{
    LIFT_STUB(0x5a4430);
}

// 0x5a4900
void __cdecl InstantEffect::addZoneScore(void)
{
    LIFT_STUB(0x5a4900);
}

// 0x5a49b0
__cdecl PassiveEffect::PassiveEffect(void)
{
    LIFT_STUB(0x5a49b0);
}

// 0x5a4b80
bool __cdecl PassiveEffect::Initialize1(::EffectSource, ::Zone *, unsigned __int64, unsigned __int64, char, unsigned __int64, ::Data::EffectRecord const *)
{
    LIFT_STUB(0x5a4b80);
}

// 0x5a4d90
short __cdecl PassiveEffect::FetchBroadcast(char *, short) const
{
    LIFT_STUB(0x5a4d90);
}

// 0x5a4e20
short __cdecl PassiveEffect::FetchDb(char *, short) const
{
    LIFT_STUB(0x5a4e20);
}

// 0x5a4ea0
void __cdecl PassiveEffect::SetProperty(::EffectProperty const *)
{
    LIFT_STUB(0x5a4ea0);
}

// 0x5a4fb0
::EffectAttachFail __cdecl PassiveEffect::Invoke(short, unsigned int)
{
    LIFT_STUB(0x5a4fb0);
}

// 0x5a52c0
void __cdecl PassiveEffect::setDuration(long)
{
    LIFT_STUB(0x5a52c0);
}

// 0x5a5320
short __cdecl PassiveEffect::GetSlotIndex(void)
{
    LIFT_STUB(0x5a5320);
}

// 0x5a5430
void __cdecl PassiveEffect::attached(short, ::ChangedProperty *)
{
    LIFT_STUB(0x5a5430);
}

// 0x5a56a0
void __cdecl PassiveEffect::detached(::DetachReason, bool, bool)
{
    LIFT_STUB(0x5a56a0);
}

// 0x5a5ae0
bool __cdecl PassiveEffect::invokeDetachEffect(::DetachReason)
{
    LIFT_STUB(0x5a5ae0);
}

// 0x5a5cf0
void __cdecl PassiveEffect::intervalExpired(long, __int64)
{
    LIFT_STUB(0x5a5cf0);
}

// 0x5a60b0
bool __cdecl PassiveEffect::ResetDuration(long)
{
    LIFT_STUB(0x5a60b0);
}

// 0x5a61f0
void __cdecl PassiveEffect::CalcRemained(void)
{
    LIFT_STUB(0x5a61f0);
}

// 0x5a62a0
long __cdecl PassiveEffect::GetRemainDuration(wchar_t *)
{
    __int64 now = GetTickCount64() - Daemon::Instance->StartSystemTick64;
    long elapsed = static_cast<long>((now - _updateTime) / 100) * 100;
    long remain = _prop.Default.duration - elapsed;
    if (remain < 0)
        return 0;
    return remain;
}

// 0x5a6300
void __cdecl PassiveEffect::CalcScheduleTime(__int64, long)
{
    LIFT_STUB(0x5a6300);
}

// 0x5a63d0
void __cdecl PassiveEffect::UpdateScheduleTime(__int64, bool)
{
    LIFT_STUB(0x5a63d0);
}

// 0x5a64b0
void __cdecl PassiveEffect::broadcastPassiveFullSync(bool)
{
    LIFT_STUB(0x5a64b0);
}

// 0x5a65d0
void __cdecl PassiveEffect::broadcastPassiveDetachCountSync(void)
{
    LIFT_STUB(0x5a65d0);
}

// 0x5a6760
void __cdecl PassiveEffect::broadcastPassiveDetach(void)
{
    LIFT_STUB(0x5a6760);
}

// 0x5a6850
bool __cdecl PassiveEffect::checkApplyPassive(void)
{
    LIFT_STUB(0x5a6850);
}

// 0x5a68f0
::Data::EffectTransitionType __cdecl PassiveEffect::getTransitionLinkState(void)
{
    LIFT_STUB(0x5a68f0);
}

// 0x5a69a0
bool __cdecl PassiveEffect::dispelLink(void)
{
    LIFT_STUB(0x5a69a0);
}

// 0x5a79b0
bool __cdecl PassiveEffect::applyDurationFormula(long &)
{
    LIFT_STUB(0x5a79b0);
}

// 0x5a7d00
bool __cdecl PassiveEffect::checkStackable(::PassiveEffect::ReturnStackable &)
{
    LIFT_STUB(0x5a7d00);
}

// 0x5a7dc0
long __cdecl PassiveEffect::getExpirationRemainDuration(void)
{
    LIFT_STUB(0x5a7dc0);
}

// 0x5a7e70
::PassiveEffect::ReturnStackable __cdecl PassiveEffect::checkStackPriority(::PassiveEffect *)
{
    LIFT_STUB(0x5a7e70);
}

// 0x5a9040
::EffectEventType __cdecl PassiveEffect::getEventType(::Data::EffectDetachSlotType)
{
    LIFT_STUB(0x5a9040);
}

// 0x5a9130
void __cdecl PassiveEffect::execChangeDefaultStanceByFlag(::ChangedProperty *)
{
    LIFT_STUB(0x5a9130);
}

// 0x5a9210
void __cdecl PassiveEffect::reApplyAbility(char, ::ChangedProperty *)
{
    LIFT_STUB(0x5a9210);
}

// 0x5a9340
void __cdecl PassiveEffect::applyAbility(bool, ::ChangedProperty *)
{
    LIFT_STUB(0x5a9340);
}

// 0x5a94a0
void __cdecl PassiveEffect::applyFunctionFlag(bool, ::ChangedProperty *)
{
    LIFT_STUB(0x5a94a0);
}

// 0x5a95c0
void __cdecl PassiveEffect::applyEffectAttribute(bool, ::ChangedProperty *)
{
    LIFT_STUB(0x5a95c0);
}

// 0x5a9930
void __cdecl PassiveEffect::applyEffectFlag(bool, ::ChangedProperty *)
{
    LIFT_STUB(0x5a9930);
}

// 0x5a99b0
void __cdecl PassiveEffect::applyMaxStackEffectFlag(bool, ::ChangedProperty *)
{
    LIFT_STUB(0x5a99b0);
}

// 0x5a9a30
bool __cdecl PassiveEffect::onEvent(unsigned __int64, unsigned __int64, ::EffectEventType)
{
    LIFT_STUB(0x5a9a30);
}

// 0x5a9dc0
bool __cdecl PassiveEffect::invokeEventEffect(unsigned __int64, unsigned __int64, ::EffectEventType)
{
    LIFT_STUB(0x5a9dc0);
}

// 0x5aa0a0
bool __cdecl PassiveEffect::invokeTransformEffect(void)
{
    LIFT_STUB(0x5aa0a0);
}

// 0x5aa150
__cdecl ControlledCreatureEffectSlot::ControlledCreatureEffectSlot(void)
{
    LIFT_STUB(0x5aa150);
}

// 0x5aa500
__cdecl DuelBotEffectSlot::DuelBotEffectSlot(void)
{
    LIFT_STUB(0x5aa500);
}

// 0x5aa760
::EffectSlotList *const __cdecl DuelBotEffectSlot::GetEffectSlotList(int)
{
    LIFT_STUB(0x5aa760);
}

// 0x5aa810
__cdecl NpcEffectSlot::NpcEffectSlot(void)
{
    LIFT_STUB(0x5aa810);
}

// 0x5aa970
__cdecl BossNpcEffectSlot::BossNpcEffectSlot(void)
{
    LIFT_STUB(0x5aa970);
}

// 0x5aaae0
::EffectSlotList *const __cdecl BossNpcEffectSlot::GetEffectSlotList(int)
{
    LIFT_STUB(0x5aaae0);
}

// 0x5aab70
__cdecl EffectContainer::EffectContainer(void)
{
    LIFT_STUB(0x5aab70);
}
