// propertysync.cpp: propertysync.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "propertysync.h"
#include "LiftStub.h"

// 0x687ce0
__cdecl SyncBuffer::~SyncBuffer(void)
{
    LIFT_STUB(0x687ce0);
}

// 0x687df0
bool __cdecl SyncBuffer::Initialize(::SyncBuffer::Def const *)
{
    LIFT_STUB(0x687df0);
}

// 0x687fc0
bool __cdecl SyncBuffer::Initialize(::SyncBuffer const *)
{
    LIFT_STUB(0x687fc0);
}

// 0x6880c0
bool __cdecl SyncBuffer::Clear(void) const
{
    LIFT_STUB(0x6880c0);
}

// 0x688130
short __cdecl SyncBuffer::Copy(char *, unsigned __int64, short *, bool) const
{
    LIFT_STUB(0x688130);
}

// 0x6881b0
bool __cdecl SyncBuffer::Set(::Field::Def const *, int, void const *, int, bool, bool *, int, int)
{
    LIFT_STUB(0x6881b0);
}

// 0x688560
char * __cdecl SyncBuffer::set(::Field::Def const *, int, char *, void const *, int, bool, short &)
{
    LIFT_STUB(0x688560);
}

// 0x688890
char * __cdecl SyncBuffer::setInt(char *, void const *, unsigned char)
{
    LIFT_STUB(0x688890);
}

// 0x6888d0
char * __cdecl SyncBuffer::setString(char *, wchar_t const *, short, int, bool, short &)
{
    LIFT_STUB(0x6888d0);
}

// 0x688990
void __cdecl SyncBuffer::realign(int, char *, short)
{
    LIFT_STUB(0x688990);
}
