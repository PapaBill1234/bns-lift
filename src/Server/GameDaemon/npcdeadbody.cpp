// npcdeadbody.cpp: npcdeadbody.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "npcdeadbody.h"
#include "creature.h"
#include "npc.h"
#include "pc.h"
#include "zone.h"
#include "LiftStub.h"

// 0x423550
bool __cdecl NpcDeadBodyIdManager::IsExist(unsigned __int64)
{
    LIFT_STUB(0x423550);
}

// 0x423570
__cdecl NpcDeadBody::NpcDeadBody(unsigned __int64)
{
    LIFT_STUB(0x423570);
}

// 0x423780
__cdecl NpcDeadBody::~NpcDeadBody(void)
{
    LIFT_STUB(0x423780);
}

// 0x423820
bool __cdecl NpcDeadBody::Initialize(unsigned __int64, bool, ::vector16, ::Zone *, unsigned __int64, unsigned __int64, unsigned __int64 *const, int, unsigned __int64, ::Npc *, unsigned __int64, unsigned __int64, unsigned __int64, unsigned __int64, unsigned __int64, unsigned __int64, unsigned __int64, unsigned __int64, unsigned __int64, unsigned __int64, unsigned __int64)
{
    LIFT_STUB(0x423820);
}

// 0x424330
bool __cdecl NpcDeadBody::Initialize(::Npc *, ::vector16, unsigned __int64, unsigned __int64, __int64, __int64, ::Data::ContributionRewardRecordPtr const &, int)
{
    LIFT_STUB(0x424330);
}

// 0x424790
void __cdecl NpcDeadBody::Spawn(void)
{
    LIFT_STUB(0x424790);
}

// 0x424890
bool __cdecl NpcDeadBody::CheckDeadBodyFieldItem(::Pc *)
{
    LIFT_STUB(0x424890);
}

// 0x4248e0
bool __cdecl NpcDeadBody::CreateDeadBodyFieldItem(::Pc *)
{
    LIFT_STUB(0x4248e0);
}

// 0x4249e0
void __cdecl NpcDeadBody::OnTimer(::Zone *, unsigned short)
{
    LIFT_STUB(0x4249e0);
}

// 0x424a10
bool __cdecl NpcDeadBody::CheckAuth(::Pc *)
{
    LIFT_STUB(0x424a10);
}

// 0x424c20
bool __cdecl NpcDeadBody::CheckAuthContribution(::Pc *)
{
    LIFT_STUB(0x424c20);
}

// 0x424cb0
bool __cdecl NpcDeadBody::LootQuestCase(::Pc *, unsigned short, char, char, ::LootFailReason &)
{
    LIFT_STUB(0x424cb0);
}

// 0x425300
bool __cdecl NpcDeadBody::UpdateItemPouch(void)
{
    LIFT_STUB(0x425300);
}

// 0x4253c0
void __cdecl NpcDeadBody::FetchExceptLootCase(::FragmentPacket *)
{
    LIFT_STUB(0x4253c0);
}

// 0x425540
void __cdecl NpcDeadBody::FetchDistributionAuthorities(::Packet *)
{
    LIFT_STUB(0x425540);
}

// 0x4256f0
void __cdecl NpcDeadBody::hide(void)
{
    LIFT_STUB(0x4256f0);
}

// 0x4257b0
void __cdecl NpcDeadBody::decompose(void)
{
    LIFT_STUB(0x4257b0);
}

// 0x425850
void __cdecl NpcDeadBody::setRemainDuration(void)
{
    LIFT_STUB(0x425850);
}

// 0x4258d0
::Pointer2< ::Creature> __cdecl NpcDeadBody::getPcInAuthorizedList(void)
{
    LIFT_STUB(0x4258d0);
}

// 0x425c10
void __cdecl NpcDeadBody::makeItemPouch(void)
{
    LIFT_STUB(0x425c10);
}

// 0x4271a0
bool __cdecl NpcDeadBody::contributionRewardRangeCheckEnabled(::Npc *)
{
    LIFT_STUB(0x4271a0);
}

// 0x427210
void __cdecl NpcDeadBody::distributeContributionReward(__int64, __int64, unsigned __int64 *const, int)
{
    LIFT_STUB(0x427210);
}

// 0x4275c0
void __cdecl NpcDeadBody::distributeGuildContributionReward(bool, __int64, __int64)
{
    LIFT_STUB(0x4275c0);
}

// 0x427cd0
void __cdecl NpcDeadBody::addTakeFactionScoreBroadcast(int, unsigned __int64 *const, int *const, int *const)
{
    LIFT_STUB(0x427cd0);
}

// 0x428120
void __cdecl NpcDeadBody::setQuestLootItemProb(unsigned __int64 *const, int, bool)
{
    LIFT_STUB(0x428120);
}

// 0x428830
__cdecl NpcDeadBodyList::~NpcDeadBodyList(void)
{
    LIFT_STUB(0x428830);
}

// 0x4288f0
bool __cdecl NpcDeadBodyList::Initialize(::Zone *, int)
{
    LIFT_STUB(0x4288f0);
}

// 0x4289a0
::NpcDeadBody * __cdecl NpcDeadBodyList::Create(void)
{
    LIFT_STUB(0x4289a0);
}

// 0x428b10
bool __cdecl NpcDeadBodyList::Remove(unsigned __int64)
{
    LIFT_STUB(0x428b10);
}
