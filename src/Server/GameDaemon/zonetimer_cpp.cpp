// zonetimer_cpp.cpp: zonetimer.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "zonetimer.h"
#include "zone.h"
#include "LiftStub.h"
#include <windows.h>
#include <time.h>

#pragma comment(linker, "/INCLUDE:?preExecute@ZoneSerializer@@UEAAXJ@Z")  // LIFT: dead-strip keep (no live caller yet)

namespace
{
// LIFT: views of PDB classes that have no layout in the skeleton yet. Offsets are from the PDB.

// LIFT: view of ZonePerfMonitor (StartClock at +0x8, StartMsec at +0x120).
struct ZonePerfMonitorView
{
    char lift_pad_0[0x8];
    long StartClock;            // +8 (0x8)
    char lift_pad_1[0x120 - 0xC];
    __int64 StartMsec;          // +288 (0x120)
};

// LIFT: view of Zone (perfMon at +0x4290).
struct ZonePerfView
{
    char lift_pad_0[0x4290];
    ZonePerfMonitorView *perfMon;  // +17040 (0x4290)
};

// LIFT: view of ZoneSerializer (_zoneInstance at +0x98).
struct ZoneSerializerView
{
    char lift_pad_0[0x98];
    ZonePerfView *_zoneInstance;  // +152 (0x98)
};
}  // namespace

// 0x25fd00
bool __cdecl ZoneSerializer::Initialize(::Zone *, long, long)
{
    LIFT_STUB(0x25fd00);
}

// 0x25fdf0
bool __cdecl ZoneSerializer::Clear(void)
{
    LIFT_STUB(0x25fdf0);
}

// 0x25fe70
void __cdecl ZoneSerializer::executeLast(long, unsigned int *)
{
    LIFT_STUB(0x25fe70);
}

// 0x260170
void __cdecl ZoneSerializer::preExecute(long)
{
    ZonePerfView *zoneInstance = reinterpret_cast<ZoneSerializerView *>(this)->_zoneInstance;
    if (zoneInstance != nullptr)
    {
        ZonePerfMonitorView *perfMon = zoneInstance->perfMon;
        if (perfMon != nullptr)
        {
            // LIFT: inline ZonePerfMonitor::Start
            perfMon->StartClock = clock();
            perfMon->StartMsec = GetTickCount64() - Daemon::Instance->StartSystemTick64;
        }
    }
}

// 0x2601c0
void __cdecl ZoneSerializer::postExecute(long, unsigned int, unsigned int)
{
    LIFT_STUB(0x2601c0);
}
