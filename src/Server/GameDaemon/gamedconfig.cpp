// gamedconfig.cpp: gamedconfig.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "gamedconfig.h"
#include "geoworld.h"
#include "LiftStub.h"

// 0x343940
::GamedConfig * __cdecl GamedConfig::Load(void)
{
    LIFT_STUB(0x343940);
}

// 0x343a20
void __cdecl GamedConfig::Reload(void)
{
    LIFT_STUB(0x343a20);
}

// 0x343f20
void __cdecl GamedConfig::Destroy(::GamedConfig *)
{
    LIFT_STUB(0x343f20);
}

// 0x343ff0
void __cdecl GamedConfig::setPerfGeoZone(wchar_t const *)
{
    LIFT_STUB(0x343ff0);
}

// 0x344290
void __cdecl GamedConfig::setSkipActionPacketList(wchar_t const *)
{
    LIFT_STUB(0x344290);
}

// 0x345cb0
void __cdecl GamedConfig::setZoneRecommendPcCount(wchar_t const *, bool)
{
    LIFT_STUB(0x345cb0);
}

// 0x346060
void __cdecl GamedConfig::setExceptLastChangedPropertyList(wchar_t const *)
{
    LIFT_STUB(0x346060);
}

// 0x346250
bool __cdecl GamedConfig::UsePerfGeoZone(::GeoZone const *) const
{
    LIFT_STUB(0x346250);
}
