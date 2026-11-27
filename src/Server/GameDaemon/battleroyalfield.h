// battleroyalfield.h: battleroyalfield.cpp, battleroyalfield.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class BattleRoyalField
{
public:
    virtual wchar_t const * __cdecl GetTypeName(void);  // 0x35f60
    __cdecl BattleRoyalField(void);  // 0x51440
    virtual __cdecl ~BattleRoyalField(void);  // 0x515d0
    virtual bool __cdecl CanJoinState(::Pc *, ::Zone *);  // 0x51700
    virtual int __cdecl GetMaxPcCount(void);  // 0x517c0
    virtual bool __cdecl Init(::Zone *, bool);  // 0x51890
    virtual void __cdecl OnEntered(::Zone *, ::Creature *, ::EnterReason);  // 0x51e70
private:
    bool __cdecl isWinnerPc(::Zone *, ::Pc *);  // 0x52480
public:
    virtual void __cdecl OnLeaved(::Zone *, ::Creature *, ::LeaveReason);  // 0x52600
    virtual void __cdecl OnKill(::Zone *, ::GameObject *, ::Creature *);  // 0x52e50
    void __cdecl SetBattleRoyalFieldStateForDebug(::Zone *, char);  // 0x53060
    virtual void __cdecl OnZoneAttractionTimer(::Zone *);  // 0x531a0
private:
    bool __cdecl checkStandBy(::Zone *);  // 0x53240
    bool __cdecl standBy(::Zone *);  // 0x53410
    bool __cdecl onStandBy(::Zone *);  // 0x53630
    bool __cdecl start(::Zone *);  // 0x537b0
    void __cdecl setEventAreaInfo(void);  // 0x53980
    bool __cdecl onStart(::Zone *);  // 0x53aa0
    void __cdecl setBattleRoyalFieldStartTime(__int64);  // 0x53d70
    void __cdecl setCombatStartTime(::Zone *, __int64);  // 0x53e10
    bool __cdecl inProgress(::Zone *);  // 0x53ec0
    bool __cdecl onInProgress(::Zone *);  // 0x54090
    bool __cdecl finish(::Zone *);  // 0x541a0
    bool __cdecl onFinish(::Zone *);  // 0x542e0
public:
    bool __cdecl IsPartyMode(void);  // 0x544e0
    virtual bool __cdecl IsArenaMathcing(void);  // 0x54520
protected:
    virtual void __cdecl onIncrementReservePcCountAttractionRule(::Zone *, int);  // 0x54530
private:
    void __cdecl doEnvOperation(::Zone *);  // 0x54660
    bool __cdecl executeBattleRoyalFieldEvent(::Zone *);  // 0x547d0
    bool __cdecl invokeEventEffect(::Zone *, int);  // 0x54fe0
    bool __cdecl invokeEffect(::Zone *, unsigned __int64, unsigned __int64, unsigned __int64);  // 0x555e0
    bool __cdecl startEvent(::Zone *);  // 0x556d0
    bool __cdecl stopEvent(::Zone *);  // 0x557e0
    bool __cdecl setNextEventIndex(::Zone *);  // 0x55a60
    bool __cdecl calculateEventCenterPos(void);  // 0x55b70
public:
    virtual void __cdecl OnDead(::Zone *, unsigned __int64, ::Creature *);  // 0x55e20
    bool __cdecl CheckToFinishGame(void);  // 0x56440
    virtual void __cdecl OnDamagedEvent(::Zone *, ::ControlledCreature *const, ::Creature *, __int64);  // 0x56550
    bool __cdecl GetFinishRespawnArea(::Pc *, unsigned int &, unsigned __int64 &);  // 0x567f0
    virtual bool __cdecl CanResurrect(::ControlledCreature const *);  // 0x568e0
    static wchar_t * __cdecl GetStateName(char);  // 0x56ab0
    static wchar_t * __cdecl GetPartyStateName(char);  // 0x56b00
    static wchar_t * __cdecl GetPcCombatSideName(char);  // 0x56b40
    virtual void __cdecl TakeAttractionReward(::Pc *);  // 0x56bb0
private:
    void __cdecl processBattleRoyalResultTran(::Pc *, char);  // 0x56bd0
    bool __cdecl startBattleRoyalResultTran(::Pc *, char, ::DuelResultTranResultNotifyInfo const &);  // 0x571c0
public:
    virtual bool __cdecl EnableInfiniteHyperEnergy(void) const;  // 0x57720
    virtual bool __cdecl EnableArenaEventReturnToArenaLobbyAllPc(void);  // 0x57730
    void __cdecl FetchBattleRoyalScore(::Packet &, ::RepeatPacketComposer &);  // 0x57740
};

class BattleRoyalFieldGameLog
{
public:
    static void __cdecl WriteBattleRoyalFieldEnd(::Zone *, unsigned __int64, wchar_t *, char);  // 0x5b630
    static void __cdecl WriteBattleRoyalFieldStartPc(::Pc *, unsigned __int64, wchar_t *);  // 0x5b700
    static void __cdecl WriteBattleRoyalFieldEndPc(::Pc *, unsigned __int64, wchar_t *, char, char, char);  // 0x5b900
    static void __cdecl WriteLootBattleRoyalFieldDroppedItem(::Pc *, unsigned __int64, unsigned __int64, __int64);  // 0x5bb50
    static void __cdecl WriteBattleRoyalFieldRewardItem(::Pc *, unsigned __int64, __int64, __int64);  // 0x5bd40
};

class BattleRoyalFieldPlayerManager
{
public:
    __cdecl BattleRoyalFieldPlayerManager(void);  // 0x51650
    bool __cdecl PlayerEnter(::Zone *, ::Pc *);  // 0x57840
    void __cdecl PlayerLeave(::Zone *, ::Pc *);  // 0x57980
private:
    bool __cdecl partyEnter(::Zone *, ::Pc *);  // 0x57b00
    void __cdecl partyLeave(::Zone *, ::Pc *);  // 0x57c50
public:
    bool __cdecl AllPlayerStartGame(::Zone *, unsigned __int64, wchar_t *);  // 0x57d70
private:
    bool __cdecl allPartyStartGame(::Zone *);  // 0x581f0
public:
    bool __cdecl AllPlayerFinishGame(::Zone *);  // 0x58370
    bool __cdecl PlayerFinishGame(::Zone *, ::Pc *, bool);  // 0x58890
private:
    void __cdecl partyFinishGame(::Zone *, ::Pc *);  // 0x58cc0
public:
    ::BattleRoyalFieldPlayer __cdecl GetPlayerRecord(::Zone *, unsigned __int64);  // 0x58e30
    char __cdecl GetPlayerState(::Zone *, unsigned __int64);  // 0x58fd0
    char __cdecl GetPlayerKillCount(unsigned __int64);  // 0x59110
    void __cdecl IncreaseKillPcCount(::Zone *, ::Pc *);  // 0x59160
    int __cdecl GetPlayerAttackDamage(unsigned __int64);  // 0x59270
    void __cdecl AddAttackDamage(::Zone *, ::Pc *, int);  // 0x592c0
    char __cdecl GetPlayerRanking(unsigned __int64);  // 0x594f0
    bool __cdecl SetAllPlayerCombatSide(::Zone *, char);  // 0x59530
private:
    bool __cdecl insertPlayerRecord(::Zone *, ::Pc *);  // 0x59800
    void __cdecl resetPlayerRecord(::Zone *, unsigned __int64);  // 0x59b60
    bool __cdecl insertPartyRecord(::Zone *, ::Pc *);  // 0x59cf0
    void __cdecl resetPartyRecord(::Zone *, unsigned __int64);  // 0x59df0
    void __cdecl increasePlayingPartyMemberCount(::Zone *, ::Pc *);  // 0x59ec0
    void __cdecl decreasePlayingPartyMemberCount(::Zone *, ::Pc *);  // 0x5a010
    bool __cdecl isMemberCountZero(::Zone *, ::Pc *);  // 0x5a160
    bool __cdecl setPartyState(::Zone *, unsigned __int64, char);  // 0x5a290
    bool __cdecl setPlayerRanking(::Zone *, ::Pc *, bool);  // 0x5a420
    bool __cdecl setPlayerCombatSide(::Zone *, ::Pc *, char);  // 0x5a6c0
    void __cdecl initAllPlayer(::Zone *);  // 0x5a8c0
    void __cdecl increasePlayingPcCount(::Zone *, unsigned __int64);  // 0x5ad70
    void __cdecl decreasePlayingPcCount(::Zone *, unsigned __int64);  // 0x5b010
    void __cdecl increasePlayingPartyCount(::Zone *, ::Pc *);  // 0x5b2b0
    void __cdecl decreasePlayingPartyCount(::Zone *, ::Pc *);  // 0x5b3d0
public:
    void __cdecl WriteBattleRoyalFieldStartPcLog(::Zone *, unsigned __int64, wchar_t *);  // 0x5b4f0
};

