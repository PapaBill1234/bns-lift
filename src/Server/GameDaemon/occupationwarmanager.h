// occupationwarmanager.h: occupationwarmanager.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class OccupationWarManager
{
public:
    virtual bool __cdecl Init(::Zone *, unsigned __int64);  // 0x170b00
    virtual void __cdecl OnTimer(void);  // 0x170c10
    virtual bool __cdecl TryToManipulateEnv(::Pc *, ::Env *, ::Data::ZoneEnv2RecordPtr &);  // 0x170ff0
    virtual void __cdecl OnEnvManipulated(::Pc *, ::Env *, ::Data::ZoneEnv2RecordPtr const &, char, char);  // 0x171160
    virtual void __cdecl OnCanceledEnvManipulation(::Env *, ::Data::ZoneEnv2RecordPtr &, char, char);  // 0x171500
    virtual void __cdecl Reset(void);  // 0x171540
private:
    void __cdecl addZoneScorePerSec(void);  // 0x171600
    void __cdecl manipulateEnv(::Env *, ::Data::ZoneEnv2RecordPtr const &, char, char);  // 0x171880
protected:
    virtual int __cdecl getRatingRevise(short);  // 0x1719a0
};

