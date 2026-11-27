// duelbottrainingroomtran.h: duelbottrainingroomtran.cpp, duelbottrainingroomtran.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class DuelBotTrainingRoomResultTran
{
public:
    virtual ::GameTranDef const * __cdecl GetDefinition(void) const;  // 0xaca50
private:
    virtual bool __cdecl work(int, void *);  // 0xafaf0
    bool __cdecl init(int, void *);  // 0xafb70
    bool __cdecl updateDuelBotTrainingRoomScoreTry(void);  // 0xafd20
    bool __cdecl updateDuelBotTrainingRoomScoreOk(void *);  // 0xafe50
    bool __cdecl updateDuelBotTrainingRoomScoreFail(short);  // 0xb0180
};

class DuelBotTrainingRoomRewardTran
{
public:
    virtual ::GameTranDef const * __cdecl GetDefinition(void) const;  // 0xaca60
private:
    virtual bool __cdecl work(int, void *);  // 0xb0320
    bool __cdecl init(int, void *);  // 0xb03a0
    bool __cdecl takeDuelBotTrainingRoomRewardTry(void);  // 0xb0540
    bool __cdecl takeDuelBotTrainingRoomRewardOk(void *);  // 0xb10e0
    bool __cdecl takeDuelBotTrainingRoomRewardFail(void *);  // 0xb1420
};

