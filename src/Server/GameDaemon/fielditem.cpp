// fielditem.cpp: fielditem.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "fielditem.h"
#include "creature.h"
#include "zone.h"
#include "Daemon.h"
#include "LiftStub.h"

#pragma comment(linker, "/INCLUDE:?IsExist@FieldItemIdManager@@MEAA_N_K@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetRemainedDecomposition@FieldItem@@QEBA_JXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetRemainedExplosion@FieldItem@@QEBA_JXZ")  // LIFT: dead-strip keep (no live caller yet)

namespace
{
// LIFT: view of the PDB class FieldItemIdManager (size 0x48). The skeleton class has no members yet.
struct FieldItemIdManagerView
{
    char lift_pad_0[0x38];
    ::Zone const * Zone;  // +56 (0x38)
};

// LIFT: view of the PDB class FieldItem. The skeleton class has no members yet.
struct FieldItemView
{
    char lift_pad_0[0x40];
    long remainedDecomposition;  // +64 (0x40)
    long remainedExplosion;      // +68 (0x44)
    __int64 droppedTime;         // +72 (0x48)
    __int64 activatedTime;       // +80 (0x50)
};
}

// 0x5a06b0
bool __cdecl FieldItemIdManager::IsExist(unsigned __int64 id)
{
    ::Zone const *zone = reinterpret_cast<FieldItemIdManagerView *>(this)->Zone;
    return reinterpret_cast<::ZoneMemberView const *>(zone)->fieldItemList->Get(id) != nullptr;
}

// 0x5a0700
__cdecl FieldItem::FieldItem(unsigned __int64)
{
    LIFT_STUB(0x5a0700);
}

// 0x5a07f0
__cdecl FieldItem::~FieldItem(void)
{
    LIFT_STUB(0x5a07f0);
}

// 0x5a0870
bool __cdecl FieldItem::Initialize(unsigned __int64, unsigned int, ::vector16, ::Zone *, unsigned __int64)
{
    LIFT_STUB(0x5a0870);
}

// 0x5a0a90
__int64 __cdecl FieldItem::GetRemainedDecomposition(void) const
{
    FieldItemView const *self = reinterpret_cast<FieldItemView const *>(this);
    __int64 now = GetTickCount64() - Daemon::Instance->StartSystemTick64;
    __int64 remained = self->remainedDecomposition - (now - self->droppedTime) / 100 * 100;
    if (remained < 0)
        return 0;
    return remained;
}

// 0x5a0af0
__int64 __cdecl FieldItem::GetRemainedExplosion(void) const
{
    FieldItemView const *self = reinterpret_cast<FieldItemView const *>(this);
    __int64 now = GetTickCount64() - Daemon::Instance->StartSystemTick64;
    __int64 remained = self->remainedExplosion - (now - self->activatedTime) / 100 * 100;
    if (remained < 0)
        return 0;
    return remained;
}

// 0x5a0b50
bool __cdecl FieldItem::Create(unsigned __int64)
{
    LIFT_STUB(0x5a0b50);
}

// 0x5a0d90
bool __cdecl FieldItem::Spawn(void)
{
    LIFT_STUB(0x5a0d90);
}

// 0x5a0e70
bool __cdecl FieldItem::Pickup(unsigned __int64)
{
    LIFT_STUB(0x5a0e70);
}

// 0x5a1180
bool __cdecl FieldItem::Drop(::FieldItemDropState, ::vector16)
{
    LIFT_STUB(0x5a1180);
}

// 0x5a1440
bool __cdecl FieldItem::Drop(::FieldItemDropState)
{
    LIFT_STUB(0x5a1440);
}

// 0x5a1600
bool __cdecl FieldItem::consumeUseCount(short)
{
    LIFT_STUB(0x5a1600);
}

// 0x5a16b0
bool __cdecl FieldItem::Use(char)
{
    LIFT_STUB(0x5a16b0);
}

// 0x5a1760
bool __cdecl FieldItem::PrepareThrow(::vector16)
{
    LIFT_STUB(0x5a1760);
}

// 0x5a1830
bool __cdecl FieldItem::Throw(void)
{
    LIFT_STUB(0x5a1830);
}

// 0x5a1a50
bool __cdecl FieldItem::checkTargetState(unsigned __int64, ::Creature *, ::Data::SkillTargetStateType)
{
    LIFT_STUB(0x5a1a50);
}

// 0x5a1c70
void __cdecl FieldItem::OnTimer(::Zone *, unsigned short)
{
    LIFT_STUB(0x5a1c70);
}

// 0x5a1cb0
void __cdecl FieldItem::Remove(char)
{
    LIFT_STUB(0x5a1cb0);
}

// 0x5a1e00
bool __cdecl FieldItem::activate(unsigned __int64)
{
    LIFT_STUB(0x5a1e00);
}

// 0x5a2020
bool __cdecl FieldItem::explode(void)
{
    LIFT_STUB(0x5a2020);
}

// 0x5a22e0
bool __cdecl FieldItem::invokeThrowEffect(::Creature *)
{
    LIFT_STUB(0x5a22e0);
}

// 0x5a2520
bool __cdecl FieldItem::invokeEffect(::Creature *, unsigned __int64)
{
    LIFT_STUB(0x5a2520);
}

// 0x5a25a0
bool __cdecl FieldItem::checkTargetStateFilter(::Creature *, unsigned __int64) const
{
    LIFT_STUB(0x5a25a0);
}

// 0x5a26b0
__cdecl FieldItemList::~FieldItemList(void)
{
    LIFT_STUB(0x5a26b0);
}

// 0x5a2830
bool __cdecl FieldItemList::Initialize(::Zone *, int)
{
    LIFT_STUB(0x5a2830);
}

// 0x5a2920
::FieldItem * __cdecl FieldItemList::CreateFieldItem(void)
{
    LIFT_STUB(0x5a2920);
}

// 0x5a29d0
bool __cdecl FieldItemList::Remove(unsigned __int64)
{
    LIFT_STUB(0x5a29d0);
}

// 0x5a2ac0
bool __cdecl FieldItemList::RemoveAll(void)
{
    LIFT_STUB(0x5a2ac0);
}
