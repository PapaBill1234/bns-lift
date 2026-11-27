// moveaction_cpp.cpp: moveaction.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "moveaction.h"
#include "action.h"
#include "controlledcreature.h"
#include "creature.h"
#include "zone.h"
#include "LiftStub.h"

// 0x47aca0
void __cdecl KnockBackAction::startAction(void)
{
    LIFT_STUB(0x47aca0);
}

// 0x47acc0
bool __cdecl AirDashAction::Initialize(::Zone *, ::Creature *, unsigned __int64)
{
    LIFT_STUB(0x47acc0);
}

// 0x47ad80
bool __cdecl AirDashAction::prepareAction(void)
{
    LIFT_STUB(0x47ad80);
}

// 0x47af10
void __cdecl AirDashAction::startAction(void)
{
    LIFT_STUB(0x47af10);
}

// 0x47b480
bool __cdecl WarpAction::prepareAction(void)
{
    LIFT_STUB(0x47b480);
}

// 0x47b580
void __cdecl WarpAction::startAction(void)
{
    LIFT_STUB(0x47b580);
}

// 0x47c010
void __cdecl WarpAction::adjustZ(::GeoCell)
{
    LIFT_STUB(0x47c010);
}

// 0x47c0d0
bool __cdecl WarpToGuildMemberAction::prepareAction(void)
{
    LIFT_STUB(0x47c0d0);
}

// 0x47c6b0
void __cdecl WarpToGuildMemberAction::startAction(void)
{
    LIFT_STUB(0x47c6b0);
}

// 0x47c7b0
void __cdecl WarpToGuildMemberAction::finishAction(void)
{
    LIFT_STUB(0x47c7b0);
}

// 0x47cba0
void __cdecl WarpToGuildMemberAction::cancelAction(::Action::CancelReason, wchar_t const *, int)
{
    LIFT_STUB(0x47cba0);
}

// 0x47cc20
void __cdecl WarpToGuildMemberAction::failAction(::Action::FailReason)
{
    LIFT_STUB(0x47cc20);
}

// 0x47cc50
bool __cdecl WarpToGuildMemberAction::checkConsumeItem(void)
{
    LIFT_STUB(0x47cc50);
}

// 0x47ce60
::GameFailReason __cdecl WarpToGuildMemberAction::checkCasterCond(void)
{
    LIFT_STUB(0x47ce60);
}

// 0x47d240
::GameFailReason __cdecl WarpToGuildMemberAction::checkTargetCond(void)
{
    LIFT_STUB(0x47d240);
}

// 0x47d630
bool __cdecl CallGuildMemberAction::prepareAction(void)
{
    LIFT_STUB(0x47d630);
}

// 0x47dad0
void __cdecl CallGuildMemberAction::startAction(void)
{
    LIFT_STUB(0x47dad0);
}

// 0x47dbb0
void __cdecl CallGuildMemberAction::finishAction(void)
{
    LIFT_STUB(0x47dbb0);
}

// 0x47e0c0
void __cdecl CallGuildMemberAction::cancelAction(::Action::CancelReason, wchar_t const *, int)
{
    LIFT_STUB(0x47e0c0);
}

// 0x47e140
void __cdecl CallGuildMemberAction::failAction(::Action::FailReason)
{
    LIFT_STUB(0x47e140);
}

// 0x47e170
bool __cdecl CallGuildMemberAction::checkConsumeItem(void)
{
    LIFT_STUB(0x47e170);
}

// 0x47e380
bool __cdecl CallGuildMemberAction::disposeItem(void)
{
    LIFT_STUB(0x47e380);
}

// 0x47e4a0
::GameFailReason __cdecl CallGuildMemberAction::checkCasterCond(void)
{
    LIFT_STUB(0x47e4a0);
}

// 0x47e7c0
bool __cdecl WarpToGuildMeetingPlaceAction::prepareAction(void)
{
    LIFT_STUB(0x47e7c0);
}

// 0x47eea0
void __cdecl WarpToGuildMeetingPlaceAction::startAction(void)
{
    LIFT_STUB(0x47eea0);
}

// 0x47ef80
void __cdecl WarpToGuildMeetingPlaceAction::finishAction(void)
{
    LIFT_STUB(0x47ef80);
}

// 0x47f210
void __cdecl WarpToGuildMeetingPlaceAction::cancelAction(::Action::CancelReason, wchar_t const *, int)
{
    LIFT_STUB(0x47f210);
}

// 0x47f290
void __cdecl WarpToGuildMeetingPlaceAction::failAction(::Action::FailReason)
{
    LIFT_STUB(0x47f290);
}

// 0x47f2c0
::GameFailReason __cdecl WarpToGuildMeetingPlaceAction::checkCasterCond(void)
{
    LIFT_STUB(0x47f2c0);
}

// 0x47f4b0
bool __cdecl RecallSummonAction::prepareAction(void)
{
    LIFT_STUB(0x47f4b0);
}

// 0x47f510
void __cdecl RecallSummonAction::startAction(void)
{
    LIFT_STUB(0x47f510);
}

// 0x47f890
bool __cdecl TeleportAction::Initialize(::Zone *, ::Creature *, short, short)
{
    LIFT_STUB(0x47f890);
}

// 0x47f960
void __cdecl TeleportAction::startAction(void)
{
    LIFT_STUB(0x47f960);
}

// 0x4803c0
__int64 __cdecl TeleportAction::getDistanceSquare(unsigned int, short, short, unsigned int, short, short)
{
    LIFT_STUB(0x4803c0);
}

// 0x480500
bool __cdecl TeleportAction::checkStartTeleport(::Data::TeleportRecordPtr)
{
    LIFT_STUB(0x480500);
}

// 0x480720
void __cdecl TeleportAction::finishAction(void)
{
    LIFT_STUB(0x480720);
}

// 0x480c00
void __cdecl TeleportAction::cancelAction(::Action::CancelReason, wchar_t const *, int)
{
    LIFT_STUB(0x480c00);
}

// 0x480c90
void __cdecl TeleportAction::failAction(::Action::FailReason)
{
    LIFT_STUB(0x480c90);
}

// 0x480cd0
bool __cdecl MoveAction::Initialize(::Zone *, ::Creature *, short, short, short, short, short, short, int, int, int, int, int, int, long, short, short, short, ::MoveTypeList *, short, ::MoveAction::Cell *, int)
{
    LIFT_STUB(0x480cd0);
}

// 0x4810b0
bool __cdecl MoveAction::prepareAction(void)
{
    LIFT_STUB(0x4810b0);
}

// 0x481330
bool __cdecl MoveAction::IsAvailableAction(void)
{
    LIFT_STUB(0x481330);
}

// 0x4813d0
void __cdecl MoveAction::startAction(void)
{
    LIFT_STUB(0x4813d0);
}

// 0x4822b0
bool __cdecl MoveAction::checkCellInRadius(short, ::GeoCell &, short)
{
    LIFT_STUB(0x4822b0);
}

// 0x4823f0
::GameFailReason __cdecl MoveAction::changeMoveState(int, ::GeoCell &, ::GeoCell &, short, short, ::MoveType &)
{
    LIFT_STUB(0x4823f0);
}

// 0x483150
::GameFailReason __cdecl MoveAction::validateMove(::GeoCell &, ::GeoCell &, short, short, ::MoveType)
{
    LIFT_STUB(0x483150);
}

// 0x4839a0
void __cdecl MoveAction::intervalAction(long)
{
    LIFT_STUB(0x4839a0);
}

// 0x4839c0
void __cdecl MoveAction::finishAction(void)
{
    LIFT_STUB(0x4839c0);
}

// 0x483a40
void __cdecl MoveAction::cancelAction(::Action::CancelReason, wchar_t const *, int)
{
    LIFT_STUB(0x483a40);
}

// 0x483ad0
void __cdecl MoveAction::failAction(::Action::FailReason)
{
    LIFT_STUB(0x483ad0);
}

// 0x483e00
::GameFailReason __cdecl MoveAction::moveCaster(::vector16, long, ::GeoCell *, char *const, int, bool)
{
    LIFT_STUB(0x483e00);
}

// 0x483f60
void __cdecl MoveAction::actionFailed(short, bool, bool)
{
    LIFT_STUB(0x483f60);
}

// 0x484100
bool __cdecl MoveAction::checkCell(::vector16 &, ::MoveAction::Cell &)
{
    LIFT_STUB(0x484100);
}

// 0x4845d0
::GameFailReason __cdecl MoveAction::checkPortalWhenLink(::GeoCell)
{
    LIFT_STUB(0x4845d0);
}

// 0x484660
bool __cdecl MoveAction::unlinkByPortal(::Creature *)
{
    LIFT_STUB(0x484660);
}

// 0x485140
bool __cdecl MoveAction::checkSpeed(void)
{
    LIFT_STUB(0x485140);
}

// 0x485d80
void __cdecl MoveAction::dump(void)
{
    LIFT_STUB(0x485d80);
}

// 0x486130
::GameFailReason __cdecl MoveAction::checkCellList(void)
{
    LIFT_STUB(0x486130);
}

// 0x486330
::GameFailReason __cdecl MoveAction::checkMoveTypeList(void)
{
    LIFT_STUB(0x486330);
}

// 0x486600
::GameFailReason __cdecl MoveAction::availableHyperMove(::MoveType, int &)
{
    LIFT_STUB(0x486600);
}

// 0x4869a0
::GameFailReason __cdecl MoveAction::availableGlide(void)
{
    LIFT_STUB(0x4869a0);
}

// 0x486b70
::GameFailReason __cdecl MoveAction::isValidInBlockMove(::ControlledCreature *)
{
    LIFT_STUB(0x486b70);
}

// 0x487750
bool __cdecl SummonMoveAction::Initialize(::Zone *, ::Creature *, short, short, short, short, short, short, long, short, short, short, ::MoveTypeList *, short, ::MoveAction::Cell *, int)
{
    LIFT_STUB(0x487750);
}

// 0x487ae0
bool __cdecl SummonMoveAction::prepareAction(void)
{
    LIFT_STUB(0x487ae0);
}

// 0x487d60
bool __cdecl SummonMoveAction::IsAvailableAction(void)
{
    LIFT_STUB(0x487d60);
}

// 0x487e00
void __cdecl SummonMoveAction::startAction(void)
{
    LIFT_STUB(0x487e00);
}

// 0x489090
::GameFailReason __cdecl SummonMoveAction::checkMasterRange(void)
{
    LIFT_STUB(0x489090);
}

// 0x489360
bool __cdecl SummonMoveAction::checkCellInRadius(short, ::GeoCell &, short)
{
    LIFT_STUB(0x489360);
}

// 0x4894c0
::GameFailReason __cdecl SummonMoveAction::changeMoveState(int, ::GeoCell &, ::GeoCell &, short, short, ::MoveType &)
{
    LIFT_STUB(0x4894c0);
}

// 0x489950
::GameFailReason __cdecl SummonMoveAction::validateMove(::GeoCell &, ::GeoCell &, short, short, ::MoveType)
{
    LIFT_STUB(0x489950);
}

// 0x489e40
void __cdecl SummonMoveAction::intervalAction(long)
{
    LIFT_STUB(0x489e40);
}

// 0x489e60
void __cdecl SummonMoveAction::finishAction(void)
{
    LIFT_STUB(0x489e60);
}

// 0x489ee0
void __cdecl SummonMoveAction::cancelAction(::Action::CancelReason, wchar_t const *, int)
{
    LIFT_STUB(0x489ee0);
}

// 0x489f70
void __cdecl SummonMoveAction::failAction(::Action::FailReason)
{
    LIFT_STUB(0x489f70);
}

// 0x48a2a0
::GameFailReason __cdecl SummonMoveAction::moveCaster(::vector16, long, ::GeoCell *, char *const, int, bool)
{
    LIFT_STUB(0x48a2a0);
}

// 0x48a400
void __cdecl SummonMoveAction::actionFailed(short, bool, bool)
{
    LIFT_STUB(0x48a400);
}

// 0x48a5a0
bool __cdecl SummonMoveAction::checkCell(::vector16 &, ::MoveAction::Cell &)
{
    LIFT_STUB(0x48a5a0);
}

// 0x48aa70
bool __cdecl SummonMoveAction::checkSpeed(void)
{
    LIFT_STUB(0x48aa70);
}

// 0x48af20
void __cdecl SummonMoveAction::dump(void)
{
    LIFT_STUB(0x48af20);
}

// 0x48b2d0
::GameFailReason __cdecl SummonMoveAction::checkCellList(void)
{
    LIFT_STUB(0x48b2d0);
}

// 0x48b500
::GameFailReason __cdecl SummonMoveAction::checkMoveTypeList(void)
{
    LIFT_STUB(0x48b500);
}

// 0x48b7b0
::GameFailReason __cdecl SummonMoveAction::isValidInBlockMove(::ControlledCreature *)
{
    LIFT_STUB(0x48b7b0);
}

// 0x48c390
bool __cdecl EscapeFromCaveAction::Initialize(::Zone *, ::Creature *, short)
{
    LIFT_STUB(0x48c390);
}

// 0x48c450
void __cdecl EscapeFromCaveAction::startAction(void)
{
    LIFT_STUB(0x48c450);
}

// 0x48c640
void __cdecl EscapeFromCaveAction::finishAction(void)
{
    LIFT_STUB(0x48c640);
}

// 0x48ca70
void __cdecl EscapeFromCaveAction::cancelAction(::Action::CancelReason, wchar_t const *, int)
{
    LIFT_STUB(0x48ca70);
}

// 0x48cbc0
void __cdecl EscapeFromCaveAction::failAction(::Action::FailReason)
{
    LIFT_STUB(0x48cbc0);
}

// 0x48cbf0
bool __cdecl EscapeFromCaveAction::checkCaveEscapeItem(void)
{
    LIFT_STUB(0x48cbf0);
}

// 0x48cdc0
bool __cdecl EscapeFromCaveAction::consumeCaveEscapeItem(void)
{
    LIFT_STUB(0x48cdc0);
}
