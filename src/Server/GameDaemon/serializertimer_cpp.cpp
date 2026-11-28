// serializertimer_cpp.cpp: serializertimer.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "serializertimer.h"
#include "serializedobject.h"
#include "serializer.h"
#include "LiftStub.h"

#pragma comment(linker, "/INCLUDE:?TimerId@SerializerTimer@@MEBA_KXZ")  // LIFT: dead-strip keep (no live caller yet)

// 0x665000
__cdecl TimerSlotVector::~TimerSlotVector(void)
{
    LIFT_STUB(0x665000);
}

// 0x665050
void __cdecl TimerSlotVector::Initialize(int, ::Serializer *)
{
    LIFT_STUB(0x665050);
}

// 0x665100
::SerializedObjectQueue * __cdecl TimerSlotVector::Add(::SerializedObject *, int, int)
{
    LIFT_STUB(0x665100);
}

// 0x665510
::SerializedObjectQueue * __cdecl TimerSlotVector::Add(::SerializedObjectQueue *, ::SerializedObjectQueue *)
{
    LIFT_STUB(0x665510);
}

// 0x665610
::SerializedObjectQueue * __cdecl TimerSlotVector::AddEvent(unsigned int, int, int)
{
    LIFT_STUB(0x665610);
}

// 0x6656b0
int __cdecl TimerSlotVector::Expire(int, ::SerializedObjectQueue *, bool)
{
    LIFT_STUB(0x6656b0);
}

// 0x665a40
__cdecl TimerSlotList::~TimerSlotList(void)
{
    LIFT_STUB(0x665a40);
}

// 0x665ae0
void __cdecl TimerSlotList::Initialize(int, ::Serializer *)
{
    LIFT_STUB(0x665ae0);
}

// 0x665bf0
::SerializedObjectQueue * __cdecl TimerSlotList::Add(::SerializedObject *, long)
{
    LIFT_STUB(0x665bf0);
}

// 0x665d20
void __cdecl TimerSlotList::Clear(void)
{
    LIFT_STUB(0x665d20);
}

// 0x665e20
__cdecl SerializerTimer::SerializerTimer(void)
{
    LIFT_STUB(0x665e20);
}

// 0x665fa0
__cdecl SerializerTimer::~SerializerTimer(void)
{
    LIFT_STUB(0x665fa0);
}

// 0x6660d0
bool __cdecl SerializerTimer::Initialize(::Serializer *, int)
{
    LIFT_STUB(0x6660d0);
}

// 0x666180
unsigned __int64 __cdecl SerializerTimer::TimerId(void) const
{
    return _serializer->Id();
}

// 0x666190
void __cdecl SerializerTimer::preprocessExpireEvent(void)
{
    LIFT_STUB(0x666190);
}

// 0x666200
bool __cdecl SerializerTimer::timerExpired(void)
{
    LIFT_STUB(0x666200);
}

// 0x666760
bool __cdecl SerializerTimer::Add(::SerializedObject *, long)
{
    LIFT_STUB(0x666760);
}

// 0x6668c0
bool __cdecl SerializerTimer::AddEvent(unsigned int, long)
{
    LIFT_STUB(0x6668c0);
}

// 0x6669b0
bool __cdecl SerializerTimer::Remove(::SerializedObject *)
{
    LIFT_STUB(0x6669b0);
}

// 0x666ac0
void __cdecl SerializerTimer::Clear(void)
{
    LIFT_STUB(0x666ac0);
}

// 0x666bc0
void __cdecl SerializerTimer::add(::SerializedObject *)
{
    LIFT_STUB(0x666bc0);
}

// 0x666cf0
bool __cdecl SerializerTimer::stop(void)
{
    LIFT_STUB(0x666cf0);
}

// 0x666ed0
void __cdecl SerializerTimer::addGlobalTimer(long, ::SerializedObjectQueue *)
{
    LIFT_STUB(0x666ed0);
}

// 0x666f90
void __cdecl SerializerTimer::dump(void)
{
    LIFT_STUB(0x666f90);
}
