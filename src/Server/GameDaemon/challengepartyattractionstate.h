// challengepartyattractionstate.h: challengepartyattractionstate.cpp, challengepartyattractionstate.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"
#include "attractionstate.h"

class ChallengePartyAttractionState
{
public:
    virtual ::ATTRACTION_STATE_TYPE __cdecl GetType(void);  // 0x35f20
    virtual wchar_t const * __cdecl GetTypeName(void);  // 0x35f30
    virtual void __cdecl SetAttractionOption(char);  // 0x35f40
    virtual bool __cdecl Init(::Zone *, bool);  // 0x6b7e0
    virtual void __cdecl LeaveAttractionZone(::Pc *);  // 0x6b920
    virtual void __cdecl ReviveByAttractionRule(::Pc *);  // 0x6bde0
    virtual bool __cdecl OnZoneOpen(::Zone *, bool);  // 0x6be40
    virtual void __cdecl OnZoneAttractionTimer(::Zone *);  // 0x6be60
    virtual void __cdecl OnEntered(::Zone *, ::Creature *, ::EnterReason);  // 0x6bf70
    virtual void __cdecl OnBossCombatStart(::Zone *, ::Creature *);  // 0x6c1e0
    virtual void __cdecl OnBossCombatEnd(::Zone *, ::Creature *);  // 0x6c2b0
    virtual void __cdecl OnDamagedEvent(::Zone *, ::Npc *const, ::Creature *, __int64);  // 0x6c300
    virtual void __cdecl PatternStart(::Zone *, char);  // 0x6c350
    virtual void __cdecl PatternFinish(::Zone *, char, bool, bool);  // 0x6c8f0
    void __cdecl ResetEnvOperation(::Zone *);  // 0x6cfe0
private:
    void __cdecl initEnvOperation(::Zone *);  // 0x6d070
    bool __cdecl changeEnvState(::Zone *, unsigned __int64, char);  // 0x6d1c0
    void __cdecl start(::Zone *);  // 0x6d2d0
    void __cdecl finish(::Zone *, bool);  // 0x6dc00
    void __cdecl calcScore(::Zone *, bool);  // 0x6ea60
    void __cdecl calcPatternScore(::Zone *);  // 0x6ec40
    void __cdecl initPatternScore(::Zone *);  // 0x6ee50
    bool __cdecl isTimeOut(::Zone *);  // 0x6eeb0
    void __cdecl initPlayerState(::Pc *);  // 0x6ef00
    // LIFT: the PDB members before +16 are not declared yet; pad keeps _attractionOption at +16.
    __int64 _padTo16;  // +8 (_data)
    char _attractionOption;  // +16
public:
    virtual __cdecl ~ChallengePartyAttractionState(void);  // 0x6f370
    virtual ::AttractionState::ERROR_REASON __cdecl CanTeamAttractionWithTarget(::Pc *, ::Creature *);  // 0x6f3e0
};

