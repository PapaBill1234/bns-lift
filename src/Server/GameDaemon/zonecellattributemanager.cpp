// zonecellattributemanager.cpp: zonecellattributemanager.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "zonecellattributemanager.h"
#include "LiftStub.h"

// 0x130c0
__cdecl ZoneCellAttributeTable::ZoneCellAttributeTable(int, ::Data::ZoneCellAttributeRecordPtr)
{
    LIFT_STUB(0x130c0);
}

// 0x13150 LIFT: log path (E16). The body calls Log::Write. Keep the stub.
__cdecl ZoneCellAttributeTable::~ZoneCellAttributeTable(void)
{
    LIFT_STUB(0x13150);
}

// 0x131f0
bool __cdecl ZoneCellAttributeTable::setAttr(short, short, ::Data::ZoneCellAttributeCellAttributeType)
{
    LIFT_STUB(0x131f0);
}

// 0x13390
char __cdecl ZoneCellAttributeTable::getAttr(short, short) const
{
    LIFT_STUB(0x13390);
}

// 0x13510
bool __cdecl ZoneCellAttributeTable::initialize(void)
{
    LIFT_STUB(0x13510);
}

// 0x13b90
bool __cdecl ZoneCellAttributeTable::check(short, short, short, ::Data::ZoneCellAttributeCellAttributeType) const
{
    LIFT_STUB(0x13b90);
}

// 0x13c20
__cdecl ZoneCellAttributeManager::ZoneCellAttributeManager(void)
{
    LIFT_STUB(0x13c20);
}

// 0x13d60
__cdecl ZoneCellAttributeManager::~ZoneCellAttributeManager(void)
{
    LIFT_STUB(0x13d60);
}

// 0x13ed0
bool __cdecl ZoneCellAttributeManager::Create(int, ::Data::ZoneCellAttributeRecordPtr)
{
    LIFT_STUB(0x13ed0);
}

// 0x14240
bool __cdecl ZoneCellAttributeManager::Check(int, short, short, short, ::Data::ZoneCellAttributeCellAttributeType) const
{
    LIFT_STUB(0x14240);
}
