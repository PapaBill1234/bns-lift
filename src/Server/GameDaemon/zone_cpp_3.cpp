// zone_cpp_3.cpp: zone.cpp part 3 (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "zone.h"
#include "action.h"
#include "attractionstate.h"
#include "battleroyalfield.h"
#include "controlledcreature.h"
#include "creature.h"
#include "gameobject.h"
#include "geoworld.h"
#include "pc.h"
#include "publicraid.h"
#include "zonebroadcast.h"
#include "zonenpcspawnevent.h"
#include "zoneserializedobject.h"
#include "zonescore.h"
#include "Memory.h"
#include "LiftStub.h"
#include <time.h>

#define ZONE_FILE L"e:\\dailybuild02\\gamedaemon-common-0.0.348\\depot\\branch\\348nc\\program\\server\\gamedaemon\\Zone.cpp"

#pragma comment(linker, "/INCLUDE:?GetZoneScore@Zone@@QEAAHD@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?Initialize@ZoneWaitingPcList@@QEAA_NH@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?Find@ZoneWaitingPcList@@QEAA_NPEAVPc@@@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetCount@ZoneWaitingPcList@@QEAAIXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?EndZsoTest@ZonePerfMonitor@@QEAAXH@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?HandleNpcSpawnEvent@Zone@@QEAAXW4SpawnEvent@ZoneNpcSpawnEvent@@_K@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetDuelAttractionState@Zone@@QEAAPEAVDuelAttractionState@@XZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetPartyBattleFieldAttractionState@Zone@@QEAAPEAVPartyBattleFieldAttractionState@@XZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetPublicRaid@Zone@@QEAAPEAVPublicRaid@@XZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetEnterPublicRaidAttractionState@Zone@@QEAAPEAVEnterPublicRaidAttractionState@@XZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetBattleRoyalFieldAttractionState@Zone@@QEAAPEAVBattleRoyalField@@XZ")  // LIFT: dead-strip keep (no live caller yet)

// 0x24aef0
void __cdecl Zone::updateCreatureProperty(void)
{
    LIFT_STUB(0x24aef0);
}

// 0x24b480
void __cdecl Zone::moveTo(::Creature *, int, int)
{
    LIFT_STUB(0x24b480);
}

// 0x24bc60
void __cdecl Zone::checkLifeTime(void)
{
    LIFT_STUB(0x24bc60);
}

// 0x24bf70
void __cdecl Zone::syncObjectData(void)
{
    LIFT_STUB(0x24bf70);
}

// 0x24c350
void __cdecl Zone::clearBroadcastPacket(void)
{
    LIFT_STUB(0x24c350);
}

// 0x24c610
void __cdecl Zone::makeEnterLeavePacket(::BroadcastPacketType)
{
    LIFT_STUB(0x24c610);
}

// 0x24c6f0
void __cdecl Zone::makeLeavePacket(::BroadcastPacketType)
{
    LIFT_STUB(0x24c6f0);
}

// 0x24c900
void __cdecl Zone::makeEnterPacket(::BroadcastPacketType)
{
    LIFT_STUB(0x24c900);
}

// 0x24d190
int __cdecl Zone::makeInZoneCreaturePacket(::BroadcastPacketType)
{
    LIFT_STUB(0x24d190);
}

// 0x24e710
void __cdecl Zone::makeCubeSyncPacket(::BroadcastPacketType)
{
    LIFT_STUB(0x24e710);
}

// 0x24ee60
void __cdecl Zone::makeOutOfSightPacket(::ZoneBroadcastCube *, ::BroadcastPacketType)
{
    LIFT_STUB(0x24ee60);
}

// 0x24f1f0
void __cdecl Zone::makeEncounterPacket(::ZoneBroadcastCube *, ::BroadcastPacketType)
{
    LIFT_STUB(0x24f1f0);
}

// 0x24f730
int __cdecl Zone::makeInCubeCreaturePacket(::ZoneBroadcastCube *, ::BroadcastPacketType)
{
    LIFT_STUB(0x24f730);
}

// 0x24fcf0
int __cdecl Zone::makeOutCubeCreaturePacket(::ZoneBroadcastCube *, ::BroadcastPacketType)
{
    LIFT_STUB(0x24fcf0);
}

// 0x2500f0
void __cdecl Zone::makeEnvObjectPacket(::ZoneBroadcastCube *, ::BroadcastPacketType)
{
    LIFT_STUB(0x2500f0);
}

// 0x2502b0
void __cdecl Zone::makeFieldItemPacket(::ZoneBroadcastCube *, ::BroadcastPacketType)
{
    LIFT_STUB(0x2502b0);
}

// 0x250520
void __cdecl Zone::makeGatherSourcePacket(::ZoneBroadcastCube *, ::BroadcastPacketType)
{
    LIFT_STUB(0x250520);
}

// 0x250660
void __cdecl Zone::makeNpcDeadBodyPacket(::ZoneBroadcastCube *, ::BroadcastPacketType)
{
    LIFT_STUB(0x250660);
}

// 0x250930
void __cdecl Zone::makeHoldingFieldItemPacket(::FragmentPacket *, ::BroadcastPacketType)
{
    LIFT_STUB(0x250930);
}

// 0x250c40
void __cdecl Zone::makeCampfirePacket(::ZoneBroadcastCube *, ::BroadcastPacketType)
{
    LIFT_STUB(0x250c40);
}

// 0x250e30
void __cdecl Zone::makeDroppedPouchPacket(::ZoneBroadcastCube *, ::BroadcastPacketType)
{
    LIFT_STUB(0x250e30);
}

// 0x250fe0
void __cdecl Zone::makeOutCubeEnvObjectPacket(::ZoneBroadcastCube *, ::BroadcastPacketType)
{
    LIFT_STUB(0x250fe0);
}

// 0x251150
void __cdecl Zone::makeOutCubeFieldItemPacket(::ZoneBroadcastCube *, ::BroadcastPacketType)
{
    LIFT_STUB(0x251150);
}

// 0x251270
void __cdecl Zone::makeOutCubeGatherSourcePacket(::ZoneBroadcastCube *, ::BroadcastPacketType)
{
    LIFT_STUB(0x251270);
}

// 0x2513a0
void __cdecl Zone::makeOutCubeNpcDeadBodyPacket(::ZoneBroadcastCube *, ::BroadcastPacketType)
{
    LIFT_STUB(0x2513a0);
}

// 0x2514c0
void __cdecl Zone::makeOutCubeCampfirePacket(::ZoneBroadcastCube *, ::BroadcastPacketType)
{
    LIFT_STUB(0x2514c0);
}

// 0x2515e0
void __cdecl Zone::makeOutCubeDroppedPouchPacket(::ZoneBroadcastCube *, ::BroadcastPacketType)
{
    LIFT_STUB(0x2515e0);
}

// 0x251700
void __cdecl Zone::clearList(void)
{
    LIFT_STUB(0x251700);
}

// 0x251980
void __cdecl Zone::clearLeaveList(void)
{
    LIFT_STUB(0x251980);
}

// 0x251c90
void __cdecl Zone::sendInZoneCreaturePacket(void)
{
    LIFT_STUB(0x251c90);
}

// 0x251f00
void __cdecl Zone::sendInCubeCreaturePacket(::ZoneBroadcastCube *)
{
    LIFT_STUB(0x251f00);
}

// 0x2521b0
void __cdecl Zone::sendOutCubeCreaturePacket(::ZoneBroadcastCube *)
{
    LIFT_STUB(0x2521b0);
}

// 0x252460
void __cdecl Zone::broadcastSyncPacket(void)
{
    LIFT_STUB(0x252460);
}

// 0x2528c0
void __cdecl Zone::syncPropertyToDB(::Pc *, ::Packet &, ::RepeatPacketComposer &, int &)
{
    LIFT_STUB(0x2528c0);
}

// 0x252c30
void __cdecl Zone::syncPropertyToDB(void)
{
    LIFT_STUB(0x252c30);
}

// 0x253150
void __cdecl Zone::syncPropertyToGamed(::Pc *)
{
    LIFT_STUB(0x253150);
}

// 0x2532c0
void __cdecl Zone::syncPropertyToGamed(void)
{
    LIFT_STUB(0x2532c0);
}

// 0x253590
void __cdecl Zone::syncPropertyToDuelBotD(void)
{
    LIFT_STUB(0x253590);
}

// 0x255690
bool __cdecl Zone::Think(::ScriptEvent const *)
{
    LIFT_STUB(0x255690);
}

// 0x255700
void __cdecl Zone::SetTriggerEventTimer(long)
{
    LIFT_STUB(0x255700);
}

// 0x255770
void __cdecl Zone::SetAttractionTimer(long)
{
    LIFT_STUB(0x255770);
}

// 0x2557e0
void __cdecl Zone::SetAttractionEventTimer(long)
{
    LIFT_STUB(0x2557e0);
}

// 0x255850
void __cdecl Zone::OnOpen(void)
{
    LIFT_STUB(0x255850);
}

// 0x255930
void __cdecl Zone::OnTimer(::Zone *, unsigned short)
{
    LIFT_STUB(0x255930);
}

// 0x255d20
void __cdecl Zone::doZoneRuleTimer(void)
{
    LIFT_STUB(0x255d20);
}

// 0x256030
void __cdecl Zone::OnEnterZone(::Pc *)
{
    LIFT_STUB(0x256030);
}

// 0x256260
void __cdecl Zone::OnKill(::ControlledCreature *, ::GameObject *, unsigned __int64)
{
    LIFT_STUB(0x256260);
}

// 0x256370
void __cdecl Zone::OnKilled(::ControlledCreature *, ::GameObject *, unsigned __int64)
{
    LIFT_STUB(0x256370);
}

// 0x256480
bool __cdecl Zone::FindCell(short, short, short, short, ::GeoCell &) const
{
    LIFT_STUB(0x256480);
}

// 0x256500
bool __cdecl Zone::FindCell(short, short, short, ::GeoCell &) const
{
    LIFT_STUB(0x256500);
}

// 0x256570
int __cdecl Zone::InvokeEffectToAllPc(unsigned __int64)
{
    LIFT_STUB(0x256570);
}

// 0x2567d0
void __cdecl Zone::HandleNpcSpawnEvent(::ZoneNpcSpawnEvent::SpawnEvent e, unsigned __int64 dataKey)
{
    ZoneNpcSpawnEventManagerView *npcSpawnEventManager = liftZoneView(this)->_npcSpawnEventManager;
    if (npcSpawnEventManager != nullptr)
        npcSpawnEventManager->HandleNpcSpawnEvent(this, e, dataKey);
}

// 0x256830
bool const __cdecl Zone::IsJumpingTutorialZone(char, char) const
{
    LIFT_STUB(0x256830);
}

// 0x2568a0
bool __cdecl Zone::PostZSO(::ZoneSerializedObject *)
{
    LIFT_STUB(0x2568a0);
}

// 0x256990
bool __cdecl Zone::PostZSO2(::ZoneSerializedObject *, long)
{
    LIFT_STUB(0x256990);
}

// 0x256a70
bool __cdecl Zone::ExecuteZSO(::ZoneSerializedObject *)
{
    LIFT_STUB(0x256a70);
}

// 0x256ba0
bool __cdecl Zone::ExecuteZSOLast(::ZoneSerializedObject *)
{
    LIFT_STUB(0x256ba0);
}

// 0x256cd0
bool __cdecl Zone::AttachSimOperation(::Action *)
{
    LIFT_STUB(0x256cd0);
}

// 0x256ee0
void __cdecl Zone::ClearSimOperations(unsigned __int64)
{
    LIFT_STUB(0x256ee0);
}

// 0x256f90
char __cdecl Zone::GetSimOpSlotId(void)
{
    LIFT_STUB(0x256f90);
}

// 0x2570b0
bool __cdecl Zone::CanResurrect(::Pc *)
{
    LIFT_STUB(0x2570b0);
}

// 0x257140
void __cdecl Zone::increaseMainFactionPcCount(char)
{
    LIFT_STUB(0x257140);
}

// 0x2573d0
void __cdecl Zone::decreaseMainFactionPcCount(char)
{
    LIFT_STUB(0x2573d0);
}

// 0x257640
void __cdecl Zone::OnDamagedEvent(::ControlledCreature *const, ::Creature *, __int64)
{
    LIFT_STUB(0x257640);
}

// 0x2577b0
bool __cdecl Zone::IsAllowInvitePartyInArena(void)
{
    LIFT_STUB(0x2577b0);
}

// 0x257830
int __cdecl Zone::GetMainFactionPcCount(char)
{
    LIFT_STUB(0x257830);
}

// 0x257960
void __cdecl Zone::CheckAndEnableGuildBattleFieldGate(void)
{
    LIFT_STUB(0x257960);
}

// 0x257ad0
::DuelAttractionState * __cdecl Zone::GetDuelAttractionState(void)
{
    AttractionStateView *attractionState = liftZoneView(this)->_attractionState;
    if (attractionState != nullptr && attractionState->GetType() == ATTRACTION_STATE_TYPE_DUEL)
        return reinterpret_cast< ::DuelAttractionState *>(liftZoneView(this)->_attractionState);
    return nullptr;
}

// 0x257b10
::PartyBattleFieldAttractionState * __cdecl Zone::GetPartyBattleFieldAttractionState(void)
{
    AttractionStateView *attractionState = liftZoneView(this)->_attractionState;
    if (attractionState != nullptr && attractionState->GetType() == ATTRACTION_STATE_TYPE_PARTYBATTLE)
        return reinterpret_cast< ::PartyBattleFieldAttractionState *>(liftZoneView(this)->_attractionState);
    return nullptr;
}

// 0x257b50
::PublicRaid * __cdecl Zone::GetPublicRaid(void)
{
    AttractionStateView *attractionState = liftZoneView(this)->_attractionState;
    if (attractionState != nullptr && attractionState->GetType() == ATTRACTION_STATE_TYPE_PUBLIC_RAID)
        return reinterpret_cast< ::PublicRaid *>(liftZoneView(this)->_attractionState);
    return nullptr;
}

// 0x257b90
::EnterPublicRaidAttractionState * __cdecl Zone::GetEnterPublicRaidAttractionState(void)
{
    if (liftZoneView(this)->_attractionState != nullptr
        && liftZoneView(this)->_attractionState->IsEnterPublicRaidAttractionState())
        return reinterpret_cast< ::EnterPublicRaidAttractionState *>(liftZoneView(this)->_attractionState);
    return nullptr;
}

// 0x257bd0
::BattleRoyalField * __cdecl Zone::GetBattleRoyalFieldAttractionState(void)
{
    AttractionStateView *attractionState = liftZoneView(this)->_attractionState;
    if (attractionState != nullptr && attractionState->GetType() == ATTRACTION_STATE_TYPE_BATTLEROYAL_FIELD)
        return reinterpret_cast< ::BattleRoyalField *>(liftZoneView(this)->_attractionState);
    return nullptr;
}

// 0x257c10
void __cdecl Zone::UpdateZoneBroadcastBossNpcList(char, unsigned __int64, __int64, __int64)
{
    LIFT_STUB(0x257c10);
}

// 0x257db0
void __cdecl Zone::FetchInZoneAttractionState(::FragmentPacket &)
{
    LIFT_STUB(0x257db0);
}

// 0x257e60
void __cdecl Zone::FetchInZoneAttractionMemberState(::FragmentPacket &)
{
    LIFT_STUB(0x257e60);
}

// 0x257ef0
bool __cdecl Zone::GetGuildBattleFieldEntrance(::GeoZone const *, ::Data::FieldZoneRecordGuildBattleFieldEntrancePtr &)
{
    LIFT_STUB(0x257ef0);
}

// 0x257f70
void __cdecl Zone::MakeLeaveActionAllPc(bool)
{
    LIFT_STUB(0x257f70);
}

// 0x2582a0
bool __cdecl Zone::CheckActivatedGuildBattleField(void)
{
    LIFT_STUB(0x2582a0);
}

// 0x258340
void __cdecl Zone::ChangeZoneMode(char)
{
    LIFT_STUB(0x258340);
}

// 0x2585e0
void __cdecl Zone::ChangeEventZoneMode(char, char, short, __int64, bool)
{
    LIFT_STUB(0x2585e0);
}

// 0x258710
int __cdecl Zone::GetZoneScore(char scoreType)
{
    ::ZoneScore *score = liftZoneView(this)->_score;
    if (score == nullptr)
        return 0;
    return score->Score(scoreType);
}

// 0x258770
short __cdecl Zone::GetZoneTypeGameLog(void) const
{
    LIFT_STUB(0x258770);
}

// 0x2587e0
void __cdecl Zone::SetZRegVar(int, __int64)
{
    LIFT_STUB(0x2587e0);
}

// 0x258820
bool __cdecl Zone::InOutCreatureDetectStart(char, unsigned __int64, ::Data::ScriptDetectRefTypeType, unsigned __int64, unsigned __int64, short, long, short, unsigned __int64, unsigned __int64, unsigned __int64, unsigned __int64)
{
    LIFT_STUB(0x258820);
}

// 0x258920
__cdecl ZoneWaitingPcList::~ZoneWaitingPcList(void)
{
    LIFT_STUB(0x258920);
}

// 0x2589c0
bool __cdecl ZoneWaitingPcList::Initialize(int maxSize)
{
    this->maxSize = maxSize;
    count = 0;
    gmCount = 0;
    pcList = static_cast< ::Pc **>(
        Memory::_Manager[2]->AllocZero(sizeof(::Pc *) * (maxSize + 30), ZONE_FILE, 14736));
    pcId = static_cast<unsigned __int64 *>(
        Memory::_Manager[2]->AllocZero(sizeof(unsigned __int64) * (maxSize + 30), ZONE_FILE, 14738));
    pcRegisterTime = static_cast<__int64 *>(
        Memory::_Manager[2]->AllocZero(sizeof(__int64) * (maxSize + 30), ZONE_FILE, 14740));
    return true;
}

// 0x258a50
bool __cdecl ZoneWaitingPcList::Add(::Pc *, unsigned __int64)
{
    LIFT_STUB(0x258a50);
}

// 0x258d20
bool __cdecl ZoneWaitingPcList::DeleteInvalidPc(unsigned __int64)
{
    LIFT_STUB(0x258d20);
}

// 0x258f80
bool __cdecl ZoneWaitingPcList::Find(::Pc *pc)
{
    bool found = false;
    listLock.Enter();
    int total = count + gmCount;
    for (int i = 0; i < total; ++i)
    {
        if (pcList[i] == pc)
        {
            found = true;
            break;
        }
    }
    listLock.Leave();
    return found;
}

// 0x259000
bool __cdecl ZoneWaitingPcList::Remove(::Pc *, unsigned __int64)
{
    LIFT_STUB(0x259000);
}

// 0x2591d0
void __cdecl ZoneWaitingPcList::RemoveAll(void)
{
    LIFT_STUB(0x2591d0);
}

// 0x259340
unsigned int __cdecl ZoneWaitingPcList::GetCount(void)
{
    listLock.Enter();
    unsigned int result = count;
    listLock.Leave();
    return result;
}

// 0x2593a0
__cdecl ZonePerfMonitor::~ZonePerfMonitor(void)
{
    LIFT_STUB(0x2593a0);
}

// 0x259440
bool __cdecl ZonePerfMonitor::Initialize(::Zone const *, unsigned int)
{
    LIFT_STUB(0x259440);
}

// 0x2594e0
void __cdecl ZonePerfMonitor::End(bool, int, int, int, int, int, int, __int64, __int64, __int64, __int64, __int64, __int64)
{
    LIFT_STUB(0x2594e0);
}

// 0x2595e0
void __cdecl ZonePerfMonitor::Report(void)
{
    LIFT_STUB(0x2595e0);
}

// 0x259bb0
bool __cdecl ZonePerfMonitor::initialize(void)
{
    LIFT_STUB(0x259bb0);
}

// 0x259e40
bool __cdecl ZonePerfMonitor::initZoneCounter(void)
{
    LIFT_STUB(0x259e40);
}

// 0x259f90
void __cdecl ZonePerfMonitor::EndZsoTest(int zsoType)
{
    _zsoTestResult[zsoType].end = clock();
    __int64 elapsed = _zsoTestResult[zsoType].end - _zsoTestResult[zsoType].start;
    _zsoTestResult[zsoType].total += elapsed;
    if (_zsoTestResult[zsoType].max < elapsed)
        _zsoTestResult[zsoType].max = elapsed;
}

// 0x259ff0
unsigned char __cdecl Zone::GetPcBroadcastReceiverMask(unsigned __int64)
{
    LIFT_STUB(0x259ff0);
}
