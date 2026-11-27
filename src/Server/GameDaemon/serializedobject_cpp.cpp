// serializedobject_cpp.cpp: serializedobject.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "serializedobject.h"
#include "serializer.h"
#include "LiftStub.h"

// 0x662cb0
bool __cdecl SerializedObjectHistory::add(::SerializedObjectQueue *, ::SerializedObjectQueue *, wchar_t const *, int)
{
    LIFT_STUB(0x662cb0);
}

// 0x662da0
void __cdecl SerializedObjectHistory::dump(::SerializedObject *)
{
    LIFT_STUB(0x662da0);
}

// 0x663090
__cdecl SerializedObject::~SerializedObject(void)
{
    LIFT_STUB(0x663090);
}

// 0x6630c0
void __cdecl SerializedObject::Set(::Serializer *, long)
{
    LIFT_STUB(0x6630c0);
}

// 0x6631a0
__cdecl SerializedObjectQueue::~SerializedObjectQueue(void)
{
    LIFT_STUB(0x6631a0);
}

// 0x6632b0
wchar_t const * __cdecl SerializedObjectQueue::GetQueueTypeString(char)
{
    LIFT_STUB(0x6632b0);
}

// 0x663340
bool __cdecl SerializedObjectQueue::Add(::SerializedObject *)
{
    LIFT_STUB(0x663340);
}

// 0x6635d0
bool __cdecl SerializedObjectQueue::Add(::SerializedObjectQueue *, bool)
{
    LIFT_STUB(0x6635d0);
}

// 0x6637f0
bool __cdecl SerializedObjectQueue::Remove(::SerializedObject *)
{
    LIFT_STUB(0x6637f0);
}

// 0x663930
::SerializedObject * __cdecl SerializedObjectQueue::Clear(bool)
{
    LIFT_STUB(0x663930);
}

// 0x663a80
::SerializedObject * __cdecl SerializedObjectQueue::DetachList(void)
{
    LIFT_STUB(0x663a80);
}

// 0x663ba0
void __cdecl SerializedObject::CheckValid(::SerializedObject *, ::SerializedObject *, ::SerializedObjectQueue *, ::SourceLocation const &)
{
    LIFT_STUB(0x663ba0);
}
