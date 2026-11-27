// controlledcreature.cpp: controlledcreature.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "controlledcreature.h"
#include "pc.h"
#include "LiftStub.h"

// 0x5d28e0
__cdecl ControlledCreature::ControlledCreature(void)
{
    LIFT_STUB(0x5d28e0);
}

// 0x5d2980
__cdecl ControlledCreature::~ControlledCreature(void)
{
    LIFT_STUB(0x5d2980);
}

// 0x5d2a80
bool __cdecl ControlledCreature::Initialize(unsigned __int64)
{
    LIFT_STUB(0x5d2a80);
}

// 0x5d2c50
void __cdecl ControlledCreature::EnterZone(::EnterReason, bool, unsigned int)
{
    LIFT_STUB(0x5d2c50);
}

// 0x5d2ca0
void __cdecl ControlledCreature::LeaveZone(::LeaveReason)
{
    LIFT_STUB(0x5d2ca0);
}

// 0x5d2eb0
bool __cdecl ControlledCreature::AddPrivateProperty(char, short, char *, short)
{
    LIFT_STUB(0x5d2eb0);
}

// 0x5d2fe0
void __cdecl ControlledCreature::SendChangedPrivateProperty(void)
{
    LIFT_STUB(0x5d2fe0);
}

// 0x5d30a0
bool __cdecl ControlledCreature::AddActionPrivate(char const *, short)
{
    LIFT_STUB(0x5d30a0);
}

// 0x5d31c0
void __cdecl ControlledCreature::SendActionPrivatePacket(void)
{
    LIFT_STUB(0x5d31c0);
}

// 0x5d3280
bool __cdecl ControlledCreature::SaveMove(::vector16, ::GeoCell const *, short, char const *const, int, long, short, ::MoveTypeList *)
{
    LIFT_STUB(0x5d3280);
}

// 0x5d33d0
bool __cdecl ControlledCreature::MergeMove(::vector16, ::GeoCell const *, short, char const *const, int, long, short, ::MoveTypeList *)
{
    LIFT_STUB(0x5d33d0);
}

// 0x5d36a0
void __cdecl ControlledCreature::BroadcastLastMove(void)
{
    LIFT_STUB(0x5d36a0);
}

// 0x5d37a0
void __cdecl ControlledCreature::mergeMoveTypeEnd(::LastMove *)
{
    LIFT_STUB(0x5d37a0);
}

// 0x5d3a20
::MoveType __cdecl ControlledCreature::convertMoveType(::MoveType)
{
    LIFT_STUB(0x5d3a20);
}

// 0x5d3b40
bool __cdecl ControlledCreature::SetMoveTimeStamp(__int64, long)
{
    LIFT_STUB(0x5d3b40);
}

// 0x5d3be0
void __cdecl ControlledCreature::EnterAttraction(::EnterReason, unsigned int)
{
    LIFT_STUB(0x5d3be0);
}

// 0x5d3fa0
void __cdecl ControlledCreature::attachAttractionEffect(::dr_tref)
{
    LIFT_STUB(0x5d3fa0);
}

// 0x5d42c0
bool __cdecl MoveHackChecker::Initialize(void)
{
    LIFT_STUB(0x5d42c0);
}

// 0x5d43a0
bool __cdecl MoveHackChecker::Check(long, unsigned __int64, wchar_t const *)
{
    LIFT_STUB(0x5d43a0);
}

// 0x5d4500
void __cdecl MoveHackChecker::OnTimer(::Pc *)
{
    LIFT_STUB(0x5d4500);
}

// 0x5d47b0
bool __cdecl MoveHackChecker::GetFailCountListString(::Pc *, wchar_t *, int)
{
    LIFT_STUB(0x5d47b0);
}
