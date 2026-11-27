// manipulateaction.h: manipulateaction.cpp, manipulateaction.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"
#include "action.h"

class FishManipulateAction
{
public:
    bool __cdecl Initialize(::Zone *, ::Creature *, unsigned __int64, short, char, short, short, short, unsigned __int64, int, bool);  // 0x283c00
    __cdecl FishManipulateAction(void);  // 0x4675f0
private:
    virtual void __cdecl startAction(void);  // 0x4771b0
    virtual void __cdecl failAction(::Action::FailReason);  // 0x4776b0
    virtual void __cdecl finishAction(void);  // 0x4776f0
    virtual void __cdecl cancelAction(::Action::CancelReason, wchar_t const *, int);  // 0x477d80
    void __cdecl send(::Creature *, ::GameFailReason, short, int, ::FishInfoStatus);  // 0x478070
    bool __cdecl checkEnv(::Creature *, short &);  // 0x478330
    bool __cdecl checkItem(::Creature *, short &);  // 0x478450
    bool __cdecl checkFishingAvailability(::Creature *, short &);  // 0x4786d0
    bool __cdecl checkHooksetTime(::Creature *, ::GameLogEndFishingStatusCode &);  // 0x478920
    bool __cdecl checkDisposeFishingPaste(char);  // 0x478aa0
    bool __cdecl checkContentQuota(::Creature *);  // 0x478c00
    __int64 __cdecl consumeContentQuota(::Creature *, char);  // 0x478ce0
    bool __cdecl acquireLifeContentsPoint(::Creature *, short);  // 0x478e90
    int __cdecl decideFishRandomSize(int, int, unsigned __int64);  // 0x479050
    short __cdecl convertFailReason(short);  // 0x4791d0
};

class GiveFactionScoreToRefinerAction
{
private:
    virtual void __cdecl startAction(void);  // 0x476b60
    virtual void __cdecl failAction(::Action::FailReason);  // 0x476d60
    virtual void __cdecl finishAction(void);  // 0x476d90
    virtual void __cdecl cancelAction(::Action::CancelReason, wchar_t const *, int);  // 0x476fe0
};

class ManipulateAction
{
public:
    __cdecl ManipulateAction(::ActionClass);  // 0x467590
private:
    virtual void __cdecl startAction(void);  // 0x474d10
    virtual void __cdecl failAction(::Action::FailReason);  // 0x475440
    virtual void __cdecl finishAction(void);  // 0x475480
    virtual void __cdecl cancelAction(::Action::CancelReason, wchar_t const *, int);  // 0x475ae0
protected:
    bool __cdecl checkRange(::Creature *, short &);  // 0x475c40
    bool __cdecl getManipulationPoint(::Creature *, ::vector16 &);  // 0x475fa0
    void __cdecl disposeItem(::Creature *, ::Item *);  // 0x476090
    void __cdecl handleActionTarget(::Creature *, char, unsigned __int64);  // 0x476260
};

class ManipulateActionGameLog
{
public:
    static short __cdecl GetFishingFieldId(::Env *);  // 0x479230
    static short __cdecl GetFishingPasteId(::Item *);  // 0x479280
    static void __cdecl WriteFishManipulationStart(::Pc *, ::Item *, short, short, __int64);  // 0x4792f0
    static void __cdecl WriteFishManipulationCancel(::Pc *, int, short, short, bool, __int64);  // 0x4794f0
    static void __cdecl WriteFishManipulationFinish(::Pc *, int, short, short, ::Data::FishRecordPtr, int, __int64, bool, char, __int64);  // 0x4796b0
    static void __cdecl WriteDisposeItem(::Pc *, int, __int64, short, short);  // 0x479920
};

class NpcManipulateAction
{
private:
    virtual void __cdecl startAction(void);  // 0x4762d0
    virtual void __cdecl failAction(::Action::FailReason);  // 0x476800
    virtual void __cdecl finishAction(void);  // 0x476830
    virtual void __cdecl cancelAction(::Action::CancelReason, wchar_t const *, int);  // 0x476ad0
};

class TakeRefinerRewardTask
{
public:
    bool __cdecl Initialize(::Zone *, ::Creature *, unsigned __int64);  // 0x477060
private:
    virtual void __cdecl start(void);  // 0x4770f0
};

