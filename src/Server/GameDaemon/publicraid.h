// publicraid.h: publicraid.cpp, publicraid.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class EnterPublicRaidAttractionState
{
public:
    virtual void __cdecl SetRoomInfo(::Zone *, ::ArenaLobbyRoomInfo const &, bool);  // 0x1a0cf0
protected:
    bool __cdecl setMaxReservePcCountTouched(::Zone *, bool);  // 0x1a0d70
public:
    bool __cdecl IncrementReservePcCount(::Zone *, int);  // 0x1a0dd0
protected:
    bool __cdecl decrementReservePcCount(::Pc *, ::Zone *, int);  // 0x1a0ed0
    bool __cdecl checkReservePcCount(::Pc *, ::Zone *, int, int);  // 0x1a10b0
};

// LIFT: views of the PDB record Data::PublicRaidRecord (base DrEl, size 0xB0) and of Data::PublicRaidRecordPtr.
// Only the fields that the lifted bodies read are declared.
struct PublicRaidRecordView
{
    char lift_pad_0[0x20];  // ❓ no PDB name: fields +0 to +0x1F are not declared yet
    char max_pc_count;  // +32 (0x20)
};

class PublicRaidRecordPtrView
{
public:
    ::PublicRaidRecordView *_record;  // 0x0 (PDB: DrRecordPtr::_record, DrEl *)
};

class PublicRaid
{
public:
    virtual wchar_t const * __cdecl GetTypeName(void);  // 0x180e50
    virtual int __cdecl GetMaxPcCount(void);  // 0x180e60
    virtual __cdecl ~PublicRaid(void);  // 0x1a1120
    virtual bool __cdecl Init(::Zone *, bool);  // 0x1a11a0
    virtual void __cdecl OnEntered(::Zone *, ::Creature *, ::EnterReason);  // 0x1a13e0
    virtual void __cdecl OnLeaved(::Zone *, ::Creature *, ::LeaveReason);  // 0x1a1500
    virtual void __cdecl OnBossCombatEnd(::Zone *, ::Creature *);  // 0x1a1660
    void __cdecl SetContentQuota(::Pc *);  // 0x1a16a0
    virtual bool __cdecl CanJoinState(::Pc *, ::Zone *);  // 0x1a17c0
    bool __cdecl CanPreserveSessionState(::Pc *);  // 0x1a1840
    virtual void __cdecl OnZoneAttractionTimer(::Zone *);  // 0x1a1910
private:
    bool __cdecl onTimeCheck(::Zone *);  // 0x1a19e0
    bool __cdecl onStandBy(::Zone *);  // 0x1a1a70
    bool __cdecl onStart(::Zone *);  // 0x1a1ba0
    bool __cdecl onFinish(::Zone *);  // 0x1a1ec0
public:
    bool __cdecl SetPublicRaidEvent(::Zone *, unsigned __int64);  // 0x1a1f60
private:
    bool __cdecl executePublicRaidEvent(void);  // 0x1a2120
public:
    bool __cdecl AddScore(::Zone *, ::Pc *);  // 0x1a2220
    void __cdecl ReduceScore(::Zone *);  // 0x1a2410
private:
    void __cdecl stopPublicRaidEvent(bool);  // 0x1a24c0
    bool __cdecl setEventAttendee(void);  // 0x1a2840
    char __cdecl setEffectTargetInfoAtEventFinish(unsigned __int64 *const, unsigned __int64 *const, unsigned __int64 *const, unsigned __int64 *const);  // 0x1a2ac0
    void __cdecl invokeNpcEffectAtEventFinish(unsigned __int64 const *const, int, unsigned __int64 const *const, int);  // 0x1a2e70
    void __cdecl invokePcEffectAtEventFinish(unsigned __int64 const *const, int, unsigned __int64 const *const, int);  // 0x1a3000
    void __cdecl invokeSummonedEffectAtEventFinish(::Summoned *, unsigned __int64 const *const, int);  // 0x1a32e0
    bool __cdecl invokeEffect(unsigned __int64, unsigned __int64, unsigned __int64);  // 0x1a33b0
    void __cdecl broadcastPublicRaidEventStart(unsigned __int64);  // 0x1a3460
    void __cdecl broadcastPublicRaidEventScore(short);  // 0x1a3630
    void __cdecl broadcastPublicRaidEventStop(short);  // 0x1a3800
    void __cdecl doEnvOperation(void);  // 0x1a39f0
    bool __cdecl getEventCylinder(::cylinder16 &);  // 0x1a3b40
private:
    // PDB layout (size 0xD3A8). The vfptr is at +0.
    char lift_pad_8[0xD340];  // ❓ no PDB name: base EnterPublicRaidAttractionState and _state (+8 to +0xD347) are not declared yet
    ::PublicRaidRecordPtrView _data;  // +54088 (0xD348) (PDB: Data::PublicRaidRecordPtr)
};

class PublicRaidGameLog
{
public:
    static void __cdecl WritePublicRaidDisconnected(::Pc *, unsigned __int64, char);  // 0x1a3cc0
    static void __cdecl WritePublicRaidFinishTeam(::Zone *, unsigned __int64);  // 0x1a3e50
    static void __cdecl WritePublicRaidStartPc(::Pc *, unsigned __int64);  // 0x1a4030
    static void __cdecl WritePublicRaidFinishPc(::Pc *, unsigned __int64);  // 0x1a41c0
};

