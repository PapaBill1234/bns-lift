// gamebuildertask.h: gamebuildertask.cpp, gamebuildertask.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class AasSetTimeTask
{
public:
    bool __cdecl Initialize(::Session const *, ::Zone *, ::Creature *, ::Creature *, char, char, int, int);  // 0x280550
private:
    virtual void __cdecl start(void);  // 0x280650
};

class AchievementSetRegisterBuilderTask
{
public:
    bool __cdecl Initialize(::Session const *, ::Zone *, ::Creature *, short, __int64);  // 0x281510
private:
    virtual void __cdecl start(void);  // 0x2815c0
};

class AddQuestTask
{
public:
    bool __cdecl Initialize(::Session const *, ::Zone *, ::Creature *, ::Creature *, __int64);  // 0x27ef50
private:
    virtual void __cdecl start(void);  // 0x27f030
};

class AnnounceZoneTask
{
public:
    bool __cdecl Initialize(::Session const *, ::Zone *, ::Creature *, wchar_t const *, char, char);  // 0x2802c0
private:
    virtual void __cdecl start(void);  // 0x2803b0
};

class ChangeChannelBuilderTask
{
public:
    bool __cdecl Initialize(::Session const *, ::Zone *, ::Creature *, int);  // 0x282930
private:
    virtual void __cdecl start(void);  // 0x2829d0
};

class DelSkillTask
{
public:
    bool __cdecl Initialize(::Session const *, ::Zone *, ::Creature *, ::Creature *, int);  // 0x27c200
private:
    virtual void __cdecl start(void);  // 0x27c2d0
};

class DeleteQuestTask
{
public:
    bool __cdecl Initialize(::Session const *, ::Zone *, ::Creature *, ::Creature *, __int64);  // 0x27f220
private:
    virtual void __cdecl start(void);  // 0x27f300
};

class DespawnNpcTask
{
public:
    bool __cdecl Initialize(::Session const *, ::Zone *, ::Creature *, ::Creature *);  // 0x27b870
private:
    virtual void __cdecl start(void);  // 0x27b9a0
};

class DispelAllTask
{
public:
    bool __cdecl Initialize(::Session const *, ::Zone *, ::Creature *, ::Creature *);  // 0x27c6d0
private:
    virtual void __cdecl start(void);  // 0x27c7a0
};

class DisposeItemAllTask
{
public:
    bool __cdecl Initialize(::Session const *, ::Zone *, ::Creature *);  // 0x281e70
private:
    virtual void __cdecl start(void);  // 0x281f00
};

class GetPcAssetTask
{
public:
    bool __cdecl Initialize(::Session const *, ::Zone *, ::Creature *, ::Creature *);  // 0x27f510
private:
    virtual void __cdecl start(void);  // 0x27f5e0
};

class GmHideTask
{
public:
    bool __cdecl Initialize(::Session const *, ::Zone *, ::Creature *);  // 0x27ace0
private:
    virtual void __cdecl start(void);  // 0x27ad70
};

class GmOnTask
{
public:
    bool __cdecl Initialize(::Session const *, ::Zone *, ::Creature *);  // 0x27e180
    static void __cdecl GmOn(::Pc &);  // 0x27e210
private:
    virtual void __cdecl start(void);  // 0x27e350
};

class HealthyTask
{
public:
    bool __cdecl Initialize(::Session const *, ::Zone *, ::Creature *);  // 0x27aef0
private:
    virtual void __cdecl start(void);  // 0x27af80
};

class InvokeEffectTask
{
public:
    bool __cdecl Initialize(::Session const *, ::Zone *, ::Creature *, wchar_t const *);  // 0x281b90
private:
    virtual void __cdecl start(void);  // 0x281ca0
};

class KillMeTask
{
public:
    bool __cdecl Initialize(::Session const *, ::Zone *, ::Creature *);  // 0x27b5d0
private:
    virtual void __cdecl start(void);  // 0x27b660
};

class LocTask
{
public:
    bool __cdecl Initialize(::Session const *, ::Zone *, ::Creature *);  // 0x27c560
private:
    virtual void __cdecl start(void);  // 0x27c5f0
};

class PartyHomeTask
{
public:
    bool __cdecl Initialize(::Session const *, ::Zone *, ::Creature *, ::Creature *);  // 0x27d410
private:
    virtual void __cdecl start(void);  // 0x27d4e0
};

class PartyShowTask
{
public:
    bool __cdecl Initialize(::Session const *, ::Zone *, ::Creature *, ::Creature *);  // 0x27f950
private:
    virtual void __cdecl start(void);  // 0x27fa20
};

class QuestBuilderTask
{
public:
    enum QuestBuilderType {};
public:
    __cdecl QuestBuilderTask(void);  // 0x27a300
private:
    wchar_t * __cdecl getcommandstr(::QuestBuilderTask::QuestBuilderType);  // 0x280d20
public:
    bool __cdecl Initialize(::Session const *, ::Zone *, ::Creature *, ::Creature *, unsigned short, char, char, int &);  // 0x280da0
private:
    virtual void __cdecl start(void);  // 0x280ed0
    void __cdecl sendsuccess(void);  // 0x281080
    void __cdecl sendfailure(int);  // 0x281380
};

class RecallTask
{
public:
    __cdecl RecallTask(void);  // 0x27a290
    bool __cdecl Initialize(::Session const *, ::Zone *, ::Creature *, ::Creature *);  // 0x27c8b0
private:
    virtual void __cdecl start(void);  // 0x27c980
    void __cdecl warp(void);  // 0x27cba0
    bool __cdecl zoneTransition(void);  // 0x27cd40
};

class RemoveSkillDelay
{
public:
    bool __cdecl Initialize(::Session const *, ::Zone *, ::Creature *);  // 0x27c3f0
private:
    virtual void __cdecl start(void);  // 0x27c480
};

class RemoveTraceTask
{
public:
    bool __cdecl Initialize(::Session const *, ::Zone *, ::Creature *, char);  // 0x2830b0
private:
    virtual void __cdecl start(void);  // 0x283150
};

class ResetActivatedTeleportAllTask
{
public:
    bool __cdecl Initialize(::Session const *, ::Zone *, ::Creature *);  // 0x2820b0
private:
    virtual void __cdecl start(void);  // 0x282140
};

class ResurrectTask
{
public:
    enum CommandType {};
public:
    __cdecl ResurrectTask(void);  // 0x27a220
    bool __cdecl Initialize(::Session const *, ::Zone *, ::Creature *, ::Creature *, ::ResurrectTask::CommandType);  // 0x27b150
private:
    virtual void __cdecl start(void);  // 0x27b250
};

class ReturnToArenaLobbyBuilderTask
{
private:
    virtual void __cdecl start(void);  // 0x2809e0
};

class SendHomeTask
{
public:
    bool __cdecl Initialize(::Session const *, ::Zone *, ::Creature *, ::Creature *);  // 0x27d070
private:
    virtual void __cdecl start(void);  // 0x27d140
};

class SequesterItemTask
{
public:
    bool __cdecl Initialize(::Session const *, ::Zone *, ::Creature *, ::Creature *, char, short, bool);  // 0x27fdf0
private:
    virtual void __cdecl start(void);  // 0x27fee0
};

class ServerStatTask
{
public:
    bool __cdecl Initialize(::Session const *, ::Zone *, ::Creature *);  // 0x27ddb0
private:
    virtual void __cdecl start(void);  // 0x27de40
};

class SetActivatedTeleportAllTask
{
public:
    bool __cdecl Initialize(::Session const *, ::Zone *, ::Creature *);  // 0x281fa0
private:
    virtual void __cdecl start(void);  // 0x282030
};

class SetParamTask
{
public:
    bool __cdecl Initialize(::Session const *, ::Zone *, ::Creature *, ::Creature *, wchar_t *, __int64);  // 0x27d830
private:
    virtual void __cdecl start(void);  // 0x27d9e0
    bool __cdecl setLevel(char, ::ChangedProperty *);  // 0x27dc80
};

class SetSeasonContentsCombatRatingScoreBuilderTask
{
public:
    bool __cdecl Initialize(::Session const *, ::Zone *, ::Creature *, char, int);  // 0x2821c0
private:
    virtual void __cdecl start(void);  // 0x282270
};

class SetSkillTask
{
public:
    bool __cdecl Initialize(::Session const *, ::Zone *, ::Creature *, ::Creature *, int);  // 0x27c010
private:
    virtual void __cdecl start(void);  // 0x27c0e0
};

class SilenceTask
{
public:
    bool __cdecl Initialize(::Session const *, ::Zone *, ::Creature *, ::Creature *, char);  // 0x2800b0
private:
    virtual void __cdecl start(void);  // 0x280170
};

class SpawnNpcTask
{
public:
    bool __cdecl Initialize(::Session const *, ::Zone *, ::Creature *, wchar_t const *, char);  // 0x281680
private:
    virtual void __cdecl start(void);  // 0x2817a0
};

class SpawnZoneNpcBuilderTask
{
private:
    virtual void __cdecl start(void);  // 0x280890
};

class StartBattleRoyalFieldTask
{
public:
    bool __cdecl Initialize(::Session const *, ::Zone *, ::Creature *);  // 0x282ea0
private:
    virtual void __cdecl start(void);  // 0x282f30
};

class SummonTask
{
public:
    bool __cdecl Initialize(::Session const *, ::Zone *, ::Creature *, __int64, short);  // 0x27bc40
private:
    virtual void __cdecl start(void);  // 0x27bcf0
};

class TeleportTask
{
public:
    bool __cdecl Initialize(::Session const *, ::Zone *, ::Creature *, int, int, int, int);  // 0x27ea70
private:
    virtual void __cdecl start(void);  // 0x27eb30
    void __cdecl warp(void);  // 0x27ec00
    void __cdecl zoneTransition(void);  // 0x27ed60
};

class TeleportToTask
{
public:
    bool __cdecl Initialize(::Session const *, ::Zone *, ::Creature *, ::Creature *);  // 0x27e400
private:
    virtual void __cdecl start(void);  // 0x27e4d0
    void __cdecl warp(void);  // 0x27e6d0
    void __cdecl zoneTransition(void);  // 0x27e870
};

class UndyingTask
{
public:
    bool __cdecl Initialize(::Session const *, ::Zone *, ::Creature *, char);  // 0x27ab10
private:
    virtual void __cdecl start(void);  // 0x27abb0
};

class WhoTask
{
public:
    bool __cdecl Initialize(::Session const *, ::Zone *, ::Creature *);  // 0x27df80
private:
    virtual void __cdecl start(void);  // 0x27e010
};

::Pointer2< ::Creature> __cdecl GetCreature(unsigned __int64);  // 0x27a3f0
::Pointer2< ::Pc> __cdecl GetPcFromName(wchar_t const *);  // 0x27a5d0
bool __cdecl validateBuilder(wchar_t const *, ::Zone *, ::Creature *);  // 0x27a620
bool __cdecl validateTarget(wchar_t const *, ::Zone *, ::Creature *, ::Creature *);  // 0x27a6f0
void __cdecl AuditLogDIC(::Creature *, ::Creature *, wchar_t const *, int, wchar_t const *, ...);  // 0x27a800
