// zonebroadcast_cpp.cpp: zonebroadcast.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "zonebroadcast.h"
#include "creature.h"
#include "duelbot.h"
#include "geoworld.h"
#include "npc.h"
#include "pc.h"
#include "summoned.h"
#include "zone.h"
#include "LiftStub.h"

namespace
{
// LIFT: view of the PDB class ZoneBroadcastCube. Only the list heads that the lifted bodies use are declared.
struct ZoneBroadcastCubeView
{
    char lift_pad_0[0x90];               // ❓ no PDB name: ZoneBroadcastCube +0 to +0x8F are not declared here
    ::ZoneFieldItemNode *FieldItemHead;  // +144 (0x90)
    ::ZoneCampfireNode *CampfireHead;    // +152 (0x98)
};
}

#pragma comment(linker, "/INCLUDE:?AddToCube@ZoneFieldItemNode@@IEAA_NPEAVZoneBroadcastCube@@@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?AddToCube@ZoneCampfireNode@@IEAA_NPEAVZoneBroadcastCube@@@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?Clear@ZoneObjectIdList@@QEAAXXZ")  // LIFT: dead-strip keep (no live caller yet)

// 0x25a050
bool __cdecl ZoneCreatureNode::AddToCube(::ZoneBroadcastCube *)
{
    LIFT_STUB(0x25a050);
}

// 0x25a100
bool __cdecl ZoneCreatureNode::RemoveFromCube(void)
{
    LIFT_STUB(0x25a100);
}

// 0x25a1e0
bool __cdecl ZoneFieldItemNode::AddToCube(::ZoneBroadcastCube *cube)
{
    if (cube == nullptr)
        return false;

    ZoneBroadcastCubeView *const view = reinterpret_cast<ZoneBroadcastCubeView *>(cube);
    Cube = cube;
    Prev = nullptr;
    Next = view->FieldItemHead;
    if (view->FieldItemHead != nullptr)
        view->FieldItemHead->Prev = this;
    reinterpret_cast<ZoneBroadcastCubeView *>(Cube)->FieldItemHead = this;
    return true;
}

// 0x25a230
bool __cdecl ZoneFieldItemNode::RemoveFromCube(void)
{
    LIFT_STUB(0x25a230);
}

// 0x25a2a0
bool __cdecl ZoneCampfireNode::AddToCube(::ZoneBroadcastCube *cube)
{
    if (cube == nullptr)
        return false;

    ZoneBroadcastCubeView *const view = reinterpret_cast<ZoneBroadcastCubeView *>(cube);
    Cube = cube;
    Prev = nullptr;
    Next = view->CampfireHead;
    if (view->CampfireHead != nullptr)
        view->CampfireHead->Prev = this;
    reinterpret_cast<ZoneBroadcastCubeView *>(Cube)->CampfireHead = this;
    return true;
}

// 0x25a2f0
__cdecl ZoneObjectIdList::~ZoneObjectIdList(void)
{
    LIFT_STUB(0x25a2f0);
}

// 0x25a3b0
void __cdecl ZoneObjectIdList::Add(unsigned __int64, char, __int64, unsigned char)
{
    LIFT_STUB(0x25a3b0);
}

// 0x25a430
void __cdecl ZoneObjectIdList::Clear(void)
{
    for (unsigned int i = 0; i < Count; ++i)
    {
        Ids[i] = 0;
        Datas[i] = 0;
        Datas2[i] = 0;
        Datas3[i] = 0;
    }
    Count = 0;
}

// 0x25a480
void __cdecl ZoneObjectIdList::grow(void)
{
    LIFT_STUB(0x25a480);
}

// 0x25a6c0
__cdecl ZoneBroadcastCube::ZoneBroadcastCube(::GeoCube const *)
{
    LIFT_STUB(0x25a6c0);
}

// 0x25aa40
__cdecl ZoneBroadcastCube::~ZoneBroadcastCube(void)
{
    LIFT_STUB(0x25aa40);
}

// 0x25ac50
__cdecl ZoneCreatureList::ZoneCreatureList(::Zone const *)
{
    LIFT_STUB(0x25ac50);
}

// 0x25ade0
__cdecl ZoneCreatureList::~ZoneCreatureList(void)
{
    LIFT_STUB(0x25ade0);
}

// 0x25af40
::ZoneCreatureNode * __cdecl ZoneCreatureList::Add(::Creature *)
{
    LIFT_STUB(0x25af40);
}

// 0x25b060
::ZoneCreatureNode * __cdecl ZoneCreatureList::AddPc(::Pc *)
{
    LIFT_STUB(0x25b060);
}

// 0x25b300
::ZoneCreatureNode * __cdecl ZoneCreatureList::AddNpc(::Npc *)
{
    LIFT_STUB(0x25b300);
}

// 0x25b6b0
::ZoneCreatureNode * __cdecl ZoneCreatureList::AddDuelBot(::DuelBot *)
{
    LIFT_STUB(0x25b6b0);
}

// 0x25b8d0
::ZoneCreatureNode * __cdecl ZoneCreatureList::AddSummoned(::Summoned *)
{
    LIFT_STUB(0x25b8d0);
}

// 0x25bb50
::ZoneCreatureNode * __cdecl ZoneCreatureList::AddDuelBotSummoned(::DuelBotSummoned *)
{
    LIFT_STUB(0x25bb50);
}

// 0x25bd70
bool __cdecl ZoneCreatureList::Remove(unsigned __int64)
{
    LIFT_STUB(0x25bd70);
}

// 0x25be80
bool __cdecl ZoneCreatureList::RemovePc(unsigned __int64)
{
    LIFT_STUB(0x25be80);
}

// 0x25bf40
bool __cdecl ZoneCreatureList::RemoveNpc(unsigned __int64)
{
    LIFT_STUB(0x25bf40);
}

// 0x25c090
bool __cdecl ZoneCreatureList::RemoveDuelBot(unsigned __int64)
{
    LIFT_STUB(0x25c090);
}

// 0x25c1a0
bool __cdecl ZoneCreatureList::RemoveSummoned(unsigned __int64)
{
    LIFT_STUB(0x25c1a0);
}

// 0x25c270
bool __cdecl ZoneCreatureList::RemoveDuelBotSummoned(unsigned __int64)
{
    LIFT_STUB(0x25c270);
}

// 0x25c380
void __cdecl ZoneCreatureList::RemoveAll(void)
{
    LIFT_STUB(0x25c380);
}

// 0x25c6a0
void __cdecl ZoneCreatureList::fetchPcLocInfo(::FragmentPacket &)
{
    LIFT_STUB(0x25c6a0);
}

// 0x25c800
::ZoneCreatureNode * __cdecl ZoneCreatureList::find(unsigned __int64) const
{
    LIFT_STUB(0x25c800);
}

// 0x25c9f0
bool __cdecl ZoneCubeMigratorList::AddToCube(::ZoneCreatureNode *)
{
    LIFT_STUB(0x25c9f0);
}
