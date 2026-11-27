// tendencymanager.h: tendencymanager.cpp, tendencymanager.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class BuyuDoTendencyAttractionQuestPack
{
public:
    __cdecl BuyuDoTendencyAttractionQuestPack(void);  // 0x223940
    virtual bool __cdecl Init(::Data::TendencyFieldRecordPtr);  // 0x223a20
    virtual bool __cdecl GetNextQuests(::Pc *, char, char, char, unsigned __int64, int, short const *const, int, short *);  // 0x223a40
private:
    bool __cdecl getNextSimpleQuests(::Pc *, unsigned __int64, int, short const *const, int, short *);  // 0x223ad0
    bool __cdecl getNextTendencyQuests(::Pc *, char, char, unsigned __int64, int, short *);  // 0x223cc0
public:
    virtual void __cdecl Shake(void);  // 0x223e80
    virtual bool __cdecl AddQuest(char, short, char);  // 0x224050
};

class NormalTendencyAttractionQuestPack
{
public:
    __cdecl NormalTendencyAttractionQuestPack(void);  // 0x222f80
    virtual bool __cdecl GetNextQuests(::Pc *, char, char, char, unsigned __int64, int, short const *const, int, short *);  // 0x223010
private:
    bool __cdecl getNextSimpleQuests(unsigned __int64, int, short const *const, int, short *);  // 0x223090
    bool __cdecl getNextTendencyQuests(char, unsigned __int64, int, short *);  // 0x223270
public:
    virtual void __cdecl Shake(void);  // 0x223360
    virtual bool __cdecl Init(::Data::TendencyFieldRecordPtr);  // 0x223680
    virtual bool __cdecl AddQuest(char, short, char);  // 0x2236a0
};

class TendencyAttractionQuestPack
{
public:
    virtual __cdecl ~TendencyAttractionQuestPack(void);  // 0x1edf30
};

class TendencyField
{
public:
    struct EventData {};
public:
    __cdecl TendencyField(void);  // 0x21f560
    __cdecl ~TendencyField(void);  // 0x21f660
    bool __cdecl Initialize(unsigned __int64);  // 0x21f750
    void __cdecl DelZones(unsigned __int64 const *, int);  // 0x21f880
private:
    wchar_t const * __cdecl getStateStr(void);  // 0x21fa30
public:
    void __cdecl AddScore(unsigned __int64, unsigned __int64, unsigned __int64);  // 0x21fa70
    void __cdecl SetScore(__int64, __int64, __int64);  // 0x21fb60
    void __cdecl SetPlayValueForDebug(char);  // 0x21fc40
    void __cdecl GetJackpotInfo(int, bool, int &, char &);  // 0x21fd20
    bool __cdecl PublishTendencyQuestPack(char, ::Pc *, int, short *);  // 0x21fe40
    bool __cdecl CheckManifestTendency(__int64 &);  // 0x21ff20
private:
    void __cdecl setTendencyInfo(int, __int64);  // 0x21ffb0
    void __cdecl resetTendencyInfo(void);  // 0x220230
public:
    void __cdecl OnTimer(__int64, __int64);  // 0x2202d0
private:
    bool __cdecl timeCheck(::Data::TendencyFieldTendencyStateType, __int64);  // 0x2204a0
    bool __cdecl postNotifyEvent(unsigned __int64, ::TendencyField::EventData const &);  // 0x2205b0
    bool __cdecl postManifestTendencyTask(unsigned __int64);  // 0x2207c0
    void __cdecl collectScore(void);  // 0x220a50
    bool __cdecl onScoreCheck(__int64, __int64);  // 0x220c80
    bool __cdecl eventStandBy(__int64, int, int);  // 0x2211e0
    bool __cdecl onStandBy(__int64, __int64);  // 0x2218c0
    bool __cdecl onInProgress(__int64, __int64);  // 0x2219c0
    bool __cdecl eventFinish(__int64);  // 0x221a50
};

class TendencyManager
{
public:
    static void __cdecl FinalizeInstance(void);  // 0x221d50
private:
    __cdecl TendencyManager(void);  // 0x221df0
    void __cdecl cleanupData(void);  // 0x221ec0
public:
    void __cdecl TimerExpired(long);  // 0x221ff0
    void __cdecl CreateTendencyField(void);  // 0x2220b0
    bool __cdecl AddTendencyFieldTargetZone(unsigned __int64, unsigned __int64);  // 0x222300
    bool __cdecl AddTendencyFieldNonTargetZone(unsigned __int64, unsigned __int64);  // 0x2225b0
    void __cdecl SetTendencyScores(unsigned __int64, __int64, __int64, __int64);  // 0x2228a0
    void __cdecl SetPlayValue(unsigned __int64, char);  // 0x2229e0
    bool __cdecl CheckManifestTendency(unsigned __int64, __int64 &);  // 0x222b10
    bool __cdecl IsPlayable(unsigned __int64);  // 0x222bb0
    bool __cdecl AddQuest(::dr_tref, char, short, char);  // 0x222c40
    void __cdecl Shake(void);  // 0x222de0
    bool __cdecl PublishTendencyQuestPack(::dr_tref, char, ::Pc *, int, short *);  // 0x222e70
};

