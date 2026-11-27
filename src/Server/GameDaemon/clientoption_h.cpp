// clientoption_h.cpp: clientoption.h (GameDaemon PDB, 2019 + PDB).
#include "clientoption.h"
#include "propertysync.h"
#include "LiftStub.h"


// 0x19480
__cdecl ClientOption::~ClientOption(void)
{
    LIFT_STUB(0x19480);
}

// 0x19490
int const __cdecl ClientOption::TypeId(void) const
{
    return 14;
}

// 0x194a0
wchar_t const * __cdecl ClientOption::Name(void) const
{
    return L"ClientOption";
}

// 0x194b0
int __cdecl ClientOption::FieldMax(void) const
{
    return fieldMax;
}

// 0x194c0
::Field::Def const * __cdecl ClientOption::FieldDefine(void) const
{
    return fieldDefine;
}

// 0x194d0
int __cdecl ClientOption::SyncMax(void) const
{
    return syncMax;
}

// 0x194e0
::SyncBuffer::Def const * __cdecl ClientOption::SyncDefine(void) const
{
    return syncDefine;
}

// LIFT: definitions of the PDB static data members.
int ClientOption::fieldMax;
::Field::Def const * ClientOption::fieldDefine;
int ClientOption::syncMax;
::SyncBuffer::Def const * ClientOption::syncDefine;
