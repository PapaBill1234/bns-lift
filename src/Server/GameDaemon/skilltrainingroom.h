// skilltrainingroom.h: skilltrainingroom.cpp, skilltrainingroom.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class SkillTrainingRoom
{
public:
    virtual wchar_t const * __cdecl GetTypeName(void);  // 0x180e40
    virtual bool __cdecl Init(::Zone *, bool);  // 0x1bcfa0
    virtual void __cdecl LeaveAttractionZone(::Pc *);  // 0x1bd090
    virtual void __cdecl OnEntered(::Zone *, ::Creature *, ::EnterReason);  // 0x1bd550
    virtual void __cdecl OnLeaved(::Zone *, ::Creature *, ::LeaveReason);  // 0x1bd7b0
    void __cdecl Start(::Pc *, unsigned __int64, char);  // 0x1bd950
private:
    bool __cdecl spawnResetStageNpc(::Zone *, ::Data::NpcResetStageRecordPtr const &);  // 0x1bdff0
    bool __cdecl spawnSupportNpc(::Zone *, unsigned __int64);  // 0x1be140
    bool __cdecl doEnvOperation(::Zone *, ::Data::NpcResetStageRecordPtr const &);  // 0x1be1e0
public:
    void __cdecl Stop(::Pc *, char);  // 0x1be3b0
    void __cdecl Restart(::Pc *);  // 0x1be600
    void __cdecl InitCreatureState(::Pc *);  // 0x1bea00
private:
    bool __cdecl initZoneState(::Pc *, ::Zone *);  // 0x1bed00
    bool __cdecl clearNpcReg(::Zone *, ::Data::NpcResetStageRecordPtr const &);  // 0x1beea0
    void __cdecl clearEnv(::Zone *, ::Data::NpcResetStageRecordPtr const &);  // 0x1befd0
    void __cdecl initPlayerState(::Pc *, bool);  // 0x1bf140
    void __cdecl initNpcState(::Pc *);  // 0x1bf5f0
    void __cdecl remainEffects(::Pc *);  // 0x1bf750
    void __cdecl invokeSubjectEffect(::Pc *, bool);  // 0x1bf790
    ::Pc * __cdecl getPlayer(::Zone *);  // 0x1bfa50
    void __cdecl WriteSkillTrainingRoomLog(::Pc *, int);  // 0x1bfab0
};

