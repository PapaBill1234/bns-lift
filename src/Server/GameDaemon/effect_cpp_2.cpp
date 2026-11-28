// effect_cpp_2.cpp: effect.cpp part 2 (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "effect.h"
#include "creature.h"
#include "effectproperty.h"
#include "zone.h"
#include "LiftStub.h"
#include <new>

#define EFFECT_FILE L"e:\\dailybuild02\\gamedaemon-common-0.0.348\\depot\\branch\\348nc\\program\\server\\gamedaemon\\Effect.cpp"

// 0x5aac20
__cdecl EffectContainer::~EffectContainer(void)
{
    LIFT_STUB(0x5aac20);
}

// 0x5aaed0
void __cdecl EffectContainer::Initialize(::Creature *)
{
    LIFT_STUB(0x5aaed0);
}

// 0x5ab0f0
bool __cdecl EffectContainer::Attach(::PassiveEffect *, ::ChangedProperty *)
{
    LIFT_STUB(0x5ab0f0);
}

// 0x5ab430
bool __cdecl EffectContainer::Detach(::PassiveEffect *, ::DetachReason, int)
{
    LIFT_STUB(0x5ab430);
}

// 0x5ab7a0
bool __cdecl EffectContainer::DetachByGroupId(::EffectSlot, unsigned int, ::DetachReason)
{
    LIFT_STUB(0x5ab7a0);
}

// 0x5ab910
bool __cdecl EffectContainer::DetachByDataId(::EffectSlot, unsigned int, ::DetachReason)
{
    LIFT_STUB(0x5ab910);
}

// 0x5aba90
bool __cdecl EffectContainer::DetachByAttributeValue(::Data::EffectEffectSlotType, unsigned __int64, unsigned __int64, unsigned __int64, char, bool)
{
    LIFT_STUB(0x5aba90);
}

// 0x5abf80
bool __cdecl EffectContainer::DetachByType(::Data::EffectRecordSubType, ::DetachReason, short, __int64, bool)
{
    LIFT_STUB(0x5abf80);
}

// 0x5ac0a0
bool __cdecl EffectContainer::DetachAll(::EffectSlot, ::DetachReason, int)
{
    LIFT_STUB(0x5ac0a0);
}

// 0x5ac200
bool __cdecl EffectContainer::DetachBindingSkillStep(bool)
{
    LIFT_STUB(0x5ac200);
}

// 0x5ac380
bool __cdecl EffectContainer::DetachFactionScore(int)
{
    LIFT_STUB(0x5ac380);
}

// 0x5ac510
bool __cdecl EffectContainer::Find(::Data::EffectRecordSubType, ::PassiveEffect **)
{
    LIFT_STUB(0x5ac510);
}

// 0x5ac670
bool __cdecl EffectContainer::Find(::EffectSlot, ::Data::EffectRecordSubType, ::PassiveEffect **)
{
    LIFT_STUB(0x5ac670);
}

// 0x5ac7c0
void __cdecl EffectContainer::clearGeoEffects(void)
{
    LIFT_STUB(0x5ac7c0);
}

// 0x5acba0
void __cdecl EffectContainer::clearEffectsByLeaveZone(void)
{
    LIFT_STUB(0x5acba0);
}

// 0x5acf80
void __cdecl EffectContainer::clearEffects(void)
{
    LIFT_STUB(0x5acf80);
}

// 0x5ad2e0
void __cdecl EffectContainer::DetachAllBuffDebuff(bool, bool)
{
    LIFT_STUB(0x5ad2e0);
}

// 0x5ad810
void __cdecl EffectContainer::DetachByDuelBotChallengeAttractionRule(void)
{
    LIFT_STUB(0x5ad810);
}

// 0x5adbf0
void __cdecl EffectContainer::RemainBySkillTrainingRoomAttractionRule(void)
{
    LIFT_STUB(0x5adbf0);
}

// 0x5adfd0
void __cdecl EffectContainer::RemainByChallengePartyAttractionRule(void)
{
    LIFT_STUB(0x5adfd0);
}

// 0x5ae3b0
void __cdecl EffectContainer::ClearAllBuffDebuff(void)
{
    LIFT_STUB(0x5ae3b0);
}

// 0x5ae810
void __cdecl EffectContainer::EnterZone(::EnterReason)
{
    LIFT_STUB(0x5ae810);
}

// 0x5ae9a0
void __cdecl EffectContainer::LeaveZone(::LeaveReason, bool)
{
    LIFT_STUB(0x5ae9a0);
}

// 0x5aeaf0
void __cdecl EffectContainer::SendUpdateCache(void)
{
    LIFT_STUB(0x5aeaf0);
}

// 0x5aed50
void __cdecl EffectContainer::sendDeleteCache(::PassiveEffect *)
{
    LIFT_STUB(0x5aed50);
}

// 0x5aedc0
void __cdecl EffectContainer::updatePassiveEffects(bool)
{
    LIFT_STUB(0x5aedc0);
}

// 0x5aefa0
bool __cdecl EffectContainer::OnEvent(unsigned __int64, unsigned __int64, ::Data::EffectRecordSubType)
{
    LIFT_STUB(0x5aefa0);
}

// 0x5af290
bool __cdecl EffectContainer::OnEvent(unsigned __int64, unsigned __int64, ::Data::SkillEventTypeType, ::SkillResult, short)
{
    LIFT_STUB(0x5af290);
}

// 0x5af460
bool __cdecl EffectContainer::OnEventByCasting(bool)
{
    LIFT_STUB(0x5af460);
}

// 0x5af510
bool __cdecl EffectContainer::onEvent(unsigned __int64, unsigned __int64, ::EffectEventType)
{
    LIFT_STUB(0x5af510);
}

// 0x5af920
void __cdecl EffectContainer::postEvent(::EffectEventType, short)
{
    LIFT_STUB(0x5af920);
}

// 0x5afb30
int __cdecl EffectContainer::SetDbList(unsigned __int64, short, char const *, int, ::EffectProperty *, short &)
{
    LIFT_STUB(0x5afb30);
}

// 0x5afcf0
void __cdecl EffectContainer::restore(::EffectProperty const *const, short)
{
    LIFT_STUB(0x5afcf0);
}

// 0x5b0160
short __cdecl EffectContainer::FetchList(short *, char *, short, int)
{
    LIFT_STUB(0x5b0160);
}

// 0x5b0320
short __cdecl EffectContainer::GetListSize(void)
{
    LIFT_STUB(0x5b0320);
}

// 0x5b03c0
short __cdecl EffectContainer::newIndex(::EffectSlot)
{
    LIFT_STUB(0x5b03c0);
}

// 0x5b0440
void __cdecl EffectContainer::SetSchedule(::PassiveEffect *, long)
{
    LIFT_STUB(0x5b0440);
}

// 0x5b0500
bool __cdecl EffectContainer::SetScheduleInterval(long)
{
    LIFT_STUB(0x5b0500);
}

// 0x5b0600
bool __cdecl EffectContainer::setScheduleInterval(long)
{
    LIFT_STUB(0x5b0600);
}

// 0x5b0690
void __cdecl EffectContainer::OnTimer(long)
{
    LIFT_STUB(0x5b0690);
}

// 0x5b0790
void __cdecl EffectContainer::executeSchedule(long)
{
    LIFT_STUB(0x5b0790);
}

// 0x5b0920
void __cdecl EffectContainer::releaseDetachedList(void)
{
    LIFT_STUB(0x5b0920);
}

// 0x5b09e0
void __cdecl EffectContainer::reschedule(__int64, long)
{
    LIFT_STUB(0x5b09e0);
}

// 0x5b0b50
__cdecl EffectFactory::~EffectFactory(void)
{
    LIFT_STUB(0x5b0b50);
}

// 0x5b0be0
bool __cdecl EffectFactory::Init(void)
{
    LIFT_STUB(0x5b0be0);
}

// 0x5b0dc0
char __cdecl EffectFactory::GetBroadcastType(int) const
{
    LIFT_STUB(0x5b0dc0);
}

// 0x5b0e20
::Effect * __cdecl EffectFactory::CreateEffect(::Data::EffectRecordSubType) const
{
    LIFT_STUB(0x5b0e20);
}

// 0x5b37f0
::Effect * __cdecl EffectFactory::CreateEffect(::EffectSource, ::Zone *, unsigned __int64, unsigned __int64, char, unsigned __int64, ::Data::EffectRecord const *) const
{
    LIFT_STUB(0x5b37f0);
}

// 0x5b3970
bool __cdecl EffectFactory::initEffect(::Effect *, ::EffectSource, ::Zone *, unsigned __int64, unsigned __int64, char, unsigned __int64, ::Data::EffectRecord const *, long, bool, ::SkillResult, ::ApplySkillModifyInfo *, short, ::vector16, short, short, ::vector16, char, ::TargetPart, unsigned __int64, unsigned __int64, bool, short, int, short, unsigned __int64, unsigned __int64, unsigned __int64, unsigned __int64) const
{
    LIFT_STUB(0x5b3970);
}

// 0x5b3d20
::EffectAttachFail __cdecl EffectFactory::InvokeEffect(::EffectSource, ::Zone *, unsigned __int64, unsigned __int64, char, unsigned __int64, ::Data::EffectRecord const *, long, bool, ::SkillResult, ::ApplySkillModifyInfo *, short, ::vector16, short, short, ::vector16, char, ::TargetPart, unsigned __int64, unsigned __int64, bool, short, int, short, unsigned __int64, unsigned __int64, unsigned __int64, unsigned __int64) const
{
    LIFT_STUB(0x5b3d20);
}

// 0x5b3ef0
::EffectAttachFail __cdecl EffectFactory::InvokeEffect(::EffectSource, ::Zone *, unsigned __int64, unsigned __int64, char, unsigned __int64, unsigned __int64, short, unsigned int) const
{
    LIFT_STUB(0x5b3ef0);
}

// 0x5b3ff0
::EffectAttachFail __cdecl EffectFactory::InvokeEffect(::EffectSource, ::Zone *, unsigned __int64, unsigned __int64, char, unsigned __int64, ::Data::EffectRecord const *, short, unsigned int) const
{
    LIFT_STUB(0x5b3ff0);
}

// 0x5b4180
::EffectAttachFail __cdecl EffectFactory::InvokeEffect(::EffectSource, ::Zone *, unsigned __int64, unsigned __int64, char, unsigned __int64, unsigned __int64, long) const
{
    LIFT_STUB(0x5b4180);
}

// 0x5b4250
::EffectAttachFail __cdecl EffectFactory::InvokeEffect(::EffectSource, ::Zone *, unsigned __int64, unsigned __int64, char, unsigned __int64, ::Data::EffectRecord const *, long) const
{
    LIFT_STUB(0x5b4250);
}

// 0x5b4410
::EffectAttachFail __cdecl EffectFactory::InvokeEffect(::EffectSource, ::Zone *, unsigned __int64, unsigned __int64, char, unsigned __int64, ::Data::EffectRecord const *, bool, ::SkillResult, ::ApplySkillModifyInfo *, short, ::vector16, short, short) const
{
    LIFT_STUB(0x5b4410);
}

// 0x5b45d0
::EffectAttachFail __cdecl EffectFactory::InvokeEffect(::EffectSource, ::Zone *, unsigned __int64, unsigned __int64, char, unsigned __int64, unsigned __int64, ::vector16, char, ::TargetPart, unsigned __int64, unsigned __int64) const
{
    LIFT_STUB(0x5b45d0);
}

// 0x5b46d0
::EffectAttachFail __cdecl EffectFactory::InvokeEffect(::EffectSource, ::Zone *, unsigned __int64, unsigned __int64, char, unsigned __int64, ::Data::EffectRecord const *, ::vector16, char, ::TargetPart, unsigned __int64, unsigned __int64) const
{
    LIFT_STUB(0x5b46d0);
}

// 0x5b4870
#pragma comment(linker, "/INCLUDE:??0EffectList@@QEAA@XZ")  // LIFT: dead-strip keep (no live caller yet)
__cdecl EffectList::EffectList(void)
{
    head = ::new (Memory::_Manager[2]->Alloc(sizeof(::EffectNode), EFFECT_FILE, 5924)) ::EffectNode;
    head->prev = head;
    head->next = NULL;
    head->effectData = NULL;
}

// 0x5b48d0
__cdecl EffectList::~EffectList(void)
{
    LIFT_STUB(0x5b48d0);
}

// 0x5b4910
void __cdecl EffectList::Insert(::PassiveEffect *)
{
    LIFT_STUB(0x5b4910);
}

// 0x5b4990
void __cdecl EffectList::Delete(::EffectNode *)
{
    LIFT_STUB(0x5b4990);
}

// 0x5b49f0
#pragma comment(linker, "/INCLUDE:?Clear@EffectList@@QEAAXXZ")  // LIFT: dead-strip keep (no live caller yet)
void __cdecl EffectList::Clear(void)
{
    ::EffectNode* node = head->next;
    while (node != NULL)
    {
        ::EffectNode* const next = node->next;
        node->effectData = NULL;
        node->prev = NULL;
        node->next = NULL;
        Memory::_Manager[2]->Free(node, EFFECT_FILE, 6031);
        node = next;
    }
    head->prev = head;
    head->next = NULL;
    head->effectData = NULL;
}

// 0x5b4aa0
void __cdecl EffectTimer::TimerExpired(unsigned int, long)
{
    LIFT_STUB(0x5b4aa0);
}
