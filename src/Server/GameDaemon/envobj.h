// envobj.h: envobj.cpp, envobj.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class AirDash
{
public:
    virtual bool __cdecl CheckToManipulate(::Pc *, ::Item *, ::QuestRequiredItems const *, char, short &);  // 0x455430
    short __cdecl CheckAvailableAirDash(::Pc *);  // 0x59f010
    bool __cdecl ExecuteAirDash(::ControlledCreature *, long &);  // 0x59f240
};

class AirDashLeave
{
public:
    short __cdecl CheckAvailableAirDash(::Pc *);  // 0x59f810
    bool __cdecl ExecuteAirDash(::Pc *);  // 0x59f970
};

class ControlPoint
{
public:
    virtual bool __cdecl CheckToManipulate(::Pc *, ::Item *, ::QuestRequiredItems const *, char, short &);  // 0x59bf40
    virtual void __cdecl Manipulate(::Pc *, ::Item *, ::QuestRequiredItems const *, char);  // 0x59c190
    virtual void __cdecl ChangeState(char);  // 0x59c1e0
    virtual void __cdecl InitState(void);  // 0x59c200
    void __cdecl CancelOccupation(void);  // 0x59c310
    virtual bool __cdecl Initialize(unsigned __int64, ::Zone *, ::GeoEnvObj const *);  // 0x59c390
};

class EffectRegion
{
public:
    virtual void __cdecl OnLeaved(::Zone *, ::Creature *);  // 0x59c8c0
    virtual void __cdecl InitState(void);  // 0x59e330
    virtual void __cdecl OnEntered(::Zone *, ::Creature *);  // 0x59e360
    void __cdecl ApplyEffect(::Creature *, bool);  // 0x59e620
    virtual void __cdecl SetEnable(bool);  // 0x59e780
protected:
    virtual void __cdecl OnTimer(::Zone *, unsigned short);  // 0x59eb20
};

// LIFT: views of the PDB records Data::ZoneEnv2Record and Data::ZoneEnv2PlaceRecord (base DrEl, size 6).
// Only the fields that the lifted bodies read are declared.
struct EnvZoneEnv2RecordView
{
    char lift_pad_0[0x68];
    long manipulate_duration;  // +104 (0x68)
};

struct EnvZoneEnv2PlaceRecordView
{
    char lift_pad_0[0x38];
    short action_radius;  // +56 (0x38)
};

class EnvZoneEnv2PtrView
{
public:
    ::EnvZoneEnv2RecordView *_record;  // 0x0 (PDB: DrRecordPtr::_record, DrEl *)
};

class EnvZoneEnv2PlacePtrView
{
public:
    ::EnvZoneEnv2PlaceRecordView *_record;  // 0x0 (PDB: DrRecordPtr::_record, DrEl *)
};

class Env
{
public:
    virtual short __cdecl GetActionRadius(void);  // 0x4553f0
    virtual long __cdecl GetManipulateDuration(char);  // 0x455400
    virtual unsigned __int64 __cdecl GetOwnerId(void);  // 0x455410
protected:
    __cdecl Env(void);  // 0x596ac0
    virtual __cdecl ~Env(void);  // 0x596bc0
public:
    virtual bool __cdecl Initialize(unsigned __int64, ::Zone *, ::GeoEnvObj const *);  // 0x596c30
    virtual bool __cdecl Think(::ScriptEvent const *);  // 0x596eb0
    virtual void __cdecl SetEnable(bool);  // 0x596f20
protected:
    bool __cdecl invokeEffect(::Creature *, ::Creature *, unsigned __int64);  // 0x5971c0
    bool __cdecl invokeMainFactionEffect(::Creature *, char);  // 0x597270
public:
    bool __cdecl SetSession(unsigned __int64);  // 0x597520
protected:
    virtual void __cdecl OnTimer(::Zone *, unsigned short);  // 0x597560
    void __cdecl onStateChange(::Zone *, char, char);  // 0x5975a0
    void __cdecl onEnableChange(::Zone *, bool);  // 0x5976f0
    bool __cdecl checkToManipulateQuestEnv(::Pc *, ::Item *, ::QuestRequiredItems const *, short &);  // 0x597800
    bool __cdecl checkToManipulateNormalEnv(::Pc *, unsigned __int64, short, ::Item *, unsigned __int64, short &);  // 0x597ba0
    void __cdecl manipulate(::Pc *, ::Item *, ::QuestRequiredItems const *);  // 0x597dc0
public:
    bool __cdecl IsQuestEnv(void);  // 0x598260
    bool __cdecl DropFieldItem(::Pc *, short, char);  // 0x5982a0
    static ::Env * __cdecl Create(int, ::Zone *, ::GeoEnvObj const *);  // 0x598550
protected:
    void __cdecl setQuestLootItemProb(void);  // 0x5989f0
public:
    bool __cdecl LootQuestCase(::Pc *, char, unsigned short, char, char, ::LootFailReason &);  // 0x598d70
    void __cdecl FetchExceptLootCase(::FragmentPacket *);  // 0x5990c0
    virtual bool __cdecl GetPos(::vector16 &);  // 0x599240
    virtual bool __cdecl GetActionPoint(::vector16 &);  // 0x599280
    virtual bool __cdecl GetManipulationCylinder(::cylinder16 &);  // 0x5992b0
    virtual bool __cdecl CheckToManipulate(::Pc *, ::Item *, ::QuestRequiredItems const *, char, short &);  // 0x599310
    virtual void __cdecl Manipulate(::Pc *, ::Item *, ::QuestRequiredItems const *, char);  // 0x599570
    virtual void __cdecl ChangeState(char);  // 0x599cb0
    virtual void __cdecl DiffHp(::Creature *, int, short, unsigned __int64, unsigned int);  // 0x599d40
    virtual bool __cdecl IsMoveBlock(void);  // 0x599f20
protected:
    ::ItemPouch * __cdecl makeItemPouch(::Pc *, int);  // 0x599f40
public:
    virtual void __cdecl InitState(void);  // 0x59a230
    bool __cdecl UpdateItemPouch(void);  // 0x59a3b0
    virtual bool __cdecl CheckToLoot(::Pc *);  // 0x59a410
    virtual void __cdecl OnKilled(::Zone *, ::GameObject *, unsigned __int64);  // 0x59a430
    virtual void __cdecl OnDamaged(::Zone *, ::GameObject *, unsigned int, __int64);  // 0x59a530
    virtual void __cdecl OnAttacked(::Zone *, ::GameObject *, unsigned __int64, short);  // 0x59a550
protected:
    void __cdecl setGuildBattleFieldGateEnable(bool);  // 0x59a570
public:
    void __cdecl SetGuildBattleFieldGateEnableOnly(bool);  // 0x59a6a0
protected:
    // LIFT: base GameObject and the PDB members from _geoEnvObj (+72) to _exceptLootCaseBitmap (+124) are not declared yet.
    char lift_pad_8[0x30 - 8];
    ::EnvZoneEnv2PtrView _env2;  // +48 (PDB: Data::ZoneEnv2RecordPtr)
    void *_env2spawn;  // +56 (PDB: Data::ZoneEnv2SpawnRecordPtr)
    ::EnvZoneEnv2PlacePtrView _env2place;  // +64 (PDB: Data::ZoneEnv2PlaceRecordPtr)
    char lift_pad_48[0x80 - 0x48];
    unsigned __int64 _ownerId;  // +128
};

class FallDeathRegion
{
public:
    virtual void __cdecl OnEntered(::Zone *, ::Creature *);  // 0x59ffb0
    void __cdecl ApplyEffect(::Creature *, bool);  // 0x5a0020
protected:
    virtual void __cdecl OnTimer(::Zone *, unsigned short);  // 0x5a01f0
};

class FishingPoint
{
public:
    virtual bool __cdecl CheckToManipulate(::Pc *, ::Item *, ::QuestRequiredItems const *, char, short &);  // 0x5a0280
    virtual void __cdecl Manipulate(::Pc *, ::Item *, ::QuestRequiredItems const *, char);  // 0x5a02c0
    bool __cdecl SetInfo(::Item *, unsigned __int64 &, __int64 &, __int64 &);  // 0x5a02d0
};

class FootSwitch
{
public:
    virtual void __cdecl OnEntered(::Zone *, ::Creature *);  // 0x59ebb0
    virtual void __cdecl OnLeaved(::Zone *, ::Creature *);  // 0x59eec0
};

class MultipleLoop
{
public:
    virtual bool __cdecl CheckToManipulate(::Pc *, ::Item *, ::QuestRequiredItems const *, char, short &);  // 0x59c3b0
    virtual void __cdecl Manipulate(::Pc *, ::Item *, ::QuestRequiredItems const *, char);  // 0x59c430
    virtual void __cdecl ChangeState(char);  // 0x59c480
    virtual void __cdecl InitState(void);  // 0x59c4a0
};

class OceanicRegion
{
public:
    virtual void __cdecl OnEntered(::Zone *, ::Creature *);  // 0x59fc50
    virtual void __cdecl OnLeaved(::Zone *, ::Creature *);  // 0x59fcc0
    void __cdecl ApplyEffect(::Creature *, bool);  // 0x59fcf0
protected:
    virtual void __cdecl OnTimer(::Zone *, unsigned short);  // 0x59fef0
};

class Portal
{
public:
    virtual void __cdecl OnEntered(::Zone *, ::Creature *);  // 0x59c5e0
    virtual bool __cdecl GetPos(::vector16 &);  // 0x59c9e0
    virtual bool __cdecl GetActionPoint(::vector16 &);  // 0x59ca30
    virtual short __cdecl GetActionRadius(void);  // 0x59ca70
    virtual bool __cdecl GetManipulationCylinder(::cylinder16 &);  // 0x59ca90
    virtual bool __cdecl CheckToManipulate(::Pc *, ::Item *, ::QuestRequiredItems const *, char, short &);  // 0x59cb00
    virtual void __cdecl Manipulate(::Pc *, ::Item *, ::QuestRequiredItems const *, char);  // 0x59cd40
private:
    bool __cdecl selectZone(::Creature *, int &, short &);  // 0x59cdf0
public:
    ::GameFailReason __cdecl ApplyTransit(::Creature *);  // 0x59cff0
private:
    bool __cdecl selectZoneByDungeonStep(unsigned __int64, ::Pc *, int &, short &);  // 0x59d500
    ::GameFailReason __cdecl checkTransit(::Pc *, ::Data::ZoneRecordPtr);  // 0x59d750
};

class Refiner
{
public:
    enum Operation {};
public:
    virtual bool __cdecl Initialize(unsigned __int64, ::Zone *, ::GeoEnvObj const *);  // 0x59a800
    virtual void __cdecl OnTimer(::Zone *, unsigned short);  // 0x59a840
    ::Refiner::Operation __cdecl GetOperation(char, char);  // 0x59aa40
    bool __cdecl TakeReward(::Pc *);  // 0x59aab0
    bool __cdecl CheckToGiveFactionScore(::Pc *);  // 0x59add0
    bool __cdecl GiveFactionScore(::Pc *, int &);  // 0x59ae20
    virtual long __cdecl GetManipulateDuration(char);  // 0x59b170
    virtual bool __cdecl CheckToManipulate(::Pc *, ::Item *, ::QuestRequiredItems const *, char, short &);  // 0x59b250
    virtual void __cdecl Manipulate(::Pc *, ::Item *, ::QuestRequiredItems const *, char);  // 0x59b3f0
    virtual void __cdecl ChangeState(char);  // 0x59b830
private:
    void __cdecl onOccopied(void);  // 0x59b960
    bool __cdecl invokeGuildEffect(bool, unsigned __int64);  // 0x59b9c0
public:
    virtual void __cdecl InitState(void);  // 0x59bc80
};

