// gameobject.h: gameobject.cpp, gameobject.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class GameObject
{
private:
    virtual ::MemoryManager * __cdecl childRoleAllocator(void);  // 0x1d070
public:
    virtual __cdecl ~GameObject(void);  // 0x1d080
    void __cdecl Initialize(unsigned __int64);  // 0x36c4f0
    virtual bool __cdecl Think(::ScriptEvent const *);  // 0x36c580
    virtual void __cdecl OnTimer(::Zone *, unsigned short);  // 0x36c5c0
    virtual void __cdecl OnAttack(::Zone *, ::GameObject *, unsigned __int64, short);  // 0x36c630
    virtual void __cdecl OnDamage(::Zone *, ::GameObject *, unsigned int, __int64);  // 0x36c7a0
    virtual void __cdecl OnKill(::Zone *, ::GameObject *, unsigned __int64, ::Data::QuestForwarding const *);  // 0x36c910
    virtual void __cdecl OnAttacked(::Zone *, ::GameObject *, unsigned __int64, short);  // 0x36ca80
    virtual void __cdecl OnDamaged(::Zone *, ::GameObject *, unsigned int, __int64);  // 0x36cbf0
    virtual void __cdecl OnKilled(::Zone *, ::GameObject *, ::GameObject *, unsigned __int64, ::Data::QuestForwarding const *);  // 0x36cd80
private:
    char lift_pad_8[0x28 - 8];  // LIFT: PDB members from +8 to +0x27 are not declared yet
public:
    unsigned __int64 Id;  // +0x28 (PDB: GameObject::Id; the object type is the high 16 bits)
};

class GameObjectCounter
{
public:
    __cdecl GameObjectCounter(void);  // 0x36d560
    void __cdecl Init(void);  // 0x36d7f0
    void __cdecl Fini(void);  // 0x36d9b0
    void __cdecl AddSummoned(::Summoned *);  // 0x36db40
    void __cdecl RemoveSummoned(::Summoned *);  // 0x36dc60
};

class GameObjectIdManager
{
public:
    unsigned __int64 __cdecl Make(unsigned __int64);  // 0x1d090
    virtual __cdecl ~GameObjectIdManager(void);  // 0x6aad60
};

class GameObjectTimer
{
public:
    static ::GameObjectTimer * __cdecl Create(unsigned short, ::Zone *, ::GameObject &);  // 0x36d0a0
    static void __cdecl Destroy(::GameObjectTimer **);  // 0x36d1d0
    bool __cdecl SetTimer(long);  // 0x36d230
    bool __cdecl ExecuteTimer(void);  // 0x36d340
    bool __cdecl ResetTimer(void);  // 0x36d430
    bool __cdecl Disable(void);  // 0x36d490
private:
    virtual void __cdecl TimerExpired(unsigned int, long);  // 0x36d500
};

