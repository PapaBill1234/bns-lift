// gameobject_cpp.cpp: gameobject.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "gameobject.h"
#include "summoned.h"
#include "zone.h"
#include "LiftStub.h"
#include "AlertSender.h"
#include "Log.h"

// LIFT: per-exe path literal (lessons A6).
#define GAMEOBJECT_FILE L"e:\\dailybuild02\\gamedaemon-common-0.0.348\\depot\\branch\\348nc\\program\\server\\gamedaemon\\GameObject.cpp"

// 0x36c4f0
void __cdecl GameObject::Initialize(unsigned __int64)
{
    LIFT_STUB(0x36c4f0);
}

// 0x36c580
#pragma comment(linker, "/INCLUDE:?Think@GameObject@@UEAA_NPEBVScriptEvent@@@Z")  // LIFT: dead-strip keep (no live caller yet)
bool __cdecl GameObject::Think(::ScriptEvent const *)
{
    Log::Write(Log::LT_ERROR, GAMEOBJECT_FILE, 44, L"== CRASH == [object], Think; called ... wrong");
    AlertSender::Write(GAMEOBJECT_FILE, 44, L"== CRASH == [object], Think; called ... wrong");
    return false;
}

// 0x36c5c0
#pragma comment(linker, "/INCLUDE:?OnTimer@GameObject@@UEAAXPEAVZone@@G@Z")  // LIFT: dead-strip keep (no live caller yet)
void __cdecl GameObject::OnTimer(::Zone *, unsigned short timerSubtype)
{
    // LIFT: GameObject::Id is read through the view GameObjectIdView (gameobject.h).
    unsigned __int64 const id = reinterpret_cast< ::GameObjectIdView const *>(this)->Id;
    Log::Write(Log::LT_ERROR, GAMEOBJECT_FILE, 50, L"== CRASH == [object], OnTimer; called ... wrong, id:0x%I64x, subtype:%u", id, timerSubtype);
    AlertSender::Write(GAMEOBJECT_FILE, 50, L"== CRASH == [object], OnTimer; called ... wrong, id:0x%I64x, subtype:%u", id, timerSubtype);
}

// 0x36c630
void __cdecl GameObject::OnAttack(::Zone *, ::GameObject *, unsigned __int64, short)
{
    LIFT_STUB(0x36c630);
}

// 0x36c7a0
void __cdecl GameObject::OnDamage(::Zone *, ::GameObject *, unsigned int, __int64)
{
    LIFT_STUB(0x36c7a0);
}

// 0x36c910
void __cdecl GameObject::OnKill(::Zone *, ::GameObject *, unsigned __int64, ::Data::QuestForwarding const *)
{
    LIFT_STUB(0x36c910);
}

// 0x36ca80
void __cdecl GameObject::OnAttacked(::Zone *, ::GameObject *, unsigned __int64, short)
{
    LIFT_STUB(0x36ca80);
}

// 0x36cbf0
void __cdecl GameObject::OnDamaged(::Zone *, ::GameObject *, unsigned int, __int64)
{
    LIFT_STUB(0x36cbf0);
}

// 0x36cd80
void __cdecl GameObject::OnKilled(::Zone *, ::GameObject *, ::GameObject *, unsigned __int64, ::Data::QuestForwarding const *)
{
    LIFT_STUB(0x36cd80);
}

// 0x36d0a0
::GameObjectTimer * __cdecl GameObjectTimer::Create(unsigned short, ::Zone *, ::GameObject &)
{
    LIFT_STUB(0x36d0a0);
}

// 0x36d1d0
void __cdecl GameObjectTimer::Destroy(::GameObjectTimer **)
{
    LIFT_STUB(0x36d1d0);
}

// 0x36d230
bool __cdecl GameObjectTimer::SetTimer(long)
{
    LIFT_STUB(0x36d230);
}

// 0x36d340
bool __cdecl GameObjectTimer::ExecuteTimer(void)
{
    LIFT_STUB(0x36d340);
}

// 0x36d430
bool __cdecl GameObjectTimer::ResetTimer(void)
{
    LIFT_STUB(0x36d430);
}

// 0x36d490
bool __cdecl GameObjectTimer::Disable(void)
{
    LIFT_STUB(0x36d490);
}

// 0x36d500
void __cdecl GameObjectTimer::TimerExpired(unsigned int, long)
{
    LIFT_STUB(0x36d500);
}

// 0x36d560
__cdecl GameObjectCounter::GameObjectCounter(void)
{
    LIFT_STUB(0x36d560);
}

// 0x36d7f0
void __cdecl GameObjectCounter::Init(void)
{
    LIFT_STUB(0x36d7f0);
}

// 0x36d9b0
void __cdecl GameObjectCounter::Fini(void)
{
    LIFT_STUB(0x36d9b0);
}

// 0x36db40
void __cdecl GameObjectCounter::AddSummoned(::Summoned *)
{
    LIFT_STUB(0x36db40);
}

// 0x36dc60
void __cdecl GameObjectCounter::RemoveSummoned(::Summoned *)
{
    LIFT_STUB(0x36dc60);
}
