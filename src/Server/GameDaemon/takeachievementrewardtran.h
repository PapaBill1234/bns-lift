// takeachievementrewardtran.h: takeachievementrewardtran.cpp, takeachievementrewardtran.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class TakeAchievementRewardTran
{
public:
    virtual ::GameTranDef const * __cdecl GetDefinition(void) const;  // 0x1d77b0
    static ::GameTranDef _def;  // LIFT: PDB data TakeAchievementRewardTran::_def
private:
    virtual bool __cdecl work(int, void *);  // 0x1d7820
    bool __cdecl init(int, void *);  // 0x1d7950
    bool __cdecl registerRewardStart(void);  // 0x1d7a50
    bool __cdecl registerRewardOk(void *);  // 0x1d86c0
public:
    static short __cdecl GetClientErrorCode(::TakeAchievementRewardTranFailParam::FAIL_FROM, short);  // 0x1d8a60
private:
    bool __cdecl registerRewardExpired(void);  // 0x1d8b10
    bool __cdecl registerRewardFail(void *);  // 0x1d8f50
    bool __cdecl finishPropertyTransactionReq(void);  // 0x1d9530
    bool __cdecl finishPropertyTransactionOk(void);  // 0x1d9700
    bool __cdecl finishPropertyTransactionFail(void);  // 0x1d9a10
    bool __cdecl completeAchievementReq(void);  // 0x1d9be0
    bool __cdecl completeAchievementOk(void);  // 0x1d9d60
    bool __cdecl completeAchievementFail(void);  // 0x1da270
};

