// zoneevent.cpp: zoneevent.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "zoneevent.h"
#include "creature.h"
#include "zone.h"
#include "LiftStub.h"

// 0x25cab0
bool __cdecl ZoneEvent::ProcessFactionKillEvent(void)
{
    LIFT_STUB(0x25cab0);
}

// 0x25cc70
bool __cdecl ZoneEvent::ProcessKillNpcEvent(unsigned __int64)
{
    LIFT_STUB(0x25cc70);
}

// 0x25ce70
bool __cdecl ZoneEvent::setEventStep(char)
{
    LIFT_STUB(0x25ce70);
}

// 0x25cef0
__cdecl InOutDetector::InOutDetector(void)
{
    LIFT_STUB(0x25cef0);
}

// 0x25cf60
__cdecl InOutDetector::~InOutDetector(void)
{
    LIFT_STUB(0x25cf60);
}

// 0x25cfd0
void __cdecl InOutDetector::stop(::Zone *, ::Data::ScriptStopDetectReasonType)
{
    LIFT_STUB(0x25cfd0);
}

// 0x25d210
void __cdecl InOutDetector::clear(void)
{
    LIFT_STUB(0x25d210);
}

// 0x25d290
bool __cdecl InOutDetector::Start(::Zone *, unsigned __int64, ::Data::ScriptDetectRefTypeType, unsigned __int64, unsigned __int64, short, long, short, unsigned __int64, unsigned __int64, unsigned __int64, unsigned __int64)
{
    LIFT_STUB(0x25d290);
}

// 0x25da80
bool __cdecl InOutDetector::Detect(::Zone *)
{
    LIFT_STUB(0x25da80);
}

// 0x25dc60
bool __cdecl InOutDetector::checkCreature(::Creature *, __int64 &)
{
    LIFT_STUB(0x25dc60);
}

// 0x25dd40
bool __cdecl InOutDetector::gather(::Zone *, ::Pointer2< ::Creature>)
{
    LIFT_STUB(0x25dd40);
}

// 0x25e3c0
void __cdecl InOutDetector::invokeEventIn(::Zone *, ::Pointer2< ::Creature>, ::Creature *)
{
    LIFT_STUB(0x25e3c0);
}

// 0x25e600
void __cdecl InOutDetector::invokeEventOut(::Zone *, ::Pointer2< ::Creature>, ::Creature *)
{
    LIFT_STUB(0x25e600);
}

// 0x25e840
__cdecl ZoneCreatureDetector::ZoneCreatureDetector(::Zone *)
{
    LIFT_STUB(0x25e840);
}

// 0x25e920
bool __cdecl ZoneCreatureDetector::OnDetect(void)
{
    LIFT_STUB(0x25e920);
}

// 0x25ea20
bool __cdecl ZoneCreatureDetector::Start(char, unsigned __int64, ::Data::ScriptDetectRefTypeType, unsigned __int64, unsigned __int64, short, long, short, unsigned __int64, unsigned __int64, unsigned __int64, unsigned __int64)
{
    LIFT_STUB(0x25ea20);
}

// 0x25ec30
bool __cdecl ZoneCreatureDetector::Stop(char)
{
    LIFT_STUB(0x25ec30);
}
