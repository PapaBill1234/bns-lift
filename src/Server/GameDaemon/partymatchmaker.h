// partymatchmaker.h: partymatchmaker.cpp, partymatchmaker.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class PartyMatchMaker
{
public:
    enum RegisterResult {};
public:
    virtual wchar_t const * __cdecl Name(void);  // 0x180b90
    __cdecl PartyMatchMaker(void);  // 0x18bfa0
    virtual __cdecl ~PartyMatchMaker(void);  // 0x18c080
private:
    virtual void __cdecl run(void);  // 0x18c140
public:
    ::PartyMatchMaker::RegisterResult __cdecl Register(unsigned int, ::Pc *);  // 0x18c600
};

class PartyMatchPoint
{
protected:
    __cdecl PartyMatchPoint(void);  // 0x18b1a0
    __cdecl ~PartyMatchPoint(void);  // 0x18b1f0
private:
    void __cdecl add(::Pc *);  // 0x18b200
    void __cdecl matchPartyToPc(void);  // 0x18b250
    void __cdecl matchPcToPc(void);  // 0x18b3b0
    bool __cdecl findJobInParty(::Pc *, bool *const);  // 0x18b490
    void __cdecl sendFail(::Pc *, short);  // 0x18b710
    void __cdecl sendMatch(::Pc *, ::Pc *);  // 0x18b800
    void __cdecl sendMatch2(::Pc *, ::Pc *);  // 0x18bb40
    bool __cdecl send(::Pc *, ::Pc *, bool);  // 0x18be80
};

class PartyMatchQueue
{
protected:
    __cdecl ~PartyMatchQueue(void);  // 0x18ad50
    void __cdecl clearGarbages(void);  // 0x18add0
    ::Pc * __cdecl pop(int);  // 0x18aff0
    void __cdecl push(int, ::Pc *);  // 0x18b0e0
};

