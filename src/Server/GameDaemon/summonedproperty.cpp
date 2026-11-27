// summonedproperty.cpp: summonedproperty.h (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "summonedproperty.h"
#include "propertysync.h"
#include "LiftStub.h"

// 0x1a220
__cdecl SummonedProperty::~SummonedProperty(void)
{
    LIFT_STUB(0x1a220);
}

// 0x1a240
wchar_t const * __cdecl SummonedProperty::Name(void) const
{
    LIFT_STUB(0x1a240);
}

// 0x1a250
int __cdecl SummonedProperty::FieldMax(void) const
{
    LIFT_STUB(0x1a250);
}

// 0x1a260
::Field::Def const * __cdecl SummonedProperty::FieldDefine(void) const
{
    LIFT_STUB(0x1a260);
}

// 0x1a270
int __cdecl SummonedProperty::SyncMax(void) const
{
    LIFT_STUB(0x1a270);
}

// 0x1a280
::SyncBuffer::Def const * __cdecl SummonedProperty::SyncDefine(void) const
{
    LIFT_STUB(0x1a280);
}
