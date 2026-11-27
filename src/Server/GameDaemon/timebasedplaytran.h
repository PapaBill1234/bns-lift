// timebasedplaytran.h: timebasedplaytran.cpp, timebasedplaytran.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class TakeTimeBasedPlayRewardTran
{
public:
    virtual ::GameTranDef const * __cdecl GetDefinition(void) const;  // 0x224250
    static ::GameTranDef _def;  // LIFT: PDB data TakeTimeBasedPlayRewardTran::_def
    __cdecl TakeTimeBasedPlayRewardTran(::User *);  // 0x224260
private:
    bool __cdecl sendFailToClient(short);  // 0x2242d0
    virtual bool __cdecl work(int, void *);  // 0x224320
    bool __cdecl takeToLobbyd(void *);  // 0x224420
    bool __cdecl takeToLobbydOk(void *);  // 0x224600
    bool __cdecl takeToLobbydFail(void *);  // 0x224e80
    bool __cdecl calcTimeBasedPlayInfo(void);  // 0x225030
};

