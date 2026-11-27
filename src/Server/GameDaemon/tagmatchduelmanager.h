// tagmatchduelmanager.h: tagmatchduelmanager.cpp, tagmatchduelmanager.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class TagMatchDuelManager
{
public:
    enum FighterChangeReason {};
private:
    virtual bool __cdecl verifyDuelType(void) const;  // 0x4c390
    virtual ::DuelRule *const __cdecl instantiateDuelRule(void);  // 0x4c3a0
    virtual ::DuelTeam *const __cdecl instantiateDuelTeam(int);  // 0x4c400
public:
    bool __cdecl ChooseDuelOrder(unsigned __int64, char, short &);  // 0x1d0cb0
    bool __cdecl TakeTagToken(unsigned __int64, short &);  // 0x1d10c0
    bool __cdecl CanChangeFighter(::Pc const *const, ::TagMatchDuelManager::FighterChangeReason) const;  // 0x1d14d0
    bool __cdecl CanChangeFighter(::TagMatchDuelMember const *const, ::TagMatchDuelManager::FighterChangeReason) const;  // 0x1d15d0
    bool __cdecl CanInterfere(::Pc const *const) const;  // 0x1d17c0
    bool __cdecl CanInterfere(::TagMatchDuelMember const *const) const;  // 0x1d18a0
    bool __cdecl CanStopInterference(::TagMatchDuelMember const *const) const;  // 0x1d1a40
    bool __cdecl ChangeFighter(::Pc const *const, ::TagMatchDuelManager::FighterChangeReason);  // 0x1d1b50
    bool __cdecl InterfereInFight(::Pc const *const);  // 0x1d2d10
    bool __cdecl StopInterference(::Pc const *const, bool);  // 0x1d3390
    virtual void __cdecl OnEventTimer(void);  // 0x1d36d0
private:
    virtual void __cdecl handleOnDead(::DuelMember *const);  // 0x1d3920
    virtual void __cdecl handleOnLeave(::DuelMember *const);  // 0x1d39c0
    void __cdecl onEliminate(::DuelMember *const, ::TagMatchDuelManager::FighterChangeReason);  // 0x1d3a60
    ::TagMatchDuelMember *const __cdecl getReplacementMember(int, ::TagMatchDuelManager::FighterChangeReason);  // 0x1d4640
    ::TagMatchDuelMember const *const __cdecl getOppositeFightMember(int) const;  // 0x1d46d0
    virtual void __cdecl readyByForce(void);  // 0x1d4740
    void __cdecl arrangeDuelOrder(bool);  // 0x1d47f0
    virtual void __cdecl startRound(void);  // 0x1d4ce0
    virtual void __cdecl enterToArena(void);  // 0x1d4d60
    virtual void __cdecl leaveFromArena(void);  // 0x1d4fa0
    virtual void __cdecl rearrangeDuelMember(::DuelTeam *const);  // 0x1d51b0
    virtual void __cdecl resetRound(void);  // 0x1d5570
    bool __cdecl replaceAbsentFighter(::TagMatchDuelMember *const);  // 0x1d5590
    void __cdecl prepareMoveInto(::TagMatchDuelMember *const, bool);  // 0x1d5810
    void __cdecl prepareMoveOut(::TagMatchDuelMember *const, bool);  // 0x1d5b30
    bool __cdecl setInsideMoveDest(int, int, ::DuelMoveInfo &);  // 0x1d5fa0
    bool __cdecl setOutsideMoveDest(int, int, ::DuelMoveInfo &);  // 0x1d6130
    void __cdecl moveDuelMember(::Pc *const, ::DuelMoveInfo const &);  // 0x1d6350
    void __cdecl invokeFighterTimeLimitEffect(::TagMatchDuelMember *const) const;  // 0x1d6980
    virtual void __cdecl invokeArenaOutsideRoundStartEffect(::DuelMember *const) const;  // 0x1d6ae0
    void __cdecl invokeTagIntoEffectBySkill(::TagMatchDuelMember *const) const;  // 0x1d6d10
    void __cdecl invokeTagIntoEffectBySystem(::TagMatchDuelMember *const) const;  // 0x1d6f10
    void __cdecl invokeTagOutEffect(::TagMatchDuelMember *const) const;  // 0x1d7110
    void __cdecl invokeInterferenceIntoEffect(::TagMatchDuelMember *const) const;  // 0x1d7310
    void __cdecl invokeInterferenceOutEffect(::TagMatchDuelMember *const) const;  // 0x1d7510
    virtual ::Data::ZonePcSpawnRecordPtr const __cdecl getRoundStartPcSpawn(int, int) const;  // 0x1d7710
};

class TagMatchDuelMember
{
public:
    virtual bool __cdecl ReadyRound(short &);  // 0x1d04b0
    virtual void __cdecl ResetRound(void);  // 0x1d0560
};

class TagMatchDuelRule
{
public:
    virtual ::DuelRoundResult const __cdecl CalcRoundResult(::Zone *const);  // 0x1d0b00
};

class TagMatchDuelTeam
{
private:
    virtual ::DuelMember *const __cdecl instantiateDuelMember(int, int, ::Pc *const);  // 0x4c290
public:
    void __cdecl GiveTagToken(::TagMatchDuelMember const *const);  // 0x1d05c0
    void __cdecl SetTagTokenOwnerMember(::TagMatchDuelMember *const, wchar_t const *, int);  // 0x1d0670
    virtual void __cdecl Dump(wchar_t *, unsigned __int64);  // 0x1d0800
private:
    virtual void __cdecl onLeave(::DuelMember *const);  // 0x1d0a60
public:
    virtual void __cdecl ResetRound(void);  // 0x1d0ae0
};

