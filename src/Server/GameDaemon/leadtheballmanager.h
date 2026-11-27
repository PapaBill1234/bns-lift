// leadtheballmanager.h: leadtheballmanager.cpp, leadtheballmanager.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class DeleteEvent
{
public:
    virtual unsigned int __cdecl EventId(void) const;  // 0x137a30
    virtual bool __cdecl HandleEvent(::EventContext *, unsigned long);  // 0x6a1a50
};

class LeadTheBallManager
{
public:
    virtual __int64 __cdecl Context1(void);  // 0x137a40
    __cdecl LeadTheBallManager(void);  // 0x137a90
    virtual bool __cdecl Init(::Zone *, unsigned __int64);  // 0x137b50
    virtual void __cdecl OnTimer(void);  // 0x137f40
    virtual bool __cdecl EnterNpc(::Npc *);  // 0x1381d0
    virtual bool __cdecl TryToManipulateEnv(::Pc *, ::Env *, ::Data::ZoneEnv2RecordPtr &);  // 0x1382d0
    virtual void __cdecl OnDead(unsigned __int64, ::Pc *);  // 0x138380
    virtual void __cdecl OnEnvManipulated(::Pc *, ::Env *, ::Data::ZoneEnv2RecordPtr const &, char, char);  // 0x138550
    virtual void __cdecl OnCanceledEnvManipulation(::Env *, ::Data::ZoneEnv2RecordPtr &, char, char);  // 0x138720
    virtual void __cdecl OnEnterFootSwitch(::Creature *, ::Env *, ::Data::ZoneEnv2RecordPtr const &);  // 0x138770
    virtual void __cdecl Reset(void);  // 0x138970
protected:
    virtual int __cdecl getRatingRevise(short);  // 0x138bb0
private:
    void __cdecl setEnvInitState(void);  // 0x138c00
    void __cdecl setEnvInitEnable(void);  // 0x138d30
    void __cdecl changeInGameSubStep(void);  // 0x138f40
    bool __cdecl invokeEffect(unsigned __int64, unsigned __int64, unsigned __int64);  // 0x139040
    bool __cdecl checkSpawnBall(void);  // 0x1390f0
    void __cdecl spawnBall(void);  // 0x139200
    void __cdecl addZoneScoreGoalIn(char, bool);  // 0x1394e0
    void __cdecl sendGoalInCountInfo(void);  // 0x139760
public:
    virtual __int64 __cdecl Context2(void);  // 0x1ee470
};

