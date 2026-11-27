// duelbotaction.cpp: duelbotaction.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "duelbotaction.h"
#include "action.h"
#include "moveaction.h"
#include "zone.h"
#include "LiftStub.h"

// 0xa2970
__cdecl DuelBotMoveAction::DuelBotMoveAction(void)
{
    LIFT_STUB(0xa2970);
}

// 0xa29b0
bool __cdecl DuelBotMoveAction::Initialize(::Zone *, unsigned __int64, short, short, char, short, short)
{
    LIFT_STUB(0xa29b0);
}

// 0xa2aa0
bool __cdecl DuelBotMoveAction::IsAvailableAction(void)
{
    LIFT_STUB(0xa2aa0);
}

// 0xa2ad0
void __cdecl DuelBotMoveAction::startAction(void)
{
    LIFT_STUB(0xa2ad0);
}

// 0xa2c40
void __cdecl DuelBotMoveAction::intervalAction(long)
{
    LIFT_STUB(0xa2c40);
}

// 0xa2e60
void __cdecl DuelBotMoveAction::finishAction(void)
{
    LIFT_STUB(0xa2e60);
}

// 0xa2e70
void __cdecl AirDashAction::cancelAction(::Action::CancelReason, wchar_t const *, int)
{
    LIFT_STUB(0xa2e70);
}

// 0xa2ea0
bool __cdecl DuelBotMoveAction::move(::vector16 const &, long)
{
    LIFT_STUB(0xa2ea0);
}

// 0xa3070
long __cdecl DuelBotMoveAction::getTimerDuration(void) const
{
    LIFT_STUB(0xa3070);
}

// 0xa3150
bool __cdecl DuelBotSummonedMoveAction::Initialize(::Zone *, unsigned __int64, short, short, short)
{
    LIFT_STUB(0xa3150);
}

// 0xa31d0
void __cdecl DuelBotSummonedMoveAction::startAction(void)
{
    LIFT_STUB(0xa31d0);
}

// 0xa32f0
void __cdecl DuelBotSummonedMoveAction::intervalAction(long)
{
    LIFT_STUB(0xa32f0);
}

// 0xa3510
bool __cdecl DuelBotSummonedMoveAction::move(::vector16 const &, long)
{
    LIFT_STUB(0xa3510);
}

// 0xa36e0
long __cdecl DuelBotSummonedMoveAction::getTimerDuration(void) const
{
    LIFT_STUB(0xa36e0);
}
