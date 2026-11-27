// npcdeadbody.h: npcdeadbody.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class NpcDeadBody
{
public:
    __cdecl NpcDeadBody(unsigned __int64);  // 0x423570
    virtual __cdecl ~NpcDeadBody(void);  // 0x423780
    bool __cdecl Initialize(unsigned __int64, bool, ::vector16, ::Zone *, unsigned __int64, unsigned __int64, unsigned __int64 *const, int, unsigned __int64, ::Npc *, unsigned __int64, unsigned __int64, unsigned __int64, unsigned __int64, unsigned __int64, unsigned __int64, unsigned __int64, unsigned __int64, unsigned __int64, unsigned __int64, unsigned __int64);  // 0x423820
    bool __cdecl Initialize(::Npc *, ::vector16, unsigned __int64, unsigned __int64, __int64, __int64, ::Data::ContributionRewardRecordPtr const &, int);  // 0x424330
    void __cdecl Spawn(void);  // 0x424790
    bool __cdecl CheckDeadBodyFieldItem(::Pc *);  // 0x424890
    bool __cdecl CreateDeadBodyFieldItem(::Pc *);  // 0x4248e0
    virtual void __cdecl OnTimer(::Zone *, unsigned short);  // 0x4249e0
    bool __cdecl CheckAuth(::Pc *);  // 0x424a10
    bool __cdecl CheckAuthContribution(::Pc *);  // 0x424c20
    bool __cdecl LootQuestCase(::Pc *, unsigned short, char, char, ::LootFailReason &);  // 0x424cb0
    bool __cdecl UpdateItemPouch(void);  // 0x425300
    void __cdecl FetchExceptLootCase(::FragmentPacket *);  // 0x4253c0
    void __cdecl FetchDistributionAuthorities(::Packet *);  // 0x425540
private:
    void __cdecl hide(void);  // 0x4256f0
    void __cdecl decompose(void);  // 0x4257b0
    void __cdecl setRemainDuration(void);  // 0x425850
    ::Pointer2< ::Creature> __cdecl getPcInAuthorizedList(void);  // 0x4258d0
    void __cdecl makeItemPouch(void);  // 0x425c10
    bool __cdecl contributionRewardRangeCheckEnabled(::Npc *);  // 0x4271a0
    void __cdecl distributeContributionReward(__int64, __int64, unsigned __int64 *const, int);  // 0x427210
    void __cdecl distributeGuildContributionReward(bool, __int64, __int64);  // 0x4275c0
    void __cdecl addTakeFactionScoreBroadcast(int, unsigned __int64 *const, int *const, int *const);  // 0x427cd0
    void __cdecl setQuestLootItemProb(unsigned __int64 *const, int, bool);  // 0x428120
};

class NpcDeadBodyIdManager
{
protected:
    virtual bool __cdecl IsExist(unsigned __int64);  // 0x423550
};

class NpcDeadBodyList
{
public:
    __cdecl ~NpcDeadBodyList(void);  // 0x428830
    bool __cdecl Initialize(::Zone *, int);  // 0x4288f0
    ::NpcDeadBody * __cdecl Create(void);  // 0x4289a0
    bool __cdecl Remove(unsigned __int64);  // 0x428b10
};

