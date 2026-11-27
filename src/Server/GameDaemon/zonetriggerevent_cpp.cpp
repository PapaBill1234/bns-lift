// zonetriggerevent_cpp.cpp: zonetriggerevent.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "zonetriggerevent.h"
#include "zone.h"
#include "LiftStub.h"

// 0x6820c0
__cdecl ZoneEventStage::ZoneEventStage(void)
{
    LIFT_STUB(0x6820c0);
}

// 0x6821f0
void __cdecl ZoneEventStage::despawnNpcGroup(::Zone *, ::Data::NpcResetStageRecordPtr const &) const
{
    LIFT_STUB(0x6821f0);
}

// 0x6822f0
void __cdecl ZoneEventStage::spawnNpcGroup(::Zone *, ::Data::NpcResetStageRecordPtr const &) const
{
    LIFT_STUB(0x6822f0);
}

// 0x682430
void __cdecl ZoneEventStage::doEnvOperation(::Zone *, ::Data::NpcResetStageRecordPtr const &) const
{
    LIFT_STUB(0x682430);
}

// 0x6825c0
void __cdecl ZoneEventStage::spawnNpcBySpawnIdRange(::Zone *, ::Data::NpcResetStageRecordPtr const &) const
{
    LIFT_STUB(0x6825c0);
}

// 0x682810
void __cdecl ZoneEventStage::despawnNpcBySpawnIdRange(::Zone *, ::Data::NpcResetStageRecordPtr const &) const
{
    LIFT_STUB(0x682810);
}

// 0x6829a0
bool __cdecl ZoneEventStage::SetupNextStage(::Zone *, char, char)
{
    LIFT_STUB(0x6829a0);
}

// 0x682ab0
bool __cdecl ZoneEventStage::SetupFailStage(::Zone *, char)
{
    LIFT_STUB(0x682ab0);
}

// 0x682ba0
bool __cdecl ZoneEventStageStandBy::Init(::Data::ZoneTriggerEventStageRecordPtr &)
{
    LIFT_STUB(0x682ba0);
}

// 0x682f30
bool __cdecl ZoneEventSingleStage::Init(char, ::Data::ZoneTriggerEventStageRecordStagePtr *const)
{
    LIFT_STUB(0x682f30);
}

// 0x6832d0
char __cdecl ZoneTriggerEvent::NextBranch(void)
{
    LIFT_STUB(0x6832d0);
}

// 0x683310
bool __cdecl ZoneTriggerWeeklyEvent::CheckEventCond(::Zone *, unsigned __int64)
{
    LIFT_STUB(0x683310);
}

// 0x683530
bool __cdecl ZoneTriggerTimeoutEvent::CheckEventCond(::Zone *, unsigned __int64)
{
    LIFT_STUB(0x683530);
}

// 0x683620
bool __cdecl ZoneTriggerNpcKilledEvent::CheckEventCond(::Zone *, unsigned __int64)
{
    LIFT_STUB(0x683620);
}

// 0x6836d0
void __cdecl ZoneTriggerNpcKilledEvent::ResetContext(void)
{
    LIFT_STUB(0x6836d0);
}

// 0x683700
bool __cdecl ZoneTriggerNpcKilledEvent2::CheckEventCond(::Zone *, unsigned __int64)
{
    LIFT_STUB(0x683700);
}

// 0x683780
void __cdecl ZoneTriggerNpcKilledEvent2::ResetContext(void)
{
    LIFT_STUB(0x683780);
}

// 0x683790
bool __cdecl ZoneTriggerNpcSurvivedScoreDecisionTimeoutEvent::CheckEventCond(::Zone *, unsigned __int64)
{
    LIFT_STUB(0x683790);
}

// 0x683960
bool __cdecl ZoneTriggerNpcSurvivedScoreDecisionTimeoutEvent::checkScoreCond(::Zone *)
{
    LIFT_STUB(0x683960);
}

// 0x683a10
bool __cdecl ZoneTriggerNpcSurvivedTimeoutEvent::CheckEventCond(::Zone *, unsigned __int64)
{
    LIFT_STUB(0x683a10);
}

// 0x683ae0
bool __cdecl ZoneTriggerBossChallengeTimeoutEvent::CheckEventCond(::Zone *, unsigned __int64)
{
    LIFT_STUB(0x683ae0);
}

// 0x683bf0
bool __cdecl ZoneTriggerBossChallengeTimeoutEvent::PostExecute(::Zone *, bool &)
{
    LIFT_STUB(0x683bf0);
}

// 0x683c20
bool __cdecl ZoneTriggerBossChallengeRoundScoreEvent::CheckEventCond(::Zone *, unsigned __int64)
{
    LIFT_STUB(0x683c20);
}

// 0x683dd0
bool __cdecl ZoneTriggerBossChallengeRoundScoreEvent::PostExecute(::Zone *, bool &)
{
    LIFT_STUB(0x683dd0);
}

// 0x683e00
bool __cdecl ZoneTriggerBossChallengeBossNpcKilledEvent::CheckEventCond(::Zone *, unsigned __int64)
{
    LIFT_STUB(0x683e00);
}

// 0x683f20
bool __cdecl ZoneTriggerBossChallengeBossNpcKilledEvent::PostExecute(::Zone *, bool &)
{
    LIFT_STUB(0x683f20);
}

// 0x683fe0
bool __cdecl ZoneEventStageContext::InitEventStage(::ZoneEventStageManager *, ::ZoneEventStage *)
{
    LIFT_STUB(0x683fe0);
}

// 0x6842b0
::ZoneTriggerEvent * __cdecl ZoneEventStageContext::createEvent(::Data::ZoneTriggerEventCondRecordPtr const &)
{
    LIFT_STUB(0x6842b0);
}

// 0x684700
void __cdecl ZoneEventStageContext::SetZoneModeContext(::Zone const *)
{
    LIFT_STUB(0x684700);
}

// 0x684790
void __cdecl ZoneEventStageContext::onNextStageStarted(::Zone const *, ::ZoneTriggerEvent *)
{
    LIFT_STUB(0x684790);
}

// 0x684880
void __cdecl ZoneEventStageContext::onStageFinished(::Zone *)
{
    LIFT_STUB(0x684880);
}

// 0x684a20
void __cdecl ZoneEventStageContext::clear(void)
{
    LIFT_STUB(0x684a20);
}

// 0x684bf0
::ZoneTriggerEvent * __cdecl ZoneEventStageContext::CheckNextEvent(::Zone *, ::ZoneTriggerEvent::TriggerEvent, unsigned __int64)
{
    LIFT_STUB(0x684bf0);
}

// 0x684d00
::ZoneTriggerEvent * __cdecl ZoneEventStageContext::CheckFailEvent(::Zone *, ::ZoneTriggerEvent::TriggerEvent, unsigned __int64)
{
    LIFT_STUB(0x684d00);
}

// 0x684e10
bool __cdecl ZoneEventStageContext::SetupNextStage(::Zone *, ::ZoneEventStageContext *, ::ZoneTriggerEvent *, bool &)
{
    LIFT_STUB(0x684e10);
}

// 0x684fd0
bool __cdecl ZoneEventStageContext::SetupFailStage(::Zone *, ::ZoneEventStageContext *, unsigned __int64)
{
    LIFT_STUB(0x684fd0);
}

// 0x6851e0
__cdecl ZoneEventStageManager::~ZoneEventStageManager(void)
{
    LIFT_STUB(0x6851e0);
}

// 0x685290
bool __cdecl ZoneEventStageManager::Init(::Zone *)
{
    LIFT_STUB(0x685290);
}

// 0x685880
void __cdecl ZoneEventStageManager::SetTotalDurationTime(char)
{
    LIFT_STUB(0x685880);
}

// 0x685920
void __cdecl ZoneEventStageManager::SetTimer(::Zone *)
{
    LIFT_STUB(0x685920);
}

// 0x685b00
void __cdecl ZoneEventStageManager::HandleTriggerEvent(::Zone *, ::ZoneTriggerEvent::TriggerEvent, unsigned __int64)
{
    LIFT_STUB(0x685b00);
}

// 0x685e50
bool __cdecl ZoneEventStageManager::startNextStage(::Zone *, ::ZoneTriggerEvent *, bool &)
{
    LIFT_STUB(0x685e50);
}

// 0x6860f0
bool __cdecl ZoneEventStageManager::startFailStage(::Zone *, unsigned __int64)
{
    LIFT_STUB(0x6860f0);
}

// 0x6862e0
bool __cdecl ZoneEventStageManager::FetchZoneModeInfo(::FragmentPacket &)
{
    LIFT_STUB(0x6862e0);
}

// 0x686410
void __cdecl ZoneEventStageManager::writeDICLog(::Zone *, char, char, char, char)
{
    LIFT_STUB(0x686410);
}
