// capturetheflag_cpp.cpp: capturetheflag.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "capturetheflag.h"
#include "envobj.h"
#include "fielditem.h"
#include "pc.h"
#include "zone.h"
#include "LiftStub.h"

// 0x64980
bool __cdecl CaptureTheFlag::Init(::Zone *, unsigned __int64)
{
    LIFT_STUB(0x64980);
}

// 0x64be0
void __cdecl CaptureTheFlag::OnTimer(void)
{
    LIFT_STUB(0x64be0);
}

// 0x64e80
bool __cdecl CaptureTheFlag::CheckToManipulateEnv(::Pc *, ::Env *, ::Data::ZoneEnv2RecordPtr const &)
{
    LIFT_STUB(0x64e80);
}

// 0x64ee0
bool __cdecl CaptureTheFlag::TryToManipulateEnv(::Pc *, ::Env *, ::Data::ZoneEnv2RecordPtr &)
{
    LIFT_STUB(0x64ee0);
}

// 0x64f50
void __cdecl CaptureTheFlag::DisposeFieldItem(::Pc *, ::FieldItem *)
{
    LIFT_STUB(0x64f50);
}

// 0x65030
bool __cdecl CaptureTheFlag::canPlantFlag(::Pc *, ::Env *, ::Data::ZoneEnv2RecordPtr const &)
{
    LIFT_STUB(0x65030);
}

// 0x65120
bool __cdecl CaptureTheFlag::canStealFlag(::Pc *, ::Env *, ::Data::ZoneEnv2RecordPtr const &)
{
    LIFT_STUB(0x65120);
}

// 0x651c0
void __cdecl CaptureTheFlag::OnEnvManipulated(::Pc *, ::Env *, ::Data::ZoneEnv2RecordPtr const &, char, char)
{
    LIFT_STUB(0x651c0);
}

// 0x652c0
void __cdecl CaptureTheFlag::OnCanceledEnvManipulation(::Env *, ::Data::ZoneEnv2RecordPtr &, char, char)
{
    LIFT_STUB(0x652c0);
}

// 0x65340
void __cdecl CaptureTheFlag::Reset(void)
{
    LIFT_STUB(0x65340);
}

// 0x654e0
int __cdecl CaptureTheFlag::getRatingRevise(short)
{
    LIFT_STUB(0x654e0);
}

// 0x65530
void __cdecl CaptureTheFlag::initEnableFlagSpawnEnv(void)
{
    LIFT_STUB(0x65530);
}

// 0x655e0
short __cdecl CaptureTheFlag::addZoneScorePerSecForAlpha(void)
{
    LIFT_STUB(0x655e0);
}

// 0x65770
short __cdecl CaptureTheFlag::addZoneScorePerSecForBeta(void)
{
    LIFT_STUB(0x65770);
}

// 0x65900
bool __cdecl CaptureTheFlag::checkFinishCondForAlpha(void)
{
    LIFT_STUB(0x65900);
}

// 0x659d0
bool __cdecl CaptureTheFlag::checkFinishCondForBeta(void)
{
    LIFT_STUB(0x659d0);
}

// 0x65a80
void __cdecl CaptureTheFlag::onControlPointEnvManipulated(::Pc *, ::Env *, ::Data::ZoneEnv2RecordPtr const &)
{
    LIFT_STUB(0x65a80);
}
