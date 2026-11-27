// fielditem.h: fielditem.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class FieldItem
{
private:
    __cdecl FieldItem(unsigned __int64);  // 0x5a0700
public:
    virtual __cdecl ~FieldItem(void);  // 0x5a07f0
    bool __cdecl Initialize(unsigned __int64, unsigned int, ::vector16, ::Zone *, unsigned __int64);  // 0x5a0870
    __int64 __cdecl GetRemainedDecomposition(void) const;  // 0x5a0a90
    __int64 __cdecl GetRemainedExplosion(void) const;  // 0x5a0af0
    bool __cdecl Create(unsigned __int64);  // 0x5a0b50
    bool __cdecl Spawn(void);  // 0x5a0d90
    bool __cdecl Pickup(unsigned __int64);  // 0x5a0e70
    bool __cdecl Drop(::FieldItemDropState, ::vector16);  // 0x5a1180
    bool __cdecl Drop(::FieldItemDropState);  // 0x5a1440
private:
    bool __cdecl consumeUseCount(short);  // 0x5a1600
public:
    bool __cdecl Use(char);  // 0x5a16b0
    bool __cdecl PrepareThrow(::vector16);  // 0x5a1760
    bool __cdecl Throw(void);  // 0x5a1830
private:
    bool __cdecl checkTargetState(unsigned __int64, ::Creature *, ::Data::SkillTargetStateType);  // 0x5a1a50
public:
    virtual void __cdecl OnTimer(::Zone *, unsigned short);  // 0x5a1c70
    void __cdecl Remove(char);  // 0x5a1cb0
private:
    bool __cdecl activate(unsigned __int64);  // 0x5a1e00
    bool __cdecl explode(void);  // 0x5a2020
    bool __cdecl invokeThrowEffect(::Creature *);  // 0x5a22e0
    bool __cdecl invokeEffect(::Creature *, unsigned __int64);  // 0x5a2520
    bool __cdecl checkTargetStateFilter(::Creature *, unsigned __int64) const;  // 0x5a25a0
private:
    char lift_pad_8[0x28 - 8];  // LIFT: base GameObject (+8 to +0x27) is not declared yet
public:
    unsigned __int64 Id;  // +0x28 (PDB: GameObject::Id)
};

class FieldItemIdManager
{
protected:
    virtual bool __cdecl IsExist(unsigned __int64);  // 0x5a06b0
};

class FieldItemList
{
public:
    __cdecl ~FieldItemList(void);  // 0x5a26b0
    bool __cdecl Initialize(::Zone *, int);  // 0x5a2830
    ::FieldItem * __cdecl CreateFieldItem(void);  // 0x5a2920
    bool __cdecl Remove(unsigned __int64);  // 0x5a29d0
    bool __cdecl RemoveAll(void);  // 0x5a2ac0
    // LIFT: PDB members (size 0x20); IdMgr (+0x10) and zone (+0x18) are not declared yet.
    ::FieldItem **FieldItems;  // +0x0
    int Count;  // +0x8
    int MaxSize;  // +0xC
};

