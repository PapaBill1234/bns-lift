// occupationwarmanager.cpp: occupationwarmanager.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "occupationwarmanager.h"
#include "capturetheflag.h"
#include "envobj.h"
#include "pc.h"
#include "zone.h"
#include "LiftStub.h"

// 0x170b00
bool __cdecl OccupationWarManager::Init(::Zone *, unsigned __int64)
{
    LIFT_STUB(0x170b00);
}

// 0x170c10
void __cdecl OccupationWarManager::OnTimer(void)
{
    LIFT_STUB(0x170c10);
}

// 0x170e30
void __cdecl CaptureTheFlag::OnDead(unsigned __int64, ::Pc *)
{
    LIFT_STUB(0x170e30);
}

// 0x170ff0
bool __cdecl OccupationWarManager::TryToManipulateEnv(::Pc *, ::Env *, ::Data::ZoneEnv2RecordPtr &)
{
    LIFT_STUB(0x170ff0);
}

// 0x171160
void __cdecl OccupationWarManager::OnEnvManipulated(::Pc *, ::Env *, ::Data::ZoneEnv2RecordPtr const &, char, char)
{
    LIFT_STUB(0x171160);
}

// 0x171500
void __cdecl OccupationWarManager::OnCanceledEnvManipulation(::Env *, ::Data::ZoneEnv2RecordPtr &, char, char)
{
    LIFT_STUB(0x171500);
}

// 0x171540
void __cdecl OccupationWarManager::Reset(void)
{
    LIFT_STUB(0x171540);
}

// 0x171600
void __cdecl OccupationWarManager::addZoneScorePerSec(void)
{
    LIFT_STUB(0x171600);
}

// 0x171880
void __cdecl OccupationWarManager::manipulateEnv(::Env *, ::Data::ZoneEnv2RecordPtr const &, char, char)
{
    LIFT_STUB(0x171880);
}

// 0x1719a0
int __cdecl OccupationWarManager::getRatingRevise(short)
{
    LIFT_STUB(0x1719a0);
}
