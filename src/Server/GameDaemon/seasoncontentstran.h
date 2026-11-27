// seasoncontentstran.h: seasoncontentstran.cpp, seasoncontentstran.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class DuelResultTran
{
public:
    virtual ::GameTranDef const * __cdecl GetDefinition(void) const;  // 0x180c80
    static ::GameTranDef _def;  // LIFT: PDB data DuelResultTran::_def
    __cdecl DuelResultTran(::User *);  // 0x1b8520
private:
    virtual bool __cdecl work(int, void *);  // 0x1b8590
    bool __cdecl init(int, void *);  // 0x1b8610
    bool __cdecl updateSeasonContentsCombatRecordTry(void);  // 0x1b8870
    bool __cdecl updateSeasonContentsCombatRecordOk(void *);  // 0x1b89c0
    bool __cdecl updateSeasonContentsCombatRecordFail(short);  // 0x1b8ee0
    void __cdecl writeGameLog(::Pointer2< ::Pc>);  // 0x1b9170
};

class PartyBattleResultTran
{
public:
    virtual ::GameTranDef const * __cdecl GetDefinition(void) const;  // 0x180c70
    static ::GameTranDef _def;  // LIFT: PDB data PartyBattleResultTran::_def
    __cdecl PartyBattleResultTran(::User *);  // 0x1b7610
private:
    virtual bool __cdecl work(int, void *);  // 0x1b7680
    bool __cdecl init(int, void *);  // 0x1b7700
    bool __cdecl updateSeasonContentsCombatRecordTry(void);  // 0x1b7960
    bool __cdecl updateSeasonContentsCombatRecordOk(void *);  // 0x1b7ab0
    bool __cdecl updateSeasonContentsCombatRecordFail(short);  // 0x1b7fd0
    void __cdecl writeGameLog(::Pointer2< ::Pc>);  // 0x1b8230
};

class TimeAttackRecordResultTran
{
public:
    virtual ::GameTranDef const * __cdecl GetDefinition(void) const;  // 0x180c90
    static ::GameTranDef _def;  // LIFT: PDB data TimeAttackRecordResultTran::_def
private:
    virtual bool __cdecl work(int, void *);  // 0x1b9460
    bool __cdecl init(int, void *);  // 0x1b94e0
    bool __cdecl updateSeasonContentsTimeAttackRecordTry(void);  // 0x1b9740
    bool __cdecl updateSeasonContentsTimeAttackRecordOk(void *);  // 0x1b9890
    bool __cdecl updateSeasonContentsTimeAttackRecordFail(short);  // 0x1b9d90
};

