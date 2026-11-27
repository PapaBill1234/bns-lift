// warfieldmanager.cpp: warfieldmanager.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "warfieldmanager.h"
#include "task.h"
#include "zone.h"
#include "LiftStub.h"

// 0x226b00
__cdecl WarFieldGroup::WarFieldGroup(void)
{
    LIFT_STUB(0x226b00);
}

// 0x226c00
__cdecl WarFieldGroup::~WarFieldGroup(void)
{
    LIFT_STUB(0x226c00);
}

// 0x226cf0
bool __cdecl WarFieldGroup::init(unsigned __int64)
{
    LIFT_STUB(0x226cf0);
}

// 0x226d70
unsigned __int64 __cdecl WarFieldGroup::getDataKey(void)
{
    LIFT_STUB(0x226d70);
}

// 0x226de0
void __cdecl WarFieldGroup::changeStep(char)
{
    LIFT_STUB(0x226de0);
}

// 0x226f10
int __cdecl WarFieldGroup::executeSerializedJob(::Task *)
{
    LIFT_STUB(0x226f10);
}

// 0x227030
int __cdecl WarFieldGroup::executeSerializedJob(::Data::WarFieldWarFieldZoneTypeType, ::Task *)
{
    LIFT_STUB(0x227030);
}

// 0x227250
void __cdecl WarFieldGroup::timerExpired(long)
{
    LIFT_STUB(0x227250);
}

// 0x227560
bool __cdecl WarFieldGroup::addZone(::Data::WarFieldWarFieldZoneTypeType, ::Zone *)
{
    LIFT_STUB(0x227560);
}

// 0x227870
__cdecl WarFieldManager::WarFieldManager(void)
{
    LIFT_STUB(0x227870);
}

// 0x227930
__cdecl WarFieldManager::~WarFieldManager(void)
{
    LIFT_STUB(0x227930);
}

// 0x227ab0
void __cdecl WarFieldManager::TimerExpired(long)
{
    LIFT_STUB(0x227ab0);
}

// 0x227b70
bool __cdecl WarFieldManager::AddZone(::Data::WarFieldWarFieldZoneTypeType, ::Zone *, unsigned __int64)
{
    LIFT_STUB(0x227b70);
}

// 0x227f00
char __cdecl WarFieldManager::GetStep(unsigned __int64)
{
    LIFT_STUB(0x227f00);
}
