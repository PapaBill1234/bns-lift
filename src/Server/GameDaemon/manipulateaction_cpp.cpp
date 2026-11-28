// manipulateaction_cpp.cpp: manipulateaction.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "manipulateaction.h"
#include "action.h"
#include "creature.h"
#include "envobj.h"
#include "item.h"
#include "pc.h"
#include "zone.h"
#include "LiftStub.h"

// 0x474d10
void __cdecl ManipulateAction::startAction(void)
{
    LIFT_STUB(0x474d10);
}

// 0x475440
void __cdecl ManipulateAction::failAction(::Action::FailReason)
{
    LIFT_STUB(0x475440);
}

// 0x475480
void __cdecl ManipulateAction::finishAction(void)
{
    LIFT_STUB(0x475480);
}

// 0x475ae0
void __cdecl ManipulateAction::cancelAction(::Action::CancelReason, wchar_t const *, int)
{
    LIFT_STUB(0x475ae0);
}

// 0x475c40
bool __cdecl ManipulateAction::checkRange(::Creature *, short &)
{
    LIFT_STUB(0x475c40);
}

// 0x475fa0
bool __cdecl ManipulateAction::getManipulationPoint(::Creature *, ::vector16 &)
{
    LIFT_STUB(0x475fa0);
}

// 0x476090
void __cdecl ManipulateAction::disposeItem(::Creature *, ::Item *)
{
    LIFT_STUB(0x476090);
}

// 0x476260
void __cdecl ManipulateAction::handleActionTarget(::Creature *, char, unsigned __int64)
{
    LIFT_STUB(0x476260);
}

// 0x4762d0
void __cdecl NpcManipulateAction::startAction(void)
{
    LIFT_STUB(0x4762d0);
}

// 0x476800
void __cdecl NpcManipulateAction::failAction(::Action::FailReason)
{
    LIFT_STUB(0x476800);
}

// 0x476830
void __cdecl NpcManipulateAction::finishAction(void)
{
    LIFT_STUB(0x476830);
}

// 0x476ad0
void __cdecl NpcManipulateAction::cancelAction(::Action::CancelReason, wchar_t const *, int)
{
    LIFT_STUB(0x476ad0);
}

// 0x476b60
void __cdecl GiveFactionScoreToRefinerAction::startAction(void)
{
    LIFT_STUB(0x476b60);
}

// 0x476d60
void __cdecl GiveFactionScoreToRefinerAction::failAction(::Action::FailReason)
{
    LIFT_STUB(0x476d60);
}

// 0x476d90
void __cdecl GiveFactionScoreToRefinerAction::finishAction(void)
{
    LIFT_STUB(0x476d90);
}

// 0x476fe0
void __cdecl GiveFactionScoreToRefinerAction::cancelAction(::Action::CancelReason, wchar_t const *, int)
{
    LIFT_STUB(0x476fe0);
}

// 0x477060
bool __cdecl TakeRefinerRewardTask::Initialize(::Zone *, ::Creature *, unsigned __int64)
{
    LIFT_STUB(0x477060);
}

// 0x4770f0
void __cdecl TakeRefinerRewardTask::start(void)
{
    LIFT_STUB(0x4770f0);
}

// 0x4771b0
void __cdecl FishManipulateAction::startAction(void)
{
    LIFT_STUB(0x4771b0);
}

// 0x4776b0
void __cdecl FishManipulateAction::failAction(::Action::FailReason)
{
    LIFT_STUB(0x4776b0);
}

// 0x4776f0
void __cdecl FishManipulateAction::finishAction(void)
{
    LIFT_STUB(0x4776f0);
}

// 0x477d80
void __cdecl FishManipulateAction::cancelAction(::Action::CancelReason, wchar_t const *, int)
{
    LIFT_STUB(0x477d80);
}

// 0x478070
void __cdecl FishManipulateAction::send(::Creature *, ::GameFailReason, short, int, ::FishInfoStatus)
{
    LIFT_STUB(0x478070);
}

// 0x478330
bool __cdecl FishManipulateAction::checkEnv(::Creature *, short &)
{
    LIFT_STUB(0x478330);
}

// 0x478450
bool __cdecl FishManipulateAction::checkItem(::Creature *, short &)
{
    LIFT_STUB(0x478450);
}

// 0x4786d0
bool __cdecl FishManipulateAction::checkFishingAvailability(::Creature *, short &)
{
    LIFT_STUB(0x4786d0);
}

// 0x478920
bool __cdecl FishManipulateAction::checkHooksetTime(::Creature *, ::GameLogEndFishingStatusCode &)
{
    LIFT_STUB(0x478920);
}

// 0x478aa0
bool __cdecl FishManipulateAction::checkDisposeFishingPaste(char)
{
    LIFT_STUB(0x478aa0);
}

// 0x478c00
bool __cdecl FishManipulateAction::checkContentQuota(::Creature *)
{
    LIFT_STUB(0x478c00);
}

// 0x478ce0
__int64 __cdecl FishManipulateAction::consumeContentQuota(::Creature *, char)
{
    LIFT_STUB(0x478ce0);
}

// 0x478e90
bool __cdecl FishManipulateAction::acquireLifeContentsPoint(::Creature *, short)
{
    LIFT_STUB(0x478e90);
}

// 0x479050
int __cdecl FishManipulateAction::decideFishRandomSize(int, int, unsigned __int64)
{
    LIFT_STUB(0x479050);
}

// 0x4791d0
// ❓ the skeleton has no names for the fail reason values; the values are from the binary. `this` is not used.
#pragma comment(linker, "/INCLUDE:?convertFailReason@FishManipulateAction@@AEAAFF@Z")  // LIFT: dead-strip keep (no live caller yet)
short __cdecl FishManipulateAction::convertFailReason(short failReason)
{
    switch (failReason)
    {
    case 219:
        return 664;
    case 220:
        return 665;
    case 223:
        return 666;
    case 226:
        return 667;
    case 639:
        return 656;
    case 640:
        return 657;
    case 650:
        return 659;
    }
    return failReason;
}

// 0x479230
short __cdecl ManipulateActionGameLog::GetFishingFieldId(::Env *)
{
    LIFT_STUB(0x479230);
}

// 0x479280
short __cdecl ManipulateActionGameLog::GetFishingPasteId(::Item *)
{
    LIFT_STUB(0x479280);
}

// 0x4792f0
void __cdecl ManipulateActionGameLog::WriteFishManipulationStart(::Pc *, ::Item *, short, short, __int64)
{
    LIFT_STUB(0x4792f0);
}

// 0x4794f0
void __cdecl ManipulateActionGameLog::WriteFishManipulationCancel(::Pc *, int, short, short, bool, __int64)
{
    LIFT_STUB(0x4794f0);
}

// 0x4796b0
void __cdecl ManipulateActionGameLog::WriteFishManipulationFinish(::Pc *, int, short, short, ::Data::FishRecordPtr, int, __int64, bool, char, __int64)
{
    LIFT_STUB(0x4796b0);
}

// 0x479920
void __cdecl ManipulateActionGameLog::WriteDisposeItem(::Pc *, int, __int64, short, short)
{
    LIFT_STUB(0x479920);
}
