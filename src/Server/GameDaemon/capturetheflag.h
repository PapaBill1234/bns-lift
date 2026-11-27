// capturetheflag.h: capturetheflag.cpp, capturetheflag.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class CaptureTheFlag : private ::LiftBytes<0xd628 - 8>  // LIFT: PDB base and members +8 to +0xD627 are not declared yet
{
public:
    virtual bool __cdecl Init(::Zone *, unsigned __int64);  // 0x64980
    virtual void __cdecl OnTimer(void);  // 0x64be0
    virtual bool __cdecl CheckToManipulateEnv(::Pc *, ::Env *, ::Data::ZoneEnv2RecordPtr const &);  // 0x64e80
    virtual bool __cdecl TryToManipulateEnv(::Pc *, ::Env *, ::Data::ZoneEnv2RecordPtr &);  // 0x64ee0
    virtual void __cdecl DisposeFieldItem(::Pc *, ::FieldItem *);  // 0x64f50
private:
    bool __cdecl canPlantFlag(::Pc *, ::Env *, ::Data::ZoneEnv2RecordPtr const &);  // 0x65030
    bool __cdecl canStealFlag(::Pc *, ::Env *, ::Data::ZoneEnv2RecordPtr const &);  // 0x65120
public:
    virtual void __cdecl OnEnvManipulated(::Pc *, ::Env *, ::Data::ZoneEnv2RecordPtr const &, char, char);  // 0x651c0
    virtual void __cdecl OnCanceledEnvManipulation(::Env *, ::Data::ZoneEnv2RecordPtr &, char, char);  // 0x652c0
    virtual void __cdecl Reset(void);  // 0x65340
protected:
    virtual int __cdecl getRatingRevise(short);  // 0x654e0
private:
    void __cdecl initEnableFlagSpawnEnv(void);  // 0x65530
    short __cdecl addZoneScorePerSecForAlpha(void);  // 0x655e0
    short __cdecl addZoneScorePerSecForBeta(void);  // 0x65770
    bool __cdecl checkFinishCondForAlpha(void);  // 0x65900
    bool __cdecl checkFinishCondForBeta(void);  // 0x659d0
    void __cdecl onControlPointEnvManipulated(::Pc *, ::Env *, ::Data::ZoneEnv2RecordPtr const &);  // 0x65a80
public:
    virtual void __cdecl OnDead(unsigned __int64, ::Pc *);  // 0x170e30
    virtual __int64 __cdecl Context1(void);  // 0x180ed0
    virtual __int64 __cdecl Context2(void);  // 0x180ee0
private:
    // LIFT: CaptureTheFlag has only part of its PDB members yet (size 0xD648).
    int _flagCount;  // +0xD628
    __int64 _lastFlagSpawnedTime;  // +0xD630
};

