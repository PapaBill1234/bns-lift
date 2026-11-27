// bossskillaction.h: bossskillaction.cpp, bossskillaction.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"
#include "action.h"

class BossLinkLaserSkillAction
{
private:
    bool __cdecl InitializeLinkLaser(::Data::CombatSequenceActionBossLinkLaserAttack const &, ::ScriptEvent const &);  // 0x5fd20
    virtual bool __cdecl prepareAction(void);  // 0x60050
    virtual bool __cdecl invokeExecute(char, unsigned short &);  // 0x602d0
    virtual void __cdecl stateExecute(void);  // 0x60d10
    virtual void __cdecl stateReturn(void);  // 0x60d50
    virtual void __cdecl gatherTarget(char);  // 0x60fa0
    void __cdecl gatherTargetByCube(unsigned __int64, unsigned __int64, unsigned __int64 *const, char *);  // 0x61120
    void __cdecl gatherTargetBounceAngle(::LinkLaserGatheredTargetStruct &);  // 0x61c00
    bool __cdecl executeLinkTerminate(::Data::CombatSequenceLinkLaserTerminateCondType);  // 0x61f10
    virtual void __cdecl broadcastSkill(::SkillFlowCode);  // 0x62180
    virtual void __cdecl cancelAction(::Action::CancelReason, wchar_t const *, int);  // 0x621b0
    virtual short __cdecl getDashAngle(unsigned __int64);  // 0x62200
    void __cdecl broadcastLinkLaserSkill(::SkillFlowCode);  // 0x62280
};

class BossMultigroundSkillAction
{
private:
    __cdecl BossMultigroundSkillAction(unsigned __int64 const *const, int);  // 0x5bf30
    virtual bool __cdecl prepareAction(void);  // 0x5dfa0
    bool __cdecl setTargetPositions(void);  // 0x5dff0
    virtual void __cdecl broadcastSkill(::SkillFlowCode);  // 0x5e150
    void __cdecl broadcastMultigroundSkill(::SkillFlowCode);  // 0x5e170
    virtual bool __cdecl invokeExecute(char, unsigned short &);  // 0x5e4b0
    virtual void __cdecl stateReturn(void);  // 0x5e630
    virtual void __cdecl gatherTarget(char);  // 0x5e800
};

class BossRepeaterGroundSkillAction
{
private:
    __cdecl BossRepeaterGroundSkillAction(bool, char, unsigned __int64);  // 0x5d900
    bool __cdecl checkTargetExceptCond(void);  // 0x5d990
    virtual bool __cdecl prepareAction(void);  // 0x5da70
    virtual void __cdecl stateFly(void);  // 0x5dbb0
    virtual void __cdecl stateReturn(void);  // 0x5dc30
    unsigned __int64 __cdecl getNextTarget(void);  // 0x5de20
};

class BossRepeaterSkillAction
{
private:
    bool __cdecl checkTargetExceptCond(void);  // 0x5d3a0
    virtual bool __cdecl prepareAction(void);  // 0x5d480
    virtual void __cdecl stateReturn(void);  // 0x5d5c0
    unsigned __int64 __cdecl getNextTarget(void);  // 0x5d7b0
};

class BossRushSkillAction
{
private:
    virtual bool __cdecl prepareAction(void);  // 0x5c050
    virtual void __cdecl intervalAction(long);  // 0x5c2a0
    virtual void __cdecl stateReturn(void);  // 0x5c330
    void __cdecl executeMove(long);  // 0x5c510
    bool __cdecl move(::vector16 const &, long);  // 0x5c770
    bool __cdecl isSameCell(::vector16 const &, ::vector16 const &);  // 0x5ca10
    static ::vector16 __cdecl getPosInBoundary(::GeoZone const *, ::vector16 const &, ::vector16 const &);  // 0x5cbe0
    virtual bool __cdecl invokeExecute(char, unsigned short &);  // 0x5cd00
    virtual void __cdecl gatherTarget(char);  // 0x5cf60
    bool __cdecl invokeEffect(unsigned __int64, unsigned __int64, unsigned __int64);  // 0x5d320
};

class BossSimultaneousCasterSkillAction
{
public:
    __cdecl BossSimultaneousCasterSkillAction(long);  // 0x5bfc0
    virtual void __cdecl stateExecute(void);  // 0x5f110
    virtual bool __cdecl prepareAction(void);  // 0x5f150
    virtual void __cdecl broadcastSkill(::SkillFlowCode);  // 0x5f260
    virtual void __cdecl stateCast(void);  // 0x5f580
    virtual void __cdecl stateReturn(void);  // 0x5f5e0
    virtual bool __cdecl invokeExecute(char, unsigned short &);  // 0x5f800
    virtual void __cdecl gatherTarget(char);  // 0x5f8f0
};

class BossSimultaneousGroundSkillAction
{
public:
    virtual bool __cdecl prepareAction(void);  // 0x5ec80
    virtual void __cdecl broadcastSkill(::SkillFlowCode);  // 0x5ed90
};

class BossSkillFactory
{
public:
    static ::SkillAction * __cdecl CreateBossRushSkillAction(::Npc &, unsigned __int64, ::vector16, short, unsigned __int64, unsigned __int64, bool);  // 0x625e0
    static ::SkillAction * __cdecl CreateBossRepeaterSkillAction(::Npc &, unsigned __int64, ::Creature *, bool, char);  // 0x62850
    static ::SkillAction * __cdecl CreateBossSimultaneousGroundSkillAction(::Npc &, unsigned __int64, ::Creature *, long);  // 0x62b60
    static ::SkillAction * __cdecl CreateBossSimultaneousCasterSkillAction(::Npc &, ::Creature *, unsigned __int64, long);  // 0x62d50
    static ::SkillAction * __cdecl CreateBossLinkLaserSkillAction(::Npc &, ::Data::CombatSequenceActionBossLinkLaserAttack const &, ::ScriptEvent const &);  // 0x62f10
};

