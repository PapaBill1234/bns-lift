// moveaction.h: moveaction.cpp, moveaction.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"
#include "action.h"

class AirDashAction
{
private:
    virtual void __cdecl cancelAction(::Action::CancelReason, wchar_t const *, int);  // 0xa2e70
public:
    bool __cdecl Initialize(::Zone *, ::Creature *, unsigned __int64);  // 0x47acc0
private:
    virtual bool __cdecl prepareAction(void);  // 0x47ad80
    virtual void __cdecl startAction(void);  // 0x47af10
    virtual void __cdecl intervalAction(long);  // 0x47c7a0
};

class CallGuildMemberAction
{
public:
    __cdecl CallGuildMemberAction(void);  // 0x455150
private:
    virtual bool __cdecl prepareAction(void);  // 0x47d630
    virtual void __cdecl startAction(void);  // 0x47dad0
    virtual void __cdecl finishAction(void);  // 0x47dbb0
    virtual void __cdecl cancelAction(::Action::CancelReason, wchar_t const *, int);  // 0x47e0c0
    virtual void __cdecl failAction(::Action::FailReason);  // 0x47e140
    bool __cdecl checkConsumeItem(void);  // 0x47e170
    bool __cdecl disposeItem(void);  // 0x47e380
    ::GameFailReason __cdecl checkCasterCond(void);  // 0x47e4a0
};

class EscapeFromCaveAction
{
public:
    bool __cdecl Initialize(::Zone *, ::Creature *, short);  // 0x48c390
private:
    virtual void __cdecl startAction(void);  // 0x48c450
    virtual void __cdecl finishAction(void);  // 0x48c640
    virtual void __cdecl cancelAction(::Action::CancelReason, wchar_t const *, int);  // 0x48ca70
    virtual void __cdecl failAction(::Action::FailReason);  // 0x48cbc0
    bool __cdecl checkCaveEscapeItem(void);  // 0x48cbf0
    bool __cdecl consumeCaveEscapeItem(void);  // 0x48cdc0
};

class KnockBackAction
{
private:
    virtual void __cdecl startAction(void);  // 0x47aca0
};

class MoveAction
{
public:
    struct Cell {};
public:
    bool __cdecl Initialize(::Zone *, ::Creature *, short, short, short, short, short, short, int, int, int, int, int, int, long, short, short, short, ::MoveTypeList *, short, ::MoveAction::Cell *, int);  // 0x480cd0
private:
    virtual bool __cdecl prepareAction(void);  // 0x4810b0
public:
    virtual bool __cdecl IsAvailableAction(void);  // 0x481330
private:
    virtual void __cdecl startAction(void);  // 0x4813d0
    bool __cdecl checkCellInRadius(short, ::GeoCell &, short);  // 0x4822b0
    ::GameFailReason __cdecl changeMoveState(int, ::GeoCell &, ::GeoCell &, short, short, ::MoveType &);  // 0x4823f0
    ::GameFailReason __cdecl validateMove(::GeoCell &, ::GeoCell &, short, short, ::MoveType);  // 0x483150
    virtual void __cdecl intervalAction(long);  // 0x4839a0
    virtual void __cdecl finishAction(void);  // 0x4839c0
    virtual void __cdecl cancelAction(::Action::CancelReason, wchar_t const *, int);  // 0x483a40
    virtual void __cdecl failAction(::Action::FailReason);  // 0x483ad0
    ::GameFailReason __cdecl moveCaster(::vector16, long, ::GeoCell *, char *const, int, bool);  // 0x483e00
    void __cdecl actionFailed(short, bool, bool);  // 0x483f60
    bool __cdecl checkCell(::vector16 &, ::MoveAction::Cell &);  // 0x484100
    ::GameFailReason __cdecl checkPortalWhenLink(::GeoCell);  // 0x4845d0
    bool __cdecl unlinkByPortal(::Creature *);  // 0x484660
    bool __cdecl checkSpeed(void);  // 0x485140
    void __cdecl dump(void);  // 0x485d80
    ::GameFailReason __cdecl checkCellList(void);  // 0x486130
    ::GameFailReason __cdecl checkMoveTypeList(void);  // 0x486330
    ::GameFailReason __cdecl availableHyperMove(::MoveType, int &);  // 0x486600
    ::GameFailReason __cdecl availableGlide(void);  // 0x4869a0
    ::GameFailReason __cdecl isValidInBlockMove(::ControlledCreature *);  // 0x486b70
};

class RecallSummonAction
{
private:
    virtual bool __cdecl prepareAction(void);  // 0x47f4b0
    virtual void __cdecl startAction(void);  // 0x47f510
};

class SummonMoveAction
{
public:
    bool __cdecl Initialize(::Zone *, ::Creature *, short, short, short, short, short, short, long, short, short, short, ::MoveTypeList *, short, ::MoveAction::Cell *, int);  // 0x487750
private:
    virtual bool __cdecl prepareAction(void);  // 0x487ae0
public:
    virtual bool __cdecl IsAvailableAction(void);  // 0x487d60
private:
    virtual void __cdecl startAction(void);  // 0x487e00
    ::GameFailReason __cdecl checkMasterRange(void);  // 0x489090
    bool __cdecl checkCellInRadius(short, ::GeoCell &, short);  // 0x489360
    ::GameFailReason __cdecl changeMoveState(int, ::GeoCell &, ::GeoCell &, short, short, ::MoveType &);  // 0x4894c0
    ::GameFailReason __cdecl validateMove(::GeoCell &, ::GeoCell &, short, short, ::MoveType);  // 0x489950
    virtual void __cdecl intervalAction(long);  // 0x489e40
    virtual void __cdecl finishAction(void);  // 0x489e60
    virtual void __cdecl cancelAction(::Action::CancelReason, wchar_t const *, int);  // 0x489ee0
    virtual void __cdecl failAction(::Action::FailReason);  // 0x489f70
    ::GameFailReason __cdecl moveCaster(::vector16, long, ::GeoCell *, char *const, int, bool);  // 0x48a2a0
    void __cdecl actionFailed(short, bool, bool);  // 0x48a400
    bool __cdecl checkCell(::vector16 &, ::MoveAction::Cell &);  // 0x48a5a0
    bool __cdecl checkSpeed(void);  // 0x48aa70
    void __cdecl dump(void);  // 0x48af20
    ::GameFailReason __cdecl checkCellList(void);  // 0x48b2d0
    ::GameFailReason __cdecl checkMoveTypeList(void);  // 0x48b500
    ::GameFailReason __cdecl isValidInBlockMove(::ControlledCreature *);  // 0x48b7b0
};

class TeleportAction
{
public:
    bool __cdecl Initialize(::Zone *, ::Creature *, short, short);  // 0x47f890
private:
    virtual void __cdecl startAction(void);  // 0x47f960
    __int64 __cdecl getDistanceSquare(unsigned int, short, short, unsigned int, short, short);  // 0x4803c0
    bool __cdecl checkStartTeleport(::Data::TeleportRecordPtr);  // 0x480500
    virtual void __cdecl finishAction(void);  // 0x480720
    virtual void __cdecl cancelAction(::Action::CancelReason, wchar_t const *, int);  // 0x480c00
    virtual void __cdecl failAction(::Action::FailReason);  // 0x480c90
};

class WarpAction
{
private:
    virtual bool __cdecl prepareAction(void);  // 0x47b480
    virtual void __cdecl startAction(void);  // 0x47b580
    void __cdecl adjustZ(::GeoCell);  // 0x47c010
};

class WarpToGuildMeetingPlaceAction
{
private:
    virtual bool __cdecl prepareAction(void);  // 0x47e7c0
    virtual void __cdecl startAction(void);  // 0x47eea0
    virtual void __cdecl finishAction(void);  // 0x47ef80
    virtual void __cdecl cancelAction(::Action::CancelReason, wchar_t const *, int);  // 0x47f210
    virtual void __cdecl failAction(::Action::FailReason);  // 0x47f290
    ::GameFailReason __cdecl checkCasterCond(void);  // 0x47f2c0
};

class WarpToGuildMemberAction
{
public:
    __cdecl WarpToGuildMemberAction(void);  // 0x455090
private:
    virtual bool __cdecl prepareAction(void);  // 0x47c0d0
    virtual void __cdecl startAction(void);  // 0x47c6b0
    virtual void __cdecl finishAction(void);  // 0x47c7b0
    virtual void __cdecl cancelAction(::Action::CancelReason, wchar_t const *, int);  // 0x47cba0
    virtual void __cdecl failAction(::Action::FailReason);  // 0x47cc20
    bool __cdecl checkConsumeItem(void);  // 0x47cc50
    ::GameFailReason __cdecl checkCasterCond(void);  // 0x47ce60
    ::GameFailReason __cdecl checkTargetCond(void);  // 0x47d240
};

