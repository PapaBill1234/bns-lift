// brainboss_cpp.cpp: brainboss.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "brainboss.h"
#include "creature.h"
#include "npc.h"
#include "brainbase.h"
#include "LiftStub.h"

namespace
{
// LIFT: view of the PDB class BrainBoss (size 0x510, base BrainBase at +0). The skeleton class has no members yet.
struct BrainBossView
{
    ::BrainBaseMemberView base;                       // +0 (0x0)
    void *_boss;                                      // +160 (0xA0) BossNpc *
    char lift_pad_0[0x4D8 - 0xA8];
    unsigned __int64 _specialTargets[6];              // +1240 (0x4D8)
    char _specialRotateCount;                         // +1288 (0x508)
    int _BossHateListEmptiedState;                    // +1292 (0x50C) BrainBoss::BossHateListEmptiedType
};

const int BOSS_HATE_LIST_EMPTIED_STATE_READY = 0;     // LIFT: PDB enumerator BrainBoss::BOSS_HATE_LIST_EMPTIED_STATE_READY
}

// 0x7c740
__cdecl BrainBoss::BrainBoss(::Npc &)
{
    LIFT_STUB(0x7c740);
}

// 0x7c9e0
bool __cdecl BrainBoss::Stop(void)
{
    LIFT_STUB(0x7c9e0);
}

// 0x7c9f0
#pragma comment(linker, "/INCLUDE:?InitSpecialState@BrainBoss@@UEAAXXZ")  // LIFT: dead-strip keep (no live caller yet)
void __cdecl BrainBoss::InitSpecialState(void)
{
    BrainBossView *self = reinterpret_cast<BrainBossView *>(this);
    for (int i = 0; i < 6; ++i)
        self->_specialTargets[i] = 0;
    self->_specialRotateCount = 0;
}

// 0x7ca30
void __cdecl BrainBoss::GatherSpecialTargets(char, char, bool, bool, char, bool, char)
{
    LIFT_STUB(0x7ca30);
}

// 0x7cdc0
void __cdecl BrainBoss::getNearSpecialTargets(::Creature **const, char, char)
{
    LIFT_STUB(0x7cdc0);
}

// 0x7cf80
void __cdecl BrainBoss::getFarSpecialTargets(::Creature **const, char, char)
{
    LIFT_STUB(0x7cf80);
}

// 0x7d140
void __cdecl BrainBoss::getMinHateSpecialTargets(::Creature **const, char, char)
{
    LIFT_STUB(0x7d140);
}

// 0x7d2e0
#pragma comment(linker, "/INCLUDE:?checkPCHateListEmptied@BrainBoss@@AEAA_NXZ")  // LIFT: dead-strip keep (no live caller yet)
bool __cdecl BrainBoss::checkPCHateListEmptied(void)
{
    BrainBossView *self = reinterpret_cast<BrainBossView *>(this);
    if (self->_boss == nullptr || self->_BossHateListEmptiedState != BOSS_HATE_LIST_EMPTIED_STATE_READY)
        return false;
    bool found = false;
    for (int i = 0; i < self->base._hateMax; ++i)
    {
        // LIFT: id type = high 16 bits of the creature id. ❓ PDB name of the inline id-type helper and of the values 1 and 2.
        unsigned short type = static_cast<unsigned short>(self->base._hates[i]._creatureId >> 48);
        if (type == 1 || type == 2)
        {
            found = true;
            break;
        }
    }
    return !found;
}

// 0x7d350
void __cdecl BrainBoss::fireEventHateListEmptied(void)
{
    LIFT_STUB(0x7d350);
}

// 0x7d4c0
bool __cdecl BrainBoss::ResetHateByTargetId(unsigned __int64, wchar_t const *)
{
    LIFT_STUB(0x7d4c0);
}

// 0x7d530
bool __cdecl BrainBoss::ResetHateByIndex(int, wchar_t const *)
{
    LIFT_STUB(0x7d530);
}

// 0x7d570
bool __cdecl BrainBoss::checkSpecialTargetCond(::Creature *, bool, bool, char, bool, char)
{
    LIFT_STUB(0x7d570);
}
