// mentoringtran.h: mentoringtran.cpp, mentoringtran.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class ConfirmInvitationMentoringTran
{
public:
    virtual ::GameTranDef const * __cdecl GetDefinition(void) const;  // 0x16a300
    static ::GameTranDef _def;  // LIFT: PDB data ConfirmInvitationMentoringTran::_def
    __cdecl ConfirmInvitationMentoringTran(::User *);  // 0x16a320
private:
    virtual bool __cdecl work(int, void *);  // 0x16a4c0
    bool __cdecl init(int, void *);  // 0x16a540
    bool __cdecl abort(short);  // 0x16a600
    bool __cdecl confirmInvitationMentoring(void);  // 0x16a6d0
    bool __cdecl confirmInvitationMentoringOkFromCache(void *);  // 0x16a820
    bool __cdecl confirmInvitationMentoringFailFromCache(void *);  // 0x16ae90
};

class LeaveMentoringTran
{
public:
    virtual ::GameTranDef const * __cdecl GetDefinition(void) const;  // 0x16a310
    static ::GameTranDef _def;  // LIFT: PDB data LeaveMentoringTran::_def
private:
    virtual bool __cdecl work(int, void *);  // 0x16b000
    bool __cdecl init(int &, void *);  // 0x16b0e0
    bool __cdecl abort(short);  // 0x16b1d0
    bool __cdecl leaveMentoringReq(void);  // 0x16b2c0
    bool __cdecl leaveMentoringOkFromCache(void *);  // 0x16b390
};

