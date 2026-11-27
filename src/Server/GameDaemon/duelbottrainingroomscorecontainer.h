// duelbottrainingroomscorecontainer.h: duelbottrainingroomscorecontainer.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class DuelBotTrainingRoomScoreContainer
{
public:
    struct DuelBotTrainingRoomScoreValue;
public:
    __cdecl ~DuelBotTrainingRoomScoreContainer(void);  // 0xaeb90
private:
    void __cdecl syncToClient(::DuelBotTrainingRoomScoreEntry *) const;  // 0xaec30
public:
    bool __cdecl Initialize(::Pc *);  // 0xaee80
    bool __cdecl GetNewRecordValue(short, ::DuelBotTrainingRoomScoreContainer::DuelBotTrainingRoomScoreValue &, bool &) const;  // 0xaef40
    bool __cdecl SetRecordValue(short, ::DuelBotTrainingRoomScoreContainer::DuelBotTrainingRoomScoreValue &, bool, bool);  // 0xaf0c0
    ::DuelBotTrainingRoomScoreEntry const * __cdecl GetRecordEntry(short);  // 0xaf420
    char __cdecl GetAchievementValue(short, char);  // 0xaf480
    bool __cdecl SetRewardValueToRecord(::DuelBotTrainingRoomScoreContainer::DuelBotTrainingRoomScoreValue &, char, char);  // 0xaf670
    void __cdecl FetchList(::Packet *, ::RepeatPacketComposer *);  // 0xaf770
    bool __cdecl SetReceiveRewardFlag(void);  // 0xafa40
};

class DuelBotTrainingRoomScoreEntry
{
public:
    __cdecl DuelBotTrainingRoomScoreEntry(void);  // 0xae7b0
    __cdecl ~DuelBotTrainingRoomScoreEntry(void);  // 0xae800
    void __cdecl Initialize(short, short, short, short, short, short, short, short, short, short, short, short, short, short, short, short, short, short, short, short, short, short);  // 0xae820
};

struct DuelBotTrainingRoomScoreContainer::DuelBotTrainingRoomScoreValue
{
public:
    void __cdecl SetAchievementValue(short, char);  // 0xaeab0
};

