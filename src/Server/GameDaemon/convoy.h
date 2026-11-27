// convoy.h: convoy.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class Convoy
{
public:
    __cdecl Convoy(::Zone *, ::Data::ZoneConvoyRecordPtr);  // 0x40bbd0
    virtual void __cdecl EventOccured(::ScriptEvent const *);  // 0x40bd80
private:
    virtual void __cdecl OnTimer(::Zone *);  // 0x40bdd0
public:
    ::GameFailReason __cdecl CanStart(::Pc *, unsigned char, ::Npc **const);  // 0x40bfa0
    bool __cdecl Start(::Pc *, ::Npc **const);  // 0x40c170
    bool __cdecl AddPc(::Pc *);  // 0x40c630
    bool __cdecl RemovePc(::Pc *);  // 0x40c710
private:
    void __cdecl checkArrived(::GameObject *, ::GameObject *);  // 0x40c780
public:
    void __cdecl OnAttacked(::Pc *, ::Creature *);  // 0x40cdf0
private:
    void __cdecl checkNpcKilled(::GameObject *);  // 0x40ceb0
public:
    void __cdecl OnFailed(::Pc *, ::GameFailReason);  // 0x40d010
private:
    void __cdecl failed(::Pc *, ::GameFailReason);  // 0x40d0b0
public:
    void __cdecl OnDisposeQuest(::Pc *, unsigned __int64);  // 0x40d240
private:
    void __cdecl failedAll(void);  // 0x40d320
    void __cdecl resetAll(void);  // 0x40d780
};

