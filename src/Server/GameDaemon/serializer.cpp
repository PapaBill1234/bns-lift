// serializer.cpp: serializer.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "serializer.h"
#include "serializedobject.h"
#include "LiftStub.h"

// 0x663e00
__cdecl Serializer::~Serializer(void)
{
    LIFT_STUB(0x663e00);
}

// 0x663ed0
void __cdecl Serializer::dump(void)
{
    LIFT_STUB(0x663ed0);
}

// 0x664020
::SerializedObjectQueue * __cdecl Serializer::GetNextExpire(void)
{
    LIFT_STUB(0x664020);
}

// 0x664090
bool __cdecl Serializer::Initialize(unsigned __int64, long, long)
{
    LIFT_STUB(0x664090);
}

// 0x664280
void __cdecl Serializer::execute(long, ::SerializedObjectQueue *, unsigned int *)
{
    LIFT_STUB(0x664280);
}

// 0x664d10
bool __cdecl Serializer::Post(::SerializedObject *, long)
{
    LIFT_STUB(0x664d10);
}

// 0x664d80
bool __cdecl Serializer::post(::SerializedObject *)
{
    LIFT_STUB(0x664d80);
}

// 0x664ec0
bool __cdecl SerializedObjectList::grow(void)
{
    LIFT_STUB(0x664ec0);
}
